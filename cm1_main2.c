#ifdef CP1_NEW
#include "out/compile2.cm1.c"
#else
#include "compile.cm1.c"
#endif

int main(int argc, char** argv) {
   const char* bin = argv[0];
   char abs_path[1024];
   uint16_t abs_path_len = 0;
   if (bin[0] == '/') {
      abs_path_len = strlen(bin);
      memcpy(abs_path, bin, abs_path_len);
      abs_path[abs_path_len] = '0';
   } else {
      bool has_slash = false;
      for (int i = 0; ; i++) {
         if (bin[i] == '\0') { break; }
         if (bin[i] == '/') {
            has_slash = true;
            break;
         }
      }
      if (has_slash) {
         #ifdef _WIN32
         /* cwd'char[1024]
         'x.getcwd(cwd, 1024)
         'c.strcpy(abs_path, &cwd[2])
         i' = 0
         loop ; ; i++ {
            if abs_path[i] == ''\0 {
               break
            } elif abs_path[i] == ''\\ {
               abs_path[i] = ''/
            }
         }
         abs_path[i++] = ''/
         'c.strcpy(&abs_path[i], bin) */
         #else
         realpath(bin, abs_path);
         #endif
      } else {
         char *path = strdup(getenv("PATH"));
         #ifdef _WIN32
         /* loop i' = 0; path[i] != ''\0; i++ {
            if path[i] == ''\\ {
               path[i] = ''/
            }
         }
         found = 'c.strtok(path, ";") */
         #else
         char *found = strtok(path, ":");
         #endif
         int fd = -1;
         while (found != NULL) {
            #ifdef _WIN32
            sprintf(abs_path, "%s/%s.exe", found, bin);
            #else
            sprintf(abs_path, "%s/%s", found, bin);
            #endif
            fd = open(abs_path, O_RDONLY);
            if (fd != -1) {
               close(fd);
               break;
            }
            #ifdef _WIN32
            // found = 'c.strtok(null, ";")
            #else
            found = strtok(NULL, ":");
            #endif
         }
         if (fd == -1) {
            printf("Cannot run %s because we can't detect its absolute path\n", bin);
            exit(EXIT_FAILURE);
         }
         free(path);
      }
   }
   char *slash = strrchr(abs_path, '/');
   #ifdef CP1_NEW
   strcpy(slash, "/cp1-compile.cm1");
   #else
   strcpy(slash, "/cp1-compile.cm1");
   #endif
   cm1_init(abs_path);
   return _Tcp1_Fmain_2(argc, argv);
}
