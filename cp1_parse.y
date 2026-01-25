%include {
char* string_mem;
void stdout_then_print_error(void*, int);
}
%name cp1Parse
%token_prefix CP1_TOKEN_
%stack_size 0 // let it grow

%token_type {union _Tcp1_Ttoken_data}

%left PLUS MINUS. 

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
            if (_Tcp1_Glast_token == CP1_TOKEN_END) {
               if (string_mem[0] == 0) {
                  ibuf = sprintf(errbuf, "%s:%u:%u: syntax error, got #end-of-file but expected tokens are: #%s", input_path, _Tcp1_Grow, _Tcp1_Gcol, _Tcp1_Ftoken_name_1(i));
               } else {
                  ibuf = sprintf(errbuf, "%s:%u:%u: syntax error, got token '%c' but expected tokens are: #%s", input_path, _Tcp1_Grow, _Tcp1_Gcol, string_mem[0], _Tcp1_Ftoken_name_1(i));
               }
            } else {
               ibuf = sprintf(errbuf, "%s:%u:%u: syntax error, got token #%s but expected tokens are: #%s", input_path, _Tcp1_Grow, _Tcp1_Gcol, _Tcp1_Ftoken_name_1(_Tcp1_Glast_token), _Tcp1_Ftoken_name_1(i));
            }
         } else {
            if (second_expect == 0) {
               second_expect = i;
            }
            ibuf += sprintf(errbuf + ibuf, ", #%s", _Tcp1_Ftoken_name_1(i));
         }
      }
   }
   if (!first) {
      errbuf[ibuf++] = '\n';
      stdout_then_print_error(errbuf, ibuf);
      if (_Tcp1_Glast_token == CP1_TOKEN_SPACE && (first_expect == CP1_TOKEN_SPACE_CLOSE_CURLY_BRACE && second_expect == CP1_TOKEN_SEMICOLON)) {
         stdout_then_print_error(errbuf, sprintf(errbuf, "%s:%u:%u: Maybe you forgot to put semicolon?\n", input_path, _Tcp1_Grow, _Tcp1_Gcol));
      } else if (
         (
         _Tcp1_Glast_token == CP1_TOKEN_SPACE_THEN_OPEN_CURLY_BRACE ||
         _Tcp1_Glast_token == CP1_TOKEN_SPACE ||
         _Tcp1_Glast_token == CP1_TOKEN_CLOSE_PARENTHESIS ||
         _Tcp1_Glast_token == CP1_TOKEN_SPACE_CLOSE_PARENTHESIS
         ) &&
         // Extra parenthesis might be a common error, help them know
            (
            first_expect == CP1_TOKEN_PLUS &&
            second_expect == CP1_TOKEN_MINUS
            )) {
               // Detect when the parser is suggesting ++ and -- operators
               stdout_then_print_error(errbuf, sprintf(errbuf, "%s:%u:%u: Maybe you have extra parenthesis that are not used?\n", input_path, _Tcp1_Grow, _Tcp1_Gcol));
      } else {
         const char* tokname = _Tcp1_Ftoken_name_1(_Tcp1_Glast_token);
         if (
            memcmp(tokname, "space-op-", 9) == 0 ||
            memcmp(tokname, "space-cmp-", 10) == 0 ||
            memcmp(tokname, "space-bool-", 11) == 0) {
            // Missing parenthesis might be a common error, help them know
            // Detect when the parser hits the expression's end in...
            if (
               first_expect == CP1_TOKEN_SPACE_THEN_OPEN_CURLY_BRACE || // in: if, elif, switch
               first_expect == CP1_TOKEN_SPACE_CLOSE_CURLY_BRACE || // in: assign statements
               first_expect == CP1_TOKEN_CLOSE_PARENTHESIS || // in: function arguments
               first_expect == CP1_TOKEN_SPACE) { // in: meta function arguments
               stdout_then_print_error(errbuf, sprintf(errbuf, "%s:%u:%u: Maybe you lack parenthesis when using different operators?\n", input_path, _Tcp1_Grow, _Tcp1_Gcol));
            }
         }
      }
   }
   exit(EXIT_FAILURE);
   return;
}
   
cp1 ::= decls space_or_end.
cp1 ::= SPACE decls space_or_end.
cp1 ::= space_or_end.

begin_pos(t) ::= .
   { t.basic.row = _Tcp1_Grow; t.basic.col = _Tcp1_Gcol; }
end_pos(t) ::= .
   { t.basic.row = _Tcp1_Grow; t.basic.col = _Tcp1_Gcol - 1; }

func_decl_begin ::= FUNC_ID(name).
   { _Tcp1_Fdecl_func_begin_3(name.basic.id, name.basic.row, name.basic.col); }
func_decl_begin_angle ::= FUNC_ID_ANGLE(name).
   { _Tcp1_Fdecl_func_begin_3(name.basic.id, name.basic.row, name.basic.col); }
at_name ::= ID_TYPE(e).
   { _Tcp1_Fat_push_4(e.basic.id, 1, e.basic.row, e.basic.col); }
enum_cvar_begin ::= HASH_ID(e).
   { _Tcp1_Fenum_add_cvar_3(e.basic.id, e.basic.row, e.basic.col); }
enum_cvar_begin_decl ::= HASH_ID(e) typeAndInfo_optional.
   { _Tcp1_Fdecl_add_cvar_3(e.basic.id, e.basic.row, e.basic.col); }
struct_decl_begin ::= STRUCT SPACE ID_TYPE(name).
   { _Tcp1_Fdecl_at_begin_struct_3(name.basic.id, name.basic.row, name.basic.col); }
struct_decl_begin ::= UNION SPACE ID_TYPE(name).
   { _Tcp1_Fdecl_at_begin_struct_3(name.basic.id, name.basic.row, name.basic.col);
     _Tcp1_Fstruct_attr_union_0(); }
fvar_decl_name ::= ID(name).
   { _Tcp1_Fdecl_var_begin_3(name.basic.id, name.basic.row, name.basic.col); }
lvar_decl_name ::= ID(name).
   { _Tcp1_Fdecl_var_begin_3(name.basic.id, name.basic.row, name.basic.col); }

cvar_attr ::= SPACE_AT_REAL_NAME_STR(e).
   { _Tcp1_Fcvar_attr_real_name_1(e.basic.id); }
cvar_attr ::= SPACE_AT_REAL_NAME.
   { _Tcp1_Fcvar_attr_real_name_1(-1); }
cvar_attr ::= SPACE_AT_NO_DECL.
   { _Tcp1_Fcvar_attr_no_decl_0(); }
cvar_attr ::= SPACE_AT_NO_NAME.
   { _Tcp1_Fcvar_attr_no_name_0(); }
cvar_attr ::= SPACE_AT_DONT_COUNT.
   { _Tcp1_Fcvar_attr_dont_count_0(); }
cvar_attr ::= SPACE_AT_NO_DECL_STR(e).
   { _Tcp1_Fcvar_attr_no_decl_0(); _Tcp1_Fcvar_attr_real_name_1(e.basic.id); }
cvar_attrs ::= cvar_attr.
cvar_attrs ::= cvar_attrs cvar_attr.
cvar_attrs_optional ::= .
cvar_attrs_optional ::= cvar_attrs.
enum_cvar ::= enum_cvar_begin cvar_attrs_optional.
enum_cvar ::= enum_cvar_begin cvar_attrs_optional SPACE_EQUAL SPACE expr(set).
   { _Tcp1_Fenum_set_cvar_expr_1(set.basic.id); }
cvar_decl ::= enum_cvar_begin_decl cvar_attrs_optional.
cvar_decl ::= enum_cvar_begin_decl cvar_attrs_optional SPACE_EQUAL SPACE expr(set).
   { _Tcp1_Fenum_set_cvar_expr_1(set.basic.id); }
enum_decl_begin ::= ENUM SPACE ID_TYPE(name).
   { _Tcp1_Fdecl_at_begin_enum_3(name.basic.id, name.basic.row, name.basic.col); }

decl_include ::= INCLUDE(e).
   { _Tcp1_Fdecl_include_begin_3(e.basic.id, e.basic.row, e.basic.col); }
decl ::= decl_include SPACE_THEN_OPEN_CURLY_BRACE OPEN_CURLY_BRACE SPACE decls SPACE_CLOSE_CURLY_BRACE.
   { _Tcp1_Fdecl_include_end_0(); }
decl ::= decl_include SPACE_THEN_OPEN_CURLY_BRACE OPEN_CURLY_BRACE SPACE CLOSE_CURLY_BRACE.
   { _Tcp1_Fdecl_include_end_0(); }

/*
at_root ::= DOT.
   { _Tcp1_Fat_root_0(); }
*/
/* at_graves_count(l) ::= GRAVE(e).
   { l.basic.id = 1; l.basic.row = e.basic.row; l.basic.col = e.basic.col; }
at_graves_count(l) ::= at_graves_count(r) GRAVE.
   { l.basic.id = r.basic.id + 1; l.basic.row = r.basic.row; l.basic.col = r.basic.col; }
at_graves ::= at_graves_count(e).
   { _Tcp1_Fat_graves_3(e.basic.id, e.basic.row, e.basic.col); } */
// at_names ::= at_alias.
// at_names ::= at_graves at_name.
at_begin ::= .
   { _Tcp1_Fat_begin_relative_0(); }
at_names ::= at_begin at_name.
at_names ::= at_names at_name.
at(l) ::= type_basic_id(r).
   { l.basic.id = _Tcp1_Fat_basic_type_1(r.basic.id); }
at(l) ::= at_names.
   { l.basic.id = _Tcp1_Fat_done_0(); }
