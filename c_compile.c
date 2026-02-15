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
#define typedef_t decl_t
#define typedef_limit 0x8000
#define expr_t uint32_t
#define expr_limit 0xffff
#define exprtype_t uint8_t
#define func_t declidx_t
#define type_t decl_t
#define star_t uint8_t // how many '*' in the type
#define type_void 0
#define type_u16 1
#define type_u32 2
#define type_i32 3
#define type_u8 4
#define type_char 5
#define exprtype_i32 0
#define exprtype_call 1
#define exprtype_math 2
#define exprtype_lvar 3
#define exprtype_gvar 4
#define exprtype_str 5
#define exprtype_unary 6
#define exprtype_cast 7
#define exprtype_compare 8
#define exprtype_bools 9
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
#define stmttype_else 6
#define stmttype_for 7
#define stmttype_break 8
#define stmttype_continue 9
#define stmttype_while 10
#define stmttype_do 11
#define stmttype_do_end 12
#define stmttype_label 13
#define stmttype_goto 14
#define mathtype_t uint8_t
#define mathtype_add 0
#define mathtype_sub 1
#define mathtype_mul 2
#define mathtype_div 3
#define boolstype_t uint8_t
#define boolstype_and 0
#define boolstype_or 1
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
#define unarytype_postinc 0
#define unarytype_preinc 1
#define unarytype_expoint 2
#define unarytype_postdec 3
#define unarytype_predec 4
#define unaryop_t uint8_t
#define unaryop_postinc 0
#define unaryop_preinc 1
#define unaryop_postdec 0
#define unaryop_predec 1
#define comparetype_t uint8_t
#define comparetype_lt 0
#define comparetype_gt 1
#define comparetype_eq 2
#define comparetype_lteq 3
#define comparetype_gteq 4
#define comparetype_noteq 5

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
#define bc_lt_i32 16
#define bc_gt_i32 17
#define bc_eq_i32 18
#define bc_lteq_i32 19
#define bc_gteq_i32 20
#define bc_noteq_i32 21
#define bc_unaryop_lvar_32_postinc 22
#define bc_unaryop_lvar_32_preinc 23
#define bc_unaryop_lvar_32_postdec 24
#define bc_unaryop_lvar_32_predec 25
#define bc_mem_postinc_8 26
#define bc_mem_preinc_8 27
#define bc_mem_postdec_8 28
#define bc_mem_predec_8 29
#define bc_pop_32 30
#define bc_and 31
#define bc_or 32

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
   func_t func;
   expr_t arg_v[call_arg_limit];
   uint8_t arg_c;
};

struct exprdata_math_t {
   mathtype_t type;
   expr_t a;
   expr_t b;
};

struct exprdata_bools_t {
   boolstype_t type;
   expr_t a;
   expr_t b;
};

struct exprdata_compare_t {
   comparetype_t type;
   expr_t a;
   expr_t b;
};

struct exprdata_cast_t {
   type_t type;
   expr_t expr;
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
   struct exprdata_bools_t bools;
   struct exprdata_compare_t compare;
   struct exprdata_cast_t cast;
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

struct stmtdata_label_t {
   id_t id;
};

struct stmtdata_goto_t {
   id_t id;
};

struct stmtdata_for_t {
   expr_t expr;
   scope_t scope;
};

struct stmtdata_while_t {
   expr_t expr;
   scope_t scope;
};

struct stmtdata_do_end_t {
   expr_t expr;
};

union stmtdata_t {
   struct stmtdata_lvar_t lvar;
   struct stmtdata_return_t return_;
   struct stmtdata_assign_t assign;
   struct stmtdata_scope_t scope;
   struct stmtdata_expr_t expr;
   struct stmtdata_if_t if_;
   struct stmtdata_label_t label;
   struct stmtdata_goto_t goto_;
   struct stmtdata_for_t for_;
   struct stmtdata_while_t while_;
   struct stmtdata_do_end_t do_end;
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

type_t typedef_type_v[typedef_limit];
id_t typedef_id_v[typedef_limit];
typedef_t typedef_c;

decl_t func_decl_v[func_limit];
type_t func_type_v[func_limit];
star_t func_star_v[func_limit];
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
expr_t scope_for_continue_expr_v[scope_limit][call_arg_limit];
uint8_t scope_for_continue_c[scope_limit];
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
   // printf("%.*s %u\n", len, str, len);
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
      case type_u8: return 1;
   }
   return 0;
}

