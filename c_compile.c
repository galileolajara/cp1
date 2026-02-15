#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include "num.c"
#define putint Fputint
#define getint Fgetint
#define putnum Fputnum
#define getnum Fgetnum

char* string_buf;
uint32_t string_len;

struct c_token_data_i32 {
   uint32_t row;
   uint32_t col;
   int32_t id;
   int32_t id2;
   int32_t id3;
};

struct c_token_data_f32 {
   uint32_t row;
   uint32_t col;
   float f32;
};

struct c_token_data_f64 {
   uint32_t row;
   uint32_t col;
   double f64;
};

struct c_token_data_u64 {
   uint32_t row;
   uint32_t col;
   uint64_t u64;
};

struct c_token_data_index {
   int v[15];
   int c;
};

union c_token_data {
   struct c_token_data_i32 i32;
   struct c_token_data_f32 f32;
   struct c_token_data_f64 f64;
   struct c_token_data_u64 u64;
   struct c_token_data_index index;
   void* pointer;
};

struct c_lexer {
   uint8_t* content;
   uint8_t* start;
   uint8_t* cursor;
   uint8_t* marker;
};

#define id_t uint16_t
#define decl_t uint16_t
#define decl_nil 0xffff
#define decltype_t uint8_t
#define declidx_t uint16_t
#define expr_t uint32_t
#define expr_limit 0xffff
#define exprtype_t uint8_t
#define func_t declidx_t
#define type_t decl_t
#define type_void 0
#define type_u16 1
#define type_bool 2
#define type_char 3
#define exprtype_i32 0
#define exprtype_call 1
#define exprtype_math 2
#define exprtype_lvar 3
#define exprtype_gvar 4
#define exprtype_str 5
#define exprtype_unary 6
#define lvar_t uint16_t
#define lvar_limit 0x8000
#define stmt_t uint16_t
#define stmt_limit 0x8000
#define stmttype_t uint8_t
#define stmttype_lvar 0
#define stmttype_return 1
#define stmttype_assign 2
#define stmttype_expr 3
#define stmttype_if 4
#define stmttype_scope 5
#define mathtype_t uint8_t
#define mathtype_add 0
#define mathtype_sub 1
#define mathtype_mul 2
#define mathtype_div 3
#define scope_t uint16_t
#define scope_limit 0x8000
#define lvaridx_t uint8_t
#define call_arg_limit 16
#define nest_t uint8_t
#define nest_limit 16
#define gvar_t uint16_t
#define gvar_limit 0x8000
#define str_t uint16_t
#define str_limit 0x8000
#define unarytype_t uint8_t
#define unarytype_expoint 0

#define mem_t uint32_t
#define mem_max 0xffffffff
#define putmem(ptr, mem) putnum(ptr, mem)
#define getmem(ptr) getnum(ptr)

#define bc_write(op) *(bytecode_ptr++) = bc_##op;

#define bc_return 0
#define bc_return_32 1
#define bc_push_32 2
#define bc_push_call 3
#define bc_push_lvar_32 4
#define bc_add_i32 5
#define bc_sub_i32 6
#define bc_mul_i32 7
#define bc_div_i32 8
#define bc_lvar_set_32 9
#define bc_mem_set_8 10
#define bc_mem_push_8 11
#define bc_if 12
#define bc_jump 13
#define bc_push_addr 14
#define bc_not 15

#define id_limit 0x8000
#define decl_limit 0x8000
#define func_limit 0x8000
#define bytecode_limit (1024 * 1024 * 1024)

#define decltype_func 1
#define decltype_gvar 2

#define BIT8_IS(v, i) (v[(i) >> 3] & (1 << ((i) & 7))) != 0
#define BIT8_NOT(v, i) (v[(i) >> 3] & (1 << ((i) & 7))) == 0
#define BIT8_SET(v, i) v[(i) >> 3] |= 1 << ((i) & 7)

struct exprdata_i32_t {
   int32_t val;
};

struct exprdata_str_t {
   str_t str;
};

struct exprdata_call_t {
   id_t func_id;
   expr_t arg_v[call_arg_limit];
   uint8_t arg_c;
};

struct exprdata_math_t {
   mathtype_t type;
   expr_t a;
   expr_t b;
};

struct exprdata_unary_t {
   unarytype_t type;
   expr_t expr;
};

struct exprdata_lvar_t {
   lvar_t lvar;
};