/*
at(l) ::= at_root.
   { l.basic.id = _Tcp1_Fat_done_0(); }
*/
/* at(l) ::= at_graves.
   { l.basic.id = _Tcp1_Fat_done_0(); } */
decl_at_name ::= ID_TYPE(e).
   { _Tcp1_Fdecl_at_add_4(e.basic.id, 1, e.basic.row, e.basic.col); }
decl_at_begin_at ::= .
   { _Tcp1_Fat_begin_0(); }
decl_at_names ::= decl_at_begin_at decl_at_name.
decl_at_names ::= decl_at_names decl_at_name.
decl_at_namespace ::= decl_at_names.
decl_at_namespace ::= type_basic_id(e).
   { _Tcp1_Fdecl_at_basic_1(e.basic.id); }
decl_at_begin_begin(l) ::= USING SPACE(r).
   { _Tcp1_Fat_begin_relative_pause_0(); l.basic.row = r.basic.row; l.basic.col = r.basic.col; }
decl_at_begin_end ::= /* CLOSE_PARENTHESIS */.
   { _Tcp1_Fat_begin_relative_resume_0(); }
decl_at_begin ::= decl_at_begin_begin(pos) /* OPEN_PARENTHESIS */ decl_at_namespace decl_at_begin_end.
   { _Tcp1_Fdecl_at_begin_2(pos.basic.row, pos.basic.col); }
decl_at ::= decl_at_begin SPACE_THEN_OPEN_CURLY_BRACE OPEN_CURLY_BRACE SPACE decls SPACE_CLOSE_CURLY_BRACE.
   { _Tcp1_Fdecl_at_end_0(); }
decl_at ::= decl_at_begin SPACE_THEN_OPEN_CURLY_BRACE OPEN_CURLY_BRACE SPACE_CLOSE_CURLY_BRACE.
   { _Tcp1_Fdecl_at_end_0(); }
decl ::= decl_at.

/* template_name(l) ::= HASH_ID(r).
   { l.basic.id = r.basic.id; } */

decl_template_inst ::= HASH_ID(name) TEMPLATE_JSON(json).
   { _Tcp1_Fdecl_template_inst_3(name.basic.id, json.basic.row, json.basic.col); }
/* decl_template_inst ::= TEMPLATE_INST SPACE at(at) template_name(name) SEMICOLON.
   { _Tcp1_Fdecl_template_inst_2(name.basic.id, at); } */
decl ::= decl_template_inst.
meta_reflection(l) ::= .
   { l.basic.id = 0; l.basic.id2 = 0; }
meta_reflection(l) ::= SPACE_AT_REFLECTION.
   { l.basic.id = 1; l.basic.id2 = 0; }
meta_reflection(l) ::= SPACE_AT_NO_CACHE.
   { l.basic.id = 0; l.basic.id2 = 1; }
meta_reflection(l) ::= SPACE_AT_REFLECTION SPACE_AT_NO_CACHE.
   { l.basic.id = 1; l.basic.id2 = 1; }
meta_reflection(l) ::= SPACE_AT_NO_CACHE SPACE_AT_REFLECTION.
   { l.basic.id = 1; l.basic.id2 = 1; }
decl_template_code ::= META SPACE HASH_ID(name) meta_reflection(r) SPACE_THEN_OPEN_CURLY_BRACE TEMPLATE_CODE(code).
   { _Tcp1_Fdecl_template_code_4(name.basic.id, code.basic.row, r.basic.id, r.basic.id2); }
decl ::= decl_template_code.
decl_import ::= IMPORT(path) SEMICOLON.
   { _Tcp1_Fdecl_import_4(path.basic.id, path.basic.row, path.basic.col, false); }
decl_import ::= REQUIRE(path) SEMICOLON.
   { _Tcp1_Fdecl_import_4(path.basic.id, path.basic.row, path.basic.col, true); }
decl ::= decl_import.

decl_cvar ::= cvars_decl SEMICOLON.
// decl_cvar ::= OPEN_CURLY_BRACE_CVAR_SPACE CLOSE_CURLY_BRACE.
decl ::= decl_cvar.

space_or_end ::= SPACE END.
space_or_end ::= END.

decl ::= decl_func.
decl ::= decl_struct.
decl ::= decl_enum.
decl ::= decl_gvars.
decl_alias_begin ::= USING_WITH_SEMICOLON SPACE.
   { _Tcp1_Fat_begin_relative_pause_0(); }
decl_alias_end ::= SEMICOLON.
   { _Tcp1_Fat_begin_relative_resume_0(); }
decl ::= decl_alias_begin ID_TYPE(short) SPACE_EQUAL SPACE at(long) decl_alias_end.
   { _Tcp1_Fdecl_alias_4(short.basic.id, long.basic.id, short.basic.row, short.basic.col); }
decls ::= decl.
decls ::= decls SPACE decl.

open_parenthesis_or_space(l) ::= OPEN_PARENTHESIS(r).
   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; }
open_parenthesis_or_space(l) ::= OPEN_PARENTHESIS SPACE(r).
   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; }
open_angle_or_space(l) ::= OPEN_ANGLE(r).
   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; }
open_angle_or_space(l) ::= OPEN_ANGLE SPACE(r).
   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; }
close_parenthesis_or_space(l) ::= CLOSE_PARENTHESIS(r).
   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; }
close_parenthesis_or_space(l) ::= SPACE_CLOSE_PARENTHESIS(r).
   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; }
close_parenthesis_or_comma(l) ::= close_parenthesis_or_space(r).
   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; }
close_parenthesis_or_comma(l) ::= COMMA_SPACE_CLOSE_PARENTHESIS(r).
   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; }
close_angle_or_space(l) ::= CLOSE_ANGLE(r).
   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; }
close_angle_or_space(l) ::= SPACE_CLOSE_ANGLE(r).
   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; }
close_angle_or_comma(l) ::= close_angle_or_space(r).
   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; }
close_angle_or_comma(l) ::= COMMA_SPACE_CLOSE_ANGLE(r).
   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; }

close_curly_brace_or_scolon(l) ::= SPACE_CLOSE_CURLY_BRACE(r).
   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; }
close_curly_brace_or_scolon(l) ::= SEMICOLON SPACE_CLOSE_CURLY_BRACE(r).
   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; }

open_bracket_or_space(l) ::= OPEN_BRACKET(r).
   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; }
open_bracket_or_space(l) ::= OPEN_BRACKET SPACE(r).
   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; }
/* close_bracket_or_space(l) ::= CLOSE_BRACKET(r).
   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; }
close_bracket_or_space(l) ::= SPACE_CLOSE_BRACKET(r).
   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; } */
close_bracket_or_comma(l) ::= CLOSE_BRACKET(r).
   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; }
close_bracket_or_comma(l) ::= SPACE_CLOSE_BRACKET(r).
   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; }
close_bracket_or_comma(l) ::= COMMA_SPACE_CLOSE_BRACKET(r).
   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; }

scolon_space ::= SEMICOLON SPACE.

lvar_decl(l) ::= lvar_decl_name(r).
   { _Tcp1_Fdecl_var_end_0(); l.basic.row = r.basic.row; l.basic.col = r.basic.col; }
farg ::= lvar_decl(e) typeAndInfo.
   { _Tcp1_Fdecl_var_as_farg_2(e.basic.row, e.basic.col); }
expr_type_this_apply ::= THIS.
   { _Tcp1_Fdecl_var_this_0(); }
farg ::= lvar_decl expr_type_this_apply typeInfo_optional.
   { _Tcp1_Fdecl_var_as_this_0(); }
expr_type_none ::= .
   { _Tcp1_Fdecl_var_type_1(-1); }
expr_type_apply ::= at(r).
   { _Tcp1_Fdecl_var_type_1(r.basic.id); }
farg_list ::= farg.
farg_list ::= farg_list COMMA_SPACE farg.
fargs ::= open_parenthesis_or_space CLOSE_PARENTHESIS.
fargs ::= open_parenthesis_or_space farg_list close_parenthesis_or_comma.
fargs_angle ::= open_angle_or_space CLOSE_ANGLE.
fargs_angle ::= open_angle_or_space farg_list close_angle_or_comma.
farg_next_group ::= open_parenthesis_or_space.
   { _Tcp1_Ffarg_next_group_0(); }
fargs ::= fargs farg_next_group farg_list close_parenthesis_or_comma.
fargs ::= fargs farg_next_group CLOSE_PARENTHESIS.
fargs_angle ::= fargs_angle farg_next_group farg_list close_parenthesis_or_comma.
fargs_angle ::= fargs_angle farg_next_group CLOSE_PARENTHESIS.
func_attr ::= SPACE_AT_MAIN.
   { _Tcp1_Ffunc_attr_main_0(); }
func_attr ::= SPACE_AT_CASE DOT FUNC_ID(e) OPEN_PARENTHESIS CLOSE_PARENTHESIS.
   { _Tcp1_Ffunc_attr_case_1(e.basic.id); }
func_attr ::= SPACE_AT_PROCESS.
   { _Tcp1_Ffunc_attr_process_0(); }
func_attr ::= SPACE_AT_INLINE.
   { _Tcp1_Ffunc_attr_inline_0(); }
func_attr ::= SPACE_AT_CP1_NAME.
   { _Tcp1_Ffunc_attr_cp1_name_0(); }
func_attr ::= SPACE_AT_DECL OPEN_PARENTHESIS STRING CLOSE_PARENTHESIS.
   { _Tcp1_Ffunc_attr_decl_0(); }
func_attr ::= SPACE_AT_VAR_ARGS.
   { _Tcp1_Ffunc_attr_var_args_0(); }
func_attr ::= SPACE_AT_NO_DECL.
   { _Tcp1_Ffunc_attr_no_decl_0(); }
