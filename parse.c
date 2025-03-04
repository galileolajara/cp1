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

struct _NCp1_NTokenDataI32 {
   uint32_t row;
   uint32_t col;
   int32_t id;
   int32_t id2;
   int32_t id3;
};
struct _NCp1_NTokenDataF32 {
   uint32_t row;
   uint32_t col;
   float f32;
};
struct _NCp1_NTokenDataU64 {
   uint32_t row;
   uint32_t col;
   uint64_t u64;
};
struct _NCp1_NTokenDataIndex {
   int v[15];
   int c;
};
union _NCp1_NTokenData {
   struct _NCp1_NTokenDataI32 basic;
   struct _NCp1_NTokenDataF32 f32;
   struct _NCp1_NTokenDataU64 u64;
   struct _NCp1_NTokenDataIndex index;
   void* pointer;
};

/*
void _NCp1_Ppreprocess_init_0() {
#ifdef _WIN32
   _NCp1_Ppreprocess_def_2("windows", 7);
#endif
#ifdef __APPLE__
   _NCp1_Ppreprocess_def_2("apple", 5);
	#ifdef TARGET_OS_MAC
   _NCp1_Ppreprocess_def_2("macos", 5);
	#endif
#endif
#ifdef __linux__
   _NCp1_Ppreprocess_def_2("linux", 5);
#endif
#ifdef __unix__
   _NCp1_Ppreprocess_def_2("unix", 4);
#endif
#ifdef BSD
   _NCp1_Ppreprocess_def_2("bsd", 3);
#endif
#ifdef __FreeBSD__
   _NCp1_Ppreprocess_def_2("freebsd", 7);
#endif
#ifdef __OpenBSD__
   _NCp1_Ppreprocess_def_2("openbsd", 7);
#endif
#ifdef __NetBSD__
   _NCp1_Ppreprocess_def_2("netbsd", 6);
#endif
#ifdef __DragonFly__
   _NCp1_Ppreprocess_def_2("dragonfly", 9);
#endif
#if defined(_LP64) || defined(__LP64__)
   _NCp1_Ppreprocess_def_2("cpu64", 5);
#endif
}
*/

extern int _Glast_token;
extern int _Glast_last_token;

typedef int _NCp1_NExprI;
typedef int _NCp1_NId;
typedef int _NCp1_NInclude;
typedef int _NCp1_NAt;
typedef int8_t _NCp1_NBasicTypeId;
typedef int8_t _NCp1_NUnary;
typedef int8_t _NCp1_NMath;
typedef int8_t _NCp1_NExprType;
typedef int8_t _NCp1_NExprInt;
typedef int8_t _NCp1_NNameType;
typedef int8_t _NCp1_NStmtType;
typedef int8_t _NCp1_NCompare;
typedef int8_t _NCp1_NAssign;
typedef int8_t _NCp1_NBools;
typedef int _NCp1_NToken;
struct _NCp1_NStmtSpace;
struct _NCp1_NStmt;
struct _NCp1_NExprData;
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

void* _NCp1_NParser_Palloc_0() {
   return cp1ParseAlloc(malloc);
}

void _NCp1_NParser_Pfree_1(void* parser) {
   cp1ParseFree(parser, free);
}

int _NCp1_Pchar_escape_value_1(char c) {
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
