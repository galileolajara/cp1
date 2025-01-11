%name glcParse
%token_prefix GLC_TOKEN_

%token_type {union glc_token}

%left PLUS MINUS. 

%syntax_error{
   int n = YYNTOKEN;
   bool first = true;
   for (int i = 0; i < n; ++i) {
      int a = yy_find_shift_action((YYCODETYPE)i, yypParser->yytos->stateno);
      if (a != YY_ERROR_ACTION) {
         if (first) {
            first = false;
            printf("%s:%u:%u: syntax error, expected token: #%s", input_path, _Grow, _Gcol, _Nglc_Ptoken_name_1(i));
         } else {
            printf(", #%s", _Nglc_Ptoken_name_1(i));
         }
      }
   }
   if (!first) {
      printf("\n");
   }
   exit(EXIT_FAILURE);
   return;
}
   
glc ::= decls space_or_end.
glc ::= SPACE decls space_or_end.
glc ::= space_or_end.

begin_pos(t) ::= .
   { t.basic.row = _Grow; t.basic.col = _Gcol; }
end_pos(t) ::= .
   { t.basic.row = _Grow; t.basic.col = _Gcol - 1; }

// NOTE BEGIN: Order of declaration of the following must not be changed:
func_decl_begin ::= ID_LPAREN(name).
   { _Nglc_Pdecl_func_begin_3(name.basic.id, name.basic.row, name.basic.col); }
/* at_name ::= ID_MODULO(e).
   { _Nglc_Pat_push_4(e.basic.id, 0, e.basic.row, e.basic.col); } */
at_name ::= ID_COLON(e).
   { _Nglc_Pat_push_4(e.basic.id, 1, e.basic.row, e.basic.col); }
/* at_name ::= ID_BSLASH(e).
   { _Nglc_Pat_push_4(e.basic.id, 2, e.basic.row, e.basic.col); } */
at_alias ::= ID_QUOTE(e).
   { _Nglc_Pat_alias_3(e.basic.id, e.basic.row, e.basic.col); }
enum_cvar_begin ::= ID_HASH(e).
   { _Nglc_Penum_add_cvar_3(e.basic.id, e.basic.row, e.basic.col); }
enum_cvar_begin_decl ::= ID_HASH(e) typeAndInfo_optional.
   { _Nglc_Pdecl_add_cvar_3(e.basic.id, e.basic.row, e.basic.col); }
struct_decl_begin ::= LCBRACE(pos) ID_COLON(name).
   { _Nglc_Pdecl_at_begin_struct_3(name.basic.id, pos.basic.row, pos.basic.col); }
fvar_decl_name ::= ID(name).
   { _Nglc_Pdecl_var_begin_3(name.basic.id, name.basic.row, name.basic.col); }
lvar_decl_name ::= ID(name).
   { _Nglc_Pdecl_var_begin_3(name.basic.id, name.basic.row, name.basic.col); }
// NOTE END

cvar_attr ::= SPACE_AT_REAL_NAME_STR(e).
   { _Nglc_Pcvar_attr_real_name_1(e.basic.id); }
cvar_attr ::= SPACE_AT_NO_DECL.
   { _Nglc_Pcvar_attr_no_decl_0(); }
cvar_attrs ::= cvar_attr.
cvar_attrs ::= cvar_attrs cvar_attr.
cvar_attrs_optional ::= .
cvar_attrs_optional ::= cvar_attrs.
enum_cvar ::= enum_cvar_begin cvar_attrs_optional.
enum_cvar ::= enum_cvar_begin cvar_attrs_optional SPACE_EQUAL_SPACE expr(set).
   { _Nglc_Penum_set_cvar_expr_1(set.basic.id); }
enum_cvar_decl ::= enum_cvar_begin_decl cvar_attrs_optional.
enum_cvar_decl ::= enum_cvar_begin_decl cvar_attrs_optional SPACE_EQUAL_SPACE expr(set).
   { _Nglc_Penum_set_cvar_expr_1(set.basic.id); }
enum_decl_begin ::= LCBRACE(pos) ID_COLON(name).
   { _Nglc_Pdecl_at_begin_enum_3(name.basic.id, pos.basic.row, pos.basic.col); }

decl_include ::= INCLUDE(e).
   { _Nglc_Pdecl_include_begin_3(e.basic.id, e.basic.row, e.basic.col); }
decl ::= decl_include SPACE decls SPACE_RCBRACE.
   { _Nglc_Pdecl_include_end_0(); }
decl ::= decl_include SPACE_RCBRACE.
   { _Nglc_Pdecl_include_end_0(); }

at_root ::= QUOTE.
   { _Nglc_Pat_root_0(); }
at_graves_count(l) ::= GRAVE(e).
   { l.basic.id = 1; l.basic.row = e.basic.row; l.basic.col = e.basic.col; }
at_graves_count(l) ::= at_graves_count(r) GRAVE.
   { l.basic.id = r.basic.id + 1; l.basic.row = r.basic.row; l.basic.col = r.basic.col; }
at_graves ::= at_graves_count(e).
   { _Nglc_Pat_graves_3(e.basic.id, e.basic.row, e.basic.col); }
at_names ::= at_alias.
at_names ::= at_root at_name.
at_names ::= at_graves at_name.
at_begin ::= .
   { _Nglc_Pat_begin_relative_0(); }
at_names ::= at_begin at_name.
at_names ::= at_names at_name.
at(l) ::= type_basic_id(r).
   { l.basic.id = _Nglc_Pat_basic_type_1(r.basic.id); }
at(l) ::= at_names.
   { l.basic.id = _Nglc_Pat_done_0(); }
at(l) ::= at_root.
   { l.basic.id = _Nglc_Pat_done_0(); }
at(l) ::= at_graves.
   { l.basic.id = _Nglc_Pat_done_0(); }
/* decl_at_name ::= ID_MODULO(e).
   { _Nglc_Pdecl_at_add_2(e.basic.id, 0); } */
decl_at_name ::= ID_COLON(e).
   { _Nglc_Pdecl_at_add_2(e.basic.id, 1); }