func_attr ::= SPACE_AT_NO_DECL_STR(e).
   { _Tcp1_Ffunc_attr_no_decl_0(); _Tcp1_Ffunc_attr_real_name_1(e.basic.id); }
func_attr ::= SPACE_AT_NO_BODY.
   { _Tcp1_Ffunc_attr_no_body_0(); }
func_attr ::= SPACE_AT_OVERLOAD_Tcp1_GET.
   { _Tcp1_Ffunc_attr_overload_get_0(); }
func_attr ::= SPACE_AT_OVERLOAD_SET.
   { _Tcp1_Ffunc_attr_overload_set_0(); }
func_attr ::= SPACE_AT_OVERLOAD_MATH.
   { _Tcp1_Ffunc_attr_overload_math_0(); }
func_attr ::= SPACE_AT_OVERLOAD_BOOLS.
   { _Tcp1_Ffunc_attr_overload_bools_0(); }
func_attr ::= SPACE_AT_OVERLOAD_COMPARE.
   { _Tcp1_Ffunc_attr_overload_compare_0(); }
func_attr ::= SPACE_AT_OVERLOAD_IF_BEGIN.
   { _Tcp1_Ffunc_attr_overload_if_begin_0(); }
func_attr ::= SPACE_AT_OVERLOAD_IF_ELSE.
   { _Tcp1_Ffunc_attr_overload_if_else_0(); }
func_attr ::= SPACE_AT_OVERLOAD_IF_END.
   { _Tcp1_Ffunc_attr_overload_if_end_0(); }
func_attr ::= SPACE_AT_OVERLOAD_STATEMENT.
   { _Tcp1_Ffunc_attr_overload_statement_0(); }
func_attr ::= SPACE_AT_REAL_NAME_STR(e).
   { _Tcp1_Ffunc_attr_real_name_1(e.basic.id); }
func_attr ::= SPACE_AT_META OPEN_PARENTHESIS ID(id1) COMMA_SPACE ID(id2) CLOSE_PARENTHESIS.
   { _Tcp1_Ffunc_attr_meta_method_3(id1.basic.id, -1, id2.basic.id); }
func_attr ::= SPACE_AT_META OPEN_PARENTHESIS ID(id1) COMMA_SPACE ID(id2) COMMA_SPACE ID(id3) CLOSE_PARENTHESIS.
   { _Tcp1_Ffunc_attr_meta_method_3(id1.basic.id, id2.basic.id, id3.basic.id); }
func_attr ::= SPACE_AT_REAL_NAME.
   { _Tcp1_Ffunc_attr_real_name_1(-1); }
/* func_attrs(l) ::= OPEN_CURLY_BRACE_SPACE(r).
   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; }
func_attrs(l) ::= func_attr OPEN_CURLY_BRACE_SPACE(r).
   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; }
func_attrs_base ::= func_attr.
func_attrs_base ::= func_attrs_base func_attr.
func_attrs(l) ::= func_attrs_base func_attr OPEN_CURLY_BRACE_SPACE(r). */
func_attrs ::= func_attr.
func_attrs ::= func_attrs func_attr.
func_attrs_optional ::= .
func_attrs_optional ::= func_attrs.
/*   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; } */
type_basic_id(l) ::= REF.
   { l.basic.id = 2; }
type_basic_id(l) ::= BOOL.
   { l.basic.id = 3; }
type_basic_id(l) ::= CHAR.
   { l.basic.id = 4; }
type_basic_id(l) ::= INTC.
   { l.basic.id = 5; }
type_basic_id(l) ::= I8.
   { l.basic.id = 6; }
type_basic_id(l) ::= U8.
   { l.basic.id = 7; }
type_basic_id(l) ::= I16.
   { l.basic.id = 8; }
type_basic_id(l) ::= U16.
   { l.basic.id = 9; }
type_basic_id(l) ::= I32.
   { l.basic.id = 10; }
type_basic_id(l) ::= U32.
   { l.basic.id = 11; }
type_basic_id(l) ::= I64.
   { l.basic.id = 12; }
type_basic_id(l) ::= U64.
   { l.basic.id = 13; }
type_basic_id(l) ::= ISZ.
   { l.basic.id = 14; }
type_basic_id(l) ::= USZ.
   { l.basic.id = 15; }
type_basic_id(l) ::= F32.
   { l.basic.id = 16; }
type_basic_id(l) ::= F64.
   { l.basic.id = 17; }
// expr_type_basic(l) ::= type_basic_id(r). { l.basic.id = _Tcp1_Fexpr_type_basic_1(r.basic.id); }
// expr_type_custom(l) ::= at(r). { l.basic.id = _Tcp1_Fexpr_type_1(r.basic.id); }
// expr_type(l) ::= expr_type_basic(r). { l.basic.id = r.basic.id; }
// expr_type(l) ::= expr_type_custom(r). { l.basic.id = r.basic.id; }
// expr_type(l) ::= at(r). { l.basic.id = _Tcp1_Fexpr_type_1(r.basic.id); }
func_type ::= typeAndInfo_optional.
func_decl ::= func_decl_begin fargs func_type func_attrs_optional. // SPACE open_curly_brace_or_space.
   { _Tcp1_Fdecl_func_end_3(_Tcp1_Grow, _Tcp1_Gcol, 0); }
func_decl ::= func_decl_begin_angle fargs_angle func_type func_attrs_optional. // SPACE open_curly_brace_or_space.
   { _Tcp1_Fdecl_func_end_3(_Tcp1_Grow, _Tcp1_Gcol, 1); }
/* func_decl ::= OPEN_CURLY_BRACE func_decl_begin fargs func_type.
   { _Tcp1_Fdecl_func_end_2(_Tcp1_Grow, _Tcp1_Gcol); } */
/* func_attrs_inline(l) ::= SPACE_AT_INLINE_SEMICOLON(r).
   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; }
func_attrs_inline(l) ::= func_attr SPACE_AT_INLINE_SEMICOLON(r).
   { l.basic.row = r.basic.row; l.basic.col = l.basic.col; }
func_attrs_inline(l) ::= func_attrs_base func_attr SPACE_AT_INLINE_SEMICOLON(r).
   { l.basic.row = r.basic.row; l.basic.col = l.basic.col; }
func_decl_inline ::= func_decl_begin fargs func_type func_attrs_inline(end).
   { _Tcp1_Fdecl_func_end_2(end.basic.row, end.basic.col); } */
fvar_decl ::= fvar_decl_name.
   { _Tcp1_Fdecl_var_end_0(); }
fvar_attr ::= SPACE_AT_REAL_NAME_STR(e).
   { _Tcp1_Fdecl_var_attr_real_name_1(e.basic.id); }
fvar_attr ::= SPACE_AT_REAL_NAME.
   { _Tcp1_Fdecl_var_attr_real_name_1(-1); }
fvar_attrs_list ::= fvar_attr.
fvar_attrs_list ::= fvar_attrs_list fvar_attr.
fvar_attrs_optional ::= .
fvar_attrs_optional ::= fvar_attrs_list.
fvar ::= fvar_decl typeAndInfo fvar_attrs_optional.
   { _Tcp1_Fdecl_var_as_fvar_0(); }
struct_fvars ::= fvar.
struct_fvars ::= struct_fvars COMMA_SPACE fvar.
enum_cvars ::= enum_cvar.
enum_cvars ::= enum_cvars COMMA_SPACE enum_cvar.
cvars_decl ::= cvar_decl.
cvars_decl ::= cvars_decl COMMA_SPACE cvar_decl.

typeInfo ::= typeInfo_arr.
typeInfo ::= typeInfo_ref.
typeInfo ::= typeInfo_bi.
typeInfo_bi ::= DOT.
   { _Tcp1_Ftype_info_static_0(); }
ref_count(l) ::= AMPERSAND.
   { l.basic.id = 1; }
ref_count(l) ::= ref_count(r) AMPERSAND.
   { l.basic.id = r.basic.id + 1; }
typeInfo_ref ::= ref_count(c).
   { _Tcp1_Ftype_info_ref_1(c.basic.id); }
typeInfo_ref ::= typeInfo_arr ref_count(c).
   { _Tcp1_Ftype_info_ref_1(c.basic.id); }
typeInfo_ref ::= typeInfo_bi ref_count(c).
   { _Tcp1_Ftype_info_ref_1(c.basic.id); }
typeInfo_arr ::= OPEN_BRACKET CLOSE_BRACKET.
   { _Tcp1_Ftype_info_arr_2(0, 0); }
typeInfo_arr ::= typeInfo_arr_exprs.
typeInfo_arr ::= typeInfo_bi OPEN_BRACKET CLOSE_BRACKET.
   { _Tcp1_Ftype_info_arr_2(0, 0); }
typeInfo_arr ::= typeInfo_bi typeInfo_arr_exprs.
typeInfo_arr ::= typeInfo_ref OPEN_BRACKET CLOSE_BRACKET.
   { _Tcp1_Ftype_info_arr_2(0, 0); }
typeInfo_arr ::= typeInfo_arr OPEN_BRACKET CLOSE_BRACKET.
   { _Tcp1_Ftype_info_arr_2(0, 0); }
typeInfo_arr ::= typeInfo_arr typeInfo_arr_exprs.
typeInfo_arr_exprs ::= open_bracket_or_space typeInfo_arr_exprs1(e) close_bracket_or_comma.
   { _Tcp1_Ftype_info_arr_2(e.index.v, e.index.c); }
typeInfo_arr_exprs1(l) ::= expr(e).
   { l.index.v[(l.index.c = 1) - 1] = e.basic.id; }
typeInfo_arr_exprs1(l) ::= typeInfo_arr_exprs1 COMMA_SPACE expr(e).
   { l.index.v[l.index.c ++] = e.basic.id; }