struct exprdata_gvar_t {
   id_t name;
};

union exprdata_t {
   struct exprdata_i32_t i32;
   struct exprdata_call_t call;
   struct exprdata_math_t math;
   struct exprdata_unary_t unary;
   struct exprdata_lvar_t lvar;
   struct exprdata_gvar_t gvar;
   struct exprdata_str_t str;
};

struct stmtdata_lvar_t {
   lvar_t lvar;
   expr_t expr;
};

struct stmtdata_assign_t {
   expr_t des;
   expr_t src;
};

struct stmtdata_scope_t {
   scope_t scope;
};

struct stmtdata_expr_t {
   expr_t expr;
};

struct stmtdata_return_t {
   expr_t expr;
};

struct stmtdata_if_t {
   expr_t expr;
   bool is_elif;
};

union stmtdata_t {
   struct stmtdata_lvar_t lvar;
   struct stmtdata_return_t return_;
   struct stmtdata_assign_t assign;
   struct stmtdata_scope_t scope;
   struct stmtdata_expr_t expr;
   struct stmtdata_if_t if_;
};

const char* input_path;
uint8_t* id_str_v[id_limit];
uint8_t id_len_v[id_limit];
decl_t id_decl_v[id_limit];
id_t id_c;

id_t decl_id_v[decl_limit];
decltype_t decl_type_v[decl_limit];
declidx_t decl_idx_v[decl_limit];
uint32_t decl_row_v[decl_limit];
uint32_t decl_col_v[decl_limit];
decl_t decl_c;

decl_t func_decl_v[func_limit];
type_t func_type_v[func_limit];
lvar_t func_arg_first_v[func_limit];
lvar_t func_arg_last_v[func_limit];
lvar_t func_arg_limit_v[func_limit];
lvar_t func_lvar_limit_v[func_limit];
int32_t func_bytecode_v[func_limit];
scope_t func_scope_v[func_limit];
func_t func_c;
func_t func_arg_c;
func_t func_now;
func_t func_main = func_limit;

gvar_t gvar_decl_v[gvar_limit];
type_t gvar_type_v[gvar_limit];
mem_t gvar_mem_v[gvar_limit];
gvar_t gvar_c;
mem_t gvar_mem;

id_t lvar_id_v[lvar_limit];
lvaridx_t lvar_idx_v[lvar_limit];
lvar_t lvar_next_v[lvar_limit];
type_t lvar_type_v[lvar_limit];
uint32_t lvar_row_v[lvar_limit];
uint32_t lvar_col_v[lvar_limit];
lvar_t lvar_c;

stmttype_t stmt_type_v[stmt_limit];
union stmtdata_t stmt_data_v[stmt_limit];
uint32_t stmt_row_v[stmt_limit];
uint32_t stmt_col_v[stmt_limit];
stmt_t stmt_next_v[stmt_limit];
stmt_t stmt_c;

scope_t scope_parent_v[scope_limit];
lvar_t scope_lvar_first_v[scope_limit];
lvar_t scope_lvar_last_v[scope_limit];
stmt_t scope_stmt_first_v[scope_limit];
stmt_t scope_stmt_last_v[scope_limit];
scope_t scope_c;
scope_t scope_now;

char* str_buf_v[str_limit];
uint32_t str_len_v[str_limit];
mem_t str_mem_v[str_limit];
mem_t str_mem;
str_t str_c;

exprtype_t expr_type_v[expr_limit];
union exprdata_t expr_data_v[expr_limit];
uint32_t expr_row_v[expr_limit];
uint32_t expr_col_v[expr_limit];
expr_t expr_c;

expr_t call_arg_expr_v[nest_limit][call_arg_limit];
lvaridx_t call_arg_c[nest_limit];
nest_t call_c;

uint8_t bytecode_v[bytecode_limit];
uint8_t* bytecode_ptr;

int token_last;
uint32_t row_now;
uint32_t col_now;

void c_lexer_init(struct c_lexer* lex, void* data) {
   lex->start = data;
   lex->cursor = data;
   lex->content = data;
}

id_t c_lexer_id(uint8_t* str, uint32_t len) {
   printf("%.*s %u\n", len, str, len);
   if (len > 255) {
      printf("Identifier is too long (more than 255 bytes): %.*s\n", len, str);
      return 0;
   }
   uint32_t len8 = len;
   for (id_t i = 0; i < id_c; i++) {
      if ((id_len_v[i] == len8) && (memcmp(id_str_v[i], str, len8) == 0)) {
         return i;
      }
   }
   // printf("new id #%u: %.*s\n", id_c, len, lex->start);
   id_t i = id_c++;
   id_str_v[i] = str;
   id_len_v[i] = len8;
   id_decl_v[i] = decl_nil;
   return i;
}

