void qalloc_undo(int32_t _Lsize_0);
void _NCp1_Pdecl_import_4(_NCp1_NInclude _Lpath_0, uint32_t _Lrow_1, uint32_t _Lcol_2, bool _Lrequire_3);
void _NCp1_Pdecl_template_inst_3(_NCp1_NId _Lname_0, uint32_t _Lrow_1, uint32_t _Lcol_2);
void _NCp1_Pdecl_template_code_3(_NCp1_NId _Lname_0, uint32_t _Lrow_1, bool _Lwith_reflection_2);
void _NCp1_Pdecl_func_begin_3(_NCp1_NId _Lname_0, uint32_t _Lrow_1, uint32_t _Lcol_2);
void _NCp1_Pdecl_func_end_2(uint32_t _Lrow_0, uint32_t _Lcol_1);
void _NCp1_Pdecl_struct_end_2(uint32_t _Lrow_0, uint32_t _Lcol_1);
void _NCp1_Pdecl_var_begin_3(_NCp1_NId _Lname_0, uint32_t _Lrow_1, uint32_t _Lcol_2);
void _NCp1_Pdecl_var_attr_real_name_1(_NCp1_NId _Lname_0);
void _NCp1_Pdecl_var_attr_extern_0();
void _NCp1_Pdecl_var_attr_no_decl_0();
void _NCp1_Pdecl_var_end_0();
void _NCp1_Pdecl_var_as_farg_2(uint32_t _Lrow_0, uint32_t _Lcol_1);
void _NCp1_Pfarg_next_group_0();
void _NCp1_Pdecl_var_as_this_0();
void _NCp1_Pdecl_var_as_fvar_0();
void _NCp1_Pfunc_body_end_0();
void _NCp1_Pexpr_push_call_2(uint32_t _Lrow_0, uint32_t _Lcol_1);
_NCp1_NExprI _NCp1_Pexpr_pop_func_2(_NCp1_NAt _Lat_0, _NCp1_NId _Lfunc_name_1);
void _NCp1_Pexpr_push_metacall_2(uint32_t _Lrow_0, uint32_t _Lcol_1);
_NCp1_NExprI _NCp1_Pexpr_pop_metafunc_2(_NCp1_NAt _Lat_0, _NCp1_NId _Lfunc_name_1);
_NCp1_NExprI _NCp1_Pexpr_pop_method_2(_NCp1_NExprI _Lthiss_0, _NCp1_NId _Lfunc_name_1);
void _NCp1_Pmetacarg_push_1(_NCp1_NExprI _Lexpr_0);
void _NCp1_Pmetacarg_next_group_0();
void _NCp1_Pcarg_push_1(_NCp1_NExprI _Lexpr_0);
void _NCp1_Pcarg_push_str_1(_NCp1_NExprI _Lexpr_0);
void _NCp1_Pcarg_next_group_0();
void _NCp1_Pexpr2stmt_5(_NCp1_NExprI _Le_idx_0, uint32_t _Lbegin_row_1, uint32_t _Lbegin_col_2, uint32_t _Lend_row_3, uint32_t _Lend_col_4);
void _NCp1_Pstmt_return_5(_NCp1_NExprI _Le_0, uint32_t _Lbegin_row_1, uint32_t _Lbegin_col_2, uint32_t _Lend_row_3, uint32_t _Lend_col_4);
void _NCp1_Pstmt_continue_5(_NCp1_NId _Lid_0, uint32_t _Lbegin_row_1, uint32_t _Lbegin_col_2, uint32_t _Lend_row_3, uint32_t _Lend_col_4);
void _NCp1_Pstmt_break_5(_NCp1_NId _Lid_0, uint32_t _Lbegin_row_1, uint32_t _Lbegin_col_2, uint32_t _Lend_row_3, uint32_t _Lend_col_4);
void _NCp1_Pfunc_attr_main_0();
void _NCp1_Pfunc_attr_decl_0();
void _NCp1_Pfunc_attr_cp1_name_0();
void _NCp1_Pfunc_attr_process_0();
void _NCp1_Pfunc_attr_inline_0();
void _NCp1_Pfunc_attr_var_args_0();
void _NCp1_Pfunc_attr_no_decl_0();
void _NCp1_Pfunc_attr_no_body_0();
void _NCp1_Pfunc_attr_real_name_1(_NCp1_NId _Lname_0);
void _NCp1_Pfunc_attr_meta_method_3(_NCp1_NId _Lprefix1_0, _NCp1_NId _Lprefix2_1, _NCp1_NId _Lend_2);
void _NCp1_Pfunc_attr_case_1(_NCp1_NId _Lname_0);
void _NCp1_Penum_attr_soa_field_2(_NCp1_NAt _Lat_0, _NCp1_NId _Lid_1);
void _NCp1_Penum_attr_no_decl_0();
void _NCp1_Penum_attr_real_name_1(_NCp1_NId _Lid_0);
_NCp1_NExprI _NCp1_Pexpr_lvar_4(_NCp1_NId _Lname_0, uint8_t _Ldecl_1, uint32_t _Lrow_2, uint32_t _Lcol_3);
_NCp1_NExprI _NCp1_Pexpr_gvar_2(_NCp1_NAt _Lat_0, _NCp1_NId _Lname_1);
_NCp1_NExprI _NCp1_Pexpr_fvar_2(_NCp1_NExprI _Lexpr_0, _NCp1_NId _Lmember_1);
_NCp1_NExprI _NCp1_Pexpr_soa_field_3(_NCp1_NExprI _Lexpr_0, _NCp1_NId _Lgroup_1, _NCp1_NId _Lfield_2);
_NCp1_NExprI _NCp1_Pexpr_assign_3(_NCp1_NExprI _Lleft_0, _NCp1_NExprI _Lright_1, _NCp1_NAssign _Ltype_2);
_NCp1_NExprI _NCp1_Pexpr_math_3(_NCp1_NExprI _Lleft_0, _NCp1_NExprI _Lright_1, _NCp1_NMath _Ltype_2);
_NCp1_NExprI _NCp1_Pexpr_math_add_2(_NCp1_NExprI _Lexpr_0, _NCp1_NExprI _Lright_1);
_NCp1_NExprI _NCp1_Pexpr_bools_3(_NCp1_NExprI _Lleft_0, _NCp1_NExprI _Lright_1, _NCp1_NBools _Ltype_2);
_NCp1_NExprI _NCp1_Pexpr_bools_add_2(_NCp1_NExprI _Lbools_0, _NCp1_NExprI _Lright_1);
char* _NCp1_Ptoken_name_1(_NCp1_NToken _Ltok_0);
void _NCp1_Pdecl_var_type_1(_NCp1_NAt _Ltype_0);
void _NCp1_Pdecl_var_this_0();
void _NCp1_Pstmt_lvar_add_4(_NCp1_NId _Lname_0, _NCp1_NExprI _Lset_1, uint32_t _Lrow_2, uint32_t _Lcol_3);
void _NCp1_Pstmt_lvar_end_2(uint32_t _Lend_row_0, uint32_t _Lend_col_1);
void _NCp1_Pdecl_include_begin_3(_NCp1_NInclude _Linc_0, uint32_t _Lrow_1, uint32_t _Lcol_2);
void _NCp1_Pdecl_include_end_0();
void _NCp1_Pdecl_at_basic_1(_NCp1_NBasicTypeId _Ltype_0);
void _NCp1_Pdecl_at_add_2(_NCp1_NId _Lname_0, _NCp1_NNameType _Ltype_1);
void _NCp1_Pdecl_at_begin_2(uint32_t _Lrow_0, uint32_t _Lcol_1);
void _NCp1_Pdecl_at_begin_struct_3(_NCp1_NId _Lname_0, uint32_t _Lrow_1, uint32_t _Lcol_2);
void _NCp1_Pdecl_at_end_0();
void _NCp1_Pdecl_alias_4(_NCp1_NId _Lname_0, _NCp1_NAt _Lat_1, uint32_t _Lrow_2, uint32_t _Lcol_3);
void _NCp1_Pat_push_4(_NCp1_NId _Lname_0, _NCp1_NNameType _Ltype_1, uint32_t _Lrow_2, uint32_t _Lcol_3);
_NCp1_NAt _NCp1_Pat_done_0();
void _NCp1_Pat_begin_0();
void _NCp1_Pat_begin_relative_0();
void _NCp1_Pat_begin_relative_pause_0();
void _NCp1_Pat_begin_relative_resume_0();
void _NCp1_Pat_root_0();
void _NCp1_Pat_alias_3(_NCp1_NId _Lname_0, uint32_t _Lrow_1, uint32_t _Lcol_2);
void _NCp1_Pat_graves_3(int8_t _Lgraves_0, uint32_t _Lrow_1, uint32_t _Lcol_2);
_NCp1_NAt _NCp1_Pat_basic_type_1(_NCp1_NBasicTypeId _Ltype_0);
void _NCp1_Pdecl_var_as_gvar_0();
void _NCp1_Ptype_info_arr_2(_NCp1_NExprI* _Lexpr_v_0, uint8_t _Lexpr_c_1);
void _NCp1_Ptype_info_ref_1(int8_t _Lc_0);
void _NCp1_Ptype_info_static_0();
void _NCp1_Ptype_info_begin_0();
void _NCp1_Ptype_info_finalize_0();
_NCp1_NExprI _NCp1_Pexpr_int_2(int32_t _Lvalue_0, _NCp1_NExprInt _Ltype_1);
_NCp1_NExprI _NCp1_Pexpr_int64_2(int64_t _Lvalue_0, _NCp1_NExprInt _Ltype_1);
_NCp1_NExprI _NCp1_Pexpr_f32_1(float _Lvalue_0);
_NCp1_NExprI _NCp1_Pexpr_size_of_type_1(_NCp1_NAt _Lat_0);
_NCp1_NExprI _NCp1_Pexpr_null_0();
void _NCp1_Pdecl_at_begin_enum_3(_NCp1_NId _Lname_0, uint32_t _Lrow_1, uint32_t _Lcol_2);
void _NCp1_Pdecl_enum_end_3(_NCp1_NAt _Lbase_type_0, uint32_t _Lrow_1, uint32_t _Lcol_2);
_NCp1_NExprI _NCp1_Pexpr_cvar_2(_NCp1_NAt _Lat_0, _NCp1_NId _Lname_1);
void _NCp1_Penum_add_cvar_3(_NCp1_NId _Lname_0, uint32_t _Lrow_1, uint32_t _Lcol_2);
void _NCp1_Pdecl_add_cvar_3(_NCp1_NId _Lname_0, uint32_t _Lrow_1, uint32_t _Lcol_2);
void _NCp1_Penum_set_cvar_expr_1(_NCp1_NExprI _Lset_0);
void _NCp1_Pstruct_attr_real_name_1(_NCp1_NId _Lname_0);
void _NCp1_Pstruct_attr_union_0();
void _NCp1_Pstruct_attr_no_decl_0();
_NCp1_NExprI _NCp1_Pexpr_str_1(_NCp1_NExprI _Lprev_0);
_NCp1_NExprI _NCp1_Pexpr_unary_2(_NCp1_NExprI _Lexpr_0, _NCp1_NUnary _Ltype_1);
_NCp1_NExprI _NCp1_Pexpr_ref_1(_NCp1_NExprI _Lexpr_0);
_NCp1_NExprI _NCp1_Pexpr_cast_fast_2(_NCp1_NExprI _Lexpr_0, _NCp1_NAt _Ltype_1);
_NCp1_NExprI _NCp1_Pexpr_index_3(_NCp1_NExprI _Lleft_0, _NCp1_NExprI* _Lright_v_1, int32_t _Lright_c_2);
void _NCp1_Penum_base_begin_0();
void _NCp1_Pstmt_switch_begin_0();
void _NCp1_Pstmt_switch_set_6(_NCp1_NExprI _Lexpr_0, uint32_t _Lbegin_row_1, uint32_t _Lbegin_col_2, uint32_t _Lend_row_3, uint32_t _Lend_col_4, _NCp1_NExprI _Lcases_5);
void _NCp1_Pstmt_switch_expr_add_1(_NCp1_NExprI _Lexpr_0);
void _NCp1_Pstmt_switch_case_begin_5(uint32_t _Lbegin_row_0, uint32_t _Lbegin_col_1, uint32_t _Lend_row_2, uint32_t _Lend_col_3, bool _Lfall_through_4);
void _NCp1_Pstmt_switch_case_end_0();
void _NCp1_Pstmt_switch_default_begin_5(uint32_t _Lbegin_row_0, uint32_t _Lbegin_col_1, uint32_t _Lend_row_2, uint32_t _Lend_col_3, bool _Lfall_through_4);
void _NCp1_Pstmt_switch_default_end_0();
void _NCp1_Pstmt_switch_end_0();
void _NCp1_Pstmt_if_begin_0();
void _NCp1_Pstmt_if_set_5(_NCp1_NExprI _Lexpr_0, uint32_t _Lbegin_row_1, uint32_t _Lbegin_col_2, uint32_t _Lend_row_3, uint32_t _Lend_col_4);
void _NCp1_Pstmt_if_end_0();
void _NCp1_Pstmt_loop_begin_0();
void _NCp1_Pstmt_loop_set_6(_NCp1_NExprI _Lexpr_0, uint32_t _Lbegin_row_1, uint32_t _Lbegin_col_2, uint32_t _Lend_row_3, uint32_t _Lend_col_4, struct _NCp1_NStmtSpace* _Lcontinu_5);
void _NCp1_Pstmt_loop_end_0();
void _NCp1_Pstmt_elif_begin_0();
void _NCp1_Pstmt_elif_set_5(_NCp1_NExprI _Lexpr_0, uint32_t _Lbegin_row_1, uint32_t _Lbegin_col_2, uint32_t _Lend_row_3, uint32_t _Lend_col_4);
void _NCp1_Pstmt_elif_end_0();
void _NCp1_Pstmt_else_set_0();
void _NCp1_Pstmt_else_end_0();
void _NCp1_Pstmt_if_end_ifs_0();
struct _NCp1_NStmtSpace* _NCp1_Pstmt_space_begin_0();
struct _NCp1_NStmtSpace* _NCp1_Pstmt_space_begin_detach_0();
struct _NCp1_NStmtSpace* _NCp1_Pstmt_space_end_0();
_NCp1_NExprI _NCp1_Pexpr_compare_3(_NCp1_NExprI _Lleft_0, _NCp1_NExprI _Lright_1, _NCp1_NCompare _Ltype_2);
_NCp1_NExprI _NCp1_Pexpr_bool_1(bool _Lvalue_0);
_NCp1_NExprI _NCp1_Pexpr_char_1(int32_t _Lvalue_0);
void _NCp1_Pcvar_attr_real_name_1(_NCp1_NId _Lname_0);
void _NCp1_Pcvar_attr_no_decl_0();