typeInfo_begin ::= .
   { _Tcp1_Ftype_info_begin_1(false); }
typeInfo_begin ::= SPACE_AT_CONST.
   { _Tcp1_Ftype_info_begin_1(true); }
typeInfo_none ::= typeInfo_begin.
   { _Tcp1_Ftype_info_finalize_0(); }
typeInfo_optional ::= typeInfo_none.
typeInfo_optional ::= typeInfo_begin typeInfo.
   { _Tcp1_Ftype_info_finalize_0(); }

expr_int(l) ::= NUM_ZERO.
   { l.basic.id = _Tcp1_Fexpr_int_2(0, 0); }
expr_int(l) ::= NUM_I32(e).
   { l.basic.id = _Tcp1_Fexpr_int_2(e.basic.id, 0); }
expr_int(l) ::= NUM_U32(e).
   { l.basic.id = _Tcp1_Fexpr_int_2(e.basic.id, 1); }
expr_int(l) ::= NUM_F32(e).
   { l.basic.id = _Tcp1_Fexpr_f32_1(e.f32.f32); }
expr_int(l) ::= NUM_F64(e).
   { l.basic.id = _Tcp1_Fexpr_f64_1(e.f64.f64); }
expr_int(l) ::= NUM_OCT(e).
   { l.basic.id = _Tcp1_Fexpr_int_2(e.basic.id, 3); }
expr_int(l) ::= NUM_HEX(e).
   { l.basic.id = _Tcp1_Fexpr_int_2(e.basic.id, 4); }
expr_int(l) ::= NUM_U64(e).
   { l.basic.id = _Tcp1_Fexpr_int64_2(e.u64.u64, 5); }

expr_str(l) ::= STRING.
   { l.basic.id = _Tcp1_Fexpr_str_2(-1, 0); }
expr_str(l) ::= STRING_MACRO.
   { l.basic.id = _Tcp1_Fexpr_str_2(-1, 1); }
expr_str(l) ::= expr_str(e) SPACE_THEN_STRING STRING.
   { l.basic.id = _Tcp1_Fexpr_str_2(e.basic.id, 0); }
expr_str(l) ::= expr_str(e) SPACE_THEN_STRING STRING_MACRO.
   { l.basic.id = _Tcp1_Fexpr_str_2(e.basic.id, 1); }

/* expr_lvar_plus(l) ::= PLUS.
   { l.basic.id = 1; }
expr_lvar_plus(l) ::= expr_lvar_plus(r) PLUS.
   { l.basic.id = r.basic.id + 1; } */
expr_lvar(e) ::= ID(var).
   { e.basic.id = _Tcp1_Fexpr_lvar_4(var.basic.id, 0, var.basic.row, var.basic.col); }
expr_lvar(e) ::= ID(var) EXCLAMATION expr_type_none.
   { e.basic.id = _Tcp1_Fexpr_lvar_4(var.basic.id, 1, var.basic.row, var.basic.col); }
expr_lvar(e) ::= ID(var) QUESTION expr_type_none.
   { e.basic.id = _Tcp1_Fexpr_lvar_4(var.basic.id, 2, var.basic.row, var.basic.col); }
/* expr_lvar(e) ::= expr_lvar_plus(plus) open_parenthesis_or_space ID(var) typeAndInfo close_parenthesis_or_space.
   { e.basic.id = _Tcp1_Fexpr_lvar_4(var.basic.id, plus.basic.id, var.basic.row, var.basic.col); } */
expr_cvar(l) ::= HASH_ID(e).
   { l.basic.id = _Tcp1_Fexpr_cvar_2(-1, e.basic.id); }
expr_cvar(l) ::= at(at) HASH_ID(e).
   { l.basic.id = _Tcp1_Fexpr_cvar_2(at.basic.id, e.basic.id); }
value(l) ::= value4fix(r).
   { l.basic.id = r.basic.id; }
value(l) ::= negVal(r).
   { l.basic.id = r.basic.id; }
value(l) ::= notExpr(r).
   { l.basic.id = r.basic.id; }
value4fix(l) ::= fastCastExpr(r).
   { l.basic.id = r.basic.id; }
value4fix(l) ::= value4cast(r).
   { l.basic.id = r.basic.id; }
value4cast(l) ::= valueonly(r).
   { l.basic.id = r.basic.id; }
value4cast(l) ::= expr_in_paren(r).
   { l.basic.id = r.basic.id; }
value4arr(l) ::= sizeOfTypeExpr(r).
   { l.basic.id = r.basic.id; }
value4arr(l) ::= boolExpr(r).
   { l.basic.id = r.basic.id; }
value4arr(l) ::= charExpr(r).
   { l.basic.id = r.basic.id; }
value4arr(l) ::= nullExpr(r).
   { l.basic.id = r.basic.id; }
charExpr(l) ::= CHAR1(c).
   { l.basic.id = _Tcp1_Fexpr_char_1(c.basic.id); }
charExpr(l) ::= CHAR2(c).
   { l.basic.id = _Tcp1_Fexpr_char_1(c.basic.id); }
boolExpr(l) ::= TRUE.
   { l.basic.id = _Tcp1_Fexpr_bool_1(1); }
boolExpr(l) ::= FALSE.
   { l.basic.id = _Tcp1_Fexpr_bool_1(0); }
nullExpr(l) ::= NULL.
   { l.basic.id = _Tcp1_Fexpr_null_0(); }
value4arr(l) ::= expr_lvar(r).
   { l.basic.id = r.basic.id; }
value4arr(l) ::= expr_cvar(r).
   { l.basic.id = r.basic.id; }
value4arr(l) ::= expr_int(r).
   { l.basic.id = r.basic.id; }
value4arr(l) ::= expr_str(r).
   { l.basic.id = r.basic.id; }
value4arr(l) ::= indexExpr(r).
   { l.basic.id = r.basic.id; }
valueonly(l) ::= value4arr(r).
   { l.basic.id = r.basic.id; }
valueonly(l) ::= callExpr(r).
   { l.basic.id = r.basic.id; }
valueonly(l) ::= fvarExpr(r).
   { l.basic.id = r.basic.id; }
valueonly(l) ::= soaFieldExpr(r).
   { l.basic.id = r.basic.id; }
valueonly(l) ::= gvarExpr(r).
   { l.basic.id = r.basic.id; }
gvarExpr(l) ::= DOT ID(r).
   { l.basic.id = _Tcp1_Fexpr_gvar_4(-1, r.basic.id, r.basic.row, r.basic.col); }
gvarExpr(l) ::= at(at) DOT ID(r).
   { l.basic.id = _Tcp1_Fexpr_gvar_4(at.basic.id, r.basic.id, r.basic.row, r.basic.col); }
fvarExpr(l) ::= value4fix(e) DOT ID(r).
   { l.basic.id = _Tcp1_Fexpr_fvar_4(e.basic.id, r.basic.id, r.basic.row, r.basic.col); }
soaFieldExpr(l) ::= value4fix(e) SOA_FIELD(f).
   { l.basic.id = _Tcp1_Fexpr_soa_field_5(e.basic.id, f.basic.id, f.basic.id2, f.basic.row, f.basic.col); }
expr_and1(l) ::= expr(left) COMMA_SPACE expr(right).
   { l.basic.id = _Tcp1_Fexpr_bools_3(left.basic.id, right.basic.id, 0); }
expr_and1(l) ::= expr_and1(left) COMMA_SPACE expr(right).
   { l.basic.id = _Tcp1_Fexpr_bools_add_2(left.basic.id, right.basic.id); }
expr_and(l) ::= OPEN_PARENTHESIS_AMP_AMP_COMMA SPACE expr_and1(r) close_parenthesis_or_comma.
   { l.basic.id = r.basic.id; }
expr_and_c(l) ::= value(left) SPACE_BOOL_AND_AND SPACE value(right).
   { l.basic.id = _Tcp1_Fexpr_bools_3(left.basic.id, right.basic.id, 0); }
expr_and_c(l) ::= expr_and_c(left) SPACE_BOOL_AND_AND SPACE value(right).
   { l.basic.id = _Tcp1_Fexpr_bools_add_2(left.basic.id, right.basic.id); }
expr_and_c(l) ::= value(left) SPACE_BOOL_AND_AND_SPACE value(right).
   { l.basic.id = _Tcp1_Fexpr_bools_3(left.basic.id, right.basic.id, 0); }
expr_and_c(l) ::= expr_and_c(left) SPACE_BOOL_AND_AND_SPACE value(right).
   { l.basic.id = _Tcp1_Fexpr_bools_add_2(left.basic.id, right.basic.id); }
expr_or_c(l) ::= value(left) SPACE_BOOL_OR_OR SPACE value(right).
   { l.basic.id = _Tcp1_Fexpr_bools_3(left.basic.id, right.basic.id, 1); }
expr_or_c(l) ::= expr_or_c(left) SPACE_BOOL_OR_OR SPACE value(right).
   { l.basic.id = _Tcp1_Fexpr_bools_add_2(left.basic.id, right.basic.id); }
expr_or_c(l) ::= value(left) SPACE_BOOL_OR_OR_SPACE value(right).
   { l.basic.id = _Tcp1_Fexpr_bools_3(left.basic.id, right.basic.id, 1); }
expr_or_c(l) ::= expr_or_c(left) SPACE_BOOL_OR_OR_SPACE value(right).
   { l.basic.id = _Tcp1_Fexpr_bools_add_2(left.basic.id, right.basic.id); }
expr_or1(l) ::= expr(left) COMMA_SPACE expr(right).
   { l.basic.id = _Tcp1_Fexpr_bools_3(left.basic.id, right.basic.id, 1); }
expr_or1(l) ::= expr_or1(left) COMMA_SPACE expr(right).
   { l.basic.id = _Tcp1_Fexpr_bools_add_2(left.basic.id, right.basic.id); }