decl_at_name ::= ID_BSLASH(e).
   { _Nglc_Pdecl_at_add_2(e.basic.id, 2); }
decl_at_begin_at ::= .
   { _Nglc_Pat_begin_0(); }
decl_at_names ::= decl_at_begin_at decl_at_name.
decl_at_names ::= decl_at_names decl_at_name.
decl_at_namespace ::= decl_at_names.
decl_at_namespace ::= type_basic_id(e).
   { _Nglc_Pdecl_at_basic_1(e.basic.id); }
decl_at_begin_begin(l) ::= LCBRACE_AT_LPAREN(r).
   { _Nglc_Pat_begin_relative_pause_0(); l.basic.row = r.basic.row; l.basic.col = r.basic.col; }
decl_at_begin_end ::= RPAREN.
   { _Nglc_Pat_begin_relative_resume_0(); }
decl_at_begin ::= decl_at_begin_begin(pos) decl_at_namespace decl_at_begin_end.
   { _Nglc_Pdecl_at_begin_2(pos.basic.row, pos.basic.col); }
decl_at ::= decl_at_begin SPACE decls SPACE_RCBRACE.
   { _Nglc_Pdecl_at_end_0(); }
decl_at ::= decl_at_begin SPACE_RCBRACE.
   { _Nglc_Pdecl_at_end_0(); }
decl ::= decl_at.

decl_cvar ::= LCBRACE_CVAR_SPACE enum_cvars_decl rcbrace_or_comma.
decl_cvar ::= LCBRACE_CVAR_SPACE RCBRACE.
decl ::= decl_cvar.

space_or_end ::= SPACE END.
space_or_end ::= END.

decl ::= decl_func.
decl ::= decl_struct.
decl ::= decl_enum.
decl ::= decl_gvars.
decl_alias_begin ::= LCBRACE_USING_SPACE.
   { _Nglc_Pat_begin_relative_pause_0(); }
decl_alias_end ::= RCBRACE.
   { _Nglc_Pat_begin_relative_resume_0(); }
decl ::= decl_alias_begin ID_QUOTE(short) SPACE_EQUAL_SPACE at(long) decl_alias_end.
   { _Nglc_Pdecl_alias_4(short.basic.id, long.basic.id, short.basic.row, short.basic.col); }
decls ::= decl.
decls ::= decls SPACE decl.

lparen_or_space(l) ::= LPAREN(r).
   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; }
lparen_or_space(l) ::= LPAREN_SPACE(r).
   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; }
rparen_or_space(l) ::= RPAREN(r).
   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; }
rparen_or_space(l) ::= SPACE_RPAREN(r).
   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; }
rparen_or_comma(l) ::= rparen_or_space(r).
   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; }
rparen_or_comma(l) ::= COMMA_SPACE_RPAREN(r).
   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; }

rcbrace_or_space(l) ::= RCBRACE(r).
   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; }
rcbrace_or_space(l) ::= SPACE_RCBRACE(r).
   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; }
rcbrace_or_comma(l) ::= RCBRACE(r).
   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; }
rcbrace_or_comma(l) ::= SPACE_RCBRACE(r).
   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; }
rcbrace_or_comma(l) ::= COMMA_SPACE_RCBRACE(r).
   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; }
rcbrace_or_scolon(l) ::= RCBRACE(r).
   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; }
rcbrace_or_scolon(l) ::= SPACE_RCBRACE(r).
   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; }
rcbrace_or_scolon(l) ::= SCOLON_SPACE_RCBRACE(r).
   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; }

lbracket_or_space(l) ::= LBRACKET(r).
   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; }
lbracket_or_space(l) ::= LBRACKET_SPACE(r).
   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; }
/* rbracket_or_space(l) ::= RBRACKET(r).
   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; }
rbracket_or_space(l) ::= SPACE_RBRACKET(r).
   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; } */
rbracket_or_comma(l) ::= RBRACKET(r).
   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; }
rbracket_or_comma(l) ::= SPACE_RBRACKET(r).
   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; }
rbracket_or_comma(l) ::= COMMA_SPACE_RBRACKET(r).
   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; }

lvar_decl(l) ::= lvar_decl_name(r).
   { _Nglc_Pdecl_var_end_0(); l.basic.row = r.basic.row; l.basic.col = r.basic.col; }
farg ::= lvar_decl(e) typeAndInfo_optional.
   { _Nglc_Pdecl_var_as_farg_2(e.basic.row, e.basic.col); }
expr_type_this_apply ::= GRAVE_THIS.
   { _Nglc_Pdecl_var_this_0(); }
farg ::= lvar_decl expr_type_this_apply typeInfo_optional.
   { _Nglc_Pdecl_var_as_this_0(); }
expr_type_none ::= .
   { _Nglc_Pdecl_var_type_1(-1); }
expr_type_apply ::= at(r).
   { _Nglc_Pdecl_var_type_1(r.basic.id); }
farg_list ::= farg.
farg_list ::= farg_list COMMA_SPACE farg.
fargs ::= lparen_or_space RPAREN.
fargs ::= lparen_or_space farg_list rparen_or_comma.
farg_next_group ::= lparen_or_space.
   { _Nglc_Pfarg_next_group_0(); }
fargs ::= fargs farg_next_group farg_list rparen_or_comma.
fargs ::= fargs farg_next_group RPAREN.
func_attr ::= SPACE_AT_MAIN.
   { _Nglc_Pfunc_attr_main_0(); }
func_attr ::= SPACE_AT_CASE DOT ID_LPAREN(e) LPAREN RPAREN.
   { _Nglc_Pfunc_attr_case_1(e.basic.id); }
func_attr ::= SPACE_AT_PROCESS.
   { _Nglc_Pfunc_attr_process_0(); }
func_attr ::= SPACE_AT_INLINE.
   { _Nglc_Pfunc_attr_inline_0(); }
func_attr ::= SPACE_AT_CGL_NAME.
   { _Nglc_Pfunc_attr_cgl_name_0(); }
