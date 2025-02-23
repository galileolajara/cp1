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
#include <sys/stat.h>
void _NCp1_Pc_init_0() {
   memcpy(cp1_tmp, "cp1-tmp-0/", cp1_tmp_len = 10);
   #ifdef SPAWN_PARSE
   memcpy(parser_path, _Ginclude_dir, _Ginclude_dir_len);
   #ifdef CP1_NEW
   memcpy(parser_path + _Ginclude_dir_len, "/out/cp1-parse", 15);
   #else
   memcpy(parser_path + _Ginclude_dir_len, "/bin/cp1-parse", 15);
   #endif
   #endif

   memcpy(qjs_path, _Ginclude_dir, _Ginclude_dir_len);
   memcpy(qjs_path + _Ginclude_dir_len, "/bin/cp1-qjs", 13);

   mkdir("cp1-tmp-0", 0755);
}
bool _NCp1_Pwrite_file_3(char* _Lpath_0, void* _Ldata_1, size_t _Lsize_2);
void _NCp1_Pread_2(char* _Lin_path_cp1_0, uint32_t _Lin_path_cp1_len_1);
int quickjs_path_len;
void* _NCp1_Pread_file_5(char* _Lpath_0, int32_t _Ladd_before_1, int32_t _Ladd_after_2, size_t _Lmax_size_3, size_t* _Lout_size_4);
uint32_t _NCp1_Pquickjs_hex_2(char* js_data, uint32_t code_crc32c) {
   int i = 0;
   js_data[i++] = '/';
   js_data[i++] = '/';
   js_data[i++] = ' ';
   uint8_t n;
   n = code_crc32c >> 28;
   js_data[i++] = n < 10 ? '0' + n : 'a' + n - 10;
   n = (code_crc32c >> 24) & 15;
   js_data[i++] = n < 10 ? '0' + n : 'a' + n - 10;
   n = (code_crc32c >> 20) & 15;
   js_data[i++] = n < 10 ? '0' + n : 'a' + n - 10;
   n = (code_crc32c >> 16) & 15;
   js_data[i++] = n < 10 ? '0' + n : 'a' + n - 10;
   n = (code_crc32c >> 12) & 15;
   js_data[i++] = n < 10 ? '0' + n : 'a' + n - 10;
   n = (code_crc32c >> 8) & 15;
   js_data[i++] = n < 10 ? '0' + n : 'a' + n - 10;
   n = (code_crc32c >> 4) & 15;
   js_data[i++] = n < 10 ? '0' + n : 'a' + n - 10;
   n = code_crc32c & 15;
   js_data[i++] = n < 10 ? '0' + n : 'a' + n - 10;
   js_data[i++] = ' ';
   return i;
}
bool _NCp1_Pquickjs_begin_6(char* path, uint8_t path_len, char* tplt_name, uint8_t tplt_name_len, uint32_t code_crc32c, uint32_t arg_crc32c) {
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
   int j = i;
   cp1_tmp[j++] = '.';
   cp1_tmp[j++] = 'c';
   cp1_tmp[j++] = 'p';
   cp1_tmp[j++] = '1';
   cp1_tmp[j] = '\0';
   size_t cache_size;
   char* cache = _NCp1_Pread_file_5(cp1_tmp, 0, 0, 12, &cache_size);
   if (cache != NULL && cache_size == 12) {
      char scratch[12];
      _NCp1_Pquickjs_hex_2(scratch, code_crc32c);
      if (memcmp(scratch, cache, 12) == 0) {
         // printf("%s did not change, using the cached copy\n", cp1_tmp);
         _NCp1_Pread_2(cp1_tmp, j);
         return false;
      }
   }
   cp1_tmp[i] = '\0';
   quickjs_path_len = i;
   return true;
}
void _NCp1_Pquickjs_end_2(char* js_data, uint32_t js_len) {
   char tmp_path[1024];
   sprintf(tmp_path, "%s-%u", cp1_tmp, getpid());
   _NCp1_Pwrite_file_3(tmp_path, js_data, js_len);
   #ifdef _WIN32
   unlink(cp1_tmp);
   #endif
   rename(tmp_path, cp1_tmp);
   const char *argv[] = {"cp1-qjs", cp1_tmp, NULL};
   // int status = qjs_main(2, argv);
   pid_t pid;
   int spawn = posix_spawn(&pid, qjs_path, NULL, NULL, argv, environ);
   int status;
   waitpid(pid, &status, 0);
   if (status != 0) {
      exit(EXIT_FAILURE);
   }
   int i = quickjs_path_len;
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
#else
   int status = parse_main(3, argv);
#endif
   if (status != 0) {
      exit(EXIT_FAILURE);
   }
   return cp1_tmp;
}