expr_or(l) ::= OPEN_PARENTHESIS_PIPE_PIPE_COMMA SPACE expr_or1(r) close_parenthesis_or_comma.
   { l.basic.id = r.basic.id; }
expr_add(e) ::= value(left) SPACE_OP_PLUS SPACE value(right).
   { e.basic.id = _Tcp1_Fexpr_math_3(left.basic.id, right.basic.id, 0); }
expr_add(e) ::= expr_add(left) SPACE_OP_PLUS SPACE value(right).
   { e.basic.id = _Tcp1_Fexpr_math_add_2(left.basic.id, right.basic.id); }
expr_sub(e) ::= value(left) SPACE_OP_MINUS_SPACE value(right).
   { e.basic.id = _Tcp1_Fexpr_math_3(left.basic.id, right.basic.id, 1); }
expr_sub(e) ::= expr_sub(left) SPACE_OP_MINUS_SPACE value(right).
   { e.basic.id = _Tcp1_Fexpr_math_add_2(left.basic.id, right.basic.id); }
expr_mul(e) ::= value(left) SPACE_OP_MUL SPACE value(right).
   { e.basic.id = _Tcp1_Fexpr_math_3(left.basic.id, right.basic.id, 2); }
expr_mul(e) ::= expr_mul(left) SPACE_OP_MUL SPACE value(right).
   { e.basic.id = _Tcp1_Fexpr_math_add_2(left.basic.id, right.basic.id); }
expr_div(e) ::= value(left) SPACE_OP_DIV SPACE value(right).
   { e.basic.id = _Tcp1_Fexpr_math_3(left.basic.id, right.basic.id, 3); }
expr_div(e) ::= expr_div(left) SPACE_OP_DIV SPACE value(right).
   { e.basic.id = _Tcp1_Fexpr_math_add_2(left.basic.id, right.basic.id); }
expr_mod(e) ::= value(left) SPACE_OP_MOD SPACE value(right).
   { e.basic.id = _Tcp1_Fexpr_math_3(left.basic.id, right.basic.id, 4); }
expr_mod(e) ::= expr_div(left) SPACE_OP_MOD SPACE value(right).
   { e.basic.id = _Tcp1_Fexpr_math_add_2(left.basic.id, right.basic.id); }
expr_lshift(e) ::= value(left) SPACE_OP_LSHIFT SPACE value(right).
   { e.basic.id = _Tcp1_Fexpr_math_3(left.basic.id, right.basic.id, 5); }
expr_rshift(e) ::= value(left) SPACE_OP_RSHIFT SPACE value(right).
   { e.basic.id = _Tcp1_Fexpr_math_3(left.basic.id, right.basic.id, 6); }
expr_bit_and(e) ::= value(left) SPACE_OP_AND_SPACE value(right).
   { e.basic.id = _Tcp1_Fexpr_math_3(left.basic.id, right.basic.id, 7); }
expr_bit_and(e) ::= expr_bit_and(left) SPACE_OP_AND_SPACE value(right).
   { e.basic.id = _Tcp1_Fexpr_math_add_2(left.basic.id, right.basic.id); }
expr_bit_or(e) ::= value(left) SPACE_OP_OR_SPACE value(right).
   { e.basic.id = _Tcp1_Fexpr_math_3(left.basic.id, right.basic.id, 8); }
expr_bit_or(e) ::= expr_bit_or(left) SPACE_OP_OR_SPACE value(right).
   { e.basic.id = _Tcp1_Fexpr_math_add_2(left.basic.id, right.basic.id); }
expr_bit_xor(e) ::= value(left) SPACE_OP_XOR SPACE value(right).
   { e.basic.id = _Tcp1_Fexpr_math_3(left.basic.id, right.basic.id, 9); }
expr_bit_xor(e) ::= expr_bit_xor(left) SPACE_OP_XOR SPACE value(right).
   { e.basic.id = _Tcp1_Fexpr_math_add_2(left.basic.id, right.basic.id); }
opExpr(l) ::= assignExpr1(r).
   { l.basic.id = r.basic.id; }
opExpr(l) ::= expr_add(r).
   { l.basic.id = r.basic.id; }
opExpr(l) ::= expr_sub(r).
   { l.basic.id = r.basic.id; }
opExpr(l) ::= expr_mul(r).
   { l.basic.id = r.basic.id; }
opExpr(l) ::= expr_div(r).
   { l.basic.id = r.basic.id; }
opExpr(l) ::= expr_mod(r).
   { l.basic.id = r.basic.id; }
opExpr(l) ::= expr_lshift(r).
   { l.basic.id = r.basic.id; }
opExpr(l) ::= expr_rshift(r).
   { l.basic.id = r.basic.id; }
opExpr(l) ::= expr_bit_and(r).
   { l.basic.id = r.basic.id; }
opExpr(l) ::= expr_bit_or(r).
   { l.basic.id = r.basic.id; }
opExpr(l) ::= expr_bit_xor(r).
   { l.basic.id = r.basic.id; }
opExpr(l) ::= compareExpr(r).
   { l.basic.id = r.basic.id; }
opExpr(l) ::= incExpr(r).
   { l.basic.id = r.basic.id; }
opExpr(l) ::= decExpr(r).
   { l.basic.id = r.basic.id; }
compare_type(l) ::= SPACE_CMP_EQUAL_EQUAL SPACE.
   { l.basic.id = 0; }
compare_type(l) ::= SPACE_CMP_NOT_EQUAL SPACE.
   { l.basic.id = 1; }
compare_type(l) ::= SPACE_CMP_LESS_THAN SPACE.
   { l.basic.id = 2; }
compare_type(l) ::= SPACE_CMP_LESS_EQUAL SPACE.
   { l.basic.id = 3; }
compare_type(l) ::= SPACE_CMP_MORE_THAN_SPACE.
   { l.basic.id = 4; }
compare_type(l) ::= SPACE_CMP_MORE_EQUAL SPACE.
   { l.basic.id = 5; }
compareExpr(l) ::= value(a) compare_type(t) value(b).
   { l.basic.id = _Tcp1_Fexpr_compare_3(a.basic.id, b.basic.id, t.basic.id); }
expr_in_paren(l) ::= open_parenthesis_or_space opExpr(r) close_parenthesis_or_space.
   { l.basic.id = r.basic.id; }
expr_in_paren(l) ::= exprs(r).
   { l.basic.id = r.basic.id; }
funcExpr(l) ::= FUNC_ID(func).
   { l.basic.id = -1; l.basic.id2 = func.basic.id; _Tcp1_Fexpr_push_call_2(func.basic.row, func.basic.col); }
funcExpr(l) ::= at(at) DOT FUNC_ID(func).
   { l.basic.id = at.basic.id; l.basic.id2 = func.basic.id; _Tcp1_Fexpr_push_call_2(func.basic.row, func.basic.col); }
funcExpr_angle(l) ::= FUNC_ID_ANGLE(func).
   { l.basic.id = -1; l.basic.id2 = func.basic.id; _Tcp1_Fexpr_push_call_2(func.basic.row, func.basic.col); }
funcExpr_angle(l) ::= at(at) DOT FUNC_ID_ANGLE(func).
   { l.basic.id = at.basic.id; l.basic.id2 = func.basic.id; _Tcp1_Fexpr_push_call_2(func.basic.row, func.basic.col); }
metaFuncExpr(l) ::= ID_THEN_OPEN_CURLY_BRACE(func).
   { l.basic.id = -1; l.basic.id2 = func.basic.id; _Tcp1_Fexpr_push_call_2(func.basic.row, func.basic.col); }
metaFuncExpr(l) ::= ID_TYPE_THEN_OPEN_CURLY_BRACE(func).
   { l.basic.id = -1; l.basic.id2 = func.basic.id; _Tcp1_Fexpr_push_call_2(func.basic.row, func.basic.col); }
metaFuncExpr(l) ::= at(at) DOT ID_THEN_OPEN_CURLY_BRACE(func).
   { l.basic.id = at.basic.id; l.basic.id2 = func.basic.id; _Tcp1_Fexpr_push_call_2(func.basic.row, func.basic.col); }
methodExpr(l) ::= value4fix(e) DOT FUNC_ID(func).
   { l.basic.id = e.basic.id; l.basic.id2 = func.basic.id; _Tcp1_Fexpr_push_call_2(func.basic.row, func.basic.col); }
methodExpr_angle(l) ::= value4fix(e) DOT FUNC_ID_ANGLE(func).
   { l.basic.id = e.basic.id; l.basic.id2 = func.basic.id; _Tcp1_Fexpr_push_call_2(func.basic.row, func.basic.col); }
metaMethodExpr(l) ::= value4fix(e) DOT ID_THEN_OPEN_CURLY_BRACE(func).
   { l.basic.id = e.basic.id; l.basic.id2 = func.basic.id; _Tcp1_Fexpr_push_call_2(func.basic.row, func.basic.col); }
metaCall_args_optional ::= OPEN_CURLY_BRACE CLOSE_CURLY_BRACE.
metaCall_args_optional ::= OPEN_CURLY_BRACE SPACE CLOSE_CURLY_BRACE.
metaCall_args_optional ::= metaCall_args_next_group_empty metaCall_args CLOSE_CURLY_BRACE.
metaCall_args_optional ::= metaCall_args_next_group_empty metaCall_args SPACE_CLOSE_CURLY_BRACE.
metaCall_arg ::= expr(e).
   { _Tcp1_Fmetacarg_push_1(e.basic.id); }
metaCall_arg_list ::= metaCall_arg.
metaCall_arg_list ::= metaCall_arg_list COMMA_SPACE metaCall_arg.
metaCall_args ::= metaCall_arg_list.
metaCall_args_next_group ::= SPACE.
   { _Tcp1_Fmetacarg_next_group_0(); }