func_attr ::= SPACE_AT_DECL LPAREN STRING RPAREN.
   { _Nglc_Pfunc_attr_decl_0(); }
func_attr ::= SPACE_AT_VAR_ARGS.
   { _Nglc_Pfunc_attr_var_args_0(); }
func_attr ::= SPACE_AT_NO_DECL.
   { _Nglc_Pfunc_attr_no_decl_0(); }
func_attr ::= SPACE_AT_NO_BODY.
   { _Nglc_Pfunc_attr_no_body_0(); }
func_attr ::= SPACE_AT_REAL_NAME_STR(e).
   { _Nglc_Pfunc_attr_real_name_1(e.basic.id); }
func_attr ::= SPACE_AT_REAL_NAME.
   { _Nglc_Pfunc_attr_real_name_1(-1); }
/* func_attrs(l) ::= LCBRACE_SPACE(r).
   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; }
func_attrs(l) ::= func_attr LCBRACE_SPACE(r).
   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; }
func_attrs_base ::= func_attr.
func_attrs_base ::= func_attrs_base func_attr.
func_attrs(l) ::= func_attrs_base func_attr LCBRACE_SPACE(r). */
func_attrs ::= func_attr.
func_attrs ::= func_attrs func_attr.
/*   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; } */
type_basic_id(l) ::= GRAVE_REF.
   { l.basic.id = 2; }
type_basic_id(l) ::= GRAVE_BOOL.
   { l.basic.id = 3; }
type_basic_id(l) ::= GRAVE_CHAR.
   { l.basic.id = 4; }
type_basic_id(l) ::= GRAVE_TINT.
   { l.basic.id = 5; }
type_basic_id(l) ::= GRAVE_TNUM.
   { l.basic.id = 6; }
type_basic_id(l) ::= GRAVE_INT.
   { l.basic.id = 7; }
type_basic_id(l) ::= GRAVE_NUM.
   { l.basic.id = 8; }
type_basic_id(l) ::= GRAVE_FLOAT.
   { l.basic.id = 9; }
type_basic_id(l) ::= GRAVE_SIZE.
   { l.basic.id = 10; }
type_basic_id(l) ::= GRAVE_LNUM.
   { l.basic.id = 11; }
// expr_type_basic(l) ::= type_basic_id(r). { l.basic.id = _Nglc_Pexpr_type_basic_1(r.basic.id); }
// expr_type_custom(l) ::= at(r). { l.basic.id = _Nglc_Pexpr_type_1(r.basic.id); }
// expr_type(l) ::= expr_type_basic(r). { l.basic.id = r.basic.id; }
// expr_type(l) ::= expr_type_custom(r). { l.basic.id = r.basic.id; }
// expr_type(l) ::= at(r). { l.basic.id = _Nglc_Pexpr_type_1(r.basic.id); }
func_type ::= typeAndInfo_optional.
func_decl ::= LCBRACE func_decl_begin fargs func_type func_attrs.
   { _Nglc_Pdecl_func_end_2(_Grow, _Gcol); }
func_decl ::= LCBRACE func_decl_begin fargs func_type.
   { _Nglc_Pdecl_func_end_2(_Grow, _Gcol); }
/* func_attrs_inline(l) ::= SPACE_AT_INLINE_SCOLON(r).
   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; }
func_attrs_inline(l) ::= func_attr SPACE_AT_INLINE_SCOLON(r).
   { l.basic.row = r.basic.row; l.basic.col = l.basic.col; }
func_attrs_inline(l) ::= func_attrs_base func_attr SPACE_AT_INLINE_SCOLON(r).
   { l.basic.row = r.basic.row; l.basic.col = l.basic.col; }
func_decl_inline ::= func_decl_begin fargs func_type func_attrs_inline(end).
   { _Nglc_Pdecl_func_end_2(end.basic.row, end.basic.col); } */
fvar_decl ::= fvar_decl_name.
   { _Nglc_Pdecl_var_end_0(); }
fvar ::= fvar_decl typeAndInfo_optional.
   { _Nglc_Pdecl_var_as_fvar_0(); }
struct_fvars ::= fvar.
struct_fvars ::= struct_fvars COMMA_SPACE fvar.
enum_cvars ::= enum_cvar.
enum_cvars ::= enum_cvars COMMA_SPACE enum_cvar.
enum_cvars_decl ::= enum_cvar_decl.
enum_cvars_decl ::= enum_cvars_decl COMMA_SPACE enum_cvar_decl.

typeInfo ::= typeInfo_arr.
typeInfo ::= typeInfo_ref.
typeInfo ::= typeInfo_bi.
typeInfo_bi ::= PLUS.
   { _Nglc_Ptype_info_static_0(); }
ref_count(l) ::= AMPERSAND.
   { l.basic.id = 1; }
ref_count(l) ::= ref_count(r) AMPERSAND.
   { l.basic.id = r.basic.id + 1; }
typeInfo_ref ::= ref_count(c).
   { _Nglc_Ptype_info_ref_1(c.basic.id); }
typeInfo_ref ::= typeInfo_arr ref_count(c).
   { _Nglc_Ptype_info_ref_1(c.basic.id); }
typeInfo_ref ::= typeInfo_bi ref_count(c).
   { _Nglc_Ptype_info_ref_1(c.basic.id); }
typeInfo_arr ::= lbracket_or_space RBRACKET.
   { _Nglc_Ptype_info_arr_2(0, 0); }
typeInfo_arr ::= typeInfo_arr_exprs.
typeInfo_arr ::= typeInfo_bi lbracket_or_space RBRACKET.
   { _Nglc_Ptype_info_arr_2(0, 0); }
typeInfo_arr ::= typeInfo_bi typeInfo_arr_exprs.
typeInfo_arr ::= typeInfo_ref lbracket_or_space RBRACKET.
   { _Nglc_Ptype_info_arr_2(0, 0); }
typeInfo_arr ::= typeInfo_arr lbracket_or_space RBRACKET.
   { _Nglc_Ptype_info_arr_2(0, 0); }
