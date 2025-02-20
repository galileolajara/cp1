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
#include <stdlib.h>
#include <string.h>
#include "sqlite3/sqlite3.h"
// #include "table.h"
#define TABLE_SCHEMA \
   "CREATE TABLE IF NOT EXISTS codes(" \
   "`path` TEXT NOT NULL PRIMARY KEY, " \
   "`text`, " \
   "`mtime` INT NOT NULL, " \
   "`binary`, " \
   "`parser-pid` INT NOT NULL) without rowid;"
sqlite3 *db;
sqlite3_stmt *stmt;
/* void closedb() {
   printf("closing database connection\n");
   sqlite3_finalize(stmt);
   sqlite3_close(db);
} */
void check_error(int rc, sqlite3 *db, const char *msg) {
    if (rc != SQLITE_OK && rc != SQLITE_DONE && rc != SQLITE_ROW) {
        fprintf(stderr, "Error: %s - %s\n", msg, sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }
}
void _NCp1_Psqlite_init_0() {
   int rc;
   rc = sqlite3_open("cp1.db", &db);
   check_error(rc, db, "Cannot open database");
   // atexit(closedb);

   char *errMsg = 0;
   journal_again:
   rc = sqlite3_exec(db, "PRAGMA journal_mode = WAL;", NULL, NULL, &errMsg);
   if (rc == SQLITE_BUSY) {
      goto journal_again;
   }

   create_again:
   rc = sqlite3_exec(db, TABLE_SCHEMA, NULL, NULL, &errMsg);
   if (rc == SQLITE_BUSY) {
      goto create_again;
   }
   check_error(rc, db, "Cannot create table");

   const char *sql_select = "SELECT `binary` FROM `codes` WHERE `path` = ?;";

   // Prepare the statement
   prepare_again:
   rc = sqlite3_prepare_v2(db, sql_select, -1, &stmt, NULL);
   if (rc == SQLITE_BUSY) {
      goto prepare_again;
   }
   check_error(rc, db, "Cannot prepare statement");
}
void* _NCp1_Pread_cp1_2(char* path, int32_t path_len) {
   int rc;
   rc = sqlite3_bind_text(stmt, 1, path, path_len, SQLITE_STATIC);

   // Execute the query and fetch the result
   execute_again:
   rc = sqlite3_step(stmt);
   if (rc == SQLITE_BUSY) {
      goto execute_again;
   }
   check_error(rc, db, "Cannot execute statement");
   if (rc == SQLITE_ROW) {
      void* bin = sqlite3_column_blob(stmt, 0);
      size_t bin_size = sqlite3_column_bytes(stmt, 0);

      void* bin2 = malloc(bin_size);
      memcpy(bin2, bin, bin_size);

      sqlite3_reset(stmt);
      return bin2;
   } else if (rc == SQLITE_DONE) {
     // printf("No user found with the given name.\n");
     exit(EXIT_FAILURE);
   } else {
     // fprintf(stderr, "Error executing SELECT statement: %s\n", sqlite3_errmsg(db));
     exit(EXIT_FAILURE);
   }
   // return NULL;
}