metaCall_args_next_group ::= SEMICOLON SPACE.
   { _Tcp1_Fmetacarg_next_group_0(); }
metaCall_args_next_group_empty ::= OPEN_CURLY_BRACE.
   { _Tcp1_Fmetacarg_next_group_0(); }
metaCall_args_next_group_empty ::= OPEN_CURLY_BRACE SPACE.
   { _Tcp1_Fmetacarg_next_group_0(); }
metaCall_args ::= metaCall_args metaCall_args_next_group metaCall_arg_list.
call_arg ::= expr(e).
   { _Tcp1_Fcarg_push_1(e.basic.id); }
call_arg ::= expr_str(e) HASH.
   { _Tcp1_Fcarg_push_str_1(e.basic.id); }
call_arg_list ::= call_arg.
call_arg_list ::= call_arg_list COMMA_SPACE call_arg.
call_args ::= open_parenthesis_or_space CLOSE_PARENTHESIS.
call_args ::= open_parenthesis_or_space call_arg_list close_parenthesis_or_comma.
call_args_angle ::= open_angle_or_space CLOSE_ANGLE.
call_args_angle ::= open_angle_or_space call_arg_list close_angle_or_comma.
call_args_next_group ::= open_parenthesis_or_space.
   { _Tcp1_Fcarg_next_group_0(); }
call_args ::= call_args call_args_next_group call_arg_list close_parenthesis_or_comma.
call_args ::= call_args call_args_next_group CLOSE_PARENTHESIS.
call_args_angle ::= call_args_angle call_args_next_group call_arg_list close_parenthesis_or_comma.
call_args_angle ::= call_args_angle call_args_next_group CLOSE_PARENTHESIS.
callExpr(l) ::= callExpr_func(r).
   { l.basic.id = r.basic.id; }
callExpr(l) ::= callExpr_method(r).
   { l.basic.id = r.basic.id; }
callExpr_func(l) ::= funcExpr(e) call_args.
   { l.basic.id = _Tcp1_Fexpr_pop_func_3(e.basic.id, e.basic.id2, 0); }
callExpr_func(l) ::= funcExpr_angle(e) call_args_angle.
   { l.basic.id = _Tcp1_Fexpr_pop_func_3(e.basic.id, e.basic.id2, 1); }
callExpr_method(l) ::= methodExpr(e) call_args.
   { l.basic.id = _Tcp1_Fexpr_pop_method_3(e.basic.id, e.basic.id2, 0); }
callExpr_method(l) ::= methodExpr_angle(e) call_args_angle.
   { l.basic.id = _Tcp1_Fexpr_pop_method_3(e.basic.id, e.basic.id2, 1); }
expr2stmt_base(l) ::= callExpr(r).
   { l.basic.id = r.basic.id; }
metaCallExpr_func(l) ::= metaFuncExpr(e) metaCall_args_optional.
   { l.basic.id = _Tcp1_Fexpr_pop_metafunc_2(e.basic.id, e.basic.id2); }
metaCallExpr_method(l) ::= metaMethodExpr(e) metaCall_args_optional.
   { l.basic.id = _Tcp1_Fexpr_pop_metamethod_2(e.basic.id, e.basic.id2); }
metaCallExpr(l) ::= metaCallExpr_func(r).
   { l.basic.id = r.basic.id; }
metaCallExpr(l) ::= metaCallExpr_method(r).
   { l.basic.id = r.basic.id; }
assign_type(l) ::= SPACE_COLON_EQUAL SPACE.
   { l.basic.id = 1; }
assign_type(l) ::= SPACE_PLUS_EQUAL SPACE.
   { l.basic.id = 2; }
assign_type(l) ::= SPACE_MINUS_EQUAL SPACE.
   { l.basic.id = 3; }
assign_type(l) ::= SPACE_MUL_EQUAL SPACE.
   { l.basic.id = 4; }
assign_type(l) ::= SPACE_DIV_EQUAL SPACE.
   { l.basic.id = 5; }
assign_type(l) ::= SPACE_LSHIFT_EQUAL SPACE.
   { l.basic.id = 6; }
assign_type(l) ::= SPACE_RSHIFT_EQUAL SPACE.
   { l.basic.id = 7; }
assign_type(l) ::= SPACE_AND_EQUAL SPACE.
   { l.basic.id = 8; }
assign_type(l) ::= SPACE_OR_EQUAL SPACE.
   { l.basic.id = 9; }
assign_type(l) ::= SPACE_XOR_EQUAL SPACE.
   { l.basic.id = 10; }
assign_type1(l) ::= SPACE_EQUAL SPACE.
   { l.basic.id = 0; }
assign_type1(l) ::= assign_type(r).
   { l.basic.id = r.basic.id; }
assign_type2(l) ::= SPACE_EQUAL SPACE.
   { l.basic.id = 0; }
assign_type2(l) ::= assign_type(r).
   { l.basic.id = r.basic.id; }
assignExpr1(l) ::= value(left) assign_type1(type) expr(right).
   { l.basic.id = _Tcp1_Fexpr_assign_3(left.basic.id, right.basic.id, type.basic.id); }
assignExpr2(l) ::= value(left) assign_type2(type) expr(right).
   { l.basic.id = _Tcp1_Fexpr_assign_3(left.basic.id, right.basic.id, type.basic.id); }
expr2stmt_base(l) ::= expr_str(r).
   { l.basic.id = r.basic.id; }
expr2stmt_base(l) ::= incExpr(r).
   { l.basic.id = r.basic.id; }
expr2stmt_base(l) ::= decExpr(r).
   { l.basic.id = r.basic.id; }
expr2stmt_base(l) ::= assignExpr2(r).
   { l.basic.id = r.basic.id; }
expr2stmt_base(l) ::= exprs(r).
   { l.basic.id = r.basic.id; }
expr2stmt ::= begin_pos(begin) expr2stmt_base(e) end_pos(end).
   { _Tcp1_Fexpr2stmt_5(e.basic.id, begin.basic.row, begin.basic.col, end.basic.row, end.basic.col); }
stmt ::= begin_pos(begin) metaCallExpr(e) end_pos(end).
   { _Tcp1_Fexpr2stmt_5(e.basic.id, begin.basic.row, begin.basic.col, end.basic.row, end.basic.col); }
expr(l) ::= fastCastExpr(r).
   { l.basic.id = r.basic.id; }
expr(l) ::= negVal(r).
   { l.basic.id = r.basic.id; }
expr(l) ::= notExpr(r).
   { l.basic.id = r.basic.id; }
expr(l) ::= refExpr(r).
   { l.basic.id = r.basic.id; }
expr(l) ::= valueonly(r).
   { l.basic.id = r.basic.id; }
expr(l) ::= opExpr(r).
   { l.basic.id = r.basic.id; }
expr(l) ::= exprs(r).
   { l.basic.id = r.basic.id; }
expr(l) ::= expr_and_c(r).
   { l.basic.id = r.basic.id; }
expr(l) ::= expr_or_c(r).
   { l.basic.id = r.basic.id; }
exprs(l) ::= expr_and(r).
   { l.basic.id = r.basic.id; }
exprs(l) ::= expr_or(r).
   { l.basic.id = r.basic.id; }

sizeOfTypeExpr(l) ::= at(at) OPEN_BRACKET USZ CLOSE_BRACKET.
   { l.basic.id = _Tcp1_Fexpr_size_of_type_1(at.basic.id); }

fastCastExpr(l) ::= value4cast(e) at(at).
   { l.basic.id = _Tcp1_Fexpr_cast_fast_2(e.basic.id, at.basic.id); }
fastCastExpr(l) ::= value4cast(e) BASE.
   { l.basic.id = _Tcp1_Fexpr_cast_fast_2(e.basic.id, -1); }

negVal(l) ::= MINUS value4fix(e).
   { l.basic.id = _Tcp1_Fexpr_unary_2(e.basic.id, 0); }

incExpr(l) ::= value(e) PLUS PLUS.
   { l.basic.id = _Tcp1_Fexpr_unary_2(e.basic.id, 1); }

decExpr(l) ::= value(e) MINUS MINUS.
   { l.basic.id = _Tcp1_Fexpr_unary_2(e.basic.id, 2); }

notExpr(l) ::= EXCLAMATION value(e).
   { l.basic.id = _Tcp1_Fexpr_unary_2(e.basic.id, 3); }

refExpr(l) ::= AMPERSAND value(e).
   { l.basic.id = _Tcp1_Fexpr_ref_1(e.basic.id); }
/*
  expr
  { $$.v[0] = $expr; $$.c = 1; }
| indexExpr_exprs exprEnd expr
  { $$.v[$$.c++] = $expr; }
*/

indexExpr_exprs(l) ::= expr(e).
   { l.index.v[0] = e.basic.id; l.index.c = 1; }
indexExpr_exprs(l) ::= indexExpr_exprs COMMA_SPACE expr(e).
   { l.index.v[l.index.c ++] = e.basic.id; }
indexExpr(l) ::= valueonly(r) open_bracket_or_space indexExpr_exprs(e) close_bracket_or_comma.
   { l.basic.id = _Tcp1_Fexpr_index_3(r.basic.id, e.index.v, e.index.c); }

stmt ::= stmt_loop.
stmt_loop_begin ::= LOOP.
   { _Tcp1_Fstmt_loop_begin_0(); }
stmt_loop_begin2 ::= LOOP_WITH_SEMICOLON.
   { _Tcp1_Fstmt_loop_begin_0(); }