typeInfo_arr ::= typeInfo_arr typeInfo_arr_exprs.
typeInfo_arr_exprs ::= lbracket_or_space typeInfo_arr_exprs1(e) rbracket_or_comma.
   { _Nglc_Ptype_info_arr_2(e.index.v, e.index.c); }
typeInfo_arr_exprs1(l) ::= expr(e).
   { l.index.v[(l.index.c = 1) - 1] = e.basic.id; }
typeInfo_arr_exprs1(l) ::= typeInfo_arr_exprs1 COMMA_SPACE expr(e).
   { l.index.v[l.index.c ++] = e.basic.id; }
typeInfo_begin ::= .
   { _Nglc_Ptype_info_begin_0(); }
typeInfo_none ::= typeInfo_begin.
   { _Nglc_Ptype_info_finalize_0(); }
typeInfo_optional ::= typeInfo_none.
typeInfo_optional ::= typeInfo_begin typeInfo.
   { _Nglc_Ptype_info_finalize_0(); }

expr_int(l) ::= NUM_DEC(e).
   { l.basic.id = _Nglc_Pexpr_int_2(e.basic.id, 0); }
expr_int(l) ::= NUM_HEX(e).
   { l.basic.id = _Nglc_Pexpr_int_2(e.basic.id, 1); }
expr_int(l) ::= NUM_OCT(e).
   { l.basic.id = _Nglc_Pexpr_int_2(e.basic.id, 2); }

expr_str(l) ::= STRING.
   { l.basic.id = _Nglc_Pexpr_str_1(-1); }
expr_str(l) ::= expr_str(e) SPACE STRING.
   { l.basic.id = _Nglc_Pexpr_str_1(e.basic.id); }

expr_lvar_plus(l) ::= PLUS.
   { l.basic.id = 1; }
expr_lvar_plus(l) ::= expr_lvar_plus(r) PLUS.
   { l.basic.id = r.basic.id + 1; }
expr_lvar(e) ::= ID(var).
   { e.basic.id = _Nglc_Pexpr_lvar_4(var.basic.id, 0, var.basic.row, var.basic.col); }
expr_lvar(e) ::= expr_lvar_plus(plus) ID(var) expr_type_none.
   { e.basic.id = _Nglc_Pexpr_lvar_4(var.basic.id, plus.basic.id, var.basic.row, var.basic.col); }
expr_lvar(e) ::= expr_lvar_plus(plus) lparen_or_space ID(var) typeAndInfo rparen_or_space.
   { e.basic.id = _Nglc_Pexpr_lvar_4(var.basic.id, plus.basic.id, var.basic.row, var.basic.col); }
expr_cvar(l) ::= ID_HASH(e).
   { l.basic.id = _Nglc_Pexpr_cvar_2(-1, e.basic.id); }
expr_cvar(l) ::= at(at) ID_HASH(e).
   { l.basic.id = _Nglc_Pexpr_cvar_2(at.basic.id, e.basic.id); }
value(l) ::= value4fix(r).
   { l.basic.id = r.basic.id; }
value(l) ::= negVal(r).
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
   { l.basic.id = _Nglc_Pexpr_char_1(c.basic.id); }
charExpr(l) ::= CHAR2(c).
   { l.basic.id = _Nglc_Pexpr_char_1(c.basic.id); }
boolExpr(l) ::= TRUE.
   { l.basic.id = _Nglc_Pexpr_bool_1(1); }
boolExpr(l) ::= FALSE.
   { l.basic.id = _Nglc_Pexpr_bool_1(0); }
nullExpr(l) ::= NULL.
   { l.basic.id = _Nglc_Pexpr_null_0(); }
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
valueonly(l) ::= gvarExpr(r).
   { l.basic.id = r.basic.id; }
gvarExpr(l) ::= DOT ID(r).
   { l.basic.id = _Nglc_Pexpr_gvar_2(-1, r.basic.id); }
gvarExpr(l) ::= at(at) DOT ID(r).
   { l.basic.id = _Nglc_Pexpr_gvar_2(at.basic.id, r.basic.id); }
fvarExpr(l) ::= value4fix(e) DOT ID(r).
   { l.basic.id = _Nglc_Pexpr_fvar_2(e.basic.id, r.basic.id); }
expr_and1(l) ::= expr(left) COMMA_SPACE expr(right).
   { l.basic.id = _Nglc_Pexpr_bools_3(left.basic.id, right.basic.id, 0); }
expr_and1(l) ::= expr_and1(left) COMMA_SPACE expr(right).
   { l.basic.id = _Nglc_Pexpr_bools_add_2(left.basic.id, right.basic.id); }
expr_and(l) ::= LPAREN_AMP_AMP_COMMA_SPACE expr_and1(r) rparen_or_comma.
   { l.basic.id = r.basic.id; }
expr_or1(l) ::= expr(left) COMMA_SPACE expr(right).
   { l.basic.id = _Nglc_Pexpr_bools_3(left.basic.id, right.basic.id, 1); }
expr_or1(l) ::= expr_or1(left) COMMA_SPACE expr(right).
   { l.basic.id = _Nglc_Pexpr_bools_add_2(left.basic.id, right.basic.id); }
expr_or(l) ::= LPAREN_PIPE_PIPE_COMMA_SPACE expr_or1(r) rparen_or_comma.
   { l.basic.id = r.basic.id; }
expr_add(e) ::= value(left) SPACE_PLUS_SPACE value(right).
   { e.basic.id = _Nglc_Pexpr_math_3(left.basic.id, right.basic.id, 0); }
expr_add(e) ::= expr_add(left) SPACE_PLUS_SPACE value(right).
   { e.basic.id = _Nglc_Pexpr_math_add_2(left.basic.id, right.basic.id); }
expr_sub(e) ::= value(left) SPACE_MINUS_SPACE value(right).
   { e.basic.id = _Nglc_Pexpr_math_3(left.basic.id, right.basic.id, 1); }
