#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <spawn.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

#define PORT 60101
#define BACKLOG 5

extern char **environ;
int server_fd;

struct Path {
   int len;
   char str[0];
};

pthread_mutex_t path_mutex;

struct Path** path_v;
int32_t path_cap;
int32_t path_c;

void *handle_client(void *arg) {
   struct sockaddr_in address;
   int addrlen = sizeof(address);
   // char buffer[1024] = {0};

   while (1) {
      int new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
      if (new_socket < 0) {
         perror("accept failed");
         continue;
      }
      // printf("Connection accepted by thread %ld\n", pthread_self());

      /*
      // Send a response
      char *response = "Hello from server";
      send(new_socket, response, strlen(response), 0);

      close(new_socket);
      */
      uint8_t path[4096];
      int path_len = read(new_socket, path, sizeof(path));
      path[path_len] = 0;
      // printf("parsing [%.*s]\n", path_len, path);

      pthread_mutex_lock(&path_mutex);
      bool found = false;
      for (int32_t i = 0; i < path_c; i++) {
         if ((path_v[i]->len == path_len) && (memcmp(path_v[i]->str, path, path_len) == 0)) {
            found = true;
            break;
         }
      }

      if (found) {
         pthread_mutex_unlock(&path_mutex);
         // printf("race condition for [%.*s]\n", path_len, path);
         close(new_socket);
      } else {
         int32_t i = path_c++;
         if (path_cap < path_c) {
            path_cap += path_cap;
            path_v = realloc(path_v, path_cap * sizeof(void*));
         }
         struct Path* p = malloc(sizeof(struct Path) + path_len);
         p->len = path_len;
         memcpy(p->str, path, path_len);
         path_v[i] = p;
         pthread_mutex_unlock(&path_mutex);

         pid_t pid;
         char *argv[] = {"out/cp1-parse", (char*)path, NULL};
         int ret = posix_spawn(&pid, "out/cp1-parse", NULL, NULL, argv, environ);
         // printf("posix_spawn out/cp1-parse [%.*s], returned %d\n", path_len, path, ret);
         int status;
         waitpid(pid, &status, 0);

         pthread_mutex_lock(&path_mutex);
         // re-find 'i' because it might be moved
         for (int32_t j = 0; j < path_c; j++) {
            if (p == path_v[j]) {
               i = j;
               break;
            }
         }

         path_c--;
         if (i != path_c) {
            path_v[i] = path_v[path_c];
         }
         pthread_mutex_unlock(&path_mutex);

         write(new_socket, path, 1);
         read(new_socket, path, 1);
         close(new_socket);
      }
   }

   return NULL;
}

void daemonize() {
   pid_t pid = fork();
   if (pid < 0) {
      perror("fork");
      exit(EXIT_FAILURE);
   }
   if (pid > 0) {
      // Parent exits, leaving child in background
      exit(EXIT_SUCCESS);
   }

   // Create a new session and become session leader
   if (setsid() < 0) {
      perror("setsid");
      exit(EXIT_FAILURE);
   }

   // Fork again to prevent reacquiring a terminal
   pid = fork();
   if (pid < 0) {
      perror("fork");
      exit(EXIT_FAILURE);
   }
   if (pid > 0) {
      exit(EXIT_SUCCESS);
   }

   // Set file permissions mask to 0
   umask(0);

   /*
   // Change working directory to root to avoid locking a filesystem
   if (chdir("/") < 0) {
      perror("chdir");
      exit(EXIT_FAILURE);
   }
   */

   // Redirect standard file descriptors to /dev/null
   int fd = open("/dev/null", O_RDWR);
   if (fd < 0) {
      perror("open");
      exit(EXIT_FAILURE);
   }
   dup2(fd, STDIN_FILENO);
   dup2(fd, STDOUT_FILENO);
   dup2(fd, STDERR_FILENO);
   close(fd);
}

void handle_signal(int sig) {
   if (sig == SIGTERM || sig == SIGINT) {
      exit(0);
   }
}

int main() {
   daemonize();

   // Handle termination signals
   signal(SIGTERM, handle_signal);
   signal(SIGINT, handle_signal);

   // printf("setsid %d %s\n", pid, strerror(errno));

   path_cap = 32;
   path_v = malloc(path_cap * sizeof(void*));

   if (pthread_mutex_init(&path_mutex, NULL) != 0) {
      perror("Mutex init failed");
      return EXIT_FAILURE;
   }

   struct sockaddr_in address;
   int addrlen = sizeof(address);

   // Create socket
   if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
      perror("socket failed");
      exit(EXIT_FAILURE);
   }

   int opt = 1;
   if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
      perror("setsockopt failed");
      close(server_fd);
      exit(EXIT_FAILURE);
   }

   // Bind address
   address.sin_family = AF_INET;
   address.sin_addr.s_addr = INADDR_ANY;
   address.sin_port = htons(PORT);

   if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
      // perror("bind failed");
      exit(EXIT_FAILURE);
   }

   // Start listening
   if (listen(server_fd, BACKLOG) < 0) {
      // perror("listen failed");
      exit(EXIT_FAILURE);
   }
   // printf("Listening on port %d...\n", PORT);

   // Get number of CPU cores
   int num_threads = sysconf(_SC_NPROCESSORS_ONLN);
	// printf("threads: %u\n", num_threads);
   pthread_t threads[256];

   // Spawn threads
   for (int i = 0; i < num_threads; i++) {
      if (pthread_create(&threads[i], NULL, handle_client, NULL) != 0) {
         perror("pthread_create failed");
         exit(EXIT_FAILURE);
      }
   }

   // Join threads
   for (int i = 0; i < num_threads; i++) {
      pthread_join(threads[i], NULL);
   }

   close(server_fd);
   return 0;
}
