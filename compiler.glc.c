#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "num.c"
#include <string.h>
#define _Mglc_Chash_table_size (64)
#define _Mglc_Efunc_Cnil (-1)
#define _Mglc_Ebasic_type_id_Croot 0
#define _Mglc_Ebasic_type_id_Cref (_Mglc_Ebasic_type_id_Croot + 1)
#define _Mglc_Ebasic_type_id_Cbool (_Mglc_Ebasic_type_id_Cref + 1)
#define _Mglc_Ebasic_type_id_Cchar (_Mglc_Ebasic_type_id_Cbool + 1)
#define _Mglc_Ebasic_type_id_Ctint (_Mglc_Ebasic_type_id_Cchar + 1)
#define _Mglc_Ebasic_type_id_Ctnum (_Mglc_Ebasic_type_id_Ctint + 1)
#define _Mglc_Ebasic_type_id_Cint (_Mglc_Ebasic_type_id_Ctnum + 1)
#define _Mglc_Ebasic_type_id_Cnum (_Mglc_Ebasic_type_id_Cint + 1)
#define _Mglc_Ebasic_type_id_Cfloat (_Mglc_Ebasic_type_id_Cnum + 1)
#define _Mglc_Ebasic_type_id_Csize (_Mglc_Ebasic_type_id_Cfloat + 1)
#define _Mglc_Ebasic_type_id_Clnum (_Mglc_Ebasic_type_id_Csize + 1)
#define _Mglc_Ebasic_type_id_CCOUNT (_Mglc_Ebasic_type_id_Clnum + 1)
#define _Mglc_Ename_type_Cmodule 0
#define _Mglc_Ename_type_Cstruct (_Mglc_Ename_type_Cmodule + 1)
#define _Mglc_Ename_type_Cenum (_Mglc_Ename_type_Cstruct + 1)
#define _Mglc_Ename_type_Cbasic (_Mglc_Ename_type_Cenum + 1)
#define _Mglc_Eat_Cnil (-1)
#define _Mglc_Eat_Croot (_Mglc_Eat_Cnil + 1)
#define _Mglc_Ctype_info_star_limit (8)
#define _Mglc_Cexpr_carg_group_limit (4)
#define _Mglc_Eenum_Cnil (-1)
#define _Mstdc_Eexit_Csuccess 0
#define _Mstdc_Eexit_Cfailure (_Mstdc_Eexit_Csuccess + 1)
#define _Mglc_Efunc_flags_Creal_name (64)
#define _Mglc_Einclude_Cnil (-1)
#define _Mglc_Efunc_flags_Cglc_name (256)
#define _Mglc_Efunc_flags_C0 0
#define _Mglc_Ecvar_flags_Cas_enum (2)
#define _Mglc_Ecvar_flags_C0 0
#define _Mglc_Evar_flags_Cno_decl (4)
#define _Mglc_Evar_flags_C0 0
#define _Mglc_Ecvar_flags_Cset_expr (1)
#define _Mglc_Ecvar_Cnil (-1)
#define _Mglc_Estruct_flags_Cunion (4)
#define _Mglc_Estruct_flags_C0 0
#define _Mglc_Edecl_var_type_Cgvar 0
#define _Mglc_Edecl_var_type_Cfvar (_Mglc_Edecl_var_type_Cgvar + 1)
#define _Mglc_Evar_flags_Cextern (2)
#define _Mglc_Efunc_flags_Cno_decl (16)
#define _Mglc_Efunc_flags_Cdecl (512)
#define _Mglc_Estruct_Cnil (-1)
#define _Mglc_Eenum_flags_Creal_name (1)
#define _Mglc_Eenum_flags_C0 0
#define _Mglc_Eid_Cnil (-1)
#define _Mglc_Estruct_flags_Creal_name (1)
#define _Mglc_Elvar_Cnil (-1)
#define _Mglc_Elvar_C0 (_Mglc_Elvar_Cnil + 1)
#define _Mglc_Efunc_flags_Ccase (128)
#define _Mglc_Efunc_flags_Chas_body (1)
#define _Mglc_Efunc_flags_Cno_body (32)
#define _Mglc_Evar_flags_Creal_name (1)
#define _Mglc_Eexpr_type_Cnil 0
#define _Mglc_Eexpr_type_Ccall_method (_Mglc_Eexpr_type_Cnil + 1)
#define _Mglc_Eexpr_type_Clvar (_Mglc_Eexpr_type_Ccall_method + 1)
#define _Mglc_Eexpr_type_Cgvar (_Mglc_Eexpr_type_Clvar + 1)
#define _Mglc_Eexpr_type_Cmath (_Mglc_Eexpr_type_Cgvar + 1)
#define _Mglc_Eexpr_type_Cassign (_Mglc_Eexpr_type_Cmath + 1)
#define _Mglc_Eexpr_type_Cbools (_Mglc_Eexpr_type_Cassign + 1)
#define _Mglc_Eexpr_type_Cfunc (_Mglc_Eexpr_type_Cbools + 1)
#define _Mglc_Eexpr_type_Cmethod (_Mglc_Eexpr_type_Cfunc + 1)
#define _Mglc_Eexpr_type_Cfvar (_Mglc_Eexpr_type_Cmethod + 1)
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
#define _Mglc_Elvar_flags_Cset_expr (1)
#define _Mglc_Elvar_flags_C0 0
#define _Mglc_Cdebug_rd_wr (true)
#define _Mglc_Eexpr_Cnil (-1)
#define _Mglc_Efunc_C0 (_Mglc_Efunc_Cnil + 1)
#define _Mglc_Efunc_C1 (_Mglc_Efunc_C0 + 1)
#define _Mglc_Estmt_type_Cnil (255)
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
#define _Mglc_Estmt_type_Cswitch (_Mglc_Estmt_type_Cbreak + 1)
#define _Mglc_Estmt_type_Ccase (_Mglc_Estmt_type_Cswitch + 1)
#define _Mglc_Estmt_type_Cdefault (_Mglc_Estmt_type_Ccase + 1)
#define _Mglc_Estmt_type_Ccase_end (_Mglc_Estmt_type_Cdefault + 1)
#define _Mglc_Estmt_type_Cdefault_end (_Mglc_Estmt_type_Ccase_end + 1)
#define _Mglc_Estmt_type_Cswitch_end (_Mglc_Estmt_type_Cdefault_end + 1)
#define _Mglc_Estruct_flags_Cno_decl (2)
#define _Mglc_Eexpr_C0 (_Mglc_Eexpr_Cnil + 1)
#define _Mglc_Eassign_Ceq 0
#define _Mglc_Eassign_Cplus_eq (_Mglc_Eassign_Ceq + 1)
#define _Mglc_Eassign_Cminus_eq (_Mglc_Eassign_Cplus_eq + 1)
#define _Mglc_Eassign_Cmul_eq (_Mglc_Eassign_Cminus_eq + 1)
#define _Mglc_Eassign_Cdiv_eq (_Mglc_Eassign_Cmul_eq + 1)
#define _Mglc_Eassign_Clshift_eq (_Mglc_Eassign_Cdiv_eq + 1)
#define _Mglc_Eassign_Crshift_eq (_Mglc_Eassign_Clshift_eq + 1)
#define _Mglc_Eassign_Cand_eq (_Mglc_Eassign_Crshift_eq + 1)
#define _Mglc_Eassign_Cor_eq (_Mglc_Eassign_Cand_eq + 1)
#define _Mglc_Eassign_Cxor_eq (_Mglc_Eassign_Cor_eq + 1)
#define _Mglc_Ecompare_Ceq 0
#define _Mglc_Ecompare_Cnot_eq (_Mglc_Ecompare_Ceq + 1)
#define _Mglc_Ecompare_Clt (_Mglc_Ecompare_Cnot_eq + 1)
#define _Mglc_Ecompare_Cle (_Mglc_Ecompare_Clt + 1)
#define _Mglc_Ecompare_Cgt (_Mglc_Ecompare_Cle + 1)
#define _Mglc_Ecompare_Cge (_Mglc_Ecompare_Cgt + 1)
#define _Mglc_Emath_Cadd 0
#define _Mglc_Emath_Csub (_Mglc_Emath_Cadd + 1)
#define _Mglc_Emath_Cmul (_Mglc_Emath_Csub + 1)
#define _Mglc_Emath_Cdiv (_Mglc_Emath_Cmul + 1)
#define _Mglc_Emath_Clshift (_Mglc_Emath_Cdiv + 1)
#define _Mglc_Emath_Crshift (_Mglc_Emath_Clshift + 1)
#define _Mglc_Emath_Cand (_Mglc_Emath_Crshift + 1)
#define _Mglc_Emath_Cor (_Mglc_Emath_Cand + 1)
#define _Mglc_Emath_Cxor (_Mglc_Emath_Cor + 1)
#define _Mglc_Eunary_Cneg 0
#define _Mglc_Eunary_Cinc (_Mglc_Eunary_Cneg + 1)
#define _Mglc_Eunary_Cdec (_Mglc_Eunary_Cinc + 1)
#define _Mglc_Ebools_Cand 0
#define _Mglc_Ebools_Cor (_Mglc_Ebools_Cand + 1)
#define _Mglc_Egvar_Cnil (-1)
#define _Mglc_Efunc_flags_Cvar_args (8)
#define _Mglc_Elvar_flags_Cprocessed (2)
#define _Mglc_Egvar_flags_Cno_decl (1)
#define _Mglc_Egvar_flags_C0 0
typedef int32_t _Mglc_Efunc;
typedef uint8_t _Mglc_Ebasic_type_id;
typedef int32_t _Mglc_Eat;
typedef uint8_t _Mglc_Ename_type;
typedef int32_t _Mglc_Eid;
typedef int32_t _Mglc_Egvar;
typedef int32_t _Mglc_Ecvar;
typedef int32_t _Mglc_Estruct;
typedef int32_t _Mglc_Eenum;
typedef int32_t _Mglc_Efile;
typedef int32_t _Mglc_Einclude;
typedef uint32_t _Mglc_Efunc_flags;
typedef uint32_t _Mglc_Evar_flags;
typedef int32_t _Mglc_Eexpr;
typedef uint8_t _Mglc_Estmt_type;
typedef uint8_t _Mglc_Estmt_space_flags;
typedef int32_t _Mglc_Elvar;
typedef uint8_t _Mglc_Elvar_flags;
typedef int32_t _Mstdc_Eexit;
typedef uint8_t _Mglc_Estruct_flags;
typedef uint8_t _Mglc_Eenum_flags;
typedef uint8_t _Mglc_Ecvar_flags;
typedef uint8_t _Mglc_Edecl_var_type;
typedef uint8_t _Mglc_Egvar_flags;
typedef int32_t _Mstdc_Efile;
typedef int32_t _Mstdc_Eopen_flags;
typedef int32_t _Mstdc_Eseek;
typedef uint8_t _Mglc_Eexpr_type;
typedef uint8_t _Mglc_Eexpr_flags;
typedef uint8_t _Mglc_Eassign;
typedef uint8_t _Mglc_Ecompare;
typedef uint8_t _Mglc_Emath;
typedef uint8_t _Mglc_Eunary;
typedef int32_t _Mglc_Efvar;
typedef uint8_t _Mglc_Ebools;
typedef uint8_t _Mglc_Eexpr_int;
struct _Mglc_Smap;
struct _Mglc_Smap {
uint64_t _Fdata[(_Mglc_Chash_table_size + 7) >> 3];
};
union _Mglc_Sat_name;
union _Mglc_Sat_name {
_Mglc_Eid _Fid;
_Mglc_Ebasic_type_id _Fbasic;
};
union _Mglc_Sat_type;
union _Mglc_Sat_type {
_Mglc_Estruct _Fstruct;
_Mglc_Eenum _Fenum;
};
struct _Mglc_Sat;
struct _Mglc_Sat {
_Mglc_Ename_type _Ftype;
_Mglc_Eat _Fparent;
union _Mglc_Sat_name _Fname;
int32_t _Ffunc_c;
int32_t _Ffunc_cap;
_Mglc_Efunc* _Ffunc_v;
int32_t _Fgvar_c;
int32_t _Fgvar_cap;
_Mglc_Egvar* _Fgvar_v;
int32_t _Fcvar_c;
int32_t _Fcvar_cap;
_Mglc_Ecvar* _Fcvar_v;
union _Mglc_Sat_type _Fdecl;
};
struct _Mglc_Stype_info;
struct _Mglc_Stype_info {
int8_t _Fref_v[_Mglc_Ctype_info_star_limit];
int8_t _Farray_c;
int8_t _Fstar_c;
bool _Fbuilt_in;
bool _Fconst;
};
struct _Mglc_Svalue;
struct _Mglc_Svalue {
int8_t _Fref;
bool _Fparen;
_Mglc_Eat _Ftype;
struct _Mglc_Stype_info _Finfo;
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
struct _Mglc_Svalue* _Fsize_value_v;
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
_Mglc_Efunc _Fprocess_next;
_Mglc_Efile _Ffile;
int32_t _Fbegin_row;
int32_t _Fbegin_col;
int32_t _Fend_row;
int32_t _Fend_col;
_Mglc_Einclude _Finclude;
_Mglc_Eat _Fat;
_Mglc_Efunc_flags _Fflags;
_Mglc_Eid _Freal_name;
char* _Fdecl_str;
int32_t _Fdecl_len;
_Mglc_Eid _Fcase;
struct _Mglc_Sdecl_var _Fdecl;
struct _Mglc_Sstmt_space _Fstmt_space;
_Mglc_Elvar _Flvar_c;
struct _Mglc_Slvar* _Flvar_v;
uint32_t _Fbody_file_pos;
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
_Mglc_Efile _Ffile;
int32_t _Fbegin_row;
int32_t _Fbegin_col;
int32_t _Fend_row;
int32_t _Fend_col;
_Mglc_Einclude _Finclude;
_Mglc_Eat _Fat;
_Mglc_Estruct_flags _Fflags;
_Mglc_Eid _Freal_name;
int32_t _Fmethod_c;
int32_t _Fmethod_cap;
_Mglc_Efunc* _Fmethod_v;
uint32_t _Ffvar_c;
struct _Mglc_Sfvar _Ffvar_v[0];
};
struct _Mglc_Senum;
struct _Mglc_Senum {
_Mglc_Efile _Ffile;
int32_t _Fbegin_row;
int32_t _Fbegin_col;
int32_t _Fend_row;
int32_t _Fend_col;
_Mglc_Einclude _Finclude;
_Mglc_Eat _Fat;
_Mglc_Eat _Fbase_type;
_Mglc_Eenum_flags _Fflags;
_Mglc_Eid _Freal_name;
int32_t _Fmethod_c;
int32_t _Fmethod_cap;
_Mglc_Efunc* _Fmethod_v;
};
struct _Mglc_Sbasic_type;
struct _Mglc_Sbasic_type {
int32_t _Fmethod_c;
int32_t _Fmethod_cap;
_Mglc_Efunc* _Fmethod_v;
};
struct _Mglc_Scvar;
struct _Mglc_Scvar {
_Mglc_Efile _Ffile;
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
_Mglc_Efile _Ffile;
int32_t _Frow;
int32_t _Fcol;
_Mglc_Einclude _Finclude;
_Mglc_Eat _Fat;
_Mglc_Egvar_flags _Fflags;
struct _Mglc_Sdecl_var _Fdecl;
};
union _Mglc_Srdr;
union _Mglc_Srdr {
void* _Fref;
size_t _Fpos;
uint8_t* _F1;
char* _Fchar;
uint32_t* _F4;
};
struct _Mglc_Sfile;
struct _Mglc_Sfile {
char* _Fpath;
void* _Fdata;
_Mglc_Eid* _Fid_table;
_Mglc_Eat* _Fat_table;
_Mglc_Ecvar* _Fcvar_table;
};
struct _Mglc_Sexpr;
struct _Mglc_Sexpr {
_Mglc_Eexpr_type _Ftype;
_Mglc_Eexpr_flags _Fflags;
};
struct _Mglc_Sexpr_assign;
struct _Mglc_Sexpr_assign {
struct _Mglc_Sexpr _Fbase;
_Mglc_Eexpr _Fleft;
_Mglc_Eexpr _Fright;
_Mglc_Eassign _Ftype;
struct _Mglc_Svalue _Fleft_val;
struct _Mglc_Svalue _Fright_val;
};
struct _Mglc_Sexpr_compare;
struct _Mglc_Sexpr_compare {
struct _Mglc_Sexpr _Fbase;
_Mglc_Eexpr _Fleft;
_Mglc_Eexpr _Fright;
_Mglc_Ecompare _Ftype;
struct _Mglc_Svalue _Fleft_val;
struct _Mglc_Svalue _Fright_val;
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
struct _Mglc_Sexpr_math_item;
struct _Mglc_Sexpr_math_item {
_Mglc_Eexpr _Fexpr;
struct _Mglc_Svalue _Fval;
};
struct _Mglc_Sexpr_math;
struct _Mglc_Sexpr_math {
struct _Mglc_Sexpr _Fbase;
_Mglc_Eexpr _Fleft;
_Mglc_Eexpr _Fright;
_Mglc_Emath _Ftype;
struct _Mglc_Svalue _Fleft_val;
struct _Mglc_Svalue _Fright_val;
uint8_t _Fitem_c;
struct _Mglc_Sexpr_math_item* _Fitem_v;
};
struct _Mglc_Sexpr_unary;
struct _Mglc_Sexpr_unary {
struct _Mglc_Sexpr _Fbase;
_Mglc_Eexpr _Fexpr;
_Mglc_Eunary _Ftype;
struct _Mglc_Svalue _Fval;
};
struct _Mglc_Sexpr_ref;
struct _Mglc_Sexpr_ref {
struct _Mglc_Sexpr _Fbase;
_Mglc_Eexpr _Fexpr;
struct _Mglc_Svalue _Fval;
};
struct _Mglc_Sexpr_lvar;
struct _Mglc_Sexpr_lvar {
struct _Mglc_Sexpr _Fbase;
_Mglc_Elvar _Flvar;
};
struct _Mglc_Sexpr_fvar;
struct _Mglc_Sexpr_fvar {
struct _Mglc_Sexpr _Fbase;
_Mglc_Eexpr _Fexpr;
_Mglc_Eid _Fmember;
_Mglc_Efvar _Ffvar;
struct _Mglc_Svalue _Fval;
};
struct _Mglc_Sexpr_gvar;
struct _Mglc_Sexpr_gvar {
struct _Mglc_Sexpr _Fbase;
_Mglc_Egvar _Fgvar;
};
struct _Mglc_Sexpr_cvar;
struct _Mglc_Sexpr_cvar {
struct _Mglc_Sexpr _Fbase;
_Mglc_Eat _Fat;
_Mglc_Eid _Fname;
_Mglc_Ecvar _Fcvar;
_Mglc_Eat _Ftry;
};
struct _Mglc_Sexpr_bools_item;
struct _Mglc_Sexpr_bools_item {
_Mglc_Eexpr _Fexpr;
struct _Mglc_Svalue _Fval;
};
struct _Mglc_Sexpr_bools;
struct _Mglc_Sexpr_bools {
struct _Mglc_Sexpr _Fbase;
_Mglc_Eexpr _Fleft;
_Mglc_Eexpr _Fright;
_Mglc_Ebools _Ftype;
struct _Mglc_Svalue _Fleft_val;
struct _Mglc_Svalue _Fright_val;
uint8_t _Fitem_c;
struct _Mglc_Sexpr_bools_item* _Fitem_v;
};
struct _Mglc_Scarg;
struct _Mglc_Scarg {
int8_t _Fref;
_Mglc_Eexpr _Fexpr;
struct _Mglc_Svalue _Fvalue;
};
struct _Mglc_Sexpr_method;
struct _Mglc_Sexpr_method {
struct _Mglc_Sexpr _Fbase;
_Mglc_Eexpr _Fthis;
_Mglc_Eid _Ffunc_name;
_Mglc_Efunc _Ffunc_idx;
struct _Mglc_Svalue _Fthis_value;
uint8_t _Fgroup_c;
uint8_t _Fgroup_v[_Mglc_Cexpr_carg_group_limit];
uint8_t _Fcarg_c;
struct _Mglc_Scarg _Fcarg_v[0];
};
struct _Mglc_Sexpr_func;
struct _Mglc_Sexpr_func {
struct _Mglc_Sexpr _Fbase;
_Mglc_Eat _Fat;
_Mglc_Eid _Ffunc_name;
_Mglc_Efunc _Ffunc_idx;
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
struct _Mglc_Sexpr_index;
struct _Mglc_Sexpr_index {
struct _Mglc_Sexpr _Fbase;
_Mglc_Eexpr _Fleft;
_Mglc_Eexpr _Fright;
struct _Mglc_Svalue _Fleft_val;
struct _Mglc_Svalue _Fright_val;
};
struct _Mglc_Sexpr_cast_fast;
struct _Mglc_Sexpr_cast_fast {
struct _Mglc_Sexpr _Fbase;
_Mglc_Eexpr _Fexpr;
_Mglc_Eat _Ftype;
struct _Mglc_Svalue _Fval;
};
struct _Mglc_Sstmt_expr;
struct _Mglc_Sstmt_expr {
struct _Mglc_Sstmt _Fbase;
_Mglc_Eexpr _Fexpr;
};
struct _Mglc_Sstmt_if;
struct _Mglc_Sstmt_if {
struct _Mglc_Sstmt _Fbase;
bool _Fnot;
_Mglc_Eexpr _Fexpr;
struct _Mglc_Svalue _Fval;
};
struct _Mglc_Sstmt_if_elif;
struct _Mglc_Sstmt_if_elif {
struct _Mglc_Sstmt _Fbase;
bool _Fnot;
_Mglc_Eexpr _Fexpr;
struct _Mglc_Svalue _Fval;
};
struct _Mglc_Sstmt_if_else;
struct _Mglc_Sstmt_if_else {
struct _Mglc_Sstmt _Fbase;
};
struct _Mglc_Sstmt_if_end;
struct _Mglc_Sstmt_if_end {
struct _Mglc_Sstmt _Fbase;
};
struct _Mglc_Sstmt_switch_case_func;
struct _Mglc_Sstmt_switch_case_func {
_Mglc_Ecvar _Fcvar;
_Mglc_Efunc _Ffunc;
};
struct _Mglc_Sstmt_switch;
struct _Mglc_Sstmt_switch {
struct _Mglc_Sstmt _Fbase;
_Mglc_Eexpr _Fexpr;
struct _Mglc_Svalue _Fval;
_Mglc_Eexpr _Fcases;
uint32_t _Fcase_func_c;
struct _Mglc_Sstmt_switch_case_func* _Fcase_func_v;
};
struct _Mglc_Sstmt_case_item;
struct _Mglc_Sstmt_case_item {
_Mglc_Eexpr _Fexpr;
struct _Mglc_Svalue _Fval;
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
struct _Mglc_Sstmt_return;
struct _Mglc_Sstmt_return {
struct _Mglc_Sstmt _Fbase;
_Mglc_Eexpr _Fexpr;
struct _Mglc_Svalue _Fval;
};
union _Mglc_Scase_stack;
union _Mglc_Scase_stack {
struct _Mglc_Sstmt_case* _Fcase;
struct _Mglc_Sstmt_default* _Fdefault;
};
struct _Mglc_Smap _Gid_map;
struct _Mglc_Smap _Ginclude_map;
_Mglc_Efunc _Gfunc_main;
_Mglc_Eat _Gat_c;
_Mglc_Eat _Gat_cap;
struct _Mglc_Sat* _Gat_v;
_Mglc_Efunc _Gfunc_c;
struct _Mglc_Sbasic_type _Gbasic_type[_Mglc_Ebasic_type_id_CCOUNT];
char** _Gid_c_name_v;
int32_t _Gid_c;
uint8_t* _Gfunc_in_process;
_Mglc_Efunc* _Gfunc_head_outputted_v;
_Mglc_Efunc* _Gfunc_body_outputted_v;
int32_t _Ginclude_c;
uint8_t* _Ginclude_is_outputted;
_Mglc_Einclude* _Ginclude_outputted_v;
_Mglc_Ecvar _Gcvar_c;
uint8_t* _Gcvar_is_outputted;
_Mglc_Ecvar* _Gcvar_outputted_v;
_Mglc_Egvar _Ggvar_c;
uint8_t* _Ggvar_is_outputted;
_Mglc_Egvar* _Ggvar_outputted_v;
_Mglc_Eenum _Genum_c;
uint8_t* _Genum_is_outputted;
_Mglc_Eenum* _Genum_outputted_v;
_Mglc_Estruct _Gstruct_c;
uint8_t* _Gstruct_is_outputted;
_Mglc_Estruct* _Gstruct_outputted_v;
_Mglc_Efunc _Gprocess_first;
_Mglc_Efunc _Gprocess_last;
FILE* _Gout;
int32_t _Gfunc_head_outputted_c;
bool _Ginclude_stdbool;
bool _Ginclude_stddef;
int32_t _Ginclude_outputted_c;
int32_t _Gcvar_outputted_c;
int32_t _Genum_outputted_c;
int32_t _Gstruct_outputted_c;
int32_t _Ggvar_outputted_c;
struct _Mglc_Sdecl_func* _Gctx_func;
int32_t _Gfunc_body_outputted_c;
int32_t _Gnest_id;
int32_t _Gquick_alloc_c;
int32_t _Gquick_alloc_cap;
void* _Gquick_alloc_v;
_Mglc_Efile _Gfile_c;
_Mglc_Efile _Gfile_cap;
struct _Mglc_Sfile* _Gfile_v;
_Mglc_Eid* _Gid_table;
int32_t _Ginclude_table_cap;
_Mglc_Einclude* _Ginclude_table;
int32_t _Ginclude_cap;
uint8_t* _Ginclude_len_v;
char** _Ginclude_str_v;
_Mglc_Eat* _Gat_table;
_Mglc_Ecvar* _Gcvar_table;
_Mglc_Ecvar _Gcvar_cap;
struct _Mglc_Scvar* _Gcvar_v;
_Mglc_Egvar _Ggvar_cap;
struct _Mglc_Sdecl_gvar* _Ggvar_v;
_Mglc_Eenum _Genum_cap;
struct _Mglc_Senum** _Genum_v;
_Mglc_Estruct _Gstruct_cap;
struct _Mglc_Sstruct** _Gstruct_v;
_Mglc_Efunc _Gfunc_cap;
struct _Mglc_Sdecl_func** _Gfunc_v;
_Mglc_Efunc _Gctx_func_id;
char** _Gid_str_v;
int32_t _Gid_cap;
uint8_t* _Gid_len_v;
int32_t _Gctx_begin_row;
int32_t _Gctx_begin_col;
int32_t _Gctx_end_row;
int32_t _Gctx_end_col;
int32_t _Gexpr_c;
int32_t _Gexpr_cap;
struct _Mglc_Sexpr** _Gexpr_v;
uint8_t* _Gexpr_is_processed;
int32_t _Gnest_stack_id_v[64];
uint8_t _Gnest_stack_c;
union _Mglc_Snest _Gnest_stack_ptr_v[64];
struct _Mglc_Sstmt_switch* _Gswitch_stack_v[64];
uint8_t _Gswitch_stack_c;
union _Mglc_Scase_stack _Gcase_stack_v[64];
uint8_t _Gcase_stack_c;
int32_t main(int32_t _Larg_c_0, char** _Larg_v_1);
void qalloc_undo(int32_t _Lsize_0);
void _Mglc_Smap_Pinit_1(struct _Mglc_Smap* _Lm_0);
void _Mglc_Pquick_alloc_init_0();
#define _Mglc_Pgrow_2(cap, c) cap = Fpow2gteq((c) + 8)
#define _Mglc_Prealloc_3(r, c, oldc) r = realloc(r, sizeof(r[0]) * (c)); memset(r + (oldc), 0, sizeof(r[0]) * ((c) - (oldc)))
void _Mglc_Sat_Pinit_4(struct _Mglc_Sat* _Lat_0, _Mglc_Ename_type _Ltype_1, _Mglc_Eat _Lparent_2, _Mglc_Eid _Lname_3);
void _Mglc_Pread_1(char* _Lin_path_0);
struct _Mglc_Sdecl_func* _Mglc_Efunc_Pptr_1(_Mglc_Efunc _Lf_0);
struct _Mglc_Sat* _Mglc_Eat_Pptr_1(_Mglc_Eat _Li_0);
char* _Mglc_Efile_Ppath_1(_Mglc_Efile _Lf_0);
char* _Mglc_Eid_Pstr_1(_Mglc_Eid _Lid_0);
struct _Mglc_Sstruct* _Mglc_Estruct_Pptr_1(_Mglc_Estruct _Ls_0);
struct _Mglc_Senum* _Mglc_Eenum_Pptr_1(_Mglc_Eenum _Lf_0);
_Mglc_Eid _Mglc_Pid_add_2(uint8_t _Lid_len_0, char* _Lid_str_1);
#define _Mglc_Pquick_alloc_arr_2(r, c) r = qalloc(sizeof(r[0]) * (c))
void _Mglc_Efunc_Pprocess_later_1(_Mglc_Efunc _Lf_idx_0);
bool _Mglc_Efunc_Pprocess_now_1(_Mglc_Efunc _Lf_idx_0);
void _Mglc_Eat_Poutput_4(_Mglc_Eat _Lat_i_0, _Mglc_Efile _Lfile_1, int32_t _Lrow_2, int32_t _Lcol_3);
void _Mglc_Einclude_Poutput_1(_Mglc_Einclude _Lthis_0);
struct _Mglc_Scvar* _Mglc_Ecvar_Pptr_1(_Mglc_Ecvar _Lc_0);
bool _Mglc_Ecvar_Pprocess_1(_Mglc_Ecvar _Lc_0);
char* _Mglc_Einclude_Pstr_1(_Mglc_Einclude _Li_0);
void _Mglc_Ecvar_Pwrite_1(_Mglc_Ecvar _Lc_0);
void _Mglc_Eexpr_Pwrite_1(_Mglc_Eexpr _Le_0);
void _Mglc_Eat_Pwrite_1(_Mglc_Eat _Lat_idx_0);
void _Mglc_Eat_Pwrite_space_1(_Mglc_Eat _Lat_idx_0);
void _Mglc_Sdecl_var_Pwrite_type_2(struct _Mglc_Sdecl_var* _Lvd_0, _Mglc_Edecl_var_type _Lvar_type_1);
struct _Mglc_Sdecl_gvar* _Mglc_Egvar_Pptr_1(_Mglc_Egvar _Lg_0);
void _Mglc_Sdecl_func_Pwrite_1(struct _Mglc_Sdecl_func* _Lf_0);
bool _Mglc_Eat_Pwrite_type_info_3(_Mglc_Eat _Ltd_0, struct _Mglc_Stype_info* _Lti_1, int32_t _Ladd_2);
void _Mglc_Sdecl_var_Pwrite_lvar_type_2(struct _Mglc_Sdecl_var* _Lvd_0, _Mglc_Elvar _Llvar_1);
void _Mglc_Sstmt_space_Pwrite_1(struct _Mglc_Sstmt_space* _Lspace_0);
bool _Mstdc_Efile_Popen_3(_Mstdc_Efile* _Lfile_0, char* _Lpath_1, _Mstdc_Eopen_flags _Lflags_2);
uint8_t _Mglc_Srdr_Pn1_1(union _Mglc_Srdr* _Lr_0);
int32_t _Mglc_Smap_Pget_or_insert_4(struct _Mglc_Smap* _Lm_0, char* _Lstr_1, uint8_t _Llen_2, int32_t _Lval_3);
void _Mglc_Ename_type_Prd_2(_Mglc_Ename_type* _Li_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Ebasic_type_id_Prd_2(_Mglc_Ebasic_type_id* _Le_0, union _Mglc_Srdr* _Lr_1);
_Mglc_Eat _Mglc_Pbasic_type_1(_Mglc_Ebasic_type_id _Lt_0);
void _Mglc_Eat_Prd_2(_Mglc_Eat* _Li_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Eid_Prd_2(_Mglc_Eid* _Lid_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Einclude_Prd_2(_Mglc_Einclude* _Li_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Sdecl_var_Prd_2(struct _Mglc_Sdecl_var* _Lvd_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Ecvar_flags_Prd_2(_Mglc_Ecvar_flags* _Lf_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Eexpr_Prd_2(_Mglc_Eexpr* _Le_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Ecvar_Prd_2(_Mglc_Ecvar* _Lc_0, union _Mglc_Srdr* _Lr_1);
#define _Mglc_Pquick_alloc_one_1(r) r = qalloc(sizeof(r[0]))
void _Mglc_Eenum_flags_Prd_2(_Mglc_Eenum_flags* _Le_0, union _Mglc_Srdr* _Lr_1);
#define _Mglc_Pquick_alloc_plus_2(r, plus) r = qalloc(sizeof(r[0]) + plus)
void _Mglc_Estruct_flags_Prd_2(_Mglc_Estruct_flags* _Lf_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Sfarg_Prd_2(struct _Mglc_Sfarg* _Lf_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Efunc_flags_Prd_2(_Mglc_Efunc_flags* _Le_0, union _Mglc_Srdr* _Lr_1);
void* qalloc(int32_t _Lsize_0);
void _Mglc_Efunc_Prd_2(_Mglc_Efunc* _Lf_0, union _Mglc_Srdr* _Lr_1);
uint32_t _Mglc_Srdr_Pn4_1(union _Mglc_Srdr* _Lr_0);
struct _Mglc_Sfile* _Mglc_Efile_Pptr_1(_Mglc_Efile _Lf_0);
bool _Mglc_Eat_Pfinalize_4(_Mglc_Eat _Lat_i_0, struct _Mglc_Stype_info* _Lti_1, int32_t _Lrow_2, int32_t _Lcol_3);
void _Mglc_Sdecl_func_Plvars_rd_2(struct _Mglc_Sdecl_func* _Lf_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Sstmt_space_Prd_3(struct _Mglc_Sstmt_space* _Lspace_0, union _Mglc_Srdr* _Lr_1, struct _Mglc_Sstmt_space* _Lparent_2);
bool _Mglc_Sstmt_Pprocess_1(struct _Mglc_Sstmt* _Ls_0);
void _Mglc_Estruct_Poutput_1(_Mglc_Estruct _Ls_i_0);
void _Mglc_Eenum_Poutput_1(_Mglc_Eenum _Le_i_0);
bool _Mglc_Eexpr_Pprocess_1(_Mglc_Eexpr _Le_0);
char* _Mglc_Eid_Pc_name_1(_Mglc_Eid _Lid_0);
struct _Mglc_Sexpr* _Mglc_Eexpr_Pptr_1(_Mglc_Eexpr _Le_0);
void _Mglc_Eexpr_Pwrite_assign_1(struct _Mglc_Sexpr* _Lexpr_0);
void _Mglc_Eexpr_Pwrite_compare_1(struct _Mglc_Sexpr* _Lexpr_0);
void _Mglc_Eexpr_Pwrite_bool_1(struct _Mglc_Sexpr* _Lexpr_0);
void _Mglc_Eexpr_Pwrite_char_1(struct _Mglc_Sexpr* _Lexpr_0);
void _Mglc_Eexpr_Pwrite_math_1(struct _Mglc_Sexpr* _Lexpr_0);
void _Mglc_Eexpr_Pwrite_unary_1(struct _Mglc_Sexpr* _Lexpr_0);
void _Mglc_Eexpr_Pwrite_ref_1(struct _Mglc_Sexpr* _Lexpr_0);
void _Mglc_Eexpr_Pwrite_lvar_1(struct _Mglc_Sexpr* _Lexpr_0);
void _Mglc_Eexpr_Pwrite_fvar_1(struct _Mglc_Sexpr* _Lexpr_0);
void _Mglc_Eexpr_Pwrite_gvar_1(struct _Mglc_Sexpr* _Lexpr_0);
void _Mglc_Eexpr_Pwrite_cvar_1(struct _Mglc_Sexpr* _Lexpr_0);
void _Mglc_Eexpr_Pwrite_bools_1(struct _Mglc_Sexpr* _Lexpr_0);
void _Mglc_Eexpr_Pwrite_method_1(struct _Mglc_Sexpr* _Lexpr_0);
void _Mglc_Eexpr_Pwrite_func_1(struct _Mglc_Sexpr* _Lexpr_0);
void _Mglc_Eexpr_Pwrite_str_1(struct _Mglc_Sexpr* _Lexpr_0);
void _Mglc_Eexpr_Pwrite_int_1(struct _Mglc_Sexpr* _Lexpr_0);
void _Mglc_Eexpr_Pwrite_size_of_type_1(struct _Mglc_Sexpr* _Lexpr_0);
void _Mglc_Eexpr_Pwrite_null_1(struct _Mglc_Sexpr* _Lexpr_0);
void _Mglc_Eexpr_Pwrite_index_1(struct _Mglc_Sexpr* _Lexpr_0);
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
void _Mglc_Sdecl_var_Pwrite_2(struct _Mglc_Sdecl_var* _Lvd_0, _Mglc_Edecl_var_type _Lvar_type_1);
bool _Mglc_Eexpr_Pwrite_value_2(_Mglc_Eexpr _Le_0, struct _Mglc_Svalue* _Lv_1);
void _Mglc_Stype_info_Pcount_1(struct _Mglc_Stype_info* _Lti_0);
bool _Mglc_Eat_Pwrite_type_1(_Mglc_Eat _Ltd_0);
int32_t _Mglc_Eat_Pcount_stars0_2(_Mglc_Eat _Ltd_0, struct _Mglc_Stype_info* _Lti_1);
size_t _Mstdc_Sfile_Pwrite_3(FILE* _Lf_0, void* _Lbuf_1, size_t _Lsize_2);
void _Mglc_Sdecl_var_Pwrite_lvar_2(struct _Mglc_Sdecl_var* _Lvd_0, _Mglc_Elvar _Llvar_1);
struct _Mglc_Slvar* _Mglc_Elvar_Pptr_1(_Mglc_Elvar _Ll_0);
void _Mglc_Sstmt_Pwrite_1(struct _Mglc_Sstmt* _Ls_0);
void _Mglc_Evar_flags_Prd_2(_Mglc_Evar_flags* _Lf_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Stype_info_Prd_2(struct _Mglc_Stype_info* _Lti_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Eexpr_type_Prd_2(_Mglc_Eexpr_type* _Le_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Eexpr_Prd_assign_2(_Mglc_Eexpr _Le_idx_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Eexpr_Prd_compare_2(_Mglc_Eexpr _Le_idx_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Eexpr_Prd_bool_2(_Mglc_Eexpr _Le_idx_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Eexpr_Prd_char_2(_Mglc_Eexpr _Le_idx_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Eexpr_Prd_math_2(_Mglc_Eexpr _Le_idx_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Eexpr_Prd_unary_2(_Mglc_Eexpr _Le_idx_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Eexpr_Prd_ref_2(_Mglc_Eexpr _Le_idx_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Eexpr_Prd_cast_fast_2(_Mglc_Eexpr _Le_idx_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Eexpr_Prd_lvar_2(_Mglc_Eexpr _Le_idx_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Eexpr_Prd_fvar_2(_Mglc_Eexpr _Le_idx_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Eexpr_Prd_gvar_2(_Mglc_Eexpr _Le_idx_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Eexpr_Prd_cvar_2(_Mglc_Eexpr _Le_idx_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Eexpr_Prd_bools_2(_Mglc_Eexpr _Le_idx_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Eexpr_Prd_method_2(_Mglc_Eexpr _Le_idx_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Eexpr_Prd_func_2(_Mglc_Eexpr _Le_idx_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Eexpr_Prd_str_2(_Mglc_Eexpr _Le_idx_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Eexpr_Prd_int_2(_Mglc_Eexpr _Le_idx_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Eexpr_Prd_size_of_type_2(_Mglc_Eexpr _Le_idx_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Eexpr_Prd_null_2(_Mglc_Eexpr _Le_idx_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Eexpr_Prd_index_2(_Mglc_Eexpr _Le_idx_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Elvar_flags_Prd_2(_Mglc_Elvar_flags* _Lf_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Elvar_Prd_2(_Mglc_Elvar* _Ll_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Estmt_type_Prd_2(_Mglc_Estmt_type* _Ls_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Sstmt_space_Prd_expr_2(struct _Mglc_Sstmt_space* _Lspace_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Sstmt_space_Prd_if_2(struct _Mglc_Sstmt_space* _Lspace_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Sstmt_space_Prd_if_elif_2(struct _Mglc_Sstmt_space* _Lspace_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Sstmt_space_Prd_if_else_2(struct _Mglc_Sstmt_space* _Lspace_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Sstmt_space_Prd_if_end_2(struct _Mglc_Sstmt_space* _Lspace_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Sstmt_space_Prd_switch_2(struct _Mglc_Sstmt_space* _Lspace_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Sstmt_space_Prd_case_2(struct _Mglc_Sstmt_space* _Lspace_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Sstmt_space_Prd_case_end_2(struct _Mglc_Sstmt_space* _Lspace_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Sstmt_space_Prd_default_2(struct _Mglc_Sstmt_space* _Lspace_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Sstmt_space_Prd_default_end_2(struct _Mglc_Sstmt_space* _Lspace_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Sstmt_space_Prd_switch_end_2(struct _Mglc_Sstmt_space* _Lspace_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Sstmt_space_Prd_do_2(struct _Mglc_Sstmt_space* _Lspace_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Sstmt_space_Prd_do_end_2(struct _Mglc_Sstmt_space* _Lspace_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Sstmt_space_Prd_while_2(struct _Mglc_Sstmt_space* _Lspace_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Sstmt_space_Prd_while_end_2(struct _Mglc_Sstmt_space* _Lspace_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Sstmt_space_Prd_continue_2(struct _Mglc_Sstmt_space* _Lspace_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Sstmt_space_Prd_break_2(struct _Mglc_Sstmt_space* _Lspace_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Sstmt_space_Prd_return_2(struct _Mglc_Sstmt_space* _Lspace_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Sstmt_space_Prd_space_2(struct _Mglc_Sstmt_space* _Lspace_0, union _Mglc_Srdr* _Lr_1);
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
void _Mglc_Sstmt_Pprocess_expr_2(struct _Mglc_Sstmt* _Lstmt_0, bool* _Lok_1);
void _Mglc_Sstmt_Pprocess_if_2(struct _Mglc_Sstmt* _Lstmt_0, bool* _Lok_1);
void _Mglc_Sstmt_Pprocess_if_elif_2(struct _Mglc_Sstmt* _Lstmt_0, bool* _Lok_1);
void _Mglc_Sstmt_Pprocess_if_else_2(struct _Mglc_Sstmt* _Lstmt_0, bool* _Lok_1);
void _Mglc_Sstmt_Pprocess_if_end_2(struct _Mglc_Sstmt* _Lstmt_0, bool* _Lok_1);
void _Mglc_Sstmt_Pprocess_switch_2(struct _Mglc_Sstmt* _Lstmt_0, bool* _Lok_1);
void _Mglc_Sstmt_Pprocess_case_2(struct _Mglc_Sstmt* _Lstmt_0, bool* _Lok_1);
void _Mglc_Sstmt_Pprocess_case_end_2(struct _Mglc_Sstmt* _Lstmt_0, bool* _Lok_1);
void _Mglc_Sstmt_Pprocess_default_2(struct _Mglc_Sstmt* _Lstmt_0, bool* _Lok_1);
void _Mglc_Sstmt_Pprocess_default_end_2(struct _Mglc_Sstmt* _Lstmt_0, bool* _Lok_1);
void _Mglc_Sstmt_Pprocess_switch_end_2(struct _Mglc_Sstmt* _Lstmt_0, bool* _Lok_1);
void _Mglc_Sstmt_Pprocess_do_2(struct _Mglc_Sstmt* _Lstmt_0, bool* _Lok_1);
void _Mglc_Sstmt_Pprocess_do_end_2(struct _Mglc_Sstmt* _Lstmt_0, bool* _Lok_1);
void _Mglc_Sstmt_Pprocess_while_2(struct _Mglc_Sstmt* _Lstmt_0, bool* _Lok_1);
void _Mglc_Sstmt_Pprocess_while_end_2(struct _Mglc_Sstmt* _Lstmt_0, bool* _Lok_1);
void _Mglc_Sstmt_Pprocess_continue_2(struct _Mglc_Sstmt* _Lstmt_0, bool* _Lok_1);
void _Mglc_Sstmt_Pprocess_break_2(struct _Mglc_Sstmt* _Lstmt_0, bool* _Lok_1);
void _Mglc_Sstmt_Pprocess_return_2(struct _Mglc_Sstmt* _Lstmt_0, bool* _Lok_1);
void _Mglc_Sstmt_Pprocess_space_2(struct _Mglc_Sstmt* _Lstmt_0, bool* _Lok_1);
bool _Mglc_Sdecl_var_Pprocess_3(struct _Mglc_Sdecl_var* _Lvd_0, int32_t _Lrow_1, int32_t _Lcol_2);
void _Mglc_Eexpr_Pprocess_assign_2(struct _Mglc_Sexpr* _Lexpr_0, bool* _Lok_1);
void _Mglc_Eexpr_Pprocess_compare_2(struct _Mglc_Sexpr* _Lexpr_0, bool* _Lok_1);
void _Mglc_Eexpr_Pprocess_bool_2(struct _Mglc_Sexpr* _Lexpr_0, bool* _Lok_1);
void _Mglc_Eexpr_Pprocess_char_2(struct _Mglc_Sexpr* _Lexpr_0, bool* _Lok_1);
void _Mglc_Eexpr_Pprocess_math_2(struct _Mglc_Sexpr* _Lexpr_0, bool* _Lok_1);
void _Mglc_Eexpr_Pprocess_unary_2(struct _Mglc_Sexpr* _Lexpr_0, bool* _Lok_1);
void _Mglc_Eexpr_Pprocess_ref_2(struct _Mglc_Sexpr* _Lexpr_0, bool* _Lok_1);
void _Mglc_Eexpr_Pprocess_cast_fast_2(struct _Mglc_Sexpr* _Lexpr_0, bool* _Lok_1);
void _Mglc_Eexpr_Pprocess_lvar_2(struct _Mglc_Sexpr* _Lexpr_0, bool* _Lok_1);
void _Mglc_Eexpr_Pprocess_fvar_2(struct _Mglc_Sexpr* _Lexpr_0, bool* _Lok_1);
void _Mglc_Eexpr_Pprocess_gvar_2(struct _Mglc_Sexpr* _Lexpr_0, bool* _Lok_1);
void _Mglc_Eexpr_Pprocess_cvar_2(struct _Mglc_Sexpr* _Lexpr_0, bool* _Lok_1);
void _Mglc_Eexpr_Pprocess_bools_2(struct _Mglc_Sexpr* _Lexpr_0, bool* _Lok_1);
void _Mglc_Eexpr_Pprocess_method_2(struct _Mglc_Sexpr* _Lexpr_0, bool* _Lok_1);
void _Mglc_Eexpr_Pprocess_func_2(struct _Mglc_Sexpr* _Lexpr_0, bool* _Lok_1);
void _Mglc_Eexpr_Pprocess_str_2(struct _Mglc_Sexpr* _Lexpr_0, bool* _Lok_1);
void _Mglc_Eexpr_Pprocess_int_2(struct _Mglc_Sexpr* _Lexpr_0, bool* _Lok_1);
void _Mglc_Eexpr_Pprocess_size_of_type_2(struct _Mglc_Sexpr* _Lexpr_0, bool* _Lok_1);
void _Mglc_Eexpr_Pprocess_null_2(struct _Mglc_Sexpr* _Lexpr_0, bool* _Lok_1);
void _Mglc_Eexpr_Pprocess_index_2(struct _Mglc_Sexpr* _Lexpr_0, bool* _Lok_1);
void _Mglc_Pwrite_char_1(char _Lc_0);
void _Mglc_Egvar_Pwrite_1(_Mglc_Egvar _Lg_0);
void _Mglc_Pwrite_str_node_2(int32_t _Llen_0, void* _Lptr_1);
void _Mglc_Sexpr_cast_fast_Pwrite_value_2(struct _Mglc_Sexpr_cast_fast* _Le_0, struct _Mglc_Svalue* _Lv_1);
int32_t _Mglc_Eat_Ppointer_1(_Mglc_Eat _Ltd_0);
void _Mglc_Sstmt_Pwrite_expr_1(struct _Mglc_Sstmt* _Lstmt_0);
void _Mglc_Sstmt_Pwrite_if_1(struct _Mglc_Sstmt* _Lstmt_0);
void _Mglc_Sstmt_Pwrite_if_elif_1(struct _Mglc_Sstmt* _Lstmt_0);
void _Mglc_Sstmt_Pwrite_if_else_1(struct _Mglc_Sstmt* _Lstmt_0);
void _Mglc_Sstmt_Pwrite_if_end_1(struct _Mglc_Sstmt* _Lstmt_0);
void _Mglc_Sstmt_Pwrite_switch_1(struct _Mglc_Sstmt* _Lstmt_0);
void _Mglc_Sstmt_Pwrite_case_1(struct _Mglc_Sstmt* _Lstmt_0);
void _Mglc_Sstmt_Pwrite_case_end_1(struct _Mglc_Sstmt* _Lstmt_0);
void _Mglc_Sstmt_Pwrite_default_1(struct _Mglc_Sstmt* _Lstmt_0);
void _Mglc_Sstmt_Pwrite_default_end_1(struct _Mglc_Sstmt* _Lstmt_0);
void _Mglc_Sstmt_Pwrite_switch_end_1(struct _Mglc_Sstmt* _Lstmt_0);
void _Mglc_Sstmt_Pwrite_do_1(struct _Mglc_Sstmt* _Lstmt_0);
void _Mglc_Sstmt_Pwrite_do_end_1(struct _Mglc_Sstmt* _Lstmt_0);
void _Mglc_Sstmt_Pwrite_while_1(struct _Mglc_Sstmt* _Lstmt_0);
void _Mglc_Sstmt_Pwrite_while_end_1(struct _Mglc_Sstmt* _Lstmt_0);
void _Mglc_Sstmt_Pwrite_continue_1(struct _Mglc_Sstmt* _Lstmt_0);
void _Mglc_Sstmt_Pwrite_break_1(struct _Mglc_Sstmt* _Lstmt_0);
void _Mglc_Sstmt_Pwrite_return_1(struct _Mglc_Sstmt* _Lstmt_0);
void _Mglc_Sstmt_Pwrite_space_1(struct _Mglc_Sstmt* _Lstmt_0);
void _Mglc_Eexpr_Pset_3(_Mglc_Eexpr _Le_0, struct _Mglc_Sexpr* _Lexpr_1, _Mglc_Eexpr_type _Ltype_2);
void _Mglc_Eassign_Prd_2(_Mglc_Eassign* _Ls_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Ecompare_Prd_2(_Mglc_Ecompare* _Le_0, union _Mglc_Srdr* _Lr_1);
bool _Mglc_Srdr_Pbool_1(union _Mglc_Srdr* _Lr_0);
void _Mglc_Emath_Prd_2(_Mglc_Emath* _Le_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Eunary_Prd_2(_Mglc_Eunary* _Lu_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Ebools_Prd_2(_Mglc_Ebools* _Le_0, union _Mglc_Srdr* _Lr_1);
void _Mglc_Srdr_Pcopy_3(union _Mglc_Srdr* _Lr_0, void* _Ldata_1, int32_t _Lsize_2);
void _Mglc_Sstmt_space_Pstmt_push_7(struct _Mglc_Sstmt_space* _Ls_0, struct _Mglc_Sstmt* _Ls2_1, int32_t _Lbegin_row_2, int32_t _Lbegin_col_3, int32_t _Lend_row_4, int32_t _Lend_col_5, _Mglc_Estmt_type _Ltype_6);
bool _Mglc_Eexpr_Pvalue_4(_Mglc_Eexpr _Le_0, int32_t _Lref_1, bool _Lparen_2, struct _Mglc_Svalue* _Lv_3);
bool _Mglc_Eexpr_Pprocess_case_func_2(struct _Mglc_Sexpr* _Lexpr_0, _Mglc_Efunc _Lf_idx_1);
uint8_t _Mglc_Eid_Plen_1(_Mglc_Eid _Lid_0);
bool _Mglc_Sstmt_space_Pprocess_1(struct _Mglc_Sstmt_space* _Lspace_0);
void _Mglc_Eexpr_Ptry_deduce_2(_Mglc_Eexpr _Le_idx_0, _Mglc_Eat _Lat_1);
void _Mglc_Stype_info_Pinit_1(struct _Mglc_Stype_info* _Lti_0);
void _Mglc_Stype_info_Pcopy_from_2(struct _Mglc_Stype_info* _Lti_0, struct _Mglc_Stype_info* _Lti2_1);
_Mglc_Eat _Mglc_Eexpr_Ptype_1(_Mglc_Eexpr _Le_0);
bool _Mglc_Elvar_Pprocess_1(_Mglc_Elvar _Ll_0);
bool _Mglc_Egvar_Pprocess_1(_Mglc_Egvar _Lg_0);
bool _Mglc_Pfarg_process_4(_Mglc_Eexpr _Le_0, int8_t _Lca_ref_1, struct _Mglc_Svalue* _Lca_value_2, struct _Mglc_Sdecl_var* _Lfd_arg_3);
void _Mglc_Eexpr_Pvalue_assign_5(_Mglc_Eexpr _Le_0, int8_t _Lref_1, bool _Lparen_2, struct _Mglc_Svalue* _Lv_3, bool* _Lok_4);
void _Mglc_Eexpr_Pvalue_compare_5(_Mglc_Eexpr _Le_0, int8_t _Lref_1, bool _Lparen_2, struct _Mglc_Svalue* _Lv_3, bool* _Lok_4);
void _Mglc_Eexpr_Pvalue_bool_5(_Mglc_Eexpr _Lle_0, int32_t _Lref_1, bool _Lparen_2, struct _Mglc_Svalue* _Lv_3, bool* _Lok_4);
void _Mglc_Eexpr_Pvalue_char_5(_Mglc_Eexpr _Lle_0, int32_t _Lref_1, bool _Lparen_2, struct _Mglc_Svalue* _Lv_3, bool* _Lok_4);
void _Mglc_Eexpr_Pvalue_math_5(_Mglc_Eexpr _Le_0, int8_t _Lref_1, bool _Lparen_2, struct _Mglc_Svalue* _Lv_3, bool* _Lok_4);
void _Mglc_Eexpr_Pvalue_unary_5(_Mglc_Eexpr _Le_0, int8_t _Lref_1, bool _Lparen_2, struct _Mglc_Svalue* _Lv_3, bool* _Lok_4);
void _Mglc_Eexpr_Pvalue_ref_5(_Mglc_Eexpr _Le_0, int8_t _Lref_1, bool _Lparen_2, struct _Mglc_Svalue* _Lv_3, bool* _Lok_4);
void _Mglc_Eexpr_Pvalue_cast_fast_5(_Mglc_Eexpr _Le_0, int8_t _Lref_1, bool _Lparen_2, struct _Mglc_Svalue* _Lv_3, bool* _Lok_4);
void _Mglc_Eexpr_Pvalue_lvar_5(_Mglc_Eexpr _Le_0, int8_t _Lref_1, bool _Lparen_2, struct _Mglc_Svalue* _Lv_3, bool* _Lok_4);
void _Mglc_Eexpr_Pvalue_fvar_5(_Mglc_Eexpr _Lexpr_0, int8_t _Lref_1, bool _Lparen_2, struct _Mglc_Svalue* _Lv_3, bool* _Lok_4);
void _Mglc_Eexpr_Pvalue_gvar_5(_Mglc_Eexpr _Lg_0, int32_t _Lref_1, bool _Lparen_2, struct _Mglc_Svalue* _Lv_3, bool* _Lok_4);
void _Mglc_Eexpr_Pvalue_cvar_5(_Mglc_Eexpr _Le_0, int8_t _Lref_1, bool _Lparen_2, struct _Mglc_Svalue* _Lv_3, bool* _Lok_4);
void _Mglc_Eexpr_Pvalue_bools_5(_Mglc_Eexpr _Le_0, int32_t _Lref_1, bool _Lparen_2, struct _Mglc_Svalue* _Lv_3, bool* _Lok_4);
void _Mglc_Eexpr_Pvalue_func_5(_Mglc_Eexpr _Le_0, int32_t _Lref_1, bool _Lparen_2, struct _Mglc_Svalue* _Lv_3, bool* _Lok_4);
void _Mglc_Eexpr_Pvalue_method_5(_Mglc_Eexpr _Le_0, int32_t _Lref_1, bool _Lparen_2, struct _Mglc_Svalue* _Lv_3, bool* _Lok_4);
void _Mglc_Eexpr_Pvalue_str_5(_Mglc_Eexpr _Ls_0, int32_t _Lref_1, bool _Lparen_2, struct _Mglc_Svalue* _Lv_3, bool* _Lok_4);
void _Mglc_Eexpr_Pvalue_int_5(_Mglc_Eexpr _Lle_0, int32_t _Lref_1, bool _Lparen_2, struct _Mglc_Svalue* _Lv_3, bool* _Lok_4);
void _Mglc_Eexpr_Pvalue_size_of_type_5(_Mglc_Eexpr _Lle_0, int32_t _Lref_1, bool _Lparen_2, struct _Mglc_Svalue* _Lv_3, bool* _Lok_4);
void _Mglc_Eexpr_Pvalue_null_5(_Mglc_Eexpr _Lle_0, int32_t _Lref_1, bool _Lparen_2, struct _Mglc_Svalue* _Lv_3, bool* _Lok_4);
void _Mglc_Eexpr_Pvalue_index_5(_Mglc_Eexpr _Le_0, int8_t _Lref_1, bool _Lparen_2, struct _Mglc_Svalue* _Lv_3, bool* _Lok_4);
void _Mglc_Eexpr_Ptry_deduce_math_2(struct _Mglc_Sexpr* _Lexpr_0, _Mglc_Eat _Lat_1);
void _Mglc_Eexpr_Ptry_deduce_cvar_2(struct _Mglc_Sexpr* _Lexpr_0, _Mglc_Eat _Lat_1);
void _Mglc_Eexpr_Ptype_assign_2(struct _Mglc_Sexpr* _Lexpr_0, _Mglc_Eat* _Lat_1);
void _Mglc_Eexpr_Ptype_compare_2(struct _Mglc_Sexpr* _Lexpr_0, _Mglc_Eat* _Lat_1);
void _Mglc_Eexpr_Ptype_bool_2(struct _Mglc_Sexpr* _Lexpr_0, _Mglc_Eat* _Lat_1);
void _Mglc_Eexpr_Ptype_char_2(struct _Mglc_Sexpr* _Lexpr_0, _Mglc_Eat* _Lat_1);
void _Mglc_Eexpr_Ptype_math_2(struct _Mglc_Sexpr* _Lexpr_0, _Mglc_Eat* _Lat_1);
void _Mglc_Eexpr_Ptype_unary_2(struct _Mglc_Sexpr* _Lexpr_0, _Mglc_Eat* _Lat_1);
void _Mglc_Eexpr_Ptype_ref_2(struct _Mglc_Sexpr* _Lexpr_0, _Mglc_Eat* _Lat_1);
void _Mglc_Eexpr_Ptype_cast_fast_2(struct _Mglc_Sexpr* _Lexpr_0, _Mglc_Eat* _Lat_1);
void _Mglc_Eexpr_Ptype_lvar_2(struct _Mglc_Sexpr* _Lexpr_0, _Mglc_Eat* _Lat_1);
void _Mglc_Eexpr_Ptype_fvar_2(struct _Mglc_Sexpr* _Lexpr_0, _Mglc_Eat* _Lat_1);
void _Mglc_Eexpr_Ptype_gvar_2(struct _Mglc_Sexpr* _Lexpr_0, _Mglc_Eat* _Lat_1);
void _Mglc_Eexpr_Ptype_cvar_2(struct _Mglc_Sexpr* _Lexpr_0, _Mglc_Eat* _Lat_1);
void _Mglc_Eexpr_Ptype_bools_2(struct _Mglc_Sexpr* _Lexpr_0, _Mglc_Eat* _Lat_1);
void _Mglc_Eexpr_Ptype_func_2(struct _Mglc_Sexpr* _Lexpr_0, _Mglc_Eat* _Lat_1);
void _Mglc_Eexpr_Ptype_method_2(struct _Mglc_Sexpr* _Lexpr_0, _Mglc_Eat* _Lat_1);
void _Mglc_Eexpr_Ptype_int_2(struct _Mglc_Sexpr* _Lexpr_0, _Mglc_Eat* _Lat_1);
void _Mglc_Eexpr_Ptype_size_of_type_2(struct _Mglc_Sexpr* _Lexpr_0, _Mglc_Eat* _Lat_1);
void _Mglc_Eexpr_Ptype_null_2(struct _Mglc_Sexpr* _Lexpr_0, _Mglc_Eat* _Lat_1);
void _Mglc_Eexpr_Ptype_index_2(struct _Mglc_Sexpr* _Lexpr_0, _Mglc_Eat* _Lat_1);
void _Mglc_Svalue_Pset_5(struct _Mglc_Svalue* _Lv_0, int8_t _Lref_1, bool _Lparen_2, _Mglc_Eat _Ltype_3, struct _Mglc_Stype_info* _Linfo_4);
int32_t main(int32_t _Larg_c_0, char** _Larg_v_1) {
if(_Larg_c_0 < 2) {
fprintf(stdout, "usage: %s file.glc-t\n", _Larg_v_1[0]);
return 0;
}
if(false) {
qalloc_undo(0);
}
_Mglc_Smap_Pinit_1(&_Gid_map);
_Mglc_Smap_Pinit_1(&_Ginclude_map);
_Mglc_Pquick_alloc_init_0();
_Gfunc_main = _Mglc_Efunc_Cnil;
_Mglc_Ebasic_type_id _Ltype_2;
_Ltype_2 = (_Mglc_Ebasic_type_id)(0);
for(int i = _Mglc_Ebasic_type_id_CCOUNT; i > 0; ) {
i --;
_Mglc_Eat _Lat_idx_3;
struct _Mglc_Sat* _Lat_5;
_Lat_idx_3 = _Gat_c++;
if(_Gat_cap <= _Gat_c) {
_Mglc_Eat _Lold_cap_4;
_Lold_cap_4 = _Gat_cap;
_Mglc_Pgrow_2(_Gat_cap, _Gat_c);
_Mglc_Prealloc_3(_Gat_v, _Gat_cap, _Lold_cap_4);
}
_Lat_5 = (&_Gat_v[_Lat_idx_3]);
_Mglc_Sat_Pinit_4(_Lat_5, _Mglc_Ename_type_Cbasic, _Mglc_Eat_Croot, (_Mglc_Eid)(_Ltype_2));
continue_0:;
_Ltype_2++;
}
break_0:;
int32_t _Li_6;
_Li_6 = 1;
for(int i = _Larg_c_0 - 2; i > 0; ) {
i --;
char* _Lin_path_7;
_Lin_path_7 = _Larg_v_1[_Li_6];
_Mglc_Pread_1(_Lin_path_7);
continue_1:;
_Li_6++;
}
break_1:;
_Mglc_Efunc _Lf_idx_8;
_Lf_idx_8 = (_Mglc_Efunc)(0);
for(int i = _Gfunc_c; i > 0; ) {
i --;
struct _Mglc_Sdecl_func* _Lf_9;
_Lf_9 = _Mglc_Efunc_Pptr_1(_Lf_idx_8);
if((*_Lf_9)._Fthis_idx != -1) {
struct _Mglc_Sat* _Lat_10;
_Lat_10 = _Mglc_Eat_Pptr_1((*_Lf_9)._Fat);
if((*_Lat_10)._Ftype == _Mglc_Ename_type_Cstruct) {
struct _Mglc_Sstruct* _Lt_11;
int32_t _Lt_method_idx_12;
if((*_Lat_10)._Fdecl._Fenum == _Mglc_Eenum_Cnil) {
fprintf(stdout, "%s:%u:%u: function using '`this' was declared on struct /%s that was not defined\n", _Mglc_Efile_Ppath_1((*_Lf_9)._Ffile), (*_Lf_9)._Fbegin_row, (*_Lf_9)._Fbegin_col, _Mglc_Eid_Pstr_1((*_Lat_10)._Fname._Fid));
exit(_Mstdc_Eexit_Cfailure);
}
_Lt_11 = _Mglc_Estruct_Pptr_1((*_Lat_10)._Fdecl._Fstruct);
_Lt_method_idx_12 = (*_Lt_11)._Fmethod_c++;
if((*_Lt_11)._Fmethod_cap <= (*_Lt_11)._Fmethod_c) {
int32_t _Lold_cap_13;
_Lold_cap_13 = (*_Lt_11)._Fmethod_cap;
_Mglc_Pgrow_2((*_Lt_11)._Fmethod_cap, (*_Lt_11)._Fmethod_c);
_Mglc_Prealloc_3((*_Lt_11)._Fmethod_v, (*_Lt_11)._Fmethod_cap, _Lold_cap_13);
}
(*_Lt_11)._Fmethod_v[_Lt_method_idx_12] = _Lf_idx_8;
} else if((*_Lat_10)._Ftype == _Mglc_Ename_type_Cenum) {
struct _Mglc_Senum* _Lt_14;
int32_t _Lt_method_idx_15;
if((*_Lat_10)._Fdecl._Fenum == _Mglc_Eenum_Cnil) {
fprintf(stdout, "%s:%u:%u: function using '`this' was declared on enum \\%s that was not defined\n", _Mglc_Efile_Ppath_1((*_Lf_9)._Ffile), (*_Lf_9)._Fbegin_row, (*_Lf_9)._Fbegin_col, _Mglc_Eid_Pstr_1((*_Lat_10)._Fname._Fid));
exit(_Mstdc_Eexit_Cfailure);
}
_Lt_14 = _Mglc_Eenum_Pptr_1((*_Lat_10)._Fdecl._Fenum);
_Lt_method_idx_15 = (*_Lt_14)._Fmethod_c++;
if((*_Lt_14)._Fmethod_cap <= (*_Lt_14)._Fmethod_c) {
int32_t _Lold_cap_16;
_Lold_cap_16 = (*_Lt_14)._Fmethod_cap;
_Mglc_Pgrow_2((*_Lt_14)._Fmethod_cap, (*_Lt_14)._Fmethod_c);
_Mglc_Prealloc_3((*_Lt_14)._Fmethod_v, (*_Lt_14)._Fmethod_cap, _Lold_cap_16);
}
(*_Lt_14)._Fmethod_v[_Lt_method_idx_15] = _Lf_idx_8;
} else if((*_Lat_10)._Ftype == _Mglc_Ename_type_Cbasic) {
struct _Mglc_Sbasic_type* _Lt_17;
int32_t _Lt_method_idx_18;
_Lt_17 = (&_Gbasic_type[(*_Lat_10)._Fname._Fbasic]);
_Lt_method_idx_18 = (*_Lt_17)._Fmethod_c++;
if((*_Lt_17)._Fmethod_cap <= (*_Lt_17)._Fmethod_c) {
int32_t _Lold_cap_19;
_Lold_cap_19 = (*_Lt_17)._Fmethod_cap;
_Mglc_Pgrow_2((*_Lt_17)._Fmethod_cap, (*_Lt_17)._Fmethod_c);
_Mglc_Prealloc_3((*_Lt_17)._Fmethod_v, (*_Lt_17)._Fmethod_cap, _Lold_cap_19);
}
(*_Lt_17)._Fmethod_v[_Lt_method_idx_18] = _Lf_idx_8;
} else {
fprintf(stdout, "%s:%u:%u: function using '`this' was declared on a type that's not a struct or enum\n", _Mglc_Efile_Ppath_1((*_Lf_9)._Ffile), (*_Lf_9)._Fbegin_row, (*_Lf_9)._Fbegin_col);
exit(_Mstdc_Eexit_Cfailure);
}
}
continue_2:;
_Lf_idx_8++;
}
break_2:;
if(_Gfunc_main != _Mglc_Efunc_Cnil) {
struct _Mglc_Sdecl_func* _Lf_20;
_Lf_20 = _Mglc_Efunc_Pptr_1(_Gfunc_main);
(*_Lf_20)._Freal_name = _Mglc_Pid_add_2(4, "main");
(*_Lf_20)._Fflags |= _Mglc_Efunc_flags_Creal_name;
}
_Mglc_Pquick_alloc_arr_2(_Gid_c_name_v, _Gid_c);
if(true) {
_Mglc_Efunc _Lfunc_c8_21;
_Lfunc_c8_21 = ((_Gfunc_c + 7) >> 3);
_Mglc_Pquick_alloc_arr_2(_Gfunc_in_process, _Lfunc_c8_21);
_Mglc_Pquick_alloc_arr_2(_Gfunc_head_outputted_v, _Gfunc_c);
_Mglc_Pquick_alloc_arr_2(_Gfunc_body_outputted_v, _Gfunc_c);
}
if(true) {
int32_t _Linclude_c8_22;
_Linclude_c8_22 = ((_Ginclude_c + 7) >> 3);
_Mglc_Pquick_alloc_arr_2(_Ginclude_is_outputted, _Linclude_c8_22);
_Mglc_Pquick_alloc_arr_2(_Ginclude_outputted_v, _Ginclude_c);
}
if(true) {
_Mglc_Ecvar _Lcvar_c8_23;
_Lcvar_c8_23 = ((_Gcvar_c + 7) >> 3);
_Mglc_Pquick_alloc_arr_2(_Gcvar_is_outputted, _Lcvar_c8_23);
_Mglc_Pquick_alloc_arr_2(_Gcvar_outputted_v, _Gcvar_c);
}
if(true) {
_Mglc_Egvar _Lgvar_c8_24;
_Lgvar_c8_24 = ((_Ggvar_c + 7) >> 3);
_Mglc_Pquick_alloc_arr_2(_Ggvar_is_outputted, _Lgvar_c8_24);
_Mglc_Pquick_alloc_arr_2(_Ggvar_outputted_v, _Ggvar_c);
}
if(true) {
_Mglc_Eenum _Lenum_c8_25;
_Lenum_c8_25 = ((_Genum_c + 7) >> 3);
_Mglc_Pquick_alloc_arr_2(_Genum_is_outputted, _Lenum_c8_25);
_Mglc_Pquick_alloc_arr_2(_Genum_outputted_v, _Genum_c);
}
if(true) {
_Mglc_Estruct _Lstruct_c8_26;
_Lstruct_c8_26 = ((_Gstruct_c + 7) >> 3);
_Mglc_Pquick_alloc_arr_2(_Gstruct_is_outputted, _Lstruct_c8_26);
_Mglc_Pquick_alloc_arr_2(_Gstruct_outputted_v, _Gstruct_c);
}
_Gprocess_first = _Mglc_Efunc_Cnil;
_Gprocess_last = _Mglc_Efunc_Cnil;
if(_Gfunc_main != _Mglc_Efunc_Cnil) {
_Mglc_Efunc_Pprocess_later_1(_Gfunc_main);
}
while(_Gprocess_first != _Mglc_Efunc_Cnil) {
_Mglc_Efunc _Lf_i_27;
_Lf_i_27 = _Gprocess_first;
_Gprocess_first = _Mglc_Efunc_Cnil;
_Gprocess_last = _Mglc_Efunc_Cnil;
while(1) {
struct _Mglc_Sdecl_func* _Lf_28;
if(!(_Mglc_Efunc_Pprocess_now_1(_Lf_i_27))) {
return -1;
}
_Lf_28 = _Mglc_Efunc_Pptr_1(_Lf_i_27);
_Lf_i_27 = (*_Lf_28)._Fprocess_next;
if(_Lf_i_27 == _Mglc_Efunc_Cnil) {
goto break_4;
}
continue_4:;
}
break_4:;
continue_3:;
}
break_3:;
fprintf(stdout, "finished processing, writing...\n");
_Gout = fopen(_Larg_v_1[(_Larg_c_0 - 1)], "w");
int32_t _Li_29;
_Li_29 = 0;
for(int i = _Gfunc_head_outputted_c; i > 0; ) {
i --;
_Mglc_Efunc _Lf_idx_30;
struct _Mglc_Sdecl_func* _Lf_31;
int32_t _Lrow_32;
int32_t _Lcol_33;
_Lf_idx_30 = _Gfunc_head_outputted_v[_Li_29];
_Lf_31 = _Mglc_Efunc_Pptr_1(_Lf_idx_30);
_Lrow_32 = (*_Lf_31)._Fbegin_row;
_Lcol_33 = (*_Lf_31)._Fbegin_col;
if((*_Lf_31)._Fdecl._Ftype != _Mglc_Eat_Cnil) {
_Mglc_Eat_Poutput_4((*_Lf_31)._Fdecl._Ftype, (*_Lf_31)._Ffile, _Lrow_32, _Lcol_33);
}
int32_t _Li_34;
_Li_34 = 0;
for(int i = (*_Lf_31)._Ffarg_c; i > 0; ) {
i --;
_Mglc_Eat_Poutput_4((*_Lf_31)._Ffarg_v[_Li_34]._Fdecl._Ftype, (*_Lf_31)._Ffile, _Lrow_32, _Lcol_33);
continue_6:;
_Li_34++;
}
break_6:;
if((*_Lf_31)._Finclude != _Mglc_Einclude_Cnil) {
_Mglc_Einclude_Poutput_1((*_Lf_31)._Finclude);
}
if(((*_Lf_31)._Fflags & _Mglc_Efunc_flags_Cglc_name) != _Mglc_Efunc_flags_C0) {
struct _Mglc_Sat* _Lat_35;
_Lat_35 = _Mglc_Eat_Pptr_1((*_Lf_31)._Fat);
int32_t _Li_36;
_Mglc_Ecvar* _Lv_37;
_Li_36 = 0;
_Lv_37 = (*_Lat_35)._Fcvar_v;
for(int i = (*_Lat_35)._Fcvar_c; i > 0; ) {
i --;
_Mglc_Ecvar _Lcvar_38;
_Lcvar_38 = _Lv_37[_Li_36];
if(((*_Mglc_Ecvar_Pptr_1(_Lcvar_38))._Fflags & _Mglc_Ecvar_flags_Cas_enum) != _Mglc_Ecvar_flags_C0) {
_Mglc_Ecvar_Pprocess_1(_Lcvar_38);
}
continue_7:;
_Li_36++;
}
break_7:;
}
continue_5:;
_Li_29++;
}
break_5:;
fprintf(_Gout, "#include <stdint.h>\n");
if(_Ginclude_stdbool) {
fprintf(_Gout, "#include <stdbool.h>\n");
}
if(_Ginclude_stddef) {
fprintf(_Gout, "#include <stddef.h>\n");
}
int32_t _Li_39;
_Li_39 = 0;
for(int i = _Ginclude_outputted_c; i > 0; ) {
i --;
_Mglc_Einclude _Linc_40;
_Linc_40 = _Ginclude_outputted_v[_Li_39];
fprintf(_Gout, "#include %s\n", _Mglc_Einclude_Pstr_1(_Linc_40));
continue_8:;
_Li_39++;
}
break_8:;
int32_t _Li_41;
_Li_41 = 0;
for(int i = _Gcvar_outputted_c; i > 0; ) {
i --;
_Mglc_Ecvar _Lc_i_42;
struct _Mglc_Scvar* _Lc_43;
_Lc_i_42 = _Gcvar_outputted_v[_Li_41];
_Lc_43 = _Mglc_Ecvar_Pptr_1(_Lc_i_42);
if(((*_Lc_43)._Fdecl._Fflags & _Mglc_Evar_flags_Cno_decl) != _Mglc_Evar_flags_C0) {
goto continue_9;
}
fprintf(_Gout, "#define ");
_Mglc_Ecvar_Pwrite_1(_Lc_i_42);
fprintf(_Gout, " ");
if(((*_Lc_43)._Fflags & _Mglc_Ecvar_flags_Cset_expr) != _Mglc_Ecvar_flags_C0) {
fprintf(_Gout, "(");
_Mglc_Eexpr_Pwrite_1((*_Lc_43)._Fexpr_set);
fprintf(_Gout, ")");
} else if((*_Lc_43)._Flast_cvar != _Mglc_Ecvar_Cnil) {
fprintf(_Gout, "(");
_Mglc_Ecvar_Pwrite_1((*_Lc_43)._Flast_cvar);
fprintf(_Gout, " + 1)");
} else {
fprintf(_Gout, "0");
}
fprintf(_Gout, "\n");
continue_9:;
_Li_41++;
}
break_9:;
int32_t _Li_44;
_Li_44 = 0;
for(int i = _Genum_outputted_c; i > 0; ) {
i --;
_Mglc_Eenum _Le_i_45;
struct _Mglc_Senum* _Le_46;
_Le_i_45 = _Genum_outputted_v[_Li_44];
_Le_46 = _Mglc_Eenum_Pptr_1(_Le_i_45);
fprintf(_Gout, "typedef ");
_Mglc_Eat_Pwrite_1((*_Le_46)._Fbase_type);
fprintf(_Gout, " ");
_Mglc_Eat_Pwrite_1((*_Le_46)._Fat);
fprintf(_Gout, ";\n");
continue_10:;
_Li_44++;
}
break_10:;
int32_t _Li_47;
_Li_47 = 0;
for(int i = _Gstruct_outputted_c; i > 0; ) {
i --;
_Mglc_Estruct _Ls_i_48;
struct _Mglc_Sstruct* _Ls_49;
_Ls_i_48 = _Gstruct_outputted_v[_Li_47];
_Ls_49 = _Mglc_Estruct_Pptr_1(_Ls_i_48);
if(((*_Ls_49)._Fflags & _Mglc_Estruct_flags_Cunion) != _Mglc_Estruct_flags_C0) {
fprintf(_Gout, "union ");
} else {
fprintf(_Gout, "struct ");
}
_Mglc_Eat_Pwrite_space_1((*_Ls_49)._Fat);
if(((*_Ls_49)._Fflags & _Mglc_Estruct_flags_Cunion) != _Mglc_Estruct_flags_C0) {
fprintf(_Gout, ";\nunion ");
} else {
fprintf(_Gout, ";\nstruct ");
}
_Mglc_Eat_Pwrite_space_1((*_Ls_49)._Fat);
fprintf(_Gout, " {\n");
int32_t _Lj_50;
_Lj_50 = 0;
for(int i = (*_Ls_49)._Ffvar_c; i > 0; ) {
i --;
struct _Mglc_Sfvar* _Lfvar_51;
_Lfvar_51 = (&(*_Ls_49)._Ffvar_v[_Lj_50]);
_Mglc_Sdecl_var_Pwrite_type_2(&(*_Lfvar_51)._Fdecl, _Mglc_Edecl_var_type_Cfvar);
fprintf(_Gout, ";\n");
continue_12:;
_Lj_50++;
}
break_12:;
fprintf(_Gout, "};\n");
continue_11:;
_Li_47++;
}
break_11:;
int32_t _Li_52;
_Li_52 = 0;
for(int i = _Ggvar_outputted_c; i > 0; ) {
i --;
_Mglc_Egvar _Lg_i_53;
struct _Mglc_Sdecl_gvar* _Lg_54;
_Lg_i_53 = _Ggvar_outputted_v[_Li_52];
_Lg_54 = _Mglc_Egvar_Pptr_1(_Lg_i_53);
if(((*_Lg_54)._Fdecl._Fflags & _Mglc_Evar_flags_Cno_decl) != _Mglc_Evar_flags_C0) {
goto continue_13;
}
if(((*_Lg_54)._Fdecl._Fflags & _Mglc_Evar_flags_Cextern) != _Mglc_Evar_flags_C0) {
fprintf(_Gout, "extern ");
}
_Mglc_Sdecl_var_Pwrite_type_2(&(*_Lg_54)._Fdecl, _Mglc_Edecl_var_type_Cgvar);
fprintf(_Gout, ";\n");
continue_13:;
_Li_52++;
}
break_13:;
int32_t _Li_55;
_Li_55 = 0;
for(int i = _Gfunc_head_outputted_c; i > 0; ) {
i --;
_Mglc_Efunc _Lf_idx_56;
struct _Mglc_Sdecl_func* _Lf_57;
_Lf_idx_56 = _Gfunc_head_outputted_v[_Li_55];
_Lf_57 = _Mglc_Efunc_Pptr_1(_Lf_idx_56);
if(((*_Lf_57)._Fflags & _Mglc_Efunc_flags_Cno_decl) != _Mglc_Efunc_flags_C0) {
goto continue_14;
}
if(((*_Lf_57)._Fflags & _Mglc_Efunc_flags_Cdecl) != _Mglc_Efunc_flags_C0) {
if((((*_Lf_57)._Fdecl_str[0] == '#') && ((*_Lf_57)._Fdecl_str[1] == ' '))) {
fprintf(_Gout, "#define ");
_Mglc_Sdecl_func_Pwrite_1(_Lf_57);
fprintf(_Gout, "(");
int32_t _Lj_58;
_Lj_58 = 0;
for(int i = (*_Lf_57)._Ffarg_c; i > 0; ) {
i --;
if(_Lj_58 != 0) {
fprintf(_Gout, ", ");
}
fprintf(_Gout, "%s", _Mglc_Eid_Pstr_1((*_Lf_57)._Ffarg_v[_Lj_58]._Fdecl._Fname));
continue_15:;
_Lj_58++;
}
break_15:;
fprintf(_Gout, ") ");
fprintf(_Gout, "%.*s\n", (*_Lf_57)._Fdecl_len - 2, &(*_Lf_57)._Fdecl_str[2]);
} else {
fprintf(_Gout, "%.*s\n", (*_Lf_57)._Fdecl_len, (*_Lf_57)._Fdecl_str);
}
goto continue_14;
}
_Gctx_func = _Lf_57;
if((*_Lf_57)._Fdecl._Ftype == _Mglc_Eat_Cnil) {
fprintf(_Gout, "void");
} else {
_Mglc_Eat_Pwrite_type_info_3((*_Lf_57)._Fdecl._Ftype, &(*_Lf_57)._Fdecl._Ftype_info, 0);
}
fprintf(_Gout, " ");
_Mglc_Sdecl_func_Pwrite_1(_Lf_57);
fprintf(_Gout, "(");
int32_t _Lj_59;
_Lj_59 = 0;
for(int i = (*_Lf_57)._Ffarg_c; i > 0; ) {
i --;
if(_Lj_59 != 0) {
fprintf(_Gout, ", ");
}
_Mglc_Sdecl_var_Pwrite_lvar_type_2(&(*_Lf_57)._Ffarg_v[_Lj_59]._Fdecl, (_Mglc_Elvar)(_Lj_59));
continue_16:;
_Lj_59++;
}
break_16:;
if(((*_Lf_57)._Fflags & _Mglc_Efunc_flags_Cglc_name) != _Mglc_Efunc_flags_C0) {
struct _Mglc_Sat* _Lat_60;
fprintf(_Gout, ") {\nswitch(_Le_0) {\n");
_Lat_60 = _Mglc_Eat_Pptr_1((*_Lf_57)._Fat);
int32_t _Li_61;
_Mglc_Ecvar* _Lv_62;
_Li_61 = 0;
_Lv_62 = (*_Lat_60)._Fcvar_v;
for(int i = (*_Lat_60)._Fcvar_c; i > 0; ) {
i --;
_Mglc_Ecvar _Lcvar_i_63;
struct _Mglc_Scvar* _Lcvar_64;
_Lcvar_i_63 = _Lv_62[_Li_61];
_Lcvar_64 = _Mglc_Ecvar_Pptr_1(_Lcvar_i_63);
if(((*_Lcvar_64)._Fflags & _Mglc_Ecvar_flags_Cas_enum) == _Mglc_Ecvar_flags_C0) {
goto continue_17;
}
fprintf(_Gout, "case ");
_Mglc_Ecvar_Pwrite_1(_Lcvar_i_63);
fprintf(_Gout, ": return \"%s\";\n", _Mglc_Eid_Pstr_1((*_Lcvar_64)._Fdecl._Fname));
continue_17:;
_Li_61++;
}
break_17:;
fprintf(_Gout, "}\nreturn \"(ERROR)\";\n}\n");
} else {
fprintf(_Gout, ");\n");
}
continue_14:;
_Li_55++;
}
break_14:;
int32_t _Li_65;
_Li_65 = 0;
for(int i = _Gfunc_body_outputted_c; i > 0; ) {
i --;
_Mglc_Efunc _Lf_idx_66;
struct _Mglc_Sdecl_func* _Lf_67;
_Lf_idx_66 = _Gfunc_body_outputted_v[_Li_65];
_Lf_67 = _Mglc_Efunc_Pptr_1(_Lf_idx_66);
_Gctx_func = _Lf_67;
_Gnest_id = 0;
if((*_Lf_67)._Fdecl._Ftype == _Mglc_Eat_Cnil) {
fprintf(_Gout, "void");
} else {
_Mglc_Eat_Pwrite_type_info_3((*_Lf_67)._Fdecl._Ftype, &(*_Lf_67)._Fdecl._Ftype_info, 0);
}
fprintf(_Gout, " ");
_Mglc_Sdecl_func_Pwrite_1(_Lf_67);
fprintf(_Gout, "(");
int32_t _Lj_68;
_Lj_68 = 0;
for(int i = (*_Lf_67)._Ffarg_c; i > 0; ) {
i --;
if(_Lj_68 != 0) {
fprintf(_Gout, ", ");
}
_Mglc_Sdecl_var_Pwrite_lvar_type_2(&(*_Lf_67)._Ffarg_v[_Lj_68]._Fdecl, (_Mglc_Elvar)(_Lj_68));
continue_19:;
_Lj_68++;
}
break_19:;
fprintf(_Gout, ") {\n");
_Mglc_Sstmt_space_Pwrite_1(&(*_Lf_67)._Fstmt_space);
fprintf(_Gout, "}\n");
continue_18:;
_Li_65++;
}
break_18:;
return 0;
}
void qalloc_undo(int32_t _Lsize_0) {
if(sizeof(void*) == 8) {
_Lsize_0 = ((_Lsize_0 + 7) & (-1 ^ 7));
} else {
_Lsize_0 = ((_Lsize_0 + 3) & (-1 ^ 3));
}
_Gquick_alloc_c -= _Lsize_0;
}
void _Mglc_Pquick_alloc_init_0() {
_Gquick_alloc_cap = (16 * 1024);
_Gquick_alloc_v = malloc(_Gquick_alloc_cap);
memset(_Gquick_alloc_v, 0, _Gquick_alloc_cap);
}
void _Mglc_Sat_Pinit_4(struct _Mglc_Sat* _Lat_0, _Mglc_Ename_type _Ltype_1, _Mglc_Eat _Lparent_2, _Mglc_Eid _Lname_3) {
(*_Lat_0)._Ftype = _Ltype_1;
(*_Lat_0)._Fparent = _Lparent_2;
(*_Lat_0)._Fname._Fid = _Lname_3;
(*_Lat_0)._Ffunc_c = 0;
(*_Lat_0)._Ffunc_cap = 0;
(*_Lat_0)._Ffunc_v = NULL;
(*_Lat_0)._Fgvar_c = 0;
(*_Lat_0)._Fgvar_cap = 0;
(*_Lat_0)._Fgvar_v = NULL;
(*_Lat_0)._Fdecl._Fstruct = _Mglc_Estruct_Cnil;
}
void _Mglc_Pread_1(char* _Lin_path_0) {
_Mstdc_Efile _Lin_fd_1;
size_t _Lin_size_2;
union _Mglc_Srdr _Lr_begin_3;
_Mglc_Efile _Lfile_idx_4;
struct _Mglc_Sfile* _Lfile_6;
union _Mglc_Srdr _Lr_7;
_Mglc_Eenum _Lenum_c_50;
_Mglc_Eenum _Le_idx_begin_51;
_Mglc_Estruct _Lstruct_c_57;
_Mglc_Estruct _Ls_idx_begin_58;
_Mglc_Efunc _Lfunc_c_67;
_Mglc_Efunc _Lf_idx_begin_68;
_Mglc_Efunc _Lfunc_main_84;
if(!(_Mstdc_Efile_Popen_3(&_Lin_fd_1, _Lin_path_0, O_RDONLY))) {
fprintf(stdout, "Cannot open file for reading: %s\n", _Lin_path_0);
exit(_Mstdc_Eexit_Cfailure);
}
_Lin_size_2 = lseek(_Lin_fd_1, 0, SEEK_END);
_Lr_begin_3._Fref = malloc(_Lin_size_2);
lseek(_Lin_fd_1, 0, SEEK_SET);
read(_Lin_fd_1, _Lr_begin_3._Fref, _Lin_size_2);
close(_Lin_fd_1);
_Lfile_idx_4 = _Gfile_c++;
if(_Gfile_cap <= _Gfile_c) {
_Mglc_Efile _Lold_cap_5;
_Lold_cap_5 = _Gfile_cap;
_Mglc_Pgrow_2(_Gfile_cap, _Gfile_c);
_Mglc_Prealloc_3(_Gfile_v, _Gfile_cap, _Lold_cap_5);
}
_Lfile_6 = (&_Gfile_v[_Lfile_idx_4]);
(*_Lfile_6)._Fpath = _Lin_path_0;
(*_Lfile_6)._Fdata = _Lr_begin_3._Fref;
_Lr_7._Fref = _Lr_begin_3._Fref;
if(true) {
uint32_t _Lid_c_8;
_Lid_c_8 = Fgetnum(&_Lr_7);
_Mglc_Pquick_alloc_arr_2(_Gid_table, _Lid_c_8);
(*_Lfile_6)._Fid_table = _Gid_table;
int32_t _Li_9;
_Li_9 = 0;
for(int i = _Lid_c_8; i > 0; ) {
i --;
uint8_t _Lid_len_10;
char* _Lid_str_11;
_Lid_len_10 = _Mglc_Srdr_Pn1_1(&_Lr_7);
_Lid_str_11 = _Lr_7._Fchar;
_Lr_7._Fpos += (_Lid_len_10 + 1);
_Gid_table[_Li_9] = _Mglc_Pid_add_2(_Lid_len_10, _Lid_str_11);
continue_0:;
_Li_9++;
}
break_0:;
}
if(true) {
uint32_t _Linclude_c_12;
_Linclude_c_12 = Fgetnum(&_Lr_7);
if(_Ginclude_table_cap <= _Linclude_c_12) {
int32_t _Lold_cap_13;
_Lold_cap_13 = _Ginclude_table_cap;
_Mglc_Pgrow_2(_Ginclude_table_cap, _Linclude_c_12);
_Mglc_Prealloc_3(_Ginclude_table, _Ginclude_table_cap, _Lold_cap_13);
}
int32_t _Li_14;
_Li_14 = 0;
for(int i = _Linclude_c_12; i > 0; ) {
i --;
uint8_t _Linclude_len_15;
void* _Linclude_str_16;
int32_t _Lfound_17;
_Linclude_len_15 = _Mglc_Srdr_Pn1_1(&_Lr_7);
_Linclude_str_16 = _Lr_7._Fref;
_Lr_7._Fpos += (_Linclude_len_15 + 1);
_Lfound_17 = _Mglc_Smap_Pget_or_insert_4(&_Ginclude_map, _Linclude_str_16, _Linclude_len_15, _Ginclude_c);
if(_Lfound_17 == -1) {
int32_t _Linclude_idx_18;
_Linclude_idx_18 = _Ginclude_c++;
if(_Ginclude_cap <= _Ginclude_c) {
int32_t _Lold_cap_19;
_Lold_cap_19 = _Ginclude_cap;
_Mglc_Pgrow_2(_Ginclude_cap, _Ginclude_c);
_Mglc_Prealloc_3(_Ginclude_len_v, _Ginclude_cap, _Lold_cap_19);
_Mglc_Prealloc_3(_Ginclude_str_v, _Ginclude_cap, _Lold_cap_19);
}
_Ginclude_len_v[_Linclude_idx_18] = _Linclude_len_15;
_Ginclude_str_v[_Linclude_idx_18] = _Linclude_str_16;
_Ginclude_table[_Li_14] = (_Mglc_Einclude)(_Linclude_idx_18);
} else {
_Ginclude_table[_Li_14] = (_Mglc_Einclude)(_Lfound_17);
}
continue_1:;
_Li_14++;
}
break_1:;
}
if(true) {
uint32_t _Lat_c_20;
_Mglc_Ename_type _Lat_type_21;
_Lat_c_20 = Fgetnum(&_Lr_7);
_Mglc_Pquick_alloc_arr_2(_Gat_table, _Lat_c_20);
(*_Lfile_6)._Fat_table = _Gat_table;
int32_t _Li_22;
_Li_22 = 0;
for(int i = _Lat_c_20; i > 0; ) {
i --;
_Mglc_Ename_type_Prd_2(&_Lat_type_21, &_Lr_7);
if(_Lat_type_21 == _Mglc_Ename_type_Cbasic) {
_Mglc_Ebasic_type_id _Lbasic_23;
_Mglc_Ebasic_type_id_Prd_2(&_Lbasic_23, &_Lr_7);
_Gat_table[_Li_22] = _Mglc_Pbasic_type_1(_Lbasic_23);
} else {
_Mglc_Eat _Lat_parent_24;
_Mglc_Eid _Lat_name_25;
int32_t _Lfound_26;
_Mglc_Eat_Prd_2(&_Lat_parent_24, &_Lr_7);
_Mglc_Eid_Prd_2(&_Lat_name_25, &_Lr_7);
_Lfound_26 = -1;
int32_t _Lj_27;
_Lj_27 = 0;
for(int i = _Gat_c; i > 0; ) {
i --;
struct _Mglc_Sat* _Lat_28;
_Lat_28 = (&_Gat_v[_Lj_27]);
if((((*_Lat_28)._Fparent == _Lat_parent_24) && ((*_Lat_28)._Ftype == _Lat_type_21) && ((*_Lat_28)._Fname._Fid == _Lat_name_25))) {
_Lfound_26 = _Lj_27;
goto break_3;
}
continue_3:;
_Lj_27++;
}
break_3:;
if(_Lfound_26 == -1) {
_Mglc_Eat _Lat_idx_29;
struct _Mglc_Sat* _Lat_31;
_Lat_idx_29 = _Gat_c++;
if(_Gat_cap <= _Gat_c) {
_Mglc_Eat _Lold_cap_30;
_Lold_cap_30 = _Gat_cap;
_Mglc_Pgrow_2(_Gat_cap, _Gat_c);
_Mglc_Prealloc_3(_Gat_v, _Gat_cap, _Lold_cap_30);
}
_Lat_31 = (&_Gat_v[_Lat_idx_29]);
_Mglc_Sat_Pinit_4(_Lat_31, _Lat_type_21, _Lat_parent_24, _Lat_name_25);
_Gat_table[_Li_22] = (_Mglc_Eat)(_Lat_idx_29);
} else {
_Gat_table[_Li_22] = (_Mglc_Eat)(_Lfound_26);
}
}
continue_2:;
_Li_22++;
}
break_2:;
}
if(true) {
_Mglc_Ecvar _Lcvar_c_32;
_Mglc_Ecvar _Lcvar_begin_33;
_Lcvar_c_32 = (_Mglc_Ecvar)(Fgetnum(&_Lr_7));
_Mglc_Pquick_alloc_arr_2(_Gcvar_table, _Lcvar_c_32);
(*_Lfile_6)._Fcvar_table = _Gcvar_table;
fflush(stdout);
_Lcvar_begin_33 = _Gcvar_c;
_Gcvar_c += _Lcvar_c_32;
if(_Gcvar_cap <= _Gcvar_c) {
_Mglc_Ecvar _Lold_cap_34;
_Lold_cap_34 = _Gcvar_cap;
_Mglc_Pgrow_2(_Gcvar_cap, _Gcvar_c);
_Mglc_Prealloc_3(_Gcvar_v, _Gcvar_cap, _Lold_cap_34);
}
_Mglc_Ecvar _Lcvar_idx_35;
int32_t _Li_36;
_Lcvar_idx_35 = _Lcvar_begin_33;
_Li_36 = 0;
for(int i = _Lcvar_c_32; i > 0; ) {
i --;
struct _Mglc_Scvar* _Lcvar_37;
struct _Mglc_Sat* _Lat_38;
int32_t _Lat_cvar_idx_39;
_Lcvar_37 = (&_Gcvar_v[_Lcvar_idx_35]);
(*_Lcvar_37)._Ffile = _Lfile_idx_4;
_Mglc_Einclude_Prd_2(&(*_Lcvar_37)._Finclude, &_Lr_7);
_Mglc_Eat_Prd_2(&(*_Lcvar_37)._Fat, &_Lr_7);
_Mglc_Sdecl_var_Prd_2(&(*_Lcvar_37)._Fdecl, &_Lr_7);
_Mglc_Ecvar_flags_Prd_2(&(*_Lcvar_37)._Fflags, &_Lr_7);
_Lat_38 = _Mglc_Eat_Pptr_1((*_Lcvar_37)._Fat);
_Lat_cvar_idx_39 = (*_Lat_38)._Fcvar_c++;
if((*_Lat_38)._Fcvar_cap <= (*_Lat_38)._Fcvar_c) {
int32_t _Lold_cap_40;
_Lold_cap_40 = (*_Lat_38)._Fcvar_cap;
_Mglc_Pgrow_2((*_Lat_38)._Fcvar_cap, (*_Lat_38)._Fcvar_c);
_Mglc_Prealloc_3((*_Lat_38)._Fcvar_v, (*_Lat_38)._Fcvar_cap, _Lold_cap_40);
}
(*_Lat_38)._Fcvar_v[_Lat_cvar_idx_39] = _Lcvar_idx_35;
if(((*_Lcvar_37)._Fflags & _Mglc_Ecvar_flags_Cset_expr) != _Mglc_Ecvar_flags_C0) {
_Mglc_Eexpr_Prd_2(&(*_Lcvar_37)._Fexpr_set, &_Lr_7);
} else {
_Mglc_Ecvar_Prd_2(&(*_Lcvar_37)._Flast_cvar, &_Lr_7);
}
_Gcvar_table[_Li_36] = _Lcvar_idx_35;
continue_4:;
_Lcvar_idx_35++;
_Li_36++;
}
break_4:;
}
if(true) {
_Mglc_Egvar _Lgvar_c_41;
_Mglc_Egvar _Lgvar_begin_42;
_Lgvar_c_41 = (_Mglc_Egvar)(Fgetnum(&_Lr_7));
fflush(stdout);
_Lgvar_begin_42 = _Ggvar_c;
_Ggvar_c += _Lgvar_c_41;
if(_Ggvar_cap <= _Ggvar_c) {
_Mglc_Egvar _Lold_cap_43;
_Lold_cap_43 = _Ggvar_cap;
_Mglc_Pgrow_2(_Ggvar_cap, _Ggvar_c);
_Mglc_Prealloc_3(_Ggvar_v, _Ggvar_cap, _Lold_cap_43);
}
_Mglc_Egvar _Lgvar_idx_44;
int32_t _Li_45;
_Lgvar_idx_44 = _Lgvar_begin_42;
_Li_45 = 0;
for(int i = _Lgvar_c_41; i > 0; ) {
i --;
struct _Mglc_Sdecl_gvar* _Lgvar_46;
struct _Mglc_Sat* _Lat_47;
int32_t _Lat_gvar_idx_48;
_Lgvar_46 = (&_Ggvar_v[_Lgvar_idx_44]);
_Mglc_Einclude_Prd_2(&(*_Lgvar_46)._Finclude, &_Lr_7);
_Mglc_Eat_Prd_2(&(*_Lgvar_46)._Fat, &_Lr_7);
_Mglc_Sdecl_var_Prd_2(&(*_Lgvar_46)._Fdecl, &_Lr_7);
_Lat_47 = _Mglc_Eat_Pptr_1((*_Lgvar_46)._Fat);
_Lat_gvar_idx_48 = (*_Lat_47)._Fgvar_c++;
if((*_Lat_47)._Fgvar_cap <= (*_Lat_47)._Fgvar_c) {
int32_t _Lold_cap_49;
_Lold_cap_49 = (*_Lat_47)._Fgvar_cap;
_Mglc_Pgrow_2((*_Lat_47)._Fgvar_cap, (*_Lat_47)._Fgvar_c);
_Mglc_Prealloc_3((*_Lat_47)._Fgvar_v, (*_Lat_47)._Fgvar_cap, _Lold_cap_49);
}
(*_Lat_47)._Fgvar_v[_Lat_gvar_idx_48] = _Lgvar_idx_44;
continue_5:;
_Lgvar_idx_44++;
_Li_45++;
}
break_5:;
}
_Lenum_c_50 = (_Mglc_Eenum)(Fgetnum(&_Lr_7));
fflush(stdout);
_Le_idx_begin_51 = _Genum_c;
_Genum_c += _Lenum_c_50;
if(_Genum_cap <= _Genum_c) {
_Mglc_Eenum _Lold_cap_52;
_Lold_cap_52 = _Genum_cap;
_Mglc_Pgrow_2(_Genum_cap, _Genum_c);
_Mglc_Prealloc_3(_Genum_v, _Genum_cap, _Lold_cap_52);
}
_Mglc_Eenum _Le_idx_53;
_Le_idx_53 = _Le_idx_begin_51;
for(int i = _Lenum_c_50; i > 0; ) {
i --;
struct _Mglc_Senum* _Le_54;
_Mglc_Eat _Lat_i_55;
struct _Mglc_Sat* _Lat_56;
_Mglc_Pquick_alloc_one_1(_Le_54);
_Genum_v[_Le_idx_53] = _Le_54;
(*_Le_54)._Ffile = _Lfile_idx_4;
(*_Le_54)._Fbegin_row = Fgetnum(&_Lr_7);
(*_Le_54)._Fbegin_col = Fgetnum(&_Lr_7);
(*_Le_54)._Fend_row = Fgetnum(&_Lr_7);
(*_Le_54)._Fend_col = Fgetnum(&_Lr_7);
_Mglc_Einclude_Prd_2(&(*_Le_54)._Finclude, &_Lr_7);
_Mglc_Eat_Prd_2(&(*_Le_54)._Fat, &_Lr_7);
_Mglc_Eat_Prd_2(&(*_Le_54)._Fbase_type, &_Lr_7);
_Mglc_Eenum_flags_Prd_2(&(*_Le_54)._Fflags, &_Lr_7);
_Lat_i_55 = (*_Le_54)._Fat;
_Lat_56 = _Mglc_Eat_Pptr_1(_Lat_i_55);
(*_Lat_56)._Fdecl._Fenum = _Le_idx_53;
if(((*_Le_54)._Fflags & _Mglc_Eenum_flags_Creal_name) != _Mglc_Eenum_flags_C0) {
_Mglc_Eid_Prd_2(&(*_Le_54)._Freal_name, &_Lr_7);
} else {
(*_Le_54)._Freal_name = _Mglc_Eid_Cnil;
}
continue_6:;
_Le_idx_53++;
}
break_6:;
_Lstruct_c_57 = (_Mglc_Estruct)(Fgetnum(&_Lr_7));
_Ls_idx_begin_58 = _Gstruct_c;
_Gstruct_c += _Lstruct_c_57;
if(_Gstruct_cap <= _Gstruct_c) {
_Mglc_Estruct _Lold_cap_59;
_Lold_cap_59 = _Gstruct_cap;
_Mglc_Pgrow_2(_Gstruct_cap, _Gstruct_c);
_Mglc_Prealloc_3(_Gstruct_v, _Gstruct_cap, _Lold_cap_59);
}
_Mglc_Estruct _Ls_idx_60;
_Ls_idx_60 = _Ls_idx_begin_58;
for(int i = _Lstruct_c_57; i > 0; ) {
i --;
uint8_t _Lfvar_c_61;
struct _Mglc_Sstruct* _Ls_62;
_Mglc_Eat _Lat_i_63;
struct _Mglc_Sat* _Lat_64;
_Lfvar_c_61 = _Mglc_Srdr_Pn1_1(&_Lr_7);
_Mglc_Pquick_alloc_plus_2(_Ls_62, sizeof(struct _Mglc_Sfvar) * _Lfvar_c_61);
_Gstruct_v[_Ls_idx_60] = _Ls_62;
(*_Ls_62)._Ffile = _Lfile_idx_4;
(*_Ls_62)._Ffvar_c = _Lfvar_c_61;
(*_Ls_62)._Fbegin_row = Fgetnum(&_Lr_7);
(*_Ls_62)._Fbegin_col = Fgetnum(&_Lr_7);
(*_Ls_62)._Fend_row = Fgetnum(&_Lr_7);
(*_Ls_62)._Fend_col = Fgetnum(&_Lr_7);
_Mglc_Einclude_Prd_2(&(*_Ls_62)._Finclude, &_Lr_7);
_Mglc_Eat_Prd_2(&(*_Ls_62)._Fat, &_Lr_7);
_Mglc_Estruct_flags_Prd_2(&(*_Ls_62)._Fflags, &_Lr_7);
_Lat_i_63 = (*_Ls_62)._Fat;
_Lat_64 = _Mglc_Eat_Pptr_1(_Lat_i_63);
(*_Lat_64)._Fdecl._Fstruct = _Ls_idx_60;
int32_t _Lj_65;
_Lj_65 = 0;
for(int i = _Lfvar_c_61; i > 0; ) {
i --;
struct _Mglc_Sfvar* _Lfvar_66;
_Lfvar_66 = (&(*_Ls_62)._Ffvar_v[_Lj_65]);
_Mglc_Sdecl_var_Prd_2(&(*_Lfvar_66)._Fdecl, &_Lr_7);
continue_8:;
_Lj_65++;
}
break_8:;
if(((*_Ls_62)._Fflags & _Mglc_Estruct_flags_Creal_name) != _Mglc_Estruct_flags_C0) {
_Mglc_Eid_Prd_2(&(*_Ls_62)._Freal_name, &_Lr_7);
} else {
(*_Ls_62)._Freal_name = _Mglc_Eid_Cnil;
}
continue_7:;
_Ls_idx_60++;
}
break_7:;
_Lfunc_c_67 = (_Mglc_Efunc)(Fgetnum(&_Lr_7));
fflush(stdout);
_Lf_idx_begin_68 = _Gfunc_c;
_Gfunc_c += _Lfunc_c_67;
if(_Gfunc_cap <= _Gfunc_c) {
_Mglc_Efunc _Lold_cap_69;
_Lold_cap_69 = _Gfunc_cap;
_Mglc_Pgrow_2(_Gfunc_cap, _Gfunc_c);
_Mglc_Prealloc_3(_Gfunc_v, _Gfunc_cap, _Lold_cap_69);
}
_Mglc_Efunc _Lf_idx_70;
_Lf_idx_70 = _Lf_idx_begin_68;
for(int i = _Lfunc_c_67; i > 0; ) {
i --;
uint8_t _Lfarg_c_71;
struct _Mglc_Sdecl_func* _Lf_72;
union _Mglc_Srdr _Lr0_73;
int8_t _Lthis_idx_76;
uint8_t _Lgroup_c_77;
_Mglc_Eat _Lat_i_80;
struct _Mglc_Sat* _Lat_81;
int32_t _Lat_func_idx_82;
_Lfarg_c_71 = _Mglc_Srdr_Pn1_1(&_Lr_7);
_Mglc_Pquick_alloc_plus_2(_Lf_72, sizeof(struct _Mglc_Sfarg) * _Lfarg_c_71);
_Gfunc_v[_Lf_idx_70] = _Lf_72;
(*_Lf_72)._Ffarg_c = _Lfarg_c_71;
(*_Lf_72)._Ffile = _Lfile_idx_4;
(*_Lf_72)._Fbegin_row = Fgetnum(&_Lr_7);
(*_Lf_72)._Fbegin_col = Fgetnum(&_Lr_7);
(*_Lf_72)._Fend_row = Fgetnum(&_Lr_7);
(*_Lf_72)._Fend_col = Fgetnum(&_Lr_7);
_Mglc_Einclude_Prd_2(&(*_Lf_72)._Finclude, &_Lr_7);
_Mglc_Eat_Prd_2(&(*_Lf_72)._Fat, &_Lr_7);
_Mglc_Sdecl_var_Prd_2(&(*_Lf_72)._Fdecl, &_Lr_7);
_Lr0_73._Fref = _Lf_72;
(*_Lf_72)._Flvar_c = _Mglc_Elvar_C0;
_Gctx_func = _Lf_72;
_Gctx_func_id = _Lf_idx_70;
int32_t _Lj_74;
_Lj_74 = 0;
for(int i = _Lfarg_c_71; i > 0; ) {
i --;
struct _Mglc_Sfarg* _Lfarg_75;
_Lfarg_75 = (&(*_Lf_72)._Ffarg_v[_Lj_74]);
_Mglc_Sfarg_Prd_2(_Lfarg_75, &_Lr_7);
continue_10:;
_Lj_74++;
}
break_10:;
_Lthis_idx_76 = (int8_t)(_Mglc_Srdr_Pn1_1(&_Lr_7));
(*_Lf_72)._Fthis_idx = _Lthis_idx_76;
if(_Lthis_idx_76 != -1) {
(*_Lf_72)._Fthis_group = _Mglc_Srdr_Pn1_1(&_Lr_7);
}
_Lgroup_c_77 = _Mglc_Srdr_Pn1_1(&_Lr_7);
(*_Lf_72)._Fgroup_c = _Lgroup_c_77;
int32_t _Li_78;
_Li_78 = 0;
for(int i = _Lgroup_c_77; i > 0; ) {
i --;
(*_Lf_72)._Fgroup_v[_Li_78] = _Mglc_Srdr_Pn1_1(&_Lr_7);
continue_11:;
_Li_78++;
}
break_11:;
_Mglc_Efunc_flags_Prd_2(&(*_Lf_72)._Fflags, &_Lr_7);
if(((*_Lf_72)._Fflags & _Mglc_Efunc_flags_Creal_name) != _Mglc_Efunc_flags_C0) {
_Mglc_Eid_Prd_2(&(*_Lf_72)._Freal_name, &_Lr_7);
}
if(((*_Lf_72)._Fflags & _Mglc_Efunc_flags_Ccase) != _Mglc_Efunc_flags_C0) {
_Mglc_Eid_Prd_2(&(*_Lf_72)._Fcase, &_Lr_7);
}
if(((*_Lf_72)._Fflags & _Mglc_Efunc_flags_Cdecl) != _Mglc_Efunc_flags_C0) {
uint32_t _Llen_79;
_Llen_79 = Fgetnum(&_Lr_7);
(*_Lf_72)._Fdecl_len = _Llen_79;
(*_Lf_72)._Fdecl_str = qalloc(_Llen_79 + 1);
memcpy((*_Lf_72)._Fdecl_str, _Lr_7._Fref, _Llen_79);
(*_Lf_72)._Fdecl_str[_Llen_79] = 0;
_Lr_7._Fpos += _Llen_79;
}
_Lat_i_80 = (*_Lf_72)._Fat;
_Lat_81 = _Mglc_Eat_Pptr_1(_Lat_i_80);
_Lat_func_idx_82 = (*_Lat_81)._Ffunc_c++;
if((*_Lat_81)._Ffunc_cap <= (*_Lat_81)._Ffunc_c) {
int32_t _Lold_cap_83;
_Lold_cap_83 = (*_Lat_81)._Ffunc_cap;
_Mglc_Pgrow_2((*_Lat_81)._Ffunc_cap, (*_Lat_81)._Ffunc_c);
_Mglc_Prealloc_3((*_Lat_81)._Ffunc_v, (*_Lat_81)._Ffunc_cap, _Lold_cap_83);
}
(*_Lat_81)._Ffunc_v[_Lat_func_idx_82] = _Lf_idx_70;
continue_9:;
_Lf_idx_70++;
}
break_9:;
_Mglc_Efunc_Prd_2(&_Lfunc_main_84, &_Lr_7);
if(_Lfunc_main_84 != _Mglc_Efunc_Cnil) {
if(_Gfunc_main != _Mglc_Efunc_Cnil) {
struct _Mglc_Sdecl_func* _Lfirst_85;
struct _Mglc_Sdecl_func* _Lsecond_86;
_Lfirst_85 = _Mglc_Efunc_Pptr_1(_Gfunc_main);
_Lsecond_86 = _Mglc_Efunc_Pptr_1(_Lfunc_main_84);
fprintf(stdout, "There are more than one function with @main attribute, first is %u:%u and second is %u:%u\n", (*_Lfirst_85)._Fbegin_row, (*_Lfirst_85)._Fbegin_col, (*_Lsecond_86)._Fbegin_row, (*_Lsecond_86)._Fbegin_col);
exit(_Mstdc_Eexit_Cfailure);
}
_Gfunc_main = _Lfunc_main_84;
}
_Mglc_Efunc _Lf_idx_87;
_Lf_idx_87 = _Lf_idx_begin_68;
for(int i = _Lfunc_c_67; i > 0; ) {
i --;
struct _Mglc_Sdecl_func* _Lf_88;
uint32_t _Lsize_89;
_Lf_88 = _Gfunc_v[_Lf_idx_87];
if(((*_Lf_88)._Fflags & _Mglc_Efunc_flags_Chas_body) == _Mglc_Efunc_flags_C0) {
goto continue_12;
}
_Lsize_89 = _Mglc_Srdr_Pn4_1(&_Lr_7);
(*_Lf_88)._Fbody_file_pos = (_Lr_7._Fpos - _Lr_begin_3._Fpos);
_Lr_7._Fpos += _Lsize_89;
continue_12:;
_Lf_idx_87++;
}
break_12:;
}
struct _Mglc_Sdecl_func* _Mglc_Efunc_Pptr_1(_Mglc_Efunc _Lf_0) {
return _Gfunc_v[_Lf_0];
}
struct _Mglc_Sat* _Mglc_Eat_Pptr_1(_Mglc_Eat _Li_0) {
return &_Gat_v[_Li_0];
}
char* _Mglc_Efile_Ppath_1(_Mglc_Efile _Lf_0) {
return (*_Mglc_Efile_Pptr_1(_Lf_0))._Fpath;
}
char* _Mglc_Eid_Pstr_1(_Mglc_Eid _Lid_0) {
return _Gid_str_v[_Lid_0];
}
struct _Mglc_Sstruct* _Mglc_Estruct_Pptr_1(_Mglc_Estruct _Ls_0) {
return _Gstruct_v[_Ls_0];
}
struct _Mglc_Senum* _Mglc_Eenum_Pptr_1(_Mglc_Eenum _Lf_0) {
return _Genum_v[_Lf_0];
}
_Mglc_Eid _Mglc_Pid_add_2(uint8_t _Lid_len_0, char* _Lid_str_1) {
int32_t _Lfound_2;
int32_t _Lid_idx_3;
_Lfound_2 = _Mglc_Smap_Pget_or_insert_4(&_Gid_map, _Lid_str_1, _Lid_len_0, _Gid_c);
if(_Lfound_2 != -1) {
return _Lfound_2;
}
_Lid_idx_3 = _Gid_c++;
if(_Gid_cap <= _Gid_c) {
int32_t _Lold_cap_4;
_Lold_cap_4 = _Gid_cap;
_Mglc_Pgrow_2(_Gid_cap, _Gid_c);
_Mglc_Prealloc_3(_Gid_len_v, _Gid_cap, _Lold_cap_4);
_Mglc_Prealloc_3(_Gid_str_v, _Gid_cap, _Lold_cap_4);
}
_Gid_len_v[_Lid_idx_3] = _Lid_len_0;
_Gid_str_v[_Lid_idx_3] = _Lid_str_1;
return _Lid_idx_3;
}
void _Mglc_Efunc_Pprocess_later_1(_Mglc_Efunc _Lf_idx_0) {
uint32_t _Lnum_1;
uint32_t _Ln3_2;
int32_t _Ln17_3;
struct _Mglc_Sdecl_func* _Lf_4;
_Lnum_1 = (uint32_t)(_Lf_idx_0);
_Ln3_2 = (_Lnum_1 >> 3);
_Ln17_3 = (1 << (_Lnum_1 & 7));
if((_Gfunc_in_process[_Ln3_2] & _Ln17_3) != 0) {
return;
}
_Gfunc_in_process[_Ln3_2] |= _Ln17_3;
_Lf_4 = _Mglc_Efunc_Pptr_1(_Lf_idx_0);
if((*_Lf_4)._Fdecl._Ftype != _Mglc_Eat_Cnil) {
_Mglc_Eat_Pfinalize_4((*_Lf_4)._Fdecl._Ftype, &(*_Lf_4)._Fdecl._Ftype_info, (*_Lf_4)._Fbegin_row, (*_Lf_4)._Fbegin_col);
}
_Gfunc_head_outputted_v[_Gfunc_head_outputted_c++] = _Lf_idx_0;
if(((*_Lf_4)._Fflags & _Mglc_Efunc_flags_Chas_body) != _Mglc_Efunc_flags_C0) {
(*_Lf_4)._Fprocess_next = _Mglc_Efunc_Cnil;
if(_Gprocess_first == _Mglc_Efunc_Cnil) {
_Gprocess_first = _Lf_idx_0;
_Gprocess_last = _Lf_idx_0;
} else {
struct _Mglc_Sdecl_func* _Lf_last_5;
_Lf_last_5 = _Mglc_Efunc_Pptr_1(_Gprocess_last);
(*_Lf_last_5)._Fprocess_next = _Lf_idx_0;
_Gprocess_last = _Lf_idx_0;
}
}
}
bool _Mglc_Efunc_Pprocess_now_1(_Mglc_Efunc _Lf_idx_0) {
struct _Mglc_Sdecl_func* _Lf_1;
union _Mglc_Srdr _Lr_2;
struct _Mglc_Sfile* _Lfile_3;
struct _Mglc_Sstmt* _Ls_4;
_Lf_1 = _Mglc_Efunc_Pptr_1(_Lf_idx_0);
_Gctx_func = _Lf_1;
_Lfile_3 = _Mglc_Efile_Pptr_1((*_Lf_1)._Ffile);
_Lr_2._Fref = (*_Lfile_3)._Fdata;
_Gid_table = (*_Lfile_3)._Fid_table;
_Gat_table = (*_Lfile_3)._Fat_table;
_Gcvar_table = (*_Lfile_3)._Fcvar_table;
_Lr_2._Fpos += (*_Lf_1)._Fbody_file_pos;
_Mglc_Sdecl_func_Plvars_rd_2(_Lf_1, &_Lr_2);
_Mglc_Sstmt_space_Prd_3(&(*_Lf_1)._Fstmt_space, &_Lr_2, NULL);
_Ls_4 = (*_Lf_1)._Fstmt_space._Fstmt_first;
while(_Ls_4 != NULL) {
_Gctx_begin_row = (*_Ls_4)._Fbegin_row;
_Gctx_begin_col = (*_Ls_4)._Fbegin_col;
_Gctx_end_row = (*_Ls_4)._Fend_row;
_Gctx_end_col = (*_Ls_4)._Fend_col;
if(!(_Mglc_Sstmt_Pprocess_1(_Ls_4))) {
return false;
}
_Ls_4 = (*_Ls_4)._Fstmt_next;
continue_0:;
}
break_0:;
if(((*_Lf_1)._Fflags & _Mglc_Efunc_flags_Cno_body) == _Mglc_Efunc_flags_C0) {
_Gfunc_body_outputted_v[_Gfunc_body_outputted_c++] = _Lf_idx_0;
}
return true;
}
void _Mglc_Eat_Poutput_4(_Mglc_Eat _Lat_i_0, _Mglc_Efile _Lfile_1, int32_t _Lrow_2, int32_t _Lcol_3) {
struct _Mglc_Sat* _Lat_4;
_Lat_4 = _Mglc_Eat_Pptr_1(_Lat_i_0);
switch((*_Lat_4)._Ftype) {
case _Mglc_Ename_type_Cstruct:;
if((*_Lat_4)._Fdecl._Fstruct == _Mglc_Estruct_Cnil) {
fprintf(stdout, "%s:%u:%u: Error, struct '/%s' was not defined\n", _Mglc_Efile_Ppath_1(_Lfile_1), _Lrow_2, _Lcol_3, _Mglc_Eid_Pstr_1((*_Lat_4)._Fname._Fid));
exit(_Mstdc_Eexit_Cfailure);
}
_Mglc_Estruct_Poutput_1((*_Lat_4)._Fdecl._Fstruct);
break;
case _Mglc_Ename_type_Cenum:;
if((*_Lat_4)._Fdecl._Fenum == _Mglc_Eenum_Cnil) {
fprintf(stdout, "%s:%u:%u: Error, enum '\\%s' was not defined\n", _Mglc_Efile_Ppath_1(_Lfile_1), _Lrow_2, _Lcol_3, _Mglc_Eid_Pstr_1((*_Lat_4)._Fname._Fid));
exit(_Mstdc_Eexit_Cfailure);
}
_Mglc_Eenum_Poutput_1((*_Lat_4)._Fdecl._Fenum);
break;
case _Mglc_Ename_type_Cbasic:;
switch((*_Lat_4)._Fname._Fbasic) {
case _Mglc_Ebasic_type_id_Cbool:;
_Ginclude_stdbool = true;
break;
case _Mglc_Ebasic_type_id_Csize:;
_Ginclude_stddef = true;
break;
}
break;
}
}
void _Mglc_Einclude_Poutput_1(_Mglc_Einclude _Lthis_0) {
uint32_t _Lnum_1;
uint32_t _Ln3_2;
int32_t _Ln17_3;
_Lnum_1 = (uint32_t)(_Lthis_0);
_Ln3_2 = (_Lnum_1 >> 3);
_Ln17_3 = (1 << (_Lnum_1 & 7));
if((_Ginclude_is_outputted[_Ln3_2] & _Ln17_3) != 0) {
return;
}
_Ginclude_is_outputted[_Ln3_2] |= _Ln17_3;
_Ginclude_outputted_v[_Ginclude_outputted_c++] = _Lthis_0;
}
struct _Mglc_Scvar* _Mglc_Ecvar_Pptr_1(_Mglc_Ecvar _Lc_0) {
return &_Gcvar_v[_Lc_0];
}
bool _Mglc_Ecvar_Pprocess_1(_Mglc_Ecvar _Lc_0) {
uint32_t _Lnum_1;
uint32_t _Ln3_2;
int32_t _Ln17_3;
struct _Mglc_Scvar* _Lcvar_4;
_Mglc_Eat _Lat_i_5;
_Lnum_1 = (uint32_t)(_Lc_0);
_Ln3_2 = (_Lnum_1 >> 3);
_Ln17_3 = (1 << (_Lnum_1 & 7));
if((_Gcvar_is_outputted[_Ln3_2] & _Ln17_3) != 0) {
return true;
}
_Gcvar_is_outputted[_Ln3_2] |= _Ln17_3;
_Lcvar_4 = _Mglc_Ecvar_Pptr_1(_Lc_0);
if(((*_Lcvar_4)._Fflags & _Mglc_Ecvar_flags_Cset_expr) != _Mglc_Ecvar_flags_C0) {
if(!(_Mglc_Eexpr_Pprocess_1((*_Lcvar_4)._Fexpr_set))) {
return false;
}
} else if((*_Lcvar_4)._Flast_cvar != _Mglc_Ecvar_Cnil) {
if(!(_Mglc_Ecvar_Pprocess_1((*_Lcvar_4)._Flast_cvar))) {
return false;
}
}
_Lat_i_5 = (*_Lcvar_4)._Fdecl._Ftype;
if(_Lat_i_5 != _Mglc_Eat_Cnil) {
struct _Mglc_Sat* _Lat_6;
_Lat_6 = _Mglc_Eat_Pptr_1(_Lat_i_5);
if((((*_Lat_6)._Ftype != _Mglc_Ename_type_Cbasic) && ((*_Lat_6)._Fdecl._Fstruct == _Mglc_Estruct_Cnil))) {
fprintf(stdout, "Error, the type '%s' used in cvar '.%s' was not defined\n", _Mglc_Eid_Pstr_1((*_Lat_6)._Fname._Fid), _Mglc_Eid_Pstr_1((*_Lcvar_4)._Fdecl._Fname));
return false;
}
_Mglc_Eat_Poutput_4(_Lat_i_5, (*_Lcvar_4)._Ffile, (*_Lcvar_4)._Frow, (*_Lcvar_4)._Fcol);
}
_Gcvar_outputted_v[_Gcvar_outputted_c++] = _Lc_0;
return true;
}
char* _Mglc_Einclude_Pstr_1(_Mglc_Einclude _Li_0) {
return _Ginclude_str_v[_Li_0];
}
void _Mglc_Ecvar_Pwrite_1(_Mglc_Ecvar _Lc_0) {
struct _Mglc_Scvar* _Lcvar_1;
_Lcvar_1 = _Mglc_Ecvar_Pptr_1(_Lc_0);
if(((*_Lcvar_1)._Fdecl._Fflags & _Mglc_Evar_flags_Creal_name) != _Mglc_Evar_flags_C0) {
fprintf(_Gout, "%s", _Mglc_Eid_Pstr_1((*_Lcvar_1)._Fdecl._Freal_name));
} else {
_Mglc_Eat_Pwrite_space_1((*_Lcvar_1)._Fat);
fprintf(_Gout, "_C%s", _Mglc_Eid_Pc_name_1((*_Lcvar_1)._Fdecl._Fname));
}
}
void _Mglc_Eexpr_Pwrite_1(_Mglc_Eexpr _Le_0) {
struct _Mglc_Sexpr* _Lexpr_1;
_Lexpr_1 = _Mglc_Eexpr_Pptr_1(_Le_0);
switch((*_Lexpr_1)._Ftype) {
case _Mglc_Eexpr_type_Cassign:;
_Mglc_Eexpr_Pwrite_assign_1(_Lexpr_1);
break;
case _Mglc_Eexpr_type_Ccompare:;
_Mglc_Eexpr_Pwrite_compare_1(_Lexpr_1);
break;
case _Mglc_Eexpr_type_Cbool:;
_Mglc_Eexpr_Pwrite_bool_1(_Lexpr_1);
break;
case _Mglc_Eexpr_type_Cchar:;
_Mglc_Eexpr_Pwrite_char_1(_Lexpr_1);
break;
case _Mglc_Eexpr_type_Cmath:;
_Mglc_Eexpr_Pwrite_math_1(_Lexpr_1);
break;
case _Mglc_Eexpr_type_Cunary:;
_Mglc_Eexpr_Pwrite_unary_1(_Lexpr_1);
break;
case _Mglc_Eexpr_type_Cref:;
_Mglc_Eexpr_Pwrite_ref_1(_Lexpr_1);
break;
case _Mglc_Eexpr_type_Clvar:;
_Mglc_Eexpr_Pwrite_lvar_1(_Lexpr_1);
break;
case _Mglc_Eexpr_type_Cfvar:;
_Mglc_Eexpr_Pwrite_fvar_1(_Lexpr_1);
break;
case _Mglc_Eexpr_type_Cgvar:;
_Mglc_Eexpr_Pwrite_gvar_1(_Lexpr_1);
break;
case _Mglc_Eexpr_type_Ccvar:;
_Mglc_Eexpr_Pwrite_cvar_1(_Lexpr_1);
break;
case _Mglc_Eexpr_type_Cbools:;
_Mglc_Eexpr_Pwrite_bools_1(_Lexpr_1);
break;
case _Mglc_Eexpr_type_Cmethod:;
_Mglc_Eexpr_Pwrite_method_1(_Lexpr_1);
break;
case _Mglc_Eexpr_type_Cfunc:;
_Mglc_Eexpr_Pwrite_func_1(_Lexpr_1);
break;
case _Mglc_Eexpr_type_Cstr:;
_Mglc_Eexpr_Pwrite_str_1(_Lexpr_1);
break;
case _Mglc_Eexpr_type_Cint:;
_Mglc_Eexpr_Pwrite_int_1(_Lexpr_1);
break;
case _Mglc_Eexpr_type_Csize_of_type:;
_Mglc_Eexpr_Pwrite_size_of_type_1(_Lexpr_1);
break;
case _Mglc_Eexpr_type_Cnull:;
_Mglc_Eexpr_Pwrite_null_1(_Lexpr_1);
break;
case _Mglc_Eexpr_type_Cindex:;
_Mglc_Eexpr_Pwrite_index_1(_Lexpr_1);
break;
default:;
fprintf(stdout, "%s:%u:%u - %u:%u: :write not implemented in expression #%s\n", _Mglc_Efile_Ppath_1((*_Gctx_func)._Ffile), _Gctx_begin_row, _Gctx_begin_col, _Gctx_end_row, _Gctx_end_col, _Mglc_Eexpr_type_Pglc_name_1((*_Lexpr_1)._Ftype));
break;
}
}
void _Mglc_Eat_Pwrite_1(_Mglc_Eat _Lat_idx_0) {
struct _Mglc_Sat* _Lat_1;
_Lat_1 = _Mglc_Eat_Pptr_1(_Lat_idx_0);
switch((*_Lat_1)._Ftype) {
case _Mglc_Ename_type_Cmodule:;
if((*_Lat_1)._Fparent != _Mglc_Eat_Croot) {
_Mglc_Eat_Pwrite_space_1((*_Lat_1)._Fparent);
}
fprintf(_Gout, "_M%s", _Mglc_Eid_Pc_name_1((*_Lat_1)._Fname._Fid));
break;
case _Mglc_Ename_type_Cstruct:;
_Mglc_Estruct _Lt_idx_2;
struct _Mglc_Sstruct* _Lt_3;
_Lt_idx_2 = (*_Lat_1)._Fdecl._Fstruct;
_Lt_3 = _Mglc_Estruct_Pptr_1(_Lt_idx_2);
if(_Lt_idx_2 != _Mglc_Estruct_Cnil) {
if(((*_Lt_3)._Fflags & _Mglc_Estruct_flags_Creal_name) != _Mglc_Estruct_flags_C0) {
fprintf(_Gout, "%s", _Mglc_Eid_Pstr_1((*_Lt_3)._Freal_name));
return;
}
}
if(((*_Lt_3)._Fflags & _Mglc_Estruct_flags_Cunion) != _Mglc_Estruct_flags_C0) {
fprintf(_Gout, "union ");
} else {
fprintf(_Gout, "struct ");
}
if((*_Lat_1)._Fparent != _Mglc_Eat_Croot) {
_Mglc_Eat_Pwrite_space_1((*_Lat_1)._Fparent);
}
fprintf(_Gout, "_S%s", _Mglc_Eid_Pc_name_1((*_Lat_1)._Fname._Fid));
break;
case _Mglc_Ename_type_Cenum:;
_Mglc_Eenum _Lt_idx_4;
_Lt_idx_4 = (*_Lat_1)._Fdecl._Fenum;
if(_Lt_idx_4 != _Mglc_Eenum_Cnil) {
struct _Mglc_Senum* _Lt_5;
_Lt_5 = _Mglc_Eenum_Pptr_1(_Lt_idx_4);
if(((*_Lt_5)._Fflags & _Mglc_Eenum_flags_Creal_name) != _Mglc_Eenum_flags_C0) {
fprintf(_Gout, "%s", _Mglc_Eid_Pstr_1((*_Lt_5)._Freal_name));
return;
}
}
if((*_Lat_1)._Fparent != _Mglc_Eat_Croot) {
_Mglc_Eat_Pwrite_space_1((*_Lat_1)._Fparent);
}
fprintf(_Gout, "_E%s", _Mglc_Eid_Pc_name_1((*_Lat_1)._Fname._Fid));
break;
case _Mglc_Ename_type_Cbasic:;
switch((*_Lat_1)._Fname._Fbasic) {
case _Mglc_Ebasic_type_id_Cref:;
fprintf(_Gout, "void*");
break;
case _Mglc_Ebasic_type_id_Ctnum:;
fprintf(_Gout, "uint8_t");
break;
case _Mglc_Ebasic_type_id_Ctint:;
fprintf(_Gout, "int8_t");
break;
case _Mglc_Ebasic_type_id_Cint:;
fprintf(_Gout, "int32_t");
break;
case _Mglc_Ebasic_type_id_Cnum:;
fprintf(_Gout, "uint32_t");
break;
case _Mglc_Ebasic_type_id_Clnum:;
fprintf(_Gout, "uint64_t");
break;
case _Mglc_Ebasic_type_id_Cfloat:;
fprintf(_Gout, "float");
break;
case _Mglc_Ebasic_type_id_Cbool:;
fprintf(_Gout, "bool");
break;
case _Mglc_Ebasic_type_id_Cchar:;
fprintf(_Gout, "char");
break;
case _Mglc_Ebasic_type_id_Csize:;
fprintf(_Gout, "size_t");
break;
}
break;
}
}
void _Mglc_Eat_Pwrite_space_1(_Mglc_Eat _Lat_idx_0) {
struct _Mglc_Sat* _Lat_1;
_Lat_1 = _Mglc_Eat_Pptr_1(_Lat_idx_0);
switch((*_Lat_1)._Ftype) {
case _Mglc_Ename_type_Cmodule:;
if((*_Lat_1)._Fparent != _Mglc_Eat_Croot) {
_Mglc_Eat_Pwrite_space_1((*_Lat_1)._Fparent);
}
fprintf(_Gout, "_M%s", _Mglc_Eid_Pc_name_1((*_Lat_1)._Fname._Fid));
break;
case _Mglc_Ename_type_Cstruct:;
if((*_Lat_1)._Fparent != _Mglc_Eat_Croot) {
_Mglc_Eat_Pwrite_space_1((*_Lat_1)._Fparent);
}
fprintf(_Gout, "_S%s", _Mglc_Eid_Pc_name_1((*_Lat_1)._Fname._Fid));
break;
case _Mglc_Ename_type_Cenum:;
if((*_Lat_1)._Fparent != _Mglc_Eat_Croot) {
_Mglc_Eat_Pwrite_space_1((*_Lat_1)._Fparent);
}
fprintf(_Gout, "_E%s", _Mglc_Eid_Pc_name_1((*_Lat_1)._Fname._Fid));
break;
case _Mglc_Ename_type_Cbasic:;
switch((*_Lat_1)._Fname._Fbasic) {
case _Mglc_Ebasic_type_id_Cref:;
fprintf(_Gout, "_Tref");
break;
case _Mglc_Ebasic_type_id_Cint:;
fprintf(_Gout, "_Tint");
break;
case _Mglc_Ebasic_type_id_Cnum:;
fprintf(_Gout, "_Tnum");
break;
case _Mglc_Ebasic_type_id_Cfloat:;
fprintf(_Gout, "_Tfloat");
break;
case _Mglc_Ebasic_type_id_Cbool:;
fprintf(_Gout, "_Tbool");
break;
case _Mglc_Ebasic_type_id_Cchar:;
fprintf(_Gout, "_Tchar");
break;
case _Mglc_Ebasic_type_id_Csize:;
fprintf(_Gout, "_Tsize");
break;
}
break;
}
}
void _Mglc_Sdecl_var_Pwrite_type_2(struct _Mglc_Sdecl_var* _Lvd_0, _Mglc_Edecl_var_type _Lvar_type_1) {
if((*_Lvd_0)._Ftype_info._Fconst) {
fprintf(_Gout, "const ");
}
_Mglc_Eat_Pwrite_type_info_3((*_Lvd_0)._Ftype, &(*_Lvd_0)._Ftype_info, 0 - (*_Lvd_0)._Fsize_c);
fprintf(_Gout, " ");
_Mglc_Sdecl_var_Pwrite_2(_Lvd_0, _Lvar_type_1);
int32_t _Li_2;
_Li_2 = 0;
for(int i = (*_Lvd_0)._Fsize_c; i > 0; ) {
i --;
fprintf(_Gout, "[");
_Mglc_Eexpr_Pwrite_value_2((*_Lvd_0)._Fsize_expr_v[_Li_2], &(*_Lvd_0)._Fsize_value_v[_Li_2]);
fprintf(_Gout, "]");
continue_0:;
_Li_2++;
}
break_0:;
}
struct _Mglc_Sdecl_gvar* _Mglc_Egvar_Pptr_1(_Mglc_Egvar _Lg_0) {
return &_Ggvar_v[_Lg_0];
}
void _Mglc_Sdecl_func_Pwrite_1(struct _Mglc_Sdecl_func* _Lf_0) {
if(((*_Lf_0)._Fflags & _Mglc_Efunc_flags_Creal_name) != _Mglc_Efunc_flags_C0) {
fprintf(_Gout, "%s", _Mglc_Eid_Pstr_1((*_Lf_0)._Freal_name));
} else {
_Mglc_Eat_Pwrite_space_1((*_Lf_0)._Fat);
fprintf(_Gout, "_P%s", _Mglc_Eid_Pc_name_1((*_Lf_0)._Fdecl._Fname));
int32_t _Li_1;
_Li_1 = 0;
for(int i = (*_Lf_0)._Fgroup_c; i > 0; ) {
i --;
fprintf(_Gout, "_%u", (*_Lf_0)._Fgroup_v[_Li_1]);
continue_0:;
_Li_1++;
}
break_0:;
}
}
bool _Mglc_Eat_Pwrite_type_info_3(_Mglc_Eat _Ltd_0, struct _Mglc_Stype_info* _Lti_1, int32_t _Ladd_2) {
int32_t _Ls_3;
_Mglc_Stype_info_Pcount_1(_Lti_1);
_Mglc_Eat_Pwrite_type_1(_Ltd_0);
_Ls_3 = (_Mglc_Eat_Pcount_stars0_2(_Ltd_0, _Lti_1) + _Ladd_2);
if(_Ls_3 > 0) {
_Mstdc_Sfile_Pwrite_3(_Gout, "********************************", _Ls_3);
}
return true;
}
void _Mglc_Sdecl_var_Pwrite_lvar_type_2(struct _Mglc_Sdecl_var* _Lvd_0, _Mglc_Elvar _Llvar_1) {
if((*_Lvd_0)._Ftype_info._Fconst) {
fprintf(_Gout, "const ");
}
_Mglc_Eat_Pwrite_type_info_3((*_Lvd_0)._Ftype, &(*_Lvd_0)._Ftype_info, 0 - (*_Lvd_0)._Fsize_c);
fprintf(_Gout, " ");
_Mglc_Sdecl_var_Pwrite_lvar_2(_Lvd_0, _Llvar_1);
int32_t _Li_2;
_Li_2 = 0;
for(int i = (*_Lvd_0)._Fsize_c; i > 0; ) {
i --;
fprintf(_Gout, "[");
_Mglc_Eexpr_Pwrite_value_2((*_Lvd_0)._Fsize_expr_v[_Li_2], &(*_Lvd_0)._Fsize_value_v[_Li_2]);
fprintf(_Gout, "]");
continue_0:;
_Li_2++;
}
break_0:;
}
void _Mglc_Sstmt_space_Pwrite_1(struct _Mglc_Sstmt_space* _Lspace_0) {
uint8_t _Li_1;
int32_t _Llvar_c_2;
struct _Mglc_Sstmt* _Ls_5;
if((*_Lspace_0)._Fparent == NULL) {
_Li_1 = (*_Gctx_func)._Ffarg_c;
_Llvar_c_2 = ((*_Lspace_0)._Flvar_c - (*_Gctx_func)._Ffarg_c);
} else {
_Li_1 = 0;
_Llvar_c_2 = (*_Lspace_0)._Flvar_c;
}
for(int i = _Llvar_c_2; i > 0; ) {
i --;
_Mglc_Elvar _Llvar_i_3;
struct _Mglc_Slvar* _Llvar_4;
_Llvar_i_3 = (*_Lspace_0)._Flvar_v[_Li_1];
_Llvar_4 = _Mglc_Elvar_Pptr_1(_Llvar_i_3);
_Mglc_Sdecl_var_Pwrite_lvar_type_2(&(*_Llvar_4)._Fdecl, _Llvar_i_3);
if(((*_Llvar_4)._Fflags & _Mglc_Elvar_flags_Cset_expr) != _Mglc_Elvar_flags_C0) {
fprintf(_Gout, " = ");
_Mglc_Eexpr_Pwrite_1((*_Llvar_4)._Fset_expr);
}
fprintf(_Gout, ";\n");
continue_0:;
_Li_1++;
}
break_0:;
_Ls_5 = (*_Lspace_0)._Fstmt_first;
while(_Ls_5 != NULL) {
_Mglc_Sstmt_Pwrite_1(_Ls_5);
_Ls_5 = (*_Ls_5)._Fstmt_next;
continue_1:;
}
break_1:;
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
uint8_t _Mglc_Srdr_Pn1_1(union _Mglc_Srdr* _Lr_0) {
uint8_t _Lval_1;
_Lval_1 = (*_Lr_0)._F1[0];
(*_Lr_0)._Fpos++;
return _Lval_1;
}
void _Mglc_Ename_type_Prd_2(_Mglc_Ename_type* _Li_0, union _Mglc_Srdr* _Lr_1) {
(*_Li_0) = (_Mglc_Ename_type)(_Mglc_Srdr_Pn1_1(_Lr_1));
}
void _Mglc_Ebasic_type_id_Prd_2(_Mglc_Ebasic_type_id* _Le_0, union _Mglc_Srdr* _Lr_1) {
(*_Le_0) = (_Mglc_Ebasic_type_id)(_Mglc_Srdr_Pn1_1(_Lr_1));
}
_Mglc_Eat _Mglc_Pbasic_type_1(_Mglc_Ebasic_type_id _Lt_0) {
return _Lt_0;
}
void _Mglc_Eat_Prd_2(_Mglc_Eat* _Li_0, union _Mglc_Srdr* _Lr_1) {
_Mglc_Eat _Lidx_2;
_Lidx_2 = ((_Mglc_Eat)(Fgetnum(_Lr_1) - 1));
if(_Lidx_2 == _Mglc_Eat_Cnil) {
(*_Li_0) = _Mglc_Eat_Cnil;
} else {
(*_Li_0) = _Gat_table[_Lidx_2];
}
}
void _Mglc_Eid_Prd_2(_Mglc_Eid* _Lid_0, union _Mglc_Srdr* _Lr_1) {
_Mglc_Eid _Lidx_2;
_Lidx_2 = ((_Mglc_Eid)(Fgetnum(_Lr_1) - 1));
if(_Lidx_2 == _Mglc_Eid_Cnil) {
(*_Lid_0) = _Mglc_Eid_Cnil;
} else {
(*_Lid_0) = _Gid_table[_Lidx_2];
}
}
void _Mglc_Einclude_Prd_2(_Mglc_Einclude* _Li_0, union _Mglc_Srdr* _Lr_1) {
_Mglc_Einclude _Lidx_2;
_Lidx_2 = ((_Mglc_Einclude)(Fgetnum(_Lr_1) - 1));
if(_Lidx_2 == _Mglc_Einclude_Cnil) {
(*_Li_0) = _Mglc_Einclude_Cnil;
} else {
(*_Li_0) = _Ginclude_table[_Lidx_2];
}
}
void _Mglc_Sdecl_var_Prd_2(struct _Mglc_Sdecl_var* _Lvd_0, union _Mglc_Srdr* _Lr_1) {
_Mglc_Eid_Prd_2(&(*_Lvd_0)._Fname, _Lr_1);
_Mglc_Eat_Prd_2(&(*_Lvd_0)._Ftype, _Lr_1);
_Mglc_Evar_flags_Prd_2(&(*_Lvd_0)._Fflags, _Lr_1);
if(((*_Lvd_0)._Fflags & _Mglc_Evar_flags_Creal_name) != _Mglc_Evar_flags_C0) {
_Mglc_Eid_Prd_2(&(*_Lvd_0)._Freal_name, _Lr_1);
}
_Mglc_Stype_info_Prd_2(&(*_Lvd_0)._Ftype_info, _Lr_1);
(*_Lvd_0)._Fsize_c = _Mglc_Srdr_Pn1_1(_Lr_1);
if((*_Lvd_0)._Fsize_c > 0) {
_Mglc_Pquick_alloc_arr_2((*_Lvd_0)._Fsize_expr_v, (*_Lvd_0)._Fsize_c);
_Mglc_Pquick_alloc_arr_2((*_Lvd_0)._Fsize_value_v, (*_Lvd_0)._Fsize_c);
int32_t _Li_2;
_Li_2 = 0;
for(int i = (*_Lvd_0)._Fsize_c; i > 0; ) {
i --;
_Mglc_Eexpr_Prd_2(&(*_Lvd_0)._Fsize_expr_v[_Li_2], _Lr_1);
continue_0:;
_Li_2++;
}
break_0:;
}
}
void _Mglc_Ecvar_flags_Prd_2(_Mglc_Ecvar_flags* _Lf_0, union _Mglc_Srdr* _Lr_1) {
(*_Lf_0) = (_Mglc_Ecvar_flags)(_Mglc_Srdr_Pn1_1(_Lr_1));
}
void _Mglc_Eexpr_Prd_2(_Mglc_Eexpr* _Le_0, union _Mglc_Srdr* _Lr_1) {
_Mglc_Eexpr_type _Ltype_2;
if(_Mglc_Cdebug_rd_wr) {
if(_Mglc_Srdr_Pn1_1(_Lr_1) != 255) {
fprintf(stdout, "Error reading expr\n");
fflush(stdout);
exit(_Mstdc_Eexit_Cfailure);
}
}
_Mglc_Eexpr_type_Prd_2(&_Ltype_2, _Lr_1);
if(_Ltype_2 == _Mglc_Eexpr_type_Cnil) {
(*_Le_0) = _Mglc_Eexpr_Cnil;
} else {
_Mglc_Eexpr _Le_idx_3;
_Le_idx_3 = (_Mglc_Eexpr)(_Gexpr_c++);
if(_Gexpr_cap <= _Gexpr_c) {
int32_t _Lold_cap_4;
_Lold_cap_4 = _Gexpr_cap;
_Mglc_Pgrow_2(_Gexpr_cap, _Gexpr_c);
_Mglc_Prealloc_3(_Gexpr_v, _Gexpr_cap, _Lold_cap_4);
_Mglc_Prealloc_3(_Gexpr_is_processed, (_Gexpr_cap + 7) >> 3, (_Lold_cap_4 + 7) >> 3);
}
(*_Le_0) = _Le_idx_3;
switch(_Ltype_2) {
case _Mglc_Eexpr_type_Cassign:;
_Mglc_Eexpr_Prd_assign_2(_Le_idx_3, _Lr_1);
break;
case _Mglc_Eexpr_type_Ccompare:;
_Mglc_Eexpr_Prd_compare_2(_Le_idx_3, _Lr_1);
break;
case _Mglc_Eexpr_type_Cbool:;
_Mglc_Eexpr_Prd_bool_2(_Le_idx_3, _Lr_1);
break;
case _Mglc_Eexpr_type_Cchar:;
_Mglc_Eexpr_Prd_char_2(_Le_idx_3, _Lr_1);
break;
case _Mglc_Eexpr_type_Cmath:;
_Mglc_Eexpr_Prd_math_2(_Le_idx_3, _Lr_1);
break;
case _Mglc_Eexpr_type_Cunary:;
_Mglc_Eexpr_Prd_unary_2(_Le_idx_3, _Lr_1);
break;
case _Mglc_Eexpr_type_Cref:;
_Mglc_Eexpr_Prd_ref_2(_Le_idx_3, _Lr_1);
break;
case _Mglc_Eexpr_type_Ccast_fast:;
_Mglc_Eexpr_Prd_cast_fast_2(_Le_idx_3, _Lr_1);
break;
case _Mglc_Eexpr_type_Clvar:;
_Mglc_Eexpr_Prd_lvar_2(_Le_idx_3, _Lr_1);
break;
case _Mglc_Eexpr_type_Cfvar:;
_Mglc_Eexpr_Prd_fvar_2(_Le_idx_3, _Lr_1);
break;
case _Mglc_Eexpr_type_Cgvar:;
_Mglc_Eexpr_Prd_gvar_2(_Le_idx_3, _Lr_1);
break;
case _Mglc_Eexpr_type_Ccvar:;
_Mglc_Eexpr_Prd_cvar_2(_Le_idx_3, _Lr_1);
break;
case _Mglc_Eexpr_type_Cbools:;
_Mglc_Eexpr_Prd_bools_2(_Le_idx_3, _Lr_1);
break;
case _Mglc_Eexpr_type_Cmethod:;
_Mglc_Eexpr_Prd_method_2(_Le_idx_3, _Lr_1);
break;
case _Mglc_Eexpr_type_Cfunc:;
_Mglc_Eexpr_Prd_func_2(_Le_idx_3, _Lr_1);
break;
case _Mglc_Eexpr_type_Cstr:;
_Mglc_Eexpr_Prd_str_2(_Le_idx_3, _Lr_1);
break;
case _Mglc_Eexpr_type_Cint:;
_Mglc_Eexpr_Prd_int_2(_Le_idx_3, _Lr_1);
break;
case _Mglc_Eexpr_type_Csize_of_type:;
_Mglc_Eexpr_Prd_size_of_type_2(_Le_idx_3, _Lr_1);
break;
case _Mglc_Eexpr_type_Cnull:;
_Mglc_Eexpr_Prd_null_2(_Le_idx_3, _Lr_1);
break;
case _Mglc_Eexpr_type_Cindex:;
_Mglc_Eexpr_Prd_index_2(_Le_idx_3, _Lr_1);
break;
default:;
fprintf(stdout, ":rd was not implemented in expression #%s\n", _Mglc_Eexpr_type_Pglc_name_1(_Ltype_2));
exit(_Mstdc_Eexit_Cfailure);
break;
}
}
if(_Mglc_Cdebug_rd_wr) {
if(_Mglc_Srdr_Pn1_1(_Lr_1) != 255) {
fprintf(stdout, "Error reading expr\n");
fflush(stdout);
exit(_Mstdc_Eexit_Cfailure);
}
}
}
void _Mglc_Ecvar_Prd_2(_Mglc_Ecvar* _Lc_0, union _Mglc_Srdr* _Lr_1) {
_Mglc_Ecvar _Lidx_2;
_Lidx_2 = ((_Mglc_Ecvar)(Fgetnum(_Lr_1) - 1));
if(_Lidx_2 == _Mglc_Ecvar_Cnil) {
(*_Lc_0) = _Mglc_Ecvar_Cnil;
} else {
(*_Lc_0) = _Gcvar_table[_Lidx_2];
}
}
void _Mglc_Eenum_flags_Prd_2(_Mglc_Eenum_flags* _Le_0, union _Mglc_Srdr* _Lr_1) {
(*_Le_0) = (_Mglc_Eenum_flags)(_Mglc_Srdr_Pn1_1(_Lr_1));
}
void _Mglc_Estruct_flags_Prd_2(_Mglc_Estruct_flags* _Lf_0, union _Mglc_Srdr* _Lr_1) {
(*_Lf_0) = (_Mglc_Estruct_flags)(_Mglc_Srdr_Pn1_1(_Lr_1));
}
void _Mglc_Sfarg_Prd_2(struct _Mglc_Sfarg* _Lf_0, union _Mglc_Srdr* _Lr_1) {
_Mglc_Sdecl_var_Prd_2(&(*_Lf_0)._Fdecl, _Lr_1);
}
void _Mglc_Efunc_flags_Prd_2(_Mglc_Efunc_flags* _Le_0, union _Mglc_Srdr* _Lr_1) {
(*_Le_0) = (_Mglc_Efunc_flags)(Fgetnum(_Lr_1));
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
void _Mglc_Efunc_Prd_2(_Mglc_Efunc* _Lf_0, union _Mglc_Srdr* _Lr_1) {
(*_Lf_0) = ((_Mglc_Efunc)(Fgetnum(_Lr_1) - _Mglc_Efunc_C1));
}
uint32_t _Mglc_Srdr_Pn4_1(union _Mglc_Srdr* _Lr_0) {
uint32_t _Lval_1;
_Lval_1 = (uint32_t)((*_Lr_0)._F1[0]);
_Lval_1 |= ((*_Lr_0)._F1[1] << 8);
_Lval_1 |= ((*_Lr_0)._F1[2] << 16);
_Lval_1 |= ((*_Lr_0)._F1[3] << 24);
(*_Lr_0)._Fpos += 4;
return _Lval_1;
}
struct _Mglc_Sfile* _Mglc_Efile_Pptr_1(_Mglc_Efile _Lf_0) {
return &_Gfile_v[_Lf_0];
}
bool _Mglc_Eat_Pfinalize_4(_Mglc_Eat _Lat_i_0, struct _Mglc_Stype_info* _Lti_1, int32_t _Lrow_2, int32_t _Lcol_3) {
struct _Mglc_Sat* _Lat_4;
_Lat_4 = _Mglc_Eat_Pptr_1(_Lat_i_0);
if((*_Lat_4)._Ftype == _Mglc_Ename_type_Cstruct) {
if((*_Lti_1)._Fbuilt_in) {
if((*_Lti_1)._Fref_v[0] != 0) {
fprintf(stdout, "%s:%d:%d: Can't use plus symbol (+) because type '/%s' has reference\n", _Mglc_Efile_Ppath_1((*_Gctx_func)._Ffile), _Lrow_2, _Lcol_3, _Mglc_Eid_Pstr_1((*_Lat_4)._Fname._Fid));
return false;
}
(*_Lti_1)._Fref_v[0] = -1;
}
} else {
if((*_Lti_1)._Fbuilt_in) {
fprintf(stdout, "%s:%d:%d: Can't use plus symbol (+) because type is not a struct\n", _Mglc_Efile_Ppath_1((*_Gctx_func)._Ffile), _Lrow_2, _Lcol_3);
return false;
}
}
return true;
}
void _Mglc_Sdecl_func_Plvars_rd_2(struct _Mglc_Sdecl_func* _Lf_0, union _Mglc_Srdr* _Lr_1) {
_Mglc_Elvar _Llvar_c_2;
_Llvar_c_2 = (_Mglc_Elvar)(Fgetnum(_Lr_1));
(*_Lf_0)._Flvar_c = _Llvar_c_2;
_Mglc_Pquick_alloc_arr_2((*_Lf_0)._Flvar_v, _Llvar_c_2);
int32_t _Li_3;
_Li_3 = 0;
for(int i = (*_Lf_0)._Flvar_c; i > 0; ) {
i --;
struct _Mglc_Slvar* _Ll_4;
_Ll_4 = (&(*_Lf_0)._Flvar_v[_Li_3]);
(*_Ll_4)._Frow = Fgetnum(_Lr_1);
(*_Ll_4)._Fcol = Fgetnum(_Lr_1);
_Mglc_Sdecl_var_Prd_2(&(*_Ll_4)._Fdecl, _Lr_1);
_Mglc_Elvar_flags_Prd_2(&(*_Ll_4)._Fflags, _Lr_1);
if(((*_Ll_4)._Fflags & _Mglc_Elvar_flags_Cset_expr) != _Mglc_Elvar_flags_C0) {
_Mglc_Eexpr_Prd_2(&(*_Ll_4)._Fset_expr, _Lr_1);
}
continue_0:;
_Li_3++;
}
break_0:;
}
void _Mglc_Sstmt_space_Prd_3(struct _Mglc_Sstmt_space* _Lspace_0, union _Mglc_Srdr* _Lr_1, struct _Mglc_Sstmt_space* _Lparent_2) {
uint32_t _Llvar_c_3;
(*_Lspace_0)._Fparent = _Lparent_2;
(*_Lspace_0)._Fstmt_first = NULL;
(*_Lspace_0)._Fstmt_last = NULL;
_Llvar_c_3 = Fgetnum(_Lr_1);
(*_Lspace_0)._Flvar_c = _Llvar_c_3;
_Mglc_Pquick_alloc_arr_2((*_Lspace_0)._Flvar_v, _Llvar_c_3);
int32_t _Li_4;
_Li_4 = 0;
for(int i = _Llvar_c_3; i > 0; ) {
i --;
_Mglc_Elvar_Prd_2(&(*_Lspace_0)._Flvar_v[_Li_4], _Lr_1);
continue_0:;
_Li_4++;
}
break_0:;
while(1) {
_Mglc_Estmt_type _Ltype_5;
uint32_t _Lbegin_row_6;
uint32_t _Lbegin_col_7;
uint32_t _Lend_row_8;
uint32_t _Lend_col_9;
_Mglc_Estmt_type_Prd_2(&_Ltype_5, _Lr_1);
if(_Ltype_5 == _Mglc_Estmt_type_Cnil) {
goto break_1;
}
if(_Mglc_Cdebug_rd_wr) {
if(_Mglc_Srdr_Pn1_1(_Lr_1) != 255) {
fprintf(stdout, "Error reading stmt\n");
fflush(stdout);
exit(_Mstdc_Eexit_Cfailure);
}
}
_Lbegin_row_6 = Fgetnum(_Lr_1);
_Lbegin_col_7 = Fgetnum(_Lr_1);
_Lend_row_8 = Fgetnum(_Lr_1);
_Lend_col_9 = Fgetnum(_Lr_1);
_Gctx_begin_row = _Lbegin_row_6;
_Gctx_begin_col = _Lbegin_col_7;
_Gctx_end_row = _Lend_row_8;
_Gctx_end_col = _Lend_col_9;
switch(_Ltype_5) {
case _Mglc_Estmt_type_Cexpr:;
_Mglc_Sstmt_space_Prd_expr_2(_Lspace_0, _Lr_1);
break;
case _Mglc_Estmt_type_Cif:;
_Mglc_Sstmt_space_Prd_if_2(_Lspace_0, _Lr_1);
break;
case _Mglc_Estmt_type_Cif_elif:;
_Mglc_Sstmt_space_Prd_if_elif_2(_Lspace_0, _Lr_1);
break;
case _Mglc_Estmt_type_Cif_else:;
_Mglc_Sstmt_space_Prd_if_else_2(_Lspace_0, _Lr_1);
break;
case _Mglc_Estmt_type_Cif_end:;
_Mglc_Sstmt_space_Prd_if_end_2(_Lspace_0, _Lr_1);
break;
case _Mglc_Estmt_type_Cswitch:;
_Mglc_Sstmt_space_Prd_switch_2(_Lspace_0, _Lr_1);
break;
case _Mglc_Estmt_type_Ccase:;
_Mglc_Sstmt_space_Prd_case_2(_Lspace_0, _Lr_1);
break;
case _Mglc_Estmt_type_Ccase_end:;
_Mglc_Sstmt_space_Prd_case_end_2(_Lspace_0, _Lr_1);
break;
case _Mglc_Estmt_type_Cdefault:;
_Mglc_Sstmt_space_Prd_default_2(_Lspace_0, _Lr_1);
break;
case _Mglc_Estmt_type_Cdefault_end:;
_Mglc_Sstmt_space_Prd_default_end_2(_Lspace_0, _Lr_1);
break;
case _Mglc_Estmt_type_Cswitch_end:;
_Mglc_Sstmt_space_Prd_switch_end_2(_Lspace_0, _Lr_1);
break;
case _Mglc_Estmt_type_Cdo:;
_Mglc_Sstmt_space_Prd_do_2(_Lspace_0, _Lr_1);
break;
case _Mglc_Estmt_type_Cdo_end:;
_Mglc_Sstmt_space_Prd_do_end_2(_Lspace_0, _Lr_1);
break;
case _Mglc_Estmt_type_Cwhile:;
_Mglc_Sstmt_space_Prd_while_2(_Lspace_0, _Lr_1);
break;
case _Mglc_Estmt_type_Cwhile_end:;
_Mglc_Sstmt_space_Prd_while_end_2(_Lspace_0, _Lr_1);
break;
case _Mglc_Estmt_type_Ccontinue:;
_Mglc_Sstmt_space_Prd_continue_2(_Lspace_0, _Lr_1);
break;
case _Mglc_Estmt_type_Cbreak:;
_Mglc_Sstmt_space_Prd_break_2(_Lspace_0, _Lr_1);
break;
case _Mglc_Estmt_type_Creturn:;
_Mglc_Sstmt_space_Prd_return_2(_Lspace_0, _Lr_1);
break;
case _Mglc_Estmt_type_Cspace:;
_Mglc_Sstmt_space_Prd_space_2(_Lspace_0, _Lr_1);
break;
default:;
fprintf(stdout, ":rd not yet implemented in stmt #%s\n", _Mglc_Estmt_type_Pglc_name_1(_Ltype_5));
exit(_Mstdc_Eexit_Cfailure);
break;
}
if(_Mglc_Cdebug_rd_wr) {
if(_Mglc_Srdr_Pn1_1(_Lr_1) != 255) {
fprintf(stdout, "Error reading stmt\n");
fflush(stdout);
exit(_Mstdc_Eexit_Cfailure);
}
}
continue_1:;
}
break_1:;
}
bool _Mglc_Sstmt_Pprocess_1(struct _Mglc_Sstmt* _Ls_0) {
bool _Lok_1;
_Lok_1 = false;
_Gctx_begin_row = (*_Ls_0)._Fbegin_row;
_Gctx_begin_col = (*_Ls_0)._Fbegin_col;
_Gctx_end_row = (*_Ls_0)._Fend_row;
_Gctx_end_col = (*_Ls_0)._Fend_col;
switch((*_Ls_0)._Ftype) {
case _Mglc_Estmt_type_Cexpr:;
_Mglc_Sstmt_Pprocess_expr_2(_Ls_0, &_Lok_1);
break;
case _Mglc_Estmt_type_Cif:;
_Mglc_Sstmt_Pprocess_if_2(_Ls_0, &_Lok_1);
break;
case _Mglc_Estmt_type_Cif_elif:;
_Mglc_Sstmt_Pprocess_if_elif_2(_Ls_0, &_Lok_1);
break;
case _Mglc_Estmt_type_Cif_else:;
_Mglc_Sstmt_Pprocess_if_else_2(_Ls_0, &_Lok_1);
break;
case _Mglc_Estmt_type_Cif_end:;
_Mglc_Sstmt_Pprocess_if_end_2(_Ls_0, &_Lok_1);
break;
case _Mglc_Estmt_type_Cswitch:;
_Mglc_Sstmt_Pprocess_switch_2(_Ls_0, &_Lok_1);
break;
case _Mglc_Estmt_type_Ccase:;
_Mglc_Sstmt_Pprocess_case_2(_Ls_0, &_Lok_1);
break;
case _Mglc_Estmt_type_Ccase_end:;
_Mglc_Sstmt_Pprocess_case_end_2(_Ls_0, &_Lok_1);
break;
case _Mglc_Estmt_type_Cdefault:;
_Mglc_Sstmt_Pprocess_default_2(_Ls_0, &_Lok_1);
break;
case _Mglc_Estmt_type_Cdefault_end:;
_Mglc_Sstmt_Pprocess_default_end_2(_Ls_0, &_Lok_1);
break;
case _Mglc_Estmt_type_Cswitch_end:;
_Mglc_Sstmt_Pprocess_switch_end_2(_Ls_0, &_Lok_1);
break;
case _Mglc_Estmt_type_Cdo:;
_Mglc_Sstmt_Pprocess_do_2(_Ls_0, &_Lok_1);
break;
case _Mglc_Estmt_type_Cdo_end:;
_Mglc_Sstmt_Pprocess_do_end_2(_Ls_0, &_Lok_1);
break;
case _Mglc_Estmt_type_Cwhile:;
_Mglc_Sstmt_Pprocess_while_2(_Ls_0, &_Lok_1);
break;
case _Mglc_Estmt_type_Cwhile_end:;
_Mglc_Sstmt_Pprocess_while_end_2(_Ls_0, &_Lok_1);
break;
case _Mglc_Estmt_type_Ccontinue:;
_Mglc_Sstmt_Pprocess_continue_2(_Ls_0, &_Lok_1);
break;
case _Mglc_Estmt_type_Cbreak:;
_Mglc_Sstmt_Pprocess_break_2(_Ls_0, &_Lok_1);
break;
case _Mglc_Estmt_type_Creturn:;
_Mglc_Sstmt_Pprocess_return_2(_Ls_0, &_Lok_1);
break;
case _Mglc_Estmt_type_Cspace:;
_Mglc_Sstmt_Pprocess_space_2(_Ls_0, &_Lok_1);
break;
default:;
fprintf(stdout, "%s:%u:%u - %u:%u: :process is not implemented in statement #%s\n", _Mglc_Efile_Ppath_1((*_Gctx_func)._Ffile), (*_Ls_0)._Fbegin_row, (*_Ls_0)._Fbegin_col, (*_Ls_0)._Fend_row, (*_Ls_0)._Fend_col, _Mglc_Estmt_type_Pglc_name_1((*_Ls_0)._Ftype));
break;
}
if(!(_Lok_1)) {
fprintf(stdout, "%s:%u:%u - %u:%u: Processing of statement #%s failed\n", _Mglc_Efile_Ppath_1((*_Gctx_func)._Ffile), (*_Ls_0)._Fbegin_row, (*_Ls_0)._Fbegin_col, (*_Ls_0)._Fend_row, (*_Ls_0)._Fend_col, _Mglc_Estmt_type_Pglc_name_1((*_Ls_0)._Ftype));
}
return _Lok_1;
}
void _Mglc_Estruct_Poutput_1(_Mglc_Estruct _Ls_i_0) {
uint32_t _Lnum_1;
uint32_t _Ln3_2;
int32_t _Ln17_3;
struct _Mglc_Sstruct* _Ls_4;
int32_t _Lrow_5;
int32_t _Lcol_6;
_Lnum_1 = (uint32_t)(_Ls_i_0);
_Ln3_2 = (_Lnum_1 >> 3);
_Ln17_3 = (1 << (_Lnum_1 & 7));
if((_Gstruct_is_outputted[_Ln3_2] & _Ln17_3) != 0) {
return;
}
_Gstruct_is_outputted[_Ln3_2] |= _Ln17_3;
_Ls_4 = _Mglc_Estruct_Pptr_1(_Ls_i_0);
_Lrow_5 = (*_Ls_4)._Fbegin_row;
_Lcol_6 = (*_Ls_4)._Fbegin_col;
int32_t _Li_7;
_Li_7 = 0;
for(int i = (*_Ls_4)._Ffvar_c; i > 0; ) {
i --;
if(!(_Mglc_Sdecl_var_Pprocess_3(&(*_Ls_4)._Ffvar_v[_Li_7]._Fdecl, _Lrow_5, _Lcol_6))) {
return;
}
continue_0:;
_Li_7++;
}
break_0:;
if((*_Ls_4)._Finclude != _Mglc_Einclude_Cnil) {
_Mglc_Einclude_Poutput_1((*_Ls_4)._Finclude);
}
if(((*_Ls_4)._Fflags & _Mglc_Estruct_flags_Cno_decl) == _Mglc_Estruct_flags_C0) {
_Gstruct_outputted_v[_Gstruct_outputted_c++] = _Ls_i_0;
}
}
void _Mglc_Eenum_Poutput_1(_Mglc_Eenum _Le_i_0) {
uint32_t _Lnum_1;
uint32_t _Ln3_2;
int32_t _Ln17_3;
struct _Mglc_Senum* _Le_4;
_Lnum_1 = (uint32_t)(_Le_i_0);
_Ln3_2 = (_Lnum_1 >> 3);
_Ln17_3 = (1 << (_Lnum_1 & 7));
if((_Genum_is_outputted[_Ln3_2] & _Ln17_3) != 0) {
return;
}
_Genum_is_outputted[_Ln3_2] |= _Ln17_3;
_Le_4 = _Mglc_Eenum_Pptr_1(_Le_i_0);
_Mglc_Eat_Poutput_4((*_Le_4)._Fbase_type, (*_Le_4)._Ffile, (*_Le_4)._Fbegin_row, (*_Le_4)._Fbegin_col);
if((*_Le_4)._Finclude != _Mglc_Einclude_Cnil) {
_Mglc_Einclude_Poutput_1((*_Le_4)._Finclude);
}
_Genum_outputted_v[_Genum_outputted_c++] = _Le_i_0;
}
bool _Mglc_Eexpr_Pprocess_1(_Mglc_Eexpr _Le_0) {
uint32_t _Lnum_1;
uint32_t _Ln3_2;
int32_t _Ln17_3;
struct _Mglc_Sexpr* _Lexpr_4;
bool _Lok_5;
if(_Le_0 == _Mglc_Eexpr_Cnil) {
fprintf(stdout, "%s:%u:%u - %u:%u: Processed a nil expression\n", _Mglc_Efile_Ppath_1((*_Gctx_func)._Ffile), _Gctx_begin_row, _Gctx_begin_col, _Gctx_end_row, _Gctx_end_col);
return false;
}
_Lnum_1 = (uint32_t)(_Le_0);
_Ln3_2 = (_Lnum_1 >> 3);
_Ln17_3 = (1 << (_Lnum_1 & 7));
if((_Gexpr_is_processed[_Ln3_2] & _Ln17_3) != _Mglc_Eexpr_C0) {
return true;
}
_Gexpr_is_processed[_Ln3_2] |= _Ln17_3;
_Lexpr_4 = _Mglc_Eexpr_Pptr_1(_Le_0);
_Lok_5 = false;
switch((*_Lexpr_4)._Ftype) {
case _Mglc_Eexpr_type_Cassign:;
_Mglc_Eexpr_Pprocess_assign_2(_Lexpr_4, &_Lok_5);
break;
case _Mglc_Eexpr_type_Ccompare:;
_Mglc_Eexpr_Pprocess_compare_2(_Lexpr_4, &_Lok_5);
break;
case _Mglc_Eexpr_type_Cbool:;
_Mglc_Eexpr_Pprocess_bool_2(_Lexpr_4, &_Lok_5);
break;
case _Mglc_Eexpr_type_Cchar:;
_Mglc_Eexpr_Pprocess_char_2(_Lexpr_4, &_Lok_5);
break;
case _Mglc_Eexpr_type_Cmath:;
_Mglc_Eexpr_Pprocess_math_2(_Lexpr_4, &_Lok_5);
break;
case _Mglc_Eexpr_type_Cunary:;
_Mglc_Eexpr_Pprocess_unary_2(_Lexpr_4, &_Lok_5);
break;
case _Mglc_Eexpr_type_Cref:;
_Mglc_Eexpr_Pprocess_ref_2(_Lexpr_4, &_Lok_5);
break;
case _Mglc_Eexpr_type_Ccast_fast:;
_Mglc_Eexpr_Pprocess_cast_fast_2(_Lexpr_4, &_Lok_5);
break;
case _Mglc_Eexpr_type_Clvar:;
_Mglc_Eexpr_Pprocess_lvar_2(_Lexpr_4, &_Lok_5);
break;
case _Mglc_Eexpr_type_Cfvar:;
_Mglc_Eexpr_Pprocess_fvar_2(_Lexpr_4, &_Lok_5);
break;
case _Mglc_Eexpr_type_Cgvar:;
_Mglc_Eexpr_Pprocess_gvar_2(_Lexpr_4, &_Lok_5);
break;
case _Mglc_Eexpr_type_Ccvar:;
_Mglc_Eexpr_Pprocess_cvar_2(_Lexpr_4, &_Lok_5);
break;
case _Mglc_Eexpr_type_Cbools:;
_Mglc_Eexpr_Pprocess_bools_2(_Lexpr_4, &_Lok_5);
break;
case _Mglc_Eexpr_type_Cmethod:;
_Mglc_Eexpr_Pprocess_method_2(_Lexpr_4, &_Lok_5);
break;
case _Mglc_Eexpr_type_Cfunc:;
_Mglc_Eexpr_Pprocess_func_2(_Lexpr_4, &_Lok_5);
break;
case _Mglc_Eexpr_type_Cstr:;
_Mglc_Eexpr_Pprocess_str_2(_Lexpr_4, &_Lok_5);
break;
case _Mglc_Eexpr_type_Cint:;
_Mglc_Eexpr_Pprocess_int_2(_Lexpr_4, &_Lok_5);
break;
case _Mglc_Eexpr_type_Csize_of_type:;
_Mglc_Eexpr_Pprocess_size_of_type_2(_Lexpr_4, &_Lok_5);
break;
case _Mglc_Eexpr_type_Cnull:;
_Mglc_Eexpr_Pprocess_null_2(_Lexpr_4, &_Lok_5);
break;
case _Mglc_Eexpr_type_Cindex:;
_Mglc_Eexpr_Pprocess_index_2(_Lexpr_4, &_Lok_5);
break;
default:;
fprintf(stdout, "%s:%u:%u - %u:%u: :process not implemented for expression #%s\n", _Mglc_Efile_Ppath_1((*_Gctx_func)._Ffile), _Gctx_begin_row, _Gctx_begin_col, _Gctx_end_row, _Gctx_end_col, _Mglc_Eexpr_type_Pglc_name_1((*_Lexpr_4)._Ftype));
return false;
break;
}
if(!(_Lok_5)) {
fprintf(stdout, "%s:%u:%u - %u:%u: Processing of expression #%s failed\n", _Mglc_Efile_Ppath_1((*_Gctx_func)._Ffile), _Gctx_begin_row, _Gctx_begin_col, _Gctx_end_row, _Gctx_end_col, _Mglc_Eexpr_type_Pglc_name_1((*_Lexpr_4)._Ftype));
}
return _Lok_5;
}
char* _Mglc_Eid_Pc_name_1(_Mglc_Eid _Lid_0) {
char* _Lc_name_1;
uint8_t _Llen_2;
char* _Lstr_3;
_Lc_name_1 = _Gid_c_name_v[_Lid_0];
if(_Lc_name_1 != NULL) {
return _Lc_name_1;
}
_Llen_2 = _Gid_len_v[_Lid_0];
_Lstr_3 = _Gid_str_v[_Lid_0];
_Lc_name_1 = qalloc(_Llen_2 + 1);
_Gid_c_name_v[_Lid_0] = _Lc_name_1;
int32_t _Li_4;
_Li_4 = 0;
for(int i = _Llen_2; i > 0; ) {
i --;
if(_Lstr_3[_Li_4] == '-') {
_Lc_name_1[_Li_4] = '_';
} else {
_Lc_name_1[_Li_4] = _Lstr_3[_Li_4];
}
continue_0:;
_Li_4++;
}
break_0:;
_Lc_name_1[_Llen_2] = '\0';
return _Lc_name_1;
}
struct _Mglc_Sexpr* _Mglc_Eexpr_Pptr_1(_Mglc_Eexpr _Le_0) {
return _Gexpr_v[_Le_0];
}
void _Mglc_Eexpr_Pwrite_assign_1(struct _Mglc_Sexpr* _Lexpr_0) {
struct _Mglc_Sexpr_assign* _Le_1;
_Le_1 = _Lexpr_0;
_Mglc_Eexpr_Pwrite_value_2((*_Le_1)._Fleft, &(*_Le_1)._Fleft_val);
switch((*_Le_1)._Ftype) {
case _Mglc_Eassign_Ceq:;
fprintf(_Gout, " = ");
break;
case _Mglc_Eassign_Cplus_eq:;
fprintf(_Gout, " += ");
break;
case _Mglc_Eassign_Cminus_eq:;
fprintf(_Gout, " -= ");
break;
case _Mglc_Eassign_Cmul_eq:;
fprintf(_Gout, " *= ");
break;
case _Mglc_Eassign_Cdiv_eq:;
fprintf(_Gout, " /= ");
break;
case _Mglc_Eassign_Clshift_eq:;
fprintf(_Gout, " <<= ");
break;
case _Mglc_Eassign_Crshift_eq:;
fprintf(_Gout, " >>= ");
break;
case _Mglc_Eassign_Cand_eq:;
fprintf(_Gout, " &= ");
break;
case _Mglc_Eassign_Cor_eq:;
fprintf(_Gout, " |= ");
break;
case _Mglc_Eassign_Cxor_eq:;
fprintf(_Gout, " ^= ");
break;
}
_Mglc_Eexpr_Pwrite_value_2((*_Le_1)._Fright, &(*_Le_1)._Fright_val);
}
void _Mglc_Eexpr_Pwrite_compare_1(struct _Mglc_Sexpr* _Lexpr_0) {
struct _Mglc_Sexpr_compare* _Le_1;
_Le_1 = _Lexpr_0;
_Mglc_Eexpr_Pwrite_value_2((*_Le_1)._Fleft, &(*_Le_1)._Fleft_val);
switch((*_Le_1)._Ftype) {
case _Mglc_Ecompare_Ceq:;
fprintf(_Gout, " == ");
break;
case _Mglc_Ecompare_Cnot_eq:;
fprintf(_Gout, " != ");
break;
case _Mglc_Ecompare_Clt:;
fprintf(_Gout, " < ");
break;
case _Mglc_Ecompare_Cle:;
fprintf(_Gout, " <= ");
break;
case _Mglc_Ecompare_Cgt:;
fprintf(_Gout, " > ");
break;
case _Mglc_Ecompare_Cge:;
fprintf(_Gout, " >= ");
break;
}
_Mglc_Eexpr_Pwrite_value_2((*_Le_1)._Fright, &(*_Le_1)._Fright_val);
}
void _Mglc_Eexpr_Pwrite_bool_1(struct _Mglc_Sexpr* _Lexpr_0) {
struct _Mglc_Sexpr_bool* _Le_1;
_Le_1 = _Lexpr_0;
if((*_Le_1)._Fvalue) {
fprintf(_Gout, "true");
} else {
fprintf(_Gout, "false");
}
}
void _Mglc_Eexpr_Pwrite_char_1(struct _Mglc_Sexpr* _Lexpr_0) {
struct _Mglc_Sexpr_char* _Le_1;
_Le_1 = _Lexpr_0;
_Mglc_Pwrite_char_1((*_Le_1)._Fvalue);
}
void _Mglc_Eexpr_Pwrite_math_1(struct _Mglc_Sexpr* _Lexpr_0) {
struct _Mglc_Sexpr_math* _Le_1;
_Le_1 = _Lexpr_0;
switch((*_Le_1)._Ftype) {
case _Mglc_Emath_Cadd:;
_Mglc_Eexpr_Pwrite_value_2((*_Le_1)._Fleft, &(*_Le_1)._Fleft_val);
fprintf(_Gout, " + ");
_Mglc_Eexpr_Pwrite_value_2((*_Le_1)._Fright, &(*_Le_1)._Fright_val);
int32_t _Li_2;
_Li_2 = 0;
for(int i = (*_Le_1)._Fitem_c; i > 0; ) {
i --;
fprintf(_Gout, " + ");
_Mglc_Eexpr_Pwrite_value_2((*_Le_1)._Fitem_v[_Li_2]._Fexpr, &(*_Le_1)._Fitem_v[_Li_2]._Fval);
continue_0:;
_Li_2++;
}
break_0:;
break;
case _Mglc_Emath_Csub:;
_Mglc_Eexpr_Pwrite_value_2((*_Le_1)._Fleft, &(*_Le_1)._Fleft_val);
fprintf(_Gout, " - ");
_Mglc_Eexpr_Pwrite_value_2((*_Le_1)._Fright, &(*_Le_1)._Fright_val);
int32_t _Li_3;
_Li_3 = 0;
for(int i = (*_Le_1)._Fitem_c; i > 0; ) {
i --;
fprintf(_Gout, " - ");
_Mglc_Eexpr_Pwrite_value_2((*_Le_1)._Fitem_v[_Li_3]._Fexpr, &(*_Le_1)._Fitem_v[_Li_3]._Fval);
continue_1:;
_Li_3++;
}
break_1:;
break;
case _Mglc_Emath_Cmul:;
_Mglc_Eexpr_Pwrite_value_2((*_Le_1)._Fleft, &(*_Le_1)._Fleft_val);
fprintf(_Gout, " * ");
_Mglc_Eexpr_Pwrite_value_2((*_Le_1)._Fright, &(*_Le_1)._Fright_val);
int32_t _Li_4;
_Li_4 = 0;
for(int i = (*_Le_1)._Fitem_c; i > 0; ) {
i --;
fprintf(_Gout, " * ");
_Mglc_Eexpr_Pwrite_value_2((*_Le_1)._Fitem_v[_Li_4]._Fexpr, &(*_Le_1)._Fitem_v[_Li_4]._Fval);
continue_2:;
_Li_4++;
}
break_2:;
break;
case _Mglc_Emath_Cdiv:;
_Mglc_Eexpr_Pwrite_value_2((*_Le_1)._Fleft, &(*_Le_1)._Fleft_val);
fprintf(_Gout, " / ");
_Mglc_Eexpr_Pwrite_value_2((*_Le_1)._Fright, &(*_Le_1)._Fright_val);
int32_t _Li_5;
_Li_5 = 0;
for(int i = (*_Le_1)._Fitem_c; i > 0; ) {
i --;
fprintf(_Gout, " / ");
_Mglc_Eexpr_Pwrite_value_2((*_Le_1)._Fitem_v[_Li_5]._Fexpr, &(*_Le_1)._Fitem_v[_Li_5]._Fval);
continue_3:;
_Li_5++;
}
break_3:;
break;
case _Mglc_Emath_Clshift:;
_Mglc_Eexpr_Pwrite_value_2((*_Le_1)._Fleft, &(*_Le_1)._Fleft_val);
fprintf(_Gout, " << ");
_Mglc_Eexpr_Pwrite_value_2((*_Le_1)._Fright, &(*_Le_1)._Fright_val);
break;
case _Mglc_Emath_Crshift:;
_Mglc_Eexpr_Pwrite_value_2((*_Le_1)._Fleft, &(*_Le_1)._Fleft_val);
fprintf(_Gout, " >> ");
_Mglc_Eexpr_Pwrite_value_2((*_Le_1)._Fright, &(*_Le_1)._Fright_val);
break;
case _Mglc_Emath_Cand:;
_Mglc_Eexpr_Pwrite_value_2((*_Le_1)._Fleft, &(*_Le_1)._Fleft_val);
fprintf(_Gout, " & ");
_Mglc_Eexpr_Pwrite_value_2((*_Le_1)._Fright, &(*_Le_1)._Fright_val);
int32_t _Li_6;
_Li_6 = 0;
for(int i = (*_Le_1)._Fitem_c; i > 0; ) {
i --;
fprintf(_Gout, " & ");
_Mglc_Eexpr_Pwrite_value_2((*_Le_1)._Fitem_v[_Li_6]._Fexpr, &(*_Le_1)._Fitem_v[_Li_6]._Fval);
continue_4:;
_Li_6++;
}
break_4:;
break;
case _Mglc_Emath_Cor:;
_Mglc_Eexpr_Pwrite_value_2((*_Le_1)._Fleft, &(*_Le_1)._Fleft_val);
fprintf(_Gout, " | ");
_Mglc_Eexpr_Pwrite_value_2((*_Le_1)._Fright, &(*_Le_1)._Fright_val);
int32_t _Li_7;
_Li_7 = 0;
for(int i = (*_Le_1)._Fitem_c; i > 0; ) {
i --;
fprintf(_Gout, " | ");
_Mglc_Eexpr_Pwrite_value_2((*_Le_1)._Fitem_v[_Li_7]._Fexpr, &(*_Le_1)._Fitem_v[_Li_7]._Fval);
continue_5:;
_Li_7++;
}
break_5:;
break;
case _Mglc_Emath_Cxor:;
_Mglc_Eexpr_Pwrite_value_2((*_Le_1)._Fleft, &(*_Le_1)._Fleft_val);
fprintf(_Gout, " ^ ");
_Mglc_Eexpr_Pwrite_value_2((*_Le_1)._Fright, &(*_Le_1)._Fright_val);
int32_t _Li_8;
_Li_8 = 0;
for(int i = (*_Le_1)._Fitem_c; i > 0; ) {
i --;
fprintf(_Gout, " ^ ");
_Mglc_Eexpr_Pwrite_value_2((*_Le_1)._Fitem_v[_Li_8]._Fexpr, &(*_Le_1)._Fitem_v[_Li_8]._Fval);
continue_6:;
_Li_8++;
}
break_6:;
break;
}
}
void _Mglc_Eexpr_Pwrite_unary_1(struct _Mglc_Sexpr* _Lexpr_0) {
struct _Mglc_Sexpr_unary* _Le_1;
_Le_1 = _Lexpr_0;
switch((*_Le_1)._Ftype) {
case _Mglc_Eunary_Cneg:;
fprintf(_Gout, "-");
_Mglc_Eexpr_Pwrite_value_2((*_Le_1)._Fexpr, &(*_Le_1)._Fval);
break;
case _Mglc_Eunary_Cinc:;
_Mglc_Eexpr_Pwrite_value_2((*_Le_1)._Fexpr, &(*_Le_1)._Fval);
fprintf(_Gout, "++");
break;
case _Mglc_Eunary_Cdec:;
_Mglc_Eexpr_Pwrite_value_2((*_Le_1)._Fexpr, &(*_Le_1)._Fval);
fprintf(_Gout, "--");
break;
}
}
void _Mglc_Eexpr_Pwrite_ref_1(struct _Mglc_Sexpr* _Lexpr_0) {
struct _Mglc_Sexpr_ref* _Le_1;
_Le_1 = _Lexpr_0;
_Mglc_Eexpr_Pwrite_value_2((*_Le_1)._Fexpr, &(*_Le_1)._Fval);
}
void _Mglc_Eexpr_Pwrite_lvar_1(struct _Mglc_Sexpr* _Lexpr_0) {
struct _Mglc_Sexpr_lvar* _Le_1;
_Le_1 = _Lexpr_0;
_Mglc_Sdecl_var_Pwrite_lvar_2(&(*_Mglc_Elvar_Pptr_1((*_Le_1)._Flvar))._Fdecl, (*_Le_1)._Flvar);
}
void _Mglc_Eexpr_Pwrite_fvar_1(struct _Mglc_Sexpr* _Lexpr_0) {
struct _Mglc_Sexpr_fvar* _Le_1;
_Le_1 = _Lexpr_0;
_Mglc_Eexpr_Pwrite_value_2((*_Le_1)._Fexpr, &(*_Le_1)._Fval);
fprintf(_Gout, ".");
_Mglc_Sdecl_var_Pwrite_2(&(*_Mglc_Estruct_Pptr_1((*_Mglc_Eat_Pptr_1((*_Le_1)._Fval._Ftype))._Fdecl._Fstruct))._Ffvar_v[(*_Le_1)._Ffvar]._Fdecl, _Mglc_Edecl_var_type_Cfvar);
}
void _Mglc_Eexpr_Pwrite_gvar_1(struct _Mglc_Sexpr* _Lexpr_0) {
struct _Mglc_Sexpr_gvar* _Le_1;
_Le_1 = _Lexpr_0;
_Mglc_Egvar_Pwrite_1((*_Le_1)._Fgvar);
}
void _Mglc_Eexpr_Pwrite_cvar_1(struct _Mglc_Sexpr* _Lexpr_0) {
struct _Mglc_Sexpr_cvar* _Le_1;
_Le_1 = _Lexpr_0;
_Mglc_Ecvar_Pwrite_1((*_Le_1)._Fcvar);
}
void _Mglc_Eexpr_Pwrite_bools_1(struct _Mglc_Sexpr* _Lexpr_0) {
struct _Mglc_Sexpr_bools* _Le_1;
_Le_1 = _Lexpr_0;
switch((*_Le_1)._Ftype) {
case _Mglc_Ebools_Cand:;
fprintf(_Gout, "(");
_Mglc_Eexpr_Pwrite_value_2((*_Le_1)._Fleft, &(*_Le_1)._Fleft_val);
fprintf(_Gout, " && ");
_Mglc_Eexpr_Pwrite_value_2((*_Le_1)._Fright, &(*_Le_1)._Fright_val);
int32_t _Li_2;
_Li_2 = 0;
for(int i = (*_Le_1)._Fitem_c; i > 0; ) {
i --;
struct _Mglc_Sexpr_bools_item* _Litem_3;
fprintf(_Gout, " && ");
_Litem_3 = (&(*_Le_1)._Fitem_v[_Li_2]);
_Mglc_Eexpr_Pwrite_value_2((*_Litem_3)._Fexpr, &(*_Litem_3)._Fval);
continue_0:;
_Li_2++;
}
break_0:;
fprintf(_Gout, ")");
break;
case _Mglc_Ebools_Cor:;
fprintf(_Gout, "(");
_Mglc_Eexpr_Pwrite_value_2((*_Le_1)._Fleft, &(*_Le_1)._Fleft_val);
fprintf(_Gout, " || ");
_Mglc_Eexpr_Pwrite_value_2((*_Le_1)._Fright, &(*_Le_1)._Fright_val);
int32_t _Li_4;
_Li_4 = 0;
for(int i = (*_Le_1)._Fitem_c; i > 0; ) {
i --;
struct _Mglc_Sexpr_bools_item* _Litem_5;
fprintf(_Gout, " || ");
_Litem_5 = (&(*_Le_1)._Fitem_v[_Li_4]);
_Mglc_Eexpr_Pwrite_value_2((*_Litem_5)._Fexpr, &(*_Litem_5)._Fval);
continue_1:;
_Li_4++;
}
break_1:;
fprintf(_Gout, ")");
break;
}
}
void _Mglc_Eexpr_Pwrite_method_1(struct _Mglc_Sexpr* _Lexpr_0) {
struct _Mglc_Sexpr_method* _Le_1;
struct _Mglc_Sdecl_func* _Lf_2;
bool _Lfirst_3;
int32_t _Li_4;
_Le_1 = _Lexpr_0;
_Lf_2 = _Mglc_Efunc_Pptr_1((*_Le_1)._Ffunc_idx);
_Mglc_Sdecl_func_Pwrite_1(_Lf_2);
fprintf(_Gout, "(");
_Lfirst_3 = true;
_Li_4 = 0;
for(int i = (*_Lf_2)._Fthis_idx; i > 0; ) {
i --;
struct _Mglc_Scarg* _Lca_5;
if(_Lfirst_3) {
_Lfirst_3 = false;
} else {
fprintf(_Gout, ", ");
}
_Lca_5 = (&(*_Le_1)._Fcarg_v[_Li_4]);
_Mglc_Eexpr_Pwrite_value_2((*_Lca_5)._Fexpr, &(*_Lca_5)._Fvalue);
continue_0:;
_Li_4++;
}
break_0:;
if(_Lfirst_3) {
_Lfirst_3 = false;
} else {
fprintf(_Gout, ", ");
}
_Mglc_Eexpr_Pwrite_value_2((*_Le_1)._Fthis, &(*_Le_1)._Fthis_value);
for(int i = (*_Le_1)._Fcarg_c - (*_Lf_2)._Fthis_idx; i > 0; ) {
i --;
struct _Mglc_Scarg* _Lca_6;
fprintf(_Gout, ", ");
_Lca_6 = (&(*_Le_1)._Fcarg_v[_Li_4]);
_Mglc_Eexpr_Pwrite_value_2((*_Lca_6)._Fexpr, &(*_Lca_6)._Fvalue);
continue_1:;
_Li_4++;
}
break_1:;
fprintf(_Gout, ")");
}
void _Mglc_Eexpr_Pwrite_func_1(struct _Mglc_Sexpr* _Lexpr_0) {
struct _Mglc_Sexpr_func* _Le_1;
struct _Mglc_Sdecl_func* _Lf_2;
_Le_1 = _Lexpr_0;
_Lf_2 = _Mglc_Efunc_Pptr_1((*_Le_1)._Ffunc_idx);
_Mglc_Sdecl_func_Pwrite_1(_Lf_2);
fprintf(_Gout, "(");
int32_t _Li_3;
_Li_3 = 0;
for(int i = (*_Le_1)._Fcarg_c; i > 0; ) {
i --;
if(_Li_3 != 0) {
fprintf(_Gout, ", ");
}
_Mglc_Eexpr_Pwrite_value_2((*_Le_1)._Fcarg_v[_Li_3]._Fexpr, &(*_Le_1)._Fcarg_v[_Li_3]._Fvalue);
continue_0:;
_Li_3++;
}
break_0:;
fprintf(_Gout, ")");
}
void _Mglc_Eexpr_Pwrite_str_1(struct _Mglc_Sexpr* _Lexpr_0) {
struct _Mglc_Sexpr_str* _Le_1;
struct _Mglc_Sexpr_str_node* _Ln_2;
_Le_1 = _Lexpr_0;
_Ln_2 = (*_Le_1)._Ffirst;
while(1) {
_Mglc_Pwrite_str_node_2((*_Ln_2)._Flen, (*_Ln_2)._Fbuf);
_Ln_2 = (*_Ln_2)._Fnext;
if(_Ln_2 == NULL) {
goto break_0;
}
fputc('\n', _Gout);
continue_0:;
}
break_0:;
}
void _Mglc_Eexpr_Pwrite_int_1(struct _Mglc_Sexpr* _Lexpr_0) {
struct _Mglc_Sexpr_int* _Le_1;
_Le_1 = _Lexpr_0;
fprintf(_Gout, "%d", (*_Le_1)._Fvalue);
}
void _Mglc_Eexpr_Pwrite_size_of_type_1(struct _Mglc_Sexpr* _Lexpr_0) {
struct _Mglc_Sexpr_size_of_type* _Le_1;
_Le_1 = _Lexpr_0;
fprintf(_Gout, "sizeof(");
_Mglc_Eat_Pwrite_1((*_Le_1)._Ftype);
fprintf(_Gout, ")");
}
void _Mglc_Eexpr_Pwrite_null_1(struct _Mglc_Sexpr* _Lexpr_0) {
struct _Mglc_Sexpr_null* _Le_1;
_Le_1 = _Lexpr_0;
fprintf(_Gout, "NULL");
}
void _Mglc_Eexpr_Pwrite_index_1(struct _Mglc_Sexpr* _Lexpr_0) {
struct _Mglc_Sexpr_index* _Le_1;
_Le_1 = _Lexpr_0;
_Mglc_Eexpr_Pwrite_value_2((*_Le_1)._Fleft, &(*_Le_1)._Fleft_val);
fprintf(_Gout, "[");
_Mglc_Eexpr_Pwrite_value_2((*_Le_1)._Fright, &(*_Le_1)._Fright_val);
fprintf(_Gout, "]");
}
void _Mglc_Sdecl_var_Pwrite_2(struct _Mglc_Sdecl_var* _Lvd_0, _Mglc_Edecl_var_type _Lvar_type_1) {
if(((*_Lvd_0)._Fflags & _Mglc_Evar_flags_Creal_name) != _Mglc_Evar_flags_C0) {
fprintf(_Gout, "%s", _Mglc_Eid_Pstr_1((*_Lvd_0)._Freal_name));
return;
}
switch(_Lvar_type_1) {
case _Mglc_Edecl_var_type_Cgvar:;
fprintf(_Gout, "_G%s", _Mglc_Eid_Pc_name_1((*_Lvd_0)._Fname));
break;
case _Mglc_Edecl_var_type_Cfvar:;
fprintf(_Gout, "_F%s", _Mglc_Eid_Pc_name_1((*_Lvd_0)._Fname));
break;
}
}
bool _Mglc_Eexpr_Pwrite_value_2(_Mglc_Eexpr _Le_0, struct _Mglc_Svalue* _Lv_1) {
struct _Mglc_Sexpr* _Lexpr_2;
int8_t _Lref_3;
_Lexpr_2 = _Mglc_Eexpr_Pptr_1(_Le_0);
_Lref_3 = (*_Lv_1)._Fref;
if((*_Lv_1)._Fparen) {
if(_Lref_3 <= 0) {
_Mstdc_Sfile_Pwrite_3(_Gout, "(&", 2);
} else {
_Mstdc_Sfile_Pwrite_3(_Gout, "(*******************************", _Lref_3);
}
} else {
if(_Lref_3 <= 0) {
_Mstdc_Sfile_Pwrite_3(_Gout, "&", 1);
} else if(_Lref_3 > 1) {
_Mstdc_Sfile_Pwrite_3(_Gout, "*******************************", _Lref_3 - 1);
}
}
if((*_Lexpr_2)._Ftype == _Mglc_Eexpr_type_Ccast_fast) {
struct _Mglc_Sexpr_cast_fast* _Le_4;
_Le_4 = _Lexpr_2;
_Mglc_Sexpr_cast_fast_Pwrite_value_2(_Le_4, _Lv_1);
} else {
_Mglc_Eexpr_Pwrite_1(_Le_0);
}
if((*_Lv_1)._Fparen) {
_Mstdc_Sfile_Pwrite_3(_Gout, ")", 1);
}
return true;
}
void _Mglc_Stype_info_Pcount_1(struct _Mglc_Stype_info* _Lti_0) {
int8_t _Lstar_c_1;
_Lstar_c_1 = (*_Lti_0)._Farray_c;
int8_t _Li_2;
_Li_2 = (*_Lti_0)._Farray_c;
for(int i = _Li_2 + 1; i > 0; ) {
i --;
_Lstar_c_1 += (*_Lti_0)._Fref_v[_Li_2];
_Li_2 -= 1;
continue_0:;
}
break_0:;
(*_Lti_0)._Fstar_c = _Lstar_c_1;
}
bool _Mglc_Eat_Pwrite_type_1(_Mglc_Eat _Ltd_0) {
_Mglc_Eat_Pwrite_1(_Ltd_0);
return true;
}
int32_t _Mglc_Eat_Pcount_stars0_2(_Mglc_Eat _Ltd_0, struct _Mglc_Stype_info* _Lti_1) {
return (*_Lti_1)._Fstar_c + _Mglc_Eat_Ppointer_1(_Ltd_0);
}
size_t _Mstdc_Sfile_Pwrite_3(FILE* _Lf_0, void* _Lbuf_1, size_t _Lsize_2) {
return fwrite(_Lbuf_1, 1, _Lsize_2, _Lf_0);
}
void _Mglc_Sdecl_var_Pwrite_lvar_2(struct _Mglc_Sdecl_var* _Lvd_0, _Mglc_Elvar _Llvar_1) {
fprintf(_Gout, "_L%s_%u", _Mglc_Eid_Pc_name_1((*_Lvd_0)._Fname), _Llvar_1);
}
struct _Mglc_Slvar* _Mglc_Elvar_Pptr_1(_Mglc_Elvar _Ll_0) {
return &(*_Gctx_func)._Flvar_v[_Ll_0];
}
void _Mglc_Sstmt_Pwrite_1(struct _Mglc_Sstmt* _Ls_0) {
switch((*_Ls_0)._Ftype) {
case _Mglc_Estmt_type_Cexpr:;
_Mglc_Sstmt_Pwrite_expr_1(_Ls_0);
break;
case _Mglc_Estmt_type_Cif:;
_Mglc_Sstmt_Pwrite_if_1(_Ls_0);
break;
case _Mglc_Estmt_type_Cif_elif:;
_Mglc_Sstmt_Pwrite_if_elif_1(_Ls_0);
break;
case _Mglc_Estmt_type_Cif_else:;
_Mglc_Sstmt_Pwrite_if_else_1(_Ls_0);
break;
case _Mglc_Estmt_type_Cif_end:;
_Mglc_Sstmt_Pwrite_if_end_1(_Ls_0);
break;
case _Mglc_Estmt_type_Cswitch:;
_Mglc_Sstmt_Pwrite_switch_1(_Ls_0);
break;
case _Mglc_Estmt_type_Ccase:;
_Mglc_Sstmt_Pwrite_case_1(_Ls_0);
break;
case _Mglc_Estmt_type_Ccase_end:;
_Mglc_Sstmt_Pwrite_case_end_1(_Ls_0);
break;
case _Mglc_Estmt_type_Cdefault:;
_Mglc_Sstmt_Pwrite_default_1(_Ls_0);
break;
case _Mglc_Estmt_type_Cdefault_end:;
_Mglc_Sstmt_Pwrite_default_end_1(_Ls_0);
break;
case _Mglc_Estmt_type_Cswitch_end:;
_Mglc_Sstmt_Pwrite_switch_end_1(_Ls_0);
break;
case _Mglc_Estmt_type_Cdo:;
_Mglc_Sstmt_Pwrite_do_1(_Ls_0);
break;
case _Mglc_Estmt_type_Cdo_end:;
_Mglc_Sstmt_Pwrite_do_end_1(_Ls_0);
break;
case _Mglc_Estmt_type_Cwhile:;
_Mglc_Sstmt_Pwrite_while_1(_Ls_0);
break;
case _Mglc_Estmt_type_Cwhile_end:;
_Mglc_Sstmt_Pwrite_while_end_1(_Ls_0);
break;
case _Mglc_Estmt_type_Ccontinue:;
_Mglc_Sstmt_Pwrite_continue_1(_Ls_0);
break;
case _Mglc_Estmt_type_Cbreak:;
_Mglc_Sstmt_Pwrite_break_1(_Ls_0);
break;
case _Mglc_Estmt_type_Creturn:;
_Mglc_Sstmt_Pwrite_return_1(_Ls_0);
break;
case _Mglc_Estmt_type_Cspace:;
_Mglc_Sstmt_Pwrite_space_1(_Ls_0);
break;
default:;
fprintf(stdout, ":write not yet implemented in stmt #%s\n", _Mglc_Estmt_type_Pglc_name_1((*_Ls_0)._Ftype));
exit(_Mstdc_Eexit_Cfailure);
break;
}
}
void _Mglc_Evar_flags_Prd_2(_Mglc_Evar_flags* _Lf_0, union _Mglc_Srdr* _Lr_1) {
(*_Lf_0) = (_Mglc_Evar_flags)(Fgetnum(_Lr_1));
}
void _Mglc_Stype_info_Prd_2(struct _Mglc_Stype_info* _Lti_0, union _Mglc_Srdr* _Lr_1) {
uint8_t _Lc_2;
_Lc_2 = _Mglc_Srdr_Pn1_1(_Lr_1);
int32_t _Li_3;
_Li_3 = 0;
for(int i = _Lc_2; i > 0; ) {
i --;
(*_Lti_0)._Fref_v[_Li_3] = _Mglc_Srdr_Pn1_1(_Lr_1);
continue_0:;
_Li_3++;
}
break_0:;
(*_Lti_0)._Farray_c = _Mglc_Srdr_Pn1_1(_Lr_1);
(*_Lti_0)._Fstar_c = _Mglc_Srdr_Pn1_1(_Lr_1);
(*_Lti_0)._Fbuilt_in = (_Mglc_Srdr_Pn1_1(_Lr_1) != 0);
(*_Lti_0)._Fconst = (_Mglc_Srdr_Pn1_1(_Lr_1) != 0);
}
void _Mglc_Eexpr_type_Prd_2(_Mglc_Eexpr_type* _Le_0, union _Mglc_Srdr* _Lr_1) {
(*_Le_0) = (_Mglc_Eexpr_type)(_Mglc_Srdr_Pn1_1(_Lr_1));
}
void _Mglc_Eexpr_Prd_assign_2(_Mglc_Eexpr _Le_idx_0, union _Mglc_Srdr* _Lr_1) {
struct _Mglc_Sexpr_assign* _Le_2;
_Mglc_Pquick_alloc_one_1(_Le_2);
_Mglc_Eexpr_Pset_3(_Le_idx_0, &(*_Le_2)._Fbase, _Mglc_Eexpr_type_Cassign);
_Mglc_Eexpr_Prd_2(&(*_Le_2)._Fleft, _Lr_1);
_Mglc_Eexpr_Prd_2(&(*_Le_2)._Fright, _Lr_1);
_Mglc_Eassign_Prd_2(&(*_Le_2)._Ftype, _Lr_1);
}
void _Mglc_Eexpr_Prd_compare_2(_Mglc_Eexpr _Le_idx_0, union _Mglc_Srdr* _Lr_1) {
struct _Mglc_Sexpr_compare* _Le_2;
_Mglc_Pquick_alloc_one_1(_Le_2);
_Mglc_Eexpr_Pset_3(_Le_idx_0, &(*_Le_2)._Fbase, _Mglc_Eexpr_type_Ccompare);
_Mglc_Eexpr_Prd_2(&(*_Le_2)._Fleft, _Lr_1);
_Mglc_Eexpr_Prd_2(&(*_Le_2)._Fright, _Lr_1);
_Mglc_Ecompare_Prd_2(&(*_Le_2)._Ftype, _Lr_1);
}
void _Mglc_Eexpr_Prd_bool_2(_Mglc_Eexpr _Le_idx_0, union _Mglc_Srdr* _Lr_1) {
struct _Mglc_Sexpr_bool* _Le_2;
_Mglc_Pquick_alloc_one_1(_Le_2);
_Mglc_Eexpr_Pset_3(_Le_idx_0, &(*_Le_2)._Fbase, _Mglc_Eexpr_type_Cbool);
(*_Le_2)._Fvalue = _Mglc_Srdr_Pbool_1(_Lr_1);
}
void _Mglc_Eexpr_Prd_char_2(_Mglc_Eexpr _Le_idx_0, union _Mglc_Srdr* _Lr_1) {
struct _Mglc_Sexpr_char* _Le_2;
_Mglc_Pquick_alloc_one_1(_Le_2);
_Mglc_Eexpr_Pset_3(_Le_idx_0, &(*_Le_2)._Fbase, _Mglc_Eexpr_type_Cchar);
(*_Le_2)._Fvalue = Fgetnum(_Lr_1);
}
void _Mglc_Eexpr_Prd_math_2(_Mglc_Eexpr _Le_idx_0, union _Mglc_Srdr* _Lr_1) {
struct _Mglc_Sexpr_math* _Le_2;
uint8_t _Litem_c_3;
_Mglc_Pquick_alloc_one_1(_Le_2);
_Mglc_Eexpr_Pset_3(_Le_idx_0, &(*_Le_2)._Fbase, _Mglc_Eexpr_type_Cmath);
_Mglc_Eexpr_Prd_2(&(*_Le_2)._Fleft, _Lr_1);
_Mglc_Eexpr_Prd_2(&(*_Le_2)._Fright, _Lr_1);
_Mglc_Emath_Prd_2(&(*_Le_2)._Ftype, _Lr_1);
_Litem_c_3 = _Mglc_Srdr_Pn1_1(_Lr_1);
if(_Litem_c_3 > 0) {
(*_Le_2)._Fitem_c = _Litem_c_3;
_Mglc_Pquick_alloc_arr_2((*_Le_2)._Fitem_v, _Litem_c_3);
int32_t _Li_4;
_Li_4 = 0;
for(int i = (*_Le_2)._Fitem_c; i > 0; ) {
i --;
_Mglc_Eexpr_Prd_2(&(*_Le_2)._Fitem_v[_Li_4]._Fexpr, _Lr_1);
continue_0:;
_Li_4++;
}
break_0:;
}
}
void _Mglc_Eexpr_Prd_unary_2(_Mglc_Eexpr _Le_idx_0, union _Mglc_Srdr* _Lr_1) {
struct _Mglc_Sexpr_unary* _Le_2;
_Mglc_Pquick_alloc_one_1(_Le_2);
_Mglc_Eexpr_Pset_3(_Le_idx_0, &(*_Le_2)._Fbase, _Mglc_Eexpr_type_Cunary);
_Mglc_Eexpr_Prd_2(&(*_Le_2)._Fexpr, _Lr_1);
_Mglc_Eunary_Prd_2(&(*_Le_2)._Ftype, _Lr_1);
}
void _Mglc_Eexpr_Prd_ref_2(_Mglc_Eexpr _Le_idx_0, union _Mglc_Srdr* _Lr_1) {
struct _Mglc_Sexpr_ref* _Le_2;
_Mglc_Pquick_alloc_one_1(_Le_2);
_Mglc_Eexpr_Pset_3(_Le_idx_0, &(*_Le_2)._Fbase, _Mglc_Eexpr_type_Cref);
_Mglc_Eexpr_Prd_2(&(*_Le_2)._Fexpr, _Lr_1);
}
void _Mglc_Eexpr_Prd_cast_fast_2(_Mglc_Eexpr _Le_idx_0, union _Mglc_Srdr* _Lr_1) {
struct _Mglc_Sexpr_cast_fast* _Le_2;
_Mglc_Pquick_alloc_one_1(_Le_2);
_Mglc_Eexpr_Pset_3(_Le_idx_0, &(*_Le_2)._Fbase, _Mglc_Eexpr_type_Ccast_fast);
_Mglc_Eexpr_Prd_2(&(*_Le_2)._Fexpr, _Lr_1);
_Mglc_Eat_Prd_2(&(*_Le_2)._Ftype, _Lr_1);
}
void _Mglc_Eexpr_Prd_lvar_2(_Mglc_Eexpr _Le_idx_0, union _Mglc_Srdr* _Lr_1) {
struct _Mglc_Sexpr_lvar* _Le_2;
_Mglc_Pquick_alloc_one_1(_Le_2);
_Mglc_Eexpr_Pset_3(_Le_idx_0, &(*_Le_2)._Fbase, _Mglc_Eexpr_type_Clvar);
_Mglc_Elvar_Prd_2(&(*_Le_2)._Flvar, _Lr_1);
}
void _Mglc_Eexpr_Prd_fvar_2(_Mglc_Eexpr _Le_idx_0, union _Mglc_Srdr* _Lr_1) {
struct _Mglc_Sexpr_fvar* _Le_2;
_Mglc_Pquick_alloc_one_1(_Le_2);
_Mglc_Eexpr_Pset_3(_Le_idx_0, &(*_Le_2)._Fbase, _Mglc_Eexpr_type_Cfvar);
_Mglc_Eexpr_Prd_2(&(*_Le_2)._Fexpr, _Lr_1);
_Mglc_Eid_Prd_2(&(*_Le_2)._Fmember, _Lr_1);
}
void _Mglc_Eexpr_Prd_gvar_2(_Mglc_Eexpr _Le_idx_0, union _Mglc_Srdr* _Lr_1) {
struct _Mglc_Sexpr_gvar* _Le_2;
_Mglc_Eat _Lat_idx_3;
_Mglc_Eid _Lname_4;
struct _Mglc_Sat* _Lat_5;
_Mglc_Egvar _Lfound_6;
_Mglc_Pquick_alloc_one_1(_Le_2);
_Mglc_Eexpr_Pset_3(_Le_idx_0, &(*_Le_2)._Fbase, _Mglc_Eexpr_type_Cgvar);
_Mglc_Eat_Prd_2(&_Lat_idx_3, _Lr_1);
_Mglc_Eid_Prd_2(&_Lname_4, _Lr_1);
if(_Lat_idx_3 == _Mglc_Eat_Cnil) {
_Lat_idx_3 = (*_Gctx_func)._Fat;
}
_Lat_5 = _Mglc_Eat_Pptr_1(_Lat_idx_3);
_Lfound_6 = _Mglc_Egvar_Cnil;
int32_t _Li_7;
_Li_7 = 0;
for(int i = (*_Lat_5)._Fgvar_c; i > 0; ) {
i --;
_Mglc_Egvar _Lgvar_8;
_Lgvar_8 = (*_Lat_5)._Fgvar_v[_Li_7];
if((*_Mglc_Egvar_Pptr_1(_Lgvar_8))._Fdecl._Fname == _Lname_4) {
_Lfound_6 = _Lgvar_8;
goto break_0;
}
continue_0:;
_Li_7++;
}
break_0:;
if(_Lfound_6 == _Mglc_Egvar_Cnil) {
fprintf(stdout, "%s:%u:%u - %u:%u: Cannot find gvar '.%s'\n", _Mglc_Efile_Ppath_1((*_Gctx_func)._Ffile), _Gctx_begin_row, _Gctx_begin_col, _Gctx_end_row, _Gctx_end_col, _Mglc_Eid_Pstr_1(_Lname_4));
exit(_Mstdc_Eexit_Cfailure);
}
(*_Le_2)._Fgvar = _Lfound_6;
}
void _Mglc_Eexpr_Prd_cvar_2(_Mglc_Eexpr _Le_idx_0, union _Mglc_Srdr* _Lr_1) {
struct _Mglc_Sexpr_cvar* _Le_2;
_Mglc_Pquick_alloc_one_1(_Le_2);
_Mglc_Eexpr_Pset_3(_Le_idx_0, &(*_Le_2)._Fbase, _Mglc_Eexpr_type_Ccvar);
_Mglc_Eat_Prd_2(&(*_Le_2)._Fat, _Lr_1);
_Mglc_Eid_Prd_2(&(*_Le_2)._Fname, _Lr_1);
(*_Le_2)._Ftry = _Mglc_Eat_Cnil;
}
void _Mglc_Eexpr_Prd_bools_2(_Mglc_Eexpr _Le_idx_0, union _Mglc_Srdr* _Lr_1) {
struct _Mglc_Sexpr_bools* _Le_2;
uint8_t _Litem_c_3;
_Mglc_Pquick_alloc_one_1(_Le_2);
_Mglc_Eexpr_Pset_3(_Le_idx_0, &(*_Le_2)._Fbase, _Mglc_Eexpr_type_Cbools);
_Mglc_Eexpr_Prd_2(&(*_Le_2)._Fleft, _Lr_1);
_Mglc_Eexpr_Prd_2(&(*_Le_2)._Fright, _Lr_1);
_Litem_c_3 = _Mglc_Srdr_Pn1_1(_Lr_1);
if(_Litem_c_3 > 0) {
(*_Le_2)._Fitem_c = _Litem_c_3;
_Mglc_Pquick_alloc_arr_2((*_Le_2)._Fitem_v, _Litem_c_3);
int32_t _Li_4;
_Li_4 = 0;
for(int i = _Litem_c_3; i > 0; ) {
i --;
_Mglc_Eexpr_Prd_2(&(*_Le_2)._Fitem_v[_Li_4]._Fexpr, _Lr_1);
continue_0:;
_Li_4++;
}
break_0:;
}
_Mglc_Ebools_Prd_2(&(*_Le_2)._Ftype, _Lr_1);
}
void _Mglc_Eexpr_Prd_method_2(_Mglc_Eexpr _Le_idx_0, union _Mglc_Srdr* _Lr_1) {
_Mglc_Eexpr _Lthis_expr_2;
_Mglc_Eid _Lfunc_name_3;
uint8_t _Lgroup_c_4;
int8_t _Lgroup_v_5[_Mglc_Cexpr_carg_group_limit];
uint8_t _Lcarg_c_7;
struct _Mglc_Sexpr_method* _Le_8;
_Mglc_Eexpr_Prd_2(&_Lthis_expr_2, _Lr_1);
_Mglc_Eid_Prd_2(&_Lfunc_name_3, _Lr_1);
_Lgroup_c_4 = _Mglc_Srdr_Pn1_1(_Lr_1);
int32_t _Li_6;
_Li_6 = 0;
for(int i = _Lgroup_c_4; i > 0; ) {
i --;
_Lgroup_v_5[_Li_6] = _Mglc_Srdr_Pn1_1(_Lr_1);
continue_0:;
_Li_6++;
}
break_0:;
_Lcarg_c_7 = _Mglc_Srdr_Pn1_1(_Lr_1);
_Mglc_Pquick_alloc_plus_2(_Le_8, sizeof(struct _Mglc_Scarg) * _Lcarg_c_7);
_Mglc_Eexpr_Pset_3(_Le_idx_0, &(*_Le_8)._Fbase, _Mglc_Eexpr_type_Cmethod);
(*_Le_8)._Fthis = _Lthis_expr_2;
(*_Le_8)._Ffunc_name = _Lfunc_name_3;
(*_Le_8)._Fgroup_c = _Lgroup_c_4;
int32_t _Li_9;
_Li_9 = 0;
for(int i = _Lgroup_c_4; i > 0; ) {
i --;
(*_Le_8)._Fgroup_v[_Li_9] = _Lgroup_v_5[_Li_9];
continue_1:;
_Li_9++;
}
break_1:;
(*_Le_8)._Fcarg_c = _Lcarg_c_7;
int32_t _Li_10;
_Li_10 = 0;
for(int i = _Lcarg_c_7; i > 0; ) {
i --;
_Mglc_Eexpr_Prd_2(&(*_Le_8)._Fcarg_v[_Li_10]._Fexpr, _Lr_1);
continue_2:;
_Li_10++;
}
break_2:;
}
void _Mglc_Eexpr_Prd_func_2(_Mglc_Eexpr _Le_idx_0, union _Mglc_Srdr* _Lr_1) {
_Mglc_Eat _Lat_idx_2;
_Mglc_Eid _Lfunc_name_3;
uint8_t _Lgroup_c_4;
int8_t _Lgroup_v_5[_Mglc_Cexpr_carg_group_limit];
uint8_t _Lcarg_c_7;
struct _Mglc_Sexpr_func* _Le_8;
_Mglc_Eat_Prd_2(&_Lat_idx_2, _Lr_1);
_Mglc_Eid_Prd_2(&_Lfunc_name_3, _Lr_1);
_Lgroup_c_4 = _Mglc_Srdr_Pn1_1(_Lr_1);
int32_t _Li_6;
_Li_6 = 0;
for(int i = _Lgroup_c_4; i > 0; ) {
i --;
_Lgroup_v_5[_Li_6] = _Mglc_Srdr_Pn1_1(_Lr_1);
continue_0:;
_Li_6++;
}
break_0:;
_Lcarg_c_7 = _Mglc_Srdr_Pn1_1(_Lr_1);
_Mglc_Pquick_alloc_plus_2(_Le_8, sizeof(struct _Mglc_Scarg) * _Lcarg_c_7);
_Mglc_Eexpr_Pset_3(_Le_idx_0, &(*_Le_8)._Fbase, _Mglc_Eexpr_type_Cfunc);
(*_Le_8)._Fat = _Lat_idx_2;
(*_Le_8)._Ffunc_name = _Lfunc_name_3;
(*_Le_8)._Fgroup_c = _Lgroup_c_4;
int32_t _Li_9;
_Li_9 = 0;
for(int i = _Lgroup_c_4; i > 0; ) {
i --;
(*_Le_8)._Fgroup_v[_Li_9] = _Lgroup_v_5[_Li_9];
continue_1:;
_Li_9++;
}
break_1:;
(*_Le_8)._Fcarg_c = _Lcarg_c_7;
int32_t _Li_10;
_Li_10 = 0;
for(int i = _Lcarg_c_7; i > 0; ) {
i --;
_Mglc_Eexpr_Prd_2(&(*_Le_8)._Fcarg_v[_Li_10]._Fexpr, _Lr_1);
continue_2:;
_Li_10++;
}
break_2:;
}
void _Mglc_Eexpr_Prd_str_2(_Mglc_Eexpr _Le_idx_0, union _Mglc_Srdr* _Lr_1) {
uint32_t _Lnode_c_2;
struct _Mglc_Sexpr_str* _Le_3;
bool _Lfirst_4;
_Lnode_c_2 = Fgetnum(_Lr_1);
_Mglc_Pquick_alloc_one_1(_Le_3);
_Mglc_Eexpr_Pset_3(_Le_idx_0, &(*_Le_3)._Fbase, _Mglc_Eexpr_type_Cstr);
_Lfirst_4 = true;
for(int i = _Lnode_c_2; i > 0; ) {
i --;
uint32_t _Llen_5;
struct _Mglc_Sexpr_str_node* _Ln_6;
_Llen_5 = Fgetnum(_Lr_1);
_Mglc_Pquick_alloc_plus_2(_Ln_6, _Llen_5 + 1);
(*_Ln_6)._Flen = _Llen_5;
_Mglc_Srdr_Pcopy_3(_Lr_1, (*_Ln_6)._Fbuf, _Llen_5);
(*_Ln_6)._Fbuf[_Llen_5] = 0;
(*_Ln_6)._Fnext = NULL;
if(_Lfirst_4) {
_Lfirst_4 = false;
(*_Le_3)._Ffirst = _Ln_6;
(*_Le_3)._Flast = _Ln_6;
} else {
(*(*_Le_3)._Flast)._Fnext = _Ln_6;
(*_Le_3)._Flast = _Ln_6;
}
continue_0:;
}
break_0:;
}
void _Mglc_Eexpr_Prd_int_2(_Mglc_Eexpr _Le_idx_0, union _Mglc_Srdr* _Lr_1) {
struct _Mglc_Sexpr_int* _Le_2;
_Mglc_Pquick_alloc_one_1(_Le_2);
_Mglc_Eexpr_Pset_3(_Le_idx_0, &(*_Le_2)._Fbase, _Mglc_Eexpr_type_Cint);
(*_Le_2)._Ftype = (_Mglc_Eexpr_int)(_Mglc_Srdr_Pn1_1(_Lr_1));
(*_Le_2)._Fvalue = Fgetnum(_Lr_1);
}
void _Mglc_Eexpr_Prd_size_of_type_2(_Mglc_Eexpr _Le_idx_0, union _Mglc_Srdr* _Lr_1) {
struct _Mglc_Sexpr_size_of_type* _Le_2;
_Mglc_Pquick_alloc_one_1(_Le_2);
_Mglc_Eexpr_Pset_3(_Le_idx_0, &(*_Le_2)._Fbase, _Mglc_Eexpr_type_Csize_of_type);
_Mglc_Eat_Prd_2(&(*_Le_2)._Ftype, _Lr_1);
}
void _Mglc_Eexpr_Prd_null_2(_Mglc_Eexpr _Le_idx_0, union _Mglc_Srdr* _Lr_1) {
struct _Mglc_Sexpr_null* _Le_2;
_Mglc_Pquick_alloc_one_1(_Le_2);
_Mglc_Eexpr_Pset_3(_Le_idx_0, &(*_Le_2)._Fbase, _Mglc_Eexpr_type_Cnull);
}
void _Mglc_Eexpr_Prd_index_2(_Mglc_Eexpr _Le_idx_0, union _Mglc_Srdr* _Lr_1) {
struct _Mglc_Sexpr_index* _Le_2;
_Mglc_Pquick_alloc_one_1(_Le_2);
_Mglc_Eexpr_Pset_3(_Le_idx_0, &(*_Le_2)._Fbase, _Mglc_Eexpr_type_Cindex);
_Mglc_Eexpr_Prd_2(&(*_Le_2)._Fleft, _Lr_1);
_Mglc_Eexpr_Prd_2(&(*_Le_2)._Fright, _Lr_1);
}
void _Mglc_Elvar_flags_Prd_2(_Mglc_Elvar_flags* _Lf_0, union _Mglc_Srdr* _Lr_1) {
(*_Lf_0) = (_Mglc_Elvar_flags)(_Mglc_Srdr_Pn1_1(_Lr_1));
}
void _Mglc_Elvar_Prd_2(_Mglc_Elvar* _Ll_0, union _Mglc_Srdr* _Lr_1) {
(*_Ll_0) = ((_Mglc_Elvar)(Fgetnum(_Lr_1) - 1));
}
void _Mglc_Estmt_type_Prd_2(_Mglc_Estmt_type* _Ls_0, union _Mglc_Srdr* _Lr_1) {
(*_Ls_0) = (_Mglc_Estmt_type)(_Mglc_Srdr_Pn1_1(_Lr_1));
}
void _Mglc_Sstmt_space_Prd_expr_2(struct _Mglc_Sstmt_space* _Lspace_0, union _Mglc_Srdr* _Lr_1) {
struct _Mglc_Sstmt_expr* _Ls_2;
_Mglc_Pquick_alloc_one_1(_Ls_2);
_Mglc_Eexpr_Prd_2(&(*_Ls_2)._Fexpr, _Lr_1);
_Mglc_Sstmt_space_Pstmt_push_7(_Lspace_0, &(*_Ls_2)._Fbase, _Gctx_begin_row, _Gctx_begin_col, _Gctx_end_row, _Gctx_end_col, _Mglc_Estmt_type_Cexpr);
}
void _Mglc_Sstmt_space_Prd_if_2(struct _Mglc_Sstmt_space* _Lspace_0, union _Mglc_Srdr* _Lr_1) {
struct _Mglc_Sstmt_if* _Ls_2;
_Mglc_Pquick_alloc_one_1(_Ls_2);
(*_Ls_2)._Fnot = _Mglc_Srdr_Pbool_1(_Lr_1);
_Mglc_Eexpr_Prd_2(&(*_Ls_2)._Fexpr, _Lr_1);
_Mglc_Sstmt_space_Pstmt_push_7(_Lspace_0, &(*_Ls_2)._Fbase, _Gctx_begin_row, _Gctx_begin_col, _Gctx_end_row, _Gctx_end_col, _Mglc_Estmt_type_Cif);
}
void _Mglc_Sstmt_space_Prd_if_elif_2(struct _Mglc_Sstmt_space* _Lspace_0, union _Mglc_Srdr* _Lr_1) {
struct _Mglc_Sstmt_if_elif* _Ls_2;
_Mglc_Pquick_alloc_one_1(_Ls_2);
(*_Ls_2)._Fnot = _Mglc_Srdr_Pbool_1(_Lr_1);
_Mglc_Eexpr_Prd_2(&(*_Ls_2)._Fexpr, _Lr_1);
_Mglc_Sstmt_space_Pstmt_push_7(_Lspace_0, &(*_Ls_2)._Fbase, _Gctx_begin_row, _Gctx_begin_col, _Gctx_end_row, _Gctx_end_col, _Mglc_Estmt_type_Cif_elif);
}
void _Mglc_Sstmt_space_Prd_if_else_2(struct _Mglc_Sstmt_space* _Lspace_0, union _Mglc_Srdr* _Lr_1) {
struct _Mglc_Sstmt_if_else* _Ls_2;
_Mglc_Pquick_alloc_one_1(_Ls_2);
_Mglc_Sstmt_space_Pstmt_push_7(_Lspace_0, &(*_Ls_2)._Fbase, 0, 0, 0, 0, _Mglc_Estmt_type_Cif_else);
}
void _Mglc_Sstmt_space_Prd_if_end_2(struct _Mglc_Sstmt_space* _Lspace_0, union _Mglc_Srdr* _Lr_1) {
struct _Mglc_Sstmt_if_end* _Ls_2;
_Mglc_Pquick_alloc_one_1(_Ls_2);
_Mglc_Sstmt_space_Pstmt_push_7(_Lspace_0, &(*_Ls_2)._Fbase, 0, 0, 0, 0, _Mglc_Estmt_type_Cif_end);
}
void _Mglc_Sstmt_space_Prd_switch_2(struct _Mglc_Sstmt_space* _Lspace_0, union _Mglc_Srdr* _Lr_1) {
struct _Mglc_Sstmt_switch* _Ls_2;
_Mglc_Pquick_alloc_one_1(_Ls_2);
_Mglc_Eexpr_Prd_2(&(*_Ls_2)._Fexpr, _Lr_1);
_Mglc_Eexpr_Prd_2(&(*_Ls_2)._Fcases, _Lr_1);
_Mglc_Sstmt_space_Pstmt_push_7(_Lspace_0, &(*_Ls_2)._Fbase, _Gctx_begin_row, _Gctx_begin_col, _Gctx_end_row, _Gctx_end_col, _Mglc_Estmt_type_Cswitch);
}
void _Mglc_Sstmt_space_Prd_case_2(struct _Mglc_Sstmt_space* _Lspace_0, union _Mglc_Srdr* _Lr_1) {
uint32_t _Lexpr_c_2;
struct _Mglc_Sstmt_case* _Ls_3;
_Lexpr_c_2 = Fgetnum(_Lr_1);
_Mglc_Pquick_alloc_plus_2(_Ls_3, sizeof(struct _Mglc_Sstmt_case_item) * _Lexpr_c_2);
(*_Ls_3)._Fexpr_c = _Lexpr_c_2;
int32_t _Li_4;
_Li_4 = 0;
for(int i = _Lexpr_c_2; i > 0; ) {
i --;
_Mglc_Eexpr_Prd_2(&(*_Ls_3)._Fexpr_v[_Li_4]._Fexpr, _Lr_1);
continue_0:;
_Li_4++;
}
break_0:;
(*_Ls_3)._Ffall_through = _Mglc_Srdr_Pbool_1(_Lr_1);
_Mglc_Sstmt_space_Pstmt_push_7(_Lspace_0, &(*_Ls_3)._Fbase, _Gctx_begin_row, _Gctx_begin_col, _Gctx_end_row, _Gctx_end_col, _Mglc_Estmt_type_Ccase);
}
void _Mglc_Sstmt_space_Prd_case_end_2(struct _Mglc_Sstmt_space* _Lspace_0, union _Mglc_Srdr* _Lr_1) {
struct _Mglc_Sstmt_case_end* _Ls_2;
_Mglc_Pquick_alloc_one_1(_Ls_2);
_Mglc_Sstmt_space_Pstmt_push_7(_Lspace_0, &(*_Ls_2)._Fbase, _Gctx_begin_row, _Gctx_begin_col, _Gctx_end_row, _Gctx_end_col, _Mglc_Estmt_type_Ccase_end);
}
void _Mglc_Sstmt_space_Prd_default_2(struct _Mglc_Sstmt_space* _Lspace_0, union _Mglc_Srdr* _Lr_1) {
struct _Mglc_Sstmt_default* _Ls_2;
_Mglc_Pquick_alloc_one_1(_Ls_2);
(*_Ls_2)._Ffall_through = _Mglc_Srdr_Pbool_1(_Lr_1);
_Mglc_Sstmt_space_Pstmt_push_7(_Lspace_0, &(*_Ls_2)._Fbase, _Gctx_begin_row, _Gctx_begin_col, _Gctx_end_row, _Gctx_end_col, _Mglc_Estmt_type_Cdefault);
}
void _Mglc_Sstmt_space_Prd_default_end_2(struct _Mglc_Sstmt_space* _Lspace_0, union _Mglc_Srdr* _Lr_1) {
struct _Mglc_Sstmt_default_end* _Ls_2;
_Mglc_Pquick_alloc_one_1(_Ls_2);
_Mglc_Sstmt_space_Pstmt_push_7(_Lspace_0, &(*_Ls_2)._Fbase, _Gctx_begin_row, _Gctx_begin_col, _Gctx_end_row, _Gctx_end_col, _Mglc_Estmt_type_Cdefault_end);
}
void _Mglc_Sstmt_space_Prd_switch_end_2(struct _Mglc_Sstmt_space* _Lspace_0, union _Mglc_Srdr* _Lr_1) {
struct _Mglc_Sstmt_switch_end* _Ls_2;
_Mglc_Pquick_alloc_one_1(_Ls_2);
_Mglc_Sstmt_space_Pstmt_push_7(_Lspace_0, &(*_Ls_2)._Fbase, 0, 0, 0, 0, _Mglc_Estmt_type_Cswitch_end);
}
void _Mglc_Sstmt_space_Prd_do_2(struct _Mglc_Sstmt_space* _Lspace_0, union _Mglc_Srdr* _Lr_1) {
struct _Mglc_Sstmt_do* _Ls_2;
_Mglc_Pquick_alloc_one_1(_Ls_2);
_Mglc_Eexpr_Prd_2(&(*_Ls_2)._Fexpr, _Lr_1);
_Mglc_Sstmt_space_Pstmt_push_7(_Lspace_0, &(*_Ls_2)._Fbase, _Gctx_begin_row, _Gctx_begin_col, _Gctx_end_row, _Gctx_end_col, _Mglc_Estmt_type_Cdo);
if(_Mglc_Srdr_Pbool_1(_Lr_1)) {
struct _Mglc_Sstmt_space* _Lspace2_3;
_Mglc_Pquick_alloc_one_1(_Lspace2_3);
(*_Ls_2)._Fcontinue = _Lspace2_3;
_Mglc_Sstmt_space_Prd_3(_Lspace2_3, _Lr_1, _Lspace_0);
}
_Gnest_stack_id_v[_Gnest_stack_c] = _Gnest_id++;
_Gnest_stack_ptr_v[_Gnest_stack_c]._Fdo = _Ls_2;
_Gnest_stack_c++;
}
void _Mglc_Sstmt_space_Prd_do_end_2(struct _Mglc_Sstmt_space* _Lspace_0, union _Mglc_Srdr* _Lr_1) {
struct _Mglc_Sstmt_do* _Ldo_2;
struct _Mglc_Sstmt_do_end* _Ls_3;
_Ldo_2 = _Gnest_stack_ptr_v[(_Gnest_stack_c -= 1)]._Fdo;
_Mglc_Pquick_alloc_one_1(_Ls_3);
(*_Ls_3)._Fdo = _Ldo_2;
(*_Ldo_2)._Fend = _Ls_3;
_Mglc_Sstmt_space_Pstmt_push_7(_Lspace_0, &(*_Ls_3)._Fbase, 0, 0, 0, 0, _Mglc_Estmt_type_Cdo_end);
}
void _Mglc_Sstmt_space_Prd_while_2(struct _Mglc_Sstmt_space* _Lspace_0, union _Mglc_Srdr* _Lr_1) {
struct _Mglc_Sstmt_while* _Ls_2;
_Mglc_Pquick_alloc_one_1(_Ls_2);
_Mglc_Eexpr_Prd_2(&(*_Ls_2)._Fexpr, _Lr_1);
_Mglc_Sstmt_space_Pstmt_push_7(_Lspace_0, &(*_Ls_2)._Fbase, _Gctx_begin_row, _Gctx_begin_col, _Gctx_end_row, _Gctx_end_col, _Mglc_Estmt_type_Cwhile);
if(_Mglc_Srdr_Pbool_1(_Lr_1)) {
struct _Mglc_Sstmt_space* _Lspace2_3;
_Mglc_Pquick_alloc_one_1(_Lspace2_3);
(*_Ls_2)._Fcontinue = _Lspace2_3;
_Mglc_Sstmt_space_Prd_3(_Lspace2_3, _Lr_1, _Lspace_0);
}
_Gnest_stack_id_v[_Gnest_stack_c] = _Gnest_id++;
_Gnest_stack_ptr_v[_Gnest_stack_c]._Fwhile = _Ls_2;
_Gnest_stack_c++;
}
void _Mglc_Sstmt_space_Prd_while_end_2(struct _Mglc_Sstmt_space* _Lspace_0, union _Mglc_Srdr* _Lr_1) {
struct _Mglc_Sstmt_while* _Lwhile_2;
struct _Mglc_Sstmt_while_end* _Ls_3;
_Lwhile_2 = _Gnest_stack_ptr_v[(_Gnest_stack_c -= 1)]._Fwhile;
_Mglc_Pquick_alloc_one_1(_Ls_3);
(*_Ls_3)._Fwhile = _Lwhile_2;
(*_Lwhile_2)._Fend = _Ls_3;
_Mglc_Sstmt_space_Pstmt_push_7(_Lspace_0, &(*_Ls_3)._Fbase, 0, 0, 0, 0, _Mglc_Estmt_type_Cwhile_end);
}
void _Mglc_Sstmt_space_Prd_continue_2(struct _Mglc_Sstmt_space* _Lspace_0, union _Mglc_Srdr* _Lr_1) {
struct _Mglc_Sstmt_continue* _Ls_2;
_Mglc_Pquick_alloc_one_1(_Ls_2);
(*_Ls_2)._Fnest = _Mglc_Srdr_Pn1_1(_Lr_1);
_Mglc_Sstmt_space_Pstmt_push_7(_Lspace_0, &(*_Ls_2)._Fbase, _Gctx_begin_row, _Gctx_begin_col, _Gctx_end_row, _Gctx_end_col, _Mglc_Estmt_type_Ccontinue);
}
void _Mglc_Sstmt_space_Prd_break_2(struct _Mglc_Sstmt_space* _Lspace_0, union _Mglc_Srdr* _Lr_1) {
struct _Mglc_Sstmt_break* _Ls_2;
_Mglc_Pquick_alloc_one_1(_Ls_2);
(*_Ls_2)._Fnest = _Mglc_Srdr_Pn1_1(_Lr_1);
_Mglc_Sstmt_space_Pstmt_push_7(_Lspace_0, &(*_Ls_2)._Fbase, _Gctx_begin_row, _Gctx_begin_col, _Gctx_end_row, _Gctx_end_col, _Mglc_Estmt_type_Cbreak);
}
void _Mglc_Sstmt_space_Prd_return_2(struct _Mglc_Sstmt_space* _Lspace_0, union _Mglc_Srdr* _Lr_1) {
struct _Mglc_Sstmt_return* _Ls_2;
_Mglc_Pquick_alloc_one_1(_Ls_2);
_Mglc_Eexpr_Prd_2(&(*_Ls_2)._Fexpr, _Lr_1);
_Mglc_Sstmt_space_Pstmt_push_7(_Lspace_0, &(*_Ls_2)._Fbase, _Gctx_begin_row, _Gctx_begin_col, _Gctx_end_row, _Gctx_end_col, _Mglc_Estmt_type_Creturn);
}
void _Mglc_Sstmt_space_Prd_space_2(struct _Mglc_Sstmt_space* _Lspace_0, union _Mglc_Srdr* _Lr_1) {
struct _Mglc_Sstmt_space* _Ls_2;
_Mglc_Pquick_alloc_one_1(_Ls_2);
_Mglc_Sstmt_space_Prd_3(_Ls_2, _Lr_1, _Lspace_0);
_Mglc_Sstmt_space_Pstmt_push_7(_Lspace_0, &(*_Ls_2)._Fbase, _Gctx_begin_row, _Gctx_begin_col, _Gctx_end_row, _Gctx_end_col, _Mglc_Estmt_type_Cspace);
}
void _Mglc_Sstmt_Pprocess_expr_2(struct _Mglc_Sstmt* _Lstmt_0, bool* _Lok_1) {
struct _Mglc_Sstmt_expr* _Ls_2;
_Ls_2 = _Lstmt_0;
if(!(_Mglc_Eexpr_Pprocess_1((*_Ls_2)._Fexpr))) {
return;
}
(*_Lok_1) = true;
}
void _Mglc_Sstmt_Pprocess_if_2(struct _Mglc_Sstmt* _Lstmt_0, bool* _Lok_1) {
struct _Mglc_Sstmt_if* _Ls_2;
_Ls_2 = _Lstmt_0;
if(!(_Mglc_Eexpr_Pvalue_4((*_Ls_2)._Fexpr, 1, false, &(*_Ls_2)._Fval))) {
return;
}
(*_Lok_1) = true;
}
void _Mglc_Sstmt_Pprocess_if_elif_2(struct _Mglc_Sstmt* _Lstmt_0, bool* _Lok_1) {
struct _Mglc_Sstmt_if_elif* _Ls_2;
_Ls_2 = _Lstmt_0;
if(!(_Mglc_Eexpr_Pvalue_4((*_Ls_2)._Fexpr, 1, false, &(*_Ls_2)._Fval))) {
return;
}
(*_Lok_1) = true;
}
void _Mglc_Sstmt_Pprocess_if_else_2(struct _Mglc_Sstmt* _Lstmt_0, bool* _Lok_1) {
struct _Mglc_Sstmt_if_else* _Ls_2;
_Ls_2 = _Lstmt_0;
(*_Lok_1) = true;
}
void _Mglc_Sstmt_Pprocess_if_end_2(struct _Mglc_Sstmt* _Lstmt_0, bool* _Lok_1) {
struct _Mglc_Sstmt_if_end* _Ls_2;
_Ls_2 = _Lstmt_0;
(*_Lok_1) = true;
}
void _Mglc_Sstmt_Pprocess_switch_2(struct _Mglc_Sstmt* _Lstmt_0, bool* _Lok_1) {
struct _Mglc_Sstmt_switch* _Ls_2;
_Ls_2 = _Lstmt_0;
_Gswitch_stack_v[_Gswitch_stack_c++] = _Ls_2;
if(!(_Mglc_Eexpr_Pvalue_4((*_Ls_2)._Fexpr, 1, false, &(*_Ls_2)._Fval))) {
return;
}
if((*_Ls_2)._Fval._Ftype == _Mglc_Eat_Cnil) {
fprintf(stdout, "%s:%u:%u: Error, the expression used for switch doesn't have a type\n", _Mglc_Efile_Ppath_1((*_Gctx_func)._Ffile), (*_Ls_2)._Fbase._Fbegin_row, (*_Ls_2)._Fbase._Fbegin_col);
return;
}
if((*_Ls_2)._Fcases != _Mglc_Eexpr_Cnil) {
struct _Mglc_Sat* _Ltype_3;
struct _Mglc_Sexpr_func* _Le_4;
_Mglc_Eid _Lfunc_name_5;
struct _Mglc_Sat* _Lf_6;
int32_t _Lcase_c_7;
int32_t _Lcase_cap_8;
_Mglc_Efunc* _Lcase_v_9;
_Ltype_3 = _Mglc_Eat_Pptr_1((*_Ls_2)._Fval._Ftype);
if((*_Ltype_3)._Ftype != _Mglc_Ename_type_Cenum) {
fprintf(stdout, "%s:%u:%u: Error, the expression used for switch must be an enum when using @case attribute\n", _Mglc_Efile_Ppath_1((*_Gctx_func)._Ffile), (*_Ls_2)._Fbase._Fbegin_row, (*_Ls_2)._Fbase._Fbegin_col);
return;
}
_Le_4 = _Mglc_Eexpr_Pptr_1((*_Ls_2)._Fcases);
_Lfunc_name_5 = (*_Le_4)._Ffunc_name;
_Lf_6 = _Mglc_Eat_Pptr_1((*_Gctx_func)._Fat);
_Lcase_c_7 = 0;
_Lcase_cap_8 = 0;
_Lcase_v_9 = NULL;
int32_t _Li_10;
_Li_10 = 0;
for(int i = (*_Lf_6)._Ffunc_c; i > 0; ) {
i --;
_Mglc_Efunc _Lfunc_i_11;
struct _Mglc_Sdecl_func* _Lfunc_12;
_Lfunc_i_11 = (*_Lf_6)._Ffunc_v[_Li_10];
_Lfunc_12 = _Mglc_Efunc_Pptr_1(_Lfunc_i_11);
if(((*_Lfunc_12)._Fflags & _Mglc_Efunc_flags_Ccase) != _Mglc_Efunc_flags_C0) {
if((*_Lfunc_12)._Fcase == _Lfunc_name_5) {
int32_t _Lci_13;
_Lci_13 = _Lcase_c_7++;
if(_Lcase_cap_8 <= _Lcase_c_7) {
int32_t _Lold_cap_14;
_Lold_cap_14 = _Lcase_cap_8;
_Mglc_Pgrow_2(_Lcase_cap_8, _Lcase_c_7);
_Mglc_Prealloc_3(_Lcase_v_9, _Lcase_cap_8, _Lold_cap_14);
}
_Lcase_v_9[_Lci_13] = _Lfunc_i_11;
}
}
continue_0:;
_Li_10++;
}
break_0:;
if(_Lcase_c_7 > 0) {
char* _Lfunc_name_str_15;
uint8_t _Lfunc_name_len_16;
struct _Mglc_Sstmt_switch_case_func* _Lfunc_v_17;
if(!(_Mglc_Eexpr_Pprocess_case_func_2(_Mglc_Eexpr_Pptr_1((*_Ls_2)._Fcases), _Lcase_v_9[0]))) {
return;
}
_Lfunc_name_str_15 = _Mglc_Eid_Pstr_1(_Lfunc_name_5);
_Lfunc_name_len_16 = _Mglc_Eid_Plen_1(_Lfunc_name_5);
(*_Ls_2)._Fcase_func_c = _Lcase_c_7;
_Mglc_Pquick_alloc_arr_2((*_Ls_2)._Fcase_func_v, _Lcase_c_7);
_Lfunc_v_17 = (*_Ls_2)._Fcase_func_v;
int32_t _Li_18;
_Li_18 = 0;
for(int i = _Lcase_c_7; i > 0; ) {
i --;
_Mglc_Efunc _Lfunc_i_19;
struct _Mglc_Sdecl_func* _Lfunc_20;
_Mglc_Eid _Lfunc_name2_21;
char* _Lcvar_name_str_22;
uint8_t _Lcvar_name_len_23;
_Mglc_Eid _Lfound_id_24;
_Mglc_Ecvar _Lfound_cvar_26;
_Lfunc_i_19 = _Lcase_v_9[_Li_18];
_Lfunc_20 = _Mglc_Efunc_Pptr_1(_Lfunc_i_19);
_Lfunc_name2_21 = (*_Lfunc_20)._Fdecl._Fname;
_Lcvar_name_str_22 = &_Mglc_Eid_Pstr_1(_Lfunc_name2_21)[(_Lfunc_name_len_16 + 1)];
_Lcvar_name_len_23 = (_Mglc_Eid_Plen_1(_Lfunc_name2_21) - (_Lfunc_name_len_16 + 1));
_Lfound_id_24 = _Mglc_Eid_Cnil;
_Mglc_Eid _Lj_25;
_Lj_25 = (_Mglc_Eid)(0);
for(int i = _Gid_c; i > 0; ) {
i --;
if(((_Mglc_Eid_Plen_1(_Lj_25) == _Lcvar_name_len_23) && (memcmp(_Mglc_Eid_Pstr_1(_Lj_25), _Lcvar_name_str_22, _Lcvar_name_len_23) == 0))) {
_Lfound_id_24 = _Lj_25;
goto break_2;
}
continue_2:;
_Lj_25++;
}
break_2:;
if(_Lfound_id_24 == _Mglc_Eid_Cnil) {
fprintf(stdout, "%s:%u:%u: Cannot find a case for cvar named '#%s'\n", _Mglc_Efile_Ppath_1((*_Lfunc_20)._Ffile), (*_Lfunc_20)._Fbegin_row, (*_Lfunc_20)._Fbegin_col, _Lcvar_name_str_22);
return;
}
_Lfound_cvar_26 = _Mglc_Ecvar_Cnil;
int32_t _Lj_27;
_Lj_27 = 0;
for(int i = (*_Ltype_3)._Fcvar_c; i > 0; ) {
i --;
_Mglc_Ecvar _Lcvar_i_28;
struct _Mglc_Scvar* _Lcvar_29;
_Lcvar_i_28 = (*_Ltype_3)._Fcvar_v[_Lj_27];
_Lcvar_29 = _Mglc_Ecvar_Pptr_1(_Lcvar_i_28);
if((*_Lcvar_29)._Fdecl._Fname == _Lfound_id_24) {
_Lfound_cvar_26 = _Lcvar_i_28;
goto break_3;
}
continue_3:;
_Lj_27++;
}
break_3:;
if(_Lfound_cvar_26 == _Mglc_Ecvar_Cnil) {
fprintf(stdout, "%s:%u:%u: Cannot find a case for cvar named '#%s'\n", _Mglc_Efile_Ppath_1((*_Lfunc_20)._Ffile), (*_Lfunc_20)._Fbegin_row, (*_Lfunc_20)._Fbegin_col, _Lcvar_name_str_22);
return;
}
if(!(_Mglc_Ecvar_Pprocess_1(_Lfound_cvar_26))) {
return;
}
_Mglc_Efunc_Pprocess_later_1(_Lfunc_i_19);
_Lfunc_v_17[_Li_18]._Fcvar = _Lfound_cvar_26;
_Lfunc_v_17[_Li_18]._Ffunc = _Lfunc_i_19;
continue_1:;
_Li_18++;
}
break_1:;
free(_Lcase_v_9);
}
}
(*_Lok_1) = true;
}
void _Mglc_Sstmt_Pprocess_case_2(struct _Mglc_Sstmt* _Lstmt_0, bool* _Lok_1) {
struct _Mglc_Sstmt_case* _Ls_2;
struct _Mglc_Sstmt_switch* _Lswitch_3;
_Ls_2 = _Lstmt_0;
_Lswitch_3 = _Gswitch_stack_v[(_Gswitch_stack_c - 1)];
if((*_Lswitch_3)._Fval._Ftype != _Mglc_Eat_Cnil) {
_Mglc_Eat _Ltype_i_4;
struct _Mglc_Sat* _Ltype_5;
_Ltype_i_4 = (*_Lswitch_3)._Fval._Ftype;
_Ltype_5 = _Mglc_Eat_Pptr_1(_Ltype_i_4);
if((*_Ltype_5)._Ftype == _Mglc_Ename_type_Cenum) {
int32_t _Li_6;
_Li_6 = 0;
for(int i = (*_Ls_2)._Fexpr_c; i > 0; ) {
i --;
_Mglc_Eexpr _Le_i_7;
struct _Mglc_Sexpr* _Le_8;
_Le_i_7 = (*_Ls_2)._Fexpr_v[_Li_6]._Fexpr;
_Le_8 = _Mglc_Eexpr_Pptr_1(_Le_i_7);
if((*_Le_8)._Ftype == _Mglc_Eexpr_type_Ccvar) {
struct _Mglc_Sexpr_cvar* _Le2_9;
_Le2_9 = _Le_8;
if((*_Le2_9)._Fat == _Mglc_Eat_Cnil) {
(*_Le2_9)._Ftry = _Ltype_i_4;
}
}
continue_0:;
_Li_6++;
}
break_0:;
}
}
int32_t _Li_10;
_Li_10 = 0;
for(int i = (*_Ls_2)._Fexpr_c; i > 0; ) {
i --;
_Mglc_Eexpr _Le_i_11;
_Le_i_11 = (*_Ls_2)._Fexpr_v[_Li_10]._Fexpr;
if(!(_Mglc_Eexpr_Pvalue_4(_Le_i_11, 1, true, &(*_Ls_2)._Fexpr_v[_Li_10]._Fval))) {
return;
}
continue_1:;
_Li_10++;
}
break_1:;
(*_Lok_1) = true;
}
void _Mglc_Sstmt_Pprocess_case_end_2(struct _Mglc_Sstmt* _Lstmt_0, bool* _Lok_1) {
struct _Mglc_Sstmt_case_end* _Ls_2;
_Ls_2 = _Lstmt_0;
(*_Lok_1) = true;
}
void _Mglc_Sstmt_Pprocess_default_2(struct _Mglc_Sstmt* _Lstmt_0, bool* _Lok_1) {
(*_Lok_1) = true;
}
void _Mglc_Sstmt_Pprocess_default_end_2(struct _Mglc_Sstmt* _Lstmt_0, bool* _Lok_1) {
struct _Mglc_Sstmt_default_end* _Ls_2;
_Ls_2 = _Lstmt_0;
(*_Lok_1) = true;
}
void _Mglc_Sstmt_Pprocess_switch_end_2(struct _Mglc_Sstmt* _Lstmt_0, bool* _Lok_1) {
struct _Mglc_Sstmt_switch_end* _Ls_2;
_Gswitch_stack_c -= 1;
_Ls_2 = _Lstmt_0;
(*_Lok_1) = true;
}
void _Mglc_Sstmt_Pprocess_do_2(struct _Mglc_Sstmt* _Lstmt_0, bool* _Lok_1) {
struct _Mglc_Sstmt_do* _Ls_2;
_Ls_2 = _Lstmt_0;
if((*_Ls_2)._Fexpr != _Mglc_Eexpr_Cnil) {
if(!(_Mglc_Eexpr_Pprocess_1((*_Ls_2)._Fexpr))) {
return;
}
}
(*_Lok_1) = true;
}
void _Mglc_Sstmt_Pprocess_do_end_2(struct _Mglc_Sstmt* _Lstmt_0, bool* _Lok_1) {
struct _Mglc_Sstmt_do_end* _Ls_2;
struct _Mglc_Sstmt_space* _Lcontinue_3;
_Ls_2 = _Lstmt_0;
_Lcontinue_3 = (*(*_Ls_2)._Fdo)._Fcontinue;
if(_Lcontinue_3 != NULL) {
_Mglc_Sstmt_space_Pprocess_1(_Lcontinue_3);
}
(*_Lok_1) = true;
}
void _Mglc_Sstmt_Pprocess_while_2(struct _Mglc_Sstmt* _Lstmt_0, bool* _Lok_1) {
struct _Mglc_Sstmt_while* _Ls_2;
_Ls_2 = _Lstmt_0;
if((*_Ls_2)._Fexpr != _Mglc_Eexpr_Cnil) {
if(!(_Mglc_Eexpr_Pprocess_1((*_Ls_2)._Fexpr))) {
return;
}
}
(*_Lok_1) = true;
}
void _Mglc_Sstmt_Pprocess_while_end_2(struct _Mglc_Sstmt* _Lstmt_0, bool* _Lok_1) {
struct _Mglc_Sstmt_while_end* _Ls_2;
struct _Mglc_Sstmt_space* _Lcontinue_3;
_Ls_2 = _Lstmt_0;
_Lcontinue_3 = (*(*_Ls_2)._Fwhile)._Fcontinue;
if(_Lcontinue_3 != NULL) {
_Mglc_Sstmt_space_Pprocess_1(_Lcontinue_3);
}
(*_Lok_1) = true;
}
void _Mglc_Sstmt_Pprocess_continue_2(struct _Mglc_Sstmt* _Lstmt_0, bool* _Lok_1) {
struct _Mglc_Sstmt_continue* _Ls_2;
_Ls_2 = _Lstmt_0;
(*_Lok_1) = true;
}
void _Mglc_Sstmt_Pprocess_break_2(struct _Mglc_Sstmt* _Lstmt_0, bool* _Lok_1) {
struct _Mglc_Sstmt_break* _Ls_2;
_Ls_2 = _Lstmt_0;
(*_Lok_1) = true;
}
void _Mglc_Sstmt_Pprocess_return_2(struct _Mglc_Sstmt* _Lstmt_0, bool* _Lok_1) {
struct _Mglc_Sstmt_return* _Ls_2;
_Ls_2 = _Lstmt_0;
if((*_Ls_2)._Fexpr != _Mglc_Eexpr_Cnil) {
_Mglc_Eexpr_Ptry_deduce_2((*_Ls_2)._Fexpr, (*_Gctx_func)._Fdecl._Ftype);
if(!(_Mglc_Eexpr_Pvalue_4((*_Ls_2)._Fexpr, 1 + (*_Gctx_func)._Fdecl._Ftype_info._Fref_v[(*_Gctx_func)._Fdecl._Ftype_info._Farray_c], false, &(*_Ls_2)._Fval))) {
return;
}
}
(*_Lok_1) = true;
}
void _Mglc_Sstmt_Pprocess_space_2(struct _Mglc_Sstmt* _Lstmt_0, bool* _Lok_1) {
struct _Mglc_Sstmt_space* _Lspace_2;
_Lspace_2 = _Lstmt_0;
if(!(_Mglc_Sstmt_space_Pprocess_1(_Lspace_2))) {
return;
}
(*_Lok_1) = true;
}
bool _Mglc_Sdecl_var_Pprocess_3(struct _Mglc_Sdecl_var* _Lvd_0, int32_t _Lrow_1, int32_t _Lcol_2) {
_Mglc_Eat _Lat_i_3;
struct _Mglc_Sat* _Lat_4;
_Lat_i_3 = (*_Lvd_0)._Ftype;
_Lat_4 = _Mglc_Eat_Pptr_1(_Lat_i_3);
if((((*_Lat_4)._Ftype != _Mglc_Ename_type_Cbasic) && ((*_Lat_4)._Fdecl._Fstruct == _Mglc_Estruct_Cnil))) {
fprintf(stdout, "%s:%u:%u: Error, the type '%s' used in '%s' was not defined\n", _Mglc_Efile_Ppath_1((*_Gctx_func)._Ffile), _Lrow_1, _Lcol_2, _Mglc_Eid_Pstr_1((*_Lat_4)._Fname._Fid), _Mglc_Eid_Pstr_1((*_Lvd_0)._Fname));
return false;
}
_Mglc_Eat_Poutput_4(_Lat_i_3, (*_Gctx_func)._Ffile, _Lrow_1, _Lcol_2);
if(!(_Mglc_Eat_Pfinalize_4(_Lat_i_3, &(*_Lvd_0)._Ftype_info, _Lrow_1, _Lcol_2))) {
return false;
}
int32_t _Li_5;
_Li_5 = 0;
for(int i = (*_Lvd_0)._Fsize_c; i > 0; ) {
i --;
if(!(_Mglc_Eexpr_Pvalue_4((*_Lvd_0)._Fsize_expr_v[_Li_5], 1, false, &(*_Lvd_0)._Fsize_value_v[_Li_5]))) {
return false;
}
continue_0:;
_Li_5++;
}
break_0:;
return true;
}
void _Mglc_Eexpr_Pprocess_assign_2(struct _Mglc_Sexpr* _Lexpr_0, bool* _Lok_1) {
struct _Mglc_Sexpr_assign* _Le_2;
struct _Mglc_Sexpr* _Lleft_e_3;
_Le_2 = _Lexpr_0;
_Lleft_e_3 = _Mglc_Eexpr_Pptr_1((*_Le_2)._Fleft);
if((*_Lleft_e_3)._Ftype == _Mglc_Eexpr_type_Clvar) {
struct _Mglc_Sexpr_lvar* _Lleft_4;
struct _Mglc_Slvar* _Llvar_5;
_Lleft_4 = _Lleft_e_3;
_Llvar_5 = _Mglc_Elvar_Pptr_1((*_Lleft_4)._Flvar);
if((*_Llvar_5)._Fdecl._Ftype == _Mglc_Eat_Cnil) {
struct _Mglc_Sat* _Lat_6;
if(!(_Mglc_Eexpr_Pvalue_4((*_Le_2)._Fright, 1, true, &(*_Le_2)._Fright_val))) {
return;
}
(*_Llvar_5)._Fdecl._Ftype = (*_Le_2)._Fright_val._Ftype;
_Lat_6 = _Mglc_Eat_Pptr_1((*_Llvar_5)._Fdecl._Ftype);
_Mglc_Stype_info_Pinit_1(&(*_Llvar_5)._Fdecl._Ftype_info);
_Mglc_Stype_info_Pcopy_from_2(&(*_Llvar_5)._Fdecl._Ftype_info, &(*_Le_2)._Fright_val._Finfo);
_Mglc_Eexpr_Pvalue_4((*_Le_2)._Fleft, 1, true, &(*_Le_2)._Fleft_val);
(*_Lok_1) = true;
return;
}
}
if(!(_Mglc_Eexpr_Pvalue_4((*_Le_2)._Fleft, 1, true, &(*_Le_2)._Fleft_val))) {
return;
}
_Mglc_Eexpr_Ptry_deduce_2((*_Le_2)._Fright, _Mglc_Eexpr_Ptype_1((*_Le_2)._Fleft));
if(!(_Mglc_Eexpr_Pvalue_4((*_Le_2)._Fright, 1, true, &(*_Le_2)._Fright_val))) {
return;
}
(*_Lok_1) = true;
}
void _Mglc_Eexpr_Pprocess_compare_2(struct _Mglc_Sexpr* _Lexpr_0, bool* _Lok_1) {
struct _Mglc_Sexpr_compare* _Le_2;
_Le_2 = _Lexpr_0;
if(!(_Mglc_Eexpr_Pvalue_4((*_Le_2)._Fleft, 1, true, &(*_Le_2)._Fleft_val))) {
return;
}
_Mglc_Eexpr_Ptry_deduce_2((*_Le_2)._Fright, (*_Le_2)._Fleft_val._Ftype);
if(!(_Mglc_Eexpr_Pvalue_4((*_Le_2)._Fright, 1, true, &(*_Le_2)._Fright_val))) {
return;
}
(*_Lok_1) = true;
}
void _Mglc_Eexpr_Pprocess_bool_2(struct _Mglc_Sexpr* _Lexpr_0, bool* _Lok_1) {
_Ginclude_stdbool = true;
(*_Lok_1) = true;
}
void _Mglc_Eexpr_Pprocess_char_2(struct _Mglc_Sexpr* _Lexpr_0, bool* _Lok_1) {
(*_Lok_1) = true;
}
void _Mglc_Eexpr_Pprocess_math_2(struct _Mglc_Sexpr* _Lexpr_0, bool* _Lok_1) {
struct _Mglc_Sexpr_math* _Le_2;
_Le_2 = _Lexpr_0;
if(!(_Mglc_Eexpr_Pvalue_4((*_Le_2)._Fleft, 1, true, &(*_Le_2)._Fleft_val))) {
return;
}
_Mglc_Eexpr_Ptry_deduce_2((*_Le_2)._Fright, (*_Le_2)._Fleft_val._Ftype);
if(!(_Mglc_Eexpr_Pvalue_4((*_Le_2)._Fright, 1, true, &(*_Le_2)._Fright_val))) {
return;
}
int32_t _Li_3;
_Li_3 = 0;
for(int i = (*_Le_2)._Fitem_c; i > 0; ) {
i --;
struct _Mglc_Sexpr_math_item* _Litem_4;
_Litem_4 = (&(*_Le_2)._Fitem_v[_Li_3]);
if(!(_Mglc_Eexpr_Pvalue_4((*_Litem_4)._Fexpr, 1, true, &(*_Litem_4)._Fval))) {
return;
}
continue_0:;
_Li_3++;
}
break_0:;
(*_Lok_1) = true;
}
void _Mglc_Eexpr_Pprocess_unary_2(struct _Mglc_Sexpr* _Lexpr_0, bool* _Lok_1) {
struct _Mglc_Sexpr_unary* _Le_2;
_Le_2 = _Lexpr_0;
if(!(_Mglc_Eexpr_Pvalue_4((*_Le_2)._Fexpr, 1, true, &(*_Le_2)._Fval))) {
return;
}
(*_Lok_1) = true;
}
void _Mglc_Eexpr_Pprocess_ref_2(struct _Mglc_Sexpr* _Lexpr_0, bool* _Lok_1) {
struct _Mglc_Sexpr_ref* _Le_2;
_Le_2 = _Lexpr_0;
if(!(_Mglc_Eexpr_Pvalue_4((*_Le_2)._Fexpr, 2, false, &(*_Le_2)._Fval))) {
return;
}
(*_Lok_1) = true;
}
void _Mglc_Eexpr_Pprocess_cast_fast_2(struct _Mglc_Sexpr* _Lexpr_0, bool* _Lok_1) {
struct _Mglc_Sexpr_cast_fast* _Le_2;
_Le_2 = _Lexpr_0;
if(!(_Mglc_Eexpr_Pvalue_4((*_Le_2)._Fexpr, 1, false, &(*_Le_2)._Fval))) {
return;
}
_Mglc_Eat_Poutput_4((*_Le_2)._Ftype, (*_Gctx_func)._Ffile, _Gctx_begin_row, _Gctx_begin_col);
(*_Lok_1) = true;
}
void _Mglc_Eexpr_Pprocess_lvar_2(struct _Mglc_Sexpr* _Lexpr_0, bool* _Lok_1) {
struct _Mglc_Sexpr_lvar* _Le_2;
_Le_2 = _Lexpr_0;
if(!(_Mglc_Elvar_Pprocess_1((*_Le_2)._Flvar))) {
return;
}
(*_Lok_1) = true;
}
void _Mglc_Eexpr_Pprocess_fvar_2(struct _Mglc_Sexpr* _Lexpr_0, bool* _Lok_1) {
struct _Mglc_Sexpr_fvar* _Le_2;
_Mglc_Eat _Ltype_i_3;
struct _Mglc_Sat* _Ltype_4;
_Mglc_Estruct _Lstruct_i_5;
struct _Mglc_Sstruct* _Lstruct_6;
_Mglc_Eid _Lmember_7;
_Le_2 = _Lexpr_0;
_Ltype_i_3 = _Mglc_Eexpr_Ptype_1((*_Le_2)._Fexpr);
if(_Ltype_i_3 == _Mglc_Eat_Cnil) {
fprintf(stdout, "%s:%u:%u - %u:%u Cannot get member '.%s' from an expression of unknown type\n", _Mglc_Efile_Ppath_1((*_Gctx_func)._Ffile), _Gctx_begin_row, _Gctx_begin_col, _Gctx_end_row, _Gctx_end_col, _Mglc_Eid_Pstr_1((*_Le_2)._Fmember));
return;
}
_Ltype_4 = _Mglc_Eat_Pptr_1(_Ltype_i_3);
if((*_Ltype_4)._Ftype != _Mglc_Ename_type_Cstruct) {
fprintf(stdout, "%s:%u:%u - %u:%u Cannot get member '.%s' because the type is not a struct or union\n", _Mglc_Efile_Ppath_1((*_Gctx_func)._Ffile), _Gctx_begin_row, _Gctx_begin_col, _Gctx_end_row, _Gctx_end_col, _Mglc_Eid_Pstr_1((*_Le_2)._Fmember));
return;
}
if(!(_Mglc_Eexpr_Pvalue_4((*_Le_2)._Fexpr, 1 - _Mglc_Eat_Ppointer_1(_Ltype_i_3), true, &(*_Le_2)._Fval))) {
return;
}
if((*_Le_2)._Fval._Finfo._Farray_c > 0) {
fprintf(stdout, "%s:%u:%u - %u:%u Cannot get member '.%s' because the expression is an array(%d)\n", _Mglc_Efile_Ppath_1((*_Gctx_func)._Ffile), _Gctx_begin_row, _Gctx_begin_col, _Gctx_end_row, _Gctx_end_col, _Mglc_Eid_Pstr_1((*_Le_2)._Fmember), (*_Le_2)._Fval._Finfo._Farray_c);
return;
}
if((*_Ltype_4)._Fdecl._Fstruct == _Mglc_Estruct_Cnil) {
fprintf(stdout, "%s:%u:%u - %u:%u Cannot get member '.%s' because the type '/%s' was not defined\n", _Mglc_Efile_Ppath_1((*_Gctx_func)._Ffile), _Gctx_begin_row, _Gctx_begin_col, _Gctx_end_row, _Gctx_end_col, _Mglc_Eid_Pstr_1((*_Le_2)._Fmember), _Mglc_Eid_Pstr_1((*_Ltype_4)._Fname._Fid));
return;
}
_Lstruct_i_5 = (*_Ltype_4)._Fdecl._Fstruct;
_Lstruct_6 = _Mglc_Estruct_Pptr_1(_Lstruct_i_5);
_Lmember_7 = (*_Le_2)._Fmember;
_Mglc_Efvar _Li_8;
_Li_8 = (_Mglc_Efvar)(0);
for(int i = (*_Lstruct_6)._Ffvar_c; i > 0; ) {
i --;
if((*_Lstruct_6)._Ffvar_v[_Li_8]._Fdecl._Fname == _Lmember_7) {
(*_Le_2)._Ffvar = _Li_8;
(*_Lok_1) = true;
return;
}
continue_0:;
_Li_8++;
}
break_0:;
fprintf(stdout, "%s:%u:%u - %u:%u Cannot find member named '.%s' from type '/%s'\n", _Mglc_Efile_Ppath_1((*_Gctx_func)._Ffile), _Gctx_begin_row, _Gctx_begin_col, _Gctx_end_row, _Gctx_end_col, _Mglc_Eid_Pstr_1((*_Le_2)._Fmember), _Mglc_Eid_Pstr_1((*_Ltype_4)._Fname._Fid));
}
void _Mglc_Eexpr_Pprocess_gvar_2(struct _Mglc_Sexpr* _Lexpr_0, bool* _Lok_1) {
struct _Mglc_Sexpr_gvar* _Le_2;
_Le_2 = _Lexpr_0;
if(!(_Mglc_Egvar_Pprocess_1((*_Le_2)._Fgvar))) {
return;
}
(*_Lok_1) = true;
}
void _Mglc_Eexpr_Pprocess_cvar_2(struct _Mglc_Sexpr* _Lexpr_0, bool* _Lok_1) {
struct _Mglc_Sexpr_cvar* _Le_2;
_Mglc_Eid _Lname_3;
int32_t _Lcvar_c_5;
_Mglc_Ecvar* _Lcvar_v_6;
_Le_2 = _Lexpr_0;
_Lname_3 = (*_Le_2)._Fname;
if((*_Le_2)._Ftry != _Mglc_Eat_Cnil) {
struct _Mglc_Sat* _Lat_4;
_Lat_4 = _Mglc_Eat_Pptr_1((*_Le_2)._Ftry);
_Lcvar_c_5 = (*_Lat_4)._Fcvar_c;
_Lcvar_v_6 = (*_Lat_4)._Fcvar_v;
int32_t _Li_7;
_Li_7 = 0;
for(int i = _Lcvar_c_5; i > 0; ) {
i --;
_Mglc_Ecvar _Lcvar_8;
_Lcvar_8 = _Lcvar_v_6[_Li_7];
if((*_Mglc_Ecvar_Pptr_1(_Lcvar_8))._Fdecl._Fname == _Lname_3) {
if(!(_Mglc_Ecvar_Pprocess_1(_Lcvar_8))) {
return;
}
(*_Le_2)._Fcvar = _Lcvar_8;
(*_Lok_1) = true;
return;
}
continue_0:;
_Li_7++;
}
break_0:;
}
if((*_Le_2)._Fat != _Mglc_Eat_Cnil) {
struct _Mglc_Sat* _Lat_9;
_Lat_9 = _Mglc_Eat_Pptr_1((*_Le_2)._Fat);
_Lcvar_c_5 = (*_Lat_9)._Fcvar_c;
_Lcvar_v_6 = (*_Lat_9)._Fcvar_v;
} else {
struct _Mglc_Sat* _Lat_10;
_Lat_10 = _Mglc_Eat_Pptr_1((*_Gctx_func)._Fat);
_Lcvar_c_5 = (*_Lat_10)._Fcvar_c;
_Lcvar_v_6 = (*_Lat_10)._Fcvar_v;
}
int32_t _Li_11;
_Li_11 = 0;
for(int i = _Lcvar_c_5; i > 0; ) {
i --;
_Mglc_Ecvar _Lcvar_12;
_Lcvar_12 = _Lcvar_v_6[_Li_11];
if((*_Mglc_Ecvar_Pptr_1(_Lcvar_12))._Fdecl._Fname == _Lname_3) {
if(!(_Mglc_Ecvar_Pprocess_1(_Lcvar_12))) {
return;
}
(*_Le_2)._Fcvar = _Lcvar_12;
(*_Lok_1) = true;
return;
}
continue_1:;
_Li_11++;
}
break_1:;
fprintf(stdout, "%s:%u:%u - %u:%u: Cannot find #%s\n", _Mglc_Efile_Ppath_1((*_Gctx_func)._Ffile), _Gctx_begin_row, _Gctx_begin_col, _Gctx_end_row, _Gctx_end_col, _Mglc_Eid_Pstr_1(_Lname_3));
}
void _Mglc_Eexpr_Pprocess_bools_2(struct _Mglc_Sexpr* _Lexpr_0, bool* _Lok_1) {
struct _Mglc_Sexpr_bools* _Le_2;
_Le_2 = _Lexpr_0;
if(!(_Mglc_Eexpr_Pvalue_4((*_Le_2)._Fleft, 1, true, &(*_Le_2)._Fleft_val))) {
return;
}
if(!(_Mglc_Eexpr_Pvalue_4((*_Le_2)._Fright, 1, true, &(*_Le_2)._Fright_val))) {
return;
}
int32_t _Li_3;
_Li_3 = 0;
for(int i = (*_Le_2)._Fitem_c; i > 0; ) {
i --;
struct _Mglc_Sexpr_bools_item* _Litem_4;
_Litem_4 = (&(*_Le_2)._Fitem_v[_Li_3]);
if(!(_Mglc_Eexpr_Pvalue_4((*_Litem_4)._Fexpr, 1, true, &(*_Litem_4)._Fval))) {
return;
}
continue_0:;
_Li_3++;
}
break_0:;
(*_Lok_1) = true;
}
void _Mglc_Eexpr_Pprocess_method_2(struct _Mglc_Sexpr* _Lexpr_0, bool* _Lok_1) {
struct _Mglc_Sexpr_method* _Le_2;
_Mglc_Eid _Lfunc_name_3;
uint8_t _Lgroup_c_4;
uint8_t* _Lgroup_v_5;
uint8_t _Lcarg_c_6;
uint8_t _Lcarg_c1_7;
_Mglc_Eat _Lat_idx_8;
struct _Mglc_Sat* _Lat_9;
int32_t _Lmethod_c_10;
_Mglc_Efunc* _Lmethod_v_11;
int32_t _Lfound_16;
int32_t _Lsimilar_c_17;
_Le_2 = _Lexpr_0;
_Lfunc_name_3 = (*_Le_2)._Ffunc_name;
_Lgroup_c_4 = (*_Le_2)._Fgroup_c;
_Lgroup_v_5 = (*_Le_2)._Fgroup_v;
_Lcarg_c_6 = (*_Le_2)._Fcarg_c;
_Lcarg_c1_7 = (_Lcarg_c_6 + 1);
_Lat_idx_8 = _Mglc_Eexpr_Ptype_1((*_Le_2)._Fthis);
if(_Lat_idx_8 == _Mglc_Eat_Cnil) {
fprintf(stdout, "%s:%u:%u - %u:%u: Cannot call method :%s on a value without a type\n", _Mglc_Efile_Ppath_1((*_Gctx_func)._Ffile), _Gctx_begin_row, _Gctx_begin_col, _Gctx_end_row, _Gctx_end_col, _Mglc_Eid_Pstr_1(_Lfunc_name_3));
return;
}
_Lat_9 = _Mglc_Eat_Pptr_1(_Lat_idx_8);
if((*_Lat_9)._Ftype == _Mglc_Ename_type_Cbasic) {
struct _Mglc_Sbasic_type* _Lt_12;
_Lt_12 = (&_Gbasic_type[(*_Lat_9)._Fname._Fbasic]);
_Lmethod_c_10 = (*_Lt_12)._Fmethod_c;
_Lmethod_v_11 = (*_Lt_12)._Fmethod_v;
} else {
if((((*_Lat_9)._Fdecl._Fstruct == _Mglc_Estruct_Cnil) && ((*_Lat_9)._Ftype != _Mglc_Ename_type_Cbasic) && ((*_Lat_9)._Ftype != _Mglc_Ename_type_Cmodule))) {
char _Lc_13;
if((*_Lat_9)._Ftype == _Mglc_Ename_type_Cstruct) {
_Lc_13 = '/';
} else {
_Lc_13 = '\\';
}
fprintf(stdout, "%s:%u:%u - %u:%u: Cannot call method :%s because the type %c%s is not defined\n", _Mglc_Efile_Ppath_1((*_Gctx_func)._Ffile), _Gctx_begin_row, _Gctx_begin_col, _Gctx_end_row, _Gctx_end_col, _Mglc_Eid_Pstr_1(_Lfunc_name_3), _Lc_13, _Mglc_Eid_Pstr_1((*_Lat_9)._Fname._Fid));
return;
}
if((*_Lat_9)._Ftype == _Mglc_Ename_type_Cstruct) {
struct _Mglc_Sstruct* _Lt_14;
_Lt_14 = _Mglc_Estruct_Pptr_1((*_Lat_9)._Fdecl._Fstruct);
_Lmethod_c_10 = (*_Lt_14)._Fmethod_c;
_Lmethod_v_11 = (*_Lt_14)._Fmethod_v;
} else if((*_Lat_9)._Ftype == _Mglc_Ename_type_Cenum) {
struct _Mglc_Senum* _Lt_15;
_Lt_15 = _Mglc_Eenum_Pptr_1((*_Lat_9)._Fdecl._Fenum);
_Lmethod_c_10 = (*_Lt_15)._Fmethod_c;
_Lmethod_v_11 = (*_Lt_15)._Fmethod_v;
}
}
_Lfound_16 = -1;
_Lsimilar_c_17 = 0;
int32_t _Li_18;
_Li_18 = 0;
for(int i = _Lmethod_c_10; i > 0; ) {
i --;
_Mglc_Efunc _Lf_idx_19;
struct _Mglc_Sdecl_func* _Lf_20;
bool _Lmatch_21;
int32_t _Lj_25;
int32_t _Lk_26;
_Lf_idx_19 = _Lmethod_v_11[_Li_18];
_Lf_20 = _Mglc_Efunc_Pptr_1(_Lf_idx_19);
if((*_Lf_20)._Fdecl._Fname != _Lfunc_name_3) {
goto continue_0;
}
_Lfound_16 = _Li_18;
_Lsimilar_c_17++;
if((*_Lf_20)._Fgroup_c != _Lgroup_c_4) {
goto continue_0;
}
_Lmatch_21 = true;
if(((*_Lf_20)._Fflags & _Mglc_Efunc_flags_Cvar_args) != _Mglc_Efunc_flags_C0) {
if((*_Lf_20)._Ffarg_c > _Lcarg_c1_7) {
goto continue_0;
}
int32_t _Lj_22;
_Lj_22 = 0;
for(int i = _Lgroup_c_4 - 1; i > 0; ) {
i --;
if((*_Lf_20)._Fthis_group == _Lj_22) {
if((*_Lf_20)._Fgroup_v[_Lj_22] != (_Lgroup_v_5[_Lj_22] + 1)) {
_Lmatch_21 = false;
goto break_1;
}
} else {
if((*_Lf_20)._Fgroup_v[_Lj_22] != _Lgroup_v_5[_Lj_22]) {
_Lmatch_21 = false;
goto break_1;
}
}
continue_1:;
_Lj_22++;
}
break_1:;
if(_Lmatch_21) {
uint8_t _Lj_23;
_Lj_23 = (_Lgroup_c_4 - 1);
if((*_Lf_20)._Fthis_group == _Lj_23) {
if((*_Lf_20)._Fgroup_v[_Lj_23] > (_Lgroup_v_5[_Lj_23] + 1)) {
_Lmatch_21 = false;
}
} else {
if((*_Lf_20)._Fgroup_v[_Lj_23] > _Lgroup_v_5[_Lj_23]) {
_Lmatch_21 = false;
}
}
}
} else {
if((*_Lf_20)._Ffarg_c != _Lcarg_c1_7) {
goto continue_0;
}
int32_t _Lj_24;
_Lj_24 = 0;
for(int i = _Lgroup_c_4; i > 0; ) {
i --;
if((*_Lf_20)._Fthis_group == _Lj_24) {
if((*_Lf_20)._Fgroup_v[_Lj_24] != (_Lgroup_v_5[_Lj_24] + 1)) {
_Lmatch_21 = false;
goto break_2;
}
} else {
if((*_Lf_20)._Fgroup_v[_Lj_24] != _Lgroup_v_5[_Lj_24]) {
_Lmatch_21 = false;
goto break_2;
}
}
continue_2:;
_Lj_24++;
}
break_2:;
}
if(!(_Lmatch_21)) {
goto continue_0;
}
_Mglc_Efunc_Pprocess_later_1(_Lf_idx_19);
_Lj_25 = 0;
_Lk_26 = 0;
for(int i = (*_Lf_20)._Fthis_idx; i > 0; ) {
i --;
struct _Mglc_Scarg* _Lca_27;
_Lca_27 = (&(*_Le_2)._Fcarg_v[_Lk_26]);
if(!(_Mglc_Pfarg_process_4((*_Lca_27)._Fexpr, (*_Lca_27)._Fref, &(*_Lca_27)._Fvalue, &(*_Lf_20)._Ffarg_v[_Lj_25]._Fdecl))) {
return;
}
continue_3:;
_Lj_25++;
_Lk_26++;
}
break_3:;
if(!(_Mglc_Pfarg_process_4((*_Le_2)._Fthis, 0, &(*_Le_2)._Fthis_value, &(*_Lf_20)._Ffarg_v[_Lj_25++]._Fdecl))) {
return;
}
for(int i = ((*_Lf_20)._Ffarg_c - 1) - (*_Lf_20)._Fthis_idx; i > 0; ) {
i --;
struct _Mglc_Scarg* _Lca_28;
_Lca_28 = (&(*_Le_2)._Fcarg_v[_Lk_26]);
if(!(_Mglc_Pfarg_process_4((*_Lca_28)._Fexpr, (*_Lca_28)._Fref, &(*_Lca_28)._Fvalue, &(*_Lf_20)._Ffarg_v[_Lj_25]._Fdecl))) {
return;
}
continue_4:;
_Lj_25++;
_Lk_26++;
}
break_4:;
(*_Le_2)._Ffunc_idx = _Lf_idx_19;
if(((*_Lf_20)._Fflags & _Mglc_Efunc_flags_Cvar_args) != _Mglc_Efunc_flags_C0) {
for(int i = (*_Le_2)._Fcarg_c - _Lk_26; i > 0; ) {
i --;
struct _Mglc_Scarg* _Lca_29;
int32_t _Lr_30;
_Lca_29 = (&(*_Le_2)._Fcarg_v[_Lk_26]);
if((*_Lca_29)._Fref) {
_Lr_30 = (1 + (*_Lca_29)._Fref);
} else {
_Lr_30 = 1;
}
if(!(_Mglc_Eexpr_Pvalue_4((*_Lca_29)._Fexpr, _Lr_30, false, &(*_Lca_29)._Fvalue))) {
return;
}
continue_5:;
_Lk_26++;
}
break_5:;
}
(*_Lok_1) = true;
return;
continue_0:;
_Li_18++;
}
break_0:;
fprintf(stdout, "%s:%u:%u - %u:%u: Cannot find method :%s with %u argument/s\n", _Mglc_Efile_Ppath_1((*_Gctx_func)._Ffile), _Gctx_begin_row, _Gctx_begin_col, _Gctx_end_row, _Gctx_end_col, _Mglc_Eid_Pstr_1(_Lfunc_name_3), _Lcarg_c_6);
if(_Lfound_16 != -1) {
fprintf(stdout, "But found %u functions with different no. of argument/s:\n", _Lsimilar_c_17);
int32_t _Li_31;
_Li_31 = 0;
for(int i = (*_Lat_9)._Ffunc_c; i > 0; ) {
i --;
_Mglc_Efunc _Lf_idx_32;
struct _Mglc_Sdecl_func* _Lf_33;
_Lf_idx_32 = (*_Lat_9)._Ffunc_v[_Li_31];
_Lf_33 = _Gfunc_v[_Lf_idx_32];
if((*_Lf_33)._Fdecl._Fname == _Lfunc_name_3) {
fprintf(stdout, "- :%s with %u args\n", _Mglc_Eid_Pstr_1(_Lfunc_name_3), (*_Lf_33)._Ffarg_c);
}
continue_6:;
_Li_31++;
}
break_6:;
}
}
void _Mglc_Eexpr_Pprocess_func_2(struct _Mglc_Sexpr* _Lexpr_0, bool* _Lok_1) {
struct _Mglc_Sexpr_func* _Le_2;
_Mglc_Eid _Lfunc_name_3;
uint8_t _Lcarg_c_4;
uint8_t _Lgroup_c_5;
uint8_t* _Lgroup_v_6;
_Mglc_Eat _Lat_idx_7;
struct _Mglc_Sat* _Lat_8;
int32_t _Lfound_10;
int32_t _Lsimilar_c_11;
_Le_2 = _Lexpr_0;
_Lfunc_name_3 = (*_Le_2)._Ffunc_name;
_Lcarg_c_4 = (*_Le_2)._Fcarg_c;
_Lgroup_c_5 = (*_Le_2)._Fgroup_c;
_Lgroup_v_6 = (*_Le_2)._Fgroup_v;
_Lat_idx_7 = (*_Le_2)._Fat;
if(_Lat_idx_7 == _Mglc_Eat_Cnil) {
_Lat_8 = _Mglc_Eat_Pptr_1((*_Gctx_func)._Fat);
} else {
_Lat_8 = _Mglc_Eat_Pptr_1(_Lat_idx_7);
}
if((((*_Lat_8)._Fdecl._Fstruct == _Mglc_Estruct_Cnil) && ((*_Lat_8)._Ftype != _Mglc_Ename_type_Cbasic) && ((*_Lat_8)._Ftype != _Mglc_Ename_type_Cmodule))) {
char _Lc_9;
if((*_Lat_8)._Ftype == _Mglc_Ename_type_Cstruct) {
_Lc_9 = '/';
} else {
_Lc_9 = '\\';
}
fprintf(stdout, "%s:%u:%u - %u:%u: Cannot call function :%s because the type %c%s is not defined\n", _Mglc_Efile_Ppath_1((*_Gctx_func)._Ffile), _Gctx_begin_row, _Gctx_begin_col, _Gctx_end_row, _Gctx_end_col, _Mglc_Eid_Pstr_1(_Lfunc_name_3), _Lc_9, _Mglc_Eid_Pstr_1((*_Lat_8)._Fname._Fid));
return;
}
_Lfound_10 = -1;
_Lsimilar_c_11 = 0;
int32_t _Li_12;
_Li_12 = 0;
for(int i = (*_Lat_8)._Ffunc_c; i > 0; ) {
i --;
_Mglc_Efunc _Lf_idx_13;
struct _Mglc_Sdecl_func* _Lf_14;
bool _Lmatch_15;
int32_t _Lj_19;
_Lf_idx_13 = (*_Lat_8)._Ffunc_v[_Li_12];
_Lf_14 = _Mglc_Efunc_Pptr_1(_Lf_idx_13);
if((*_Lf_14)._Fdecl._Fname != _Lfunc_name_3) {
goto continue_0;
}
_Lfound_10 = _Li_12;
_Lsimilar_c_11++;
if((*_Lf_14)._Fgroup_c != _Lgroup_c_5) {
goto continue_0;
}
_Lmatch_15 = true;
if(((*_Lf_14)._Fflags & _Mglc_Efunc_flags_Cvar_args) != _Mglc_Efunc_flags_C0) {
if((*_Lf_14)._Ffarg_c > _Lcarg_c_4) {
goto continue_0;
}
int32_t _Lj_16;
_Lj_16 = 0;
for(int i = _Lgroup_c_5 - 1; i > 0; ) {
i --;
if((*_Lf_14)._Fgroup_v[_Lj_16] != _Lgroup_v_6[_Lj_16]) {
_Lmatch_15 = false;
goto break_1;
}
continue_1:;
_Lj_16++;
}
break_1:;
if(_Lmatch_15) {
uint8_t _Lj_17;
_Lj_17 = (_Lgroup_c_5 - 1);
if((*_Lf_14)._Fgroup_v[_Lj_17] > _Lgroup_v_6[_Lj_17]) {
_Lmatch_15 = false;
}
}
} else {
if((*_Lf_14)._Ffarg_c != _Lcarg_c_4) {
goto continue_0;
}
int32_t _Lj_18;
_Lj_18 = 0;
for(int i = _Lgroup_c_5; i > 0; ) {
i --;
if((*_Lf_14)._Fgroup_v[_Lj_18] != _Lgroup_v_6[_Lj_18]) {
_Lmatch_15 = false;
goto break_2;
}
continue_2:;
_Lj_18++;
}
break_2:;
}
if(!(_Lmatch_15)) {
goto continue_0;
}
_Mglc_Efunc_Pprocess_later_1(_Lf_idx_13);
_Lj_19 = 0;
for(int i = (*_Lf_14)._Ffarg_c; i > 0; ) {
i --;
struct _Mglc_Scarg* _Lca_20;
_Lca_20 = (&(*_Le_2)._Fcarg_v[_Lj_19]);
if(!(_Mglc_Pfarg_process_4((*_Lca_20)._Fexpr, (*_Lca_20)._Fref, &(*_Lca_20)._Fvalue, &(*_Lf_14)._Ffarg_v[_Lj_19]._Fdecl))) {
return;
}
continue_3:;
_Lj_19++;
}
break_3:;
(*_Le_2)._Ffunc_idx = _Lf_idx_13;
if(((*_Lf_14)._Fflags & _Mglc_Efunc_flags_Cvar_args) != _Mglc_Efunc_flags_C0) {
for(int i = (*_Le_2)._Fcarg_c - _Lj_19; i > 0; ) {
i --;
struct _Mglc_Scarg* _Lca_21;
int32_t _Lr_22;
_Lca_21 = (&(*_Le_2)._Fcarg_v[_Lj_19]);
if((*_Lca_21)._Fref) {
_Lr_22 = (1 + (*_Lca_21)._Fref);
} else {
_Lr_22 = 1;
}
if(!(_Mglc_Eexpr_Pvalue_4((*_Lca_21)._Fexpr, _Lr_22, false, &(*_Lca_21)._Fvalue))) {
return;
}
continue_4:;
_Lj_19++;
}
break_4:;
}
(*_Le_2)._Ffunc_idx = _Lf_idx_13;
(*_Lok_1) = true;
return;
continue_0:;
_Li_12++;
}
break_0:;
fprintf(stdout, "%s:%u:%u - %u:%u: Cannot find function :%s with %u argument/s\n", _Mglc_Efile_Ppath_1((*_Gctx_func)._Ffile), _Gctx_begin_row, _Gctx_begin_col, _Gctx_end_row, _Gctx_end_col, _Mglc_Eid_Pstr_1(_Lfunc_name_3), _Lcarg_c_4);
if(_Lfound_10 != -1) {
fprintf(stdout, "But found %u functions with different no. of argument/s:\n", _Lsimilar_c_11);
int32_t _Li_23;
_Li_23 = 0;
for(int i = (*_Lat_8)._Ffunc_c; i > 0; ) {
i --;
_Mglc_Efunc _Lf_idx_24;
struct _Mglc_Sdecl_func* _Lf_25;
_Lf_idx_24 = (*_Lat_8)._Ffunc_v[_Li_23];
_Lf_25 = _Gfunc_v[_Lf_idx_24];
if((*_Lf_25)._Fdecl._Fname == _Lfunc_name_3) {
fprintf(stdout, "- :%s with %u args\n", _Mglc_Eid_Pstr_1(_Lfunc_name_3), (*_Lf_25)._Ffarg_c);
}
continue_5:;
_Li_23++;
}
break_5:;
}
}
void _Mglc_Eexpr_Pprocess_str_2(struct _Mglc_Sexpr* _Lexpr_0, bool* _Lok_1) {
(*_Lok_1) = true;
}
void _Mglc_Eexpr_Pprocess_int_2(struct _Mglc_Sexpr* _Lexpr_0, bool* _Lok_1) {
(*_Lok_1) = true;
}
void _Mglc_Eexpr_Pprocess_size_of_type_2(struct _Mglc_Sexpr* _Lexpr_0, bool* _Lok_1) {
struct _Mglc_Sexpr_size_of_type* _Le_2;
_Le_2 = _Lexpr_0;
_Mglc_Eat_Poutput_4((*_Le_2)._Ftype, (*_Gctx_func)._Ffile, _Gctx_begin_row, _Gctx_begin_col);
(*_Lok_1) = true;
}
void _Mglc_Eexpr_Pprocess_null_2(struct _Mglc_Sexpr* _Lexpr_0, bool* _Lok_1) {
_Ginclude_stddef = true;
(*_Lok_1) = true;
}
void _Mglc_Eexpr_Pprocess_index_2(struct _Mglc_Sexpr* _Lexpr_0, bool* _Lok_1) {
struct _Mglc_Sexpr_index* _Le_2;
_Le_2 = _Lexpr_0;
if(!(_Mglc_Eexpr_Pvalue_4((*_Le_2)._Fleft, 1, true, &(*_Le_2)._Fleft_val))) {
return;
}
if(!(_Mglc_Eexpr_Pvalue_4((*_Le_2)._Fright, 1, true, &(*_Le_2)._Fright_val))) {
return;
}
(*_Lok_1) = true;
}
void _Mglc_Egvar_Pwrite_1(_Mglc_Egvar _Lg_0) {
struct _Mglc_Sdecl_gvar* _Lgvar_1;
_Lgvar_1 = _Mglc_Egvar_Pptr_1(_Lg_0);
_Mglc_Sdecl_var_Pwrite_2(&(*_Lgvar_1)._Fdecl, _Mglc_Edecl_var_type_Cgvar);
}
void _Mglc_Sexpr_cast_fast_Pwrite_value_2(struct _Mglc_Sexpr_cast_fast* _Le_0, struct _Mglc_Svalue* _Lv_1) {
fprintf(_Gout, "(");
_Mglc_Eat_Pwrite_type_info_3((*_Le_0)._Ftype, &(*_Lv_1)._Finfo, 0);
fprintf(_Gout, ")(");
_Mglc_Eexpr_Pwrite_value_2((*_Le_0)._Fexpr, &(*_Le_0)._Fval);
fprintf(_Gout, ")");
}
int32_t _Mglc_Eat_Ppointer_1(_Mglc_Eat _Ltd_0) {
if((*_Mglc_Eat_Pptr_1(_Ltd_0))._Ftype == _Mglc_Ename_type_Cstruct) {
return 1;
} else {
return 0;
}
}
void _Mglc_Sstmt_Pwrite_expr_1(struct _Mglc_Sstmt* _Lstmt_0) {
struct _Mglc_Sstmt_expr* _Ls_1;
_Ls_1 = _Lstmt_0;
_Mglc_Eexpr_Pwrite_1((*_Ls_1)._Fexpr);
fprintf(_Gout, ";\n");
}
void _Mglc_Sstmt_Pwrite_if_1(struct _Mglc_Sstmt* _Lstmt_0) {
struct _Mglc_Sstmt_if* _Ls_1;
_Ls_1 = _Lstmt_0;
if((*_Ls_1)._Fnot) {
fprintf(_Gout, "if(!(");
_Mglc_Eexpr_Pwrite_value_2((*_Ls_1)._Fexpr, &(*_Ls_1)._Fval);
fprintf(_Gout, ")) {\n");
} else {
fprintf(_Gout, "if(");
_Mglc_Eexpr_Pwrite_value_2((*_Ls_1)._Fexpr, &(*_Ls_1)._Fval);
fprintf(_Gout, ") {\n");
}
}
void _Mglc_Sstmt_Pwrite_if_elif_1(struct _Mglc_Sstmt* _Lstmt_0) {
struct _Mglc_Sstmt_if_elif* _Ls_1;
_Ls_1 = _Lstmt_0;
if((*_Ls_1)._Fnot) {
fprintf(_Gout, "} else if(!(");
_Mglc_Eexpr_Pwrite_value_2((*_Ls_1)._Fexpr, &(*_Ls_1)._Fval);
fprintf(_Gout, ")) {\n");
} else {
fprintf(_Gout, "} else if(");
_Mglc_Eexpr_Pwrite_value_2((*_Ls_1)._Fexpr, &(*_Ls_1)._Fval);
fprintf(_Gout, ") {\n");
}
}
void _Mglc_Sstmt_Pwrite_if_else_1(struct _Mglc_Sstmt* _Lstmt_0) {
struct _Mglc_Sstmt_if_else* _Ls_1;
_Ls_1 = _Lstmt_0;
fprintf(_Gout, "} else {\n");
}
void _Mglc_Sstmt_Pwrite_if_end_1(struct _Mglc_Sstmt* _Lstmt_0) {
struct _Mglc_Sstmt_if_end* _Ls_1;
_Ls_1 = _Lstmt_0;
fprintf(_Gout, "}\n");
}
void _Mglc_Sstmt_Pwrite_switch_1(struct _Mglc_Sstmt* _Lstmt_0) {
struct _Mglc_Sstmt_switch* _Ls_1;
_Ls_1 = _Lstmt_0;
fprintf(_Gout, "switch(");
_Mglc_Eexpr_Pwrite_value_2((*_Ls_1)._Fexpr, &(*_Ls_1)._Fval);
fprintf(_Gout, ") {\n");
if((*_Ls_1)._Fcase_func_c > 0) {
struct _Mglc_Sexpr* _Le_2;
struct _Mglc_Sexpr_func* _Lfunc_3;
struct _Mglc_Sstmt_switch_case_func* _Lv_4;
_Le_2 = _Mglc_Eexpr_Pptr_1((*_Ls_1)._Fcases);
_Lfunc_3 = _Le_2;
_Lv_4 = (*_Ls_1)._Fcase_func_v;
int32_t _Li_5;
_Li_5 = 0;
for(int i = (*_Ls_1)._Fcase_func_c; i > 0; ) {
i --;
fprintf(_Gout, "case ");
_Mglc_Ecvar_Pwrite_1(_Lv_4[_Li_5]._Fcvar);
fprintf(_Gout, ":;\n");
(*_Lfunc_3)._Ffunc_idx = _Lv_4[_Li_5]._Ffunc;
_Mglc_Eexpr_Pwrite_func_1(_Le_2);
fprintf(_Gout, ";\nbreak;\n");
continue_0:;
_Li_5++;
}
break_0:;
}
}
void _Mglc_Sstmt_Pwrite_case_1(struct _Mglc_Sstmt* _Lstmt_0) {
struct _Mglc_Sstmt_case* _Ls_1;
_Ls_1 = _Lstmt_0;
int32_t _Li_2;
_Li_2 = 0;
for(int i = (*_Ls_1)._Fexpr_c; i > 0; ) {
i --;
fprintf(_Gout, "case ");
_Mglc_Eexpr_Pwrite_value_2((*_Ls_1)._Fexpr_v[_Li_2]._Fexpr, &(*_Ls_1)._Fexpr_v[_Li_2]._Fval);
fprintf(_Gout, ":;\n");
continue_0:;
_Li_2++;
}
break_0:;
_Gcase_stack_v[_Gcase_stack_c++]._Fcase = _Ls_1;
}
void _Mglc_Sstmt_Pwrite_case_end_1(struct _Mglc_Sstmt* _Lstmt_0) {
struct _Mglc_Sstmt_case_end* _Ls_1;
struct _Mglc_Sstmt_case* _Lcase_2;
_Ls_1 = _Lstmt_0;
_Lcase_2 = _Gcase_stack_v[(_Gcase_stack_c -= 1)]._Fcase;
if(!((*_Lcase_2)._Ffall_through)) {
fprintf(_Gout, "break;\n");
}
}
void _Mglc_Sstmt_Pwrite_default_1(struct _Mglc_Sstmt* _Lstmt_0) {
struct _Mglc_Sstmt_default* _Ls_1;
_Ls_1 = _Lstmt_0;
fprintf(_Gout, "default:;\n");
_Gcase_stack_v[_Gcase_stack_c++]._Fdefault = _Ls_1;
}
void _Mglc_Sstmt_Pwrite_default_end_1(struct _Mglc_Sstmt* _Lstmt_0) {
struct _Mglc_Sstmt_default_end* _Ls_1;
struct _Mglc_Sstmt_default* _Ldefault_2;
_Ls_1 = _Lstmt_0;
_Ldefault_2 = _Gcase_stack_v[(_Gcase_stack_c -= 1)]._Fdefault;
if(!((*_Ldefault_2)._Ffall_through)) {
fprintf(_Gout, "break;\n");
}
}
void _Mglc_Sstmt_Pwrite_switch_end_1(struct _Mglc_Sstmt* _Lstmt_0) {
struct _Mglc_Sstmt_switch_end* _Ls_1;
_Ls_1 = _Lstmt_0;
fprintf(_Gout, "}\n");
}
void _Mglc_Sstmt_Pwrite_do_1(struct _Mglc_Sstmt* _Lstmt_0) {
struct _Mglc_Sstmt_do* _Ls_1;
_Ls_1 = _Lstmt_0;
_Gnest_stack_id_v[_Gnest_stack_c] = _Gnest_id++;
_Gnest_stack_ptr_v[_Gnest_stack_c]._Fdo = _Ls_1;
_Gnest_stack_c++;
if((*_Ls_1)._Fexpr == _Mglc_Eexpr_Cnil) {
fprintf(_Gout, "while(1) {\n");
} else {
fprintf(_Gout, "for(int i = ");
_Mglc_Eexpr_Pwrite_1((*_Ls_1)._Fexpr);
fprintf(_Gout, "; i > 0; ) {\ni --;\n");
}
}
void _Mglc_Sstmt_Pwrite_do_end_1(struct _Mglc_Sstmt* _Lstmt_0) {
int32_t _Lid_1;
struct _Mglc_Sstmt_do_end* _Ls_2;
struct _Mglc_Sstmt_space* _Lcontinue_3;
_Lid_1 = _Gnest_stack_id_v[(_Gnest_stack_c -= 1)];
_Ls_2 = _Lstmt_0;
fprintf(_Gout, "continue_%u:;\n", _Lid_1);
_Lcontinue_3 = (*(*_Ls_2)._Fdo)._Fcontinue;
if(_Lcontinue_3 != NULL) {
_Mglc_Sstmt_space_Pwrite_1(_Lcontinue_3);
}
fprintf(_Gout, "}\nbreak_%u:;\n", _Lid_1);
}
void _Mglc_Sstmt_Pwrite_while_1(struct _Mglc_Sstmt* _Lstmt_0) {
struct _Mglc_Sstmt_while* _Ls_1;
_Ls_1 = _Lstmt_0;
_Gnest_stack_id_v[_Gnest_stack_c] = _Gnest_id++;
_Gnest_stack_ptr_v[_Gnest_stack_c]._Fwhile = _Ls_1;
_Gnest_stack_c++;
fprintf(_Gout, "while(");
_Mglc_Eexpr_Pwrite_1((*_Ls_1)._Fexpr);
fprintf(_Gout, ") {\n");
}
void _Mglc_Sstmt_Pwrite_while_end_1(struct _Mglc_Sstmt* _Lstmt_0) {
int32_t _Lid_1;
struct _Mglc_Sstmt_while_end* _Ls_2;
struct _Mglc_Sstmt_space* _Lcontinue_3;
_Lid_1 = _Gnest_stack_id_v[(_Gnest_stack_c -= 1)];
_Ls_2 = _Lstmt_0;
fprintf(_Gout, "continue_%u:;\n", _Lid_1);
_Lcontinue_3 = (*(*_Ls_2)._Fwhile)._Fcontinue;
if(_Lcontinue_3 != NULL) {
_Mglc_Sstmt_space_Pwrite_1(_Lcontinue_3);
}
fprintf(_Gout, "}\nbreak_%u:;\n", _Lid_1);
}
void _Mglc_Sstmt_Pwrite_continue_1(struct _Mglc_Sstmt* _Lstmt_0) {
struct _Mglc_Sstmt_continue* _Ls_1;
_Ls_1 = _Lstmt_0;
fprintf(_Gout, "goto continue_%u;\n", _Gnest_stack_id_v[(*_Ls_1)._Fnest]);
}
void _Mglc_Sstmt_Pwrite_break_1(struct _Mglc_Sstmt* _Lstmt_0) {
struct _Mglc_Sstmt_break* _Ls_1;
_Ls_1 = _Lstmt_0;
fprintf(_Gout, "goto break_%u;\n", _Gnest_stack_id_v[(*_Ls_1)._Fnest]);
}
void _Mglc_Sstmt_Pwrite_return_1(struct _Mglc_Sstmt* _Lstmt_0) {
struct _Mglc_Sstmt_return* _Ls_1;
_Ls_1 = _Lstmt_0;
if((*_Ls_1)._Fexpr == _Mglc_Eexpr_Cnil) {
fprintf(_Gout, "return;\n");
} else {
fprintf(_Gout, "return ");
_Mglc_Eexpr_Pwrite_value_2((*_Ls_1)._Fexpr, &(*_Ls_1)._Fval);
fprintf(_Gout, ";\n");
}
}
void _Mglc_Sstmt_Pwrite_space_1(struct _Mglc_Sstmt* _Lstmt_0) {
struct _Mglc_Sstmt_space* _Lspace_1;
_Lspace_1 = _Lstmt_0;
_Mglc_Sstmt_space_Pwrite_1(_Lspace_1);
}
void _Mglc_Eexpr_Pset_3(_Mglc_Eexpr _Le_0, struct _Mglc_Sexpr* _Lexpr_1, _Mglc_Eexpr_type _Ltype_2) {
_Gexpr_v[_Le_0] = _Lexpr_1;
(*_Lexpr_1)._Ftype = _Ltype_2;
}
void _Mglc_Eassign_Prd_2(_Mglc_Eassign* _Ls_0, union _Mglc_Srdr* _Lr_1) {
(*_Ls_0) = (_Mglc_Eassign)(_Mglc_Srdr_Pn1_1(_Lr_1));
}
void _Mglc_Ecompare_Prd_2(_Mglc_Ecompare* _Le_0, union _Mglc_Srdr* _Lr_1) {
(*_Le_0) = (_Mglc_Ecompare)(_Mglc_Srdr_Pn1_1(_Lr_1));
}
bool _Mglc_Srdr_Pbool_1(union _Mglc_Srdr* _Lr_0) {
return _Mglc_Srdr_Pn1_1(_Lr_0) != 0;
}
void _Mglc_Emath_Prd_2(_Mglc_Emath* _Le_0, union _Mglc_Srdr* _Lr_1) {
(*_Le_0) = (_Mglc_Emath)(_Mglc_Srdr_Pn1_1(_Lr_1));
}
void _Mglc_Eunary_Prd_2(_Mglc_Eunary* _Lu_0, union _Mglc_Srdr* _Lr_1) {
(*_Lu_0) = (_Mglc_Eunary)(_Mglc_Srdr_Pn1_1(_Lr_1));
}
void _Mglc_Ebools_Prd_2(_Mglc_Ebools* _Le_0, union _Mglc_Srdr* _Lr_1) {
(*_Le_0) = (_Mglc_Ebools)(_Mglc_Srdr_Pn1_1(_Lr_1));
}
void _Mglc_Srdr_Pcopy_3(union _Mglc_Srdr* _Lr_0, void* _Ldata_1, int32_t _Lsize_2) {
memcpy(_Ldata_1, (*_Lr_0)._Fref, _Lsize_2);
(*_Lr_0)._Fpos += _Lsize_2;
}
void _Mglc_Sstmt_space_Pstmt_push_7(struct _Mglc_Sstmt_space* _Ls_0, struct _Mglc_Sstmt* _Ls2_1, int32_t _Lbegin_row_2, int32_t _Lbegin_col_3, int32_t _Lend_row_4, int32_t _Lend_col_5, _Mglc_Estmt_type _Ltype_6) {
(*_Ls2_1)._Fbegin_row = _Lbegin_row_2;
(*_Ls2_1)._Fbegin_col = _Lbegin_col_3;
(*_Ls2_1)._Fend_row = _Lend_row_4;
(*_Ls2_1)._Fend_col = _Lend_col_5;
(*_Ls2_1)._Ftype = _Ltype_6;
(*_Ls2_1)._Fstmt_next = NULL;
if((*_Ls_0)._Fstmt_last == NULL) {
(*_Ls_0)._Fstmt_first = _Ls2_1;
(*_Ls_0)._Fstmt_last = _Ls2_1;
} else {
(*(*_Ls_0)._Fstmt_last)._Fstmt_next = _Ls2_1;
(*_Ls_0)._Fstmt_last = _Ls2_1;
}
}
bool _Mglc_Eexpr_Pvalue_4(_Mglc_Eexpr _Le_0, int32_t _Lref_1, bool _Lparen_2, struct _Mglc_Svalue* _Lv_3) {
struct _Mglc_Sexpr* _Lexpr_4;
bool _Lok_5;
if(!(_Mglc_Eexpr_Pprocess_1(_Le_0))) {
return false;
}
_Lexpr_4 = _Mglc_Eexpr_Pptr_1(_Le_0);
_Lok_5 = false;
switch((*_Lexpr_4)._Ftype) {
case _Mglc_Eexpr_type_Cassign:;
_Mglc_Eexpr_Pvalue_assign_5(_Le_0, _Lref_1, _Lparen_2, _Lv_3, &_Lok_5);
break;
case _Mglc_Eexpr_type_Ccompare:;
_Mglc_Eexpr_Pvalue_compare_5(_Le_0, _Lref_1, _Lparen_2, _Lv_3, &_Lok_5);
break;
case _Mglc_Eexpr_type_Cbool:;
_Mglc_Eexpr_Pvalue_bool_5(_Le_0, _Lref_1, _Lparen_2, _Lv_3, &_Lok_5);
break;
case _Mglc_Eexpr_type_Cchar:;
_Mglc_Eexpr_Pvalue_char_5(_Le_0, _Lref_1, _Lparen_2, _Lv_3, &_Lok_5);
break;
case _Mglc_Eexpr_type_Cmath:;
_Mglc_Eexpr_Pvalue_math_5(_Le_0, _Lref_1, _Lparen_2, _Lv_3, &_Lok_5);
break;
case _Mglc_Eexpr_type_Cunary:;
_Mglc_Eexpr_Pvalue_unary_5(_Le_0, _Lref_1, _Lparen_2, _Lv_3, &_Lok_5);
break;
case _Mglc_Eexpr_type_Cref:;
_Mglc_Eexpr_Pvalue_ref_5(_Le_0, _Lref_1, _Lparen_2, _Lv_3, &_Lok_5);
break;
case _Mglc_Eexpr_type_Ccast_fast:;
_Mglc_Eexpr_Pvalue_cast_fast_5(_Le_0, _Lref_1, _Lparen_2, _Lv_3, &_Lok_5);
break;
case _Mglc_Eexpr_type_Clvar:;
_Mglc_Eexpr_Pvalue_lvar_5(_Le_0, _Lref_1, _Lparen_2, _Lv_3, &_Lok_5);
break;
case _Mglc_Eexpr_type_Cfvar:;
_Mglc_Eexpr_Pvalue_fvar_5(_Le_0, _Lref_1, _Lparen_2, _Lv_3, &_Lok_5);
break;
case _Mglc_Eexpr_type_Cgvar:;
_Mglc_Eexpr_Pvalue_gvar_5(_Le_0, _Lref_1, _Lparen_2, _Lv_3, &_Lok_5);
break;
case _Mglc_Eexpr_type_Ccvar:;
_Mglc_Eexpr_Pvalue_cvar_5(_Le_0, _Lref_1, _Lparen_2, _Lv_3, &_Lok_5);
break;
case _Mglc_Eexpr_type_Cbools:;
_Mglc_Eexpr_Pvalue_bools_5(_Le_0, _Lref_1, _Lparen_2, _Lv_3, &_Lok_5);
break;
case _Mglc_Eexpr_type_Cfunc:;
_Mglc_Eexpr_Pvalue_func_5(_Le_0, _Lref_1, _Lparen_2, _Lv_3, &_Lok_5);
break;
case _Mglc_Eexpr_type_Cmethod:;
_Mglc_Eexpr_Pvalue_method_5(_Le_0, _Lref_1, _Lparen_2, _Lv_3, &_Lok_5);
break;
case _Mglc_Eexpr_type_Cstr:;
_Mglc_Eexpr_Pvalue_str_5(_Le_0, _Lref_1, _Lparen_2, _Lv_3, &_Lok_5);
break;
case _Mglc_Eexpr_type_Cint:;
_Mglc_Eexpr_Pvalue_int_5(_Le_0, _Lref_1, _Lparen_2, _Lv_3, &_Lok_5);
break;
case _Mglc_Eexpr_type_Csize_of_type:;
_Mglc_Eexpr_Pvalue_size_of_type_5(_Le_0, _Lref_1, _Lparen_2, _Lv_3, &_Lok_5);
break;
case _Mglc_Eexpr_type_Cnull:;
_Mglc_Eexpr_Pvalue_null_5(_Le_0, _Lref_1, _Lparen_2, _Lv_3, &_Lok_5);
break;
case _Mglc_Eexpr_type_Cindex:;
_Mglc_Eexpr_Pvalue_index_5(_Le_0, _Lref_1, _Lparen_2, _Lv_3, &_Lok_5);
break;
default:;
fprintf(stdout, "%u:%u - %u:%u: :value not implemented for #%s\n", _Gctx_begin_row, _Gctx_begin_col, _Gctx_end_row, _Gctx_end_col, _Mglc_Eexpr_type_Pglc_name_1((*_Lexpr_4)._Ftype));
break;
}
return _Lok_5;
}
bool _Mglc_Eexpr_Pprocess_case_func_2(struct _Mglc_Sexpr* _Lexpr_0, _Mglc_Efunc _Lf_idx_1) {
struct _Mglc_Sexpr_func* _Le_2;
_Mglc_Eid _Lfunc_name_3;
uint8_t _Lcarg_c_4;
uint8_t _Lgroup_c_5;
uint8_t* _Lgroup_v_6;
struct _Mglc_Sat* _Lat_7;
struct _Mglc_Sdecl_func* _Lf_8;
int32_t _Lj_9;
_Le_2 = _Lexpr_0;
_Lfunc_name_3 = (*_Le_2)._Ffunc_name;
_Lcarg_c_4 = (*_Le_2)._Fcarg_c;
_Lgroup_c_5 = (*_Le_2)._Fgroup_c;
_Lgroup_v_6 = (*_Le_2)._Fgroup_v;
_Lat_7 = _Mglc_Eat_Pptr_1((*_Gctx_func)._Fat);
_Mglc_Efunc_Pprocess_later_1(_Lf_idx_1);
_Lf_8 = _Mglc_Efunc_Pptr_1(_Lf_idx_1);
_Lj_9 = 0;
for(int i = (*_Lf_8)._Ffarg_c; i > 0; ) {
i --;
struct _Mglc_Scarg* _Lca_10;
_Lca_10 = (&(*_Le_2)._Fcarg_v[_Lj_9]);
if(!(_Mglc_Pfarg_process_4((*_Lca_10)._Fexpr, (*_Lca_10)._Fref, &(*_Lca_10)._Fvalue, &(*_Lf_8)._Ffarg_v[_Lj_9]._Fdecl))) {
return false;
}
continue_0:;
_Lj_9++;
}
break_0:;
(*_Le_2)._Ffunc_idx = _Lf_idx_1;
if(((*_Lf_8)._Fflags & _Mglc_Efunc_flags_Cvar_args) != _Mglc_Efunc_flags_C0) {
for(int i = (*_Le_2)._Fcarg_c - _Lj_9; i > 0; ) {
i --;
struct _Mglc_Scarg* _Lca_11;
int32_t _Lr_12;
_Lca_11 = (&(*_Le_2)._Fcarg_v[_Lj_9]);
if((*_Lca_11)._Fref) {
_Lr_12 = (1 + (*_Lca_11)._Fref);
} else {
_Lr_12 = 1;
}
if(!(_Mglc_Eexpr_Pvalue_4((*_Lca_11)._Fexpr, _Lr_12, false, &(*_Lca_11)._Fvalue))) {
return false;
}
continue_1:;
_Lj_9++;
}
break_1:;
}
(*_Le_2)._Ffunc_idx = _Lf_idx_1;
return true;
}
uint8_t _Mglc_Eid_Plen_1(_Mglc_Eid _Lid_0) {
return _Gid_len_v[_Lid_0];
}
bool _Mglc_Sstmt_space_Pprocess_1(struct _Mglc_Sstmt_space* _Lspace_0) {
struct _Mglc_Sstmt* _Ls_1;
uint8_t _Li_2;
int32_t _Llvar_c_3;
_Ls_1 = (*_Lspace_0)._Fstmt_first;
while(_Ls_1 != NULL) {
if(!(_Mglc_Sstmt_Pprocess_1(_Ls_1))) {
return false;
}
_Ls_1 = (*_Ls_1)._Fstmt_next;
continue_0:;
}
break_0:;
if((*_Lspace_0)._Fparent == NULL) {
_Li_2 = (*_Gctx_func)._Ffarg_c;
_Llvar_c_3 = ((*_Lspace_0)._Flvar_c - (*_Gctx_func)._Ffarg_c);
} else {
_Li_2 = 0;
_Llvar_c_3 = (*_Lspace_0)._Flvar_c;
}
for(int i = _Llvar_c_3; i > 0; ) {
i --;
_Mglc_Elvar_Pprocess_1((*_Lspace_0)._Flvar_v[_Li_2]);
continue_1:;
_Li_2++;
}
break_1:;
return true;
}
void _Mglc_Eexpr_Ptry_deduce_2(_Mglc_Eexpr _Le_idx_0, _Mglc_Eat _Lat_1) {
struct _Mglc_Sexpr* _Lexpr_2;
_Lexpr_2 = _Mglc_Eexpr_Pptr_1(_Le_idx_0);
switch((*_Lexpr_2)._Ftype) {
case _Mglc_Eexpr_type_Cmath:;
_Mglc_Eexpr_Ptry_deduce_math_2(_Lexpr_2, _Lat_1);
break;
case _Mglc_Eexpr_type_Ccvar:;
_Mglc_Eexpr_Ptry_deduce_cvar_2(_Lexpr_2, _Lat_1);
break;
}
}
void _Mglc_Stype_info_Pinit_1(struct _Mglc_Stype_info* _Lti_0) {
(*_Lti_0)._Fref_v[0] = 0;
(*_Lti_0)._Farray_c = 0;
(*_Lti_0)._Fstar_c = 0;
(*_Lti_0)._Fbuilt_in = false;
(*_Lti_0)._Fconst = false;
}
void _Mglc_Stype_info_Pcopy_from_2(struct _Mglc_Stype_info* _Lti_0, struct _Mglc_Stype_info* _Lti2_1) {
memcpy((*_Lti_0)._Fref_v, (*_Lti2_1)._Fref_v, _Mglc_Ctype_info_star_limit);
(*_Lti_0)._Farray_c = (*_Lti2_1)._Farray_c;
(*_Lti_0)._Fstar_c = (*_Lti2_1)._Fstar_c;
(*_Lti_0)._Fconst = (*_Lti2_1)._Fconst;
}
_Mglc_Eat _Mglc_Eexpr_Ptype_1(_Mglc_Eexpr _Le_0) {
struct _Mglc_Sexpr* _Lexpr_1;
_Mglc_Eat _Lat_2;
if(!(_Mglc_Eexpr_Pprocess_1(_Le_0))) {
return _Mglc_Eat_Cnil;
}
_Lexpr_1 = _Mglc_Eexpr_Pptr_1(_Le_0);
_Lat_2 = _Mglc_Eat_Cnil;
switch((*_Lexpr_1)._Ftype) {
case _Mglc_Eexpr_type_Cassign:;
_Mglc_Eexpr_Ptype_assign_2(_Lexpr_1, &_Lat_2);
break;
case _Mglc_Eexpr_type_Ccompare:;
_Mglc_Eexpr_Ptype_compare_2(_Lexpr_1, &_Lat_2);
break;
case _Mglc_Eexpr_type_Cbool:;
_Mglc_Eexpr_Ptype_bool_2(_Lexpr_1, &_Lat_2);
break;
case _Mglc_Eexpr_type_Cchar:;
_Mglc_Eexpr_Ptype_char_2(_Lexpr_1, &_Lat_2);
break;
case _Mglc_Eexpr_type_Cmath:;
_Mglc_Eexpr_Ptype_math_2(_Lexpr_1, &_Lat_2);
break;
case _Mglc_Eexpr_type_Cunary:;
_Mglc_Eexpr_Ptype_unary_2(_Lexpr_1, &_Lat_2);
break;
case _Mglc_Eexpr_type_Cref:;
_Mglc_Eexpr_Ptype_ref_2(_Lexpr_1, &_Lat_2);
break;
case _Mglc_Eexpr_type_Ccast_fast:;
_Mglc_Eexpr_Ptype_cast_fast_2(_Lexpr_1, &_Lat_2);
break;
case _Mglc_Eexpr_type_Clvar:;
_Mglc_Eexpr_Ptype_lvar_2(_Lexpr_1, &_Lat_2);
break;
case _Mglc_Eexpr_type_Cfvar:;
_Mglc_Eexpr_Ptype_fvar_2(_Lexpr_1, &_Lat_2);
break;
case _Mglc_Eexpr_type_Cgvar:;
_Mglc_Eexpr_Ptype_gvar_2(_Lexpr_1, &_Lat_2);
break;
case _Mglc_Eexpr_type_Ccvar:;
_Mglc_Eexpr_Ptype_cvar_2(_Lexpr_1, &_Lat_2);
break;
case _Mglc_Eexpr_type_Cbools:;
_Mglc_Eexpr_Ptype_bools_2(_Lexpr_1, &_Lat_2);
break;
case _Mglc_Eexpr_type_Cfunc:;
_Mglc_Eexpr_Ptype_func_2(_Lexpr_1, &_Lat_2);
break;
case _Mglc_Eexpr_type_Cmethod:;
_Mglc_Eexpr_Ptype_method_2(_Lexpr_1, &_Lat_2);
break;
case _Mglc_Eexpr_type_Cint:;
_Mglc_Eexpr_Ptype_int_2(_Lexpr_1, &_Lat_2);
break;
case _Mglc_Eexpr_type_Csize_of_type:;
_Mglc_Eexpr_Ptype_size_of_type_2(_Lexpr_1, &_Lat_2);
break;
case _Mglc_Eexpr_type_Cnull:;
_Mglc_Eexpr_Ptype_null_2(_Lexpr_1, &_Lat_2);
break;
case _Mglc_Eexpr_type_Cindex:;
_Mglc_Eexpr_Ptype_index_2(_Lexpr_1, &_Lat_2);
break;
default:;
fprintf(stdout, "%u:%u - %u:%u: :type not implemented for #%s\n", _Gctx_begin_row, _Gctx_begin_col, _Gctx_end_row, _Gctx_end_col, _Mglc_Eexpr_type_Pglc_name_1((*_Lexpr_1)._Ftype));
break;
}
return _Lat_2;
}
bool _Mglc_Elvar_Pprocess_1(_Mglc_Elvar _Ll_0) {
struct _Mglc_Slvar* _Llvar_1;
_Mglc_Eat _Lat_i_2;
_Llvar_1 = _Mglc_Elvar_Pptr_1(_Ll_0);
if(((*_Llvar_1)._Fflags & _Mglc_Elvar_flags_Cprocessed) != _Mglc_Elvar_flags_C0) {
return true;
}
(*_Llvar_1)._Fflags |= _Mglc_Elvar_flags_Cprocessed;
_Lat_i_2 = (*_Llvar_1)._Fdecl._Ftype;
if(_Lat_i_2 == _Mglc_Eat_Cnil) {
if(((*_Llvar_1)._Fflags & _Mglc_Elvar_flags_Cset_expr) != _Mglc_Elvar_flags_C0) {
struct _Mglc_Svalue _Lv_3;
if(!(_Mglc_Eexpr_Pvalue_4((*_Llvar_1)._Fset_expr, 1, false, &_Lv_3))) {
return false;
}
(*_Llvar_1)._Fdecl._Ftype = _Lv_3._Ftype;
_Mglc_Stype_info_Pinit_1(&(*_Llvar_1)._Fdecl._Ftype_info);
_Mglc_Stype_info_Pcopy_from_2(&(*_Llvar_1)._Fdecl._Ftype_info, &_Lv_3._Finfo);
} else {
fprintf(stdout, "%s:%u:%u: Variable '%s' doesn't have a type or a value\n", _Mglc_Efile_Ppath_1((*_Gctx_func)._Ffile), (*_Llvar_1)._Frow, (*_Llvar_1)._Fcol, _Mglc_Eid_Pstr_1((*_Llvar_1)._Fdecl._Fname));
return false;
}
return true;
}
return _Mglc_Sdecl_var_Pprocess_3(&(*_Llvar_1)._Fdecl, (*_Llvar_1)._Frow, (*_Llvar_1)._Fcol);
}
bool _Mglc_Egvar_Pprocess_1(_Mglc_Egvar _Lg_0) {
uint32_t _Lnum_1;
uint32_t _Ln3_2;
int32_t _Ln17_3;
struct _Mglc_Sdecl_gvar* _Lgvar_4;
_Mglc_Eat _Lat_i_5;
struct _Mglc_Sat* _Lat_6;
_Lnum_1 = (uint32_t)(_Lg_0);
_Ln3_2 = (_Lnum_1 >> 3);
_Ln17_3 = (1 << (_Lnum_1 & 7));
if((_Ggvar_is_outputted[_Ln3_2] & _Ln17_3) != 0) {
return true;
}
_Ggvar_is_outputted[_Ln3_2] |= _Ln17_3;
_Lgvar_4 = _Mglc_Egvar_Pptr_1(_Lg_0);
_Lat_i_5 = (*_Lgvar_4)._Fdecl._Ftype;
_Lat_6 = _Mglc_Eat_Pptr_1(_Lat_i_5);
if((((*_Lat_6)._Ftype != _Mglc_Ename_type_Cbasic) && ((*_Lat_6)._Fdecl._Fstruct == _Mglc_Estruct_Cnil))) {
fprintf(stdout, "Error, the type '%s' used in gvar '.%s' was not defined\n", _Mglc_Eid_Pstr_1((*_Lat_6)._Fname._Fid), _Mglc_Eid_Pstr_1((*_Lgvar_4)._Fdecl._Fname));
return false;
}
if(!(_Mglc_Sdecl_var_Pprocess_3(&(*_Lgvar_4)._Fdecl, (*_Lgvar_4)._Frow, (*_Lgvar_4)._Fcol))) {
return false;
}
if(((*_Lgvar_4)._Fflags & _Mglc_Egvar_flags_Cno_decl) == _Mglc_Egvar_flags_C0) {
_Ggvar_outputted_v[_Ggvar_outputted_c++] = _Lg_0;
}
return true;
}
bool _Mglc_Pfarg_process_4(_Mglc_Eexpr _Le_0, int8_t _Lca_ref_1, struct _Mglc_Svalue* _Lca_value_2, struct _Mglc_Sdecl_var* _Lfd_arg_3) {
struct _Mglc_Sexpr* _Lce_4;
int32_t _Lr_5;
_Lce_4 = _Mglc_Eexpr_Pptr_1(_Le_0);
if(_Lca_ref_1 != 0) {
_Lr_5 = (1 + _Lca_ref_1);
} else {
_Lr_5 = 1;
_Lr_5 += (int32_t)((*_Lfd_arg_3)._Ftype_info._Fref_v[(*_Lfd_arg_3)._Ftype_info._Farray_c]);
}
if((*_Lce_4)._Ftype == _Mglc_Eexpr_type_Clvar) {
struct _Mglc_Sexpr_lvar* _Lve_6;
struct _Mglc_Slvar* _Llvar_7;
struct _Mglc_Sdecl_var* _Lvd_8;
_Lve_6 = _Lce_4;
_Llvar_7 = _Mglc_Elvar_Pptr_1((*_Lve_6)._Flvar);
_Lvd_8 = (&(*_Llvar_7)._Fdecl);
if((*_Lvd_8)._Ftype == _Mglc_Eat_Cnil) {
if(((*_Llvar_7)._Fflags & _Mglc_Elvar_flags_Cset_expr) == _Mglc_Elvar_flags_C0) {
(*_Lvd_8)._Ftype = (*_Lfd_arg_3)._Ftype;
_Mglc_Stype_info_Pinit_1(&(*_Lvd_8)._Ftype_info);
_Mglc_Stype_info_Pcopy_from_2(&(*_Lvd_8)._Ftype_info, &(*_Lfd_arg_3)._Ftype_info);
if((*_Lfd_arg_3)._Ftype_info._Fbuilt_in) {
(*_Lvd_8)._Ftype_info._Fbuilt_in = true;
(*_Lvd_8)._Ftype_info._Fref_v[0] = '\0';
} else if((*_Lvd_8)._Ftype_info._Fref_v[(*_Lvd_8)._Ftype_info._Farray_c] + _Mglc_Eat_Ppointer_1((*_Lvd_8)._Ftype)) {
(*_Lvd_8)._Ftype_info._Fref_v[(*_Lvd_8)._Ftype_info._Farray_c] -= (char)(1);
(*_Lvd_8)._Ftype_info._Fstar_c -= 1;
}
}
}
}
_Mglc_Eexpr_Ptry_deduce_2(_Le_0, (*_Lfd_arg_3)._Ftype);
if(!(_Mglc_Eexpr_Pvalue_4(_Le_0, _Lr_5, false, _Lca_value_2))) {
return false;
}
return true;
}
void _Mglc_Eexpr_Pvalue_assign_5(_Mglc_Eexpr _Le_0, int8_t _Lref_1, bool _Lparen_2, struct _Mglc_Svalue* _Lv_3, bool* _Lok_4) {
struct _Mglc_Sexpr_assign* _Lexpr_5;
_Lexpr_5 = _Mglc_Eexpr_Pptr_1(_Le_0);
if(_Mglc_Eexpr_Pvalue_4((*_Lexpr_5)._Fleft, 1, _Lparen_2, _Lv_3) == false) {
return;
}
(*_Lv_3)._Fparen = _Lparen_2;
(*_Lv_3)._Fref = _Lref_1;
(*_Lok_4) = true;
}
void _Mglc_Eexpr_Pvalue_compare_5(_Mglc_Eexpr _Le_0, int8_t _Lref_1, bool _Lparen_2, struct _Mglc_Svalue* _Lv_3, bool* _Lok_4) {
struct _Mglc_Sexpr_compare* _Lexpr_5;
_Lexpr_5 = _Mglc_Eexpr_Pptr_1(_Le_0);
(*_Lv_3)._Ftype = _Mglc_Pbasic_type_1(_Mglc_Ebasic_type_id_Cbool);
_Mglc_Stype_info_Pinit_1(&(*_Lv_3)._Finfo);
(*_Lv_3)._Finfo._Farray_c = 0;
(*_Lv_3)._Finfo._Fref_v[0] = '\0';
(*_Lv_3)._Finfo._Fstar_c = 0;
(*_Lv_3)._Fref = 1;
(*_Lv_3)._Fparen = _Lparen_2;
(*_Lok_4) = true;
}
void _Mglc_Eexpr_Pvalue_bool_5(_Mglc_Eexpr _Lle_0, int32_t _Lref_1, bool _Lparen_2, struct _Mglc_Svalue* _Lv_3, bool* _Lok_4) {
(*_Lv_3)._Ftype = _Mglc_Pbasic_type_1(_Mglc_Ebasic_type_id_Cbool);
_Mglc_Stype_info_Pinit_1(&(*_Lv_3)._Finfo);
(*_Lv_3)._Finfo._Farray_c = 0;
(*_Lv_3)._Finfo._Fref_v[0] = '\0';
(*_Lv_3)._Finfo._Fstar_c = 0;
(*_Lv_3)._Fref = 1;
(*_Lv_3)._Fparen = false;
(*_Lok_4) = true;
}
void _Mglc_Eexpr_Pvalue_char_5(_Mglc_Eexpr _Lle_0, int32_t _Lref_1, bool _Lparen_2, struct _Mglc_Svalue* _Lv_3, bool* _Lok_4) {
(*_Lv_3)._Ftype = _Mglc_Pbasic_type_1(_Mglc_Ebasic_type_id_Cchar);
_Mglc_Stype_info_Pinit_1(&(*_Lv_3)._Finfo);
(*_Lv_3)._Finfo._Farray_c = 0;
(*_Lv_3)._Finfo._Fref_v[0] = '\0';
(*_Lv_3)._Finfo._Fstar_c = 0;
(*_Lv_3)._Fref = 1;
(*_Lv_3)._Fparen = false;
(*_Lok_4) = true;
}
void _Mglc_Eexpr_Pvalue_math_5(_Mglc_Eexpr _Le_0, int8_t _Lref_1, bool _Lparen_2, struct _Mglc_Svalue* _Lv_3, bool* _Lok_4) {
struct _Mglc_Sexpr_math* _Lexpr_5;
_Lexpr_5 = _Mglc_Eexpr_Pptr_1(_Le_0);
if(!(_Mglc_Eexpr_Pvalue_4((*_Lexpr_5)._Fleft, 1, _Lparen_2, _Lv_3))) {
return;
}
(*_Lv_3)._Fparen = _Lparen_2;
(*_Lv_3)._Fref = _Lref_1;
(*_Lok_4) = true;
}
void _Mglc_Eexpr_Pvalue_unary_5(_Mglc_Eexpr _Le_0, int8_t _Lref_1, bool _Lparen_2, struct _Mglc_Svalue* _Lv_3, bool* _Lok_4) {
struct _Mglc_Sexpr_unary* _Lexpr_5;
_Lexpr_5 = _Mglc_Eexpr_Pptr_1(_Le_0);
(*_Lv_3)._Ftype = _Mglc_Eexpr_Ptype_1((*_Lexpr_5)._Fexpr);
_Mglc_Stype_info_Pinit_1(&(*_Lv_3)._Finfo);
(*_Lv_3)._Finfo._Farray_c = 0;
(*_Lv_3)._Finfo._Fref_v[0] = 0;
(*_Lv_3)._Finfo._Fstar_c = 0;
(*_Lv_3)._Fref = 1;
(*_Lok_4) = true;
}
void _Mglc_Eexpr_Pvalue_ref_5(_Mglc_Eexpr _Le_0, int8_t _Lref_1, bool _Lparen_2, struct _Mglc_Svalue* _Lv_3, bool* _Lok_4) {
struct _Mglc_Sexpr_ref* _Lexpr_5;
_Lexpr_5 = _Mglc_Eexpr_Pptr_1(_Le_0);
(*_Lv_3)._Ftype = _Mglc_Pbasic_type_1(_Mglc_Ebasic_type_id_Cref);
_Mglc_Stype_info_Pinit_1(&(*_Lv_3)._Finfo);
(*_Lv_3)._Finfo._Farray_c = 0;
(*_Lv_3)._Finfo._Fref_v[0] = 1;
(*_Lv_3)._Finfo._Fstar_c = 1;
(*_Lv_3)._Fref = 1;
(*_Lok_4) = true;
}
void _Mglc_Eexpr_Pvalue_cast_fast_5(_Mglc_Eexpr _Le_0, int8_t _Lref_1, bool _Lparen_2, struct _Mglc_Svalue* _Lv_3, bool* _Lok_4) {
struct _Mglc_Sexpr_cast_fast* _Lexpr_5;
_Lexpr_5 = _Mglc_Eexpr_Pptr_1(_Le_0);
_Mglc_Eexpr_Pvalue_4((*_Lexpr_5)._Fexpr, _Lref_1, _Lparen_2, _Lv_3);
(*_Lv_3)._Ftype = (*_Lexpr_5)._Ftype;
(*_Lok_4) = true;
}
void _Mglc_Eexpr_Pvalue_lvar_5(_Mglc_Eexpr _Le_0, int8_t _Lref_1, bool _Lparen_2, struct _Mglc_Svalue* _Lv_3, bool* _Lok_4) {
struct _Mglc_Sexpr_lvar* _Lexpr_5;
struct _Mglc_Slvar* _Llvar_6;
_Lexpr_5 = _Mglc_Eexpr_Pptr_1(_Le_0);
_Llvar_6 = _Mglc_Elvar_Pptr_1((*_Lexpr_5)._Flvar);
_Mglc_Svalue_Pset_5(_Lv_3, _Lref_1, _Lparen_2, (*_Llvar_6)._Fdecl._Ftype, &(*_Llvar_6)._Fdecl._Ftype_info);
if((*_Lv_3)._Fref == 1) {
(*_Lv_3)._Fparen = false;
}
(*_Lok_4) = true;
}
void _Mglc_Eexpr_Pvalue_fvar_5(_Mglc_Eexpr _Lexpr_0, int8_t _Lref_1, bool _Lparen_2, struct _Mglc_Svalue* _Lv_3, bool* _Lok_4) {
struct _Mglc_Sexpr_fvar* _Le_5;
struct _Mglc_Sfvar* _Lfvar_6;
_Le_5 = _Mglc_Eexpr_Pptr_1(_Lexpr_0);
_Lfvar_6 = (&(*_Mglc_Estruct_Pptr_1((*_Mglc_Eat_Pptr_1((*_Le_5)._Fval._Ftype))._Fdecl._Fstruct))._Ffvar_v[(*_Le_5)._Ffvar]);
_Mglc_Svalue_Pset_5(_Lv_3, _Lref_1, _Lparen_2, (*_Lfvar_6)._Fdecl._Ftype, &(*_Lfvar_6)._Fdecl._Ftype_info);
if((*_Lv_3)._Fref == 1) {
(*_Lv_3)._Fparen = false;
}
(*_Lok_4) = true;
}
void _Mglc_Eexpr_Pvalue_gvar_5(_Mglc_Eexpr _Lg_0, int32_t _Lref_1, bool _Lparen_2, struct _Mglc_Svalue* _Lv_3, bool* _Lok_4) {
struct _Mglc_Sexpr_gvar* _Le_5;
struct _Mglc_Sdecl_gvar* _Lgvar_6;
_Le_5 = _Mglc_Eexpr_Pptr_1(_Lg_0);
_Lgvar_6 = _Mglc_Egvar_Pptr_1((*_Le_5)._Fgvar);
_Mglc_Svalue_Pset_5(_Lv_3, _Lref_1, _Lparen_2, (*_Lgvar_6)._Fdecl._Ftype, &(*_Lgvar_6)._Fdecl._Ftype_info);
if((*_Lv_3)._Fref == 1) {
(*_Lv_3)._Fparen = false;
}
(*_Lok_4) = true;
}
void _Mglc_Eexpr_Pvalue_cvar_5(_Mglc_Eexpr _Le_0, int8_t _Lref_1, bool _Lparen_2, struct _Mglc_Svalue* _Lv_3, bool* _Lok_4) {
struct _Mglc_Sexpr_cvar* _Lexpr_5;
struct _Mglc_Scvar* _Lcvar_6;
_Lexpr_5 = _Mglc_Eexpr_Pptr_1(_Le_0);
_Lcvar_6 = _Mglc_Ecvar_Pptr_1((*_Lexpr_5)._Fcvar);
_Mglc_Svalue_Pset_5(_Lv_3, _Lref_1, _Lparen_2, (*_Lcvar_6)._Fdecl._Ftype, &(*_Lcvar_6)._Fdecl._Ftype_info);
if((*_Lv_3)._Fref == 1) {
(*_Lv_3)._Fparen = false;
}
(*_Lok_4) = true;
}
void _Mglc_Eexpr_Pvalue_bools_5(_Mglc_Eexpr _Le_0, int32_t _Lref_1, bool _Lparen_2, struct _Mglc_Svalue* _Lv_3, bool* _Lok_4) {
(*_Lv_3)._Ftype = _Mglc_Pbasic_type_1(_Mglc_Ebasic_type_id_Cbool);
_Mglc_Stype_info_Pinit_1(&(*_Lv_3)._Finfo);
(*_Lv_3)._Finfo._Farray_c = 0;
(*_Lv_3)._Finfo._Fref_v[0] = '\0';
(*_Lv_3)._Finfo._Fstar_c = 0;
(*_Lv_3)._Fref = 1;
(*_Lv_3)._Fparen = false;
(*_Lok_4) = true;
}
void _Mglc_Eexpr_Pvalue_func_5(_Mglc_Eexpr _Le_0, int32_t _Lref_1, bool _Lparen_2, struct _Mglc_Svalue* _Lv_3, bool* _Lok_4) {
struct _Mglc_Sexpr_func* _Lexpr_5;
struct _Mglc_Sdecl_func* _Lf_6;
_Lexpr_5 = _Mglc_Eexpr_Pptr_1(_Le_0);
_Lf_6 = _Mglc_Efunc_Pptr_1((*_Lexpr_5)._Ffunc_idx);
_Mglc_Svalue_Pset_5(_Lv_3, _Lref_1, _Lparen_2, (*_Lf_6)._Fdecl._Ftype, &(*_Lf_6)._Fdecl._Ftype_info);
if((*_Lv_3)._Fref == 1) {
(*_Lv_3)._Fparen = false;
}
(*_Lok_4) = true;
}
void _Mglc_Eexpr_Pvalue_method_5(_Mglc_Eexpr _Le_0, int32_t _Lref_1, bool _Lparen_2, struct _Mglc_Svalue* _Lv_3, bool* _Lok_4) {
struct _Mglc_Sexpr_method* _Lexpr_5;
struct _Mglc_Sdecl_func* _Lf_6;
_Lexpr_5 = _Mglc_Eexpr_Pptr_1(_Le_0);
_Lf_6 = _Mglc_Efunc_Pptr_1((*_Lexpr_5)._Ffunc_idx);
_Mglc_Svalue_Pset_5(_Lv_3, _Lref_1, _Lparen_2, (*_Lf_6)._Fdecl._Ftype, &(*_Lf_6)._Fdecl._Ftype_info);
if((*_Lv_3)._Fref == 1) {
(*_Lv_3)._Fparen = false;
}
(*_Lok_4) = true;
}
void _Mglc_Eexpr_Pvalue_str_5(_Mglc_Eexpr _Ls_0, int32_t _Lref_1, bool _Lparen_2, struct _Mglc_Svalue* _Lv_3, bool* _Lok_4) {
(*_Lv_3)._Ftype = _Mglc_Pbasic_type_1(_Mglc_Ebasic_type_id_Cchar);
_Mglc_Stype_info_Pinit_1(&(*_Lv_3)._Finfo);
(*_Lv_3)._Finfo._Farray_c = 1;
(*_Lv_3)._Finfo._Fref_v[0] = '\0';
(*_Lv_3)._Finfo._Fref_v[1] = '\0';
(*_Lv_3)._Finfo._Fstar_c = 1;
(*_Lv_3)._Fref = 1;
(*_Lok_4) = true;
}
void _Mglc_Eexpr_Pvalue_int_5(_Mglc_Eexpr _Lle_0, int32_t _Lref_1, bool _Lparen_2, struct _Mglc_Svalue* _Lv_3, bool* _Lok_4) {
(*_Lv_3)._Ftype = _Mglc_Pbasic_type_1(_Mglc_Ebasic_type_id_Cint);
_Mglc_Stype_info_Pinit_1(&(*_Lv_3)._Finfo);
(*_Lv_3)._Finfo._Farray_c = 0;
(*_Lv_3)._Finfo._Fref_v[0] = '\0';
(*_Lv_3)._Finfo._Fstar_c = 0;
(*_Lv_3)._Fref = 1;
(*_Lv_3)._Fparen = false;
(*_Lok_4) = true;
}
void _Mglc_Eexpr_Pvalue_size_of_type_5(_Mglc_Eexpr _Lle_0, int32_t _Lref_1, bool _Lparen_2, struct _Mglc_Svalue* _Lv_3, bool* _Lok_4) {
(*_Lv_3)._Ftype = _Mglc_Pbasic_type_1(_Mglc_Ebasic_type_id_Csize);
_Mglc_Stype_info_Pinit_1(&(*_Lv_3)._Finfo);
(*_Lv_3)._Finfo._Farray_c = 0;
(*_Lv_3)._Finfo._Fref_v[0] = '\0';
(*_Lv_3)._Finfo._Fstar_c = 0;
(*_Lv_3)._Fref = 1;
(*_Lv_3)._Fparen = false;
(*_Lok_4) = true;
}
void _Mglc_Eexpr_Pvalue_null_5(_Mglc_Eexpr _Lle_0, int32_t _Lref_1, bool _Lparen_2, struct _Mglc_Svalue* _Lv_3, bool* _Lok_4) {
(*_Lv_3)._Ftype = _Mglc_Pbasic_type_1(_Mglc_Ebasic_type_id_Cref);
_Mglc_Stype_info_Pinit_1(&(*_Lv_3)._Finfo);
(*_Lv_3)._Finfo._Farray_c = 0;
(*_Lv_3)._Finfo._Fref_v[0] = '\0';
(*_Lv_3)._Finfo._Fstar_c = 0;
(*_Lv_3)._Fref = 1;
(*_Lv_3)._Fparen = false;
(*_Lok_4) = true;
}
void _Mglc_Eexpr_Pvalue_index_5(_Mglc_Eexpr _Le_0, int8_t _Lref_1, bool _Lparen_2, struct _Mglc_Svalue* _Lv_3, bool* _Lok_4) {
struct _Mglc_Sexpr_index* _Lexpr_5;
int8_t _Lc_6;
_Lexpr_5 = _Mglc_Eexpr_Pptr_1(_Le_0);
(*_Lv_3)._Ftype = (*_Lexpr_5)._Fleft_val._Ftype;
_Mglc_Stype_info_Pinit_1(&(*_Lv_3)._Finfo);
_Mglc_Stype_info_Pcopy_from_2(&(*_Lv_3)._Finfo, &(*_Lexpr_5)._Fleft_val._Finfo);
(*_Lv_3)._Finfo._Farray_c -= 1;
_Lc_6 = (*_Lv_3)._Finfo._Fref_v[(*_Lv_3)._Finfo._Farray_c];
(*_Lv_3)._Fref = ((_Lc_6 + 2) - _Lref_1);
(*_Lv_3)._Finfo._Fref_v[(*_Lv_3)._Finfo._Farray_c] = (_Lref_1 - 1);
_Mglc_Stype_info_Pcount_1(&(*_Lv_3)._Finfo);
if((*_Lv_3)._Fref == 1) {
(*_Lv_3)._Fparen = false;
} else {
(*_Lv_3)._Fparen = _Lparen_2;
}
(*_Lok_4) = true;
}
void _Mglc_Eexpr_Ptry_deduce_math_2(struct _Mglc_Sexpr* _Lexpr_0, _Mglc_Eat _Lat_1) {
struct _Mglc_Sexpr_math* _Le_2;
_Le_2 = _Lexpr_0;
_Mglc_Eexpr_Ptry_deduce_2((*_Le_2)._Fleft, _Lat_1);
_Mglc_Eexpr_Ptry_deduce_2((*_Le_2)._Fright, _Lat_1);
int32_t _Li_3;
_Li_3 = 0;
for(int i = (*_Le_2)._Fitem_c; i > 0; ) {
i --;
_Mglc_Eexpr_Ptry_deduce_2((*_Le_2)._Fitem_v[_Li_3]._Fexpr, _Lat_1);
continue_0:;
_Li_3++;
}
break_0:;
}
void _Mglc_Eexpr_Ptry_deduce_cvar_2(struct _Mglc_Sexpr* _Lexpr_0, _Mglc_Eat _Lat_1) {
struct _Mglc_Sexpr_cvar* _Le_2;
_Le_2 = _Lexpr_0;
if((*_Le_2)._Fat == _Mglc_Eat_Cnil) {
(*_Le_2)._Ftry = _Lat_1;
}
}
void _Mglc_Eexpr_Ptype_assign_2(struct _Mglc_Sexpr* _Lexpr_0, _Mglc_Eat* _Lat_1) {
struct _Mglc_Sexpr_assign* _Le_2;
_Le_2 = _Lexpr_0;
(*_Lat_1) = _Mglc_Eexpr_Ptype_1((*_Le_2)._Fleft);
}
void _Mglc_Eexpr_Ptype_compare_2(struct _Mglc_Sexpr* _Lexpr_0, _Mglc_Eat* _Lat_1) {
struct _Mglc_Sexpr_compare* _Le_2;
_Le_2 = _Lexpr_0;
(*_Lat_1) = _Mglc_Pbasic_type_1(_Mglc_Ebasic_type_id_Cbool);
}
void _Mglc_Eexpr_Ptype_bool_2(struct _Mglc_Sexpr* _Lexpr_0, _Mglc_Eat* _Lat_1) {
(*_Lat_1) = _Mglc_Pbasic_type_1(_Mglc_Ebasic_type_id_Cbool);
}
void _Mglc_Eexpr_Ptype_char_2(struct _Mglc_Sexpr* _Lexpr_0, _Mglc_Eat* _Lat_1) {
(*_Lat_1) = _Mglc_Pbasic_type_1(_Mglc_Ebasic_type_id_Cchar);
}
void _Mglc_Eexpr_Ptype_math_2(struct _Mglc_Sexpr* _Lexpr_0, _Mglc_Eat* _Lat_1) {
struct _Mglc_Sexpr_math* _Le_2;
_Le_2 = _Lexpr_0;
(*_Lat_1) = _Mglc_Eexpr_Ptype_1((*_Le_2)._Fleft);
}
void _Mglc_Eexpr_Ptype_unary_2(struct _Mglc_Sexpr* _Lexpr_0, _Mglc_Eat* _Lat_1) {
struct _Mglc_Sexpr_unary* _Le_2;
_Le_2 = _Lexpr_0;
(*_Lat_1) = _Mglc_Eexpr_Ptype_1((*_Le_2)._Fexpr);
}
void _Mglc_Eexpr_Ptype_ref_2(struct _Mglc_Sexpr* _Lexpr_0, _Mglc_Eat* _Lat_1) {
(*_Lat_1) = _Mglc_Pbasic_type_1(_Mglc_Ebasic_type_id_Cref);
}
void _Mglc_Eexpr_Ptype_cast_fast_2(struct _Mglc_Sexpr* _Lexpr_0, _Mglc_Eat* _Lat_1) {
struct _Mglc_Sexpr_cast_fast* _Le_2;
_Le_2 = _Lexpr_0;
(*_Lat_1) = (*_Le_2)._Ftype;
}
void _Mglc_Eexpr_Ptype_lvar_2(struct _Mglc_Sexpr* _Lexpr_0, _Mglc_Eat* _Lat_1) {
struct _Mglc_Sexpr_lvar* _Le_2;
struct _Mglc_Slvar* _Llvar_3;
_Le_2 = _Lexpr_0;
_Llvar_3 = _Mglc_Elvar_Pptr_1((*_Le_2)._Flvar);
(*_Lat_1) = (*_Llvar_3)._Fdecl._Ftype;
}
void _Mglc_Eexpr_Ptype_fvar_2(struct _Mglc_Sexpr* _Lexpr_0, _Mglc_Eat* _Lat_1) {
struct _Mglc_Sexpr_fvar* _Le_2;
_Le_2 = _Lexpr_0;
(*_Lat_1) = (*_Mglc_Estruct_Pptr_1((*_Mglc_Eat_Pptr_1((*_Le_2)._Fval._Ftype))._Fdecl._Fstruct))._Ffvar_v[(*_Le_2)._Ffvar]._Fdecl._Ftype;
}
void _Mglc_Eexpr_Ptype_gvar_2(struct _Mglc_Sexpr* _Lexpr_0, _Mglc_Eat* _Lat_1) {
struct _Mglc_Sexpr_gvar* _Le_2;
struct _Mglc_Sdecl_gvar* _Lgvar_3;
_Le_2 = _Lexpr_0;
_Lgvar_3 = _Mglc_Egvar_Pptr_1((*_Le_2)._Fgvar);
(*_Lat_1) = (*_Lgvar_3)._Fdecl._Ftype;
}
void _Mglc_Eexpr_Ptype_cvar_2(struct _Mglc_Sexpr* _Lexpr_0, _Mglc_Eat* _Lat_1) {
struct _Mglc_Sexpr_cvar* _Le_2;
struct _Mglc_Scvar* _Lcvar_3;
_Le_2 = _Lexpr_0;
_Lcvar_3 = _Mglc_Ecvar_Pptr_1((*_Le_2)._Fcvar);
(*_Lat_1) = (*_Lcvar_3)._Fdecl._Ftype;
}
void _Mglc_Eexpr_Ptype_bools_2(struct _Mglc_Sexpr* _Lexpr_0, _Mglc_Eat* _Lat_1) {
(*_Lat_1) = _Mglc_Pbasic_type_1(_Mglc_Ebasic_type_id_Cbool);
}
void _Mglc_Eexpr_Ptype_func_2(struct _Mglc_Sexpr* _Lexpr_0, _Mglc_Eat* _Lat_1) {
struct _Mglc_Sexpr_func* _Le_2;
_Le_2 = _Lexpr_0;
(*_Lat_1) = (*_Mglc_Efunc_Pptr_1((*_Le_2)._Ffunc_idx))._Fdecl._Ftype;
}
void _Mglc_Eexpr_Ptype_method_2(struct _Mglc_Sexpr* _Lexpr_0, _Mglc_Eat* _Lat_1) {
struct _Mglc_Sexpr_method* _Le_2;
_Le_2 = _Lexpr_0;
(*_Lat_1) = (*_Mglc_Efunc_Pptr_1((*_Le_2)._Ffunc_idx))._Fdecl._Ftype;
}
void _Mglc_Eexpr_Ptype_int_2(struct _Mglc_Sexpr* _Lexpr_0, _Mglc_Eat* _Lat_1) {
(*_Lat_1) = _Mglc_Pbasic_type_1(_Mglc_Ebasic_type_id_Cint);
}
void _Mglc_Eexpr_Ptype_size_of_type_2(struct _Mglc_Sexpr* _Lexpr_0, _Mglc_Eat* _Lat_1) {
(*_Lat_1) = _Mglc_Pbasic_type_1(_Mglc_Ebasic_type_id_Csize);
}
void _Mglc_Eexpr_Ptype_null_2(struct _Mglc_Sexpr* _Lexpr_0, _Mglc_Eat* _Lat_1) {
(*_Lat_1) = _Mglc_Pbasic_type_1(_Mglc_Ebasic_type_id_Cref);
}
void _Mglc_Eexpr_Ptype_index_2(struct _Mglc_Sexpr* _Lexpr_0, _Mglc_Eat* _Lat_1) {
struct _Mglc_Sexpr_index* _Le_2;
_Le_2 = _Lexpr_0;
(*_Lat_1) = _Mglc_Eexpr_Ptype_1((*_Le_2)._Fleft);
}
void _Mglc_Svalue_Pset_5(struct _Mglc_Svalue* _Lv_0, int8_t _Lref_1, bool _Lparen_2, _Mglc_Eat _Ltype_3, struct _Mglc_Stype_info* _Linfo_4) {
int8_t _Lc_5;
_Lc_5 = (*_Linfo_4)._Fref_v[(*_Linfo_4)._Farray_c];
(*_Lv_0)._Ftype = _Ltype_3;
(*_Lv_0)._Fref = ((_Lc_5 + 2) - _Lref_1);
_Mglc_Stype_info_Pinit_1(&(*_Lv_0)._Finfo);
_Mglc_Stype_info_Pcopy_from_2(&(*_Lv_0)._Finfo, _Linfo_4);
(*_Lv_0)._Finfo._Fref_v[(*_Lv_0)._Finfo._Farray_c] = (_Lref_1 - 1);
_Mglc_Stype_info_Pcount_1(&(*_Lv_0)._Finfo);
(*_Lv_0)._Fparen = _Lparen_2;
}
