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
char cp1_tmp_js[1024];
#define cp1_tmp_len 17
#define SPAWN_PARSE
#ifdef SPAWN_PARSE
char parser_path[1024];
#endif
char qjs_path[1024];
#include <sys/stat.h>
void hex32(char* out, uint32_t hex) {
   uint8_t i = 0;
   uint8_t n;
   n = hex >> 28;
   out[i++] = n < 10 ? '0' + n : 'a' + n - 10;
   n = (hex >> 24) & 15;
   out[i++] = n < 10 ? '0' + n : 'a' + n - 10;
   n = (hex >> 20) & 15;
   out[i++] = n < 10 ? '0' + n : 'a' + n - 10;
   n = (hex >> 16) & 15;
   out[i++] = n < 10 ? '0' + n : 'a' + n - 10;
   n = (hex >> 12) & 15;
   out[i++] = n < 10 ? '0' + n : 'a' + n - 10;
   n = (hex >> 8) & 15;
   out[i++] = n < 10 ? '0' + n : 'a' + n - 10;
   n = (hex >> 4) & 15;
   out[i++] = n < 10 ? '0' + n : 'a' + n - 10;
   n = hex & 15;
   out[i++] = n < 10 ? '0' + n : 'a' + n - 10;
}
#include "build-crc32c.c"
void _NCp1_Pc_init_1(uint32_t js_crc32c) {
   memcpy(cp1_tmp, "cp1-tmp-", 8);
   hex32(&cp1_tmp[8], _NCp1_Pbuild_crc32c_0());
   cp1_tmp[cp1_tmp_len - 1] = '\0';
   mkdir(cp1_tmp, 0755);
   cp1_tmp[cp1_tmp_len - 1] = '/';

   memcpy(cp1_tmp_js, "cp1-tmp-", 8);
   hex32(&cp1_tmp_js[8], js_crc32c);
   cp1_tmp_js[cp1_tmp_len - 1] = '\0';
   mkdir(cp1_tmp_js, 0755);
   cp1_tmp_js[cp1_tmp_len - 1] = '/';

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
}
bool _NCp1_Pwrite_file_3(char* _Lpath_0, void* _Ldata_1, size_t _Lsize_2);
void _NCp1_Pread_3(char* _Lin_path_cp1_0, uint16_t _Lin_path_cp1_len_1, bool strdup);
int quickjs_path_len;
void* _NCp1_Pread_file_5(char* _Lpath_0, int32_t _Ladd_before_1, int32_t _Ladd_after_2, size_t _Lmax_size_3, size_t* _Lout_size_4);
uint32_t _NCp1_Pquickjs_hex_2(char* js_data, uint32_t code_crc32c) {
   int i = 0;
   js_data[i++] = '/';
   js_data[i++] = '/';
   js_data[i++] = ' ';
   hex32(&js_data[i], code_crc32c);
   i += 8;
   js_data[i++] = ' ';
   return i;
}
bool _NCp1_Pquickjs_begin_6(char* path, uint8_t path_len, char* tplt_name, uint8_t tplt_name_len, uint32_t code_crc32c, uint32_t arg_crc32c) {
   int i;
   if (memcmp(path, "cp1-tmp-", 8) == 0) {
      i = 0;
   } else {
      i = cp1_tmp_len;
   }
   memcpy(cp1_tmp_js + i, path, path_len);
   i += path_len;
   cp1_tmp_js[i++] = '-';
   memcpy(&cp1_tmp_js[i], tplt_name, tplt_name_len);
   i += tplt_name_len;
   cp1_tmp_js[i++] = '-';
   hex32(&cp1_tmp_js[i], arg_crc32c);
   i += 8;
   cp1_tmp_js[i++] = '.';
   cp1_tmp_js[i++] = 'j';
   cp1_tmp_js[i++] = 's';
   int j = i;
   cp1_tmp_js[j++] = '.';
   cp1_tmp_js[j++] = 'c';
   cp1_tmp_js[j++] = 'p';
   cp1_tmp_js[j++] = '1';
   cp1_tmp_js[j] = '\0';
   size_t cache_size;
   char* cache = _NCp1_Pread_file_5(cp1_tmp_js, 0, 0, 12, &cache_size);
   if (cache != NULL && cache_size == 12) {
      char scratch[12];
      _NCp1_Pquickjs_hex_2(scratch, code_crc32c);
      if (memcmp(scratch, cache, 12) == 0) {
         // printf("%s did not change, using the cached copy\n", cp1_tmp_js);
         /* char* new_path = malloc(j + 1);
         memcpy(new_path, cp1_tmp_js, j + 1);
         _NCp1_Pread_2(new_path, j); */
         _NCp1_Pread_3(cp1_tmp_js, j, true);
         return false;
      }
   }
   cp1_tmp_js[i] = '\0';
   quickjs_path_len = i;
   return true;
}
void _NCp1_Pquickjs_end_2(char* js_data, uint32_t js_len) {
   char tmp_path[1024 + 10];
   sprintf(tmp_path, "%s-%u", cp1_tmp_js, getpid());
   _NCp1_Pwrite_file_3(tmp_path, js_data, js_len);
   #ifdef _WIN32
   unlink(cp1_tmp_js);
   #endif
   rename(tmp_path, cp1_tmp_js);
   const char *argv[] = {"cp1-qjs", cp1_tmp_js, NULL};
   // int status = qjs_main(2, argv);
   pid_t pid;
   int spawn = posix_spawn(&pid, qjs_path, NULL, NULL, argv, environ);
   int status;
   waitpid(pid, &status, 0);
   if (status != 0) {
      exit(EXIT_FAILURE);
   }
   int i = quickjs_path_len;
   cp1_tmp_js[i++] = '.';
   cp1_tmp_js[i++] = 'c';
   cp1_tmp_js[i++] = 'p';
   cp1_tmp_js[i++] = '1';
   cp1_tmp_js[i] = '\0';
   /* char* new_path = malloc(i + 1);
   memcpy(new_path, cp1_tmp_js, i + 1);
   _NCp1_Pread_2(new_path, i); */
   _NCp1_Pread_3(cp1_tmp_js, i, true);
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
   // const char* path = *ppath;
   const char* fullpath;
   char cp1_tmp2[1024];
   char* tmp = cp1_tmp;
   struct stat s;
   if (cp1_tmp == path /* memcmp(path, cp1_tmp, cp1_tmp_len) == 0 */) {
      stat_tmp:
      if (stat(path, &s) == 0) {
         memcpy(cp1_tmp2, path, path_len + 1);
         fullpath = cp1_tmp2;
      } else {
         goto notfound;
      }
      memcpy(tmp, path, path_len + 1);
      tmp[path_len] = '-';
      tmp[path_len + 1] = 'b';
      tmp[path_len + 2] = '\0';
   } else if (cp1_tmp_js == path /* memcmp(path, cp1_tmp_js, cp1_tmp_len) == 0 */) {
      tmp = cp1_tmp_js;
      goto stat_tmp;
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
      memcpy(tmp + cp1_tmp_len, path, path_len);
      tmp[cp1_tmp_len + path_len] = '-';
      tmp[cp1_tmp_len + path_len + 1] = 'b';
      tmp[cp1_tmp_len + path_len + 2] = '\0';
   }
   struct stat s2;
   if (stat(tmp, &s2) == 0) {
      // printf("comparing timestamps of %s and %s\n", tmp, path);
#ifdef __APPLE__
      if (s2.st_mtimespec.tv_sec > s.st_mtimespec.tv_sec) {
         // printf("cached\n");
         return tmp;
      } else if ((s2.st_mtimespec.tv_sec == s.st_mtimespec.tv_sec) && (s2.st_mtimespec.tv_nsec > s.st_mtimespec.tv_nsec)) {
         // printf("cached\n");
         return tmp;
      }
#else
      if (s2.st_mtim.tv_sec > s.st_mtim.tv_sec) {
         // printf("cached\n");
         return tmp;
      } else if ((s2.st_mtim.tv_sec == s.st_mtim.tv_sec) && (s2.st_mtim.tv_nsec > s.st_mtim.tv_nsec)) {
         // printf("cached\n");
         return tmp;
      }
#endif
   }
   create_folders_recursively(tmp);
   const char *argv[] = {"cp1-parse", fullpath, tmp, NULL};
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
   return tmp;
}