void call_arg_begin() {
   call_arg_c[call_c] = 0;
   call_c++;
}

void call_arg(expr_t e) {
   call_arg_expr_v[call_c - 1][call_arg_c[call_c - 1]++] = e;
}

void func_arg(type_t t, id_t id, uint32_t row, uint32_t col) {
   lvar_t v = lvar_c++;
   lvar_t v2 = func_arg_first_v[func_c];
   lvaridx_t idx = 0;
   func_arg_last_v[func_c] = v;
   if (v2 == lvar_limit) {
      func_arg_first_v[func_c] = v;
   } else {
      while (1) {
         if (lvar_id_v[v2] == id) {
            printf("%s:%u:%u: Cannot declare '%.*s' because it was already declared at %u:%u\n", input_path, row, col, id_len_v[id], id_str_v[id], lvar_row_v[v2], lvar_col_v[v2]);
            exit(EXIT_FAILURE);
            return;
         }
         lvar_t v3 = lvar_next_v[v2];
         if (v3 == lvar_limit) {
            lvar_next_v[v2] = v;
            idx = lvar_idx_v[v2] + 1;
            break;
         }
         v2 = v3;
      }
   }
   lvar_id_v[v] = id;
   lvar_idx_v[v] = idx;
   lvar_type_v[v] = t;
   lvar_row_v[v] = row;
   lvar_col_v[v] = col;
   lvar_next_v[v] = lvar_limit;
   func_arg_c++;
}

void func_sig_undo() {
   decl_c--;
   id_decl_v[decl_id_v[decl_c]] = decl_nil;
   func_c--;
   lvar_c -= func_arg_limit_v[func_c];
   if (func_main == func_c) {
      func_main = func_limit;
   }

   // initialize the func_arg_first and func_arg_last of the next function
   func_arg_first_v[func_c] = lvar_limit;
   func_arg_last_v[func_c] = lvar_limit;
}

uint8_t type_size(type_t t) {
   switch (t) {
      case type_bool: return 1;
   }
   return 0;
}

void decl_gvar(type_t t, id_t id, uint32_t row, uint32_t col) {
   decl_t d = decl_c++;
   decl_id_v[d] = id;
   decl_type_v[d] = decltype_gvar;
   decl_row_v[d] = row;
   decl_col_v[d] = col;
   id_decl_v[id] = d;
   gvar_t g = gvar_c++;
   decl_idx_v[d] = g;
   gvar_decl_v[g] = d;
   gvar_type_v[g] = t;
   uint8_t size = type_size(t);
   // align to its size
   gvar_mem = (gvar_mem + (size - 1)) & (mem_max ^ (size - 1));
   gvar_mem_v[g] = gvar_mem;
   gvar_mem += size;
}

void func_sig(type_t t, id_t id, uint32_t row, uint32_t col) {
   decl_t d = id_decl_v[id];
   if (d != decl_nil) {
      printf("%s:%u:%u: Cannot declare '%.*s' because it was already declared at %u:%u\n", input_path, row, col, id_len_v[id], id_str_v[id], decl_row_v[d], decl_col_v[d]);
      exit(EXIT_FAILURE);
      return;
   }
   d = decl_c++;
   decl_id_v[d] = id;
   decl_type_v[d] = decltype_func;
   decl_row_v[d] = row;
   decl_col_v[d] = col;
   id_decl_v[id] = d;
   func_t f = func_c++;
   decl_idx_v[d] = f;
   func_decl_v[f] = d;
   func_type_v[f] = t;
   func_arg_limit_v[f] = func_arg_c;
   func_lvar_limit_v[f] = func_arg_c;
   func_arg_c = 0;
   func_bytecode_v[f] = bytecode_limit;
   func_scope_v[f] = scope_limit;
   func_now = f;
   if ((func_main == func_limit) && (id_len_v[id] == 4) && (memcmp(id_str_v[id], "main", 4) == 0)) {
      func_main = f;
   }

   // initialize the func_arg_first and func_arg_last of the next function
   func_arg_first_v[func_c] = lvar_limit;
   func_arg_last_v[func_c] = lvar_limit;
}

