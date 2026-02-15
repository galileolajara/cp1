if (true) {
   char* src_path = argv[2];
   char cp1_path[1024];
   sprintf(cp1_path, "%s.cp1", src_path);
   char tmp_path[1024];
   sprintf(tmp_path, "%s.cp1-%u", src_path, getpid());
   int fd = open(tmp_path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
   write(fd, output_buf, output_len);
   close(fd);
   #ifdef _WIN32
   unlink(cp1_path);
   #endif
   rename(tmp_path, cp1_path);
   printf("%s -> %s\n", tmp_path, cp1_path);
}