expr_sub(e) ::= expr_sub(left) SPACE_MINUS_SPACE value(right).
   { e.basic.id = _Nglc_Pexpr_math_add_2(left.basic.id, right.basic.id); }
expr_mul(e) ::= value(left) SPACE_MUL_SPACE value(right).
   { e.basic.id = _Nglc_Pexpr_math_3(left.basic.id, right.basic.id, 2); }
expr_mul(e) ::= expr_mul(left) SPACE_MUL_SPACE value(right).
   { e.basic.id = _Nglc_Pexpr_math_add_2(left.basic.id, right.basic.id); }
expr_div(e) ::= value(left) SPACE_DIV_SPACE value(right).
   { e.basic.id = _Nglc_Pexpr_math_3(left.basic.id, right.basic.id, 3); }
expr_div(e) ::= expr_div(left) SPACE_DIV_SPACE value(right).
   { e.basic.id = _Nglc_Pexpr_math_add_2(left.basic.id, right.basic.id); }
expr_lshift(e) ::= value(left) SPACE_LANGLE_LANGLE_SPACE value(right).
   { e.basic.id = _Nglc_Pexpr_math_3(left.basic.id, right.basic.id, 4); }
expr_rshift(e) ::= value(left) SPACE_RANGLE_RANGLE_SPACE value(right).
   { e.basic.id = _Nglc_Pexpr_math_3(left.basic.id, right.basic.id, 5); }
expr_bit_and(e) ::= value(left) SPACE_AMP_SPACE value(right).
   { e.basic.id = _Nglc_Pexpr_math_3(left.basic.id, right.basic.id, 6); }
expr_bit_and(e) ::= expr_bit_and(left) SPACE_AMP_SPACE value(right).
   { e.basic.id = _Nglc_Pexpr_math_add_2(left.basic.id, right.basic.id); }
expr_bit_or(e) ::= value(left) SPACE_PIPE_SPACE value(right).
   { e.basic.id = _Nglc_Pexpr_math_3(left.basic.id, right.basic.id, 7); }
expr_bit_or(e) ::= expr_bit_or(left) SPACE_PIPE_SPACE value(right).
   { e.basic.id = _Nglc_Pexpr_math_add_2(left.basic.id, right.basic.id); }
expr_bit_xor(e) ::= value(left) SPACE_XOR_SPACE value(right).
   { e.basic.id = _Nglc_Pexpr_math_3(left.basic.id, right.basic.id, 8); }
expr_bit_xor(e) ::= expr_bit_xor(left) SPACE_XOR_SPACE value(right).
   { e.basic.id = _Nglc_Pexpr_math_add_2(left.basic.id, right.basic.id); }
opExpr(l) ::= refExpr(r).
   { l.basic.id = r.basic.id; }
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
compare_type(l) ::= SPACE_EQUAL_EQUAL_SPACE.
   { l.basic.id = 0; }
compare_type(l) ::= SPACE_EXPOINT_EQUAL_SPACE.
   { l.basic.id = 1; }
compare_type(l) ::= SPACE_LANGLE_SPACE.
   { l.basic.id = 2; }
compare_type(l) ::= SPACE_LANGLE_EQUAL_SPACE.
   { l.basic.id = 3; }
compare_type(l) ::= SPACE_RANGLE_SPACE.
   { l.basic.id = 4; }
compare_type(l) ::= SPACE_RANGLE_EQUAL_SPACE.
   { l.basic.id = 5; }
compareExpr(l) ::= value(a) compare_type(t) value(b).
   { l.basic.id = _Nglc_Pexpr_compare_3(a.basic.id, b.basic.id, t.basic.id); }
expr_in_paren(l) ::= lparen_or_space opExpr(r) rparen_or_space.
   { l.basic.id = r.basic.id; }
expr_in_paren(l) ::= exprs(r).
   { l.basic.id = r.basic.id; }
funcExpr(l) ::= ID_LPAREN(func).
   { l.basic.id = -1; l.basic.id2 = func.basic.id; _Nglc_Pexpr_push_call_2(func.basic.row, func.basic.col); }
funcExpr(l) ::= at(at) DOT ID_LPAREN(func).
   { l.basic.id = at.basic.id; l.basic.id2 = func.basic.id; _Nglc_Pexpr_push_call_2(func.basic.row, func.basic.col); }
methodExpr(l) ::= value4fix(e) DOT ID_LPAREN(func).
   { l.basic.id = e.basic.id; l.basic.id2 = func.basic.id; _Nglc_Pexpr_push_call_2(func.basic.row, func.basic.col); }
call_args_optional ::= lparen_or_space RPAREN.
call_args_optional ::= call_args.
call_arg ::= expr(e).
   { _Nglc_Pcarg_push_1(e.basic.id); }
call_arg ::= expr_str(e) HASH.
   { _Nglc_Pcarg_push_str_1(e.basic.id); }
call_arg_list ::= call_arg.
call_arg_list ::= call_arg_list COMMA_SPACE call_arg.
call_args ::= lparen_or_space call_arg_list rparen_or_comma.
call_args_next_group ::= lparen_or_space.
   { _Nglc_Pcarg_next_group_0(); }
call_args ::= call_args call_args_next_group call_arg_list rparen_or_comma.
call_args ::= call_args call_args_next_group RPAREN.
callExpr(l) ::= callExpr_func(r).
   { l.basic.id = r.basic.id; }
callExpr(l) ::= callExpr_method(r).
   { l.basic.id = r.basic.id; }
callExpr_func(l) ::= funcExpr(e) call_args_optional.
   { l.basic.id = _Nglc_Pexpr_pop_func_2(e.basic.id, e.basic.id2); }
callExpr_method(l) ::= methodExpr(e) call_args_optional.
   { l.basic.id = _Nglc_Pexpr_pop_method_2(e.basic.id, e.basic.id2); }
expr2stmt_base(l) ::= callExpr(r).
   { l.basic.id = r.basic.id; }
assign_type(l) ::= SPACE_PLUS_EQUAL_SPACE.
   { l.basic.id = 1; }
assign_type(l) ::= SPACE_MINUS_EQUAL_SPACE.
   { l.basic.id = 2; }