void decl_typedef(type_t t, id_t id, uint32_t row, uint32_t col) {
   typedef_t td = typedef_c++;
   typedef_type_v[td] = t;
   typedef_id_v[td] = id;
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
   scope_for_continue_c[scope] = 0;
   func_scope_v[f] = scope;
   scope_now = scope;
}

int32_t expr_cast(type_t t, expr_t a, uint32_t row, uint32_t col) {
   expr_t e = expr_c++;
   expr_type_v[e] = exprtype_cast;
   expr_row_v[e] = row;
   expr_col_v[e] = col;
   struct exprdata_cast_t* data = &expr_data_v[e].cast;
   data->type = t;
   data->expr = a;
   return e;
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

expr_t expr_compare(comparetype_t type, expr_t a, expr_t b, uint32_t row, uint32_t col) {
   expr_t e = expr_c++;
   expr_type_v[e] = exprtype_compare;
   struct exprdata_compare_t* data = &expr_data_v[e].compare;
   data->type = type;
   data->a = a;
   data->b = b;
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

expr_t expr_bools(boolstype_t type, expr_t a, expr_t b, uint32_t row, uint32_t col) {
   expr_t e = expr_c++;
   expr_type_v[e] = exprtype_bools;
   struct exprdata_bools_t* data = &expr_data_v[e].bools;
   data->type = type;
   data->a = a;
   data->b = b;
   return e;
}

gvar_t gvar_get(expr_t e) {
   struct exprdata_gvar_t* data = &expr_data_v[e].gvar;
   id_t id = data->name;
   gvar_t v = gvar_limit;
   for (decl_t d = 0; d < decl_c; d++) {
      if (decl_id_v[d] == id) {
         if (decl_type_v[d] == decltype_gvar) {
            return decl_idx_v[d];
         }
         break;
      }
   }
   printf("%s:%u:%u: Variable '%.*s' was not found\n", input_path, expr_row_v[e], expr_col_v[e], id_len_v[id], id_str_v[id]);
   exit(EXIT_FAILURE);
}

void expr_unaryop(expr_t e, unaryop_t op) {
   exprtype_t et = expr_type_v[e];
   switch (et) {
      case exprtype_lvar: {
         bc_write(unaryop_lvar_32_postinc + op);
         *(bytecode_ptr++) = lvar_idx_v[expr_data_v[e].lvar.lvar];
         break;
      }
      case exprtype_gvar: {
         gvar_t g = gvar_get(e);
         type_t t = gvar_type_v[g];
         switch (t) {
            case type_u8: {
               bc_write(mem_postinc_8 + op);
               putmem(&bytecode_ptr, gvar_mem_v[g]);
               break;
            }
         }
         break;
      }
      default:
         printf("expr_unaryop on an expr type %u is not yet implemented\n", et);
         exit(EXIT_FAILURE);
   }
}

void expr_gvar_do(expr_t e, bool assign) {
   gvar_t g = gvar_get(e);
   type_t t = gvar_type_v[g];
   switch (t) {
      case type_u8: {
         if (assign) {
            bc_write(mem_set_8);
            putmem(&bytecode_ptr, gvar_mem_v[g]);
         } else {
            bc_write(mem_push_8);
            putmem(&bytecode_ptr, gvar_mem_v[g]);
         }
         break;
      }
      default:
         printf("expr_gvar_do on type %u is not yet implemented\n", t);
         exit(EXIT_FAILURE);
   }
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
         data->func = f;
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
      case exprtype_cast: {
         struct exprdata_cast_t* data = &expr_data_v[e].cast;
         expr_write(data->expr);
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
      case exprtype_bools: {
         struct exprdata_bools_t* data = &expr_data_v[e].bools;
         expr_write(data->a);
         expr_write(data->b);
         switch (data->type) {
            case boolstype_and: bc_write(and); break;
            case boolstype_or: bc_write(or); break;
         }
         break;
      }
      case exprtype_compare: {
         struct exprdata_compare_t* data = &expr_data_v[e].compare;
         expr_write(data->a);
         expr_write(data->b);
         switch (data->type) {
            case comparetype_lt: bc_write(lt_i32); break;
            case comparetype_gt: bc_write(gt_i32); break;
            case comparetype_eq: bc_write(eq_i32); break;
            case comparetype_lteq: bc_write(lteq_i32); break;
            case comparetype_gteq: bc_write(gteq_i32); break;
            case comparetype_noteq: bc_write(noteq_i32); break;
            default:
               printf("expr_write on a comparetype %u is not yet implemented\n", data->type);
               exit(EXIT_FAILURE);
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
         unarytype_t type = data->type;
         switch (type) {
            case unarytype_postinc:
            case unarytype_preinc:
            case unarytype_postdec:
            case unarytype_predec:
               expr_unaryop(data->expr, type);
               break;
            case unarytype_expoint:
               expr_write(data->expr);
               bc_write(not);
               break;
            default:
               printf("unarytype not yet implemented: %u\n", data->type);
               exit(EXIT_FAILURE);
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
   while (scope != scope_limit) {
      lvar_t v2 = scope_lvar_first_v[scope];
      while (v2 != lvar_limit) {
         if (lvar_id_v[v2] == id) {
            v = v2;
            goto done;
         }
         v2 = lvar_next_v[v2];
      }
      scope = scope_parent_v[scope];
   }
done:
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
   // printf("stmt %u @ %u:%u\n", type, row_now, col_now);
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
   scope_for_continue_c[scope] = 0;
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

void stmt_do_begin() {
   stmt_new(stmttype_do);
}

void stmt_do_end(expr_t e) {
   stmt_t stmt = stmt_new(stmttype_do_end);
   stmt_data_v[stmt].do_end.expr = e;
}

void stmt_while(expr_t e) {
   stmt_t stmt = stmt_new(stmttype_while);
   struct stmtdata_while_t* data = &stmt_data_v[stmt].while_;
   data->expr = e;
   data->scope = scope_c; // while_begin pushes this scope immediately after
}

void stmt_label(id_t id) {
   stmt_t stmt = stmt_new(stmttype_label);
   stmt_data_v[stmt].label.id = id;
}

void stmt_goto(id_t id) {
   stmt_t stmt = stmt_new(stmttype_goto);
   stmt_data_v[stmt].goto_.id = id;
}

void stmt_for(expr_t e) {
   stmt_t stmt = stmt_new(stmttype_for);
   struct stmtdata_for_t* data = &stmt_data_v[stmt].for_;
   data->expr = e;
   data->scope = scope_now;
}

void stmt_for_on_continue(expr_t e) {
   scope_t scope = scope_now;
   uint8_t c = scope_for_continue_c[scope];
   if (c >= call_arg_limit) {
      printf("%s:%u:%u: for loop update supports up to %u expressions\n", input_path, row_now, col_now, call_arg_limit);
      exit(EXIT_FAILURE);
   }
   scope_for_continue_expr_v[scope][c] = e;
   scope_for_continue_c[scope] = c + 1;
}

void stmt_continue() {
   stmt_new(stmttype_continue);
}

void stmt_break() {
   stmt_new(stmttype_break);
}

void stmt_if_begin(expr_t e, bool is_elif) {
   stmt_t stmt = stmt_new(stmttype_if);
   struct stmtdata_if_t* data = &stmt_data_v[stmt].if_;
   data->expr = e;
   data->is_elif = is_elif;
}

void stmt_else_begin() {
   stmt_new(stmttype_else);
}

void stmt_lvar(type_t t, id_t id, uint32_t row, uint32_t col, expr_t e) {
   lvar_t v = lvar_c++;
   scope_t scope = scope_now;
   while (scope != scope_limit) {
      lvar_t v2 = scope_lvar_first_v[scope];
      while (v2 != lvar_limit) {
         if (lvar_id_v[v2] == id) {
            printf("%s:%u:%u: Cannot declare %.*s because it was already declared at %u:%u\n", input_path, row, col, id_len_v[id], id_str_v[id], lvar_row_v[v2], lvar_col_v[v2]);
            exit(EXIT_FAILURE);
            return;
         }
         v2 = lvar_next_v[v2];
      }
      scope = scope_parent_v[scope];
   }
   lvaridx_t idx = func_lvar_limit_v[func_now];
   if (scope_lvar_first_v[scope_now] == lvar_limit) {
      scope_lvar_first_v[scope_now] = v;
      scope_lvar_last_v[scope_now] = v;
   } else {
      lvar_t last = scope_lvar_last_v[scope_now];
      lvar_next_v[last] = v;
      scope_lvar_last_v[scope_now] = v;
   }
   lvar_id_v[v] = id;
   lvar_idx_v[v] = idx;
   lvar_type_v[v] = t;
   lvar_row_v[v] = row;
   lvar_col_v[v] = col;
   lvar_next_v[v] = lvar_limit;

   stmt_t stmt = stmt_new(stmttype_lvar);
   struct stmtdata_lvar_t* data = &stmt_data_v[stmt].lvar;
   data->lvar = v;
   data->expr = e;

   func_lvar_limit_v[func_now] = idx + 1;
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
   int32_t offset = target - ptr;
   memcpy(ptr, &offset, sizeof(offset));
}

struct jump_patch_list_t {
   uint8_t** ptr_v;
   uint32_t ptr_c;
   uint32_t ptr_cap;
};

struct loop_write_ctx_t {
   struct jump_patch_list_t break_jumps;
   struct jump_patch_list_t continue_jumps;
};

struct loop_write_ctx_t loop_write_ctx_v[nest_limit];
nest_t loop_write_ctx_c;

struct jump_patch_list_t goto_jump_v[id_limit];
uint8_t goto_touched_bits[(id_limit + 7) >> 3];
id_t goto_touched_v[id_limit];
uint32_t goto_touched_c;
uint8_t* label_target_v[id_limit];
bool label_defined_v[id_limit];
uint32_t label_row_v[id_limit];
uint32_t label_col_v[id_limit];
uint32_t goto_row_v[id_limit];
uint32_t goto_col_v[id_limit];

void jump_patch_list_add(struct jump_patch_list_t* list, uint8_t* ptr) {
   if (list->ptr_c == list->ptr_cap) {
      uint32_t cap = list->ptr_cap == 0 ? 8 : list->ptr_cap * 2;
      uint8_t** ptr_v = realloc(list->ptr_v, cap * sizeof(uint8_t*));
      if (ptr_v == NULL) {
         printf("Out of memory while compiling loop jumps\n");
         exit(EXIT_FAILURE);
      }
      list->ptr_v = ptr_v;
      list->ptr_cap = cap;
   }
   list->ptr_v[list->ptr_c++] = ptr;
}

void jump_patch_list_apply(struct jump_patch_list_t* list, uint8_t* target) {
   for (uint32_t i = 0; i < list->ptr_c; i++) {
      jump_patch(list->ptr_v[i], target);
   }
}

void jump_patch_list_free(struct jump_patch_list_t* list) {
   free(list->ptr_v);
   list->ptr_v = NULL;
   list->ptr_c = 0;
   list->ptr_cap = 0;
}

void goto_ctx_begin() {
   memset(goto_touched_bits, 0, sizeof(goto_touched_bits));
   goto_touched_c = 0;
}

void goto_ctx_touch(id_t id) {
   if (BIT8_NOT(goto_touched_bits, id)) {
      BIT8_SET(goto_touched_bits, id);
      goto_touched_v[goto_touched_c++] = id;
      label_target_v[id] = NULL;
      label_defined_v[id] = false;
      label_row_v[id] = 0;
      label_col_v[id] = 0;
      goto_row_v[id] = 0;
      goto_col_v[id] = 0;
      goto_jump_v[id].ptr_v = NULL;
      goto_jump_v[id].ptr_c = 0;
      goto_jump_v[id].ptr_cap = 0;
   }
}

void goto_ctx_label_define(id_t id, stmt_t stmt) {
   goto_ctx_touch(id);
   if (label_defined_v[id]) {
      printf("%s:%u:%u: Duplicate label '%.*s' first declared at %u:%u\n", input_path, stmt_row_v[stmt], stmt_col_v[stmt], id_len_v[id], id_str_v[id], label_row_v[id], label_col_v[id]);
      exit(EXIT_FAILURE);
   }
   label_defined_v[id] = true;
   label_target_v[id] = bytecode_ptr;
   label_row_v[id] = stmt_row_v[stmt];
   label_col_v[id] = stmt_col_v[stmt];
   jump_patch_list_apply(&goto_jump_v[id], label_target_v[id]);
}

void goto_ctx_goto_write(id_t id, stmt_t stmt, uint8_t* patch_ptr) {
   goto_ctx_touch(id);
   if (label_defined_v[id]) {
      jump_patch(patch_ptr, label_target_v[id]);
      return;
   }
   if (goto_row_v[id] == 0) {
      goto_row_v[id] = stmt_row_v[stmt];
      goto_col_v[id] = stmt_col_v[stmt];
   }
   jump_patch_list_add(&goto_jump_v[id], patch_ptr);
}

void goto_ctx_end() {
   for (uint32_t i = 0; i < goto_touched_c; i++) {
      id_t id = goto_touched_v[i];
      if (!label_defined_v[id] && (goto_jump_v[id].ptr_c != 0)) {
         printf("%s:%u:%u: goto target label '%.*s' was not found\n", input_path, goto_row_v[id], goto_col_v[id], id_len_v[id], id_str_v[id]);
         exit(EXIT_FAILURE);
      }
      jump_patch_list_free(&goto_jump_v[id]);
   }
}

void loop_write_push() {
   if (loop_write_ctx_c >= nest_limit) {
      printf("Too many nested loops (limit is %u)\n", nest_limit);
      exit(EXIT_FAILURE);
   }
   struct loop_write_ctx_t* loop = &loop_write_ctx_v[loop_write_ctx_c++];
   loop->break_jumps.ptr_v = NULL;
   loop->break_jumps.ptr_c = 0;
   loop->break_jumps.ptr_cap = 0;
   loop->continue_jumps.ptr_v = NULL;
   loop->continue_jumps.ptr_c = 0;
   loop->continue_jumps.ptr_cap = 0;
}

struct loop_write_ctx_t* loop_write_top(stmt_t stmt, const char* keyword) {
   if (loop_write_ctx_c == 0) {
      printf("%s:%u:%u: Cannot use %s outside a loop\n", input_path, stmt_row_v[stmt], stmt_col_v[stmt], keyword);
      exit(EXIT_FAILURE);
   }
   return &loop_write_ctx_v[loop_write_ctx_c - 1];
}

void loop_write_pop() {
   struct loop_write_ctx_t* loop = &loop_write_ctx_v[--loop_write_ctx_c];
   jump_patch_list_free(&loop->break_jumps);
   jump_patch_list_free(&loop->continue_jumps);
}

void expr_write_stmt(expr_t e, const char* context) {
   expr_write(e);
   if (expr_type_v[e] == exprtype_call) {
      struct exprdata_call_t* data = &expr_data_v[e].call;
      func_t f = data->func;
      if ((func_type_v[f] != type_void) || (func_star_v[f] != 0)) {
         printf("%s:%u:%u: %s call expression must return void\n", input_path, expr_row_v[e], expr_col_v[e], context);
         exit(EXIT_FAILURE);
      }
   } else {
      bc_write(pop_32);
   }
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
         expr_t e = stmt_data_v[stmt].expr.expr;
         expr_write_stmt(e, "statement");
         return stmt_next_v[stmt];
      }
      case stmttype_label: {
         goto_ctx_label_define(stmt_data_v[stmt].label.id, stmt);
         return stmt_next_v[stmt];
      }
      case stmttype_goto: {
         bc_write(jump);
         uint8_t* goto_jump = bytecode_ptr;
         bytecode_ptr += 4;
         goto_ctx_goto_write(stmt_data_v[stmt].goto_.id, stmt, goto_jump);
         return stmt_next_v[stmt];
      }
      case stmttype_for: {
         struct stmtdata_for_t* data = &stmt_data_v[stmt].for_;
         stmt_t body_stmt = stmt_next_v[stmt];
         if ((body_stmt == stmt_limit) || (stmt_type_v[body_stmt] != stmttype_scope)) {
            printf("%s:%u:%u: for statement body scope was not found\n", input_path, stmt_row_v[stmt], stmt_col_v[stmt]);
            exit(EXIT_FAILURE);
         }

         uint8_t* loop_begin = bytecode_ptr;
         uint8_t* cond_false_jump = NULL;
         if (data->expr != expr_limit) {
            expr_write(data->expr);
            bc_write(if);
            cond_false_jump = bytecode_ptr;
            bytecode_ptr += 4;
         }

         loop_write_push();
         struct loop_write_ctx_t* loop = &loop_write_ctx_v[loop_write_ctx_c - 1];

         scope_write(stmt_data_v[body_stmt].scope.scope);

         uint8_t* continue_target = bytecode_ptr;
         jump_patch_list_apply(&loop->continue_jumps, continue_target);

         uint8_t continue_expr_c = scope_for_continue_c[data->scope];
         for (uint8_t i = 0; i < continue_expr_c; i++) {
            expr_write_stmt(scope_for_continue_expr_v[data->scope][i], "for-loop update");
         }

         bc_write(jump);
         uint8_t* loop_back_jump = bytecode_ptr;
         bytecode_ptr += 4;
         jump_patch(loop_back_jump, loop_begin);

         uint8_t* loop_end = bytecode_ptr;
         if (cond_false_jump != NULL) {
            jump_patch(cond_false_jump, loop_end);
         }
         jump_patch_list_apply(&loop->break_jumps, loop_end);
         loop_write_pop();
         return stmt_next_v[body_stmt];
      }
      case stmttype_while: {
         struct stmtdata_while_t* data = &stmt_data_v[stmt].while_;
         stmt_t loop_scope_stmt = stmt_next_v[stmt];
         if ((loop_scope_stmt == stmt_limit) || (stmt_type_v[loop_scope_stmt] != stmttype_scope)) {
            printf("%s:%u:%u: while statement scope was not found\n", input_path, stmt_row_v[stmt], stmt_col_v[stmt]);
            exit(EXIT_FAILURE);
         }
         scope_t loop_scope = stmt_data_v[loop_scope_stmt].scope.scope;
         if (data->scope != loop_scope) {
            printf("%s:%u:%u: internal error while resolving while-loop scope\n", input_path, stmt_row_v[stmt], stmt_col_v[stmt]);
            exit(EXIT_FAILURE);
         }
         stmt_t body_stmt = scope_stmt_first_v[loop_scope];
         if ((body_stmt == stmt_limit) || (stmt_type_v[body_stmt] != stmttype_scope)) {
            printf("%s:%u:%u: while statement body scope was not found\n", input_path, stmt_row_v[stmt], stmt_col_v[stmt]);
            exit(EXIT_FAILURE);
         }

         uint8_t* loop_begin = bytecode_ptr;
         expr_write(data->expr);
         bc_write(if);
         uint8_t* cond_false_jump = bytecode_ptr;
         bytecode_ptr += 4;

         loop_write_push();
         struct loop_write_ctx_t* loop = &loop_write_ctx_v[loop_write_ctx_c - 1];

         scope_write(stmt_data_v[body_stmt].scope.scope);

         uint8_t* continue_target = bytecode_ptr;
         jump_patch_list_apply(&loop->continue_jumps, continue_target);

         bc_write(jump);
         uint8_t* loop_back_jump = bytecode_ptr;
         bytecode_ptr += 4;
         jump_patch(loop_back_jump, loop_begin);

         uint8_t* loop_end = bytecode_ptr;
         jump_patch(cond_false_jump, loop_end);
         jump_patch_list_apply(&loop->break_jumps, loop_end);
         loop_write_pop();
         return stmt_next_v[loop_scope_stmt];
      }
      case stmttype_do: {
         stmt_t body_stmt = stmt_next_v[stmt];
         if ((body_stmt == stmt_limit) || (stmt_type_v[body_stmt] != stmttype_scope)) {
            printf("%s:%u:%u: do statement body scope was not found\n", input_path, stmt_row_v[stmt], stmt_col_v[stmt]);
            exit(EXIT_FAILURE);
         }
         stmt_t end_stmt = stmt_next_v[body_stmt];
         if ((end_stmt == stmt_limit) || (stmt_type_v[end_stmt] != stmttype_do_end)) {
            printf("%s:%u:%u: do statement end condition was not found\n", input_path, stmt_row_v[stmt], stmt_col_v[stmt]);
            exit(EXIT_FAILURE);
         }

         uint8_t* loop_begin = bytecode_ptr;

         loop_write_push();
         struct loop_write_ctx_t* loop = &loop_write_ctx_v[loop_write_ctx_c - 1];

         scope_write(stmt_data_v[body_stmt].scope.scope);

         uint8_t* continue_target = bytecode_ptr;
         jump_patch_list_apply(&loop->continue_jumps, continue_target);

         expr_write(stmt_data_v[end_stmt].do_end.expr);
         bc_write(if);
         uint8_t* cond_false_jump = bytecode_ptr;
         bytecode_ptr += 4;

         bc_write(jump);
         uint8_t* loop_back_jump = bytecode_ptr;
         bytecode_ptr += 4;
         jump_patch(loop_back_jump, loop_begin);

         uint8_t* loop_end = bytecode_ptr;
         jump_patch(cond_false_jump, loop_end);
         jump_patch_list_apply(&loop->break_jumps, loop_end);
         loop_write_pop();
         return stmt_next_v[end_stmt];
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
         stmt_t else_stmt = stmt_limit;
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
            if (stmt_type_v[next] == stmttype_else) {
               stmt_t maybe_else_scope = stmt_next_v[next];
               if ((maybe_else_scope == stmt_limit) || (stmt_type_v[maybe_else_scope] != stmttype_scope)) {
                  printf("%s:%u:%u: else statement body scope was not found\n", input_path, stmt_row_v[next], stmt_col_v[next]);
                  exit(EXIT_FAILURE);
               }
               has_else = true;
               else_stmt = next;
               next = stmt_next_v[maybe_else_scope];
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
            if (cur_if != else_stmt) {
               printf("%s:%u:%u: internal error while compiling else statement\n", input_path, stmt_row_v[cur_if], stmt_col_v[cur_if]);
               exit(EXIT_FAILURE);
            }
            stmt_t else_scope = stmt_next_v[cur_if];
            scope_write(stmt_data_v[else_scope].scope.scope);
            cur_if = stmt_next_v[else_scope];
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
      case stmttype_else: {
         printf("%s:%u:%u: internal error, unexpected else statement marker\n", input_path, stmt_row_v[stmt], stmt_col_v[stmt]);
         exit(EXIT_FAILURE);
      }
      case stmttype_do_end: {
         printf("%s:%u:%u: internal error, unexpected do-end statement marker\n", input_path, stmt_row_v[stmt], stmt_col_v[stmt]);
         exit(EXIT_FAILURE);
      }
      case stmttype_break: {
         struct loop_write_ctx_t* loop = loop_write_top(stmt, "break");
         bc_write(jump);
         jump_patch_list_add(&loop->break_jumps, bytecode_ptr);
         bytecode_ptr += 4;
         return stmt_next_v[stmt];
      }
      case stmttype_continue: {
         struct loop_write_ctx_t* loop = loop_write_top(stmt, "continue");
         bc_write(jump);
         jump_patch_list_add(&loop->continue_jumps, bytecode_ptr);
         bytecode_ptr += 4;
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

#include "c_preprocess.c"

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
   uint8_t* data_raw = malloc(size + 1);
   read(fd, data_raw, size);
   close(fd);
   data_raw[size] = 0;

   uint8_t* data = preprocess(data_raw, size);
   free(data_raw);
   size = strlen((char*)data);
   string_mem = malloc(size + 1);

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
            for (typedef_t td = 0; td < typedef_c; td++) {
               if (typedef_id_v[td] == tok.i32.id) {
                  t = C_TOKEN_TYPE;
                  tok.i32.id = typedef_type_v[td];
                  break;
               }
            }
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
      goto_ctx_begin();
      stmt_t stmt = scope_stmt_first_v[scope];
      while (stmt != stmt_limit) {
         stmt = stmt_write(stmt);
      }
      goto_ctx_end();
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
