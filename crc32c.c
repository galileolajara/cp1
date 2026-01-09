#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "crc32c.h"

int main(int argc, char** argv) {
   int32_t sum = 0;
   for (int i = 1; i < argc - 1; i++) {
      int fd = open(argv[i],
            O_RDONLY
#ifdef _WIN32
            | O_BINARY
#endif
      );
      size_t len = lseek(fd, 0, SEEK_END);
      lseek(fd, 0, SEEK_SET);
      void* mem = malloc(len);
      read(fd, mem, len);
      close(fd);
      sum = crc32c(sum, mem, len);
   }
   FILE* f = fopen(argv[argc - 1], "wb");
   fprintf(f, "#define _Tcp1_Fbuild_crc32c_0() 0x%x\n", sum);
   fclose(f);
   return 0;
}
