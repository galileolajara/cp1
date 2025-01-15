#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "num.c"
#include <string.h>
#define _NCp1_Chash_table_size (64)
#define _NCp1_NFunc_Cnil (-1)
#define _NCp1_NInclude_Cnil (-1)
#define _NStdc_NExit_Csuccess 0
#define _NStdc_NExit_Cfailure (_NStdc_NExit_Csuccess + 1)
#define _NCp1_NNameType_Cmodule 0
#define _NCp1_NNameType_Cstruct_enum (_NCp1_NNameType_Cmodule + 1)
#define _NCp1_NNameType_Cbasic (_NCp1_NNameType_Cstruct_enum + 1)
#define _NCp1_NAt_Cnil (-1)
#define _NCp1_NBasicTypeId_Croot 0
#define _NCp1_NBasicTypeId_Crelative (_NCp1_NBasicTypeId_Croot + 1)
#define _NCp1_Ctype_info_star_limit (8)
#define _NCp1_Cexpr_carg_group_limit (4)
#define _NCp1_NToken_Cnil 0
#define _NCp1_NToken_Cplus (_NCp1_NToken_Cnil + 1)
#define _NCp1_NToken_Cminus (_NCp1_NToken_Cplus + 1)
#define _NCp1_NToken_Cspace (_NCp1_NToken_Cminus + 1)
#define _NCp1_NToken_Cid_lparen (_NCp1_NToken_Cspace + 1)
#define _NCp1_NToken_Cid_upper (_NCp1_NToken_Cid_lparen + 1)
#define _NCp1_NToken_Cid_dot_upper (_NCp1_NToken_Cid_upper + 1)
#define _NCp1_NToken_Cid_hash (_NCp1_NToken_Cid_dot_upper + 1)
#define _NCp1_NToken_Cid (_NCp1_NToken_Cid_hash + 1)
#define _NCp1_NToken_Cspace_at_real_name_str (_NCp1_NToken_Cid + 1)
#define _NCp1_NToken_Cspace_at_real_name (_NCp1_NToken_Cspace_at_real_name_str + 1)
#define _NCp1_NToken_Cspace_at_no_decl (_NCp1_NToken_Cspace_at_real_name + 1)
#define _NCp1_NToken_Cspace_equal_space (_NCp1_NToken_Cspace_at_no_decl + 1)
#define _NCp1_NToken_Cinclude (_NCp1_NToken_Cspace_equal_space + 1)
#define _NCp1_NToken_Cspace_rcbrace (_NCp1_NToken_Cinclude + 1)
#define _NCp1_NToken_Cgrave (_NCp1_NToken_Cspace_rcbrace + 1)
#define _NCp1_NToken_Cid_bslash (_NCp1_NToken_Cgrave + 1)
#define _NCp1_NToken_Cusing (_NCp1_NToken_Cid_bslash + 1)
#define _NCp1_NToken_Crparen (_NCp1_NToken_Cusing + 1)
#define _NCp1_NToken_Clparen (_NCp1_NToken_Crparen + 1)
#define _NCp1_NToken_Clcbrace_space (_NCp1_NToken_Clparen + 1)
#define _NCp1_NToken_Crcbrace (_NCp1_NToken_Clcbrace_space + 1)
#define _NCp1_NToken_Cscolon (_NCp1_NToken_Crcbrace + 1)
#define _NCp1_NToken_Cend (_NCp1_NToken_Cscolon + 1)
#define _NCp1_NToken_Clparen_space (_NCp1_NToken_Cend + 1)
#define _NCp1_NToken_Cspace_rparen (_NCp1_NToken_Clparen_space + 1)
#define _NCp1_NToken_Ccomma_space_rparen (_NCp1_NToken_Cspace_rparen + 1)
#define _NCp1_NToken_Clcbrace (_NCp1_NToken_Ccomma_space_rparen + 1)
#define _NCp1_NToken_Clbracket (_NCp1_NToken_Clcbrace + 1)
#define _NCp1_NToken_Clbracket_space (_NCp1_NToken_Clbracket + 1)
#define _NCp1_NToken_Crbracket (_NCp1_NToken_Clbracket_space + 1)
#define _NCp1_NToken_Cspace_rbracket (_NCp1_NToken_Crbracket + 1)
#define _NCp1_NToken_Ccomma_space_rbracket (_NCp1_NToken_Cspace_rbracket + 1)
#define _NCp1_NToken_Ccolon (_NCp1_NToken_Ccomma_space_rbracket + 1)
#define _NCp1_NToken_Cthis (_NCp1_NToken_Ccolon + 1)
#define _NCp1_NToken_Ccomma_space (_NCp1_NToken_Cthis + 1)
#define _NCp1_NToken_Cspace_at_main (_NCp1_NToken_Ccomma_space + 1)
#define _NCp1_NToken_Cspace_at_case (_NCp1_NToken_Cspace_at_main + 1)
#define _NCp1_NToken_Cdot (_NCp1_NToken_Cspace_at_case + 1)
#define _NCp1_NToken_Cspace_at_process (_NCp1_NToken_Cdot + 1)
#define _NCp1_NToken_Cspace_at_inline (_NCp1_NToken_Cspace_at_process + 1)
#define _NCp1_NToken_Cspace_at_cp1_name (_NCp1_NToken_Cspace_at_inline + 1)
#define _NCp1_NToken_Cspace_at_decl (_NCp1_NToken_Cspace_at_cp1_name + 1)
#define _NCp1_NToken_Cstring (_NCp1_NToken_Cspace_at_decl + 1)
#define _NCp1_NToken_Cspace_at_var_args (_NCp1_NToken_Cstring + 1)
#define _NCp1_NToken_Cspace_at_no_body (_NCp1_NToken_Cspace_at_var_args + 1)
#define _NCp1_NToken_Cref (_NCp1_NToken_Cspace_at_no_body + 1)
#define _NCp1_NToken_Cbool (_NCp1_NToken_Cref + 1)
#define _NCp1_NToken_Cchar (_NCp1_NToken_Cbool + 1)
#define _NCp1_NToken_Cintc (_NCp1_NToken_Cchar + 1)
#define _NCp1_NToken_Ci8 (_NCp1_NToken_Cintc + 1)
#define _NCp1_NToken_Cu8 (_NCp1_NToken_Ci8 + 1)
#define _NCp1_NToken_Ci16 (_NCp1_NToken_Cu8 + 1)
#define _NCp1_NToken_Cu16 (_NCp1_NToken_Ci16 + 1)
#define _NCp1_NToken_Ci32 (_NCp1_NToken_Cu16 + 1)
#define _NCp1_NToken_Cu32 (_NCp1_NToken_Ci32 + 1)
#define _NCp1_NToken_Ci64 (_NCp1_NToken_Cu32 + 1)
#define _NCp1_NToken_Cu64 (_NCp1_NToken_Ci64 + 1)
#define _NCp1_NToken_Cisz (_NCp1_NToken_Cu64 + 1)
#define _NCp1_NToken_Cusz (_NCp1_NToken_Cisz + 1)
#define _NCp1_NToken_Cf32 (_NCp1_NToken_Cusz + 1)
#define _NCp1_NToken_Cf64 (_NCp1_NToken_Cf32 + 1)
#define _NCp1_NToken_Campersand (_NCp1_NToken_Cf64 + 1)
#define _NCp1_NToken_Cnum_dec (_NCp1_NToken_Campersand + 1)
#define _NCp1_NToken_Cnum_hex (_NCp1_NToken_Cnum_dec + 1)
#define _NCp1_NToken_Cnum_oct (_NCp1_NToken_Cnum_hex + 1)
#define _NCp1_NToken_Cchar1 (_NCp1_NToken_Cnum_oct + 1)
#define _NCp1_NToken_Cchar2 (_NCp1_NToken_Cchar1 + 1)
#define _NCp1_NToken_Ctrue (_NCp1_NToken_Cchar2 + 1)
#define _NCp1_NToken_Cfalse (_NCp1_NToken_Ctrue + 1)
#define _NCp1_NToken_Cnull (_NCp1_NToken_Cfalse + 1)
#define _NCp1_NToken_Clparen_amp_amp_comma_space (_NCp1_NToken_Cnull + 1)
#define _NCp1_NToken_Clparen_pipe_pipe_comma_space (_NCp1_NToken_Clparen_amp_amp_comma_space + 1)
#define _NCp1_NToken_Cspace_plus_space (_NCp1_NToken_Clparen_pipe_pipe_comma_space + 1)
#define _NCp1_NToken_Cspace_minus_space (_NCp1_NToken_Cspace_plus_space + 1)
#define _NCp1_NToken_Cspace_mul_space (_NCp1_NToken_Cspace_minus_space + 1)
#define _NCp1_NToken_Cspace_div_space (_NCp1_NToken_Cspace_mul_space + 1)
#define _NCp1_NToken_Cspace_langle_langle_space (_NCp1_NToken_Cspace_div_space + 1)
#define _NCp1_NToken_Cspace_rangle_rangle_space (_NCp1_NToken_Cspace_langle_langle_space + 1)
#define _NCp1_NToken_Cspace_amp_space (_NCp1_NToken_Cspace_rangle_rangle_space + 1)
#define _NCp1_NToken_Cspace_pipe_space (_NCp1_NToken_Cspace_amp_space + 1)
#define _NCp1_NToken_Cspace_xor_space (_NCp1_NToken_Cspace_pipe_space + 1)
#define _NCp1_NToken_Cspace_equal_equal_space (_NCp1_NToken_Cspace_xor_space + 1)
#define _NCp1_NToken_Cspace_expoint_equal_space (_NCp1_NToken_Cspace_equal_equal_space + 1)
#define _NCp1_NToken_Cspace_langle_space (_NCp1_NToken_Cspace_expoint_equal_space + 1)
#define _NCp1_NToken_Cspace_langle_equal_space (_NCp1_NToken_Cspace_langle_space + 1)
#define _NCp1_NToken_Cspace_rangle_space (_NCp1_NToken_Cspace_langle_equal_space + 1)
#define _NCp1_NToken_Cspace_rangle_equal_space (_NCp1_NToken_Cspace_rangle_space + 1)
#define _NCp1_NToken_Chash (_NCp1_NToken_Cspace_rangle_equal_space + 1)
#define _NCp1_NToken_Cspace_plus_equal_space (_NCp1_NToken_Chash + 1)
#define _NCp1_NToken_Cspace_minus_equal_space (_NCp1_NToken_Cspace_plus_equal_space + 1)
#define _NCp1_NToken_Cspace_mul_equal_space (_NCp1_NToken_Cspace_minus_equal_space + 1)
#define _NCp1_NToken_Cspace_div_equal_space (_NCp1_NToken_Cspace_mul_equal_space + 1)
#define _NCp1_NToken_Cspace_lshift_equal_space (_NCp1_NToken_Cspace_div_equal_space + 1)
#define _NCp1_NToken_Cspace_rshift_equal_space (_NCp1_NToken_Cspace_lshift_equal_space + 1)
#define _NCp1_NToken_Cspace_and_equal_space (_NCp1_NToken_Cspace_rshift_equal_space + 1)
#define _NCp1_NToken_Cspace_or_equal_space (_NCp1_NToken_Cspace_and_equal_space + 1)
#define _NCp1_NToken_Cspace_xor_equal_space (_NCp1_NToken_Cspace_or_equal_space + 1)
#define _NCp1_NToken_Cexpoint (_NCp1_NToken_Cspace_xor_equal_space + 1)
#define _NCp1_NToken_Cloop (_NCp1_NToken_Cexpoint + 1)
#define _NCp1_NToken_Clcbrace_lparen (_NCp1_NToken_Cloop + 1)
#define _NCp1_NId_Cnil (-1)
#define _NCp1_NId_C0 (_NCp1_NId_Cnil + 1)
#define _NCp1_NExprI_Cnil (-1)
#define _NCp1_NExprI_C0 (_NCp1_NExprI_Cnil + 1)
#define _NCp1_NAssign_Ceq 0
#define _NCp1_NMath_Cadd 0
#define _NCp1_NBools_Cand 0
#define _NCp1_NInclude_C0 (_NCp1_NInclude_Cnil + 1)
#define _NCp1_NBasicTypeId_Cref (_NCp1_NBasicTypeId_Crelative + 1)
#define _NCp1_NBasicTypeId_Cbool (_NCp1_NBasicTypeId_Cref + 1)
#define _NCp1_NBasicTypeId_Cchar (_NCp1_NBasicTypeId_Cbool + 1)
#define _NCp1_NBasicTypeId_Cintc (_NCp1_NBasicTypeId_Cchar + 1)
#define _NCp1_NBasicTypeId_Ci8 (_NCp1_NBasicTypeId_Cintc + 1)
#define _NCp1_NBasicTypeId_Cu8 (_NCp1_NBasicTypeId_Ci8 + 1)
#define _NCp1_NBasicTypeId_Ci16 (_NCp1_NBasicTypeId_Cu8 + 1)
#define _NCp1_NBasicTypeId_Cu16 (_NCp1_NBasicTypeId_Ci16 + 1)
#define _NCp1_NBasicTypeId_Ci32 (_NCp1_NBasicTypeId_Cu16 + 1)
#define _NCp1_NExprInt_Cdec 0
#define _NCp1_NUnary_Cneg 0
#define _NCp1_NCompare_Ceq 0
#define _NCp1_NCvarFlags_Cset_expr (1)
#define _NCp1_NCvarFlags_C0 0
#define _NCp1_NEnumFlags_Creal_name (1)
#define _NCp1_NEnumFlags_C0 0
#define _NCp1_NStructFlags_Creal_name (1)
#define _NCp1_NStructFlags_C0 0
#define _NCp1_NFuncFlags_Cinline (2)
#define _NCp1_NFuncFlags_Chas_body (1)
#define _NCp1_NFuncFlags_Creal_name (64)
#define _NCp1_NFuncFlags_C0 0
#define _NCp1_NFuncFlags_Ccase (128)
#define _NCp1_NFuncFlags_Cdecl (512)
#define _NCp1_NFuncFlags2_C0 0
#define _NCp1_NFuncFlags2_Cmain (1)
#define _NCp1_NAt_Croot (_NCp1_NAt_Cnil + 1)
#define _NCp1_NVarFlags_C0 0
#define _NCp1_NVarFlags_Creal_name (1)
#define _NCp1_NVarFlags_Cextern (2)
#define _NCp1_NVarFlags_Cno_decl (4)
#define _NCp1_Cexpr_call_nest_limit (8)
#define _NCp1_NExprType_Cnil 0
#define _NCp1_NExprType_Ccall_method (_NCp1_NExprType_Cnil + 1)
#define _NCp1_NExprType_Clvar (_NCp1_NExprType_Ccall_method + 1)
#define _NCp1_NExprType_Cgvar (_NCp1_NExprType_Clvar + 1)
#define _NCp1_NExprType_Cmath (_NCp1_NExprType_Cgvar + 1)
#define _NCp1_NExprType_Cassign (_NCp1_NExprType_Cmath + 1)
#define _NCp1_NExprType_Cbools (_NCp1_NExprType_Cassign + 1)
#define _NCp1_NExprType_Cfunc (_NCp1_NExprType_Cbools + 1)
#define _NCp1_Ccp1_carg_limit (64)
#define _NCp1_NExprType_Cmethod (_NCp1_NExprType_Cfunc + 1)
#define _NCp1_NStmtType_Cspace 0
#define _NCp1_NStmtType_Cif (_NCp1_NStmtType_Cspace + 1)
#define _NCp1_NStmtType_Cif_elif (_NCp1_NStmtType_Cif + 1)
#define _NCp1_NStmtType_Cif_else (_NCp1_NStmtType_Cif_elif + 1)
#define _NCp1_NStmtType_Cif_end (_NCp1_NStmtType_Cif_else + 1)
#define _NCp1_NStmtType_Cdo (_NCp1_NStmtType_Cif_end + 1)
#define _NCp1_NStmtType_Cdo_end (_NCp1_NStmtType_Cdo + 1)
#define _NCp1_NStmtType_Cwhile (_NCp1_NStmtType_Cdo_end + 1)
#define _NCp1_NStmtType_Cwhile_end (_NCp1_NStmtType_Cwhile + 1)
#define _NCp1_NStmtType_Cexpr (_NCp1_NStmtType_Cwhile_end + 1)
#define _NCp1_NStmtType_Creturn (_NCp1_NStmtType_Cexpr + 1)
#define _NCp1_NStmtType_Ccontinue (_NCp1_NStmtType_Creturn + 1)
#define _NCp1_NStmtType_Cbreak (_NCp1_NStmtType_Ccontinue + 1)
#define _NCp1_NFuncFlags_Ccp1_name (256)
#define _NCp1_NFuncFlags_Cprocess (4)
#define _NCp1_NFuncFlags_Cvar_args (8)
#define _NCp1_NFuncFlags_Cno_decl (16)
#define _NCp1_NFuncFlags_Cno_body (32)
#define _NCp1_NLvar_Cnil (-1)
#define _NCp1_NStmtSpaceFlags_Cskip_lvar_decl (1)
#define _NCp1_NStmtSpaceFlags_C0 0
#define _NCp1_NExprType_Cfvar (_NCp1_NExprType_Cmethod + 1)
#define _NCp1_Cdecl_at_nest_limit (8)
#define _NCp1_NAt_Crelative (_NCp1_NAt_Croot + 1)
#define _NCp1_NExprType_Ci32 (_NCp1_NExprType_Cfvar + 1)
#define _NCp1_NExprType_Ccvar (_NCp1_NExprType_Ci32 + 1)
#define _NCp1_NExprType_Cstr (_NCp1_NExprType_Ccvar + 1)
#define _NCp1_NExprType_Cindex (_NCp1_NExprType_Cstr + 1)
#define _NCp1_NExprType_Cunary (_NCp1_NExprType_Cindex + 1)
#define _NCp1_NExprType_Ccompare (_NCp1_NExprType_Cunary + 1)
#define _NCp1_NExprType_Cbool (_NCp1_NExprType_Ccompare + 1)
#define _NCp1_NExprType_Cnull (_NCp1_NExprType_Cbool + 1)
#define _NCp1_NExprType_Ccast_fast (_NCp1_NExprType_Cnull + 1)
#define _NCp1_NExprType_Cref (_NCp1_NExprType_Ccast_fast + 1)
#define _NCp1_NExprType_Cchar (_NCp1_NExprType_Cref + 1)
#define _NCp1_NExprType_Csize_of_type (_NCp1_NExprType_Cchar + 1)
#define _NCp1_NCvar_Cnil (-1)
#define _NCp1_NCvarFlags_Cas_enum (2)
#define _NCp1_NStructFlags_Cunion (4)
#define _NCp1_NStructFlags_Cno_decl (2)
#define _NCp1_NStmtType_Cswitch (_NCp1_NStmtType_Cbreak + 1)
#define _NCp1_NStmtType_Ccase (_NCp1_NStmtType_Cswitch + 1)
#define _NCp1_NStmtType_Cdefault (_NCp1_NStmtType_Ccase + 1)
#define _NCp1_NStmtType_Ccase_end (_NCp1_NStmtType_Cdefault + 1)
#define _NCp1_NStmtType_Cdefault_end (_NCp1_NStmtType_Ccase_end + 1)
#define _NCp1_NStmtType_Cswitch_end (_NCp1_NStmtType_Cdefault_end + 1)
#define _NCp1_Cdebug_rd_wr (true)
#define _NCp1_NFunc_C0 (_NCp1_NFunc_Cnil + 1)
#define _NCp1_NFunc_C1 (_NCp1_NFunc_C0 + 1)
#define _NCp1_NLvarFlags_Cset_expr (1)
#define _NCp1_NLvarFlags_C0 0
#define _NCp1_NStmtType_Cnil (255)
#define _NCp1_Cdecl_var_size_limit (8)
#define _NCp1_NToken_Cwhile (_NCp1_NToken_Clcbrace_lparen + 1)
#define _NCp1_NToken_Cif (_NCp1_NToken_Cwhile + 1)
#define _NCp1_NToken_Cspace_elif (_NCp1_NToken_Cif + 1)
#define _NCp1_NToken_Cspace_else (_NCp1_NToken_Cspace_elif + 1)
#define _NCp1_NToken_Cswitch (_NCp1_NToken_Cspace_else + 1)
#define _NCp1_NToken_Cspace_at_fall_through (_NCp1_NToken_Cswitch + 1)
#define _NCp1_NToken_Ccase (_NCp1_NToken_Cspace_at_fall_through + 1)
#define _NCp1_NToken_Cdefault (_NCp1_NToken_Ccase + 1)
#define _NCp1_NToken_Ccontinue (_NCp1_NToken_Cdefault + 1)
#define _NCp1_NToken_Cbreak (_NCp1_NToken_Ccontinue + 1)
#define _NCp1_NToken_Creturn (_NCp1_NToken_Cbreak + 1)
#define _NCp1_NToken_Cvar (_NCp1_NToken_Creturn + 1)
#define _NCp1_NToken_Cspace_at_extern (_NCp1_NToken_Cvar + 1)
#define _NCp1_NToken_Cspace_at_union (_NCp1_NToken_Cspace_at_extern + 1)
typedef int32_t _NCp1_NFunc;
typedef int32_t _NCp1_NInclude;
typedef int _NStdc_NFd;
typedef int _NStdc_NOpenFlags;
typedef int _NStdc_NExit;
typedef int _NStdc_NSeek;
typedef int32_t _NCp1_NAt;
typedef uint8_t _NCp1_NNameType;
typedef int32_t _NCp1_NId;
typedef uint8_t _NCp1_NBasicTypeId;
typedef uint32_t _NCp1_NFuncFlags;
typedef uint32_t _NCp1_NVarFlags;
typedef int32_t _NCp1_NExprI;
typedef uint8_t _NCp1_NStmtType;
typedef uint8_t _NCp1_NStmtSpaceFlags;
typedef int32_t _NCp1_NLvar;
typedef uint8_t _NCp1_NLvarFlags;
typedef int32_t _NCp1_NStruct;
typedef uint8_t _NCp1_NStructFlags;
typedef uint32_t _NCp1_NToken;
typedef uint8_t _NCp1_NAssign;
typedef uint8_t _NCp1_NMath;
typedef uint8_t _NCp1_NBools;
typedef uint8_t _NCp1_NExprInt;
typedef uint8_t _NCp1_NUnary;
typedef uint8_t _NCp1_NCompare;
typedef int32_t _NCp1_NCvar;
typedef uint8_t _NCp1_NCvarFlags;
typedef int32_t _NCp1_NGvar;
typedef uint8_t _NCp1_NGvarFlags;
typedef int32_t _NCp1_NEnum;
typedef uint8_t _NCp1_NEnumFlags;
typedef uint32_t _NCp1_NFuncFlags2;
typedef uint8_t _NCp1_NExprType;
typedef uint8_t _NCp1_NExprFlags;
typedef int32_t _NCp1_NAlias;
struct _NCp1_NMap;
struct _NCp1_NMap {
uint64_t _Fdata[(_NCp1_Chash_table_size + 7) >> 3];
};
struct _NCp1_NAtMap;
struct _NCp1_NAtMap {
uint64_t _Fdata[(_NCp1_Chash_table_size + 7) >> 3];
};
union _NCp1_NRdr;
union _NCp1_NRdr {
void* _Freff;
size_t _Fpos;
uint8_t* _Fp1;
char* _Fcharr;
uint32_t* _Fp4;
};
union _NCp1_NWtr;
union _NCp1_NWtr {
void* _Freff;
size_t _Fpos;
uint8_t* _Fp1;
uint32_t* _Fp4;
};
union _NCp1_NAtName;
union _NCp1_NAtName {
_NCp1_NId _Fid;
_NCp1_NBasicTypeId _Fbasic;
};
struct _NCp1_NAtData;
struct _NCp1_NAtData {
_NCp1_NNameType _Ftype;
_NCp1_NAt _Fparent;
union _NCp1_NAtName _Fname;
};
struct _NCp1_NTypeInfo;
struct _NCp1_NTypeInfo {
int8_t _Fref_v[_NCp1_Ctype_info_star_limit];
int8_t _Farray_c;
int8_t _Fstar_c;
bool _Fbuilt_in;
bool _Fconst;
};
struct _NCp1_NDeclVarData;
struct _NCp1_NDeclVarData {
_NCp1_NId _Fname;
_NCp1_NAt _Ftype;
_NCp1_NVarFlags _Fflags;
_NCp1_NId _Freal_name;
struct _NCp1_NTypeInfo _Ftype_info;
uint8_t _Fsize_c;
_NCp1_NExprI* _Fsize_expr_v;
};
struct _NCp1_NStmt;
struct _NCp1_NStmt {
int32_t _Fbegin_row;
int32_t _Fbegin_col;
int32_t _Fend_row;
int32_t _Fend_col;
_NCp1_NStmtType _Ftype;
struct _NCp1_NStmt* _Fstmt_next;
};
struct _NCp1_NStmtSpace;
struct _NCp1_NStmtSpace {
struct _NCp1_NStmt _Fbase;
struct _NCp1_NStmtSpace* _Fparent;
_NCp1_NStmtSpaceFlags _Fflags;
struct _NCp1_NStmt* _Fstmt_first;
struct _NCp1_NStmt* _Fstmt_last;
int32_t _Flvar_c;
int32_t _Flvar_cap;
_NCp1_NLvar* _Flvar_v;
};
struct _NCp1_NLvarData;
struct _NCp1_NLvarData {
int32_t _Frow;
int32_t _Fcol;
struct _NCp1_NDeclVarData _Fdecl;
_NCp1_NLvarFlags _Fflags;
_NCp1_NExprI _Fset_expr;
};
struct _NCp1_NFarg;
struct _NCp1_NFarg {
int32_t _Frow;
int32_t _Fcol;
struct _NCp1_NDeclVarData _Fdecl;
};
struct _NCp1_NDeclFunc;
struct _NCp1_NDeclFunc {
int32_t _Fbegin_row;
int32_t _Fbegin_col;
int32_t _Fend_row;
int32_t _Fend_col;
_NCp1_NInclude _Finclude;
_NCp1_NAt _Fat;
_NCp1_NFuncFlags _Fflags;
_NCp1_NId _Freal_name;
char* _Fdecl_str;
int32_t _Fdecl_len;
_NCp1_NId _Fcas;
struct _NCp1_NDeclVarData _Fdecl;
struct _NCp1_NStmtSpace* _Fstmt_space;
_NCp1_NLvar _Flvar_c;
_NCp1_NLvar _Flvar_cap;
struct _NCp1_NLvarData** _Flvar_v;
int8_t _Fthis_idx;
int8_t _Fthis_group;
int8_t _Fgroup_c;
int8_t _Fgroup_v[_NCp1_Cexpr_carg_group_limit];
uint8_t _Ffarg_c;
struct _NCp1_NFarg _Ffarg_v[0];
};
struct _NCp1_NFvarData;
struct _NCp1_NFvarData {
struct _NCp1_NDeclVarData _Fdecl;
};
struct _NCp1_NStructData;
struct _NCp1_NStructData {
int32_t _Fbegin_row;
int32_t _Fbegin_col;
int32_t _Fend_row;
int32_t _Fend_col;
_NCp1_NInclude _Finclude;
_NCp1_NAt _Fat;
_NCp1_NStructFlags _Fflags;
_NCp1_NId _Freal_name;
uint32_t _Ffvar_c;
struct _NCp1_NFvarData _Ffvar_v[0];
};
struct _NCp1_NParser;
struct _NCp1_NParser {
};
struct _NCp1_NLexer;
struct _NCp1_NLexer {
uint8_t* _Fcontent;
uint8_t* _Fstart;
uint8_t* _Fcursor;
uint8_t* _Fmarker;
};
struct _NCp1_NTokenData;
struct _NCp1_NTokenData {
int32_t _Frow;
int32_t _Fcol;
int32_t _Fid;
int32_t _Fid2;
int32_t _Fval[12];
};
struct _NCp1_NCvarData;
struct _NCp1_NCvarData {
int32_t _Frow;
int32_t _Fcol;
_NCp1_NInclude _Finclude;
_NCp1_NAt _Fat;
_NCp1_NCvarFlags _Fflags;
struct _NCp1_NDeclVarData _Fdecl;
_NCp1_NExprI _Fexpr_set;
_NCp1_NCvar _Flast_cvar;
};
struct _NCp1_NDeclGvar;
struct _NCp1_NDeclGvar {
int32_t _Frow;
int32_t _Fcol;
_NCp1_NInclude _Finclude;
_NCp1_NAt _Fat;
_NCp1_NGvarFlags _Fflags;
struct _NCp1_NDeclVarData _Fdecl;
};
struct _NCp1_NEnumData;
struct _NCp1_NEnumData {
int32_t _Fbegin_row;
int32_t _Fbegin_col;
int32_t _Fend_row;
int32_t _Fend_col;
_NCp1_NInclude _Finclude;
_NCp1_NAt _Fat;
_NCp1_NAt _Fbase_type;
_NCp1_NEnumFlags _Fflags;
_NCp1_NId _Freal_name;
};
struct _NCp1_NExpr;
struct _NCp1_NExpr {
_NCp1_NExprType _Ftype;
_NCp1_NExprFlags _Fflags;
};
struct _NCp1_NCarg;
struct _NCp1_NCarg {
int8_t _Freff;
_NCp1_NExprI _Fexpr;
};
struct _NCp1_NExprFunc;
struct _NCp1_NExprFunc {
struct _NCp1_NExpr _Fbase;
_NCp1_NAt _Fat;
_NCp1_NId _Ffunc_name;
uint8_t _Fgroup_c;
uint8_t _Fgroup_v[_NCp1_Cexpr_carg_group_limit];
uint8_t _Fcarg_c;
struct _NCp1_NCarg _Fcarg_v[0];
};
struct _NCp1_NExprMethod;
struct _NCp1_NExprMethod {
struct _NCp1_NExpr _Fbase;
_NCp1_NExprI _Fthiss;
_NCp1_NId _Ffunc_name;
uint8_t _Fgroup_c;
uint8_t _Fgroup_v[_NCp1_Cexpr_carg_group_limit];
uint8_t _Fcarg_c;
struct _NCp1_NCarg _Fcarg_v[0];
};
struct _NCp1_NExprStrNode;
struct _NCp1_NExprStrNode {
struct _NCp1_NExprStrNode* _Fnext;
int32_t _Flen;
char _Fbuf[0];
};
struct _NCp1_NExprStr;
struct _NCp1_NExprStr {
struct _NCp1_NExpr _Fbase;
int32_t _Fnode_c;
struct _NCp1_NExprStrNode* _Ffirst;
struct _NCp1_NExprStrNode* _Flast;
};
struct _NCp1_NStmtExpr;
struct _NCp1_NStmtExpr {
struct _NCp1_NStmt _Fbase;
_NCp1_NExprI _Fexpr;
};
struct _NCp1_NValue;
struct _NCp1_NValue {
int8_t _Freff;
bool _Fparen;
_NCp1_NAt _Ftype;
struct _NCp1_NTypeInfo _Finfo;
};
struct _NCp1_NStmtReturn;
struct _NCp1_NStmtReturn {
struct _NCp1_NStmt _Fbase;
_NCp1_NExprI _Fexpr;
struct _NCp1_NValue _Fval;
};
struct _NCp1_NStmtContinue;
struct _NCp1_NStmtContinue {
struct _NCp1_NStmt _Fbase;
uint8_t _Fnest;
};
struct _NCp1_NStmtBreak;
struct _NCp1_NStmtBreak {
struct _NCp1_NStmt _Fbase;
uint8_t _Fnest;
};
struct _NCp1_NExprLvar;
struct _NCp1_NExprLvar {
struct _NCp1_NExpr _Fbase;
_NCp1_NLvar _Flvar;
};
struct _NCp1_NExprGvar;
struct _NCp1_NExprGvar {
struct _NCp1_NExpr _Fbase;
_NCp1_NAt _Fat;
_NCp1_NId _Fname;
};
struct _NCp1_NExprFvar;
struct _NCp1_NExprFvar {
struct _NCp1_NExpr _Fbase;
_NCp1_NExprI _Fexpr;
_NCp1_NId _Fmember;
};
struct _NCp1_NExprAssign;
struct _NCp1_NExprAssign {
struct _NCp1_NExpr _Fbase;
_NCp1_NExprI _Fleft;
_NCp1_NExprI _Fright;
_NCp1_NAssign _Ftype;
};
struct _NCp1_NExprMathItem;
struct _NCp1_NExprMathItem {
_NCp1_NExprI _Fexpr;
};
struct _NCp1_NExprMath;
struct _NCp1_NExprMath {
struct _NCp1_NExpr _Fbase;
_NCp1_NExprI _Fleft;
_NCp1_NExprI _Fright;
_NCp1_NMath _Ftype;
uint8_t _Fitem_c;
uint8_t _Fitem_cap;
struct _NCp1_NExprMathItem* _Fitem_v;
};
struct _NCp1_NExprBoolsItem;
struct _NCp1_NExprBoolsItem {
_NCp1_NExprI _Fexpr;
};
struct _NCp1_NExprBools;
struct _NCp1_NExprBools {
struct _NCp1_NExpr _Fbase;
_NCp1_NExprI _Fleft;
_NCp1_NExprI _Fright;
_NCp1_NBools _Ftype;
uint8_t _Fitem_c;
uint8_t _Fitem_cap;
struct _NCp1_NExprBoolsItem* _Fitem_v;
};
struct _NCp1_NRowCol;
struct _NCp1_NRowCol {
int32_t _Frow;
int32_t _Fcol;
};
struct _NCp1_NExprIntData;
struct _NCp1_NExprIntData {
struct _NCp1_NExpr _Fbase;
int32_t _Fvalue;
_NCp1_NExprInt _Ftype;
};
struct _NCp1_NExprSizeOfType;
struct _NCp1_NExprSizeOfType {
struct _NCp1_NExpr _Fbase;
_NCp1_NAt _Ftype;
};
struct _NCp1_NExprNull;
struct _NCp1_NExprNull {
struct _NCp1_NExpr _Fbase;
};
struct _NCp1_NExprCvar;
struct _NCp1_NExprCvar {
struct _NCp1_NExpr _Fbase;
_NCp1_NAt _Fat;
_NCp1_NId _Fname;
};
struct _NCp1_NExprUnary;
struct _NCp1_NExprUnary {
struct _NCp1_NExpr _Fbase;
_NCp1_NExprI _Fexpr;
_NCp1_NUnary _Ftype;
};
struct _NCp1_NExprRef;
struct _NCp1_NExprRef {
struct _NCp1_NExpr _Fbase;
_NCp1_NExprI _Fexpr;
};
struct _NCp1_NExprCastFast;
struct _NCp1_NExprCastFast {
struct _NCp1_NExpr _Fbase;
_NCp1_NExprI _Fexpr;
_NCp1_NAt _Ftype;
};
struct _NCp1_NExprIndex;
struct _NCp1_NExprIndex {
struct _NCp1_NExpr _Fbase;
_NCp1_NExprI _Fleft;
_NCp1_NExprI _Fright;
};
struct _NCp1_NStmtSwitch;
struct _NCp1_NStmtSwitch {
struct _NCp1_NStmt _Fbase;
_NCp1_NExprI _Fexpr;
_NCp1_NExprI _Fcases;
};
struct _NCp1_NStmtCaseItem;
struct _NCp1_NStmtCaseItem {
_NCp1_NExprI _Fexpr;
};
struct _NCp1_NStmtCase;
struct _NCp1_NStmtCase {
struct _NCp1_NStmt _Fbase;
bool _Ffall_through;
uint32_t _Fexpr_c;
struct _NCp1_NStmtCaseItem _Fexpr_v[0];
};
struct _NCp1_NStmtCaseEnd;
struct _NCp1_NStmtCaseEnd {
struct _NCp1_NStmt _Fbase;
};
struct _NCp1_NStmtDefault;
struct _NCp1_NStmtDefault {
struct _NCp1_NStmt _Fbase;
bool _Ffall_through;
};
struct _NCp1_NStmtDefaultEnd;
struct _NCp1_NStmtDefaultEnd {
struct _NCp1_NStmt _Fbase;
};
struct _NCp1_NStmtSwitchEnd;
struct _NCp1_NStmtSwitchEnd {
struct _NCp1_NStmt _Fbase;
};
struct _NCp1_NStmtIf;
struct _NCp1_NStmtIf {
struct _NCp1_NStmt _Fbase;
bool _Fnot;
_NCp1_NExprI _Fexpr;
};
struct _NCp1_NStmtDoEnd;
struct _NCp1_NStmtDoEnd {
struct _NCp1_NStmt _Fbase;
struct _NCp1_NStmtDo* _Fdo;
};
struct _NCp1_NStmtDo;
struct _NCp1_NStmtDo {
struct _NCp1_NStmt _Fbase;
_NCp1_NExprI _Fexpr;
struct _NCp1_NStmtSpace* _Fcontinu;
struct _NCp1_NStmtDoEnd* _Fend;
};
struct _NCp1_NStmtWhileEnd;
struct _NCp1_NStmtWhileEnd {
struct _NCp1_NStmt _Fbase;
struct _NCp1_NStmtWhile* _Fwhil;
};
struct _NCp1_NStmtWhile;
struct _NCp1_NStmtWhile {
struct _NCp1_NStmt _Fbase;
_NCp1_NExprI _Fexpr;
struct _NCp1_NStmtSpace* _Fcontinu;
struct _NCp1_NStmtWhileEnd* _Fend;
};
union _NCp1_NNest;
union _NCp1_NNest {
struct _NCp1_NStmtDo* _Fdo;
struct _NCp1_NStmtWhile* _Fwhil;
void* _Freff;
};
struct _NCp1_NStmtIfElse;
struct _NCp1_NStmtIfElse {
struct _NCp1_NStmt _Fbase;
};
struct _NCp1_NStmtIfEnd;
struct _NCp1_NStmtIfEnd {
struct _NCp1_NStmt _Fbase;
};
struct _NCp1_NExprCompare;
struct _NCp1_NExprCompare {
struct _NCp1_NExpr _Fbase;
_NCp1_NExprI _Fleft;
_NCp1_NExprI _Fright;
_NCp1_NCompare _Ftype;
};
struct _NCp1_NExprBool;
struct _NCp1_NExprBool {
struct _NCp1_NExpr _Fbase;
bool _Fvalue;
};
struct _NCp1_NExprChar;
struct _NCp1_NExprChar {
struct _NCp1_NExpr _Fbase;
char _Fvalue;
};
struct _NCp1_NStmtIfElif;
struct _NCp1_NStmtIfElif {
struct _NCp1_NStmt _Fbase;
bool _Fnot;
_NCp1_NExprI _Fexpr;
};
struct _NCp1_NMap _Gid_map;
struct _NCp1_NMap _Ginclude_map;
struct _NCp1_NAtMap _Gat_map;
_NCp1_NFunc _Gfunc_main;
_NCp1_NInclude _Gdecl_include;
char* input_path;
int32_t _Gid_cap;
char** _Gid_str_v;
uint8_t* _Gid_len_v;
int32_t _Ginclude_cap;
char** _Ginclude_str_v;
uint8_t* _Ginclude_len_v;
_NCp1_NAt _Gat_cap;
struct _NCp1_NAtData* _Gat_v;
_NCp1_NAt _Gat_c;
_NCp1_NFunc _Gfunc_cap;
struct _NCp1_NDeclFunc** _Gfunc_v;
_NCp1_NStruct _Gstruct_cap;
struct _NCp1_NStructData** _Gstruct_v;
uint32_t _Gdecl_fvar_cap;
struct _NCp1_NDeclVarData* _Gdecl_fvar_v;
extern int32_t _Grow;
extern int32_t _Gcol;
extern int32_t _Glast_row;
extern int32_t _Glast_col;
_NCp1_NToken _Glast_token;
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
char* _Glock_path;
int32_t _Gquick_alloc_cap;
void* _Gquick_alloc_v;
int32_t _Gquick_alloc_c;
_NCp1_NCvar _Gcvar_c;
struct _NCp1_NCvarData* _Gcvar_v;
_NCp1_NGvar _Ggvar_c;
struct _NCp1_NDeclGvar* _Ggvar_v;
_NCp1_NEnum _Genum_c;
struct _NCp1_NEnumData** _Genum_v;
_NCp1_NStruct _Gstruct_c;
_NCp1_NFunc _Gfunc_c;
_NCp1_NId _Gdecl_func_name;
int32_t _Gdecl_func_row;
int32_t _Gdecl_func_col;
_NCp1_NFuncFlags _Gdecl_func_flags;
_NCp1_NFuncFlags2 _Gdecl_func_flags2;
int32_t _Gdecl_farg_c;
int8_t _Gdecl_farg_group_c;
int8_t _Gdecl_farg_group_v[_NCp1_Cexpr_carg_group_limit];
int8_t _Gdecl_func_this_idx;
int8_t _Gdecl_func_this_group;
_NCp1_NId _Gdecl_func_real_name;
_NCp1_NId _Gdecl_func_case;
char* _Gdecl_func_decl_str;
int32_t _Gdecl_func_decl_len;
struct _NCp1_NStmtSpace* _Gdecl_func_space;
struct _NCp1_NStmtSpace* _Gdecl_func_ctx_space;
struct _NCp1_NDeclFunc* _Gctx_func;
int32_t _Gnest_id;
_NCp1_NAt _Gdecl_at;
struct _NCp1_NDeclVarData _Gdecl_var;
struct _NCp1_NFarg* _Gdecl_farg_v;
uint32_t _Gdecl_fvar_c;
int32_t _Gdecl_struct_row;
int32_t _Gdecl_struct_col;
_NCp1_NAt _Gdecl_struct_at;
_NCp1_NStructFlags _Gdecl_struct_flags;
_NCp1_NId _Gdecl_struct_real_name;
int32_t _Gdecl_var_row;
int32_t _Gdecl_var_col;
int32_t _Gdecl_farg_cap;
int8_t _Gexpr_call_c;
uint8_t _Gexpr_call_carg_c[_NCp1_Cexpr_call_nest_limit];
uint8_t _Gexpr_call_cgrp_c[_NCp1_Cexpr_call_nest_limit];
uint8_t _Gexpr_call_cgrp_v[_NCp1_Cexpr_call_nest_limit][_NCp1_Cexpr_carg_group_limit];
_NCp1_NExprI _Gexpr_call_carg_v[_NCp1_Cexpr_call_nest_limit][_NCp1_Ccp1_carg_limit];
uint8_t _Gnest_stack_c;
extern int32_t _Gstring_len;
extern char* _Gstring_buf;
int32_t _Gdecl_include_row;
int32_t _Gdecl_include_col;
_NCp1_NAt _Gbuild_at;
_NCp1_NAt _Gdecl_at_v[_NCp1_Cdecl_at_nest_limit];
uint8_t _Gdecl_at_c;
_NCp1_NAlias _Gat_alias_c;
_NCp1_NId* _Gat_alias_name_v;
struct _NCp1_NRowCol* _Gat_alias_pos_v;
_NCp1_NAlias _Gat_alias_cap;
_NCp1_NAt* _Gat_alias_at_v;
bool _Gat_begin_relative_pause;
_NCp1_NGvar _Ggvar_cap;
int32_t _Gdecl_enum_row;
int32_t _Gdecl_enum_col;
_NCp1_NAt _Gdecl_enum_at;
_NCp1_NEnumFlags _Gdecl_enum_flags;
_NCp1_NCvar _Gdecl_enum_last_cvar;
_NCp1_NEnum _Genum_cap;
_NCp1_NCvar _Glast_cvar;
_NCp1_NCvar _Gcvar_cap;
uint32_t _Gswitch_expr_c;
uint32_t _Gswitch_expr_cap;
_NCp1_NExprI* _Gswitch_expr_v;
int32_t _Gnest_stack_id_v[64];
union _NCp1_NNest _Gnest_stack_ptr_v[64];
int32_t _Gexpr_c;
int32_t _Gexpr_cap;
struct _NCp1_NExpr** _Gexpr_v;
int main(int _Larg_c_0, char** _Larg_v_1);
void _NCp1_Pexport_0();
void _NCp1_NMap_Pinit_1(struct _NCp1_NMap* _Lm_0);
void _NCp1_NAtMap_Pinit_1(struct _NCp1_NAtMap* _Lm_0);
void _NCp1_Pquick_alloc_init_0();
bool _NStdc_NFd_Popen_3(_NStdc_NFd* _Lfile_0, char* _Lpath_1, _NStdc_NOpenFlags _Lflags_2);
int _NStdc_NFd_Pclose_1(_NStdc_NFd _Lfile_0);
void _NCp1_Pget_row_col_4(int32_t* _Lout_row_0, int32_t* _Lout_col_1, void* _Lend_2, void* _Lbegin_3);
void _NCp1_Pparse_string_4(union _NCp1_NRdr* _Lr_0, union _NCp1_NWtr* _Lw_1, char _Lending_2, void* _Lin_data_3);
void _NCp1_Pparse_str_init_1(int32_t _Lmax_size_0);
#define _NCp1_Pmalloc_arr_2(r, c) r = malloc(sizeof(r[0]) * (c)); memset(r, 0, sizeof(r[0]) * (c))
struct _NCp1_NParser* _NCp1_NParser_Palloc_0();
void _NCp1_NLexer_Pinit_3(struct _NCp1_NLexer* _Llex_0, uint8_t* _Ldata_1, size_t _Lsize_2);
_NCp1_NToken cp1_lexer_scan(struct _NCp1_NLexer* _Llex_0);
void cp1Parse(struct _NCp1_NParser* _Lpsr_0, _NCp1_NToken _Lt_1, struct _NCp1_NTokenData* _Ltok_2);
int32_t _NCp1_Pchar_escape_value_1(char _Lc_0);
int32_t _NCp1_NLexer_Pget_id_3(struct _NCp1_NLexer* _Llex_0, uint8_t _Lbegin_1, uint8_t _Lend_2);
uint32_t _NCp1_NLexer_Pget_u32_dec_1(struct _NCp1_NLexer* _Llex_0);
uint32_t _NCp1_NLexer_Pget_u32_oct_1(struct _NCp1_NLexer* _Llex_0);
int32_t _NCp1_NLexer_Pget_include_1(struct _NCp1_NLexer* _Llex_0);
void _NCp1_NParser_Pfree_1(struct _NCp1_NParser* _Lpsr_0);
void* qalloc(int32_t _Lsize_0);
void _NCp1_NWtr_Pn1_2(union _NCp1_NWtr* _Lw_0, uint8_t _Ln_1);
void _NCp1_NWtr_Pcopy_3(union _NCp1_NWtr* _Lw_0, void* _Ldata_1, int32_t _Lsize_2);
void _NCp1_NNameType_Pwr_2(_NCp1_NNameType _Li_0, union _NCp1_NWtr* _Lw_1);
void _NCp1_NBasicTypeId_Pwr_2(_NCp1_NBasicTypeId _Le_0, union _NCp1_NWtr* _Lw_1);
void _NCp1_NAt_Pwr_3(_NCp1_NAt _Lat_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2);
void _NCp1_NId_Pwr_3(_NCp1_NId _Lid_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2);
void _NCp1_Pwrite_cvar_2(union _NCp1_NWtr* _Lw_0, bool _Lheader_1);
void _NCp1_Pwrite_gvar_2(union _NCp1_NWtr* _Lw_0, bool _Lheader_1);
void _NCp1_Pwrite_enum_2(union _NCp1_NWtr* _Lw_0, bool _Lheader_1);
void _NCp1_Pwrite_struct_2(union _NCp1_NWtr* _Lw_0, bool _Lheader_1);
void _NCp1_Pwrite_func_2(union _NCp1_NWtr* _Lw_0, bool _Lheader_1);
bool _NStdc_NFd_Popen_4(_NStdc_NFd* _Lfile_0, char* _Lpath_1, _NStdc_NOpenFlags _Lflags_2, int _Lmode_3);
void _NCp1_NAt_Pwr_header_2(_NCp1_NAt _Lid_0, union _NCp1_NWtr* _Lw_1);
void _NCp1_NId_Pwr_header_2(_NCp1_NId _Lid_0, union _NCp1_NWtr* _Lw_1);
void qalloc_undo(int32_t _Lsize_0);
void _NCp1_Pdecl_func_begin_3(_NCp1_NId _Lname_0, int32_t _Lrow_1, int32_t _Lcol_2);
void _NCp1_Pdecl_func_end_2(int32_t _Lrow_0, int32_t _Lcol_1);
void _NCp1_Pdecl_struct_end_2(int32_t _Lrow_0, int32_t _Lcol_1);
void _NCp1_Pdecl_var_begin_3(_NCp1_NId _Lname_0, int32_t _Lrow_1, int32_t _Lcol_2);
void _NCp1_Pdecl_var_attr_real_name_1(_NCp1_NId _Lname_0);
void _NCp1_Pdecl_var_attr_extern_0();
void _NCp1_Pdecl_var_attr_no_decl_0();
void _NCp1_Pdecl_var_end_0();
void _NCp1_Pdecl_var_as_farg_2(int32_t _Lrow_0, int32_t _Lcol_1);
void _NCp1_Pfarg_next_group_0();
void _NCp1_Pdecl_var_as_this_0();
void _NCp1_Pdecl_var_as_fvar_0();
void _NCp1_Pfunc_body_end_0();
void _NCp1_Pexpr_push_call_2(int32_t _Lrow_0, int32_t _Lcol_1);
_NCp1_NExprI _NCp1_Pexpr_pop_func_2(_NCp1_NAt _Lat_0, _NCp1_NId _Lfunc_name_1);
_NCp1_NExprI _NCp1_Pexpr_pop_method_2(_NCp1_NExprI _Lthiss_0, _NCp1_NId _Lfunc_name_1);
void _NCp1_Pcarg_push_1(_NCp1_NExprI _Lexpr_0);
void _NCp1_Pcarg_push_str_1(_NCp1_NExprI _Lexpr_0);
void _NCp1_Pcarg_next_group_0();
void _NCp1_Pexpr2stmt_5(_NCp1_NExprI _Le_0, int32_t _Lbegin_row_1, int32_t _Lbegin_col_2, int32_t _Lend_row_3, int32_t _Lend_col_4);
void _NCp1_Pstmt_return_5(_NCp1_NExprI _Le_0, int32_t _Lbegin_row_1, int32_t _Lbegin_col_2, int32_t _Lend_row_3, int32_t _Lend_col_4);
void _NCp1_Pstmt_continue_5(_NCp1_NId _Lid_0, int32_t _Lbegin_row_1, int32_t _Lbegin_col_2, int32_t _Lend_row_3, int32_t _Lend_col_4);
void _NCp1_Pstmt_break_5(_NCp1_NId _Lid_0, int32_t _Lbegin_row_1, int32_t _Lbegin_col_2, int32_t _Lend_row_3, int32_t _Lend_col_4);
void _NCp1_Pfunc_attr_main_0();
void _NCp1_Pfunc_attr_decl_0();
void _NCp1_Pfunc_attr_cp1_name_0();
void _NCp1_Pfunc_attr_process_0();
void _NCp1_Pfunc_attr_inline_0();
void _NCp1_Pfunc_attr_var_args_0();
void _NCp1_Pfunc_attr_no_decl_0();
void _NCp1_Pfunc_attr_no_body_0();
void _NCp1_Pfunc_attr_real_name_1(_NCp1_NId _Lname_0);
void _NCp1_Pfunc_attr_case_1(_NCp1_NId _Lname_0);
_NCp1_NExprI _NCp1_Pexpr_lvar_4(_NCp1_NId _Lname_0, uint8_t _Ldecl_1, int32_t _Lrow_2, int32_t _Lcol_3);
_NCp1_NExprI _NCp1_Pexpr_gvar_2(_NCp1_NAt _Lat_0, _NCp1_NId _Lname_1);
_NCp1_NExprI _NCp1_Pexpr_fvar_2(_NCp1_NExprI _Lexpr_0, _NCp1_NId _Lmember_1);
_NCp1_NExprI _NCp1_Pexpr_assign_3(_NCp1_NExprI _Lleft_0, _NCp1_NExprI _Lright_1, _NCp1_NAssign _Ltype_2);
_NCp1_NExprI _NCp1_Pexpr_math_3(_NCp1_NExprI _Lleft_0, _NCp1_NExprI _Lright_1, _NCp1_NMath _Ltype_2);
_NCp1_NExprI _NCp1_Pexpr_math_add_2(_NCp1_NExprI _Lexpr_0, _NCp1_NExprI _Lright_1);
_NCp1_NExprI _NCp1_Pexpr_bools_3(_NCp1_NExprI _Lleft_0, _NCp1_NExprI _Lright_1, _NCp1_NBools _Ltype_2);
_NCp1_NExprI _NCp1_Pexpr_bools_add_2(_NCp1_NExprI _Lbools_0, _NCp1_NExprI _Lright_1);
char* _NCp1_Ptoken_name_1(_NCp1_NToken _Ltok_0);
void _NCp1_Pdecl_var_type_1(_NCp1_NAt _Ltype_0);
void _NCp1_Pdecl_var_this_0();
void _NCp1_Pstmt_lvar_add_4(_NCp1_NId _Lname_0, _NCp1_NExprI _Lset_1, int32_t _Lrow_2, int32_t _Lcol_3);
void _NCp1_Pstmt_lvar_end_2(int32_t _Lend_row_0, int32_t _Lend_col_1);
void _NCp1_Pdecl_include_begin_3(_NCp1_NInclude _Linc_0, int32_t _Lrow_1, int32_t _Lcol_2);
void _NCp1_Pdecl_include_end_0();
void _NCp1_Pdecl_at_basic_1(_NCp1_NBasicTypeId _Ltype_0);
void _NCp1_Pdecl_at_add_2(_NCp1_NId _Lname_0, _NCp1_NNameType _Ltype_1);
void _NCp1_Pdecl_at_begin_2(int32_t _Lrow_0, int32_t _Lcol_1);
void _NCp1_Pdecl_at_begin_struct_3(_NCp1_NId _Lname_0, int32_t _Lrow_1, int32_t _Lcol_2);
void _NCp1_Pdecl_at_end_0();
void _NCp1_Pdecl_alias_4(_NCp1_NId _Lname_0, _NCp1_NAt _Lat_1, int32_t _Lrow_2, int32_t _Lcol_3);
void _NCp1_Pat_push_4(_NCp1_NId _Lname_0, _NCp1_NNameType _Ltype_1, int32_t _Lrow_2, int32_t _Lcol_3);
_NCp1_NAt _NCp1_Pat_done_0();
void _NCp1_Pat_begin_0();
void _NCp1_Pat_begin_relative_0();
void _NCp1_Pat_begin_relative_pause_0();
void _NCp1_Pat_begin_relative_resume_0();
void _NCp1_Pat_root_0();
void _NCp1_Pat_alias_3(_NCp1_NId _Lname_0, int32_t _Lrow_1, int32_t _Lcol_2);
void _NCp1_Pat_graves_3(int8_t _Lgraves_0, int32_t _Lrow_1, int32_t _Lcol_2);
_NCp1_NAt _NCp1_Pat_basic_type_1(_NCp1_NBasicTypeId _Ltype_0);
void _NCp1_Pdecl_var_as_gvar_0();
void _NCp1_Ptype_info_arr_2(_NCp1_NExprI* _Lexpr_v_0, uint8_t _Lexpr_c_1);
void _NCp1_Ptype_info_ref_1(int8_t _Lc_0);
void _NCp1_Ptype_info_static_0();
void _NCp1_Ptype_info_begin_0();
void _NCp1_Ptype_info_finalize_0();
_NCp1_NExprI _NCp1_Pexpr_int_2(int32_t _Lvalue_0, _NCp1_NExprInt _Ltype_1);
_NCp1_NExprI _NCp1_Pexpr_size_of_type_1(_NCp1_NAt _Lat_0);
_NCp1_NExprI _NCp1_Pexpr_null_0();
void _NCp1_Pdecl_at_begin_enum_3(_NCp1_NId _Lname_0, int32_t _Lrow_1, int32_t _Lcol_2);
void _NCp1_Pdecl_enum_end_3(_NCp1_NAt _Lbase_type_0, int32_t _Lrow_1, int32_t _Lcol_2);
_NCp1_NExprI _NCp1_Pexpr_cvar_2(_NCp1_NAt _Lat_0, _NCp1_NId _Lname_1);
void _NCp1_Penum_add_cvar_3(_NCp1_NId _Lname_0, int32_t _Lrow_1, int32_t _Lcol_2);
void _NCp1_Pdecl_add_cvar_3(_NCp1_NId _Lname_0, int32_t _Lrow_1, int32_t _Lcol_2);
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
void _NCp1_Pstmt_switch_set_6(_NCp1_NExprI _Lexpr_0, int32_t _Lbegin_row_1, int32_t _Lbegin_col_2, int32_t _Lend_row_3, int32_t _Lend_col_4, _NCp1_NExprI _Lcases_5);
void _NCp1_Pstmt_switch_expr_add_1(_NCp1_NExprI _Lexpr_0);
void _NCp1_Pstmt_switch_case_begin_5(int32_t _Lbegin_row_0, int32_t _Lbegin_col_1, int32_t _Lend_row_2, int32_t _Lend_col_3, bool _Lfall_through_4);
void _NCp1_Pstmt_switch_case_end_0();
void _NCp1_Pstmt_switch_default_begin_5(int32_t _Lbegin_row_0, int32_t _Lbegin_col_1, int32_t _Lend_row_2, int32_t _Lend_col_3, bool _Lfall_through_4);
void _NCp1_Pstmt_switch_default_end_0();
void _NCp1_Pstmt_switch_end_0();
void _NCp1_Pstmt_if_begin_0();
void _NCp1_Pstmt_if_set_6(bool _Lnot_0, _NCp1_NExprI _Lexpr_1, int32_t _Lbegin_row_2, int32_t _Lbegin_col_3, int32_t _Lend_row_4, int32_t _Lend_col_5);
void _NCp1_Pstmt_if_end_0();
void _NCp1_Pstmt_do_begin_0();
void _NCp1_Pstmt_do_set_6(_NCp1_NExprI _Lexpr_0, int32_t _Lbegin_row_1, int32_t _Lbegin_col_2, int32_t _Lend_row_3, int32_t _Lend_col_4, struct _NCp1_NStmtSpace* _Lcontinu_5);
void _NCp1_Pstmt_do_end_0();
void _NCp1_Pstmt_while_begin_0();
void _NCp1_Pstmt_while_set_6(_NCp1_NExprI _Lexpr_0, int32_t _Lbegin_row_1, int32_t _Lbegin_col_2, int32_t _Lend_row_3, int32_t _Lend_col_4, struct _NCp1_NStmtSpace* _Lcontinu_5);
void _NCp1_Pstmt_while_end_0();
void _NCp1_Pstmt_elif_begin_0();
void _NCp1_Pstmt_elif_set_6(bool _Lnot_0, _NCp1_NExprI _Lexpr_1, int32_t _Lbegin_row_2, int32_t _Lbegin_col_3, int32_t _Lend_row_4, int32_t _Lend_col_5);
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
int32_t _NCp1_NMap_Pget_or_insert_4(struct _NCp1_NMap* _Lm_0, char* _Lstr_1, uint8_t _Llen_2, int32_t _Lval_3);
#define _NCp1_Pgrow_2(cap, c) cap = Fpow2gteq((c) + 8)
#define _NCp1_Prealloc_3(r, c, oldc) r = realloc(r, sizeof(r[0]) * (c)); memset(r + (oldc), 0, sizeof(r[0]) * ((c) - (oldc)))
void _NCp1_NAt_Pput_to_header_1(_NCp1_NAt _Lat_0);
void _NCp1_NInclude_Pwr_2(_NCp1_NInclude _Li_0, union _NCp1_NWtr* _Lw_1);
void _NCp1_NDeclVarData_Pwr_3(struct _NCp1_NDeclVarData* _Lvd_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2);
void _NCp1_NCvarFlags_Pwr_2(_NCp1_NCvarFlags _Lf_0, union _NCp1_NWtr* _Lw_1);
void _NCp1_NExprI_Pwr_3(_NCp1_NExprI _Le_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2);
void _NCp1_NCvar_Pwr_2(_NCp1_NCvar _Lg_0, union _NCp1_NWtr* _Lw_1);
void _NCp1_NEnumFlags_Pwr_2(_NCp1_NEnumFlags _Le_0, union _NCp1_NWtr* _Lw_1);
void _NCp1_NStructFlags_Pwr_2(_NCp1_NStructFlags _Lf_0, union _NCp1_NWtr* _Lw_1);
void _NCp1_NFvarData_Pwr_3(struct _NCp1_NFvarData* _Lf_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2);
void _NCp1_NFarg_Pwr_3(struct _NCp1_NFarg* _Lf_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2);
void _NCp1_NFuncFlags_Pwr_2(_NCp1_NFuncFlags _Le_0, union _NCp1_NWtr* _Lw_1);
void _NCp1_NFunc_Pwr_2(_NCp1_NFunc _Lf_0, union _NCp1_NWtr* _Lw_1);
void _NCp1_NDeclFunc_Plvars_wr_3(struct _NCp1_NDeclFunc* _Lf_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2);
void _NCp1_NStmtSpace_Pwr_3(struct _NCp1_NStmtSpace* _Lspace_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2);
void _NCp1_NWtr_Pn4_2(union _NCp1_NWtr* _Lw_0, uint32_t _Ln_1);
#define _NCp1_Pquick_alloc_one_1(r) r = qalloc(sizeof(r[0]))
#define _NCp1_Pquick_alloc_plus_2(r, plus) r = qalloc(sizeof(r[0]) + plus)
void _NCp1_NDeclVarData_Pcopy_from_2(struct _NCp1_NDeclVarData* _Lvd_0, struct _NCp1_NDeclVarData* _Lsrc_1);
void _NCp1_NFarg_Pcopy_from_2(struct _NCp1_NFarg* _Lf_0, struct _NCp1_NFarg* _Lsrc_1);
uint8_t _NCp1_NId_Plen_1(_NCp1_NId _Lid_0);
char* _NCp1_NId_Pstr_1(_NCp1_NId _Lid_0);
struct _NCp1_NDeclFunc* _NCp1_NFunc_Pptr_1(_NCp1_NFunc _Lf_0);
_NCp1_NLvar _NCp1_NStmtSpace_Plvar_new_4(struct _NCp1_NStmtSpace* _Lspace_0, _NCp1_NId _Lname_1, int32_t _Lrow_2, int32_t _Lcol_3);
struct _NCp1_NLvarData* _NCp1_NLvar_Pptr_1(_NCp1_NLvar _Ll_0);
void _NCp1_NTypeInfo_Pinit_1(struct _NCp1_NTypeInfo* _Lti_0);
_NCp1_NExprI _NCp1_Pexpr_push_2(struct _NCp1_NExpr* _Le_0, _NCp1_NExprType _Ltype_1);
struct _NCp1_NExpr* _NCp1_NExprI_Pptr_1(_NCp1_NExprI _Le_0);
void _NCp1_Pstmt_push_6(struct _NCp1_NStmt* _Ls_0, int32_t _Lbegin_row_1, int32_t _Lbegin_col_2, int32_t _Lend_row_3, int32_t _Lend_col_4, _NCp1_NStmtType _Ltype_5);
_NCp1_NId _NCp1_NLvar_Pname_1(_NCp1_NLvar _Ll_0);
char* _NCp1_NToken_Pcp1_name_1(_NCp1_NToken _Le_0) {
switch(_Le_0) {
case _NCp1_NToken_Cnil: return "nil";
case _NCp1_NToken_Cplus: return "plus";
case _NCp1_NToken_Cminus: return "minus";
case _NCp1_NToken_Cspace: return "space";
case _NCp1_NToken_Cid_lparen: return "id-lparen";
case _NCp1_NToken_Cid_upper: return "id-upper";
case _NCp1_NToken_Cid_dot_upper: return "id-dot-upper";
case _NCp1_NToken_Cid_hash: return "id-hash";
case _NCp1_NToken_Cid: return "id";
case _NCp1_NToken_Cspace_at_real_name_str: return "space-at-real-name-str";
case _NCp1_NToken_Cspace_at_real_name: return "space-at-real-name";
case _NCp1_NToken_Cspace_at_no_decl: return "space-at-no-decl";
case _NCp1_NToken_Cspace_equal_space: return "space-equal-space";
case _NCp1_NToken_Cinclude: return "include";
case _NCp1_NToken_Cspace_rcbrace: return "space-rcbrace";
case _NCp1_NToken_Cgrave: return "grave";
case _NCp1_NToken_Cid_bslash: return "id-bslash";
case _NCp1_NToken_Cusing: return "using";
case _NCp1_NToken_Crparen: return "rparen";
case _NCp1_NToken_Clparen: return "lparen";
case _NCp1_NToken_Clcbrace_space: return "lcbrace-space";
case _NCp1_NToken_Crcbrace: return "rcbrace";
case _NCp1_NToken_Cscolon: return "scolon";
case _NCp1_NToken_Cend: return "end";
case _NCp1_NToken_Clparen_space: return "lparen-space";
case _NCp1_NToken_Cspace_rparen: return "space-rparen";
case _NCp1_NToken_Ccomma_space_rparen: return "comma-space-rparen";
case _NCp1_NToken_Clcbrace: return "lcbrace";
case _NCp1_NToken_Clbracket: return "lbracket";
case _NCp1_NToken_Clbracket_space: return "lbracket-space";
case _NCp1_NToken_Crbracket: return "rbracket";
case _NCp1_NToken_Cspace_rbracket: return "space-rbracket";
case _NCp1_NToken_Ccomma_space_rbracket: return "comma-space-rbracket";
case _NCp1_NToken_Ccolon: return "colon";
case _NCp1_NToken_Cthis: return "this";
case _NCp1_NToken_Ccomma_space: return "comma-space";
case _NCp1_NToken_Cspace_at_main: return "space-at-main";
case _NCp1_NToken_Cspace_at_case: return "space-at-case";
case _NCp1_NToken_Cdot: return "dot";
case _NCp1_NToken_Cspace_at_process: return "space-at-process";
case _NCp1_NToken_Cspace_at_inline: return "space-at-inline";
case _NCp1_NToken_Cspace_at_cp1_name: return "space-at-cp1-name";
case _NCp1_NToken_Cspace_at_decl: return "space-at-decl";
case _NCp1_NToken_Cstring: return "string";
case _NCp1_NToken_Cspace_at_var_args: return "space-at-var-args";
case _NCp1_NToken_Cspace_at_no_body: return "space-at-no-body";
case _NCp1_NToken_Cref: return "ref";
case _NCp1_NToken_Cbool: return "bool";
case _NCp1_NToken_Cchar: return "char";
case _NCp1_NToken_Cintc: return "intc";
case _NCp1_NToken_Ci8: return "i8";
case _NCp1_NToken_Cu8: return "u8";
case _NCp1_NToken_Ci16: return "i16";
case _NCp1_NToken_Cu16: return "u16";
case _NCp1_NToken_Ci32: return "i32";
case _NCp1_NToken_Cu32: return "u32";
case _NCp1_NToken_Ci64: return "i64";
case _NCp1_NToken_Cu64: return "u64";
case _NCp1_NToken_Cisz: return "isz";
case _NCp1_NToken_Cusz: return "usz";
case _NCp1_NToken_Cf32: return "f32";
case _NCp1_NToken_Cf64: return "f64";
case _NCp1_NToken_Campersand: return "ampersand";
case _NCp1_NToken_Cnum_dec: return "num-dec";
case _NCp1_NToken_Cnum_hex: return "num-hex";
case _NCp1_NToken_Cnum_oct: return "num-oct";
case _NCp1_NToken_Cchar1: return "char1";
case _NCp1_NToken_Cchar2: return "char2";
case _NCp1_NToken_Ctrue: return "true";
case _NCp1_NToken_Cfalse: return "false";
case _NCp1_NToken_Cnull: return "null";
case _NCp1_NToken_Clparen_amp_amp_comma_space: return "lparen-amp-amp-comma-space";
case _NCp1_NToken_Clparen_pipe_pipe_comma_space: return "lparen-pipe-pipe-comma-space";
case _NCp1_NToken_Cspace_plus_space: return "space-plus-space";
case _NCp1_NToken_Cspace_minus_space: return "space-minus-space";
case _NCp1_NToken_Cspace_mul_space: return "space-mul-space";
case _NCp1_NToken_Cspace_div_space: return "space-div-space";
case _NCp1_NToken_Cspace_langle_langle_space: return "space-langle-langle-space";
case _NCp1_NToken_Cspace_rangle_rangle_space: return "space-rangle-rangle-space";
case _NCp1_NToken_Cspace_amp_space: return "space-amp-space";
case _NCp1_NToken_Cspace_pipe_space: return "space-pipe-space";
case _NCp1_NToken_Cspace_xor_space: return "space-xor-space";
case _NCp1_NToken_Cspace_equal_equal_space: return "space-equal-equal-space";
case _NCp1_NToken_Cspace_expoint_equal_space: return "space-expoint-equal-space";
case _NCp1_NToken_Cspace_langle_space: return "space-langle-space";
case _NCp1_NToken_Cspace_langle_equal_space: return "space-langle-equal-space";
case _NCp1_NToken_Cspace_rangle_space: return "space-rangle-space";
case _NCp1_NToken_Cspace_rangle_equal_space: return "space-rangle-equal-space";
case _NCp1_NToken_Chash: return "hash";
case _NCp1_NToken_Cspace_plus_equal_space: return "space-plus-equal-space";
case _NCp1_NToken_Cspace_minus_equal_space: return "space-minus-equal-space";
case _NCp1_NToken_Cspace_mul_equal_space: return "space-mul-equal-space";
case _NCp1_NToken_Cspace_div_equal_space: return "space-div-equal-space";
case _NCp1_NToken_Cspace_lshift_equal_space: return "space-lshift-equal-space";
case _NCp1_NToken_Cspace_rshift_equal_space: return "space-rshift-equal-space";
case _NCp1_NToken_Cspace_and_equal_space: return "space-and-equal-space";
case _NCp1_NToken_Cspace_or_equal_space: return "space-or-equal-space";
case _NCp1_NToken_Cspace_xor_equal_space: return "space-xor-equal-space";
case _NCp1_NToken_Cexpoint: return "expoint";
case _NCp1_NToken_Cloop: return "loop";
case _NCp1_NToken_Clcbrace_lparen: return "lcbrace-lparen";
case _NCp1_NToken_Cwhile: return "while";
case _NCp1_NToken_Cif: return "if";
case _NCp1_NToken_Cspace_elif: return "space-elif";
case _NCp1_NToken_Cspace_else: return "space-else";
case _NCp1_NToken_Cswitch: return "switch";
case _NCp1_NToken_Cspace_at_fall_through: return "space-at-fall-through";
case _NCp1_NToken_Ccase: return "case";
case _NCp1_NToken_Cdefault: return "default";
case _NCp1_NToken_Ccontinue: return "continue";
case _NCp1_NToken_Cbreak: return "break";
case _NCp1_NToken_Creturn: return "return";
case _NCp1_NToken_Cvar: return "var";
case _NCp1_NToken_Cspace_at_extern: return "space-at-extern";
case _NCp1_NToken_Cspace_at_union: return "space-at-union";
}
return "(ERROR)";
}
struct _NCp1_NAtData* _NCp1_NAt_Pptr_1(_NCp1_NAt _Li_0);
_NCp1_NAt _NCp1_Pat_create_basic_1(_NCp1_NBasicTypeId _Lbasic_0);
_NCp1_NAt _NCp1_Pat_create_3(_NCp1_NAt _Lparent_0, _NCp1_NNameType _Ltype_1, _NCp1_NId _Lname_2);
void _NCp1_Ptype_info_arr_1(_NCp1_NExprI _Lexpr_0);
void _NCp1_NTypeInfo_Pfinalize_1(struct _NCp1_NTypeInfo* _Lti_0);
struct _NCp1_NCvarData* _NCp1_NCvar_Pptr_1(_NCp1_NCvar _Lc_0);
struct _NCp1_NStmtSpace* _NCp1_Pstmt_space_begin_1(bool _Lattach_0);
void _NCp1_NVarFlags_Pwr_2(_NCp1_NVarFlags _Lf_0, union _NCp1_NWtr* _Lw_1);
void _NCp1_NTypeInfo_Pwr_2(struct _NCp1_NTypeInfo* _Lti_0, union _NCp1_NWtr* _Lw_1);
void _NCp1_NExprType_Pwr_2(_NCp1_NExprType _Le_0, union _NCp1_NWtr* _Lw_1);
void _NCp1_NExprI_Pwr_math_3(struct _NCp1_NExpr* _Lexpr_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2);
void _NCp1_NExprI_Pwr_bools_3(struct _NCp1_NExpr* _Lexpr_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2);
void _NCp1_NExprI_Pwr_str_3(struct _NCp1_NExpr* _Lexpr_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2);
void _NCp1_NExprI_Pwr_cvar_3(struct _NCp1_NExpr* _Lexpr_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2);
void _NCp1_NExprI_Pwr_unary_3(struct _NCp1_NExpr* _Lexpr_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2);
void _NCp1_NExprI_Pwr_ref_3(struct _NCp1_NExpr* _Lexpr_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2);
void _NCp1_NExprI_Pwr_cast_fast_3(struct _NCp1_NExpr* _Lexpr_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2);
void _NCp1_NExprI_Pwr_index_3(struct _NCp1_NExpr* _Lexpr_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2);
void _NCp1_NExprI_Pwr_compare_3(struct _NCp1_NExpr* _Lexpr_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2);
void _NCp1_NExprI_Pwr_bool_3(struct _NCp1_NExpr* _Lexpr_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2);
void _NCp1_NExprI_Pwr_char_3(struct _NCp1_NExpr* _Lexpr_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2);
void _NCp1_NExprI_Pwr_method_3(struct _NCp1_NExpr* _Lexpr_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2);
void _NCp1_NExprI_Pwr_func_3(struct _NCp1_NExpr* _Lexpr_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2);
void _NCp1_NExprI_Pwr_null_3(struct _NCp1_NExpr* _Lexpr_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2);
void _NCp1_NExprI_Pwr_i32_3(struct _NCp1_NExpr* _Lexpr_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2);
void _NCp1_NExprI_Pwr_size_of_type_3(struct _NCp1_NExpr* _Lexpr_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2);
void _NCp1_NExprI_Pwr_assign_3(struct _NCp1_NExpr* _Lexpr_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2);
void _NCp1_NExprI_Pwr_fvar_3(struct _NCp1_NExpr* _Lexpr_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2);
void _NCp1_NExprI_Pwr_gvar_3(struct _NCp1_NExpr* _Lexpr_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2);
void _NCp1_NExprI_Pwr_lvar_3(struct _NCp1_NExpr* _Lexpr_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2);
char* _NCp1_NExprType_Pcp1_name_1(_NCp1_NExprType _Le_0) {
switch(_Le_0) {
case _NCp1_NExprType_Cnil: return "nil";
case _NCp1_NExprType_Ccall_method: return "call-method";
case _NCp1_NExprType_Clvar: return "lvar";
case _NCp1_NExprType_Cgvar: return "gvar";
case _NCp1_NExprType_Cmath: return "math";
case _NCp1_NExprType_Cassign: return "assign";
case _NCp1_NExprType_Cbools: return "bools";
case _NCp1_NExprType_Cfunc: return "func";
case _NCp1_NExprType_Cmethod: return "method";
case _NCp1_NExprType_Cfvar: return "fvar";
case _NCp1_NExprType_Ci32: return "i32";
case _NCp1_NExprType_Ccvar: return "cvar";
case _NCp1_NExprType_Cstr: return "str";
case _NCp1_NExprType_Cindex: return "index";
case _NCp1_NExprType_Cunary: return "unary";
case _NCp1_NExprType_Ccompare: return "compare";
case _NCp1_NExprType_Cbool: return "bool";
case _NCp1_NExprType_Cnull: return "null";
case _NCp1_NExprType_Ccast_fast: return "cast-fast";
case _NCp1_NExprType_Cref: return "ref";
case _NCp1_NExprType_Cchar: return "char";
case _NCp1_NExprType_Csize_of_type: return "size-of-type";
}
return "(ERROR)";
}
void _NCp1_NLvarFlags_Pwr_2(_NCp1_NLvarFlags _Lf_0, union _NCp1_NWtr* _Lw_1);
void _NCp1_NLvar_Pwr_2(_NCp1_NLvar _Ll_0, union _NCp1_NWtr* _Lw_1);
void _NCp1_NStmtType_Pwr_2(_NCp1_NStmtType _Ls_0, union _NCp1_NWtr* _Lw_1);
void _NCp1_NStmtSpace_Pwr_break_3(struct _NCp1_NStmt* _Lstmt_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2);
void _NCp1_NStmtSpace_Pwr_switch_3(struct _NCp1_NStmt* _Lstmt_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2);
void _NCp1_NStmtSpace_Pwr_case_3(struct _NCp1_NStmt* _Lstmt_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2);
void _NCp1_NStmtSpace_Pwr_case_end_3(struct _NCp1_NStmt* _Lstmt_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2);
void _NCp1_NStmtSpace_Pwr_default_3(struct _NCp1_NStmt* _Lstmt_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2);
void _NCp1_NStmtSpace_Pwr_default_end_3(struct _NCp1_NStmt* _Lstmt_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2);
void _NCp1_NStmtSpace_Pwr_switch_end_3(struct _NCp1_NStmt* _Lstmt_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2);
void _NCp1_NStmtSpace_Pwr_if_3(struct _NCp1_NStmt* _Lstmt_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2);
void _NCp1_NStmtSpace_Pwr_if_elif_3(struct _NCp1_NStmt* _Lstmt_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2);
void _NCp1_NStmtSpace_Pwr_if_else_3(struct _NCp1_NStmt* _Lstmt_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2);
void _NCp1_NStmtSpace_Pwr_if_end_3(struct _NCp1_NStmt* _Lstmt_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2);
void _NCp1_NStmtSpace_Pwr_do_3(struct _NCp1_NStmt* _Lstmt_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2);
void _NCp1_NStmtSpace_Pwr_do_end_3(struct _NCp1_NStmt* _Lstmt_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2);
void _NCp1_NStmtSpace_Pwr_while_3(struct _NCp1_NStmt* _Lstmt_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2);
void _NCp1_NStmtSpace_Pwr_while_end_3(struct _NCp1_NStmt* _Lstmt_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2);
void _NCp1_NStmtSpace_Pwr_continue_3(struct _NCp1_NStmt* _Lstmt_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2);
void _NCp1_NStmtSpace_Pwr_return_3(struct _NCp1_NStmt* _Lstmt_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2);
void _NCp1_NStmtSpace_Pwr_space_3(struct _NCp1_NStmt* _Lstmt_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2);
void _NCp1_NStmtSpace_Pwr_expr_3(struct _NCp1_NStmt* _Lstmt_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2);
char* _NCp1_NStmtType_Pcp1_name_1(_NCp1_NStmtType _Le_0) {
switch(_Le_0) {
case _NCp1_NStmtType_Cspace: return "space";
case _NCp1_NStmtType_Cif: return "if";
case _NCp1_NStmtType_Cif_elif: return "if-elif";
case _NCp1_NStmtType_Cif_else: return "if-else";
case _NCp1_NStmtType_Cif_end: return "if-end";
case _NCp1_NStmtType_Cdo: return "do";
case _NCp1_NStmtType_Cdo_end: return "do-end";
case _NCp1_NStmtType_Cwhile: return "while";
case _NCp1_NStmtType_Cwhile_end: return "while-end";
case _NCp1_NStmtType_Cexpr: return "expr";
case _NCp1_NStmtType_Creturn: return "return";
case _NCp1_NStmtType_Ccontinue: return "continue";
case _NCp1_NStmtType_Cbreak: return "break";
case _NCp1_NStmtType_Cswitch: return "switch";
case _NCp1_NStmtType_Ccase: return "case";
case _NCp1_NStmtType_Cdefault: return "default";
case _NCp1_NStmtType_Ccase_end: return "case-end";
case _NCp1_NStmtType_Cdefault_end: return "default-end";
case _NCp1_NStmtType_Cswitch_end: return "switch-end";
case _NCp1_NStmtType_Cnil: return "nil";
}
return "(ERROR)";
}
void _NCp1_NTypeInfo_Pcopy_from_2(struct _NCp1_NTypeInfo* _Lti_0, struct _NCp1_NTypeInfo* _Lti2_1);
#define _NCp1_Pquick_alloc_arr_2(r, c) r = qalloc(sizeof(r[0]) * (c))
void _NCp1_Pfunc_stmt_add_1(struct _NCp1_NStmt* _Ls_0);
int32_t _NCp1_NAtMap_Pget_or_insert_5(struct _NCp1_NAtMap* _Lm_0, _NCp1_NAt _Lparent_1, _NCp1_NNameType _Ltype_2, _NCp1_NId _Lname_3, int32_t _Lval_4);
void _NCp1_NWtr_Pb_2(union _NCp1_NWtr* _Lw_0, bool _Lval_1);
void _NCp1_NMath_Pwr_2(_NCp1_NMath _Le_0, union _NCp1_NWtr* _Lw_1);
void _NCp1_NBools_Pwr_2(_NCp1_NBools _Le_0, union _NCp1_NWtr* _Lw_1);
void _NCp1_NUnary_Pwr_2(_NCp1_NUnary _Lu_0, union _NCp1_NWtr* _Lw_1);
void _NCp1_NCompare_Pwr_2(_NCp1_NCompare _Le_0, union _NCp1_NWtr* _Lw_1);
void _NCp1_NAssign_Pwr_2(_NCp1_NAssign _Ls_0, union _NCp1_NWtr* _Lw_1);
int main(int _Larg_c_0, char** _Larg_v_1) {
_NStdc_NFd _Lin_fd_2;
char* _Llock_path_3;
size_t _Lin_size_4;
uint8_t* _Lin_data_5;
union _NCp1_NRdr _Lr_end_23;
struct _NCp1_NParser* _Lpsr_24;
struct _NCp1_NLexer _Llex_25;
int32_t _Lnext_row_26;
int32_t _Lnext_col_27;
struct _NCp1_NTokenData _Ltok_28;
union _NCp1_NWtr _Lw_begin_36;
union _NCp1_NWtr _Lw_37;
int32_t _Lid_bit8_c_39;
_NCp1_NAt _Lat_bit8_c_41;
char* _Lout_path_44;
size_t _Lout_path_len_45;
_NStdc_NFd _Lout_fd_46;
char _Lfinal_path_53[512];
if(false) {
_NCp1_Pexport_0();
}
_NCp1_NMap_Pinit_1(&_Gid_map);
_NCp1_NMap_Pinit_1(&_Ginclude_map);
_NCp1_NAtMap_Pinit_1(&_Gat_map);
_NCp1_Pquick_alloc_init_0();
_Gfunc_main = _NCp1_NFunc_Cnil;
_Gdecl_include = _NCp1_NInclude_Cnil;
if(_Larg_c_0 != 3) {
fprintf(stdout, "Usage: %s [file.cgl] [output.cgl-b]\n", _Larg_v_1[0]);
return 0;
}
input_path = _Larg_v_1[1];
if(!(_NStdc_NFd_Popen_3(&_Lin_fd_2, input_path, O_RDONLY))) {
fprintf(stdout, "Cannot open file for reading: %s\n", input_path);
exit(_NStdc_NExit_Cfailure);
}
_Llock_path_3 = _Larg_v_1[2];
_Lin_size_4 = lseek(_Lin_fd_2, 0, SEEK_END);
_Lin_data_5 = malloc(_Lin_size_4 + 2);
lseek(_Lin_fd_2, 0, SEEK_SET);
read(_Lin_fd_2, _Lin_data_5, _Lin_size_4);
_Lin_data_5[_Lin_size_4] = 0;
_Lin_data_5[(_Lin_size_4 + 1)] = 0;
_NStdc_NFd_Pclose_1(_Lin_fd_2);
if(((_Lin_data_5[(_Lin_size_4 - 2)] == '\r') && (_Lin_data_5[(_Lin_size_4 - 1)] == '\n'))) {
fprintf(stdout, "Error reading file '%s' because it uses Windows-style line endings\n", input_path);
fprintf(stdout, "Please convert the line endings to Unix-style line endings\n");
exit(_NStdc_NExit_Cfailure);
}
if(_Lin_data_5[(_Lin_size_4 - 1)] != '\n') {
fprintf(stdout, "Error reading file '%s' because it doesn:T end with a new line\n", input_path);
exit(_NStdc_NExit_Cfailure);
}
if(true) {
bool _Lpreprocess_6;
union _NCp1_NRdr _Lr_end_7;
union _NCp1_NRdr _Lr_8;
void* _Lnew_data_9;
union _NCp1_NWtr _Lw_10;
union _NCp1_NWtr _Lw_begin_22;
_Lpreprocess_6 = false;
_Lr_end_7._Freff = _Lin_data_5;
_Lr_end_7._Fpos += _Lin_size_4;
_Lr_8._Freff = _Lin_data_5;
_Lnew_data_9 = malloc(_Lin_size_4 + 1);
_Lw_10._Freff = _Lnew_data_9;
while(_Lr_8._Fpos < _Lr_end_7._Fpos) {
if(_Lr_8._Fp1[0] == '/') {
if(_Lr_8._Fp1[1] == '/') {
if(_Lr_8._Freff == _Lin_data_5) {
} else if(((_Lr_8._Fp1[-1] == ' ') || (_Lr_8._Fp1[-1] == '\t') || (_Lr_8._Fp1[-1] == '\n'))) {
} else {
int32_t _Lrow_11;
int32_t _Lcol_12;
_NCp1_Pget_row_col_4(&_Lrow_11, &_Lcol_12, _Lr_8._Freff, _Lin_data_5);
fprintf(stdout, "%s:%u:%u: There must be a space or tab before the // comment\n", input_path, _Lrow_11, _Lcol_12);
exit(_NStdc_NExit_Cfailure);
}
_Lr_8._Fpos += 2;
while(1) {
if(_Lr_8._Fp1[0] == '\n') {
goto break_1;
}
_Lr_8._Fpos++;
continue_1:;
}
break_1:;
goto continue_0;
}
} else if(((_Lr_8._Fp1[0] == '#') && (_Lr_8._Fp1[1] == 'i') && (_Lr_8._Fp1[2] == 'n') && (_Lr_8._Fp1[3] == 'c') && (_Lr_8._Fp1[4] == 'l') && (_Lr_8._Fp1[5] == 'u') && (_Lr_8._Fp1[6] == 'd') && (_Lr_8._Fp1[7] == 'e') && (_Lr_8._Fp1[8] == ' ') && (_Lr_8._Fp1[9] == '<'))) {
_Lr_8._Fpos += 10;
while(1) {
if(_Lr_8._Fp1[0] == '\n') {
goto break_2;
}
_Lr_8._Fpos++;
continue_2:;
}
break_2:;
goto continue_0;
} else if(((_Lr_8._Fp1[0] == '#') && (_Lr_8._Fp1[1] == 'i') && (_Lr_8._Fp1[2] == 'm') && (_Lr_8._Fp1[3] == 'p') && (_Lr_8._Fp1[4] == 'o') && (_Lr_8._Fp1[5] == 'r') && (_Lr_8._Fp1[6] == 't') && (_Lr_8._Fp1[7] == ' ') && (_Lr_8._Fp1[8] == '\"'))) {
_Lr_8._Fpos += 9;
while(1) {
if(_Lr_8._Fp1[0] == '\n') {
goto break_3;
}
_Lr_8._Fpos++;
continue_3:;
}
break_3:;
goto continue_0;
} else if(_Lr_8._Fp1[0] == '\'') {
if(_Lr_8._Fp1[1] == '\'') {
if(_Lr_8._Fp1[2] == '\\') {
_Lw_10._Fp1[0] = '\'';
_Lw_10._Fp1[1] = '\'';
_Lw_10._Fp1[2] = '\\';
_Lw_10._Fp1[3] = _Lr_8._Fp1[3];
_Lw_10._Fpos += 4;
_Lr_8._Fpos += 4;
goto continue_0;
} else {
_Lw_10._Fp1[0] = '\'';
_Lw_10._Fp1[1] = '\'';
_Lw_10._Fp1[2] = _Lr_8._Fp1[2];
_Lw_10._Fpos += 3;
_Lr_8._Fpos += 3;
goto continue_0;
}
} else if((((_Lr_8._Fp1[2] == ' ') || (_Lr_8._Fp1[2] == '\t')) && ((_Lr_8._Fp1[1] == '-') || (_Lr_8._Fp1[1] == '=')))) {
_Lw_10._Fp1[0] = '\'';
_Lw_10._Fp1[1] = _Lr_8._Fp1[1];
_Lw_10._Fp1[2] = _Lr_8._Fp1[2];
_Lw_10._Fpos += 3;
_Lr_8._Fpos += 3;
while(1) {
uint8_t _Lc_13;
_Lc_13 = _Lr_8._Fp1[0];
_Lw_10._Fp1[0] = _Lc_13;
_Lw_10._Fpos++;
_Lr_8._Fpos++;
if(_Lc_13 == '\n') {
goto break_4;
}
if(_Lr_8._Fpos >= _Lr_end_7._Fpos) {
int32_t _Lrow_14;
int32_t _Lcol_15;
_NCp1_Pget_row_col_4(&_Lrow_14, &_Lcol_15, _Lr_8._Freff, _Lin_data_5);
fprintf(stdout, "%s:%u:%u: String did not end with a new line\n", input_path, _Lrow_14, _Lcol_15);
exit(_NStdc_NExit_Cfailure);
}
continue_4:;
}
break_4:;
goto continue_0;
#if 0
hello
hello
hello
hello
hello
hello
hello
hello
hello
#endif
} else if(_Lr_8._Fp1[1] == '\"') {
_NCp1_Pparse_string_4(&_Lr_8, &_Lw_10, '\"', _Lin_data_5);
goto continue_0;
} else if(_Lr_8._Fp1[1] == '|') {
_NCp1_Pparse_string_4(&_Lr_8, &_Lw_10, '|', _Lin_data_5);
goto continue_0;
} else if(_Lr_8._Fp1[1] == ';') {
_NCp1_Pparse_string_4(&_Lr_8, &_Lw_10, ';', _Lin_data_5);
goto continue_0;
} else if(_Lr_8._Fp1[1] == '_') {
_NCp1_Pparse_string_4(&_Lr_8, &_Lw_10, '_', _Lin_data_5);
goto continue_0;
} else if(_Lr_8._Fp1[1] == '+') {
_NCp1_Pparse_string_4(&_Lr_8, &_Lw_10, '+', _Lin_data_5);
goto continue_0;
} else if(_Lr_8._Fp1[1] == '<') {
_NCp1_Pparse_string_4(&_Lr_8, &_Lw_10, '>', _Lin_data_5);
goto continue_0;
} else if(_Lr_8._Fp1[1] == '[') {
_NCp1_Pparse_string_4(&_Lr_8, &_Lw_10, ']', _Lin_data_5);
goto continue_0;
} else if(_Lr_8._Fp1[1] == '{') {
_NCp1_Pparse_string_4(&_Lr_8, &_Lw_10, '}', _Lin_data_5);
goto continue_0;
} else if(_Lr_8._Fp1[1] == '(') {
_NCp1_Pparse_string_4(&_Lr_8, &_Lw_10, ')', _Lin_data_5);
goto continue_0;
}
} else if(_Lr_8._Fp1[0] == '\"') {
_Lw_10._Fp1[0] = '\"';
_Lw_10._Fpos++;
_Lr_8._Fpos++;
while(1) {
if(_Lr_8._Fp1[0] == '\n') {
int32_t _Lrow_16;
int32_t _Lcol_17;
_NCp1_Pget_row_col_4(&_Lrow_16, &_Lcol_17, _Lr_8._Freff, _Lin_data_5);
fprintf(stdout, "%s:%u:%u: Unterminated string\n", input_path, _Lrow_16, _Lcol_17);
exit(_NStdc_NExit_Cfailure);
} else if(_Lr_8._Fp1[0] == '\"') {
_Lw_10._Fp1[0] = '\"';
_Lw_10._Fpos++;
_Lr_8._Fpos++;
goto break_5;
} else if(_Lr_8._Fp1[0] == '\\') {
switch(_Lr_8._Fp1[1]) {
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
int32_t _Lrow_18;
int32_t _Lcol_19;
_NCp1_Pget_row_col_4(&_Lrow_18, &_Lcol_19, _Lr_8._Freff, _Lin_data_5);
fprintf(stdout, "%s:%u:%u: Encountered invalid escape sequence in the string: '\\%c'\n", input_path, _Lrow_18, _Lcol_19, _Lr_8._Fp1[1]);
exit(_NStdc_NExit_Cfailure);
break;
}
_Lw_10._Fp1[0] = '\\';
_Lw_10._Fp1[1] = _Lr_8._Fp1[1];
_Lw_10._Fpos += 2;
_Lr_8._Fpos += 2;
} else {
_Lw_10._Fp1[0] = _Lr_8._Fp1[0];
_Lw_10._Fpos++;
_Lr_8._Fpos++;
}
if(_Lr_8._Fpos >= _Lr_end_7._Fpos) {
int32_t _Lrow_20;
int32_t _Lcol_21;
_NCp1_Pget_row_col_4(&_Lrow_20, &_Lcol_21, _Lr_8._Freff, _Lin_data_5);
fprintf(stdout, "%s:%u:%u: Unterminated string\n", input_path, _Lrow_20, _Lcol_21);
exit(_NStdc_NExit_Cfailure);
}
continue_5:;
}
break_5:;
goto continue_0;
}
_Lw_10._Fp1[0] = _Lr_8._Fp1[0];
_Lw_10._Fpos++;
_Lr_8._Fpos++;
continue_0:;
}
break_0:;
_Lw_10._Fp1[0] = '\0';
free(_Lin_data_5);
_Lin_data_5 = _Lnew_data_9;
_Lw_begin_22._Freff = _Lnew_data_9;
_Lin_size_4 = (_Lw_10._Fpos - _Lw_begin_22._Fpos);
}
_Lr_end_23._Freff = _Lin_data_5;
_Lr_end_23._Fpos += _Lin_size_4;
_NCp1_Pparse_str_init_1(_Lin_size_4);
_Gid_cap = 64;
_NCp1_Pmalloc_arr_2(_Gid_str_v, _Gid_cap);
_NCp1_Pmalloc_arr_2(_Gid_len_v, _Gid_cap);
_Ginclude_cap = 64;
_NCp1_Pmalloc_arr_2(_Ginclude_str_v, _Ginclude_cap);
_NCp1_Pmalloc_arr_2(_Ginclude_len_v, _Ginclude_cap);
_Gat_cap = (_NCp1_NAt)(64);
_NCp1_Pmalloc_arr_2(_Gat_v, _Gat_cap);
_Gat_c = (_NCp1_NAt)(2);
_Gat_v[0]._Ftype = _NCp1_NNameType_Cbasic;
_Gat_v[0]._Fparent = _NCp1_NAt_Cnil;
_Gat_v[0]._Fname._Fbasic = _NCp1_NBasicTypeId_Croot;
_Gat_v[1]._Ftype = _NCp1_NNameType_Cbasic;
_Gat_v[1]._Fparent = _NCp1_NAt_Cnil;
_Gat_v[1]._Fname._Fbasic = _NCp1_NBasicTypeId_Crelative;
_Gfunc_cap = (_NCp1_NFunc)(32);
_NCp1_Pmalloc_arr_2(_Gfunc_v, _Gfunc_cap);
_Gstruct_cap = (_NCp1_NStruct)(32);
_NCp1_Pmalloc_arr_2(_Gstruct_v, _Gstruct_cap);
_Gdecl_fvar_cap = 32;
_NCp1_Pmalloc_arr_2(_Gdecl_fvar_v, _Gdecl_fvar_cap);
_Lpsr_24 = _NCp1_NParser_Palloc_0();
_NCp1_NLexer_Pinit_3(&_Llex_25, _Lin_data_5, _Lin_size_4);
_Lnext_row_26 = 1;
_Lnext_col_27 = 1;
_Grow = 1;
_Gcol = 1;
while(1) {
_NCp1_NToken _Lt_29;
uint8_t* _Lpos_35;
_Ltok_28._Frow = _Lnext_row_26;
_Ltok_28._Fcol = _Lnext_col_27;
_Lt_29 = cp1_lexer_scan(&_Llex_25);
if(true) {
uint8_t* _Lpos_30;
_Lpos_30 = _Llex_25._Fstart;
while(_Lpos_30 < _Lr_end_23._Fp1) {
if(((_Lpos_30[0] == ' ') || (_Lpos_30[0] == '\t'))) {
_Ltok_28._Fcol++;
} else if(_Lpos_30[0] == '\n') {
_Ltok_28._Frow++;
_Ltok_28._Fcol = 1;
} else {
goto break_7;
}
_Lpos_30++;
continue_7:;
}
break_7:;
}
_Glast_row = _Grow;
_Glast_col = _Gcol;
_Grow = _Ltok_28._Frow;
_Gcol = _Ltok_28._Fcol;
switch(_Lt_29) {
case _NCp1_NToken_Cchar1:;
union _NCp1_NRdr _Lr_31;
_Lr_31._Freff = _Llex_25._Fstart;
_Ltok_28._Fid = _Lr_31._Fp1[2];
_Glast_token = _Lt_29;
cp1Parse(_Lpsr_24, _Lt_29, &_Ltok_28);
break;
case _NCp1_NToken_Cchar2:;
union _NCp1_NRdr _Lr_32;
_Lr_32._Freff = _Llex_25._Fstart;
_Ltok_28._Fid = _NCp1_Pchar_escape_value_1(_Lr_32._Fp1[3]);
_Glast_token = _Lt_29;
cp1Parse(_Lpsr_24, _Lt_29, &_Ltok_28);
break;
case _NCp1_NToken_Cspace_at_real_name_str:;
union _NCp1_NRdr _Lr_start_33;
int32_t _Lstart_34;
_Lr_start_33._Freff = _Llex_25._Fstart;
_Lstart_34 = 11;
while(1) {
_Lstart_34++;
_Lr_start_33._Fpos++;
if(_Lr_start_33._Fp1[0] == '@') {
goto break_8;
}
continue_8:;
}
break_8:;
_Ltok_28._Fid = _NCp1_NLexer_Pget_id_3(&_Llex_25, _Lstart_34, 1);
_Glast_token = _Lt_29;
cp1Parse(_Lpsr_24, _Lt_29, &_Ltok_28);
break;
case _NCp1_NToken_Cnum_dec:;
_Ltok_28._Fid = _NCp1_NLexer_Pget_u32_dec_1(&_Llex_25);
_Glast_token = _Lt_29;
cp1Parse(_Lpsr_24, _Lt_29, &_Ltok_28);
break;
case _NCp1_NToken_Cnum_oct:;
_Ltok_28._Fid = _NCp1_NLexer_Pget_u32_oct_1(&_Llex_25);
_Glast_token = _Lt_29;
cp1Parse(_Lpsr_24, _Lt_29, &_Ltok_28);
break;
case _NCp1_NToken_Cinclude:;
_Ltok_28._Fid = _NCp1_NLexer_Pget_include_1(&_Llex_25);
_Glast_token = _Lt_29;
cp1Parse(_Lpsr_24, _Lt_29, &_Ltok_28);
break;
case _NCp1_NToken_Cid:;
_Ltok_28._Fid = _NCp1_NLexer_Pget_id_3(&_Llex_25, 0, 0);
if(_Llex_25._Fcursor[0] == '(') {
_Lt_29 = _NCp1_NToken_Cid_lparen;
}
_Glast_token = _Lt_29;
cp1Parse(_Lpsr_24, _Lt_29, &_Ltok_28);
break;
case _NCp1_NToken_Cid_hash:;
_Ltok_28._Fid = _NCp1_NLexer_Pget_id_3(&_Llex_25, 1, 0);
_Glast_token = _Lt_29;
cp1Parse(_Lpsr_24, _Lt_29, &_Ltok_28);
break;
case _NCp1_NToken_Cid_dot_upper:;
_Ltok_28._Fid = _NCp1_NLexer_Pget_id_3(&_Llex_25, 1, 0);
_Glast_token = _Lt_29;
cp1Parse(_Lpsr_24, _Lt_29, &_Ltok_28);
break;
case _NCp1_NToken_Cid_upper:;
_Ltok_28._Fid = _NCp1_NLexer_Pget_id_3(&_Llex_25, 0, 0);
_Glast_token = _Lt_29;
cp1Parse(_Lpsr_24, _Lt_29, &_Ltok_28);
break;
case _NCp1_NToken_Clcbrace:;
if(_Llex_25._Fcursor[0] == '(') {
_Lt_29 = _NCp1_NToken_Clcbrace_lparen;
}
_Glast_token = _Lt_29;
cp1Parse(_Lpsr_24, _Lt_29, &_Ltok_28);
break;
default:;
_Glast_token = _Lt_29;
cp1Parse(_Lpsr_24, _Lt_29, &_Ltok_28);
break;
}
if(_Lt_29 == _NCp1_NToken_Cend) {
goto break_6;
}
_Lpos_35 = _Llex_25._Fstart;
while(_Lpos_35 < _Llex_25._Fcursor) {
if((_Lpos_35[0] & 128) == 0) {
if(_Lpos_35[0] == '\n') {
_Lnext_row_26++;
_Lnext_col_27 = 1;
} else {
_Lnext_col_27++;
}
}
_Lpos_35++;
continue_9:;
}
break_9:;
continue_6:;
}
break_6:;
_Glast_token = _NCp1_NToken_Cnil;
cp1Parse(_Lpsr_24, _NCp1_NToken_Cnil, &_Ltok_28);
_NCp1_NParser_Pfree_1(_Lpsr_24);
_Lw_begin_36._Freff = qalloc((_Lin_size_4 << 2) + 1024);
_Lw_37._Freff = _Lw_begin_36._Freff;
Fputnum(&_Lw_37, _Gid_c);
int32_t _Li_38;
_Li_38 = 0;
for(int i = _Gid_c; i > 0; ) {
i --;
_NCp1_NWtr_Pn1_2(&_Lw_37, _Gid_len_v[_Li_38]);
_NCp1_NWtr_Pcopy_3(&_Lw_37, _Gid_str_v[_Li_38], _Gid_len_v[_Li_38]);
_NCp1_NWtr_Pn1_2(&_Lw_37, 0);
continue_10:;
_Li_38++;
}
break_10:;
_Lid_bit8_c_39 = ((_Gid_c + 7) >> 3);
_NCp1_Pmalloc_arr_2(_Gid_in_header_v, _Lid_bit8_c_39);
_NCp1_Pmalloc_arr_2(_Gid_in_header_idx_v, _Gid_c);
_NCp1_Pmalloc_arr_2(_Gid_in_header_id_v, _Gid_c);
Fputnum(&_Lw_37, _Ginclude_c);
int32_t _Li_40;
_Li_40 = 0;
for(int i = _Ginclude_c; i > 0; ) {
i --;
_NCp1_NWtr_Pn1_2(&_Lw_37, _Ginclude_len_v[_Li_40]);
_NCp1_NWtr_Pcopy_3(&_Lw_37, _Ginclude_str_v[_Li_40], _Ginclude_len_v[_Li_40]);
_NCp1_NWtr_Pn1_2(&_Lw_37, 0);
continue_11:;
_Li_40++;
}
break_11:;
_Lat_bit8_c_41 = ((_Gat_c + 7) >> 3);
_NCp1_Pmalloc_arr_2(_Gat_in_header_v, _Lat_bit8_c_41);
_NCp1_Pmalloc_arr_2(_Gat_in_header_idx_v, _Gat_c);
_NCp1_Pmalloc_arr_2(_Gat_in_header_at_v, _Gat_c);
Fputnum(&_Lw_37, _Gat_c);
int32_t _Li_42;
_Li_42 = 0;
for(int i = _Gat_c; i > 0; ) {
i --;
struct _NCp1_NAtData* _Lat_43;
_Lat_43 = (&_Gat_v[_Li_42]);
_NCp1_NNameType_Pwr_2((*_Lat_43)._Ftype, &_Lw_37);
if((*_Lat_43)._Ftype == _NCp1_NNameType_Cbasic) {
_NCp1_NBasicTypeId_Pwr_2((*_Lat_43)._Fname._Fbasic, &_Lw_37);
} else {
_NCp1_NAt_Pwr_3((*_Lat_43)._Fparent, &_Lw_37, false);
_NCp1_NId_Pwr_3((*_Lat_43)._Fname._Fid, &_Lw_37, false);
}
continue_12:;
_Li_42++;
}
break_12:;
_NCp1_Pwrite_cvar_2(&_Lw_37, false);
_NCp1_Pwrite_gvar_2(&_Lw_37, false);
_NCp1_Pwrite_enum_2(&_Lw_37, false);
_NCp1_Pwrite_struct_2(&_Lw_37, false);
_NCp1_Pwrite_func_2(&_Lw_37, false);
_Lout_path_44 = malloc(strlen(_Llock_path_3) + 4 + 1);
sprintf(_Lout_path_44, "%s.tmp", _Llock_path_3);
_Lout_path_len_45 = strlen(_Lout_path_44);
if(!(_NStdc_NFd_Popen_4(&_Lout_fd_46, _Lout_path_44, O_CREAT | O_TRUNC | O_WRONLY, 32676))) {
fprintf(stdout, "Cannot open file for writing: %s\n", _Lout_path_44);
exit(_NStdc_NExit_Cfailure);
}
write(_Lout_fd_46, _Lw_begin_36._Freff, _Lw_37._Fpos - _Lw_begin_36._Fpos);
_NStdc_NFd_Pclose_1(_Lout_fd_46);
_Lw_37._Freff = _Lw_begin_36._Freff;
Fputnum(&_Lw_37, _Gid_in_header_c);
int32_t _Lj_47;
_Lj_47 = 0;
for(int i = _Gid_in_header_c; i > 0; ) {
i --;
uint32_t _Li_48;
_Li_48 = _Gid_in_header_id_v[_Lj_47];
_NCp1_NWtr_Pn1_2(&_Lw_37, _Gid_len_v[_Li_48]);
_NCp1_NWtr_Pcopy_3(&_Lw_37, _Gid_str_v[_Li_48], _Gid_len_v[_Li_48]);
_NCp1_NWtr_Pn1_2(&_Lw_37, 0);
continue_13:;
_Lj_47++;
}
break_13:;
Fputnum(&_Lw_37, _Ginclude_c);
int32_t _Li_49;
_Li_49 = 0;
for(int i = _Ginclude_c; i > 0; ) {
i --;
_NCp1_NWtr_Pn1_2(&_Lw_37, _Ginclude_len_v[_Li_49]);
_NCp1_NWtr_Pcopy_3(&_Lw_37, _Ginclude_str_v[_Li_49], _Ginclude_len_v[_Li_49]);
_NCp1_NWtr_Pn1_2(&_Lw_37, 0);
continue_14:;
_Li_49++;
}
break_14:;
Fputnum(&_Lw_37, _Gat_in_header_c);
int32_t _Lj_50;
_Lj_50 = 0;
for(int i = _Gat_in_header_c; i > 0; ) {
i --;
uint32_t _Li_51;
struct _NCp1_NAtData* _Lat_52;
_Li_51 = _Gat_in_header_at_v[_Lj_50];
_Lat_52 = (&_Gat_v[_Li_51]);
_NCp1_NNameType_Pwr_2((*_Lat_52)._Ftype, &_Lw_37);
if((*_Lat_52)._Ftype == _NCp1_NNameType_Cbasic) {
_NCp1_NBasicTypeId_Pwr_2((*_Lat_52)._Fname._Fbasic, &_Lw_37);
} else {
_NCp1_NAt_Pwr_header_2((*_Lat_52)._Fparent, &_Lw_37);
_NCp1_NId_Pwr_header_2((*_Lat_52)._Fname._Fid, &_Lw_37);
}
continue_15:;
_Lj_50++;
}
break_15:;
_NCp1_Pwrite_cvar_2(&_Lw_37, true);
_NCp1_Pwrite_gvar_2(&_Lw_37, true);
_NCp1_Pwrite_enum_2(&_Lw_37, true);
_NCp1_Pwrite_struct_2(&_Lw_37, true);
_NCp1_Pwrite_func_2(&_Lw_37, true);
_Lout_path_44[(_Lout_path_len_45 - 5)] = 'h';
if(!(_NStdc_NFd_Popen_4(&_Lout_fd_46, _Lout_path_44, O_CREAT | O_TRUNC | O_WRONLY, 32676))) {
fprintf(stdout, "Cannot open file for writing: %s\n", _Lout_path_44);
exit(_NStdc_NExit_Cfailure);
}
write(_Lout_fd_46, _Lw_begin_36._Freff, _Lw_37._Fpos - _Lw_begin_36._Fpos);
_NStdc_NFd_Pclose_1(_Lout_fd_46);
_Lout_path_44[(_Lout_path_len_45 - 5)] = 'b';
memcpy(_Lfinal_path_53, _Lout_path_44, _Lout_path_len_45 - 4);
_Lfinal_path_53[(_Lout_path_len_45 - 4)] = 0;
rename(_Lout_path_44, _Lfinal_path_53);
_Glock_path = NULL;
_Lout_path_44[(_Lout_path_len_45 - 5)] = 'h';
memcpy(_Lfinal_path_53, _Lout_path_44, _Lout_path_len_45 - 4);
_Lfinal_path_53[(_Lout_path_len_45 - 4)] = 0;
rename(_Lout_path_44, _Lfinal_path_53);
return 0;
}
void _NCp1_Pexport_0() {
qalloc_undo(0);
_NCp1_Pdecl_func_begin_3(_NCp1_NId_C0, 0, 0);
_NCp1_Pdecl_func_end_2(0, 0);
_NCp1_Pdecl_struct_end_2(0, 0);
_NCp1_Pdecl_var_begin_3(_NCp1_NId_C0, 0, 0);
_NCp1_Pdecl_var_attr_real_name_1(_NCp1_NId_Cnil);
_NCp1_Pdecl_var_attr_extern_0();
_NCp1_Pdecl_var_attr_no_decl_0();
_NCp1_Pdecl_var_end_0();
_NCp1_Pdecl_var_as_farg_2(0, 0);
_NCp1_Pfarg_next_group_0();
_NCp1_Pdecl_var_as_this_0();
_NCp1_Pdecl_var_as_fvar_0();
_NCp1_Pfunc_body_end_0();
_NCp1_Pexpr_push_call_2(0, 0);
_NCp1_Pexpr_pop_func_2(_NCp1_NAt_Cnil, _NCp1_NId_Cnil);
_NCp1_Pexpr_pop_method_2(_NCp1_NExprI_Cnil, _NCp1_NId_Cnil);
_NCp1_Pcarg_push_1(_NCp1_NExprI_Cnil);
_NCp1_Pcarg_push_str_1(_NCp1_NExprI_Cnil);
_NCp1_Pcarg_next_group_0();
_NCp1_Pexpr2stmt_5(_NCp1_NExprI_Cnil, 0, 0, 0, 0);
_NCp1_Pstmt_return_5(_NCp1_NExprI_Cnil, 0, 0, 0, 0);
_NCp1_Pstmt_continue_5(_NCp1_NId_Cnil, 0, 0, 0, 0);
_NCp1_Pstmt_break_5(_NCp1_NId_Cnil, 0, 0, 0, 0);
_NCp1_Pfunc_attr_main_0();
_NCp1_Pfunc_attr_decl_0();
_NCp1_Pfunc_attr_cp1_name_0();
_NCp1_Pfunc_attr_process_0();
_NCp1_Pfunc_attr_inline_0();
_NCp1_Pfunc_attr_var_args_0();
_NCp1_Pfunc_attr_no_decl_0();
_NCp1_Pfunc_attr_no_body_0();
_NCp1_Pfunc_attr_real_name_1(_NCp1_NId_Cnil);
_NCp1_Pfunc_attr_case_1(_NCp1_NId_Cnil);
_NCp1_Pexpr_lvar_4(_NCp1_NId_C0, 0, 0, 0);
_NCp1_Pexpr_gvar_2(_NCp1_NAt_Cnil, _NCp1_NId_C0);
_NCp1_Pexpr_fvar_2(_NCp1_NExprI_Cnil, _NCp1_NId_Cnil);
_NCp1_Pexpr_assign_3(_NCp1_NExprI_C0, _NCp1_NExprI_C0, _NCp1_NAssign_Ceq);
_NCp1_Pexpr_math_3(_NCp1_NExprI_C0, _NCp1_NExprI_C0, _NCp1_NMath_Cadd);
_NCp1_Pexpr_math_add_2(_NCp1_NExprI_C0, _NCp1_NExprI_C0);
_NCp1_Pexpr_bools_3(_NCp1_NExprI_C0, _NCp1_NExprI_C0, _NCp1_NBools_Cand);
_NCp1_Pexpr_bools_add_2(_NCp1_NExprI_C0, _NCp1_NExprI_C0);
_NCp1_Ptoken_name_1(_NCp1_NToken_Cnil);
_NCp1_Pdecl_var_type_1(_NCp1_NAt_Cnil);
_NCp1_Pdecl_var_this_0();
_NCp1_Pstmt_lvar_add_4(_NCp1_NId_C0, _NCp1_NExprI_Cnil, 0, 0);
_NCp1_Pstmt_lvar_end_2(0, 0);
_NCp1_Pdecl_include_begin_3(_NCp1_NInclude_C0, 0, 0);
_NCp1_Pdecl_include_end_0();
_NCp1_Pdecl_at_basic_1(_NCp1_NBasicTypeId_Croot);
_NCp1_Pdecl_at_add_2(_NCp1_NId_C0, _NCp1_NNameType_Cmodule);
_NCp1_Pdecl_at_begin_2(0, 0);
_NCp1_Pdecl_at_begin_struct_3(_NCp1_NId_Cnil, 0, 0);
_NCp1_Pdecl_at_end_0();
_NCp1_Pdecl_alias_4(_NCp1_NId_Cnil, _NCp1_NAt_Cnil, 0, 0);
_NCp1_Pat_push_4(_NCp1_NId_C0, _NCp1_NNameType_Cmodule, 0, 0);
_NCp1_Pat_done_0();
_NCp1_Pat_begin_0();
_NCp1_Pat_begin_relative_0();
_NCp1_Pat_begin_relative_pause_0();
_NCp1_Pat_begin_relative_resume_0();
_NCp1_Pat_root_0();
_NCp1_Pat_alias_3(_NCp1_NId_Cnil, 0, 0);
_NCp1_Pat_graves_3(0, 0, 0);
_NCp1_Pat_basic_type_1(_NCp1_NBasicTypeId_Ci32);
_NCp1_Pdecl_var_as_gvar_0();
_NCp1_Ptype_info_arr_2(NULL, 0);
_NCp1_Ptype_info_ref_1(0);
_NCp1_Ptype_info_static_0();
_NCp1_Ptype_info_begin_0();
_NCp1_Ptype_info_finalize_0();
_NCp1_Pexpr_int_2(0, _NCp1_NExprInt_Cdec);
_NCp1_Pexpr_size_of_type_1(_NCp1_NAt_Cnil);
_NCp1_Pexpr_null_0();
_NCp1_Pdecl_at_begin_enum_3(_NCp1_NId_Cnil, 0, 0);
_NCp1_Pdecl_enum_end_3(_NCp1_NAt_Cnil, 0, 0);
_NCp1_Pexpr_cvar_2(_NCp1_NAt_Cnil, _NCp1_NId_Cnil);
_NCp1_Penum_add_cvar_3(_NCp1_NId_Cnil, 0, 0);
_NCp1_Pdecl_add_cvar_3(_NCp1_NId_Cnil, 0, 0);
_NCp1_Penum_set_cvar_expr_1(_NCp1_NExprI_Cnil);
_NCp1_Pstruct_attr_real_name_1(_NCp1_NId_Cnil);
_NCp1_Pstruct_attr_union_0();
_NCp1_Pstruct_attr_no_decl_0();
_NCp1_Pexpr_str_1(_NCp1_NExprI_Cnil);
_NCp1_Pexpr_unary_2(_NCp1_NExprI_Cnil, _NCp1_NUnary_Cneg);
_NCp1_Pexpr_ref_1(_NCp1_NExprI_Cnil);
_NCp1_Pexpr_cast_fast_2(_NCp1_NExprI_Cnil, _NCp1_NAt_Cnil);
_NCp1_Pexpr_index_3(_NCp1_NExprI_Cnil, NULL, 0);
_NCp1_Penum_base_begin_0();
_NCp1_Pstmt_switch_begin_0();
_NCp1_Pstmt_switch_set_6(_NCp1_NExprI_Cnil, 0, 0, 0, 0, _NCp1_NExprI_Cnil);
_NCp1_Pstmt_switch_expr_add_1(_NCp1_NExprI_Cnil);
_NCp1_Pstmt_switch_case_begin_5(0, 0, 0, 0, false);
_NCp1_Pstmt_switch_case_end_0();
_NCp1_Pstmt_switch_default_begin_5(0, 0, 0, 0, false);
_NCp1_Pstmt_switch_default_end_0();
_NCp1_Pstmt_switch_end_0();
_NCp1_Pstmt_if_begin_0();
_NCp1_Pstmt_if_set_6(false, _NCp1_NExprI_Cnil, 0, 0, 0, 0);
_NCp1_Pstmt_if_end_0();
_NCp1_Pstmt_do_begin_0();
_NCp1_Pstmt_do_set_6(_NCp1_NExprI_Cnil, 0, 0, 0, 0, NULL);
_NCp1_Pstmt_do_end_0();
_NCp1_Pstmt_while_begin_0();
_NCp1_Pstmt_while_set_6(_NCp1_NExprI_Cnil, 0, 0, 0, 0, NULL);
_NCp1_Pstmt_while_end_0();
_NCp1_Pstmt_elif_begin_0();
_NCp1_Pstmt_elif_set_6(false, _NCp1_NExprI_Cnil, 0, 0, 0, 0);
_NCp1_Pstmt_elif_end_0();
_NCp1_Pstmt_else_set_0();
_NCp1_Pstmt_else_end_0();
_NCp1_Pstmt_if_end_ifs_0();
_NCp1_Pstmt_space_begin_0();
_NCp1_Pstmt_space_begin_detach_0();
_NCp1_Pstmt_space_end_0();
_NCp1_Pexpr_compare_3(_NCp1_NExprI_Cnil, _NCp1_NExprI_Cnil, _NCp1_NCompare_Ceq);
_NCp1_Pexpr_bool_1(false);
_NCp1_Pexpr_char_1(0);
_NCp1_Pcvar_attr_real_name_1(_NCp1_NId_Cnil);
_NCp1_Pcvar_attr_no_decl_0();
}
void _NCp1_Pquick_alloc_init_0() {
_Gquick_alloc_cap = (16 * 1024);
_Gquick_alloc_v = malloc(_Gquick_alloc_cap);
memset(_Gquick_alloc_v, 0, _Gquick_alloc_cap);
}
inline bool _NStdc_NFd_Popen_3(_NStdc_NFd* _Lfile_0, char* _Lpath_1, _NStdc_NOpenFlags _Lflags_2) {
_NStdc_NFd _Lfd_3;
_Lfd_3 = open(_Lpath_1, _Lflags_2);
if(_Lfd_3 != -1) {
(*_Lfile_0) = _Lfd_3;
return true;
} else {
return false;
}
}
inline int _NStdc_NFd_Pclose_1(_NStdc_NFd _Lfile_0) {
return close(_Lfile_0);
}
void _NCp1_Pget_row_col_4(int32_t* _Lout_row_0, int32_t* _Lout_col_1, void* _Lend_2, void* _Lbegin_3) {
int32_t _Lrow_4;
int32_t _Lcol_5;
union _NCp1_NRdr _Lr_6;
union _NCp1_NRdr _Lr_end_7;
_Lrow_4 = 1;
_Lcol_5 = 1;
_Lr_6._Freff = _Lbegin_3;
_Lr_end_7._Freff = _Lend_2;
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
void _NCp1_Pparse_string_4(union _NCp1_NRdr* _Lr_0, union _NCp1_NWtr* _Lw_1, char _Lending_2, void* _Lin_data_3) {
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
_NCp1_Pget_row_col_4(&_Lrow_5, &_Lcol_6, (*_Lr_0)._Freff, _Lin_data_3);
fprintf(stdout, "%s:%u:%u: Unterminated string\n", input_path, _Lrow_5, _Lcol_6);
exit(_NStdc_NExit_Cfailure);
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
void _NCp1_NLexer_Pinit_3(struct _NCp1_NLexer* _Llex_0, uint8_t* _Ldata_1, size_t _Lsize_2) {
(*_Llex_0)._Fstart = _Ldata_1;
(*_Llex_0)._Fcursor = _Ldata_1;
(*_Llex_0)._Fcontent = _Ldata_1;
}
int32_t _NCp1_NLexer_Pget_id_3(struct _NCp1_NLexer* _Llex_0, uint8_t _Lbegin_1, uint8_t _Lend_2) {
union _NCp1_NRdr _Lr_start_3;
union _NCp1_NRdr _Lr_cursor_4;
size_t _Llength_5;
uint8_t _Llen_6;
int32_t _Lfound_7;
_Lr_start_3._Freff = (*_Llex_0)._Fstart;
_Lr_start_3._Fpos += _Lbegin_1;
_Lr_cursor_4._Freff = (*_Llex_0)._Fcursor;
_Llength_5 = (_Lr_cursor_4._Fpos - _Lr_start_3._Fpos - _Lend_2);
if(_Llength_5 > 255) {
fprintf(stdout, "too long id was detected\n");
exit(_NStdc_NExit_Cfailure);
}
_Llen_6 = (uint8_t)(_Llength_5);
_Lfound_7 = _NCp1_NMap_Pget_or_insert_4(&_Gid_map, _Lr_start_3._Freff, _Llen_6, _Gid_c);
if(_Lfound_7 == -1) {
int32_t _Lid_8;
char* _Ltext_10;
_Lid_8 = _Gid_c++;
if(_Gid_cap <= _Gid_c) {
int32_t _Lold_cap_9;
_Lold_cap_9 = _Gid_cap;
_NCp1_Pgrow_2(_Gid_cap, _Gid_c);
_NCp1_Prealloc_3(_Gid_str_v, _Gid_cap, _Lold_cap_9);
_NCp1_Prealloc_3(_Gid_len_v, _Gid_cap, _Lold_cap_9);
}
_Ltext_10 = qalloc(_Llen_6 + 1);
memcpy(_Ltext_10, _Lr_start_3._Freff, _Llen_6);
_Ltext_10[_Llen_6] = 0;
_Gid_str_v[_Lid_8] = _Ltext_10;
_Gid_len_v[_Lid_8] = _Llen_6;
return _Lid_8;
} else {
return _Lfound_7;
}
}
uint32_t _NCp1_NLexer_Pget_u32_dec_1(struct _NCp1_NLexer* _Llex_0) {
union _NCp1_NRdr _Lr_start_1;
union _NCp1_NRdr _Lr_cursor_2;
size_t _Llength_3;
uint64_t _Lval_4;
_Lr_start_1._Freff = (*_Llex_0)._Fstart;
_Lr_cursor_2._Freff = (*_Llex_0)._Fcursor;
_Llength_3 = (_Lr_cursor_2._Fpos - _Lr_start_1._Fpos);
if(_Llength_3 > 10) {
fprintf(stdout, "%s:%u:%u: Integer literal was too long\n", input_path, _Grow, _Gcol);
exit(_NStdc_NExit_Cfailure);
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
exit(_NStdc_NExit_Cfailure);
}
return (uint32_t)(_Lval_4);
}
uint32_t _NCp1_NLexer_Pget_u32_oct_1(struct _NCp1_NLexer* _Llex_0) {
union _NCp1_NRdr _Lr_start_1;
union _NCp1_NRdr _Lr_cursor_2;
size_t _Llength_3;
uint64_t _Lval_4;
_Lr_start_1._Freff = (*_Llex_0)._Fstart;
_Lr_cursor_2._Freff = (*_Llex_0)._Fcursor;
_Llength_3 = (_Lr_cursor_2._Fpos - _Lr_start_1._Fpos);
if(_Llength_3 > 12) {
fprintf(stdout, "%s:%u:%u: Integer literal was too long\n", input_path, _Grow, _Gcol);
exit(_NStdc_NExit_Cfailure);
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
exit(_NStdc_NExit_Cfailure);
}
return (uint32_t)(_Lval_4);
}
int32_t _NCp1_NLexer_Pget_include_1(struct _NCp1_NLexer* _Llex_0) {
union _NCp1_NRdr _Lr_start_1;
union _NCp1_NRdr _Lr_cursor_2;
size_t _Llength_3;
uint8_t _Llen_4;
int32_t _Lfound_5;
_Lr_start_1._Freff = (*_Llex_0)._Fstart;
_Lr_start_1._Fpos += 9;
_Lr_cursor_2._Freff = (*_Llex_0)._Fcursor;
_Llength_3 = (_Lr_cursor_2._Fpos - _Lr_start_1._Fpos - 1);
if(_Llength_3 > 255) {
fprintf(stdout, "too long include was detected\n");
exit(_NStdc_NExit_Cfailure);
}
_Llen_4 = (uint8_t)(_Llength_3);
_Lfound_5 = _NCp1_NMap_Pget_or_insert_4(&_Ginclude_map, _Lr_start_1._Freff, _Llen_4, _Ginclude_c);
if(_Lfound_5 == -1) {
int32_t _Linclude_6;
char* _Ltext_8;
_Linclude_6 = _Ginclude_c++;
if(_Ginclude_cap <= _Ginclude_c) {
int32_t _Lold_cap_7;
_Lold_cap_7 = _Ginclude_cap;
_NCp1_Pgrow_2(_Ginclude_cap, _Ginclude_c);
_NCp1_Prealloc_3(_Ginclude_str_v, _Ginclude_cap, _Lold_cap_7);
_NCp1_Prealloc_3(_Ginclude_len_v, _Ginclude_cap, _Lold_cap_7);
}
_Ltext_8 = qalloc(_Llen_4 + 1);
memcpy(_Ltext_8, _Lr_start_1._Freff, _Llen_4);
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
union _NCp1_NRdr _Lr_1;
_Lr_1._Freff = _Gquick_alloc_v;
_Lr_1._Fpos += _Gquick_alloc_c;
_Gquick_alloc_c += _Lsize_0;
return _Lr_1._Freff;
}
_NCp1_Pgrow_2(_Gquick_alloc_cap, _Gquick_alloc_c + _Lsize_0);
_Gquick_alloc_v = malloc(_Gquick_alloc_cap);
memset(_Gquick_alloc_v, 0, _Gquick_alloc_cap);
_Gquick_alloc_c = _Lsize_0;
return _Gquick_alloc_v;
}
inline void _NCp1_NWtr_Pn1_2(union _NCp1_NWtr* _Lw_0, uint8_t _Ln_1) {
(*_Lw_0)._Fp1[0] = _Ln_1;
(*_Lw_0)._Fpos++;
}
inline void _NCp1_NWtr_Pcopy_3(union _NCp1_NWtr* _Lw_0, void* _Ldata_1, int32_t _Lsize_2) {
memcpy((*_Lw_0)._Freff, _Ldata_1, _Lsize_2);
(*_Lw_0)._Fpos += _Lsize_2;
}
inline void _NCp1_NNameType_Pwr_2(_NCp1_NNameType _Li_0, union _NCp1_NWtr* _Lw_1) {
_NCp1_NWtr_Pn1_2(_Lw_1, _Li_0);
}
inline void _NCp1_NBasicTypeId_Pwr_2(_NCp1_NBasicTypeId _Le_0, union _NCp1_NWtr* _Lw_1) {
_NCp1_NWtr_Pn1_2(_Lw_1, _Le_0);
}
inline void _NCp1_NAt_Pwr_3(_NCp1_NAt _Lat_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2) {
if(_Lat_0 == _NCp1_NAt_Cnil) {
Fputnum(_Lw_1, 0);
} else {
if(_Lheader_2) {
Fputnum(_Lw_1, 1 + _Gat_in_header_idx_v[_Lat_0]);
} else {
Fputnum(_Lw_1, 1 + _Lat_0);
_NCp1_NAt_Pput_to_header_1(_Lat_0);
}
}
}
inline void _NCp1_NId_Pwr_3(_NCp1_NId _Lid_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2) {
if(_Lid_0 == _NCp1_NId_Cnil) {
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
void _NCp1_Pwrite_cvar_2(union _NCp1_NWtr* _Lw_0, bool _Lheader_1) {
Fputnum(_Lw_0, _Gcvar_c);
int32_t _Li_2;
_Li_2 = 0;
for(int i = _Gcvar_c; i > 0; ) {
i --;
struct _NCp1_NCvarData* _Lcvar_3;
_Lcvar_3 = (&_Gcvar_v[_Li_2]);
_NCp1_NInclude_Pwr_2((*_Lcvar_3)._Finclude, _Lw_0);
_NCp1_NAt_Pwr_3((*_Lcvar_3)._Fat, _Lw_0, _Lheader_1);
_NCp1_NDeclVarData_Pwr_3(&(*_Lcvar_3)._Fdecl, _Lw_0, _Lheader_1);
_NCp1_NCvarFlags_Pwr_2((*_Lcvar_3)._Fflags, _Lw_0);
if(((*_Lcvar_3)._Fflags & _NCp1_NCvarFlags_Cset_expr) != _NCp1_NCvarFlags_C0) {
_NCp1_NExprI_Pwr_3((*_Lcvar_3)._Fexpr_set, _Lw_0, _Lheader_1);
} else {
_NCp1_NCvar_Pwr_2((*_Lcvar_3)._Flast_cvar, _Lw_0);
}
continue_0:;
_Li_2++;
}
break_0:;
}
void _NCp1_Pwrite_gvar_2(union _NCp1_NWtr* _Lw_0, bool _Lheader_1) {
Fputnum(_Lw_0, _Ggvar_c);
int32_t _Li_2;
_Li_2 = 0;
for(int i = _Ggvar_c; i > 0; ) {
i --;
struct _NCp1_NDeclGvar* _Lgvar_3;
_Lgvar_3 = (&_Ggvar_v[_Li_2]);
_NCp1_NInclude_Pwr_2((*_Lgvar_3)._Finclude, _Lw_0);
_NCp1_NAt_Pwr_3((*_Lgvar_3)._Fat, _Lw_0, _Lheader_1);
_NCp1_NDeclVarData_Pwr_3(&(*_Lgvar_3)._Fdecl, _Lw_0, _Lheader_1);
continue_0:;
_Li_2++;
}
break_0:;
}
void _NCp1_Pwrite_enum_2(union _NCp1_NWtr* _Lw_0, bool _Lheader_1) {
Fputnum(_Lw_0, _Genum_c);
int32_t _Li_2;
_Li_2 = 0;
for(int i = _Genum_c; i > 0; ) {
i --;
struct _NCp1_NEnumData* _Le_3;
_Le_3 = _Genum_v[_Li_2++];
Fputnum(_Lw_0, (*_Le_3)._Fbegin_row);
Fputnum(_Lw_0, (*_Le_3)._Fbegin_col);
Fputnum(_Lw_0, (*_Le_3)._Fend_row);
Fputnum(_Lw_0, (*_Le_3)._Fend_col);
_NCp1_NInclude_Pwr_2((*_Le_3)._Finclude, _Lw_0);
_NCp1_NAt_Pwr_3((*_Le_3)._Fat, _Lw_0, _Lheader_1);
_NCp1_NAt_Pwr_3((*_Le_3)._Fbase_type, _Lw_0, _Lheader_1);
_NCp1_NEnumFlags_Pwr_2((*_Le_3)._Fflags, _Lw_0);
if(((*_Le_3)._Fflags & _NCp1_NEnumFlags_Creal_name) != _NCp1_NEnumFlags_C0) {
_NCp1_NId_Pwr_3((*_Le_3)._Freal_name, _Lw_0, _Lheader_1);
}
continue_0:;
}
break_0:;
}
void _NCp1_Pwrite_struct_2(union _NCp1_NWtr* _Lw_0, bool _Lheader_1) {
Fputnum(_Lw_0, _Gstruct_c);
int32_t _Li_2;
_Li_2 = 0;
for(int i = _Gstruct_c; i > 0; ) {
i --;
struct _NCp1_NStructData* _Ls_3;
_Ls_3 = _Gstruct_v[_Li_2++];
_NCp1_NWtr_Pn1_2(_Lw_0, (*_Ls_3)._Ffvar_c);
Fputnum(_Lw_0, (*_Ls_3)._Fbegin_row);
Fputnum(_Lw_0, (*_Ls_3)._Fbegin_col);
Fputnum(_Lw_0, (*_Ls_3)._Fend_row);
Fputnum(_Lw_0, (*_Ls_3)._Fend_col);
_NCp1_NInclude_Pwr_2((*_Ls_3)._Finclude, _Lw_0);
_NCp1_NAt_Pwr_3((*_Ls_3)._Fat, _Lw_0, _Lheader_1);
_NCp1_NStructFlags_Pwr_2((*_Ls_3)._Fflags, _Lw_0);
int32_t _Lj_4;
_Lj_4 = 0;
for(int i = (*_Ls_3)._Ffvar_c; i > 0; ) {
i --;
_NCp1_NFvarData_Pwr_3(&(*_Ls_3)._Ffvar_v[_Lj_4], _Lw_0, _Lheader_1);
continue_1:;
_Lj_4++;
}
break_1:;
if(((*_Ls_3)._Fflags & _NCp1_NStructFlags_Creal_name) != _NCp1_NStructFlags_C0) {
_NCp1_NId_Pwr_3((*_Ls_3)._Freal_name, _Lw_0, _Lheader_1);
}
continue_0:;
}
break_0:;
}
inline void _NCp1_Pwrite_func_2(union _NCp1_NWtr* _Lw_0, bool _Lheader_1) {
Fputnum(_Lw_0, _Gfunc_c);
int32_t _Li_2;
_Li_2 = 0;
for(int i = _Gfunc_c; i > 0; ) {
i --;
struct _NCp1_NDeclFunc* _Lf_3;
_Lf_3 = _Gfunc_v[_Li_2++];
_NCp1_NWtr_Pn1_2(_Lw_0, (*_Lf_3)._Ffarg_c);
Fputnum(_Lw_0, (*_Lf_3)._Fbegin_row);
Fputnum(_Lw_0, (*_Lf_3)._Fbegin_col);
Fputnum(_Lw_0, (*_Lf_3)._Fend_row);
Fputnum(_Lw_0, (*_Lf_3)._Fend_col);
_NCp1_NInclude_Pwr_2((*_Lf_3)._Finclude, _Lw_0);
_NCp1_NAt_Pwr_3((*_Lf_3)._Fat, _Lw_0, _Lheader_1);
_NCp1_NDeclVarData_Pwr_3(&(*_Lf_3)._Fdecl, _Lw_0, _Lheader_1);
int32_t _Lj_4;
_Lj_4 = 0;
for(int i = (*_Lf_3)._Ffarg_c; i > 0; ) {
i --;
_NCp1_NFarg_Pwr_3(&(*_Lf_3)._Ffarg_v[_Lj_4], _Lw_0, _Lheader_1);
continue_1:;
_Lj_4++;
}
break_1:;
_NCp1_NWtr_Pn1_2(_Lw_0, (*_Lf_3)._Fthis_idx);
if((*_Lf_3)._Fthis_idx != -1) {
_NCp1_NWtr_Pn1_2(_Lw_0, (*_Lf_3)._Fthis_group);
}
_NCp1_NWtr_Pn1_2(_Lw_0, (*_Lf_3)._Fgroup_c);
int32_t _Lj_5;
_Lj_5 = 0;
for(int i = (*_Lf_3)._Fgroup_c; i > 0; ) {
i --;
_NCp1_NWtr_Pn1_2(_Lw_0, (*_Lf_3)._Fgroup_v[_Lj_5]);
continue_2:;
_Lj_5++;
}
break_2:;
if(_Lheader_1) {
if((*_Lf_3)._Fflags & _NCp1_NFuncFlags_Cinline) {
_NCp1_NFuncFlags_Pwr_2((*_Lf_3)._Fflags, _Lw_0);
} else {
_NCp1_NFuncFlags_Pwr_2((_NCp1_NFuncFlags)((*_Lf_3)._Fflags & (-1 ^ _NCp1_NFuncFlags_Chas_body)), _Lw_0);
}
} else {
_NCp1_NFuncFlags_Pwr_2((*_Lf_3)._Fflags, _Lw_0);
}
if(((*_Lf_3)._Fflags & _NCp1_NFuncFlags_Creal_name) != _NCp1_NFuncFlags_C0) {
_NCp1_NId_Pwr_3((*_Lf_3)._Freal_name, _Lw_0, _Lheader_1);
}
if(((*_Lf_3)._Fflags & _NCp1_NFuncFlags_Ccase) != _NCp1_NFuncFlags_C0) {
_NCp1_NId_Pwr_3((*_Lf_3)._Fcas, _Lw_0, _Lheader_1);
}
if(((*_Lf_3)._Fflags & _NCp1_NFuncFlags_Cdecl) != _NCp1_NFuncFlags_C0) {
Fputnum(_Lw_0, (*_Lf_3)._Fdecl_len);
_NCp1_NWtr_Pcopy_3(_Lw_0, (*_Lf_3)._Fdecl_str, (*_Lf_3)._Fdecl_len);
}
continue_0:;
}
break_0:;
_NCp1_NFunc_Pwr_2(_Gfunc_main, _Lw_0);
int32_t _Li_6;
_Li_6 = 0;
for(int i = _Gfunc_c; i > 0; ) {
i --;
struct _NCp1_NDeclFunc* _Lf_7;
union _NCp1_NWtr _Lpos_4_8;
size_t _Lpos_4_next_9;
_Lf_7 = _Gfunc_v[_Li_6++];
if(((*_Lf_7)._Fflags & _NCp1_NFuncFlags_Chas_body) == _NCp1_NFuncFlags_C0) {
goto continue_3;
}
if(_Lheader_1) {
if((*_Lf_7)._Fflags & _NCp1_NFuncFlags_Cinline) {
} else {
goto continue_3;
}
}
_Lpos_4_8._Fp1 = (*_Lw_0)._Fp1;
(*_Lw_0)._Fpos += 4;
_Lpos_4_next_9 = (*_Lw_0)._Fpos;
_NCp1_NDeclFunc_Plvars_wr_3(_Lf_7, _Lw_0, _Lheader_1);
_NCp1_NStmtSpace_Pwr_3((*_Lf_7)._Fstmt_space, _Lw_0, _Lheader_1);
_NCp1_NWtr_Pn4_2(&_Lpos_4_8, (*_Lw_0)._Fpos - _Lpos_4_next_9);
continue_3:;
}
break_3:;
}
inline bool _NStdc_NFd_Popen_4(_NStdc_NFd* _Lfile_0, char* _Lpath_1, _NStdc_NOpenFlags _Lflags_2, int _Lmode_3) {
_NStdc_NFd _Lfd_4;
_Lfd_4 = open(_Lpath_1, _Lflags_2, _Lmode_3);
if(_Lfd_4 != -1) {
(*_Lfile_0) = _Lfd_4;
return true;
} else {
return false;
}
}
inline void _NCp1_NAt_Pwr_header_2(_NCp1_NAt _Lid_0, union _NCp1_NWtr* _Lw_1) {
if(_Lid_0 == _NCp1_NAt_Cnil) {
Fputnum(_Lw_1, 0);
} else {
Fputnum(_Lw_1, 1 + _Gat_in_header_idx_v[_Lid_0]);
}
}
inline void _NCp1_NId_Pwr_header_2(_NCp1_NId _Lid_0, union _NCp1_NWtr* _Lw_1) {
if(_Lid_0 == _NCp1_NId_Cnil) {
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
void _NCp1_Pdecl_func_begin_3(_NCp1_NId _Lname_0, int32_t _Lrow_1, int32_t _Lcol_2) {
_Gdecl_func_name = _Lname_0;
_Gdecl_func_row = _Lrow_1;
_Gdecl_func_col = _Lcol_2;
_Gdecl_func_flags = _NCp1_NFuncFlags_C0;
_Gdecl_func_flags2 = _NCp1_NFuncFlags2_C0;
_Gdecl_farg_c = 0;
_Gdecl_farg_group_c = 1;
_Gdecl_farg_group_v[0] = 0;
_Gdecl_func_this_idx = -1;
_Gdecl_func_this_group = -1;
_Gdecl_func_real_name = _NCp1_NId_Cnil;
_Gdecl_func_case = _NCp1_NId_Cnil;
_Gdecl_func_decl_str = NULL;
_Gdecl_func_decl_len = 0;
_NCp1_Pquick_alloc_one_1(_Gdecl_func_space);
_Gdecl_func_ctx_space = _Gdecl_func_space;
}
void _NCp1_Pdecl_func_end_2(int32_t _Lrow_0, int32_t _Lcol_1) {
_NCp1_NFunc _Lf_idx_2;
struct _NCp1_NDeclFunc* _Lf_4;
struct _NCp1_NStmtSpace* _Lspace_9;
_Lf_idx_2 = (_NCp1_NFunc)(_Gfunc_c++);
if(_Gfunc_cap <= _Gfunc_c) {
_NCp1_NFunc _Lold_cap_3;
_Lold_cap_3 = _Gfunc_cap;
_NCp1_Pgrow_2(_Gfunc_cap, _Gfunc_c);
_NCp1_Prealloc_3(_Gfunc_v, _Gfunc_cap, _Lold_cap_3);
}
_NCp1_Pquick_alloc_plus_2(_Lf_4, sizeof(struct _NCp1_NFarg) * _Gdecl_farg_c);
_Gctx_func = _Lf_4;
_Gnest_id = 0;
_Gfunc_v[_Lf_idx_2] = _Lf_4;
(*_Lf_4)._Fbegin_row = _Gdecl_func_row;
(*_Lf_4)._Fbegin_col = _Gdecl_func_col;
(*_Lf_4)._Fend_row = _Lrow_0;
(*_Lf_4)._Fend_col = _Lcol_1;
(*_Lf_4)._Finclude = _Gdecl_include;
(*_Lf_4)._Fat = _Gdecl_at;
if((_Gdecl_func_flags & _NCp1_NFuncFlags_Creal_name) != _NCp1_NFuncFlags_C0) {
if(_Gdecl_func_real_name == _NCp1_NId_Cnil) {
(*_Lf_4)._Freal_name = _Gdecl_func_name;
} else {
(*_Lf_4)._Freal_name = _Gdecl_func_real_name;
}
}
if((_Gdecl_func_flags & _NCp1_NFuncFlags_Ccase) != _NCp1_NFuncFlags_C0) {
(*_Lf_4)._Fcas = _Gdecl_func_case;
}
_Gdecl_var._Fname = _Gdecl_func_name;
_NCp1_NDeclVarData_Pcopy_from_2(&(*_Lf_4)._Fdecl, &_Gdecl_var);
(*_Lf_4)._Ffarg_c = _Gdecl_farg_c;
int32_t _Li_5;
_Li_5 = 0;
for(int i = _Gdecl_farg_c; i > 0; ) {
i --;
struct _NCp1_NFarg* _Lfa_6;
_Lfa_6 = (&(*_Lf_4)._Ffarg_v[_Li_5]);
_NCp1_NFarg_Pcopy_from_2(_Lfa_6, &_Gdecl_farg_v[_Li_5]);
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
if((_Gdecl_func_flags2 & _NCp1_NFuncFlags2_Cmain) != _NCp1_NFuncFlags2_C0) {
_Gfunc_main = _Lf_idx_2;
} else if(((_Gdecl_at == _NCp1_NAt_Croot) && (_NCp1_NId_Plen_1((*_Lf_4)._Fdecl._Fname) == 4) && (memcmp("main", _NCp1_NId_Pstr_1((*_Lf_4)._Fdecl._Fname), 4) == 0))) {
if(_Gfunc_main != _NCp1_NFunc_Cnil) {
struct _NCp1_NDeclFunc* _Lmain_8;
_Lmain_8 = _NCp1_NFunc_Pptr_1(_Gfunc_main);
fprintf(stdout, "%u:%u: There:S already a function with @main attribute at %u:%u\n", (*_Lf_4)._Fbegin_row, (*_Lf_4)._Fbegin_col, (*_Lmain_8)._Fbegin_row, (*_Lmain_8)._Fbegin_col);
exit(_NStdc_NExit_Cfailure);
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
struct _NCp1_NFarg* _Lfa_11;
_NCp1_NLvar _Llvar_i_12;
struct _NCp1_NLvarData* _Llvar_13;
_Lfa_11 = (&(*_Lf_4)._Ffarg_v[_Li_10]);
_Llvar_i_12 = _NCp1_NStmtSpace_Plvar_new_4(_Lspace_9, (*_Lfa_11)._Fdecl._Fname, (*_Lfa_11)._Frow, (*_Lfa_11)._Fcol);
_Llvar_13 = _NCp1_NLvar_Pptr_1(_Llvar_i_12);
_NCp1_NDeclVarData_Pcopy_from_2(&(*_Llvar_13)._Fdecl, &(*_Lfa_11)._Fdecl);
continue_2:;
_Li_10++;
}
break_2:;
}
void _NCp1_Pdecl_struct_end_2(int32_t _Lrow_0, int32_t _Lcol_1) {
_NCp1_NStruct _Ls_idx_2;
struct _NCp1_NStructData* _Ls_4;
_Ls_idx_2 = _Gstruct_c++;
if(_Gstruct_cap <= _Gstruct_c) {
_NCp1_NStruct _Lold_cap_3;
_Lold_cap_3 = _Gstruct_cap;
_NCp1_Pgrow_2(_Gstruct_cap, _Gstruct_c);
_NCp1_Prealloc_3(_Gstruct_v, _Gstruct_cap, _Lold_cap_3);
}
_NCp1_Pquick_alloc_plus_2(_Ls_4, sizeof(struct _NCp1_NFvarData) * _Gdecl_fvar_c);
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
struct _NCp1_NFvarData* _La_6;
_La_6 = (&(*_Ls_4)._Ffvar_v[_Li_5]);
_NCp1_NDeclVarData_Pcopy_from_2(&(*_La_6)._Fdecl, &_Gdecl_fvar_v[_Li_5]);
continue_0:;
_Li_5++;
}
break_0:;
(*_Ls_4)._Freal_name = _Gdecl_struct_real_name;
}
void _NCp1_Pdecl_var_begin_3(_NCp1_NId _Lname_0, int32_t _Lrow_1, int32_t _Lcol_2) {
_Gdecl_var._Fname = _Lname_0;
_Gdecl_var_row = _Lrow_1;
_Gdecl_var_col = _Lcol_2;
_NCp1_NTypeInfo_Pinit_1(&_Gdecl_var._Ftype_info);
_Gdecl_var._Fflags = _NCp1_NVarFlags_C0;
_Gdecl_var._Freal_name = _NCp1_NId_Cnil;
_Gdecl_var._Fsize_c = 0;
}
void _NCp1_Pdecl_var_attr_real_name_1(_NCp1_NId _Lname_0) {
if((_Gdecl_var._Fflags & _NCp1_NVarFlags_Creal_name) != _NCp1_NVarFlags_C0) {
fprintf(stdout, "%u:%u: error @real-name specified more than once\n", _Glast_row, _Glast_col);
exit(_NStdc_NExit_Cfailure);
}
_Gdecl_var._Fflags |= _NCp1_NVarFlags_Creal_name;
_Gdecl_var._Freal_name = _Lname_0;
}
void _NCp1_Pdecl_var_attr_extern_0() {
if((_Gdecl_var._Fflags & _NCp1_NVarFlags_Cextern) != _NCp1_NVarFlags_C0) {
fprintf(stdout, "%u:%u: error @extern specified more than once\n", _Glast_row, _Glast_col);
exit(_NStdc_NExit_Cfailure);
}
_Gdecl_var._Fflags |= _NCp1_NVarFlags_Cextern;
}
void _NCp1_Pdecl_var_attr_no_decl_0() {
if((_Gdecl_var._Fflags & _NCp1_NVarFlags_Cno_decl) != _NCp1_NVarFlags_C0) {
fprintf(stdout, "%u:%u: error @no-decl specified more than once\n", _Glast_row, _Glast_col);
exit(_NStdc_NExit_Cfailure);
}
_Gdecl_var._Fflags |= _NCp1_NVarFlags_Cno_decl;
}
void _NCp1_Pdecl_var_end_0() {
}
void _NCp1_Pdecl_var_as_farg_2(int32_t _Lrow_0, int32_t _Lcol_1) {
int32_t _Lfarg_idx_2;
struct _NCp1_NFarg* _Lfa_4;
_Lfarg_idx_2 = _Gdecl_farg_c++;
if(_Gdecl_farg_cap <= _Gdecl_farg_c) {
int32_t _Lold_cap_3;
_Lold_cap_3 = _Gdecl_farg_cap;
_NCp1_Pgrow_2(_Gdecl_farg_cap, _Gdecl_farg_c);
_NCp1_Prealloc_3(_Gdecl_farg_v, _Gdecl_farg_cap, _Lold_cap_3);
}
_Lfa_4 = (&_Gdecl_farg_v[_Lfarg_idx_2]);
(*_Lfa_4)._Frow = _Lrow_0;
(*_Lfa_4)._Fcol = _Lcol_1;
_NCp1_NDeclVarData_Pcopy_from_2(&(*_Lfa_4)._Fdecl, &_Gdecl_var);
_Gdecl_farg_group_v[(_Gdecl_farg_group_c - 1)]++;
}
void _NCp1_Pfarg_next_group_0() {
_Gdecl_farg_group_v[_Gdecl_farg_group_c] = 0;
_Gdecl_farg_group_c++;
}
void _NCp1_Pdecl_var_as_this_0() {
int32_t _Lfarg_idx_0;
_Gdecl_func_this_idx = _Gdecl_farg_c;
_Gdecl_func_this_group = (_Gdecl_farg_group_c - 1);
_Lfarg_idx_0 = _Gdecl_farg_c++;
if(_Gdecl_farg_cap <= _Gdecl_farg_c) {
int32_t _Lold_cap_1;
_Lold_cap_1 = _Gdecl_farg_cap;
_NCp1_Pgrow_2(_Gdecl_farg_cap, _Gdecl_farg_c);
_NCp1_Prealloc_3(_Gdecl_farg_v, _Gdecl_farg_cap, _Lold_cap_1);
}
_NCp1_NDeclVarData_Pcopy_from_2(&_Gdecl_farg_v[_Lfarg_idx_0]._Fdecl, &_Gdecl_var);
_Gdecl_farg_v[_Lfarg_idx_0]._Fdecl._Ftype = _Gdecl_at;
_Gdecl_farg_group_v[(_Gdecl_farg_group_c - 1)]++;
}
void _NCp1_Pdecl_var_as_fvar_0() {
uint32_t _Lfvar_0;
_Lfvar_0 = _Gdecl_fvar_c++;
if(_Gdecl_fvar_cap <= _Gdecl_fvar_c) {
uint32_t _Lold_cap_1;
_Lold_cap_1 = _Gdecl_fvar_cap;
_NCp1_Pgrow_2(_Gdecl_fvar_cap, _Gdecl_fvar_c);
_NCp1_Prealloc_3(_Gdecl_fvar_v, _Gdecl_fvar_cap, _Lold_cap_1);
}
_NCp1_NDeclVarData_Pcopy_from_2(&_Gdecl_fvar_v[_Lfvar_0], &_Gdecl_var);
}
void _NCp1_Pfunc_body_end_0() {
struct _NCp1_NDeclFunc* _Lf_0;
int32_t _Lc_1;
struct _NCp1_NStmt* _Ls_2;
_Lf_0 = _Gfunc_v[(_Gfunc_c - 1)];
(*_Lf_0)._Fflags |= _NCp1_NFuncFlags_Chas_body;
_Lc_1 = 0;
_Ls_2 = (*(*_Lf_0)._Fstmt_space)._Fstmt_first;
while(_Ls_2 != NULL) {
_Lc_1++;
_Ls_2 = (*_Ls_2)._Fstmt_next;
continue_0:;
}
break_0:;
}
void _NCp1_Pexpr_push_call_2(int32_t _Lrow_0, int32_t _Lcol_1) {
int8_t _Lcall_idx_2;
_Lcall_idx_2 = _Gexpr_call_c++;
if(_Lcall_idx_2 >= _NCp1_Cexpr_call_nest_limit) {
fprintf(stdout, "%u:%u: Too much nested calls\n", _Lrow_0, _Lcol_1);
exit(_NStdc_NExit_Cfailure);
}
_Gexpr_call_carg_c[_Lcall_idx_2] = 0;
_Gexpr_call_cgrp_c[_Lcall_idx_2] = 1;
_Gexpr_call_cgrp_v[_Lcall_idx_2][0] = 0;
}
_NCp1_NExprI _NCp1_Pexpr_pop_func_2(_NCp1_NAt _Lat_0, _NCp1_NId _Lfunc_name_1) {
int8_t _Lcall_idx_2;
uint8_t _Lcarg_c_3;
struct _NCp1_NExprFunc* _Le_4;
_NCp1_NExprI _Le_idx_5;
_Lcall_idx_2 = (_Gexpr_call_c -= 1);
_Lcarg_c_3 = _Gexpr_call_carg_c[_Lcall_idx_2];
_NCp1_Pquick_alloc_plus_2(_Le_4, sizeof(struct _NCp1_NCarg) * _Lcarg_c_3);
_Le_idx_5 = _NCp1_Pexpr_push_2(&(*_Le_4)._Fbase, _NCp1_NExprType_Cfunc);
(*_Le_4)._Fat = _Lat_0;
(*_Le_4)._Ffunc_name = _Lfunc_name_1;
(*_Le_4)._Fcarg_c = _Lcarg_c_3;
int32_t _Li_6;
_Li_6 = 0;
for(int i = _Lcarg_c_3; i > 0; ) {
i --;
(*_Le_4)._Fcarg_v[_Li_6]._Freff = 0;
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
_NCp1_NExprI _NCp1_Pexpr_pop_method_2(_NCp1_NExprI _Lthiss_0, _NCp1_NId _Lfunc_name_1) {
int8_t _Lcall_idx_2;
uint8_t _Lcarg_c_3;
struct _NCp1_NExprMethod* _Le_4;
_NCp1_NExprI _Le_idx_5;
_Lcall_idx_2 = (_Gexpr_call_c -= 1);
_Lcarg_c_3 = _Gexpr_call_carg_c[_Lcall_idx_2];
_NCp1_Pquick_alloc_plus_2(_Le_4, sizeof(struct _NCp1_NCarg) * _Lcarg_c_3);
_Le_idx_5 = _NCp1_Pexpr_push_2(&(*_Le_4)._Fbase, _NCp1_NExprType_Cmethod);
(*_Le_4)._Fthiss = _Lthiss_0;
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
void _NCp1_Pcarg_push_1(_NCp1_NExprI _Lexpr_0) {
int8_t _Lcall_idx_1;
_Lcall_idx_1 = (_Gexpr_call_c - 1);
_Gexpr_call_carg_v[_Lcall_idx_1][_Gexpr_call_carg_c[_Lcall_idx_1]++] = _Lexpr_0;
_Gexpr_call_cgrp_v[_Lcall_idx_1][(_Gexpr_call_cgrp_c[_Lcall_idx_1] - 1)]++;
}
void _NCp1_Pcarg_push_str_1(_NCp1_NExprI _Lexpr_0) {
if(true) {
int8_t _Lcall_idx_1;
_Lcall_idx_1 = (_Gexpr_call_c - 1);
_Gexpr_call_carg_v[_Lcall_idx_1][_Gexpr_call_carg_c[_Lcall_idx_1]++] = _Lexpr_0;
_Gexpr_call_cgrp_v[_Lcall_idx_1][(_Gexpr_call_cgrp_c[_Lcall_idx_1] - 1)]++;
}
if(true) {
struct _NCp1_NExprStr* _Le_2;
int32_t _Llen_3;
struct _NCp1_NExprStrNode* _Ls_4;
int8_t _Lcall_idx_5;
_Le_2 = _NCp1_NExprI_Pptr_1(_Lexpr_0);
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
_Gexpr_call_carg_v[_Lcall_idx_5][_Gexpr_call_carg_c[_Lcall_idx_5]++] = _NCp1_Pexpr_int_2(_Llen_3, _NCp1_NExprInt_Cdec);
_Gexpr_call_cgrp_v[_Lcall_idx_5][(_Gexpr_call_cgrp_c[_Lcall_idx_5] - 1)]++;
}
}
void _NCp1_Pcarg_next_group_0() {
int8_t _Lcall_idx_0;
_Lcall_idx_0 = (_Gexpr_call_c - 1);
_Gexpr_call_cgrp_v[_Lcall_idx_0][_Gexpr_call_cgrp_c[_Lcall_idx_0]] = 0;
_Gexpr_call_cgrp_c[_Lcall_idx_0]++;
}
void _NCp1_Pexpr2stmt_5(_NCp1_NExprI _Le_0, int32_t _Lbegin_row_1, int32_t _Lbegin_col_2, int32_t _Lend_row_3, int32_t _Lend_col_4) {
struct _NCp1_NStmtExpr* _Ls_5;
_NCp1_Pquick_alloc_one_1(_Ls_5);
_NCp1_Pstmt_push_6(&(*_Ls_5)._Fbase, _Lbegin_row_1, _Lbegin_col_2, _Lend_row_3, _Lend_col_4, _NCp1_NStmtType_Cexpr);
(*_Ls_5)._Fexpr = _Le_0;
}
void _NCp1_Pstmt_return_5(_NCp1_NExprI _Le_0, int32_t _Lbegin_row_1, int32_t _Lbegin_col_2, int32_t _Lend_row_3, int32_t _Lend_col_4) {
struct _NCp1_NStmtReturn* _Ls_5;
_NCp1_Pquick_alloc_one_1(_Ls_5);
_NCp1_Pstmt_push_6(&(*_Ls_5)._Fbase, _Lbegin_row_1, _Lbegin_col_2, _Lend_row_3, _Lend_col_4, _NCp1_NStmtType_Creturn);
(*_Ls_5)._Fexpr = _Le_0;
}
void _NCp1_Pstmt_continue_5(_NCp1_NId _Lid_0, int32_t _Lbegin_row_1, int32_t _Lbegin_col_2, int32_t _Lend_row_3, int32_t _Lend_col_4) {
struct _NCp1_NStmtContinue* _Ls_5;
_NCp1_Pquick_alloc_one_1(_Ls_5);
_NCp1_Pstmt_push_6(&(*_Ls_5)._Fbase, _Lbegin_row_1, _Lbegin_col_2, _Lend_row_3, _Lend_col_4, _NCp1_NStmtType_Ccontinue);
if(_Gnest_stack_c <= 0) {
fprintf(stdout, "%s:%u:%u: Cannot have a continue because it:S not inside a loop\n", input_path, _Lbegin_row_1, _Lbegin_col_2);
exit(_NStdc_NExit_Cfailure);
}
(*_Ls_5)._Fnest = (_Gnest_stack_c - 1);
}
void _NCp1_Pstmt_break_5(_NCp1_NId _Lid_0, int32_t _Lbegin_row_1, int32_t _Lbegin_col_2, int32_t _Lend_row_3, int32_t _Lend_col_4) {
struct _NCp1_NStmtBreak* _Ls_5;
_NCp1_Pquick_alloc_one_1(_Ls_5);
_NCp1_Pstmt_push_6(&(*_Ls_5)._Fbase, _Lbegin_row_1, _Lbegin_col_2, _Lend_row_3, _Lend_col_4, _NCp1_NStmtType_Cbreak);
if(_Gnest_stack_c <= 0) {
fprintf(stdout, "%s:%u:%u: Cannot have a break because it:S not inside a loop\n", input_path, _Lbegin_row_1, _Lbegin_col_2);
exit(_NStdc_NExit_Cfailure);
}
(*_Ls_5)._Fnest = (_Gnest_stack_c - 1);
}
void _NCp1_Pfunc_attr_main_0() {
if((_Gdecl_func_flags2 & _NCp1_NFuncFlags2_Cmain) != _NCp1_NFuncFlags2_C0) {
fprintf(stdout, "%s:%u:%u: Error @main specified more than once\n", input_path, _Glast_row, _Glast_col);
exit(_NStdc_NExit_Cfailure);
}
if(_Gfunc_main != _NCp1_NFunc_Cnil) {
struct _NCp1_NDeclFunc* _Lfirst_0;
_Lfirst_0 = _NCp1_NFunc_Pptr_1(_Gfunc_main);
fprintf(stdout, "There cannot be more than one function with @main attribute, first was %s:%u:%u and then %u:%u\n", input_path, (*_Lfirst_0)._Fbegin_row, (*_Lfirst_0)._Fbegin_col, _Gdecl_func_row, _Gdecl_func_col);
exit(_NStdc_NExit_Cfailure);
}
_Gdecl_func_flags2 |= _NCp1_NFuncFlags2_Cmain;
}
void _NCp1_Pfunc_attr_decl_0() {
if((_Gdecl_func_flags & _NCp1_NFuncFlags_Cdecl) != _NCp1_NFuncFlags_C0) {
fprintf(stdout, "%s:%u:%u: Error @decl specified more than once\n", input_path, _Glast_row, _Glast_col);
exit(_NStdc_NExit_Cfailure);
}
_Gdecl_func_flags |= _NCp1_NFuncFlags_Cdecl;
_Gdecl_func_decl_str = qalloc(_Gstring_len + 1);
memcpy(_Gdecl_func_decl_str, _Gstring_buf, _Gstring_len);
_Gdecl_func_decl_str[_Gstring_len] = 0;
_Gdecl_func_decl_len = _Gstring_len;
}
void _NCp1_Pfunc_attr_cp1_name_0() {
if((_Gdecl_func_flags & _NCp1_NFuncFlags_Ccp1_name) != _NCp1_NFuncFlags_C0) {
fprintf(stdout, "%s:%u:%u: Error @cp1-name specified more than once\n", input_path, _Glast_row, _Glast_col);
exit(_NStdc_NExit_Cfailure);
}
_Gdecl_func_flags |= _NCp1_NFuncFlags_Ccp1_name;
}
void _NCp1_Pfunc_attr_process_0() {
if((_Gdecl_func_flags & _NCp1_NFuncFlags_Cprocess) != _NCp1_NFuncFlags_C0) {
fprintf(stdout, "%s:%u:%u: Error @process specified more than once\n", input_path, _Glast_row, _Glast_col);
exit(_NStdc_NExit_Cfailure);
}
_Gdecl_func_flags |= _NCp1_NFuncFlags_Cprocess;
}
void _NCp1_Pfunc_attr_inline_0() {
if((_Gdecl_func_flags & _NCp1_NFuncFlags_Cinline) != _NCp1_NFuncFlags_C0) {
fprintf(stdout, "%s:%u:%u: Error @inline specified more than once\n", input_path, _Glast_row, _Glast_col);
exit(_NStdc_NExit_Cfailure);
}
_Gdecl_func_flags |= _NCp1_NFuncFlags_Cinline;
}
void _NCp1_Pfunc_attr_var_args_0() {
if((_Gdecl_func_flags & _NCp1_NFuncFlags_Cvar_args) != _NCp1_NFuncFlags_C0) {
fprintf(stdout, "%s:%u:%u: Error @var-args specified more than once\n", input_path, _Glast_row, _Glast_col);
exit(_NStdc_NExit_Cfailure);
}
_Gdecl_func_flags |= _NCp1_NFuncFlags_Cvar_args;
}
void _NCp1_Pfunc_attr_no_decl_0() {
if((_Gdecl_func_flags & _NCp1_NFuncFlags_Cno_decl) != _NCp1_NFuncFlags_C0) {
fprintf(stdout, "%s:%u:%u: Error @no-decl specified more than once\n", input_path, _Glast_row, _Glast_col);
exit(_NStdc_NExit_Cfailure);
}
_Gdecl_func_flags |= _NCp1_NFuncFlags_Cno_decl;
}
void _NCp1_Pfunc_attr_no_body_0() {
if((_Gdecl_func_flags & _NCp1_NFuncFlags_Cno_body) != _NCp1_NFuncFlags_C0) {
fprintf(stdout, "%s:%u:%u: Error @no-body specified more than once\n", input_path, _Glast_row, _Glast_col);
exit(_NStdc_NExit_Cfailure);
}
_Gdecl_func_flags |= _NCp1_NFuncFlags_Cno_body;
}
void _NCp1_Pfunc_attr_real_name_1(_NCp1_NId _Lname_0) {
if((_Gdecl_func_flags & _NCp1_NFuncFlags_Creal_name) != _NCp1_NFuncFlags_C0) {
fprintf(stdout, "%s:%u:%u: Error @real-name specified more than once\n", input_path, _Glast_row, _Glast_col);
exit(_NStdc_NExit_Cfailure);
}
_Gdecl_func_flags |= _NCp1_NFuncFlags_Creal_name;
_Gdecl_func_real_name = _Lname_0;
}
void _NCp1_Pfunc_attr_case_1(_NCp1_NId _Lname_0) {
char* _Lname_str_1;
uint8_t _Lname_len_2;
char* _Lfunc_name_str_3;
uint8_t _Lfunc_name_len_4;
if((_Gdecl_func_flags & _NCp1_NFuncFlags_Ccase) != _NCp1_NFuncFlags_C0) {
fprintf(stdout, "%s:%u:%u: Error @case specified more than once\n", input_path, _Glast_row, _Glast_col);
exit(_NStdc_NExit_Cfailure);
}
_Lname_str_1 = _NCp1_NId_Pstr_1(_Lname_0);
_Lname_len_2 = _NCp1_NId_Plen_1(_Lname_0);
_Lfunc_name_str_3 = _NCp1_NId_Pstr_1(_Gdecl_func_name);
_Lfunc_name_len_4 = _NCp1_NId_Plen_1(_Gdecl_func_name);
if(((_Lname_len_2 > _Lfunc_name_len_4) || (_Lfunc_name_str_3[_Lname_len_2] != '-') || (memcmp(_Lname_str_1, _Lfunc_name_str_3, _Lname_len_2) != 0))) {
fprintf(stdout, "%s:%u:%u: Error, function name must begin with words used in @case followed by '-' (dash) then followed by the name of the cvar of case\n", input_path, _Glast_row, _Glast_col);
exit(_NStdc_NExit_Cfailure);
}
_Gdecl_func_flags |= _NCp1_NFuncFlags_Ccase;
_Gdecl_func_case = _Lname_0;
}
_NCp1_NExprI _NCp1_Pexpr_lvar_4(_NCp1_NId _Lname_0, uint8_t _Ldecl_1, int32_t _Lrow_2, int32_t _Lcol_3) {
if(_Ldecl_1 == 0) {
struct _NCp1_NStmtSpace* _Lspace_4;
_Lspace_4 = _Gdecl_func_ctx_space;
while(1) {
_NCp1_NLvar* _Lv_5;
_NCp1_NLvar _Lfound_6;
_Lv_5 = (*_Lspace_4)._Flvar_v;
_Lfound_6 = _NCp1_NLvar_Cnil;
int32_t _Li_7;
_Li_7 = 0;
for(int i = (*_Lspace_4)._Flvar_c; i > 0; ) {
i --;
_NCp1_NLvar _Llvar_8;
_Llvar_8 = _Lv_5[_Li_7];
if(_NCp1_NLvar_Pname_1(_Llvar_8) == _Lname_0) {
_Lfound_6 = _Llvar_8;
goto break_1;
}
continue_1:;
_Li_7++;
}
break_1:;
if(_Lfound_6 != _NCp1_NLvar_Cnil) {
struct _NCp1_NExprLvar* _Le_9;
_NCp1_NExprI _Le_idx_10;
_NCp1_Pquick_alloc_one_1(_Le_9);
_Le_idx_10 = _NCp1_Pexpr_push_2(&(*_Le_9)._Fbase, _NCp1_NExprType_Clvar);
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
fprintf(stdout, "%s:%u:%u: local variable '%s' was not found\n", input_path, _Lrow_2, _Lcol_3, _NCp1_NId_Pstr_1(_Lname_0));
exit(_NStdc_NExit_Cfailure);
return _NCp1_NExprI_Cnil;
} else {
struct _NCp1_NStmtSpace* _Lspace_11;
struct _NCp1_NExprLvar* _Le_12;
_NCp1_NExprI _Le_idx_13;
struct _NCp1_NLvarData* _Llvar_14;
_Lspace_11 = _Gdecl_func_ctx_space;
while(_Ldecl_1 > 1) {
_Lspace_11 = (*_Lspace_11)._Fparent;
if(_Lspace_11 == NULL) {
fprintf(stdout, "%s:%u:%u: Cannot declare local variable '%s' with too much '+'\n", input_path, _Lrow_2, _Lcol_3, _NCp1_NId_Pstr_1(_Lname_0));
exit(_NStdc_NExit_Cfailure);
}
if(((*_Lspace_11)._Fflags & _NCp1_NStmtSpaceFlags_Cskip_lvar_decl) == _NCp1_NStmtSpaceFlags_C0) {
_Ldecl_1--;
}
continue_2:;
}
break_2:;
_NCp1_Pquick_alloc_one_1(_Le_12);
_Le_idx_13 = _NCp1_Pexpr_push_2(&(*_Le_12)._Fbase, _NCp1_NExprType_Clvar);
(*_Le_12)._Flvar = _NCp1_NStmtSpace_Plvar_new_4(_Lspace_11, _Lname_0, _Lrow_2, _Lcol_3);
_Llvar_14 = _NCp1_NLvar_Pptr_1((*_Le_12)._Flvar);
_Gdecl_var._Fname = _Lname_0;
_NCp1_NDeclVarData_Pcopy_from_2(&(*_Llvar_14)._Fdecl, &_Gdecl_var);
return _Le_idx_13;
}
}
_NCp1_NExprI _NCp1_Pexpr_gvar_2(_NCp1_NAt _Lat_0, _NCp1_NId _Lname_1) {
struct _NCp1_NExprGvar* _Le_2;
_NCp1_NExprI _Le_idx_3;
_NCp1_Pquick_alloc_one_1(_Le_2);
_Le_idx_3 = _NCp1_Pexpr_push_2(&(*_Le_2)._Fbase, _NCp1_NExprType_Cgvar);
(*_Le_2)._Fat = _Lat_0;
(*_Le_2)._Fname = _Lname_1;
return _Le_idx_3;
}
_NCp1_NExprI _NCp1_Pexpr_fvar_2(_NCp1_NExprI _Lexpr_0, _NCp1_NId _Lmember_1) {
struct _NCp1_NExprFvar* _Le_2;
_NCp1_NExprI _Le_idx_3;
_NCp1_Pquick_alloc_one_1(_Le_2);
_Le_idx_3 = _NCp1_Pexpr_push_2(&(*_Le_2)._Fbase, _NCp1_NExprType_Cfvar);
(*_Le_2)._Fexpr = _Lexpr_0;
(*_Le_2)._Fmember = _Lmember_1;
return _Le_idx_3;
}
_NCp1_NExprI _NCp1_Pexpr_assign_3(_NCp1_NExprI _Lleft_0, _NCp1_NExprI _Lright_1, _NCp1_NAssign _Ltype_2) {
struct _NCp1_NExprAssign* _Le_3;
_NCp1_NExprI _Le_idx_4;
_NCp1_Pquick_alloc_one_1(_Le_3);
_Le_idx_4 = _NCp1_Pexpr_push_2(&(*_Le_3)._Fbase, _NCp1_NExprType_Cassign);
(*_Le_3)._Fleft = _Lleft_0;
(*_Le_3)._Fright = _Lright_1;
(*_Le_3)._Ftype = _Ltype_2;
return _Le_idx_4;
}
_NCp1_NExprI _NCp1_Pexpr_math_3(_NCp1_NExprI _Lleft_0, _NCp1_NExprI _Lright_1, _NCp1_NMath _Ltype_2) {
struct _NCp1_NExprMath* _Le_3;
_NCp1_NExprI _Le_idx_4;
_NCp1_Pquick_alloc_one_1(_Le_3);
_Le_idx_4 = _NCp1_Pexpr_push_2(&(*_Le_3)._Fbase, _NCp1_NExprType_Cmath);
(*_Le_3)._Fleft = _Lleft_0;
(*_Le_3)._Fright = _Lright_1;
(*_Le_3)._Ftype = _Ltype_2;
return _Le_idx_4;
}
_NCp1_NExprI _NCp1_Pexpr_math_add_2(_NCp1_NExprI _Lexpr_0, _NCp1_NExprI _Lright_1) {
struct _NCp1_NExprMath* _Le_2;
uint8_t _Li_3;
struct _NCp1_NExprMathItem* _Litem_5;
_Le_2 = _NCp1_NExprI_Pptr_1(_Lexpr_0);
_Li_3 = (*_Le_2)._Fitem_c++;
if((*_Le_2)._Fitem_cap <= (*_Le_2)._Fitem_c) {
uint8_t _Lold_cap_4;
_Lold_cap_4 = (*_Le_2)._Fitem_cap;
_NCp1_Pgrow_2((*_Le_2)._Fitem_cap, (*_Le_2)._Fitem_c);
_NCp1_Prealloc_3((*_Le_2)._Fitem_v, (*_Le_2)._Fitem_cap, _Lold_cap_4);
}
_Litem_5 = (&(*_Le_2)._Fitem_v[_Li_3]);
(*_Litem_5)._Fexpr = _Lright_1;
return _Lexpr_0;
}
_NCp1_NExprI _NCp1_Pexpr_bools_3(_NCp1_NExprI _Lleft_0, _NCp1_NExprI _Lright_1, _NCp1_NBools _Ltype_2) {
struct _NCp1_NExprBools* _Le_3;
_NCp1_NExprI _Le_idx_4;
_NCp1_Pquick_alloc_one_1(_Le_3);
_Le_idx_4 = _NCp1_Pexpr_push_2(&(*_Le_3)._Fbase, _NCp1_NExprType_Cbools);
(*_Le_3)._Fleft = _Lleft_0;
(*_Le_3)._Fright = _Lright_1;
(*_Le_3)._Ftype = _Ltype_2;
return _Le_idx_4;
}
_NCp1_NExprI _NCp1_Pexpr_bools_add_2(_NCp1_NExprI _Lbools_0, _NCp1_NExprI _Lright_1) {
struct _NCp1_NExprBools* _Le_2;
uint8_t _Li_3;
_Le_2 = _NCp1_NExprI_Pptr_1(_Lbools_0);
_Li_3 = (*_Le_2)._Fitem_c++;
if((*_Le_2)._Fitem_cap <= (*_Le_2)._Fitem_c) {
uint8_t _Lold_cap_4;
_Lold_cap_4 = (*_Le_2)._Fitem_cap;
_NCp1_Pgrow_2((*_Le_2)._Fitem_cap, (*_Le_2)._Fitem_c);
_NCp1_Prealloc_3((*_Le_2)._Fitem_v, (*_Le_2)._Fitem_cap, _Lold_cap_4);
}
(*_Le_2)._Fitem_v[_Li_3]._Fexpr = _Lright_1;
return _Lbools_0;
}
char* _NCp1_Ptoken_name_1(_NCp1_NToken _Ltok_0) {
return _NCp1_NToken_Pcp1_name_1(_Ltok_0);
}
void _NCp1_Pdecl_var_type_1(_NCp1_NAt _Ltype_0) {
if(_Ltype_0 != _NCp1_NAt_Cnil) {
struct _NCp1_NAtData* _Lat_1;
_Lat_1 = _NCp1_NAt_Pptr_1(_Ltype_0);
if((*_Lat_1)._Ftype == _NCp1_NNameType_Cmodule) {
fprintf(stdout, "%u:%u: module '%%%s' cannot be used as a type\n", _Glast_row, _Glast_col, _NCp1_NId_Pstr_1((*_Lat_1)._Fname._Fid));
exit(_NStdc_NExit_Cfailure);
}
}
_Gdecl_var._Ftype = _Ltype_0;
_Gdecl_var._Fsize_c = 0;
_NCp1_NTypeInfo_Pinit_1(&_Gdecl_var._Ftype_info);
_Gdecl_var._Fflags = _NCp1_NVarFlags_C0;
}
void _NCp1_Pdecl_var_this_0() {
_NCp1_NAt _Ltype_0;
struct _NCp1_NAtData* _Lat_1;
_Ltype_0 = _Gdecl_at;
_Lat_1 = _NCp1_NAt_Pptr_1(_Ltype_0);
if((*_Lat_1)._Ftype == _NCp1_NNameType_Cmodule) {
fprintf(stdout, "%u:%u: module '%%%s' cannot be used as a type\n", _Glast_row, _Glast_col, _NCp1_NId_Pstr_1((*_Lat_1)._Fname._Fid));
exit(_NStdc_NExit_Cfailure);
}
_Gdecl_var._Ftype = _Ltype_0;
}
void _NCp1_Pstmt_lvar_add_4(_NCp1_NId _Lname_0, _NCp1_NExprI _Lset_1, int32_t _Lrow_2, int32_t _Lcol_3) {
_NCp1_NLvar _Llvar_i_4;
struct _NCp1_NLvarData* _Llvar_5;
_Llvar_i_4 = _NCp1_NStmtSpace_Plvar_new_4(_Gdecl_func_ctx_space, _Lname_0, _Lrow_2, _Lcol_3);
_Llvar_5 = _NCp1_NLvar_Pptr_1(_Llvar_i_4);
_Gdecl_var._Fname = _Lname_0;
_NCp1_NDeclVarData_Pcopy_from_2(&(*_Llvar_5)._Fdecl, &_Gdecl_var);
if(_Lset_1 != _NCp1_NExprI_Cnil) {
_NCp1_NExprI _Le_6;
_Le_6 = _NCp1_Pexpr_assign_3(_NCp1_Pexpr_lvar_4(_Lname_0, 0, _Lrow_2, _Lcol_3), _Lset_1, _NCp1_NAssign_Ceq);
_NCp1_Pexpr2stmt_5(_Le_6, _Lrow_2, _Lcol_3, _Lrow_2, _Lcol_3);
}
}
void _NCp1_Pstmt_lvar_end_2(int32_t _Lend_row_0, int32_t _Lend_col_1) {
}
void _NCp1_Pdecl_include_begin_3(_NCp1_NInclude _Linc_0, int32_t _Lrow_1, int32_t _Lcol_2) {
if(_Gdecl_include != _NCp1_NInclude_Cnil) {
fprintf(stdout, "%s:%u:%u: Cannot {include inside another {include of %u:%u\n", input_path, _Lrow_1, _Lcol_2, _Gdecl_include_row, _Gdecl_include_col);
exit(_NStdc_NExit_Cfailure);
return;
}
_Gdecl_include = _Linc_0;
_Gdecl_include_row = _Lrow_1;
_Gdecl_include_col = _Lcol_2;
}
void _NCp1_Pdecl_include_end_0() {
_Gdecl_include = _NCp1_NInclude_Cnil;
}
void _NCp1_Pdecl_at_basic_1(_NCp1_NBasicTypeId _Ltype_0) {
_Gbuild_at = _NCp1_Pat_create_basic_1(_Ltype_0);
}
void _NCp1_Pdecl_at_add_2(_NCp1_NId _Lname_0, _NCp1_NNameType _Ltype_1) {
_Gbuild_at = _NCp1_Pat_create_3(_Gbuild_at, _Ltype_1, _Lname_0);
}
void _NCp1_Pdecl_at_begin_2(int32_t _Lrow_0, int32_t _Lcol_1) {
_Gdecl_at_v[_Gdecl_at_c++] = _Gdecl_at;
_Gdecl_at = _Gbuild_at;
}
void _NCp1_Pdecl_at_begin_struct_3(_NCp1_NId _Lname_0, int32_t _Lrow_1, int32_t _Lcol_2) {
_Gdecl_struct_row = _Lrow_1;
_Gdecl_struct_col = _Lcol_2;
_Gbuild_at = _Gdecl_at;
_NCp1_Pdecl_at_add_2(_Lname_0, _NCp1_NNameType_Cstruct_enum);
_Gdecl_at_v[_Gdecl_at_c++] = _Gdecl_at;
_Gdecl_at = _Gbuild_at;
_Gdecl_struct_at = _Gbuild_at;
_Gdecl_fvar_c = 0;
_Gdecl_struct_real_name = _NCp1_NId_Cnil;
_Gdecl_struct_flags = _NCp1_NStructFlags_C0;
}
void _NCp1_Pdecl_at_end_0() {
_Gdecl_at_c--;
_Gdecl_at = _Gdecl_at_v[_Gdecl_at_c];
}
void _NCp1_Pdecl_alias_4(_NCp1_NId _Lname_0, _NCp1_NAt _Lat_1, int32_t _Lrow_2, int32_t _Lcol_3) {
_NCp1_NAlias _Lalias_idx_5;
int32_t _Li_4;
_Li_4 = 0;
for(int i = _Gat_alias_c; i > 0; ) {
i --;
if(_Gat_alias_name_v[_Li_4] == _Lname_0) {
fprintf(stdout, "%s:%u:%u: Alias '%s was already declared at %u:%u\n", input_path, _Lrow_2, _Lcol_3, _NCp1_NId_Pstr_1(_Lname_0), _Gat_alias_pos_v[_Li_4]._Frow, _Gat_alias_pos_v[_Li_4]._Fcol);
exit(_NStdc_NExit_Cfailure);
return;
}
continue_0:;
_Li_4++;
}
break_0:;
_Lalias_idx_5 = _Gat_alias_c++;
if(_Gat_alias_cap <= _Gat_alias_c) {
_NCp1_NAlias _Lold_cap_6;
_Lold_cap_6 = _Gat_alias_cap;
_NCp1_Pgrow_2(_Gat_alias_cap, _Gat_alias_c);
_NCp1_Prealloc_3(_Gat_alias_name_v, _Gat_alias_cap, _Lold_cap_6);
_NCp1_Prealloc_3(_Gat_alias_at_v, _Gat_alias_cap, _Lold_cap_6);
_NCp1_Prealloc_3(_Gat_alias_pos_v, _Gat_alias_cap, _Lold_cap_6);
}
_Gat_alias_name_v[_Lalias_idx_5] = _Lname_0;
_Gat_alias_at_v[_Lalias_idx_5] = _Lat_1;
_Gat_alias_pos_v[_Lalias_idx_5]._Frow = _Lrow_2;
_Gat_alias_pos_v[_Lalias_idx_5]._Fcol = _Lcol_3;
}
void _NCp1_Pat_push_4(_NCp1_NId _Lname_0, _NCp1_NNameType _Ltype_1, int32_t _Lrow_2, int32_t _Lcol_3) {
if(_Gbuild_at == _NCp1_NAt_Crelative) {
int32_t _Li_4;
_Li_4 = 0;
for(int i = _Gat_alias_c; i > 0; ) {
i --;
if(_Gat_alias_name_v[_Li_4] == _Lname_0) {
_Gbuild_at = _Gat_alias_at_v[_Li_4];
return;
}
continue_0:;
_Li_4++;
}
break_0:;
}
_Gbuild_at = _NCp1_Pat_create_3(_Gbuild_at, _Ltype_1, _Lname_0);
}
_NCp1_NAt _NCp1_Pat_done_0() {
return _Gbuild_at;
}
void _NCp1_Pat_begin_0() {
_Gbuild_at = _Gdecl_at;
}
void _NCp1_Pat_begin_relative_0() {
if(_Gat_begin_relative_pause) {
_Gbuild_at = _Gdecl_at;
} else {
_Gbuild_at = _NCp1_NAt_Crelative;
}
}
void _NCp1_Pat_begin_relative_pause_0() {
_Gat_begin_relative_pause = true;
}
void _NCp1_Pat_begin_relative_resume_0() {
_Gat_begin_relative_pause = false;
}
void _NCp1_Pat_root_0() {
_Gbuild_at = _NCp1_NAt_Croot;
}
void _NCp1_Pat_alias_3(_NCp1_NId _Lname_0, int32_t _Lrow_1, int32_t _Lcol_2) {
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
fprintf(stdout, "%s:%u:%u: Cannot recognize the '%s, did you forgot to put using '%s = ...;?\n", input_path, _Lrow_1, _Lcol_2, _NCp1_NId_Pstr_1(_Lname_0), _NCp1_NId_Pstr_1(_Lname_0));
exit(_NStdc_NExit_Cfailure);
}
void _NCp1_Pat_graves_3(int8_t _Lgraves_0, int32_t _Lrow_1, int32_t _Lcol_2) {
_Gbuild_at = _Gdecl_at;
while(_Lgraves_0 > 0) {
struct _NCp1_NAtData* _Lat_3;
_Lgraves_0--;
if(_Gbuild_at == _NCp1_NAt_Croot) {
fprintf(stdout, "%s:%u:%u: Too many graves in the namespace, going beyond the root namespace\n", input_path, _Lrow_1, _Lcol_2);
exit(_NStdc_NExit_Cfailure);
}
_Lat_3 = _NCp1_NAt_Pptr_1(_Gbuild_at);
_Gbuild_at = (*_Lat_3)._Fparent;
continue_0:;
}
break_0:;
}
_NCp1_NAt _NCp1_Pat_basic_type_1(_NCp1_NBasicTypeId _Ltype_0) {
_NCp1_NAt _Lbuild_idx_3;
struct _NCp1_NAtData* _Lat_5;
_NCp1_NAt _Li_1;
_Li_1 = (_NCp1_NAt)(0);
for(int i = _Gat_c; i > 0; ) {
i --;
struct _NCp1_NAtData* _Lat_2;
_Lat_2 = (&_Gat_v[_Li_1]);
if((((*_Lat_2)._Ftype == _NCp1_NNameType_Cbasic) && ((*_Lat_2)._Fname._Fbasic == _Ltype_0))) {
return _Li_1;
}
continue_0:;
_Li_1++;
}
break_0:;
_Lbuild_idx_3 = _Gat_c++;
if(_Gat_cap <= _Gat_c) {
_NCp1_NAt _Lold_cap_4;
_Lold_cap_4 = _Gat_cap;
_NCp1_Pgrow_2(_Gat_cap, _Gat_c);
_NCp1_Prealloc_3(_Gat_v, _Gat_cap, _Lold_cap_4);
}
_Lat_5 = (&_Gat_v[_Lbuild_idx_3]);
(*_Lat_5)._Fparent = _NCp1_NAt_Croot;
(*_Lat_5)._Ftype = _NCp1_NNameType_Cbasic;
(*_Lat_5)._Fname._Fbasic = _Ltype_0;
return _Lbuild_idx_3;
}
void _NCp1_Pdecl_var_as_gvar_0() {
_NCp1_NGvar _Lgvar_idx_0;
struct _NCp1_NDeclGvar* _Lgvar_2;
_Lgvar_idx_0 = _Ggvar_c++;
if(_Ggvar_cap <= _Ggvar_c) {
_NCp1_NGvar _Lold_cap_1;
_Lold_cap_1 = _Ggvar_cap;
_NCp1_Pgrow_2(_Ggvar_cap, _Ggvar_c);
_NCp1_Prealloc_3(_Ggvar_v, _Ggvar_cap, _Lold_cap_1);
}
_Lgvar_2 = (&_Ggvar_v[_Lgvar_idx_0]);
(*_Lgvar_2)._Finclude = _Gdecl_include;
(*_Lgvar_2)._Fat = _Gdecl_at;
_NCp1_NDeclVarData_Pcopy_from_2(&(*_Lgvar_2)._Fdecl, &_Gdecl_var);
}
void _NCp1_Ptype_info_arr_2(_NCp1_NExprI* _Lexpr_v_0, uint8_t _Lexpr_c_1) {
union _NCp1_NRdr _Lr_2;
_Lr_2._Freff = _Lexpr_v_0;
if(_Lexpr_v_0 == NULL) {
struct _NCp1_NTypeInfo* _Lti_3;
_Lti_3 = (&_Gdecl_var._Ftype_info);
(*_Lti_3)._Farray_c += 1;
(*_Lti_3)._Fref_v[(*_Lti_3)._Farray_c] = 0;
return;
}
uint8_t _Li_4;
_Li_4 = _Lexpr_c_1;
for(int i = _Lexpr_c_1; i > 0; ) {
i --;
_NCp1_Ptype_info_arr_1(_Lexpr_v_0[(_Li_4 -= 1)]);
continue_0:;
}
break_0:;
}
void _NCp1_Ptype_info_ref_1(int8_t _Lc_0) {
struct _NCp1_NTypeInfo* _Lti_1;
_Lti_1 = (&_Gdecl_var._Ftype_info);
(*_Lti_1)._Fref_v[(*_Lti_1)._Farray_c] += _Lc_0;
}
void _NCp1_Ptype_info_static_0() {
_Gdecl_var._Ftype_info._Fbuilt_in = true;
}
void _NCp1_Ptype_info_begin_0() {
_Gdecl_var._Fsize_c = 0;
_NCp1_NTypeInfo_Pinit_1(&_Gdecl_var._Ftype_info);
_Gdecl_var._Fflags = _NCp1_NVarFlags_C0;
}
void _NCp1_Ptype_info_finalize_0() {
_NCp1_NTypeInfo_Pfinalize_1(&_Gdecl_var._Ftype_info);
}
_NCp1_NExprI _NCp1_Pexpr_int_2(int32_t _Lvalue_0, _NCp1_NExprInt _Ltype_1) {
struct _NCp1_NExprIntData* _Le_2;
_NCp1_NExprI _Le_idx_3;
_NCp1_Pquick_alloc_one_1(_Le_2);
_Le_idx_3 = _NCp1_Pexpr_push_2(&(*_Le_2)._Fbase, _NCp1_NExprType_Ci32);
(*_Le_2)._Fvalue = _Lvalue_0;
(*_Le_2)._Ftype = _Ltype_1;
return _Le_idx_3;
}
_NCp1_NExprI _NCp1_Pexpr_size_of_type_1(_NCp1_NAt _Lat_0) {
struct _NCp1_NExprSizeOfType* _Le_1;
_NCp1_NExprI _Le_idx_2;
_NCp1_Pquick_alloc_one_1(_Le_1);
_Le_idx_2 = _NCp1_Pexpr_push_2(&(*_Le_1)._Fbase, _NCp1_NExprType_Csize_of_type);
(*_Le_1)._Ftype = _Lat_0;
return _Le_idx_2;
}
_NCp1_NExprI _NCp1_Pexpr_null_0() {
struct _NCp1_NExprNull* _Le_0;
_NCp1_NExprI _Le_idx_1;
_NCp1_Pquick_alloc_one_1(_Le_0);
_Le_idx_1 = _NCp1_Pexpr_push_2(&(*_Le_0)._Fbase, _NCp1_NExprType_Cnull);
return _Le_idx_1;
}
void _NCp1_Pdecl_at_begin_enum_3(_NCp1_NId _Lname_0, int32_t _Lrow_1, int32_t _Lcol_2) {
_Gdecl_enum_row = _Lrow_1;
_Gdecl_enum_col = _Lcol_2;
_Gbuild_at = _Gdecl_at;
_NCp1_Pdecl_at_add_2(_Lname_0, _NCp1_NNameType_Cstruct_enum);
_Gdecl_at_v[_Gdecl_at_c++] = _Gdecl_at;
_Gdecl_at = _Gbuild_at;
_Gdecl_enum_at = _Gbuild_at;
_Gdecl_enum_flags = _NCp1_NEnumFlags_C0;
_Gdecl_enum_last_cvar = _NCp1_NCvar_Cnil;
}
void _NCp1_Pdecl_enum_end_3(_NCp1_NAt _Lbase_type_0, int32_t _Lrow_1, int32_t _Lcol_2) {
_NCp1_NEnum _Ls_idx_3;
struct _NCp1_NEnumData* _Ls_5;
_Ls_idx_3 = _Genum_c++;
if(_Genum_cap <= _Genum_c) {
_NCp1_NEnum _Lold_cap_4;
_Lold_cap_4 = _Genum_cap;
_NCp1_Pgrow_2(_Genum_cap, _Genum_c);
_NCp1_Prealloc_3(_Genum_v, _Genum_cap, _Lold_cap_4);
}
_NCp1_Pquick_alloc_one_1(_Ls_5);
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
_Gdecl_enum_last_cvar = _NCp1_NCvar_Cnil;
}
_NCp1_NExprI _NCp1_Pexpr_cvar_2(_NCp1_NAt _Lat_0, _NCp1_NId _Lname_1) {
struct _NCp1_NExprCvar* _Le_2;
_NCp1_NExprI _Le_idx_3;
_NCp1_Pquick_alloc_one_1(_Le_2);
_Le_idx_3 = _NCp1_Pexpr_push_2(&(*_Le_2)._Fbase, _NCp1_NExprType_Ccvar);
(*_Le_2)._Fat = _Lat_0;
(*_Le_2)._Fname = _Lname_1;
return _Le_idx_3;
}
void _NCp1_Penum_add_cvar_3(_NCp1_NId _Lname_0, int32_t _Lrow_1, int32_t _Lcol_2) {
_NCp1_NCvar _Lc_idx_3;
struct _NCp1_NCvarData* _Lc_5;
_Lc_idx_3 = _Gcvar_c++;
_Glast_cvar = _Lc_idx_3;
if(_Gcvar_cap <= _Gcvar_c) {
_NCp1_NCvar _Lold_cap_4;
_Lold_cap_4 = _Gcvar_cap;
_NCp1_Pgrow_2(_Gcvar_cap, _Gcvar_c);
_NCp1_Prealloc_3(_Gcvar_v, _Gcvar_cap, _Lold_cap_4);
}
_Lc_5 = _NCp1_NCvar_Pptr_1(_Lc_idx_3);
(*_Lc_5)._Frow = _Lrow_1;
(*_Lc_5)._Fcol = _Lcol_2;
(*_Lc_5)._Finclude = _Gdecl_include;
(*_Lc_5)._Fat = _Gdecl_at;
(*_Lc_5)._Fdecl._Fname = _Lname_0;
(*_Lc_5)._Fdecl._Ftype = _Gdecl_enum_at;
_NCp1_NTypeInfo_Pinit_1(&(*_Lc_5)._Fdecl._Ftype_info);
(*_Lc_5)._Fflags = _NCp1_NCvarFlags_Cas_enum;
(*_Lc_5)._Flast_cvar = _Gdecl_enum_last_cvar;
_Gdecl_enum_last_cvar = _Lc_idx_3;
}
void _NCp1_Pdecl_add_cvar_3(_NCp1_NId _Lname_0, int32_t _Lrow_1, int32_t _Lcol_2) {
_NCp1_NCvar _Lc_idx_3;
struct _NCp1_NCvarData* _Lc_5;
_Lc_idx_3 = _Gcvar_c++;
_Glast_cvar = _Lc_idx_3;
if(_Gcvar_cap <= _Gcvar_c) {
_NCp1_NCvar _Lold_cap_4;
_Lold_cap_4 = _Gcvar_cap;
_NCp1_Pgrow_2(_Gcvar_cap, _Gcvar_c);
_NCp1_Prealloc_3(_Gcvar_v, _Gcvar_cap, _Lold_cap_4);
}
_Lc_5 = _NCp1_NCvar_Pptr_1(_Lc_idx_3);
(*_Lc_5)._Frow = _Lrow_1;
(*_Lc_5)._Fcol = _Lcol_2;
(*_Lc_5)._Finclude = _Gdecl_include;
(*_Lc_5)._Fat = _Gdecl_at;
_Gdecl_var._Fname = _Lname_0;
_NCp1_NDeclVarData_Pcopy_from_2(&(*_Lc_5)._Fdecl, &_Gdecl_var);
(*_Lc_5)._Fflags = _NCp1_NCvarFlags_C0;
}
void _NCp1_Penum_set_cvar_expr_1(_NCp1_NExprI _Lset_0) {
struct _NCp1_NCvarData* _Lc_1;
_Lc_1 = _NCp1_NCvar_Pptr_1(_Glast_cvar);
(*_Lc_1)._Fflags |= _NCp1_NCvarFlags_Cset_expr;
(*_Lc_1)._Fexpr_set = _Lset_0;
}
void _NCp1_Pstruct_attr_real_name_1(_NCp1_NId _Lname_0) {
if((_Gdecl_struct_flags & _NCp1_NStructFlags_Creal_name) != _NCp1_NStructFlags_C0) {
fprintf(stdout, "%u:%u: error @real-name specified more than once\n", _Glast_row, _Glast_col);
exit(_NStdc_NExit_Cfailure);
}
_Gdecl_struct_flags |= _NCp1_NStructFlags_Creal_name;
_Gdecl_struct_real_name = _Lname_0;
}
void _NCp1_Pstruct_attr_union_0() {
if((_Gdecl_struct_flags & _NCp1_NStructFlags_Cunion) != _NCp1_NStructFlags_C0) {
fprintf(stdout, "%u:%u: error @union specified more than once\n", _Glast_row, _Glast_col);
exit(_NStdc_NExit_Cfailure);
}
_Gdecl_struct_flags |= _NCp1_NStructFlags_Cunion;
}
void _NCp1_Pstruct_attr_no_decl_0() {
if((_Gdecl_struct_flags & _NCp1_NStructFlags_Cno_decl) != _NCp1_NStructFlags_C0) {
fprintf(stdout, "%u:%u: error @no-decl specified more than once\n", _Glast_row, _Glast_col);
exit(_NStdc_NExit_Cfailure);
}
_Gdecl_struct_flags |= _NCp1_NStructFlags_Cno_decl;
}
_NCp1_NExprI _NCp1_Pexpr_str_1(_NCp1_NExprI _Lprev_0) {
int32_t _Llen_1;
struct _NCp1_NExprStrNode* _Ln_2;
_Llen_1 = _Gstring_len;
_NCp1_Pquick_alloc_plus_2(_Ln_2, _Llen_1 + 1);
(*_Ln_2)._Flen = _Llen_1;
memcpy((*_Ln_2)._Fbuf, _Gstring_buf, _Llen_1);
(*_Ln_2)._Fbuf[_Llen_1] = '\0';
(*_Ln_2)._Fnext = NULL;
if(_Lprev_0 == _NCp1_NExprI_Cnil) {
struct _NCp1_NExprStr* _Le_3;
_NCp1_NExprI _Le_idx_4;
_NCp1_Pquick_alloc_one_1(_Le_3);
_Le_idx_4 = _NCp1_Pexpr_push_2(&(*_Le_3)._Fbase, _NCp1_NExprType_Cstr);
(*_Le_3)._Fnode_c = 1;
(*_Le_3)._Ffirst = _Ln_2;
(*_Le_3)._Flast = _Ln_2;
return _Le_idx_4;
} else {
struct _NCp1_NExprStr* _Le_5;
_Le_5 = _NCp1_NExprI_Pptr_1(_Lprev_0);
(*_Le_5)._Fnode_c++;
(*(*_Le_5)._Flast)._Fnext = _Ln_2;
(*_Le_5)._Flast = _Ln_2;
return _Lprev_0;
}
}
_NCp1_NExprI _NCp1_Pexpr_unary_2(_NCp1_NExprI _Lexpr_0, _NCp1_NUnary _Ltype_1) {
struct _NCp1_NExprUnary* _Le_2;
_NCp1_NExprI _Le_idx_3;
_NCp1_Pquick_alloc_one_1(_Le_2);
_Le_idx_3 = _NCp1_Pexpr_push_2(&(*_Le_2)._Fbase, _NCp1_NExprType_Cunary);
(*_Le_2)._Fexpr = _Lexpr_0;
(*_Le_2)._Ftype = _Ltype_1;
return _Le_idx_3;
}
_NCp1_NExprI _NCp1_Pexpr_ref_1(_NCp1_NExprI _Lexpr_0) {
struct _NCp1_NExprRef* _Le_1;
_NCp1_NExprI _Le_idx_2;
_NCp1_Pquick_alloc_one_1(_Le_1);
_Le_idx_2 = _NCp1_Pexpr_push_2(&(*_Le_1)._Fbase, _NCp1_NExprType_Cref);
(*_Le_1)._Fexpr = _Lexpr_0;
return _Le_idx_2;
}
_NCp1_NExprI _NCp1_Pexpr_cast_fast_2(_NCp1_NExprI _Lexpr_0, _NCp1_NAt _Ltype_1) {
struct _NCp1_NExprCastFast* _Le_2;
_NCp1_NExprI _Le_idx_3;
_NCp1_Pquick_alloc_one_1(_Le_2);
_Le_idx_3 = _NCp1_Pexpr_push_2(&(*_Le_2)._Fbase, _NCp1_NExprType_Ccast_fast);
(*_Le_2)._Fexpr = _Lexpr_0;
(*_Le_2)._Ftype = _Ltype_1;
return _Le_idx_3;
}
_NCp1_NExprI _NCp1_Pexpr_index_3(_NCp1_NExprI _Lleft_0, _NCp1_NExprI* _Lright_v_1, int32_t _Lright_c_2) {
_NCp1_NExprI _Le_idx_5;
int32_t _Li_3;
_Li_3 = _Lright_c_2;
for(int i = _Lright_c_2; i > 0; ) {
i --;
struct _NCp1_NExprIndex* _Le_4;
_NCp1_Pquick_alloc_one_1(_Le_4);
_Le_idx_5 = _NCp1_Pexpr_push_2(&(*_Le_4)._Fbase, _NCp1_NExprType_Cindex);
(*_Le_4)._Fleft = _Lleft_0;
(*_Le_4)._Fright = _Lright_v_1[(_Li_3 -= 1)];
continue_0:;
}
break_0:;
return _Le_idx_5;
}
void _NCp1_Penum_base_begin_0() {
_Gdecl_at = (*_NCp1_NAt_Pptr_1(_Gdecl_at))._Fparent;
}
void _NCp1_Pstmt_switch_begin_0() {
_NCp1_Pstmt_space_begin_0();
(*_Gdecl_func_ctx_space)._Fflags |= _NCp1_NStmtSpaceFlags_Cskip_lvar_decl;
}
void _NCp1_Pstmt_switch_set_6(_NCp1_NExprI _Lexpr_0, int32_t _Lbegin_row_1, int32_t _Lbegin_col_2, int32_t _Lend_row_3, int32_t _Lend_col_4, _NCp1_NExprI _Lcases_5) {
struct _NCp1_NStmtSwitch* _Ls_6;
_NCp1_Pquick_alloc_one_1(_Ls_6);
(*_Ls_6)._Fexpr = _Lexpr_0;
(*_Ls_6)._Fcases = _Lcases_5;
_NCp1_Pstmt_push_6(&(*_Ls_6)._Fbase, _Lbegin_row_1, _Lbegin_col_2, _Lend_row_3, _Lend_col_4, _NCp1_NStmtType_Cswitch);
_Gswitch_expr_c = 0;
}
void _NCp1_Pstmt_switch_expr_add_1(_NCp1_NExprI _Lexpr_0) {
uint32_t _Lexpr_i_1;
_Lexpr_i_1 = _Gswitch_expr_c++;
if(_Gswitch_expr_cap <= _Gswitch_expr_c) {
uint32_t _Lold_cap_2;
_Lold_cap_2 = _Gswitch_expr_cap;
_NCp1_Pgrow_2(_Gswitch_expr_cap, _Gswitch_expr_c);
_NCp1_Prealloc_3(_Gswitch_expr_v, _Gswitch_expr_cap, _Lold_cap_2);
}
_Gswitch_expr_v[_Lexpr_i_1] = _Lexpr_0;
}
void _NCp1_Pstmt_switch_case_begin_5(int32_t _Lbegin_row_0, int32_t _Lbegin_col_1, int32_t _Lend_row_2, int32_t _Lend_col_3, bool _Lfall_through_4) {
uint32_t _Lexpr_c_5;
struct _NCp1_NStmtCase* _Ls_6;
_Lexpr_c_5 = _Gswitch_expr_c;
_Gswitch_expr_c = 0;
_NCp1_Pquick_alloc_plus_2(_Ls_6, sizeof(struct _NCp1_NStmtCaseItem) * _Lexpr_c_5);
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
_NCp1_Pstmt_push_6(&(*_Ls_6)._Fbase, _Lbegin_row_0, _Lbegin_col_1, _Lend_row_2, _Lend_col_3, _NCp1_NStmtType_Ccase);
_NCp1_Pstmt_space_begin_0();
}
void _NCp1_Pstmt_switch_case_end_0() {
struct _NCp1_NStmtCaseEnd* _Ls_0;
_NCp1_Pstmt_space_end_0();
_NCp1_Pquick_alloc_one_1(_Ls_0);
_NCp1_Pstmt_push_6(&(*_Ls_0)._Fbase, 0, 0, 0, 0, _NCp1_NStmtType_Ccase_end);
}
void _NCp1_Pstmt_switch_default_begin_5(int32_t _Lbegin_row_0, int32_t _Lbegin_col_1, int32_t _Lend_row_2, int32_t _Lend_col_3, bool _Lfall_through_4) {
struct _NCp1_NStmtDefault* _Ls_5;
_NCp1_Pquick_alloc_one_1(_Ls_5);
(*_Ls_5)._Ffall_through = _Lfall_through_4;
_NCp1_Pstmt_push_6(&(*_Ls_5)._Fbase, _Lbegin_row_0, _Lbegin_col_1, _Lend_row_2, _Lend_col_3, _NCp1_NStmtType_Cdefault);
_NCp1_Pstmt_space_begin_0();
}
void _NCp1_Pstmt_switch_default_end_0() {
struct _NCp1_NStmtDefaultEnd* _Ls_0;
_NCp1_Pstmt_space_end_0();
_NCp1_Pquick_alloc_one_1(_Ls_0);
_NCp1_Pstmt_push_6(&(*_Ls_0)._Fbase, 0, 0, 0, 0, _NCp1_NStmtType_Cdefault_end);
}
void _NCp1_Pstmt_switch_end_0() {
struct _NCp1_NStmtSwitchEnd* _Ls_0;
_NCp1_Pquick_alloc_one_1(_Ls_0);
_NCp1_Pstmt_push_6(&(*_Ls_0)._Fbase, 0, 0, 0, 0, _NCp1_NStmtType_Cswitch_end);
_NCp1_Pstmt_space_end_0();
}
void _NCp1_Pstmt_if_begin_0() {
_NCp1_Pstmt_space_begin_0();
(*_Gdecl_func_ctx_space)._Fflags |= _NCp1_NStmtSpaceFlags_Cskip_lvar_decl;
}
void _NCp1_Pstmt_if_set_6(bool _Lnot_0, _NCp1_NExprI _Lexpr_1, int32_t _Lbegin_row_2, int32_t _Lbegin_col_3, int32_t _Lend_row_4, int32_t _Lend_col_5) {
struct _NCp1_NStmtIf* _Ls_6;
_NCp1_Pquick_alloc_one_1(_Ls_6);
(*_Ls_6)._Fnot = _Lnot_0;
(*_Ls_6)._Fexpr = _Lexpr_1;
_NCp1_Pstmt_push_6(&(*_Ls_6)._Fbase, _Lbegin_row_2, _Lbegin_col_3, _Lend_row_4, _Lend_col_5, _NCp1_NStmtType_Cif);
_NCp1_Pstmt_space_begin_0();
}
void _NCp1_Pstmt_if_end_0() {
_NCp1_Pstmt_space_end_0();
}
void _NCp1_Pstmt_do_begin_0() {
_NCp1_Pstmt_space_begin_0();
(*_Gdecl_func_ctx_space)._Fflags |= _NCp1_NStmtSpaceFlags_Cskip_lvar_decl;
}
void _NCp1_Pstmt_do_set_6(_NCp1_NExprI _Lexpr_0, int32_t _Lbegin_row_1, int32_t _Lbegin_col_2, int32_t _Lend_row_3, int32_t _Lend_col_4, struct _NCp1_NStmtSpace* _Lcontinu_5) {
struct _NCp1_NStmtDo* _Ls_6;
_NCp1_Pquick_alloc_one_1(_Ls_6);
_Gnest_stack_id_v[_Gnest_stack_c] = _Gnest_id++;
_Gnest_stack_ptr_v[_Gnest_stack_c]._Fdo = _Ls_6;
_Gnest_stack_c++;
(*_Ls_6)._Fexpr = _Lexpr_0;
(*_Ls_6)._Fcontinu = _Lcontinu_5;
_NCp1_Pstmt_push_6(&(*_Ls_6)._Fbase, _Lbegin_row_1, _Lbegin_col_2, _Lend_row_3, _Lend_col_4, _NCp1_NStmtType_Cdo);
_NCp1_Pstmt_space_begin_0();
}
void _NCp1_Pstmt_do_end_0() {
struct _NCp1_NStmtDoEnd* _Ls_0;
_Gnest_stack_c -= 1;
_NCp1_Pstmt_space_end_0();
_NCp1_Pquick_alloc_one_1(_Ls_0);
_NCp1_Pstmt_push_6(&(*_Ls_0)._Fbase, 0, 0, 0, 0, _NCp1_NStmtType_Cdo_end);
_NCp1_Pstmt_space_end_0();
}
void _NCp1_Pstmt_while_begin_0() {
_NCp1_Pstmt_space_begin_0();
(*_Gdecl_func_ctx_space)._Fflags |= _NCp1_NStmtSpaceFlags_Cskip_lvar_decl;
}
void _NCp1_Pstmt_while_set_6(_NCp1_NExprI _Lexpr_0, int32_t _Lbegin_row_1, int32_t _Lbegin_col_2, int32_t _Lend_row_3, int32_t _Lend_col_4, struct _NCp1_NStmtSpace* _Lcontinu_5) {
struct _NCp1_NStmtWhile* _Ls_6;
_NCp1_Pquick_alloc_one_1(_Ls_6);
_Gnest_stack_id_v[_Gnest_stack_c] = _Gnest_id++;
_Gnest_stack_ptr_v[_Gnest_stack_c]._Fwhil = _Ls_6;
_Gnest_stack_c++;
(*_Ls_6)._Fexpr = _Lexpr_0;
(*_Ls_6)._Fcontinu = _Lcontinu_5;
_NCp1_Pstmt_push_6(&(*_Ls_6)._Fbase, _Lbegin_row_1, _Lbegin_col_2, _Lend_row_3, _Lend_col_4, _NCp1_NStmtType_Cwhile);
_NCp1_Pstmt_space_begin_0();
}
void _NCp1_Pstmt_while_end_0() {
struct _NCp1_NStmtWhileEnd* _Ls_0;
_Gnest_stack_c -= 1;
_NCp1_Pstmt_space_end_0();
_NCp1_Pquick_alloc_one_1(_Ls_0);
_NCp1_Pstmt_push_6(&(*_Ls_0)._Fbase, 0, 0, 0, 0, _NCp1_NStmtType_Cwhile_end);
_NCp1_Pstmt_space_end_0();
}
void _NCp1_Pstmt_elif_begin_0() {
}
void _NCp1_Pstmt_elif_set_6(bool _Lnot_0, _NCp1_NExprI _Lexpr_1, int32_t _Lbegin_row_2, int32_t _Lbegin_col_3, int32_t _Lend_row_4, int32_t _Lend_col_5) {
struct _NCp1_NStmtIf* _Ls_6;
_NCp1_Pquick_alloc_one_1(_Ls_6);
(*_Ls_6)._Fnot = _Lnot_0;
(*_Ls_6)._Fexpr = _Lexpr_1;
_NCp1_Pstmt_push_6(&(*_Ls_6)._Fbase, _Lbegin_row_2, _Lbegin_col_3, _Lend_row_4, _Lend_col_5, _NCp1_NStmtType_Cif_elif);
_NCp1_Pstmt_space_begin_0();
}
void _NCp1_Pstmt_elif_end_0() {
_NCp1_Pstmt_space_end_0();
}
void _NCp1_Pstmt_else_set_0() {
struct _NCp1_NStmtIfElse* _Ls_0;
_NCp1_Pquick_alloc_one_1(_Ls_0);
_NCp1_Pstmt_push_6(&(*_Ls_0)._Fbase, 0, 0, 0, 0, _NCp1_NStmtType_Cif_else);
_NCp1_Pstmt_space_begin_0();
}
void _NCp1_Pstmt_else_end_0() {
_NCp1_Pstmt_space_end_0();
}
void _NCp1_Pstmt_if_end_ifs_0() {
struct _NCp1_NStmtIfEnd* _Ls_0;
_NCp1_Pquick_alloc_one_1(_Ls_0);
_NCp1_Pstmt_push_6(&(*_Ls_0)._Fbase, 0, 0, 0, 0, _NCp1_NStmtType_Cif_end);
_NCp1_Pstmt_space_end_0();
}
struct _NCp1_NStmtSpace* _NCp1_Pstmt_space_begin_0() {
return _NCp1_Pstmt_space_begin_1(true);
}
struct _NCp1_NStmtSpace* _NCp1_Pstmt_space_begin_detach_0() {
return _NCp1_Pstmt_space_begin_1(false);
}
struct _NCp1_NStmtSpace* _NCp1_Pstmt_space_end_0() {
struct _NCp1_NStmtSpace* _Lret_0;
_Lret_0 = _Gdecl_func_ctx_space;
_Gdecl_func_ctx_space = (*_Gdecl_func_ctx_space)._Fparent;
return _Lret_0;
}
_NCp1_NExprI _NCp1_Pexpr_compare_3(_NCp1_NExprI _Lleft_0, _NCp1_NExprI _Lright_1, _NCp1_NCompare _Ltype_2) {
struct _NCp1_NExprCompare* _Le_3;
_NCp1_NExprI _Le_idx_4;
_NCp1_Pquick_alloc_one_1(_Le_3);
_Le_idx_4 = _NCp1_Pexpr_push_2(&(*_Le_3)._Fbase, _NCp1_NExprType_Ccompare);
(*_Le_3)._Fleft = _Lleft_0;
(*_Le_3)._Fright = _Lright_1;
(*_Le_3)._Ftype = _Ltype_2;
return _Le_idx_4;
}
_NCp1_NExprI _NCp1_Pexpr_bool_1(bool _Lvalue_0) {
struct _NCp1_NExprBool* _Le_1;
_NCp1_NExprI _Le_idx_2;
_NCp1_Pquick_alloc_one_1(_Le_1);
_Le_idx_2 = _NCp1_Pexpr_push_2(&(*_Le_1)._Fbase, _NCp1_NExprType_Cbool);
(*_Le_1)._Fvalue = _Lvalue_0;
return _Le_idx_2;
}
_NCp1_NExprI _NCp1_Pexpr_char_1(int32_t _Lvalue_0) {
struct _NCp1_NExprChar* _Le_1;
_NCp1_NExprI _Le_idx_2;
_NCp1_Pquick_alloc_one_1(_Le_1);
_Le_idx_2 = _NCp1_Pexpr_push_2(&(*_Le_1)._Fbase, _NCp1_NExprType_Cchar);
(*_Le_1)._Fvalue = _Lvalue_0;
return _Le_idx_2;
}
void _NCp1_Pcvar_attr_real_name_1(_NCp1_NId _Lname_0) {
struct _NCp1_NCvarData* _Lc_1;
_Lc_1 = _NCp1_NCvar_Pptr_1(_Glast_cvar);
(*_Lc_1)._Fdecl._Fflags |= _NCp1_NVarFlags_Creal_name;
(*_Lc_1)._Fdecl._Freal_name = _Lname_0;
}
void _NCp1_Pcvar_attr_no_decl_0() {
struct _NCp1_NCvarData* _Lc_0;
_Lc_0 = _NCp1_NCvar_Pptr_1(_Glast_cvar);
(*_Lc_0)._Fdecl._Fflags |= _NCp1_NVarFlags_Cno_decl;
}
void _NCp1_NAt_Pput_to_header_1(_NCp1_NAt _Lat_0) {
if((_Gat_in_header_v[(_Lat_0 >> 3)] & (1 << (_Lat_0 & 7))) == 0) {
_Gat_in_header_v[(_Lat_0 >> 3)] |= (1 << (_Lat_0 & 7));
_Gat_in_header_idx_v[_Lat_0] = _Gat_in_header_c;
_Gat_in_header_at_v[_Gat_in_header_c++] = _Lat_0;
if(((_Lat_0 != _NCp1_NAt_Croot) && (_Lat_0 != _NCp1_NAt_Crelative))) {
_NCp1_NAt_Pput_to_header_1((*_NCp1_NAt_Pptr_1(_Lat_0))._Fparent);
}
}
}
inline void _NCp1_NInclude_Pwr_2(_NCp1_NInclude _Li_0, union _NCp1_NWtr* _Lw_1) {
Fputnum(_Lw_1, _Li_0 + 1);
}
void _NCp1_NDeclVarData_Pwr_3(struct _NCp1_NDeclVarData* _Lvd_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2) {
_NCp1_NId_Pwr_3((*_Lvd_0)._Fname, _Lw_1, _Lheader_2);
_NCp1_NAt_Pwr_3((*_Lvd_0)._Ftype, _Lw_1, _Lheader_2);
_NCp1_NVarFlags_Pwr_2((*_Lvd_0)._Fflags, _Lw_1);
if(((*_Lvd_0)._Fflags & _NCp1_NVarFlags_Creal_name) != _NCp1_NVarFlags_C0) {
_NCp1_NId_Pwr_3((*_Lvd_0)._Freal_name, _Lw_1, _Lheader_2);
}
_NCp1_NTypeInfo_Pwr_2(&(*_Lvd_0)._Ftype_info, _Lw_1);
_NCp1_NWtr_Pn1_2(_Lw_1, (*_Lvd_0)._Fsize_c);
int32_t _Li_3;
_Li_3 = 0;
for(int i = (*_Lvd_0)._Fsize_c; i > 0; ) {
i --;
_NCp1_NExprI_Pwr_3((*_Lvd_0)._Fsize_expr_v[_Li_3], _Lw_1, _Lheader_2);
continue_0:;
_Li_3++;
}
break_0:;
}
inline void _NCp1_NCvarFlags_Pwr_2(_NCp1_NCvarFlags _Lf_0, union _NCp1_NWtr* _Lw_1) {
_NCp1_NWtr_Pn1_2(_Lw_1, _Lf_0);
}
void _NCp1_NExprI_Pwr_3(_NCp1_NExprI _Le_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2) {
if(_NCp1_Cdebug_rd_wr) {
_NCp1_NWtr_Pn1_2(_Lw_1, 255);
}
if(_Le_0 == _NCp1_NExprI_Cnil) {
_NCp1_NExprType_Pwr_2(_NCp1_NExprType_Cnil, _Lw_1);
} else {
struct _NCp1_NExpr* _Lexpr_3;
_Lexpr_3 = _NCp1_NExprI_Pptr_1(_Le_0);
_NCp1_NExprType_Pwr_2((*_Lexpr_3)._Ftype, _Lw_1);
switch((*_Lexpr_3)._Ftype) {
case _NCp1_NExprType_Cmath:;
_NCp1_NExprI_Pwr_math_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _NCp1_NExprType_Cbools:;
_NCp1_NExprI_Pwr_bools_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _NCp1_NExprType_Cstr:;
_NCp1_NExprI_Pwr_str_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _NCp1_NExprType_Ccvar:;
_NCp1_NExprI_Pwr_cvar_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _NCp1_NExprType_Cunary:;
_NCp1_NExprI_Pwr_unary_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _NCp1_NExprType_Cref:;
_NCp1_NExprI_Pwr_ref_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _NCp1_NExprType_Ccast_fast:;
_NCp1_NExprI_Pwr_cast_fast_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _NCp1_NExprType_Cindex:;
_NCp1_NExprI_Pwr_index_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _NCp1_NExprType_Ccompare:;
_NCp1_NExprI_Pwr_compare_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _NCp1_NExprType_Cbool:;
_NCp1_NExprI_Pwr_bool_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _NCp1_NExprType_Cchar:;
_NCp1_NExprI_Pwr_char_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _NCp1_NExprType_Cmethod:;
_NCp1_NExprI_Pwr_method_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _NCp1_NExprType_Cfunc:;
_NCp1_NExprI_Pwr_func_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _NCp1_NExprType_Cnull:;
_NCp1_NExprI_Pwr_null_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _NCp1_NExprType_Ci32:;
_NCp1_NExprI_Pwr_i32_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _NCp1_NExprType_Csize_of_type:;
_NCp1_NExprI_Pwr_size_of_type_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _NCp1_NExprType_Cassign:;
_NCp1_NExprI_Pwr_assign_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _NCp1_NExprType_Cfvar:;
_NCp1_NExprI_Pwr_fvar_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _NCp1_NExprType_Cgvar:;
_NCp1_NExprI_Pwr_gvar_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
case _NCp1_NExprType_Clvar:;
_NCp1_NExprI_Pwr_lvar_3(_Lexpr_3, _Lw_1, _Lheader_2);
break;
default:;
fprintf(stdout, "wr() was not implemented in expression #%s\n", _NCp1_NExprType_Pcp1_name_1((*_Lexpr_3)._Ftype));
exit(_NStdc_NExit_Cfailure);
break;
}
}
if(_NCp1_Cdebug_rd_wr) {
_NCp1_NWtr_Pn1_2(_Lw_1, 255);
}
}
inline void _NCp1_NCvar_Pwr_2(_NCp1_NCvar _Lg_0, union _NCp1_NWtr* _Lw_1) {
Fputnum(_Lw_1, _Lg_0 + 1);
}
inline void _NCp1_NEnumFlags_Pwr_2(_NCp1_NEnumFlags _Le_0, union _NCp1_NWtr* _Lw_1) {
_NCp1_NWtr_Pn1_2(_Lw_1, _Le_0);
}
inline void _NCp1_NStructFlags_Pwr_2(_NCp1_NStructFlags _Lf_0, union _NCp1_NWtr* _Lw_1) {
_NCp1_NWtr_Pn1_2(_Lw_1, _Lf_0);
}
void _NCp1_NFvarData_Pwr_3(struct _NCp1_NFvarData* _Lf_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2) {
_NCp1_NDeclVarData_Pwr_3(&(*_Lf_0)._Fdecl, _Lw_1, _Lheader_2);
}
void _NCp1_NFarg_Pwr_3(struct _NCp1_NFarg* _Lf_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2) {
_NCp1_NDeclVarData_Pwr_3(&(*_Lf_0)._Fdecl, _Lw_1, _Lheader_2);
}
inline void _NCp1_NFuncFlags_Pwr_2(_NCp1_NFuncFlags _Le_0, union _NCp1_NWtr* _Lw_1) {
Fputnum(_Lw_1, _Le_0);
}
inline void _NCp1_NFunc_Pwr_2(_NCp1_NFunc _Lf_0, union _NCp1_NWtr* _Lw_1) {
Fputnum(_Lw_1, _Lf_0 + _NCp1_NFunc_C1);
}
void _NCp1_NDeclFunc_Plvars_wr_3(struct _NCp1_NDeclFunc* _Lf_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2) {
Fputnum(_Lw_1, (*_Lf_0)._Flvar_c);
int32_t _Li_3;
_Li_3 = 0;
for(int i = (*_Lf_0)._Flvar_c; i > 0; ) {
i --;
struct _NCp1_NLvarData* _Ll_4;
_Ll_4 = (*_Lf_0)._Flvar_v[_Li_3];
Fputnum(_Lw_1, (*_Ll_4)._Frow);
Fputnum(_Lw_1, (*_Ll_4)._Fcol);
_NCp1_NDeclVarData_Pwr_3(&(*_Ll_4)._Fdecl, _Lw_1, _Lheader_2);
_NCp1_NLvarFlags_Pwr_2((*_Ll_4)._Fflags, _Lw_1);
if(((*_Ll_4)._Fflags & _NCp1_NLvarFlags_Cset_expr) != _NCp1_NLvarFlags_C0) {
_NCp1_NExprI_Pwr_3((*_Ll_4)._Fset_expr, _Lw_1, _Lheader_2);
}
continue_0:;
_Li_3++;
}
break_0:;
}
void _NCp1_NStmtSpace_Pwr_3(struct _NCp1_NStmtSpace* _Lspace_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2) {
struct _NCp1_NStmt* _Lstmt_4;
Fputnum(_Lw_1, (*_Lspace_0)._Flvar_c);
int32_t _Li_3;
_Li_3 = 0;
for(int i = (*_Lspace_0)._Flvar_c; i > 0; ) {
i --;
_NCp1_NLvar_Pwr_2((*_Lspace_0)._Flvar_v[_Li_3], _Lw_1);
continue_0:;
_Li_3++;
}
break_0:;
_Lstmt_4 = (*_Lspace_0)._Fstmt_first;
while(_Lstmt_4 != NULL) {
_NCp1_NStmtType_Pwr_2((*_Lstmt_4)._Ftype, _Lw_1);
if(_NCp1_Cdebug_rd_wr) {
_NCp1_NWtr_Pn1_2(_Lw_1, 255);
}
Fputnum(_Lw_1, (*_Lstmt_4)._Fbegin_row);
Fputnum(_Lw_1, (*_Lstmt_4)._Fbegin_col);
Fputnum(_Lw_1, (*_Lstmt_4)._Fend_row);
Fputnum(_Lw_1, (*_Lstmt_4)._Fend_col);
switch((*_Lstmt_4)._Ftype) {
case _NCp1_NStmtType_Cbreak:;
_NCp1_NStmtSpace_Pwr_break_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _NCp1_NStmtType_Cswitch:;
_NCp1_NStmtSpace_Pwr_switch_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _NCp1_NStmtType_Ccase:;
_NCp1_NStmtSpace_Pwr_case_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _NCp1_NStmtType_Ccase_end:;
_NCp1_NStmtSpace_Pwr_case_end_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _NCp1_NStmtType_Cdefault:;
_NCp1_NStmtSpace_Pwr_default_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _NCp1_NStmtType_Cdefault_end:;
_NCp1_NStmtSpace_Pwr_default_end_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _NCp1_NStmtType_Cswitch_end:;
_NCp1_NStmtSpace_Pwr_switch_end_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _NCp1_NStmtType_Cif:;
_NCp1_NStmtSpace_Pwr_if_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _NCp1_NStmtType_Cif_elif:;
_NCp1_NStmtSpace_Pwr_if_elif_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _NCp1_NStmtType_Cif_else:;
_NCp1_NStmtSpace_Pwr_if_else_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _NCp1_NStmtType_Cif_end:;
_NCp1_NStmtSpace_Pwr_if_end_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _NCp1_NStmtType_Cdo:;
_NCp1_NStmtSpace_Pwr_do_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _NCp1_NStmtType_Cdo_end:;
_NCp1_NStmtSpace_Pwr_do_end_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _NCp1_NStmtType_Cwhile:;
_NCp1_NStmtSpace_Pwr_while_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _NCp1_NStmtType_Cwhile_end:;
_NCp1_NStmtSpace_Pwr_while_end_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _NCp1_NStmtType_Ccontinue:;
_NCp1_NStmtSpace_Pwr_continue_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _NCp1_NStmtType_Creturn:;
_NCp1_NStmtSpace_Pwr_return_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _NCp1_NStmtType_Cspace:;
_NCp1_NStmtSpace_Pwr_space_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
case _NCp1_NStmtType_Cexpr:;
_NCp1_NStmtSpace_Pwr_expr_3(_Lstmt_4, _Lw_1, _Lheader_2);
break;
default:;
fprintf(stdout, "wr() not yet implemented in stmt #%s\n", _NCp1_NStmtType_Pcp1_name_1((*_Lstmt_4)._Ftype));
exit(_NStdc_NExit_Cfailure);
break;
}
if(_NCp1_Cdebug_rd_wr) {
_NCp1_NWtr_Pn1_2(_Lw_1, 255);
}
_Lstmt_4 = (*_Lstmt_4)._Fstmt_next;
continue_1:;
}
break_1:;
_NCp1_NStmtType_Pwr_2(_NCp1_NStmtType_Cnil, _Lw_1);
}
inline void _NCp1_NWtr_Pn4_2(union _NCp1_NWtr* _Lw_0, uint32_t _Ln_1) {
(*_Lw_0)._Fp1[0] = _Ln_1;
(*_Lw_0)._Fp1[1] = (_Ln_1 >> 8);
(*_Lw_0)._Fp1[2] = (_Ln_1 >> 16);
(*_Lw_0)._Fp1[3] = (_Ln_1 >> 24);
(*_Lw_0)._Fpos += 4;
}
void _NCp1_NDeclVarData_Pcopy_from_2(struct _NCp1_NDeclVarData* _Lvd_0, struct _NCp1_NDeclVarData* _Lsrc_1) {
(*_Lvd_0)._Fname = (*_Lsrc_1)._Fname;
(*_Lvd_0)._Ftype = (*_Lsrc_1)._Ftype;
(*_Lvd_0)._Fflags = (*_Lsrc_1)._Fflags;
(*_Lvd_0)._Freal_name = (*_Lsrc_1)._Freal_name;
_NCp1_NTypeInfo_Pcopy_from_2(&(*_Lvd_0)._Ftype_info, &(*_Lsrc_1)._Ftype_info);
(*_Lvd_0)._Ftype_info._Fbuilt_in = (*_Lsrc_1)._Ftype_info._Fbuilt_in;
(*_Lvd_0)._Fsize_c = (*_Lsrc_1)._Fsize_c;
if((*_Lvd_0)._Fsize_c > 0) {
_NCp1_Pquick_alloc_arr_2((*_Lvd_0)._Fsize_expr_v, (*_Lvd_0)._Fsize_c);
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
void _NCp1_NFarg_Pcopy_from_2(struct _NCp1_NFarg* _Lf_0, struct _NCp1_NFarg* _Lsrc_1) {
(*_Lf_0)._Frow = (*_Lsrc_1)._Frow;
(*_Lf_0)._Fcol = (*_Lsrc_1)._Fcol;
_NCp1_NDeclVarData_Pcopy_from_2(&(*_Lf_0)._Fdecl, &(*_Lsrc_1)._Fdecl);
}
inline uint8_t _NCp1_NId_Plen_1(_NCp1_NId _Lid_0) {
return _Gid_len_v[_Lid_0];
}
inline char* _NCp1_NId_Pstr_1(_NCp1_NId _Lid_0) {
return _Gid_str_v[_Lid_0];
}
inline struct _NCp1_NDeclFunc* _NCp1_NFunc_Pptr_1(_NCp1_NFunc _Lf_0) {
return _Gfunc_v[_Lf_0];
}
_NCp1_NLvar _NCp1_NStmtSpace_Plvar_new_4(struct _NCp1_NStmtSpace* _Lspace_0, _NCp1_NId _Lname_1, int32_t _Lrow_2, int32_t _Lcol_3) {
_NCp1_NLvar* _Lv_4;
int32_t _Li_7;
struct _NCp1_NDeclFunc* _Lf_9;
_NCp1_NLvar _Llvar_10;
struct _NCp1_NLvarData* _Litem_12;
_Lv_4 = (*_Lspace_0)._Flvar_v;
int32_t _Li_5;
_Li_5 = 0;
for(int i = (*_Lspace_0)._Flvar_c; i > 0; ) {
i --;
struct _NCp1_NLvarData* _Llvar_6;
_Llvar_6 = _NCp1_NLvar_Pptr_1(_Lv_4[_Li_5]);
if((*_Llvar_6)._Fdecl._Fname == _Lname_1) {
fprintf(stdout, "%u:%u: lvar '%s' was already declared at %u:%u\n", _Lrow_2, _Lcol_3, _NCp1_NId_Pstr_1(_Lname_1), (*_Llvar_6)._Frow, (*_Llvar_6)._Fcol);
exit(_NStdc_NExit_Cfailure);
}
continue_0:;
_Li_5++;
}
break_0:;
_Li_7 = (*_Lspace_0)._Flvar_c++;
if((*_Lspace_0)._Flvar_cap <= (*_Lspace_0)._Flvar_c) {
int32_t _Lold_cap_8;
_Lold_cap_8 = (*_Lspace_0)._Flvar_cap;
_NCp1_Pgrow_2((*_Lspace_0)._Flvar_cap, (*_Lspace_0)._Flvar_c);
_NCp1_Prealloc_3((*_Lspace_0)._Flvar_v, (*_Lspace_0)._Flvar_cap, _Lold_cap_8);
}
_Lf_9 = _Gctx_func;
_Llvar_10 = (*_Lf_9)._Flvar_c++;
(*_Lspace_0)._Flvar_v[_Li_7] = _Llvar_10;
if((*_Lf_9)._Flvar_cap <= (*_Lf_9)._Flvar_c) {
_NCp1_NLvar _Lold_cap_11;
_Lold_cap_11 = (*_Lf_9)._Flvar_cap;
_NCp1_Pgrow_2((*_Lf_9)._Flvar_cap, (*_Lf_9)._Flvar_c);
_NCp1_Prealloc_3((*_Lf_9)._Flvar_v, (*_Lf_9)._Flvar_cap, _Lold_cap_11);
}
_NCp1_Pquick_alloc_one_1(_Litem_12);
(*_Lf_9)._Flvar_v[_Llvar_10] = _Litem_12;
(*_Litem_12)._Frow = _Lrow_2;
(*_Litem_12)._Fcol = _Lcol_3;
(*_Litem_12)._Fdecl._Fname = _Lname_1;
return _Llvar_10;
}
inline struct _NCp1_NLvarData* _NCp1_NLvar_Pptr_1(_NCp1_NLvar _Ll_0) {
return (*_Gctx_func)._Flvar_v[_Ll_0];
}
void _NCp1_NTypeInfo_Pinit_1(struct _NCp1_NTypeInfo* _Lti_0) {
(*_Lti_0)._Fref_v[0] = 0;
(*_Lti_0)._Farray_c = 0;
(*_Lti_0)._Fstar_c = 0;
(*_Lti_0)._Fbuilt_in = false;
(*_Lti_0)._Fconst = false;
}
_NCp1_NExprI _NCp1_Pexpr_push_2(struct _NCp1_NExpr* _Le_0, _NCp1_NExprType _Ltype_1) {
int32_t _Le_idx_2;
(*_Le_0)._Ftype = _Ltype_1;
_Le_idx_2 = _Gexpr_c++;
if(_Gexpr_cap <= _Gexpr_c) {
int32_t _Lold_cap_3;
_Lold_cap_3 = _Gexpr_cap;
_NCp1_Pgrow_2(_Gexpr_cap, _Gexpr_c);
_NCp1_Prealloc_3(_Gexpr_v, _Gexpr_cap, _Lold_cap_3);
}
_Gexpr_v[_Le_idx_2] = _Le_0;
return _Le_idx_2;
}
inline struct _NCp1_NExpr* _NCp1_NExprI_Pptr_1(_NCp1_NExprI _Le_0) {
return _Gexpr_v[_Le_0];
}
void _NCp1_Pstmt_push_6(struct _NCp1_NStmt* _Ls_0, int32_t _Lbegin_row_1, int32_t _Lbegin_col_2, int32_t _Lend_row_3, int32_t _Lend_col_4, _NCp1_NStmtType _Ltype_5) {
(*_Ls_0)._Fbegin_row = _Lbegin_row_1;
(*_Ls_0)._Fbegin_col = _Lbegin_col_2;
(*_Ls_0)._Fend_row = _Lend_row_3;
(*_Ls_0)._Fend_col = _Lend_col_4;
(*_Ls_0)._Ftype = _Ltype_5;
_NCp1_Pfunc_stmt_add_1(_Ls_0);
}
inline _NCp1_NId _NCp1_NLvar_Pname_1(_NCp1_NLvar _Ll_0) {
return (*_NCp1_NLvar_Pptr_1(_Ll_0))._Fdecl._Fname;
}
inline struct _NCp1_NAtData* _NCp1_NAt_Pptr_1(_NCp1_NAt _Li_0) {
return &_Gat_v[_Li_0];
}
_NCp1_NAt _NCp1_Pat_create_basic_1(_NCp1_NBasicTypeId _Lbasic_0) {
_NCp1_NAt _Lbuild_idx_3;
struct _NCp1_NAtData* _Lat_5;
_NCp1_NAt _Li_1;
_Li_1 = (_NCp1_NAt)(0);
for(int i = _Gat_c; i > 0; ) {
i --;
struct _NCp1_NAtData* _Lat_2;
_Lat_2 = (&_Gat_v[_Li_1]);
if((((*_Lat_2)._Ftype == _NCp1_NNameType_Cbasic) && ((*_Lat_2)._Fname._Fbasic == _Lbasic_0))) {
return _Li_1;
}
continue_0:;
_Li_1++;
}
break_0:;
_Lbuild_idx_3 = _Gat_c++;
if(_Gat_cap <= _Gat_c) {
_NCp1_NAt _Lold_cap_4;
_Lold_cap_4 = _Gat_cap;
_NCp1_Pgrow_2(_Gat_cap, _Gat_c);
_NCp1_Prealloc_3(_Gat_v, _Gat_cap, _Lold_cap_4);
}
_Lat_5 = (&_Gat_v[_Lbuild_idx_3]);
(*_Lat_5)._Fparent = _NCp1_NAt_Croot;
(*_Lat_5)._Ftype = _NCp1_NNameType_Cbasic;
(*_Lat_5)._Fname._Fbasic = _Lbasic_0;
return _Lbuild_idx_3;
}
_NCp1_NAt _NCp1_Pat_create_3(_NCp1_NAt _Lparent_0, _NCp1_NNameType _Ltype_1, _NCp1_NId _Lname_2) {
int32_t _Lfound_3;
_NCp1_NAt _Lbuild_idx_4;
struct _NCp1_NAtData* _Lat_6;
_Lfound_3 = _NCp1_NAtMap_Pget_or_insert_5(&_Gat_map, _Lparent_0, _Ltype_1, _Lname_2, _Gat_c);
if(_Lfound_3 != -1) {
return _Lfound_3;
}
_Lbuild_idx_4 = _Gat_c++;
if(_Gat_cap <= _Gat_c) {
_NCp1_NAt _Lold_cap_5;
_Lold_cap_5 = _Gat_cap;
_NCp1_Pgrow_2(_Gat_cap, _Gat_c);
_NCp1_Prealloc_3(_Gat_v, _Gat_cap, _Lold_cap_5);
}
_Lat_6 = (&_Gat_v[_Lbuild_idx_4]);
(*_Lat_6)._Fparent = _Lparent_0;
(*_Lat_6)._Ftype = _Ltype_1;
(*_Lat_6)._Fname._Fid = _Lname_2;
return _Lbuild_idx_4;
}
void _NCp1_Ptype_info_arr_1(_NCp1_NExprI _Lexpr_0) {
struct _NCp1_NTypeInfo* _Lti_1;
_Lti_1 = (&_Gdecl_var._Ftype_info);
(*_Lti_1)._Farray_c += 1;
(*_Lti_1)._Fref_v[(*_Lti_1)._Farray_c] = 0;
if(_Lexpr_0 != _NCp1_NExprI_Cnil) {
struct _NCp1_NDeclVarData* _Lvd_2;
_Lvd_2 = (&_Gdecl_var);
if((*_Lvd_2)._Fsize_c == 0) {
_NCp1_Pquick_alloc_arr_2((*_Lvd_2)._Fsize_expr_v, _NCp1_Cdecl_var_size_limit);
}
(*_Lvd_2)._Fsize_expr_v[(*_Lvd_2)._Fsize_c++] = _Lexpr_0;
}
}
void _NCp1_NTypeInfo_Pfinalize_1(struct _NCp1_NTypeInfo* _Lti_0) {
int8_t _Lref_v_1[_NCp1_Ctype_info_star_limit];
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
inline struct _NCp1_NCvarData* _NCp1_NCvar_Pptr_1(_NCp1_NCvar _Lc_0) {
return &_Gcvar_v[_Lc_0];
}
struct _NCp1_NStmtSpace* _NCp1_Pstmt_space_begin_1(bool _Lattach_0) {
struct _NCp1_NStmtSpace* _Lparent_1;
struct _NCp1_NStmtSpace* _Lspace_2;
_Lparent_1 = _Gdecl_func_ctx_space;
_NCp1_Pquick_alloc_one_1(_Gdecl_func_ctx_space);
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
inline void _NCp1_NVarFlags_Pwr_2(_NCp1_NVarFlags _Lf_0, union _NCp1_NWtr* _Lw_1) {
Fputnum(_Lw_1, _Lf_0);
}
void _NCp1_NTypeInfo_Pwr_2(struct _NCp1_NTypeInfo* _Lti_0, union _NCp1_NWtr* _Lw_1) {
int32_t _Lc_2;
_Lc_2 = 0;
for(int i = _NCp1_Ctype_info_star_limit; i > 0; ) {
i --;
if((*_Lti_0)._Fref_v[_Lc_2] == 0) {
goto break_0;
}
_Lc_2++;
continue_0:;
}
break_0:;
_NCp1_NWtr_Pn1_2(_Lw_1, _Lc_2);
int32_t _Li_3;
_Li_3 = 0;
for(int i = _Lc_2; i > 0; ) {
i --;
_NCp1_NWtr_Pn1_2(_Lw_1, (*_Lti_0)._Fref_v[_Li_3]);
continue_1:;
_Li_3++;
}
break_1:;
_NCp1_NWtr_Pn1_2(_Lw_1, (*_Lti_0)._Farray_c);
_NCp1_NWtr_Pn1_2(_Lw_1, (*_Lti_0)._Fstar_c);
_NCp1_NWtr_Pb_2(_Lw_1, (*_Lti_0)._Fbuilt_in);
_NCp1_NWtr_Pb_2(_Lw_1, (*_Lti_0)._Fconst);
}
inline void _NCp1_NExprType_Pwr_2(_NCp1_NExprType _Le_0, union _NCp1_NWtr* _Lw_1) {
_NCp1_NWtr_Pn1_2(_Lw_1, _Le_0);
}
inline void _NCp1_NExprI_Pwr_math_3(struct _NCp1_NExpr* _Lexpr_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2) {
struct _NCp1_NExprMath* _Le_3;
_Le_3 = _Lexpr_0;
_NCp1_NExprI_Pwr_3((*_Le_3)._Fleft, _Lw_1, _Lheader_2);
_NCp1_NExprI_Pwr_3((*_Le_3)._Fright, _Lw_1, _Lheader_2);
_NCp1_NMath_Pwr_2((*_Le_3)._Ftype, _Lw_1);
_NCp1_NWtr_Pn1_2(_Lw_1, (*_Le_3)._Fitem_c);
int32_t _Li_4;
_Li_4 = 0;
for(int i = (*_Le_3)._Fitem_c; i > 0; ) {
i --;
_NCp1_NExprI_Pwr_3((*_Le_3)._Fitem_v[_Li_4]._Fexpr, _Lw_1, _Lheader_2);
continue_0:;
_Li_4++;
}
break_0:;
}
inline void _NCp1_NExprI_Pwr_bools_3(struct _NCp1_NExpr* _Lexpr_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2) {
struct _NCp1_NExprBools* _Le_3;
_Le_3 = _Lexpr_0;
_NCp1_NExprI_Pwr_3((*_Le_3)._Fleft, _Lw_1, _Lheader_2);
_NCp1_NExprI_Pwr_3((*_Le_3)._Fright, _Lw_1, _Lheader_2);
_NCp1_NWtr_Pn1_2(_Lw_1, (*_Le_3)._Fitem_c);
int32_t _Li_4;
_Li_4 = 0;
for(int i = (*_Le_3)._Fitem_c; i > 0; ) {
i --;
_NCp1_NExprI_Pwr_3((*_Le_3)._Fitem_v[_Li_4]._Fexpr, _Lw_1, _Lheader_2);
continue_0:;
_Li_4++;
}
break_0:;
_NCp1_NBools_Pwr_2((*_Le_3)._Ftype, _Lw_1);
}
inline void _NCp1_NExprI_Pwr_str_3(struct _NCp1_NExpr* _Lexpr_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2) {
struct _NCp1_NExprStr* _Le_3;
struct _NCp1_NExprStrNode* _Ln_4;
_Le_3 = _Lexpr_0;
Fputnum(_Lw_1, (*_Le_3)._Fnode_c);
_Ln_4 = (*_Le_3)._Ffirst;
while(1) {
Fputnum(_Lw_1, (*_Ln_4)._Flen);
_NCp1_NWtr_Pcopy_3(_Lw_1, (*_Ln_4)._Fbuf, (*_Ln_4)._Flen);
_Ln_4 = (*_Ln_4)._Fnext;
if(_Ln_4 == NULL) {
goto break_0;
}
continue_0:;
}
break_0:;
}
inline void _NCp1_NExprI_Pwr_cvar_3(struct _NCp1_NExpr* _Lexpr_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2) {
struct _NCp1_NExprCvar* _Le_3;
_Le_3 = _Lexpr_0;
_NCp1_NAt_Pwr_3((*_Le_3)._Fat, _Lw_1, _Lheader_2);
_NCp1_NId_Pwr_3((*_Le_3)._Fname, _Lw_1, _Lheader_2);
}
inline void _NCp1_NExprI_Pwr_unary_3(struct _NCp1_NExpr* _Lexpr_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2) {
struct _NCp1_NExprUnary* _Le_3;
_Le_3 = _Lexpr_0;
_NCp1_NExprI_Pwr_3((*_Le_3)._Fexpr, _Lw_1, _Lheader_2);
_NCp1_NUnary_Pwr_2((*_Le_3)._Ftype, _Lw_1);
}
inline void _NCp1_NExprI_Pwr_ref_3(struct _NCp1_NExpr* _Lexpr_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2) {
struct _NCp1_NExprRef* _Le_3;
_Le_3 = _Lexpr_0;
_NCp1_NExprI_Pwr_3((*_Le_3)._Fexpr, _Lw_1, _Lheader_2);
}
inline void _NCp1_NExprI_Pwr_cast_fast_3(struct _NCp1_NExpr* _Lexpr_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2) {
struct _NCp1_NExprCastFast* _Le_3;
_Le_3 = _Lexpr_0;
_NCp1_NExprI_Pwr_3((*_Le_3)._Fexpr, _Lw_1, _Lheader_2);
_NCp1_NAt_Pwr_3((*_Le_3)._Ftype, _Lw_1, _Lheader_2);
}
inline void _NCp1_NExprI_Pwr_index_3(struct _NCp1_NExpr* _Lexpr_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2) {
struct _NCp1_NExprIndex* _Le_3;
_Le_3 = _Lexpr_0;
_NCp1_NExprI_Pwr_3((*_Le_3)._Fleft, _Lw_1, _Lheader_2);
_NCp1_NExprI_Pwr_3((*_Le_3)._Fright, _Lw_1, _Lheader_2);
}
inline void _NCp1_NExprI_Pwr_compare_3(struct _NCp1_NExpr* _Lexpr_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2) {
struct _NCp1_NExprCompare* _Le_3;
_Le_3 = _Lexpr_0;
_NCp1_NExprI_Pwr_3((*_Le_3)._Fleft, _Lw_1, _Lheader_2);
_NCp1_NExprI_Pwr_3((*_Le_3)._Fright, _Lw_1, _Lheader_2);
_NCp1_NCompare_Pwr_2((*_Le_3)._Ftype, _Lw_1);
}
inline void _NCp1_NExprI_Pwr_bool_3(struct _NCp1_NExpr* _Lexpr_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2) {
struct _NCp1_NExprBool* _Le_3;
_Le_3 = _Lexpr_0;
_NCp1_NWtr_Pb_2(_Lw_1, (*_Le_3)._Fvalue);
}
inline void _NCp1_NExprI_Pwr_char_3(struct _NCp1_NExpr* _Lexpr_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2) {
struct _NCp1_NExprChar* _Le_3;
_Le_3 = _Lexpr_0;
Fputnum(_Lw_1, (*_Le_3)._Fvalue);
}
inline void _NCp1_NExprI_Pwr_method_3(struct _NCp1_NExpr* _Lexpr_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2) {
struct _NCp1_NExprMethod* _Le_3;
_Le_3 = _Lexpr_0;
_NCp1_NExprI_Pwr_3((*_Le_3)._Fthiss, _Lw_1, _Lheader_2);
_NCp1_NId_Pwr_3((*_Le_3)._Ffunc_name, _Lw_1, _Lheader_2);
_NCp1_NWtr_Pn1_2(_Lw_1, (*_Le_3)._Fgroup_c);
int32_t _Li_4;
_Li_4 = 0;
for(int i = (*_Le_3)._Fgroup_c; i > 0; ) {
i --;
_NCp1_NWtr_Pn1_2(_Lw_1, (*_Le_3)._Fgroup_v[_Li_4]);
continue_0:;
_Li_4++;
}
break_0:;
_NCp1_NWtr_Pn1_2(_Lw_1, (*_Le_3)._Fcarg_c);
int32_t _Li_5;
_Li_5 = 0;
for(int i = (*_Le_3)._Fcarg_c; i > 0; ) {
i --;
_NCp1_NExprI_Pwr_3((*_Le_3)._Fcarg_v[_Li_5]._Fexpr, _Lw_1, _Lheader_2);
continue_1:;
_Li_5++;
}
break_1:;
}
inline void _NCp1_NExprI_Pwr_func_3(struct _NCp1_NExpr* _Lexpr_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2) {
struct _NCp1_NExprFunc* _Le_3;
_Le_3 = _Lexpr_0;
_NCp1_NAt_Pwr_3((*_Le_3)._Fat, _Lw_1, _Lheader_2);
_NCp1_NId_Pwr_3((*_Le_3)._Ffunc_name, _Lw_1, _Lheader_2);
_NCp1_NWtr_Pn1_2(_Lw_1, (*_Le_3)._Fgroup_c);
int32_t _Li_4;
_Li_4 = 0;
for(int i = (*_Le_3)._Fgroup_c; i > 0; ) {
i --;
_NCp1_NWtr_Pn1_2(_Lw_1, (*_Le_3)._Fgroup_v[_Li_4]);
continue_0:;
_Li_4++;
}
break_0:;
_NCp1_NWtr_Pn1_2(_Lw_1, (*_Le_3)._Fcarg_c);
int32_t _Li_5;
_Li_5 = 0;
for(int i = (*_Le_3)._Fcarg_c; i > 0; ) {
i --;
_NCp1_NExprI_Pwr_3((*_Le_3)._Fcarg_v[_Li_5]._Fexpr, _Lw_1, _Lheader_2);
continue_1:;
_Li_5++;
}
break_1:;
}
inline void _NCp1_NExprI_Pwr_null_3(struct _NCp1_NExpr* _Lexpr_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2) {
struct _NCp1_NExprNull* _Le_3;
_Le_3 = _Lexpr_0;
}
inline void _NCp1_NExprI_Pwr_i32_3(struct _NCp1_NExpr* _Lexpr_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2) {
struct _NCp1_NExprIntData* _Le_3;
_Le_3 = _Lexpr_0;
_NCp1_NWtr_Pn1_2(_Lw_1, (*_Le_3)._Ftype);
Fputnum(_Lw_1, (*_Le_3)._Fvalue);
}
inline void _NCp1_NExprI_Pwr_size_of_type_3(struct _NCp1_NExpr* _Lexpr_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2) {
struct _NCp1_NExprSizeOfType* _Le_3;
_Le_3 = _Lexpr_0;
_NCp1_NAt_Pwr_3((*_Le_3)._Ftype, _Lw_1, _Lheader_2);
}
inline void _NCp1_NExprI_Pwr_assign_3(struct _NCp1_NExpr* _Lexpr_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2) {
struct _NCp1_NExprAssign* _Le_3;
_Le_3 = _Lexpr_0;
_NCp1_NExprI_Pwr_3((*_Le_3)._Fleft, _Lw_1, _Lheader_2);
_NCp1_NExprI_Pwr_3((*_Le_3)._Fright, _Lw_1, _Lheader_2);
_NCp1_NAssign_Pwr_2((*_Le_3)._Ftype, _Lw_1);
}
inline void _NCp1_NExprI_Pwr_fvar_3(struct _NCp1_NExpr* _Lexpr_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2) {
struct _NCp1_NExprFvar* _Le_3;
_Le_3 = _Lexpr_0;
_NCp1_NExprI_Pwr_3((*_Le_3)._Fexpr, _Lw_1, _Lheader_2);
_NCp1_NId_Pwr_3((*_Le_3)._Fmember, _Lw_1, _Lheader_2);
}
inline void _NCp1_NExprI_Pwr_gvar_3(struct _NCp1_NExpr* _Lexpr_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2) {
struct _NCp1_NExprGvar* _Le_3;
_Le_3 = _Lexpr_0;
_NCp1_NAt_Pwr_3((*_Le_3)._Fat, _Lw_1, _Lheader_2);
_NCp1_NId_Pwr_3((*_Le_3)._Fname, _Lw_1, _Lheader_2);
}
inline void _NCp1_NExprI_Pwr_lvar_3(struct _NCp1_NExpr* _Lexpr_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2) {
struct _NCp1_NExprLvar* _Le_3;
_Le_3 = _Lexpr_0;
_NCp1_NLvar_Pwr_2((*_Le_3)._Flvar, _Lw_1);
}
inline void _NCp1_NLvarFlags_Pwr_2(_NCp1_NLvarFlags _Lf_0, union _NCp1_NWtr* _Lw_1) {
_NCp1_NWtr_Pn1_2(_Lw_1, _Lf_0);
}
inline void _NCp1_NLvar_Pwr_2(_NCp1_NLvar _Ll_0, union _NCp1_NWtr* _Lw_1) {
Fputnum(_Lw_1, _Ll_0 + 1);
}
inline void _NCp1_NStmtType_Pwr_2(_NCp1_NStmtType _Ls_0, union _NCp1_NWtr* _Lw_1) {
_NCp1_NWtr_Pn1_2(_Lw_1, _Ls_0);
}
inline void _NCp1_NStmtSpace_Pwr_break_3(struct _NCp1_NStmt* _Lstmt_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2) {
struct _NCp1_NStmtBreak* _Ls_3;
_Ls_3 = _Lstmt_0;
_NCp1_NWtr_Pn1_2(_Lw_1, (*_Ls_3)._Fnest);
}
inline void _NCp1_NStmtSpace_Pwr_switch_3(struct _NCp1_NStmt* _Lstmt_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2) {
struct _NCp1_NStmtSwitch* _Ls_3;
_Ls_3 = _Lstmt_0;
_NCp1_NExprI_Pwr_3((*_Ls_3)._Fexpr, _Lw_1, _Lheader_2);
_NCp1_NExprI_Pwr_3((*_Ls_3)._Fcases, _Lw_1, _Lheader_2);
}
inline void _NCp1_NStmtSpace_Pwr_case_3(struct _NCp1_NStmt* _Lstmt_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2) {
struct _NCp1_NStmtCase* _Ls_3;
_Ls_3 = _Lstmt_0;
Fputnum(_Lw_1, (*_Ls_3)._Fexpr_c);
int32_t _Li_4;
_Li_4 = 0;
for(int i = (*_Ls_3)._Fexpr_c; i > 0; ) {
i --;
_NCp1_NExprI_Pwr_3((*_Ls_3)._Fexpr_v[_Li_4]._Fexpr, _Lw_1, _Lheader_2);
continue_0:;
_Li_4++;
}
break_0:;
_NCp1_NWtr_Pb_2(_Lw_1, (*_Ls_3)._Ffall_through);
}
inline void _NCp1_NStmtSpace_Pwr_case_end_3(struct _NCp1_NStmt* _Lstmt_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2) {
}
inline void _NCp1_NStmtSpace_Pwr_default_3(struct _NCp1_NStmt* _Lstmt_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2) {
struct _NCp1_NStmtDefault* _Ls_3;
_Ls_3 = _Lstmt_0;
_NCp1_NWtr_Pb_2(_Lw_1, (*_Ls_3)._Ffall_through);
}
inline void _NCp1_NStmtSpace_Pwr_default_end_3(struct _NCp1_NStmt* _Lstmt_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2) {
}
inline void _NCp1_NStmtSpace_Pwr_switch_end_3(struct _NCp1_NStmt* _Lstmt_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2) {
}
inline void _NCp1_NStmtSpace_Pwr_if_3(struct _NCp1_NStmt* _Lstmt_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2) {
struct _NCp1_NStmtIf* _Ls_3;
_Ls_3 = _Lstmt_0;
_NCp1_NWtr_Pb_2(_Lw_1, (*_Ls_3)._Fnot);
_NCp1_NExprI_Pwr_3((*_Ls_3)._Fexpr, _Lw_1, _Lheader_2);
}
inline void _NCp1_NStmtSpace_Pwr_if_elif_3(struct _NCp1_NStmt* _Lstmt_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2) {
struct _NCp1_NStmtIfElif* _Ls_3;
_Ls_3 = _Lstmt_0;
_NCp1_NWtr_Pb_2(_Lw_1, (*_Ls_3)._Fnot);
_NCp1_NExprI_Pwr_3((*_Ls_3)._Fexpr, _Lw_1, _Lheader_2);
}
inline void _NCp1_NStmtSpace_Pwr_if_else_3(struct _NCp1_NStmt* _Lstmt_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2) {
}
inline void _NCp1_NStmtSpace_Pwr_if_end_3(struct _NCp1_NStmt* _Lstmt_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2) {
}
inline void _NCp1_NStmtSpace_Pwr_do_3(struct _NCp1_NStmt* _Lstmt_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2) {
struct _NCp1_NStmtDo* _Ls_3;
_Ls_3 = _Lstmt_0;
_NCp1_NExprI_Pwr_3((*_Ls_3)._Fexpr, _Lw_1, _Lheader_2);
if((*_Ls_3)._Fcontinu != NULL) {
_NCp1_NWtr_Pb_2(_Lw_1, true);
_NCp1_NStmtSpace_Pwr_3((*_Ls_3)._Fcontinu, _Lw_1, _Lheader_2);
} else {
_NCp1_NWtr_Pb_2(_Lw_1, false);
}
}
inline void _NCp1_NStmtSpace_Pwr_do_end_3(struct _NCp1_NStmt* _Lstmt_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2) {
}
inline void _NCp1_NStmtSpace_Pwr_while_3(struct _NCp1_NStmt* _Lstmt_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2) {
struct _NCp1_NStmtWhile* _Ls_3;
_Ls_3 = _Lstmt_0;
_NCp1_NExprI_Pwr_3((*_Ls_3)._Fexpr, _Lw_1, _Lheader_2);
if((*_Ls_3)._Fcontinu != NULL) {
_NCp1_NWtr_Pb_2(_Lw_1, true);
_NCp1_NStmtSpace_Pwr_3((*_Ls_3)._Fcontinu, _Lw_1, _Lheader_2);
} else {
_NCp1_NWtr_Pb_2(_Lw_1, false);
}
}
inline void _NCp1_NStmtSpace_Pwr_while_end_3(struct _NCp1_NStmt* _Lstmt_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2) {
}
inline void _NCp1_NStmtSpace_Pwr_continue_3(struct _NCp1_NStmt* _Lstmt_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2) {
struct _NCp1_NStmtContinue* _Ls_3;
_Ls_3 = _Lstmt_0;
_NCp1_NWtr_Pn1_2(_Lw_1, (*_Ls_3)._Fnest);
}
inline void _NCp1_NStmtSpace_Pwr_return_3(struct _NCp1_NStmt* _Lstmt_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2) {
struct _NCp1_NStmtReturn* _Ls_3;
_Ls_3 = _Lstmt_0;
_NCp1_NExprI_Pwr_3((*_Ls_3)._Fexpr, _Lw_1, _Lheader_2);
}
inline void _NCp1_NStmtSpace_Pwr_space_3(struct _NCp1_NStmt* _Lstmt_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2) {
struct _NCp1_NStmtSpace* _Ls_3;
_Ls_3 = _Lstmt_0;
_NCp1_NStmtSpace_Pwr_3(_Ls_3, _Lw_1, _Lheader_2);
}
inline void _NCp1_NStmtSpace_Pwr_expr_3(struct _NCp1_NStmt* _Lstmt_0, union _NCp1_NWtr* _Lw_1, bool _Lheader_2) {
struct _NCp1_NStmtExpr* _Ls_3;
_Ls_3 = _Lstmt_0;
_NCp1_NExprI_Pwr_3((*_Ls_3)._Fexpr, _Lw_1, _Lheader_2);
}
void _NCp1_NTypeInfo_Pcopy_from_2(struct _NCp1_NTypeInfo* _Lti_0, struct _NCp1_NTypeInfo* _Lti2_1) {
memcpy((*_Lti_0)._Fref_v, (*_Lti2_1)._Fref_v, _NCp1_Ctype_info_star_limit);
(*_Lti_0)._Farray_c = (*_Lti2_1)._Farray_c;
(*_Lti_0)._Fstar_c = (*_Lti2_1)._Fstar_c;
(*_Lti_0)._Fconst = (*_Lti2_1)._Fconst;
}
void _NCp1_Pfunc_stmt_add_1(struct _NCp1_NStmt* _Ls_0) {
(*_Ls_0)._Fstmt_next = NULL;
if((*_Gdecl_func_ctx_space)._Fstmt_last == NULL) {
(*_Gdecl_func_ctx_space)._Fstmt_first = _Ls_0;
(*_Gdecl_func_ctx_space)._Fstmt_last = _Ls_0;
} else {
(*(*_Gdecl_func_ctx_space)._Fstmt_last)._Fstmt_next = _Ls_0;
(*_Gdecl_func_ctx_space)._Fstmt_last = _Ls_0;
}
}
inline void _NCp1_NWtr_Pb_2(union _NCp1_NWtr* _Lw_0, bool _Lval_1) {
if(_Lval_1) {
_NCp1_NWtr_Pn1_2(_Lw_0, 1);
} else {
_NCp1_NWtr_Pn1_2(_Lw_0, 0);
}
}
inline void _NCp1_NMath_Pwr_2(_NCp1_NMath _Le_0, union _NCp1_NWtr* _Lw_1) {
_NCp1_NWtr_Pn1_2(_Lw_1, _Le_0);
}
inline void _NCp1_NBools_Pwr_2(_NCp1_NBools _Le_0, union _NCp1_NWtr* _Lw_1) {
_NCp1_NWtr_Pn1_2(_Lw_1, _Le_0);
}
inline void _NCp1_NUnary_Pwr_2(_NCp1_NUnary _Lu_0, union _NCp1_NWtr* _Lw_1) {
_NCp1_NWtr_Pn1_2(_Lw_1, _Lu_0);
}
inline void _NCp1_NCompare_Pwr_2(_NCp1_NCompare _Le_0, union _NCp1_NWtr* _Lw_1) {
_NCp1_NWtr_Pn1_2(_Lw_1, _Le_0);
}
inline void _NCp1_NAssign_Pwr_2(_NCp1_NAssign _Ls_0, union _NCp1_NWtr* _Lw_1) {
_NCp1_NWtr_Pn1_2(_Lw_1, _Ls_0);
}
