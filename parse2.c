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

#include "sqlite3/sqlite3.h"
// #include "table.h"
extern char* input_path;
sqlite3* db;
void check_error(int rc, sqlite3 *db, const char *msg) {
    if (rc != SQLITE_OK && rc != SQLITE_DONE && rc != SQLITE_ROW) {
        fprintf(stderr, "Error: %s - %s\n", msg, sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }
}
#include <time.h>
uint64_t current_time_millis() {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return (uint64_t)(ts.tv_sec) * 1000LL + (ts.tv_nsec / 1000000LL);
}
bool _NCp1_Pwrite_cp1_4(char* text_data, size_t text_size, uint8_t* bin_data, size_t bin_size) {
   printf("write-cp1(%s)\n", input_path);
   int rc;
   rc = sqlite3_open("cp1.db", &db);
   check_error(rc, db, "Cannot open database");
   
   // Enable WAL2 mode
   // char *errMsg = 0;
   // rc = sqlite3_exec(db, "PRAGMA journal_mode = WAL2;", NULL, NULL, &errMsg);

   // Create a table if it doesn't exist
   // rc = sqlite3_exec(db, TABLE_SCHEMA, NULL, NULL, &errMsg);

   sqlite3_stmt *stmt;
   const char *sql_insert = "REPLACE INTO codes(`path`, `text`, `binary`, `parser-pid`, `mtime`) VALUES (?, ?, ?, ?, ?);";
   rc = sqlite3_prepare_v2(db, sql_insert, -1, &stmt, NULL);
   check_error(rc, db, "Failed to prepare SELECT statement");

   // Bind values to placeholders (use ? placeholders in SQL)
   rc = sqlite3_bind_text(stmt, 1, input_path, -1, SQLITE_STATIC);
   rc = sqlite3_bind_text(stmt, 2, text_data, text_size, SQLITE_STATIC);
   rc = sqlite3_bind_blob(stmt, 3, bin_data, bin_size, SQLITE_STATIC);
   rc = sqlite3_bind_int(stmt, 4, getpid());
   rc = sqlite3_bind_int64(stmt, 5, current_time_millis());

   // Execute statement
   rc = sqlite3_step(stmt);
   check_error(rc, db, "Failed to execute REPLACE statement");

   // sqlite3_finalize(stmt);
   // sqlite3_close(db);
   return true;
}

union cp1_token {
   struct {
      int row;
      int col;
      float f32;
   } f32;
   struct {
      int row;
      int col;
      uint64_t u64;
   } u64;
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

/*
void _NCp1_Ppreprocess_def_2(const char*, uint8_t);

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

extern uint8_t _Glast_token;
/* extern char* _Glock_path;
void cleanup() {
   if (_Glock_path != 0) {
      // printf("deleting %s\n", _Glock_path);
      unlink(_Glock_path);
   }
}
void _NCp1_PParser_at_exit_0() {
   atexit(cleanup);
} */

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
typedef int8_t _NCp1_NToken;
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
   // const char *limit;
   const char *marker;
   // const char *ctx_marker;
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
