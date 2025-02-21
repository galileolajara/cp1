#include <stdio.h>
#include <stdint.h>
void _NCp1_Poutput_reserve_1(uint32_t);
extern char* output_data;
extern uint32_t output_len;
void _NCp1_Pwrite_str_node_2(uint32_t len, char* buf) {
   _NCp1_Poutput_reserve_1(2 + (len << 1));
   output_data[output_len++] = '"';
   for (int i = 0; i < len; i ++) {
      switch(buf[i]) {
case '\a': output_data[output_len++] = '\\'; output_data[output_len++] = 'a'; break;
case '\b': output_data[output_len++] = '\\'; output_data[output_len++] = 'b'; break;
case '\f': output_data[output_len++] = '\\'; output_data[output_len++] = 'f'; break;
case '\n': output_data[output_len++] = '\\'; output_data[output_len++] = 'n'; break;
case '\r': output_data[output_len++] = '\\'; output_data[output_len++] = 'r'; break;
case '\t': output_data[output_len++] = '\\'; output_data[output_len++] = 't'; break;
case '\v': output_data[output_len++] = '\\'; output_data[output_len++] = 'v'; break;
case '\\': output_data[output_len++] = '\\'; output_data[output_len++] = '\\'; break;
case '\'': output_data[output_len++] = '\''; break;
case '"':  output_data[output_len++] = '\\'; output_data[output_len++] = '"'; break;
case '\0': output_data[output_len++] = '\\'; output_data[output_len++] = '0'; break;
default:   output_data[output_len++] = buf[i];
      }
   }
   output_data[output_len++] = '"';
}

void _NCp1_Pwrite_char_1(char c) {
   _NCp1_Poutput_reserve_1(4);
   output_data[output_len++] = '\'';
   switch(c) {
   case '\a': output_data[output_len++] = '\\'; output_data[output_len++] = 'a'; break;
   case '\b': output_data[output_len++] = '\\'; output_data[output_len++] = 'b'; break;
   case '\f': output_data[output_len++] = '\\'; output_data[output_len++] = 'f'; break;
   case '\n': output_data[output_len++] = '\\'; output_data[output_len++] = 'n'; break;
   case '\r': output_data[output_len++] = '\\'; output_data[output_len++] = 'r'; break;
   case '\t': output_data[output_len++] = '\\'; output_data[output_len++] = 't'; break;
   case '\v': output_data[output_len++] = '\\'; output_data[output_len++] = 'v'; break;
   case '\\': output_data[output_len++] = '\\'; output_data[output_len++] = '\\'; break;
   case '\'': output_data[output_len++] = '\\'; output_data[output_len++] = '\''; break;
   case '"':  output_data[output_len++] = '\\'; output_data[output_len++] = '"'; break;
   case '\0': output_data[output_len++] = '\\'; output_data[output_len++] = '0'; break;
   default:   output_data[output_len++] = c;
   }
   output_data[output_len++] = '\'';
}
#include <stdlib.h>
#include <string.h>
#include "sqlite3/sqlite3.h"
// #include "table.h"
#define TABLE_SCHEMA \
   "CREATE TABLE IF NOT EXISTS codes(" \
   "`path` TEXT NOT NULL PRIMARY KEY, " \
   "`text`, " \
   "`mtime` INT NOT NULL, " \
   "`binary`, " \
   "`parser-pid` INT NOT NULL) without rowid;"
