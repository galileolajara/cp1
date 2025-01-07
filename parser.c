#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>

union glc_token {
   struct {
      int row;
      int col;
      int id;
      int id2;
   } basic;
   struct {
      int v[15];
      int c;
   } index;
   void* pointer;
};

typedef int _Mglc_Eexpr_i;
typedef int _Mglc_Eid;
typedef int _Mglc_Einclude;
typedef int _Mglc_Eat;
typedef int8_t _Mglc_Ebasic_type_id;
typedef int8_t _Mglc_Eunary;
typedef int8_t _Mglc_Emath;
typedef int8_t _Mglc_Eexpr_type;
typedef int8_t _Mglc_Eexpr_int;
typedef int8_t _Mglc_Ename_type;
typedef int8_t _Mglc_Estmt_type;
typedef int8_t _Mglc_Ecompare;
typedef int8_t _Mglc_Eassign;
typedef int8_t _Mglc_Ebools;
typedef int8_t _Mglc_Etoken;
struct _Mglc_Sstmt_space;
struct _Mglc_Sstmt;
struct _Mglc_Sexpr_data;
#ifdef GLC_NEW
#include "out/export.h"
#else
#include "export.h"
#endif

extern int _Glast_row;
extern int _Glast_col;
extern int _Grow;
extern int _Gcol;
int _Glast_row;
int _Glast_col;
int _Grow;
int _Gcol;

extern char* input_path;

#ifdef GLC_NEW
#include "out/cgl_parser.c"
#else
#include "cgl_parser.c"
#endif

struct glc_lexer {
   const char *content;
   const char *start;
   const char *cursor;
   const char *limit;
   const char *marker;
   const char *ctx_marker;
};

void* _Mglc_Sparser_Palloc_0() {
   return glcParseAlloc(malloc);
}

void _Mglc_Sparser_Pfree_1(void* parser) {
   glcParseFree(parser, free);
}

int _Mglc_Pchar_escape_value_1(char c) {
   switch(c) {
      case 'a': return '\a';
      case 'b': return '\b';
      case 'f': return '\f';
      case 'n': return '\n';
      case 'r': return '\r';
      case 't': return '\t';
      case 'v': return '\v';
      case '\\': return '\\';
      case '\'': return '\'';
      case '"': return '"';
      case '0': return '\0';
      default:
         printf("%s:%u:%u: Invalid escape sequence '\\%c'\n", input_path, _Grow, _Gcol, c);
         exit(EXIT_FAILURE);
   }
}

#ifdef GLC_NEW
#include "out/lexer.c"
#else
#include "lexer.c"
#endif