void func_body_begin(uint32_t row, uint32_t col) {
   func_t f = func_now;
   decl_t d = func_decl_v[f];
   if (func_scope_v[f] != scope_limit) {
      id_t id = decl_id_v[d];
      printf("%s:%u:%u: Function '%.*s' already has a body at %u:%u\n", input_path, row, col, id_len_v[id], id_str_v[id], decl_row_v[d], decl_col_v[d]);
      exit(EXIT_FAILURE);
   }
   decl_row_v[d] = row;
   decl_col_v[d] = col;
   scope_t scope = scope_c++;
   scope_parent_v[scope] = scope_limit;
   scope_lvar_first_v[scope] = func_arg_first_v[f];
   scope_lvar_last_v[scope] = func_arg_last_v[f];
   scope_stmt_first_v[scope] = stmt_limit;
   scope_stmt_last_v[scope] = stmt_limit;
   func_scope_v[f] = scope;
   scope_now = scope;
}

int32_t expr_call(id_t name, uint32_t row, uint32_t col) {
   call_c--;
   uint8_t arg_c = call_arg_c[call_c];
   expr_t e = expr_c++;
   expr_type_v[e] = exprtype_call;
   expr_row_v[e] = row;
   expr_col_v[e] = col;
   struct exprdata_call_t* data = &expr_data_v[e].call;
   data->func_id = name;
   data->arg_c = arg_c;
   for (uint8_t i = 0; i < arg_c; i++) {
      data->arg_v[i] = call_arg_expr_v[call_c][i];
   }
   return e;
}

expr_t expr_unary(unarytype_t type, expr_t a, uint32_t row, uint32_t col) {
   expr_t e = expr_c++;
   expr_type_v[e] = exprtype_unary;
   struct exprdata_unary_t* data = &expr_data_v[e].unary;
   data->type = type;
   data->expr = a;
   return e;
}

expr_t expr_math(mathtype_t type, expr_t a, expr_t b, uint32_t row, uint32_t col) {
   expr_t e = expr_c++;
   expr_type_v[e] = exprtype_math;
   struct exprdata_math_t* data = &expr_data_v[e].math;
   data->type = type;
   data->a = a;
   data->b = b;
   return e;
}

void expr_gvar_do(expr_t e, bool assign) {
   struct exprdata_gvar_t* data = &expr_data_v[e].gvar;
   id_t id = data->name;
   gvar_t v = gvar_limit;
   for (decl_t d = 0; d < decl_c; d++) {
      if (decl_id_v[d] == id) {
         if (decl_type_v[d] == decltype_gvar) {
            gvar_t g = decl_idx_v[d];
            switch (gvar_type_v[g]) {
               case type_bool: {
                  if (assign) {
                     bc_write(mem_set_8);
                     putmem(&bytecode_ptr, gvar_mem_v[g]);
                  } else {
                     bc_write(mem_push_8);
                     putmem(&bytecode_ptr, gvar_mem_v[g]);
                  }
                  break;
               }
            }
            return;
         }
         break;
      }
   }
   printf("%s:%u:%u: Variable '%.*s' was not found\n", input_path, expr_row_v[e], expr_col_v[e], id_len_v[id], id_str_v[id]);
   exit(EXIT_FAILURE);
}