assign_type(l) ::= SPACE_MUL_EQUAL_SPACE.
   { l.basic.id = 3; }
assign_type(l) ::= SPACE_DIV_EQUAL_SPACE.
   { l.basic.id = 4; }
assign_type(l) ::= SPACE_LSHIFT_EQUAL_SPACE.
   { l.basic.id = 5; }
assign_type(l) ::= SPACE_RSHIFT_EQUAL_SPACE.
   { l.basic.id = 6; }
assign_type(l) ::= SPACE_AND_EQUAL_SPACE.
   { l.basic.id = 7; }
assign_type(l) ::= SPACE_OR_EQUAL_SPACE.
   { l.basic.id = 8; }
assign_type(l) ::= SPACE_XOR_EQUAL_SPACE.
   { l.basic.id = 9; }
assign_type1(l) ::= SPACE_COLON_EQUAL_SPACE.
   { l.basic.id = 0; }
assign_type1(l) ::= assign_type(r).
   { l.basic.id = r.basic.id; }
assign_type2(l) ::= SPACE_EQUAL_SPACE.
   { l.basic.id = 0; }
assign_type2(l) ::= assign_type(r).
   { l.basic.id = r.basic.id; }
assignExpr1(l) ::= value(left) assign_type1(type) expr(right).
   { l.basic.id = _Nglc_Pexpr_assign_3(left.basic.id, right.basic.id, type.basic.id); }
assignExpr2(l) ::= value(left) assign_type2(type) expr(right).
   { l.basic.id = _Nglc_Pexpr_assign_3(left.basic.id, right.basic.id, type.basic.id); }
expr2stmt_base(l) ::= incExpr(r).
   { l.basic.id = r.basic.id; }
expr2stmt_base(l) ::= decExpr(r).
   { l.basic.id = r.basic.id; }
expr2stmt_base(l) ::= assignExpr2(r).
   { l.basic.id = r.basic.id; }
expr2stmt_base(l) ::= exprs(r).
   { l.basic.id = r.basic.id; }
expr2stmt ::= begin_pos(begin) expr2stmt_base(e) end_pos(end).
   { _Nglc_Pexpr2stmt_5(e.basic.id, begin.basic.row, begin.basic.col, end.basic.row, end.basic.col); }
expr(l) ::= fastCastExpr(r).
   { l.basic.id = r.basic.id; }
expr(l) ::= negVal(r).
   { l.basic.id = r.basic.id; }
expr(l) ::= valueonly(r).
   { l.basic.id = r.basic.id; }
expr(l) ::= opExpr(r).
   { l.basic.id = r.basic.id; }
expr(l) ::= exprs(r).
   { l.basic.id = r.basic.id; }
exprs(l) ::= expr_and(r).
   { l.basic.id = r.basic.id; }
exprs(l) ::= expr_or(r).
   { l.basic.id = r.basic.id; }

sizeOfTypeExpr(l) ::= at(at) LBRACKET GRAVE_SIZE RBRACKET.
   { l.basic.id = _Nglc_Pexpr_size_of_type_1(at.basic.id); }

fastCastExpr(l) ::= value4cast(e) at(at).
   { l.basic.id = _Nglc_Pexpr_cast_fast_2(e.basic.id, at.basic.id); }

negVal(l) ::= MINUS value4fix(e).
   { l.basic.id = _Nglc_Pexpr_unary_2(e.basic.id, 0); }

incExpr(l) ::= value(e) PLUS PLUS.
   { l.basic.id = _Nglc_Pexpr_unary_2(e.basic.id, 1); }

decExpr(l) ::= value(e) MINUS MINUS.
   { l.basic.id = _Nglc_Pexpr_unary_2(e.basic.id, 2); }

refExpr(l) ::= AMPERSAND SPACE value(e).
   { l.basic.id = _Nglc_Pexpr_ref_1(e.basic.id); }
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
indexExpr(l) ::= valueonly(r) lbracket_or_space indexExpr_exprs(e) rbracket_or_comma.
   { l.basic.id = _Nglc_Pexpr_index_3(r.basic.id, e.index.v, e.index.c); }

stmt ::= stmt_do.
stmt_do_begin ::= LCBRACE_DO.
   { _Nglc_Pstmt_do_begin_0(); }
do_expr_val(l) ::= lparen_or_space RPAREN.
   { l.basic.id = -1; }
do_expr_val(l) ::= lparen_or_space expr(e) rparen_or_space.
   { l.basic.id = e.basic.id; }
do_expr ::= begin_pos(begin) do_expr_val(e) end_pos(end).
   { _Nglc_Pstmt_do_set_6(e.basic.id, begin.basic.row, begin.basic.col, end.basic.row, end.basic.col, 0); }
do_continue_begin(l) ::= .
   { l.pointer = _Nglc_Pstmt_space_begin_detach_0(); } 
do_continue_end ::= .
   { _Nglc_Pstmt_space_end_0(); } 
do_expr ::= LCBRACE begin_pos(begin) do_expr_val(e) end_pos(end) do_continue_begin(c) stmts_optional do_continue_end.
   { _Nglc_Pstmt_do_set_6(e.basic.id, begin.basic.row, begin.basic.col, end.basic.row, end.basic.col, c.pointer); }
stmt_do ::= stmt_do_begin space_begin do_expr stmts_optional.
   { _Nglc_Pstmt_do_end_0(); }

stmt ::= stmt_while.
stmt_while_begin ::= LCBRACE_WHILE.
   { _Nglc_Pstmt_while_begin_0(); }
while_expr_val(l) ::= lparen_or_space RPAREN.
   { l.basic.id = -1; }
while_expr_val(l) ::= lparen_or_space expr(e) rparen_or_space.
   { l.basic.id = e.basic.id; }
while_expr_val(l) ::= expr_and(e).
   { l.basic.id = e.basic.id; }
while_expr_val(l) ::= expr_or(e).
   { l.basic.id = e.basic.id; }
