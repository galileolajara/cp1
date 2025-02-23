#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
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
#if 0
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
#endif
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
#include <sys/wait.h>
#define SERVER_IP "127.0.0.1"  // Change this to the server's IP if needed
#define SERVER_PORT 60101
extern char **environ;
extern char _Ginclude_dir[];
extern uint16_t _Ginclude_dir_len;
extern char** _Ginclude_path_v;
extern uint16_t* _Ginclude_path_len_v;
extern uint8_t _Ginclude_path_c;
char cp1_tmp[1024];
uint16_t cp1_tmp_len;
#define SPAWN_PARSE
#ifdef SPAWN_PARSE
char parser_path[1024];
#endif
char qjs_path[1024];
// char _Gcurrent_dir[1024];
// uint16_t _Gcurrent_dir_len;
#include <sys/stat.h>
void _NCp1_Pc_init_0() {
#if 0
   memcpy(&_Ginclude_dir[_Ginclude_dir_len], "/bin/cp1-server", 16);
   pid_t pid;
   char *argv[] = {"cp1-server", NULL};
   posix_spawn(&pid, _Ginclude_dir, NULL, NULL, argv, environ);
#endif

   memcpy(cp1_tmp, "cp1-tmp-0/", cp1_tmp_len = 10);
   // getcwd(_Gcurrent_dir, sizeof(_Gcurrent_dir));
   // _Gcurrent_dir_len = strlen(_Gcurrent_dir);
   // printf("current directory is %s\n", _Gcurrent_dir);
   /* for (uint8_t i = 0; i < _Ginclude_path_c; i++) {
      printf("- %s[%u]\n", _Ginclude_path_v[i], _Ginclude_path_len_v[i]);
   } */
   #ifdef SPAWN_PARSE
   memcpy(parser_path, _Ginclude_dir, _Ginclude_dir_len);
#ifdef CP1_NEW
   memcpy(parser_path + _Ginclude_dir_len, "/out/cp1-parse", 15);
#else
   memcpy(parser_path + _Ginclude_dir_len, "/bin/cp1-parse", 15);
#endif
   // printf("parser_path %s\n", parser_path);
   #endif

   memcpy(qjs_path, _Ginclude_dir, _Ginclude_dir_len);
/* #ifdef CP1_NEW
   memcpy(qjs_path + _Ginclude_dir_len, "/out/cp1-qjs", 13);
#else */
   memcpy(qjs_path + _Ginclude_dir_len, "/bin/cp1-qjs", 13);
// #endif

   mkdir("cp1-tmp-0", 0755);
}
// int qjs_main(int argc, char **argv);
bool _NCp1_Pwrite_file_3(char* _Lpath_0, void* _Ldata_1, size_t _Lsize_2);
void _NCp1_Pread_2(char* _Lin_path_cp1_0, uint32_t _Lin_path_cp1_len_1);
void _NCp1_Pquickjs_7(char* path, uint8_t path_len, char* tplt_name, uint8_t tplt_name_len, uint32_t arg_crc32c, char* js_data, uint32_t js_len) {
   int i = cp1_tmp_len;
   memcpy(cp1_tmp + i, path, path_len);
   i += path_len;
   cp1_tmp[i++] = '-';
   memcpy(&cp1_tmp[i], tplt_name, tplt_name_len);
   i += tplt_name_len;
   cp1_tmp[i++] = '-';
   uint8_t n;
   n = arg_crc32c >> 28;
   cp1_tmp[i++] = n < 10 ? '0' + n : 'a' + n - 10;
   n = (arg_crc32c >> 24) & 15;
   cp1_tmp[i++] = n < 10 ? '0' + n : 'a' + n - 10;
   n = (arg_crc32c >> 20) & 15;
   cp1_tmp[i++] = n < 10 ? '0' + n : 'a' + n - 10;
   n = (arg_crc32c >> 16) & 15;
   cp1_tmp[i++] = n < 10 ? '0' + n : 'a' + n - 10;
   n = (arg_crc32c >> 12) & 15;
   cp1_tmp[i++] = n < 10 ? '0' + n : 'a' + n - 10;
   n = (arg_crc32c >> 8) & 15;
   cp1_tmp[i++] = n < 10 ? '0' + n : 'a' + n - 10;
   n = (arg_crc32c >> 4) & 15;
   cp1_tmp[i++] = n < 10 ? '0' + n : 'a' + n - 10;
   n = arg_crc32c & 15;
   cp1_tmp[i++] = n < 10 ? '0' + n : 'a' + n - 10;
   cp1_tmp[i++] = '.';
   cp1_tmp[i++] = 'j';
   cp1_tmp[i++] = 's';
   cp1_tmp[i] = '\0';
   _NCp1_Pwrite_file_3(cp1_tmp, js_data, js_len);
   const char *argv[] = {"cp1-qjs", cp1_tmp, NULL};
   // int status = qjs_main(2, argv);
   pid_t pid;
   int spawn = posix_spawn(&pid, qjs_path, NULL, NULL, argv, environ);
   int status;
   waitpid(pid, &status, 0);
   if (status != 0) {
      // unlink(jspath);
      exit(EXIT_FAILURE);
   }
   cp1_tmp[i++] = '.';
   cp1_tmp[i++] = 'c';
   cp1_tmp[i++] = 'p';
   cp1_tmp[i++] = '1';
   cp1_tmp[i] = '\0';
   _NCp1_Pread_2(cp1_tmp, i);
}
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <libgen.h>  // For dirname()
#include <unistd.h>  // For access()
void create_folders_recursively(const char *file_path) {
    char path[1024];  
    strncpy(path, file_path, sizeof(path));
    path[sizeof(path) - 1] = '\0';

    // Get directory path from file path
    char *dir_path = dirname(path);

    // Tokenize path components
    char temp_path[1024] = {0};
    char *token = strtok(dir_path, "/");

    // Skip first directory
    int first = 1;
    while (token != NULL) {
        if (first) {
            first = 0;
            strcat(temp_path, token);
        } else {
            strcat(temp_path, "/");
            strcat(temp_path, token);

            // Check if directory exists
            // printf("trying to create directory %s\n", temp_path);
            if (access(temp_path, F_OK) != 0) {
                if (mkdir(temp_path, 0755) != 0 && errno != EEXIST) {
                    perror("mkdir failed");
                    return;
                }
            }
        }
        token = strtok(NULL, "/");
    }
}
// int parse_main(int argc, char** argv);
char* _NCp1_Preq_parse_2(const char* path, uint8_t path_len) {
   // printf("req-parse of %s\n", path);
   const char* fullpath;
   char cp1_tmp2[1024];
   struct stat s;
   if (path == cp1_tmp) {
      if (stat(path, &s) == 0) {
         // printf("file '%s' was found\n", path);
         memcpy(cp1_tmp2, path, path_len + 1);
         fullpath = cp1_tmp2;
      } else {
         goto notfound;
      }
      cp1_tmp[path_len] = '-';
      cp1_tmp[path_len + 1] = 'b';
      cp1_tmp[path_len + 2] = '\0';
   } else {
      if (stat(path, &s) == 0) {
         // printf("file '%s' was found\n", path);
         fullpath = path;
      } else {
         for (uint8_t i = 0; i < _Ginclude_path_c; i++) {
            memcpy(_Ginclude_path_v[i] + _Ginclude_path_len_v[i], path, path_len);
            _Ginclude_path_v[i][_Ginclude_path_len_v[i] + path_len] = 0;
            // printf("trying file '%.*s'\n", _Ginclude_path_len_v[i] + path_len, _Ginclude_path_v[i]);
            if (stat(_Ginclude_path_v[i], &s) == 0) {
               // printf("file '%s' was found\n", _Ginclude_path_v[i]);
               fullpath = _Ginclude_path_v[i];
               goto found;
            }
         }
         memcpy(&_Ginclude_dir[_Ginclude_dir_len], "/include/", 9);
         memcpy(&_Ginclude_dir[_Ginclude_dir_len + 9], path, path_len);
         _Ginclude_dir[_Ginclude_dir_len + 9 + path_len] = 0;
         // printf("trying file '%s'\n", _Ginclude_dir);
         if (stat(_Ginclude_dir, &s) == 0) {
            // printf("file '%s' was found\n", _Ginclude_path_v[i]);
            fullpath = _Ginclude_dir;
         } else {
            notfound:
            printf("Cannot find file '%s'\n", path);
            exit(EXIT_FAILURE);
         }
      }
      found:;
      memcpy(cp1_tmp + cp1_tmp_len, path, path_len);
      cp1_tmp[cp1_tmp_len + path_len] = '-';
      cp1_tmp[cp1_tmp_len + path_len + 1] = 'b';
      cp1_tmp[cp1_tmp_len + path_len + 2] = '\0';
   }
   struct stat s2;
   if (stat(cp1_tmp, &s2) == 0) {
#ifdef __APPLE__
      if (s2.st_mtimespec.tv_sec > s.st_mtimespec.tv_sec) {
         return cp1_tmp;
      } else if ((s2.st_mtimespec.tv_sec == s.st_mtimespec.tv_sec) && (s2.st_mtimespec.tv_nsec > s.st_mtimespec.tv_nsec)) {
         return cp1_tmp;
      }
#else
      if (s2.st_mtim.tv_sec > s.st_mtim.tv_sec) {
         return cp1_tmp;
      } else if ((s2.st_mtim.tv_sec == s.st_mtim.tv_sec) && (s2.st_mtim.tv_nsec > s.st_mtim.tv_nsec)) {
         return cp1_tmp;
      }
#endif
   }
   create_folders_recursively(cp1_tmp);
   // printf("parsing %s to %s\n", fullpath, cp1_tmp);
   const char *argv[] = {"cp1-parse", fullpath, cp1_tmp, NULL};
#ifdef SPAWN_PARSE
   pid_t pid;
   // memcpy(&_Ginclude_dir[_Ginclude_dir_len], "/bin/cp1-parse", 15);
   int spawn = posix_spawn(&pid, parser_path, NULL, NULL, argv, environ);
   int status;
   waitpid(pid, &status, 0);
   // printf("spawn %s = %d, %d, %d\n", _Ginclude_dir, spawn, pid, status);
#else
   int status = parse_main(3, argv);
#endif
   if (status != 0) {
      exit(EXIT_FAILURE);
   }
   return cp1_tmp;
#if 0
   int sock;
   struct sockaddr_in server_addr;
   struct timespec wait_connect;
   static char buf[16 * 1024];
   int bufi = 0;
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
#endif
}