/* loop_expr_val(l) ::= open_parenthesis_or_space CLOSE_PARENTHESIS.
   { l.basic.id = -1; }
loop_expr_val(l) ::= open_parenthesis_or_space expr(e) close_parenthesis_or_space.
   { l.basic.id = e.basic.id; } */
loop_expr0 ::= begin_pos(begin) expr(e) end_pos(end).
   { _Tcp1_Fstmt_loop_set_6(e.basic.id, begin.basic.row, begin.basic.col, end.basic.row, end.basic.col, 0); }
/* loop_expr1 ::= begin_pos(begin) loop_expr_val(e) end_pos(end) loop_continue_begin(c) SPACE loop_continue_stmts loop_continue_end.
   { _Tcp1_Fstmt_loop_set_6(e.basic.id, begin.basic.row, begin.basic.col, end.basic.row, end.basic.col, c.pointer); } */
loop_continue_begin(l) ::= .
   { l.pointer = _Tcp1_Fstmt_space_begin_detach_0(); } 
loop_continue_end ::= .
   { _Tcp1_Fstmt_space_end_0(); }
loop_continue_stmts ::= stmts_brace.
loop_continue_stmts ::= stmts_expr SEMICOLON.
loop_continue_stmts ::= stmts_expr.
loop_forever ::= .
   { _Tcp1_Fstmt_loop_set_6(-1, 0, 0, 0, 0, 0); }

loop_expr2 ::= SPACE begin_pos(begin) expr(e) end_pos(end) SEMICOLON loop_continue_begin(c) SPACE loop_continue_stmts loop_continue_end.
   { _Tcp1_Fstmt_loop_set_6(e.basic.id, begin.basic.row, begin.basic.col, end.basic.row, end.basic.col, c.pointer); }
loop_expr2 ::= SEMICOLON loop_continue_begin(c) SPACE loop_continue_stmts loop_continue_end.
   { _Tcp1_Fstmt_loop_set_6(-1, 0, 0, 0, 0, c.pointer); }
loop_expr2 ::= SPACE begin_pos(begin) expr(e) end_pos(end).
   { _Tcp1_Fstmt_loop_set_6(e.basic.id, begin.basic.row, begin.basic.col, end.basic.row, end.basic.col, 0); }
loop_expr2 ::= SPACE begin_pos(begin) expr(e) end_pos(end) SEMICOLON.
   { _Tcp1_Fstmt_loop_set_6(e.basic.id, begin.basic.row, begin.basic.col, end.basic.row, end.basic.col, 0); }
loop_expr2 ::= loop_forever.
stmt_loop ::= stmt_loop_begin SPACE_THEN_OPEN_CURLY_BRACE loop_forever stmts_optional2.
   { _Tcp1_Fstmt_loop_end_0(); }
stmt_loop ::= stmt_loop_begin SPACE loop_expr0 SPACE_THEN_OPEN_CURLY_BRACE stmts_optional2.
   { _Tcp1_Fstmt_loop_end_0(); }
/* stmt_loop ::= stmt_loop_begin2 SPACE loop_expr1 SPACE_THEN_OPEN_CURLY_BRACE stmts_optional2.
   { _Tcp1_Fstmt_loop_end_0(); } */
stmt_loop ::= stmt_loop_begin2 SEMICOLON loop_expr2 SPACE_THEN_OPEN_CURLY_BRACE stmts_optional2.
   { _Tcp1_Fstmt_loop_end_0(); }
stmt_loop ::= stmt_loop_begin2 SPACE stmt_lvars_no_begin SEMICOLON loop_expr2 SPACE_THEN_OPEN_CURLY_BRACE stmts_optional2.
   { _Tcp1_Fstmt_loop_end_0(); }

stmt ::= stmt_if_chain.
   { _Tcp1_Fstmt_if_end_ifs_0(); }
stmt ::= stmt_if_chain stmt_else.
   { _Tcp1_Fstmt_if_end_ifs_0(); }
stmt_if_begin ::= IF SPACE.
   { _Tcp1_Fstmt_if_begin_0(); }
stmt_elif_begin ::= SPACE_ELIF SPACE.
   { _Tcp1_Fstmt_elif_begin_0(); }
stmt_else_set ::= SPACE_ELSE SPACE_THEN_OPEN_CURLY_BRACE.
   { _Tcp1_Fstmt_else_set_0(); }
if_expr ::= begin_pos(begin) expr(e) end_pos(end).
   { _Tcp1_Fstmt_if_set_5(e.basic.id, begin.basic.row, begin.basic.col, end.basic.row, end.basic.col); }
stmt_if ::= stmt_if_begin if_expr SPACE_THEN_OPEN_CURLY_BRACE stmts_optional2.
   { _Tcp1_Fstmt_if_end_0(); }
elif_expr ::= begin_pos(begin) expr(e) end_pos(end).
   { _Tcp1_Fstmt_elif_set_5(e.basic.id, begin.basic.row, begin.basic.col, end.basic.row, end.basic.col); }
stmt_elif ::= stmt_elif_begin elif_expr SPACE_THEN_OPEN_CURLY_BRACE stmts_optional2.
   { _Tcp1_Fstmt_elif_end_0(); }
stmt_else ::= stmt_else_set stmts_optional2.
   { _Tcp1_Fstmt_else_end_0(); }
stmt_if_chain ::= stmt_if.
stmt_if_chain ::= stmt_if_chain stmt_elif.

stmt ::= stmt_switch.
stmt_switch_begin ::= SWITCH.
   { _Tcp1_Fstmt_switch_begin_0(); }
switch_expr ::= begin_pos(begin) SPACE expr(e) end_pos(end).
   { _Tcp1_Fstmt_switch_set_6(e.basic.id, begin.basic.row, begin.basic.col, end.basic.row, end.basic.col, -1); }
switch_expr ::= begin_pos(begin) DOT callExpr_func(cases) SPACE expr(e) end_pos(end).
   { _Tcp1_Fstmt_switch_set_6(e.basic.id, begin.basic.row, begin.basic.col, end.basic.row, end.basic.col, cases.basic.id); }
switch_case_expr ::= expr(e).
   { _Tcp1_Fstmt_switch_expr_add_1(e.basic.id); }
switch_case_exprs ::= switch_case_expr.
switch_case_exprs ::= switch_case_exprs COMMA_SPACE switch_case_expr.
switch_case_fall(l) ::= .
   { l.basic.id = 0; }
switch_case_fall(l) ::= SPACE_AT_FALL_THROUGH.
   { l.basic.id = 1; }
switch_case_paren_or_expr ::= switch_case_exprs.
switch_case_expr_end ::= CASE(begin) SPACE switch_case_paren_or_expr switch_case_fall(fall) end_pos(end).
   { _Tcp1_Fstmt_switch_case_begin_5(begin.basic.row, begin.basic.col, end.basic.row, end.basic.col, fall.basic.id); }
switch_case ::= switch_case_expr_end SPACE_THEN_OPEN_CURLY_BRACE stmts_optional2.
   { _Tcp1_Fstmt_switch_case_end_0(); }
switch_default_begin ::= DEFAULT(begin) switch_case_fall(fall) end_pos(end).
   { _Tcp1_Fstmt_switch_default_begin_5(begin.basic.row, begin.basic.col, end.basic.row, end.basic.col, fall.basic.id); }
switch_case ::= switch_default_begin SPACE_THEN_OPEN_CURLY_BRACE stmts_optional2.
   { _Tcp1_Fstmt_switch_default_end_0(); }
switch_cases ::= switch_case.
switch_cases ::= switch_cases SPACE switch_case.
stmt_switch ::= stmt_switch_begin switch_expr SPACE_THEN_OPEN_CURLY_BRACE OPEN_CURLY_BRACE SPACE switch_cases SPACE_CLOSE_CURLY_BRACE.
   { _Tcp1_Fstmt_switch_end_0(); }
stmt_switch ::= stmt_switch_begin switch_expr SPACE_THEN_OPEN_CURLY_BRACE OPEN_CURLY_BRACE SPACE_CLOSE_CURLY_BRACE.
   { _Tcp1_Fstmt_switch_end_0(); }

stmt_expr ::= stmt_continue.
stmt_continue ::= begin_pos(begin) CONTINUE end_pos(end).
   { _Tcp1_Fstmt_continue_5(-1, begin.basic.row, begin.basic.col, end.basic.row, end.basic.col); }

stmt_expr ::= stmt_break.
stmt_break ::= begin_pos(begin) BREAK end_pos(end).
   { _Tcp1_Fstmt_break_5(-1, begin.basic.row, begin.basic.col, end.basic.row, end.basic.col); }

stmt_expr ::= stmt_return.
stmt_return ::= begin_pos(begin) RETURN end_pos(end).
   { _Tcp1_Fstmt_return_5(-1, begin.basic.row, begin.basic.col, end.basic.row, end.basic.col); }
stmt_return ::= begin_pos(begin) RETURN SPACE expr(e) end_pos(end).
   { _Tcp1_Fstmt_return_5(e.basic.id, begin.basic.row, begin.basic.col, end.basic.row, end.basic.col); }

typeAndInfo ::= expr_type_apply typeInfo_optional.
typeAndInfo_optional ::= typeAndInfo.
typeAndInfo_optional ::= expr_type_none typeInfo_none.

stmt_expr ::= stmt_lvars.
stmt_lvars ::= decl_lvar_begin lvar_list(end).
   { _Tcp1_Fstmt_lvar_end_2(end.basic.row, end.basic.col); }
stmt_lvars_no_begin ::= lvar_list(end).
   { _Tcp1_Fstmt_lvar_end_2(end.basic.row, end.basic.col); }
decl_lvar ::= ID(var) typeAndInfo_optional SPACE_EQUAL SPACE expr(e).
   { _Tcp1_Fstmt_lvar_add_4(var.basic.id, e.basic.id, var.basic.row, var.basic.col); }