while_expr ::= begin_pos(begin) while_expr_val(e) end_pos(end).
   { _Nglc_Pstmt_while_set_6(e.basic.id, begin.basic.row, begin.basic.col, end.basic.row, end.basic.col, 0); }
while_continue_begin(l) ::= .
   { l.pointer = _Nglc_Pstmt_space_begin_detach_0(); } 
while_continue_end ::= .
   { _Nglc_Pstmt_space_end_0(); } 
while_expr ::= LCBRACE begin_pos(begin) while_expr_val(e) end_pos(end) while_continue_begin(c) stmts_optional while_continue_end.
   { _Nglc_Pstmt_while_set_6(e.basic.id, begin.basic.row, begin.basic.col, end.basic.row, end.basic.col, c.pointer); }
stmt_while ::= stmt_while_begin space_begin while_expr stmts_optional.
   { _Nglc_Pstmt_while_end_0(); }

stmt ::= stmt_if_chain.
   { _Nglc_Pstmt_if_end_ifs_0(); }
stmt ::= stmt_if_chain stmt_else.
   { _Nglc_Pstmt_if_end_ifs_0(); }
space_begin ::= .
space_begin ::= stmt_lvars.
stmt_if_begin ::= LCBRACE_IF.
   { _Nglc_Pstmt_if_begin_0(); }
stmt_elif_begin ::= LCBRACE_ELIF.
   { _Nglc_Pstmt_elif_begin_0(); }
stmt_else_set ::= LCBRACE_ELSE.
   { _Nglc_Pstmt_else_set_0(); }
stmt_if_not(l) ::= .
   { l.basic.id = 0; }
stmt_if_not(l) ::= EXPOINT.
   { l.basic.id = 1; }
if_expr_val(l) ::= lparen_or_space expr(e) rparen_or_space.
   { l.basic.id = e.basic.id; }
if_expr_val(l) ::= expr_and(e).
   { l.basic.id = e.basic.id; }
if_expr_val(l) ::= expr_or(e).
   { l.basic.id = e.basic.id; }
if_expr ::= begin_pos(begin) stmt_if_not(not) if_expr_val(e) end_pos(end).
   { _Nglc_Pstmt_if_set_6(not.basic.id, e.basic.id, begin.basic.row, begin.basic.col, end.basic.row, end.basic.col); }
stmt_if ::= stmt_if_begin space_begin if_expr stmts_optional.
   { _Nglc_Pstmt_if_end_0(); }
elif_expr ::= begin_pos(begin) stmt_if_not(not) if_expr_val(e) end_pos(end).
   { _Nglc_Pstmt_elif_set_6(not.basic.id, e.basic.id, begin.basic.row, begin.basic.col, end.basic.row, end.basic.col); }
stmt_elif ::= stmt_elif_begin elif_expr stmts_optional.
   { _Nglc_Pstmt_elif_end_0(); }
stmt_else ::= stmt_else_set stmts_optional.
   { _Nglc_Pstmt_else_end_0(); }
stmt_if_chain ::= stmt_if.
stmt_if_chain ::= stmt_if_chain stmt_elif.

stmt ::= stmt_switch.
stmt_switch_begin ::= LCBRACE_SWITCH.
   { _Nglc_Pstmt_switch_begin_0(); }
switch_expr ::= begin_pos(begin) if_expr_val(e) end_pos(end).
   { _Nglc_Pstmt_switch_set_6(e.basic.id, begin.basic.row, begin.basic.col, end.basic.row, end.basic.col, -1); }
switch_expr ::= begin_pos(begin) if_expr_val(e) DOT callExpr_func(cases) end_pos(end).
   { _Nglc_Pstmt_switch_set_6(e.basic.id, begin.basic.row, begin.basic.col, end.basic.row, end.basic.col, cases.basic.id); }
switch_case_expr ::= expr(e).
   { _Nglc_Pstmt_switch_expr_add_1(e.basic.id); }
switch_case_exprs ::= switch_case_expr.
switch_case_exprs ::= switch_case_exprs COMMA_SPACE switch_case_expr.
switch_case_fall(l) ::= .
   { l.basic.id = 0; }
switch_case_fall(l) ::= SPACE_AT_FALL_THROUGH.
   { l.basic.id = 1; }
switch_case_expr_end ::= LCBRACE_CASE(begin) lparen_or_space switch_case_exprs rparen_or_comma switch_case_fall(fall) end_pos(end).
   { _Nglc_Pstmt_switch_case_begin_5(begin.basic.row, begin.basic.col, end.basic.row, end.basic.col, fall.basic.id); }
switch_case ::= switch_case_expr_end stmts_optional.
   { _Nglc_Pstmt_switch_case_end_0(); }
switch_default_begin ::= LCBRACE_DEFAULT(begin) switch_case_fall(fall) end_pos(end).
   { _Nglc_Pstmt_switch_default_begin_5(begin.basic.row, begin.basic.col, end.basic.row, end.basic.col, fall.basic.id); }
switch_case ::= switch_default_begin stmts_optional.
   { _Nglc_Pstmt_switch_default_end_0(); }
switch_cases ::= switch_case.
switch_cases ::= switch_cases SPACE switch_case.
stmt_switch ::= stmt_switch_begin space_begin switch_expr SPACE switch_cases rcbrace_or_space.
   { _Nglc_Pstmt_switch_end_0(); }
stmt_switch ::= stmt_switch_begin space_begin switch_expr rcbrace_or_space.
   { _Nglc_Pstmt_switch_end_0(); }

stmt_expr ::= stmt_continue.
stmt_continue ::= begin_pos(begin) CONTINUE end_pos(end).
   { _Nglc_Pstmt_continue_5(-1, begin.basic.row, begin.basic.col, end.basic.row, end.basic.col); }

stmt_expr ::= stmt_break.
stmt_break ::= begin_pos(begin) BREAK end_pos(end).
   { _Nglc_Pstmt_break_5(-1, begin.basic.row, begin.basic.col, end.basic.row, end.basic.col); }