void expr_write(expr_t e) {
   // printf("expr_write %u @ %u:%u\n", expr_type_v[e], expr_row_v[e], expr_col_v[e]);
   switch (expr_type_v[e]) {
      case exprtype_i32: {
         bc_write(push_32);
         putint(&bytecode_ptr, expr_data_v[e].i32.val);
         break;
      }
      case exprtype_call: {
         struct exprdata_call_t* data = &expr_data_v[e].call;
         id_t name = data->func_id;
         func_t f = func_limit;
         for (func_t i = 0; i < func_c; i++) {
            decl_t d = func_decl_v[i];
            if (decl_id_v[d] == name) {
               f = i;
               break;
            }
         }
         if (f == func_limit) {
            printf("%s:%u:%u: Function '%.*s' not found\n", input_path, expr_row_v[e], expr_col_v[e], id_len_v[name], id_str_v[name]);
            exit(EXIT_FAILURE);
         }
         uint8_t arg_c = data->arg_c;
         if (func_arg_limit_v[f] != arg_c) {
            printf("%s:%u:%u: Function '%.*s' requires %u arguments\n", input_path, expr_row_v[e], expr_col_v[e], id_len_v[name], id_str_v[name], func_arg_limit_v[f]);
            exit(EXIT_FAILURE);
         }
         for (uint8_t i = 0; i < arg_c; i++) {
            expr_write(data->arg_v[i]);
         }
         bc_write(push_call);
         putnum(&bytecode_ptr, f);
         break;
      }
      case exprtype_math: {
         struct exprdata_math_t* data = &expr_data_v[e].math;
         expr_write(data->a);
         expr_write(data->b);
         switch (data->type) {
            case mathtype_add: bc_write(add_i32); break;
            case mathtype_sub: bc_write(sub_i32); break;
            case mathtype_mul: bc_write(mul_i32); break;
            case mathtype_div: bc_write(div_i32); break;
         }
         break;
      }
      case exprtype_lvar: {
         bc_write(push_lvar_32);
         *(bytecode_ptr++) = lvar_idx_v[expr_data_v[e].lvar.lvar];
         break;
      }
      case exprtype_gvar: {
         expr_gvar_do(e, false);
         break;
      }
      case exprtype_str: {
         bc_write(push_addr);
         putmem(&bytecode_ptr, gvar_mem + str_mem_v[expr_data_v[e].str.str]);
         break;
      }
      case exprtype_unary: {
         struct exprdata_unary_t* data = &expr_data_v[e].unary;
         expr_write(data->expr);
         switch (data->type) {
            case unarytype_expoint: bc_write(not); break;
            default: printf("unarytype not yet implemented: %u\n", data->type);
         }
         break;
      }
      default: {
         printf("expr_write not yet implemented: %u\n", expr_type_v[e]);
      }
   }
}

expr_t expr_var(id_t id, uint32_t row, uint32_t col) {
   scope_t scope = scope_now;
   lvar_t v = lvar_limit;
   lvar_t v2 = scope_lvar_first_v[scope];
   if (v2 != lvar_limit) {
      while (1) {
         if (lvar_id_v[v2] == id) {
            v = v2;
            break;
         }
         lvar_t v3 = lvar_next_v[v2];
         again:
         if (v3 == lvar_limit) {
            scope = scope_parent_v[scope];
            if (scope == scope_limit) {
               break;
            }
            v3 = scope_lvar_first_v[scope];
            goto again;
         }
         v2 = v3;
      }
   }
   expr_t e = expr_c++;
   expr_row_v[e] = row;
   expr_col_v[e] = col;
   if (v != lvar_limit) {
      expr_type_v[e] = exprtype_lvar;
      expr_data_v[e].lvar.lvar = v;
   } else {
      expr_type_v[e] = exprtype_gvar;
      expr_data_v[e].gvar.name = id;
   }
   return e;
}

expr_t expr_str(uint32_t row, uint32_t col) {
   uint8_t* buf = string_buf;
   uint32_t len = string_len;
   str_t s = str_limit;
   for (str_t i = 0; i < str_c; i++) {
      if ((str_len_v[i] == string_len) && (memcmp(str_buf_v[i], buf, len) == 0)) {
         s = i;
         break;
      }
   }
   if (s == str_limit) {
      s = str_c++;
      uint8_t* buf2 = malloc(len);
      memcpy(buf2, buf, len);
      str_buf_v[s] = buf2;
      str_len_v[s] = len;
      str_mem_v[s] = str_mem;
      str_mem += len + 1; // + 1 for null terminator
   }
   expr_t e = expr_c++;
   expr_type_v[e] = exprtype_str;
   expr_row_v[e] = row;
   expr_col_v[e] = col;
   struct exprdata_str_t* data = &expr_data_v[e].str;
   data->str = s;
   return e;
}

expr_t expr_i32(int32_t i, uint32_t row, uint32_t col) {
   expr_t e = expr_c++;
   expr_type_v[e] = exprtype_i32;
   expr_row_v[e] = row;
   expr_col_v[e] = col;
   struct exprdata_i32_t* data = &expr_data_v[e].i32;
   data->val = i;
   return e;
}

stmt_t stmt_new(stmttype_t type) {
   stmt_t stmt = stmt_c++;
   stmt_t stmt2 = scope_stmt_last_v[scope_now];
   if (stmt2 == stmt_limit) {
      scope_stmt_first_v[scope_now] = stmt;
      scope_stmt_last_v[scope_now] = stmt;
   } else {
      stmt_next_v[stmt2] = stmt;
      scope_stmt_last_v[scope_now] = stmt;
   }
   stmt_type_v[stmt] = type;
   stmt_next_v[stmt] = stmt_limit;
   stmt_row_v[stmt] = row_now;
   stmt_col_v[stmt] = col_now;
   return stmt;
}