sqlite3 *db;
sqlite3_stmt *stmt;
/* void closedb() {
   printf("closing database connection\n");
   sqlite3_finalize(stmt);
   sqlite3_close(db);
} */
void check_error(int rc, sqlite3 *db, const char *msg) {
    if (rc != SQLITE_OK && rc != SQLITE_DONE && rc != SQLITE_ROW) {
        fprintf(stderr, "Error: %s - %s\n", msg, sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }
}
#if 0
void _NCp1_Psqlite_init_0() {
   int rc;
   rc = sqlite3_open("cp1.db", &db);
   check_error(rc, db, "Cannot open database");
   // atexit(closedb);

   char *errMsg = 0;
   journal_again:
   rc = sqlite3_exec(db, "PRAGMA journal_mode = WAL;", NULL, NULL, &errMsg);
   if (rc == SQLITE_BUSY) {
      goto journal_again;
   }

   create_again:
   rc = sqlite3_exec(db, TABLE_SCHEMA, NULL, NULL, &errMsg);
   if (rc == SQLITE_BUSY) {
      goto create_again;
   }
   check_error(rc, db, "Cannot create table");

   const char *sql_select = "SELECT `binary` FROM `codes` WHERE `path` = ?;";

   // Prepare the statement
   prepare_again:
   rc = sqlite3_prepare_v2(db, sql_select, -1, &stmt, NULL);
   if (rc == SQLITE_BUSY) {
      goto prepare_again;
   }
   check_error(rc, db, "Cannot prepare statement");
}
void* _NCp1_Pread_cp1_2(char* path, int32_t path_len) {
   int rc;
   rc = sqlite3_bind_text(stmt, 1, path, path_len, SQLITE_STATIC);

   // Execute the query and fetch the result
   execute_again:
   rc = sqlite3_step(stmt);
   if (rc == SQLITE_BUSY) {
      goto execute_again;
   }
   check_error(rc, db, "Cannot execute statement");
   if (rc == SQLITE_ROW) {
      void* bin = sqlite3_column_blob(stmt, 0);
      size_t bin_size = sqlite3_column_bytes(stmt, 0);

      void* bin2 = malloc(bin_size);
      memcpy(bin2, bin, bin_size);

      sqlite3_reset(stmt);
      return bin2;
   } else if (rc == SQLITE_DONE) {
     // printf("No user found with the given name.\n");
     exit(EXIT_FAILURE);
   } else {
     // fprintf(stderr, "Error executing SELECT statement: %s\n", sqlite3_errmsg(db));
     exit(EXIT_FAILURE);
   }
   // return NULL;
}
#endif
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <spawn.h>
#include <arpa/inet.h>
#include <signal.h>
#include <fcntl.h>
#define SERVER_IP "127.0.0.1"  // Change this to the server's IP if needed
#define SERVER_PORT 60101
extern char **environ;
// int sock;
void _NCp1_Prun_server_0() {
   /* pid_t pid = fork();

   if (pid < 0) {
      // Fork failed
      printf("fork failed\n");
      exit(EXIT_FAILURE);
      return;
   } else if (pid == 0) {
      // Child process
      printf("fork made a child process\n");
      // char arg
      char* argv[1];
      argv[0] = NULL;
      execv("out/cp1-server", argv);
      // execlp("gedit", "gedit", (char *)NULL); // Replace "gedit" with any program you want to launch
      perror("execv"); // Only runs if execlp fails
      exit(EXIT_FAILURE);
      return;
   } */
   // printf("fork\n");

   // int sock;
   /* struct sigaction arg = {
      .sa_handler=SIG_IGN,
      .sa_flags=SA_NOCLDWAIT // Never wait for termination of a child process.
   };
   sigaction(SIGCHLD, &arg, NULL); */
   /* posix_spawnattr_t attr;

   // Initialize attributes
   posix_spawnattr_init(&attr);

   // Set the child process to be in a new process group (detached)
   int ret = posix_spawnattr_setpgroup(&attr, 0); */
   // printf("ret = %d\n", ret);
   /*posix_spawnattr_t attr;
   posix_spawn_file_actions_t file_actions;

   // Initialize attributes and file actions
   posix_spawnattr_init(&attr);
   posix_spawn_file_actions_init(&file_actions);

   // Redirect child's stdin to /dev/null (optional)
   posix_spawn_file_actions_addopen(&file_actions, 0, "/dev/null", O_RDONLY, 0); */
   pid_t pid;
   char *argv[] = {"out/cp1-server", NULL};
   posix_spawn(&pid, "out/cp1-server", NULL, NULL, argv, environ);
   // posix_spawnattr_destroy(&attr);
   // posix_spawn_file_actions_destroy(&file_actions);

   // Manually set the child’s process group after spawn
   // setpgid(pid, pid);
   // posix_spawnattr_destroy(&attr);
}
void _NCp1_Preq_parse_2(const char* path, int32_t path_len) {
   int sock;
   struct sockaddr_in server_addr;
   struct timespec wait_connect;
   // char *message = "Hello";
   
   // Define server address
   server_addr.sin_family = AF_INET;
   server_addr.sin_port = htons(SERVER_PORT);
   if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
      perror("Invalid address/Address not supported");
      close(sock);
      exit(EXIT_FAILURE);
   }
   
   // Create socket
   create_sock:
   sock = socket(AF_INET, SOCK_STREAM, 0);
   if (sock == -1) {
      perror("Socket creation failed");
      exit(EXIT_FAILURE);
   }

   wait_connect.tv_sec = 0;
   wait_connect.tv_nsec = 1000000; // 1 millisecond in nanoseconds
   
   // Connect to server
   reconnect:
   if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
      if (wait_connect.tv_nsec <= 512000000) { // 512 milliseconds in nanoseconds
         // printf("Cannot connect to cp1-server, retrying...\n");
         struct timespec rem;
         nanosleep(&wait_connect, &rem);
         wait_connect.tv_nsec += wait_connect.tv_nsec;
         goto reconnect;
      } else {
         printf("Cannot connect to cp1-server\n");
         exit(EXIT_FAILURE);
      }
   }
   write(sock, path, path_len);
   uint8_t data[4096];
   int len = read(sock, data, sizeof(data));
   if (len == 0) {
      close(sock);
      // printf("race, retrying...\n");
      goto create_sock;
   } else {
      write(sock, data, 1);
      // printf("read: %d\n", len);
      close(sock);
   }
}
