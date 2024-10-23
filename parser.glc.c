#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "alloc.h"
#include <string.h>
#define _Mglc_Efunc_Cnil (-1)
#define _Mglc_Einclude_Cnil (-1)
#define _Mstdc_Eexit_Csuccess 0
#define _Mstdc_Eexit_Cfailure (_Mstdc_Eexit_Csuccess + 1)
#define _Mglc_Ename_type_Cmodule 0
#define _Mglc_Ename_type_Cstruct (_Mglc_Ename_type_Cmodule + 1)
#define _Mglc_Ename_type_Cenum (_Mglc_Ename_type_Cstruct + 1)
#define _Mglc_Ename_type_Cbasic (_Mglc_Ename_type_Cenum + 1)
#define _Mglc_Eat_Cnil (-1)
#define _Mglc_Ebasic_type_id_Croot 0
#define _Mglc_Ctype_info_star_limit (8)
#define _Mglc_Cexpr_carg_group_limit (4)
#define _Mglc_Etoken_Cnil 0
#define _Mglc_Etoken_Cplus (_Mglc_Etoken_Cnil + 1)
#define _Mglc_Etoken_Cminus (_Mglc_Etoken_Cplus + 1)
#define _Mglc_Etoken_Cspace (_Mglc_Etoken_Cminus + 1)
#define _Mglc_Etoken_Clcbrace (_Mglc_Etoken_Cspace + 1)
#define _Mglc_Etoken_Cid_colon (_Mglc_Etoken_Clcbrace + 1)
#define _Mglc_Etoken_Cid_modulo (_Mglc_Etoken_Cid_colon + 1)
#define _Mglc_Etoken_Cid_fslash (_Mglc_Etoken_Cid_modulo + 1)
#define _Mglc_Etoken_Cid_bslash (_Mglc_Etoken_Cid_fslash + 1)
#define _Mglc_Etoken_Cid_quote (_Mglc_Etoken_Cid_bslash + 1)
#define _Mglc_Etoken_Cid_hash (_Mglc_Etoken_Cid_quote + 1)
#define _Mglc_Etoken_Cid_dot (_Mglc_Etoken_Cid_hash + 1)
#define _Mglc_Etoken_Cid (_Mglc_Etoken_Cid_dot + 1)
#define _Mglc_Etoken_Cspace_at_real_name_str (_Mglc_Etoken_Cid + 1)
#define _Mglc_Etoken_Cspace_at_no_decl (_Mglc_Etoken_Cspace_at_real_name_str + 1)
#define _Mglc_Etoken_Cspace_equal_space (_Mglc_Etoken_Cspace_at_no_decl + 1)
#define _Mglc_Etoken_Cinclude (_Mglc_Etoken_Cspace_equal_space + 1)
#define _Mglc_Etoken_Cspace_rcbrace (_Mglc_Etoken_Cinclude + 1)
#define _Mglc_Etoken_Cquote (_Mglc_Etoken_Cspace_rcbrace + 1)
#define _Mglc_Etoken_Cgrave (_Mglc_Etoken_Cquote + 1)
#define _Mglc_Etoken_Clcbrace_at (_Mglc_Etoken_Cgrave + 1)
#define _Mglc_Etoken_Clparen (_Mglc_Etoken_Clcbrace_at + 1)
#define _Mglc_Etoken_Crparen (_Mglc_Etoken_Clparen + 1)
#define _Mglc_Etoken_Clcbrace_cvar (_Mglc_Etoken_Crparen + 1)
#define _Mglc_Etoken_Cend (_Mglc_Etoken_Clcbrace_cvar + 1)
#define _Mglc_Etoken_Clcbrace_alias (_Mglc_Etoken_Cend + 1)
#define _Mglc_Etoken_Crcbrace (_Mglc_Etoken_Clcbrace_alias + 1)
#define _Mglc_Etoken_Clparen_space (_Mglc_Etoken_Crcbrace + 1)
#define _Mglc_Etoken_Cspace_rparen (_Mglc_Etoken_Clparen_space + 1)
#define _Mglc_Etoken_Ccomma_space_rparen (_Mglc_Etoken_Cspace_rparen + 1)
#define _Mglc_Etoken_Ccomma_space_rcbrace (_Mglc_Etoken_Ccomma_space_rparen + 1)
#define _Mglc_Etoken_Cscolon_space_rcbrace (_Mglc_Etoken_Ccomma_space_rcbrace + 1)
#define _Mglc_Etoken_Clbracket (_Mglc_Etoken_Cscolon_space_rcbrace + 1)
#define _Mglc_Etoken_Clbracket_space (_Mglc_Etoken_Clbracket + 1)
#define _Mglc_Etoken_Crbracket (_Mglc_Etoken_Clbracket_space + 1)
#define _Mglc_Etoken_Cspace_rbracket (_Mglc_Etoken_Crbracket + 1)
#define _Mglc_Etoken_Ccomma_space_rbracket (_Mglc_Etoken_Cspace_rbracket + 1)
#define _Mglc_Etoken_Cgrave_this (_Mglc_Etoken_Ccomma_space_rbracket + 1)
#define _Mglc_Etoken_Ccomma_space (_Mglc_Etoken_Cgrave_this + 1)
#define _Mglc_Etoken_Cspace_at_main (_Mglc_Etoken_Ccomma_space + 1)
#define _Mglc_Etoken_Cspace_at_case (_Mglc_Etoken_Cspace_at_main + 1)
#define _Mglc_Etoken_Cspace_at_process (_Mglc_Etoken_Cspace_at_case + 1)
#define _Mglc_Etoken_Cspace_at_glc_name (_Mglc_Etoken_Cspace_at_process + 1)
#define _Mglc_Etoken_Cspace_at_var_args (_Mglc_Etoken_Cspace_at_glc_name + 1)
#define _Mglc_Etoken_Cspace_at_no_body (_Mglc_Etoken_Cspace_at_var_args + 1)
#define _Mglc_Etoken_Cspace_at_real_name (_Mglc_Etoken_Cspace_at_no_body + 1)
#define _Mglc_Etoken_Cgrave_ref (_Mglc_Etoken_Cspace_at_real_name + 1)
#define _Mglc_Etoken_Cgrave_bool (_Mglc_Etoken_Cgrave_ref + 1)
#define _Mglc_Etoken_Cgrave_char (_Mglc_Etoken_Cgrave_bool + 1)
#define _Mglc_Etoken_Cgrave_tint (_Mglc_Etoken_Cgrave_char + 1)
#define _Mglc_Etoken_Cgrave_tnum (_Mglc_Etoken_Cgrave_tint + 1)
#define _Mglc_Etoken_Cgrave_int (_Mglc_Etoken_Cgrave_tnum + 1)
#define _Mglc_Etoken_Cgrave_num (_Mglc_Etoken_Cgrave_int + 1)
#define _Mglc_Etoken_Cgrave_float (_Mglc_Etoken_Cgrave_num + 1)
#define _Mglc_Etoken_Cgrave_size (_Mglc_Etoken_Cgrave_float + 1)
#define _Mglc_Etoken_Cgrave_lnum (_Mglc_Etoken_Cgrave_size + 1)
#define _Mglc_Etoken_Cspace_at_inline_scolon (_Mglc_Etoken_Cgrave_lnum + 1)
#define _Mglc_Etoken_Campersand (_Mglc_Etoken_Cspace_at_inline_scolon + 1)
#define _Mglc_Etoken_Cnum_dec (_Mglc_Etoken_Campersand + 1)
#define _Mglc_Etoken_Cnum_hex (_Mglc_Etoken_Cnum_dec + 1)
#define _Mglc_Etoken_Cnum_oct (_Mglc_Etoken_Cnum_hex + 1)
#define _Mglc_Etoken_Cstring (_Mglc_Etoken_Cnum_oct + 1)
#define _Mglc_Etoken_Cchar1 (_Mglc_Etoken_Cstring + 1)
#define _Mglc_Etoken_Cchar2 (_Mglc_Etoken_Cchar1 + 1)
#define _Mglc_Eid_Cnil (-1)
#define _Mglc_Eid_C0 (_Mglc_Eid_Cnil + 1)
#define _Mglc_Eexpr_Cnil (-1)
#define _Mglc_Eexpr_C0 (_Mglc_Eexpr_Cnil + 1)
#define _Mglc_Eassign_Ceq 0
#define _Mglc_Emath_Cadd 0
#define _Mglc_Ebools_Cand 0
#define _Mglc_Einclude_C0 (_Mglc_Einclude_Cnil + 1)
#define _Mglc_Ebasic_type_id_Cref (_Mglc_Ebasic_type_id_Croot + 1)
#define _Mglc_Ebasic_type_id_Cbool (_Mglc_Ebasic_type_id_Cref + 1)
#define _Mglc_Ebasic_type_id_Cchar (_Mglc_Ebasic_type_id_Cbool + 1)
#define _Mglc_Ebasic_type_id_Ctint (_Mglc_Ebasic_type_id_Cchar + 1)
#define _Mglc_Ebasic_type_id_Ctnum (_Mglc_Ebasic_type_id_Ctint + 1)
#define _Mglc_Ebasic_type_id_Cint (_Mglc_Ebasic_type_id_Ctnum + 1)
#define _Mglc_Eexpr_int_Cdec 0
#define _Mglc_Eunary_Cneg 0
#define _Mglc_Ecompare_Ceq 0
#define _Mglc_Ecvar_flags_Cset_expr (1)
#define _Mglc_Ecvar_flags_C0 0
#define _Mglc_Eenum_flags_Creal_name (1)
#define _Mglc_Eenum_flags_C0 0
#define _Mglc_Estruct_flags_Creal_name (1)
#define _Mglc_Estruct_flags_C0 0
#define _Mglc_Efunc_flags_Cinline (2)
#define _Mglc_Efunc_flags_Chas_body (1)
#define _Mglc_Efunc_flags_Creal_name (64)
#define _Mglc_Efunc_flags_C0 0
#define _Mglc_Efunc_flags_Ccase (128)
#define _Mglc_Efunc_flags2_C0 0
#define _Mglc_Efunc_flags2_Cmain (1)
#define _Mglc_Eat_Croot (_Mglc_Eat_Cnil + 1)
#define _Mglc_Evar_flags_C0 0
#define _Mglc_Evar_flags_Creal_name (1)
#define _Mglc_Evar_flags_Cextern (2)
#define _Mglc_Evar_flags_Cno_decl (4)
#define _Mglc_Cexpr_call_nest_limit (8)
#define _Mglc_Eexpr_type_Cnil 0
#define _Mglc_Eexpr_type_Ccall_method (_Mglc_Eexpr_type_Cnil + 1)
#define _Mglc_Eexpr_type_Clvar (_Mglc_Eexpr_type_Ccall_method + 1)
#define _Mglc_Eexpr_type_Cgvar (_Mglc_Eexpr_type_Clvar + 1)
#define _Mglc_Eexpr_type_Cmath (_Mglc_Eexpr_type_Cgvar + 1)
#define _Mglc_Eexpr_type_Cassign (_Mglc_Eexpr_type_Cmath + 1)
#define _Mglc_Eexpr_type_Cbools (_Mglc_Eexpr_type_Cassign + 1)
#define _Mglc_Eexpr_type_Cfunc (_Mglc_Eexpr_type_Cbools + 1)
#define _Mglc_Cglc_carg_limit (64)
#define _Mglc_Eexpr_type_Cmethod (_Mglc_Eexpr_type_Cfunc + 1)
#define _Mglc_Estmt_type_Cspace 0
#define _Mglc_Estmt_type_Cif (_Mglc_Estmt_type_Cspace + 1)
#define _Mglc_Estmt_type_Cif_elif (_Mglc_Estmt_type_Cif + 1)
#define _Mglc_Estmt_type_Cif_else (_Mglc_Estmt_type_Cif_elif + 1)
#define _Mglc_Estmt_type_Cif_end (_Mglc_Estmt_type_Cif_else + 1)
#define _Mglc_Estmt_type_Cdo (_Mglc_Estmt_type_Cif_end + 1)
#define _Mglc_Estmt_type_Cdo_end (_Mglc_Estmt_type_Cdo + 1)
#define _Mglc_Estmt_type_Cwhile (_Mglc_Estmt_type_Cdo_end + 1)
#define _Mglc_Estmt_type_Cwhile_end (_Mglc_Estmt_type_Cwhile + 1)
#define _Mglc_Estmt_type_Cexpr (_Mglc_Estmt_type_Cwhile_end + 1)
#define _Mglc_Estmt_type_Creturn (_Mglc_Estmt_type_Cexpr + 1)
#define _Mglc_Estmt_type_Ccontinue (_Mglc_Estmt_type_Creturn + 1)
#define _Mglc_Estmt_type_Cbreak (_Mglc_Estmt_type_Ccontinue + 1)
#define _Mglc_Efunc_flags_Cglc_name (256)
#define _Mglc_Efunc_flags_Cprocess (4)
#define _Mglc_Efunc_flags_Cvar_args (8)
#define _Mglc_Efunc_flags_Cno_decl (16)
#define _Mglc_Efunc_flags_Cno_body (32)
#define _Mglc_Elvar_Cnil (-1)
#define _Mglc_Estmt_space_flags_Cskip_lvar_decl (1)
#define _Mglc_Estmt_space_flags_C0 0
#define _Mglc_Eexpr_type_Cfvar (_Mglc_Eexpr_type_Cmethod + 1)
#define _Mglc_Cdecl_at_nest_limit (8)
#define _Mglc_Eexpr_type_Cint (_Mglc_Eexpr_type_Cfvar + 1)
#define _Mglc_Eexpr_type_Ccvar (_Mglc_Eexpr_type_Cint + 1)
#define _Mglc_Eexpr_type_Cstr (_Mglc_Eexpr_type_Ccvar + 1)
#define _Mglc_Eexpr_type_Cindex (_Mglc_Eexpr_type_Cstr + 1)
#define _Mglc_Eexpr_type_Cunary (_Mglc_Eexpr_type_Cindex + 1)
#define _Mglc_Eexpr_type_Ccompare (_Mglc_Eexpr_type_Cunary + 1)
#define _Mglc_Eexpr_type_Cbool (_Mglc_Eexpr_type_Ccompare + 1)
#define _Mglc_Eexpr_type_Cnull (_Mglc_Eexpr_type_Cbool + 1)
#define _Mglc_Eexpr_type_Ccast_fast (_Mglc_Eexpr_type_Cnull + 1)
#define _Mglc_Eexpr_type_Cref (_Mglc_Eexpr_type_Ccast_fast + 1)
#define _Mglc_Eexpr_type_Cchar (_Mglc_Eexpr_type_Cref + 1)
#define _Mglc_Eexpr_type_Csize_of_type (_Mglc_Eexpr_type_Cchar + 1)
#define _Mglc_Ecvar_Cnil (-1)
#define _Mglc_Ecvar_flags_Cas_enum (2)
#define _Mglc_Estruct_flags_Cunion (4)
#define _Mglc_Estruct_flags_Cno_decl (2)
#define _Mglc_Estmt_type_Cswitch (_Mglc_Estmt_type_Cbreak + 1)
#define _Mglc_Estmt_type_Ccase (_Mglc_Estmt_type_Cswitch + 1)
#define _Mglc_Estmt_type_Cdefault (_Mglc_Estmt_type_Ccase + 1)
#define _Mglc_Estmt_type_Ccase_end (_Mglc_Estmt_type_Cdefault + 1)
#define _Mglc_Estmt_type_Cdefault_end (_Mglc_Estmt_type_Ccase_end + 1)
#define _Mglc_Estmt_type_Cswitch_end (_Mglc_Estmt_type_Cdefault_end + 1)
#define _Mglc_Cdebug_rd_wr (true)
#define _Mglc_Efunc_C0 (_Mglc_Efunc_Cnil + 1)
#define _Mglc_Efunc_C1 (_Mglc_Efunc_C0 + 1)
#define _Mglc_Elvar_flags_Cset_expr (1)
#define _Mglc_Elvar_flags_C0 0
#define _Mglc_Estmt_type_Cnil (255)
#define _Mglc_Cdecl_var_size_limit (8)
#define _Mglc_Etoken_Cgrave_true (_Mglc_Etoken_Cchar2 + 1)
#define _Mglc_Etoken_Cgrave_false (_Mglc_Etoken_Cgrave_true + 1)
#define _Mglc_Etoken_Cgrave_null (_Mglc_Etoken_Cgrave_false + 1)
#define _Mglc_Etoken_Clparen_amp_amp_comma_space (_Mglc_Etoken_Cgrave_null + 1)
#define _Mglc_Etoken_Clparen_pipe_pipe_comma_space (_Mglc_Etoken_Clparen_amp_amp_comma_space + 1)
#define _Mglc_Etoken_Cspace_plus_space (_Mglc_Etoken_Clparen_pipe_pipe_comma_space + 1)
#define _Mglc_Etoken_Cspace_minus_space (_Mglc_Etoken_Cspace_plus_space + 1)
#define _Mglc_Etoken_Cspace_mul_space (_Mglc_Etoken_Cspace_minus_space + 1)
#define _Mglc_Etoken_Cspace_div_space (_Mglc_Etoken_Cspace_mul_space + 1)
#define _Mglc_Etoken_Cspace_langle_langle_space (_Mglc_Etoken_Cspace_div_space + 1)
#define _Mglc_Etoken_Cspace_rangle_rangle_space (_Mglc_Etoken_Cspace_langle_langle_space + 1)
#define _Mglc_Etoken_Cspace_amp_space (_Mglc_Etoken_Cspace_rangle_rangle_space + 1)
#define _Mglc_Etoken_Cspace_pipe_space (_Mglc_Etoken_Cspace_amp_space + 1)
#define _Mglc_Etoken_Cspace_xor_space (_Mglc_Etoken_Cspace_pipe_space + 1)
#define _Mglc_Etoken_Cspace_equal_equal_space (_Mglc_Etoken_Cspace_xor_space + 1)
#define _Mglc_Etoken_Cspace_expoint_equal_space (_Mglc_Etoken_Cspace_equal_equal_space + 1)
#define _Mglc_Etoken_Cspace_langle_space (_Mglc_Etoken_Cspace_expoint_equal_space + 1)
#define _Mglc_Etoken_Cspace_langle_equal_space (_Mglc_Etoken_Cspace_langle_space + 1)
#define _Mglc_Etoken_Cspace_rangle_space (_Mglc_Etoken_Cspace_langle_equal_space + 1)
#define _Mglc_Etoken_Cspace_rangle_equal_space (_Mglc_Etoken_Cspace_rangle_space + 1)
#define _Mglc_Etoken_Chash (_Mglc_Etoken_Cspace_rangle_equal_space + 1)
#define _Mglc_Etoken_Cspace_plus_equal_space (_Mglc_Etoken_Chash + 1)
#define _Mglc_Etoken_Cspace_minus_equal_space (_Mglc_Etoken_Cspace_plus_equal_space + 1)
#define _Mglc_Etoken_Cspace_mul_equal_space (_Mglc_Etoken_Cspace_minus_equal_space + 1)
#define _Mglc_Etoken_Cspace_div_equal_space (_Mglc_Etoken_Cspace_mul_equal_space + 1)
#define _Mglc_Etoken_Cspace_lshift_equal_space (_Mglc_Etoken_Cspace_div_equal_space + 1)
#define _Mglc_Etoken_Cspace_rshift_equal_space (_Mglc_Etoken_Cspace_lshift_equal_space + 1)
#define _Mglc_Etoken_Cspace_and_equal_space (_Mglc_Etoken_Cspace_rshift_equal_space + 1)
#define _Mglc_Etoken_Cspace_or_equal_space (_Mglc_Etoken_Cspace_and_equal_space + 1)
#define _Mglc_Etoken_Cspace_xor_equal_space (_Mglc_Etoken_Cspace_or_equal_space + 1)
#define _Mglc_Etoken_Cspace_colon_equal_space (_Mglc_Etoken_Cspace_xor_equal_space + 1)
#define _Mglc_Etoken_Clcbrace_do (_Mglc_Etoken_Cspace_colon_equal_space + 1)
#define _Mglc_Etoken_Clcbrace_while (_Mglc_Etoken_Clcbrace_do + 1)
#define _Mglc_Etoken_Clcbrace_if (_Mglc_Etoken_Clcbrace_while + 1)
#define _Mglc_Etoken_Clcbrace_elif (_Mglc_Etoken_Clcbrace_if + 1)
#define _Mglc_Etoken_Clcbrace_else (_Mglc_Etoken_Clcbrace_elif + 1)
#define _Mglc_Etoken_Cexpoint (_Mglc_Etoken_Clcbrace_else + 1)
#define _Mglc_Etoken_Clcbrace_switch (_Mglc_Etoken_Cexpoint + 1)
#define _Mglc_Etoken_Cspace_at_fall_through (_Mglc_Etoken_Clcbrace_switch + 1)
#define _Mglc_Etoken_Clcbrace_case (_Mglc_Etoken_Cspace_at_fall_through + 1)
#define _Mglc_Etoken_Clcbrace_default (_Mglc_Etoken_Clcbrace_case + 1)
#define _Mglc_Etoken_Clcbrace_continue (_Mglc_Etoken_Clcbrace_default + 1)
#define _Mglc_Etoken_Clcbrace_break (_Mglc_Etoken_Clcbrace_continue + 1)
#define _Mglc_Etoken_Clcbrace_return (_Mglc_Etoken_Clcbrace_break + 1)
#define _Mglc_Etoken_Clcbrace_plus_or_space (_Mglc_Etoken_Clcbrace_return + 1)
#define _Mglc_Etoken_Cspace_at_extern (_Mglc_Etoken_Clcbrace_plus_or_space + 1)
#define _Mglc_Etoken_Cscolon_space (_Mglc_Etoken_Cspace_at_extern + 1)
#define _Mglc_Etoken_Cspace_at_union (_Mglc_Etoken_Cscolon_space + 1)
#define _Mglc_Etoken_Clcbrace_gvar (_Mglc_Etoken_Cspace_at_union + 1)
typedef int32_t _Mglc_Efunc;
typedef int32_t _Mglc_Einclude;
typedef int32_t _Mstdc_Efile;
typedef int32_t _Mstdc_Eopen_flags;
typedef int32_t _Mstdc_Eexit;
typedef int32_t _Mstdc_Eseek;
typedef int32_t _Mglc_Eat;
typedef uint8_t _Mglc_Ename_type;
typedef int32_t _Mglc_Eid;
typedef uint8_t _Mglc_Ebasic_type_id;
typedef uint32_t _Mglc_Efunc_flags;
typedef uint32_t _Mglc_Evar_flags;
typedef int32_t _Mglc_Eexpr;
typedef uint8_t _Mglc_Estmt_type;
typedef uint8_t _Mglc_Estmt_space_flags;
typedef int32_t _Mglc_Elvar;
typedef uint8_t _Mglc_Elvar_flags;
typedef int32_t _Mglc_Estruct;
typedef uint8_t _Mglc_Estruct_flags;
typedef int32_t _Mglc_Etoken;
typedef uint8_t _Mglc_Eassign;
typedef uint8_t _Mglc_Emath;
typedef uint8_t _Mglc_Ebools;
typedef uint8_t _Mglc_Eexpr_int;
typedef uint8_t _Mglc_Eunary;
typedef uint8_t _Mglc_Ecompare;
typedef int32_t _Mglc_Ecvar;
typedef uint8_t _Mglc_Ecvar_flags;
typedef int32_t _Mglc_Egvar;
typedef uint8_t _Mglc_Egvar_flags;
typedef int32_t _Mglc_Eenum;
typedef uint8_t _Mglc_Eenum_flags;
typedef uint32_t _Mglc_Efunc_flags2;
typedef uint8_t _Mglc_Eexpr_type;
typedef uint8_t _Mglc_Eexpr_flags;
typedef int32_t _Mglc_Ealias;
union _Mglc_Srdr;
union _Mglc_Srdr {
void* _Fref;
size_t _Fpos;
uint8_t* _F1;
char* _Fchar;
uint32_t* _F4;
};
union _Mglc_Swtr;
union _Mglc_Swtr {
void* _Fref;
size_t _Fpos;
uint8_t* _F1;
uint32_t* _F4;
};
union _Mglc_Sat_name;
union _Mglc_Sat_name {
_Mglc_Eid _Fid;
_Mglc_Ebasic_type_id _Fbasic;
};
struct _Mglc_Sat;
struct _Mglc_Sat {
_Mglc_Ename_type _Ftype;
_Mglc_Eat _Fparent;
union _Mglc_Sat_name _Fname;
};
struct _Mglc_Stype_info;
struct _Mglc_Stype_info {
int8_t _Fref_v[_Mglc_Ctype_info_star_limit];
int8_t _Farray_c;
int8_t _Fstar_c;
bool _Fbuilt_in;
bool _Fconst;
};
struct _Mglc_Sdecl_var;
struct _Mglc_Sdecl_var {
_Mglc_Eid _Fname;
_Mglc_Eat _Ftype;
_Mglc_Evar_flags _Fflags;
_Mglc_Eid _Freal_name;
struct _Mglc_Stype_info _Ftype_info;
uint8_t _Fsize_c;
_Mglc_Eexpr* _Fsize_expr_v;
};
struct _Mglc_Sstmt;
struct _Mglc_Sstmt {
int32_t _Fbegin_row;
int32_t _Fbegin_col;
int32_t _Fend_row;
int32_t _Fend_col;
_Mglc_Estmt_type _Ftype;
struct _Mglc_Sstmt* _Fstmt_next;
};
struct _Mglc_Sstmt_space;
struct _Mglc_Sstmt_space {
struct _Mglc_Sstmt _Fbase;
struct _Mglc_Sstmt_space* _Fparent;
_Mglc_Estmt_space_flags _Fflags;
struct _Mglc_Sstmt* _Fstmt_first;
struct _Mglc_Sstmt* _Fstmt_last;
int32_t _Flvar_c;
int32_t _Flvar_cap;
_Mglc_Elvar* _Flvar_v;
};
struct _Mglc_Slvar;
struct _Mglc_Slvar {
int32_t _Frow;
int32_t _Fcol;
struct _Mglc_Sdecl_var _Fdecl;
_Mglc_Elvar_flags _Fflags;
_Mglc_Eexpr _Fset_expr;
};
struct _Mglc_Sfarg;
struct _Mglc_Sfarg {
int32_t _Frow;
int32_t _Fcol;
struct _Mglc_Sdecl_var _Fdecl;
};
struct _Mglc_Sdecl_func;
struct _Mglc_Sdecl_func {
int32_t _Fbegin_row;
int32_t _Fbegin_col;
int32_t _Fend_row;
int32_t _Fend_col;
_Mglc_Einclude _Finclude;
_Mglc_Eat _Fat;
_Mglc_Efunc_flags _Fflags;
_Mglc_Eid _Freal_name;
_Mglc_Eid _Fcase;
struct _Mglc_Sdecl_var _Fdecl;
struct _Mglc_Sstmt_space* _Fstmt_space;
_Mglc_Elvar _Flvar_c;
_Mglc_Elvar _Flvar_cap;
struct _Mglc_Slvar** _Flvar_v;
int8_t _Fthis_idx;
int8_t _Fthis_group;
int8_t _Fgroup_c;
int8_t _Fgroup_v[_Mglc_Cexpr_carg_group_limit];
uint8_t _Ffarg_c;
struct _Mglc_Sfarg _Ffarg_v[0];
};
struct _Mglc_Sfvar;
struct _Mglc_Sfvar {
struct _Mglc_Sdecl_var _Fdecl;
};
struct _Mglc_Sstruct;
struct _Mglc_Sstruct {
int32_t _Fbegin_row;
int32_t _Fbegin_col;
int32_t _Fend_row;
int32_t _Fend_col;
_Mglc_Einclude _Finclude;
_Mglc_Eat _Fat;
_Mglc_Estruct_flags _Fflags;
_Mglc_Eid _Freal_name;
uint32_t _Ffvar_c;
struct _Mglc_Sfvar _Ffvar_v[0];
};
struct _Mglc_Sparser;
struct _Mglc_Sparser {
};
struct _Mglc_Slexer;
struct _Mglc_Slexer {
uint8_t* _Fcontent;
uint8_t* _Fstart;
uint8_t* _Fcursor;
uint8_t* _Flimit;
uint8_t* _Fmarker;
uint8_t* _Fctx_marker;
};
struct _Mglc_Stoken;
struct _Mglc_Stoken {
int32_t _Frow;
int32_t _Fcol;
int32_t _Fid;
int32_t _Fid2;
int32_t _Fval[12];
};
struct _Mglc_Scvar;
struct _Mglc_Scvar {
int32_t _Frow;
int32_t _Fcol;
_Mglc_Einclude _Finclude;
_Mglc_Eat _Fat;
_Mglc_Ecvar_flags _Fflags;
struct _Mglc_Sdecl_var _Fdecl;
_Mglc_Eexpr _Fexpr_set;
_Mglc_Ecvar _Flast_cvar;
};
struct _Mglc_Sdecl_gvar;
struct _Mglc_Sdecl_gvar {
int32_t _Frow;
int32_t _Fcol;
_Mglc_Einclude _Finclude;
_Mglc_Eat _Fat;
_Mglc_Egvar_flags _Fflags;
struct _Mglc_Sdecl_var _Fdecl;
};
struct _Mglc_Senum;
struct _Mglc_Senum {
int32_t _Fbegin_row;
int32_t _Fbegin_col;
int32_t _Fend_row;
int32_t _Fend_col;
_Mglc_Einclude _Finclude;
_Mglc_Eat _Fat;
_Mglc_Eat _Fbase_type;
_Mglc_Eenum_flags _Fflags;
_Mglc_Eid _Freal_name;
};
struct _Mglc_Sexpr;
struct _Mglc_Sexpr {
_Mglc_Eexpr_type _Ftype;
_Mglc_Eexpr_flags _Fflags;
};
struct _Mglc_Scarg;
struct _Mglc_Scarg {
int8_t _Fref;
_Mglc_Eexpr _Fexpr;
};
struct _Mglc_Sexpr_func;
struct _Mglc_Sexpr_func {
struct _Mglc_Sexpr _Fbase;
_Mglc_Eat _Fat;
_Mglc_Eid _Ffunc_name;
uint8_t _Fgroup_c;
uint8_t _Fgroup_v[_Mglc_Cexpr_carg_group_limit];
uint8_t _Fcarg_c;
struct _Mglc_Scarg _Fcarg_v[0];
};
struct _Mglc_Sexpr_method;
struct _Mglc_Sexpr_method {
struct _Mglc_Sexpr _Fbase;
_Mglc_Eexpr _Fthis;
_Mglc_Eid _Ffunc_name;
uint8_t _Fgroup_c;
uint8_t _Fgroup_v[_Mglc_Cexpr_carg_group_limit];
uint8_t _Fcarg_c;
struct _Mglc_Scarg _Fcarg_v[0];
};
struct _Mglc_Sexpr_str_node;
struct _Mglc_Sexpr_str_node {
struct _Mglc_Sexpr_str_node* _Fnext;
int32_t _Flen;
char _Fbuf[0];
};
struct _Mglc_Sexpr_str;
struct _Mglc_Sexpr_str {
struct _Mglc_Sexpr _Fbase;
int32_t _Fnode_c;
struct _Mglc_Sexpr_str_node* _Ffirst;
struct _Mglc_Sexpr_str_node* _Flast;
};
struct _Mglc_Sstmt_expr;
struct _Mglc_Sstmt_expr {
struct _Mglc_Sstmt _Fbase;
_Mglc_Eexpr _Fexpr;
};
struct _Mglc_Svalue;
struct _Mglc_Svalue {
int8_t _Fref;
bool _Fparen;
_Mglc_Eat _Ftype;
struct _Mglc_Stype_info _Finfo;
};
struct _Mglc_Sstmt_return;
struct _Mglc_Sstmt_return {
struct _Mglc_Sstmt _Fbase;
_Mglc_Eexpr _Fexpr;
struct _Mglc_Svalue _Fval;
};
struct _Mglc_Sstmt_continue;
struct _Mglc_Sstmt_continue {
struct _Mglc_Sstmt _Fbase;
uint8_t _Fnest;
};
struct _Mglc_Sstmt_break;
struct _Mglc_Sstmt_break {
struct _Mglc_Sstmt _Fbase;
uint8_t _Fnest;
};
struct _Mglc_Sexpr_lvar;
struct _Mglc_Sexpr_lvar {
struct _Mglc_Sexpr _Fbase;
_Mglc_Elvar _Flvar;
};
struct _Mglc_Sexpr_gvar;
struct _Mglc_Sexpr_gvar {
struct _Mglc_Sexpr _Fbase;
_Mglc_Eat _Fat;
_Mglc_Eid _Fname;
};
struct _Mglc_Sexpr_fvar;
struct _Mglc_Sexpr_fvar {
struct _Mglc_Sexpr _Fbase;
_Mglc_Eexpr _Fexpr;
_Mglc_Eid _Fmember;
};
struct _Mglc_Sexpr_assign;
struct _Mglc_Sexpr_assign {
struct _Mglc_Sexpr _Fbase;
_Mglc_Eexpr _Fleft;
_Mglc_Eexpr _Fright;
_Mglc_Eassign _Ftype;
};
struct _Mglc_Sexpr_math_item;
struct _Mglc_Sexpr_math_item {
_Mglc_Eexpr _Fexpr;
};
struct _Mglc_Sexpr_math;
struct _Mglc_Sexpr_math {
struct _Mglc_Sexpr _Fbase;
_Mglc_Eexpr _Fleft;
_Mglc_Eexpr _Fright;
_Mglc_Emath _Ftype;
uint8_t _Fitem_c;
uint8_t _Fitem_cap;
struct _Mglc_Sexpr_math_item* _Fitem_v;
};
struct _Mglc_Sexpr_bools_item;
struct _Mglc_Sexpr_bools_item {
_Mglc_Eexpr _Fexpr;
};
struct _Mglc_Sexpr_bools;
struct _Mglc_Sexpr_bools {
struct _Mglc_Sexpr _Fbase;
_Mglc_Eexpr _Fleft;
_Mglc_Eexpr _Fright;
_Mglc_Ebools _Ftype;
uint8_t _Fitem_c;
uint8_t _Fitem_cap;
struct _Mglc_Sexpr_bools_item* _Fitem_v;
};
struct _Mglc_Srow_col;
struct _Mglc_Srow_col {
int32_t _Frow;
int32_t _Fcol;
};
struct _Mglc_Sexpr_int;
struct _Mglc_Sexpr_int {
struct _Mglc_Sexpr _Fbase;
int32_t _Fvalue;
_Mglc_Eexpr_int _Ftype;
};
struct _Mglc_Sexpr_size_of_type;
struct _Mglc_Sexpr_size_of_type {
struct _Mglc_Sexpr _Fbase;
_Mglc_Eat _Ftype;
};
struct _Mglc_Sexpr_null;
struct _Mglc_Sexpr_null {
struct _Mglc_Sexpr _Fbase;
};
struct _Mglc_Sexpr_cvar;
struct _Mglc_Sexpr_cvar {
struct _Mglc_Sexpr _Fbase;
_Mglc_Eat _Fat;
_Mglc_Eid _Fname;
};
struct _Mglc_Sexpr_unary;
struct _Mglc_Sexpr_unary {
struct _Mglc_Sexpr _Fbase;
_Mglc_Eexpr _Fexpr;
_Mglc_Eunary _Ftype;
};
struct _Mglc_Sexpr_ref;
struct _Mglc_Sexpr_ref {
struct _Mglc_Sexpr _Fbase;
_Mglc_Eexpr _Fexpr;
};
struct _Mglc_Sexpr_cast_fast;
struct _Mglc_Sexpr_cast_fast {
struct _Mglc_Sexpr _Fbase;
_Mglc_Eexpr _Fexpr;
_Mglc_Eat _Ftype;
};
struct _Mglc_Sexpr_index;
struct _Mglc_Sexpr_index {
struct _Mglc_Sexpr _Fbase;
_Mglc_Eexpr _Fleft;
_Mglc_Eexpr _Fright;
};
struct _Mglc_Sstmt_switch;
struct _Mglc_Sstmt_switch {
struct _Mglc_Sstmt _Fbase;
_Mglc_Eexpr _Fexpr;
_Mglc_Eexpr _Fcases;
};
struct _Mglc_Sstmt_case_item;
struct _Mglc_Sstmt_case_item {
_Mglc_Eexpr _Fexpr;
};
struct _Mglc_Sstmt_case;
struct _Mglc_Sstmt_case {
struct _Mglc_Sstmt _Fbase;
bool _Ffall_through;
uint32_t _Fexpr_c;
struct _Mglc_Sstmt_case_item _Fexpr_v[0];
};
struct _Mglc_Sstmt_case_end;
struct _Mglc_Sstmt_case_end {
struct _Mglc_Sstmt _Fbase;
};
struct _Mglc_Sstmt_default;
struct _Mglc_Sstmt_default {
struct _Mglc_Sstmt _Fbase;
bool _Ffall_through;
};
struct _Mglc_Sstmt_default_end;
struct _Mglc_Sstmt_default_end {
struct _Mglc_Sstmt _Fbase;
};
struct _Mglc_Sstmt_switch_end;
struct _Mglc_Sstmt_switch_end {
struct _Mglc_Sstmt _Fbase;
};
struct _Mglc_Sstmt_if;
struct _Mglc_Sstmt_if {
struct _Mglc_Sstmt _Fbase;
bool _Fnot;
_Mglc_Eexpr _Fexpr;
};
struct _Mglc_Sstmt_do_end;
struct _Mglc_Sstmt_do_end {
struct _Mglc_Sstmt _Fbase;
struct _Mglc_Sstmt_do* _Fdo;
};
struct _Mglc_Sstmt_do;
struct _Mglc_Sstmt_do {
struct _Mglc_Sstmt _Fbase;
_Mglc_Eexpr _Fexpr;
struct _Mglc_Sstmt_space* _Fcontinue;
struct _Mglc_Sstmt_do_end* _Fend;
};
struct _Mglc_Sstmt_while_end;
struct _Mglc_Sstmt_while_end {
struct _Mglc_Sstmt _Fbase;
struct _Mglc_Sstmt_while* _Fwhile;
};
struct _Mglc_Sstmt_while;
struct _Mglc_Sstmt_while {
struct _Mglc_Sstmt _Fbase;
_Mglc_Eexpr _Fexpr;
struct _Mglc_Sstmt_space* _Fcontinue;
struct _Mglc_Sstmt_while_end* _Fend;
};
union _Mglc_Snest;
union _Mglc_Snest {
struct _Mglc_Sstmt_do* _Fdo;
struct _Mglc_Sstmt_while* _Fwhile;
void* _Fref;
};
struct _Mglc_Sstmt_if_else;
struct _Mglc_Sstmt_if_else {
struct _Mglc_Sstmt _Fbase;
};
struct _Mglc_Sstmt_if_end;
struct _Mglc_Sstmt_if_end {
struct _Mglc_Sstmt _Fbase;
};
struct _Mglc_Sexpr_compare;
struct _Mglc_Sexpr_compare {
struct _Mglc_Sexpr _Fbase;
_Mglc_Eexpr _Fleft;
_Mglc_Eexpr _Fright;
_Mglc_Ecompare _Ftype;
};
struct _Mglc_Sexpr_bool;
struct _Mglc_Sexpr_bool {
struct _Mglc_Sexpr _Fbase;
bool _Fvalue;
};
struct _Mglc_Sexpr_char;
struct _Mglc_Sexpr_char {
struct _Mglc_Sexpr _Fbase;
char _Fvalue;
};
struct _Mglc_Sstmt_if_elif;
struct _Mglc_Sstmt_if_elif {
struct _Mglc_Sstmt _Fbase;
bool _Fnot;
_Mglc_Eexpr _Fexpr;
};
_Mglc_Efunc _Gfunc_main;
_Mglc_Einclude _Gdecl_include;
char* input_path;
int32_t _Gid_cap;
char** _Gid_str_v;
uint8_t* _Gid_len_v;
int32_t _Ginclude_cap;
char** _Ginclude_str_v;
uint8_t* _Ginclude_len_v;
_Mglc_Eat _Gat_cap;
struct _Mglc_Sat* _Gat_v;
_Mglc_Eat _Gat_c;
_Mglc_Efunc _Gfunc_cap;
struct _Mglc_Sdecl_func** _Gfunc_v;
_Mglc_Estruct _Gstruct_cap;
struct _Mglc_Sstruct** _Gstruct_v;
uint32_t _Gdecl_fvar_cap;
struct _Mglc_Sdecl_var* _Gdecl_fvar_v;
extern int32_t _Grow;
extern int32_t _Gcol;
extern int32_t _Glast_row;
extern int32_t _Glast_col;
int32_t _Gid_c;
uint8_t* _Gid_in_header_v;
uint32_t* _Gid_in_header_idx_v;
uint32_t* _Gid_in_header_id_v;
int32_t _Ginclude_c;
uint8_t* _Gat_in_header_v;
uint32_t* _Gat_in_header_idx_v;
uint32_t* _Gat_in_header_at_v;
int32_t _Gid_in_header_c;
int32_t _Gat_in_header_c;
int32_t _Gquick_alloc_cap;
void* _Gquick_alloc_v;
int32_t _Gquick_alloc_c;
_Mglc_Ecvar _Gcvar_c;
struct _Mglc_Scvar* _Gcvar_v;
_Mglc_Egvar _Ggvar_c;
struct _Mglc_Sdecl_gvar* _Ggvar_v;
_Mglc_Eenum _Genum_c;
struct _Mglc_Senum** _Genum_v;
_Mglc_Estruct _Gstruct_c;
_Mglc_Efunc _Gfunc_c;
_Mglc_Eid _Gdecl_func_name;
int32_t _Gdecl_func_row;
int32_t _Gdecl_func_col;
_Mglc_Efunc_flags _Gdecl_func_flags;
_Mglc_Efunc_flags2 _Gdecl_func_flags2;
int32_t _Gdecl_farg_c;
int8_t _Gdecl_farg_group_c;
int8_t _Gdecl_farg_group_v[_Mglc_Cexpr_carg_group_limit];
int8_t _Gdecl_func_this_idx;
int8_t _Gdecl_func_this_group;
_Mglc_Eid _Gdecl_func_real_name;
_Mglc_Eid _Gdecl_func_case;
struct _Mglc_Sstmt_space* _Gdecl_func_space;
struct _Mglc_Sstmt_space* _Gdecl_func_ctx_space;
struct _Mglc_Sdecl_func* _Gctx_func;
int32_t _Gnest_id;
_Mglc_Eat _Gdecl_at;
struct _Mglc_Sdecl_var _Gdecl_var;
struct _Mglc_Sfarg* _Gdecl_farg_v;
uint32_t _Gdecl_fvar_c;
int32_t _Gdecl_struct_row;
int32_t _Gdecl_struct_col;
_Mglc_Eat _Gdecl_struct_at;
_Mglc_Estruct_flags _Gdecl_struct_flags;
_Mglc_Eid _Gdecl_struct_real_name;
int32_t _Gdecl_var_row;
int32_t _Gdecl_var_col;
int32_t _Gdecl_farg_cap;
int8_t _Gexpr_call_c;
uint8_t _Gexpr_call_carg_c[_Mglc_Cexpr_call_nest_limit];
uint8_t _Gexpr_call_cgrp_c[_Mglc_Cexpr_call_nest_limit];
uint8_t _Gexpr_call_cgrp_v[_Mglc_Cexpr_call_nest_limit][_Mglc_Cexpr_carg_group_limit];
_Mglc_Eexpr _Gexpr_call_carg_v[_Mglc_Cexpr_call_nest_limit][_Mglc_Cglc_carg_limit];
uint8_t _Gnest_stack_c;
int32_t _Gdecl_include_row;
int32_t _Gdecl_include_col;
_Mglc_Eat _Gbuild_at;
_Mglc_Eat _Gdecl_at_v[_Mglc_Cdecl_at_nest_limit];
uint8_t _Gdecl_at_c;
_Mglc_Ealias _Gat_alias_c;
_Mglc_Eid* _Gat_alias_name_v;
struct _Mglc_Srow_col* _Gat_alias_pos_v;
_Mglc_Ealias _Gat_alias_cap;
_Mglc_Eat* _Gat_alias_at_v;
_Mglc_Egvar _Ggvar_cap;
int32_t _Gdecl_enum_row;
int32_t _Gdecl_enum_col;
_Mglc_Eat _Gdecl_enum_at;
_Mglc_Eenum_flags _Gdecl_enum_flags;
_Mglc_Ecvar _Gdecl_enum_last_cvar;
_Mglc_Eenum _Genum_cap;
_Mglc_Ecvar _Glast_cvar;
_Mglc_Ecvar _Gcvar_cap;
extern int32_t _Gstring_len;
extern char* _Gstring_buf;
uint32_t _Gswitch_expr_c;
uint32_t _Gswitch_expr_cap;
_Mglc_Eexpr* _Gswitch_expr_v;
int32_t _Gnest_stack_id_v[64];
union _Mglc_Snest _Gnest_stack_ptr_v[64];
int32_t _Gexpr_c;
int32_t _Gexpr_cap;
struct _Mglc_Sexpr** _Gexpr_v;
int32_t main(int32_t _Largc_0, char** _Largv_1);
void _Mglc_Pexport_0();
void _Mglc_Pquick_alloc_init_0();
bool _Mstdc_Efile_Popen_3(_Mstdc_Efile* _Lfile_0, char* _Lpath_1, _Mstdc_Eopen_flags _Lflags_2);
void _Mglc_Pget_row_col_4(int32_t* _Lout_row_0, int32_t* _Lout_col_1, void* _Lend_2, void* _Lbegin_3);
void _Mglc_Pparse_comment_4(union _Mglc_Srdr* _Lr_0, union _Mglc_Swtr* _Lw_1, char _Lending_2, void* _Lin_data_3);
void _Mglc_Pparse_string_4(union _Mglc_Srdr* _Lr_0, union _Mglc_Swtr* _Lw_1, char _Lending_2, void* _Lin_data_3);
void _Mglc_Pparse_str_init_1(int32_t _Lmax_size_0);
struct _Mglc_Sparser* _Mglc_Sparser_Palloc_0();
void _Mglc_Slexer_Pinit_3(struct _Mglc_Slexer* _Llex_0, uint8_t* _Ldata_1, size_t _Lsize_2);
_Mglc_Etoken glc_lexer_scan(struct _Mglc_Slexer* _Llex_0);
int32_t _Mglc_Slexer_Pget_id_3(struct _Mglc_Slexer* _Llex_0, uint8_t _Lbegin_1, uint8_t _Lend_2);
void glcParse(struct _Mglc_Sparser* _Lpsr_0, _Mglc_Etoken _Lt_1, struct _Mglc_Stoken* _Ltok_2);
int32_t _Mglc_Pchar_escape_value_1(char _Lc_0);
uint32_t _Mglc_Slexer_Pget_num_dec_1(struct _Mglc_Slexer* _Llex_0);
uint32_t _Mglc_Slexer_Pget_num_oct_1(struct _Mglc_Slexer* _Llex_0);
int32_t _Mglc_Slexer_Pget_include_1(struct _Mglc_Slexer* _Llex_0);
void _Mglc_Sparser_Pfree_1(struct _Mglc_Sparser* _Lpsr_0);
void* qalloc(int32_t _Lsize_0);
void _Mglc_Swtr_Pn1_2(union _Mglc_Swtr* _Lw_0, uint8_t _Ln_1);
void _Mglc_Swtr_Pcopy_3(union _Mglc_Swtr* _Lw_0, void* _Ldata_1, int32_t _Lsize_2);
void _Mglc_Ename_type_Pwr_2(_Mglc_Ename_type _Li_0, union _Mglc_Swtr* _Lw_1);
void _Mglc_Ebasic_type_id_Pwr_2(_Mglc_Ebasic_type_id _Le_0, union _Mglc_Swtr* _Lw_1);
void _Mglc_Eat_Pwr_3(_Mglc_Eat _Lat_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2);
void _Mglc_Eid_Pwr_3(_Mglc_Eid _Lid_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2);
void _Mglc_Pwrite_cvar_2(union _Mglc_Swtr* _Lw_0, bool _Lheader_1);
void _Mglc_Pwrite_gvar_2(union _Mglc_Swtr* _Lw_0, bool _Lheader_1);
void _Mglc_Pwrite_enum_2(union _Mglc_Swtr* _Lw_0, bool _Lheader_1);
void _Mglc_Pwrite_struct_2(union _Mglc_Swtr* _Lw_0, bool _Lheader_1);
void _Mglc_Pwrite_func_2(union _Mglc_Swtr* _Lw_0, bool _Lheader_1);
bool _Mstdc_Efile_Popen_4(_Mstdc_Efile* _Lfile_0, char* _Lpath_1, _Mstdc_Eopen_flags _Lflags_2, int32_t _Lmode_3);
void _Mglc_Eat_Pwr_header_2(_Mglc_Eat _Lid_0, union _Mglc_Swtr* _Lw_1);
void _Mglc_Eid_Pwr_header_2(_Mglc_Eid _Lid_0, union _Mglc_Swtr* _Lw_1);
void _Mglc_Pdecl_func_begin_3(_Mglc_Eid _Lname_0, int32_t _Lrow_1, int32_t _Lcol_2);
void _Mglc_Pdecl_func_end_2(int32_t _Lrow_0, int32_t _Lcol_1);
void _Mglc_Pdecl_struct_end_2(int32_t _Lrow_0, int32_t _Lcol_1);
void _Mglc_Pdecl_var_begin_3(_Mglc_Eid _Lname_0, int32_t _Lrow_1, int32_t _Lcol_2);
void _Mglc_Pdecl_var_attr_real_name_1(_Mglc_Eid _Lname_0);
void _Mglc_Pdecl_var_attr_extern_0();
void _Mglc_Pdecl_var_attr_no_decl_0();
void _Mglc_Pdecl_var_end_0();
void _Mglc_Pdecl_var_as_farg_2(int32_t _Lrow_0, int32_t _Lcol_1);
void _Mglc_Pfarg_next_group_0();
void _Mglc_Pdecl_var_as_this_0();
void _Mglc_Pdecl_var_as_fvar_0();
void _Mglc_Pfunc_body_end_1(bool _Linline_0);
void _Mglc_Pexpr_push_call_2(int32_t _Lrow_0, int32_t _Lcol_1);
_Mglc_Eexpr _Mglc_Pexpr_pop_func_2(_Mglc_Eat _Lat_0, _Mglc_Eid _Lfunc_name_1);
_Mglc_Eexpr _Mglc_Pexpr_pop_method_2(_Mglc_Eexpr _Lthis_0, _Mglc_Eid _Lfunc_name_1);
void _Mglc_Pcarg_push_1(_Mglc_Eexpr _Lexpr_0);
void _Mglc_Pcarg_push_str_1(_Mglc_Eexpr _Lexpr_0);
void _Mglc_Pcarg_next_group_0();
void _Mglc_Pexpr2stmt_5(_Mglc_Eexpr _Le_0, int32_t _Lbegin_row_1, int32_t _Lbegin_col_2, int32_t _Lend_row_3, int32_t _Lend_col_4);
void _Mglc_Pstmt_return_5(_Mglc_Eexpr _Le_0, int32_t _Lbegin_row_1, int32_t _Lbegin_col_2, int32_t _Lend_row_3, int32_t _Lend_col_4);
void _Mglc_Pstmt_continue_5(_Mglc_Eid _Lid_0, int32_t _Lbegin_row_1, int32_t _Lbegin_col_2, int32_t _Lend_row_3, int32_t _Lend_col_4);
void _Mglc_Pstmt_break_5(_Mglc_Eid _Lid_0, int32_t _Lbegin_row_1, int32_t _Lbegin_col_2, int32_t _Lend_row_3, int32_t _Lend_col_4);
void _Mglc_Pfunc_attr_main_0();
void _Mglc_Pfunc_attr_glc_name_0();
void _Mglc_Pfunc_attr_process_0();
void _Mglc_Pfunc_attr_var_args_0();
void _Mglc_Pfunc_attr_no_decl_0();
void _Mglc_Pfunc_attr_no_body_0();
void _Mglc_Pfunc_attr_real_name_1(_Mglc_Eid _Lname_0);
void _Mglc_Pfunc_attr_case_1(_Mglc_Eid _Lname_0);
_Mglc_Eexpr _Mglc_Pexpr_lvar_4(_Mglc_Eid _Lname_0, uint8_t _Ldecl_1, int32_t _Lrow_2, int32_t _Lcol_3);
_Mglc_Eexpr _Mglc_Pexpr_gvar_2(_Mglc_Eat _Lat_0, _Mglc_Eid _Lname_1);
_Mglc_Eexpr _Mglc_Pexpr_fvar_2(_Mglc_Eexpr _Lexpr_0, _Mglc_Eid _Lmember_1);
_Mglc_Eexpr _Mglc_Pexpr_assign_3(_Mglc_Eexpr _Lleft_0, _Mglc_Eexpr _Lright_1, _Mglc_Eassign _Ltype_2);
_Mglc_Eexpr _Mglc_Pexpr_math_3(_Mglc_Eexpr _Lleft_0, _Mglc_Eexpr _Lright_1, _Mglc_Emath _Ltype_2);
_Mglc_Eexpr _Mglc_Pexpr_math_add_2(_Mglc_Eexpr _Lexpr_0, _Mglc_Eexpr _Lright_1);
_Mglc_Eexpr _Mglc_Pexpr_bools_3(_Mglc_Eexpr _Lleft_0, _Mglc_Eexpr _Lright_1, _Mglc_Ebools _Ltype_2);
_Mglc_Eexpr _Mglc_Pexpr_bools_add_2(_Mglc_Eexpr _Lbools_0, _Mglc_Eexpr _Lright_1);
char* _Mglc_Ptoken_name_1(_Mglc_Etoken _Ltok_0);
void _Mglc_Pdecl_var_type_1(_Mglc_Eat _Ltype_0);
void _Mglc_Pdecl_var_this_0();
void _Mglc_Pstmt_lvar_add_4(_Mglc_Eid _Lname_0, _Mglc_Eexpr _Lset_1, int32_t _Lrow_2, int32_t _Lcol_3);
void _Mglc_Pstmt_lvar_end_2(int32_t _Lend_row_0, int32_t _Lend_col_1);
void _Mglc_Pdecl_include_begin_3(_Mglc_Einclude _Linc_0, int32_t _Lrow_1, int32_t _Lcol_2);
void _Mglc_Pdecl_include_end_0();
void _Mglc_Pdecl_at_basic_1(_Mglc_Ebasic_type_id _Ltype_0);
void _Mglc_Pdecl_at_add_2(_Mglc_Eid _Lname_0, _Mglc_Ename_type _Ltype_1);
void _Mglc_Pdecl_at_begin_2(int32_t _Lrow_0, int32_t _Lcol_1);
void _Mglc_Pdecl_at_begin_struct_3(_Mglc_Eid _Lname_0, int32_t _Lrow_1, int32_t _Lcol_2);
void _Mglc_Pdecl_at_end_0();
void _Mglc_Pdecl_alias_4(_Mglc_Eid _Lname_0, _Mglc_Eat _Lat_1, int32_t _Lrow_2, int32_t _Lcol_3);
void _Mglc_Pat_push_4(_Mglc_Eid _Lname_0, _Mglc_Ename_type _Ltype_1, int32_t _Lrow_2, int32_t _Lcol_3);
_Mglc_Eat _Mglc_Pat_done_0();
void _Mglc_Pat_begin_0();
void _Mglc_Pat_root_0();
void _Mglc_Pat_alias_3(_Mglc_Eid _Lname_0, int32_t _Lrow_1, int32_t _Lcol_2);
void _Mglc_Pat_graves_3(int8_t _Lgraves_0, int32_t _Lrow_1, int32_t _Lcol_2);
_Mglc_Eat _Mglc_Pat_basic_type_1(_Mglc_Ebasic_type_id _Ltype_0);
void _Mglc_Pdecl_var_as_gvar_0();
void _Mglc_Ptype_info_arr_2(_Mglc_Eexpr* _Lexpr_v_0, uint8_t _Lexpr_c_1);
void _Mglc_Ptype_info_ref_1(int8_t _Lc_0);
void _Mglc_Ptype_info_static_0();
void _Mglc_Ptype_info_begin_0();
void _Mglc_Ptype_info_finalize_0();
_Mglc_Eexpr _Mglc_Pexpr_int_2(int32_t _Lvalue_0, _Mglc_Eexpr_int _Ltype_1);
_Mglc_Eexpr _Mglc_Pexpr_size_of_type_1(_Mglc_Eat _Lat_0);
_Mglc_Eexpr _Mglc_Pexpr_null_0();
void _Mglc_Pdecl_at_begin_enum_3(_Mglc_Eid _Lname_0, int32_t _Lrow_1, int32_t _Lcol_2);
void _Mglc_Pdecl_enum_end_3(_Mglc_Eat _Lbase_type_0, int32_t _Lrow_1, int32_t _Lcol_2);
_Mglc_Eexpr _Mglc_Pexpr_cvar_2(_Mglc_Eat _Lat_0, _Mglc_Eid _Lname_1);
void _Mglc_Penum_add_cvar_3(_Mglc_Eid _Lname_0, int32_t _Lrow_1, int32_t _Lcol_2);
void _Mglc_Pdecl_add_cvar_3(_Mglc_Eid _Lname_0, int32_t _Lrow_1, int32_t _Lcol_2);
void _Mglc_Penum_set_cvar_expr_1(_Mglc_Eexpr _Lset_0);
void _Mglc_Pstruct_attr_real_name_1(_Mglc_Eid _Lname_0);
void _Mglc_Pstruct_attr_union_0();
void _Mglc_Pstruct_attr_no_decl_0();
_Mglc_Eexpr _Mglc_Pexpr_str_1(_Mglc_Eexpr _Lprev_0);
_Mglc_Eexpr _Mglc_Pexpr_unary_2(_Mglc_Eexpr _Lexpr_0, _Mglc_Eunary _Ltype_1);
_Mglc_Eexpr _Mglc_Pexpr_ref_1(_Mglc_Eexpr _Lexpr_0);
_Mglc_Eexpr _Mglc_Pexpr_cast_fast_2(_Mglc_Eexpr _Lexpr_0, _Mglc_Eat _Ltype_1);
_Mglc_Eexpr _Mglc_Pexpr_index_3(_Mglc_Eexpr _Lleft_0, _Mglc_Eexpr* _Lright_v_1, int32_t _Lright_c_2);
void _Mglc_Penum_base_begin_0();
void _Mglc_Pstmt_switch_begin_0();
void _Mglc_Pstmt_switch_set_6(_Mglc_Eexpr _Lexpr_0, int32_t _Lbegin_row_1, int32_t _Lbegin_col_2, int32_t _Lend_row_3, int32_t _Lend_col_4, _Mglc_Eexpr _Lcases_5);
void _Mglc_Pstmt_switch_expr_add_1(_Mglc_Eexpr _Lexpr_0);
void _Mglc_Pstmt_switch_case_begin_5(int32_t _Lbegin_row_0, int32_t _Lbegin_col_1, int32_t _Lend_row_2, int32_t _Lend_col_3, bool _Lfall_through_4);
void _Mglc_Pstmt_switch_case_end_0();
void _Mglc_Pstmt_switch_default_begin_5(int32_t _Lbegin_row_0, int32_t _Lbegin_col_1, int32_t _Lend_row_2, int32_t _Lend_col_3, bool _Lfall_through_4);
void _Mglc_Pstmt_switch_default_end_0();
void _Mglc_Pstmt_switch_end_0();
void _Mglc_Pstmt_if_begin_0();
void _Mglc_Pstmt_if_set_6(bool _Lnot_0, _Mglc_Eexpr _Lexpr_1, int32_t _Lbegin_row_2, int32_t _Lbegin_col_3, int32_t _Lend_row_4, int32_t _Lend_col_5);
void _Mglc_Pstmt_if_end_0();
void _Mglc_Pstmt_do_begin_0();
void _Mglc_Pstmt_do_set_6(_Mglc_Eexpr _Lexpr_0, int32_t _Lbegin_row_1, int32_t _Lbegin_col_2, int32_t _Lend_row_3, int32_t _Lend_col_4, struct _Mglc_Sstmt_space* _Lcontinue_5);
void _Mglc_Pstmt_do_end_0();
void _Mglc_Pstmt_while_begin_0();
void _Mglc_Pstmt_while_set_6(_Mglc_Eexpr _Lexpr_0, int32_t _Lbegin_row_1, int32_t _Lbegin_col_2, int32_t _Lend_row_3, int32_t _Lend_col_4, struct _Mglc_Sstmt_space* _Lcontinue_5);
void _Mglc_Pstmt_while_end_0();
void _Mglc_Pstmt_elif_begin_0();
void _Mglc_Pstmt_elif_set_6(bool _Lnot_0, _Mglc_Eexpr _Lexpr_1, int32_t _Lbegin_row_2, int32_t _Lbegin_col_3, int32_t _Lend_row_4, int32_t _Lend_col_5);
void _Mglc_Pstmt_elif_end_0();
void _Mglc_Pstmt_else_set_0();
void _Mglc_Pstmt_else_end_0();
void _Mglc_Pstmt_if_end_ifs_0();
struct _Mglc_Sstmt_space* _Mglc_Pstmt_space_begin_0();
struct _Mglc_Sstmt_space* _Mglc_Pstmt_space_begin_detach_0();
struct _Mglc_Sstmt_space* _Mglc_Pstmt_space_end_0();
_Mglc_Eexpr _Mglc_Pexpr_compare_3(_Mglc_Eexpr _Lleft_0, _Mglc_Eexpr _Lright_1, _Mglc_Ecompare _Ltype_2);
_Mglc_Eexpr _Mglc_Pexpr_bool_1(bool _Lvalue_0);
_Mglc_Eexpr _Mglc_Pexpr_char_1(int32_t _Lvalue_0);
void _Mglc_Pcvar_attr_real_name_1(_Mglc_Eid _Lname_0);
void _Mglc_Pcvar_attr_no_decl_0();
void _Mglc_Eat_Pput_to_header_1(_Mglc_Eat _Lat_0);
void _Mglc_Einclude_Pwr_2(_Mglc_Einclude _Li_0, union _Mglc_Swtr* _Lw_1);
void _Mglc_Sdecl_var_Pwr_3(struct _Mglc_Sdecl_var* _Lvd_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2);
void _Mglc_Ecvar_flags_Pwr_2(_Mglc_Ecvar_flags _Lf_0, union _Mglc_Swtr* _Lw_1);
void _Mglc_Eexpr_Pwr_3(_Mglc_Eexpr _Le_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2);
void _Mglc_Ecvar_Pwr_2(_Mglc_Ecvar _Lg_0, union _Mglc_Swtr* _Lw_1);
void _Mglc_Eenum_flags_Pwr_2(_Mglc_Eenum_flags _Le_0, union _Mglc_Swtr* _Lw_1);
void _Mglc_Estruct_flags_Pwr_2(_Mglc_Estruct_flags _Lf_0, union _Mglc_Swtr* _Lw_1);
void _Mglc_Sfvar_Pwr_3(struct _Mglc_Sfvar* _Lf_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2);
void _Mglc_Sfarg_Pwr_3(struct _Mglc_Sfarg* _Lf_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2);
void _Mglc_Efunc_flags_Pwr_2(_Mglc_Efunc_flags _Le_0, union _Mglc_Swtr* _Lw_1);
void _Mglc_Efunc_Pwr_2(_Mglc_Efunc _Lf_0, union _Mglc_Swtr* _Lw_1);
void _Mglc_Sdecl_func_Plvars_wr_3(struct _Mglc_Sdecl_func* _Lf_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2);
void _Mglc_Sstmt_space_Pwr_3(struct _Mglc_Sstmt_space* _Lspace_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2);
void _Mglc_Swtr_Pn4_2(union _Mglc_Swtr* _Lw_0, uint32_t _Ln_1);
void _Mglc_Sdecl_var_Pcopy_from_2(struct _Mglc_Sdecl_var* _Lvd_0, struct _Mglc_Sdecl_var* _Lsrc_1);
void _Mglc_Sfarg_Pcopy_from_2(struct _Mglc_Sfarg* _Lf_0, struct _Mglc_Sfarg* _Lsrc_1);
uint8_t _Mglc_Eid_Plen_1(_Mglc_Eid _Lid_0);
char* _Mglc_Eid_Pstr_1(_Mglc_Eid _Lid_0);
struct _Mglc_Sdecl_func* _Mglc_Efunc_Pptr_1(_Mglc_Efunc _Lf_0);
_Mglc_Elvar _Mglc_Sstmt_space_Plvar_new_4(struct _Mglc_Sstmt_space* _Lspace_0, _Mglc_Eid _Lname_1, int32_t _Lrow_2, int32_t _Lcol_3);
struct _Mglc_Slvar* _Mglc_Elvar_Pptr_1(_Mglc_Elvar _Ll_0);
void _Mglc_Stype_info_Pinit_1(struct _Mglc_Stype_info* _Lti_0);
_Mglc_Eexpr _Mglc_Pexpr_push_2(struct _Mglc_Sexpr* _Le_0, _Mglc_Eexpr_type _Ltype_1);
struct _Mglc_Sexpr* _Mglc_Eexpr_Pptr_1(_Mglc_Eexpr _Le_0);
void _Mglc_Pstmt_push_6(struct _Mglc_Sstmt* _Ls_0, int32_t _Lbegin_row_1, int32_t _Lbegin_col_2, int32_t _Lend_row_3, int32_t _Lend_col_4, _Mglc_Estmt_type _Ltype_5);
_Mglc_Eid _Mglc_Elvar_Pname_1(_Mglc_Elvar _Ll_0);
char* _Mglc_Etoken_Pglc_name_1(_Mglc_Etoken _Le_0) {
switch(_Le_0) {
case _Mglc_Etoken_Cnil: return "nil";
case _Mglc_Etoken_Cplus: return "plus";
case _Mglc_Etoken_Cminus: return "minus";
case _Mglc_Etoken_Cspace: return "space";
case _Mglc_Etoken_Clcbrace: return "lcbrace";
case _Mglc_Etoken_Cid_colon: return "id-colon";
case _Mglc_Etoken_Cid_modulo: return "id-modulo";
case _Mglc_Etoken_Cid_fslash: return "id-fslash";
case _Mglc_Etoken_Cid_bslash: return "id-bslash";
case _Mglc_Etoken_Cid_quote: return "id-quote";
case _Mglc_Etoken_Cid_hash: return "id-hash";
case _Mglc_Etoken_Cid_dot: return "id-dot";
case _Mglc_Etoken_Cid: return "id";
case _Mglc_Etoken_Cspace_at_real_name_str: return "space-at-real-name-str";
case _Mglc_Etoken_Cspace_at_no_decl: return "space-at-no-decl";
case _Mglc_Etoken_Cspace_equal_space: return "space-equal-space";
case _Mglc_Etoken_Cinclude: return "include";
case _Mglc_Etoken_Cspace_rcbrace: return "space-rcbrace";
case _Mglc_Etoken_Cquote: return "quote";
case _Mglc_Etoken_Cgrave: return "grave";
case _Mglc_Etoken_Clcbrace_at: return "lcbrace-at";
case _Mglc_Etoken_Clparen: return "lparen";
case _Mglc_Etoken_Crparen: return "rparen";
case _Mglc_Etoken_Clcbrace_cvar: return "lcbrace-cvar";
case _Mglc_Etoken_Cend: return "end";
case _Mglc_Etoken_Clcbrace_alias: return "lcbrace-alias";
case _Mglc_Etoken_Crcbrace: return "rcbrace";
case _Mglc_Etoken_Clparen_space: return "lparen-space";
case _Mglc_Etoken_Cspace_rparen: return "space-rparen";
case _Mglc_Etoken_Ccomma_space_rparen: return "comma-space-rparen";
case _Mglc_Etoken_Ccomma_space_rcbrace: return "comma-space-rcbrace";
case _Mglc_Etoken_Cscolon_space_rcbrace: return "scolon-space-rcbrace";
case _Mglc_Etoken_Clbracket: return "lbracket";
case _Mglc_Etoken_Clbracket_space: return "lbracket-space";
case _Mglc_Etoken_Crbracket: return "rbracket";
case _Mglc_Etoken_Cspace_rbracket: return "space-rbracket";
case _Mglc_Etoken_Ccomma_space_rbracket: return "comma-space-rbracket";
case _Mglc_Etoken_Cgrave_this: return "grave-this";
case _Mglc_Etoken_Ccomma_space: return "comma-space";
case _Mglc_Etoken_Cspace_at_main: return "space-at-main";
case _Mglc_Etoken_Cspace_at_case: return "space-at-case";
case _Mglc_Etoken_Cspace_at_process: return "space-at-process";
case _Mglc_Etoken_Cspace_at_glc_name: return "space-at-glc-name";
case _Mglc_Etoken_Cspace_at_var_args: return "space-at-var-args";
case _Mglc_Etoken_Cspace_at_no_body: return "space-at-no-body";
case _Mglc_Etoken_Cspace_at_real_name: return "space-at-real-name";
case _Mglc_Etoken_Cgrave_ref: return "grave-ref";
case _Mglc_Etoken_Cgrave_bool: return "grave-bool";
case _Mglc_Etoken_Cgrave_char: return "grave-char";
case _Mglc_Etoken_Cgrave_tint: return "grave-tint";
case _Mglc_Etoken_Cgrave_tnum: return "grave-tnum";
case _Mglc_Etoken_Cgrave_int: return "grave-int";
case _Mglc_Etoken_Cgrave_num: return "grave-num";
case _Mglc_Etoken_Cgrave_float: return "grave-float";
case _Mglc_Etoken_Cgrave_size: return "grave-size";
case _Mglc_Etoken_Cgrave_lnum: return "grave-lnum";
case _Mglc_Etoken_Cspace_at_inline_scolon: return "space-at-inline-scolon";
case _Mglc_Etoken_Campersand: return "ampersand";
case _Mglc_Etoken_Cnum_dec: return "num-dec";
case _Mglc_Etoken_Cnum_hex: return "num-hex";
case _Mglc_Etoken_Cnum_oct: return "num-oct";
case _Mglc_Etoken_Cstring: return "string";
case _Mglc_Etoken_Cchar1: return "char1";
case _Mglc_Etoken_Cchar2: return "char2";
case _Mglc_Etoken_Cgrave_true: return "grave-true";
case _Mglc_Etoken_Cgrave_false: return "grave-false";
case _Mglc_Etoken_Cgrave_null: return "grave-null";
case _Mglc_Etoken_Clparen_amp_amp_comma_space: return "lparen-amp-amp-comma-space";
case _Mglc_Etoken_Clparen_pipe_pipe_comma_space: return "lparen-pipe-pipe-comma-space";
case _Mglc_Etoken_Cspace_plus_space: return "space-plus-space";
case _Mglc_Etoken_Cspace_minus_space: return "space-minus-space";
case _Mglc_Etoken_Cspace_mul_space: return "space-mul-space";
case _Mglc_Etoken_Cspace_div_space: return "space-div-space";
case _Mglc_Etoken_Cspace_langle_langle_space: return "space-langle-langle-space";
case _Mglc_Etoken_Cspace_rangle_rangle_space: return "space-rangle-rangle-space";
case _Mglc_Etoken_Cspace_amp_space: return "space-amp-space";
case _Mglc_Etoken_Cspace_pipe_space: return "space-pipe-space";
case _Mglc_Etoken_Cspace_xor_space: return "space-xor-space";
case _Mglc_Etoken_Cspace_equal_equal_space: return "space-equal-equal-space";
case _Mglc_Etoken_Cspace_expoint_equal_space: return "space-expoint-equal-space";
case _Mglc_Etoken_Cspace_langle_space: return "space-langle-space";
case _Mglc_Etoken_Cspace_langle_equal_space: return "space-langle-equal-space";
case _Mglc_Etoken_Cspace_rangle_space: return "space-rangle-space";
case _Mglc_Etoken_Cspace_rangle_equal_space: return "space-rangle-equal-space";
case _Mglc_Etoken_Chash: return "hash";
case _Mglc_Etoken_Cspace_plus_equal_space: return "space-plus-equal-space";
case _Mglc_Etoken_Cspace_minus_equal_space: return "space-minus-equal-space";
case _Mglc_Etoken_Cspace_mul_equal_space: return "space-mul-equal-space";
case _Mglc_Etoken_Cspace_div_equal_space: return "space-div-equal-space";
case _Mglc_Etoken_Cspace_lshift_equal_space: return "space-lshift-equal-space";
case _Mglc_Etoken_Cspace_rshift_equal_space: return "space-rshift-equal-space";
case _Mglc_Etoken_Cspace_and_equal_space: return "space-and-equal-space";
case _Mglc_Etoken_Cspace_or_equal_space: return "space-or-equal-space";
case _Mglc_Etoken_Cspace_xor_equal_space: return "space-xor-equal-space";
case _Mglc_Etoken_Cspace_colon_equal_space: return "space-colon-equal-space";
case _Mglc_Etoken_Clcbrace_do: return "lcbrace-do";
case _Mglc_Etoken_Clcbrace_while: return "lcbrace-while";
case _Mglc_Etoken_Clcbrace_if: return "lcbrace-if";
case _Mglc_Etoken_Clcbrace_elif: return "lcbrace-elif";
case _Mglc_Etoken_Clcbrace_else: return "lcbrace-else";
case _Mglc_Etoken_Cexpoint: return "expoint";
case _Mglc_Etoken_Clcbrace_switch: return "lcbrace-switch";
case _Mglc_Etoken_Cspace_at_fall_through: return "space-at-fall-through";
case _Mglc_Etoken_Clcbrace_case: return "lcbrace-case";
case _Mglc_Etoken_Clcbrace_default: return "lcbrace-default";
case _Mglc_Etoken_Clcbrace_continue: return "lcbrace-continue";
case _Mglc_Etoken_Clcbrace_break: return "lcbrace-break";
case _Mglc_Etoken_Clcbrace_return: return "lcbrace-return";
case _Mglc_Etoken_Clcbrace_plus_or_space: return "lcbrace-plus-or-space";
case _Mglc_Etoken_Cspace_at_extern: return "space-at-extern";
case _Mglc_Etoken_Cscolon_space: return "scolon-space";
case _Mglc_Etoken_Cspace_at_union: return "space-at-union";
case _Mglc_Etoken_Clcbrace_gvar: return "lcbrace-gvar";
}
return "(ERROR)";
}
struct _Mglc_Sat* _Mglc_Eat_Pptr_1(_Mglc_Eat _Li_0);
_Mglc_Eat _Mglc_Pat_create_basic_1(_Mglc_Ebasic_type_id _Lbasic_0);
_Mglc_Eat _Mglc_Pat_create_3(_Mglc_Eat _Lparent_0, _Mglc_Ename_type _Ltype_1, _Mglc_Eid _Lname_2);
void _Mglc_Ptype_info_arr_1(_Mglc_Eexpr _Lexpr_0);
void _Mglc_Stype_info_Pfinalize_1(struct _Mglc_Stype_info* _Lti_0);
struct _Mglc_Scvar* _Mglc_Ecvar_Pptr_1(_Mglc_Ecvar _Lc_0);
struct _Mglc_Sstmt_space* _Mglc_Pstmt_space_begin_1(bool _Lattach_0);
void _Mglc_Evar_flags_Pwr_2(_Mglc_Evar_flags _Lf_0, union _Mglc_Swtr* _Lw_1);
void _Mglc_Stype_info_Pwr_2(struct _Mglc_Stype_info* _Lti_0, union _Mglc_Swtr* _Lw_1);
void _Mglc_Eexpr_type_Pwr_2(_Mglc_Eexpr_type _Le_0, union _Mglc_Swtr* _Lw_1);
void _Mglc_Eexpr_Pwr_math_3(struct _Mglc_Sexpr* _Lexpr_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2);
void _Mglc_Eexpr_Pwr_bools_3(struct _Mglc_Sexpr* _Lexpr_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2);
void _Mglc_Eexpr_Pwr_str_3(struct _Mglc_Sexpr* _Lexpr_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2);
void _Mglc_Eexpr_Pwr_cvar_3(struct _Mglc_Sexpr* _Lexpr_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2);
void _Mglc_Eexpr_Pwr_unary_3(struct _Mglc_Sexpr* _Lexpr_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2);
void _Mglc_Eexpr_Pwr_ref_3(struct _Mglc_Sexpr* _Lexpr_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2);
void _Mglc_Eexpr_Pwr_cast_fast_3(struct _Mglc_Sexpr* _Lexpr_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2);
void _Mglc_Eexpr_Pwr_index_3(struct _Mglc_Sexpr* _Lexpr_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2);
void _Mglc_Eexpr_Pwr_compare_3(struct _Mglc_Sexpr* _Lexpr_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2);
void _Mglc_Eexpr_Pwr_bool_3(struct _Mglc_Sexpr* _Lexpr_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2);
void _Mglc_Eexpr_Pwr_char_3(struct _Mglc_Sexpr* _Lexpr_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2);
void _Mglc_Eexpr_Pwr_method_3(struct _Mglc_Sexpr* _Lexpr_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2);
void _Mglc_Eexpr_Pwr_func_3(struct _Mglc_Sexpr* _Lexpr_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2);
void _Mglc_Eexpr_Pwr_null_3(struct _Mglc_Sexpr* _Lexpr_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2);
void _Mglc_Eexpr_Pwr_int_3(struct _Mglc_Sexpr* _Lexpr_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2);
void _Mglc_Eexpr_Pwr_size_of_type_3(struct _Mglc_Sexpr* _Lexpr_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2);
void _Mglc_Eexpr_Pwr_assign_3(struct _Mglc_Sexpr* _Lexpr_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2);
void _Mglc_Eexpr_Pwr_fvar_3(struct _Mglc_Sexpr* _Lexpr_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2);
void _Mglc_Eexpr_Pwr_gvar_3(struct _Mglc_Sexpr* _Lexpr_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2);
void _Mglc_Eexpr_Pwr_lvar_3(struct _Mglc_Sexpr* _Lexpr_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2);
char* _Mglc_Eexpr_type_Pglc_name_1(_Mglc_Eexpr_type _Le_0) {
switch(_Le_0) {
case _Mglc_Eexpr_type_Cnil: return "nil";
case _Mglc_Eexpr_type_Ccall_method: return "call-method";
case _Mglc_Eexpr_type_Clvar: return "lvar";
case _Mglc_Eexpr_type_Cgvar: return "gvar";
case _Mglc_Eexpr_type_Cmath: return "math";
case _Mglc_Eexpr_type_Cassign: return "assign";
case _Mglc_Eexpr_type_Cbools: return "bools";
case _Mglc_Eexpr_type_Cfunc: return "func";
case _Mglc_Eexpr_type_Cmethod: return "method";
case _Mglc_Eexpr_type_Cfvar: return "fvar";
case _Mglc_Eexpr_type_Cint: return "int";
case _Mglc_Eexpr_type_Ccvar: return "cvar";
case _Mglc_Eexpr_type_Cstr: return "str";
case _Mglc_Eexpr_type_Cindex: return "index";
case _Mglc_Eexpr_type_Cunary: return "unary";
case _Mglc_Eexpr_type_Ccompare: return "compare";
case _Mglc_Eexpr_type_Cbool: return "bool";
case _Mglc_Eexpr_type_Cnull: return "null";
case _Mglc_Eexpr_type_Ccast_fast: return "cast-fast";
case _Mglc_Eexpr_type_Cref: return "ref";
case _Mglc_Eexpr_type_Cchar: return "char";
case _Mglc_Eexpr_type_Csize_of_type: return "size-of-type";
}
return "(ERROR)";
}
void _Mglc_Elvar_flags_Pwr_2(_Mglc_Elvar_flags _Lf_0, union _Mglc_Swtr* _Lw_1);
void _Mglc_Elvar_Pwr_2(_Mglc_Elvar _Ll_0, union _Mglc_Swtr* _Lw_1);
void _Mglc_Estmt_type_Pwr_2(_Mglc_Estmt_type _Ls_0, union _Mglc_Swtr* _Lw_1);
void _Mglc_Sstmt_space_Pwr_break_3(struct _Mglc_Sstmt* _Lstmt_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2);
void _Mglc_Sstmt_space_Pwr_switch_3(struct _Mglc_Sstmt* _Lstmt_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2);
void _Mglc_Sstmt_space_Pwr_case_3(struct _Mglc_Sstmt* _Lstmt_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2);
void _Mglc_Sstmt_space_Pwr_case_end_3(struct _Mglc_Sstmt* _Lstmt_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2);
void _Mglc_Sstmt_space_Pwr_default_3(struct _Mglc_Sstmt* _Lstmt_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2);
void _Mglc_Sstmt_space_Pwr_default_end_3(struct _Mglc_Sstmt* _Lstmt_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2);
void _Mglc_Sstmt_space_Pwr_switch_end_3(struct _Mglc_Sstmt* _Lstmt_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2);
void _Mglc_Sstmt_space_Pwr_if_3(struct _Mglc_Sstmt* _Lstmt_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2);
void _Mglc_Sstmt_space_Pwr_if_elif_3(struct _Mglc_Sstmt* _Lstmt_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2);
void _Mglc_Sstmt_space_Pwr_if_else_3(struct _Mglc_Sstmt* _Lstmt_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2);
void _Mglc_Sstmt_space_Pwr_if_end_3(struct _Mglc_Sstmt* _Lstmt_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2);
void _Mglc_Sstmt_space_Pwr_do_3(struct _Mglc_Sstmt* _Lstmt_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2);
void _Mglc_Sstmt_space_Pwr_do_end_3(struct _Mglc_Sstmt* _Lstmt_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2);
void _Mglc_Sstmt_space_Pwr_while_3(struct _Mglc_Sstmt* _Lstmt_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2);
void _Mglc_Sstmt_space_Pwr_while_end_3(struct _Mglc_Sstmt* _Lstmt_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2);
void _Mglc_Sstmt_space_Pwr_continue_3(struct _Mglc_Sstmt* _Lstmt_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2);
void _Mglc_Sstmt_space_Pwr_return_3(struct _Mglc_Sstmt* _Lstmt_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2);
void _Mglc_Sstmt_space_Pwr_space_3(struct _Mglc_Sstmt* _Lstmt_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2);
void _Mglc_Sstmt_space_Pwr_expr_3(struct _Mglc_Sstmt* _Lstmt_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2);
char* _Mglc_Estmt_type_Pglc_name_1(_Mglc_Estmt_type _Le_0) {
switch(_Le_0) {
case _Mglc_Estmt_type_Cspace: return "space";
case _Mglc_Estmt_type_Cif: return "if";
case _Mglc_Estmt_type_Cif_elif: return "if-elif";
case _Mglc_Estmt_type_Cif_else: return "if-else";
case _Mglc_Estmt_type_Cif_end: return "if-end";
case _Mglc_Estmt_type_Cdo: return "do";
case _Mglc_Estmt_type_Cdo_end: return "do-end";
case _Mglc_Estmt_type_Cwhile: return "while";
case _Mglc_Estmt_type_Cwhile_end: return "while-end";
case _Mglc_Estmt_type_Cexpr: return "expr";
case _Mglc_Estmt_type_Creturn: return "return";
case _Mglc_Estmt_type_Ccontinue: return "continue";
case _Mglc_Estmt_type_Cbreak: return "break";
case _Mglc_Estmt_type_Cswitch: return "switch";
case _Mglc_Estmt_type_Ccase: return "case";
case _Mglc_Estmt_type_Cdefault: return "default";
case _Mglc_Estmt_type_Ccase_end: return "case-end";
case _Mglc_Estmt_type_Cdefault_end: return "default-end";
case _Mglc_Estmt_type_Cswitch_end: return "switch-end";
case _Mglc_Estmt_type_Cnil: return "nil";
}
return "(ERROR)";
}
void _Mglc_Stype_info_Pcopy_from_2(struct _Mglc_Stype_info* _Lti_0, struct _Mglc_Stype_info* _Lti2_1);
void _Mglc_Pfunc_stmt_add_1(struct _Mglc_Sstmt* _Ls_0);
void _Mglc_Swtr_Pbool_2(union _Mglc_Swtr* _Lw_0, bool _Lval_1);
void _Mglc_Emath_Pwr_2(_Mglc_Emath _Le_0, union _Mglc_Swtr* _Lw_1);
void _Mglc_Ebools_Pwr_2(_Mglc_Ebools _Le_0, union _Mglc_Swtr* _Lw_1);
void _Mglc_Eunary_Pwr_2(_Mglc_Eunary _Lu_0, union _Mglc_Swtr* _Lw_1);
void _Mglc_Ecompare_Pwr_2(_Mglc_Ecompare _Le_0, union _Mglc_Swtr* _Lw_1);
void _Mglc_Eassign_Pwr_2(_Mglc_Eassign _Ls_0, union _Mglc_Swtr* _Lw_1);
int32_t main(int32_t _Largc_0, char** _Largv_1) {
_Mstdc_Efile _Lin_fd_2;
size_t _Lin_size_3;
uint8_t* _Lin_data_4;
union _Mglc_Srdr _Lr_end_21;
struct _Mglc_Sparser* _Lpsr_22;
struct _Mglc_Slexer _Llex_23;
int32_t _Lnext_row_24;
int32_t _Lnext_col_25;
struct _Mglc_Stoken _Ltok_26;
union _Mglc_Swtr _Lw_begin_34;
union _Mglc_Swtr _Lw_35;
int32_t _Lid_bit8_c_37;
_Mglc_Eat _Lat_bit8_c_39;
char _Lout_path_42[512];
size_t _Lin_path_len_43;
_Mstdc_Efile _Lout_fd_44;
char _Lfinal_path_51[512];
if(false) {
_Mglc_Pexport_0();
}
_Mglc_Pquick_alloc_init_0();
_Gfunc_main = _Mglc_Efunc_Cnil;
_Gdecl_include = _Mglc_Einclude_Cnil;
if(_Largc_0 != 2) {
fprintf(stdout, "usage: %s file.glc\n", _Largv_1[0]);
return 0;
}
input_path = _Largv_1[1];
fprintf(stdout, "reading %s\n", input_path);
if(!(_Mstdc_Efile_Popen_3(&_Lin_fd_2, input_path, O_RDONLY))) {
fprintf(stdout, "Cannot open file for reading: %s\n", input_path);
exit(_Mstdc_Eexit_Cfailure);
}
_Lin_size_3 = lseek(_Lin_fd_2, 0, SEEK_END);
_Lin_data_4 = malloc(_Lin_size_3 + 2);
lseek(_Lin_fd_2, 0, SEEK_SET);
read(_Lin_fd_2, _Lin_data_4, _Lin_size_3);
_Lin_data_4[_Lin_size_3] = 0;
_Lin_data_4[(_Lin_size_3 + 1)] = 0;
close(_Lin_fd_2);
if(((_Lin_data_4[(_Lin_size_3 - 2)] == '\r') && (_Lin_data_4[(_Lin_size_3 - 1)] == '\n'))) {
fprintf(stdout, "Error reading file '%s' because it uses Windows-style line endings\n", input_path);
fprintf(stdout, "Please convert the line endings to Unix-style line endings\n");
exit(_Mstdc_Eexit_Cfailure);
}
if(_Lin_data_4[(_Lin_size_3 - 1)] != '\n') {
fprintf(stdout, "Error reading file '%s' because it doesn't end with a new line\n", input_path);
exit(_Mstdc_Eexit_Cfailure);
}
if(true) {
union _Mglc_Srdr _Lr_end_5;
union _Mglc_Srdr _Lr_6;
void* _Lnew_data_7;
union _Mglc_Swtr _Lw_8;
union _Mglc_Swtr _Lw_begin_20;
_Lr_end_5._Fref = _Lin_data_4;
_Lr_end_5._Fpos += _Lin_size_3;
_Lr_6._Fref = _Lin_data_4;
_Lnew_data_7 = malloc(_Lin_size_3 + 1);
_Lw_8._Fref = _Lnew_data_7;
while(_Lr_6._Fpos < _Lr_end_5._Fpos) {
if(_Lr_6._F1[0] == '`') {
if(((_Lr_6._F1[1] == '`') && ((_Lr_6._F1[2] == ' ') || (_Lr_6._F1[2] == '\t')))) {
_Lr_6._Fpos += 3;
while(1) {
if(_Lr_6._F1[0] == '\n') {
goto break_1;
}
_Lr_6._Fpos++;
if(_Lr_6._Fpos >= _Lr_end_5._Fpos) {
int32_t _Lrow_9;
int32_t _Lcol_10;
_Mglc_Pget_row_col_4(&_Lrow_9, &_Lcol_10, _Lr_6._Fref, _Lin_data_4);
fprintf(stdout, "%s:%u:%u: Comment did not end with a new line\n", input_path, _Lrow_9, _Lcol_10);
exit(_Mstdc_Eexit_Cfailure);
}
continue_1:;
}
break_1:;
goto continue_0;
} else if(_Lr_6._F1[1] == '\"') {
_Mglc_Pparse_comment_4(&_Lr_6, &_Lw_8, '\"', _Lin_data_4);
goto continue_0;
} else if(_Lr_6._F1[1] == '|') {
_Mglc_Pparse_comment_4(&_Lr_6, &_Lw_8, '|', _Lin_data_4);
goto continue_0;
} else if(_Lr_6._F1[1] == ';') {
_Mglc_Pparse_comment_4(&_Lr_6, &_Lw_8, ';', _Lin_data_4);
goto continue_0;
} else if(_Lr_6._F1[1] == '_') {
_Mglc_Pparse_comment_4(&_Lr_6, &_Lw_8, '_', _Lin_data_4);
goto continue_0;
} else if(_Lr_6._F1[1] == '+') {
_Mglc_Pparse_comment_4(&_Lr_6, &_Lw_8, '+', _Lin_data_4);
goto continue_0;
} else if(_Lr_6._F1[1] == '<') {
_Mglc_Pparse_comment_4(&_Lr_6, &_Lw_8, '>', _Lin_data_4);
goto continue_0;
} else if(_Lr_6._F1[1] == '[') {
_Mglc_Pparse_comment_4(&_Lr_6, &_Lw_8, ']', _Lin_data_4);
goto continue_0;
} else if(_Lr_6._F1[1] == '{') {
_Mglc_Pparse_comment_4(&_Lr_6, &_Lw_8, '}', _Lin_data_4);
goto continue_0;
} else if(_Lr_6._F1[1] == '(') {
_Mglc_Pparse_comment_4(&_Lr_6, &_Lw_8, ')', _Lin_data_4);
goto continue_0;
}
} else if(_Lr_6._F1[0] == '\'') {
if(_Lr_6._F1[1] == '\'') {
if(_Lr_6._F1[2] == '\\') {
_Lw_8._F1[0] = '\'';
_Lw_8._F1[1] = '\'';
_Lw_8._F1[2] = '\\';
_Lw_8._F1[3] = _Lr_6._F1[3];
_Lw_8._Fpos += 4;
_Lr_6._Fpos += 4;
goto continue_0;
} else {
_Lw_8._F1[0] = '\'';
_Lw_8._F1[1] = '\'';
_Lw_8._F1[2] = _Lr_6._F1[2];
_Lw_8._Fpos += 3;
_Lr_6._Fpos += 3;
goto continue_0;
}
} else if((((_Lr_6._F1[2] == ' ') || (_Lr_6._F1[2] == '\t')) && ((_Lr_6._F1[1] == '-') || (_Lr_6._F1[1] == '=')))) {
_Lw_8._F1[0] = '\'';
_Lw_8._F1[1] = _Lr_6._F1[1];
_Lw_8._F1[2] = _Lr_6._F1[2];
_Lw_8._Fpos += 3;
_Lr_6._Fpos += 3;
while(1) {
uint8_t _Lc_11;
_Lc_11 = _Lr_6._F1[0];
_Lw_8._F1[0] = _Lc_11;
_Lw_8._Fpos++;
_Lr_6._Fpos++;
if(_Lc_11 == '\n') {
goto break_2;
}
if(_Lr_6._Fpos >= _Lr_end_5._Fpos) {
int32_t _Lrow_12;
int32_t _Lcol_13;
_Mglc_Pget_row_col_4(&_Lrow_12, &_Lcol_13, _Lr_6._Fref, _Lin_data_4);
fprintf(stdout, "%s:%u:%u: String did not end with a new line\n", input_path, _Lrow_12, _Lcol_13);
exit(_Mstdc_Eexit_Cfailure);
}
continue_2:;
}
break_2:;
goto continue_0;
} else if(_Lr_6._F1[1] == '\"') {
_Mglc_Pparse_string_4(&_Lr_6, &_Lw_8, '\"', _Lin_data_4);
goto continue_0;
} else if(_Lr_6._F1[1] == '|') {
_Mglc_Pparse_string_4(&_Lr_6, &_Lw_8, '|', _Lin_data_4);
goto continue_0;
} else if(_Lr_6._F1[1] == ';') {
_Mglc_Pparse_string_4(&_Lr_6, &_Lw_8, ';', _Lin_data_4);
goto continue_0;
} else if(_Lr_6._F1[1] == '_') {
_Mglc_Pparse_string_4(&_Lr_6, &_Lw_8, '_', _Lin_data_4);
goto continue_0;
} else if(_Lr_6._F1[1] == '+') {
_Mglc_Pparse_string_4(&_Lr_6, &_Lw_8, '+', _Lin_data_4);
goto continue_0;
} else if(_Lr_6._F1[1] == '<') {
_Mglc_Pparse_string_4(&_Lr_6, &_Lw_8, '>', _Lin_data_4);
goto continue_0;
} else if(_Lr_6._F1[1] == '[') {
_Mglc_Pparse_string_4(&_Lr_6, &_Lw_8, ']', _Lin_data_4);
goto continue_0;
} else if(_Lr_6._F1[1] == '{') {
_Mglc_Pparse_string_4(&_Lr_6, &_Lw_8, '}', _Lin_data_4);
goto continue_0;
} else if(_Lr_6._F1[1] == '(') {
_Mglc_Pparse_string_4(&_Lr_6, &_Lw_8, ')', _Lin_data_4);
goto continue_0;
}
} else if(_Lr_6._F1[0] == '\"') {
_Lw_8._F1[0] = '\"';
_Lw_8._Fpos++;
_Lr_6._Fpos++;
while(1) {
if(_Lr_6._F1[0] == '\n') {
int32_t _Lrow_14;
int32_t _Lcol_15;
_Mglc_Pget_row_col_4(&_Lrow_14, &_Lcol_15, _Lr_6._Fref, _Lin_data_4);
fprintf(stdout, "%s:%u:%u: Unterminated string\n", input_path, _Lrow_14, _Lcol_15);
exit(_Mstdc_Eexit_Cfailure);
} else if(_Lr_6._F1[0] == '\"') {
_Lw_8._F1[0] = '\"';
_Lw_8._Fpos++;
_Lr_6._Fpos++;
goto break_3;
} else if(_Lr_6._F1[0] == '\\') {
switch(_Lr_6._F1[1]) {
case '0':;
break;
case '\\':;
break;
case '\"':;
break;
case '\'':;
break;
case 'a':;
break;
case 'b':;
break;
case 'f':;
break;
case 'n':;
break;
case 'r':;
break;
case 't':;
break;
case 'v':;
break;
default:;
int32_t _Lrow_16;
int32_t _Lcol_17;
_Mglc_Pget_row_col_4(&_Lrow_16, &_Lcol_17, _Lr_6._Fref, _Lin_data_4);
fprintf(stdout, "%s:%u:%u: Encountered invalid escape sequence in the string: '\\%c'\n", input_path, _Lrow_16, _Lcol_17, _Lr_6._F1[1]);
exit(_Mstdc_Eexit_Cfailure);
break;
}
_Lw_8._F1[0] = '\\';
_Lw_8._F1[1] = _Lr_6._F1[1];
_Lw_8._Fpos += 2;
_Lr_6._Fpos += 2;
} else {
_Lw_8._F1[0] = _Lr_6._F1[0];
_Lw_8._Fpos++;
_Lr_6._Fpos++;
}
if(_Lr_6._Fpos >= _Lr_end_5._Fpos) {
int32_t _Lrow_18;
int32_t _Lcol_19;
_Mglc_Pget_row_col_4(&_Lrow_18, &_Lcol_19, _Lr_6._Fref, _Lin_data_4);
fprintf(stdout, "%s:%u:%u: Unterminated string\n", input_path, _Lrow_18, _Lcol_19);
exit(_Mstdc_Eexit_Cfailure);
}
continue_3:;
}
break_3:;
goto continue_0;
}
_Lw_8._F1[0] = _Lr_6._F1[0];
_Lw_8._Fpos++;
_Lr_6._Fpos++;
continue_0:;
}
break_0:;
_Lw_8._F1[0] = '\0';
free(_Lin_data_4);
_Lin_data_4 = _Lnew_data_7;
_Lw_begin_20._Fref = _Lnew_data_7;
_Lin_size_3 = (_Lw_8._Fpos - _Lw_begin_20._Fpos);
}
_Lr_end_21._Fref = _Lin_data_4;
_Lr_end_21._Fpos += _Lin_size_3;
_Mglc_Pparse_str_init_1(_Lin_size_3);
_Gid_cap = 64;
_Mglc_Pmalloc_arr_2(_Gid_str_v, _Gid_cap);
_Mglc_Pmalloc_arr_2(_Gid_len_v, _Gid_cap);
_Ginclude_cap = 64;
_Mglc_Pmalloc_arr_2(_Ginclude_str_v, _Ginclude_cap);
_Mglc_Pmalloc_arr_2(_Ginclude_len_v, _Ginclude_cap);
_Gat_cap = (_Mglc_Eat)(64);
_Mglc_Pmalloc_arr_2(_Gat_v, _Gat_cap);
_Gat_c = (_Mglc_Eat)(1);
_Gat_v[0]._Ftype = _Mglc_Ename_type_Cbasic;
_Gat_v[0]._Fparent = _Mglc_Eat_Cnil;
_Gat_v[0]._Fname._Fbasic = _Mglc_Ebasic_type_id_Croot;
_Gfunc_cap = (_Mglc_Efunc)(32);
_Mglc_Pmalloc_arr_2(_Gfunc_v, _Gfunc_cap);
_Gstruct_cap = (_Mglc_Estruct)(32);
_Mglc_Pmalloc_arr_2(_Gstruct_v, _Gstruct_cap);
_Gdecl_fvar_cap = 32;
_Mglc_Pmalloc_arr_2(_Gdecl_fvar_v, _Gdecl_fvar_cap);
_Lpsr_22 = _Mglc_Sparser_Palloc_0();
_Mglc_Slexer_Pinit_3(&_Llex_23, _Lin_data_4, _Lin_size_3);
_Lnext_row_24 = 1;
_Lnext_col_25 = 1;
_Grow = 1;
_Gcol = 1;
while(1) {
_Mglc_Etoken _Lt_27;
uint8_t* _Lpos_33;
_Ltok_26._Frow = _Lnext_row_24;
_Ltok_26._Fcol = _Lnext_col_25;
_Lt_27 = glc_lexer_scan(&_Llex_23);
if(true) {
uint8_t* _Lpos_28;
_Lpos_28 = _Llex_23._Fstart;
while(_Lpos_28 < _Lr_end_21._F1) {
if(((_Lpos_28[0] == ' ') || (_Lpos_28[0] == '\t'))) {
_Ltok_26._Fcol++;
} else if(_Lpos_28[0] == '\n') {
_Ltok_26._Frow++;
_Ltok_26._Fcol = 1;
} else {
goto break_5;
}
_Lpos_28++;
continue_5:;
}
break_5:;
}
_Glast_row = _Grow;
_Glast_col = _Gcol;
_Grow = _Ltok_26._Frow;
_Gcol = _Ltok_26._Fcol;
if(((_Lt_27 >= _Mglc_Etoken_Cid_colon) && (_Lt_27 < _Mglc_Etoken_Cid))) {
_Ltok_26._Fid = _Mglc_Slexer_Pget_id_3(&_Llex_23, 1, 0);
glcParse(_Lpsr_22, _Lt_27, &_Ltok_26);
} else {
switch(_Lt_27) {
case _Mglc_Etoken_Cchar1:;
union _Mglc_Srdr _Lr_29;
_Lr_29._Fref = _Llex_23._Fstart;
_Ltok_26._Fid = _Lr_29._F1[2];
glcParse(_Lpsr_22, _Lt_27, &_Ltok_26);
break;
case _Mglc_Etoken_Cchar2:;
union _Mglc_Srdr _Lr_30;
_Lr_30._Fref = _Llex_23._Fstart;
_Ltok_26._Fid = _Mglc_Pchar_escape_value_1(_Lr_30._F1[3]);
glcParse(_Lpsr_22, _Lt_27, &_Ltok_26);
break;
case _Mglc_Etoken_Cspace_at_real_name_str:;
union _Mglc_Srdr _Lr_start_31;
int32_t _Lstart_32;
_Lr_start_31._Fref = _Llex_23._Fstart;
_Lstart_32 = 11;
while(1) {
_Lstart_32++;
_Lr_start_31._Fpos++;
if(_Lr_start_31._F1[0] == '@') {
goto break_6;
}
continue_6:;
}
break_6:;
_Ltok_26._Fid = _Mglc_Slexer_Pget_id_3(&_Llex_23, _Lstart_32, 1);
glcParse(_Lpsr_22, _Lt_27, &_Ltok_26);
break;
case _Mglc_Etoken_Cnum_dec:;
_Ltok_26._Fid = _Mglc_Slexer_Pget_num_dec_1(&_Llex_23);
glcParse(_Lpsr_22, _Lt_27, &_Ltok_26);
break;
case _Mglc_Etoken_Cnum_oct:;
_Ltok_26._Fid = _Mglc_Slexer_Pget_num_oct_1(&_Llex_23);
glcParse(_Lpsr_22, _Lt_27, &_Ltok_26);
break;
case _Mglc_Etoken_Cinclude:;
_Ltok_26._Fid = _Mglc_Slexer_Pget_include_1(&_Llex_23);
glcParse(_Lpsr_22, _Lt_27, &_Ltok_26);
break;
case _Mglc_Etoken_Cid:;
_Ltok_26._Fid = _Mglc_Slexer_Pget_id_3(&_Llex_23, 0, 0);
glcParse(_Lpsr_22, _Lt_27, &_Ltok_26);
break;
default:;
glcParse(_Lpsr_22, _Lt_27, &_Ltok_26);
break;
}
}
if(_Lt_27 == _Mglc_Etoken_Cend) {
goto break_4;
}
_Lpos_33 = _Llex_23._Fstart;
while(_Lpos_33 < _Llex_23._Fcursor) {
if((_Lpos_33[0] & 128) == 0) {
if(_Lpos_33[0] == '\n') {
_Lnext_row_24++;
_Lnext_col_25 = 1;
} else {
_Lnext_col_25++;
}
}
_Lpos_33++;
continue_7:;
}
break_7:;
continue_4:;
}
break_4:;
glcParse(_Lpsr_22, _Mglc_Etoken_Cnil, &_Ltok_26);
_Mglc_Sparser_Pfree_1(_Lpsr_22);
fprintf(stdout, "parsing finished\n");
_Lw_begin_34._Fref = qalloc((_Lin_size_3 << 2) + 1024);
_Lw_35._Fref = _Lw_begin_34._Fref;
Fputnum(&_Lw_35, _Gid_c);
int32_t _Li_36;
_Li_36 = 0;
for(int i = _Gid_c; i > 0; ) {
i --;
_Mglc_Swtr_Pn1_2(&_Lw_35, _Gid_len_v[_Li_36]);
_Mglc_Swtr_Pcopy_3(&_Lw_35, _Gid_str_v[_Li_36], _Gid_len_v[_Li_36]);
_Mglc_Swtr_Pn1_2(&_Lw_35, 0);
continue_8:;
_Li_36++;
}
break_8:;
_Lid_bit8_c_37 = ((_Gid_c + 7) >> 3);
_Mglc_Pmalloc_arr_2(_Gid_in_header_v, _Lid_bit8_c_37);
_Mglc_Pmalloc_arr_2(_Gid_in_header_idx_v, _Gid_c);
_Mglc_Pmalloc_arr_2(_Gid_in_header_id_v, _Gid_c);
Fputnum(&_Lw_35, _Ginclude_c);
int32_t _Li_38;
_Li_38 = 0;
for(int i = _Ginclude_c; i > 0; ) {
i --;
_Mglc_Swtr_Pn1_2(&_Lw_35, _Ginclude_len_v[_Li_38]);
_Mglc_Swtr_Pcopy_3(&_Lw_35, _Ginclude_str_v[_Li_38], _Ginclude_len_v[_Li_38]);
_Mglc_Swtr_Pn1_2(&_Lw_35, 0);
continue_9:;
_Li_38++;
}
break_9:;
_Lat_bit8_c_39 = ((_Gat_c + 7) >> 3);
_Mglc_Pmalloc_arr_2(_Gat_in_header_v, _Lat_bit8_c_39);
_Mglc_Pmalloc_arr_2(_Gat_in_header_idx_v, _Gat_c);
_Mglc_Pmalloc_arr_2(_Gat_in_header_at_v, _Gat_c);
Fputnum(&_Lw_35, _Gat_c);
int32_t _Li_40;
_Li_40 = 0;
for(int i = _Gat_c; i > 0; ) {
i --;
struct _Mglc_Sat* _Lat_41;
_Lat_41 = (&_Gat_v[_Li_40]);
_Mglc_Ename_type_Pwr_2((*_Lat_41)._Ftype, &_Lw_35);
if((*_Lat_41)._Ftype == _Mglc_Ename_type_Cbasic) {
_Mglc_Ebasic_type_id_Pwr_2((*_Lat_41)._Fname._Fbasic, &_Lw_35);
} else {
_Mglc_Eat_Pwr_3((*_Lat_41)._Fparent, &_Lw_35, false);
_Mglc_Eid_Pwr_3((*_Lat_41)._Fname._Fid, &_Lw_35, false);
}
continue_10:;
_Li_40++;
}
break_10:;
_Mglc_Pwrite_cvar_2(&_Lw_35, false);
_Mglc_Pwrite_gvar_2(&_Lw_35, false);
_Mglc_Pwrite_enum_2(&_Lw_35, false);
_Mglc_Pwrite_struct_2(&_Lw_35, false);
_Mglc_Pwrite_func_2(&_Lw_35, false);
_Lin_path_len_43 = strlen(input_path);
memcpy(_Lout_path_42, input_path, _Lin_path_len_43);
_Lout_path_42[_Lin_path_len_43] = '-';
_Lout_path_42[(_Lin_path_len_43 + 1)] = 't';
_Lout_path_42[(_Lin_path_len_43 + 2)] = '.';
_Lout_path_42[(_Lin_path_len_43 + 3)] = 't';
_Lout_path_42[(_Lin_path_len_43 + 4)] = 'm';
_Lout_path_42[(_Lin_path_len_43 + 5)] = 'p';
_Lout_path_42[(_Lin_path_len_43 + 6)] = 0;
if(!(_Mstdc_Efile_Popen_4(&_Lout_fd_44, _Lout_path_42, O_CREAT | O_TRUNC | O_WRONLY, 420))) {
fprintf(stdout, "Cannot open file for writing: %s\n", _Lout_path_42);
exit(_Mstdc_Eexit_Cfailure);
}
write(_Lout_fd_44, _Lw_begin_34._Fref, _Lw_35._Fpos - _Lw_begin_34._Fpos);
close(_Lout_fd_44);
_Lw_35._Fref = _Lw_begin_34._Fref;
Fputnum(&_Lw_35, _Gid_in_header_c);
int32_t _Lj_45;
_Lj_45 = 0;
for(int i = _Gid_in_header_c; i > 0; ) {
i --;
uint32_t _Li_46;
_Li_46 = _Gid_in_header_id_v[_Lj_45];
_Mglc_Swtr_Pn1_2(&_Lw_35, _Gid_len_v[_Li_46]);
_Mglc_Swtr_Pcopy_3(&_Lw_35, _Gid_str_v[_Li_46], _Gid_len_v[_Li_46]);
_Mglc_Swtr_Pn1_2(&_Lw_35, 0);
continue_11:;
_Lj_45++;
}
break_11:;
Fputnum(&_Lw_35, _Ginclude_c);
int32_t _Li_47;
_Li_47 = 0;
for(int i = _Ginclude_c; i > 0; ) {
i --;
_Mglc_Swtr_Pn1_2(&_Lw_35, _Ginclude_len_v[_Li_47]);
_Mglc_Swtr_Pcopy_3(&_Lw_35, _Ginclude_str_v[_Li_47], _Ginclude_len_v[_Li_47]);
_Mglc_Swtr_Pn1_2(&_Lw_35, 0);
continue_12:;
_Li_47++;
}
break_12:;
Fputnum(&_Lw_35, _Gat_in_header_c);
int32_t _Lj_48;
_Lj_48 = 0;
for(int i = _Gat_in_header_c; i > 0; ) {
i --;
uint32_t _Li_49;
struct _Mglc_Sat* _Lat_50;
_Li_49 = _Gat_in_header_at_v[_Lj_48];
_Lat_50 = (&_Gat_v[_Li_49]);
_Mglc_Ename_type_Pwr_2((*_Lat_50)._Ftype, &_Lw_35);
if((*_Lat_50)._Ftype == _Mglc_Ename_type_Cbasic) {
_Mglc_Ebasic_type_id_Pwr_2((*_Lat_50)._Fname._Fbasic, &_Lw_35);
} else {
_Mglc_Eat_Pwr_header_2((*_Lat_50)._Fparent, &_Lw_35);
_Mglc_Eid_Pwr_header_2((*_Lat_50)._Fname._Fid, &_Lw_35);
}
continue_13:;
_Lj_48++;
}
break_13:;
_Mglc_Pwrite_cvar_2(&_Lw_35, true);
_Mglc_Pwrite_gvar_2(&_Lw_35, true);
_Mglc_Pwrite_enum_2(&_Lw_35, true);
_Mglc_Pwrite_struct_2(&_Lw_35, true);
_Mglc_Pwrite_func_2(&_Lw_35, true);
_Lout_path_42[(_Lin_path_len_43 + 1)] = 'h';
if(!(_Mstdc_Efile_Popen_4(&_Lout_fd_44, _Lout_path_42, O_CREAT | O_TRUNC | O_WRONLY, 420))) {
fprintf(stdout, "Cannot open file for writing: %s\n", _Lout_path_42);
exit(_Mstdc_Eexit_Cfailure);
}
write(_Lout_fd_44, _Lw_begin_34._Fref, _Lw_35._Fpos - _Lw_begin_34._Fpos);
close(_Lout_fd_44);
_Lout_path_42[(_Lin_path_len_43 + 1)] = 't';
memcpy(_Lfinal_path_51, _Lout_path_42, _Lin_path_len_43 + 2);
_Lfinal_path_51[(_Lin_path_len_43 + 2)] = 0;
rename(_Lout_path_42, _Lfinal_path_51);
_Lout_path_42[(_Lin_path_len_43 + 1)] = 'h';
memcpy(_Lfinal_path_51, _Lout_path_42, _Lin_path_len_43 + 2);
_Lfinal_path_51[(_Lin_path_len_43 + 2)] = 0;
rename(_Lout_path_42, _Lfinal_path_51);
return 0;
}
void _Mglc_Pexport_0() {
_Mglc_Pdecl_func_begin_3(_Mglc_Eid_C0, 0, 0);
_Mglc_Pdecl_func_end_2(0, 0);
_Mglc_Pdecl_struct_end_2(0, 0);
_Mglc_Pdecl_var_begin_3(_Mglc_Eid_C0, 0, 0);
_Mglc_Pdecl_var_attr_real_name_1(_Mglc_Eid_Cnil);
_Mglc_Pdecl_var_attr_extern_0();
_Mglc_Pdecl_var_attr_no_decl_0();
_Mglc_Pdecl_var_end_0();
_Mglc_Pdecl_var_as_farg_2(0, 0);
_Mglc_Pfarg_next_group_0();
_Mglc_Pdecl_var_as_this_0();
_Mglc_Pdecl_var_as_fvar_0();
_Mglc_Pfunc_body_end_1(false);
_Mglc_Pexpr_push_call_2(0, 0);
_Mglc_Pexpr_pop_func_2(_Mglc_Eat_Cnil, _Mglc_Eid_Cnil);
_Mglc_Pexpr_pop_method_2(_Mglc_Eexpr_Cnil, _Mglc_Eid_Cnil);
_Mglc_Pcarg_push_1(_Mglc_Eexpr_Cnil);
_Mglc_Pcarg_push_str_1(_Mglc_Eexpr_Cnil);
_Mglc_Pcarg_next_group_0();
_Mglc_Pexpr2stmt_5(_Mglc_Eexpr_Cnil, 0, 0, 0, 0);
_Mglc_Pstmt_return_5(_Mglc_Eexpr_Cnil, 0, 0, 0, 0);
_Mglc_Pstmt_continue_5(_Mglc_Eid_Cnil, 0, 0, 0, 0);
_Mglc_Pstmt_break_5(_Mglc_Eid_Cnil, 0, 0, 0, 0);
_Mglc_Pfunc_attr_main_0();
_Mglc_Pfunc_attr_glc_name_0();
_Mglc_Pfunc_attr_process_0();
_Mglc_Pfunc_attr_var_args_0();
_Mglc_Pfunc_attr_no_decl_0();
_Mglc_Pfunc_attr_no_body_0();
_Mglc_Pfunc_attr_real_name_1(_Mglc_Eid_Cnil);
_Mglc_Pfunc_attr_case_1(_Mglc_Eid_Cnil);
_Mglc_Pexpr_lvar_4(_Mglc_Eid_C0, 0, 0, 0);
_Mglc_Pexpr_gvar_2(_Mglc_Eat_Cnil, _Mglc_Eid_C0);
_Mglc_Pexpr_fvar_2(_Mglc_Eexpr_Cnil, _Mglc_Eid_Cnil);
_Mglc_Pexpr_assign_3(_Mglc_Eexpr_C0, _Mglc_Eexpr_C0, _Mglc_Eassign_Ceq);
_Mglc_Pexpr_math_3(_Mglc_Eexpr_C0, _Mglc_Eexpr_C0, _Mglc_Emath_Cadd);
_Mglc_Pexpr_math_add_2(_Mglc_Eexpr_C0, _Mglc_Eexpr_C0);
_Mglc_Pexpr_bools_3(_Mglc_Eexpr_C0, _Mglc_Eexpr_C0, _Mglc_Ebools_Cand);
_Mglc_Pexpr_bools_add_2(_Mglc_Eexpr_C0, _Mglc_Eexpr_C0);
_Mglc_Ptoken_name_1(_Mglc_Etoken_Cnil);
_Mglc_Pdecl_var_type_1(_Mglc_Eat_Cnil);
_Mglc_Pdecl_var_this_0();
_Mglc_Pstmt_lvar_add_4(_Mglc_Eid_C0, _Mglc_Eexpr_Cnil, 0, 0);
_Mglc_Pstmt_lvar_end_2(0, 0);
_Mglc_Pdecl_include_begin_3(_Mglc_Einclude_C0, 0, 0);
_Mglc_Pdecl_include_end_0();
_Mglc_Pdecl_at_basic_1(_Mglc_Ebasic_type_id_Croot);
_Mglc_Pdecl_at_add_2(_Mglc_Eid_C0, _Mglc_Ename_type_Cmodule);
_Mglc_Pdecl_at_begin_2(0, 0);
_Mglc_Pdecl_at_begin_struct_3(_Mglc_Eid_Cnil, 0, 0);
_Mglc_Pdecl_at_end_0();
_Mglc_Pdecl_alias_4(_Mglc_Eid_Cnil, _Mglc_Eat_Cnil, 0, 0);
_Mglc_Pat_push_4(_Mglc_Eid_C0, _Mglc_Ename_type_Cmodule, 0, 0);
_Mglc_Pat_done_0();
_Mglc_Pat_begin_0();
_Mglc_Pat_root_0();
_Mglc_Pat_alias_3(_Mglc_Eid_Cnil, 0, 0);
_Mglc_Pat_graves_3(0, 0, 0);
_Mglc_Pat_basic_type_1(_Mglc_Ebasic_type_id_Cint);
_Mglc_Pdecl_var_as_gvar_0();
_Mglc_Ptype_info_arr_2(NULL, 0);
_Mglc_Ptype_info_ref_1(0);
_Mglc_Ptype_info_static_0();
_Mglc_Ptype_info_begin_0();
_Mglc_Ptype_info_finalize_0();
_Mglc_Pexpr_int_2(0, _Mglc_Eexpr_int_Cdec);
_Mglc_Pexpr_size_of_type_1(_Mglc_Eat_Cnil);
_Mglc_Pexpr_null_0();
_Mglc_Pdecl_at_begin_enum_3(_Mglc_Eid_Cnil, 0, 0);
_Mglc_Pdecl_enum_end_3(_Mglc_Eat_Cnil, 0, 0);
_Mglc_Pexpr_cvar_2(_Mglc_Eat_Cnil, _Mglc_Eid_Cnil);
_Mglc_Penum_add_cvar_3(_Mglc_Eid_Cnil, 0, 0);
_Mglc_Pdecl_add_cvar_3(_Mglc_Eid_Cnil, 0, 0);
_Mglc_Penum_set_cvar_expr_1(_Mglc_Eexpr_Cnil);
_Mglc_Pstruct_attr_real_name_1(_Mglc_Eid_Cnil);
_Mglc_Pstruct_attr_union_0();
_Mglc_Pstruct_attr_no_decl_0();
_Mglc_Pexpr_str_1(_Mglc_Eexpr_Cnil);
_Mglc_Pexpr_unary_2(_Mglc_Eexpr_Cnil, _Mglc_Eunary_Cneg);
_Mglc_Pexpr_ref_1(_Mglc_Eexpr_Cnil);
_Mglc_Pexpr_cast_fast_2(_Mglc_Eexpr_Cnil, _Mglc_Eat_Cnil);
_Mglc_Pexpr_index_3(_Mglc_Eexpr_Cnil, NULL, 0);
_Mglc_Penum_base_begin_0();
_Mglc_Pstmt_switch_begin_0();
_Mglc_Pstmt_switch_set_6(_Mglc_Eexpr_Cnil, 0, 0, 0, 0, _Mglc_Eexpr_Cnil);
_Mglc_Pstmt_switch_expr_add_1(_Mglc_Eexpr_Cnil);
_Mglc_Pstmt_switch_case_begin_5(0, 0, 0, 0, false);
_Mglc_Pstmt_switch_case_end_0();
_Mglc_Pstmt_switch_default_begin_5(0, 0, 0, 0, false);
_Mglc_Pstmt_switch_default_end_0();
_Mglc_Pstmt_switch_end_0();
_Mglc_Pstmt_if_begin_0();
_Mglc_Pstmt_if_set_6(false, _Mglc_Eexpr_Cnil, 0, 0, 0, 0);
_Mglc_Pstmt_if_end_0();
_Mglc_Pstmt_do_begin_0();
_Mglc_Pstmt_do_set_6(_Mglc_Eexpr_Cnil, 0, 0, 0, 0, NULL);
_Mglc_Pstmt_do_end_0();
_Mglc_Pstmt_while_begin_0();
_Mglc_Pstmt_while_set_6(_Mglc_Eexpr_Cnil, 0, 0, 0, 0, NULL);
_Mglc_Pstmt_while_end_0();
_Mglc_Pstmt_elif_begin_0();
_Mglc_Pstmt_elif_set_6(false, _Mglc_Eexpr_Cnil, 0, 0, 0, 0);
_Mglc_Pstmt_elif_end_0();
_Mglc_Pstmt_else_set_0();
_Mglc_Pstmt_else_end_0();
_Mglc_Pstmt_if_end_ifs_0();
_Mglc_Pstmt_space_begin_0();
_Mglc_Pstmt_space_begin_detach_0();
_Mglc_Pstmt_space_end_0();
_Mglc_Pexpr_compare_3(_Mglc_Eexpr_Cnil, _Mglc_Eexpr_Cnil, _Mglc_Ecompare_Ceq);
_Mglc_Pexpr_bool_1(false);
_Mglc_Pexpr_char_1(0);
_Mglc_Pcvar_attr_real_name_1(_Mglc_Eid_Cnil);
_Mglc_Pcvar_attr_no_decl_0();
}
void _Mglc_Pquick_alloc_init_0() {
_Gquick_alloc_cap = (16 * 1024);
_Gquick_alloc_v = malloc(_Gquick_alloc_cap);
memset(_Gquick_alloc_v, 0, _Gquick_alloc_cap);
}
bool _Mstdc_Efile_Popen_3(_Mstdc_Efile* _Lfile_0, char* _Lpath_1, _Mstdc_Eopen_flags _Lflags_2) {
int32_t _Lfd_3;
_Lfd_3 = open(_Lpath_1, _Lflags_2);
if(_Lfd_3 != -1) {
(*_Lfile_0) = _Lfd_3;
return true;
} else {
return false;
}
}
void _Mglc_Pget_row_col_4(int32_t* _Lout_row_0, int32_t* _Lout_col_1, void* _Lend_2, void* _Lbegin_3) {
int32_t _Lrow_4;
int32_t _Lcol_5;
union _Mglc_Srdr _Lr_6;
union _Mglc_Srdr _Lr_end_7;
_Lrow_4 = 1;
_Lcol_5 = 1;
_Lr_6._Fref = _Lbegin_3;
_Lr_end_7._Fref = _Lend_2;
while(_Lr_6._Fpos < _Lr_end_7._Fpos) {
if(_Lr_6._F1[0] == '\n') {
_Lrow_4++;
_Lcol_5 = 1;
} else {
_Lcol_5++;
}
_Lr_6._Fpos++;
continue_0:;
}
break_0:;
(*_Lout_row_0) = _Lrow_4;
if(_Lr_6._F1[0] == '\n') {
(*_Lout_col_1) = (_Lcol_5 - 1);
} else {
(*_Lout_col_1) = _Lcol_5;
}
}
void _Mglc_Pparse_comment_4(union _Mglc_Srdr* _Lr_0, union _Mglc_Swtr* _Lw_1, char _Lending_2, void* _Lin_data_3) {
union _Mglc_Srdr _Lr_begin_4;
_Lr_begin_4._Fpos = (*_Lr_0)._Fpos;
(*_Lr_0)._Fpos += 2;
while(1) {
uint8_t _Lc_5;
_Lc_5 = (*_Lr_0)._F1[0];
if(_Lc_5 == '\n') {
int32_t _Lrow_6;
int32_t _Lcol_7;
_Mglc_Pget_row_col_4(&_Lrow_6, &_Lcol_7, (*_Lr_0)._Fref, _Lin_data_3);
fprintf(stdout, "%s:%u:%u: Unterminated comment\n", input_path, _Lrow_6, _Lcol_7);
exit(_Mstdc_Eexit_Cfailure);
}
(*_Lr_0)._Fpos++;
if(_Lc_5 == _Lending_2) {
size_t _Llen_8;
_Llen_8 = ((*_Lr_0)._Fpos - _Lr_begin_4._Fpos);
for(int i = _Llen_8; i > 0; ) {
i --;
(*_Lw_1)._F1[0] = ' ';
(*_Lw_1)._Fpos++;
continue_1:;
}
break_1:;
return;
}
continue_0:;
}
break_0:;
}
void _Mglc_Pparse_string_4(union _Mglc_Srdr* _Lr_0, union _Mglc_Swtr* _Lw_1, char _Lending_2, void* _Lin_data_3) {
(*_Lw_1)._F1[0] = '\'';
(*_Lw_1)._F1[1] = (*_Lr_0)._F1[1];
(*_Lw_1)._Fpos += 2;
(*_Lr_0)._Fpos += 2;
while(1) {
uint8_t _Lc_4;
_Lc_4 = (*_Lr_0)._F1[0];
if(_Lc_4 == '\n') {
int32_t _Lrow_5;
int32_t _Lcol_6;
_Mglc_Pget_row_col_4(&_Lrow_5, &_Lcol_6, (*_Lr_0)._Fref, _Lin_data_3);
fprintf(stdout, "%s:%u:%u: Unterminated string\n", input_path, _Lrow_5, _Lcol_6);
exit(_Mstdc_Eexit_Cfailure);
}
(*_Lw_1)._F1[0] = _Lc_4;
(*_Lw_1)._Fpos++;
(*_Lr_0)._Fpos++;
if(_Lc_4 == _Lending_2) {
return;
}
continue_0:;
}
break_0:;
}
void _Mglc_Slexer_Pinit_3(struct _Mglc_Slexer* _Llex_0, uint8_t* _Ldata_1, size_t _Lsize_2) {
(*_Llex_0)._Fstart = _Ldata_1;
(*_Llex_0)._Fcursor = _Ldata_1;
(*_Llex_0)._Fcontent = _Ldata_1;
(*_Llex_0)._Flimit = &_Ldata_1[_Lsize_2];
}
int32_t _Mglc_Slexer_Pget_id_3(struct _Mglc_Slexer* _Llex_0, uint8_t _Lbegin_1, uint8_t _Lend_2) {
union _Mglc_Srdr _Lr_start_3;
union _Mglc_Srdr _Lr_cursor_4;
size_t _Llength_5;
uint8_t _Llen_6;
int32_t _Lid_8;
char* _Ltext_10;
_Lr_start_3._Fref = (*_Llex_0)._Fstart;
_Lr_start_3._Fpos += _Lbegin_1;
_Lr_cursor_4._Fref = (*_Llex_0)._Fcursor;
_Llength_5 = (_Lr_cursor_4._Fpos - _Lr_start_3._Fpos - _Lend_2);
if(_Llength_5 > 255) {
fprintf(stdout, "too long id was detected\n");
exit(_Mstdc_Eexit_Cfailure);
}
_Llen_6 = (uint8_t)(_Llength_5);
int32_t _Li_7;
_Li_7 = 0;
for(int i = _Gid_c; i > 0; ) {
i --;
if(_Gid_len_v[_Li_7] == _Llen_6) {
if(memcmp(_Gid_str_v[_Li_7], _Lr_start_3._Fref, _Llen_6) == 0) {
return _Li_7;
}
}
continue_0:;
_Li_7++;
}
break_0:;
_Lid_8 = _Gid_c++;
if(_Gid_cap <= _Gid_c) {
int32_t _Lold_cap_9;
_Lold_cap_9 = _Gid_cap;
_Mglc_Pgrow_2(_Gid_cap, _Gid_c);
_Mglc_Prealloc_3(_Gid_str_v, _Gid_cap, _Lold_cap_9);
_Mglc_Prealloc_3(_Gid_len_v, _Gid_cap, _Lold_cap_9);
}
_Ltext_10 = qalloc(_Llen_6 + 1);
memcpy(_Ltext_10, _Lr_start_3._Fref, _Llen_6);
_Ltext_10[_Llen_6] = 0;
_Gid_str_v[_Lid_8] = _Ltext_10;
_Gid_len_v[_Lid_8] = _Llen_6;
return _Lid_8;
}
uint32_t _Mglc_Slexer_Pget_num_dec_1(struct _Mglc_Slexer* _Llex_0) {
union _Mglc_Srdr _Lr_start_1;
union _Mglc_Srdr _Lr_cursor_2;
size_t _Llength_3;
uint64_t _Lval_4;
_Lr_start_1._Fref = (*_Llex_0)._Fstart;
_Lr_cursor_2._Fref = (*_Llex_0)._Fcursor;
_Llength_3 = (_Lr_cursor_2._Fpos - _Lr_start_1._Fpos);
if(_Llength_3 > 10) {
fprintf(stdout, "%s:%u:%u: Integer literal was too long\n", input_path, _Grow, _Gcol);
exit(_Mstdc_Eexit_Cfailure);
}
_Lval_4 = (uint64_t)(0);
for(int i = _Llength_3; i > 0; ) {
i --;
_Lval_4 = ((_Lval_4 * (uint64_t)(10)) + (_Lr_start_1._F1[0] - '0'));
_Lr_start_1._Fpos++;
continue_0:;
}
break_0:;
if(_Lval_4 > -1) {
fprintf(stdout, "%s:%u:%u: Integer literal was out of bounds\n", input_path, _Grow, _Gcol);
exit(_Mstdc_Eexit_Cfailure);
}
return (uint32_t)(_Lval_4);
}
uint32_t _Mglc_Slexer_Pget_num_oct_1(struct _Mglc_Slexer* _Llex_0) {
union _Mglc_Srdr _Lr_start_1;
union _Mglc_Srdr _Lr_cursor_2;
size_t _Llength_3;
uint64_t _Lval_4;
_Lr_start_1._Fref = (*_Llex_0)._Fstart;
_Lr_cursor_2._Fref = (*_Llex_0)._Fcursor;
_Llength_3 = (_Lr_cursor_2._Fpos - _Lr_start_1._Fpos);
if(_Llength_3 > 12) {
fprintf(stdout, "%s:%u:%u: Integer literal was too long\n", input_path, _Grow, _Gcol);
exit(_Mstdc_Eexit_Cfailure);
}
_Lval_4 = (uint64_t)(0);
for(int i = _Llength_3; i > 0; ) {
i --;
_Lval_4 = ((_Lval_4 * (uint64_t)(8)) + (_Lr_start_1._F1[0] - '0'));
_Lr_start_1._Fpos++;
continue_0:;
}
break_0:;
if(_Lval_4 > -1) {
fprintf(stdout, "%s:%u:%u: Integer literal was out of bounds\n", input_path, _Grow, _Gcol);
exit(_Mstdc_Eexit_Cfailure);
}
return (uint32_t)(_Lval_4);
}
int32_t _Mglc_Slexer_Pget_include_1(struct _Mglc_Slexer* _Llex_0) {
union _Mglc_Srdr _Lr_start_1;
union _Mglc_Srdr _Lr_cursor_2;
size_t _Llength_3;
uint8_t _Llen_4;
int32_t _Linclude_6;
char* _Ltext_8;
_Lr_start_1._Fref = (*_Llex_0)._Fstart;
_Lr_start_1._Fpos += 9;
_Lr_cursor_2._Fref = (*_Llex_0)._Fcursor;
_Llength_3 = (_Lr_cursor_2._Fpos - _Lr_start_1._Fpos - 1);
if(_Llength_3 > 255) {
fprintf(stdout, "too long include was detected\n");
exit(_Mstdc_Eexit_Cfailure);
}
_Llen_4 = (uint8_t)(_Llength_3);
int32_t _Li_5;
_Li_5 = 0;
for(int i = _Ginclude_c; i > 0; ) {
i --;
if(_Ginclude_len_v[_Li_5] == _Llen_4) {
if(memcmp(_Ginclude_str_v[_Li_5], _Lr_start_1._Fref, _Llen_4) == 0) {
return _Li_5;
}
}
continue_0:;
_Li_5++;
}
break_0:;
_Linclude_6 = _Ginclude_c++;
if(_Ginclude_cap <= _Ginclude_c) {
int32_t _Lold_cap_7;
_Lold_cap_7 = _Ginclude_cap;
_Mglc_Pgrow_2(_Ginclude_cap, _Ginclude_c);
_Mglc_Prealloc_3(_Ginclude_str_v, _Ginclude_cap, _Lold_cap_7);
_Mglc_Prealloc_3(_Ginclude_len_v, _Ginclude_cap, _Lold_cap_7);
}
_Ltext_8 = qalloc(_Llen_4 + 1);
memcpy(_Ltext_8, _Lr_start_1._Fref, _Llen_4);
_Ltext_8[_Llen_4] = 0;
_Ginclude_str_v[_Linclude_6] = _Ltext_8;
_Ginclude_len_v[_Linclude_6] = _Llen_4;
return _Linclude_6;
}
void* qalloc(int32_t _Lsize_0) {
if(sizeof(void*) == 8) {
_Lsize_0 = ((_Lsize_0 + 7) & (-1 ^ 7));
} else {
_Lsize_0 = ((_Lsize_0 + 3) & (-1 ^ 3));
}
if(_Lsize_0 <= (_Gquick_alloc_cap - _Gquick_alloc_c)) {
union _Mglc_Srdr _Lr_1;
_Lr_1._Fref = _Gquick_alloc_v;
_Lr_1._Fpos += _Gquick_alloc_c;
_Gquick_alloc_c += _Lsize_0;
return _Lr_1._Fref;
}
_Mglc_Pgrow_2(_Gquick_alloc_cap, _Gquick_alloc_c + _Lsize_0);
_Gquick_alloc_v = malloc(_Gquick_alloc_cap);
memset(_Gquick_alloc_v, 0, _Gquick_alloc_cap);
_Gquick_alloc_c = _Lsize_0;
return _Gquick_alloc_v;
}
void _Mglc_Swtr_Pn1_2(union _Mglc_Swtr* _Lw_0, uint8_t _Ln_1) {
(*_Lw_0)._F1[0] = _Ln_1;
(*_Lw_0)._Fpos++;
}
void _Mglc_Swtr_Pcopy_3(union _Mglc_Swtr* _Lw_0, void* _Ldata_1, int32_t _Lsize_2) {
memcpy((*_Lw_0)._Fref, _Ldata_1, _Lsize_2);
(*_Lw_0)._Fpos += _Lsize_2;
}
void _Mglc_Ename_type_Pwr_2(_Mglc_Ename_type _Li_0, union _Mglc_Swtr* _Lw_1) {
_Mglc_Swtr_Pn1_2(_Lw_1, _Li_0);
}
void _Mglc_Ebasic_type_id_Pwr_2(_Mglc_Ebasic_type_id _Le_0, union _Mglc_Swtr* _Lw_1) {
_Mglc_Swtr_Pn1_2(_Lw_1, _Le_0);
}
void _Mglc_Eat_Pwr_3(_Mglc_Eat _Lat_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2) {
if(_Lat_0 == _Mglc_Eat_Cnil) {
Fputnum(_Lw_1, 0);
} else {
if(_Lheader_2) {
Fputnum(_Lw_1, 1 + _Gat_in_header_idx_v[_Lat_0]);
} else {
Fputnum(_Lw_1, 1 + _Lat_0);
_Mglc_Eat_Pput_to_header_1(_Lat_0);
}
}
}
void _Mglc_Eid_Pwr_3(_Mglc_Eid _Lid_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2) {
if(_Lid_0 == _Mglc_Eid_Cnil) {
Fputnum(_Lw_1, 0);
} else {
if(_Lheader_2) {
Fputnum(_Lw_1, 1 + _Gid_in_header_idx_v[_Lid_0]);
} else {
Fputnum(_Lw_1, 1 + _Lid_0);
if((_Gid_in_header_v[(_Lid_0 >> 3)] & (1 << (_Lid_0 & 7))) == 0) {
_Gid_in_header_v[(_Lid_0 >> 3)] |= (1 << (_Lid_0 & 7));
_Gid_in_header_idx_v[_Lid_0] = _Gid_in_header_c;
_Gid_in_header_id_v[_Gid_in_header_c++] = _Lid_0;
}
}
}
}
void _Mglc_Pwrite_cvar_2(union _Mglc_Swtr* _Lw_0, bool _Lheader_1) {
Fputnum(_Lw_0, _Gcvar_c);
int32_t _Li_2;
_Li_2 = 0;
for(int i = _Gcvar_c; i > 0; ) {
i --;
struct _Mglc_Scvar* _Lcvar_3;
_Lcvar_3 = (&_Gcvar_v[_Li_2]);
_Mglc_Einclude_Pwr_2((*_Lcvar_3)._Finclude, _Lw_0);
_Mglc_Eat_Pwr_3((*_Lcvar_3)._Fat, _Lw_0, _Lheader_1);
_Mglc_Sdecl_var_Pwr_3(&(*_Lcvar_3)._Fdecl, _Lw_0, _Lheader_1);
_Mglc_Ecvar_flags_Pwr_2((*_Lcvar_3)._Fflags, _Lw_0);
if(((*_Lcvar_3)._Fflags & _Mglc_Ecvar_flags_Cset_expr) != _Mglc_Ecvar_flags_C0) {
_Mglc_Eexpr_Pwr_3((*_Lcvar_3)._Fexpr_set, _Lw_0, _Lheader_1);
} else {
_Mglc_Ecvar_Pwr_2((*_Lcvar_3)._Flast_cvar, _Lw_0);
}
continue_0:;
_Li_2++;
}
break_0:;
}
void _Mglc_Pwrite_gvar_2(union _Mglc_Swtr* _Lw_0, bool _Lheader_1) {
Fputnum(_Lw_0, _Ggvar_c);
int32_t _Li_2;
_Li_2 = 0;
for(int i = _Ggvar_c; i > 0; ) {
i --;
struct _Mglc_Sdecl_gvar* _Lgvar_3;
_Lgvar_3 = (&_Ggvar_v[_Li_2]);
_Mglc_Einclude_Pwr_2((*_Lgvar_3)._Finclude, _Lw_0);
_Mglc_Eat_Pwr_3((*_Lgvar_3)._Fat, _Lw_0, _Lheader_1);
_Mglc_Sdecl_var_Pwr_3(&(*_Lgvar_3)._Fdecl, _Lw_0, _Lheader_1);
continue_0:;
_Li_2++;
}
break_0:;
}
void _Mglc_Pwrite_enum_2(union _Mglc_Swtr* _Lw_0, bool _Lheader_1) {
Fputnum(_Lw_0, _Genum_c);
int32_t _Li_2;
_Li_2 = 0;
for(int i = _Genum_c; i > 0; ) {
i --;
struct _Mglc_Senum* _Le_3;
_Le_3 = _Genum_v[_Li_2++];
Fputnum(_Lw_0, (*_Le_3)._Fbegin_row);
Fputnum(_Lw_0, (*_Le_3)._Fbegin_col);
Fputnum(_Lw_0, (*_Le_3)._Fend_row);
Fputnum(_Lw_0, (*_Le_3)._Fend_col);
_Mglc_Einclude_Pwr_2((*_Le_3)._Finclude, _Lw_0);
_Mglc_Eat_Pwr_3((*_Le_3)._Fat, _Lw_0, _Lheader_1);
_Mglc_Eat_Pwr_3((*_Le_3)._Fbase_type, _Lw_0, _Lheader_1);
_Mglc_Eenum_flags_Pwr_2((*_Le_3)._Fflags, _Lw_0);
if(((*_Le_3)._Fflags & _Mglc_Eenum_flags_Creal_name) != _Mglc_Eenum_flags_C0) {
_Mglc_Eid_Pwr_3((*_Le_3)._Freal_name, _Lw_0, _Lheader_1);
}
continue_0:;
}
break_0:;
}
void _Mglc_Pwrite_struct_2(union _Mglc_Swtr* _Lw_0, bool _Lheader_1) {
Fputnum(_Lw_0, _Gstruct_c);
int32_t _Li_2;
_Li_2 = 0;
for(int i = _Gstruct_c; i > 0; ) {
i --;
struct _Mglc_Sstruct* _Ls_3;
_Ls_3 = _Gstruct_v[_Li_2++];
_Mglc_Swtr_Pn1_2(_Lw_0, (*_Ls_3)._Ffvar_c);
Fputnum(_Lw_0, (*_Ls_3)._Fbegin_row);
Fputnum(_Lw_0, (*_Ls_3)._Fbegin_col);
Fputnum(_Lw_0, (*_Ls_3)._Fend_row);
Fputnum(_Lw_0, (*_Ls_3)._Fend_col);
_Mglc_Einclude_Pwr_2((*_Ls_3)._Finclude, _Lw_0);
_Mglc_Eat_Pwr_3((*_Ls_3)._Fat, _Lw_0, _Lheader_1);
_Mglc_Estruct_flags_Pwr_2((*_Ls_3)._Fflags, _Lw_0);
int32_t _Lj_4;
_Lj_4 = 0;
for(int i = (*_Ls_3)._Ffvar_c; i > 0; ) {
i --;
_Mglc_Sfvar_Pwr_3(&(*_Ls_3)._Ffvar_v[_Lj_4], _Lw_0, _Lheader_1);
continue_1:;
_Lj_4++;
}
break_1:;
if(((*_Ls_3)._Fflags & _Mglc_Estruct_flags_Creal_name) != _Mglc_Estruct_flags_C0) {
_Mglc_Eid_Pwr_3((*_Ls_3)._Freal_name, _Lw_0, _Lheader_1);
}
continue_0:;
}
break_0:;
}
void _Mglc_Pwrite_func_2(union _Mglc_Swtr* _Lw_0, bool _Lheader_1) {
Fputnum(_Lw_0, _Gfunc_c);
int32_t _Li_2;
_Li_2 = 0;
for(int i = _Gfunc_c; i > 0; ) {
i --;
struct _Mglc_Sdecl_func* _Lf_3;
_Lf_3 = _Gfunc_v[_Li_2++];
_Mglc_Swtr_Pn1_2(_Lw_0, (*_Lf_3)._Ffarg_c);
Fputnum(_Lw_0, (*_Lf_3)._Fbegin_row);
Fputnum(_Lw_0, (*_Lf_3)._Fbegin_col);
Fputnum(_Lw_0, (*_Lf_3)._Fend_row);
Fputnum(_Lw_0, (*_Lf_3)._Fend_col);
_Mglc_Einclude_Pwr_2((*_Lf_3)._Finclude, _Lw_0);
_Mglc_Eat_Pwr_3((*_Lf_3)._Fat, _Lw_0, _Lheader_1);
_Mglc_Sdecl_var_Pwr_3(&(*_Lf_3)._Fdecl, _Lw_0, _Lheader_1);
int32_t _Lj_4;
_Lj_4 = 0;
for(int i = (*_Lf_3)._Ffarg_c; i > 0; ) {
i --;
_Mglc_Sfarg_Pwr_3(&(*_Lf_3)._Ffarg_v[_Lj_4], _Lw_0, _Lheader_1);
continue_1:;
_Lj_4++;
}
break_1:;
_Mglc_Swtr_Pn1_2(_Lw_0, (*_Lf_3)._Fthis_idx);
if((*_Lf_3)._Fthis_idx != -1) {
_Mglc_Swtr_Pn1_2(_Lw_0, (*_Lf_3)._Fthis_group);
}
_Mglc_Swtr_Pn1_2(_Lw_0, (*_Lf_3)._Fgroup_c);
int32_t _Lj_5;
_Lj_5 = 0;
for(int i = (*_Lf_3)._Fgroup_c; i > 0; ) {
i --;
_Mglc_Swtr_Pn1_2(_Lw_0, (*_Lf_3)._Fgroup_v[_Lj_5]);
continue_2:;
_Lj_5++;
}
break_2:;
if(_Lheader_1) {
if((*_Lf_3)._Fflags & _Mglc_Efunc_flags_Cinline) {
_Mglc_Efunc_flags_Pwr_2((*_Lf_3)._Fflags, _Lw_0);
} else {
_Mglc_Efunc_flags_Pwr_2((_Mglc_Efunc_flags)((*_Lf_3)._Fflags & (-1 ^ _Mglc_Efunc_flags_Chas_body)), _Lw_0);
}
} else {
_Mglc_Efunc_flags_Pwr_2((*_Lf_3)._Fflags, _Lw_0);
}
if(((*_Lf_3)._Fflags & _Mglc_Efunc_flags_Creal_name) != _Mglc_Efunc_flags_C0) {
_Mglc_Eid_Pwr_3((*_Lf_3)._Freal_name, _Lw_0, _Lheader_1);
}
if(((*_Lf_3)._Fflags & _Mglc_Efunc_flags_Ccase) != _Mglc_Efunc_flags_C0) {
_Mglc_Eid_Pwr_3((*_Lf_3)._Fcase, _Lw_0, _Lheader_1);
}
continue_0:;
}
break_0:;
_Mglc_Efunc_Pwr_2(_Gfunc_main, _Lw_0);
int32_t _Li_6;
_Li_6 = 0;
for(int i = _Gfunc_c; i > 0; ) {
i --;
struct _Mglc_Sdecl_func* _Lf_7;
union _Mglc_Swtr _Lpos_4_8;
size_t _Lpos_4_next_9;
_Lf_7 = _Gfunc_v[_Li_6++];
if(((*_Lf_7)._Fflags & _Mglc_Efunc_flags_Chas_body) == _Mglc_Efunc_flags_C0) {
goto continue_3;
}
if(_Lheader_1) {
if((*_Lf_7)._Fflags & _Mglc_Efunc_flags_Cinline) {
} else {
goto continue_3;
}
}
_Lpos_4_8._F1 = (*_Lw_0)._F1;
(*_Lw_0)._Fpos += 4;
_Lpos_4_next_9 = (*_Lw_0)._Fpos;
_Mglc_Sdecl_func_Plvars_wr_3(_Lf_7, _Lw_0, _Lheader_1);
_Mglc_Sstmt_space_Pwr_3((*_Lf_7)._Fstmt_space, _Lw_0, _Lheader_1);
_Mglc_Swtr_Pn4_2(&_Lpos_4_8, (*_Lw_0)._Fpos - _Lpos_4_next_9);
continue_3:;
}
break_3:;
}
bool _Mstdc_Efile_Popen_4(_Mstdc_Efile* _Lfile_0, char* _Lpath_1, _Mstdc_Eopen_flags _Lflags_2, int32_t _Lmode_3) {
int32_t _Lfd_4;
_Lfd_4 = open(_Lpath_1, _Lflags_2, _Lmode_3);
if(_Lfd_4 != -1) {
(*_Lfile_0) = _Lfd_4;
return true;
} else {
return false;
}
}
void _Mglc_Eat_Pwr_header_2(_Mglc_Eat _Lid_0, union _Mglc_Swtr* _Lw_1) {
if(_Lid_0 == _Mglc_Eat_Cnil) {
Fputnum(_Lw_1, 0);
} else {
Fputnum(_Lw_1, 1 + _Gat_in_header_idx_v[_Lid_0]);
}
}
void _Mglc_Eid_Pwr_header_2(_Mglc_Eid _Lid_0, union _Mglc_Swtr* _Lw_1) {
if(_Lid_0 == _Mglc_Eid_Cnil) {
Fputnum(_Lw_1, 0);
} else {
Fputnum(_Lw_1, 1 + _Gid_in_header_idx_v[_Lid_0]);
}
}
void _Mglc_Pdecl_func_begin_3(_Mglc_Eid _Lname_0, int32_t _Lrow_1, int32_t _Lcol_2) {
_Gdecl_func_name = _Lname_0;
_Gdecl_func_row = _Lrow_1;
_Gdecl_func_col = _Lcol_2;
_Gdecl_func_flags = _Mglc_Efunc_flags_C0;
_Gdecl_func_flags2 = _Mglc_Efunc_flags2_C0;
_Gdecl_farg_c = 0;
_Gdecl_farg_group_c = 1;
_Gdecl_farg_group_v[0] = 0;
_Gdecl_func_this_idx = -1;
_Gdecl_func_this_group = -1;
_Gdecl_func_real_name = _Mglc_Eid_Cnil;
_Gdecl_func_case = _Mglc_Eid_Cnil;
_Mglc_Pquick_alloc_one_1(_Gdecl_func_space);
_Gdecl_func_ctx_space = _Gdecl_func_space;
}
void _Mglc_Pdecl_func_end_2(int32_t _Lrow_0, int32_t _Lcol_1) {
_Mglc_Efunc _Lf_idx_2;
struct _Mglc_Sdecl_func* _Lf_4;
struct _Mglc_Sstmt_space* _Lspace_9;
_Lf_idx_2 = (_Mglc_Efunc)(_Gfunc_c++);
if(_Gfunc_cap <= _Gfunc_c) {
_Mglc_Efunc _Lold_cap_3;
_Lold_cap_3 = _Gfunc_cap;
_Mglc_Pgrow_2(_Gfunc_cap, _Gfunc_c);
_Mglc_Prealloc_3(_Gfunc_v, _Gfunc_cap, _Lold_cap_3);
}
_Mglc_Pquick_alloc_plus_2(_Lf_4, sizeof(struct _Mglc_Sfarg) * _Gdecl_farg_c);
_Gctx_func = _Lf_4;
_Gnest_id = 0;
_Gfunc_v[_Lf_idx_2] = _Lf_4;
(*_Lf_4)._Fbegin_row = _Gdecl_func_row;
(*_Lf_4)._Fbegin_col = _Gdecl_func_col;
(*_Lf_4)._Fend_row = _Lrow_0;
(*_Lf_4)._Fend_col = _Lcol_1;
(*_Lf_4)._Finclude = _Gdecl_include;
(*_Lf_4)._Fat = _Gdecl_at;
if((_Gdecl_func_flags & _Mglc_Efunc_flags_Creal_name) != _Mglc_Efunc_flags_C0) {
if(_Gdecl_func_real_name == _Mglc_Eid_Cnil) {
(*_Lf_4)._Freal_name = _Gdecl_func_name;
} else {
(*_Lf_4)._Freal_name = _Gdecl_func_real_name;
}
}
if((_Gdecl_func_flags & _Mglc_Efunc_flags_Ccase) != _Mglc_Efunc_flags_C0) {
(*_Lf_4)._Fcase = _Gdecl_func_case;
}
_Gdecl_var._Fname = _Gdecl_func_name;
_Mglc_Sdecl_var_Pcopy_from_2(&(*_Lf_4)._Fdecl, &_Gdecl_var);
(*_Lf_4)._Ffarg_c = _Gdecl_farg_c;
int32_t _Li_5;
_Li_5 = 0;
for(int i = _Gdecl_farg_c; i > 0; ) {
i --;
struct _Mglc_Sfarg* _Lfa_6;
_Lfa_6 = (&(*_Lf_4)._Ffarg_v[_Li_5]);
_Mglc_Sfarg_Pcopy_from_2(_Lfa_6, &_Gdecl_farg_v[_Li_5]);
continue_0:;
_Li_5++;
}
break_0:;
(*_Lf_4)._Fthis_idx = _Gdecl_func_this_idx;
(*_Lf_4)._Fthis_group = _Gdecl_func_this_group;
(*_Lf_4)._Fgroup_c = _Gdecl_farg_group_c;
int32_t _Li_7;
_Li_7 = 0;
for(int i = _Gdecl_farg_group_c; i > 0; ) {
i --;
(*_Lf_4)._Fgroup_v[_Li_7] = _Gdecl_farg_group_v[_Li_7];
continue_1:;
_Li_7++;
}
break_1:;
(*_Lf_4)._Fflags = _Gdecl_func_flags;
if((_Gdecl_func_flags2 & _Mglc_Efunc_flags2_Cmain) != _Mglc_Efunc_flags2_C0) {
_Gfunc_main = _Lf_idx_2;
} else if(((_Gdecl_at == _Mglc_Eat_Croot) && (_Mglc_Eid_Plen_1((*_Lf_4)._Fdecl._Fname) == 4) && (memcmp("main", _Mglc_Eid_Pstr_1((*_Lf_4)._Fdecl._Fname), 4) == 0))) {
if(_Gfunc_main != _Mglc_Efunc_Cnil) {
struct _Mglc_Sdecl_func* _Lmain_8;
_Lmain_8 = _Mglc_Efunc_Pptr_1(_Gfunc_main);
fprintf(stdout, "%u:%u: There's already a function with @main attribute at %u:%u\n", (*_Lf_4)._Fbegin_row, (*_Lf_4)._Fbegin_col, (*_Lmain_8)._Fbegin_row, (*_Lmain_8)._Fbegin_col);
exit(_Mstdc_Eexit_Cfailure);
} else {
_Gfunc_main = _Lf_idx_2;
}
}
_Lspace_9 = _Gdecl_func_space;
(*_Lf_4)._Fstmt_space = _Lspace_9;
int32_t _Li_10;
_Li_10 = 0;
for(int i = _Gdecl_farg_c; i > 0; ) {
i --;
struct _Mglc_Sfarg* _Lfa_11;
_Mglc_Elvar _Llvar_i_12;
struct _Mglc_Slvar* _Llvar_13;
_Lfa_11 = (&(*_Lf_4)._Ffarg_v[_Li_10]);
_Llvar_i_12 = _Mglc_Sstmt_space_Plvar_new_4(_Lspace_9, (*_Lfa_11)._Fdecl._Fname, (*_Lfa_11)._Frow, (*_Lfa_11)._Fcol);
_Llvar_13 = _Mglc_Elvar_Pptr_1(_Llvar_i_12);
_Mglc_Sdecl_var_Pcopy_from_2(&(*_Llvar_13)._Fdecl, &(*_Lfa_11)._Fdecl);
continue_2:;
_Li_10++;
}
break_2:;
}
void _Mglc_Pdecl_struct_end_2(int32_t _Lrow_0, int32_t _Lcol_1) {
_Mglc_Estruct _Ls_idx_2;
struct _Mglc_Sstruct* _Ls_4;
_Ls_idx_2 = _Gstruct_c++;
if(_Gstruct_cap <= _Gstruct_c) {
_Mglc_Estruct _Lold_cap_3;
_Lold_cap_3 = _Gstruct_cap;
_Mglc_Pgrow_2(_Gstruct_cap, _Gstruct_c);
_Mglc_Prealloc_3(_Gstruct_v, _Gstruct_cap, _Lold_cap_3);
}
_Mglc_Pquick_alloc_plus_2(_Ls_4, sizeof(struct _Mglc_Sfvar) * _Gdecl_fvar_c);
_Gstruct_v[_Ls_idx_2] = _Ls_4;
(*_Ls_4)._Fbegin_row = _Gdecl_struct_row;
(*_Ls_4)._Fbegin_col = _Gdecl_struct_col;
(*_Ls_4)._Fend_row = _Lrow_0;
(*_Ls_4)._Fend_col = _Lcol_1;
(*_Ls_4)._Finclude = _Gdecl_include;
(*_Ls_4)._Fat = _Gdecl_struct_at;
(*_Ls_4)._Fflags = _Gdecl_struct_flags;
(*_Ls_4)._Ffvar_c = _Gdecl_fvar_c;
int32_t _Li_5;
_Li_5 = 0;
for(int i = _Gdecl_fvar_c; i > 0; ) {
i --;
struct _Mglc_Sfvar* _La_6;
_La_6 = (&(*_Ls_4)._Ffvar_v[_Li_5]);
_Mglc_Sdecl_var_Pcopy_from_2(&(*_La_6)._Fdecl, &_Gdecl_fvar_v[_Li_5]);
continue_0:;
_Li_5++;
}
break_0:;
(*_Ls_4)._Freal_name = _Gdecl_struct_real_name;
}
void _Mglc_Pdecl_var_begin_3(_Mglc_Eid _Lname_0, int32_t _Lrow_1, int32_t _Lcol_2) {
_Gdecl_var._Fname = _Lname_0;
_Gdecl_var_row = _Lrow_1;
_Gdecl_var_col = _Lcol_2;
_Mglc_Stype_info_Pinit_1(&_Gdecl_var._Ftype_info);
_Gdecl_var._Fflags = _Mglc_Evar_flags_C0;
_Gdecl_var._Freal_name = _Mglc_Eid_Cnil;
_Gdecl_var._Fsize_c = 0;
}
void _Mglc_Pdecl_var_attr_real_name_1(_Mglc_Eid _Lname_0) {
if((_Gdecl_var._Fflags & _Mglc_Evar_flags_Creal_name) != _Mglc_Evar_flags_C0) {
fprintf(stdout, "%u:%u: error @real-name specified more than once\n", _Glast_row, _Glast_col);
exit(_Mstdc_Eexit_Cfailure);
}
_Gdecl_var._Fflags |= _Mglc_Evar_flags_Creal_name;
_Gdecl_var._Freal_name = _Lname_0;
}
void _Mglc_Pdecl_var_attr_extern_0() {
if((_Gdecl_var._Fflags & _Mglc_Evar_flags_Cextern) != _Mglc_Evar_flags_C0) {
fprintf(stdout, "%u:%u: error @extern specified more than once\n", _Glast_row, _Glast_col);
exit(_Mstdc_Eexit_Cfailure);
}
_Gdecl_var._Fflags |= _Mglc_Evar_flags_Cextern;
}
void _Mglc_Pdecl_var_attr_no_decl_0() {
if((_Gdecl_var._Fflags & _Mglc_Evar_flags_Cno_decl) != _Mglc_Evar_flags_C0) {
fprintf(stdout, "%u:%u: error @no-decl specified more than once\n", _Glast_row, _Glast_col);
exit(_Mstdc_Eexit_Cfailure);
}
_Gdecl_var._Fflags |= _Mglc_Evar_flags_Cno_decl;
}
void _Mglc_Pdecl_var_end_0() {
}
void _Mglc_Pdecl_var_as_farg_2(int32_t _Lrow_0, int32_t _Lcol_1) {
int32_t _Lfarg_idx_2;
struct _Mglc_Sfarg* _Lfa_4;
_Lfarg_idx_2 = _Gdecl_farg_c++;
if(_Gdecl_farg_cap <= _Gdecl_farg_c) {
int32_t _Lold_cap_3;
_Lold_cap_3 = _Gdecl_farg_cap;
_Mglc_Pgrow_2(_Gdecl_farg_cap, _Gdecl_farg_c);
_Mglc_Prealloc_3(_Gdecl_farg_v, _Gdecl_farg_cap, _Lold_cap_3);
}
_Lfa_4 = (&_Gdecl_farg_v[_Lfarg_idx_2]);
(*_Lfa_4)._Frow = _Lrow_0;
(*_Lfa_4)._Fcol = _Lcol_1;
_Mglc_Sdecl_var_Pcopy_from_2(&(*_Lfa_4)._Fdecl, &_Gdecl_var);
_Gdecl_farg_group_v[(_Gdecl_farg_group_c - 1)]++;
}
void _Mglc_Pfarg_next_group_0() {
_Gdecl_farg_group_v[_Gdecl_farg_group_c] = 0;
_Gdecl_farg_group_c++;
}
void _Mglc_Pdecl_var_as_this_0() {
int32_t _Lfarg_idx_0;
_Gdecl_func_this_idx = _Gdecl_farg_c;
_Gdecl_func_this_group = (_Gdecl_farg_group_c - 1);
_Lfarg_idx_0 = _Gdecl_farg_c++;
if(_Gdecl_farg_cap <= _Gdecl_farg_c) {
int32_t _Lold_cap_1;
_Lold_cap_1 = _Gdecl_farg_cap;
_Mglc_Pgrow_2(_Gdecl_farg_cap, _Gdecl_farg_c);
_Mglc_Prealloc_3(_Gdecl_farg_v, _Gdecl_farg_cap, _Lold_cap_1);
}
_Mglc_Sdecl_var_Pcopy_from_2(&_Gdecl_farg_v[_Lfarg_idx_0]._Fdecl, &_Gdecl_var);
_Gdecl_farg_v[_Lfarg_idx_0]._Fdecl._Ftype = _Gdecl_at;
_Gdecl_farg_group_v[(_Gdecl_farg_group_c - 1)]++;
}
void _Mglc_Pdecl_var_as_fvar_0() {
uint32_t _Lfvar_0;
_Lfvar_0 = _Gdecl_fvar_c++;
if(_Gdecl_fvar_cap <= _Gdecl_fvar_c) {
uint32_t _Lold_cap_1;
_Lold_cap_1 = _Gdecl_fvar_cap;
_Mglc_Pgrow_2(_Gdecl_fvar_cap, _Gdecl_fvar_c);
_Mglc_Prealloc_3(_Gdecl_fvar_v, _Gdecl_fvar_cap, _Lold_cap_1);
}
_Mglc_Sdecl_var_Pcopy_from_2(&_Gdecl_fvar_v[_Lfvar_0], &_Gdecl_var);
}
void _Mglc_Pfunc_body_end_1(bool _Linline_0) {
struct _Mglc_Sdecl_func* _Lf_1;
int32_t _Lc_2;
struct _Mglc_Sstmt* _Ls_3;
_Lf_1 = _Gfunc_v[(_Gfunc_c - 1)];
(*_Lf_1)._Fflags |= _Mglc_Efunc_flags_Chas_body;
if(_Linline_0) {
(*_Lf_1)._Fflags |= _Mglc_Efunc_flags_Cinline;
}
_Lc_2 = 0;
_Ls_3 = (*(*_Lf_1)._Fstmt_space)._Fstmt_first;
while(_Ls_3 != NULL) {
_Lc_2++;
_Ls_3 = (*_Ls_3)._Fstmt_next;
continue_0:;
}
break_0:;
}
void _Mglc_Pexpr_push_call_2(int32_t _Lrow_0, int32_t _Lcol_1) {
int8_t _Lcall_idx_2;
_Lcall_idx_2 = _Gexpr_call_c++;
if(_Lcall_idx_2 >= _Mglc_Cexpr_call_nest_limit) {
fprintf(stdout, "%u:%u: Too much nested calls\n", _Lrow_0, _Lcol_1);
exit(_Mstdc_Eexit_Cfailure);
}
_Gexpr_call_carg_c[_Lcall_idx_2] = 0;
_Gexpr_call_cgrp_c[_Lcall_idx_2] = 1;
_Gexpr_call_cgrp_v[_Lcall_idx_2][0] = 0;
}
_Mglc_Eexpr _Mglc_Pexpr_pop_func_2(_Mglc_Eat _Lat_0, _Mglc_Eid _Lfunc_name_1) {
int8_t _Lcall_idx_2;
uint8_t _Lcarg_c_3;
struct _Mglc_Sexpr_func* _Le_4;
_Mglc_Eexpr _Le_idx_5;
_Lcall_idx_2 = (_Gexpr_call_c -= 1);
_Lcarg_c_3 = _Gexpr_call_carg_c[_Lcall_idx_2];
_Mglc_Pquick_alloc_plus_2(_Le_4, sizeof(struct _Mglc_Scarg) * _Lcarg_c_3);
_Le_idx_5 = _Mglc_Pexpr_push_2(&(*_Le_4)._Fbase, _Mglc_Eexpr_type_Cfunc);
(*_Le_4)._Fat = _Lat_0;
(*_Le_4)._Ffunc_name = _Lfunc_name_1;
(*_Le_4)._Fcarg_c = _Lcarg_c_3;
int32_t _Li_6;
_Li_6 = 0;
for(int i = _Lcarg_c_3; i > 0; ) {
i --;
(*_Le_4)._Fcarg_v[_Li_6]._Fref = 0;
(*_Le_4)._Fcarg_v[_Li_6]._Fexpr = _Gexpr_call_carg_v[_Lcall_idx_2][_Li_6];
continue_0:;
_Li_6++;
}
break_0:;
(*_Le_4)._Fgroup_c = _Gexpr_call_cgrp_c[_Lcall_idx_2];
int32_t _Li_7;
_Li_7 = 0;
for(int i = (*_Le_4)._Fgroup_c; i > 0; ) {
i --;
(*_Le_4)._Fgroup_v[_Li_7] = _Gexpr_call_cgrp_v[_Lcall_idx_2][_Li_7];
continue_1:;
_Li_7++;
}
break_1:;
return _Le_idx_5;
}
_Mglc_Eexpr _Mglc_Pexpr_pop_method_2(_Mglc_Eexpr _Lthis_0, _Mglc_Eid _Lfunc_name_1) {
int8_t _Lcall_idx_2;
uint8_t _Lcarg_c_3;
struct _Mglc_Sexpr_method* _Le_4;
_Mglc_Eexpr _Le_idx_5;
_Lcall_idx_2 = (_Gexpr_call_c -= 1);
_Lcarg_c_3 = _Gexpr_call_carg_c[_Lcall_idx_2];
_Mglc_Pquick_alloc_plus_2(_Le_4, sizeof(struct _Mglc_Scarg) * _Lcarg_c_3);
_Le_idx_5 = _Mglc_Pexpr_push_2(&(*_Le_4)._Fbase, _Mglc_Eexpr_type_Cmethod);
(*_Le_4)._Fthis = _Lthis_0;
(*_Le_4)._Ffunc_name = _Lfunc_name_1;
(*_Le_4)._Fcarg_c = _Lcarg_c_3;
int32_t _Li_6;
_Li_6 = 0;
for(int i = _Lcarg_c_3; i > 0; ) {
i --;
(*_Le_4)._Fcarg_v[_Li_6]._Fexpr = _Gexpr_call_carg_v[_Lcall_idx_2][_Li_6];
continue_0:;
_Li_6++;
}
break_0:;
(*_Le_4)._Fgroup_c = _Gexpr_call_cgrp_c[_Lcall_idx_2];
int32_t _Li_7;
_Li_7 = 0;
for(int i = (*_Le_4)._Fgroup_c; i > 0; ) {
i --;
(*_Le_4)._Fgroup_v[_Li_7] = _Gexpr_call_cgrp_v[_Lcall_idx_2][_Li_7];
continue_1:;
_Li_7++;
}
break_1:;
return _Le_idx_5;
}
void _Mglc_Pcarg_push_1(_Mglc_Eexpr _Lexpr_0) {
int8_t _Lcall_idx_1;
_Lcall_idx_1 = (_Gexpr_call_c - 1);
_Gexpr_call_carg_v[_Lcall_idx_1][_Gexpr_call_carg_c[_Lcall_idx_1]++] = _Lexpr_0;
_Gexpr_call_cgrp_v[_Lcall_idx_1][(_Gexpr_call_cgrp_c[_Lcall_idx_1] - 1)]++;
}
void _Mglc_Pcarg_push_str_1(_Mglc_Eexpr _Lexpr_0) {
if(true) {
int8_t _Lcall_idx_1;
_Lcall_idx_1 = (_Gexpr_call_c - 1);
_Gexpr_call_carg_v[_Lcall_idx_1][_Gexpr_call_carg_c[_Lcall_idx_1]++] = _Lexpr_0;
_Gexpr_call_cgrp_v[_Lcall_idx_1][(_Gexpr_call_cgrp_c[_Lcall_idx_1] - 1)]++;
}
if(true) {
struct _Mglc_Sexpr_str* _Le_2;
int32_t _Llen_3;
struct _Mglc_Sexpr_str_node* _Ls_4;
int8_t _Lcall_idx_5;
_Le_2 = _Mglc_Eexpr_Pptr_1(_Lexpr_0);
_Llen_3 = 0;
_Ls_4 = (*_Le_2)._Ffirst;
while(1) {
_Llen_3 += (*_Ls_4)._Flen;
_Ls_4 = (*_Ls_4)._Fnext;
if(_Ls_4 == NULL) {
goto break_0;
}
continue_0:;
}
break_0:;
_Lcall_idx_5 = (_Gexpr_call_c - 1);
_Gexpr_call_carg_v[_Lcall_idx_5][_Gexpr_call_carg_c[_Lcall_idx_5]++] = _Mglc_Pexpr_int_2(_Llen_3, _Mglc_Eexpr_int_Cdec);
_Gexpr_call_cgrp_v[_Lcall_idx_5][(_Gexpr_call_cgrp_c[_Lcall_idx_5] - 1)]++;
}
}
void _Mglc_Pcarg_next_group_0() {
int8_t _Lcall_idx_0;
_Lcall_idx_0 = (_Gexpr_call_c - 1);
_Gexpr_call_cgrp_v[_Lcall_idx_0][_Gexpr_call_cgrp_c[_Lcall_idx_0]] = 0;
_Gexpr_call_cgrp_c[_Lcall_idx_0]++;
}
void _Mglc_Pexpr2stmt_5(_Mglc_Eexpr _Le_0, int32_t _Lbegin_row_1, int32_t _Lbegin_col_2, int32_t _Lend_row_3, int32_t _Lend_col_4) {
struct _Mglc_Sstmt_expr* _Ls_5;
_Mglc_Pquick_alloc_one_1(_Ls_5);
_Mglc_Pstmt_push_6(&(*_Ls_5)._Fbase, _Lbegin_row_1, _Lbegin_col_2, _Lend_row_3, _Lend_col_4, _Mglc_Estmt_type_Cexpr);
(*_Ls_5)._Fexpr = _Le_0;
}
void _Mglc_Pstmt_return_5(_Mglc_Eexpr _Le_0, int32_t _Lbegin_row_1, int32_t _Lbegin_col_2, int32_t _Lend_row_3, int32_t _Lend_col_4) {
struct _Mglc_Sstmt_return* _Ls_5;
_Mglc_Pquick_alloc_one_1(_Ls_5);
_Mglc_Pstmt_push_6(&(*_Ls_5)._Fbase, _Lbegin_row_1, _Lbegin_col_2, _Lend_row_3, _Lend_col_4, _Mglc_Estmt_type_Creturn);
(*_Ls_5)._Fexpr = _Le_0;
}
void _Mglc_Pstmt_continue_5(_Mglc_Eid _Lid_0, int32_t _Lbegin_row_1, int32_t _Lbegin_col_2, int32_t _Lend_row_3, int32_t _Lend_col_4) {
struct _Mglc_Sstmt_continue* _Ls_5;
_Mglc_Pquick_alloc_one_1(_Ls_5);
_Mglc_Pstmt_push_6(&(*_Ls_5)._Fbase, _Lbegin_row_1, _Lbegin_col_2, _Lend_row_3, _Lend_col_4, _Mglc_Estmt_type_Ccontinue);
if(_Gnest_stack_c <= 0) {
fprintf(stdout, "%s:%u:%u: Cannot have a continue because it's not inside a loop\n", input_path, _Lbegin_row_1, _Lbegin_col_2);
exit(_Mstdc_Eexit_Cfailure);
}
(*_Ls_5)._Fnest = (_Gnest_stack_c - 1);
}
void _Mglc_Pstmt_break_5(_Mglc_Eid _Lid_0, int32_t _Lbegin_row_1, int32_t _Lbegin_col_2, int32_t _Lend_row_3, int32_t _Lend_col_4) {
struct _Mglc_Sstmt_break* _Ls_5;
_Mglc_Pquick_alloc_one_1(_Ls_5);
_Mglc_Pstmt_push_6(&(*_Ls_5)._Fbase, _Lbegin_row_1, _Lbegin_col_2, _Lend_row_3, _Lend_col_4, _Mglc_Estmt_type_Cbreak);
if(_Gnest_stack_c <= 0) {
fprintf(stdout, "%s:%u:%u: Cannot have a break because it's not inside a loop\n", input_path, _Lbegin_row_1, _Lbegin_col_2);
exit(_Mstdc_Eexit_Cfailure);
}
(*_Ls_5)._Fnest = (_Gnest_stack_c - 1);
}
void _Mglc_Pfunc_attr_main_0() {
if((_Gdecl_func_flags2 & _Mglc_Efunc_flags2_Cmain) != _Mglc_Efunc_flags2_C0) {
fprintf(stdout, "%s:%u:%u: Error @main specified more than once\n", input_path, _Glast_row, _Glast_col);
exit(_Mstdc_Eexit_Cfailure);
}
if(_Gfunc_main != _Mglc_Efunc_Cnil) {
struct _Mglc_Sdecl_func* _Lfirst_0;
_Lfirst_0 = _Mglc_Efunc_Pptr_1(_Gfunc_main);
fprintf(stdout, "There cannot be more than one function with @main attribute, first was %s:%u:%u and then %u:%u\n", input_path, (*_Lfirst_0)._Fbegin_row, (*_Lfirst_0)._Fbegin_col, _Gdecl_func_row, _Gdecl_func_col);
exit(_Mstdc_Eexit_Cfailure);
}
_Gdecl_func_flags2 |= _Mglc_Efunc_flags2_Cmain;
}
void _Mglc_Pfunc_attr_glc_name_0() {
if((_Gdecl_func_flags & _Mglc_Efunc_flags_Cglc_name) != _Mglc_Efunc_flags_C0) {
fprintf(stdout, "%s:%u:%u: Error @glc-name specified more than once\n", input_path, _Glast_row, _Glast_col);
exit(_Mstdc_Eexit_Cfailure);
}
_Gdecl_func_flags |= _Mglc_Efunc_flags_Cglc_name;
}
void _Mglc_Pfunc_attr_process_0() {
if((_Gdecl_func_flags & _Mglc_Efunc_flags_Cprocess) != _Mglc_Efunc_flags_C0) {
fprintf(stdout, "%s:%u:%u: Error @process specified more than once\n", input_path, _Glast_row, _Glast_col);
exit(_Mstdc_Eexit_Cfailure);
}
_Gdecl_func_flags |= _Mglc_Efunc_flags_Cprocess;
}
void _Mglc_Pfunc_attr_var_args_0() {
if((_Gdecl_func_flags & _Mglc_Efunc_flags_Cvar_args) != _Mglc_Efunc_flags_C0) {
fprintf(stdout, "%s:%u:%u: Error @var-args specified more than once\n", input_path, _Glast_row, _Glast_col);
exit(_Mstdc_Eexit_Cfailure);
}
_Gdecl_func_flags |= _Mglc_Efunc_flags_Cvar_args;
}
void _Mglc_Pfunc_attr_no_decl_0() {
if((_Gdecl_func_flags & _Mglc_Efunc_flags_Cno_decl) != _Mglc_Efunc_flags_C0) {
fprintf(stdout, "%s:%u:%u: Error @no-decl specified more than once\n", input_path, _Glast_row, _Glast_col);
exit(_Mstdc_Eexit_Cfailure);
}
_Gdecl_func_flags |= _Mglc_Efunc_flags_Cno_decl;
}
void _Mglc_Pfunc_attr_no_body_0() {
if((_Gdecl_func_flags & _Mglc_Efunc_flags_Cno_body) != _Mglc_Efunc_flags_C0) {
fprintf(stdout, "%s:%u:%u: Error @no-body specified more than once\n", input_path, _Glast_row, _Glast_col);
exit(_Mstdc_Eexit_Cfailure);
}
_Gdecl_func_flags |= _Mglc_Efunc_flags_Cno_body;
}
void _Mglc_Pfunc_attr_real_name_1(_Mglc_Eid _Lname_0) {
if((_Gdecl_func_flags & _Mglc_Efunc_flags_Creal_name) != _Mglc_Efunc_flags_C0) {
fprintf(stdout, "%s:%u:%u: Error @real-name specified more than once\n", input_path, _Glast_row, _Glast_col);
exit(_Mstdc_Eexit_Cfailure);
}
_Gdecl_func_flags |= _Mglc_Efunc_flags_Creal_name;
_Gdecl_func_real_name = _Lname_0;
}
void _Mglc_Pfunc_attr_case_1(_Mglc_Eid _Lname_0) {
char* _Lname_str_1;
uint8_t _Lname_len_2;
char* _Lfunc_name_str_3;
uint8_t _Lfunc_name_len_4;
if((_Gdecl_func_flags & _Mglc_Efunc_flags_Ccase) != _Mglc_Efunc_flags_C0) {
fprintf(stdout, "%s:%u:%u: Error @case specified more than once\n", input_path, _Glast_row, _Glast_col);
exit(_Mstdc_Eexit_Cfailure);
}
_Lname_str_1 = _Mglc_Eid_Pstr_1(_Lname_0);
_Lname_len_2 = _Mglc_Eid_Plen_1(_Lname_0);
_Lfunc_name_str_3 = _Mglc_Eid_Pstr_1(_Gdecl_func_name);
_Lfunc_name_len_4 = _Mglc_Eid_Plen_1(_Gdecl_func_name);
if(((_Lname_len_2 > _Lfunc_name_len_4) || (_Lfunc_name_str_3[_Lname_len_2] != '-') || (memcmp(_Lname_str_1, _Lfunc_name_str_3, _Lname_len_2) != 0))) {
fprintf(stdout, "%s:%u:%u: Error, function name must begin with words used in @case followed by '-' (dash) then followed by the name of the cvar of case\n", input_path, _Glast_row, _Glast_col);
exit(_Mstdc_Eexit_Cfailure);
}
_Gdecl_func_flags |= _Mglc_Efunc_flags_Ccase;
_Gdecl_func_case = _Lname_0;
}
_Mglc_Eexpr _Mglc_Pexpr_lvar_4(_Mglc_Eid _Lname_0, uint8_t _Ldecl_1, int32_t _Lrow_2, int32_t _Lcol_3) {
if(_Ldecl_1 == 0) {
struct _Mglc_Sstmt_space* _Lspace_4;
_Lspace_4 = _Gdecl_func_ctx_space;
while(1) {
_Mglc_Elvar* _Lv_5;
_Mglc_Elvar _Lfound_6;
_Lv_5 = (*_Lspace_4)._Flvar_v;
_Lfound_6 = _Mglc_Elvar_Cnil;
int32_t _Li_7;
_Li_7 = 0;
for(int i = (*_Lspace_4)._Flvar_c; i > 0; ) {
i --;
_Mglc_Elvar _Llvar_8;
_Llvar_8 = _Lv_5[_Li_7];
if(_Mglc_Elvar_Pname_1(_Llvar_8) == _Lname_0) {
_Lfound_6 = _Llvar_8;
goto break_1;
}
continue_1:;
_Li_7++;
}
break_1:;
if(_Lfound_6 != _Mglc_Elvar_Cnil) {
struct _Mglc_Sexpr_lvar* _Le_9;
_Mglc_Eexpr _Le_idx_10;
_Mglc_Pquick_alloc_one_1(_Le_9);
_Le_idx_10 = _Mglc_Pexpr_push_2(&(*_Le_9)._Fbase, _Mglc_Eexpr_type_Clvar);
(*_Le_9)._Flvar = _Lfound_6;
return _Le_idx_10;
}
_Lspace_4 = (*_Lspace_4)._Fparent;
if(_Lspace_4 == NULL) {
goto break_0;
}
continue_0:;
}
break_0:;
fprintf(stdout, "%s:%u:%u: lvar '%s' was not found\n", input_path, _Lrow_2, _Lcol_3, _Mglc_Eid_Pstr_1(_Lname_0));
exit(_Mstdc_Eexit_Cfailure);
return _Mglc_Eexpr_Cnil;
} else {
struct _Mglc_Sstmt_space* _Lspace_11;
struct _Mglc_Sexpr_lvar* _Le_12;
_Mglc_Eexpr _Le_idx_13;
struct _Mglc_Slvar* _Llvar_14;
_Lspace_11 = _Gdecl_func_ctx_space;
while(_Ldecl_1 > 1) {
_Lspace_11 = (*_Lspace_11)._Fparent;
if(_Lspace_11 == NULL) {
fprintf(stdout, "%s:%u:%u: Cannot declare lvar '%s' with too much '+'\n", input_path, _Lrow_2, _Lcol_3, _Mglc_Eid_Pstr_1(_Lname_0));
exit(_Mstdc_Eexit_Cfailure);
}
if(((*_Lspace_11)._Fflags & _Mglc_Estmt_space_flags_Cskip_lvar_decl) == _Mglc_Estmt_space_flags_C0) {
_Ldecl_1--;
}
continue_2:;
}
break_2:;
_Mglc_Pquick_alloc_one_1(_Le_12);
_Le_idx_13 = _Mglc_Pexpr_push_2(&(*_Le_12)._Fbase, _Mglc_Eexpr_type_Clvar);
(*_Le_12)._Flvar = _Mglc_Sstmt_space_Plvar_new_4(_Lspace_11, _Lname_0, _Lrow_2, _Lcol_3);
_Llvar_14 = _Mglc_Elvar_Pptr_1((*_Le_12)._Flvar);
_Gdecl_var._Fname = _Lname_0;
_Mglc_Sdecl_var_Pcopy_from_2(&(*_Llvar_14)._Fdecl, &_Gdecl_var);
return _Le_idx_13;
}
}
_Mglc_Eexpr _Mglc_Pexpr_gvar_2(_Mglc_Eat _Lat_0, _Mglc_Eid _Lname_1) {
struct _Mglc_Sexpr_gvar* _Le_2;
_Mglc_Eexpr _Le_idx_3;
_Mglc_Pquick_alloc_one_1(_Le_2);
_Le_idx_3 = _Mglc_Pexpr_push_2(&(*_Le_2)._Fbase, _Mglc_Eexpr_type_Cgvar);
(*_Le_2)._Fat = _Lat_0;
(*_Le_2)._Fname = _Lname_1;
return _Le_idx_3;
}
_Mglc_Eexpr _Mglc_Pexpr_fvar_2(_Mglc_Eexpr _Lexpr_0, _Mglc_Eid _Lmember_1) {
struct _Mglc_Sexpr_fvar* _Le_2;
_Mglc_Eexpr _Le_idx_3;
_Mglc_Pquick_alloc_one_1(_Le_2);
_Le_idx_3 = _Mglc_Pexpr_push_2(&(*_Le_2)._Fbase, _Mglc_Eexpr_type_Cfvar);
(*_Le_2)._Fexpr = _Lexpr_0;
(*_Le_2)._Fmember = _Lmember_1;
return _Le_idx_3;
}
_Mglc_Eexpr _Mglc_Pexpr_assign_3(_Mglc_Eexpr _Lleft_0, _Mglc_Eexpr _Lright_1, _Mglc_Eassign _Ltype_2) {
struct _Mglc_Sexpr_assign* _Le_3;
_Mglc_Eexpr _Le_idx_4;
_Mglc_Pquick_alloc_one_1(_Le_3);
_Le_idx_4 = _Mglc_Pexpr_push_2(&(*_Le_3)._Fbase, _Mglc_Eexpr_type_Cassign);
(*_Le_3)._Fleft = _Lleft_0;
(*_Le_3)._Fright = _Lright_1;
(*_Le_3)._Ftype = _Ltype_2;
return _Le_idx_4;
}
_Mglc_Eexpr _Mglc_Pexpr_math_3(_Mglc_Eexpr _Lleft_0, _Mglc_Eexpr _Lright_1, _Mglc_Emath _Ltype_2) {
struct _Mglc_Sexpr_math* _Le_3;
_Mglc_Eexpr _Le_idx_4;
_Mglc_Pquick_alloc_one_1(_Le_3);
_Le_idx_4 = _Mglc_Pexpr_push_2(&(*_Le_3)._Fbase, _Mglc_Eexpr_type_Cmath);
(*_Le_3)._Fleft = _Lleft_0;
(*_Le_3)._Fright = _Lright_1;
(*_Le_3)._Ftype = _Ltype_2;
return _Le_idx_4;
}
_Mglc_Eexpr _Mglc_Pexpr_math_add_2(_Mglc_Eexpr _Lexpr_0, _Mglc_Eexpr _Lright_1) {
struct _Mglc_Sexpr_math* _Le_2;
uint8_t _Li_3;
struct _Mglc_Sexpr_math_item* _Litem_5;
_Le_2 = _Mglc_Eexpr_Pptr_1(_Lexpr_0);
_Li_3 = (*_Le_2)._Fitem_c++;
if((*_Le_2)._Fitem_cap <= (*_Le_2)._Fitem_c) {
uint8_t _Lold_cap_4;
_Lold_cap_4 = (*_Le_2)._Fitem_cap;
_Mglc_Pgrow_2((*_Le_2)._Fitem_cap, (*_Le_2)._Fitem_c);
_Mglc_Prealloc_3((*_Le_2)._Fitem_v, (*_Le_2)._Fitem_cap, _Lold_cap_4);
}
_Litem_5 = (&(*_Le_2)._Fitem_v[_Li_3]);
(*_Litem_5)._Fexpr = _Lright_1;
return _Lexpr_0;
}
_Mglc_Eexpr _Mglc_Pexpr_bools_3(_Mglc_Eexpr _Lleft_0, _Mglc_Eexpr _Lright_1, _Mglc_Ebools _Ltype_2) {
struct _Mglc_Sexpr_bools* _Le_3;
_Mglc_Eexpr _Le_idx_4;
_Mglc_Pquick_alloc_one_1(_Le_3);
_Le_idx_4 = _Mglc_Pexpr_push_2(&(*_Le_3)._Fbase, _Mglc_Eexpr_type_Cbools);
(*_Le_3)._Fleft = _Lleft_0;
(*_Le_3)._Fright = _Lright_1;
(*_Le_3)._Ftype = _Ltype_2;
return _Le_idx_4;
}
_Mglc_Eexpr _Mglc_Pexpr_bools_add_2(_Mglc_Eexpr _Lbools_0, _Mglc_Eexpr _Lright_1) {
struct _Mglc_Sexpr_bools* _Le_2;
uint8_t _Li_3;
_Le_2 = _Mglc_Eexpr_Pptr_1(_Lbools_0);
_Li_3 = (*_Le_2)._Fitem_c++;
if((*_Le_2)._Fitem_cap <= (*_Le_2)._Fitem_c) {
uint8_t _Lold_cap_4;
_Lold_cap_4 = (*_Le_2)._Fitem_cap;
_Mglc_Pgrow_2((*_Le_2)._Fitem_cap, (*_Le_2)._Fitem_c);
_Mglc_Prealloc_3((*_Le_2)._Fitem_v, (*_Le_2)._Fitem_cap, _Lold_cap_4);
}
(*_Le_2)._Fitem_v[_Li_3]._Fexpr = _Lright_1;
return _Lbools_0;
}
char* _Mglc_Ptoken_name_1(_Mglc_Etoken _Ltok_0) {
return _Mglc_Etoken_Pglc_name_1(_Ltok_0);
}
void _Mglc_Pdecl_var_type_1(_Mglc_Eat _Ltype_0) {
if(_Ltype_0 != _Mglc_Eat_Cnil) {
struct _Mglc_Sat* _Lat_1;
_Lat_1 = _Mglc_Eat_Pptr_1(_Ltype_0);
if((*_Lat_1)._Ftype == _Mglc_Ename_type_Cmodule) {
fprintf(stdout, "%u:%u: module '%%%s' cannot be used as a type\n", _Glast_row, _Glast_col, _Mglc_Eid_Pstr_1((*_Lat_1)._Fname._Fid));
exit(_Mstdc_Eexit_Cfailure);
}
}
_Gdecl_var._Ftype = _Ltype_0;
_Gdecl_var._Fsize_c = 0;
_Mglc_Stype_info_Pinit_1(&_Gdecl_var._Ftype_info);
_Gdecl_var._Fflags = _Mglc_Evar_flags_C0;
}
void _Mglc_Pdecl_var_this_0() {
_Mglc_Eat _Ltype_0;
struct _Mglc_Sat* _Lat_1;
_Ltype_0 = _Gdecl_at;
_Lat_1 = _Mglc_Eat_Pptr_1(_Ltype_0);
if((*_Lat_1)._Ftype == _Mglc_Ename_type_Cmodule) {
fprintf(stdout, "%u:%u: module '%%%s' cannot be used as a type\n", _Glast_row, _Glast_col, _Mglc_Eid_Pstr_1((*_Lat_1)._Fname._Fid));
exit(_Mstdc_Eexit_Cfailure);
}
_Gdecl_var._Ftype = _Ltype_0;
}
void _Mglc_Pstmt_lvar_add_4(_Mglc_Eid _Lname_0, _Mglc_Eexpr _Lset_1, int32_t _Lrow_2, int32_t _Lcol_3) {
_Mglc_Elvar _Llvar_i_4;
struct _Mglc_Slvar* _Llvar_5;
_Llvar_i_4 = _Mglc_Sstmt_space_Plvar_new_4(_Gdecl_func_ctx_space, _Lname_0, _Lrow_2, _Lcol_3);
_Llvar_5 = _Mglc_Elvar_Pptr_1(_Llvar_i_4);
_Gdecl_var._Fname = _Lname_0;
_Mglc_Sdecl_var_Pcopy_from_2(&(*_Llvar_5)._Fdecl, &_Gdecl_var);
if(_Lset_1 != _Mglc_Eexpr_Cnil) {
_Mglc_Eexpr _Le_6;
_Le_6 = _Mglc_Pexpr_assign_3(_Mglc_Pexpr_lvar_4(_Lname_0, 0, _Lrow_2, _Lcol_3), _Lset_1, _Mglc_Eassign_Ceq);
_Mglc_Pexpr2stmt_5(_Le_6, _Lrow_2, _Lcol_3, _Lrow_2, _Lcol_3);
}
}
void _Mglc_Pstmt_lvar_end_2(int32_t _Lend_row_0, int32_t _Lend_col_1) {
}
void _Mglc_Pdecl_include_begin_3(_Mglc_Einclude _Linc_0, int32_t _Lrow_1, int32_t _Lcol_2) {
if(_Gdecl_include != _Mglc_Einclude_Cnil) {
fprintf(stdout, "%s:%u:%u: Cannot {include inside another {include of %u:%u\n", input_path, _Lrow_1, _Lcol_2, _Gdecl_include_row, _Gdecl_include_col);
exit(_Mstdc_Eexit_Cfailure);
return;
}
_Gdecl_include = _Linc_0;
_Gdecl_include_row = _Lrow_1;
_Gdecl_include_col = _Lcol_2;
}
void _Mglc_Pdecl_include_end_0() {
_Gdecl_include = _Mglc_Einclude_Cnil;
}
void _Mglc_Pdecl_at_basic_1(_Mglc_Ebasic_type_id _Ltype_0) {
_Gbuild_at = _Mglc_Pat_create_basic_1(_Ltype_0);
}
void _Mglc_Pdecl_at_add_2(_Mglc_Eid _Lname_0, _Mglc_Ename_type _Ltype_1) {
_Gbuild_at = _Mglc_Pat_create_3(_Gbuild_at, _Ltype_1, _Lname_0);
}
void _Mglc_Pdecl_at_begin_2(int32_t _Lrow_0, int32_t _Lcol_1) {
_Gdecl_at_v[_Gdecl_at_c++] = _Gdecl_at;
_Gdecl_at = _Gbuild_at;
}
void _Mglc_Pdecl_at_begin_struct_3(_Mglc_Eid _Lname_0, int32_t _Lrow_1, int32_t _Lcol_2) {
_Gdecl_struct_row = _Lrow_1;
_Gdecl_struct_col = _Lcol_2;
_Gbuild_at = _Gdecl_at;
_Mglc_Pdecl_at_add_2(_Lname_0, _Mglc_Ename_type_Cstruct);
_Gdecl_at_v[_Gdecl_at_c++] = _Gdecl_at;
_Gdecl_at = _Gbuild_at;
_Gdecl_struct_at = _Gbuild_at;
_Gdecl_fvar_c = 0;
_Gdecl_struct_real_name = _Mglc_Eid_Cnil;
_Gdecl_struct_flags = _Mglc_Estruct_flags_C0;
}
void _Mglc_Pdecl_at_end_0() {
_Gdecl_at_c--;
_Gdecl_at = _Gdecl_at_v[_Gdecl_at_c];
}
void _Mglc_Pdecl_alias_4(_Mglc_Eid _Lname_0, _Mglc_Eat _Lat_1, int32_t _Lrow_2, int32_t _Lcol_3) {
_Mglc_Ealias _Lalias_idx_5;
if((*_Mglc_Eat_Pptr_1(_Lat_1))._Ftype != _Mglc_Ename_type_Cmodule) {
fprintf(stdout, "%s:%u:%u: Alias can only work on namespaces that ends with '%%'\n", input_path, _Lrow_2, _Lcol_3);
exit(_Mstdc_Eexit_Cfailure);
return;
}
int32_t _Li_4;
_Li_4 = 0;
for(int i = _Gat_alias_c; i > 0; ) {
i --;
if(_Gat_alias_name_v[_Li_4] == _Lname_0) {
fprintf(stdout, "%s:%u:%u: Alias '%s was already declared at %u:%u\n", input_path, _Lrow_2, _Lcol_3, _Mglc_Eid_Pstr_1(_Lname_0), _Gat_alias_pos_v[_Li_4]._Frow, _Gat_alias_pos_v[_Li_4]._Fcol);
exit(_Mstdc_Eexit_Cfailure);
return;
}
continue_0:;
_Li_4++;
}
break_0:;
_Lalias_idx_5 = _Gat_alias_c++;
if(_Gat_alias_cap <= _Gat_alias_c) {
_Mglc_Ealias _Lold_cap_6;
_Lold_cap_6 = _Gat_alias_cap;
_Mglc_Pgrow_2(_Gat_alias_cap, _Gat_alias_c);
_Mglc_Prealloc_3(_Gat_alias_name_v, _Gat_alias_cap, _Lold_cap_6);
_Mglc_Prealloc_3(_Gat_alias_at_v, _Gat_alias_cap, _Lold_cap_6);
_Mglc_Prealloc_3(_Gat_alias_pos_v, _Gat_alias_cap, _Lold_cap_6);
}
_Gat_alias_name_v[_Lalias_idx_5] = _Lname_0;
_Gat_alias_at_v[_Lalias_idx_5] = _Lat_1;
_Gat_alias_pos_v[_Lalias_idx_5]._Frow = _Lrow_2;
_Gat_alias_pos_v[_Lalias_idx_5]._Fcol = _Lcol_3;
}
void _Mglc_Pat_push_4(_Mglc_Eid _Lname_0, _Mglc_Ename_type _Ltype_1, int32_t _Lrow_2, int32_t _Lcol_3) {
_Gbuild_at = _Mglc_Pat_create_3(_Gbuild_at, _Ltype_1, _Lname_0);
}
_Mglc_Eat _Mglc_Pat_done_0() {
return _Gbuild_at;
}
void _Mglc_Pat_begin_0() {
_Gbuild_at = _Gdecl_at;
}
void _Mglc_Pat_root_0() {
_Gbuild_at = _Mglc_Eat_Croot;
}
void _Mglc_Pat_alias_3(_Mglc_Eid _Lname_0, int32_t _Lrow_1, int32_t _Lcol_2) {
int32_t _Li_3;
_Li_3 = 0;
for(int i = _Gat_alias_c; i > 0; ) {
i --;
if(_Gat_alias_name_v[_Li_3] == _Lname_0) {
_Gbuild_at = _Gat_alias_at_v[_Li_3];
return;
}
continue_0:;
_Li_3++;
}
break_0:;
fprintf(stdout, "%s:%u:%u: Cannot recognize the alias '%s\n", input_path, _Lrow_1, _Lcol_2, _Mglc_Eid_Pstr_1(_Lname_0));
exit(_Mstdc_Eexit_Cfailure);
}
void _Mglc_Pat_graves_3(int8_t _Lgraves_0, int32_t _Lrow_1, int32_t _Lcol_2) {
_Gbuild_at = _Gdecl_at;
while(_Lgraves_0 > 0) {
struct _Mglc_Sat* _Lat_3;
_Lgraves_0--;
if(_Gbuild_at == _Mglc_Eat_Croot) {
fprintf(stdout, "%s:%u:%u: Too many graves in the namespace, going beyond the root namespace\n", input_path, _Lrow_1, _Lcol_2);
exit(_Mstdc_Eexit_Cfailure);
}
_Lat_3 = _Mglc_Eat_Pptr_1(_Gbuild_at);
_Gbuild_at = (*_Lat_3)._Fparent;
continue_0:;
}
break_0:;
}
_Mglc_Eat _Mglc_Pat_basic_type_1(_Mglc_Ebasic_type_id _Ltype_0) {
_Mglc_Eat _Lbuild_idx_3;
struct _Mglc_Sat* _Lat_5;
_Mglc_Eat _Li_1;
_Li_1 = (_Mglc_Eat)(0);
for(int i = _Gat_c; i > 0; ) {
i --;
struct _Mglc_Sat* _Lat_2;
_Lat_2 = (&_Gat_v[_Li_1]);
if((((*_Lat_2)._Ftype == _Mglc_Ename_type_Cbasic) && ((*_Lat_2)._Fname._Fbasic == _Ltype_0))) {
return _Li_1;
}
continue_0:;
_Li_1++;
}
break_0:;
_Lbuild_idx_3 = _Gat_c++;
if(_Gat_cap <= _Gat_c) {
_Mglc_Eat _Lold_cap_4;
_Lold_cap_4 = _Gat_cap;
_Mglc_Pgrow_2(_Gat_cap, _Gat_c);
_Mglc_Prealloc_3(_Gat_v, _Gat_cap, _Lold_cap_4);
}
_Lat_5 = (&_Gat_v[_Lbuild_idx_3]);
(*_Lat_5)._Fparent = _Mglc_Eat_Croot;
(*_Lat_5)._Ftype = _Mglc_Ename_type_Cbasic;
(*_Lat_5)._Fname._Fbasic = _Ltype_0;
return _Lbuild_idx_3;
}
void _Mglc_Pdecl_var_as_gvar_0() {
_Mglc_Egvar _Lgvar_idx_0;
struct _Mglc_Sdecl_gvar* _Lgvar_2;
_Lgvar_idx_0 = _Ggvar_c++;
if(_Ggvar_cap <= _Ggvar_c) {
_Mglc_Egvar _Lold_cap_1;
_Lold_cap_1 = _Ggvar_cap;
_Mglc_Pgrow_2(_Ggvar_cap, _Ggvar_c);
_Mglc_Prealloc_3(_Ggvar_v, _Ggvar_cap, _Lold_cap_1);
}
_Lgvar_2 = (&_Ggvar_v[_Lgvar_idx_0]);
(*_Lgvar_2)._Finclude = _Gdecl_include;
(*_Lgvar_2)._Fat = _Gdecl_at;
_Mglc_Sdecl_var_Pcopy_from_2(&(*_Lgvar_2)._Fdecl, &_Gdecl_var);
}
void _Mglc_Ptype_info_arr_2(_Mglc_Eexpr* _Lexpr_v_0, uint8_t _Lexpr_c_1) {
union _Mglc_Srdr _Lr_2;
_Lr_2._Fref = _Lexpr_v_0;
if(_Lexpr_v_0 == NULL) {
struct _Mglc_Stype_info* _Lti_3;
_Lti_3 = (&_Gdecl_var._Ftype_info);
(*_Lti_3)._Farray_c += 1;
(*_Lti_3)._Fref_v[(*_Lti_3)._Farray_c] = 0;
return;
}
uint8_t _Li_4;
_Li_4 = _Lexpr_c_1;
for(int i = _Lexpr_c_1; i > 0; ) {
i --;
_Mglc_Ptype_info_arr_1(_Lexpr_v_0[(_Li_4 -= 1)]);
continue_0:;
}
break_0:;
}
void _Mglc_Ptype_info_ref_1(int8_t _Lc_0) {
struct _Mglc_Stype_info* _Lti_1;
_Lti_1 = (&_Gdecl_var._Ftype_info);
(*_Lti_1)._Fref_v[(*_Lti_1)._Farray_c] += _Lc_0;
}
void _Mglc_Ptype_info_static_0() {
_Gdecl_var._Ftype_info._Fbuilt_in = true;
}
void _Mglc_Ptype_info_begin_0() {
_Gdecl_var._Fsize_c = 0;
_Mglc_Stype_info_Pinit_1(&_Gdecl_var._Ftype_info);
_Gdecl_var._Fflags = _Mglc_Evar_flags_C0;
}
void _Mglc_Ptype_info_finalize_0() {
_Mglc_Stype_info_Pfinalize_1(&_Gdecl_var._Ftype_info);
}
_Mglc_Eexpr _Mglc_Pexpr_int_2(int32_t _Lvalue_0, _Mglc_Eexpr_int _Ltype_1) {
struct _Mglc_Sexpr_int* _Le_2;
_Mglc_Eexpr _Le_idx_3;
_Mglc_Pquick_alloc_one_1(_Le_2);
_Le_idx_3 = _Mglc_Pexpr_push_2(&(*_Le_2)._Fbase, _Mglc_Eexpr_type_Cint);
(*_Le_2)._Fvalue = _Lvalue_0;
(*_Le_2)._Ftype = _Ltype_1;
return _Le_idx_3;
}
_Mglc_Eexpr _Mglc_Pexpr_size_of_type_1(_Mglc_Eat _Lat_0) {
struct _Mglc_Sexpr_size_of_type* _Le_1;
_Mglc_Eexpr _Le_idx_2;
_Mglc_Pquick_alloc_one_1(_Le_1);
_Le_idx_2 = _Mglc_Pexpr_push_2(&(*_Le_1)._Fbase, _Mglc_Eexpr_type_Csize_of_type);
(*_Le_1)._Ftype = _Lat_0;
return _Le_idx_2;
}
_Mglc_Eexpr _Mglc_Pexpr_null_0() {
struct _Mglc_Sexpr_null* _Le_0;
_Mglc_Eexpr _Le_idx_1;
_Mglc_Pquick_alloc_one_1(_Le_0);
_Le_idx_1 = _Mglc_Pexpr_push_2(&(*_Le_0)._Fbase, _Mglc_Eexpr_type_Cnull);
return _Le_idx_1;
}
void _Mglc_Pdecl_at_begin_enum_3(_Mglc_Eid _Lname_0, int32_t _Lrow_1, int32_t _Lcol_2) {
_Gdecl_enum_row = _Lrow_1;
_Gdecl_enum_col = _Lcol_2;
_Gbuild_at = _Gdecl_at;
_Mglc_Pdecl_at_add_2(_Lname_0, _Mglc_Ename_type_Cenum);
_Gdecl_at_v[_Gdecl_at_c++] = _Gdecl_at;
_Gdecl_at = _Gbuild_at;
_Gdecl_enum_at = _Gbuild_at;
_Gdecl_enum_flags = _Mglc_Eenum_flags_C0;
_Gdecl_enum_last_cvar = _Mglc_Ecvar_Cnil;
}
void _Mglc_Pdecl_enum_end_3(_Mglc_Eat _Lbase_type_0, int32_t _Lrow_1, int32_t _Lcol_2) {
_Mglc_Eenum _Ls_idx_3;
struct _Mglc_Senum* _Ls_5;
_Ls_idx_3 = _Genum_c++;
if(_Genum_cap <= _Genum_c) {
_Mglc_Eenum _Lold_cap_4;
_Lold_cap_4 = _Genum_cap;
_Mglc_Pgrow_2(_Genum_cap, _Genum_c);
_Mglc_Prealloc_3(_Genum_v, _Genum_cap, _Lold_cap_4);
}
_Mglc_Pquick_alloc_one_1(_Ls_5);
_Genum_v[_Ls_idx_3] = _Ls_5;
(*_Ls_5)._Fbegin_row = _Gdecl_enum_row;
(*_Ls_5)._Fbegin_col = _Gdecl_enum_col;
(*_Ls_5)._Fend_row = _Lrow_1;
(*_Ls_5)._Fend_col = _Lcol_2;
(*_Ls_5)._Finclude = _Gdecl_include;
(*_Ls_5)._Fat = _Gdecl_enum_at;
(*_Ls_5)._Fbase_type = _Lbase_type_0;
_Gdecl_at = _Gdecl_enum_at;
(*_Ls_5)._Fflags = _Gdecl_enum_flags;
_Gdecl_enum_last_cvar = _Mglc_Ecvar_Cnil;
}
_Mglc_Eexpr _Mglc_Pexpr_cvar_2(_Mglc_Eat _Lat_0, _Mglc_Eid _Lname_1) {
struct _Mglc_Sexpr_cvar* _Le_2;
_Mglc_Eexpr _Le_idx_3;
_Mglc_Pquick_alloc_one_1(_Le_2);
_Le_idx_3 = _Mglc_Pexpr_push_2(&(*_Le_2)._Fbase, _Mglc_Eexpr_type_Ccvar);
(*_Le_2)._Fat = _Lat_0;
(*_Le_2)._Fname = _Lname_1;
return _Le_idx_3;
}
void _Mglc_Penum_add_cvar_3(_Mglc_Eid _Lname_0, int32_t _Lrow_1, int32_t _Lcol_2) {
_Mglc_Ecvar _Lc_idx_3;
struct _Mglc_Scvar* _Lc_5;
_Lc_idx_3 = _Gcvar_c++;
_Glast_cvar = _Lc_idx_3;
if(_Gcvar_cap <= _Gcvar_c) {
_Mglc_Ecvar _Lold_cap_4;
_Lold_cap_4 = _Gcvar_cap;
_Mglc_Pgrow_2(_Gcvar_cap, _Gcvar_c);
_Mglc_Prealloc_3(_Gcvar_v, _Gcvar_cap, _Lold_cap_4);
}
_Lc_5 = _Mglc_Ecvar_Pptr_1(_Lc_idx_3);
(*_Lc_5)._Frow = _Lrow_1;
(*_Lc_5)._Fcol = _Lcol_2;
(*_Lc_5)._Finclude = _Gdecl_include;
(*_Lc_5)._Fat = _Gdecl_at;
(*_Lc_5)._Fdecl._Fname = _Lname_0;
(*_Lc_5)._Fdecl._Ftype = _Gdecl_enum_at;
_Mglc_Stype_info_Pinit_1(&(*_Lc_5)._Fdecl._Ftype_info);
(*_Lc_5)._Fflags = _Mglc_Ecvar_flags_Cas_enum;
(*_Lc_5)._Flast_cvar = _Gdecl_enum_last_cvar;
_Gdecl_enum_last_cvar = _Lc_idx_3;
}
void _Mglc_Pdecl_add_cvar_3(_Mglc_Eid _Lname_0, int32_t _Lrow_1, int32_t _Lcol_2) {
_Mglc_Ecvar _Lc_idx_3;
struct _Mglc_Scvar* _Lc_5;
_Lc_idx_3 = _Gcvar_c++;
_Glast_cvar = _Lc_idx_3;
if(_Gcvar_cap <= _Gcvar_c) {
_Mglc_Ecvar _Lold_cap_4;
_Lold_cap_4 = _Gcvar_cap;
_Mglc_Pgrow_2(_Gcvar_cap, _Gcvar_c);
_Mglc_Prealloc_3(_Gcvar_v, _Gcvar_cap, _Lold_cap_4);
}
_Lc_5 = _Mglc_Ecvar_Pptr_1(_Lc_idx_3);
(*_Lc_5)._Frow = _Lrow_1;
(*_Lc_5)._Fcol = _Lcol_2;
(*_Lc_5)._Finclude = _Gdecl_include;
(*_Lc_5)._Fat = _Gdecl_at;
_Gdecl_var._Fname = _Lname_0;
_Mglc_Sdecl_var_Pcopy_from_2(&(*_Lc_5)._Fdecl, &_Gdecl_var);
(*_Lc_5)._Fflags = _Mglc_Ecvar_flags_C0;
}
void _Mglc_Penum_set_cvar_expr_1(_Mglc_Eexpr _Lset_0) {
struct _Mglc_Scvar* _Lc_1;
_Lc_1 = _Mglc_Ecvar_Pptr_1(_Glast_cvar);
(*_Lc_1)._Fflags |= _Mglc_Ecvar_flags_Cset_expr;
(*_Lc_1)._Fexpr_set = _Lset_0;
}
void _Mglc_Pstruct_attr_real_name_1(_Mglc_Eid _Lname_0) {
if((_Gdecl_struct_flags & _Mglc_Estruct_flags_Creal_name) != _Mglc_Estruct_flags_C0) {
fprintf(stdout, "%u:%u: error @real-name specified more than once\n", _Glast_row, _Glast_col);
exit(_Mstdc_Eexit_Cfailure);
}
_Gdecl_struct_flags |= _Mglc_Estruct_flags_Creal_name;
_Gdecl_struct_real_name = _Lname_0;
}
void _Mglc_Pstruct_attr_union_0() {
if((_Gdecl_struct_flags & _Mglc_Estruct_flags_Cunion) != _Mglc_Estruct_flags_C0) {
fprintf(stdout, "%u:%u: error @union specified more than once\n", _Glast_row, _Glast_col);
exit(_Mstdc_Eexit_Cfailure);
}
_Gdecl_struct_flags |= _Mglc_Estruct_flags_Cunion;
}
void _Mglc_Pstruct_attr_no_decl_0() {
if((_Gdecl_struct_flags & _Mglc_Estruct_flags_Cno_decl) != _Mglc_Estruct_flags_C0) {
fprintf(stdout, "%u:%u: error @no-decl specified more than once\n", _Glast_row, _Glast_col);
exit(_Mstdc_Eexit_Cfailure);
}
_Gdecl_struct_flags |= _Mglc_Estruct_flags_Cno_decl;
}
_Mglc_Eexpr _Mglc_Pexpr_str_1(_Mglc_Eexpr _Lprev_0) {
int32_t _Llen_1;
struct _Mglc_Sexpr_str_node* _Ln_2;
_Llen_1 = _Gstring_len;
_Mglc_Pquick_alloc_plus_2(_Ln_2, _Llen_1 + 1);
(*_Ln_2)._Flen = _Llen_1;
memcpy((*_Ln_2)._Fbuf, _Gstring_buf, _Llen_1);
(*_Ln_2)._Fbuf[_Llen_1] = '\0';
(*_Ln_2)._Fnext = NULL;
if(_Lprev_0 == _Mglc_Eexpr_Cnil) {
struct _Mglc_Sexpr_str* _Le_3;
_Mglc_Eexpr _Le_idx_4;
_Mglc_Pquick_alloc_one_1(_Le_3);
_Le_idx_4 = _Mglc_Pexpr_push_2(&(*_Le_3)._Fbase, _Mglc_Eexpr_type_Cstr);
(*_Le_3)._Fnode_c = 1;
(*_Le_3)._Ffirst = _Ln_2;
(*_Le_3)._Flast = _Ln_2;
return _Le_idx_4;
} else {
struct _Mglc_Sexpr_str* _Le_5;
_Le_5 = _Mglc_Eexpr_Pptr_1(_Lprev_0);
(*_Le_5)._Fnode_c++;
(*(*_Le_5)._Flast)._Fnext = _Ln_2;
(*_Le_5)._Flast = _Ln_2;
return _Lprev_0;
}
}
_Mglc_Eexpr _Mglc_Pexpr_unary_2(_Mglc_Eexpr _Lexpr_0, _Mglc_Eunary _Ltype_1) {
struct _Mglc_Sexpr_unary* _Le_2;
_Mglc_Eexpr _Le_idx_3;
_Mglc_Pquick_alloc_one_1(_Le_2);
_Le_idx_3 = _Mglc_Pexpr_push_2(&(*_Le_2)._Fbase, _Mglc_Eexpr_type_Cunary);
(*_Le_2)._Fexpr = _Lexpr_0;
(*_Le_2)._Ftype = _Ltype_1;
return _Le_idx_3;
}
_Mglc_Eexpr _Mglc_Pexpr_ref_1(_Mglc_Eexpr _Lexpr_0) {
struct _Mglc_Sexpr_ref* _Le_1;
_Mglc_Eexpr _Le_idx_2;
_Mglc_Pquick_alloc_one_1(_Le_1);
_Le_idx_2 = _Mglc_Pexpr_push_2(&(*_Le_1)._Fbase, _Mglc_Eexpr_type_Cref);
(*_Le_1)._Fexpr = _Lexpr_0;
return _Le_idx_2;
}
_Mglc_Eexpr _Mglc_Pexpr_cast_fast_2(_Mglc_Eexpr _Lexpr_0, _Mglc_Eat _Ltype_1) {
struct _Mglc_Sexpr_cast_fast* _Le_2;
_Mglc_Eexpr _Le_idx_3;
_Mglc_Pquick_alloc_one_1(_Le_2);
_Le_idx_3 = _Mglc_Pexpr_push_2(&(*_Le_2)._Fbase, _Mglc_Eexpr_type_Ccast_fast);
(*_Le_2)._Fexpr = _Lexpr_0;
(*_Le_2)._Ftype = _Ltype_1;
return _Le_idx_3;
}
_Mglc_Eexpr _Mglc_Pexpr_index_3(_Mglc_Eexpr _Lleft_0, _Mglc_Eexpr* _Lright_v_1, int32_t _Lright_c_2) {
_Mglc_Eexpr _Le_idx_5;
int32_t _Li_3;
_Li_3 = _Lright_c_2;
for(int i = _Lright_c_2; i > 0; ) {
i --;
struct _Mglc_Sexpr_index* _Le_4;
_Mglc_Pquick_alloc_one_1(_Le_4);
_Le_idx_5 = _Mglc_Pexpr_push_2(&(*_Le_4)._Fbase, _Mglc_Eexpr_type_Cindex);
(*_Le_4)._Fleft = _Lleft_0;
(*_Le_4)._Fright = _Lright_v_1[(_Li_3 -= 1)];
continue_0:;
}
break_0:;
return _Le_idx_5;
}
void _Mglc_Penum_base_begin_0() {
_Gdecl_at = (*_Mglc_Eat_Pptr_1(_Gdecl_at))._Fparent;
}
void _Mglc_Pstmt_switch_begin_0() {
_Mglc_Pstmt_space_begin_0();
(*_Gdecl_func_ctx_space)._Fflags |= _Mglc_Estmt_space_flags_Cskip_lvar_decl;
}
void _Mglc_Pstmt_switch_set_6(_Mglc_Eexpr _Lexpr_0, int32_t _Lbegin_row_1, int32_t _Lbegin_col_2, int32_t _Lend_row_3, int32_t _Lend_col_4, _Mglc_Eexpr _Lcases_5) {
struct _Mglc_Sstmt_switch* _Ls_6;
_Mglc_Pquick_alloc_one_1(_Ls_6);
(*_Ls_6)._Fexpr = _Lexpr_0;
(*_Ls_6)._Fcases = _Lcases_5;
_Mglc_Pstmt_push_6(&(*_Ls_6)._Fbase, _Lbegin_row_1, _Lbegin_col_2, _Lend_row_3, _Lend_col_4, _Mglc_Estmt_type_Cswitch);
_Gswitch_expr_c = 0;
}
void _Mglc_Pstmt_switch_expr_add_1(_Mglc_Eexpr _Lexpr_0) {
uint32_t _Lexpr_i_1;
_Lexpr_i_1 = _Gswitch_expr_c++;
if(_Gswitch_expr_cap <= _Gswitch_expr_c) {
uint32_t _Lold_cap_2;
_Lold_cap_2 = _Gswitch_expr_cap;
_Mglc_Pgrow_2(_Gswitch_expr_cap, _Gswitch_expr_c);
_Mglc_Prealloc_3(_Gswitch_expr_v, _Gswitch_expr_cap, _Lold_cap_2);
}
_Gswitch_expr_v[_Lexpr_i_1] = _Lexpr_0;
}
void _Mglc_Pstmt_switch_case_begin_5(int32_t _Lbegin_row_0, int32_t _Lbegin_col_1, int32_t _Lend_row_2, int32_t _Lend_col_3, bool _Lfall_through_4) {
uint32_t _Lexpr_c_5;
struct _Mglc_Sstmt_case* _Ls_6;
_Lexpr_c_5 = _Gswitch_expr_c;
_Gswitch_expr_c = 0;
_Mglc_Pquick_alloc_plus_2(_Ls_6, sizeof(struct _Mglc_Sstmt_case_item) * _Lexpr_c_5);
(*_Ls_6)._Ffall_through = _Lfall_through_4;
(*_Ls_6)._Fexpr_c = _Lexpr_c_5;
int32_t _Li_7;
_Li_7 = 0;
for(int i = _Lexpr_c_5; i > 0; ) {
i --;
(*_Ls_6)._Fexpr_v[_Li_7]._Fexpr = _Gswitch_expr_v[_Li_7];
continue_0:;
_Li_7++;
}
break_0:;
_Mglc_Pstmt_push_6(&(*_Ls_6)._Fbase, _Lbegin_row_0, _Lbegin_col_1, _Lend_row_2, _Lend_col_3, _Mglc_Estmt_type_Ccase);
_Mglc_Pstmt_space_begin_0();
}
void _Mglc_Pstmt_switch_case_end_0() {
struct _Mglc_Sstmt_case_end* _Ls_0;
_Mglc_Pstmt_space_end_0();
_Mglc_Pquick_alloc_one_1(_Ls_0);
_Mglc_Pstmt_push_6(&(*_Ls_0)._Fbase, 0, 0, 0, 0, _Mglc_Estmt_type_Ccase_end);
}
void _Mglc_Pstmt_switch_default_begin_5(int32_t _Lbegin_row_0, int32_t _Lbegin_col_1, int32_t _Lend_row_2, int32_t _Lend_col_3, bool _Lfall_through_4) {
struct _Mglc_Sstmt_default* _Ls_5;
_Mglc_Pquick_alloc_one_1(_Ls_5);
(*_Ls_5)._Ffall_through = _Lfall_through_4;
_Mglc_Pstmt_push_6(&(*_Ls_5)._Fbase, _Lbegin_row_0, _Lbegin_col_1, _Lend_row_2, _Lend_col_3, _Mglc_Estmt_type_Cdefault);
_Mglc_Pstmt_space_begin_0();
}
void _Mglc_Pstmt_switch_default_end_0() {
struct _Mglc_Sstmt_default_end* _Ls_0;
_Mglc_Pstmt_space_end_0();
_Mglc_Pquick_alloc_one_1(_Ls_0);
_Mglc_Pstmt_push_6(&(*_Ls_0)._Fbase, 0, 0, 0, 0, _Mglc_Estmt_type_Cdefault_end);
}
void _Mglc_Pstmt_switch_end_0() {
struct _Mglc_Sstmt_switch_end* _Ls_0;
_Mglc_Pquick_alloc_one_1(_Ls_0);
_Mglc_Pstmt_push_6(&(*_Ls_0)._Fbase, 0, 0, 0, 0, _Mglc_Estmt_type_Cswitch_end);
_Mglc_Pstmt_space_end_0();
}
void _Mglc_Pstmt_if_begin_0() {
_Mglc_Pstmt_space_begin_0();
(*_Gdecl_func_ctx_space)._Fflags |= _Mglc_Estmt_space_flags_Cskip_lvar_decl;
}
void _Mglc_Pstmt_if_set_6(bool _Lnot_0, _Mglc_Eexpr _Lexpr_1, int32_t _Lbegin_row_2, int32_t _Lbegin_col_3, int32_t _Lend_row_4, int32_t _Lend_col_5) {
struct _Mglc_Sstmt_if* _Ls_6;
_Mglc_Pquick_alloc_one_1(_Ls_6);
(*_Ls_6)._Fnot = _Lnot_0;
(*_Ls_6)._Fexpr = _Lexpr_1;
_Mglc_Pstmt_push_6(&(*_Ls_6)._Fbase, _Lbegin_row_2, _Lbegin_col_3, _Lend_row_4, _Lend_col_5, _Mglc_Estmt_type_Cif);
_Mglc_Pstmt_space_begin_0();
}
void _Mglc_Pstmt_if_end_0() {
_Mglc_Pstmt_space_end_0();
}
void _Mglc_Pstmt_do_begin_0() {
_Mglc_Pstmt_space_begin_0();
(*_Gdecl_func_ctx_space)._Fflags |= _Mglc_Estmt_space_flags_Cskip_lvar_decl;
}
void _Mglc_Pstmt_do_set_6(_Mglc_Eexpr _Lexpr_0, int32_t _Lbegin_row_1, int32_t _Lbegin_col_2, int32_t _Lend_row_3, int32_t _Lend_col_4, struct _Mglc_Sstmt_space* _Lcontinue_5) {
struct _Mglc_Sstmt_do* _Ls_6;
_Mglc_Pquick_alloc_one_1(_Ls_6);
_Gnest_stack_id_v[_Gnest_stack_c] = _Gnest_id++;
_Gnest_stack_ptr_v[_Gnest_stack_c]._Fdo = _Ls_6;
_Gnest_stack_c++;
(*_Ls_6)._Fexpr = _Lexpr_0;
(*_Ls_6)._Fcontinue = _Lcontinue_5;
_Mglc_Pstmt_push_6(&(*_Ls_6)._Fbase, _Lbegin_row_1, _Lbegin_col_2, _Lend_row_3, _Lend_col_4, _Mglc_Estmt_type_Cdo);
_Mglc_Pstmt_space_begin_0();
}
void _Mglc_Pstmt_do_end_0() {
struct _Mglc_Sstmt_do_end* _Ls_0;
_Gnest_stack_c -= 1;
_Mglc_Pstmt_space_end_0();
_Mglc_Pquick_alloc_one_1(_Ls_0);
_Mglc_Pstmt_push_6(&(*_Ls_0)._Fbase, 0, 0, 0, 0, _Mglc_Estmt_type_Cdo_end);
_Mglc_Pstmt_space_end_0();
}
void _Mglc_Pstmt_while_begin_0() {
_Mglc_Pstmt_space_begin_0();
(*_Gdecl_func_ctx_space)._Fflags |= _Mglc_Estmt_space_flags_Cskip_lvar_decl;
}
void _Mglc_Pstmt_while_set_6(_Mglc_Eexpr _Lexpr_0, int32_t _Lbegin_row_1, int32_t _Lbegin_col_2, int32_t _Lend_row_3, int32_t _Lend_col_4, struct _Mglc_Sstmt_space* _Lcontinue_5) {
struct _Mglc_Sstmt_while* _Ls_6;
_Mglc_Pquick_alloc_one_1(_Ls_6);
_Gnest_stack_id_v[_Gnest_stack_c] = _Gnest_id++;
_Gnest_stack_ptr_v[_Gnest_stack_c]._Fwhile = _Ls_6;
_Gnest_stack_c++;
(*_Ls_6)._Fexpr = _Lexpr_0;
(*_Ls_6)._Fcontinue = _Lcontinue_5;
_Mglc_Pstmt_push_6(&(*_Ls_6)._Fbase, _Lbegin_row_1, _Lbegin_col_2, _Lend_row_3, _Lend_col_4, _Mglc_Estmt_type_Cwhile);
_Mglc_Pstmt_space_begin_0();
}
void _Mglc_Pstmt_while_end_0() {
struct _Mglc_Sstmt_while_end* _Ls_0;
_Gnest_stack_c -= 1;
_Mglc_Pstmt_space_end_0();
_Mglc_Pquick_alloc_one_1(_Ls_0);
_Mglc_Pstmt_push_6(&(*_Ls_0)._Fbase, 0, 0, 0, 0, _Mglc_Estmt_type_Cwhile_end);
_Mglc_Pstmt_space_end_0();
}
void _Mglc_Pstmt_elif_begin_0() {
}
void _Mglc_Pstmt_elif_set_6(bool _Lnot_0, _Mglc_Eexpr _Lexpr_1, int32_t _Lbegin_row_2, int32_t _Lbegin_col_3, int32_t _Lend_row_4, int32_t _Lend_col_5) {
struct _Mglc_Sstmt_if* _Ls_6;
_Mglc_Pquick_alloc_one_1(_Ls_6);
(*_Ls_6)._Fnot = _Lnot_0;
(*_Ls_6)._Fexpr = _Lexpr_1;
_Mglc_Pstmt_push_6(&(*_Ls_6)._Fbase, _Lbegin_row_2, _Lbegin_col_3, _Lend_row_4, _Lend_col_5, _Mglc_Estmt_type_Cif_elif);
_Mglc_Pstmt_space_begin_0();
}
void _Mglc_Pstmt_elif_end_0() {
_Mglc_Pstmt_space_end_0();
}
void _Mglc_Pstmt_else_set_0() {
struct _Mglc_Sstmt_if_else* _Ls_0;
_Mglc_Pquick_alloc_one_1(_Ls_0);
_Mglc_Pstmt_push_6(&(*_Ls_0)._Fbase, 0, 0, 0, 0, _Mglc_Estmt_type_Cif_else);
_Mglc_Pstmt_space_begin_0();
}
void _Mglc_Pstmt_else_end_0() {
_Mglc_Pstmt_space_end_0();
}
void _Mglc_Pstmt_if_end_ifs_0() {
struct _Mglc_Sstmt_if_end* _Ls_0;
_Mglc_Pquick_alloc_one_1(_Ls_0);
_Mglc_Pstmt_push_6(&(*_Ls_0)._Fbase, 0, 0, 0, 0, _Mglc_Estmt_type_Cif_end);
_Mglc_Pstmt_space_end_0();
}
struct _Mglc_Sstmt_space* _Mglc_Pstmt_space_begin_0() {
return _Mglc_Pstmt_space_begin_1(true);
}
struct _Mglc_Sstmt_space* _Mglc_Pstmt_space_begin_detach_0() {
return _Mglc_Pstmt_space_begin_1(false);
}
struct _Mglc_Sstmt_space* _Mglc_Pstmt_space_end_0() {
struct _Mglc_Sstmt_space* _Lret_0;
_Lret_0 = _Gdecl_func_ctx_space;
_Gdecl_func_ctx_space = (*_Gdecl_func_ctx_space)._Fparent;
return _Lret_0;
}
_Mglc_Eexpr _Mglc_Pexpr_compare_3(_Mglc_Eexpr _Lleft_0, _Mglc_Eexpr _Lright_1, _Mglc_Ecompare _Ltype_2) {
struct _Mglc_Sexpr_compare* _Le_3;
_Mglc_Eexpr _Le_idx_4;
_Mglc_Pquick_alloc_one_1(_Le_3);
_Le_idx_4 = _Mglc_Pexpr_push_2(&(*_Le_3)._Fbase, _Mglc_Eexpr_type_Ccompare);
(*_Le_3)._Fleft = _Lleft_0;
(*_Le_3)._Fright = _Lright_1;
(*_Le_3)._Ftype = _Ltype_2;
return _Le_idx_4;
}
_Mglc_Eexpr _Mglc_Pexpr_bool_1(bool _Lvalue_0) {
struct _Mglc_Sexpr_bool* _Le_1;
_Mglc_Eexpr _Le_idx_2;
_Mglc_Pquick_alloc_one_1(_Le_1);
_Le_idx_2 = _Mglc_Pexpr_push_2(&(*_Le_1)._Fbase, _Mglc_Eexpr_type_Cbool);
(*_Le_1)._Fvalue = _Lvalue_0;
return _Le_idx_2;
}
_Mglc_Eexpr _Mglc_Pexpr_char_1(int32_t _Lvalue_0) {
struct _Mglc_Sexpr_char* _Le_1;
_Mglc_Eexpr _Le_idx_2;
_Mglc_Pquick_alloc_one_1(_Le_1);
_Le_idx_2 = _Mglc_Pexpr_push_2(&(*_Le_1)._Fbase, _Mglc_Eexpr_type_Cchar);
(*_Le_1)._Fvalue = _Lvalue_0;
return _Le_idx_2;
}
void _Mglc_Pcvar_attr_real_name_1(_Mglc_Eid _Lname_0) {
struct _Mglc_Scvar* _Lc_1;
_Lc_1 = _Mglc_Ecvar_Pptr_1(_Glast_cvar);
(*_Lc_1)._Fdecl._Fflags |= _Mglc_Evar_flags_Creal_name;
(*_Lc_1)._Fdecl._Freal_name = _Lname_0;
}
void _Mglc_Pcvar_attr_no_decl_0() {
struct _Mglc_Scvar* _Lc_0;
_Lc_0 = _Mglc_Ecvar_Pptr_1(_Glast_cvar);
(*_Lc_0)._Fdecl._Fflags |= _Mglc_Evar_flags_Cno_decl;
}
void _Mglc_Eat_Pput_to_header_1(_Mglc_Eat _Lat_0) {
if((_Gat_in_header_v[(_Lat_0 >> 3)] & (1 << (_Lat_0 & 7))) == 0) {
_Gat_in_header_v[(_Lat_0 >> 3)] |= (1 << (_Lat_0 & 7));
_Gat_in_header_idx_v[_Lat_0] = _Gat_in_header_c;
_Gat_in_header_at_v[_Gat_in_header_c++] = _Lat_0;
if(_Lat_0 != _Mglc_Eat_Croot) {
_Mglc_Eat_Pput_to_header_1((*_Mglc_Eat_Pptr_1(_Lat_0))._Fparent);
}
}
}
void _Mglc_Einclude_Pwr_2(_Mglc_Einclude _Li_0, union _Mglc_Swtr* _Lw_1) {
Fputnum(_Lw_1, _Li_0 + 1);
}
void _Mglc_Sdecl_var_Pwr_3(struct _Mglc_Sdecl_var* _Lvd_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2) {
_Mglc_Eid_Pwr_3((*_Lvd_0)._Fname, _Lw_1, _Lheader_2);
_Mglc_Eat_Pwr_3((*_Lvd_0)._Ftype, _Lw_1, _Lheader_2);
_Mglc_Evar_flags_Pwr_2((*_Lvd_0)._Fflags, _Lw_1);
if(((*_Lvd_0)._Fflags & _Mglc_Evar_flags_Creal_name) != _Mglc_Evar_flags_C0) {
_Mglc_Eid_Pwr_3((*_Lvd_0)._Freal_name, _Lw_1, _Lheader_2);
}
_Mglc_Stype_info_Pwr_2(&(*_Lvd_0)._Ftype_info, _Lw_1);
_Mglc_Swtr_Pn1_2(_Lw_1, (*_Lvd_0)._Fsize_c);
int32_t _Li_3;
_Li_3 = 0;
for(int i = (*_Lvd_0)._Fsize_c; i > 0; ) {
i --;
_Mglc_Eexpr_Pwr_3((*_Lvd_0)._Fsize_expr_v[_Li_3], _Lw_1, _Lheader_2);
continue_0:;
_Li_3++;
}
break_0:;
}
void _Mglc_Ecvar_flags_Pwr_2(_Mglc_Ecvar_flags _Lf_0, union _Mglc_Swtr* _Lw_1) {
_Mglc_Swtr_Pn1_2(_Lw_1, _Lf_0);
}
void _Mglc_Eexpr_Pwr_3(_Mglc_Eexpr _Le_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2) {
if(_Mglc_Cdebug_rd_wr) {
_Mglc_Swtr_Pn1_2(_Lw_1, 255);
}
if(_Le_0 == _Mglc_Eexpr_Cnil) {
_Mglc_Eexpr_type_Pwr_2(_Mglc_Eexpr_type_Cnil, _Lw_1);
} else {
struct _Mglc_Sexpr* _Lexpr_3;
_Lexpr_3 = _Mglc_Eexpr_Pptr_1(_Le_0);
_Mglc_Eexpr_type_Pwr_2((*_Lexpr_3)._Ftype, _Lw_1);
switch((*_Lexpr_3)._Ftype) {
case _Mglc_Eexpr_type_Cmath:;
_Mglc_Eexpr_Pwr_math_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _Mglc_Eexpr_type_Cbools:;
_Mglc_Eexpr_Pwr_bools_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _Mglc_Eexpr_type_Cstr:;
_Mglc_Eexpr_Pwr_str_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _Mglc_Eexpr_type_Ccvar:;
_Mglc_Eexpr_Pwr_cvar_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _Mglc_Eexpr_type_Cunary:;
_Mglc_Eexpr_Pwr_unary_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _Mglc_Eexpr_type_Cref:;
_Mglc_Eexpr_Pwr_ref_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _Mglc_Eexpr_type_Ccast_fast:;
_Mglc_Eexpr_Pwr_cast_fast_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _Mglc_Eexpr_type_Cindex:;
_Mglc_Eexpr_Pwr_index_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _Mglc_Eexpr_type_Ccompare:;
_Mglc_Eexpr_Pwr_compare_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _Mglc_Eexpr_type_Cbool:;
_Mglc_Eexpr_Pwr_bool_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _Mglc_Eexpr_type_Cchar:;
_Mglc_Eexpr_Pwr_char_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _Mglc_Eexpr_type_Cmethod:;
_Mglc_Eexpr_Pwr_method_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _Mglc_Eexpr_type_Cfunc:;
_Mglc_Eexpr_Pwr_func_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _Mglc_Eexpr_type_Cnull:;
_Mglc_Eexpr_Pwr_null_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _Mglc_Eexpr_type_Cint:;
_Mglc_Eexpr_Pwr_int_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _Mglc_Eexpr_type_Csize_of_type:;
_Mglc_Eexpr_Pwr_size_of_type_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _Mglc_Eexpr_type_Cassign:;
_Mglc_Eexpr_Pwr_assign_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _Mglc_Eexpr_type_Cfvar:;
_Mglc_Eexpr_Pwr_fvar_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _Mglc_Eexpr_type_Cgvar:;
_Mglc_Eexpr_Pwr_gvar_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _Mglc_Eexpr_type_Clvar:;
_Mglc_Eexpr_Pwr_lvar_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
default:;
fprintf(stdout, ":wr was not implemented in expression #%s\n", _Mglc_Eexpr_type_Pglc_name_1((*_Lexpr_3)._Ftype));
exit(_Mstdc_Eexit_Cfailure);
break;
}
}
if(_Mglc_Cdebug_rd_wr) {
_Mglc_Swtr_Pn1_2(_Lw_1, 255);
}
}
void _Mglc_Ecvar_Pwr_2(_Mglc_Ecvar _Lg_0, union _Mglc_Swtr* _Lw_1) {
Fputnum(_Lw_1, _Lg_0 + 1);
}
void _Mglc_Eenum_flags_Pwr_2(_Mglc_Eenum_flags _Le_0, union _Mglc_Swtr* _Lw_1) {
_Mglc_Swtr_Pn1_2(_Lw_1, _Le_0);
}
void _Mglc_Estruct_flags_Pwr_2(_Mglc_Estruct_flags _Lf_0, union _Mglc_Swtr* _Lw_1) {
_Mglc_Swtr_Pn1_2(_Lw_1, _Lf_0);
}
void _Mglc_Sfvar_Pwr_3(struct _Mglc_Sfvar* _Lf_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2) {
_Mglc_Sdecl_var_Pwr_3(&(*_Lf_0)._Fdecl, _Lw_1, _Lheader_2);
}
void _Mglc_Sfarg_Pwr_3(struct _Mglc_Sfarg* _Lf_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2) {
_Mglc_Sdecl_var_Pwr_3(&(*_Lf_0)._Fdecl, _Lw_1, _Lheader_2);
}
void _Mglc_Efunc_flags_Pwr_2(_Mglc_Efunc_flags _Le_0, union _Mglc_Swtr* _Lw_1) {
Fputnum(_Lw_1, _Le_0);
}
void _Mglc_Efunc_Pwr_2(_Mglc_Efunc _Lf_0, union _Mglc_Swtr* _Lw_1) {
Fputnum(_Lw_1, _Lf_0 + _Mglc_Efunc_C1);
}
void _Mglc_Sdecl_func_Plvars_wr_3(struct _Mglc_Sdecl_func* _Lf_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2) {
Fputnum(_Lw_1, (*_Lf_0)._Flvar_c);
int32_t _Li_3;
_Li_3 = 0;
for(int i = (*_Lf_0)._Flvar_c; i > 0; ) {
i --;
struct _Mglc_Slvar* _Ll_4;
_Ll_4 = (*_Lf_0)._Flvar_v[_Li_3];
Fputnum(_Lw_1, (*_Ll_4)._Frow);
Fputnum(_Lw_1, (*_Ll_4)._Fcol);
_Mglc_Sdecl_var_Pwr_3(&(*_Ll_4)._Fdecl, _Lw_1, _Lheader_2);
_Mglc_Elvar_flags_Pwr_2((*_Ll_4)._Fflags, _Lw_1);
if(((*_Ll_4)._Fflags & _Mglc_Elvar_flags_Cset_expr) != _Mglc_Elvar_flags_C0) {
_Mglc_Eexpr_Pwr_3((*_Ll_4)._Fset_expr, _Lw_1, _Lheader_2);
}
continue_0:;
_Li_3++;
}
break_0:;
}
void _Mglc_Sstmt_space_Pwr_3(struct _Mglc_Sstmt_space* _Lspace_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2) {
struct _Mglc_Sstmt* _Lstmt_4;
Fputnum(_Lw_1, (*_Lspace_0)._Flvar_c);
int32_t _Li_3;
_Li_3 = 0;
for(int i = (*_Lspace_0)._Flvar_c; i > 0; ) {
i --;
_Mglc_Elvar_Pwr_2((*_Lspace_0)._Flvar_v[_Li_3], _Lw_1);
continue_0:;
_Li_3++;
}
break_0:;
_Lstmt_4 = (*_Lspace_0)._Fstmt_first;
while(_Lstmt_4 != NULL) {
_Mglc_Estmt_type_Pwr_2((*_Lstmt_4)._Ftype, _Lw_1);
if(_Mglc_Cdebug_rd_wr) {
_Mglc_Swtr_Pn1_2(_Lw_1, 255);
}
Fputnum(_Lw_1, (*_Lstmt_4)._Fbegin_row);
Fputnum(_Lw_1, (*_Lstmt_4)._Fbegin_col);
Fputnum(_Lw_1, (*_Lstmt_4)._Fend_row);
Fputnum(_Lw_1, (*_Lstmt_4)._Fend_col);
switch((*_Lstmt_4)._Ftype) {
case _Mglc_Estmt_type_Cbreak:;
_Mglc_Sstmt_space_Pwr_break_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _Mglc_Estmt_type_Cswitch:;
_Mglc_Sstmt_space_Pwr_switch_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _Mglc_Estmt_type_Ccase:;
_Mglc_Sstmt_space_Pwr_case_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _Mglc_Estmt_type_Ccase_end:;
_Mglc_Sstmt_space_Pwr_case_end_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _Mglc_Estmt_type_Cdefault:;
_Mglc_Sstmt_space_Pwr_default_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _Mglc_Estmt_type_Cdefault_end:;
_Mglc_Sstmt_space_Pwr_default_end_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _Mglc_Estmt_type_Cswitch_end:;
_Mglc_Sstmt_space_Pwr_switch_end_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _Mglc_Estmt_type_Cif:;
_Mglc_Sstmt_space_Pwr_if_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _Mglc_Estmt_type_Cif_elif:;
_Mglc_Sstmt_space_Pwr_if_elif_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _Mglc_Estmt_type_Cif_else:;
_Mglc_Sstmt_space_Pwr_if_else_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _Mglc_Estmt_type_Cif_end:;
_Mglc_Sstmt_space_Pwr_if_end_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _Mglc_Estmt_type_Cdo:;
_Mglc_Sstmt_space_Pwr_do_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _Mglc_Estmt_type_Cdo_end:;
_Mglc_Sstmt_space_Pwr_do_end_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _Mglc_Estmt_type_Cwhile:;
_Mglc_Sstmt_space_Pwr_while_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _Mglc_Estmt_type_Cwhile_end:;
_Mglc_Sstmt_space_Pwr_while_end_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _Mglc_Estmt_type_Ccontinue:;
_Mglc_Sstmt_space_Pwr_continue_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _Mglc_Estmt_type_Creturn:;
_Mglc_Sstmt_space_Pwr_return_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _Mglc_Estmt_type_Cspace:;
_Mglc_Sstmt_space_Pwr_space_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _Mglc_Estmt_type_Cexpr:;
_Mglc_Sstmt_space_Pwr_expr_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
default:;
fprintf(stdout, ":wr not yet implemented in stmt #%s\n", _Mglc_Estmt_type_Pglc_name_1((*_Lstmt_4)._Ftype));
exit(_Mstdc_Eexit_Cfailure);
break;
}
if(_Mglc_Cdebug_rd_wr) {
_Mglc_Swtr_Pn1_2(_Lw_1, 255);
}
_Lstmt_4 = (*_Lstmt_4)._Fstmt_next;
continue_1:;
}
break_1:;
_Mglc_Estmt_type_Pwr_2(_Mglc_Estmt_type_Cnil, _Lw_1);
}
void _Mglc_Swtr_Pn4_2(union _Mglc_Swtr* _Lw_0, uint32_t _Ln_1) {
(*_Lw_0)._F1[0] = _Ln_1;
(*_Lw_0)._F1[1] = (_Ln_1 >> 8);
(*_Lw_0)._F1[2] = (_Ln_1 >> 16);
(*_Lw_0)._F1[3] = (_Ln_1 >> 24);
(*_Lw_0)._Fpos += 4;
}
void _Mglc_Sdecl_var_Pcopy_from_2(struct _Mglc_Sdecl_var* _Lvd_0, struct _Mglc_Sdecl_var* _Lsrc_1) {
(*_Lvd_0)._Fname = (*_Lsrc_1)._Fname;
(*_Lvd_0)._Ftype = (*_Lsrc_1)._Ftype;
(*_Lvd_0)._Fflags = (*_Lsrc_1)._Fflags;
(*_Lvd_0)._Freal_name = (*_Lsrc_1)._Freal_name;
_Mglc_Stype_info_Pcopy_from_2(&(*_Lvd_0)._Ftype_info, &(*_Lsrc_1)._Ftype_info);
(*_Lvd_0)._Ftype_info._Fbuilt_in = (*_Lsrc_1)._Ftype_info._Fbuilt_in;
(*_Lvd_0)._Fsize_c = (*_Lsrc_1)._Fsize_c;
if((*_Lvd_0)._Fsize_c > 0) {
_Mglc_Pquick_alloc_arr_2((*_Lvd_0)._Fsize_expr_v, (*_Lvd_0)._Fsize_c);
int32_t _Li_2;
_Li_2 = 0;
for(int i = (*_Lvd_0)._Fsize_c; i > 0; ) {
i --;
(*_Lvd_0)._Fsize_expr_v[_Li_2] = (*_Lsrc_1)._Fsize_expr_v[_Li_2];
continue_0:;
_Li_2++;
}
break_0:;
}
}
void _Mglc_Sfarg_Pcopy_from_2(struct _Mglc_Sfarg* _Lf_0, struct _Mglc_Sfarg* _Lsrc_1) {
(*_Lf_0)._Frow = (*_Lsrc_1)._Frow;
(*_Lf_0)._Fcol = (*_Lsrc_1)._Fcol;
_Mglc_Sdecl_var_Pcopy_from_2(&(*_Lf_0)._Fdecl, &(*_Lsrc_1)._Fdecl);
}
uint8_t _Mglc_Eid_Plen_1(_Mglc_Eid _Lid_0) {
return _Gid_len_v[_Lid_0];
}
char* _Mglc_Eid_Pstr_1(_Mglc_Eid _Lid_0) {
return _Gid_str_v[_Lid_0];
}
struct _Mglc_Sdecl_func* _Mglc_Efunc_Pptr_1(_Mglc_Efunc _Lf_0) {
return _Gfunc_v[_Lf_0];
}
_Mglc_Elvar _Mglc_Sstmt_space_Plvar_new_4(struct _Mglc_Sstmt_space* _Lspace_0, _Mglc_Eid _Lname_1, int32_t _Lrow_2, int32_t _Lcol_3) {
_Mglc_Elvar* _Lv_4;
int32_t _Li_7;
struct _Mglc_Sdecl_func* _Lf_9;
_Mglc_Elvar _Llvar_10;
struct _Mglc_Slvar* _Litem_12;
_Lv_4 = (*_Lspace_0)._Flvar_v;
int32_t _Li_5;
_Li_5 = 0;
for(int i = (*_Lspace_0)._Flvar_c; i > 0; ) {
i --;
struct _Mglc_Slvar* _Llvar_6;
_Llvar_6 = _Mglc_Elvar_Pptr_1(_Lv_4[_Li_5]);
if((*_Llvar_6)._Fdecl._Fname == _Lname_1) {
fprintf(stdout, "%u:%u: lvar '%s' was already declared at %u:%u\n", _Lrow_2, _Lcol_3, _Mglc_Eid_Pstr_1(_Lname_1), (*_Llvar_6)._Frow, (*_Llvar_6)._Fcol);
exit(_Mstdc_Eexit_Cfailure);
}
continue_0:;
_Li_5++;
}
break_0:;
_Li_7 = (*_Lspace_0)._Flvar_c++;
if((*_Lspace_0)._Flvar_cap <= (*_Lspace_0)._Flvar_c) {
int32_t _Lold_cap_8;
_Lold_cap_8 = (*_Lspace_0)._Flvar_cap;
_Mglc_Pgrow_2((*_Lspace_0)._Flvar_cap, (*_Lspace_0)._Flvar_c);
_Mglc_Prealloc_3((*_Lspace_0)._Flvar_v, (*_Lspace_0)._Flvar_cap, _Lold_cap_8);
}
_Lf_9 = _Gctx_func;
_Llvar_10 = (*_Lf_9)._Flvar_c++;
(*_Lspace_0)._Flvar_v[_Li_7] = _Llvar_10;
if((*_Lf_9)._Flvar_cap <= (*_Lf_9)._Flvar_c) {
_Mglc_Elvar _Lold_cap_11;
_Lold_cap_11 = (*_Lf_9)._Flvar_cap;
_Mglc_Pgrow_2((*_Lf_9)._Flvar_cap, (*_Lf_9)._Flvar_c);
_Mglc_Prealloc_3((*_Lf_9)._Flvar_v, (*_Lf_9)._Flvar_cap, _Lold_cap_11);
}
_Mglc_Pquick_alloc_one_1(_Litem_12);
(*_Lf_9)._Flvar_v[_Llvar_10] = _Litem_12;
(*_Litem_12)._Frow = _Lrow_2;
(*_Litem_12)._Fcol = _Lcol_3;
(*_Litem_12)._Fdecl._Fname = _Lname_1;
return _Llvar_10;
}
struct _Mglc_Slvar* _Mglc_Elvar_Pptr_1(_Mglc_Elvar _Ll_0) {
return (*_Gctx_func)._Flvar_v[_Ll_0];
}
void _Mglc_Stype_info_Pinit_1(struct _Mglc_Stype_info* _Lti_0) {
(*_Lti_0)._Fref_v[0] = 0;
(*_Lti_0)._Farray_c = 0;
(*_Lti_0)._Fstar_c = 0;
(*_Lti_0)._Fbuilt_in = false;
(*_Lti_0)._Fconst = false;
}
_Mglc_Eexpr _Mglc_Pexpr_push_2(struct _Mglc_Sexpr* _Le_0, _Mglc_Eexpr_type _Ltype_1) {
int32_t _Le_idx_2;
(*_Le_0)._Ftype = _Ltype_1;
_Le_idx_2 = _Gexpr_c++;
if(_Gexpr_cap <= _Gexpr_c) {
int32_t _Lold_cap_3;
_Lold_cap_3 = _Gexpr_cap;
_Mglc_Pgrow_2(_Gexpr_cap, _Gexpr_c);
_Mglc_Prealloc_3(_Gexpr_v, _Gexpr_cap, _Lold_cap_3);
}
_Gexpr_v[_Le_idx_2] = _Le_0;
return _Le_idx_2;
}
struct _Mglc_Sexpr* _Mglc_Eexpr_Pptr_1(_Mglc_Eexpr _Le_0) {
return _Gexpr_v[_Le_0];
}
void _Mglc_Pstmt_push_6(struct _Mglc_Sstmt* _Ls_0, int32_t _Lbegin_row_1, int32_t _Lbegin_col_2, int32_t _Lend_row_3, int32_t _Lend_col_4, _Mglc_Estmt_type _Ltype_5) {
(*_Ls_0)._Fbegin_row = _Lbegin_row_1;
(*_Ls_0)._Fbegin_col = _Lbegin_col_2;
(*_Ls_0)._Fend_row = _Lend_row_3;
(*_Ls_0)._Fend_col = _Lend_col_4;
(*_Ls_0)._Ftype = _Ltype_5;
_Mglc_Pfunc_stmt_add_1(_Ls_0);
}
_Mglc_Eid _Mglc_Elvar_Pname_1(_Mglc_Elvar _Ll_0) {
return (*_Mglc_Elvar_Pptr_1(_Ll_0))._Fdecl._Fname;
}
struct _Mglc_Sat* _Mglc_Eat_Pptr_1(_Mglc_Eat _Li_0) {
return &_Gat_v[_Li_0];
}
_Mglc_Eat _Mglc_Pat_create_basic_1(_Mglc_Ebasic_type_id _Lbasic_0) {
_Mglc_Eat _Lbuild_idx_3;
struct _Mglc_Sat* _Lat_5;
_Mglc_Eat _Li_1;
_Li_1 = (_Mglc_Eat)(0);
for(int i = _Gat_c; i > 0; ) {
i --;
struct _Mglc_Sat* _Lat_2;
_Lat_2 = (&_Gat_v[_Li_1]);
if((((*_Lat_2)._Ftype == _Mglc_Ename_type_Cbasic) && ((*_Lat_2)._Fname._Fbasic == _Lbasic_0))) {
return _Li_1;
}
continue_0:;
_Li_1++;
}
break_0:;
_Lbuild_idx_3 = _Gat_c++;
if(_Gat_cap <= _Gat_c) {
_Mglc_Eat _Lold_cap_4;
_Lold_cap_4 = _Gat_cap;
_Mglc_Pgrow_2(_Gat_cap, _Gat_c);
_Mglc_Prealloc_3(_Gat_v, _Gat_cap, _Lold_cap_4);
}
_Lat_5 = (&_Gat_v[_Lbuild_idx_3]);
(*_Lat_5)._Fparent = _Mglc_Eat_Croot;
(*_Lat_5)._Ftype = _Mglc_Ename_type_Cbasic;
(*_Lat_5)._Fname._Fbasic = _Lbasic_0;
return _Lbuild_idx_3;
}
_Mglc_Eat _Mglc_Pat_create_3(_Mglc_Eat _Lparent_0, _Mglc_Ename_type _Ltype_1, _Mglc_Eid _Lname_2) {
_Mglc_Eat _Lbuild_idx_5;
struct _Mglc_Sat* _Lat_7;
_Mglc_Eat _Li_3;
_Li_3 = (_Mglc_Eat)(0);
for(int i = _Gat_c; i > 0; ) {
i --;
struct _Mglc_Sat* _Lat_4;
_Lat_4 = (&_Gat_v[_Li_3]);
if((((*_Lat_4)._Fparent == _Lparent_0) && ((*_Lat_4)._Ftype == _Ltype_1) && ((*_Lat_4)._Fname._Fid == _Lname_2))) {
return _Li_3;
}
continue_0:;
_Li_3++;
}
break_0:;
_Lbuild_idx_5 = _Gat_c++;
if(_Gat_cap <= _Gat_c) {
_Mglc_Eat _Lold_cap_6;
_Lold_cap_6 = _Gat_cap;
_Mglc_Pgrow_2(_Gat_cap, _Gat_c);
_Mglc_Prealloc_3(_Gat_v, _Gat_cap, _Lold_cap_6);
}
_Lat_7 = (&_Gat_v[_Lbuild_idx_5]);
(*_Lat_7)._Fparent = _Lparent_0;
(*_Lat_7)._Ftype = _Ltype_1;
(*_Lat_7)._Fname._Fid = _Lname_2;
return _Lbuild_idx_5;
}
void _Mglc_Ptype_info_arr_1(_Mglc_Eexpr _Lexpr_0) {
struct _Mglc_Stype_info* _Lti_1;
_Lti_1 = (&_Gdecl_var._Ftype_info);
(*_Lti_1)._Farray_c += 1;
(*_Lti_1)._Fref_v[(*_Lti_1)._Farray_c] = 0;
if(_Lexpr_0 != _Mglc_Eexpr_Cnil) {
struct _Mglc_Sdecl_var* _Lvd_2;
_Lvd_2 = (&_Gdecl_var);
if((*_Lvd_2)._Fsize_c == 0) {
_Mglc_Pquick_alloc_arr_2((*_Lvd_2)._Fsize_expr_v, _Mglc_Cdecl_var_size_limit);
}
(*_Lvd_2)._Fsize_expr_v[(*_Lvd_2)._Fsize_c++] = _Lexpr_0;
}
}
void _Mglc_Stype_info_Pfinalize_1(struct _Mglc_Stype_info* _Lti_0) {
int8_t _Lref_v_1[_Mglc_Ctype_info_star_limit];
int8_t _Lc_2;
int8_t _Lstar_c_3;
_Lc_2 = (*_Lti_0)._Farray_c;
_Lstar_c_3 = (*_Lti_0)._Farray_c;
int32_t _Li_4;
_Li_4 = 0;
for(int i = _Lc_2 + 1; i > 0; ) {
i --;
_Lref_v_1[_Li_4] = (*_Lti_0)._Fref_v[_Li_4];
_Lstar_c_3 += _Lref_v_1[_Li_4];
_Li_4 += 1;
continue_0:;
}
break_0:;
int32_t _Li_5;
int8_t _Lj_6;
_Li_5 = 0;
_Lj_6 = _Lc_2;
for(int i = _Lc_2 + 1; i > 0; ) {
i --;
(*_Lti_0)._Fref_v[_Li_5] = _Lref_v_1[_Lj_6];
_Li_5 += 1;
_Lj_6 -= 1;
continue_1:;
}
break_1:;
(*_Lti_0)._Fstar_c = _Lstar_c_3;
}
struct _Mglc_Scvar* _Mglc_Ecvar_Pptr_1(_Mglc_Ecvar _Lc_0) {
return &_Gcvar_v[_Lc_0];
}
struct _Mglc_Sstmt_space* _Mglc_Pstmt_space_begin_1(bool _Lattach_0) {
struct _Mglc_Sstmt_space* _Lparent_1;
struct _Mglc_Sstmt_space* _Lspace_2;
_Lparent_1 = _Gdecl_func_ctx_space;
_Mglc_Pquick_alloc_one_1(_Gdecl_func_ctx_space);
_Lspace_2 = _Gdecl_func_ctx_space;
(*_Lspace_2)._Fparent = _Lparent_1;
if(_Lattach_0) {
if((*_Lparent_1)._Fstmt_last == NULL) {
(*_Lparent_1)._Fstmt_first = (&(*_Lspace_2)._Fbase);
(*_Lparent_1)._Fstmt_last = (&(*_Lspace_2)._Fbase);
} else {
(*(*_Lparent_1)._Fstmt_last)._Fstmt_next = (&(*_Lspace_2)._Fbase);
(*_Lparent_1)._Fstmt_last = (&(*_Lspace_2)._Fbase);
}
}
return _Lspace_2;
}
void _Mglc_Evar_flags_Pwr_2(_Mglc_Evar_flags _Lf_0, union _Mglc_Swtr* _Lw_1) {
Fputnum(_Lw_1, _Lf_0);
}
void _Mglc_Stype_info_Pwr_2(struct _Mglc_Stype_info* _Lti_0, union _Mglc_Swtr* _Lw_1) {
int32_t _Lc_2;
_Lc_2 = 0;
for(int i = _Mglc_Ctype_info_star_limit; i > 0; ) {
i --;
if((*_Lti_0)._Fref_v[_Lc_2] == 0) {
goto break_0;
}
_Lc_2++;
continue_0:;
}
break_0:;
_Mglc_Swtr_Pn1_2(_Lw_1, _Lc_2);
int32_t _Li_3;
_Li_3 = 0;
for(int i = _Lc_2; i > 0; ) {
i --;
_Mglc_Swtr_Pn1_2(_Lw_1, (*_Lti_0)._Fref_v[_Li_3]);
continue_1:;
_Li_3++;
}
break_1:;
_Mglc_Swtr_Pn1_2(_Lw_1, (*_Lti_0)._Farray_c);
_Mglc_Swtr_Pn1_2(_Lw_1, (*_Lti_0)._Fstar_c);
_Mglc_Swtr_Pbool_2(_Lw_1, (*_Lti_0)._Fbuilt_in);
_Mglc_Swtr_Pbool_2(_Lw_1, (*_Lti_0)._Fconst);
}
void _Mglc_Eexpr_type_Pwr_2(_Mglc_Eexpr_type _Le_0, union _Mglc_Swtr* _Lw_1) {
_Mglc_Swtr_Pn1_2(_Lw_1, _Le_0);
}
void _Mglc_Eexpr_Pwr_math_3(struct _Mglc_Sexpr* _Lexpr_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2) {
struct _Mglc_Sexpr_math* _Le_3;
_Le_3 = _Lexpr_0;
_Mglc_Eexpr_Pwr_3((*_Le_3)._Fleft, _Lw_1, _Lheader_2);
_Mglc_Eexpr_Pwr_3((*_Le_3)._Fright, _Lw_1, _Lheader_2);
_Mglc_Emath_Pwr_2((*_Le_3)._Ftype, _Lw_1);
_Mglc_Swtr_Pn1_2(_Lw_1, (*_Le_3)._Fitem_c);
int32_t _Li_4;
_Li_4 = 0;
for(int i = (*_Le_3)._Fitem_c; i > 0; ) {
i --;
_Mglc_Eexpr_Pwr_3((*_Le_3)._Fitem_v[_Li_4]._Fexpr, _Lw_1, _Lheader_2);
continue_0:;
_Li_4++;
}
break_0:;
}
void _Mglc_Eexpr_Pwr_bools_3(struct _Mglc_Sexpr* _Lexpr_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2) {
struct _Mglc_Sexpr_bools* _Le_3;
_Le_3 = _Lexpr_0;
_Mglc_Eexpr_Pwr_3((*_Le_3)._Fleft, _Lw_1, _Lheader_2);
_Mglc_Eexpr_Pwr_3((*_Le_3)._Fright, _Lw_1, _Lheader_2);
_Mglc_Swtr_Pn1_2(_Lw_1, (*_Le_3)._Fitem_c);
int32_t _Li_4;
_Li_4 = 0;
for(int i = (*_Le_3)._Fitem_c; i > 0; ) {
i --;
_Mglc_Eexpr_Pwr_3((*_Le_3)._Fitem_v[_Li_4]._Fexpr, _Lw_1, _Lheader_2);
continue_0:;
_Li_4++;
}
break_0:;
_Mglc_Ebools_Pwr_2((*_Le_3)._Ftype, _Lw_1);
}
void _Mglc_Eexpr_Pwr_str_3(struct _Mglc_Sexpr* _Lexpr_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2) {
struct _Mglc_Sexpr_str* _Le_3;
struct _Mglc_Sexpr_str_node* _Ln_4;
_Le_3 = _Lexpr_0;
Fputnum(_Lw_1, (*_Le_3)._Fnode_c);
_Ln_4 = (*_Le_3)._Ffirst;
while(1) {
Fputnum(_Lw_1, (*_Ln_4)._Flen);
_Mglc_Swtr_Pcopy_3(_Lw_1, (*_Ln_4)._Fbuf, (*_Ln_4)._Flen);
_Ln_4 = (*_Ln_4)._Fnext;
if(_Ln_4 == NULL) {
goto break_0;
}
continue_0:;
}
break_0:;
}
void _Mglc_Eexpr_Pwr_cvar_3(struct _Mglc_Sexpr* _Lexpr_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2) {
struct _Mglc_Sexpr_cvar* _Le_3;
_Le_3 = _Lexpr_0;
_Mglc_Eat_Pwr_3((*_Le_3)._Fat, _Lw_1, _Lheader_2);
_Mglc_Eid_Pwr_3((*_Le_3)._Fname, _Lw_1, _Lheader_2);
}
void _Mglc_Eexpr_Pwr_unary_3(struct _Mglc_Sexpr* _Lexpr_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2) {
struct _Mglc_Sexpr_unary* _Le_3;
_Le_3 = _Lexpr_0;
_Mglc_Eexpr_Pwr_3((*_Le_3)._Fexpr, _Lw_1, _Lheader_2);
_Mglc_Eunary_Pwr_2((*_Le_3)._Ftype, _Lw_1);
}
void _Mglc_Eexpr_Pwr_ref_3(struct _Mglc_Sexpr* _Lexpr_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2) {
struct _Mglc_Sexpr_ref* _Le_3;
_Le_3 = _Lexpr_0;
_Mglc_Eexpr_Pwr_3((*_Le_3)._Fexpr, _Lw_1, _Lheader_2);
}
void _Mglc_Eexpr_Pwr_cast_fast_3(struct _Mglc_Sexpr* _Lexpr_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2) {
struct _Mglc_Sexpr_cast_fast* _Le_3;
_Le_3 = _Lexpr_0;
_Mglc_Eexpr_Pwr_3((*_Le_3)._Fexpr, _Lw_1, _Lheader_2);
_Mglc_Eat_Pwr_3((*_Le_3)._Ftype, _Lw_1, _Lheader_2);
}
void _Mglc_Eexpr_Pwr_index_3(struct _Mglc_Sexpr* _Lexpr_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2) {
struct _Mglc_Sexpr_index* _Le_3;
_Le_3 = _Lexpr_0;
_Mglc_Eexpr_Pwr_3((*_Le_3)._Fleft, _Lw_1, _Lheader_2);
_Mglc_Eexpr_Pwr_3((*_Le_3)._Fright, _Lw_1, _Lheader_2);
}
void _Mglc_Eexpr_Pwr_compare_3(struct _Mglc_Sexpr* _Lexpr_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2) {
struct _Mglc_Sexpr_compare* _Le_3;
_Le_3 = _Lexpr_0;
_Mglc_Eexpr_Pwr_3((*_Le_3)._Fleft, _Lw_1, _Lheader_2);
_Mglc_Eexpr_Pwr_3((*_Le_3)._Fright, _Lw_1, _Lheader_2);
_Mglc_Ecompare_Pwr_2((*_Le_3)._Ftype, _Lw_1);
}
void _Mglc_Eexpr_Pwr_bool_3(struct _Mglc_Sexpr* _Lexpr_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2) {
struct _Mglc_Sexpr_bool* _Le_3;
_Le_3 = _Lexpr_0;
_Mglc_Swtr_Pbool_2(_Lw_1, (*_Le_3)._Fvalue);
}
void _Mglc_Eexpr_Pwr_char_3(struct _Mglc_Sexpr* _Lexpr_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2) {
struct _Mglc_Sexpr_char* _Le_3;
_Le_3 = _Lexpr_0;
Fputnum(_Lw_1, (*_Le_3)._Fvalue);
}
void _Mglc_Eexpr_Pwr_method_3(struct _Mglc_Sexpr* _Lexpr_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2) {
struct _Mglc_Sexpr_method* _Le_3;
_Le_3 = _Lexpr_0;
_Mglc_Eexpr_Pwr_3((*_Le_3)._Fthis, _Lw_1, _Lheader_2);
_Mglc_Eid_Pwr_3((*_Le_3)._Ffunc_name, _Lw_1, _Lheader_2);
_Mglc_Swtr_Pn1_2(_Lw_1, (*_Le_3)._Fgroup_c);
int32_t _Li_4;
_Li_4 = 0;
for(int i = (*_Le_3)._Fgroup_c; i > 0; ) {
i --;
_Mglc_Swtr_Pn1_2(_Lw_1, (*_Le_3)._Fgroup_v[_Li_4]);
continue_0:;
_Li_4++;
}
break_0:;
_Mglc_Swtr_Pn1_2(_Lw_1, (*_Le_3)._Fcarg_c);
int32_t _Li_5;
_Li_5 = 0;
for(int i = (*_Le_3)._Fcarg_c; i > 0; ) {
i --;
_Mglc_Eexpr_Pwr_3((*_Le_3)._Fcarg_v[_Li_5]._Fexpr, _Lw_1, _Lheader_2);
continue_1:;
_Li_5++;
}
break_1:;
}
void _Mglc_Eexpr_Pwr_func_3(struct _Mglc_Sexpr* _Lexpr_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2) {
struct _Mglc_Sexpr_func* _Le_3;
_Le_3 = _Lexpr_0;
_Mglc_Eat_Pwr_3((*_Le_3)._Fat, _Lw_1, _Lheader_2);
_Mglc_Eid_Pwr_3((*_Le_3)._Ffunc_name, _Lw_1, _Lheader_2);
_Mglc_Swtr_Pn1_2(_Lw_1, (*_Le_3)._Fgroup_c);
int32_t _Li_4;
_Li_4 = 0;
for(int i = (*_Le_3)._Fgroup_c; i > 0; ) {
i --;
_Mglc_Swtr_Pn1_2(_Lw_1, (*_Le_3)._Fgroup_v[_Li_4]);
continue_0:;
_Li_4++;
}
break_0:;
_Mglc_Swtr_Pn1_2(_Lw_1, (*_Le_3)._Fcarg_c);
int32_t _Li_5;
_Li_5 = 0;
for(int i = (*_Le_3)._Fcarg_c; i > 0; ) {
i --;
_Mglc_Eexpr_Pwr_3((*_Le_3)._Fcarg_v[_Li_5]._Fexpr, _Lw_1, _Lheader_2);
continue_1:;
_Li_5++;
}
break_1:;
}
void _Mglc_Eexpr_Pwr_null_3(struct _Mglc_Sexpr* _Lexpr_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2) {
struct _Mglc_Sexpr_null* _Le_3;
_Le_3 = _Lexpr_0;
}
void _Mglc_Eexpr_Pwr_int_3(struct _Mglc_Sexpr* _Lexpr_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2) {
struct _Mglc_Sexpr_int* _Le_3;
_Le_3 = _Lexpr_0;
_Mglc_Swtr_Pn1_2(_Lw_1, (*_Le_3)._Ftype);
Fputnum(_Lw_1, (*_Le_3)._Fvalue);
}
void _Mglc_Eexpr_Pwr_size_of_type_3(struct _Mglc_Sexpr* _Lexpr_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2) {
struct _Mglc_Sexpr_size_of_type* _Le_3;
_Le_3 = _Lexpr_0;
_Mglc_Eat_Pwr_3((*_Le_3)._Ftype, _Lw_1, _Lheader_2);
}
void _Mglc_Eexpr_Pwr_assign_3(struct _Mglc_Sexpr* _Lexpr_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2) {
struct _Mglc_Sexpr_assign* _Le_3;
_Le_3 = _Lexpr_0;
_Mglc_Eexpr_Pwr_3((*_Le_3)._Fleft, _Lw_1, _Lheader_2);
_Mglc_Eexpr_Pwr_3((*_Le_3)._Fright, _Lw_1, _Lheader_2);
_Mglc_Eassign_Pwr_2((*_Le_3)._Ftype, _Lw_1);
}
void _Mglc_Eexpr_Pwr_fvar_3(struct _Mglc_Sexpr* _Lexpr_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2) {
struct _Mglc_Sexpr_fvar* _Le_3;
_Le_3 = _Lexpr_0;
_Mglc_Eexpr_Pwr_3((*_Le_3)._Fexpr, _Lw_1, _Lheader_2);
_Mglc_Eid_Pwr_3((*_Le_3)._Fmember, _Lw_1, _Lheader_2);
}
void _Mglc_Eexpr_Pwr_gvar_3(struct _Mglc_Sexpr* _Lexpr_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2) {
struct _Mglc_Sexpr_gvar* _Le_3;
_Le_3 = _Lexpr_0;
_Mglc_Eat_Pwr_3((*_Le_3)._Fat, _Lw_1, _Lheader_2);
_Mglc_Eid_Pwr_3((*_Le_3)._Fname, _Lw_1, _Lheader_2);
}
void _Mglc_Eexpr_Pwr_lvar_3(struct _Mglc_Sexpr* _Lexpr_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2) {
struct _Mglc_Sexpr_lvar* _Le_3;
_Le_3 = _Lexpr_0;
_Mglc_Elvar_Pwr_2((*_Le_3)._Flvar, _Lw_1);
}
void _Mglc_Elvar_flags_Pwr_2(_Mglc_Elvar_flags _Lf_0, union _Mglc_Swtr* _Lw_1) {
_Mglc_Swtr_Pn1_2(_Lw_1, _Lf_0);
}
void _Mglc_Elvar_Pwr_2(_Mglc_Elvar _Ll_0, union _Mglc_Swtr* _Lw_1) {
Fputnum(_Lw_1, _Ll_0 + 1);
}
void _Mglc_Estmt_type_Pwr_2(_Mglc_Estmt_type _Ls_0, union _Mglc_Swtr* _Lw_1) {
_Mglc_Swtr_Pn1_2(_Lw_1, _Ls_0);
}
void _Mglc_Sstmt_space_Pwr_break_3(struct _Mglc_Sstmt* _Lstmt_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2) {
struct _Mglc_Sstmt_break* _Ls_3;
_Ls_3 = _Lstmt_0;
_Mglc_Swtr_Pn1_2(_Lw_1, (*_Ls_3)._Fnest);
}
void _Mglc_Sstmt_space_Pwr_switch_3(struct _Mglc_Sstmt* _Lstmt_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2) {
struct _Mglc_Sstmt_switch* _Ls_3;
_Ls_3 = _Lstmt_0;
_Mglc_Eexpr_Pwr_3((*_Ls_3)._Fexpr, _Lw_1, _Lheader_2);
_Mglc_Eexpr_Pwr_3((*_Ls_3)._Fcases, _Lw_1, _Lheader_2);
}
void _Mglc_Sstmt_space_Pwr_case_3(struct _Mglc_Sstmt* _Lstmt_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2) {
struct _Mglc_Sstmt_case* _Ls_3;
_Ls_3 = _Lstmt_0;
Fputnum(_Lw_1, (*_Ls_3)._Fexpr_c);
int32_t _Li_4;
_Li_4 = 0;
for(int i = (*_Ls_3)._Fexpr_c; i > 0; ) {
i --;
_Mglc_Eexpr_Pwr_3((*_Ls_3)._Fexpr_v[_Li_4]._Fexpr, _Lw_1, _Lheader_2);
continue_0:;
_Li_4++;
}
break_0:;
_Mglc_Swtr_Pbool_2(_Lw_1, (*_Ls_3)._Ffall_through);
}
void _Mglc_Sstmt_space_Pwr_case_end_3(struct _Mglc_Sstmt* _Lstmt_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2) {
}
void _Mglc_Sstmt_space_Pwr_default_3(struct _Mglc_Sstmt* _Lstmt_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2) {
struct _Mglc_Sstmt_default* _Ls_3;
_Ls_3 = _Lstmt_0;
_Mglc_Swtr_Pbool_2(_Lw_1, (*_Ls_3)._Ffall_through);
}
void _Mglc_Sstmt_space_Pwr_default_end_3(struct _Mglc_Sstmt* _Lstmt_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2) {
}
void _Mglc_Sstmt_space_Pwr_switch_end_3(struct _Mglc_Sstmt* _Lstmt_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2) {
}
void _Mglc_Sstmt_space_Pwr_if_3(struct _Mglc_Sstmt* _Lstmt_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2) {
struct _Mglc_Sstmt_if* _Ls_3;
_Ls_3 = _Lstmt_0;
_Mglc_Swtr_Pbool_2(_Lw_1, (*_Ls_3)._Fnot);
_Mglc_Eexpr_Pwr_3((*_Ls_3)._Fexpr, _Lw_1, _Lheader_2);
}
void _Mglc_Sstmt_space_Pwr_if_elif_3(struct _Mglc_Sstmt* _Lstmt_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2) {
struct _Mglc_Sstmt_if_elif* _Ls_3;
_Ls_3 = _Lstmt_0;
_Mglc_Swtr_Pbool_2(_Lw_1, (*_Ls_3)._Fnot);
_Mglc_Eexpr_Pwr_3((*_Ls_3)._Fexpr, _Lw_1, _Lheader_2);
}
void _Mglc_Sstmt_space_Pwr_if_else_3(struct _Mglc_Sstmt* _Lstmt_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2) {
}
void _Mglc_Sstmt_space_Pwr_if_end_3(struct _Mglc_Sstmt* _Lstmt_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2) {
}
void _Mglc_Sstmt_space_Pwr_do_3(struct _Mglc_Sstmt* _Lstmt_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2) {
struct _Mglc_Sstmt_do* _Ls_3;
_Ls_3 = _Lstmt_0;
_Mglc_Eexpr_Pwr_3((*_Ls_3)._Fexpr, _Lw_1, _Lheader_2);
if((*_Ls_3)._Fcontinue != NULL) {
_Mglc_Swtr_Pbool_2(_Lw_1, true);
_Mglc_Sstmt_space_Pwr_3((*_Ls_3)._Fcontinue, _Lw_1, _Lheader_2);
} else {
_Mglc_Swtr_Pbool_2(_Lw_1, false);
}
}
void _Mglc_Sstmt_space_Pwr_do_end_3(struct _Mglc_Sstmt* _Lstmt_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2) {
}
void _Mglc_Sstmt_space_Pwr_while_3(struct _Mglc_Sstmt* _Lstmt_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2) {
struct _Mglc_Sstmt_while* _Ls_3;
_Ls_3 = _Lstmt_0;
_Mglc_Eexpr_Pwr_3((*_Ls_3)._Fexpr, _Lw_1, _Lheader_2);
if((*_Ls_3)._Fcontinue != NULL) {
_Mglc_Swtr_Pbool_2(_Lw_1, true);
_Mglc_Sstmt_space_Pwr_3((*_Ls_3)._Fcontinue, _Lw_1, _Lheader_2);
} else {
_Mglc_Swtr_Pbool_2(_Lw_1, false);
}
}
void _Mglc_Sstmt_space_Pwr_while_end_3(struct _Mglc_Sstmt* _Lstmt_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2) {
}
void _Mglc_Sstmt_space_Pwr_continue_3(struct _Mglc_Sstmt* _Lstmt_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2) {
struct _Mglc_Sstmt_continue* _Ls_3;
_Ls_3 = _Lstmt_0;
_Mglc_Swtr_Pn1_2(_Lw_1, (*_Ls_3)._Fnest);
}
void _Mglc_Sstmt_space_Pwr_return_3(struct _Mglc_Sstmt* _Lstmt_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2) {
struct _Mglc_Sstmt_return* _Ls_3;
_Ls_3 = _Lstmt_0;
_Mglc_Eexpr_Pwr_3((*_Ls_3)._Fexpr, _Lw_1, _Lheader_2);
}
void _Mglc_Sstmt_space_Pwr_space_3(struct _Mglc_Sstmt* _Lstmt_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2) {
struct _Mglc_Sstmt_space* _Ls_3;
_Ls_3 = _Lstmt_0;
_Mglc_Sstmt_space_Pwr_3(_Ls_3, _Lw_1, _Lheader_2);
}
void _Mglc_Sstmt_space_Pwr_expr_3(struct _Mglc_Sstmt* _Lstmt_0, union _Mglc_Swtr* _Lw_1, bool _Lheader_2) {
struct _Mglc_Sstmt_expr* _Ls_3;
_Ls_3 = _Lstmt_0;
_Mglc_Eexpr_Pwr_3((*_Ls_3)._Fexpr, _Lw_1, _Lheader_2);
}
void _Mglc_Stype_info_Pcopy_from_2(struct _Mglc_Stype_info* _Lti_0, struct _Mglc_Stype_info* _Lti2_1) {
memcpy((*_Lti_0)._Fref_v, (*_Lti2_1)._Fref_v, _Mglc_Ctype_info_star_limit);
(*_Lti_0)._Farray_c = (*_Lti2_1)._Farray_c;
(*_Lti_0)._Fstar_c = (*_Lti2_1)._Fstar_c;
(*_Lti_0)._Fconst = (*_Lti2_1)._Fconst;
}
void _Mglc_Pfunc_stmt_add_1(struct _Mglc_Sstmt* _Ls_0) {
(*_Ls_0)._Fstmt_next = NULL;
if((*_Gdecl_func_ctx_space)._Fstmt_last == NULL) {
(*_Gdecl_func_ctx_space)._Fstmt_first = _Ls_0;
(*_Gdecl_func_ctx_space)._Fstmt_last = _Ls_0;
} else {
(*(*_Gdecl_func_ctx_space)._Fstmt_last)._Fstmt_next = _Ls_0;
(*_Gdecl_func_ctx_space)._Fstmt_last = _Ls_0;
}
}
void _Mglc_Swtr_Pbool_2(union _Mglc_Swtr* _Lw_0, bool _Lval_1) {
if(_Lval_1) {
_Mglc_Swtr_Pn1_2(_Lw_0, 1);
} else {
_Mglc_Swtr_Pn1_2(_Lw_0, 0);
}
}
void _Mglc_Emath_Pwr_2(_Mglc_Emath _Le_0, union _Mglc_Swtr* _Lw_1) {
_Mglc_Swtr_Pn1_2(_Lw_1, _Le_0);
}
void _Mglc_Ebools_Pwr_2(_Mglc_Ebools _Le_0, union _Mglc_Swtr* _Lw_1) {
_Mglc_Swtr_Pn1_2(_Lw_1, _Le_0);
}
void _Mglc_Eunary_Pwr_2(_Mglc_Eunary _Lu_0, union _Mglc_Swtr* _Lw_1) {
_Mglc_Swtr_Pn1_2(_Lw_1, _Lu_0);
}
void _Mglc_Ecompare_Pwr_2(_Mglc_Ecompare _Le_0, union _Mglc_Swtr* _Lw_1) {
_Mglc_Swtr_Pn1_2(_Lw_1, _Le_0);
}
void _Mglc_Eassign_Pwr_2(_Mglc_Eassign _Ls_0, union _Mglc_Swtr* _Lw_1) {
_Mglc_Swtr_Pn1_2(_Lw_1, _Ls_0);
}