void scope_push(uint32_t row, uint32_t col) {
   stmt_t stmt = stmt_new(stmttype_scope);
   scope_t scope = scope_c++;
   // printf("scope push: %u, past is: %u @ %u:%u\n", scope, scope_now, row, col);
   stmt_data_v[stmt].scope.scope = scope;
   scope_parent_v[scope] = scope_now;
   scope_lvar_first_v[scope] = lvar_limit;
   scope_lvar_last_v[scope] = lvar_limit;
   scope_stmt_first_v[scope] = stmt_limit;
   scope_stmt_last_v[scope] = stmt_limit;
   scope_now = scope;
}

void scope_pop() {
   // printf("scope pop: %u -> %u\n", scope_now, scope_parent_v[scope_now]);
   scope_now = scope_parent_v[scope_now];
}

void stmt_assign(expr_t des, uint32_t row, uint32_t col, expr_t src) {
   stmt_t stmt = stmt_new(stmttype_assign);
   struct stmtdata_assign_t* data = &stmt_data_v[stmt].assign;
   data->des = des;
   data->src = src;
}

void stmt_expr(expr_t e) {
   stmt_t stmt = stmt_new(stmttype_expr);
   struct stmtdata_expr_t* data = &stmt_data_v[stmt].expr;
   data->expr = e;
}

void stmt_if_begin(expr_t e, bool is_elif) {
   stmt_t stmt = stmt_new(stmttype_if);
   struct stmtdata_if_t* data = &stmt_data_v[stmt].if_;
   data->expr = e;
   data->is_elif = is_elif;
}

void stmt_lvar(type_t t, id_t id, uint32_t row, uint32_t col, expr_t e) {
   lvar_t v = lvar_c++;
   scope_t scope = scope_now;
   lvar_t v2 = scope_lvar_first_v[scope];
   lvaridx_t idx = 0;
   if (v2 == lvar_limit) {
      scope_lvar_first_v[scope] = v;
   } else {
      while (1) {
         if (lvar_id_v[v2] == id) {
            printf("%s:%u:%u: Cannot declare %.*s because it was already declared at %u:%u\n", input_path, row, col, id_len_v[id], id_str_v[id], lvar_row_v[v2], lvar_col_v[v2]);
            exit(EXIT_FAILURE);
            return;
         }
         lvar_t v3 = lvar_next_v[v2];
         again:
         if (v3 == lvar_limit) {
            scope = scope_parent_v[scope];
            if (scope == scope_limit) {
               lvar_next_v[v2] = v;
               idx = lvar_idx_v[v2] + 1;
               break;
            }
            v3 = scope_lvar_first_v[scope];
            goto again;
         }
         v2 = v3;
      }
   }
   lvar_id_v[v] = id;
   lvar_idx_v[v] = idx;
   lvar_type_v[v] = t;
   lvar_row_v[v] = row;
   lvar_col_v[v] = col;
   lvar_next_v[v] = lvar_limit;

   stmt_t stmt = stmt_new(stmttype_lvar);
   stmt_data_v[stmt].lvar.lvar = v;
   stmt_data_v[stmt].lvar.expr = e;

   idx++;
   if (func_lvar_limit_v[func_now] < idx) {
      func_lvar_limit_v[func_now] = idx;
   }
}

void stmt_return_expr(expr_t e) {
   stmt_t stmt = stmt_new(stmttype_return);
   stmt_data_v[stmt].return_.expr = e;
}

void stmt_return() {
   stmt_t stmt = stmt_new(stmttype_return);
   stmt_data_v[stmt].return_.expr = expr_limit;
}

void scope_write(scope_t scope);

void jump_patch(uint8_t* ptr, uint8_t* target) {
   uint32_t offset = target - ptr;
   memcpy(ptr, &offset, sizeof(offset));
}

