#ifdef __APPLE__
#include <TargetConditionals.h>
#endif
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>

struct _Ncp1_Ntoken_data_i32 {
   uint32_t row;
   uint32_t col;
   int32_t id;
   int32_t id2;
   int32_t id3;
};
struct _Ncp1_Ntoken_data_f32 {
   uint32_t row;
   uint32_t col;
   float f32;
};
struct _Ncp1_Ntoken_data_f64 {
   uint32_t row;
   uint32_t col;
   double f64;
};
struct _Ncp1_Ntoken_data_u64 {
   uint32_t row;
   uint32_t col;
   uint64_t u64;
};
struct _Ncp1_Ntoken_data_index {
   int v[15];
   int c;
};
union _Ncp1_Ntoken_data {
   struct _Ncp1_Ntoken_data_i32 basic;
   struct _Ncp1_Ntoken_data_f32 f32;
   struct _Ncp1_Ntoken_data_f64 f64;
   struct _Ncp1_Ntoken_data_u64 u64;
   struct _Ncp1_Ntoken_data_index index;
   void* pointer;
};

/*
void _Ncp1_Ppreprocess_init_0() {
#ifdef _WIN32
   _Ncp1_Ppreprocess_def_2("windows", 7);
#endif
#ifdef __APPLE__
   _Ncp1_Ppreprocess_def_2("apple", 5);
	#ifdef TARGET_OS_MAC
   _Ncp1_Ppreprocess_def_2("macos", 5);
	#endif
#endif
#ifdef __linux__
   _Ncp1_Ppreprocess_def_2("linux", 5);
#endif
#ifdef __unix__
   _Ncp1_Ppreprocess_def_2("unix", 4);
#endif
#ifdef BSD
   _Ncp1_Ppreprocess_def_2("bsd", 3);
#endif
#ifdef __FreeBSD__
   _Ncp1_Ppreprocess_def_2("freebsd", 7);
#endif
#ifdef __OpenBSD__
   _Ncp1_Ppreprocess_def_2("openbsd", 7);
#endif
#ifdef __NetBSD__
   _Ncp1_Ppreprocess_def_2("netbsd", 6);
#endif
#ifdef __DragonFly__
   _Ncp1_Ppreprocess_def_2("dragonfly", 9);
#endif
#if defined(_LP64) || defined(__LP64__)
   _Ncp1_Ppreprocess_def_2("cpu64", 5);
#endif
}
*/

extern int _Glast_token;
extern int _Glast_last_token;

typedef int _Ncp1_Nexpr_i;
typedef int _Ncp1_Nid;
typedef int _Ncp1_Ninclude;
typedef int _Ncp1_Nat;
typedef int8_t _Ncp1_Nbasic_type_id;
typedef int8_t _Ncp1_Nunary;
typedef int8_t _Ncp1_Nmath;
typedef int8_t _Ncp1_Nexpr_type;
typedef int8_t _Ncp1_Nexpr_int;
typedef int8_t _Ncp1_Nname_type;
typedef int8_t _Ncp1_Nstmt_type;
typedef int8_t _Ncp1_Ncompare;
typedef int8_t _Ncp1_Nassign;
typedef int8_t _Ncp1_Nbools;
typedef int _Ncp1_Ntoken;
struct _Ncp1_Nstmt_space;
struct _Ncp1_Nstmt;
struct _Ncp1_Nexpr_data;
#ifdef CP1_NEW
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

#ifdef CP1_NEW
#include "out/cp1_parse.c"
#else
#include "cp1_parse.c"
#endif

struct cp1_lexer {
   const char *content;
   const char *start;
   const char *cursor;
   const char *marker;
};

void* _Ncp1_Nparser_Palloc_0() {
   return cp1ParseAlloc(malloc);
}

void _Ncp1_Nparser_Pfree_1(void* parser) {
   cp1ParseFree(parser, free);
}

int _Ncp1_Pchar_escape_value_1(char c) {
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

#ifdef CP1_NEW
#include "out/lex.c"
#else
#include "lex.c"
#endif