decl_lvar ::= ID(var) typeAndInfo_optional SPACE_EQUAL SPACE QUESTION.
   { _Tcp1_Fstmt_lvar_add_4(var.basic.id, -1, var.basic.row, var.basic.col); }
decl_lvar ::= ID(var) typeAndInfo_optional.
   { _Tcp1_Fstmt_lvar_add_4(var.basic.id, -2, var.basic.row, var.basic.col); }
decl_lvars ::= decl_lvar.
decl_lvars ::= decl_lvars COMMA_SPACE decl_lvar.
lvar_list(l) ::= .
   { l.basic.row = _Tcp1_Grow; l.basic.col = _Tcp1_Gcol; }
lvar_list(l) ::= decl_lvars.
   { l.basic.row = _Tcp1_Grow; l.basic.col = _Tcp1_Gcol; }
decl_lvar_begin ::= VAR SPACE. // OPEN_CURLY_BRACE_PLUS_OR_SPACE.

decl_var_attr ::= SPACE_AT_REAL_NAME_STR(e).
   { _Tcp1_Fdecl_var_attr_real_name_1(e.basic.id); }
decl_var_attr ::= SPACE_AT_REAL_NAME.
   { _Tcp1_Fdecl_var_attr_real_name_1(-1); }
decl_var_attr ::= SPACE_AT_EXTERN.
   { _Tcp1_Fdecl_var_attr_extern_0(); }
decl_var_attr ::= SPACE_AT_NO_DECL.
   { _Tcp1_Fdecl_var_attr_no_decl_0(); }
decl_var_attr ::= SPACE_AT_NO_DECL_STR(e).
   { _Tcp1_Fdecl_var_attr_no_decl_0(); _Tcp1_Fdecl_var_attr_real_name_1(e.basic.id); }
decl_var_attrs_list ::= decl_var_attr.
decl_var_attrs_list ::= decl_var_attrs_list decl_var_attr.
decl_var_attrs_optional ::= .
decl_var_attrs_optional ::= decl_var_attrs_list.

decl_func ::= func_decl SEMICOLON. // CLOSE_CURLY_BRACE.
    { _Tcp1_Ffunc_header_end_0(); }
stmt_brace ::= stmt.
stmt_expr ::= expr2stmt.
stmts_brace ::= stmt_brace.
stmts_brace ::= stmts_expr scolon_space stmt_brace.
stmts_brace ::= stmts_brace SPACE stmt_brace.
stmts_expr ::= stmt_expr.
stmts_expr ::= stmts_expr scolon_space stmt_expr.
stmts_expr ::= stmts_brace SPACE stmt_expr.
/* stmts_optional ::= SPACE_CLOSE_CURLY_BRACE.
stmts_optional ::= SPACE stmts_brace close_curly_brace_or_space.
stmts_optional ::= SPACE stmts_expr close_curly_brace_or_scolon. */
stmts_optional2 ::= OPEN_CURLY_BRACE SPACE_CLOSE_CURLY_BRACE.
stmts_optional2 ::= OPEN_CURLY_BRACE SPACE stmts_brace SPACE_CLOSE_CURLY_BRACE.
stmts_optional2 ::= OPEN_CURLY_BRACE SPACE stmts_expr close_curly_brace_or_scolon.
/* stmts_optional3 ::= CLOSE_CURLY_BRACE.
stmts_optional3 ::= stmts_brace close_curly_brace_or_space.
stmts_optional3 ::= stmts_expr close_curly_brace_or_scolon. */
decl_struct_attr ::= SPACE_AT_NO_DECL.
   { _Tcp1_Fstruct_attr_no_decl_0(); }
decl_struct_attr ::= SPACE_AT_NO_DECL_STR(e).
   { _Tcp1_Fstruct_attr_no_decl_0(); _Tcp1_Fstruct_attr_real_name_1(e.basic.id); }
decl_struct_attr ::= SPACE_AT_REAL_NAME_STR(e).
   { _Tcp1_Fstruct_attr_real_name_1(e.basic.id); }
decl_struct_attr ::= SPACE_AT_REAL_NAME.
   { _Tcp1_Fstruct_attr_real_name_1(-1); }
decl_struct_attr ::= SPACE_AT_ALIGNED OPEN_PARENTHESIS NUM_I32(n) CLOSE_PARENTHESIS.
   { _Tcp1_Fstruct_attr_aligned_1(n.basic.id); }
/* decl_struct_attr ::= SPACE_AT_UNION.
   { _Tcp1_Fstruct_attr_union_0(); } */
decl_struct_attrs_list ::= decl_struct_attr.
decl_struct_attrs_list ::= decl_struct_attrs_list decl_struct_attr.
decl_struct_attrs_optional ::= end_pos(end).
   { _Tcp1_Fdecl_struct_end_2(end.basic.row, end.basic.col); }
decl_struct_attrs_optional ::= decl_struct_attrs_list end_pos(end).
   { _Tcp1_Fdecl_struct_end_2(end.basic.row, end.basic.col); }
decl_func ::= func_decl SPACE_THEN_OPEN_CURLY_BRACE stmts_optional2.
   { _Tcp1_Ffunc_body_end_0(); }
/* decl_func ::= func_decl_inline stmts_optional.
   { _Tcp1_Ffunc_body_end_1(true); } */
decl_struct_close_or_at ::= SEMICOLON.
   { _Tcp1_Fdecl_at_end_0(); }
decl_struct_close_or_at ::= SPACE_THEN_OPEN_CURLY_BRACE OPEN_CURLY_BRACE SPACE decls SPACE_CLOSE_CURLY_BRACE.
   { _Tcp1_Fdecl_at_end_0(); }
decl_struct_close_or_at ::= SPACE_THEN_OPEN_CURLY_BRACE OPEN_CURLY_BRACE SPACE_CLOSE_CURLY_BRACE.
   { _Tcp1_Fdecl_at_end_0(); }
decl_struct ::= struct_decl_begin OPEN_BRACKET CLOSE_BRACKET
   decl_struct_attrs_optional decl_struct_close_or_at.
decl_struct ::= struct_decl_begin OPEN_BRACKET SPACE_CLOSE_BRACKET
   decl_struct_attrs_optional decl_struct_close_or_at.
decl_struct ::= struct_decl_begin open_bracket_or_space struct_fvars close_bracket_or_comma
   decl_struct_attrs_optional decl_struct_close_or_at.
decl_enum_close_or_at ::= SEMICOLON.
   { _Tcp1_Fdecl_at_end_0(); }
decl_enum_close_or_at ::= SPACE_THEN_OPEN_CURLY_BRACE OPEN_CURLY_BRACE SPACE decls SPACE_CLOSE_CURLY_BRACE.
   { _Tcp1_Fdecl_at_end_0(); }
decl_enum_close_or_at ::= SPACE_THEN_OPEN_CURLY_BRACE OPEN_CURLY_BRACE SPACE_CLOSE_CURLY_BRACE.
   { _Tcp1_Fdecl_at_end_0(); }
enum_base_begin ::= .
   { _Tcp1_Fenum_base_begin_0(); }
decl_enum_attr ::= SPACE_AT_SOA_FIELD OPEN_PARENTHESIS AT(a) DOT ID(i) DOT CLOSE_PARENTHESIS.
   { _Tcp1_Fenum_attr_soa_field_2(a.basic.id, i.basic.id); }
decl_enum_attr ::= SPACE_AT_NO_DECL.
   { _Tcp1_Fenum_attr_no_decl_0(); }
decl_enum_attr ::= SPACE_AT_NO_DECL_STR(e).
   { _Tcp1_Fenum_attr_no_decl_0(); _Tcp1_Fenum_attr_real_name_1(e.basic.id); }
decl_enum_attr ::= SPACE_AT_REAL_NAME.
   { _Tcp1_Fenum_attr_real_name_1(-1); }
decl_enum_attr ::= SPACE_AT_REAL_NAME_STR(s).
   { _Tcp1_Fenum_attr_real_name_1(s.basic.id); }
decl_enum_attr ::= SPACE_AT_SOA_FIELD OPEN_PARENTHESIS DOT ID(i) DOT CLOSE_PARENTHESIS.
   { _Tcp1_Fenum_attr_soa_field_2(-1, i.basic.id); }
decl_enum_attrs ::= decl_enum_attr.
decl_enum_attrs ::= decl_enum_attrs decl_enum_attr.
decl_enum_attrs_optional ::= .
decl_enum_attrs_optional ::= decl_enum_attrs.
enum_base_end ::= at(at) decl_enum_attrs_optional end_pos(end).
   { _Tcp1_Fdecl_enum_end_3(at.basic.id, end.basic.row, end.basic.col); }
decl_enum ::= enum_decl_begin OPEN_BRACKET CLOSE_BRACKET enum_base_begin enum_base_end
   decl_enum_close_or_at.
decl_enum ::= enum_decl_begin OPEN_BRACKET SPACE_CLOSE_BRACKET enum_base_begin enum_base_end
   decl_enum_close_or_at.
decl_enum ::= enum_decl_begin open_bracket_or_space enum_cvars close_bracket_or_comma enum_base_begin enum_base_end
   decl_enum_close_or_at.
decl_gvar ::= fvar_decl expr_type_apply typeInfo_optional decl_var_attrs_optional.
   { _Tcp1_Fdecl_var_as_gvar_0(); }
decl_gvar_list ::= decl_gvar.
decl_gvar_list ::= decl_gvar_list decl_gvar.
//decl_gvars ::= OPEN_CURLY_BRACE_Tcp1_GVAR_SPACE CLOSE_CURLY_BRACE.
decl_gvars ::= VAR SPACE decl_gvar_list SEMICOLON.