stmt_t stmt_write(stmt_t stmt) {
   // printf("%u stmt: %u (type %u) @ %u:%u\n", nest, stmt, stmt_type_v[stmt], stmt_row_v[stmt], stmt_col_v[stmt]);
   switch (stmt_type_v[stmt]) {
      case stmttype_lvar: {
         stmt_t e = stmt_data_v[stmt].lvar.expr;
         if (e != expr_limit) {
            expr_write(e);
            bc_write(lvar_set_32);
            *(bytecode_ptr++) = lvar_idx_v[stmt_data_v[stmt].lvar.lvar];
         }
         return stmt_next_v[stmt];
      }
      case stmttype_assign: {
         expr_write(stmt_data_v[stmt].assign.src);
         expr_t e = stmt_data_v[stmt].assign.des;
         switch (expr_type_v[e]) {
            case exprtype_lvar: {
               bc_write(lvar_set_32);
               *(bytecode_ptr++) = lvar_idx_v[expr_data_v[e].lvar.lvar];
               break;
            }
            case exprtype_gvar: {
               expr_gvar_do(e, true);
               break;
            }
         }
         return stmt_next_v[stmt];
      }
      case stmttype_return: {
         stmt_t e = stmt_data_v[stmt].return_.expr;
         if (e == expr_limit) {
            bc_write(return);
         } else {
            expr_write(e);
            bc_write(return_32);
         }
         return stmt_next_v[stmt];
      }
      case stmttype_expr: {
         expr_write(stmt_data_v[stmt].expr.expr);
         return stmt_next_v[stmt];
      }
      case stmttype_if: {
         stmt_t cur_if = stmt;
         stmt_t cur_scope = stmt_next_v[cur_if];
         if ((cur_scope == stmt_limit) || (stmt_type_v[cur_scope] != stmttype_scope)) {
            printf("%s:%u:%u: if statement body scope was not found\n", input_path, stmt_row_v[cur_if], stmt_col_v[cur_if]);
            exit(EXIT_FAILURE);
         }

         uint32_t cond_c = 1;
         bool has_else = false;
         stmt_t next = stmt_next_v[cur_scope];
         while (next != stmt_limit) {
            if ((stmt_type_v[next] == stmttype_if) && stmt_data_v[next].if_.is_elif) {
               stmt_t elif_scope = stmt_next_v[next];
               if ((elif_scope == stmt_limit) || (stmt_type_v[elif_scope] != stmttype_scope)) {
                  printf("%s:%u:%u: else-if statement body scope was not found\n", input_path, stmt_row_v[next], stmt_col_v[next]);
                  exit(EXIT_FAILURE);
               }
               cond_c++;
               next = stmt_next_v[elif_scope];
               continue;
            }
            if (stmt_type_v[next] == stmttype_scope) {
               has_else = true;
               next = stmt_next_v[next];
            }
            break;
         }

         uint8_t** end_jump_v = malloc(cond_c * sizeof(uint8_t*));
         if (end_jump_v == NULL) {
            printf("Out of memory while compiling if statement\n");
            exit(EXIT_FAILURE);
         }
         uint32_t end_jump_c = 0;

         cur_if = stmt;
         for (uint32_t i = 0; i < cond_c; i++) {
            cur_scope = stmt_next_v[cur_if];

            expr_write(stmt_data_v[cur_if].if_.expr);
            bc_write(if);
            uint8_t* if_false_jump = bytecode_ptr;
            bytecode_ptr += 4;

            scope_write(stmt_data_v[cur_scope].scope.scope);

            bool has_following_branch = (i + 1 < cond_c) || has_else;
            if (has_following_branch) {
               bc_write(jump);
               end_jump_v[end_jump_c++] = bytecode_ptr;
               bytecode_ptr += 4;
            }

            jump_patch(if_false_jump, bytecode_ptr);
            cur_if = stmt_next_v[cur_scope];
         }

         if (has_else) {
            scope_write(stmt_data_v[cur_if].scope.scope);
            cur_if = stmt_next_v[cur_if];
         }

         for (uint32_t i = 0; i < end_jump_c; i++) {
            jump_patch(end_jump_v[i], bytecode_ptr);
         }
         free(end_jump_v);
         return cur_if;
      }
      case stmttype_scope: {
         scope_write(stmt_data_v[stmt].scope.scope);
         return stmt_next_v[stmt];
      }
      default:
         printf("stmt_write %u not yet implemented\n", stmt_type_v[stmt]);
         exit(EXIT_FAILURE);
   }
   return stmt_next_v[stmt];
}

void scope_write(scope_t scope) {
   stmt_t child = scope_stmt_first_v[scope];
   while (child != stmt_limit) {
      child = stmt_write(child);
   }
}

