%include {
char* string_mem;
// void stdout_then_print_error(void*, int);
}
%name cParse
%token_prefix C_TOKEN_
%stack_size 0 // let it grow

%token_type {union c_token_data}

// %left PLUS MINUS. 
%syntax_error{
   int n = YYNTOKEN;
   bool first = true;
   uint8_t first_expect = 0;
   uint8_t second_expect = 0;
   char errbuf[1024];
   int ibuf;
   for (int i = 0; i < n; ++i) {
      int a = yy_find_shift_action((YYCODETYPE)i, yypParser->yytos->stateno);
      if (a != YY_ERROR_ACTION) {
         if (first) {
            first = false;
            first_expect = i;
            if (token_last == C_TOKEN_END) {
               if (string_mem[0] == 0) {
                  ibuf = sprintf(errbuf, "%s:%u:%u: syntax error, got #end-of-file but expected tokens are: #%s", input_path, row_now, col_now, token_name(i));
               } else {
                  ibuf = sprintf(errbuf, "%s:%u:%u: syntax error, got token '%c' but expected tokens are: #%s", input_path, row_now, col_now, string_mem[0], token_name(i));
               }
            } else {
               ibuf = sprintf(errbuf, "%s:%u:%u: syntax error, got token #%s but expected tokens are: #%s", input_path, row_now, col_now, token_name(token_last), token_name(i));
            }
         } else {
            if (second_expect == 0) {
               second_expect = i;
            }
            ibuf += sprintf(errbuf + ibuf, ", #%s", token_name(i));
         }
      }
   }
   printf("%.*s\n", ibuf, errbuf);
   exit(EXIT_FAILURE);
   return;
}

c ::= decls END.
c ::= END.

decls ::= decl.
decls ::= decls decl.

decl ::= decl_func.
decl ::= decl_gvar.
decl ::= PREPROCESS.

decl_gvar ::= type(t) id(name) SEMICOLON.
{ decl_gvar(t.i32.id, name.i32.id, name.i32.row, name.i32.col); }

func_args_or_empty ::= .
func_args_or_empty ::= func_args.

func_args ::= type(t) id(name).
{ func_arg(t.i32.id, name.i32.id, name.i32.row, name.i32.col); }
func_args ::= func_args COMMA type(t) id(name).
{ func_arg(t.i32.id, name.i32.id, name.i32.row, name.i32.col); }

decl_func_sig ::= type(t) id(name) OPEN_PAREN func_args_or_empty CLOSE_PAREN.
{ func_sig(t.i32.id, name.i32.id, name.i32.row, name.i32.col); }

decl_func ::= decl_func_sig SEMICOLON.
{ func_sig_undo(); }
decl_func ::= decl_func_sig decl_func_body_begin stmts_or_empty .
decl_func_body_begin ::= OPEN_CURLY(tok).
{ func_body_begin(tok.i32.row, tok.i32.col); }

stmts ::= stmt.
stmts ::= stmts stmt.

stmts_or_empty ::= CLOSE_CURLY.
stmts_or_empty ::= stmts CLOSE_CURLY.

stmt ::= stmt_lvar.
stmt ::= stmt_return.
stmt ::= stmt_assign.
stmt ::= stmt_if.
stmt ::= stmt_if ELSE scope.
stmt ::= stmt_if else_ifs.
stmt ::= stmt_if else_ifs ELSE scope.

else_if ::= ELSE_IF OPEN_PAREN stmt_elif_begin scope.

stmt_elif_begin ::= expr(e) CLOSE_PAREN.
{ stmt_if_begin(e.i32.id, true); }

else_ifs ::= else_if.
else_ifs ::= else_ifs else_if.

stmt ::= call(e) SEMICOLON.
{ stmt_expr(e.i32.id); }

scope_begin ::= OPEN_CURLY(e).
{ scope_push(e.i32.row, e.i32.col); }
scope ::= scope_begin stmts_or_empty.
{ scope_pop(); }

stmt_if ::= IF OPEN_PAREN stmt_if_begin scope.

stmt_if_begin ::= expr(e) CLOSE_PAREN.
{ stmt_if_begin(e.i32.id, false); }

