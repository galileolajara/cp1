#include <stdio.h>
extern FILE* _Gout;
void _NCp1_Pwrite_str_node_2(int len, char* buf) {
   fputc('"', _Gout);
   for (int i = 0; i < len; i ++) {
      switch(buf[i]) {
         case '\a': fputc('\\', _Gout); fputc('a', _Gout); break;
         case '\b': fputc('\\', _Gout); fputc('b', _Gout); break;
         case '\f': fputc('\\', _Gout); fputc('f', _Gout); break;
         case '\n': fputc('\\', _Gout); fputc('n', _Gout); break;
         case '\r': fputc('\\', _Gout); fputc('r', _Gout); break;
         case '\t': fputc('\\', _Gout); fputc('t', _Gout); break;
         case '\v': fputc('\\', _Gout); fputc('v', _Gout); break;
         case '\\': fputc('\\', _Gout); fputc('\\', _Gout); break;
         case '\'': fputc('\'', _Gout); break;
         case '"': fputc('\\', _Gout); fputc('"', _Gout); break;
         case '\0': fputc('\\', _Gout); fputc('0', _Gout); break;
         default:
            fputc(buf[i], _Gout);
      }
   }
   fputc('"', _Gout);
}

void _NCp1_Pwrite_char_1(char c) {
   switch(c) {
      case '\a': fprintf(_Gout, "'\\a'"); break;
      case '\b': fprintf(_Gout, "'\\b'"); break;
      case '\f': fprintf(_Gout, "'\\f'"); break;
      case '\n': fprintf(_Gout, "'\\n'"); break;
      case '\r': fprintf(_Gout, "'\\r'"); break;
      case '\t': fprintf(_Gout, "'\\t'"); break;
      case '\v': fprintf(_Gout, "'\\v'"); break;
      case '\\': fprintf(_Gout, "'\\\\'"); break;
      case '\'': fprintf(_Gout, "'\\''"); break;
      case '"': fprintf(_Gout, "'\\\"'"); break;
      case '\0': fprintf(_Gout, "'\\0'"); break;
      default: fprintf(_Gout, "'%c'", c); break;
   }
}