#include "out/c_parse.h"
#include "out/c_token_name.h"
#include "out/c_parse.c"
#include "out/c_lex.c"
#include "runc-header.h"
#include "c_vm.c"

uint32_t row_next = 1;
uint32_t col_next = 1;

int c_lexer_scan2(struct c_lexer* lex, union c_token_data* tok) {
   tok->i32.row = row_next;
   tok->i32.col = col_next;
   while (1) {
      int t = c_lexer_scan(lex);
      if (1) {
         uint8_t* pos = lex->start;
         while (pos[0] != 0) {
            if (pos[0] == ' ') {
               tok->i32.col++;
            } else if (pos[0] == '\n') {
               tok->i32.row++;
               tok->i32.col = 1;
            } else {
               break;
            }
            pos++;
         }
      }
      if (1) {
         uint8_t* pos = lex->start;
         while (pos < lex->cursor) {
            if ((pos[0] & 128) == 0) {
               if (pos[0] == '\n') {
                  row_next++;
                  col_next = 1;
               } else {
                  col_next++;
               }
            }
            pos++;
         }
      }
      if (t != 0) { // Whitespace
         return t;
      }
   }
}

int main(int argc, char** argv) {
   if (argc < 2) {
      printf("Usage: %s [file.c]\n", argv[0]);
      exit(EXIT_FAILURE);
   }

   yyParser psr;
   if (1) {
      yyParser *yypParser = &psr;
      cParseCTX_STORE
      cParseInit(yypParser cParseCTX_PARAM);
   }

   bytecode_ptr = bytecode_v;

   int fd = open(input_path = argv[1], O_RDONLY);
   if (fd == -1) {
      printf("Cannot open file for reading: %s\n", input_path);
      exit(EXIT_FAILURE);
   }
   size_t size = lseek(fd, 0, SEEK_END);
   lseek(fd, 0, SEEK_SET);
   uint8_t* data = malloc(size + 1);
   string_mem = malloc(size);
   read(fd, data, size);
   close(fd);
   data[size] = 0;

   func_arg_first_v[0] = lvar_limit;
   func_arg_last_v[0] = lvar_limit;

   union c_token_data tok;
   struct c_lexer lex;
   c_lexer_init(&lex, data);

   #include "runc-builtins.c"

   for (;;) {
      int t = c_lexer_scan2(&lex, &tok);
      // printf("%u:%u\n", tok.i32.row, tok.i32.col);
      token_last = t;
      row_now = tok.i32.row;
      col_now = tok.i32.col;
      switch (t) {
         case C_TOKEN_ID: {
            tok.i32.id = c_lexer_id(lex.start, lex.cursor - lex.start);
            cParse(&psr, t, tok);
            break;
         }
         case C_TOKEN_INT: {
            tok.i32.id = atol(lex.start);
            cParse(&psr, t, tok);
            break;
         }
         case C_TOKEN_UINT: {
            tok.i32.id = atol(lex.start);
            cParse(&psr, t, tok);
            break;
         }
         default: {
            cParse(&psr, t, tok);
         }
      }
      if (t == C_TOKEN_END) { break; }
   }
   cParse(&psr, 0, tok);

   if (func_main == func_limit) {
      printf("There's no main() function.\n");
      exit(EXIT_FAILURE);
   }

   for (func_t f = 0; f < func_c; f++) {
      scope_t scope = func_scope_v[f];
      if (scope == scope_limit) {
         // built-in function
         continue;
      }
      func_bytecode_v[f] = bytecode_ptr - bytecode_v;
      *(bytecode_ptr++) = func_arg_limit_v[f]; // write the number of arguments
      *(bytecode_ptr++) = func_lvar_limit_v[f] - func_arg_limit_v[f]; // write the number of local variables (including the arguments)
      stmt_t stmt = scope_stmt_first_v[scope];
      while (stmt != stmt_limit) {
         stmt = stmt_write(stmt);
      }
   }

   static struct vm_locals vml;
   mem_t mem = gvar_mem;
   for (str_t s = 0; s < str_c; s++) {
      memcpy(vml.memory + mem, str_buf_v[s], str_len_v[s]);
      mem += str_len_v[s];
      vml.memory[mem++] = 0; // add null terminator
   }

   #include "runc-boot.c"

   func_run(func_main, &vml);

   #include "runc-exit.c"
   return 0;
}
