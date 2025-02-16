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
