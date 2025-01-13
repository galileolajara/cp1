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

void _Nglc_Ppreprocess_def_2(const char*, uint8_t);

void _Nglc_Ppreprocess_init_0() {
#ifdef _WIN32
   _Nglc_Ppreprocess_def_2("windows", 7);
#endif
#ifdef __APPLE__
   _Nglc_Ppreprocess_def_2("apple", 5);
	#ifdef TARGET_OS_MAC
   _Nglc_Ppreprocess_def_2("macos", 5);
	#endif
#endif
#ifdef __linux__
   _Nglc_Ppreprocess_def_2("linux", 5);
#endif
#ifdef __unix__
   _Nglc_Ppreprocess_def_2("unix", 4);
#endif
#ifdef BSD
   _Nglc_Ppreprocess_def_2("bsd", 3);
#endif
#ifdef __FreeBSD__
   _Nglc_Ppreprocess_def_2("freebsd", 7);
#endif
#ifdef __OpenBSD__
   _Nglc_Ppreprocess_def_2("openbsd", 7);
#endif
#ifdef __NetBSD__
   _Nglc_Ppreprocess_def_2("netbsd", 6);
#endif
#ifdef __DragonFly__
   _Nglc_Ppreprocess_def_2("dragonfly", 9);
#endif
#if defined(_LP64) || defined(__LP64__)
   _Nglc_Ppreprocess_def_2("cpu64", 5);
#endif
}

extern char* _Glock_path;
void cleanup() {
   if (_Glock_path != 0) {
      // printf("deleting %s\n", _Glock_path);
      unlink(_Glock_path);
   }
}
void _Nglc_Pparser_at_exit_0() {
   atexit(cleanup);
}

typedef int _Nglc_Nexpr_i;
typedef int _Nglc_Nid;
typedef int _Nglc_Ninclude;
typedef int _Nglc_Nat;
typedef int8_t _Nglc_Nbasic_type_id;
typedef int8_t _Nglc_Nunary;
typedef int8_t _Nglc_Nmath;
typedef int8_t _Nglc_Nexpr_type;
typedef int8_t _Nglc_Nexpr_int;
typedef int8_t _Nglc_Nname_type;
typedef int8_t _Nglc_Nstmt_type;
typedef int8_t _Nglc_Ncompare;
typedef int8_t _Nglc_Nassign;
typedef int8_t _Nglc_Nbools;
typedef int8_t _Nglc_Ntoken;
struct _Nglc_Nstmt_space;
struct _Nglc_Nstmt;
struct _Nglc_Nexpr_data;
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
#include "out/cp1_parser.c"
#else
#include "cp1_parser.c"
#endif

struct glc_lexer {
   const char *content;
   const char *start;
   const char *cursor;
   // const char *limit;
   const char *marker;
   // const char *ctx_marker;
};

void* _Nglc_Nparser_Palloc_0() {
   return glcParseAlloc(malloc);
}

void _Nglc_Nparser_Pfree_1(void* parser) {
   glcParseFree(parser, free);
}

int _Nglc_Pchar_escape_value_1(char c) {
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