stmt_expr ::= stmt_return.
stmt_return ::= begin_pos(begin) RETURN end_pos(end).
   { _Nglc_Pstmt_return_5(-1, begin.basic.row, begin.basic.col, end.basic.row, end.basic.col); }
stmt_return ::= begin_pos(begin) RETURN SPACE expr(e) end_pos(end).
   { _Nglc_Pstmt_return_5(e.basic.id, begin.basic.row, begin.basic.col, end.basic.row, end.basic.col); }

typeAndInfo ::= expr_type_apply typeInfo_optional.
typeAndInfo_optional ::= typeAndInfo.
typeAndInfo_optional ::= expr_type_none typeInfo_none.

stmt ::= stmt_lvars.
stmt_lvars ::= decl_lvar_begin lvar_list(end).
   { _Nglc_Pstmt_lvar_end_2(end.basic.row, end.basic.col); }
decl_lvar ::= ID(var) typeAndInfo_optional SPACE_EQUAL_SPACE expr(e).
   { _Nglc_Pstmt_lvar_add_4(var.basic.id, e.basic.id, var.basic.row, var.basic.col); }
decl_lvar ::= ID(var) typeAndInfo_optional.
   { _Nglc_Pstmt_lvar_add_4(var.basic.id, -1, var.basic.row, var.basic.col); }
decl_lvars ::= decl_lvar.
decl_lvars ::= decl_lvars COMMA_SPACE decl_lvar.
lvar_list(l) ::= RCBRACE(r).
   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; }
lvar_list(l) ::= decl_lvars rcbrace_or_comma(r).
   { l.basic.row = r.basic.row; l.basic.col = r.basic.col; }
decl_lvar_begin ::= LCBRACE_PLUS_OR_SPACE.

decl_var_attr ::= SPACE_AT_REAL_NAME_STR(e).
   { _Nglc_Pdecl_var_attr_real_name_1(e.basic.id); }
decl_var_attr ::= SPACE_AT_EXTERN.
   { _Nglc_Pdecl_var_attr_extern_0(); }
decl_var_attr ::= SPACE_AT_NO_DECL.
   { _Nglc_Pdecl_var_attr_no_decl_0(); }
decl_var_attrs_list ::= decl_var_attr.
decl_var_attrs_list ::= decl_var_attrs_list decl_var_attr.
decl_var_attrs_optional ::= .
decl_var_attrs_optional ::= decl_var_attrs_list.

decl_func ::= func_decl RCBRACE.
stmt_brace ::= stmt.
stmt_expr ::= expr2stmt.
stmts_brace ::= stmt_brace.
stmts_brace ::= stmts_expr SCOLON_SPACE stmt_brace.
stmts_brace ::= stmts_brace SPACE stmt_brace.
stmts_expr ::= stmt_expr.
stmts_expr ::= stmts_expr SCOLON_SPACE stmt_expr.
stmts_expr ::= stmts_brace SPACE stmt_expr.
stmts_optional ::= SPACE_RCBRACE.
stmts_optional ::= SPACE stmts_brace rcbrace_or_space.
stmts_optional ::= SPACE stmts_expr rcbrace_or_scolon.
decl_struct_attr ::= SPACE_AT_NO_DECL.
   { _Nglc_Pstruct_attr_no_decl_0(); }
decl_struct_attr ::= SPACE_AT_REAL_NAME_STR(e).
   { _Nglc_Pstruct_attr_real_name_1(e.basic.id); }
decl_struct_attr ::= SPACE_AT_UNION.
   { _Nglc_Pstruct_attr_union_0(); }
decl_struct_attrs_list ::= decl_struct_attr.
decl_struct_attrs_list ::= decl_struct_attrs_list decl_struct_attr.
decl_struct_attrs_optional ::= end_pos(end).
   { _Nglc_Pdecl_struct_end_2(end.basic.row, end.basic.col); }
decl_struct_attrs_optional ::= decl_struct_attrs_list end_pos(end).
   { _Nglc_Pdecl_struct_end_2(end.basic.row, end.basic.col); }
decl_func ::= func_decl stmts_optional.
   { _Nglc_Pfunc_body_end_0(); }
/* decl_func ::= func_decl_inline stmts_optional.
   { _Nglc_Pfunc_body_end_1(true); } */
decl_struct_close_or_at ::= rcbrace_or_space.
   { _Nglc_Pdecl_at_end_0(); }
decl_struct_close_or_at ::= SPACE decls rcbrace_or_space.
   { _Nglc_Pdecl_at_end_0(); }
decl_struct ::= struct_decl_begin lparen_or_space RPAREN
   decl_struct_attrs_optional decl_struct_close_or_at.
decl_struct ::= struct_decl_begin lparen_or_space struct_fvars rparen_or_comma
   decl_struct_attrs_optional decl_struct_close_or_at.
decl_enum_close_or_at ::= rcbrace_or_space.
   { _Nglc_Pdecl_at_end_0(); }
decl_enum_close_or_at ::= SPACE decls rcbrace_or_space.
   { _Nglc_Pdecl_at_end_0(); }
enum_base_begin ::= .
   { _Nglc_Penum_base_begin_0(); }
enum_base_end ::= at(at) end_pos(end).
   { _Nglc_Pdecl_enum_end_3(at.basic.id, end.basic.row, end.basic.col); }
decl_enum ::= enum_decl_begin lbracket_or_space RBRACKET enum_base_begin enum_base_end
   decl_enum_close_or_at.
decl_enum ::= enum_decl_begin lbracket_or_space enum_cvars rbracket_or_comma enum_base_begin enum_base_end
   decl_enum_close_or_at.
decl_gvar ::= fvar_decl expr_type_apply typeInfo_optional decl_var_attrs_optional.
   { _Nglc_Pdecl_var_as_gvar_0(); }
decl_gvar_list ::= decl_gvar.
decl_gvar_list ::= decl_gvar_list decl_gvar.
decl_gvars ::= LCBRACE_GVAR_SPACE RCBRACE.
decl_gvars ::= LCBRACE_GVAR_SPACE decl_gvar_list rcbrace_or_comma.
