#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include "num.c"
#include <string.h>
#define _Nglc_Chash_table_size (64)
#define _Nglc_Nfunc_Cnil (-1)
#define _Nglc_Ninclude_Cnil (-1)
#define _Nstdc_Nexit_Csuccess 0
#define _Nstdc_Nexit_Cfailure (_Nstdc_Nexit_Csuccess + 1)
#define _Nglc_Nname_type_Cmodule 0
#define _Nglc_Nname_type_Cstruct_enum (_Nglc_Nname_type_Cmodule + 1)
#define _Nglc_Nname_type_Cbasic (_Nglc_Nname_type_Cstruct_enum + 1)
#define _Nglc_Nat_Cnil (-1)
#define _Nglc_Nbasic_type_id_Croot 0
#define _Nglc_Nbasic_type_id_Crelative (_Nglc_Nbasic_type_id_Croot + 1)
#define _Nglc_Ctype_info_star_limit (8)
#define _Nglc_Cexpr_carg_group_limit (4)
#define _Nglc_Ntoken_Cnil 0
#define _Nglc_Ntoken_Cplus (_Nglc_Ntoken_Cnil + 1)
#define _Nglc_Ntoken_Cminus (_Nglc_Ntoken_Cplus + 1)
#define _Nglc_Ntoken_Cspace (_Nglc_Ntoken_Cminus + 1)
#define _Nglc_Ntoken_Cid_lparen (_Nglc_Ntoken_Cspace + 1)
#define _Nglc_Ntoken_Cid_colon (_Nglc_Ntoken_Cid_lparen + 1)
#define _Nglc_Ntoken_Cid_quote (_Nglc_Ntoken_Cid_colon + 1)
#define _Nglc_Ntoken_Cid_hash (_Nglc_Ntoken_Cid_quote + 1)
#define _Nglc_Ntoken_Clcbrace (_Nglc_Ntoken_Cid_hash + 1)
#define _Nglc_Ntoken_Cid (_Nglc_Ntoken_Clcbrace + 1)
#define _Nglc_Ntoken_Cspace_at_real_name_str (_Nglc_Ntoken_Cid + 1)
#define _Nglc_Ntoken_Cspace_at_real_name (_Nglc_Ntoken_Cspace_at_real_name_str + 1)
#define _Nglc_Ntoken_Cspace_at_no_decl (_Nglc_Ntoken_Cspace_at_real_name + 1)
#define _Nglc_Ntoken_Cspace_equal_space (_Nglc_Ntoken_Cspace_at_no_decl + 1)
#define _Nglc_Ntoken_Cinclude (_Nglc_Ntoken_Cspace_equal_space + 1)
#define _Nglc_Ntoken_Cspace_rcbrace (_Nglc_Ntoken_Cinclude + 1)
#define _Nglc_Ntoken_Cquote (_Nglc_Ntoken_Cspace_rcbrace + 1)
#define _Nglc_Ntoken_Cgrave (_Nglc_Ntoken_Cquote + 1)
#define _Nglc_Ntoken_Cid_bslash (_Nglc_Ntoken_Cgrave + 1)
#define _Nglc_Ntoken_Clcbrace_at_lparen (_Nglc_Ntoken_Cid_bslash + 1)
#define _Nglc_Ntoken_Crparen (_Nglc_Ntoken_Clcbrace_at_lparen + 1)
#define _Nglc_Ntoken_Clcbrace_cvar_space (_Nglc_Ntoken_Crparen + 1)
#define _Nglc_Ntoken_Crcbrace (_Nglc_Ntoken_Clcbrace_cvar_space + 1)
#define _Nglc_Ntoken_Cend (_Nglc_Ntoken_Crcbrace + 1)
#define _Nglc_Ntoken_Clcbrace_using_space (_Nglc_Ntoken_Cend + 1)
#define _Nglc_Ntoken_Clparen (_Nglc_Ntoken_Clcbrace_using_space + 1)
#define _Nglc_Ntoken_Clparen_space (_Nglc_Ntoken_Clparen + 1)
#define _Nglc_Ntoken_Cspace_rparen (_Nglc_Ntoken_Clparen_space + 1)
#define _Nglc_Ntoken_Ccomma_space_rparen (_Nglc_Ntoken_Cspace_rparen + 1)
#define _Nglc_Ntoken_Ccomma_space_rcbrace (_Nglc_Ntoken_Ccomma_space_rparen + 1)
#define _Nglc_Ntoken_Cscolon_space_rcbrace (_Nglc_Ntoken_Ccomma_space_rcbrace + 1)
#define _Nglc_Ntoken_Clbracket (_Nglc_Ntoken_Cscolon_space_rcbrace + 1)
#define _Nglc_Ntoken_Clbracket_space (_Nglc_Ntoken_Clbracket + 1)
#define _Nglc_Ntoken_Crbracket (_Nglc_Ntoken_Clbracket_space + 1)
#define _Nglc_Ntoken_Cspace_rbracket (_Nglc_Ntoken_Crbracket + 1)
#define _Nglc_Ntoken_Ccomma_space_rbracket (_Nglc_Ntoken_Cspace_rbracket + 1)
#define _Nglc_Ntoken_Cgrave_this (_Nglc_Ntoken_Ccomma_space_rbracket + 1)
#define _Nglc_Ntoken_Ccomma_space (_Nglc_Ntoken_Cgrave_this + 1)
#define _Nglc_Ntoken_Cspace_at_main (_Nglc_Ntoken_Ccomma_space + 1)
#define _Nglc_Ntoken_Cspace_at_case (_Nglc_Ntoken_Cspace_at_main + 1)
#define _Nglc_Ntoken_Cdot (_Nglc_Ntoken_Cspace_at_case + 1)
#define _Nglc_Ntoken_Cspace_at_process (_Nglc_Ntoken_Cdot + 1)
#define _Nglc_Ntoken_Cspace_at_inline (_Nglc_Ntoken_Cspace_at_process + 1)
#define _Nglc_Ntoken_Cspace_at_cgl_name (_Nglc_Ntoken_Cspace_at_inline + 1)
#define _Nglc_Ntoken_Cspace_at_decl (_Nglc_Ntoken_Cspace_at_cgl_name + 1)
#define _Nglc_Ntoken_Cstring (_Nglc_Ntoken_Cspace_at_decl + 1)
#define _Nglc_Ntoken_Cspace_at_var_args (_Nglc_Ntoken_Cstring + 1)
#define _Nglc_Ntoken_Cspace_at_no_body (_Nglc_Ntoken_Cspace_at_var_args + 1)
#define _Nglc_Ntoken_Cgrave_ref (_Nglc_Ntoken_Cspace_at_no_body + 1)
#define _Nglc_Ntoken_Cgrave_bool (_Nglc_Ntoken_Cgrave_ref + 1)
#define _Nglc_Ntoken_Cgrave_char (_Nglc_Ntoken_Cgrave_bool + 1)
#define _Nglc_Ntoken_Cgrave_tint (_Nglc_Ntoken_Cgrave_char + 1)
#define _Nglc_Ntoken_Cgrave_tnum (_Nglc_Ntoken_Cgrave_tint + 1)
#define _Nglc_Ntoken_Cgrave_int (_Nglc_Ntoken_Cgrave_tnum + 1)
#define _Nglc_Ntoken_Cgrave_num (_Nglc_Ntoken_Cgrave_int + 1)
#define _Nglc_Ntoken_Cgrave_float (_Nglc_Ntoken_Cgrave_num + 1)
#define _Nglc_Ntoken_Cgrave_size (_Nglc_Ntoken_Cgrave_float + 1)
#define _Nglc_Ntoken_Cgrave_lnum (_Nglc_Ntoken_Cgrave_size + 1)
#define _Nglc_Ntoken_Campersand (_Nglc_Ntoken_Cgrave_lnum + 1)
#define _Nglc_Ntoken_Cnum_dec (_Nglc_Ntoken_Campersand + 1)
#define _Nglc_Ntoken_Cnum_hex (_Nglc_Ntoken_Cnum_dec + 1)
#define _Nglc_Ntoken_Cnum_oct (_Nglc_Ntoken_Cnum_hex + 1)
#define _Nglc_Ntoken_Cchar1 (_Nglc_Ntoken_Cnum_oct + 1)
#define _Nglc_Ntoken_Cchar2 (_Nglc_Ntoken_Cchar1 + 1)
#define _Nglc_Nid_Cnil (-1)
#define _Nglc_Nid_C0 (_Nglc_Nid_Cnil + 1)
#define _Nglc_Nexpr_i_Cnil (-1)
#define _Nglc_Nexpr_i_C0 (_Nglc_Nexpr_i_Cnil + 1)
#define _Nglc_Nassign_Ceq 0
#define _Nglc_Nmath_Cadd 0
#define _Nglc_Nbools_Cand 0
#define _Nglc_Ninclude_C0 (_Nglc_Ninclude_Cnil + 1)
#define _Nglc_Nbasic_type_id_Cref (_Nglc_Nbasic_type_id_Crelative + 1)
#define _Nglc_Nbasic_type_id_Cbool (_Nglc_Nbasic_type_id_Cref + 1)
#define _Nglc_Nbasic_type_id_Cchar (_Nglc_Nbasic_type_id_Cbool + 1)
#define _Nglc_Nbasic_type_id_Ci8 (_Nglc_Nbasic_type_id_Cchar + 1)
#define _Nglc_Nbasic_type_id_Cu8 (_Nglc_Nbasic_type_id_Ci8 + 1)
#define _Nglc_Nbasic_type_id_Ci32 (_Nglc_Nbasic_type_id_Cu8 + 1)
#define _Nglc_Nexpr_int_Cdec 0
#define _Nglc_Nunary_Cneg 0
#define _Nglc_Ncompare_Ceq 0
#define _Nglc_Ncvar_flags_Cset_expr (1)
#define _Nglc_Ncvar_flags_C0 0
#define _Nglc_Nenum_flags_Creal_name (1)
#define _Nglc_Nenum_flags_C0 0
#define _Nglc_Nstruct_flags_Creal_name (1)
#define _Nglc_Nstruct_flags_C0 0
#define _Nglc_Nfunc_flags_Cinline (2)
#define _Nglc_Nfunc_flags_Chas_body (1)
#define _Nglc_Nfunc_flags_Creal_name (64)
#define _Nglc_Nfunc_flags_C0 0
#define _Nglc_Nfunc_flags_Ccase (128)
#define _Nglc_Nfunc_flags_Cdecl (512)
#define _Nglc_Nfunc_flags2_C0 0
#define _Nglc_Nfunc_flags2_Cmain (1)
#define _Nglc_Nat_Croot (_Nglc_Nat_Cnil + 1)
#define _Nglc_Nvar_flags_C0 0
#define _Nglc_Nvar_flags_Creal_name (1)
#define _Nglc_Nvar_flags_Cextern (2)
#define _Nglc_Nvar_flags_Cno_decl (4)
#define _Nglc_Cexpr_call_nest_limit (8)
#define _Nglc_Nexpr_type_Cnil 0
#define _Nglc_Nexpr_type_Ccall_method (_Nglc_Nexpr_type_Cnil + 1)
#define _Nglc_Nexpr_type_Clvar (_Nglc_Nexpr_type_Ccall_method + 1)
#define _Nglc_Nexpr_type_Cgvar (_Nglc_Nexpr_type_Clvar + 1)
#define _Nglc_Nexpr_type_Cmath (_Nglc_Nexpr_type_Cgvar + 1)
#define _Nglc_Nexpr_type_Cassign (_Nglc_Nexpr_type_Cmath + 1)
#define _Nglc_Nexpr_type_Cbools (_Nglc_Nexpr_type_Cassign + 1)
#define _Nglc_Nexpr_type_Cfunc (_Nglc_Nexpr_type_Cbools + 1)
#define _Nglc_Cglc_carg_limit (64)
#define _Nglc_Nexpr_type_Cmethod (_Nglc_Nexpr_type_Cfunc + 1)
#define _Nglc_Nstmt_type_Cspace 0
#define _Nglc_Nstmt_type_Cif (_Nglc_Nstmt_type_Cspace + 1)
#define _Nglc_Nstmt_type_Cif_elif (_Nglc_Nstmt_type_Cif + 1)
#define _Nglc_Nstmt_type_Cif_else (_Nglc_Nstmt_type_Cif_elif + 1)
#define _Nglc_Nstmt_type_Cif_end (_Nglc_Nstmt_type_Cif_else + 1)
#define _Nglc_Nstmt_type_Cdo (_Nglc_Nstmt_type_Cif_end + 1)
#define _Nglc_Nstmt_type_Cdo_end (_Nglc_Nstmt_type_Cdo + 1)
#define _Nglc_Nstmt_type_Cwhile (_Nglc_Nstmt_type_Cdo_end + 1)
#define _Nglc_Nstmt_type_Cwhile_end (_Nglc_Nstmt_type_Cwhile + 1)
#define _Nglc_Nstmt_type_Cexpr (_Nglc_Nstmt_type_Cwhile_end + 1)
#define _Nglc_Nstmt_type_Creturn (_Nglc_Nstmt_type_Cexpr + 1)
#define _Nglc_Nstmt_type_Ccontinue (_Nglc_Nstmt_type_Creturn + 1)
#define _Nglc_Nstmt_type_Cbreak (_Nglc_Nstmt_type_Ccontinue + 1)
#define _Nglc_Nfunc_flags_Ccgl_name (256)
#define _Nglc_Nfunc_flags_Cprocess (4)
#define _Nglc_Nfunc_flags_Cvar_args (8)
#define _Nglc_Nfunc_flags_Cno_decl (16)
#define _Nglc_Nfunc_flags_Cno_body (32)
#define _Nglc_Nlvar_Cnil (-1)
#define _Nglc_Nstmt_space_flags_Cskip_lvar_decl (1)
#define _Nglc_Nstmt_space_flags_C0 0
#define _Nglc_Nexpr_type_Cfvar (_Nglc_Nexpr_type_Cmethod + 1)
#define _Nglc_Cdecl_at_nest_limit (8)
#define _Nglc_Nat_Crelative (_Nglc_Nat_Croot + 1)
#define _Nglc_Nexpr_type_Ci32 (_Nglc_Nexpr_type_Cfvar + 1)
#define _Nglc_Nexpr_type_Ccvar (_Nglc_Nexpr_type_Ci32 + 1)
#define _Nglc_Nexpr_type_Cstr (_Nglc_Nexpr_type_Ccvar + 1)
#define _Nglc_Nexpr_type_Cindex (_Nglc_Nexpr_type_Cstr + 1)
#define _Nglc_Nexpr_type_Cunary (_Nglc_Nexpr_type_Cindex + 1)
#define _Nglc_Nexpr_type_Ccompare (_Nglc_Nexpr_type_Cunary + 1)
#define _Nglc_Nexpr_type_Cbool (_Nglc_Nexpr_type_Ccompare + 1)
#define _Nglc_Nexpr_type_Cnull (_Nglc_Nexpr_type_Cbool + 1)
#define _Nglc_Nexpr_type_Ccast_fast (_Nglc_Nexpr_type_Cnull + 1)
#define _Nglc_Nexpr_type_Cref (_Nglc_Nexpr_type_Ccast_fast + 1)
#define _Nglc_Nexpr_type_Cchar (_Nglc_Nexpr_type_Cref + 1)
#define _Nglc_Nexpr_type_Csize_of_type (_Nglc_Nexpr_type_Cchar + 1)
#define _Nglc_Ncvar_Cnil (-1)
#define _Nglc_Ncvar_flags_Cas_enum (2)
#define _Nglc_Nstruct_flags_Cunion (4)
#define _Nglc_Nstruct_flags_Cno_decl (2)
#define _Nglc_Nstmt_type_Cswitch (_Nglc_Nstmt_type_Cbreak + 1)
#define _Nglc_Nstmt_type_Ccase (_Nglc_Nstmt_type_Cswitch + 1)
#define _Nglc_Nstmt_type_Cdefault (_Nglc_Nstmt_type_Ccase + 1)
#define _Nglc_Nstmt_type_Ccase_end (_Nglc_Nstmt_type_Cdefault + 1)
#define _Nglc_Nstmt_type_Cdefault_end (_Nglc_Nstmt_type_Ccase_end + 1)
#define _Nglc_Nstmt_type_Cswitch_end (_Nglc_Nstmt_type_Cdefault_end + 1)
#define _Nglc_Cdebug_rd_wr (true)
#define _Nglc_Nfunc_C0 (_Nglc_Nfunc_Cnil + 1)
#define _Nglc_Nfunc_C1 (_Nglc_Nfunc_C0 + 1)
#define _Nglc_Nlvar_flags_Cset_expr (1)
#define _Nglc_Nlvar_flags_C0 0
#define _Nglc_Nstmt_type_Cnil (255)
#define _Nglc_Cdecl_var_size_limit (8)
#define _Nglc_Ntoken_Ctrue (_Nglc_Ntoken_Cchar2 + 1)
#define _Nglc_Ntoken_Cfalse (_Nglc_Ntoken_Ctrue + 1)
#define _Nglc_Ntoken_Cnull (_Nglc_Ntoken_Cfalse + 1)
#define _Nglc_Ntoken_Clparen_amp_amp_comma_space (_Nglc_Ntoken_Cnull + 1)
#define _Nglc_Ntoken_Clparen_pipe_pipe_comma_space (_Nglc_Ntoken_Clparen_amp_amp_comma_space + 1)
#define _Nglc_Ntoken_Cspace_plus_space (_Nglc_Ntoken_Clparen_pipe_pipe_comma_space + 1)
#define _Nglc_Ntoken_Cspace_minus_space (_Nglc_Ntoken_Cspace_plus_space + 1)
#define _Nglc_Ntoken_Cspace_mul_space (_Nglc_Ntoken_Cspace_minus_space + 1)
#define _Nglc_Ntoken_Cspace_div_space (_Nglc_Ntoken_Cspace_mul_space + 1)
#define _Nglc_Ntoken_Cspace_langle_langle_space (_Nglc_Ntoken_Cspace_div_space + 1)
#define _Nglc_Ntoken_Cspace_rangle_rangle_space (_Nglc_Ntoken_Cspace_langle_langle_space + 1)
#define _Nglc_Ntoken_Cspace_amp_space (_Nglc_Ntoken_Cspace_rangle_rangle_space + 1)
#define _Nglc_Ntoken_Cspace_pipe_space (_Nglc_Ntoken_Cspace_amp_space + 1)
#define _Nglc_Ntoken_Cspace_xor_space (_Nglc_Ntoken_Cspace_pipe_space + 1)
#define _Nglc_Ntoken_Cspace_equal_equal_space (_Nglc_Ntoken_Cspace_xor_space + 1)
#define _Nglc_Ntoken_Cspace_expoint_equal_space (_Nglc_Ntoken_Cspace_equal_equal_space + 1)
#define _Nglc_Ntoken_Cspace_langle_space (_Nglc_Ntoken_Cspace_expoint_equal_space + 1)
#define _Nglc_Ntoken_Cspace_langle_equal_space (_Nglc_Ntoken_Cspace_langle_space + 1)
#define _Nglc_Ntoken_Cspace_rangle_space (_Nglc_Ntoken_Cspace_langle_equal_space + 1)
#define _Nglc_Ntoken_Cspace_rangle_equal_space (_Nglc_Ntoken_Cspace_rangle_space + 1)
#define _Nglc_Ntoken_Chash (_Nglc_Ntoken_Cspace_rangle_equal_space + 1)
#define _Nglc_Ntoken_Cspace_plus_equal_space (_Nglc_Ntoken_Chash + 1)
#define _Nglc_Ntoken_Cspace_minus_equal_space (_Nglc_Ntoken_Cspace_plus_equal_space + 1)
#define _Nglc_Ntoken_Cspace_mul_equal_space (_Nglc_Ntoken_Cspace_minus_equal_space + 1)
#define _Nglc_Ntoken_Cspace_div_equal_space (_Nglc_Ntoken_Cspace_mul_equal_space + 1)
#define _Nglc_Ntoken_Cspace_lshift_equal_space (_Nglc_Ntoken_Cspace_div_equal_space + 1)
#define _Nglc_Ntoken_Cspace_rshift_equal_space (_Nglc_Ntoken_Cspace_lshift_equal_space + 1)
#define _Nglc_Ntoken_Cspace_and_equal_space (_Nglc_Ntoken_Cspace_rshift_equal_space + 1)
#define _Nglc_Ntoken_Cspace_or_equal_space (_Nglc_Ntoken_Cspace_and_equal_space + 1)
#define _Nglc_Ntoken_Cspace_xor_equal_space (_Nglc_Ntoken_Cspace_or_equal_space + 1)
#define _Nglc_Ntoken_Cspace_colon_equal_space (_Nglc_Ntoken_Cspace_xor_equal_space + 1)
#define _Nglc_Ntoken_Cexpoint (_Nglc_Ntoken_Cspace_colon_equal_space + 1)
#define _Nglc_Ntoken_Clcbrace_do (_Nglc_Ntoken_Cexpoint + 1)
#define _Nglc_Ntoken_Clcbrace_while (_Nglc_Ntoken_Clcbrace_do + 1)
#define _Nglc_Ntoken_Clcbrace_if (_Nglc_Ntoken_Clcbrace_while + 1)
#define _Nglc_Ntoken_Clcbrace_elif (_Nglc_Ntoken_Clcbrace_if + 1)
#define _Nglc_Ntoken_Clcbrace_else (_Nglc_Ntoken_Clcbrace_elif + 1)
#define _Nglc_Ntoken_Clcbrace_switch (_Nglc_Ntoken_Clcbrace_else + 1)
#define _Nglc_Ntoken_Cspace_at_fall_through (_Nglc_Ntoken_Clcbrace_switch + 1)
#define _Nglc_Ntoken_Clcbrace_case (_Nglc_Ntoken_Cspace_at_fall_through + 1)
#define _Nglc_Ntoken_Clcbrace_default (_Nglc_Ntoken_Clcbrace_case + 1)
#define _Nglc_Ntoken_Ccontinue (_Nglc_Ntoken_Clcbrace_default + 1)
#define _Nglc_Ntoken_Cbreak (_Nglc_Ntoken_Ccontinue + 1)
#define _Nglc_Ntoken_Creturn (_Nglc_Ntoken_Cbreak + 1)
#define _Nglc_Ntoken_Clcbrace_plus_or_space (_Nglc_Ntoken_Creturn + 1)
#define _Nglc_Ntoken_Cspace_at_extern (_Nglc_Ntoken_Clcbrace_plus_or_space + 1)
#define _Nglc_Ntoken_Cscolon_space (_Nglc_Ntoken_Cspace_at_extern + 1)
#define _Nglc_Ntoken_Cspace_at_union (_Nglc_Ntoken_Cscolon_space + 1)
#define _Nglc_Ntoken_Clcbrace_gvar_space (_Nglc_Ntoken_Cspace_at_union + 1)
typedef int32_t _Nglc_Nfunc;
typedef int32_t _Nglc_Ninclude;
typedef int32_t _Nstdc_Nfd;
typedef int32_t _Nstdc_Nopen_flags;
typedef int32_t _Nstdc_Nexit;
typedef int32_t _Nstdc_Nseek;
typedef int32_t _Nglc_Nat;
typedef uint8_t _Nglc_Nname_type;
typedef int32_t _Nglc_Nid;
typedef uint8_t _Nglc_Nbasic_type_id;
typedef uint32_t _Nglc_Nfunc_flags;
typedef uint32_t _Nglc_Nvar_flags;
typedef int32_t _Nglc_Nexpr_i;
typedef uint8_t _Nglc_Nstmt_type;
typedef uint8_t _Nglc_Nstmt_space_flags;
typedef int32_t _Nglc_Nlvar;
typedef uint8_t _Nglc_Nlvar_flags;
typedef int32_t _Nglc_Nstruct;
typedef uint8_t _Nglc_Nstruct_flags;
typedef uint32_t _Nglc_Ntoken;
typedef uint8_t _Nglc_Nassign;
typedef uint8_t _Nglc_Nmath;
typedef uint8_t _Nglc_Nbools;
typedef uint8_t _Nglc_Nexpr_int;
typedef uint8_t _Nglc_Nunary;
typedef uint8_t _Nglc_Ncompare;
typedef int32_t _Nglc_Ncvar;
typedef uint8_t _Nglc_Ncvar_flags;
typedef int32_t _Nglc_Ngvar;
typedef uint8_t _Nglc_Ngvar_flags;
typedef int32_t _Nglc_Nenum;
typedef uint8_t _Nglc_Nenum_flags;
typedef uint32_t _Nglc_Nfunc_flags2;
typedef uint8_t _Nglc_Nexpr_type;
typedef uint8_t _Nglc_Nexpr_flags;
typedef int32_t _Nglc_Nalias;
struct _Nglc_Nmap;
struct _Nglc_Nmap {
uint64_t _Fdata[(_Nglc_Chash_table_size + 7) >> 3];
};
struct _Nglc_Nat_map;
struct _Nglc_Nat_map {
uint64_t _Fdata[(_Nglc_Chash_table_size + 7) >> 3];
};
struct _Nsys_Ntimespec;
struct _Nsys_Ntimespec {
uint32_t tv_sec;
uint32_t tv_nsec;
};
union _Nglc_Nrdr;
union _Nglc_Nrdr {
void* _Fref;
size_t _Fpos;
uint8_t* _Fp1;
char* _Fchar;
uint32_t* _Fp4;
};
union _Nglc_Nwtr;
union _Nglc_Nwtr {
void* _Fref;
size_t _Fpos;
uint8_t* _Fp1;
uint32_t* _Fp4;
};
union _Nglc_Nat_name;
union _Nglc_Nat_name {
_Nglc_Nid _Fid;
_Nglc_Nbasic_type_id _Fbasic;
};
struct _Nglc_Nat_data;
struct _Nglc_Nat_data {
_Nglc_Nname_type _Ftype;
_Nglc_Nat _Fparent;
union _Nglc_Nat_name _Fname;
};
struct _Nglc_Ntype_info;
struct _Nglc_Ntype_info {
int8_t _Fref_v[_Nglc_Ctype_info_star_limit];
int8_t _Farray_c;
int8_t _Fstar_c;
bool _Fbuilt_in;
bool _Fconst;
};
struct _Nglc_Ndecl_var_data;
struct _Nglc_Ndecl_var_data {
_Nglc_Nid _Fname;
_Nglc_Nat _Ftype;
_Nglc_Nvar_flags _Fflags;
_Nglc_Nid _Freal_name;
struct _Nglc_Ntype_info _Ftype_info;
uint8_t _Fsize_c;
_Nglc_Nexpr_i* _Fsize_expr_v;
};
struct _Nglc_Nstmt;
struct _Nglc_Nstmt {
int32_t _Fbegin_row;
int32_t _Fbegin_col;
int32_t _Fend_row;
int32_t _Fend_col;
_Nglc_Nstmt_type _Ftype;
struct _Nglc_Nstmt* _Fstmt_next;
};
struct _Nglc_Nstmt_space;
struct _Nglc_Nstmt_space {
struct _Nglc_Nstmt _Fbase;
struct _Nglc_Nstmt_space* _Fparent;
_Nglc_Nstmt_space_flags _Fflags;
struct _Nglc_Nstmt* _Fstmt_first;
struct _Nglc_Nstmt* _Fstmt_last;
int32_t _Flvar_c;
int32_t _Flvar_cap;
_Nglc_Nlvar* _Flvar_v;
};
struct _Nglc_Nlvar_data;
struct _Nglc_Nlvar_data {
int32_t _Frow;
int32_t _Fcol;
struct _Nglc_Ndecl_var_data _Fdecl;
_Nglc_Nlvar_flags _Fflags;
_Nglc_Nexpr_i _Fset_expr;
};
struct _Nglc_Nfarg;
struct _Nglc_Nfarg {
int32_t _Frow;
int32_t _Fcol;
struct _Nglc_Ndecl_var_data _Fdecl;
};
struct _Nglc_Ndecl_func;
struct _Nglc_Ndecl_func {
int32_t _Fbegin_row;
int32_t _Fbegin_col;
int32_t _Fend_row;
int32_t _Fend_col;
_Nglc_Ninclude _Finclude;
_Nglc_Nat _Fat;
_Nglc_Nfunc_flags _Fflags;
_Nglc_Nid _Freal_name;
char* _Fdecl_str;
int32_t _Fdecl_len;
_Nglc_Nid _Fcase;
struct _Nglc_Ndecl_var_data _Fdecl;
struct _Nglc_Nstmt_space* _Fstmt_space;
_Nglc_Nlvar _Flvar_c;
_Nglc_Nlvar _Flvar_cap;
struct _Nglc_Nlvar_data** _Flvar_v;
int8_t _Fthis_idx;
int8_t _Fthis_group;
int8_t _Fgroup_c;
int8_t _Fgroup_v[_Nglc_Cexpr_carg_group_limit];
uint8_t _Ffarg_c;
struct _Nglc_Nfarg _Ffarg_v[0];
};
struct _Nglc_Nfvar_data;
struct _Nglc_Nfvar_data {
struct _Nglc_Ndecl_var_data _Fdecl;
};
struct _Nglc_Nstruct_data;
struct _Nglc_Nstruct_data {
int32_t _Fbegin_row;
int32_t _Fbegin_col;
int32_t _Fend_row;
int32_t _Fend_col;
_Nglc_Ninclude _Finclude;
_Nglc_Nat _Fat;
_Nglc_Nstruct_flags _Fflags;
_Nglc_Nid _Freal_name;
uint32_t _Ffvar_c;
struct _Nglc_Nfvar_data _Ffvar_v[0];
};
struct _Nglc_Nparser;
struct _Nglc_Nparser {
};
struct _Nglc_Nlexer;
struct _Nglc_Nlexer {
uint8_t* _Fcontent;
uint8_t* _Fstart;
uint8_t* _Fcursor;
uint8_t* _Flimit;
uint8_t* _Fmarker;
uint8_t* _Fctx_marker;
};
struct _Nglc_Ntoken_data;
struct _Nglc_Ntoken_data {
int32_t _Frow;
int32_t _Fcol;
int32_t _Fid;
int32_t _Fid2;
int32_t _Fval[12];
};
struct _Nglc_Ncvar_data;
struct _Nglc_Ncvar_data {
int32_t _Frow;
int32_t _Fcol;
_Nglc_Ninclude _Finclude;
_Nglc_Nat _Fat;
_Nglc_Ncvar_flags _Fflags;
struct _Nglc_Ndecl_var_data _Fdecl;
_Nglc_Nexpr_i _Fexpr_set;
_Nglc_Ncvar _Flast_cvar;
};
struct _Nglc_Ndecl_gvar;
struct _Nglc_Ndecl_gvar {
int32_t _Frow;
int32_t _Fcol;
_Nglc_Ninclude _Finclude;
_Nglc_Nat _Fat;
_Nglc_Ngvar_flags _Fflags;
struct _Nglc_Ndecl_var_data _Fdecl;
};
struct _Nglc_Nenum_data;
struct _Nglc_Nenum_data {
int32_t _Fbegin_row;
int32_t _Fbegin_col;
int32_t _Fend_row;
int32_t _Fend_col;
_Nglc_Ninclude _Finclude;
_Nglc_Nat _Fat;
_Nglc_Nat _Fbase_type;
_Nglc_Nenum_flags _Fflags;
_Nglc_Nid _Freal_name;
};
struct _Nglc_Nexpr;
struct _Nglc_Nexpr {
_Nglc_Nexpr_type _Ftype;
_Nglc_Nexpr_flags _Fflags;
};
struct _Nglc_Ncarg;
struct _Nglc_Ncarg {
int8_t _Fref;
_Nglc_Nexpr_i _Fexpr;
};
struct _Nglc_Nexpr_func;
struct _Nglc_Nexpr_func {
struct _Nglc_Nexpr _Fbase;
_Nglc_Nat _Fat;
_Nglc_Nid _Ffunc_name;
uint8_t _Fgroup_c;
uint8_t _Fgroup_v[_Nglc_Cexpr_carg_group_limit];
uint8_t _Fcarg_c;
struct _Nglc_Ncarg _Fcarg_v[0];
};
struct _Nglc_Nexpr_method;
struct _Nglc_Nexpr_method {
struct _Nglc_Nexpr _Fbase;
_Nglc_Nexpr_i _Fthis;
_Nglc_Nid _Ffunc_name;
uint8_t _Fgroup_c;
uint8_t _Fgroup_v[_Nglc_Cexpr_carg_group_limit];
uint8_t _Fcarg_c;
struct _Nglc_Ncarg _Fcarg_v[0];
};
struct _Nglc_Nexpr_str_node;
struct _Nglc_Nexpr_str_node {
struct _Nglc_Nexpr_str_node* _Fnext;
int32_t _Flen;
char _Fbuf[0];
};
struct _Nglc_Nexpr_str;
struct _Nglc_Nexpr_str {
struct _Nglc_Nexpr _Fbase;
int32_t _Fnode_c;
struct _Nglc_Nexpr_str_node* _Ffirst;
struct _Nglc_Nexpr_str_node* _Flast;
};
struct _Nglc_Nstmt_expr;
struct _Nglc_Nstmt_expr {
struct _Nglc_Nstmt _Fbase;
_Nglc_Nexpr_i _Fexpr;
};
struct _Nglc_Nvalue;
struct _Nglc_Nvalue {
int8_t _Fref;
bool _Fparen;
_Nglc_Nat _Ftype;
struct _Nglc_Ntype_info _Finfo;
};
struct _Nglc_Nstmt_return;
struct _Nglc_Nstmt_return {
struct _Nglc_Nstmt _Fbase;
_Nglc_Nexpr_i _Fexpr;
struct _Nglc_Nvalue _Fval;
};
struct _Nglc_Nstmt_continue;
struct _Nglc_Nstmt_continue {
struct _Nglc_Nstmt _Fbase;
uint8_t _Fnest;
};
struct _Nglc_Nstmt_break;
struct _Nglc_Nstmt_break {
struct _Nglc_Nstmt _Fbase;
uint8_t _Fnest;
};
struct _Nglc_Nexpr_lvar;
struct _Nglc_Nexpr_lvar {
struct _Nglc_Nexpr _Fbase;
_Nglc_Nlvar _Flvar;
};
struct _Nglc_Nexpr_gvar;
struct _Nglc_Nexpr_gvar {
struct _Nglc_Nexpr _Fbase;
_Nglc_Nat _Fat;
_Nglc_Nid _Fname;
};
struct _Nglc_Nexpr_fvar;
struct _Nglc_Nexpr_fvar {
struct _Nglc_Nexpr _Fbase;
_Nglc_Nexpr_i _Fexpr;
_Nglc_Nid _Fmember;
};
struct _Nglc_Nexpr_assign;
struct _Nglc_Nexpr_assign {
struct _Nglc_Nexpr _Fbase;
_Nglc_Nexpr_i _Fleft;
_Nglc_Nexpr_i _Fright;
_Nglc_Nassign _Ftype;
};
struct _Nglc_Nexpr_math_item;
struct _Nglc_Nexpr_math_item {
_Nglc_Nexpr_i _Fexpr;
};
struct _Nglc_Nexpr_math;
struct _Nglc_Nexpr_math {
struct _Nglc_Nexpr _Fbase;
_Nglc_Nexpr_i _Fleft;
_Nglc_Nexpr_i _Fright;
_Nglc_Nmath _Ftype;
uint8_t _Fitem_c;
uint8_t _Fitem_cap;
struct _Nglc_Nexpr_math_item* _Fitem_v;
};
struct _Nglc_Nexpr_bools_item;
struct _Nglc_Nexpr_bools_item {
_Nglc_Nexpr_i _Fexpr;
};
struct _Nglc_Nexpr_bools;
struct _Nglc_Nexpr_bools {
struct _Nglc_Nexpr _Fbase;
_Nglc_Nexpr_i _Fleft;
_Nglc_Nexpr_i _Fright;
_Nglc_Nbools _Ftype;
uint8_t _Fitem_c;
uint8_t _Fitem_cap;
struct _Nglc_Nexpr_bools_item* _Fitem_v;
};
struct _Nglc_Nrow_col;
struct _Nglc_Nrow_col {
int32_t _Frow;
int32_t _Fcol;
};
struct _Nglc_Nexpr_int_data;
struct _Nglc_Nexpr_int_data {
struct _Nglc_Nexpr _Fbase;
int32_t _Fvalue;
_Nglc_Nexpr_int _Ftype;
};
struct _Nglc_Nexpr_size_of_type;
struct _Nglc_Nexpr_size_of_type {
struct _Nglc_Nexpr _Fbase;
_Nglc_Nat _Ftype;
};
struct _Nglc_Nexpr_null;
struct _Nglc_Nexpr_null {
struct _Nglc_Nexpr _Fbase;
};
struct _Nglc_Nexpr_cvar;
struct _Nglc_Nexpr_cvar {
struct _Nglc_Nexpr _Fbase;
_Nglc_Nat _Fat;
_Nglc_Nid _Fname;
};
struct _Nglc_Nexpr_unary;
struct _Nglc_Nexpr_unary {
struct _Nglc_Nexpr _Fbase;
_Nglc_Nexpr_i _Fexpr;
_Nglc_Nunary _Ftype;
};
struct _Nglc_Nexpr_ref;
struct _Nglc_Nexpr_ref {
struct _Nglc_Nexpr _Fbase;
_Nglc_Nexpr_i _Fexpr;
};
struct _Nglc_Nexpr_cast_fast;
struct _Nglc_Nexpr_cast_fast {
struct _Nglc_Nexpr _Fbase;
_Nglc_Nexpr_i _Fexpr;
_Nglc_Nat _Ftype;
};
struct _Nglc_Nexpr_index;
struct _Nglc_Nexpr_index {
struct _Nglc_Nexpr _Fbase;
_Nglc_Nexpr_i _Fleft;
_Nglc_Nexpr_i _Fright;
};
struct _Nglc_Nstmt_switch;
struct _Nglc_Nstmt_switch {
struct _Nglc_Nstmt _Fbase;
_Nglc_Nexpr_i _Fexpr;
_Nglc_Nexpr_i _Fcases;
};
struct _Nglc_Nstmt_case_item;
struct _Nglc_Nstmt_case_item {
_Nglc_Nexpr_i _Fexpr;
};
struct _Nglc_Nstmt_case;
struct _Nglc_Nstmt_case {
struct _Nglc_Nstmt _Fbase;
bool _Ffall_through;
uint32_t _Fexpr_c;
struct _Nglc_Nstmt_case_item _Fexpr_v[0];
};
struct _Nglc_Nstmt_case_end;
struct _Nglc_Nstmt_case_end {
struct _Nglc_Nstmt _Fbase;
};
struct _Nglc_Nstmt_default;
struct _Nglc_Nstmt_default {
struct _Nglc_Nstmt _Fbase;
bool _Ffall_through;
};
struct _Nglc_Nstmt_default_end;
struct _Nglc_Nstmt_default_end {
struct _Nglc_Nstmt _Fbase;
};
struct _Nglc_Nstmt_switch_end;
struct _Nglc_Nstmt_switch_end {
struct _Nglc_Nstmt _Fbase;
};
struct _Nglc_Nstmt_if;
struct _Nglc_Nstmt_if {
struct _Nglc_Nstmt _Fbase;
bool _Fnot;
_Nglc_Nexpr_i _Fexpr;
};
struct _Nglc_Nstmt_do_end;
struct _Nglc_Nstmt_do_end {
struct _Nglc_Nstmt _Fbase;
struct _Nglc_Nstmt_do* _Fdo;
};
struct _Nglc_Nstmt_do;
struct _Nglc_Nstmt_do {
struct _Nglc_Nstmt _Fbase;
_Nglc_Nexpr_i _Fexpr;
struct _Nglc_Nstmt_space* _Fcontinu;
struct _Nglc_Nstmt_do_end* _Fend;
};
struct _Nglc_Nstmt_while_end;
struct _Nglc_Nstmt_while_end {
struct _Nglc_Nstmt _Fbase;
struct _Nglc_Nstmt_while* _Fwhile;
};
struct _Nglc_Nstmt_while;
struct _Nglc_Nstmt_while {
struct _Nglc_Nstmt _Fbase;
_Nglc_Nexpr_i _Fexpr;
struct _Nglc_Nstmt_space* _Fcontinu;
struct _Nglc_Nstmt_while_end* _Fend;
};
union _Nglc_Nnest;
union _Nglc_Nnest {
struct _Nglc_Nstmt_do* _Fdo;
struct _Nglc_Nstmt_while* _Fwhile;
void* _Fref;
};
struct _Nglc_Nstmt_if_else;
struct _Nglc_Nstmt_if_else {
struct _Nglc_Nstmt _Fbase;
};
struct _Nglc_Nstmt_if_end;
struct _Nglc_Nstmt_if_end {
struct _Nglc_Nstmt _Fbase;
};
struct _Nglc_Nexpr_compare;
struct _Nglc_Nexpr_compare {
struct _Nglc_Nexpr _Fbase;
_Nglc_Nexpr_i _Fleft;
_Nglc_Nexpr_i _Fright;
_Nglc_Ncompare _Ftype;
};
struct _Nglc_Nexpr_bool;
struct _Nglc_Nexpr_bool {
struct _Nglc_Nexpr _Fbase;
bool _Fvalue;
};
struct _Nglc_Nexpr_char;
struct _Nglc_Nexpr_char {
struct _Nglc_Nexpr _Fbase;
char _Fvalue;
};
struct _Nglc_Nstmt_if_elif;
struct _Nglc_Nstmt_if_elif {
struct _Nglc_Nstmt _Fbase;
bool _Fnot;
_Nglc_Nexpr_i _Fexpr;
};
struct _Nglc_Nmap _Gid_map;
struct _Nglc_Nmap _Ginclude_map;
struct _Nglc_Nat_map _Gat_map;
_Nglc_Nfunc _Gfunc_main;
_Nglc_Ninclude _Gdecl_include;
char* input_path;
char* _Glock_path;
int32_t _Gid_cap;
char** _Gid_str_v;
uint8_t* _Gid_len_v;
int32_t _Ginclude_cap;
char** _Ginclude_str_v;
uint8_t* _Ginclude_len_v;
_Nglc_Nat _Gat_cap;
struct _Nglc_Nat_data* _Gat_v;
_Nglc_Nat _Gat_c;
_Nglc_Nfunc _Gfunc_cap;
struct _Nglc_Ndecl_func** _Gfunc_v;
_Nglc_Nstruct _Gstruct_cap;
struct _Nglc_Nstruct_data** _Gstruct_v;
uint32_t _Gdecl_fvar_cap;
struct _Nglc_Ndecl_var_data* _Gdecl_fvar_v;
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
uint32_t _Gpreprocess_def_c;
uint32_t _Gpreprocess_def_cap;
char** _Gpreprocess_def_str_v;
uint8_t* _Gpreprocess_def_len_v;
int32_t _Gquick_alloc_cap;
void* _Gquick_alloc_v;
int32_t _Gquick_alloc_c;
_Nglc_Ncvar _Gcvar_c;
struct _Nglc_Ncvar_data* _Gcvar_v;
_Nglc_Ngvar _Ggvar_c;
struct _Nglc_Ndecl_gvar* _Ggvar_v;
_Nglc_Nenum _Genum_c;
struct _Nglc_Nenum_data** _Genum_v;
_Nglc_Nstruct _Gstruct_c;
_Nglc_Nfunc _Gfunc_c;
_Nglc_Nid _Gdecl_func_name;
int32_t _Gdecl_func_row;
int32_t _Gdecl_func_col;
_Nglc_Nfunc_flags _Gdecl_func_flags;
_Nglc_Nfunc_flags2 _Gdecl_func_flags2;
int32_t _Gdecl_farg_c;
int8_t _Gdecl_farg_group_c;
int8_t _Gdecl_farg_group_v[_Nglc_Cexpr_carg_group_limit];
int8_t _Gdecl_func_this_idx;
int8_t _Gdecl_func_this_group;
_Nglc_Nid _Gdecl_func_real_name;
_Nglc_Nid _Gdecl_func_case;
char* _Gdecl_func_decl_str;
int32_t _Gdecl_func_decl_len;
struct _Nglc_Nstmt_space* _Gdecl_func_space;
struct _Nglc_Nstmt_space* _Gdecl_func_ctx_space;
struct _Nglc_Ndecl_func* _Gctx_func;
int32_t _Gnest_id;
_Nglc_Nat _Gdecl_at;
struct _Nglc_Ndecl_var_data _Gdecl_var;
struct _Nglc_Nfarg* _Gdecl_farg_v;
uint32_t _Gdecl_fvar_c;
int32_t _Gdecl_struct_row;
int32_t _Gdecl_struct_col;
_Nglc_Nat _Gdecl_struct_at;
_Nglc_Nstruct_flags _Gdecl_struct_flags;
_Nglc_Nid _Gdecl_struct_real_name;
int32_t _Gdecl_var_row;
int32_t _Gdecl_var_col;
int32_t _Gdecl_farg_cap;
int8_t _Gexpr_call_c;
uint8_t _Gexpr_call_carg_c[_Nglc_Cexpr_call_nest_limit];
uint8_t _Gexpr_call_cgrp_c[_Nglc_Cexpr_call_nest_limit];
uint8_t _Gexpr_call_cgrp_v[_Nglc_Cexpr_call_nest_limit][_Nglc_Cexpr_carg_group_limit];
_Nglc_Nexpr_i _Gexpr_call_carg_v[_Nglc_Cexpr_call_nest_limit][_Nglc_Cglc_carg_limit];
uint8_t _Gnest_stack_c;
extern int32_t _Gstring_len;
extern char* _Gstring_buf;
int32_t _Gdecl_include_row;
int32_t _Gdecl_include_col;
_Nglc_Nat _Gbuild_at;
_Nglc_Nat _Gdecl_at_v[_Nglc_Cdecl_at_nest_limit];
uint8_t _Gdecl_at_c;
_Nglc_Nalias _Gat_alias_c;
_Nglc_Nid* _Gat_alias_name_v;
struct _Nglc_Nrow_col* _Gat_alias_pos_v;
_Nglc_Nalias _Gat_alias_cap;
_Nglc_Nat* _Gat_alias_at_v;
bool _Gat_begin_relative_pause;
_Nglc_Ngvar _Ggvar_cap;
int32_t _Gdecl_enum_row;
int32_t _Gdecl_enum_col;
_Nglc_Nat _Gdecl_enum_at;
_Nglc_Nenum_flags _Gdecl_enum_flags;
_Nglc_Ncvar _Gdecl_enum_last_cvar;
_Nglc_Nenum _Genum_cap;
_Nglc_Ncvar _Glast_cvar;
_Nglc_Ncvar _Gcvar_cap;
uint32_t _Gswitch_expr_c;
uint32_t _Gswitch_expr_cap;
_Nglc_Nexpr_i* _Gswitch_expr_v;
int32_t _Gnest_stack_id_v[64];
union _Nglc_Nnest _Gnest_stack_ptr_v[64];
int32_t _Gexpr_c;
int32_t _Gexpr_cap;
struct _Nglc_Nexpr** _Gexpr_v;
int32_t main(int32_t _Larg_c_0, char** _Larg_v_1);
void _Nglc_Ppreprocess_def_2(char* _Lname_0, uint8_t _Llen_1);
void _Nglc_Pexport_0();
void _Nglc_Nmap_Pinit_1(struct _Nglc_Nmap* _Lm_0);
void _Nglc_Nat_map_Pinit_1(struct _Nglc_Nat_map* _Lm_0);
void _Nglc_Pquick_alloc_init_0();
bool _Nstdc_Nfd_Popen_3(_Nstdc_Nfd* _Lfile_0, char* _Lpath_1, _Nstdc_Nopen_flags _Lflags_2);
int32_t _Nstdc_Nfd_Pstat_2(_Nstdc_Nfd _Lfile_0, struct stat* _Lstat_1);
void _Nglc_Pparser_at_exit_0();
int32_t _Nstdc_Nfd_Pclose_1(_Nstdc_Nfd _Lfile_0);
void _Nglc_Pget_row_col_4(int32_t* _Lout_row_0, int32_t* _Lout_col_1, void* _Lend_2, void* _Lbegin_3);
void _Nglc_Pparse_comment_4(union _Nglc_Nrdr* _Lr_0, union _Nglc_Nwtr* _Lw_1, char _Lending_2, void* _Lin_data_3);
void _Nglc_Pparse_string_4(union _Nglc_Nrdr* _Lr_0, union _Nglc_Nwtr* _Lw_1, char _Lending_2, void* _Lin_data_3);
void _Nglc_Ppreprocess_init_0();
void _Nglc_Ppreprocess_2(void** _Lin_out_data_0, size_t* _Lin_out_size_1);
void _Nglc_Pparse_str_init_1(int32_t _Lmax_size_0);
#define _Nglc_Pmalloc_arr_2(r, c) r = malloc(sizeof(r[0]) * (c)); memset(r, 0, sizeof(r[0]) * (c))
struct _Nglc_Nparser* _Nglc_Nparser_Palloc_0();
void _Nglc_Nlexer_Pinit_3(struct _Nglc_Nlexer* _Llex_0, uint8_t* _Ldata_1, size_t _Lsize_2);
_Nglc_Ntoken glc_lexer_scan(struct _Nglc_Nlexer* _Llex_0);
int32_t _Nglc_Nlexer_Pget_id_3(struct _Nglc_Nlexer* _Llex_0, uint8_t _Lbegin_1, uint8_t _Lend_2);
void glcParse(struct _Nglc_Nparser* _Lpsr_0, _Nglc_Ntoken _Lt_1, struct _Nglc_Ntoken_data* _Ltok_2);
int32_t _Nglc_Pchar_escape_value_1(char _Lc_0);
uint32_t _Nglc_Nlexer_Pget_u32_dec_1(struct _Nglc_Nlexer* _Llex_0);
uint32_t _Nglc_Nlexer_Pget_u32_oct_1(struct _Nglc_Nlexer* _Llex_0);
int32_t _Nglc_Nlexer_Pget_include_1(struct _Nglc_Nlexer* _Llex_0);
void _Nglc_Nparser_Pfree_1(struct _Nglc_Nparser* _Lpsr_0);
void* qalloc(int32_t _Lsize_0);
void _Nglc_Nwtr_Pn1_2(union _Nglc_Nwtr* _Lw_0, uint8_t _Ln_1);
void _Nglc_Nwtr_Pcopy_3(union _Nglc_Nwtr* _Lw_0, void* _Ldata_1, int32_t _Lsize_2);
void _Nglc_Nname_type_Pwr_2(_Nglc_Nname_type _Li_0, union _Nglc_Nwtr* _Lw_1);
void _Nglc_Nbasic_type_id_Pwr_2(_Nglc_Nbasic_type_id _Le_0, union _Nglc_Nwtr* _Lw_1);
void _Nglc_Nat_Pwr_3(_Nglc_Nat _Lat_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2);
void _Nglc_Nid_Pwr_3(_Nglc_Nid _Lid_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2);
void _Nglc_Pwrite_cvar_2(union _Nglc_Nwtr* _Lw_0, bool _Lheader_1);
void _Nglc_Pwrite_gvar_2(union _Nglc_Nwtr* _Lw_0, bool _Lheader_1);
void _Nglc_Pwrite_enum_2(union _Nglc_Nwtr* _Lw_0, bool _Lheader_1);
void _Nglc_Pwrite_struct_2(union _Nglc_Nwtr* _Lw_0, bool _Lheader_1);
void _Nglc_Pwrite_func_2(union _Nglc_Nwtr* _Lw_0, bool _Lheader_1);
bool _Nstdc_Nfd_Popen_4(_Nstdc_Nfd* _Lfile_0, char* _Lpath_1, _Nstdc_Nopen_flags _Lflags_2, int32_t _Lmode_3);
void _Nglc_Nat_Pwr_header_2(_Nglc_Nat _Lid_0, union _Nglc_Nwtr* _Lw_1);
void _Nglc_Nid_Pwr_header_2(_Nglc_Nid _Lid_0, union _Nglc_Nwtr* _Lw_1);
void qalloc_undo(int32_t _Lsize_0);
void _Nglc_Pdecl_func_begin_3(_Nglc_Nid _Lname_0, int32_t _Lrow_1, int32_t _Lcol_2);
void _Nglc_Pdecl_func_end_2(int32_t _Lrow_0, int32_t _Lcol_1);
void _Nglc_Pdecl_struct_end_2(int32_t _Lrow_0, int32_t _Lcol_1);
void _Nglc_Pdecl_var_begin_3(_Nglc_Nid _Lname_0, int32_t _Lrow_1, int32_t _Lcol_2);
void _Nglc_Pdecl_var_attr_real_name_1(_Nglc_Nid _Lname_0);
void _Nglc_Pdecl_var_attr_extern_0();
void _Nglc_Pdecl_var_attr_no_decl_0();
void _Nglc_Pdecl_var_end_0();
void _Nglc_Pdecl_var_as_farg_2(int32_t _Lrow_0, int32_t _Lcol_1);
void _Nglc_Pfarg_next_group_0();
void _Nglc_Pdecl_var_as_this_0();
void _Nglc_Pdecl_var_as_fvar_0();
void _Nglc_Pfunc_body_end_0();
void _Nglc_Pexpr_push_call_2(int32_t _Lrow_0, int32_t _Lcol_1);
_Nglc_Nexpr_i _Nglc_Pexpr_pop_func_2(_Nglc_Nat _Lat_0, _Nglc_Nid _Lfunc_name_1);
_Nglc_Nexpr_i _Nglc_Pexpr_pop_method_2(_Nglc_Nexpr_i _Lthis_0, _Nglc_Nid _Lfunc_name_1);
void _Nglc_Pcarg_push_1(_Nglc_Nexpr_i _Lexpr_0);
void _Nglc_Pcarg_push_str_1(_Nglc_Nexpr_i _Lexpr_0);
void _Nglc_Pcarg_next_group_0();
void _Nglc_Pexpr2stmt_5(_Nglc_Nexpr_i _Le_0, int32_t _Lbegin_row_1, int32_t _Lbegin_col_2, int32_t _Lend_row_3, int32_t _Lend_col_4);
void _Nglc_Pstmt_return_5(_Nglc_Nexpr_i _Le_0, int32_t _Lbegin_row_1, int32_t _Lbegin_col_2, int32_t _Lend_row_3, int32_t _Lend_col_4);
void _Nglc_Pstmt_continue_5(_Nglc_Nid _Lid_0, int32_t _Lbegin_row_1, int32_t _Lbegin_col_2, int32_t _Lend_row_3, int32_t _Lend_col_4);
void _Nglc_Pstmt_break_5(_Nglc_Nid _Lid_0, int32_t _Lbegin_row_1, int32_t _Lbegin_col_2, int32_t _Lend_row_3, int32_t _Lend_col_4);
void _Nglc_Pfunc_attr_main_0();
void _Nglc_Pfunc_attr_decl_0();
void _Nglc_Pfunc_attr_cgl_name_0();
void _Nglc_Pfunc_attr_process_0();
void _Nglc_Pfunc_attr_inline_0();
void _Nglc_Pfunc_attr_var_args_0();
void _Nglc_Pfunc_attr_no_decl_0();
void _Nglc_Pfunc_attr_no_body_0();
void _Nglc_Pfunc_attr_real_name_1(_Nglc_Nid _Lname_0);
void _Nglc_Pfunc_attr_case_1(_Nglc_Nid _Lname_0);
_Nglc_Nexpr_i _Nglc_Pexpr_lvar_4(_Nglc_Nid _Lname_0, uint8_t _Ldecl_1, int32_t _Lrow_2, int32_t _Lcol_3);
_Nglc_Nexpr_i _Nglc_Pexpr_gvar_2(_Nglc_Nat _Lat_0, _Nglc_Nid _Lname_1);
_Nglc_Nexpr_i _Nglc_Pexpr_fvar_2(_Nglc_Nexpr_i _Lexpr_0, _Nglc_Nid _Lmember_1);
_Nglc_Nexpr_i _Nglc_Pexpr_assign_3(_Nglc_Nexpr_i _Lleft_0, _Nglc_Nexpr_i _Lright_1, _Nglc_Nassign _Ltype_2);
_Nglc_Nexpr_i _Nglc_Pexpr_math_3(_Nglc_Nexpr_i _Lleft_0, _Nglc_Nexpr_i _Lright_1, _Nglc_Nmath _Ltype_2);
_Nglc_Nexpr_i _Nglc_Pexpr_math_add_2(_Nglc_Nexpr_i _Lexpr_0, _Nglc_Nexpr_i _Lright_1);
_Nglc_Nexpr_i _Nglc_Pexpr_bools_3(_Nglc_Nexpr_i _Lleft_0, _Nglc_Nexpr_i _Lright_1, _Nglc_Nbools _Ltype_2);
_Nglc_Nexpr_i _Nglc_Pexpr_bools_add_2(_Nglc_Nexpr_i _Lbools_0, _Nglc_Nexpr_i _Lright_1);
char* _Nglc_Ptoken_name_1(_Nglc_Ntoken _Ltok_0);
void _Nglc_Pdecl_var_type_1(_Nglc_Nat _Ltype_0);
void _Nglc_Pdecl_var_this_0();
void _Nglc_Pstmt_lvar_add_4(_Nglc_Nid _Lname_0, _Nglc_Nexpr_i _Lset_1, int32_t _Lrow_2, int32_t _Lcol_3);
void _Nglc_Pstmt_lvar_end_2(int32_t _Lend_row_0, int32_t _Lend_col_1);
void _Nglc_Pdecl_include_begin_3(_Nglc_Ninclude _Linc_0, int32_t _Lrow_1, int32_t _Lcol_2);
void _Nglc_Pdecl_include_end_0();
void _Nglc_Pdecl_at_basic_1(_Nglc_Nbasic_type_id _Ltype_0);
void _Nglc_Pdecl_at_add_2(_Nglc_Nid _Lname_0, _Nglc_Nname_type _Ltype_1);
void _Nglc_Pdecl_at_begin_2(int32_t _Lrow_0, int32_t _Lcol_1);
void _Nglc_Pdecl_at_begin_struct_3(_Nglc_Nid _Lname_0, int32_t _Lrow_1, int32_t _Lcol_2);
void _Nglc_Pdecl_at_end_0();
void _Nglc_Pdecl_alias_4(_Nglc_Nid _Lname_0, _Nglc_Nat _Lat_1, int32_t _Lrow_2, int32_t _Lcol_3);
void _Nglc_Pat_push_4(_Nglc_Nid _Lname_0, _Nglc_Nname_type _Ltype_1, int32_t _Lrow_2, int32_t _Lcol_3);
_Nglc_Nat _Nglc_Pat_done_0();
void _Nglc_Pat_begin_0();
void _Nglc_Pat_begin_relative_0();
void _Nglc_Pat_begin_relative_pause_0();
void _Nglc_Pat_begin_relative_resume_0();
void _Nglc_Pat_root_0();
void _Nglc_Pat_alias_3(_Nglc_Nid _Lname_0, int32_t _Lrow_1, int32_t _Lcol_2);
void _Nglc_Pat_graves_3(int8_t _Lgraves_0, int32_t _Lrow_1, int32_t _Lcol_2);
_Nglc_Nat _Nglc_Pat_basic_type_1(_Nglc_Nbasic_type_id _Ltype_0);
void _Nglc_Pdecl_var_as_gvar_0();
void _Nglc_Ptype_info_arr_2(_Nglc_Nexpr_i* _Lexpr_v_0, uint8_t _Lexpr_c_1);
void _Nglc_Ptype_info_ref_1(int8_t _Lc_0);
void _Nglc_Ptype_info_static_0();
void _Nglc_Ptype_info_begin_0();
void _Nglc_Ptype_info_finalize_0();
_Nglc_Nexpr_i _Nglc_Pexpr_int_2(int32_t _Lvalue_0, _Nglc_Nexpr_int _Ltype_1);
_Nglc_Nexpr_i _Nglc_Pexpr_size_of_type_1(_Nglc_Nat _Lat_0);
_Nglc_Nexpr_i _Nglc_Pexpr_null_0();
void _Nglc_Pdecl_at_begin_enum_3(_Nglc_Nid _Lname_0, int32_t _Lrow_1, int32_t _Lcol_2);
void _Nglc_Pdecl_enum_end_3(_Nglc_Nat _Lbase_type_0, int32_t _Lrow_1, int32_t _Lcol_2);
_Nglc_Nexpr_i _Nglc_Pexpr_cvar_2(_Nglc_Nat _Lat_0, _Nglc_Nid _Lname_1);
void _Nglc_Penum_add_cvar_3(_Nglc_Nid _Lname_0, int32_t _Lrow_1, int32_t _Lcol_2);
void _Nglc_Pdecl_add_cvar_3(_Nglc_Nid _Lname_0, int32_t _Lrow_1, int32_t _Lcol_2);
void _Nglc_Penum_set_cvar_expr_1(_Nglc_Nexpr_i _Lset_0);
void _Nglc_Pstruct_attr_real_name_1(_Nglc_Nid _Lname_0);
void _Nglc_Pstruct_attr_union_0();
void _Nglc_Pstruct_attr_no_decl_0();
_Nglc_Nexpr_i _Nglc_Pexpr_str_1(_Nglc_Nexpr_i _Lprev_0);
_Nglc_Nexpr_i _Nglc_Pexpr_unary_2(_Nglc_Nexpr_i _Lexpr_0, _Nglc_Nunary _Ltype_1);
_Nglc_Nexpr_i _Nglc_Pexpr_ref_1(_Nglc_Nexpr_i _Lexpr_0);
_Nglc_Nexpr_i _Nglc_Pexpr_cast_fast_2(_Nglc_Nexpr_i _Lexpr_0, _Nglc_Nat _Ltype_1);
_Nglc_Nexpr_i _Nglc_Pexpr_index_3(_Nglc_Nexpr_i _Lleft_0, _Nglc_Nexpr_i* _Lright_v_1, int32_t _Lright_c_2);
void _Nglc_Penum_base_begin_0();
void _Nglc_Pstmt_switch_begin_0();
void _Nglc_Pstmt_switch_set_6(_Nglc_Nexpr_i _Lexpr_0, int32_t _Lbegin_row_1, int32_t _Lbegin_col_2, int32_t _Lend_row_3, int32_t _Lend_col_4, _Nglc_Nexpr_i _Lcases_5);
void _Nglc_Pstmt_switch_expr_add_1(_Nglc_Nexpr_i _Lexpr_0);
void _Nglc_Pstmt_switch_case_begin_5(int32_t _Lbegin_row_0, int32_t _Lbegin_col_1, int32_t _Lend_row_2, int32_t _Lend_col_3, bool _Lfall_through_4);
void _Nglc_Pstmt_switch_case_end_0();
void _Nglc_Pstmt_switch_default_begin_5(int32_t _Lbegin_row_0, int32_t _Lbegin_col_1, int32_t _Lend_row_2, int32_t _Lend_col_3, bool _Lfall_through_4);
void _Nglc_Pstmt_switch_default_end_0();
void _Nglc_Pstmt_switch_end_0();
void _Nglc_Pstmt_if_begin_0();
void _Nglc_Pstmt_if_set_6(bool _Lnot_0, _Nglc_Nexpr_i _Lexpr_1, int32_t _Lbegin_row_2, int32_t _Lbegin_col_3, int32_t _Lend_row_4, int32_t _Lend_col_5);
void _Nglc_Pstmt_if_end_0();
void _Nglc_Pstmt_do_begin_0();
void _Nglc_Pstmt_do_set_6(_Nglc_Nexpr_i _Lexpr_0, int32_t _Lbegin_row_1, int32_t _Lbegin_col_2, int32_t _Lend_row_3, int32_t _Lend_col_4, struct _Nglc_Nstmt_space* _Lcontinu_5);
void _Nglc_Pstmt_do_end_0();
void _Nglc_Pstmt_while_begin_0();
void _Nglc_Pstmt_while_set_6(_Nglc_Nexpr_i _Lexpr_0, int32_t _Lbegin_row_1, int32_t _Lbegin_col_2, int32_t _Lend_row_3, int32_t _Lend_col_4, struct _Nglc_Nstmt_space* _Lcontinu_5);
void _Nglc_Pstmt_while_end_0();
void _Nglc_Pstmt_elif_begin_0();
void _Nglc_Pstmt_elif_set_6(bool _Lnot_0, _Nglc_Nexpr_i _Lexpr_1, int32_t _Lbegin_row_2, int32_t _Lbegin_col_3, int32_t _Lend_row_4, int32_t _Lend_col_5);
void _Nglc_Pstmt_elif_end_0();
void _Nglc_Pstmt_else_set_0();
void _Nglc_Pstmt_else_end_0();
void _Nglc_Pstmt_if_end_ifs_0();
struct _Nglc_Nstmt_space* _Nglc_Pstmt_space_begin_0();
struct _Nglc_Nstmt_space* _Nglc_Pstmt_space_begin_detach_0();
struct _Nglc_Nstmt_space* _Nglc_Pstmt_space_end_0();
_Nglc_Nexpr_i _Nglc_Pexpr_compare_3(_Nglc_Nexpr_i _Lleft_0, _Nglc_Nexpr_i _Lright_1, _Nglc_Ncompare _Ltype_2);
_Nglc_Nexpr_i _Nglc_Pexpr_bool_1(bool _Lvalue_0);
_Nglc_Nexpr_i _Nglc_Pexpr_char_1(int32_t _Lvalue_0);
void _Nglc_Pcvar_attr_real_name_1(_Nglc_Nid _Lname_0);
void _Nglc_Pcvar_attr_no_decl_0();
bool _Nglc_Ppreprocess_def_get_2(char* _Lname_0, uint8_t _Llen_1);
int32_t _Nglc_Nmap_Pget_or_insert_4(struct _Nglc_Nmap* _Lm_0, char* _Lstr_1, uint8_t _Llen_2, int32_t _Lval_3);
#define _Nglc_Pgrow_2(cap, c) cap = Fpow2gteq((c) + 8)
#define _Nglc_Prealloc_3(r, c, oldc) r = realloc(r, sizeof(r[0]) * (c)); memset(r + (oldc), 0, sizeof(r[0]) * ((c) - (oldc)))
void _Nglc_Nat_Pput_to_header_1(_Nglc_Nat _Lat_0);
void _Nglc_Ninclude_Pwr_2(_Nglc_Ninclude _Li_0, union _Nglc_Nwtr* _Lw_1);
void _Nglc_Ndecl_var_data_Pwr_3(struct _Nglc_Ndecl_var_data* _Lvd_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2);
void _Nglc_Ncvar_flags_Pwr_2(_Nglc_Ncvar_flags _Lf_0, union _Nglc_Nwtr* _Lw_1);
void _Nglc_Nexpr_i_Pwr_3(_Nglc_Nexpr_i _Le_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2);
void _Nglc_Ncvar_Pwr_2(_Nglc_Ncvar _Lg_0, union _Nglc_Nwtr* _Lw_1);
void _Nglc_Nenum_flags_Pwr_2(_Nglc_Nenum_flags _Le_0, union _Nglc_Nwtr* _Lw_1);
void _Nglc_Nstruct_flags_Pwr_2(_Nglc_Nstruct_flags _Lf_0, union _Nglc_Nwtr* _Lw_1);
void _Nglc_Nfvar_data_Pwr_3(struct _Nglc_Nfvar_data* _Lf_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2);
void _Nglc_Nfarg_Pwr_3(struct _Nglc_Nfarg* _Lf_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2);
void _Nglc_Nfunc_flags_Pwr_2(_Nglc_Nfunc_flags _Le_0, union _Nglc_Nwtr* _Lw_1);
void _Nglc_Nfunc_Pwr_2(_Nglc_Nfunc _Lf_0, union _Nglc_Nwtr* _Lw_1);
void _Nglc_Ndecl_func_Plvars_wr_3(struct _Nglc_Ndecl_func* _Lf_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2);
void _Nglc_Nstmt_space_Pwr_3(struct _Nglc_Nstmt_space* _Lspace_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2);
void _Nglc_Nwtr_Pn4_2(union _Nglc_Nwtr* _Lw_0, uint32_t _Ln_1);
#define _Nglc_Pquick_alloc_one_1(r) r = qalloc(sizeof(r[0]))
#define _Nglc_Pquick_alloc_plus_2(r, plus) r = qalloc(sizeof(r[0]) + plus)
void _Nglc_Ndecl_var_data_Pcopy_from_2(struct _Nglc_Ndecl_var_data* _Lvd_0, struct _Nglc_Ndecl_var_data* _Lsrc_1);
void _Nglc_Nfarg_Pcopy_from_2(struct _Nglc_Nfarg* _Lf_0, struct _Nglc_Nfarg* _Lsrc_1);
uint8_t _Nglc_Nid_Plen_1(_Nglc_Nid _Lid_0);
char* _Nglc_Nid_Pstr_1(_Nglc_Nid _Lid_0);
struct _Nglc_Ndecl_func* _Nglc_Nfunc_Pptr_1(_Nglc_Nfunc _Lf_0);
_Nglc_Nlvar _Nglc_Nstmt_space_Plvar_new_4(struct _Nglc_Nstmt_space* _Lspace_0, _Nglc_Nid _Lname_1, int32_t _Lrow_2, int32_t _Lcol_3);
struct _Nglc_Nlvar_data* _Nglc_Nlvar_Pptr_1(_Nglc_Nlvar _Ll_0);
void _Nglc_Ntype_info_Pinit_1(struct _Nglc_Ntype_info* _Lti_0);
_Nglc_Nexpr_i _Nglc_Pexpr_push_2(struct _Nglc_Nexpr* _Le_0, _Nglc_Nexpr_type _Ltype_1);
struct _Nglc_Nexpr* _Nglc_Nexpr_i_Pptr_1(_Nglc_Nexpr_i _Le_0);
void _Nglc_Pstmt_push_6(struct _Nglc_Nstmt* _Ls_0, int32_t _Lbegin_row_1, int32_t _Lbegin_col_2, int32_t _Lend_row_3, int32_t _Lend_col_4, _Nglc_Nstmt_type _Ltype_5);
_Nglc_Nid _Nglc_Nlvar_Pname_1(_Nglc_Nlvar _Ll_0);
char* _Nglc_Ntoken_Pcgl_name_1(_Nglc_Ntoken _Le_0) {
switch(_Le_0) {
case _Nglc_Ntoken_Cnil: return "nil";
case _Nglc_Ntoken_Cplus: return "plus";
case _Nglc_Ntoken_Cminus: return "minus";
case _Nglc_Ntoken_Cspace: return "space";
case _Nglc_Ntoken_Cid_lparen: return "id-lparen";
case _Nglc_Ntoken_Cid_colon: return "id-colon";
case _Nglc_Ntoken_Cid_quote: return "id-quote";
case _Nglc_Ntoken_Cid_hash: return "id-hash";
case _Nglc_Ntoken_Clcbrace: return "lcbrace";
case _Nglc_Ntoken_Cid: return "id";
case _Nglc_Ntoken_Cspace_at_real_name_str: return "space-at-real-name-str";
case _Nglc_Ntoken_Cspace_at_real_name: return "space-at-real-name";
case _Nglc_Ntoken_Cspace_at_no_decl: return "space-at-no-decl";
case _Nglc_Ntoken_Cspace_equal_space: return "space-equal-space";
case _Nglc_Ntoken_Cinclude: return "include";
case _Nglc_Ntoken_Cspace_rcbrace: return "space-rcbrace";
case _Nglc_Ntoken_Cquote: return "quote";
case _Nglc_Ntoken_Cgrave: return "grave";
case _Nglc_Ntoken_Cid_bslash: return "id-bslash";
case _Nglc_Ntoken_Clcbrace_at_lparen: return "lcbrace-at-lparen";
case _Nglc_Ntoken_Crparen: return "rparen";
case _Nglc_Ntoken_Clcbrace_cvar_space: return "lcbrace-cvar-space";
case _Nglc_Ntoken_Crcbrace: return "rcbrace";
case _Nglc_Ntoken_Cend: return "end";
case _Nglc_Ntoken_Clcbrace_using_space: return "lcbrace-using-space";
case _Nglc_Ntoken_Clparen: return "lparen";
case _Nglc_Ntoken_Clparen_space: return "lparen-space";
case _Nglc_Ntoken_Cspace_rparen: return "space-rparen";
case _Nglc_Ntoken_Ccomma_space_rparen: return "comma-space-rparen";
case _Nglc_Ntoken_Ccomma_space_rcbrace: return "comma-space-rcbrace";
case _Nglc_Ntoken_Cscolon_space_rcbrace: return "scolon-space-rcbrace";
case _Nglc_Ntoken_Clbracket: return "lbracket";
case _Nglc_Ntoken_Clbracket_space: return "lbracket-space";
case _Nglc_Ntoken_Crbracket: return "rbracket";
case _Nglc_Ntoken_Cspace_rbracket: return "space-rbracket";
case _Nglc_Ntoken_Ccomma_space_rbracket: return "comma-space-rbracket";
case _Nglc_Ntoken_Cgrave_this: return "grave-this";
case _Nglc_Ntoken_Ccomma_space: return "comma-space";
case _Nglc_Ntoken_Cspace_at_main: return "space-at-main";
case _Nglc_Ntoken_Cspace_at_case: return "space-at-case";
case _Nglc_Ntoken_Cdot: return "dot";
case _Nglc_Ntoken_Cspace_at_process: return "space-at-process";
case _Nglc_Ntoken_Cspace_at_inline: return "space-at-inline";
case _Nglc_Ntoken_Cspace_at_cgl_name: return "space-at-cgl-name";
case _Nglc_Ntoken_Cspace_at_decl: return "space-at-decl";
case _Nglc_Ntoken_Cstring: return "string";
case _Nglc_Ntoken_Cspace_at_var_args: return "space-at-var-args";
case _Nglc_Ntoken_Cspace_at_no_body: return "space-at-no-body";
case _Nglc_Ntoken_Cgrave_ref: return "grave-ref";
case _Nglc_Ntoken_Cgrave_bool: return "grave-bool";
case _Nglc_Ntoken_Cgrave_char: return "grave-char";
case _Nglc_Ntoken_Cgrave_tint: return "grave-tint";
case _Nglc_Ntoken_Cgrave_tnum: return "grave-tnum";
case _Nglc_Ntoken_Cgrave_int: return "grave-int";
case _Nglc_Ntoken_Cgrave_num: return "grave-num";
case _Nglc_Ntoken_Cgrave_float: return "grave-float";
case _Nglc_Ntoken_Cgrave_size: return "grave-size";
case _Nglc_Ntoken_Cgrave_lnum: return "grave-lnum";
case _Nglc_Ntoken_Campersand: return "ampersand";
case _Nglc_Ntoken_Cnum_dec: return "num-dec";
case _Nglc_Ntoken_Cnum_hex: return "num-hex";
case _Nglc_Ntoken_Cnum_oct: return "num-oct";
case _Nglc_Ntoken_Cchar1: return "char1";
case _Nglc_Ntoken_Cchar2: return "char2";
case _Nglc_Ntoken_Ctrue: return "true";
case _Nglc_Ntoken_Cfalse: return "false";
case _Nglc_Ntoken_Cnull: return "null";
case _Nglc_Ntoken_Clparen_amp_amp_comma_space: return "lparen-amp-amp-comma-space";
case _Nglc_Ntoken_Clparen_pipe_pipe_comma_space: return "lparen-pipe-pipe-comma-space";
case _Nglc_Ntoken_Cspace_plus_space: return "space-plus-space";
case _Nglc_Ntoken_Cspace_minus_space: return "space-minus-space";
case _Nglc_Ntoken_Cspace_mul_space: return "space-mul-space";
case _Nglc_Ntoken_Cspace_div_space: return "space-div-space";
case _Nglc_Ntoken_Cspace_langle_langle_space: return "space-langle-langle-space";
case _Nglc_Ntoken_Cspace_rangle_rangle_space: return "space-rangle-rangle-space";
case _Nglc_Ntoken_Cspace_amp_space: return "space-amp-space";
case _Nglc_Ntoken_Cspace_pipe_space: return "space-pipe-space";
case _Nglc_Ntoken_Cspace_xor_space: return "space-xor-space";
case _Nglc_Ntoken_Cspace_equal_equal_space: return "space-equal-equal-space";
case _Nglc_Ntoken_Cspace_expoint_equal_space: return "space-expoint-equal-space";
case _Nglc_Ntoken_Cspace_langle_space: return "space-langle-space";
case _Nglc_Ntoken_Cspace_langle_equal_space: return "space-langle-equal-space";
case _Nglc_Ntoken_Cspace_rangle_space: return "space-rangle-space";
case _Nglc_Ntoken_Cspace_rangle_equal_space: return "space-rangle-equal-space";
case _Nglc_Ntoken_Chash: return "hash";
case _Nglc_Ntoken_Cspace_plus_equal_space: return "space-plus-equal-space";
case _Nglc_Ntoken_Cspace_minus_equal_space: return "space-minus-equal-space";
case _Nglc_Ntoken_Cspace_mul_equal_space: return "space-mul-equal-space";
case _Nglc_Ntoken_Cspace_div_equal_space: return "space-div-equal-space";
case _Nglc_Ntoken_Cspace_lshift_equal_space: return "space-lshift-equal-space";
case _Nglc_Ntoken_Cspace_rshift_equal_space: return "space-rshift-equal-space";
case _Nglc_Ntoken_Cspace_and_equal_space: return "space-and-equal-space";
case _Nglc_Ntoken_Cspace_or_equal_space: return "space-or-equal-space";
case _Nglc_Ntoken_Cspace_xor_equal_space: return "space-xor-equal-space";
case _Nglc_Ntoken_Cspace_colon_equal_space: return "space-colon-equal-space";
case _Nglc_Ntoken_Cexpoint: return "expoint";
case _Nglc_Ntoken_Clcbrace_do: return "lcbrace-do";
case _Nglc_Ntoken_Clcbrace_while: return "lcbrace-while";
case _Nglc_Ntoken_Clcbrace_if: return "lcbrace-if";
case _Nglc_Ntoken_Clcbrace_elif: return "lcbrace-elif";
case _Nglc_Ntoken_Clcbrace_else: return "lcbrace-else";
case _Nglc_Ntoken_Clcbrace_switch: return "lcbrace-switch";
case _Nglc_Ntoken_Cspace_at_fall_through: return "space-at-fall-through";
case _Nglc_Ntoken_Clcbrace_case: return "lcbrace-case";
case _Nglc_Ntoken_Clcbrace_default: return "lcbrace-default";
case _Nglc_Ntoken_Ccontinue: return "continue";
case _Nglc_Ntoken_Cbreak: return "break";
case _Nglc_Ntoken_Creturn: return "return";
case _Nglc_Ntoken_Clcbrace_plus_or_space: return "lcbrace-plus-or-space";
case _Nglc_Ntoken_Cspace_at_extern: return "space-at-extern";
case _Nglc_Ntoken_Cscolon_space: return "scolon-space";
case _Nglc_Ntoken_Cspace_at_union: return "space-at-union";
case _Nglc_Ntoken_Clcbrace_gvar_space: return "lcbrace-gvar-space";
}
return "(ERROR)";
}
struct _Nglc_Nat_data* _Nglc_Nat_Pptr_1(_Nglc_Nat _Li_0);
_Nglc_Nat _Nglc_Pat_create_basic_1(_Nglc_Nbasic_type_id _Lbasic_0);
_Nglc_Nat _Nglc_Pat_create_3(_Nglc_Nat _Lparent_0, _Nglc_Nname_type _Ltype_1, _Nglc_Nid _Lname_2);
void _Nglc_Ptype_info_arr_1(_Nglc_Nexpr_i _Lexpr_0);
void _Nglc_Ntype_info_Pfinalize_1(struct _Nglc_Ntype_info* _Lti_0);
struct _Nglc_Ncvar_data* _Nglc_Ncvar_Pptr_1(_Nglc_Ncvar _Lc_0);
struct _Nglc_Nstmt_space* _Nglc_Pstmt_space_begin_1(bool _Lattach_0);
void _Nglc_Nvar_flags_Pwr_2(_Nglc_Nvar_flags _Lf_0, union _Nglc_Nwtr* _Lw_1);
void _Nglc_Ntype_info_Pwr_2(struct _Nglc_Ntype_info* _Lti_0, union _Nglc_Nwtr* _Lw_1);
void _Nglc_Nexpr_type_Pwr_2(_Nglc_Nexpr_type _Le_0, union _Nglc_Nwtr* _Lw_1);
void _Nglc_Nexpr_i_Pwr_math_3(struct _Nglc_Nexpr* _Lexpr_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2);
void _Nglc_Nexpr_i_Pwr_bools_3(struct _Nglc_Nexpr* _Lexpr_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2);
void _Nglc_Nexpr_i_Pwr_str_3(struct _Nglc_Nexpr* _Lexpr_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2);
void _Nglc_Nexpr_i_Pwr_cvar_3(struct _Nglc_Nexpr* _Lexpr_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2);
void _Nglc_Nexpr_i_Pwr_unary_3(struct _Nglc_Nexpr* _Lexpr_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2);
void _Nglc_Nexpr_i_Pwr_ref_3(struct _Nglc_Nexpr* _Lexpr_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2);
void _Nglc_Nexpr_i_Pwr_cast_fast_3(struct _Nglc_Nexpr* _Lexpr_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2);
void _Nglc_Nexpr_i_Pwr_index_3(struct _Nglc_Nexpr* _Lexpr_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2);
void _Nglc_Nexpr_i_Pwr_compare_3(struct _Nglc_Nexpr* _Lexpr_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2);
void _Nglc_Nexpr_i_Pwr_bool_3(struct _Nglc_Nexpr* _Lexpr_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2);
void _Nglc_Nexpr_i_Pwr_char_3(struct _Nglc_Nexpr* _Lexpr_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2);
void _Nglc_Nexpr_i_Pwr_method_3(struct _Nglc_Nexpr* _Lexpr_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2);
void _Nglc_Nexpr_i_Pwr_func_3(struct _Nglc_Nexpr* _Lexpr_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2);
void _Nglc_Nexpr_i_Pwr_null_3(struct _Nglc_Nexpr* _Lexpr_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2);
void _Nglc_Nexpr_i_Pwr_i32_3(struct _Nglc_Nexpr* _Lexpr_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2);
void _Nglc_Nexpr_i_Pwr_size_of_type_3(struct _Nglc_Nexpr* _Lexpr_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2);
void _Nglc_Nexpr_i_Pwr_assign_3(struct _Nglc_Nexpr* _Lexpr_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2);
void _Nglc_Nexpr_i_Pwr_fvar_3(struct _Nglc_Nexpr* _Lexpr_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2);
void _Nglc_Nexpr_i_Pwr_gvar_3(struct _Nglc_Nexpr* _Lexpr_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2);
void _Nglc_Nexpr_i_Pwr_lvar_3(struct _Nglc_Nexpr* _Lexpr_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2);
char* _Nglc_Nexpr_type_Pcgl_name_1(_Nglc_Nexpr_type _Le_0) {
switch(_Le_0) {
case _Nglc_Nexpr_type_Cnil: return "nil";
case _Nglc_Nexpr_type_Ccall_method: return "call-method";
case _Nglc_Nexpr_type_Clvar: return "lvar";
case _Nglc_Nexpr_type_Cgvar: return "gvar";
case _Nglc_Nexpr_type_Cmath: return "math";
case _Nglc_Nexpr_type_Cassign: return "assign";
case _Nglc_Nexpr_type_Cbools: return "bools";
case _Nglc_Nexpr_type_Cfunc: return "func";
case _Nglc_Nexpr_type_Cmethod: return "method";
case _Nglc_Nexpr_type_Cfvar: return "fvar";
case _Nglc_Nexpr_type_Ci32: return "i32";
case _Nglc_Nexpr_type_Ccvar: return "cvar";
case _Nglc_Nexpr_type_Cstr: return "str";
case _Nglc_Nexpr_type_Cindex: return "index";
case _Nglc_Nexpr_type_Cunary: return "unary";
case _Nglc_Nexpr_type_Ccompare: return "compare";
case _Nglc_Nexpr_type_Cbool: return "bool";
case _Nglc_Nexpr_type_Cnull: return "null";
case _Nglc_Nexpr_type_Ccast_fast: return "cast-fast";
case _Nglc_Nexpr_type_Cref: return "ref";
case _Nglc_Nexpr_type_Cchar: return "char";
case _Nglc_Nexpr_type_Csize_of_type: return "size-of-type";
}
return "(ERROR)";
}
void _Nglc_Nlvar_flags_Pwr_2(_Nglc_Nlvar_flags _Lf_0, union _Nglc_Nwtr* _Lw_1);
void _Nglc_Nlvar_Pwr_2(_Nglc_Nlvar _Ll_0, union _Nglc_Nwtr* _Lw_1);
void _Nglc_Nstmt_type_Pwr_2(_Nglc_Nstmt_type _Ls_0, union _Nglc_Nwtr* _Lw_1);
void _Nglc_Nstmt_space_Pwr_break_3(struct _Nglc_Nstmt* _Lstmt_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2);
void _Nglc_Nstmt_space_Pwr_switch_3(struct _Nglc_Nstmt* _Lstmt_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2);
void _Nglc_Nstmt_space_Pwr_case_3(struct _Nglc_Nstmt* _Lstmt_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2);
void _Nglc_Nstmt_space_Pwr_case_end_3(struct _Nglc_Nstmt* _Lstmt_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2);
void _Nglc_Nstmt_space_Pwr_default_3(struct _Nglc_Nstmt* _Lstmt_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2);
void _Nglc_Nstmt_space_Pwr_default_end_3(struct _Nglc_Nstmt* _Lstmt_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2);
void _Nglc_Nstmt_space_Pwr_switch_end_3(struct _Nglc_Nstmt* _Lstmt_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2);
void _Nglc_Nstmt_space_Pwr_if_3(struct _Nglc_Nstmt* _Lstmt_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2);
void _Nglc_Nstmt_space_Pwr_if_elif_3(struct _Nglc_Nstmt* _Lstmt_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2);
void _Nglc_Nstmt_space_Pwr_if_else_3(struct _Nglc_Nstmt* _Lstmt_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2);
void _Nglc_Nstmt_space_Pwr_if_end_3(struct _Nglc_Nstmt* _Lstmt_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2);
void _Nglc_Nstmt_space_Pwr_do_3(struct _Nglc_Nstmt* _Lstmt_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2);
void _Nglc_Nstmt_space_Pwr_do_end_3(struct _Nglc_Nstmt* _Lstmt_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2);
void _Nglc_Nstmt_space_Pwr_while_3(struct _Nglc_Nstmt* _Lstmt_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2);
void _Nglc_Nstmt_space_Pwr_while_end_3(struct _Nglc_Nstmt* _Lstmt_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2);
void _Nglc_Nstmt_space_Pwr_continue_3(struct _Nglc_Nstmt* _Lstmt_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2);
void _Nglc_Nstmt_space_Pwr_return_3(struct _Nglc_Nstmt* _Lstmt_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2);
void _Nglc_Nstmt_space_Pwr_space_3(struct _Nglc_Nstmt* _Lstmt_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2);
void _Nglc_Nstmt_space_Pwr_expr_3(struct _Nglc_Nstmt* _Lstmt_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2);
char* _Nglc_Nstmt_type_Pcgl_name_1(_Nglc_Nstmt_type _Le_0) {
switch(_Le_0) {
case _Nglc_Nstmt_type_Cspace: return "space";
case _Nglc_Nstmt_type_Cif: return "if";
case _Nglc_Nstmt_type_Cif_elif: return "if-elif";
case _Nglc_Nstmt_type_Cif_else: return "if-else";
case _Nglc_Nstmt_type_Cif_end: return "if-end";
case _Nglc_Nstmt_type_Cdo: return "do";
case _Nglc_Nstmt_type_Cdo_end: return "do-end";
case _Nglc_Nstmt_type_Cwhile: return "while";
case _Nglc_Nstmt_type_Cwhile_end: return "while-end";
case _Nglc_Nstmt_type_Cexpr: return "expr";
case _Nglc_Nstmt_type_Creturn: return "return";
case _Nglc_Nstmt_type_Ccontinue: return "continue";
case _Nglc_Nstmt_type_Cbreak: return "break";
case _Nglc_Nstmt_type_Cswitch: return "switch";
case _Nglc_Nstmt_type_Ccase: return "case";
case _Nglc_Nstmt_type_Cdefault: return "default";
case _Nglc_Nstmt_type_Ccase_end: return "case-end";
case _Nglc_Nstmt_type_Cdefault_end: return "default-end";
case _Nglc_Nstmt_type_Cswitch_end: return "switch-end";
case _Nglc_Nstmt_type_Cnil: return "nil";
}
return "(ERROR)";
}
void _Nglc_Ntype_info_Pcopy_from_2(struct _Nglc_Ntype_info* _Lti_0, struct _Nglc_Ntype_info* _Lti2_1);
#define _Nglc_Pquick_alloc_arr_2(r, c) r = qalloc(sizeof(r[0]) * (c))
void _Nglc_Pfunc_stmt_add_1(struct _Nglc_Nstmt* _Ls_0);
int32_t _Nglc_Nat_map_Pget_or_insert_5(struct _Nglc_Nat_map* _Lm_0, _Nglc_Nat _Lparent_1, _Nglc_Nname_type _Ltype_2, _Nglc_Nid _Lname_3, int32_t _Lval_4);
void _Nglc_Nwtr_Pb_2(union _Nglc_Nwtr* _Lw_0, bool _Lval_1);
void _Nglc_Nmath_Pwr_2(_Nglc_Nmath _Le_0, union _Nglc_Nwtr* _Lw_1);
void _Nglc_Nbools_Pwr_2(_Nglc_Nbools _Le_0, union _Nglc_Nwtr* _Lw_1);
void _Nglc_Nunary_Pwr_2(_Nglc_Nunary _Lu_0, union _Nglc_Nwtr* _Lw_1);
void _Nglc_Ncompare_Pwr_2(_Nglc_Ncompare _Le_0, union _Nglc_Nwtr* _Lw_1);
void _Nglc_Nassign_Pwr_2(_Nglc_Nassign _Ls_0, union _Nglc_Nwtr* _Lw_1);
int32_t main(int32_t _Larg_c_0, char** _Larg_v_1) {
_Nstdc_Nfd _Lin_fd_2;
char* _Llock_path_3;
size_t _Lin_size_7;
uint8_t* _Lin_data_8;
union _Nglc_Nrdr _Lr_end_28;
struct _Nglc_Nparser* _Lpsr_29;
struct _Nglc_Nlexer _Llex_30;
int32_t _Lnext_row_31;
int32_t _Lnext_col_32;
struct _Nglc_Ntoken_data _Ltok_33;
union _Nglc_Nwtr _Lw_begin_41;
union _Nglc_Nwtr _Lw_42;
int32_t _Lid_bit8_c_44;
_Nglc_Nat _Lat_bit8_c_46;
char* _Lout_path_49;
size_t _Lout_path_len_50;
_Nstdc_Nfd _Lout_fd_51;
char _Lfinal_path_58[512];
if(false) {
_Nglc_Ppreprocess_def_2("", 0);
_Nglc_Pexport_0();
}
_Nglc_Nmap_Pinit_1(&_Gid_map);
_Nglc_Nmap_Pinit_1(&_Ginclude_map);
_Nglc_Nat_map_Pinit_1(&_Gat_map);
_Nglc_Pquick_alloc_init_0();
_Gfunc_main = _Nglc_Nfunc_Cnil;
_Gdecl_include = _Nglc_Ninclude_Cnil;
if(_Larg_c_0 != 3) {
fprintf(stdout, "Usage: %s [file.cgl] [output.cgl-b]\n", _Larg_v_1[0]);
return 0;
}
input_path = _Larg_v_1[1];
if(!(_Nstdc_Nfd_Popen_3(&_Lin_fd_2, input_path, O_RDONLY))) {
fprintf(stdout, "Cannot open file for reading: %s\n", input_path);
exit(_Nstdc_Nexit_Cfailure);
}
_Llock_path_3 = _Larg_v_1[2];
_Glock_path = _Llock_path_3;
if(true) {
_Nstdc_Nfd _Lfd_4;
if(!(_Nstdc_Nfd_Popen_3(&_Lfd_4, _Llock_path_3, O_CREAT | O_EXCL))) {
struct stat _Lout_stat_5;
struct stat _Lin_stat_6;
stat(_Llock_path_3, &_Lout_stat_5);
_Nstdc_Nfd_Pstat_2(_Lin_fd_2, &_Lin_stat_6);
if(((_Lout_stat_5.st_mtimespec.tv_sec > _Lin_stat_6.st_mtimespec.tv_sec) || ((_Lout_stat_5.st_mtimespec.tv_sec == _Lin_stat_6.st_mtimespec.tv_sec) && (_Lout_stat_5.st_mtimespec.tv_nsec > _Lin_stat_6.st_mtimespec.tv_nsec)))) {
fprintf(stdout, "Skipping parsing of %s because the output file is newer\n", input_path);
return 0;
}
} else {
_Nglc_Pparser_at_exit_0();
}
_Nstdc_Nfd_Pclose_1(_Lfd_4);
}
_Lin_size_7 = lseek(_Lin_fd_2, 0, SEEK_END);
_Lin_data_8 = malloc(_Lin_size_7 + 2);
lseek(_Lin_fd_2, 0, SEEK_SET);
read(_Lin_fd_2, _Lin_data_8, _Lin_size_7);
_Lin_data_8[_Lin_size_7] = 0;
_Lin_data_8[(_Lin_size_7 + 1)] = 0;
_Nstdc_Nfd_Pclose_1(_Lin_fd_2);
if(((_Lin_data_8[(_Lin_size_7 - 2)] == '\r') && (_Lin_data_8[(_Lin_size_7 - 1)] == '\n'))) {
fprintf(stdout, "Error reading file '%s' because it uses Windows-style line endings\n", input_path);
fprintf(stdout, "Please convert the line endings to Unix-style line endings\n");
exit(_Nstdc_Nexit_Cfailure);
}
if(_Lin_data_8[(_Lin_size_7 - 1)] != '\n') {
fprintf(stdout, "Error reading file '%s' because it doesn't end with a new line\n", input_path);
exit(_Nstdc_Nexit_Cfailure);
}
if(true) {
bool _Lpreprocess_9;
union _Nglc_Nrdr _Lr_end_10;
union _Nglc_Nrdr _Lr_11;
void* _Lnew_data_12;
union _Nglc_Nwtr _Lw_13;
union _Nglc_Nwtr _Lw_begin_27;
_Lpreprocess_9 = false;
_Lr_end_10._Fref = _Lin_data_8;
_Lr_end_10._Fpos += _Lin_size_7;
_Lr_11._Fref = _Lin_data_8;
_Lnew_data_12 = malloc(_Lin_size_7 + 1);
_Lw_13._Fref = _Lnew_data_12;
while(_Lr_11._Fp1[0] == '#') {
while(1) {
_Lr_11._Fpos++;
if(_Lr_11._Fp1[0] == '\n') {
if(((_Lr_11._Fp1[0] == '#') && (_Lr_11._Fp1[1] == 'i') && (_Lr_11._Fp1[2] == 'f') && ((_Lr_11._Fp1[3] == '(') || ((_Lr_11._Fp1[3] == '!') && (_Lr_11._Fp1[4] == '('))))) {
_Lpreprocess_9 = true;
}
_Lw_13._Fp1[0] = '\n';
_Lw_13._Fpos++;
_Lr_11._Fpos++;
goto break_1;
}
continue_1:;
}
break_1:;
continue_0:;
}
break_0:;
while(_Lr_11._Fpos < _Lr_end_10._Fpos) {
if(_Lr_11._Fp1[0] == '/') {
if(((_Lr_11._Fp1[1] == '/') && ((_Lr_11._Fp1[2] == ' ') || (_Lr_11._Fp1[2] == '\t')))) {
if(_Lr_11._Fref == _Lin_data_8) {
} else if(((_Lr_11._Fp1[-1] == ' ') || (_Lr_11._Fp1[-1] == '\t') || (_Lr_11._Fp1[-1] == '\n'))) {
} else {
int32_t _Lrow_14;
int32_t _Lcol_15;
_Nglc_Pget_row_col_4(&_Lrow_14, &_Lcol_15, _Lr_11._Fref, _Lin_data_8);
fprintf(stdout, "%s:%u:%u: There must be a space or tab before the // comment\n", input_path, _Lrow_14, _Lcol_15);
exit(_Nstdc_Nexit_Cfailure);
}
_Lr_11._Fpos += 3;
while(1) {
if(_Lr_11._Fp1[0] == '\n') {
goto break_3;
}
_Lr_11._Fpos++;
if(_Lr_11._Fpos >= _Lr_end_10._Fpos) {
int32_t _Lrow_16;
int32_t _Lcol_17;
_Nglc_Pget_row_col_4(&_Lrow_16, &_Lcol_17, _Lr_11._Fref, _Lin_data_8);
fprintf(stdout, "%s:%u:%u: Comment did not end with a new line\n", input_path, _Lrow_16, _Lcol_17);
exit(_Nstdc_Nexit_Cfailure);
}
continue_3:;
}
break_3:;
goto continue_2;
} else if(_Lr_11._Fp1[1] == '\"') {
_Nglc_Pparse_comment_4(&_Lr_11, &_Lw_13, '\"', _Lin_data_8);
goto continue_2;
} else if(_Lr_11._Fp1[1] == '|') {
_Nglc_Pparse_comment_4(&_Lr_11, &_Lw_13, '|', _Lin_data_8);
goto continue_2;
} else if(_Lr_11._Fp1[1] == ';') {
_Nglc_Pparse_comment_4(&_Lr_11, &_Lw_13, ';', _Lin_data_8);
goto continue_2;
} else if(_Lr_11._Fp1[1] == '_') {
_Nglc_Pparse_comment_4(&_Lr_11, &_Lw_13, '_', _Lin_data_8);
goto continue_2;
} else if(_Lr_11._Fp1[1] == '+') {
_Nglc_Pparse_comment_4(&_Lr_11, &_Lw_13, '+', _Lin_data_8);
goto continue_2;
} else if(_Lr_11._Fp1[1] == '<') {
_Nglc_Pparse_comment_4(&_Lr_11, &_Lw_13, '>', _Lin_data_8);
goto continue_2;
} else if(_Lr_11._Fp1[1] == '[') {
_Nglc_Pparse_comment_4(&_Lr_11, &_Lw_13, ']', _Lin_data_8);
goto continue_2;
} else if(_Lr_11._Fp1[1] == '{') {
_Nglc_Pparse_comment_4(&_Lr_11, &_Lw_13, '}', _Lin_data_8);
goto continue_2;
} else if(_Lr_11._Fp1[1] == '(') {
_Nglc_Pparse_comment_4(&_Lr_11, &_Lw_13, ')', _Lin_data_8);
goto continue_2;
}
} else if(_Lr_11._Fp1[0] == '\'') {
if(_Lr_11._Fp1[1] == '\'') {
if(_Lr_11._Fp1[2] == '\\') {
_Lw_13._Fp1[0] = '\'';
_Lw_13._Fp1[1] = '\'';
_Lw_13._Fp1[2] = '\\';
_Lw_13._Fp1[3] = _Lr_11._Fp1[3];
_Lw_13._Fpos += 4;
_Lr_11._Fpos += 4;
goto continue_2;
} else {
_Lw_13._Fp1[0] = '\'';
_Lw_13._Fp1[1] = '\'';
_Lw_13._Fp1[2] = _Lr_11._Fp1[2];
_Lw_13._Fpos += 3;
_Lr_11._Fpos += 3;
goto continue_2;
}
} else if((((_Lr_11._Fp1[2] == ' ') || (_Lr_11._Fp1[2] == '\t')) && ((_Lr_11._Fp1[1] == '-') || (_Lr_11._Fp1[1] == '=')))) {
_Lw_13._Fp1[0] = '\'';
_Lw_13._Fp1[1] = _Lr_11._Fp1[1];
_Lw_13._Fp1[2] = _Lr_11._Fp1[2];
_Lw_13._Fpos += 3;
_Lr_11._Fpos += 3;
while(1) {
uint8_t _Lc_18;
_Lc_18 = _Lr_11._Fp1[0];
_Lw_13._Fp1[0] = _Lc_18;
_Lw_13._Fpos++;
_Lr_11._Fpos++;
if(_Lc_18 == '\n') {
goto break_4;
}
if(_Lr_11._Fpos >= _Lr_end_10._Fpos) {
int32_t _Lrow_19;
int32_t _Lcol_20;
_Nglc_Pget_row_col_4(&_Lrow_19, &_Lcol_20, _Lr_11._Fref, _Lin_data_8);
fprintf(stdout, "%s:%u:%u: String did not end with a new line\n", input_path, _Lrow_19, _Lcol_20);
exit(_Nstdc_Nexit_Cfailure);
}
continue_4:;
}
break_4:;
goto continue_2;
} else if(_Lr_11._Fp1[1] == '\"') {
_Nglc_Pparse_string_4(&_Lr_11, &_Lw_13, '\"', _Lin_data_8);
goto continue_2;
} else if(_Lr_11._Fp1[1] == '|') {
_Nglc_Pparse_string_4(&_Lr_11, &_Lw_13, '|', _Lin_data_8);
goto continue_2;
} else if(_Lr_11._Fp1[1] == ';') {
_Nglc_Pparse_string_4(&_Lr_11, &_Lw_13, ';', _Lin_data_8);
goto continue_2;
} else if(_Lr_11._Fp1[1] == '_') {
_Nglc_Pparse_string_4(&_Lr_11, &_Lw_13, '_', _Lin_data_8);
goto continue_2;
} else if(_Lr_11._Fp1[1] == '+') {
_Nglc_Pparse_string_4(&_Lr_11, &_Lw_13, '+', _Lin_data_8);
goto continue_2;
} else if(_Lr_11._Fp1[1] == '<') {
_Nglc_Pparse_string_4(&_Lr_11, &_Lw_13, '>', _Lin_data_8);
goto continue_2;
} else if(_Lr_11._Fp1[1] == '[') {
_Nglc_Pparse_string_4(&_Lr_11, &_Lw_13, ']', _Lin_data_8);
goto continue_2;
} else if(_Lr_11._Fp1[1] == '{') {
_Nglc_Pparse_string_4(&_Lr_11, &_Lw_13, '}', _Lin_data_8);
goto continue_2;
} else if(_Lr_11._Fp1[1] == '(') {
_Nglc_Pparse_string_4(&_Lr_11, &_Lw_13, ')', _Lin_data_8);
goto continue_2;
}
} else if(_Lr_11._Fp1[0] == '\"') {
_Lw_13._Fp1[0] = '\"';
_Lw_13._Fpos++;
_Lr_11._Fpos++;
while(1) {
if(_Lr_11._Fp1[0] == '\n') {
int32_t _Lrow_21;
int32_t _Lcol_22;
_Nglc_Pget_row_col_4(&_Lrow_21, &_Lcol_22, _Lr_11._Fref, _Lin_data_8);
fprintf(stdout, "%s:%u:%u: Unterminated string\n", input_path, _Lrow_21, _Lcol_22);
exit(_Nstdc_Nexit_Cfailure);
} else if(_Lr_11._Fp1[0] == '\"') {
_Lw_13._Fp1[0] = '\"';
_Lw_13._Fpos++;
_Lr_11._Fpos++;
goto break_5;
} else if(_Lr_11._Fp1[0] == '\\') {
switch(_Lr_11._Fp1[1]) {
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
int32_t _Lrow_23;
int32_t _Lcol_24;
_Nglc_Pget_row_col_4(&_Lrow_23, &_Lcol_24, _Lr_11._Fref, _Lin_data_8);
fprintf(stdout, "%s:%u:%u: Encountered invalid escape sequence in the string: '\\%c'\n", input_path, _Lrow_23, _Lcol_24, _Lr_11._Fp1[1]);
exit(_Nstdc_Nexit_Cfailure);
break;
}
_Lw_13._Fp1[0] = '\\';
_Lw_13._Fp1[1] = _Lr_11._Fp1[1];
_Lw_13._Fpos += 2;
_Lr_11._Fpos += 2;
} else {
_Lw_13._Fp1[0] = _Lr_11._Fp1[0];
_Lw_13._Fpos++;
_Lr_11._Fpos++;
}
if(_Lr_11._Fpos >= _Lr_end_10._Fpos) {
int32_t _Lrow_25;
int32_t _Lcol_26;
_Nglc_Pget_row_col_4(&_Lrow_25, &_Lcol_26, _Lr_11._Fref, _Lin_data_8);
fprintf(stdout, "%s:%u:%u: Unterminated string\n", input_path, _Lrow_25, _Lcol_26);
exit(_Nstdc_Nexit_Cfailure);
}
continue_5:;
}
break_5:;
goto continue_2;
} else if(((_Lr_11._Fp1[0] == '#') && (_Lr_11._Fp1[1] == 'i') && (_Lr_11._Fp1[2] == 'f') && ((_Lr_11._Fp1[3] == '(') || ((_Lr_11._Fp1[3] == '!') && (_Lr_11._Fp1[4] == '('))))) {
if(_Lr_11._Fref == _Lin_data_8) {
_Lpreprocess_9 = true;
} else if(_Lr_11._Fp1[-1] == '\n') {
_Lpreprocess_9 = true;
}
}
_Lw_13._Fp1[0] = _Lr_11._Fp1[0];
_Lw_13._Fpos++;
_Lr_11._Fpos++;
continue_2:;
}
break_2:;
_Lw_13._Fp1[0] = '\0';
free(_Lin_data_8);
_Lin_data_8 = _Lnew_data_12;
_Lw_begin_27._Fref = _Lnew_data_12;
_Lin_size_7 = (_Lw_13._Fpos - _Lw_begin_27._Fpos);
if(_Lpreprocess_9) {
_Nglc_Ppreprocess_init_0();
_Nglc_Ppreprocess_2(&_Lin_data_8, &_Lin_size_7);
}
}
_Lr_end_28._Fref = _Lin_data_8;
_Lr_end_28._Fpos += _Lin_size_7;
_Nglc_Pparse_str_init_1(_Lin_size_7);
_Gid_cap = 64;
_Nglc_Pmalloc_arr_2(_Gid_str_v, _Gid_cap);
_Nglc_Pmalloc_arr_2(_Gid_len_v, _Gid_cap);
_Ginclude_cap = 64;
_Nglc_Pmalloc_arr_2(_Ginclude_str_v, _Ginclude_cap);
_Nglc_Pmalloc_arr_2(_Ginclude_len_v, _Ginclude_cap);
_Gat_cap = (_Nglc_Nat)(64);
_Nglc_Pmalloc_arr_2(_Gat_v, _Gat_cap);
_Gat_c = (_Nglc_Nat)(2);
_Gat_v[0]._Ftype = _Nglc_Nname_type_Cbasic;
_Gat_v[0]._Fparent = _Nglc_Nat_Cnil;
_Gat_v[0]._Fname._Fbasic = _Nglc_Nbasic_type_id_Croot;
_Gat_v[1]._Ftype = _Nglc_Nname_type_Cbasic;
_Gat_v[1]._Fparent = _Nglc_Nat_Cnil;
_Gat_v[1]._Fname._Fbasic = _Nglc_Nbasic_type_id_Crelative;
_Gfunc_cap = (_Nglc_Nfunc)(32);
_Nglc_Pmalloc_arr_2(_Gfunc_v, _Gfunc_cap);
_Gstruct_cap = (_Nglc_Nstruct)(32);
_Nglc_Pmalloc_arr_2(_Gstruct_v, _Gstruct_cap);
_Gdecl_fvar_cap = 32;
_Nglc_Pmalloc_arr_2(_Gdecl_fvar_v, _Gdecl_fvar_cap);
_Lpsr_29 = _Nglc_Nparser_Palloc_0();
_Nglc_Nlexer_Pinit_3(&_Llex_30, _Lin_data_8, _Lin_size_7);
_Lnext_row_31 = 1;
_Lnext_col_32 = 1;
_Grow = 1;
_Gcol = 1;
while(1) {
_Nglc_Ntoken _Lt_34;
uint8_t* _Lpos_40;
_Ltok_33._Frow = _Lnext_row_31;
_Ltok_33._Fcol = _Lnext_col_32;
_Lt_34 = glc_lexer_scan(&_Llex_30);
if(true) {
uint8_t* _Lpos_35;
_Lpos_35 = _Llex_30._Fstart;
while(_Lpos_35 < _Lr_end_28._Fp1) {
if(((_Lpos_35[0] == ' ') || (_Lpos_35[0] == '\t'))) {
_Ltok_33._Fcol++;
} else if(_Lpos_35[0] == '\n') {
_Ltok_33._Frow++;
_Ltok_33._Fcol = 1;
} else {
goto break_7;
}
_Lpos_35++;
continue_7:;
}
break_7:;
}
_Glast_row = _Grow;
_Glast_col = _Gcol;
_Grow = _Ltok_33._Frow;
_Gcol = _Ltok_33._Fcol;
if(((_Lt_34 >= _Nglc_Ntoken_Cid_colon) && (_Lt_34 < _Nglc_Ntoken_Cid))) {
_Ltok_33._Fid = _Nglc_Nlexer_Pget_id_3(&_Llex_30, 1, 0);
glcParse(_Lpsr_29, _Lt_34, &_Ltok_33);
} else {
switch(_Lt_34) {
case _Nglc_Ntoken_Cchar1:;
union _Nglc_Nrdr _Lr_36;
_Lr_36._Fref = _Llex_30._Fstart;
_Ltok_33._Fid = _Lr_36._Fp1[2];
glcParse(_Lpsr_29, _Lt_34, &_Ltok_33);
break;
case _Nglc_Ntoken_Cchar2:;
union _Nglc_Nrdr _Lr_37;
_Lr_37._Fref = _Llex_30._Fstart;
_Ltok_33._Fid = _Nglc_Pchar_escape_value_1(_Lr_37._Fp1[3]);
glcParse(_Lpsr_29, _Lt_34, &_Ltok_33);
break;
case _Nglc_Ntoken_Cspace_at_real_name_str:;
union _Nglc_Nrdr _Lr_start_38;
int32_t _Lstart_39;
_Lr_start_38._Fref = _Llex_30._Fstart;
_Lstart_39 = 11;
while(1) {
_Lstart_39++;
_Lr_start_38._Fpos++;
if(_Lr_start_38._Fp1[0] == '@') {
goto break_8;
}
continue_8:;
}
break_8:;
_Ltok_33._Fid = _Nglc_Nlexer_Pget_id_3(&_Llex_30, _Lstart_39, 1);
glcParse(_Lpsr_29, _Lt_34, &_Ltok_33);
break;
case _Nglc_Ntoken_Cnum_dec:;
_Ltok_33._Fid = _Nglc_Nlexer_Pget_u32_dec_1(&_Llex_30);
glcParse(_Lpsr_29, _Lt_34, &_Ltok_33);
break;
case _Nglc_Ntoken_Cnum_oct:;
_Ltok_33._Fid = _Nglc_Nlexer_Pget_u32_oct_1(&_Llex_30);
glcParse(_Lpsr_29, _Lt_34, &_Ltok_33);
break;
case _Nglc_Ntoken_Cinclude:;
_Ltok_33._Fid = _Nglc_Nlexer_Pget_include_1(&_Llex_30);
glcParse(_Lpsr_29, _Lt_34, &_Ltok_33);
break;
case _Nglc_Ntoken_Cid:;
_Ltok_33._Fid = _Nglc_Nlexer_Pget_id_3(&_Llex_30, 0, 0);
if(_Llex_30._Fcursor[0] == '(') {
_Lt_34 = _Nglc_Ntoken_Cid_lparen;
}
glcParse(_Lpsr_29, _Lt_34, &_Ltok_33);
break;
default:;
glcParse(_Lpsr_29, _Lt_34, &_Ltok_33);
break;
}
}
if(_Lt_34 == _Nglc_Ntoken_Cend) {
goto break_6;
}
_Lpos_40 = _Llex_30._Fstart;
while(_Lpos_40 < _Llex_30._Fcursor) {
if((_Lpos_40[0] & 128) == 0) {
if(_Lpos_40[0] == '\n') {
_Lnext_row_31++;
_Lnext_col_32 = 1;
} else {
_Lnext_col_32++;
}
}
_Lpos_40++;
continue_9:;
}
break_9:;
continue_6:;
}
break_6:;
glcParse(_Lpsr_29, _Nglc_Ntoken_Cnil, &_Ltok_33);
_Nglc_Nparser_Pfree_1(_Lpsr_29);
_Lw_begin_41._Fref = qalloc((_Lin_size_7 << 2) + 1024);
_Lw_42._Fref = _Lw_begin_41._Fref;
Fputnum(&_Lw_42, _Gid_c);
int32_t _Li_43;
_Li_43 = 0;
for(int i = _Gid_c; i > 0; ) {
i --;
_Nglc_Nwtr_Pn1_2(&_Lw_42, _Gid_len_v[_Li_43]);
_Nglc_Nwtr_Pcopy_3(&_Lw_42, _Gid_str_v[_Li_43], _Gid_len_v[_Li_43]);
_Nglc_Nwtr_Pn1_2(&_Lw_42, 0);
continue_10:;
_Li_43++;
}
break_10:;
_Lid_bit8_c_44 = ((_Gid_c + 7) >> 3);
_Nglc_Pmalloc_arr_2(_Gid_in_header_v, _Lid_bit8_c_44);
_Nglc_Pmalloc_arr_2(_Gid_in_header_idx_v, _Gid_c);
_Nglc_Pmalloc_arr_2(_Gid_in_header_id_v, _Gid_c);
Fputnum(&_Lw_42, _Ginclude_c);
int32_t _Li_45;
_Li_45 = 0;
for(int i = _Ginclude_c; i > 0; ) {
i --;
_Nglc_Nwtr_Pn1_2(&_Lw_42, _Ginclude_len_v[_Li_45]);
_Nglc_Nwtr_Pcopy_3(&_Lw_42, _Ginclude_str_v[_Li_45], _Ginclude_len_v[_Li_45]);
_Nglc_Nwtr_Pn1_2(&_Lw_42, 0);
continue_11:;
_Li_45++;
}
break_11:;
_Lat_bit8_c_46 = ((_Gat_c + 7) >> 3);
_Nglc_Pmalloc_arr_2(_Gat_in_header_v, _Lat_bit8_c_46);
_Nglc_Pmalloc_arr_2(_Gat_in_header_idx_v, _Gat_c);
_Nglc_Pmalloc_arr_2(_Gat_in_header_at_v, _Gat_c);
Fputnum(&_Lw_42, _Gat_c);
int32_t _Li_47;
_Li_47 = 0;
for(int i = _Gat_c; i > 0; ) {
i --;
struct _Nglc_Nat_data* _Lat_48;
_Lat_48 = (&_Gat_v[_Li_47]);
_Nglc_Nname_type_Pwr_2((*_Lat_48)._Ftype, &_Lw_42);
if((*_Lat_48)._Ftype == _Nglc_Nname_type_Cbasic) {
_Nglc_Nbasic_type_id_Pwr_2((*_Lat_48)._Fname._Fbasic, &_Lw_42);
} else {
_Nglc_Nat_Pwr_3((*_Lat_48)._Fparent, &_Lw_42, false);
_Nglc_Nid_Pwr_3((*_Lat_48)._Fname._Fid, &_Lw_42, false);
}
continue_12:;
_Li_47++;
}
break_12:;
_Nglc_Pwrite_cvar_2(&_Lw_42, false);
_Nglc_Pwrite_gvar_2(&_Lw_42, false);
_Nglc_Pwrite_enum_2(&_Lw_42, false);
_Nglc_Pwrite_struct_2(&_Lw_42, false);
_Nglc_Pwrite_func_2(&_Lw_42, false);
_Lout_path_49 = malloc(strlen(_Llock_path_3) + 4 + 1);
sprintf(_Lout_path_49, "%s.tmp", _Llock_path_3);
_Lout_path_len_50 = strlen(_Lout_path_49);
if(!(_Nstdc_Nfd_Popen_4(&_Lout_fd_51, _Lout_path_49, O_CREAT | O_TRUNC | O_WRONLY, 32676))) {
fprintf(stdout, "Cannot open file for writing: %s\n", _Lout_path_49);
exit(_Nstdc_Nexit_Cfailure);
}
write(_Lout_fd_51, _Lw_begin_41._Fref, _Lw_42._Fpos - _Lw_begin_41._Fpos);
_Nstdc_Nfd_Pclose_1(_Lout_fd_51);
_Lw_42._Fref = _Lw_begin_41._Fref;
Fputnum(&_Lw_42, _Gid_in_header_c);
int32_t _Lj_52;
_Lj_52 = 0;
for(int i = _Gid_in_header_c; i > 0; ) {
i --;
uint32_t _Li_53;
_Li_53 = _Gid_in_header_id_v[_Lj_52];
_Nglc_Nwtr_Pn1_2(&_Lw_42, _Gid_len_v[_Li_53]);
_Nglc_Nwtr_Pcopy_3(&_Lw_42, _Gid_str_v[_Li_53], _Gid_len_v[_Li_53]);
_Nglc_Nwtr_Pn1_2(&_Lw_42, 0);
continue_13:;
_Lj_52++;
}
break_13:;
Fputnum(&_Lw_42, _Ginclude_c);
int32_t _Li_54;
_Li_54 = 0;
for(int i = _Ginclude_c; i > 0; ) {
i --;
_Nglc_Nwtr_Pn1_2(&_Lw_42, _Ginclude_len_v[_Li_54]);
_Nglc_Nwtr_Pcopy_3(&_Lw_42, _Ginclude_str_v[_Li_54], _Ginclude_len_v[_Li_54]);
_Nglc_Nwtr_Pn1_2(&_Lw_42, 0);
continue_14:;
_Li_54++;
}
break_14:;
Fputnum(&_Lw_42, _Gat_in_header_c);
int32_t _Lj_55;
_Lj_55 = 0;
for(int i = _Gat_in_header_c; i > 0; ) {
i --;
uint32_t _Li_56;
struct _Nglc_Nat_data* _Lat_57;
_Li_56 = _Gat_in_header_at_v[_Lj_55];
_Lat_57 = (&_Gat_v[_Li_56]);
_Nglc_Nname_type_Pwr_2((*_Lat_57)._Ftype, &_Lw_42);
if((*_Lat_57)._Ftype == _Nglc_Nname_type_Cbasic) {
_Nglc_Nbasic_type_id_Pwr_2((*_Lat_57)._Fname._Fbasic, &_Lw_42);
} else {
_Nglc_Nat_Pwr_header_2((*_Lat_57)._Fparent, &_Lw_42);
_Nglc_Nid_Pwr_header_2((*_Lat_57)._Fname._Fid, &_Lw_42);
}
continue_15:;
_Lj_55++;
}
break_15:;
_Nglc_Pwrite_cvar_2(&_Lw_42, true);
_Nglc_Pwrite_gvar_2(&_Lw_42, true);
_Nglc_Pwrite_enum_2(&_Lw_42, true);
_Nglc_Pwrite_struct_2(&_Lw_42, true);
_Nglc_Pwrite_func_2(&_Lw_42, true);
_Lout_path_49[(_Lout_path_len_50 - 5)] = 'h';
if(!(_Nstdc_Nfd_Popen_4(&_Lout_fd_51, _Lout_path_49, O_CREAT | O_TRUNC | O_WRONLY, 32676))) {
fprintf(stdout, "Cannot open file for writing: %s\n", _Lout_path_49);
exit(_Nstdc_Nexit_Cfailure);
}
write(_Lout_fd_51, _Lw_begin_41._Fref, _Lw_42._Fpos - _Lw_begin_41._Fpos);
_Nstdc_Nfd_Pclose_1(_Lout_fd_51);
_Lout_path_49[(_Lout_path_len_50 - 5)] = 'b';
memcpy(_Lfinal_path_58, _Lout_path_49, _Lout_path_len_50 - 4);
_Lfinal_path_58[(_Lout_path_len_50 - 4)] = 0;
rename(_Lout_path_49, _Lfinal_path_58);
_Glock_path = NULL;
_Lout_path_49[(_Lout_path_len_50 - 5)] = 'h';
memcpy(_Lfinal_path_58, _Lout_path_49, _Lout_path_len_50 - 4);
_Lfinal_path_58[(_Lout_path_len_50 - 4)] = 0;
rename(_Lout_path_49, _Lfinal_path_58);
return 0;
}
void _Nglc_Ppreprocess_def_2(char* _Lname_0, uint8_t _Llen_1) {
uint32_t _Li_2;
printf("defining preprocessor %s\n", _Lname_0);
_Li_2 = _Gpreprocess_def_c++;
if(_Gpreprocess_def_cap < _Gpreprocess_def_c) {
_Gpreprocess_def_cap = ((_Gpreprocess_def_c << 1) + 8);
_Gpreprocess_def_str_v = realloc(_Gpreprocess_def_str_v, _Gpreprocess_def_cap * sizeof(size_t));
_Gpreprocess_def_len_v = realloc(_Gpreprocess_def_len_v, _Gpreprocess_def_cap * sizeof(size_t));
}
_Gpreprocess_def_str_v[_Li_2] = _Lname_0;
_Gpreprocess_def_len_v[_Li_2] = _Llen_1;
}
void _Nglc_Pexport_0() {
qalloc_undo(0);
_Nglc_Pdecl_func_begin_3(_Nglc_Nid_C0, 0, 0);
_Nglc_Pdecl_func_end_2(0, 0);
_Nglc_Pdecl_struct_end_2(0, 0);
_Nglc_Pdecl_var_begin_3(_Nglc_Nid_C0, 0, 0);
_Nglc_Pdecl_var_attr_real_name_1(_Nglc_Nid_Cnil);
_Nglc_Pdecl_var_attr_extern_0();
_Nglc_Pdecl_var_attr_no_decl_0();
_Nglc_Pdecl_var_end_0();
_Nglc_Pdecl_var_as_farg_2(0, 0);
_Nglc_Pfarg_next_group_0();
_Nglc_Pdecl_var_as_this_0();
_Nglc_Pdecl_var_as_fvar_0();
_Nglc_Pfunc_body_end_0();
_Nglc_Pexpr_push_call_2(0, 0);
_Nglc_Pexpr_pop_func_2(_Nglc_Nat_Cnil, _Nglc_Nid_Cnil);
_Nglc_Pexpr_pop_method_2(_Nglc_Nexpr_i_Cnil, _Nglc_Nid_Cnil);
_Nglc_Pcarg_push_1(_Nglc_Nexpr_i_Cnil);
_Nglc_Pcarg_push_str_1(_Nglc_Nexpr_i_Cnil);
_Nglc_Pcarg_next_group_0();
_Nglc_Pexpr2stmt_5(_Nglc_Nexpr_i_Cnil, 0, 0, 0, 0);
_Nglc_Pstmt_return_5(_Nglc_Nexpr_i_Cnil, 0, 0, 0, 0);
_Nglc_Pstmt_continue_5(_Nglc_Nid_Cnil, 0, 0, 0, 0);
_Nglc_Pstmt_break_5(_Nglc_Nid_Cnil, 0, 0, 0, 0);
_Nglc_Pfunc_attr_main_0();
_Nglc_Pfunc_attr_decl_0();
_Nglc_Pfunc_attr_cgl_name_0();
_Nglc_Pfunc_attr_process_0();
_Nglc_Pfunc_attr_inline_0();
_Nglc_Pfunc_attr_var_args_0();
_Nglc_Pfunc_attr_no_decl_0();
_Nglc_Pfunc_attr_no_body_0();
_Nglc_Pfunc_attr_real_name_1(_Nglc_Nid_Cnil);
_Nglc_Pfunc_attr_case_1(_Nglc_Nid_Cnil);
_Nglc_Pexpr_lvar_4(_Nglc_Nid_C0, 0, 0, 0);
_Nglc_Pexpr_gvar_2(_Nglc_Nat_Cnil, _Nglc_Nid_C0);
_Nglc_Pexpr_fvar_2(_Nglc_Nexpr_i_Cnil, _Nglc_Nid_Cnil);
_Nglc_Pexpr_assign_3(_Nglc_Nexpr_i_C0, _Nglc_Nexpr_i_C0, _Nglc_Nassign_Ceq);
_Nglc_Pexpr_math_3(_Nglc_Nexpr_i_C0, _Nglc_Nexpr_i_C0, _Nglc_Nmath_Cadd);
_Nglc_Pexpr_math_add_2(_Nglc_Nexpr_i_C0, _Nglc_Nexpr_i_C0);
_Nglc_Pexpr_bools_3(_Nglc_Nexpr_i_C0, _Nglc_Nexpr_i_C0, _Nglc_Nbools_Cand);
_Nglc_Pexpr_bools_add_2(_Nglc_Nexpr_i_C0, _Nglc_Nexpr_i_C0);
_Nglc_Ptoken_name_1(_Nglc_Ntoken_Cnil);
_Nglc_Pdecl_var_type_1(_Nglc_Nat_Cnil);
_Nglc_Pdecl_var_this_0();
_Nglc_Pstmt_lvar_add_4(_Nglc_Nid_C0, _Nglc_Nexpr_i_Cnil, 0, 0);
_Nglc_Pstmt_lvar_end_2(0, 0);
_Nglc_Pdecl_include_begin_3(_Nglc_Ninclude_C0, 0, 0);
_Nglc_Pdecl_include_end_0();
_Nglc_Pdecl_at_basic_1(_Nglc_Nbasic_type_id_Croot);
_Nglc_Pdecl_at_add_2(_Nglc_Nid_C0, _Nglc_Nname_type_Cmodule);
_Nglc_Pdecl_at_begin_2(0, 0);
_Nglc_Pdecl_at_begin_struct_3(_Nglc_Nid_Cnil, 0, 0);
_Nglc_Pdecl_at_end_0();
_Nglc_Pdecl_alias_4(_Nglc_Nid_Cnil, _Nglc_Nat_Cnil, 0, 0);
_Nglc_Pat_push_4(_Nglc_Nid_C0, _Nglc_Nname_type_Cmodule, 0, 0);
_Nglc_Pat_done_0();
_Nglc_Pat_begin_0();
_Nglc_Pat_begin_relative_0();
_Nglc_Pat_begin_relative_pause_0();
_Nglc_Pat_begin_relative_resume_0();
_Nglc_Pat_root_0();
_Nglc_Pat_alias_3(_Nglc_Nid_Cnil, 0, 0);
_Nglc_Pat_graves_3(0, 0, 0);
_Nglc_Pat_basic_type_1(_Nglc_Nbasic_type_id_Ci32);
_Nglc_Pdecl_var_as_gvar_0();
_Nglc_Ptype_info_arr_2(NULL, 0);
_Nglc_Ptype_info_ref_1(0);
_Nglc_Ptype_info_static_0();
_Nglc_Ptype_info_begin_0();
_Nglc_Ptype_info_finalize_0();
_Nglc_Pexpr_int_2(0, _Nglc_Nexpr_int_Cdec);
_Nglc_Pexpr_size_of_type_1(_Nglc_Nat_Cnil);
_Nglc_Pexpr_null_0();
_Nglc_Pdecl_at_begin_enum_3(_Nglc_Nid_Cnil, 0, 0);
_Nglc_Pdecl_enum_end_3(_Nglc_Nat_Cnil, 0, 0);
_Nglc_Pexpr_cvar_2(_Nglc_Nat_Cnil, _Nglc_Nid_Cnil);
_Nglc_Penum_add_cvar_3(_Nglc_Nid_Cnil, 0, 0);
_Nglc_Pdecl_add_cvar_3(_Nglc_Nid_Cnil, 0, 0);
_Nglc_Penum_set_cvar_expr_1(_Nglc_Nexpr_i_Cnil);
_Nglc_Pstruct_attr_real_name_1(_Nglc_Nid_Cnil);
_Nglc_Pstruct_attr_union_0();
_Nglc_Pstruct_attr_no_decl_0();
_Nglc_Pexpr_str_1(_Nglc_Nexpr_i_Cnil);
_Nglc_Pexpr_unary_2(_Nglc_Nexpr_i_Cnil, _Nglc_Nunary_Cneg);
_Nglc_Pexpr_ref_1(_Nglc_Nexpr_i_Cnil);
_Nglc_Pexpr_cast_fast_2(_Nglc_Nexpr_i_Cnil, _Nglc_Nat_Cnil);
_Nglc_Pexpr_index_3(_Nglc_Nexpr_i_Cnil, NULL, 0);
_Nglc_Penum_base_begin_0();
_Nglc_Pstmt_switch_begin_0();
_Nglc_Pstmt_switch_set_6(_Nglc_Nexpr_i_Cnil, 0, 0, 0, 0, _Nglc_Nexpr_i_Cnil);
_Nglc_Pstmt_switch_expr_add_1(_Nglc_Nexpr_i_Cnil);
_Nglc_Pstmt_switch_case_begin_5(0, 0, 0, 0, false);
_Nglc_Pstmt_switch_case_end_0();
_Nglc_Pstmt_switch_default_begin_5(0, 0, 0, 0, false);
_Nglc_Pstmt_switch_default_end_0();
_Nglc_Pstmt_switch_end_0();
_Nglc_Pstmt_if_begin_0();
_Nglc_Pstmt_if_set_6(false, _Nglc_Nexpr_i_Cnil, 0, 0, 0, 0);
_Nglc_Pstmt_if_end_0();
_Nglc_Pstmt_do_begin_0();
_Nglc_Pstmt_do_set_6(_Nglc_Nexpr_i_Cnil, 0, 0, 0, 0, NULL);
_Nglc_Pstmt_do_end_0();
_Nglc_Pstmt_while_begin_0();
_Nglc_Pstmt_while_set_6(_Nglc_Nexpr_i_Cnil, 0, 0, 0, 0, NULL);
_Nglc_Pstmt_while_end_0();
_Nglc_Pstmt_elif_begin_0();
_Nglc_Pstmt_elif_set_6(false, _Nglc_Nexpr_i_Cnil, 0, 0, 0, 0);
_Nglc_Pstmt_elif_end_0();
_Nglc_Pstmt_else_set_0();
_Nglc_Pstmt_else_end_0();
_Nglc_Pstmt_if_end_ifs_0();
_Nglc_Pstmt_space_begin_0();
_Nglc_Pstmt_space_begin_detach_0();
_Nglc_Pstmt_space_end_0();
_Nglc_Pexpr_compare_3(_Nglc_Nexpr_i_Cnil, _Nglc_Nexpr_i_Cnil, _Nglc_Ncompare_Ceq);
_Nglc_Pexpr_bool_1(false);
_Nglc_Pexpr_char_1(0);
_Nglc_Pcvar_attr_real_name_1(_Nglc_Nid_Cnil);
_Nglc_Pcvar_attr_no_decl_0();
}
void _Nglc_Pquick_alloc_init_0() {
_Gquick_alloc_cap = (16 * 1024);
_Gquick_alloc_v = malloc(_Gquick_alloc_cap);
memset(_Gquick_alloc_v, 0, _Gquick_alloc_cap);
}
inline bool _Nstdc_Nfd_Popen_3(_Nstdc_Nfd* _Lfile_0, char* _Lpath_1, _Nstdc_Nopen_flags _Lflags_2) {
_Nstdc_Nfd _Lfd_3;
_Lfd_3 = open(_Lpath_1, _Lflags_2);
if(_Lfd_3 != -1) {
(*_Lfile_0) = _Lfd_3;
return true;
} else {
return false;
}
}
inline int32_t _Nstdc_Nfd_Pstat_2(_Nstdc_Nfd _Lfile_0, struct stat* _Lstat_1) {
return fstat(_Lfile_0, _Lstat_1);
}
inline int32_t _Nstdc_Nfd_Pclose_1(_Nstdc_Nfd _Lfile_0) {
return close(_Lfile_0);
}
void _Nglc_Pget_row_col_4(int32_t* _Lout_row_0, int32_t* _Lout_col_1, void* _Lend_2, void* _Lbegin_3) {
int32_t _Lrow_4;
int32_t _Lcol_5;
union _Nglc_Nrdr _Lr_6;
union _Nglc_Nrdr _Lr_end_7;
_Lrow_4 = 1;
_Lcol_5 = 1;
_Lr_6._Fref = _Lbegin_3;
_Lr_end_7._Fref = _Lend_2;
while(_Lr_6._Fpos < _Lr_end_7._Fpos) {
if(_Lr_6._Fp1[0] == '\n') {
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
if(_Lr_6._Fp1[0] == '\n') {
(*_Lout_col_1) = (_Lcol_5 - 1);
} else {
(*_Lout_col_1) = _Lcol_5;
}
}
void _Nglc_Pparse_comment_4(union _Nglc_Nrdr* _Lr_0, union _Nglc_Nwtr* _Lw_1, char _Lending_2, void* _Lin_data_3) {
union _Nglc_Nrdr _Lr_begin_4;
_Lr_begin_4._Fpos = (*_Lr_0)._Fpos;
(*_Lr_0)._Fpos += 2;
while(1) {
uint8_t _Lc_5;
_Lc_5 = (*_Lr_0)._Fp1[0];
if(_Lc_5 == '\n') {
int32_t _Lrow_6;
int32_t _Lcol_7;
_Nglc_Pget_row_col_4(&_Lrow_6, &_Lcol_7, (*_Lr_0)._Fref, _Lin_data_3);
fprintf(stdout, "%s:%u:%u: Unterminated comment\n", input_path, _Lrow_6, _Lcol_7);
exit(_Nstdc_Nexit_Cfailure);
}
(*_Lr_0)._Fpos++;
if(_Lc_5 == _Lending_2) {
size_t _Llen_8;
_Llen_8 = ((*_Lr_0)._Fpos - _Lr_begin_4._Fpos);
for(int i = _Llen_8; i > 0; ) {
i --;
(*_Lw_1)._Fp1[0] = ' ';
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
void _Nglc_Pparse_string_4(union _Nglc_Nrdr* _Lr_0, union _Nglc_Nwtr* _Lw_1, char _Lending_2, void* _Lin_data_3) {
(*_Lw_1)._Fp1[0] = '\'';
(*_Lw_1)._Fp1[1] = (*_Lr_0)._Fp1[1];
(*_Lw_1)._Fpos += 2;
(*_Lr_0)._Fpos += 2;
while(1) {
uint8_t _Lc_4;
_Lc_4 = (*_Lr_0)._Fp1[0];
if(_Lc_4 == '\n') {
int32_t _Lrow_5;
int32_t _Lcol_6;
_Nglc_Pget_row_col_4(&_Lrow_5, &_Lcol_6, (*_Lr_0)._Fref, _Lin_data_3);
fprintf(stdout, "%s:%u:%u: Unterminated string\n", input_path, _Lrow_5, _Lcol_6);
exit(_Nstdc_Nexit_Cfailure);
}
(*_Lw_1)._Fp1[0] = _Lc_4;
(*_Lw_1)._Fpos++;
(*_Lr_0)._Fpos++;
if(_Lc_4 == _Lending_2) {
return;
}
continue_0:;
}
break_0:;
}
void _Nglc_Ppreprocess_2(void** _Lin_out_data_0, size_t* _Lin_out_size_1) {
char* _Lin_data_2;
size_t _Lin_size_3;
union _Nglc_Nrdr _Lr_end_4;
union _Nglc_Nrdr _Lr_5;
void* _Lnew_data_6;
union _Nglc_Nwtr _Lw_7;
int32_t _Lline_8;
union _Nglc_Nwtr _Lw_begin_15;
printf("#if detected, preprocessing...\n");
_Lin_data_2 = (*_Lin_out_data_0);
_Lin_size_3 = (*_Lin_out_size_1);
_Lr_end_4._Fref = _Lin_data_2;
_Lr_end_4._Fpos += _Lin_size_3;
_Lr_5._Fref = _Lin_data_2;
_Lnew_data_6 = malloc(_Lin_size_3 + 1);
_Lw_7._Fref = _Lnew_data_6;
_Lline_8 = 0;
while(_Lr_5._Fpos < _Lr_end_4._Fpos) {
int32_t _Lline_len_9;
_Lline_8++;
_Lline_len_9 = 0;
while(1) {
if(_Lr_5._Fp1[_Lline_len_9] == '\n') {
if(((_Lr_5._Fp1[0] == '#') && (_Lr_5._Fp1[1] == 'i') && (_Lr_5._Fp1[2] == 'f') && ((_Lr_5._Fp1[3] == '(') || ((_Lr_5._Fp1[3] == '!') && (_Lr_5._Fp1[4] == '('))))) {
int32_t _Lstart_10;
bool _Linvert_11;
int32_t _Lrparen_12;
bool _Lok_14;
_Lw_7._Fp1[0] = '\n';
_Lw_7._Fpos++;
_Lstart_10 = 4;
_Linvert_11 = false;
if(_Lr_5._Fp1[3] == '!') {
_Lstart_10 = 5;
_Linvert_11 = true;
}
_Lrparen_12 = -1;
int32_t _Li_13;
_Li_13 = _Lstart_10;
for(int i = _Lline_len_9 - _Lstart_10; i > 0; ) {
i --;
if(_Lr_5._Fp1[_Li_13] == ')') {
_Lrparen_12 = _Li_13;
goto break_2;
}
continue_2:;
_Li_13++;
}
break_2:;
if(_Lrparen_12 == -1) {
printf("%s:%u: Error in preprocessing the code, #if(...) must have a closing parenthesis ')'\n", input_path, _Lline_8);
exit(_Nstdc_Nexit_Cfailure);
}
_Lok_14 = _Nglc_Ppreprocess_def_get_2(&_Lr_5._Fchar[_Lstart_10], _Lrparen_12 - _Lstart_10);
if(_Linvert_11) {
}
} else {
memcpy(_Lw_7._Fp1, _Lr_5._Fp1, _Lline_len_9 + 1);
_Lw_7._Fpos += (_Lline_len_9 + 1);
}
_Lline_len_9++;
goto break_1;
}
_Lline_len_9++;
continue_1:;
}
break_1:;
_Lr_5._Fpos += _Lline_len_9;
continue_0:;
}
break_0:;
free(_Lin_data_2);
(*_Lin_out_data_0) = _Lnew_data_6;
_Lw_begin_15._Fref = _Lnew_data_6;
(*_Lin_out_size_1) = (_Lw_7._Fpos - _Lw_begin_15._Fpos);
}
void _Nglc_Nlexer_Pinit_3(struct _Nglc_Nlexer* _Llex_0, uint8_t* _Ldata_1, size_t _Lsize_2) {
(*_Llex_0)._Fstart = _Ldata_1;
(*_Llex_0)._Fcursor = _Ldata_1;
(*_Llex_0)._Fcontent = _Ldata_1;
(*_Llex_0)._Flimit = &_Ldata_1[_Lsize_2];
}
int32_t _Nglc_Nlexer_Pget_id_3(struct _Nglc_Nlexer* _Llex_0, uint8_t _Lbegin_1, uint8_t _Lend_2) {
union _Nglc_Nrdr _Lr_start_3;
union _Nglc_Nrdr _Lr_cursor_4;
size_t _Llength_5;
uint8_t _Llen_6;
int32_t _Lfound_7;
_Lr_start_3._Fref = (*_Llex_0)._Fstart;
_Lr_start_3._Fpos += _Lbegin_1;
_Lr_cursor_4._Fref = (*_Llex_0)._Fcursor;
_Llength_5 = (_Lr_cursor_4._Fpos - _Lr_start_3._Fpos - _Lend_2);
if(_Llength_5 > 255) {
fprintf(stdout, "too long id was detected\n");
exit(_Nstdc_Nexit_Cfailure);
}
_Llen_6 = (uint8_t)(_Llength_5);
_Lfound_7 = _Nglc_Nmap_Pget_or_insert_4(&_Gid_map, _Lr_start_3._Fref, _Llen_6, _Gid_c);
if(_Lfound_7 == -1) {
int32_t _Lid_8;
char* _Ltext_10;
_Lid_8 = _Gid_c++;
if(_Gid_cap <= _Gid_c) {
int32_t _Lold_cap_9;
_Lold_cap_9 = _Gid_cap;
_Nglc_Pgrow_2(_Gid_cap, _Gid_c);
_Nglc_Prealloc_3(_Gid_str_v, _Gid_cap, _Lold_cap_9);
_Nglc_Prealloc_3(_Gid_len_v, _Gid_cap, _Lold_cap_9);
}
_Ltext_10 = qalloc(_Llen_6 + 1);
memcpy(_Ltext_10, _Lr_start_3._Fref, _Llen_6);
_Ltext_10[_Llen_6] = 0;
_Gid_str_v[_Lid_8] = _Ltext_10;
_Gid_len_v[_Lid_8] = _Llen_6;
return _Lid_8;
} else {
return _Lfound_7;
}
}
uint32_t _Nglc_Nlexer_Pget_u32_dec_1(struct _Nglc_Nlexer* _Llex_0) {
union _Nglc_Nrdr _Lr_start_1;
union _Nglc_Nrdr _Lr_cursor_2;
size_t _Llength_3;
uint64_t _Lval_4;
_Lr_start_1._Fref = (*_Llex_0)._Fstart;
_Lr_cursor_2._Fref = (*_Llex_0)._Fcursor;
_Llength_3 = (_Lr_cursor_2._Fpos - _Lr_start_1._Fpos);
if(_Llength_3 > 10) {
fprintf(stdout, "%s:%u:%u: Integer literal was too long\n", input_path, _Grow, _Gcol);
exit(_Nstdc_Nexit_Cfailure);
}
_Lval_4 = (uint64_t)(0);
for(int i = _Llength_3; i > 0; ) {
i --;
_Lval_4 = ((_Lval_4 * (uint64_t)(10)) + (_Lr_start_1._Fp1[0] - '0'));
_Lr_start_1._Fpos++;
continue_0:;
}
break_0:;
if(_Lval_4 > -1) {
fprintf(stdout, "%s:%u:%u: Integer literal was out of bounds\n", input_path, _Grow, _Gcol);
exit(_Nstdc_Nexit_Cfailure);
}
return (uint32_t)(_Lval_4);
}
uint32_t _Nglc_Nlexer_Pget_u32_oct_1(struct _Nglc_Nlexer* _Llex_0) {
union _Nglc_Nrdr _Lr_start_1;
union _Nglc_Nrdr _Lr_cursor_2;
size_t _Llength_3;
uint64_t _Lval_4;
_Lr_start_1._Fref = (*_Llex_0)._Fstart;
_Lr_cursor_2._Fref = (*_Llex_0)._Fcursor;
_Llength_3 = (_Lr_cursor_2._Fpos - _Lr_start_1._Fpos);
if(_Llength_3 > 12) {
fprintf(stdout, "%s:%u:%u: Integer literal was too long\n", input_path, _Grow, _Gcol);
exit(_Nstdc_Nexit_Cfailure);
}
_Lval_4 = (uint64_t)(0);
for(int i = _Llength_3; i > 0; ) {
i --;
_Lval_4 = ((_Lval_4 * (uint64_t)(8)) + (_Lr_start_1._Fp1[0] - '0'));
_Lr_start_1._Fpos++;
continue_0:;
}
break_0:;
if(_Lval_4 > -1) {
fprintf(stdout, "%s:%u:%u: Integer literal was out of bounds\n", input_path, _Grow, _Gcol);
exit(_Nstdc_Nexit_Cfailure);
}
return (uint32_t)(_Lval_4);
}
int32_t _Nglc_Nlexer_Pget_include_1(struct _Nglc_Nlexer* _Llex_0) {
union _Nglc_Nrdr _Lr_start_1;
union _Nglc_Nrdr _Lr_cursor_2;
size_t _Llength_3;
uint8_t _Llen_4;
int32_t _Lfound_5;
_Lr_start_1._Fref = (*_Llex_0)._Fstart;
_Lr_start_1._Fpos += 9;
_Lr_cursor_2._Fref = (*_Llex_0)._Fcursor;
_Llength_3 = (_Lr_cursor_2._Fpos - _Lr_start_1._Fpos - 1);
if(_Llength_3 > 255) {
fprintf(stdout, "too long include was detected\n");
exit(_Nstdc_Nexit_Cfailure);
}
_Llen_4 = (uint8_t)(_Llength_3);
_Lfound_5 = _Nglc_Nmap_Pget_or_insert_4(&_Ginclude_map, _Lr_start_1._Fref, _Llen_4, _Ginclude_c);
if(_Lfound_5 == -1) {
int32_t _Linclude_6;
char* _Ltext_8;
_Linclude_6 = _Ginclude_c++;
if(_Ginclude_cap <= _Ginclude_c) {
int32_t _Lold_cap_7;
_Lold_cap_7 = _Ginclude_cap;
_Nglc_Pgrow_2(_Ginclude_cap, _Ginclude_c);
_Nglc_Prealloc_3(_Ginclude_str_v, _Ginclude_cap, _Lold_cap_7);
_Nglc_Prealloc_3(_Ginclude_len_v, _Ginclude_cap, _Lold_cap_7);
}
_Ltext_8 = qalloc(_Llen_4 + 1);
memcpy(_Ltext_8, _Lr_start_1._Fref, _Llen_4);
_Ltext_8[_Llen_4] = 0;
_Ginclude_str_v[_Linclude_6] = _Ltext_8;
_Ginclude_len_v[_Linclude_6] = _Llen_4;
return _Linclude_6;
} else {
return _Lfound_5;
}
}
void* qalloc(int32_t _Lsize_0) {
if(sizeof(void*) == 8) {
_Lsize_0 = ((_Lsize_0 + 7) & (-1 ^ 7));
} else {
_Lsize_0 = ((_Lsize_0 + 3) & (-1 ^ 3));
}
if(_Lsize_0 <= (_Gquick_alloc_cap - _Gquick_alloc_c)) {
union _Nglc_Nrdr _Lr_1;
_Lr_1._Fref = _Gquick_alloc_v;
_Lr_1._Fpos += _Gquick_alloc_c;
_Gquick_alloc_c += _Lsize_0;
return _Lr_1._Fref;
}
_Nglc_Pgrow_2(_Gquick_alloc_cap, _Gquick_alloc_c + _Lsize_0);
_Gquick_alloc_v = malloc(_Gquick_alloc_cap);
memset(_Gquick_alloc_v, 0, _Gquick_alloc_cap);
_Gquick_alloc_c = _Lsize_0;
return _Gquick_alloc_v;
}
inline void _Nglc_Nwtr_Pn1_2(union _Nglc_Nwtr* _Lw_0, uint8_t _Ln_1) {
(*_Lw_0)._Fp1[0] = _Ln_1;
(*_Lw_0)._Fpos++;
}
inline void _Nglc_Nwtr_Pcopy_3(union _Nglc_Nwtr* _Lw_0, void* _Ldata_1, int32_t _Lsize_2) {
memcpy((*_Lw_0)._Fref, _Ldata_1, _Lsize_2);
(*_Lw_0)._Fpos += _Lsize_2;
}
inline void _Nglc_Nname_type_Pwr_2(_Nglc_Nname_type _Li_0, union _Nglc_Nwtr* _Lw_1) {
_Nglc_Nwtr_Pn1_2(_Lw_1, _Li_0);
}
inline void _Nglc_Nbasic_type_id_Pwr_2(_Nglc_Nbasic_type_id _Le_0, union _Nglc_Nwtr* _Lw_1) {
_Nglc_Nwtr_Pn1_2(_Lw_1, _Le_0);
}
inline void _Nglc_Nat_Pwr_3(_Nglc_Nat _Lat_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2) {
if(_Lat_0 == _Nglc_Nat_Cnil) {
Fputnum(_Lw_1, 0);
} else {
if(_Lheader_2) {
Fputnum(_Lw_1, 1 + _Gat_in_header_idx_v[_Lat_0]);
} else {
Fputnum(_Lw_1, 1 + _Lat_0);
_Nglc_Nat_Pput_to_header_1(_Lat_0);
}
}
}
inline void _Nglc_Nid_Pwr_3(_Nglc_Nid _Lid_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2) {
if(_Lid_0 == _Nglc_Nid_Cnil) {
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
void _Nglc_Pwrite_cvar_2(union _Nglc_Nwtr* _Lw_0, bool _Lheader_1) {
Fputnum(_Lw_0, _Gcvar_c);
int32_t _Li_2;
_Li_2 = 0;
for(int i = _Gcvar_c; i > 0; ) {
i --;
struct _Nglc_Ncvar_data* _Lcvar_3;
_Lcvar_3 = (&_Gcvar_v[_Li_2]);
_Nglc_Ninclude_Pwr_2((*_Lcvar_3)._Finclude, _Lw_0);
_Nglc_Nat_Pwr_3((*_Lcvar_3)._Fat, _Lw_0, _Lheader_1);
_Nglc_Ndecl_var_data_Pwr_3(&(*_Lcvar_3)._Fdecl, _Lw_0, _Lheader_1);
_Nglc_Ncvar_flags_Pwr_2((*_Lcvar_3)._Fflags, _Lw_0);
if(((*_Lcvar_3)._Fflags & _Nglc_Ncvar_flags_Cset_expr) != _Nglc_Ncvar_flags_C0) {
_Nglc_Nexpr_i_Pwr_3((*_Lcvar_3)._Fexpr_set, _Lw_0, _Lheader_1);
} else {
_Nglc_Ncvar_Pwr_2((*_Lcvar_3)._Flast_cvar, _Lw_0);
}
continue_0:;
_Li_2++;
}
break_0:;
}
void _Nglc_Pwrite_gvar_2(union _Nglc_Nwtr* _Lw_0, bool _Lheader_1) {
Fputnum(_Lw_0, _Ggvar_c);
int32_t _Li_2;
_Li_2 = 0;
for(int i = _Ggvar_c; i > 0; ) {
i --;
struct _Nglc_Ndecl_gvar* _Lgvar_3;
_Lgvar_3 = (&_Ggvar_v[_Li_2]);
_Nglc_Ninclude_Pwr_2((*_Lgvar_3)._Finclude, _Lw_0);
_Nglc_Nat_Pwr_3((*_Lgvar_3)._Fat, _Lw_0, _Lheader_1);
_Nglc_Ndecl_var_data_Pwr_3(&(*_Lgvar_3)._Fdecl, _Lw_0, _Lheader_1);
continue_0:;
_Li_2++;
}
break_0:;
}
void _Nglc_Pwrite_enum_2(union _Nglc_Nwtr* _Lw_0, bool _Lheader_1) {
Fputnum(_Lw_0, _Genum_c);
int32_t _Li_2;
_Li_2 = 0;
for(int i = _Genum_c; i > 0; ) {
i --;
struct _Nglc_Nenum_data* _Le_3;
_Le_3 = _Genum_v[_Li_2++];
Fputnum(_Lw_0, (*_Le_3)._Fbegin_row);
Fputnum(_Lw_0, (*_Le_3)._Fbegin_col);
Fputnum(_Lw_0, (*_Le_3)._Fend_row);
Fputnum(_Lw_0, (*_Le_3)._Fend_col);
_Nglc_Ninclude_Pwr_2((*_Le_3)._Finclude, _Lw_0);
_Nglc_Nat_Pwr_3((*_Le_3)._Fat, _Lw_0, _Lheader_1);
_Nglc_Nat_Pwr_3((*_Le_3)._Fbase_type, _Lw_0, _Lheader_1);
_Nglc_Nenum_flags_Pwr_2((*_Le_3)._Fflags, _Lw_0);
if(((*_Le_3)._Fflags & _Nglc_Nenum_flags_Creal_name) != _Nglc_Nenum_flags_C0) {
_Nglc_Nid_Pwr_3((*_Le_3)._Freal_name, _Lw_0, _Lheader_1);
}
continue_0:;
}
break_0:;
}
void _Nglc_Pwrite_struct_2(union _Nglc_Nwtr* _Lw_0, bool _Lheader_1) {
Fputnum(_Lw_0, _Gstruct_c);
int32_t _Li_2;
_Li_2 = 0;
for(int i = _Gstruct_c; i > 0; ) {
i --;
struct _Nglc_Nstruct_data* _Ls_3;
_Ls_3 = _Gstruct_v[_Li_2++];
_Nglc_Nwtr_Pn1_2(_Lw_0, (*_Ls_3)._Ffvar_c);
Fputnum(_Lw_0, (*_Ls_3)._Fbegin_row);
Fputnum(_Lw_0, (*_Ls_3)._Fbegin_col);
Fputnum(_Lw_0, (*_Ls_3)._Fend_row);
Fputnum(_Lw_0, (*_Ls_3)._Fend_col);
_Nglc_Ninclude_Pwr_2((*_Ls_3)._Finclude, _Lw_0);
_Nglc_Nat_Pwr_3((*_Ls_3)._Fat, _Lw_0, _Lheader_1);
_Nglc_Nstruct_flags_Pwr_2((*_Ls_3)._Fflags, _Lw_0);
int32_t _Lj_4;
_Lj_4 = 0;
for(int i = (*_Ls_3)._Ffvar_c; i > 0; ) {
i --;
_Nglc_Nfvar_data_Pwr_3(&(*_Ls_3)._Ffvar_v[_Lj_4], _Lw_0, _Lheader_1);
continue_1:;
_Lj_4++;
}
break_1:;
if(((*_Ls_3)._Fflags & _Nglc_Nstruct_flags_Creal_name) != _Nglc_Nstruct_flags_C0) {
_Nglc_Nid_Pwr_3((*_Ls_3)._Freal_name, _Lw_0, _Lheader_1);
}
continue_0:;
}
break_0:;
}
inline void _Nglc_Pwrite_func_2(union _Nglc_Nwtr* _Lw_0, bool _Lheader_1) {
Fputnum(_Lw_0, _Gfunc_c);
int32_t _Li_2;
_Li_2 = 0;
for(int i = _Gfunc_c; i > 0; ) {
i --;
struct _Nglc_Ndecl_func* _Lf_3;
_Lf_3 = _Gfunc_v[_Li_2++];
_Nglc_Nwtr_Pn1_2(_Lw_0, (*_Lf_3)._Ffarg_c);
Fputnum(_Lw_0, (*_Lf_3)._Fbegin_row);
Fputnum(_Lw_0, (*_Lf_3)._Fbegin_col);
Fputnum(_Lw_0, (*_Lf_3)._Fend_row);
Fputnum(_Lw_0, (*_Lf_3)._Fend_col);
_Nglc_Ninclude_Pwr_2((*_Lf_3)._Finclude, _Lw_0);
_Nglc_Nat_Pwr_3((*_Lf_3)._Fat, _Lw_0, _Lheader_1);
_Nglc_Ndecl_var_data_Pwr_3(&(*_Lf_3)._Fdecl, _Lw_0, _Lheader_1);
int32_t _Lj_4;
_Lj_4 = 0;
for(int i = (*_Lf_3)._Ffarg_c; i > 0; ) {
i --;
_Nglc_Nfarg_Pwr_3(&(*_Lf_3)._Ffarg_v[_Lj_4], _Lw_0, _Lheader_1);
continue_1:;
_Lj_4++;
}
break_1:;
_Nglc_Nwtr_Pn1_2(_Lw_0, (*_Lf_3)._Fthis_idx);
if((*_Lf_3)._Fthis_idx != -1) {
_Nglc_Nwtr_Pn1_2(_Lw_0, (*_Lf_3)._Fthis_group);
}
_Nglc_Nwtr_Pn1_2(_Lw_0, (*_Lf_3)._Fgroup_c);
int32_t _Lj_5;
_Lj_5 = 0;
for(int i = (*_Lf_3)._Fgroup_c; i > 0; ) {
i --;
_Nglc_Nwtr_Pn1_2(_Lw_0, (*_Lf_3)._Fgroup_v[_Lj_5]);
continue_2:;
_Lj_5++;
}
break_2:;
if(_Lheader_1) {
if((*_Lf_3)._Fflags & _Nglc_Nfunc_flags_Cinline) {
_Nglc_Nfunc_flags_Pwr_2((*_Lf_3)._Fflags, _Lw_0);
} else {
_Nglc_Nfunc_flags_Pwr_2((_Nglc_Nfunc_flags)((*_Lf_3)._Fflags & (-1 ^ _Nglc_Nfunc_flags_Chas_body)), _Lw_0);
}
} else {
_Nglc_Nfunc_flags_Pwr_2((*_Lf_3)._Fflags, _Lw_0);
}
if(((*_Lf_3)._Fflags & _Nglc_Nfunc_flags_Creal_name) != _Nglc_Nfunc_flags_C0) {
_Nglc_Nid_Pwr_3((*_Lf_3)._Freal_name, _Lw_0, _Lheader_1);
}
if(((*_Lf_3)._Fflags & _Nglc_Nfunc_flags_Ccase) != _Nglc_Nfunc_flags_C0) {
_Nglc_Nid_Pwr_3((*_Lf_3)._Fcase, _Lw_0, _Lheader_1);
}
if(((*_Lf_3)._Fflags & _Nglc_Nfunc_flags_Cdecl) != _Nglc_Nfunc_flags_C0) {
Fputnum(_Lw_0, (*_Lf_3)._Fdecl_len);
_Nglc_Nwtr_Pcopy_3(_Lw_0, (*_Lf_3)._Fdecl_str, (*_Lf_3)._Fdecl_len);
}
continue_0:;
}
break_0:;
_Nglc_Nfunc_Pwr_2(_Gfunc_main, _Lw_0);
int32_t _Li_6;
_Li_6 = 0;
for(int i = _Gfunc_c; i > 0; ) {
i --;
struct _Nglc_Ndecl_func* _Lf_7;
union _Nglc_Nwtr _Lpos_4_8;
size_t _Lpos_4_next_9;
_Lf_7 = _Gfunc_v[_Li_6++];
if(((*_Lf_7)._Fflags & _Nglc_Nfunc_flags_Chas_body) == _Nglc_Nfunc_flags_C0) {
goto continue_3;
}
if(_Lheader_1) {
if((*_Lf_7)._Fflags & _Nglc_Nfunc_flags_Cinline) {
} else {
goto continue_3;
}
}
_Lpos_4_8._Fp1 = (*_Lw_0)._Fp1;
(*_Lw_0)._Fpos += 4;
_Lpos_4_next_9 = (*_Lw_0)._Fpos;
_Nglc_Ndecl_func_Plvars_wr_3(_Lf_7, _Lw_0, _Lheader_1);
_Nglc_Nstmt_space_Pwr_3((*_Lf_7)._Fstmt_space, _Lw_0, _Lheader_1);
_Nglc_Nwtr_Pn4_2(&_Lpos_4_8, (*_Lw_0)._Fpos - _Lpos_4_next_9);
continue_3:;
}
break_3:;
}
inline bool _Nstdc_Nfd_Popen_4(_Nstdc_Nfd* _Lfile_0, char* _Lpath_1, _Nstdc_Nopen_flags _Lflags_2, int32_t _Lmode_3) {
_Nstdc_Nfd _Lfd_4;
_Lfd_4 = open(_Lpath_1, _Lflags_2, _Lmode_3);
if(_Lfd_4 != -1) {
(*_Lfile_0) = _Lfd_4;
return true;
} else {
return false;
}
}
inline void _Nglc_Nat_Pwr_header_2(_Nglc_Nat _Lid_0, union _Nglc_Nwtr* _Lw_1) {
if(_Lid_0 == _Nglc_Nat_Cnil) {
Fputnum(_Lw_1, 0);
} else {
Fputnum(_Lw_1, 1 + _Gat_in_header_idx_v[_Lid_0]);
}
}
inline void _Nglc_Nid_Pwr_header_2(_Nglc_Nid _Lid_0, union _Nglc_Nwtr* _Lw_1) {
if(_Lid_0 == _Nglc_Nid_Cnil) {
Fputnum(_Lw_1, 0);
} else {
Fputnum(_Lw_1, 1 + _Gid_in_header_idx_v[_Lid_0]);
}
}
void qalloc_undo(int32_t _Lsize_0) {
if(sizeof(void*) == 8) {
_Lsize_0 = ((_Lsize_0 + 7) & (-1 ^ 7));
} else {
_Lsize_0 = ((_Lsize_0 + 3) & (-1 ^ 3));
}
_Gquick_alloc_c -= _Lsize_0;
}
void _Nglc_Pdecl_func_begin_3(_Nglc_Nid _Lname_0, int32_t _Lrow_1, int32_t _Lcol_2) {
_Gdecl_func_name = _Lname_0;
_Gdecl_func_row = _Lrow_1;
_Gdecl_func_col = _Lcol_2;
_Gdecl_func_flags = _Nglc_Nfunc_flags_C0;
_Gdecl_func_flags2 = _Nglc_Nfunc_flags2_C0;
_Gdecl_farg_c = 0;
_Gdecl_farg_group_c = 1;
_Gdecl_farg_group_v[0] = 0;
_Gdecl_func_this_idx = -1;
_Gdecl_func_this_group = -1;
_Gdecl_func_real_name = _Nglc_Nid_Cnil;
_Gdecl_func_case = _Nglc_Nid_Cnil;
_Gdecl_func_decl_str = NULL;
_Gdecl_func_decl_len = 0;
_Nglc_Pquick_alloc_one_1(_Gdecl_func_space);
_Gdecl_func_ctx_space = _Gdecl_func_space;
}
void _Nglc_Pdecl_func_end_2(int32_t _Lrow_0, int32_t _Lcol_1) {
_Nglc_Nfunc _Lf_idx_2;
struct _Nglc_Ndecl_func* _Lf_4;
struct _Nglc_Nstmt_space* _Lspace_9;
_Lf_idx_2 = (_Nglc_Nfunc)(_Gfunc_c++);
if(_Gfunc_cap <= _Gfunc_c) {
_Nglc_Nfunc _Lold_cap_3;
_Lold_cap_3 = _Gfunc_cap;
_Nglc_Pgrow_2(_Gfunc_cap, _Gfunc_c);
_Nglc_Prealloc_3(_Gfunc_v, _Gfunc_cap, _Lold_cap_3);
}
_Nglc_Pquick_alloc_plus_2(_Lf_4, sizeof(struct _Nglc_Nfarg) * _Gdecl_farg_c);
_Gctx_func = _Lf_4;
_Gnest_id = 0;
_Gfunc_v[_Lf_idx_2] = _Lf_4;
(*_Lf_4)._Fbegin_row = _Gdecl_func_row;
(*_Lf_4)._Fbegin_col = _Gdecl_func_col;
(*_Lf_4)._Fend_row = _Lrow_0;
(*_Lf_4)._Fend_col = _Lcol_1;
(*_Lf_4)._Finclude = _Gdecl_include;
(*_Lf_4)._Fat = _Gdecl_at;
if((_Gdecl_func_flags & _Nglc_Nfunc_flags_Creal_name) != _Nglc_Nfunc_flags_C0) {
if(_Gdecl_func_real_name == _Nglc_Nid_Cnil) {
(*_Lf_4)._Freal_name = _Gdecl_func_name;
} else {
(*_Lf_4)._Freal_name = _Gdecl_func_real_name;
}
}
if((_Gdecl_func_flags & _Nglc_Nfunc_flags_Ccase) != _Nglc_Nfunc_flags_C0) {
(*_Lf_4)._Fcase = _Gdecl_func_case;
}
_Gdecl_var._Fname = _Gdecl_func_name;
_Nglc_Ndecl_var_data_Pcopy_from_2(&(*_Lf_4)._Fdecl, &_Gdecl_var);
(*_Lf_4)._Ffarg_c = _Gdecl_farg_c;
int32_t _Li_5;
_Li_5 = 0;
for(int i = _Gdecl_farg_c; i > 0; ) {
i --;
struct _Nglc_Nfarg* _Lfa_6;
_Lfa_6 = (&(*_Lf_4)._Ffarg_v[_Li_5]);
_Nglc_Nfarg_Pcopy_from_2(_Lfa_6, &_Gdecl_farg_v[_Li_5]);
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
if((_Gdecl_func_flags2 & _Nglc_Nfunc_flags2_Cmain) != _Nglc_Nfunc_flags2_C0) {
_Gfunc_main = _Lf_idx_2;
} else if(((_Gdecl_at == _Nglc_Nat_Croot) && (_Nglc_Nid_Plen_1((*_Lf_4)._Fdecl._Fname) == 4) && (memcmp("main", _Nglc_Nid_Pstr_1((*_Lf_4)._Fdecl._Fname), 4) == 0))) {
if(_Gfunc_main != _Nglc_Nfunc_Cnil) {
struct _Nglc_Ndecl_func* _Lmain_8;
_Lmain_8 = _Nglc_Nfunc_Pptr_1(_Gfunc_main);
fprintf(stdout, "%u:%u: There's already a function with @main attribute at %u:%u\n", (*_Lf_4)._Fbegin_row, (*_Lf_4)._Fbegin_col, (*_Lmain_8)._Fbegin_row, (*_Lmain_8)._Fbegin_col);
exit(_Nstdc_Nexit_Cfailure);
} else {
_Gfunc_main = _Lf_idx_2;
}
}
(*_Lf_4)._Fdecl_str = _Gdecl_func_decl_str;
(*_Lf_4)._Fdecl_len = _Gdecl_func_decl_len;
_Lspace_9 = _Gdecl_func_space;
(*_Lf_4)._Fstmt_space = _Lspace_9;
int32_t _Li_10;
_Li_10 = 0;
for(int i = _Gdecl_farg_c; i > 0; ) {
i --;
struct _Nglc_Nfarg* _Lfa_11;
_Nglc_Nlvar _Llvar_i_12;
struct _Nglc_Nlvar_data* _Llvar_13;
_Lfa_11 = (&(*_Lf_4)._Ffarg_v[_Li_10]);
_Llvar_i_12 = _Nglc_Nstmt_space_Plvar_new_4(_Lspace_9, (*_Lfa_11)._Fdecl._Fname, (*_Lfa_11)._Frow, (*_Lfa_11)._Fcol);
_Llvar_13 = _Nglc_Nlvar_Pptr_1(_Llvar_i_12);
_Nglc_Ndecl_var_data_Pcopy_from_2(&(*_Llvar_13)._Fdecl, &(*_Lfa_11)._Fdecl);
continue_2:;
_Li_10++;
}
break_2:;
}
void _Nglc_Pdecl_struct_end_2(int32_t _Lrow_0, int32_t _Lcol_1) {
_Nglc_Nstruct _Ls_idx_2;
struct _Nglc_Nstruct_data* _Ls_4;
_Ls_idx_2 = _Gstruct_c++;
if(_Gstruct_cap <= _Gstruct_c) {
_Nglc_Nstruct _Lold_cap_3;
_Lold_cap_3 = _Gstruct_cap;
_Nglc_Pgrow_2(_Gstruct_cap, _Gstruct_c);
_Nglc_Prealloc_3(_Gstruct_v, _Gstruct_cap, _Lold_cap_3);
}
_Nglc_Pquick_alloc_plus_2(_Ls_4, sizeof(struct _Nglc_Nfvar_data) * _Gdecl_fvar_c);
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
struct _Nglc_Nfvar_data* _La_6;
_La_6 = (&(*_Ls_4)._Ffvar_v[_Li_5]);
_Nglc_Ndecl_var_data_Pcopy_from_2(&(*_La_6)._Fdecl, &_Gdecl_fvar_v[_Li_5]);
continue_0:;
_Li_5++;
}
break_0:;
(*_Ls_4)._Freal_name = _Gdecl_struct_real_name;
}
void _Nglc_Pdecl_var_begin_3(_Nglc_Nid _Lname_0, int32_t _Lrow_1, int32_t _Lcol_2) {
_Gdecl_var._Fname = _Lname_0;
_Gdecl_var_row = _Lrow_1;
_Gdecl_var_col = _Lcol_2;
_Nglc_Ntype_info_Pinit_1(&_Gdecl_var._Ftype_info);
_Gdecl_var._Fflags = _Nglc_Nvar_flags_C0;
_Gdecl_var._Freal_name = _Nglc_Nid_Cnil;
_Gdecl_var._Fsize_c = 0;
}
void _Nglc_Pdecl_var_attr_real_name_1(_Nglc_Nid _Lname_0) {
if((_Gdecl_var._Fflags & _Nglc_Nvar_flags_Creal_name) != _Nglc_Nvar_flags_C0) {
fprintf(stdout, "%u:%u: error @real-name specified more than once\n", _Glast_row, _Glast_col);
exit(_Nstdc_Nexit_Cfailure);
}
_Gdecl_var._Fflags |= _Nglc_Nvar_flags_Creal_name;
_Gdecl_var._Freal_name = _Lname_0;
}
void _Nglc_Pdecl_var_attr_extern_0() {
if((_Gdecl_var._Fflags & _Nglc_Nvar_flags_Cextern) != _Nglc_Nvar_flags_C0) {
fprintf(stdout, "%u:%u: error @extern specified more than once\n", _Glast_row, _Glast_col);
exit(_Nstdc_Nexit_Cfailure);
}
_Gdecl_var._Fflags |= _Nglc_Nvar_flags_Cextern;
}
void _Nglc_Pdecl_var_attr_no_decl_0() {
if((_Gdecl_var._Fflags & _Nglc_Nvar_flags_Cno_decl) != _Nglc_Nvar_flags_C0) {
fprintf(stdout, "%u:%u: error @no-decl specified more than once\n", _Glast_row, _Glast_col);
exit(_Nstdc_Nexit_Cfailure);
}
_Gdecl_var._Fflags |= _Nglc_Nvar_flags_Cno_decl;
}
void _Nglc_Pdecl_var_end_0() {
}
void _Nglc_Pdecl_var_as_farg_2(int32_t _Lrow_0, int32_t _Lcol_1) {
int32_t _Lfarg_idx_2;
struct _Nglc_Nfarg* _Lfa_4;
_Lfarg_idx_2 = _Gdecl_farg_c++;
if(_Gdecl_farg_cap <= _Gdecl_farg_c) {
int32_t _Lold_cap_3;
_Lold_cap_3 = _Gdecl_farg_cap;
_Nglc_Pgrow_2(_Gdecl_farg_cap, _Gdecl_farg_c);
_Nglc_Prealloc_3(_Gdecl_farg_v, _Gdecl_farg_cap, _Lold_cap_3);
}
_Lfa_4 = (&_Gdecl_farg_v[_Lfarg_idx_2]);
(*_Lfa_4)._Frow = _Lrow_0;
(*_Lfa_4)._Fcol = _Lcol_1;
_Nglc_Ndecl_var_data_Pcopy_from_2(&(*_Lfa_4)._Fdecl, &_Gdecl_var);
_Gdecl_farg_group_v[(_Gdecl_farg_group_c - 1)]++;
}
void _Nglc_Pfarg_next_group_0() {
_Gdecl_farg_group_v[_Gdecl_farg_group_c] = 0;
_Gdecl_farg_group_c++;
}
void _Nglc_Pdecl_var_as_this_0() {
int32_t _Lfarg_idx_0;
_Gdecl_func_this_idx = _Gdecl_farg_c;
_Gdecl_func_this_group = (_Gdecl_farg_group_c - 1);
_Lfarg_idx_0 = _Gdecl_farg_c++;
if(_Gdecl_farg_cap <= _Gdecl_farg_c) {
int32_t _Lold_cap_1;
_Lold_cap_1 = _Gdecl_farg_cap;
_Nglc_Pgrow_2(_Gdecl_farg_cap, _Gdecl_farg_c);
_Nglc_Prealloc_3(_Gdecl_farg_v, _Gdecl_farg_cap, _Lold_cap_1);
}
_Nglc_Ndecl_var_data_Pcopy_from_2(&_Gdecl_farg_v[_Lfarg_idx_0]._Fdecl, &_Gdecl_var);
_Gdecl_farg_v[_Lfarg_idx_0]._Fdecl._Ftype = _Gdecl_at;
_Gdecl_farg_group_v[(_Gdecl_farg_group_c - 1)]++;
}
void _Nglc_Pdecl_var_as_fvar_0() {
uint32_t _Lfvar_0;
_Lfvar_0 = _Gdecl_fvar_c++;
if(_Gdecl_fvar_cap <= _Gdecl_fvar_c) {
uint32_t _Lold_cap_1;
_Lold_cap_1 = _Gdecl_fvar_cap;
_Nglc_Pgrow_2(_Gdecl_fvar_cap, _Gdecl_fvar_c);
_Nglc_Prealloc_3(_Gdecl_fvar_v, _Gdecl_fvar_cap, _Lold_cap_1);
}
_Nglc_Ndecl_var_data_Pcopy_from_2(&_Gdecl_fvar_v[_Lfvar_0], &_Gdecl_var);
}
void _Nglc_Pfunc_body_end_0() {
struct _Nglc_Ndecl_func* _Lf_0;
int32_t _Lc_1;
struct _Nglc_Nstmt* _Ls_2;
_Lf_0 = _Gfunc_v[(_Gfunc_c - 1)];
(*_Lf_0)._Fflags |= _Nglc_Nfunc_flags_Chas_body;
_Lc_1 = 0;
_Ls_2 = (*(*_Lf_0)._Fstmt_space)._Fstmt_first;
while(_Ls_2 != NULL) {
_Lc_1++;
_Ls_2 = (*_Ls_2)._Fstmt_next;
continue_0:;
}
break_0:;
}
void _Nglc_Pexpr_push_call_2(int32_t _Lrow_0, int32_t _Lcol_1) {
int8_t _Lcall_idx_2;
_Lcall_idx_2 = _Gexpr_call_c++;
if(_Lcall_idx_2 >= _Nglc_Cexpr_call_nest_limit) {
fprintf(stdout, "%u:%u: Too much nested calls\n", _Lrow_0, _Lcol_1);
exit(_Nstdc_Nexit_Cfailure);
}
_Gexpr_call_carg_c[_Lcall_idx_2] = 0;
_Gexpr_call_cgrp_c[_Lcall_idx_2] = 1;
_Gexpr_call_cgrp_v[_Lcall_idx_2][0] = 0;
}
_Nglc_Nexpr_i _Nglc_Pexpr_pop_func_2(_Nglc_Nat _Lat_0, _Nglc_Nid _Lfunc_name_1) {
int8_t _Lcall_idx_2;
uint8_t _Lcarg_c_3;
struct _Nglc_Nexpr_func* _Le_4;
_Nglc_Nexpr_i _Le_idx_5;
_Lcall_idx_2 = (_Gexpr_call_c -= 1);
_Lcarg_c_3 = _Gexpr_call_carg_c[_Lcall_idx_2];
_Nglc_Pquick_alloc_plus_2(_Le_4, sizeof(struct _Nglc_Ncarg) * _Lcarg_c_3);
_Le_idx_5 = _Nglc_Pexpr_push_2(&(*_Le_4)._Fbase, _Nglc_Nexpr_type_Cfunc);
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
_Nglc_Nexpr_i _Nglc_Pexpr_pop_method_2(_Nglc_Nexpr_i _Lthis_0, _Nglc_Nid _Lfunc_name_1) {
int8_t _Lcall_idx_2;
uint8_t _Lcarg_c_3;
struct _Nglc_Nexpr_method* _Le_4;
_Nglc_Nexpr_i _Le_idx_5;
_Lcall_idx_2 = (_Gexpr_call_c -= 1);
_Lcarg_c_3 = _Gexpr_call_carg_c[_Lcall_idx_2];
_Nglc_Pquick_alloc_plus_2(_Le_4, sizeof(struct _Nglc_Ncarg) * _Lcarg_c_3);
_Le_idx_5 = _Nglc_Pexpr_push_2(&(*_Le_4)._Fbase, _Nglc_Nexpr_type_Cmethod);
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
void _Nglc_Pcarg_push_1(_Nglc_Nexpr_i _Lexpr_0) {
int8_t _Lcall_idx_1;
_Lcall_idx_1 = (_Gexpr_call_c - 1);
_Gexpr_call_carg_v[_Lcall_idx_1][_Gexpr_call_carg_c[_Lcall_idx_1]++] = _Lexpr_0;
_Gexpr_call_cgrp_v[_Lcall_idx_1][(_Gexpr_call_cgrp_c[_Lcall_idx_1] - 1)]++;
}
void _Nglc_Pcarg_push_str_1(_Nglc_Nexpr_i _Lexpr_0) {
if(true) {
int8_t _Lcall_idx_1;
_Lcall_idx_1 = (_Gexpr_call_c - 1);
_Gexpr_call_carg_v[_Lcall_idx_1][_Gexpr_call_carg_c[_Lcall_idx_1]++] = _Lexpr_0;
_Gexpr_call_cgrp_v[_Lcall_idx_1][(_Gexpr_call_cgrp_c[_Lcall_idx_1] - 1)]++;
}
if(true) {
struct _Nglc_Nexpr_str* _Le_2;
int32_t _Llen_3;
struct _Nglc_Nexpr_str_node* _Ls_4;
int8_t _Lcall_idx_5;
_Le_2 = _Nglc_Nexpr_i_Pptr_1(_Lexpr_0);
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
_Gexpr_call_carg_v[_Lcall_idx_5][_Gexpr_call_carg_c[_Lcall_idx_5]++] = _Nglc_Pexpr_int_2(_Llen_3, _Nglc_Nexpr_int_Cdec);
_Gexpr_call_cgrp_v[_Lcall_idx_5][(_Gexpr_call_cgrp_c[_Lcall_idx_5] - 1)]++;
}
}
void _Nglc_Pcarg_next_group_0() {
int8_t _Lcall_idx_0;
_Lcall_idx_0 = (_Gexpr_call_c - 1);
_Gexpr_call_cgrp_v[_Lcall_idx_0][_Gexpr_call_cgrp_c[_Lcall_idx_0]] = 0;
_Gexpr_call_cgrp_c[_Lcall_idx_0]++;
}
void _Nglc_Pexpr2stmt_5(_Nglc_Nexpr_i _Le_0, int32_t _Lbegin_row_1, int32_t _Lbegin_col_2, int32_t _Lend_row_3, int32_t _Lend_col_4) {
struct _Nglc_Nstmt_expr* _Ls_5;
_Nglc_Pquick_alloc_one_1(_Ls_5);
_Nglc_Pstmt_push_6(&(*_Ls_5)._Fbase, _Lbegin_row_1, _Lbegin_col_2, _Lend_row_3, _Lend_col_4, _Nglc_Nstmt_type_Cexpr);
(*_Ls_5)._Fexpr = _Le_0;
}
void _Nglc_Pstmt_return_5(_Nglc_Nexpr_i _Le_0, int32_t _Lbegin_row_1, int32_t _Lbegin_col_2, int32_t _Lend_row_3, int32_t _Lend_col_4) {
struct _Nglc_Nstmt_return* _Ls_5;
_Nglc_Pquick_alloc_one_1(_Ls_5);
_Nglc_Pstmt_push_6(&(*_Ls_5)._Fbase, _Lbegin_row_1, _Lbegin_col_2, _Lend_row_3, _Lend_col_4, _Nglc_Nstmt_type_Creturn);
(*_Ls_5)._Fexpr = _Le_0;
}
void _Nglc_Pstmt_continue_5(_Nglc_Nid _Lid_0, int32_t _Lbegin_row_1, int32_t _Lbegin_col_2, int32_t _Lend_row_3, int32_t _Lend_col_4) {
struct _Nglc_Nstmt_continue* _Ls_5;
_Nglc_Pquick_alloc_one_1(_Ls_5);
_Nglc_Pstmt_push_6(&(*_Ls_5)._Fbase, _Lbegin_row_1, _Lbegin_col_2, _Lend_row_3, _Lend_col_4, _Nglc_Nstmt_type_Ccontinue);
if(_Gnest_stack_c <= 0) {
fprintf(stdout, "%s:%u:%u: Cannot have a continue because it's not inside a loop\n", input_path, _Lbegin_row_1, _Lbegin_col_2);
exit(_Nstdc_Nexit_Cfailure);
}
(*_Ls_5)._Fnest = (_Gnest_stack_c - 1);
}
void _Nglc_Pstmt_break_5(_Nglc_Nid _Lid_0, int32_t _Lbegin_row_1, int32_t _Lbegin_col_2, int32_t _Lend_row_3, int32_t _Lend_col_4) {
struct _Nglc_Nstmt_break* _Ls_5;
_Nglc_Pquick_alloc_one_1(_Ls_5);
_Nglc_Pstmt_push_6(&(*_Ls_5)._Fbase, _Lbegin_row_1, _Lbegin_col_2, _Lend_row_3, _Lend_col_4, _Nglc_Nstmt_type_Cbreak);
if(_Gnest_stack_c <= 0) {
fprintf(stdout, "%s:%u:%u: Cannot have a break because it's not inside a loop\n", input_path, _Lbegin_row_1, _Lbegin_col_2);
exit(_Nstdc_Nexit_Cfailure);
}
(*_Ls_5)._Fnest = (_Gnest_stack_c - 1);
}
void _Nglc_Pfunc_attr_main_0() {
if((_Gdecl_func_flags2 & _Nglc_Nfunc_flags2_Cmain) != _Nglc_Nfunc_flags2_C0) {
fprintf(stdout, "%s:%u:%u: Error @main specified more than once\n", input_path, _Glast_row, _Glast_col);
exit(_Nstdc_Nexit_Cfailure);
}
if(_Gfunc_main != _Nglc_Nfunc_Cnil) {
struct _Nglc_Ndecl_func* _Lfirst_0;
_Lfirst_0 = _Nglc_Nfunc_Pptr_1(_Gfunc_main);
fprintf(stdout, "There cannot be more than one function with @main attribute, first was %s:%u:%u and then %u:%u\n", input_path, (*_Lfirst_0)._Fbegin_row, (*_Lfirst_0)._Fbegin_col, _Gdecl_func_row, _Gdecl_func_col);
exit(_Nstdc_Nexit_Cfailure);
}
_Gdecl_func_flags2 |= _Nglc_Nfunc_flags2_Cmain;
}
void _Nglc_Pfunc_attr_decl_0() {
if((_Gdecl_func_flags & _Nglc_Nfunc_flags_Cdecl) != _Nglc_Nfunc_flags_C0) {
fprintf(stdout, "%s:%u:%u: Error @decl specified more than once\n", input_path, _Glast_row, _Glast_col);
exit(_Nstdc_Nexit_Cfailure);
}
_Gdecl_func_flags |= _Nglc_Nfunc_flags_Cdecl;
_Gdecl_func_decl_str = qalloc(_Gstring_len + 1);
memcpy(_Gdecl_func_decl_str, _Gstring_buf, _Gstring_len);
_Gdecl_func_decl_str[_Gstring_len] = 0;
_Gdecl_func_decl_len = _Gstring_len;
}
void _Nglc_Pfunc_attr_cgl_name_0() {
if((_Gdecl_func_flags & _Nglc_Nfunc_flags_Ccgl_name) != _Nglc_Nfunc_flags_C0) {
fprintf(stdout, "%s:%u:%u: Error @cgl-name specified more than once\n", input_path, _Glast_row, _Glast_col);
exit(_Nstdc_Nexit_Cfailure);
}
_Gdecl_func_flags |= _Nglc_Nfunc_flags_Ccgl_name;
}
void _Nglc_Pfunc_attr_process_0() {
if((_Gdecl_func_flags & _Nglc_Nfunc_flags_Cprocess) != _Nglc_Nfunc_flags_C0) {
fprintf(stdout, "%s:%u:%u: Error @process specified more than once\n", input_path, _Glast_row, _Glast_col);
exit(_Nstdc_Nexit_Cfailure);
}
_Gdecl_func_flags |= _Nglc_Nfunc_flags_Cprocess;
}
void _Nglc_Pfunc_attr_inline_0() {
if((_Gdecl_func_flags & _Nglc_Nfunc_flags_Cinline) != _Nglc_Nfunc_flags_C0) {
fprintf(stdout, "%s:%u:%u: Error @inline specified more than once\n", input_path, _Glast_row, _Glast_col);
exit(_Nstdc_Nexit_Cfailure);
}
_Gdecl_func_flags |= _Nglc_Nfunc_flags_Cinline;
}
void _Nglc_Pfunc_attr_var_args_0() {
if((_Gdecl_func_flags & _Nglc_Nfunc_flags_Cvar_args) != _Nglc_Nfunc_flags_C0) {
fprintf(stdout, "%s:%u:%u: Error @var-args specified more than once\n", input_path, _Glast_row, _Glast_col);
exit(_Nstdc_Nexit_Cfailure);
}
_Gdecl_func_flags |= _Nglc_Nfunc_flags_Cvar_args;
}
void _Nglc_Pfunc_attr_no_decl_0() {
if((_Gdecl_func_flags & _Nglc_Nfunc_flags_Cno_decl) != _Nglc_Nfunc_flags_C0) {
fprintf(stdout, "%s:%u:%u: Error @no-decl specified more than once\n", input_path, _Glast_row, _Glast_col);
exit(_Nstdc_Nexit_Cfailure);
}
_Gdecl_func_flags |= _Nglc_Nfunc_flags_Cno_decl;
}
void _Nglc_Pfunc_attr_no_body_0() {
if((_Gdecl_func_flags & _Nglc_Nfunc_flags_Cno_body) != _Nglc_Nfunc_flags_C0) {
fprintf(stdout, "%s:%u:%u: Error @no-body specified more than once\n", input_path, _Glast_row, _Glast_col);
exit(_Nstdc_Nexit_Cfailure);
}
_Gdecl_func_flags |= _Nglc_Nfunc_flags_Cno_body;
}
void _Nglc_Pfunc_attr_real_name_1(_Nglc_Nid _Lname_0) {
if((_Gdecl_func_flags & _Nglc_Nfunc_flags_Creal_name) != _Nglc_Nfunc_flags_C0) {
fprintf(stdout, "%s:%u:%u: Error @real-name specified more than once\n", input_path, _Glast_row, _Glast_col);
exit(_Nstdc_Nexit_Cfailure);
}
_Gdecl_func_flags |= _Nglc_Nfunc_flags_Creal_name;
_Gdecl_func_real_name = _Lname_0;
}
void _Nglc_Pfunc_attr_case_1(_Nglc_Nid _Lname_0) {
char* _Lname_str_1;
uint8_t _Lname_len_2;
char* _Lfunc_name_str_3;
uint8_t _Lfunc_name_len_4;
if((_Gdecl_func_flags & _Nglc_Nfunc_flags_Ccase) != _Nglc_Nfunc_flags_C0) {
fprintf(stdout, "%s:%u:%u: Error @case specified more than once\n", input_path, _Glast_row, _Glast_col);
exit(_Nstdc_Nexit_Cfailure);
}
_Lname_str_1 = _Nglc_Nid_Pstr_1(_Lname_0);
_Lname_len_2 = _Nglc_Nid_Plen_1(_Lname_0);
_Lfunc_name_str_3 = _Nglc_Nid_Pstr_1(_Gdecl_func_name);
_Lfunc_name_len_4 = _Nglc_Nid_Plen_1(_Gdecl_func_name);
if(((_Lname_len_2 > _Lfunc_name_len_4) || (_Lfunc_name_str_3[_Lname_len_2] != '-') || (memcmp(_Lname_str_1, _Lfunc_name_str_3, _Lname_len_2) != 0))) {
fprintf(stdout, "%s:%u:%u: Error, function name must begin with words used in @case followed by '-' (dash) then followed by the name of the cvar of case\n", input_path, _Glast_row, _Glast_col);
exit(_Nstdc_Nexit_Cfailure);
}
_Gdecl_func_flags |= _Nglc_Nfunc_flags_Ccase;
_Gdecl_func_case = _Lname_0;
}
_Nglc_Nexpr_i _Nglc_Pexpr_lvar_4(_Nglc_Nid _Lname_0, uint8_t _Ldecl_1, int32_t _Lrow_2, int32_t _Lcol_3) {
if(_Ldecl_1 == 0) {
struct _Nglc_Nstmt_space* _Lspace_4;
_Lspace_4 = _Gdecl_func_ctx_space;
while(1) {
_Nglc_Nlvar* _Lv_5;
_Nglc_Nlvar _Lfound_6;
_Lv_5 = (*_Lspace_4)._Flvar_v;
_Lfound_6 = _Nglc_Nlvar_Cnil;
int32_t _Li_7;
_Li_7 = 0;
for(int i = (*_Lspace_4)._Flvar_c; i > 0; ) {
i --;
_Nglc_Nlvar _Llvar_8;
_Llvar_8 = _Lv_5[_Li_7];
if(_Nglc_Nlvar_Pname_1(_Llvar_8) == _Lname_0) {
_Lfound_6 = _Llvar_8;
goto break_1;
}
continue_1:;
_Li_7++;
}
break_1:;
if(_Lfound_6 != _Nglc_Nlvar_Cnil) {
struct _Nglc_Nexpr_lvar* _Le_9;
_Nglc_Nexpr_i _Le_idx_10;
_Nglc_Pquick_alloc_one_1(_Le_9);
_Le_idx_10 = _Nglc_Pexpr_push_2(&(*_Le_9)._Fbase, _Nglc_Nexpr_type_Clvar);
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
fprintf(stdout, "%s:%u:%u: lvar '%s' was not found\n", input_path, _Lrow_2, _Lcol_3, _Nglc_Nid_Pstr_1(_Lname_0));
exit(_Nstdc_Nexit_Cfailure);
return _Nglc_Nexpr_i_Cnil;
} else {
struct _Nglc_Nstmt_space* _Lspace_11;
struct _Nglc_Nexpr_lvar* _Le_12;
_Nglc_Nexpr_i _Le_idx_13;
struct _Nglc_Nlvar_data* _Llvar_14;
_Lspace_11 = _Gdecl_func_ctx_space;
while(_Ldecl_1 > 1) {
_Lspace_11 = (*_Lspace_11)._Fparent;
if(_Lspace_11 == NULL) {
fprintf(stdout, "%s:%u:%u: Cannot declare lvar '%s' with too much '+'\n", input_path, _Lrow_2, _Lcol_3, _Nglc_Nid_Pstr_1(_Lname_0));
exit(_Nstdc_Nexit_Cfailure);
}
if(((*_Lspace_11)._Fflags & _Nglc_Nstmt_space_flags_Cskip_lvar_decl) == _Nglc_Nstmt_space_flags_C0) {
_Ldecl_1--;
}
continue_2:;
}
break_2:;
_Nglc_Pquick_alloc_one_1(_Le_12);
_Le_idx_13 = _Nglc_Pexpr_push_2(&(*_Le_12)._Fbase, _Nglc_Nexpr_type_Clvar);
(*_Le_12)._Flvar = _Nglc_Nstmt_space_Plvar_new_4(_Lspace_11, _Lname_0, _Lrow_2, _Lcol_3);
_Llvar_14 = _Nglc_Nlvar_Pptr_1((*_Le_12)._Flvar);
_Gdecl_var._Fname = _Lname_0;
_Nglc_Ndecl_var_data_Pcopy_from_2(&(*_Llvar_14)._Fdecl, &_Gdecl_var);
return _Le_idx_13;
}
}
_Nglc_Nexpr_i _Nglc_Pexpr_gvar_2(_Nglc_Nat _Lat_0, _Nglc_Nid _Lname_1) {
struct _Nglc_Nexpr_gvar* _Le_2;
_Nglc_Nexpr_i _Le_idx_3;
_Nglc_Pquick_alloc_one_1(_Le_2);
_Le_idx_3 = _Nglc_Pexpr_push_2(&(*_Le_2)._Fbase, _Nglc_Nexpr_type_Cgvar);
(*_Le_2)._Fat = _Lat_0;
(*_Le_2)._Fname = _Lname_1;
return _Le_idx_3;
}
_Nglc_Nexpr_i _Nglc_Pexpr_fvar_2(_Nglc_Nexpr_i _Lexpr_0, _Nglc_Nid _Lmember_1) {
struct _Nglc_Nexpr_fvar* _Le_2;
_Nglc_Nexpr_i _Le_idx_3;
_Nglc_Pquick_alloc_one_1(_Le_2);
_Le_idx_3 = _Nglc_Pexpr_push_2(&(*_Le_2)._Fbase, _Nglc_Nexpr_type_Cfvar);
(*_Le_2)._Fexpr = _Lexpr_0;
(*_Le_2)._Fmember = _Lmember_1;
return _Le_idx_3;
}
_Nglc_Nexpr_i _Nglc_Pexpr_assign_3(_Nglc_Nexpr_i _Lleft_0, _Nglc_Nexpr_i _Lright_1, _Nglc_Nassign _Ltype_2) {
struct _Nglc_Nexpr_assign* _Le_3;
_Nglc_Nexpr_i _Le_idx_4;
_Nglc_Pquick_alloc_one_1(_Le_3);
_Le_idx_4 = _Nglc_Pexpr_push_2(&(*_Le_3)._Fbase, _Nglc_Nexpr_type_Cassign);
(*_Le_3)._Fleft = _Lleft_0;
(*_Le_3)._Fright = _Lright_1;
(*_Le_3)._Ftype = _Ltype_2;
return _Le_idx_4;
}
_Nglc_Nexpr_i _Nglc_Pexpr_math_3(_Nglc_Nexpr_i _Lleft_0, _Nglc_Nexpr_i _Lright_1, _Nglc_Nmath _Ltype_2) {
struct _Nglc_Nexpr_math* _Le_3;
_Nglc_Nexpr_i _Le_idx_4;
_Nglc_Pquick_alloc_one_1(_Le_3);
_Le_idx_4 = _Nglc_Pexpr_push_2(&(*_Le_3)._Fbase, _Nglc_Nexpr_type_Cmath);
(*_Le_3)._Fleft = _Lleft_0;
(*_Le_3)._Fright = _Lright_1;
(*_Le_3)._Ftype = _Ltype_2;
return _Le_idx_4;
}
_Nglc_Nexpr_i _Nglc_Pexpr_math_add_2(_Nglc_Nexpr_i _Lexpr_0, _Nglc_Nexpr_i _Lright_1) {
struct _Nglc_Nexpr_math* _Le_2;
uint8_t _Li_3;
struct _Nglc_Nexpr_math_item* _Litem_5;
_Le_2 = _Nglc_Nexpr_i_Pptr_1(_Lexpr_0);
_Li_3 = (*_Le_2)._Fitem_c++;
if((*_Le_2)._Fitem_cap <= (*_Le_2)._Fitem_c) {
uint8_t _Lold_cap_4;
_Lold_cap_4 = (*_Le_2)._Fitem_cap;
_Nglc_Pgrow_2((*_Le_2)._Fitem_cap, (*_Le_2)._Fitem_c);
_Nglc_Prealloc_3((*_Le_2)._Fitem_v, (*_Le_2)._Fitem_cap, _Lold_cap_4);
}
_Litem_5 = (&(*_Le_2)._Fitem_v[_Li_3]);
(*_Litem_5)._Fexpr = _Lright_1;
return _Lexpr_0;
}
_Nglc_Nexpr_i _Nglc_Pexpr_bools_3(_Nglc_Nexpr_i _Lleft_0, _Nglc_Nexpr_i _Lright_1, _Nglc_Nbools _Ltype_2) {
struct _Nglc_Nexpr_bools* _Le_3;
_Nglc_Nexpr_i _Le_idx_4;
_Nglc_Pquick_alloc_one_1(_Le_3);
_Le_idx_4 = _Nglc_Pexpr_push_2(&(*_Le_3)._Fbase, _Nglc_Nexpr_type_Cbools);
(*_Le_3)._Fleft = _Lleft_0;
(*_Le_3)._Fright = _Lright_1;
(*_Le_3)._Ftype = _Ltype_2;
return _Le_idx_4;
}
_Nglc_Nexpr_i _Nglc_Pexpr_bools_add_2(_Nglc_Nexpr_i _Lbools_0, _Nglc_Nexpr_i _Lright_1) {
struct _Nglc_Nexpr_bools* _Le_2;
uint8_t _Li_3;
_Le_2 = _Nglc_Nexpr_i_Pptr_1(_Lbools_0);
_Li_3 = (*_Le_2)._Fitem_c++;
if((*_Le_2)._Fitem_cap <= (*_Le_2)._Fitem_c) {
uint8_t _Lold_cap_4;
_Lold_cap_4 = (*_Le_2)._Fitem_cap;
_Nglc_Pgrow_2((*_Le_2)._Fitem_cap, (*_Le_2)._Fitem_c);
_Nglc_Prealloc_3((*_Le_2)._Fitem_v, (*_Le_2)._Fitem_cap, _Lold_cap_4);
}
(*_Le_2)._Fitem_v[_Li_3]._Fexpr = _Lright_1;
return _Lbools_0;
}
char* _Nglc_Ptoken_name_1(_Nglc_Ntoken _Ltok_0) {
return _Nglc_Ntoken_Pcgl_name_1(_Ltok_0);
}
void _Nglc_Pdecl_var_type_1(_Nglc_Nat _Ltype_0) {
if(_Ltype_0 != _Nglc_Nat_Cnil) {
struct _Nglc_Nat_data* _Lat_1;
_Lat_1 = _Nglc_Nat_Pptr_1(_Ltype_0);
if((*_Lat_1)._Ftype == _Nglc_Nname_type_Cmodule) {
fprintf(stdout, "%u:%u: module '%%%s' cannot be used as a type\n", _Glast_row, _Glast_col, _Nglc_Nid_Pstr_1((*_Lat_1)._Fname._Fid));
exit(_Nstdc_Nexit_Cfailure);
}
}
_Gdecl_var._Ftype = _Ltype_0;
_Gdecl_var._Fsize_c = 0;
_Nglc_Ntype_info_Pinit_1(&_Gdecl_var._Ftype_info);
_Gdecl_var._Fflags = _Nglc_Nvar_flags_C0;
}
void _Nglc_Pdecl_var_this_0() {
_Nglc_Nat _Ltype_0;
struct _Nglc_Nat_data* _Lat_1;
_Ltype_0 = _Gdecl_at;
_Lat_1 = _Nglc_Nat_Pptr_1(_Ltype_0);
if((*_Lat_1)._Ftype == _Nglc_Nname_type_Cmodule) {
fprintf(stdout, "%u:%u: module '%%%s' cannot be used as a type\n", _Glast_row, _Glast_col, _Nglc_Nid_Pstr_1((*_Lat_1)._Fname._Fid));
exit(_Nstdc_Nexit_Cfailure);
}
_Gdecl_var._Ftype = _Ltype_0;
}
void _Nglc_Pstmt_lvar_add_4(_Nglc_Nid _Lname_0, _Nglc_Nexpr_i _Lset_1, int32_t _Lrow_2, int32_t _Lcol_3) {
_Nglc_Nlvar _Llvar_i_4;
struct _Nglc_Nlvar_data* _Llvar_5;
_Llvar_i_4 = _Nglc_Nstmt_space_Plvar_new_4(_Gdecl_func_ctx_space, _Lname_0, _Lrow_2, _Lcol_3);
_Llvar_5 = _Nglc_Nlvar_Pptr_1(_Llvar_i_4);
_Gdecl_var._Fname = _Lname_0;
_Nglc_Ndecl_var_data_Pcopy_from_2(&(*_Llvar_5)._Fdecl, &_Gdecl_var);
if(_Lset_1 != _Nglc_Nexpr_i_Cnil) {
_Nglc_Nexpr_i _Le_6;
_Le_6 = _Nglc_Pexpr_assign_3(_Nglc_Pexpr_lvar_4(_Lname_0, 0, _Lrow_2, _Lcol_3), _Lset_1, _Nglc_Nassign_Ceq);
_Nglc_Pexpr2stmt_5(_Le_6, _Lrow_2, _Lcol_3, _Lrow_2, _Lcol_3);
}
}
void _Nglc_Pstmt_lvar_end_2(int32_t _Lend_row_0, int32_t _Lend_col_1) {
}
void _Nglc_Pdecl_include_begin_3(_Nglc_Ninclude _Linc_0, int32_t _Lrow_1, int32_t _Lcol_2) {
if(_Gdecl_include != _Nglc_Ninclude_Cnil) {
fprintf(stdout, "%s:%u:%u: Cannot {include inside another {include of %u:%u\n", input_path, _Lrow_1, _Lcol_2, _Gdecl_include_row, _Gdecl_include_col);
exit(_Nstdc_Nexit_Cfailure);
return;
}
_Gdecl_include = _Linc_0;
_Gdecl_include_row = _Lrow_1;
_Gdecl_include_col = _Lcol_2;
}
void _Nglc_Pdecl_include_end_0() {
_Gdecl_include = _Nglc_Ninclude_Cnil;
}
void _Nglc_Pdecl_at_basic_1(_Nglc_Nbasic_type_id _Ltype_0) {
_Gbuild_at = _Nglc_Pat_create_basic_1(_Ltype_0);
}
void _Nglc_Pdecl_at_add_2(_Nglc_Nid _Lname_0, _Nglc_Nname_type _Ltype_1) {
_Gbuild_at = _Nglc_Pat_create_3(_Gbuild_at, _Ltype_1, _Lname_0);
}
void _Nglc_Pdecl_at_begin_2(int32_t _Lrow_0, int32_t _Lcol_1) {
_Gdecl_at_v[_Gdecl_at_c++] = _Gdecl_at;
_Gdecl_at = _Gbuild_at;
}
void _Nglc_Pdecl_at_begin_struct_3(_Nglc_Nid _Lname_0, int32_t _Lrow_1, int32_t _Lcol_2) {
_Gdecl_struct_row = _Lrow_1;
_Gdecl_struct_col = _Lcol_2;
_Gbuild_at = _Gdecl_at;
_Nglc_Pdecl_at_add_2(_Lname_0, _Nglc_Nname_type_Cstruct_enum);
_Gdecl_at_v[_Gdecl_at_c++] = _Gdecl_at;
_Gdecl_at = _Gbuild_at;
_Gdecl_struct_at = _Gbuild_at;
_Gdecl_fvar_c = 0;
_Gdecl_struct_real_name = _Nglc_Nid_Cnil;
_Gdecl_struct_flags = _Nglc_Nstruct_flags_C0;
}
void _Nglc_Pdecl_at_end_0() {
_Gdecl_at_c--;
_Gdecl_at = _Gdecl_at_v[_Gdecl_at_c];
}
void _Nglc_Pdecl_alias_4(_Nglc_Nid _Lname_0, _Nglc_Nat _Lat_1, int32_t _Lrow_2, int32_t _Lcol_3) {
_Nglc_Nalias _Lalias_idx_5;
int32_t _Li_4;
_Li_4 = 0;
for(int i = _Gat_alias_c; i > 0; ) {
i --;
if(_Gat_alias_name_v[_Li_4] == _Lname_0) {
fprintf(stdout, "%s:%u:%u: Alias '%s was already declared at %u:%u\n", input_path, _Lrow_2, _Lcol_3, _Nglc_Nid_Pstr_1(_Lname_0), _Gat_alias_pos_v[_Li_4]._Frow, _Gat_alias_pos_v[_Li_4]._Fcol);
exit(_Nstdc_Nexit_Cfailure);
return;
}
continue_0:;
_Li_4++;
}
break_0:;
_Lalias_idx_5 = _Gat_alias_c++;
if(_Gat_alias_cap <= _Gat_alias_c) {
_Nglc_Nalias _Lold_cap_6;
_Lold_cap_6 = _Gat_alias_cap;
_Nglc_Pgrow_2(_Gat_alias_cap, _Gat_alias_c);
_Nglc_Prealloc_3(_Gat_alias_name_v, _Gat_alias_cap, _Lold_cap_6);
_Nglc_Prealloc_3(_Gat_alias_at_v, _Gat_alias_cap, _Lold_cap_6);
_Nglc_Prealloc_3(_Gat_alias_pos_v, _Gat_alias_cap, _Lold_cap_6);
}
_Gat_alias_name_v[_Lalias_idx_5] = _Lname_0;
_Gat_alias_at_v[_Lalias_idx_5] = _Lat_1;
_Gat_alias_pos_v[_Lalias_idx_5]._Frow = _Lrow_2;
_Gat_alias_pos_v[_Lalias_idx_5]._Fcol = _Lcol_3;
}
void _Nglc_Pat_push_4(_Nglc_Nid _Lname_0, _Nglc_Nname_type _Ltype_1, int32_t _Lrow_2, int32_t _Lcol_3) {
_Gbuild_at = _Nglc_Pat_create_3(_Gbuild_at, _Ltype_1, _Lname_0);
}
_Nglc_Nat _Nglc_Pat_done_0() {
return _Gbuild_at;
}
void _Nglc_Pat_begin_0() {
_Gbuild_at = _Gdecl_at;
}
void _Nglc_Pat_begin_relative_0() {
if(_Gat_begin_relative_pause) {
_Gbuild_at = _Gdecl_at;
} else {
_Gbuild_at = _Nglc_Nat_Crelative;
}
}
void _Nglc_Pat_begin_relative_pause_0() {
_Gat_begin_relative_pause = true;
}
void _Nglc_Pat_begin_relative_resume_0() {
_Gat_begin_relative_pause = false;
}
void _Nglc_Pat_root_0() {
_Gbuild_at = _Nglc_Nat_Croot;
}
void _Nglc_Pat_alias_3(_Nglc_Nid _Lname_0, int32_t _Lrow_1, int32_t _Lcol_2) {
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
fprintf(stdout, "%s:%u:%u: Cannot recognize the alias '%s\n", input_path, _Lrow_1, _Lcol_2, _Nglc_Nid_Pstr_1(_Lname_0));
exit(_Nstdc_Nexit_Cfailure);
}
void _Nglc_Pat_graves_3(int8_t _Lgraves_0, int32_t _Lrow_1, int32_t _Lcol_2) {
_Gbuild_at = _Gdecl_at;
while(_Lgraves_0 > 0) {
struct _Nglc_Nat_data* _Lat_3;
_Lgraves_0--;
if(_Gbuild_at == _Nglc_Nat_Croot) {
fprintf(stdout, "%s:%u:%u: Too many graves in the namespace, going beyond the root namespace\n", input_path, _Lrow_1, _Lcol_2);
exit(_Nstdc_Nexit_Cfailure);
}
_Lat_3 = _Nglc_Nat_Pptr_1(_Gbuild_at);
_Gbuild_at = (*_Lat_3)._Fparent;
continue_0:;
}
break_0:;
}
_Nglc_Nat _Nglc_Pat_basic_type_1(_Nglc_Nbasic_type_id _Ltype_0) {
_Nglc_Nat _Lbuild_idx_3;
struct _Nglc_Nat_data* _Lat_5;
_Nglc_Nat _Li_1;
_Li_1 = (_Nglc_Nat)(0);
for(int i = _Gat_c; i > 0; ) {
i --;
struct _Nglc_Nat_data* _Lat_2;
_Lat_2 = (&_Gat_v[_Li_1]);
if((((*_Lat_2)._Ftype == _Nglc_Nname_type_Cbasic) && ((*_Lat_2)._Fname._Fbasic == _Ltype_0))) {
return _Li_1;
}
continue_0:;
_Li_1++;
}
break_0:;
_Lbuild_idx_3 = _Gat_c++;
if(_Gat_cap <= _Gat_c) {
_Nglc_Nat _Lold_cap_4;
_Lold_cap_4 = _Gat_cap;
_Nglc_Pgrow_2(_Gat_cap, _Gat_c);
_Nglc_Prealloc_3(_Gat_v, _Gat_cap, _Lold_cap_4);
}
_Lat_5 = (&_Gat_v[_Lbuild_idx_3]);
(*_Lat_5)._Fparent = _Nglc_Nat_Croot;
(*_Lat_5)._Ftype = _Nglc_Nname_type_Cbasic;
(*_Lat_5)._Fname._Fbasic = _Ltype_0;
return _Lbuild_idx_3;
}
void _Nglc_Pdecl_var_as_gvar_0() {
_Nglc_Ngvar _Lgvar_idx_0;
struct _Nglc_Ndecl_gvar* _Lgvar_2;
_Lgvar_idx_0 = _Ggvar_c++;
if(_Ggvar_cap <= _Ggvar_c) {
_Nglc_Ngvar _Lold_cap_1;
_Lold_cap_1 = _Ggvar_cap;
_Nglc_Pgrow_2(_Ggvar_cap, _Ggvar_c);
_Nglc_Prealloc_3(_Ggvar_v, _Ggvar_cap, _Lold_cap_1);
}
_Lgvar_2 = (&_Ggvar_v[_Lgvar_idx_0]);
(*_Lgvar_2)._Finclude = _Gdecl_include;
(*_Lgvar_2)._Fat = _Gdecl_at;
_Nglc_Ndecl_var_data_Pcopy_from_2(&(*_Lgvar_2)._Fdecl, &_Gdecl_var);
}
void _Nglc_Ptype_info_arr_2(_Nglc_Nexpr_i* _Lexpr_v_0, uint8_t _Lexpr_c_1) {
union _Nglc_Nrdr _Lr_2;
_Lr_2._Fref = _Lexpr_v_0;
if(_Lexpr_v_0 == NULL) {
struct _Nglc_Ntype_info* _Lti_3;
_Lti_3 = (&_Gdecl_var._Ftype_info);
(*_Lti_3)._Farray_c += 1;
(*_Lti_3)._Fref_v[(*_Lti_3)._Farray_c] = 0;
return;
}
uint8_t _Li_4;
_Li_4 = _Lexpr_c_1;
for(int i = _Lexpr_c_1; i > 0; ) {
i --;
_Nglc_Ptype_info_arr_1(_Lexpr_v_0[(_Li_4 -= 1)]);
continue_0:;
}
break_0:;
}
void _Nglc_Ptype_info_ref_1(int8_t _Lc_0) {
struct _Nglc_Ntype_info* _Lti_1;
_Lti_1 = (&_Gdecl_var._Ftype_info);
(*_Lti_1)._Fref_v[(*_Lti_1)._Farray_c] += _Lc_0;
}
void _Nglc_Ptype_info_static_0() {
_Gdecl_var._Ftype_info._Fbuilt_in = true;
}
void _Nglc_Ptype_info_begin_0() {
_Gdecl_var._Fsize_c = 0;
_Nglc_Ntype_info_Pinit_1(&_Gdecl_var._Ftype_info);
_Gdecl_var._Fflags = _Nglc_Nvar_flags_C0;
}
void _Nglc_Ptype_info_finalize_0() {
_Nglc_Ntype_info_Pfinalize_1(&_Gdecl_var._Ftype_info);
}
_Nglc_Nexpr_i _Nglc_Pexpr_int_2(int32_t _Lvalue_0, _Nglc_Nexpr_int _Ltype_1) {
struct _Nglc_Nexpr_int_data* _Le_2;
_Nglc_Nexpr_i _Le_idx_3;
_Nglc_Pquick_alloc_one_1(_Le_2);
_Le_idx_3 = _Nglc_Pexpr_push_2(&(*_Le_2)._Fbase, _Nglc_Nexpr_type_Ci32);
(*_Le_2)._Fvalue = _Lvalue_0;
(*_Le_2)._Ftype = _Ltype_1;
return _Le_idx_3;
}
_Nglc_Nexpr_i _Nglc_Pexpr_size_of_type_1(_Nglc_Nat _Lat_0) {
struct _Nglc_Nexpr_size_of_type* _Le_1;
_Nglc_Nexpr_i _Le_idx_2;
_Nglc_Pquick_alloc_one_1(_Le_1);
_Le_idx_2 = _Nglc_Pexpr_push_2(&(*_Le_1)._Fbase, _Nglc_Nexpr_type_Csize_of_type);
(*_Le_1)._Ftype = _Lat_0;
return _Le_idx_2;
}
_Nglc_Nexpr_i _Nglc_Pexpr_null_0() {
struct _Nglc_Nexpr_null* _Le_0;
_Nglc_Nexpr_i _Le_idx_1;
_Nglc_Pquick_alloc_one_1(_Le_0);
_Le_idx_1 = _Nglc_Pexpr_push_2(&(*_Le_0)._Fbase, _Nglc_Nexpr_type_Cnull);
return _Le_idx_1;
}
void _Nglc_Pdecl_at_begin_enum_3(_Nglc_Nid _Lname_0, int32_t _Lrow_1, int32_t _Lcol_2) {
_Gdecl_enum_row = _Lrow_1;
_Gdecl_enum_col = _Lcol_2;
_Gbuild_at = _Gdecl_at;
_Nglc_Pdecl_at_add_2(_Lname_0, _Nglc_Nname_type_Cstruct_enum);
_Gdecl_at_v[_Gdecl_at_c++] = _Gdecl_at;
_Gdecl_at = _Gbuild_at;
_Gdecl_enum_at = _Gbuild_at;
_Gdecl_enum_flags = _Nglc_Nenum_flags_C0;
_Gdecl_enum_last_cvar = _Nglc_Ncvar_Cnil;
}
void _Nglc_Pdecl_enum_end_3(_Nglc_Nat _Lbase_type_0, int32_t _Lrow_1, int32_t _Lcol_2) {
_Nglc_Nenum _Ls_idx_3;
struct _Nglc_Nenum_data* _Ls_5;
_Ls_idx_3 = _Genum_c++;
if(_Genum_cap <= _Genum_c) {
_Nglc_Nenum _Lold_cap_4;
_Lold_cap_4 = _Genum_cap;
_Nglc_Pgrow_2(_Genum_cap, _Genum_c);
_Nglc_Prealloc_3(_Genum_v, _Genum_cap, _Lold_cap_4);
}
_Nglc_Pquick_alloc_one_1(_Ls_5);
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
_Gdecl_enum_last_cvar = _Nglc_Ncvar_Cnil;
}
_Nglc_Nexpr_i _Nglc_Pexpr_cvar_2(_Nglc_Nat _Lat_0, _Nglc_Nid _Lname_1) {
struct _Nglc_Nexpr_cvar* _Le_2;
_Nglc_Nexpr_i _Le_idx_3;
_Nglc_Pquick_alloc_one_1(_Le_2);
_Le_idx_3 = _Nglc_Pexpr_push_2(&(*_Le_2)._Fbase, _Nglc_Nexpr_type_Ccvar);
(*_Le_2)._Fat = _Lat_0;
(*_Le_2)._Fname = _Lname_1;
return _Le_idx_3;
}
void _Nglc_Penum_add_cvar_3(_Nglc_Nid _Lname_0, int32_t _Lrow_1, int32_t _Lcol_2) {
_Nglc_Ncvar _Lc_idx_3;
struct _Nglc_Ncvar_data* _Lc_5;
_Lc_idx_3 = _Gcvar_c++;
_Glast_cvar = _Lc_idx_3;
if(_Gcvar_cap <= _Gcvar_c) {
_Nglc_Ncvar _Lold_cap_4;
_Lold_cap_4 = _Gcvar_cap;
_Nglc_Pgrow_2(_Gcvar_cap, _Gcvar_c);
_Nglc_Prealloc_3(_Gcvar_v, _Gcvar_cap, _Lold_cap_4);
}
_Lc_5 = _Nglc_Ncvar_Pptr_1(_Lc_idx_3);
(*_Lc_5)._Frow = _Lrow_1;
(*_Lc_5)._Fcol = _Lcol_2;
(*_Lc_5)._Finclude = _Gdecl_include;
(*_Lc_5)._Fat = _Gdecl_at;
(*_Lc_5)._Fdecl._Fname = _Lname_0;
(*_Lc_5)._Fdecl._Ftype = _Gdecl_enum_at;
_Nglc_Ntype_info_Pinit_1(&(*_Lc_5)._Fdecl._Ftype_info);
(*_Lc_5)._Fflags = _Nglc_Ncvar_flags_Cas_enum;
(*_Lc_5)._Flast_cvar = _Gdecl_enum_last_cvar;
_Gdecl_enum_last_cvar = _Lc_idx_3;
}
void _Nglc_Pdecl_add_cvar_3(_Nglc_Nid _Lname_0, int32_t _Lrow_1, int32_t _Lcol_2) {
_Nglc_Ncvar _Lc_idx_3;
struct _Nglc_Ncvar_data* _Lc_5;
_Lc_idx_3 = _Gcvar_c++;
_Glast_cvar = _Lc_idx_3;
if(_Gcvar_cap <= _Gcvar_c) {
_Nglc_Ncvar _Lold_cap_4;
_Lold_cap_4 = _Gcvar_cap;
_Nglc_Pgrow_2(_Gcvar_cap, _Gcvar_c);
_Nglc_Prealloc_3(_Gcvar_v, _Gcvar_cap, _Lold_cap_4);
}
_Lc_5 = _Nglc_Ncvar_Pptr_1(_Lc_idx_3);
(*_Lc_5)._Frow = _Lrow_1;
(*_Lc_5)._Fcol = _Lcol_2;
(*_Lc_5)._Finclude = _Gdecl_include;
(*_Lc_5)._Fat = _Gdecl_at;
_Gdecl_var._Fname = _Lname_0;
_Nglc_Ndecl_var_data_Pcopy_from_2(&(*_Lc_5)._Fdecl, &_Gdecl_var);
(*_Lc_5)._Fflags = _Nglc_Ncvar_flags_C0;
}
void _Nglc_Penum_set_cvar_expr_1(_Nglc_Nexpr_i _Lset_0) {
struct _Nglc_Ncvar_data* _Lc_1;
_Lc_1 = _Nglc_Ncvar_Pptr_1(_Glast_cvar);
(*_Lc_1)._Fflags |= _Nglc_Ncvar_flags_Cset_expr;
(*_Lc_1)._Fexpr_set = _Lset_0;
}
void _Nglc_Pstruct_attr_real_name_1(_Nglc_Nid _Lname_0) {
if((_Gdecl_struct_flags & _Nglc_Nstruct_flags_Creal_name) != _Nglc_Nstruct_flags_C0) {
fprintf(stdout, "%u:%u: error @real-name specified more than once\n", _Glast_row, _Glast_col);
exit(_Nstdc_Nexit_Cfailure);
}
_Gdecl_struct_flags |= _Nglc_Nstruct_flags_Creal_name;
_Gdecl_struct_real_name = _Lname_0;
}
void _Nglc_Pstruct_attr_union_0() {
if((_Gdecl_struct_flags & _Nglc_Nstruct_flags_Cunion) != _Nglc_Nstruct_flags_C0) {
fprintf(stdout, "%u:%u: error @union specified more than once\n", _Glast_row, _Glast_col);
exit(_Nstdc_Nexit_Cfailure);
}
_Gdecl_struct_flags |= _Nglc_Nstruct_flags_Cunion;
}
void _Nglc_Pstruct_attr_no_decl_0() {
if((_Gdecl_struct_flags & _Nglc_Nstruct_flags_Cno_decl) != _Nglc_Nstruct_flags_C0) {
fprintf(stdout, "%u:%u: error @no-decl specified more than once\n", _Glast_row, _Glast_col);
exit(_Nstdc_Nexit_Cfailure);
}
_Gdecl_struct_flags |= _Nglc_Nstruct_flags_Cno_decl;
}
_Nglc_Nexpr_i _Nglc_Pexpr_str_1(_Nglc_Nexpr_i _Lprev_0) {
int32_t _Llen_1;
struct _Nglc_Nexpr_str_node* _Ln_2;
_Llen_1 = _Gstring_len;
_Nglc_Pquick_alloc_plus_2(_Ln_2, _Llen_1 + 1);
(*_Ln_2)._Flen = _Llen_1;
memcpy((*_Ln_2)._Fbuf, _Gstring_buf, _Llen_1);
(*_Ln_2)._Fbuf[_Llen_1] = '\0';
(*_Ln_2)._Fnext = NULL;
if(_Lprev_0 == _Nglc_Nexpr_i_Cnil) {
struct _Nglc_Nexpr_str* _Le_3;
_Nglc_Nexpr_i _Le_idx_4;
_Nglc_Pquick_alloc_one_1(_Le_3);
_Le_idx_4 = _Nglc_Pexpr_push_2(&(*_Le_3)._Fbase, _Nglc_Nexpr_type_Cstr);
(*_Le_3)._Fnode_c = 1;
(*_Le_3)._Ffirst = _Ln_2;
(*_Le_3)._Flast = _Ln_2;
return _Le_idx_4;
} else {
struct _Nglc_Nexpr_str* _Le_5;
_Le_5 = _Nglc_Nexpr_i_Pptr_1(_Lprev_0);
(*_Le_5)._Fnode_c++;
(*(*_Le_5)._Flast)._Fnext = _Ln_2;
(*_Le_5)._Flast = _Ln_2;
return _Lprev_0;
}
}
_Nglc_Nexpr_i _Nglc_Pexpr_unary_2(_Nglc_Nexpr_i _Lexpr_0, _Nglc_Nunary _Ltype_1) {
struct _Nglc_Nexpr_unary* _Le_2;
_Nglc_Nexpr_i _Le_idx_3;
_Nglc_Pquick_alloc_one_1(_Le_2);
_Le_idx_3 = _Nglc_Pexpr_push_2(&(*_Le_2)._Fbase, _Nglc_Nexpr_type_Cunary);
(*_Le_2)._Fexpr = _Lexpr_0;
(*_Le_2)._Ftype = _Ltype_1;
return _Le_idx_3;
}
_Nglc_Nexpr_i _Nglc_Pexpr_ref_1(_Nglc_Nexpr_i _Lexpr_0) {
struct _Nglc_Nexpr_ref* _Le_1;
_Nglc_Nexpr_i _Le_idx_2;
_Nglc_Pquick_alloc_one_1(_Le_1);
_Le_idx_2 = _Nglc_Pexpr_push_2(&(*_Le_1)._Fbase, _Nglc_Nexpr_type_Cref);
(*_Le_1)._Fexpr = _Lexpr_0;
return _Le_idx_2;
}
_Nglc_Nexpr_i _Nglc_Pexpr_cast_fast_2(_Nglc_Nexpr_i _Lexpr_0, _Nglc_Nat _Ltype_1) {
struct _Nglc_Nexpr_cast_fast* _Le_2;
_Nglc_Nexpr_i _Le_idx_3;
_Nglc_Pquick_alloc_one_1(_Le_2);
_Le_idx_3 = _Nglc_Pexpr_push_2(&(*_Le_2)._Fbase, _Nglc_Nexpr_type_Ccast_fast);
(*_Le_2)._Fexpr = _Lexpr_0;
(*_Le_2)._Ftype = _Ltype_1;
return _Le_idx_3;
}
_Nglc_Nexpr_i _Nglc_Pexpr_index_3(_Nglc_Nexpr_i _Lleft_0, _Nglc_Nexpr_i* _Lright_v_1, int32_t _Lright_c_2) {
_Nglc_Nexpr_i _Le_idx_5;
int32_t _Li_3;
_Li_3 = _Lright_c_2;
for(int i = _Lright_c_2; i > 0; ) {
i --;
struct _Nglc_Nexpr_index* _Le_4;
_Nglc_Pquick_alloc_one_1(_Le_4);
_Le_idx_5 = _Nglc_Pexpr_push_2(&(*_Le_4)._Fbase, _Nglc_Nexpr_type_Cindex);
(*_Le_4)._Fleft = _Lleft_0;
(*_Le_4)._Fright = _Lright_v_1[(_Li_3 -= 1)];
continue_0:;
}
break_0:;
return _Le_idx_5;
}
void _Nglc_Penum_base_begin_0() {
_Gdecl_at = (*_Nglc_Nat_Pptr_1(_Gdecl_at))._Fparent;
}
void _Nglc_Pstmt_switch_begin_0() {
_Nglc_Pstmt_space_begin_0();
(*_Gdecl_func_ctx_space)._Fflags |= _Nglc_Nstmt_space_flags_Cskip_lvar_decl;
}
void _Nglc_Pstmt_switch_set_6(_Nglc_Nexpr_i _Lexpr_0, int32_t _Lbegin_row_1, int32_t _Lbegin_col_2, int32_t _Lend_row_3, int32_t _Lend_col_4, _Nglc_Nexpr_i _Lcases_5) {
struct _Nglc_Nstmt_switch* _Ls_6;
_Nglc_Pquick_alloc_one_1(_Ls_6);
(*_Ls_6)._Fexpr = _Lexpr_0;
(*_Ls_6)._Fcases = _Lcases_5;
_Nglc_Pstmt_push_6(&(*_Ls_6)._Fbase, _Lbegin_row_1, _Lbegin_col_2, _Lend_row_3, _Lend_col_4, _Nglc_Nstmt_type_Cswitch);
_Gswitch_expr_c = 0;
}
void _Nglc_Pstmt_switch_expr_add_1(_Nglc_Nexpr_i _Lexpr_0) {
uint32_t _Lexpr_i_1;
_Lexpr_i_1 = _Gswitch_expr_c++;
if(_Gswitch_expr_cap <= _Gswitch_expr_c) {
uint32_t _Lold_cap_2;
_Lold_cap_2 = _Gswitch_expr_cap;
_Nglc_Pgrow_2(_Gswitch_expr_cap, _Gswitch_expr_c);
_Nglc_Prealloc_3(_Gswitch_expr_v, _Gswitch_expr_cap, _Lold_cap_2);
}
_Gswitch_expr_v[_Lexpr_i_1] = _Lexpr_0;
}
void _Nglc_Pstmt_switch_case_begin_5(int32_t _Lbegin_row_0, int32_t _Lbegin_col_1, int32_t _Lend_row_2, int32_t _Lend_col_3, bool _Lfall_through_4) {
uint32_t _Lexpr_c_5;
struct _Nglc_Nstmt_case* _Ls_6;
_Lexpr_c_5 = _Gswitch_expr_c;
_Gswitch_expr_c = 0;
_Nglc_Pquick_alloc_plus_2(_Ls_6, sizeof(struct _Nglc_Nstmt_case_item) * _Lexpr_c_5);
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
_Nglc_Pstmt_push_6(&(*_Ls_6)._Fbase, _Lbegin_row_0, _Lbegin_col_1, _Lend_row_2, _Lend_col_3, _Nglc_Nstmt_type_Ccase);
_Nglc_Pstmt_space_begin_0();
}
void _Nglc_Pstmt_switch_case_end_0() {
struct _Nglc_Nstmt_case_end* _Ls_0;
_Nglc_Pstmt_space_end_0();
_Nglc_Pquick_alloc_one_1(_Ls_0);
_Nglc_Pstmt_push_6(&(*_Ls_0)._Fbase, 0, 0, 0, 0, _Nglc_Nstmt_type_Ccase_end);
}
void _Nglc_Pstmt_switch_default_begin_5(int32_t _Lbegin_row_0, int32_t _Lbegin_col_1, int32_t _Lend_row_2, int32_t _Lend_col_3, bool _Lfall_through_4) {
struct _Nglc_Nstmt_default* _Ls_5;
_Nglc_Pquick_alloc_one_1(_Ls_5);
(*_Ls_5)._Ffall_through = _Lfall_through_4;
_Nglc_Pstmt_push_6(&(*_Ls_5)._Fbase, _Lbegin_row_0, _Lbegin_col_1, _Lend_row_2, _Lend_col_3, _Nglc_Nstmt_type_Cdefault);
_Nglc_Pstmt_space_begin_0();
}
void _Nglc_Pstmt_switch_default_end_0() {
struct _Nglc_Nstmt_default_end* _Ls_0;
_Nglc_Pstmt_space_end_0();
_Nglc_Pquick_alloc_one_1(_Ls_0);
_Nglc_Pstmt_push_6(&(*_Ls_0)._Fbase, 0, 0, 0, 0, _Nglc_Nstmt_type_Cdefault_end);
}
void _Nglc_Pstmt_switch_end_0() {
struct _Nglc_Nstmt_switch_end* _Ls_0;
_Nglc_Pquick_alloc_one_1(_Ls_0);
_Nglc_Pstmt_push_6(&(*_Ls_0)._Fbase, 0, 0, 0, 0, _Nglc_Nstmt_type_Cswitch_end);
_Nglc_Pstmt_space_end_0();
}
void _Nglc_Pstmt_if_begin_0() {
_Nglc_Pstmt_space_begin_0();
(*_Gdecl_func_ctx_space)._Fflags |= _Nglc_Nstmt_space_flags_Cskip_lvar_decl;
}
void _Nglc_Pstmt_if_set_6(bool _Lnot_0, _Nglc_Nexpr_i _Lexpr_1, int32_t _Lbegin_row_2, int32_t _Lbegin_col_3, int32_t _Lend_row_4, int32_t _Lend_col_5) {
struct _Nglc_Nstmt_if* _Ls_6;
_Nglc_Pquick_alloc_one_1(_Ls_6);
(*_Ls_6)._Fnot = _Lnot_0;
(*_Ls_6)._Fexpr = _Lexpr_1;
_Nglc_Pstmt_push_6(&(*_Ls_6)._Fbase, _Lbegin_row_2, _Lbegin_col_3, _Lend_row_4, _Lend_col_5, _Nglc_Nstmt_type_Cif);
_Nglc_Pstmt_space_begin_0();
}
void _Nglc_Pstmt_if_end_0() {
_Nglc_Pstmt_space_end_0();
}
void _Nglc_Pstmt_do_begin_0() {
_Nglc_Pstmt_space_begin_0();
(*_Gdecl_func_ctx_space)._Fflags |= _Nglc_Nstmt_space_flags_Cskip_lvar_decl;
}
void _Nglc_Pstmt_do_set_6(_Nglc_Nexpr_i _Lexpr_0, int32_t _Lbegin_row_1, int32_t _Lbegin_col_2, int32_t _Lend_row_3, int32_t _Lend_col_4, struct _Nglc_Nstmt_space* _Lcontinu_5) {
struct _Nglc_Nstmt_do* _Ls_6;
_Nglc_Pquick_alloc_one_1(_Ls_6);
_Gnest_stack_id_v[_Gnest_stack_c] = _Gnest_id++;
_Gnest_stack_ptr_v[_Gnest_stack_c]._Fdo = _Ls_6;
_Gnest_stack_c++;
(*_Ls_6)._Fexpr = _Lexpr_0;
(*_Ls_6)._Fcontinu = _Lcontinu_5;
_Nglc_Pstmt_push_6(&(*_Ls_6)._Fbase, _Lbegin_row_1, _Lbegin_col_2, _Lend_row_3, _Lend_col_4, _Nglc_Nstmt_type_Cdo);
_Nglc_Pstmt_space_begin_0();
}
void _Nglc_Pstmt_do_end_0() {
struct _Nglc_Nstmt_do_end* _Ls_0;
_Gnest_stack_c -= 1;
_Nglc_Pstmt_space_end_0();
_Nglc_Pquick_alloc_one_1(_Ls_0);
_Nglc_Pstmt_push_6(&(*_Ls_0)._Fbase, 0, 0, 0, 0, _Nglc_Nstmt_type_Cdo_end);
_Nglc_Pstmt_space_end_0();
}
void _Nglc_Pstmt_while_begin_0() {
_Nglc_Pstmt_space_begin_0();
(*_Gdecl_func_ctx_space)._Fflags |= _Nglc_Nstmt_space_flags_Cskip_lvar_decl;
}
void _Nglc_Pstmt_while_set_6(_Nglc_Nexpr_i _Lexpr_0, int32_t _Lbegin_row_1, int32_t _Lbegin_col_2, int32_t _Lend_row_3, int32_t _Lend_col_4, struct _Nglc_Nstmt_space* _Lcontinu_5) {
struct _Nglc_Nstmt_while* _Ls_6;
_Nglc_Pquick_alloc_one_1(_Ls_6);
_Gnest_stack_id_v[_Gnest_stack_c] = _Gnest_id++;
_Gnest_stack_ptr_v[_Gnest_stack_c]._Fwhile = _Ls_6;
_Gnest_stack_c++;
(*_Ls_6)._Fexpr = _Lexpr_0;
(*_Ls_6)._Fcontinu = _Lcontinu_5;
_Nglc_Pstmt_push_6(&(*_Ls_6)._Fbase, _Lbegin_row_1, _Lbegin_col_2, _Lend_row_3, _Lend_col_4, _Nglc_Nstmt_type_Cwhile);
_Nglc_Pstmt_space_begin_0();
}
void _Nglc_Pstmt_while_end_0() {
struct _Nglc_Nstmt_while_end* _Ls_0;
_Gnest_stack_c -= 1;
_Nglc_Pstmt_space_end_0();
_Nglc_Pquick_alloc_one_1(_Ls_0);
_Nglc_Pstmt_push_6(&(*_Ls_0)._Fbase, 0, 0, 0, 0, _Nglc_Nstmt_type_Cwhile_end);
_Nglc_Pstmt_space_end_0();
}
void _Nglc_Pstmt_elif_begin_0() {
}
void _Nglc_Pstmt_elif_set_6(bool _Lnot_0, _Nglc_Nexpr_i _Lexpr_1, int32_t _Lbegin_row_2, int32_t _Lbegin_col_3, int32_t _Lend_row_4, int32_t _Lend_col_5) {
struct _Nglc_Nstmt_if* _Ls_6;
_Nglc_Pquick_alloc_one_1(_Ls_6);
(*_Ls_6)._Fnot = _Lnot_0;
(*_Ls_6)._Fexpr = _Lexpr_1;
_Nglc_Pstmt_push_6(&(*_Ls_6)._Fbase, _Lbegin_row_2, _Lbegin_col_3, _Lend_row_4, _Lend_col_5, _Nglc_Nstmt_type_Cif_elif);
_Nglc_Pstmt_space_begin_0();
}
void _Nglc_Pstmt_elif_end_0() {
_Nglc_Pstmt_space_end_0();
}
void _Nglc_Pstmt_else_set_0() {
struct _Nglc_Nstmt_if_else* _Ls_0;
_Nglc_Pquick_alloc_one_1(_Ls_0);
_Nglc_Pstmt_push_6(&(*_Ls_0)._Fbase, 0, 0, 0, 0, _Nglc_Nstmt_type_Cif_else);
_Nglc_Pstmt_space_begin_0();
}
void _Nglc_Pstmt_else_end_0() {
_Nglc_Pstmt_space_end_0();
}
void _Nglc_Pstmt_if_end_ifs_0() {
struct _Nglc_Nstmt_if_end* _Ls_0;
_Nglc_Pquick_alloc_one_1(_Ls_0);
_Nglc_Pstmt_push_6(&(*_Ls_0)._Fbase, 0, 0, 0, 0, _Nglc_Nstmt_type_Cif_end);
_Nglc_Pstmt_space_end_0();
}
struct _Nglc_Nstmt_space* _Nglc_Pstmt_space_begin_0() {
return _Nglc_Pstmt_space_begin_1(true);
}
struct _Nglc_Nstmt_space* _Nglc_Pstmt_space_begin_detach_0() {
return _Nglc_Pstmt_space_begin_1(false);
}
struct _Nglc_Nstmt_space* _Nglc_Pstmt_space_end_0() {
struct _Nglc_Nstmt_space* _Lret_0;
_Lret_0 = _Gdecl_func_ctx_space;
_Gdecl_func_ctx_space = (*_Gdecl_func_ctx_space)._Fparent;
return _Lret_0;
}
_Nglc_Nexpr_i _Nglc_Pexpr_compare_3(_Nglc_Nexpr_i _Lleft_0, _Nglc_Nexpr_i _Lright_1, _Nglc_Ncompare _Ltype_2) {
struct _Nglc_Nexpr_compare* _Le_3;
_Nglc_Nexpr_i _Le_idx_4;
_Nglc_Pquick_alloc_one_1(_Le_3);
_Le_idx_4 = _Nglc_Pexpr_push_2(&(*_Le_3)._Fbase, _Nglc_Nexpr_type_Ccompare);
(*_Le_3)._Fleft = _Lleft_0;
(*_Le_3)._Fright = _Lright_1;
(*_Le_3)._Ftype = _Ltype_2;
return _Le_idx_4;
}
_Nglc_Nexpr_i _Nglc_Pexpr_bool_1(bool _Lvalue_0) {
struct _Nglc_Nexpr_bool* _Le_1;
_Nglc_Nexpr_i _Le_idx_2;
_Nglc_Pquick_alloc_one_1(_Le_1);
_Le_idx_2 = _Nglc_Pexpr_push_2(&(*_Le_1)._Fbase, _Nglc_Nexpr_type_Cbool);
(*_Le_1)._Fvalue = _Lvalue_0;
return _Le_idx_2;
}
_Nglc_Nexpr_i _Nglc_Pexpr_char_1(int32_t _Lvalue_0) {
struct _Nglc_Nexpr_char* _Le_1;
_Nglc_Nexpr_i _Le_idx_2;
_Nglc_Pquick_alloc_one_1(_Le_1);
_Le_idx_2 = _Nglc_Pexpr_push_2(&(*_Le_1)._Fbase, _Nglc_Nexpr_type_Cchar);
(*_Le_1)._Fvalue = _Lvalue_0;
return _Le_idx_2;
}
void _Nglc_Pcvar_attr_real_name_1(_Nglc_Nid _Lname_0) {
struct _Nglc_Ncvar_data* _Lc_1;
_Lc_1 = _Nglc_Ncvar_Pptr_1(_Glast_cvar);
(*_Lc_1)._Fdecl._Fflags |= _Nglc_Nvar_flags_Creal_name;
(*_Lc_1)._Fdecl._Freal_name = _Lname_0;
}
void _Nglc_Pcvar_attr_no_decl_0() {
struct _Nglc_Ncvar_data* _Lc_0;
_Lc_0 = _Nglc_Ncvar_Pptr_1(_Glast_cvar);
(*_Lc_0)._Fdecl._Fflags |= _Nglc_Nvar_flags_Cno_decl;
}
bool _Nglc_Ppreprocess_def_get_2(char* _Lname_0, uint8_t _Llen_1) {
int32_t _Li_2;
_Li_2 = 0;
for(int i = _Gpreprocess_def_c; i > 0; ) {
i --;
if(((_Gpreprocess_def_len_v[_Li_2] == _Llen_1) && (memcmp(_Gpreprocess_def_str_v[_Li_2], _Lname_0, _Llen_1) == 0))) {
return true;
}
continue_0:;
_Li_2++;
}
break_0:;
return false;
}
void _Nglc_Nat_Pput_to_header_1(_Nglc_Nat _Lat_0) {
if((_Gat_in_header_v[(_Lat_0 >> 3)] & (1 << (_Lat_0 & 7))) == 0) {
_Gat_in_header_v[(_Lat_0 >> 3)] |= (1 << (_Lat_0 & 7));
_Gat_in_header_idx_v[_Lat_0] = _Gat_in_header_c;
_Gat_in_header_at_v[_Gat_in_header_c++] = _Lat_0;
if(((_Lat_0 != _Nglc_Nat_Croot) && (_Lat_0 != _Nglc_Nat_Crelative))) {
_Nglc_Nat_Pput_to_header_1((*_Nglc_Nat_Pptr_1(_Lat_0))._Fparent);
}
}
}
inline void _Nglc_Ninclude_Pwr_2(_Nglc_Ninclude _Li_0, union _Nglc_Nwtr* _Lw_1) {
Fputnum(_Lw_1, _Li_0 + 1);
}
void _Nglc_Ndecl_var_data_Pwr_3(struct _Nglc_Ndecl_var_data* _Lvd_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2) {
_Nglc_Nid_Pwr_3((*_Lvd_0)._Fname, _Lw_1, _Lheader_2);
_Nglc_Nat_Pwr_3((*_Lvd_0)._Ftype, _Lw_1, _Lheader_2);
_Nglc_Nvar_flags_Pwr_2((*_Lvd_0)._Fflags, _Lw_1);
if(((*_Lvd_0)._Fflags & _Nglc_Nvar_flags_Creal_name) != _Nglc_Nvar_flags_C0) {
_Nglc_Nid_Pwr_3((*_Lvd_0)._Freal_name, _Lw_1, _Lheader_2);
}
_Nglc_Ntype_info_Pwr_2(&(*_Lvd_0)._Ftype_info, _Lw_1);
_Nglc_Nwtr_Pn1_2(_Lw_1, (*_Lvd_0)._Fsize_c);
int32_t _Li_3;
_Li_3 = 0;
for(int i = (*_Lvd_0)._Fsize_c; i > 0; ) {
i --;
_Nglc_Nexpr_i_Pwr_3((*_Lvd_0)._Fsize_expr_v[_Li_3], _Lw_1, _Lheader_2);
continue_0:;
_Li_3++;
}
break_0:;
}
inline void _Nglc_Ncvar_flags_Pwr_2(_Nglc_Ncvar_flags _Lf_0, union _Nglc_Nwtr* _Lw_1) {
_Nglc_Nwtr_Pn1_2(_Lw_1, _Lf_0);
}
void _Nglc_Nexpr_i_Pwr_3(_Nglc_Nexpr_i _Le_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2) {
if(_Nglc_Cdebug_rd_wr) {
_Nglc_Nwtr_Pn1_2(_Lw_1, 255);
}
if(_Le_0 == _Nglc_Nexpr_i_Cnil) {
_Nglc_Nexpr_type_Pwr_2(_Nglc_Nexpr_type_Cnil, _Lw_1);
} else {
struct _Nglc_Nexpr* _Lexpr_3;
_Lexpr_3 = _Nglc_Nexpr_i_Pptr_1(_Le_0);
_Nglc_Nexpr_type_Pwr_2((*_Lexpr_3)._Ftype, _Lw_1);
switch((*_Lexpr_3)._Ftype) {
case _Nglc_Nexpr_type_Cmath:;
_Nglc_Nexpr_i_Pwr_math_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _Nglc_Nexpr_type_Cbools:;
_Nglc_Nexpr_i_Pwr_bools_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _Nglc_Nexpr_type_Cstr:;
_Nglc_Nexpr_i_Pwr_str_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _Nglc_Nexpr_type_Ccvar:;
_Nglc_Nexpr_i_Pwr_cvar_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _Nglc_Nexpr_type_Cunary:;
_Nglc_Nexpr_i_Pwr_unary_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _Nglc_Nexpr_type_Cref:;
_Nglc_Nexpr_i_Pwr_ref_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _Nglc_Nexpr_type_Ccast_fast:;
_Nglc_Nexpr_i_Pwr_cast_fast_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _Nglc_Nexpr_type_Cindex:;
_Nglc_Nexpr_i_Pwr_index_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _Nglc_Nexpr_type_Ccompare:;
_Nglc_Nexpr_i_Pwr_compare_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _Nglc_Nexpr_type_Cbool:;
_Nglc_Nexpr_i_Pwr_bool_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _Nglc_Nexpr_type_Cchar:;
_Nglc_Nexpr_i_Pwr_char_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _Nglc_Nexpr_type_Cmethod:;
_Nglc_Nexpr_i_Pwr_method_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _Nglc_Nexpr_type_Cfunc:;
_Nglc_Nexpr_i_Pwr_func_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _Nglc_Nexpr_type_Cnull:;
_Nglc_Nexpr_i_Pwr_null_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _Nglc_Nexpr_type_Ci32:;
_Nglc_Nexpr_i_Pwr_i32_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _Nglc_Nexpr_type_Csize_of_type:;
_Nglc_Nexpr_i_Pwr_size_of_type_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _Nglc_Nexpr_type_Cassign:;
_Nglc_Nexpr_i_Pwr_assign_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _Nglc_Nexpr_type_Cfvar:;
_Nglc_Nexpr_i_Pwr_fvar_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _Nglc_Nexpr_type_Cgvar:;
_Nglc_Nexpr_i_Pwr_gvar_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _Nglc_Nexpr_type_Clvar:;
_Nglc_Nexpr_i_Pwr_lvar_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
default:;
fprintf(stdout, "wr() was not implemented in expression #%s\n", _Nglc_Nexpr_type_Pcgl_name_1((*_Lexpr_3)._Ftype));
exit(_Nstdc_Nexit_Cfailure);
break;
}
}
if(_Nglc_Cdebug_rd_wr) {
_Nglc_Nwtr_Pn1_2(_Lw_1, 255);
}
}
inline void _Nglc_Ncvar_Pwr_2(_Nglc_Ncvar _Lg_0, union _Nglc_Nwtr* _Lw_1) {
Fputnum(_Lw_1, _Lg_0 + 1);
}
inline void _Nglc_Nenum_flags_Pwr_2(_Nglc_Nenum_flags _Le_0, union _Nglc_Nwtr* _Lw_1) {
_Nglc_Nwtr_Pn1_2(_Lw_1, _Le_0);
}
inline void _Nglc_Nstruct_flags_Pwr_2(_Nglc_Nstruct_flags _Lf_0, union _Nglc_Nwtr* _Lw_1) {
_Nglc_Nwtr_Pn1_2(_Lw_1, _Lf_0);
}
void _Nglc_Nfvar_data_Pwr_3(struct _Nglc_Nfvar_data* _Lf_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2) {
_Nglc_Ndecl_var_data_Pwr_3(&(*_Lf_0)._Fdecl, _Lw_1, _Lheader_2);
}
void _Nglc_Nfarg_Pwr_3(struct _Nglc_Nfarg* _Lf_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2) {
_Nglc_Ndecl_var_data_Pwr_3(&(*_Lf_0)._Fdecl, _Lw_1, _Lheader_2);
}
inline void _Nglc_Nfunc_flags_Pwr_2(_Nglc_Nfunc_flags _Le_0, union _Nglc_Nwtr* _Lw_1) {
Fputnum(_Lw_1, _Le_0);
}
inline void _Nglc_Nfunc_Pwr_2(_Nglc_Nfunc _Lf_0, union _Nglc_Nwtr* _Lw_1) {
Fputnum(_Lw_1, _Lf_0 + _Nglc_Nfunc_C1);
}
void _Nglc_Ndecl_func_Plvars_wr_3(struct _Nglc_Ndecl_func* _Lf_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2) {
Fputnum(_Lw_1, (*_Lf_0)._Flvar_c);
int32_t _Li_3;
_Li_3 = 0;
for(int i = (*_Lf_0)._Flvar_c; i > 0; ) {
i --;
struct _Nglc_Nlvar_data* _Ll_4;
_Ll_4 = (*_Lf_0)._Flvar_v[_Li_3];
Fputnum(_Lw_1, (*_Ll_4)._Frow);
Fputnum(_Lw_1, (*_Ll_4)._Fcol);
_Nglc_Ndecl_var_data_Pwr_3(&(*_Ll_4)._Fdecl, _Lw_1, _Lheader_2);
_Nglc_Nlvar_flags_Pwr_2((*_Ll_4)._Fflags, _Lw_1);
if(((*_Ll_4)._Fflags & _Nglc_Nlvar_flags_Cset_expr) != _Nglc_Nlvar_flags_C0) {
_Nglc_Nexpr_i_Pwr_3((*_Ll_4)._Fset_expr, _Lw_1, _Lheader_2);
}
continue_0:;
_Li_3++;
}
break_0:;
}
void _Nglc_Nstmt_space_Pwr_3(struct _Nglc_Nstmt_space* _Lspace_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2) {
struct _Nglc_Nstmt* _Lstmt_4;
Fputnum(_Lw_1, (*_Lspace_0)._Flvar_c);
int32_t _Li_3;
_Li_3 = 0;
for(int i = (*_Lspace_0)._Flvar_c; i > 0; ) {
i --;
_Nglc_Nlvar_Pwr_2((*_Lspace_0)._Flvar_v[_Li_3], _Lw_1);
continue_0:;
_Li_3++;
}
break_0:;
_Lstmt_4 = (*_Lspace_0)._Fstmt_first;
while(_Lstmt_4 != NULL) {
_Nglc_Nstmt_type_Pwr_2((*_Lstmt_4)._Ftype, _Lw_1);
if(_Nglc_Cdebug_rd_wr) {
_Nglc_Nwtr_Pn1_2(_Lw_1, 255);
}
Fputnum(_Lw_1, (*_Lstmt_4)._Fbegin_row);
Fputnum(_Lw_1, (*_Lstmt_4)._Fbegin_col);
Fputnum(_Lw_1, (*_Lstmt_4)._Fend_row);
Fputnum(_Lw_1, (*_Lstmt_4)._Fend_col);
switch((*_Lstmt_4)._Ftype) {
case _Nglc_Nstmt_type_Cbreak:;
_Nglc_Nstmt_space_Pwr_break_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _Nglc_Nstmt_type_Cswitch:;
_Nglc_Nstmt_space_Pwr_switch_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _Nglc_Nstmt_type_Ccase:;
_Nglc_Nstmt_space_Pwr_case_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _Nglc_Nstmt_type_Ccase_end:;
_Nglc_Nstmt_space_Pwr_case_end_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _Nglc_Nstmt_type_Cdefault:;
_Nglc_Nstmt_space_Pwr_default_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _Nglc_Nstmt_type_Cdefault_end:;
_Nglc_Nstmt_space_Pwr_default_end_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _Nglc_Nstmt_type_Cswitch_end:;
_Nglc_Nstmt_space_Pwr_switch_end_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _Nglc_Nstmt_type_Cif:;
_Nglc_Nstmt_space_Pwr_if_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _Nglc_Nstmt_type_Cif_elif:;
_Nglc_Nstmt_space_Pwr_if_elif_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _Nglc_Nstmt_type_Cif_else:;
_Nglc_Nstmt_space_Pwr_if_else_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _Nglc_Nstmt_type_Cif_end:;
_Nglc_Nstmt_space_Pwr_if_end_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _Nglc_Nstmt_type_Cdo:;
_Nglc_Nstmt_space_Pwr_do_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _Nglc_Nstmt_type_Cdo_end:;
_Nglc_Nstmt_space_Pwr_do_end_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _Nglc_Nstmt_type_Cwhile:;
_Nglc_Nstmt_space_Pwr_while_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _Nglc_Nstmt_type_Cwhile_end:;
_Nglc_Nstmt_space_Pwr_while_end_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _Nglc_Nstmt_type_Ccontinue:;
_Nglc_Nstmt_space_Pwr_continue_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _Nglc_Nstmt_type_Creturn:;
_Nglc_Nstmt_space_Pwr_return_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _Nglc_Nstmt_type_Cspace:;
_Nglc_Nstmt_space_Pwr_space_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _Nglc_Nstmt_type_Cexpr:;
_Nglc_Nstmt_space_Pwr_expr_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
default:;
fprintf(stdout, "wr() not yet implemented in stmt #%s\n", _Nglc_Nstmt_type_Pcgl_name_1((*_Lstmt_4)._Ftype));
exit(_Nstdc_Nexit_Cfailure);
break;
}
if(_Nglc_Cdebug_rd_wr) {
_Nglc_Nwtr_Pn1_2(_Lw_1, 255);
}
_Lstmt_4 = (*_Lstmt_4)._Fstmt_next;
continue_1:;
}
break_1:;
_Nglc_Nstmt_type_Pwr_2(_Nglc_Nstmt_type_Cnil, _Lw_1);
}
inline void _Nglc_Nwtr_Pn4_2(union _Nglc_Nwtr* _Lw_0, uint32_t _Ln_1) {
(*_Lw_0)._Fp1[0] = _Ln_1;
(*_Lw_0)._Fp1[1] = (_Ln_1 >> 8);
(*_Lw_0)._Fp1[2] = (_Ln_1 >> 16);
(*_Lw_0)._Fp1[3] = (_Ln_1 >> 24);
(*_Lw_0)._Fpos += 4;
}
void _Nglc_Ndecl_var_data_Pcopy_from_2(struct _Nglc_Ndecl_var_data* _Lvd_0, struct _Nglc_Ndecl_var_data* _Lsrc_1) {
(*_Lvd_0)._Fname = (*_Lsrc_1)._Fname;
(*_Lvd_0)._Ftype = (*_Lsrc_1)._Ftype;
(*_Lvd_0)._Fflags = (*_Lsrc_1)._Fflags;
(*_Lvd_0)._Freal_name = (*_Lsrc_1)._Freal_name;
_Nglc_Ntype_info_Pcopy_from_2(&(*_Lvd_0)._Ftype_info, &(*_Lsrc_1)._Ftype_info);
(*_Lvd_0)._Ftype_info._Fbuilt_in = (*_Lsrc_1)._Ftype_info._Fbuilt_in;
(*_Lvd_0)._Fsize_c = (*_Lsrc_1)._Fsize_c;
if((*_Lvd_0)._Fsize_c > 0) {
_Nglc_Pquick_alloc_arr_2((*_Lvd_0)._Fsize_expr_v, (*_Lvd_0)._Fsize_c);
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
void _Nglc_Nfarg_Pcopy_from_2(struct _Nglc_Nfarg* _Lf_0, struct _Nglc_Nfarg* _Lsrc_1) {
(*_Lf_0)._Frow = (*_Lsrc_1)._Frow;
(*_Lf_0)._Fcol = (*_Lsrc_1)._Fcol;
_Nglc_Ndecl_var_data_Pcopy_from_2(&(*_Lf_0)._Fdecl, &(*_Lsrc_1)._Fdecl);
}
inline uint8_t _Nglc_Nid_Plen_1(_Nglc_Nid _Lid_0) {
return _Gid_len_v[_Lid_0];
}
inline char* _Nglc_Nid_Pstr_1(_Nglc_Nid _Lid_0) {
return _Gid_str_v[_Lid_0];
}
inline struct _Nglc_Ndecl_func* _Nglc_Nfunc_Pptr_1(_Nglc_Nfunc _Lf_0) {
return _Gfunc_v[_Lf_0];
}
_Nglc_Nlvar _Nglc_Nstmt_space_Plvar_new_4(struct _Nglc_Nstmt_space* _Lspace_0, _Nglc_Nid _Lname_1, int32_t _Lrow_2, int32_t _Lcol_3) {
_Nglc_Nlvar* _Lv_4;
int32_t _Li_7;
struct _Nglc_Ndecl_func* _Lf_9;
_Nglc_Nlvar _Llvar_10;
struct _Nglc_Nlvar_data* _Litem_12;
_Lv_4 = (*_Lspace_0)._Flvar_v;
int32_t _Li_5;
_Li_5 = 0;
for(int i = (*_Lspace_0)._Flvar_c; i > 0; ) {
i --;
struct _Nglc_Nlvar_data* _Llvar_6;
_Llvar_6 = _Nglc_Nlvar_Pptr_1(_Lv_4[_Li_5]);
if((*_Llvar_6)._Fdecl._Fname == _Lname_1) {
fprintf(stdout, "%u:%u: lvar '%s' was already declared at %u:%u\n", _Lrow_2, _Lcol_3, _Nglc_Nid_Pstr_1(_Lname_1), (*_Llvar_6)._Frow, (*_Llvar_6)._Fcol);
exit(_Nstdc_Nexit_Cfailure);
}
continue_0:;
_Li_5++;
}
break_0:;
_Li_7 = (*_Lspace_0)._Flvar_c++;
if((*_Lspace_0)._Flvar_cap <= (*_Lspace_0)._Flvar_c) {
int32_t _Lold_cap_8;
_Lold_cap_8 = (*_Lspace_0)._Flvar_cap;
_Nglc_Pgrow_2((*_Lspace_0)._Flvar_cap, (*_Lspace_0)._Flvar_c);
_Nglc_Prealloc_3((*_Lspace_0)._Flvar_v, (*_Lspace_0)._Flvar_cap, _Lold_cap_8);
}
_Lf_9 = _Gctx_func;
_Llvar_10 = (*_Lf_9)._Flvar_c++;
(*_Lspace_0)._Flvar_v[_Li_7] = _Llvar_10;
if((*_Lf_9)._Flvar_cap <= (*_Lf_9)._Flvar_c) {
_Nglc_Nlvar _Lold_cap_11;
_Lold_cap_11 = (*_Lf_9)._Flvar_cap;
_Nglc_Pgrow_2((*_Lf_9)._Flvar_cap, (*_Lf_9)._Flvar_c);
_Nglc_Prealloc_3((*_Lf_9)._Flvar_v, (*_Lf_9)._Flvar_cap, _Lold_cap_11);
}
_Nglc_Pquick_alloc_one_1(_Litem_12);
(*_Lf_9)._Flvar_v[_Llvar_10] = _Litem_12;
(*_Litem_12)._Frow = _Lrow_2;
(*_Litem_12)._Fcol = _Lcol_3;
(*_Litem_12)._Fdecl._Fname = _Lname_1;
return _Llvar_10;
}
inline struct _Nglc_Nlvar_data* _Nglc_Nlvar_Pptr_1(_Nglc_Nlvar _Ll_0) {
return (*_Gctx_func)._Flvar_v[_Ll_0];
}
void _Nglc_Ntype_info_Pinit_1(struct _Nglc_Ntype_info* _Lti_0) {
(*_Lti_0)._Fref_v[0] = 0;
(*_Lti_0)._Farray_c = 0;
(*_Lti_0)._Fstar_c = 0;
(*_Lti_0)._Fbuilt_in = false;
(*_Lti_0)._Fconst = false;
}
_Nglc_Nexpr_i _Nglc_Pexpr_push_2(struct _Nglc_Nexpr* _Le_0, _Nglc_Nexpr_type _Ltype_1) {
int32_t _Le_idx_2;
(*_Le_0)._Ftype = _Ltype_1;
_Le_idx_2 = _Gexpr_c++;
if(_Gexpr_cap <= _Gexpr_c) {
int32_t _Lold_cap_3;
_Lold_cap_3 = _Gexpr_cap;
_Nglc_Pgrow_2(_Gexpr_cap, _Gexpr_c);
_Nglc_Prealloc_3(_Gexpr_v, _Gexpr_cap, _Lold_cap_3);
}
_Gexpr_v[_Le_idx_2] = _Le_0;
return _Le_idx_2;
}
inline struct _Nglc_Nexpr* _Nglc_Nexpr_i_Pptr_1(_Nglc_Nexpr_i _Le_0) {
return _Gexpr_v[_Le_0];
}
void _Nglc_Pstmt_push_6(struct _Nglc_Nstmt* _Ls_0, int32_t _Lbegin_row_1, int32_t _Lbegin_col_2, int32_t _Lend_row_3, int32_t _Lend_col_4, _Nglc_Nstmt_type _Ltype_5) {
(*_Ls_0)._Fbegin_row = _Lbegin_row_1;
(*_Ls_0)._Fbegin_col = _Lbegin_col_2;
(*_Ls_0)._Fend_row = _Lend_row_3;
(*_Ls_0)._Fend_col = _Lend_col_4;
(*_Ls_0)._Ftype = _Ltype_5;
_Nglc_Pfunc_stmt_add_1(_Ls_0);
}
inline _Nglc_Nid _Nglc_Nlvar_Pname_1(_Nglc_Nlvar _Ll_0) {
return (*_Nglc_Nlvar_Pptr_1(_Ll_0))._Fdecl._Fname;
}
inline struct _Nglc_Nat_data* _Nglc_Nat_Pptr_1(_Nglc_Nat _Li_0) {
return &_Gat_v[_Li_0];
}
_Nglc_Nat _Nglc_Pat_create_basic_1(_Nglc_Nbasic_type_id _Lbasic_0) {
_Nglc_Nat _Lbuild_idx_3;
struct _Nglc_Nat_data* _Lat_5;
_Nglc_Nat _Li_1;
_Li_1 = (_Nglc_Nat)(0);
for(int i = _Gat_c; i > 0; ) {
i --;
struct _Nglc_Nat_data* _Lat_2;
_Lat_2 = (&_Gat_v[_Li_1]);
if((((*_Lat_2)._Ftype == _Nglc_Nname_type_Cbasic) && ((*_Lat_2)._Fname._Fbasic == _Lbasic_0))) {
return _Li_1;
}
continue_0:;
_Li_1++;
}
break_0:;
_Lbuild_idx_3 = _Gat_c++;
if(_Gat_cap <= _Gat_c) {
_Nglc_Nat _Lold_cap_4;
_Lold_cap_4 = _Gat_cap;
_Nglc_Pgrow_2(_Gat_cap, _Gat_c);
_Nglc_Prealloc_3(_Gat_v, _Gat_cap, _Lold_cap_4);
}
_Lat_5 = (&_Gat_v[_Lbuild_idx_3]);
(*_Lat_5)._Fparent = _Nglc_Nat_Croot;
(*_Lat_5)._Ftype = _Nglc_Nname_type_Cbasic;
(*_Lat_5)._Fname._Fbasic = _Lbasic_0;
return _Lbuild_idx_3;
}
_Nglc_Nat _Nglc_Pat_create_3(_Nglc_Nat _Lparent_0, _Nglc_Nname_type _Ltype_1, _Nglc_Nid _Lname_2) {
int32_t _Lfound_3;
_Nglc_Nat _Lbuild_idx_4;
struct _Nglc_Nat_data* _Lat_6;
_Lfound_3 = _Nglc_Nat_map_Pget_or_insert_5(&_Gat_map, _Lparent_0, _Ltype_1, _Lname_2, _Gat_c);
if(_Lfound_3 != -1) {
return _Lfound_3;
}
_Lbuild_idx_4 = _Gat_c++;
if(_Gat_cap <= _Gat_c) {
_Nglc_Nat _Lold_cap_5;
_Lold_cap_5 = _Gat_cap;
_Nglc_Pgrow_2(_Gat_cap, _Gat_c);
_Nglc_Prealloc_3(_Gat_v, _Gat_cap, _Lold_cap_5);
}
_Lat_6 = (&_Gat_v[_Lbuild_idx_4]);
(*_Lat_6)._Fparent = _Lparent_0;
(*_Lat_6)._Ftype = _Ltype_1;
(*_Lat_6)._Fname._Fid = _Lname_2;
return _Lbuild_idx_4;
}
void _Nglc_Ptype_info_arr_1(_Nglc_Nexpr_i _Lexpr_0) {
struct _Nglc_Ntype_info* _Lti_1;
_Lti_1 = (&_Gdecl_var._Ftype_info);
(*_Lti_1)._Farray_c += 1;
(*_Lti_1)._Fref_v[(*_Lti_1)._Farray_c] = 0;
if(_Lexpr_0 != _Nglc_Nexpr_i_Cnil) {
struct _Nglc_Ndecl_var_data* _Lvd_2;
_Lvd_2 = (&_Gdecl_var);
if((*_Lvd_2)._Fsize_c == 0) {
_Nglc_Pquick_alloc_arr_2((*_Lvd_2)._Fsize_expr_v, _Nglc_Cdecl_var_size_limit);
}
(*_Lvd_2)._Fsize_expr_v[(*_Lvd_2)._Fsize_c++] = _Lexpr_0;
}
}
void _Nglc_Ntype_info_Pfinalize_1(struct _Nglc_Ntype_info* _Lti_0) {
int8_t _Lref_v_1[_Nglc_Ctype_info_star_limit];
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
inline struct _Nglc_Ncvar_data* _Nglc_Ncvar_Pptr_1(_Nglc_Ncvar _Lc_0) {
return &_Gcvar_v[_Lc_0];
}
struct _Nglc_Nstmt_space* _Nglc_Pstmt_space_begin_1(bool _Lattach_0) {
struct _Nglc_Nstmt_space* _Lparent_1;
struct _Nglc_Nstmt_space* _Lspace_2;
_Lparent_1 = _Gdecl_func_ctx_space;
_Nglc_Pquick_alloc_one_1(_Gdecl_func_ctx_space);
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
inline void _Nglc_Nvar_flags_Pwr_2(_Nglc_Nvar_flags _Lf_0, union _Nglc_Nwtr* _Lw_1) {
Fputnum(_Lw_1, _Lf_0);
}
void _Nglc_Ntype_info_Pwr_2(struct _Nglc_Ntype_info* _Lti_0, union _Nglc_Nwtr* _Lw_1) {
int32_t _Lc_2;
_Lc_2 = 0;
for(int i = _Nglc_Ctype_info_star_limit; i > 0; ) {
i --;
if((*_Lti_0)._Fref_v[_Lc_2] == 0) {
goto break_0;
}
_Lc_2++;
continue_0:;
}
break_0:;
_Nglc_Nwtr_Pn1_2(_Lw_1, _Lc_2);
int32_t _Li_3;
_Li_3 = 0;
for(int i = _Lc_2; i > 0; ) {
i --;
_Nglc_Nwtr_Pn1_2(_Lw_1, (*_Lti_0)._Fref_v[_Li_3]);
continue_1:;
_Li_3++;
}
break_1:;
_Nglc_Nwtr_Pn1_2(_Lw_1, (*_Lti_0)._Farray_c);
_Nglc_Nwtr_Pn1_2(_Lw_1, (*_Lti_0)._Fstar_c);
_Nglc_Nwtr_Pb_2(_Lw_1, (*_Lti_0)._Fbuilt_in);
_Nglc_Nwtr_Pb_2(_Lw_1, (*_Lti_0)._Fconst);
}
inline void _Nglc_Nexpr_type_Pwr_2(_Nglc_Nexpr_type _Le_0, union _Nglc_Nwtr* _Lw_1) {
_Nglc_Nwtr_Pn1_2(_Lw_1, _Le_0);
}
inline void _Nglc_Nexpr_i_Pwr_math_3(struct _Nglc_Nexpr* _Lexpr_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2) {
struct _Nglc_Nexpr_math* _Le_3;
_Le_3 = _Lexpr_0;
_Nglc_Nexpr_i_Pwr_3((*_Le_3)._Fleft, _Lw_1, _Lheader_2);
_Nglc_Nexpr_i_Pwr_3((*_Le_3)._Fright, _Lw_1, _Lheader_2);
_Nglc_Nmath_Pwr_2((*_Le_3)._Ftype, _Lw_1);
_Nglc_Nwtr_Pn1_2(_Lw_1, (*_Le_3)._Fitem_c);
int32_t _Li_4;
_Li_4 = 0;
for(int i = (*_Le_3)._Fitem_c; i > 0; ) {
i --;
_Nglc_Nexpr_i_Pwr_3((*_Le_3)._Fitem_v[_Li_4]._Fexpr, _Lw_1, _Lheader_2);
continue_0:;
_Li_4++;
}
break_0:;
}
inline void _Nglc_Nexpr_i_Pwr_bools_3(struct _Nglc_Nexpr* _Lexpr_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2) {
struct _Nglc_Nexpr_bools* _Le_3;
_Le_3 = _Lexpr_0;
_Nglc_Nexpr_i_Pwr_3((*_Le_3)._Fleft, _Lw_1, _Lheader_2);
_Nglc_Nexpr_i_Pwr_3((*_Le_3)._Fright, _Lw_1, _Lheader_2);
_Nglc_Nwtr_Pn1_2(_Lw_1, (*_Le_3)._Fitem_c);
int32_t _Li_4;
_Li_4 = 0;
for(int i = (*_Le_3)._Fitem_c; i > 0; ) {
i --;
_Nglc_Nexpr_i_Pwr_3((*_Le_3)._Fitem_v[_Li_4]._Fexpr, _Lw_1, _Lheader_2);
continue_0:;
_Li_4++;
}
break_0:;
_Nglc_Nbools_Pwr_2((*_Le_3)._Ftype, _Lw_1);
}
inline void _Nglc_Nexpr_i_Pwr_str_3(struct _Nglc_Nexpr* _Lexpr_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2) {
struct _Nglc_Nexpr_str* _Le_3;
struct _Nglc_Nexpr_str_node* _Ln_4;
_Le_3 = _Lexpr_0;
Fputnum(_Lw_1, (*_Le_3)._Fnode_c);
_Ln_4 = (*_Le_3)._Ffirst;
while(1) {
Fputnum(_Lw_1, (*_Ln_4)._Flen);
_Nglc_Nwtr_Pcopy_3(_Lw_1, (*_Ln_4)._Fbuf, (*_Ln_4)._Flen);
_Ln_4 = (*_Ln_4)._Fnext;
if(_Ln_4 == NULL) {
goto break_0;
}
continue_0:;
}
break_0:;
}
inline void _Nglc_Nexpr_i_Pwr_cvar_3(struct _Nglc_Nexpr* _Lexpr_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2) {
struct _Nglc_Nexpr_cvar* _Le_3;
_Le_3 = _Lexpr_0;
_Nglc_Nat_Pwr_3((*_Le_3)._Fat, _Lw_1, _Lheader_2);
_Nglc_Nid_Pwr_3((*_Le_3)._Fname, _Lw_1, _Lheader_2);
}
inline void _Nglc_Nexpr_i_Pwr_unary_3(struct _Nglc_Nexpr* _Lexpr_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2) {
struct _Nglc_Nexpr_unary* _Le_3;
_Le_3 = _Lexpr_0;
_Nglc_Nexpr_i_Pwr_3((*_Le_3)._Fexpr, _Lw_1, _Lheader_2);
_Nglc_Nunary_Pwr_2((*_Le_3)._Ftype, _Lw_1);
}
inline void _Nglc_Nexpr_i_Pwr_ref_3(struct _Nglc_Nexpr* _Lexpr_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2) {
struct _Nglc_Nexpr_ref* _Le_3;
_Le_3 = _Lexpr_0;
_Nglc_Nexpr_i_Pwr_3((*_Le_3)._Fexpr, _Lw_1, _Lheader_2);
}
inline void _Nglc_Nexpr_i_Pwr_cast_fast_3(struct _Nglc_Nexpr* _Lexpr_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2) {
struct _Nglc_Nexpr_cast_fast* _Le_3;
_Le_3 = _Lexpr_0;
_Nglc_Nexpr_i_Pwr_3((*_Le_3)._Fexpr, _Lw_1, _Lheader_2);
_Nglc_Nat_Pwr_3((*_Le_3)._Ftype, _Lw_1, _Lheader_2);
}
inline void _Nglc_Nexpr_i_Pwr_index_3(struct _Nglc_Nexpr* _Lexpr_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2) {
struct _Nglc_Nexpr_index* _Le_3;
_Le_3 = _Lexpr_0;
_Nglc_Nexpr_i_Pwr_3((*_Le_3)._Fleft, _Lw_1, _Lheader_2);
_Nglc_Nexpr_i_Pwr_3((*_Le_3)._Fright, _Lw_1, _Lheader_2);
}
inline void _Nglc_Nexpr_i_Pwr_compare_3(struct _Nglc_Nexpr* _Lexpr_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2) {
struct _Nglc_Nexpr_compare* _Le_3;
_Le_3 = _Lexpr_0;
_Nglc_Nexpr_i_Pwr_3((*_Le_3)._Fleft, _Lw_1, _Lheader_2);
_Nglc_Nexpr_i_Pwr_3((*_Le_3)._Fright, _Lw_1, _Lheader_2);
_Nglc_Ncompare_Pwr_2((*_Le_3)._Ftype, _Lw_1);
}
inline void _Nglc_Nexpr_i_Pwr_bool_3(struct _Nglc_Nexpr* _Lexpr_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2) {
struct _Nglc_Nexpr_bool* _Le_3;
_Le_3 = _Lexpr_0;
_Nglc_Nwtr_Pb_2(_Lw_1, (*_Le_3)._Fvalue);
}
inline void _Nglc_Nexpr_i_Pwr_char_3(struct _Nglc_Nexpr* _Lexpr_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2) {
struct _Nglc_Nexpr_char* _Le_3;
_Le_3 = _Lexpr_0;
Fputnum(_Lw_1, (*_Le_3)._Fvalue);
}
inline void _Nglc_Nexpr_i_Pwr_method_3(struct _Nglc_Nexpr* _Lexpr_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2) {
struct _Nglc_Nexpr_method* _Le_3;
_Le_3 = _Lexpr_0;
_Nglc_Nexpr_i_Pwr_3((*_Le_3)._Fthis, _Lw_1, _Lheader_2);
_Nglc_Nid_Pwr_3((*_Le_3)._Ffunc_name, _Lw_1, _Lheader_2);
_Nglc_Nwtr_Pn1_2(_Lw_1, (*_Le_3)._Fgroup_c);
int32_t _Li_4;
_Li_4 = 0;
for(int i = (*_Le_3)._Fgroup_c; i > 0; ) {
i --;
_Nglc_Nwtr_Pn1_2(_Lw_1, (*_Le_3)._Fgroup_v[_Li_4]);
continue_0:;
_Li_4++;
}
break_0:;
_Nglc_Nwtr_Pn1_2(_Lw_1, (*_Le_3)._Fcarg_c);
int32_t _Li_5;
_Li_5 = 0;
for(int i = (*_Le_3)._Fcarg_c; i > 0; ) {
i --;
_Nglc_Nexpr_i_Pwr_3((*_Le_3)._Fcarg_v[_Li_5]._Fexpr, _Lw_1, _Lheader_2);
continue_1:;
_Li_5++;
}
break_1:;
}
inline void _Nglc_Nexpr_i_Pwr_func_3(struct _Nglc_Nexpr* _Lexpr_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2) {
struct _Nglc_Nexpr_func* _Le_3;
_Le_3 = _Lexpr_0;
_Nglc_Nat_Pwr_3((*_Le_3)._Fat, _Lw_1, _Lheader_2);
_Nglc_Nid_Pwr_3((*_Le_3)._Ffunc_name, _Lw_1, _Lheader_2);
_Nglc_Nwtr_Pn1_2(_Lw_1, (*_Le_3)._Fgroup_c);
int32_t _Li_4;
_Li_4 = 0;
for(int i = (*_Le_3)._Fgroup_c; i > 0; ) {
i --;
_Nglc_Nwtr_Pn1_2(_Lw_1, (*_Le_3)._Fgroup_v[_Li_4]);
continue_0:;
_Li_4++;
}
break_0:;
_Nglc_Nwtr_Pn1_2(_Lw_1, (*_Le_3)._Fcarg_c);
int32_t _Li_5;
_Li_5 = 0;
for(int i = (*_Le_3)._Fcarg_c; i > 0; ) {
i --;
_Nglc_Nexpr_i_Pwr_3((*_Le_3)._Fcarg_v[_Li_5]._Fexpr, _Lw_1, _Lheader_2);
continue_1:;
_Li_5++;
}
break_1:;
}
inline void _Nglc_Nexpr_i_Pwr_null_3(struct _Nglc_Nexpr* _Lexpr_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2) {
struct _Nglc_Nexpr_null* _Le_3;
_Le_3 = _Lexpr_0;
}
inline void _Nglc_Nexpr_i_Pwr_i32_3(struct _Nglc_Nexpr* _Lexpr_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2) {
struct _Nglc_Nexpr_int_data* _Le_3;
_Le_3 = _Lexpr_0;
_Nglc_Nwtr_Pn1_2(_Lw_1, (*_Le_3)._Ftype);
Fputnum(_Lw_1, (*_Le_3)._Fvalue);
}
inline void _Nglc_Nexpr_i_Pwr_size_of_type_3(struct _Nglc_Nexpr* _Lexpr_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2) {
struct _Nglc_Nexpr_size_of_type* _Le_3;
_Le_3 = _Lexpr_0;
_Nglc_Nat_Pwr_3((*_Le_3)._Ftype, _Lw_1, _Lheader_2);
}
inline void _Nglc_Nexpr_i_Pwr_assign_3(struct _Nglc_Nexpr* _Lexpr_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2) {
struct _Nglc_Nexpr_assign* _Le_3;
_Le_3 = _Lexpr_0;
_Nglc_Nexpr_i_Pwr_3((*_Le_3)._Fleft, _Lw_1, _Lheader_2);
_Nglc_Nexpr_i_Pwr_3((*_Le_3)._Fright, _Lw_1, _Lheader_2);
_Nglc_Nassign_Pwr_2((*_Le_3)._Ftype, _Lw_1);
}
inline void _Nglc_Nexpr_i_Pwr_fvar_3(struct _Nglc_Nexpr* _Lexpr_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2) {
struct _Nglc_Nexpr_fvar* _Le_3;
_Le_3 = _Lexpr_0;
_Nglc_Nexpr_i_Pwr_3((*_Le_3)._Fexpr, _Lw_1, _Lheader_2);
_Nglc_Nid_Pwr_3((*_Le_3)._Fmember, _Lw_1, _Lheader_2);
}
inline void _Nglc_Nexpr_i_Pwr_gvar_3(struct _Nglc_Nexpr* _Lexpr_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2) {
struct _Nglc_Nexpr_gvar* _Le_3;
_Le_3 = _Lexpr_0;
_Nglc_Nat_Pwr_3((*_Le_3)._Fat, _Lw_1, _Lheader_2);
_Nglc_Nid_Pwr_3((*_Le_3)._Fname, _Lw_1, _Lheader_2);
}
inline void _Nglc_Nexpr_i_Pwr_lvar_3(struct _Nglc_Nexpr* _Lexpr_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2) {
struct _Nglc_Nexpr_lvar* _Le_3;
_Le_3 = _Lexpr_0;
_Nglc_Nlvar_Pwr_2((*_Le_3)._Flvar, _Lw_1);
}
inline void _Nglc_Nlvar_flags_Pwr_2(_Nglc_Nlvar_flags _Lf_0, union _Nglc_Nwtr* _Lw_1) {
_Nglc_Nwtr_Pn1_2(_Lw_1, _Lf_0);
}
inline void _Nglc_Nlvar_Pwr_2(_Nglc_Nlvar _Ll_0, union _Nglc_Nwtr* _Lw_1) {
Fputnum(_Lw_1, _Ll_0 + 1);
}
inline void _Nglc_Nstmt_type_Pwr_2(_Nglc_Nstmt_type _Ls_0, union _Nglc_Nwtr* _Lw_1) {
_Nglc_Nwtr_Pn1_2(_Lw_1, _Ls_0);
}
inline void _Nglc_Nstmt_space_Pwr_break_3(struct _Nglc_Nstmt* _Lstmt_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2) {
struct _Nglc_Nstmt_break* _Ls_3;
_Ls_3 = _Lstmt_0;
_Nglc_Nwtr_Pn1_2(_Lw_1, (*_Ls_3)._Fnest);
}
inline void _Nglc_Nstmt_space_Pwr_switch_3(struct _Nglc_Nstmt* _Lstmt_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2) {
struct _Nglc_Nstmt_switch* _Ls_3;
_Ls_3 = _Lstmt_0;
_Nglc_Nexpr_i_Pwr_3((*_Ls_3)._Fexpr, _Lw_1, _Lheader_2);
_Nglc_Nexpr_i_Pwr_3((*_Ls_3)._Fcases, _Lw_1, _Lheader_2);
}
inline void _Nglc_Nstmt_space_Pwr_case_3(struct _Nglc_Nstmt* _Lstmt_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2) {
struct _Nglc_Nstmt_case* _Ls_3;
_Ls_3 = _Lstmt_0;
Fputnum(_Lw_1, (*_Ls_3)._Fexpr_c);
int32_t _Li_4;
_Li_4 = 0;
for(int i = (*_Ls_3)._Fexpr_c; i > 0; ) {
i --;
_Nglc_Nexpr_i_Pwr_3((*_Ls_3)._Fexpr_v[_Li_4]._Fexpr, _Lw_1, _Lheader_2);
continue_0:;
_Li_4++;
}
break_0:;
_Nglc_Nwtr_Pb_2(_Lw_1, (*_Ls_3)._Ffall_through);
}
inline void _Nglc_Nstmt_space_Pwr_case_end_3(struct _Nglc_Nstmt* _Lstmt_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2) {
}
inline void _Nglc_Nstmt_space_Pwr_default_3(struct _Nglc_Nstmt* _Lstmt_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2) {
struct _Nglc_Nstmt_default* _Ls_3;
_Ls_3 = _Lstmt_0;
_Nglc_Nwtr_Pb_2(_Lw_1, (*_Ls_3)._Ffall_through);
}
inline void _Nglc_Nstmt_space_Pwr_default_end_3(struct _Nglc_Nstmt* _Lstmt_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2) {
}
inline void _Nglc_Nstmt_space_Pwr_switch_end_3(struct _Nglc_Nstmt* _Lstmt_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2) {
}
inline void _Nglc_Nstmt_space_Pwr_if_3(struct _Nglc_Nstmt* _Lstmt_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2) {
struct _Nglc_Nstmt_if* _Ls_3;
_Ls_3 = _Lstmt_0;
_Nglc_Nwtr_Pb_2(_Lw_1, (*_Ls_3)._Fnot);
_Nglc_Nexpr_i_Pwr_3((*_Ls_3)._Fexpr, _Lw_1, _Lheader_2);
}
inline void _Nglc_Nstmt_space_Pwr_if_elif_3(struct _Nglc_Nstmt* _Lstmt_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2) {
struct _Nglc_Nstmt_if_elif* _Ls_3;
_Ls_3 = _Lstmt_0;
_Nglc_Nwtr_Pb_2(_Lw_1, (*_Ls_3)._Fnot);
_Nglc_Nexpr_i_Pwr_3((*_Ls_3)._Fexpr, _Lw_1, _Lheader_2);
}
inline void _Nglc_Nstmt_space_Pwr_if_else_3(struct _Nglc_Nstmt* _Lstmt_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2) {
}
inline void _Nglc_Nstmt_space_Pwr_if_end_3(struct _Nglc_Nstmt* _Lstmt_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2) {
}
inline void _Nglc_Nstmt_space_Pwr_do_3(struct _Nglc_Nstmt* _Lstmt_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2) {
struct _Nglc_Nstmt_do* _Ls_3;
_Ls_3 = _Lstmt_0;
_Nglc_Nexpr_i_Pwr_3((*_Ls_3)._Fexpr, _Lw_1, _Lheader_2);
if((*_Ls_3)._Fcontinu != NULL) {
_Nglc_Nwtr_Pb_2(_Lw_1, true);
_Nglc_Nstmt_space_Pwr_3((*_Ls_3)._Fcontinu, _Lw_1, _Lheader_2);
} else {
_Nglc_Nwtr_Pb_2(_Lw_1, false);
}
}
inline void _Nglc_Nstmt_space_Pwr_do_end_3(struct _Nglc_Nstmt* _Lstmt_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2) {
}
inline void _Nglc_Nstmt_space_Pwr_while_3(struct _Nglc_Nstmt* _Lstmt_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2) {
struct _Nglc_Nstmt_while* _Ls_3;
_Ls_3 = _Lstmt_0;
_Nglc_Nexpr_i_Pwr_3((*_Ls_3)._Fexpr, _Lw_1, _Lheader_2);
if((*_Ls_3)._Fcontinu != NULL) {
_Nglc_Nwtr_Pb_2(_Lw_1, true);
_Nglc_Nstmt_space_Pwr_3((*_Ls_3)._Fcontinu, _Lw_1, _Lheader_2);
} else {
_Nglc_Nwtr_Pb_2(_Lw_1, false);
}
}
inline void _Nglc_Nstmt_space_Pwr_while_end_3(struct _Nglc_Nstmt* _Lstmt_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2) {
}
inline void _Nglc_Nstmt_space_Pwr_continue_3(struct _Nglc_Nstmt* _Lstmt_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2) {
struct _Nglc_Nstmt_continue* _Ls_3;
_Ls_3 = _Lstmt_0;
_Nglc_Nwtr_Pn1_2(_Lw_1, (*_Ls_3)._Fnest);
}
inline void _Nglc_Nstmt_space_Pwr_return_3(struct _Nglc_Nstmt* _Lstmt_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2) {
struct _Nglc_Nstmt_return* _Ls_3;
_Ls_3 = _Lstmt_0;
_Nglc_Nexpr_i_Pwr_3((*_Ls_3)._Fexpr, _Lw_1, _Lheader_2);
}
inline void _Nglc_Nstmt_space_Pwr_space_3(struct _Nglc_Nstmt* _Lstmt_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2) {
struct _Nglc_Nstmt_space* _Ls_3;
_Ls_3 = _Lstmt_0;
_Nglc_Nstmt_space_Pwr_3(_Ls_3, _Lw_1, _Lheader_2);
}
inline void _Nglc_Nstmt_space_Pwr_expr_3(struct _Nglc_Nstmt* _Lstmt_0, union _Nglc_Nwtr* _Lw_1, bool _Lheader_2) {
struct _Nglc_Nstmt_expr* _Ls_3;
_Ls_3 = _Lstmt_0;
_Nglc_Nexpr_i_Pwr_3((*_Ls_3)._Fexpr, _Lw_1, _Lheader_2);
}
void _Nglc_Ntype_info_Pcopy_from_2(struct _Nglc_Ntype_info* _Lti_0, struct _Nglc_Ntype_info* _Lti2_1) {
memcpy((*_Lti_0)._Fref_v, (*_Lti2_1)._Fref_v, _Nglc_Ctype_info_star_limit);
(*_Lti_0)._Farray_c = (*_Lti2_1)._Farray_c;
(*_Lti_0)._Fstar_c = (*_Lti2_1)._Fstar_c;
(*_Lti_0)._Fconst = (*_Lti2_1)._Fconst;
}
void _Nglc_Pfunc_stmt_add_1(struct _Nglc_Nstmt* _Ls_0) {
(*_Ls_0)._Fstmt_next = NULL;
if((*_Gdecl_func_ctx_space)._Fstmt_last == NULL) {
(*_Gdecl_func_ctx_space)._Fstmt_first = _Ls_0;
(*_Gdecl_func_ctx_space)._Fstmt_last = _Ls_0;
} else {
(*(*_Gdecl_func_ctx_space)._Fstmt_last)._Fstmt_next = _Ls_0;
(*_Gdecl_func_ctx_space)._Fstmt_last = _Ls_0;
}
}
inline void _Nglc_Nwtr_Pb_2(union _Nglc_Nwtr* _Lw_0, bool _Lval_1) {
if(_Lval_1) {
_Nglc_Nwtr_Pn1_2(_Lw_0, 1);
} else {
_Nglc_Nwtr_Pn1_2(_Lw_0, 0);
}
}
inline void _Nglc_Nmath_Pwr_2(_Nglc_Nmath _Le_0, union _Nglc_Nwtr* _Lw_1) {
_Nglc_Nwtr_Pn1_2(_Lw_1, _Le_0);
}
inline void _Nglc_Nbools_Pwr_2(_Nglc_Nbools _Le_0, union _Nglc_Nwtr* _Lw_1) {
_Nglc_Nwtr_Pn1_2(_Lw_1, _Le_0);
}
inline void _Nglc_Nunary_Pwr_2(_Nglc_Nunary _Lu_0, union _Nglc_Nwtr* _Lw_1) {
_Nglc_Nwtr_Pn1_2(_Lw_1, _Lu_0);
}
inline void _Nglc_Ncompare_Pwr_2(_Nglc_Ncompare _Le_0, union _Nglc_Nwtr* _Lw_1) {
_Nglc_Nwtr_Pn1_2(_Lw_1, _Le_0);
}
inline void _Nglc_Nassign_Pwr_2(_Nglc_Nassign _Ls_0, union _Nglc_Nwtr* _Lw_1) {
_Nglc_Nwtr_Pn1_2(_Lw_1, _Ls_0);
}