stmt_assign ::= lvar(des) EQUAL expr(src) SEMICOLON.
{ stmt_assign(des.i32.id, des.i32.row, des.i32.col, src.i32.id); }

stmt_lvar ::= type(t) id(name) SEMICOLON.
{ stmt_lvar(t.i32.id, name.i32.id, name.i32.row, name.i32.col, expr_limit); }
stmt_lvar ::= type(t) id(name) EQUAL expr(e) SEMICOLON.
{ stmt_lvar(t.i32.id, name.i32.id, name.i32.row, name.i32.col, e.i32.id); }
stmt_return ::= RETURN expr(e) SEMICOLON.
{ stmt_return_expr(e.i32.id); }
stmt_return ::= RETURN SEMICOLON.
{ stmt_return(); }

cast(out) ::= OPEN_PAREN type(t) CLOSE_PAREN value(e).
{ out.i32.id = expr_cast(t.i32.id, e.i32.id, e.i32.row, e.i32.col); }

expr ::= cast.
expr ::= value.
expr ::= math.
expr(out) ::= EXPOINT value(e).
{ out.i32.id = expr_unary(unarytype_expoint, e.i32.id, e.i32.row, e.i32.col); }

value(out) ::= OPEN_PAREN expr(in) CLOSE_PAREN.
{ out = in; }

value ::= num_int.
value ::= call.
value ::= lvar.
value(out) ::= STRING(e).
{ out.i32.id = expr_str(e.i32.row, e.i32.col); }

lvar(out) ::= id(name).
{ out.i32.id = expr_var(name.i32.id, name.i32.row, name.i32.col); }

math ::= math_add.
math ::= math_mul.

math_add(out) ::= value(a) PLUS(op) value(b).
{ out.i32.id = expr_math(mathtype_add, a.i32.id, b.i32.id, op.i32.row, op.i32.col); }
math_add(out) ::= math_add(a) PLUS(op) value(b).
{ out.i32.id = expr_math(mathtype_add, a.i32.id, b.i32.id, op.i32.row, op.i32.col); }

math_mul(out) ::= value(a) STAR(op) value(b).
{ out.i32.id = expr_math(mathtype_mul, a.i32.id, b.i32.id, op.i32.row, op.i32.col); }
math_mul(out) ::= math_mul(a) STAR(op) value(b).
{ out.i32.id = expr_math(mathtype_mul, a.i32.id, b.i32.id, op.i32.row, op.i32.col); }

call_args_or_empty ::= .
call_args_or_empty ::= call_args.

call_args ::= expr(e).
{ call_arg(e.i32.id); }
call_args ::= call_args COMMA expr(e).
{ call_arg(e.i32.id); }

call_args_begin ::= OPEN_PAREN.
{ call_arg_begin(); }

call(out) ::= id(name) call_args_begin call_args_or_empty CLOSE_PAREN.
{ out.i32.id = expr_call(name.i32.id, name.i32.row, name.i32.col); }

num_int(out) ::= TRUE(i).
{ out.i32.id = expr_i32(1, i.i32.row, i.i32.col); }
num_int(out) ::= FALSE(i).
{ out.i32.id = expr_i32(1, i.i32.row, i.i32.col); }
num_int(out) ::= INT(i).
{ out.i32.id = expr_i32(i.i32.id, i.i32.row, i.i32.col); }
num_int(out) ::= UINT(i).
{ out.i32.id = expr_i32(i.i32.id, i.i32.row, i.i32.col); }

// type ::= id.
type(out) ::= type_builtin(in).
{ out.i32.id = in.i32.id; }

type_builtin(out) ::= VOID.
{ out.i32.id = type_void; }
type_builtin(out) ::= U16.
{ out.i32.id = type_u16; }
type_builtin(out) ::= U32.
{ out.i32.id = type_u32; }
type_builtin(out) ::= I32.
{ out.i32.id = type_i32; }
type_builtin(out) ::= BOOL.
{ out.i32.id = type_bool; }
type_builtin(out) ::= CHAR.
{ out.i32.id = type_bool; }

id ::= ID.
