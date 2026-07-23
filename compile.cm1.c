// 478c312f
// #define CM1_DEBUG_STACK
// #define CM1_DEBUG_STACK_ALLOC

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <inttypes.h>

#define cm1_pop_i64() cm1_stack_v[--cm1_stack_pos].i64
#define cm1_pop_u64() cm1_stack_v[--cm1_stack_pos].u64
#define cm1_pop_u32() (uint32_t)cm1_stack_v[--cm1_stack_pos].u64
#define cm1_pop_isz() (ssize_t)cm1_stack_v[--cm1_stack_pos].i64
#define cm1_pop_usz() (size_t)cm1_stack_v[--cm1_stack_pos].u64
#define cm1_pop_i32() (int32_t)cm1_stack_v[--cm1_stack_pos].i64
#define cm1_pop_f32() cm1_stack_v[--cm1_stack_pos].f32
#define cm1_pop_f64() cm1_stack_v[--cm1_stack_pos].f64
#define cm1_pop_ptr() cm1_stack_v[--cm1_stack_pos].ptr
// Use i64 when pushing so that upper bits are zeroed
#define cm1_push_i(val) cm1_stack_v[cm1_stack_pos++].i64 = val
#define cm1_push_u(val) cm1_stack_v[cm1_stack_pos++].u64 = val

#define cm1_push_ptr(val) cm1_stack_v[cm1_stack_pos++].ptr = val

union cm1_stack_item {
   uint64_t u64;
   int64_t i64;
   float f32;
   double f64;
   void* ptr;
};

#ifndef CM1_STACK_LIMIT
#define CM1_STACK_LIMIT (1024 * 1024)
#endif

static union cm1_stack_item cm1_stack_v[CM1_STACK_LIMIT];
static uint32_t cm1_stack_pos;

static void cm1_push_f32(float value) {
   cm1_stack_v[cm1_stack_pos].u64 = 0;
   cm1_stack_v[cm1_stack_pos++].f32 = value;
}

static void cm1_push_f64(double value) {
   cm1_stack_v[cm1_stack_pos++].f64 = value;
}

void cm1_init(const char* cm1_path);
void cm1_run(uint16_t func_idx);
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#if 0
typedef struct __sFILE FILE;
FILE* stdout;
#endif
#include <string.h>
#include <stdint.h>
#include <limits.h>
void Fskipnum(uint8_t **pbuf) {
  uint8_t* buf = *pbuf;
  uint8_t first = *(buf ++);
  uint8_t zeroes = __builtin_ctz(first);
  *pbuf = buf + zeroes;
}
uint32_t Fgetnum(uint8_t **pbuf) {
  uint8_t* buf = *pbuf;
  uint8_t first = *(buf ++);
  if(first == 0) return 0xffffffff;
  uint32_t var;
  uint8_t zeroes = __builtin_ctz(first);
  
  switch(zeroes) {
    case 0:
      var = first >> 1;
      break;
    case 1:
      var = (first >> 2) | (*(buf ++) << 6);
      break;
    case 2:
      var = (first >> 3) | (*(buf ++) << 5);
      var |= *(buf ++) << (5 + 8);
      break;
    case 3:
      var = (first >> 4) | (*(buf ++) << 4);
      var |= *(buf ++) << (4 + 8);
      var |= *(buf ++) << (4 + 8 + 8);
      break;
    case 4:
      var = (first >> 5) | (*(buf ++) << 3);
      var |= *(buf ++) << (3 + 8);
      var |= *(buf ++) << (3 + 8 + 8);
      var |= *(buf ++) << (3 + 8 + 8 + 8);
      break;
    default:
      return  0xffffffff;
  }
  *pbuf = buf;
  return var;
}
void Fputnum(uint8_t **pbuf, uint32_t num) {
  uint8_t* buf = *pbuf;
  uint8_t zeroes = num == 0 ? 31 : __builtin_clz(num);
  uint8_t bits = 32 - zeroes;
  
  switch(bits) {
    case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7:
      *(buf ++) = (num << 1) | 1;
      
      break;
    case 8: case 9: case 10: case 11: case 12: case 13: case 14:
      *(buf ++) = (num << 2) | (1 << 1);
      *(buf ++) = num >> 6;
      
      break;
    case 15: case 16: case 17: case 18: case 19: case 20: case 21:
      *(buf ++) = (num << 3) | (1 << 2);
      *(buf ++) = num >> 5;
      *(buf ++) = num >> (5 + 8);
      
      break;
    case 22: case 23: case 24: case 25: case 26: case 27: case 28:
      *(buf ++) = (num << 4) | (1 << 3);
      *(buf ++) = num >> 4;
      *(buf ++) = num >> (4 + 8);
      *(buf ++) = num >> (4 + 8 + 8);
      
      break;
    default:
      *(buf ++) = (num << 5) | (1 << 4);
      *(buf ++) = num >> 3;
      *(buf ++) = num >> (3 + 8);
      *(buf ++) = num >> (3 + 8 + 8);
      *(buf ++) = num >> (3 + 8 + 8 + 8);
      
      break;
  }
  *pbuf = buf;
}
int32_t Fgetint(uint8_t **pbuf) {
  uint8_t* buf = *pbuf;
  uint8_t first = *(buf ++);
  if(first == 0) return 0xffffffff;
  int32_t var;
  uint8_t zeroes = __builtin_ctz(first);
  
  uint8_t negative;
  switch(zeroes) {
    case 0:
      negative = (first & 2) != 0;
      var = first >> 2;
      break;
    case 1:
      negative = (first & 4) != 0;
      var = (first >> 3) | (*(buf ++) << 5);
      break;
    case 2:
      negative = (first & 8) != 0;
      var = (first >> 4) | (*(buf ++) << 4);
      var |= *(buf ++) << (4 + 8);
      break;
    case 3:
      negative = (first & 16) != 0;
      var = (first >> 5) | (*(buf ++) << 3);
      var |= *(buf ++) << (3 + 8);
      var |= *(buf ++) << (3 + 8 + 8);
      break;
    case 4:
      negative = (first & 32) != 0;
      var = (first >> 6) | (*(buf ++) << 2);
      var |= *(buf ++) << (2 + 8);
      var |= *(buf ++) << (2 + 8 + 8);
      var |= *(buf ++) << (2 + 8 + 8 + 8);
      break;
    default:
      return INT_MAX;
  }
  *pbuf = buf;
  if (negative) return -var;
  return var;
}
void Fputint(uint8_t **pbuf, int32_t _int) {
   uint32_t num;
   uint8_t negative;
   if (_int < 0) {
      negative = 1;
      num = -_int;
   } else {
      negative = 0;
      num = _int;
   }
  uint8_t* buf = *pbuf;
  uint8_t zeroes = num == 0 ? 31 : __builtin_clz(num);
  uint8_t bits = 32 - zeroes + 1;
  
  switch(bits) {
    case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7:
       if(negative) {
      *(buf ++) = (num << 2) | 1 | 2;
       } else {
      *(buf ++) = (num << 2) | 1;
       }
      
      break;
    case 8: case 9: case 10: case 11: case 12: case 13: case 14:
      if(negative) {
      *(buf ++) = (num << 3) | (1 << 1) | 4;
      } else {
      *(buf ++) = (num << 3) | (1 << 1);
      }
      *(buf ++) = num >> 5;
      
      break;
    case 15: case 16: case 17: case 18: case 19: case 20: case 21:
      if(negative) {
      *(buf ++) = (num << 4) | (1 << 2) | 8;
      } else {
      *(buf ++) = (num << 4) | (1 << 2);
      }
      *(buf ++) = num >> 4;
      *(buf ++) = num >> (4 + 8);
      
      break;
    case 22: case 23: case 24: case 25: case 26: case 27: case 28:
      if(negative) {
      *(buf ++) = (num << 5) | (1 << 3) | 16;
      } else {
      *(buf ++) = (num << 5) | (1 << 3);
      }
      *(buf ++) = num >> 3;
      *(buf ++) = num >> (3 + 8);
      *(buf ++) = num >> (3 + 8 + 8);
      
      break;
    default:
      if(negative) {
      *(buf ++) = (num << 6) | (1 << 4) | 32;
      } else {
      *(buf ++) = (num << 6) | (1 << 4);
      }
      *(buf ++) = num >> 2;
      *(buf ++) = num >> (2 + 8);
      *(buf ++) = num >> (2 + 8 + 8);
      *(buf ++) = num >> (2 + 8 + 8 + 8);
      
      break;
  }
  *pbuf = buf;
}
void Fputnum1(uint8_t **pbuf, uint32_t num) {
   cm1_push_ptr(pbuf);
   cm1_push_u(num);
   cm1_run(0);
   (void)cm1_pop_ptr();
}
void Fputnum2(uint8_t **pbuf, uint32_t num) {
   cm1_push_ptr(pbuf);
   cm1_push_u(num);
   cm1_run(1);
   (void)cm1_pop_ptr();
}
void Fputnum3(uint8_t **pbuf, uint32_t num) {
   cm1_push_ptr(pbuf);
   cm1_push_u(num);
   cm1_run(2);
   (void)cm1_pop_ptr();
}
void Fputnum4(uint8_t **pbuf, uint32_t num) {
   cm1_push_ptr(pbuf);
   cm1_push_u(num);
   cm1_run(3);
   (void)cm1_pop_ptr();
}
void Fputnum5(uint8_t **pbuf, uint32_t num) {
   cm1_push_ptr(pbuf);
   cm1_push_u(num);
   cm1_run(4);
   (void)cm1_pop_ptr();
}
uint64_t Fgetlnum(uint8_t **pbuf) {
	uint8_t* buf = *pbuf;
	uint8_t first = *(buf ++);
	uint64_t var;
	uint8_t zeroes = first == 0 ? 8 : __builtin_ctzll(first);
	
	switch(zeroes) {
		case 0:
		var = first >> 1;
		break;
		case 1:
		var = (first >> 2) | (*(buf ++) << 6);
		break;
		case 2:
		var = (first >> 3) | (*(buf ++) << 5);
		var |= *(buf ++) << (5 + 8);
		break;
		case 3:
		var = (first >> 4) | (*(buf ++) << 4);
		var |= *(buf ++) << (4 + 8);
		var |= *(buf ++) << (4 + 8 + 8);
		break;
		case 4:
		var = (first >> 5) | (*(buf ++) << 3);
		var |= *(buf ++) << (3 + 8);
		var |= *(buf ++) << (3 + 8 + 8);
		var |= (uint64_t)*(buf ++) << (3 + 8 + 8 + 8);
		break;
		case 5:
		var = (first >> 6) | (*(buf ++) << 2);
		var |= *(buf ++) << (2 + 8);
		var |= *(buf ++) << (2 + 8 + 8);
		var |= (uint64_t)*(buf ++) << (2 + 8 + 8 + 8);
		var |= (uint64_t)*(buf ++) << (2 + 8 + 8 + 8 + 8);
		break;
		case 6:
		var = (first >> 7) | (*(buf ++) << 1);
		var |= *(buf ++) << (1 + 8);
		var |= *(buf ++) << (1 + 8 + 8);
		var |= (uint64_t)*(buf ++) << (1 + 8 + 8 + 8);
		var |= (uint64_t)*(buf ++) << (1 + 8 + 8 + 8 + 8);
		var |= (uint64_t)*(buf ++) << (1 + 8 + 8 + 8 + 8 + 8);
		break;
		case 7:
		var = *(buf ++);
		var |= *(buf ++) << (8);
		var |= *(buf ++) << (8 + 8);
		var |= (uint64_t)*(buf ++) << (8 + 8 + 8);
		var |= (uint64_t)*(buf ++) << (8 + 8 + 8 + 8);
		var |= (uint64_t)*(buf ++) << (8 + 8 + 8 + 8 + 8);
		var |= (uint64_t)*(buf ++) << (8 + 8 + 8 + 8 + 8 + 8);
		break;
		default:
		var =   *(buf ++);
		var |= *(buf ++) << (8);
		var |= *(buf ++) << (8 + 8);
		var |= (uint64_t)*(buf ++) << (8 + 8 + 8);
		var |= (uint64_t)*(buf ++) << (8 + 8 + 8 + 8);
		var |= (uint64_t)*(buf ++) << (8 + 8 + 8 + 8 + 8);
		var |= (uint64_t)*(buf ++) << (8 + 8 + 8 + 8 + 8 + 8);
		var |= (uint64_t)*(buf ++) << (8 + 8 + 8 + 8 + 8 + 8 + 8);
		break;
	}
	*pbuf = buf;
	return var;
}
void Fputlnum(uint8_t **pbuf, uint64_t num) {
  uint8_t* buf = *pbuf;
  uint8_t zeroes = num == 0 ? 63 : __builtin_clzll(num);
  uint8_t bits = 64 - zeroes;
  
  switch(bits) {
    case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7:
      *(buf ++) = (num << 1) | 1;
      
      break;
    case 8: case 9: case 10: case 11: case 12: case 13: case 14:
      *(buf ++) = (num << 2) | (1 << 1);
      *(buf ++) = num >> 6;
      
      break;
    case 15: case 16: case 17: case 18: case 19: case 20: case 21:
      *(buf ++) = (num << 3) | (1 << 2);
      *(buf ++) = num >> 5;
      *(buf ++) = num >> (5 + 8);
      
      break;
    case 22: case 23: case 24: case 25: case 26: case 27: case 28:
      *(buf ++) = (num << 4) | (1 << 3);
      *(buf ++) = num >> 4;
      *(buf ++) = num >> (4 + 8);
      *(buf ++) = num >> (4 + 8 + 8);
      
      break;
    case 29: case 30: case 31: case 32: case 33: case 34: case 35:
      *(buf ++) = (num << 5) | (1 << 4);
      *(buf ++) = num >> 3;
      *(buf ++) = num >> (3 + 8);
      *(buf ++) = num >> (3 + 8 + 8);
      *(buf ++) = num >> (3 + 8 + 8 + 8);
      
      break;
    case 36: case 37: case 38: case 39: case 40: case 41: case 42:
      *(buf ++) = (num << 6) | (1 << 5);
      *(buf ++) = num >> 2;
      *(buf ++) = num >> (2 + 8);
      *(buf ++) = num >> (2 + 8 + 8);
      *(buf ++) = num >> (2 + 8 + 8 + 8);
      *(buf ++) = num >> (2 + 8 + 8 + 8 + 8);
      
      break;
    case 43: case 44: case 45: case 46: case 47: case 48: case 49:
      *(buf ++) = (num << 7) | (1 << 6);
      *(buf ++) = num >> 1;
      *(buf ++) = num >> (1 + 8);
      *(buf ++) = num >> (1 + 8 + 8);
      *(buf ++) = num >> (1 + 8 + 8 + 8);
      *(buf ++) = num >> (1 + 8 + 8 + 8 + 8);
      *(buf ++) = num >> (1 + 8 + 8 + 8 + 8 + 8);
      
      break;
    case 50: case 51: case 52: case 53: case 54: case 55: case 56:
      *(buf ++) = (1 << 7);
      *(buf ++) = num;
      *(buf ++) = num >> (8);
      *(buf ++) = num >> (8 + 8);
      *(buf ++) = num >> (8 + 8 + 8);
      *(buf ++) = num >> (8 + 8 + 8 + 8);
      *(buf ++) = num >> (8 + 8 + 8 + 8 + 8);
      *(buf ++) = num >> (8 + 8 + 8 + 8 + 8 + 8);
      break;
    default:
      *(buf ++) = 0;
      *(buf ++) = num;
      *(buf ++) = num >> (8);
      *(buf ++) = num >> (8 + 8);
      *(buf ++) = num >> (8 + 8 + 8);
      *(buf ++) = num >> (8 + 8 + 8 + 8);
      *(buf ++) = num >> (8 + 8 + 8 + 8 + 8);
      *(buf ++) = num >> (8 + 8 + 8 + 8 + 8 + 8);
      *(buf ++) = num >> (8 + 8 + 8 + 8 + 8 + 8 + 8);
      
      break;
    












  }
  *pbuf = buf;
}
uint32_t Fpow2gt(uint32_t n) {
	if(n == 0) return 1;
  uint8_t bits = 32 - __builtin_clz(n);
  return 1 << bits;
}
uint32_t Fpow2gteq(uint32_t n) {
	if(n <= 1) return 1;
  uint8_t bits = 32 - __builtin_clz(n - 1);
  return 1 << bits;
}
typedef int32_t _Tposix_Tfd;
typedef int32_t _Tposix_Topen_flags;
typedef int32_t _Tlibc_Texit;
typedef int32_t _Tcp1_Tfunc;
typedef uint8_t _Tcp1_Tbasic_type_id;
typedef int32_t _Tcp1_Tat;
typedef uint8_t _Tcp1_Tname_type;
typedef int32_t _Tcp1_Tid;
typedef int32_t _Tcp1_Tgvar;
typedef int32_t _Tcp1_Tcvar;
typedef int32_t _Tcp1_Tstruct;
typedef int32_t _Tcp1_Tenum;
typedef uint8_t _Tcp1_Tat_def;
typedef int32_t _Tcp1_Tinclude;
typedef int32_t _Tcp1_Tfile;
typedef uint32_t _Tcp1_Ttemplate_inst;
typedef uint8_t _Tcp1_Tinclude_error;
typedef uint32_t _Tcp1_Ttemplate_code;
typedef uint32_t _Tcp1_Tfunc_flags;
typedef uint8_t _Tcp1_Toverload;
typedef uint32_t _Tcp1_Tvar_flags;
typedef int32_t _Tcp1_Texpr_i;
typedef uint8_t _Tcp1_Tstmt_type;
typedef uint8_t _Tcp1_Tstmt_space_flags;
typedef int32_t _Tcp1_Tlvar;
typedef uint8_t _Tcp1_Tlvar_flags;
typedef uint8_t _Tcp1_Tstruct_flags;
typedef uint8_t _Tcp1_Tenum_flags;
typedef uint8_t _Tcp1_Tcvar_flags;
typedef uint8_t _Tcp1_Tgvar_flags;
typedef uint8_t _Tlibcp1_Tfmt_Tu32_base;
typedef int32_t _Tposix_Tseek;
typedef uint8_t _Tcp1_Texpr_type;
typedef uint8_t _Tcp1_Texpr_flags;
typedef uint32_t _Twindows_Tcreate_file_access;
typedef uint32_t _Twindows_Tcreate_file_share_mode;
typedef uint32_t _Twindows_Tcreate_file_creation_disposition;
typedef uint32_t _Twindows_Tcreate_file_flags;
typedef uint8_t _Tcp1_Tassign;
typedef uint8_t _Tcp1_Tcompare;
typedef uint8_t _Tcp1_Tmath;
typedef uint8_t _Tcp1_Tunary;
typedef int32_t _Tcp1_Tfvar;
typedef uint8_t _Tcp1_Tbools;
typedef uint8_t _Tcp1_Texpr_int;
struct _Tlibcp1_Tfmt;
struct _Tlibcp1_Tfmt {
   char* _Mptr;
   uint64_t _Mlen;
   uint64_t _Mcap;
   void* _Muser_data;
};
struct _Tlibcp1_Tfmt_Tf_cstr;
struct _Tlibcp1_Tfmt_Tf_cstr {
   char* _Mstr;
   uint64_t _Mlen;
};
struct _Tlibcp1_Tfmt_Tf_char;
struct _Tlibcp1_Tfmt_Tf_char {
   char _Mchar;
};
struct _Tlibcp1_Tsprintf;
struct _Tlibcp1_Tsprintf {
   char* _Mmem;
   uint32_t _Mlen;
};
struct _Tcp1_Tmap;
struct _Tcp1_Tmap {
   uint64_t _Mdata[256];
};
struct _Tcp1_Tat_map;
struct _Tcp1_Tat_map {
   uint64_t _Mdata[256];
};
union _Tcp1_Tat_name;
union _Tcp1_Tat_name {
   _Tcp1_Tid _Mid;
   _Tcp1_Tbasic_type_id _Mbasic;
};
union _Tcp1_Tat_type;
union _Tcp1_Tat_type {
   _Tcp1_Tstruct _Mstructt;
   _Tcp1_Tenum _Menumm;
};
struct _Tcp1_Tat_data;
struct _Tcp1_Tat_data {
   _Tcp1_Tname_type _Mtype;
   _Tcp1_Tat _Mparent;
   union _Tcp1_Tat_name _Mname;
   int32_t _Mfunc_c;
   int32_t _Mfunc_cap;
   _Tcp1_Tfunc* _Mfunc_v;
   int32_t _Mgvar_c;
   int32_t _Mgvar_cap;
   _Tcp1_Tgvar* _Mgvar_v;
   int32_t _Mcvar_c;
   int32_t _Mcvar_cap;
   _Tcp1_Tcvar* _Mcvar_v;
   union _Tcp1_Tat_type _Mdecl;
   _Tcp1_Tat_def _Mdef;
};
struct _Tcp1_Ttemplate_inst_data;
struct _Tcp1_Ttemplate_inst_data {
   char* _Marg;
   uint32_t _Marg_len;
   uint32_t _Marg_crc32c;
   _Tcp1_Tid _Mname;
   _Tcp1_Tat _Mat;
   uint32_t _Mrow;
   uint32_t _Mcol;
   _Tcp1_Tfile _Mfile;
   uint8_t _Mrequire;
};
struct _Tcp1_Ttemplate_code_data;
struct _Tcp1_Ttemplate_code_data {
   uint8_t* _Mcode;
   uint32_t _Mcode_len;
   uint32_t _Mcode_crc32c;
   _Tcp1_Tid _Mname;
   _Tcp1_Tat _Mat;
   uint32_t _Mrow;
   uint32_t _Mline_c;
   uint8_t _Mwith_reflection;
   uint8_t _Mno_cache;
   uint8_t _Mjs;
   _Tcp1_Tfile _Mfile;
};
union _Tcp1_Trdr;
union _Tcp1_Trdr {
   void* _Mref;
   uint64_t _Mpos;
   uint8_t* _Mp1;
   uint16_t* _Mp2;
   char* _Mchar;
   uint32_t* _Mp4;
   float* _Mf4;
   double* _Mf8;
};
struct _Tlibcp1_Tfmt_Tf_u32;
struct _Tlibcp1_Tfmt_Tf_u32 {
   uint32_t _Mu32;
};
struct _Tcp1_Ttype_info;
struct _Tcp1_Ttype_info {
   int8_t _Mref_v[8];
   uint8_t _Marray_c;
   int8_t _Mstar_c;
   uint8_t _Mbuilt_in;
   uint8_t _Mconst;
};
struct _Tcp1_Tvalue;
struct _Tcp1_Tvalue {
   int8_t _Mref;
   uint8_t _Mparen;
   _Tcp1_Tat _Mtype;
   struct _Tcp1_Ttype_info _Minfo;
};
struct _Tcp1_Tdecl_var_data;
struct _Tcp1_Tdecl_var_data {
   _Tcp1_Tid _Mname;
   _Tcp1_Tat _Mtype;
   _Tcp1_Tvar_flags _Mflags;
   _Tcp1_Tid _Mreal_name;
   struct _Tcp1_Ttype_info _Mtype_info;
   uint8_t _Msize_c;
   _Tcp1_Texpr_i* _Msize_expr_v;
   struct _Tcp1_Tvalue* _Msize_value_v;
};
struct _Tcp1_Tstmt;
struct _Tcp1_Tstmt {
   uint32_t _Mbegin_row;
   uint32_t _Mbegin_col;
   uint32_t _Mend_row;
   uint32_t _Mend_col;
   _Tcp1_Tstmt_type _Mtype;
   struct _Tcp1_Tstmt* _Mstmt_next;
};
struct _Tcp1_Tstmt_space;
struct _Tcp1_Tstmt_space {
   struct _Tcp1_Tstmt _Mbase;
   struct _Tcp1_Tstmt_space* _Mparent;
   _Tcp1_Tstmt_space_flags _Mflags;
   struct _Tcp1_Tstmt* _Mstmt_first;
   struct _Tcp1_Tstmt* _Mstmt_last;
   int32_t _Mlvar_c;
   int32_t _Mlvar_cap;
   _Tcp1_Tlvar* _Mlvar_v;
};
struct _Tcp1_Tlvar_data;
struct _Tcp1_Tlvar_data {
   uint32_t _Mrow;
   uint32_t _Mcol;
   struct _Tcp1_Tdecl_var_data _Mdecl;
   _Tcp1_Tlvar_flags _Mflags;
};
struct _Tcp1_Tfarg;
struct _Tcp1_Tfarg {
   uint32_t _Mrow;
   uint32_t _Mcol;
   struct _Tcp1_Tdecl_var_data _Mdecl;
};
struct _Tcp1_Tdecl_func;
struct _Tcp1_Tdecl_func {
   _Tcp1_Tfunc _Mprocess_next;
   _Tcp1_Tfile _Mfile;
   uint32_t _Mbegin_row;
   uint32_t _Mbegin_col;
   uint32_t _Mend_row;
   uint32_t _Mend_col;
   _Tcp1_Tinclude _Minclude;
   _Tcp1_Tat _Mat;
   uint8_t _Mangle;
   _Tcp1_Tfunc_flags _Mflags;
   _Tcp1_Tid _Mreal_name;
   _Tcp1_Tid _Mmeta_method_prefix1;
   _Tcp1_Tid _Mmeta_method_prefix2;
   _Tcp1_Tid _Mmeta_method_arr1;
   _Tcp1_Tid _Mmeta_method_cstr1;
   _Tcp1_Tid _Mmeta_method_arr2;
   _Tcp1_Tid _Mmeta_method_cstr2;
   _Tcp1_Tid _Mmeta_method_end1;
   _Tcp1_Tid _Mmeta_method_end2;
   _Tcp1_Tfunc _Mlist1_prev;
   char* _Mdecl_str;
   int32_t _Mdecl_len;
   _Tcp1_Toverload _Moverload;
   _Tcp1_Tid _Mcas;
   struct _Tcp1_Tdecl_var_data _Mdecl;
   struct _Tcp1_Tstmt_space _Mstmt_space;
   _Tcp1_Tlvar _Mlvar_c;
   struct _Tcp1_Tlvar_data* _Mlvar_v;
   uint32_t _Mbody_file_pos;
   int8_t _Mthis_idx;
   int8_t _Mthis_group;
   int8_t _Mgroup_c;
   int8_t _Mgroup_v[256];
   uint8_t _Mfarg_c;
   struct _Tcp1_Tfarg _Mfarg_v[1];
};
struct _Tcp1_Tfvar_data;
struct _Tcp1_Tfvar_data {
   struct _Tcp1_Tdecl_var_data _Mdecl;
};
struct _Tcp1_Tstruct_data;
struct _Tcp1_Tstruct_data {
   _Tcp1_Tfile _Mfile;
   uint32_t _Mbegin_row;
   uint32_t _Mbegin_col;
   uint32_t _Mend_row;
   uint32_t _Mend_col;
   _Tcp1_Tinclude _Minclude;
   _Tcp1_Tat _Mat;
   _Tcp1_Tstruct_flags _Mflags;
   _Tcp1_Tid _Mreal_name;
   int32_t _Mmethod_c;
   int32_t _Mmethod_cap;
   _Tcp1_Tfunc* _Mmethod_v;
   uint32_t _Maligned;
   uint32_t _Mfvar_c;
   struct _Tcp1_Tfvar_data _Mfvar_v[1];
};
struct _Tcp1_Tenum_data;
struct _Tcp1_Tenum_data {
   _Tcp1_Tfile _Mfile;
   uint32_t _Mbegin_row;
   uint32_t _Mbegin_col;
   uint32_t _Mend_row;
   uint32_t _Mend_col;
   _Tcp1_Tinclude _Minclude;
   _Tcp1_Tat _Mat;
   _Tcp1_Tat _Mbase_type;
   _Tcp1_Tenum_flags _Mflags;
   _Tcp1_Tat _Msoa_field_gvar_at;
   _Tcp1_Tid _Msoa_field_gvar_id;
   _Tcp1_Tid _Mreal_name;
   int32_t _Mmethod_c;
   int32_t _Mmethod_cap;
   _Tcp1_Tfunc* _Mmethod_v;
   _Tcp1_Tfunc _Moverload_get_last;
   _Tcp1_Tfunc _Moverload_set_last;
   _Tcp1_Tfunc _Moverload_math_last;
   _Tcp1_Tfunc _Moverload_bools_last;
   _Tcp1_Tfunc _Moverload_compare_last;
   _Tcp1_Tfunc _Moverload_if_begin;
   _Tcp1_Tfunc _Moverload_if_else;
   _Tcp1_Tfunc _Moverload_if_end;
   _Tcp1_Tfunc _Moverload_statement;
};
struct _Tcp1_Tbasic_type;
struct _Tcp1_Tbasic_type {
   int32_t _Mmethod_c;
   int32_t _Mmethod_cap;
   _Tcp1_Tfunc* _Mmethod_v;
};
struct _Tcp1_Tcvar_data;
struct _Tcp1_Tcvar_data {
   _Tcp1_Tfile _Mfile;
   uint32_t _Mrow;
   uint32_t _Mcol;
   _Tcp1_Tinclude _Minclude;
   _Tcp1_Tat _Mat;
   _Tcp1_Tcvar_flags _Mflags;
   struct _Tcp1_Tdecl_var_data _Mdecl;
   _Tcp1_Texpr_i _Mexpr_set;
   _Tcp1_Tcvar _Mlast_cvar;
};
struct _Tcp1_Tdecl_gvar;
struct _Tcp1_Tdecl_gvar {
   _Tcp1_Tfile _Mfile;
   uint32_t _Mrow;
   uint32_t _Mcol;
   _Tcp1_Tinclude _Minclude;
   _Tcp1_Tat _Mat;
   _Tcp1_Tgvar_flags _Mflags;
   struct _Tcp1_Tdecl_var_data _Mdecl;
};
struct _Tlibcp1_Tfmt_Tf_i32;
struct _Tlibcp1_Tfmt_Tf_i32 {
   int32_t _Mi32;
};
struct _Tcp1_Tfile_data;
struct _Tcp1_Tfile_data {
   uint32_t _Mcrc32c;
   char* _Mpath;
   uint16_t _Mpath_len;
   void* _Mdata;
   _Tcp1_Tid* _Mid_table;
   _Tcp1_Tat* _Mat_table;
   _Tcp1_Tcvar* _Mcvar_table;
};
struct _Tlibcp1_Tfmt_Tf_u32_base;
struct _Tlibcp1_Tfmt_Tf_u32_base {
   _Tlibcp1_Tfmt_Tu32_base _Mbase;
   uint32_t _Mu32;
};
struct _Tcp1_Texpr;
struct _Tcp1_Texpr {
   _Tcp1_Texpr_type _Mtype;
   _Tcp1_Texpr_flags _Mflags;
};
struct _Tcp1_Texpr_assign;
struct _Tcp1_Texpr_assign {
   struct _Tcp1_Texpr _Mbase;
   _Tcp1_Texpr_i _Mleft;
   _Tcp1_Texpr_i _Mright;
   _Tcp1_Tassign _Mtype;
   struct _Tcp1_Tvalue _Mleft_val;
   struct _Tcp1_Tvalue _Mright_val;
   uint8_t _Mis_overload;
   uint8_t _Mis_stmt;
};
struct _Tcp1_Texpr_lvar;
struct _Tcp1_Texpr_lvar {
   struct _Tcp1_Texpr _Mbase;
   _Tcp1_Tlvar _Mlvar;
   uint8_t _Mdecl;
};
struct _Tcp1_Texpr_compare;
struct _Tcp1_Texpr_compare {
   struct _Tcp1_Texpr _Mbase;
   _Tcp1_Texpr_i _Mleft;
   _Tcp1_Texpr_i _Mright;
   _Tcp1_Tcompare _Mtype;
   struct _Tcp1_Tvalue _Mleft_val;
   struct _Tcp1_Tvalue _Mright_val;
   uint8_t _Mis_overload;
};
struct _Tcp1_Texpr_bool;
struct _Tcp1_Texpr_bool {
   struct _Tcp1_Texpr _Mbase;
   uint8_t _Mvalue;
};
struct _Tcp1_Texpr_char;
struct _Tcp1_Texpr_char {
   struct _Tcp1_Texpr _Mbase;
   char _Mvalue;
};
struct _Tcp1_Texpr_math_item;
struct _Tcp1_Texpr_math_item {
   _Tcp1_Texpr_i _Mexpr;
   struct _Tcp1_Tvalue _Mval;
};
struct _Tcp1_Texpr_math;
struct _Tcp1_Texpr_math {
   struct _Tcp1_Texpr _Mbase;
   _Tcp1_Texpr_i _Mleft;
   _Tcp1_Texpr_i _Mright;
   _Tcp1_Tmath _Mtype;
   struct _Tcp1_Tvalue _Mleft_val;
   struct _Tcp1_Tvalue _Mright_val;
   uint8_t _Mis_overload;
   uint8_t _Mitem_c;
   struct _Tcp1_Texpr_math_item* _Mitem_v;
};
struct _Tcp1_Texpr_unary;
struct _Tcp1_Texpr_unary {
   struct _Tcp1_Texpr _Mbase;
   _Tcp1_Texpr_i _Mexpr;
   _Tcp1_Tunary _Mtype;
   struct _Tcp1_Tvalue _Mval;
};
struct _Tcp1_Texpr_ref;
struct _Tcp1_Texpr_ref {
   struct _Tcp1_Texpr _Mbase;
   _Tcp1_Texpr_i _Mexpr;
   struct _Tcp1_Tvalue _Mval;
};
struct _Tcp1_Texpr_fvar;
struct _Tcp1_Texpr_fvar {
   struct _Tcp1_Texpr _Mbase;
   _Tcp1_Texpr_i _Mexpr;
   _Tcp1_Tid _Mmember;
   _Tcp1_Tfvar _Mfvar;
   struct _Tcp1_Tvalue _Mval;
};
struct _Tcp1_Texpr_soa_field;
struct _Tcp1_Texpr_soa_field {
   struct _Tcp1_Texpr _Mbase;
   _Tcp1_Texpr_i _Mexpr;
   _Tcp1_Tid _Mgroup;
   _Tcp1_Tid _Mfield;
   _Tcp1_Texpr_i _Mexpr2;
   struct _Tcp1_Tvalue _Mval;
};
struct _Tcp1_Texpr_gvar;
struct _Tcp1_Texpr_gvar {
   struct _Tcp1_Texpr _Mbase;
   _Tcp1_Tgvar _Mgvar;
};
struct _Tcp1_Texpr_cvar;
struct _Tcp1_Texpr_cvar {
   struct _Tcp1_Texpr _Mbase;
   _Tcp1_Tat _Mat;
   _Tcp1_Tid _Mname;
   _Tcp1_Tcvar _Mcvar;
   _Tcp1_Tat _Mtry;
};
struct _Tcp1_Texpr_bools_item;
struct _Tcp1_Texpr_bools_item {
   _Tcp1_Texpr_i _Mexpr;
   struct _Tcp1_Tvalue _Mval;
};
struct _Tcp1_Texpr_bools;
struct _Tcp1_Texpr_bools {
   struct _Tcp1_Texpr _Mbase;
   _Tcp1_Texpr_i _Mleft;
   _Tcp1_Texpr_i _Mright;
   _Tcp1_Tbools _Mtype;
   struct _Tcp1_Tvalue _Mleft_val;
   struct _Tcp1_Tvalue _Mright_val;
   uint8_t _Mis_overload;
   uint8_t _Mitem_c;
   struct _Tcp1_Texpr_bools_item* _Mitem_v;
};
struct _Tcp1_Tcarg;
struct _Tcp1_Tcarg {
   int8_t _Mref;
   _Tcp1_Texpr_i _Mexpr;
   struct _Tcp1_Tvalue _Mvalue;
};
struct _Tcp1_Texpr_method;
struct _Tcp1_Texpr_method {
   struct _Tcp1_Texpr _Mbase;
   _Tcp1_Texpr_i _Mthis;
   _Tcp1_Tid _Mfunc_name;
   uint8_t _Mangle;
   _Tcp1_Tfunc _Mfunc_idx;
   struct _Tcp1_Tvalue _Mthis_value;
   uint8_t _Mgroup_c;
   uint8_t _Mgroup_v[256];
   uint8_t _Mcarg_c;
   struct _Tcp1_Tcarg _Mcarg_v[1];
};
struct _Tcp1_Texpr_func;
struct _Tcp1_Texpr_func {
   struct _Tcp1_Texpr _Mbase;
   _Tcp1_Tat _Mat;
   _Tcp1_Tid _Mfunc_name;
   uint8_t _Mangle;
   _Tcp1_Tfunc _Mfunc_idx;
   uint8_t _Mgroup_c;
   uint8_t _Mgroup_v[256];
   uint8_t _Mcarg_c;
   struct _Tcp1_Tcarg _Mcarg_v[1];
};
struct _Tcp1_Texpr_meta_func;
struct _Tcp1_Texpr_meta_func {
   struct _Tcp1_Texpr _Mbase;
   uint8_t _Mexpr_c;
   _Tcp1_Texpr_i _Mexpr_v[1];
};
struct _Tcp1_Texpr_str_node;
struct _Tcp1_Texpr_str_node {
   struct _Tcp1_Texpr_str_node* _Mnext;
   uint8_t _Mmacro;
   uint32_t _Mlen;
   char _Mbuf[1];
};
struct _Tcp1_Texpr_str;
struct _Tcp1_Texpr_str {
   struct _Tcp1_Texpr _Mbase;
   int32_t _Mnode_c;
   struct _Tcp1_Texpr_str_node* _Mfirst;
   struct _Tcp1_Texpr_str_node* _Mlast;
};
union _Tcp1_Texpr_int_value;
union _Tcp1_Texpr_int_value {
   int32_t _Mi32;
   uint32_t _Mu32;
   float _Mf32;
   double _Mf64;
   uint64_t _Mu64;
};
struct _Tcp1_Texpr_int_data;
struct _Tcp1_Texpr_int_data {
   struct _Tcp1_Texpr _Mbase;
   union _Tcp1_Texpr_int_value _Mvalue;
   _Tcp1_Texpr_int _Mtype;
};
struct _Tlibcp1_Tfmt_Tf_f32;
struct _Tlibcp1_Tfmt_Tf_f32 {
   float _Mf32;
};
struct _Tlibcp1_Tfmt_Tf_f64;
struct _Tlibcp1_Tfmt_Tf_f64 {
   double _Mf64;
};
struct _Tlibcp1_Tfmt_Tf_u64;
struct _Tlibcp1_Tfmt_Tf_u64 {
   uint64_t _Mu64;
};
struct _Tcp1_Texpr_size_of_type;
struct _Tcp1_Texpr_size_of_type {
   struct _Tcp1_Texpr _Mbase;
   _Tcp1_Tat _Mtype;
};
struct _Tcp1_Texpr_null;
struct _Tcp1_Texpr_null {
   struct _Tcp1_Texpr _Mbase;
};
struct _Tcp1_Texpr_index;
struct _Tcp1_Texpr_index {
   struct _Tcp1_Texpr _Mbase;
   _Tcp1_Texpr_i _Mleft;
   _Tcp1_Texpr_i _Mright;
   struct _Tcp1_Tvalue _Mleft_val;
   struct _Tcp1_Tvalue _Mright_val;
};
struct _Tcp1_Texpr_cast_fast;
struct _Tcp1_Texpr_cast_fast {
   struct _Tcp1_Texpr _Mbase;
   _Tcp1_Texpr_i _Mexpr;
   _Tcp1_Tat _Mtype;
   struct _Tcp1_Tvalue _Mval;
};
struct _Tcp1_Tstmt_expr;
struct _Tcp1_Tstmt_expr {
   struct _Tcp1_Tstmt _Mbase;
   _Tcp1_Texpr_i _Mexpr;
};
struct _Tcp1_Tstmt_if;
struct _Tcp1_Tstmt_if {
   struct _Tcp1_Tstmt _Mbase;
   _Tcp1_Texpr_i _Mexpr;
   struct _Tcp1_Tvalue _Mval;
   uint8_t _Mis_overload;
   _Tcp1_Tat _Moverload_type;
};
struct _Tcp1_Tstmt_if_elif;
struct _Tcp1_Tstmt_if_elif {
   struct _Tcp1_Tstmt _Mbase;
   _Tcp1_Texpr_i _Mexpr;
   _Tcp1_Texpr_i _Mexpr_else;
   struct _Tcp1_Tvalue _Mval;
   uint8_t _Mis_overload;
};
struct _Tcp1_Tstmt_if_else;
struct _Tcp1_Tstmt_if_else {
   struct _Tcp1_Tstmt _Mbase;
   struct _Tcp1_Tstmt_if* _Mif_begin;
   _Tcp1_Texpr_i _Mexpr;
};
struct _Tcp1_Tstmt_if_end;
struct _Tcp1_Tstmt_if_end {
   struct _Tcp1_Tstmt _Mbase;
   struct _Tcp1_Tstmt_if* _Mif_begin;
   _Tcp1_Texpr_i _Mexpr;
};
struct _Tcp1_Tstmt_switch_case_func;
struct _Tcp1_Tstmt_switch_case_func {
   _Tcp1_Tcvar _Mcvar;
   _Tcp1_Tfunc _Mfunc;
};
struct _Tcp1_Tstmt_switch;
struct _Tcp1_Tstmt_switch {
   struct _Tcp1_Tstmt _Mbase;
   _Tcp1_Texpr_i _Mexpr;
   struct _Tcp1_Tvalue _Mval;
   _Tcp1_Texpr_i _Mcases;
   uint32_t _Mcase_func_c;
   struct _Tcp1_Tstmt_switch_case_func* _Mcase_func_v;
};
struct _Tcp1_Tstmt_case_item;
struct _Tcp1_Tstmt_case_item {
   _Tcp1_Texpr_i _Mexpr;
   struct _Tcp1_Tvalue _Mval;
};
struct _Tcp1_Tstmt_case;
struct _Tcp1_Tstmt_case {
   struct _Tcp1_Tstmt _Mbase;
   uint8_t _Mfall_through;
   uint32_t _Mexpr_c;
   struct _Tcp1_Tstmt_case_item _Mexpr_v[1];
};
struct _Tcp1_Tstmt_case_end;
struct _Tcp1_Tstmt_case_end {
   struct _Tcp1_Tstmt _Mbase;
};
struct _Tcp1_Tstmt_default;
struct _Tcp1_Tstmt_default {
   struct _Tcp1_Tstmt _Mbase;
   uint8_t _Mfall_through;
};
struct _Tcp1_Tstmt_default_end;
struct _Tcp1_Tstmt_default_end {
   struct _Tcp1_Tstmt _Mbase;
};
struct _Tcp1_Tstmt_switch_end;
struct _Tcp1_Tstmt_switch_end {
   struct _Tcp1_Tstmt _Mbase;
};
struct _Tcp1_Tstmt_loop_end;
struct _Tcp1_Tstmt_loop_end {
   struct _Tcp1_Tstmt _Mbase;
   struct _Tcp1_Tstmt_loop* _Mdo;
};
struct _Tcp1_Tstmt_loop;
struct _Tcp1_Tstmt_loop {
   struct _Tcp1_Tstmt _Mbase;
   _Tcp1_Texpr_i _Mexpr;
   struct _Tcp1_Tvalue _Mval;
   struct _Tcp1_Tstmt_space* _Mcontinu;
   struct _Tcp1_Tstmt_loop_end* _Mend;
};
union _Tcp1_Tnest;
union _Tcp1_Tnest {
   struct _Tcp1_Tstmt_loop* _Mdo;
   void* _Mref;
};
struct _Tcp1_Tstmt_continue;
struct _Tcp1_Tstmt_continue {
   struct _Tcp1_Tstmt _Mbase;
   uint8_t _Mnest;
};
struct _Tcp1_Tstmt_break;
struct _Tcp1_Tstmt_break {
   struct _Tcp1_Tstmt _Mbase;
   uint8_t _Mnest;
};
struct _Tcp1_Tstmt_return;
struct _Tcp1_Tstmt_return {
   struct _Tcp1_Tstmt _Mbase;
   _Tcp1_Texpr_i _Mexpr;
   struct _Tcp1_Tvalue _Mval;
};
struct _Tcp1_Texpr_meta_method;
struct _Tcp1_Texpr_meta_method {
   struct _Tcp1_Texpr _Mbase;
   uint8_t _Mexpr_c;
   _Tcp1_Texpr_i _Mexpr_v[1];
};
union _Tcp1_Tcase_stack;
union _Tcp1_Tcase_stack {
   struct _Tcp1_Tstmt_case* _Mcas;
   struct _Tcp1_Tstmt_default* _Mdefaul;
};
char** _Tcp1_Ginclude_path_v;
uint16_t* _Tcp1_Ginclude_path_len_v;
char** _Tcp1_Gdefine_v;
uint16_t* _Tcp1_Gdefine_len_v;
char* _Tcp1_Gdebug_func_prefix;
uint8_t _Tcp1_Gdebug_func_prefix_len;
uint8_t _Tcp1_Ginclude_path_c;
uint16_t _Tcp1_Gdefine_c;
char _Tcp1_Ginclude_dir[4096];
uint16_t _Tcp1_Ginclude_dir_len;
struct _Tcp1_Tmap _Tcp1_Gid_map;
struct _Tcp1_Tmap _Tcp1_Ginclude_map;
struct _Tcp1_Tat_map _Tcp1_Gat_map;
_Tcp1_Tfunc _Tcp1_Gfunc_main;
_Tcp1_Tat _Tcp1_Gat_c;
_Tcp1_Tat _Tcp1_Gat_cap;
struct _Tcp1_Tat_data* _Tcp1_Gat_v;
uint32_t _Tcp1_Gimport_cap;
_Tcp1_Tinclude* _Tcp1_Gimport_v;
_Tcp1_Tfile* _Tcp1_Gimport_file_v;
uint8_t* _Tcp1_Gimport_required_v;
_Tcp1_Ttemplate_inst _Tcp1_Gtemplate_inst_cap;
struct _Tcp1_Ttemplate_inst_data* _Tcp1_Gtemplate_inst_v;
uint32_t _Tcp1_Gimport_new_c;
uint32_t _Tcp1_Gimport_c;
_Tcp1_Ttemplate_inst _Tcp1_Gtemplate_inst_new_c;
uint32_t _Tcp1_Gjscode_buf_cap;
char* _Tcp1_Gjscode_buf_data;
_Tcp1_Ttemplate_inst _Tcp1_Gtemplate_inst_c;
_Tcp1_Ttemplate_code _Tcp1_Gtemplate_code_c;
struct _Tcp1_Ttemplate_code_data* _Tcp1_Gtemplate_code_v;
uint32_t _Tcp1_Gjscode_buf_len;
_Tcp1_Tfunc _Tcp1_Gfunc_c;
struct _Tcp1_Tbasic_type _Tcp1_Gbasic_type[18];
_Tcp1_Tid _Tcp1_Gid_add;
_Tcp1_Tid _Tcp1_Gid_sub;
_Tcp1_Tid _Tcp1_Gid_mul;
_Tcp1_Tid _Tcp1_Gid_div;
_Tcp1_Tid _Tcp1_Gid_eq;
_Tcp1_Tid _Tcp1_Gid_ne;
_Tcp1_Tid _Tcp1_Gid_gt;
_Tcp1_Tid _Tcp1_Gid_ge;
_Tcp1_Tid _Tcp1_Gid_lt;
_Tcp1_Tid _Tcp1_Gid_le;
_Tcp1_Tid _Tcp1_Gid_and;
_Tcp1_Tid _Tcp1_Gid_or;
uint8_t* _Tcp1_Gfunc_in_process;
_Tcp1_Tfunc* _Tcp1_Gfunc_head_outputted_v;
_Tcp1_Tfunc* _Tcp1_Gfunc_body_outputted_v;
int32_t _Tcp1_Ginclude_c;
uint8_t* _Tcp1_Ginclude_is_outputted;
_Tcp1_Tinclude* _Tcp1_Ginclude_outputted_v;
_Tcp1_Tcvar _Tcp1_Gcvar_c;
uint8_t* _Tcp1_Gcvar_is_outputted;
_Tcp1_Tcvar* _Tcp1_Gcvar_outputted_v;
_Tcp1_Tgvar _Tcp1_Ggvar_c;
uint8_t* _Tcp1_Ggvar_is_outputted;
_Tcp1_Tgvar* _Tcp1_Ggvar_outputted_v;
_Tcp1_Tenum _Tcp1_Genum_c;
uint8_t* _Tcp1_Genum_is_outputted;
_Tcp1_Tenum* _Tcp1_Genum_outputted_v;
_Tcp1_Tstruct _Tcp1_Gstruct_c;
uint8_t* _Tcp1_Gstruct_is_outputted;
_Tcp1_Tstruct* _Tcp1_Gstruct_outputted_v;
_Tcp1_Tfunc _Tcp1_Gprocess_first;
_Tcp1_Tfunc _Tcp1_Gprocess_last;
int32_t _Tcp1_Gfunc_head_outputted_c;
struct _Tcp1_Tdecl_func* _Tcp1_Gctx_func;
uint32_t _Tcp1_Goutput_cap;
char* output_data;
int32_t _Tcp1_Gcvar_outputted_c;
int32_t _Tcp1_Genum_outputted_c;
int32_t _Tcp1_Gstruct_outputted_c;
int32_t _Tcp1_Ggvar_outputted_c;
int32_t _Tcp1_Ginclude_outputted_c;
int32_t _Tcp1_Gfunc_body_outputted_c;
int32_t _Tcp1_Gnest_id;
uint32_t output_len;
uint8_t _Tcp1_Gprinted_error;
uint32_t _Tlibcp1_Gstdout_buf_len;
char _Tlibcp1_Gstdout_buf_data[4096];
int32_t _Tcp1_Gquick_alloc_c;
int32_t _Tcp1_Gquick_alloc_cap;
void* _Tcp1_Gquick_alloc_v;
int32_t _Tcp1_Ginclude_cap;
uint8_t* _Tcp1_Ginclude_len_v;
char** _Tcp1_Ginclude_str_v;
_Tcp1_Tfile _Tcp1_Gfile_c;
_Tcp1_Tfile _Tcp1_Gfile_cap;
struct _Tcp1_Tfile_data* _Tcp1_Gfile_v;
_Tcp1_Tid* _Tcp1_Gid_table;
int32_t _Tcp1_Ginclude_table_cap;
_Tcp1_Tinclude* _Tcp1_Ginclude_table;
_Tcp1_Tat* _Tcp1_Gat_table;
_Tcp1_Tcvar* _Tcp1_Gcvar_table;
_Tcp1_Tcvar _Tcp1_Gcvar_cap;
struct _Tcp1_Tcvar_data* _Tcp1_Gcvar_v;
_Tcp1_Tgvar _Tcp1_Ggvar_cap;
struct _Tcp1_Tdecl_gvar* _Tcp1_Ggvar_v;
_Tcp1_Tenum _Tcp1_Genum_cap;
struct _Tcp1_Tenum_data** _Tcp1_Genum_v;
_Tcp1_Tstruct _Tcp1_Gstruct_cap;
struct _Tcp1_Tstruct_data** _Tcp1_Gstruct_v;
_Tcp1_Tfunc _Tcp1_Gfunc_cap;
struct _Tcp1_Tdecl_func** _Tcp1_Gfunc_v;
_Tcp1_Tfunc _Tcp1_Gctx_func_id;
_Tcp1_Ttemplate_code _Tcp1_Gtemplate_code_cap;
char** _Tcp1_Gid_str_v;
uint8_t* _Tcp1_Gid_len_v;
int32_t _Tcp1_Gid_c;
int32_t _Tcp1_Gid_cap;
char** _Tcp1_Gid_c_name_v;
uint32_t _Tcp1_Gctx_begin_row;
uint32_t _Tcp1_Gctx_begin_col;
uint32_t _Tcp1_Gctx_end_row;
uint32_t _Tcp1_Gctx_end_col;
_Tcp1_Tid _Tcp1_Gid_blank;
uint8_t* _Tcp1_Gexpr_is_processed;
struct _Tcp1_Texpr** _Tcp1_Gexpr_v;
int32_t _Tcp1_Gexpr_c;
int32_t _Tcp1_Gexpr_cap;
struct _Tcp1_Tstmt_if* _Tcp1_Tstmt_space_Gif_stack_v[256];
uint8_t _Tcp1_Tstmt_space_Gif_stack_c;
int32_t _Tcp1_Gnest_stack_id_v[64];
uint8_t _Tcp1_Gnest_stack_c;
union _Tcp1_Tnest _Tcp1_Gnest_stack_ptr_v[64];
struct _Tcp1_Tstmt_switch* _Tcp1_Gswitch_stack_v[64];
uint8_t _Tcp1_Gswitch_stack_c;
union _Tcp1_Tcase_stack _Tcp1_Gcase_stack_v[64];
uint8_t _Tcp1_Gcase_stack_c;
#ifndef _Tcp1_Fmain_2
int32_t _Tcp1_Fmain_2(int32_t _Larg_c_0, char **_Larg_v_1);
#endif
#ifndef stdout_then_print_error
void stdout_then_print_error(char *_Lbuf_0, uint32_t _Llen_1);
#endif
#ifndef _Tcp1_Foutput_reserve_1
void _Tcp1_Foutput_reserve_1(uint32_t _Llen_0);
#endif
#ifndef _Tlibcp1_Fstdout_1
void _Tlibcp1_Fstdout_1(struct _Tlibcp1_Tfmt *_Lfmt_0);
#endif
#ifndef _Tlibcp1_Tfmt_Ff_reserve_cstr_4
void _Tlibcp1_Tfmt_Ff_reserve_cstr_4(struct _Tlibcp1_Tfmt *_Lfmt_0, char *_Lstr_1, int32_t _Llen_2, struct _Tlibcp1_Tfmt_Tf_cstr *_Lf_3);
#endif
#ifndef _Tlibcp1_Tfmt_Ff_reserve_stdout_1
void _Tlibcp1_Tfmt_Ff_reserve_stdout_1(struct _Tlibcp1_Tfmt *_Lfmt_0);
#endif
#ifndef _Tlibcp1_Tfmt_Tf_cstr_Ff_2
void _Tlibcp1_Tfmt_Tf_cstr_Ff_2(struct _Tlibcp1_Tfmt_Tf_cstr *_Lf_0, struct _Tlibcp1_Tfmt *_Lfmt_1);
#endif
#ifndef _Tlibcp1_Tfmt_Ff_stdout_1
void _Tlibcp1_Tfmt_Ff_stdout_1(struct _Tlibcp1_Tfmt *_Lfmt_0);
#endif
#ifndef _Tcp1_Fdeps_init_1
void _Tcp1_Fdeps_init_1(char *_Lpath_0);
#endif
#ifndef _Tlibcp1_Tfmt_Ff_reserve_Tchar_1_2
void _Tlibcp1_Tfmt_Ff_reserve_Tchar_1_2(char _Lc_0, struct _Tlibcp1_Tfmt *_Lfmt_1, struct _Tlibcp1_Tfmt_Tf_char *_Lf_2);
#endif
#ifndef _Tlibcp1_Tfmt_Tf_char_Ff_2
void _Tlibcp1_Tfmt_Tf_char_Ff_2(struct _Tlibcp1_Tfmt_Tf_char *_Lf_0, struct _Tlibcp1_Tfmt *_Lfmt_1);
#endif
#ifndef crc32c
uint32_t crc32c(uint32_t _Lcrc32c_0, void *_Ldata_1, uint32_t _Lsize_2);
#endif
#ifndef _Tlibcp1_Tfmt_Ff_reserve_arr_Tchar_1_2
void _Tlibcp1_Tfmt_Ff_reserve_arr_Tchar_1_2(char *_Lc_0, struct _Tlibcp1_Tfmt *_Lfmt_1, struct _Tlibcp1_Tfmt_Tf_cstr *_Lf_2);
#endif
#ifndef _Tlibcp1_Fsprintf_2
struct _Tlibcp1_Tsprintf* _Tlibcp1_Fsprintf_2(char *_Lbuf_0, struct _Tlibcp1_Tsprintf *_Lsf_1);
#endif
#ifndef _Tlibcp1_Tsprintf_Ff_2
void _Tlibcp1_Tsprintf_Ff_2(struct _Tlibcp1_Tsprintf *_Lsf_0, struct _Tlibcp1_Tfmt *_Lfmt_1);
#endif
#ifndef _Tlibcp1_Tfmt_Ff_reserve_sprintf_f_1
void _Tlibcp1_Tfmt_Ff_reserve_sprintf_f_1(struct _Tlibcp1_Tfmt *_Lfmt_0);
#endif
#ifndef _Tlibcp1_Tfmt_Ff_sprintf_f_1
void _Tlibcp1_Tfmt_Ff_sprintf_f_1(struct _Tlibcp1_Tfmt *_Lfmt_0);
#endif
#ifndef _Tcp1_Fc_init_1
void _Tcp1_Fc_init_1(uint32_t _Lcrc32c_0);
#endif
#ifndef _Tcp1_Fdeps_output_1
void _Tcp1_Fdeps_output_1(char *_Lpath_0);
#endif
#ifndef qalloc_undo
void qalloc_undo(int32_t _Lsize_0);
#endif
#ifndef _Tcp1_Tmap_Finit_1
void _Tcp1_Tmap_Finit_1(struct _Tcp1_Tmap *_Lm_0);
#endif
#ifndef _Tcp1_Tat_map_Finit_1
void _Tcp1_Tat_map_Finit_1(struct _Tcp1_Tat_map *_Lm_0);
#endif
#ifndef _Tcp1_Fquick_alloc_init_0
void _Tcp1_Fquick_alloc_init_0();
#endif
#ifndef _Tcp1_Tat_data_Finit_4
void _Tcp1_Tat_data_Finit_4(struct _Tcp1_Tat_data *_Lat_0, _Tcp1_Tname_type _Ltype_1, _Tcp1_Tat _Lparent_2, _Tcp1_Tid _Lname_3);
#endif
#ifndef _Tcp1_Finclude_add_2
_Tcp1_Tinclude _Tcp1_Finclude_add_2(uint8_t _Linclude_len_0, char *_Linclude_str_1);
#endif
#ifndef _Tcp1_Tinclude_Fvalidate_2
uint8_t _Tcp1_Tinclude_Fvalidate_2(_Tcp1_Tinclude _Lpath_0, _Tcp1_Tinclude_error *_Lerr_1);
#endif
#ifndef _Tlibcp1_Fstdbuf_1
void _Tlibcp1_Fstdbuf_1(struct _Tlibcp1_Tfmt *_Lfmt_0);
#endif
#ifndef _Tlibcp1_Tfmt_Ff_reserve_stdbuf_1
void _Tlibcp1_Tfmt_Ff_reserve_stdbuf_1(struct _Tlibcp1_Tfmt *_Lfmt_0);
#endif
#ifndef _Tlibcp1_Tfmt_Ff_stdbuf_1
void _Tlibcp1_Tfmt_Ff_stdbuf_1(struct _Tlibcp1_Tfmt *_Lfmt_0);
#endif
#ifndef _Tcp1_Tinclude_error_Fprint_2
void _Tcp1_Tinclude_error_Fprint_2(_Tcp1_Tinclude_error _Le_0, _Tcp1_Tinclude _Lpath_1);
#endif
#ifndef _Tcp1_Fimport_3
void _Tcp1_Fimport_3(_Tcp1_Tinclude _Lpath_0, uint8_t _Lrequire_1, _Tcp1_Tfile _Lfile_2);
#endif
#ifndef _Tcp1_Fread_4
void _Tcp1_Fread_4(char *_Lin_path_cp1_0, uint16_t _Lin_path_cp1_len_1, uint8_t _Lstrdup_2, uint8_t _Lrequire_3);
#endif
#ifndef _Tcp1_Tinclude_Fstr_1
char* _Tcp1_Tinclude_Fstr_1(_Tcp1_Tinclude _Li_0);
#endif
#ifndef _Tcp1_Tinclude_Flen_1
uint8_t _Tcp1_Tinclude_Flen_1(_Tcp1_Tinclude _Li_0);
#endif
#ifndef _Tcp1_Fmeta_begin_8
uint8_t _Tcp1_Fmeta_begin_8(char *_Lfile_0, uint8_t _Lfile_len_1, char *_Ltc_name_2, uint8_t _Ltc_name_len_3, uint32_t _Lcode_crc32c_4, uint32_t _Larg_crc32c_5, uint8_t _Lrequire_6, uint8_t _Ljs_7);
#endif
#ifndef _Tcp1_Tfile_Fpath_1
char* _Tcp1_Tfile_Fpath_1(_Tcp1_Tfile _Lf_0);
#endif
#ifndef _Tcp1_Tfile_Fpath_len_1
uint16_t _Tcp1_Tfile_Fpath_len_1(_Tcp1_Tfile _Lf_0);
#endif
#ifndef _Tcp1_Tid_Fstr_1
char* _Tcp1_Tid_Fstr_1(_Tcp1_Tid _Lid_0);
#endif
#ifndef _Tcp1_Tid_Flen_1
uint8_t _Tcp1_Tid_Flen_1(_Tcp1_Tid _Lid_0);
#endif
#ifndef _Tcp1_Fjscode_1
void _Tcp1_Fjscode_1(struct _Tlibcp1_Tfmt *_Lfmt_0);
#endif
#ifndef _Tlibcp1_Tfmt_Ff_reserve_arr_Tchar_1_3
void _Tlibcp1_Tfmt_Ff_reserve_arr_Tchar_1_3(char *_Lc_0, int32_t _Llen_1, struct _Tlibcp1_Tfmt *_Lfmt_2, struct _Tlibcp1_Tfmt_Tf_cstr *_Lf_3);
#endif
#ifndef _Tlibcp1_Tfmt_Ff_reserve_jscode_1
void _Tlibcp1_Tfmt_Ff_reserve_jscode_1(struct _Tlibcp1_Tfmt *_Lfmt_0);
#endif
#ifndef _Tlibcp1_Tfmt_Ff_jscode_1
void _Tlibcp1_Tfmt_Ff_jscode_1(struct _Tlibcp1_Tfmt *_Lfmt_0);
#endif
#ifndef _Tcp1_Tat_Fjscode_write_1
void _Tcp1_Tat_Fjscode_write_1(_Tcp1_Tat _Lat_idx_0);
#endif
#ifndef _Tcp1_Tat_Fptr_1
struct _Tcp1_Tat_data* _Tcp1_Tat_Fptr_1(_Tcp1_Tat _Li_0);
#endif
#ifndef _Tcp1_Tat_Fjscode_write_name_1
void _Tcp1_Tat_Fjscode_write_name_1(_Tcp1_Tat _Lat_idx_0);
#endif
#ifndef _Tcp1_Fquickjs_hex_2
uint32_t _Tcp1_Fquickjs_hex_2(char *_Ldata_0, uint32_t _Lcode_crc32c_1);
#endif
#ifndef _Tlibcp1_Tfmt_Ff_reserve_Tu32_1_2
void _Tlibcp1_Tfmt_Ff_reserve_Tu32_1_2(uint32_t _Lu_0, struct _Tlibcp1_Tfmt *_Lfmt_1, struct _Tlibcp1_Tfmt_Tf_u32 *_Lf_2);
#endif
#ifndef _Tlibcp1_Tfmt_Tf_u32_Ff_2
void _Tlibcp1_Tfmt_Tf_u32_Ff_2(struct _Tlibcp1_Tfmt_Tf_u32 *_Lf_0, struct _Tlibcp1_Tfmt *_Lfmt_1);
#endif
#ifndef _Tcp1_Fjs_end_3
void _Tcp1_Fjs_end_3(char *_Ljs_data_0, uint32_t _Ljs_data_len_1, uint8_t _Lrequire_2);
#endif
#ifndef _Tlibcp1_Tfmt_Ff_reserve_Tu16_1_2
void _Tlibcp1_Tfmt_Ff_reserve_Tu16_1_2(uint16_t _Lu_0, struct _Tlibcp1_Tfmt *_Lfmt_1, struct _Tlibcp1_Tfmt_Tf_u32 *_Lf_2);
#endif
#ifndef _Tcp1_Fmeta_end_3
void _Tcp1_Fmeta_end_3(char *_Ljs_data_0, uint32_t _Ljs_data_len_1, uint8_t _Lrequire_2);
#endif
#ifndef _Tlibcp1_Tfmt_Ff_reserve_Tfile_1_2
void _Tlibcp1_Tfmt_Ff_reserve_Tfile_1_2(_Tcp1_Tfile _Lid_0, struct _Tlibcp1_Tfmt *_Lfmt_1, struct _Tlibcp1_Tfmt_Tf_cstr *_Lf_2);
#endif
#ifndef _Tlibcp1_Tfmt_Ff_reserve_Tid_1_2
void _Tlibcp1_Tfmt_Ff_reserve_Tid_1_2(_Tcp1_Tid _Lid_0, struct _Tlibcp1_Tfmt *_Lfmt_1, struct _Tlibcp1_Tfmt_Tf_cstr *_Lf_2);
#endif
#ifndef _Tcp1_Tfunc_Fptr_1
struct _Tcp1_Tdecl_func* _Tcp1_Tfunc_Fptr_1(_Tcp1_Tfunc _Lf_0);
#endif
#ifndef _Tcp1_Tstruct_Fptr_1
struct _Tcp1_Tstruct_data* _Tcp1_Tstruct_Fptr_1(_Tcp1_Tstruct _Ls_0);
#endif
#ifndef _Tcp1_Tenum_Fptr_1
struct _Tcp1_Tenum_data* _Tcp1_Tenum_Fptr_1(_Tcp1_Tenum _Lf_0);
#endif
#ifndef _Tcp1_Fid_add_2
_Tcp1_Tid _Tcp1_Fid_add_2(uint8_t _Lid_len_0, char *_Lid_str_1);
#endif
#ifndef _Tcp1_Tfunc_Fprocess_later_1
uint8_t _Tcp1_Tfunc_Fprocess_later_1(_Tcp1_Tfunc _Lf_idx_0);
#endif
#ifndef _Tcp1_Tfunc_Fprocess_now_1
uint8_t _Tcp1_Tfunc_Fprocess_now_1(_Tcp1_Tfunc _Lf_idx_0);
#endif
#ifndef _Tcp1_Tlvar_Fprocess_1
uint8_t _Tcp1_Tlvar_Fprocess_1(_Tcp1_Tlvar _Ll_0);
#endif
#ifndef _Tcp1_Foutput_1
void _Tcp1_Foutput_1(struct _Tlibcp1_Tfmt *_Lfmt_0);
#endif
#ifndef _Tlibcp1_Tfmt_Ff_reserve_output_1
void _Tlibcp1_Tfmt_Ff_reserve_output_1(struct _Tlibcp1_Tfmt *_Lfmt_0);
#endif
#ifndef _Tlibcp1_Tfmt_Ff_output_1
void _Tlibcp1_Tfmt_Ff_output_1(struct _Tlibcp1_Tfmt *_Lfmt_0);
#endif
#ifndef _Tcp1_Tcvar_Fptr_1
struct _Tcp1_Tcvar_data* _Tcp1_Tcvar_Fptr_1(_Tcp1_Tcvar _Lc_0);
#endif
#ifndef _Tcp1_Tinclude_Foutput_1
void _Tcp1_Tinclude_Foutput_1(_Tcp1_Tinclude _Lthis_0);
#endif
#ifndef _Tcp1_Tgvar_Fptr_1
struct _Tcp1_Tdecl_gvar* _Tcp1_Tgvar_Fptr_1(_Tcp1_Tgvar _Lg_0);
#endif
#ifndef _Tcp1_Tat_Foutput_4
void _Tcp1_Tat_Foutput_4(_Tcp1_Tat _Lat_i_0, _Tcp1_Tfile _Lfile_1, uint32_t _Lrow_2, uint32_t _Lcol_3);
#endif
#ifndef _Tcp1_Tcvar_Fprocess_1
uint8_t _Tcp1_Tcvar_Fprocess_1(_Tcp1_Tcvar _Lc_0);
#endif
#ifndef _Tlibcp1_Tfmt_Ff_reserve_Tinclude_1_2
void _Tlibcp1_Tfmt_Ff_reserve_Tinclude_1_2(_Tcp1_Tinclude _Li_0, struct _Tlibcp1_Tfmt *_Lfmt_1, struct _Tlibcp1_Tfmt_Tf_cstr *_Lf_2);
#endif
#ifndef _Tcp1_Tcvar_Fwrite_1
void _Tcp1_Tcvar_Fwrite_1(_Tcp1_Tcvar _Lc_0);
#endif
#ifndef _Tcp1_Texpr_i_Fwrite_1
void _Tcp1_Texpr_i_Fwrite_1(_Tcp1_Texpr_i _Le_0);
#endif
#ifndef _Tlibcp1_Tfmt_Ff_reserve_Ti32_1_2
void _Tlibcp1_Tfmt_Ff_reserve_Ti32_1_2(int32_t _Li_0, struct _Tlibcp1_Tfmt *_Lfmt_1, struct _Tlibcp1_Tfmt_Tf_i32 *_Lf_2);
#endif
#ifndef _Tlibcp1_Tfmt_Tf_i32_Ff_2
void _Tlibcp1_Tfmt_Tf_i32_Ff_2(struct _Tlibcp1_Tfmt_Tf_i32 *_Lf_0, struct _Tlibcp1_Tfmt *_Lfmt_1);
#endif
#ifndef _Tcp1_Tat_Fwrite_1
void _Tcp1_Tat_Fwrite_1(_Tcp1_Tat _Lat_idx_0);
#endif
#ifndef _Tcp1_Tat_Fwrite_space_1
void _Tcp1_Tat_Fwrite_space_1(_Tcp1_Tat _Lat_idx_0);
#endif
#ifndef _Tcp1_Tdecl_var_data_Fwrite_type_fvar_1
void _Tcp1_Tdecl_var_data_Fwrite_type_fvar_1(struct _Tcp1_Tdecl_var_data *_Lvd_0);
#endif
#ifndef _Tcp1_Tdecl_var_data_Fwrite_type_gvar_2
void _Tcp1_Tdecl_var_data_Fwrite_type_gvar_2(struct _Tcp1_Tdecl_var_data *_Lvd_0, _Tcp1_Tat _Lat_1);
#endif
#ifndef _Tcp1_Tdecl_func_Fwrite_1
void _Tcp1_Tdecl_func_Fwrite_1(struct _Tcp1_Tdecl_func *_Lf_0);
#endif
#ifndef _Tcp1_Tat_Fwrite_type_info_3
uint8_t _Tcp1_Tat_Fwrite_type_info_3(_Tcp1_Tat _Ltd_0, struct _Tcp1_Ttype_info *_Lti_1, int32_t _Ladd_2);
#endif
#ifndef _Tcp1_Tdecl_var_data_Fwrite_lvar_type_2
void _Tcp1_Tdecl_var_data_Fwrite_lvar_type_2(struct _Tcp1_Tdecl_var_data *_Lvd_0, _Tcp1_Tlvar _Llvar_1);
#endif
#ifndef _Tcp1_Tfile_Fptr_1
struct _Tcp1_Tfile_data* _Tcp1_Tfile_Fptr_1(_Tcp1_Tfile _Lf_0);
#endif
#ifndef _Tlibcp1_Tfmt_Ff_reserve_Tu32_1_3
void _Tlibcp1_Tfmt_Ff_reserve_Tu32_1_3(uint32_t _Lu_0, _Tlibcp1_Tfmt_Tu32_base _Lbase_1, struct _Tlibcp1_Tfmt *_Lfmt_2, struct _Tlibcp1_Tfmt_Tf_u32_base *_Lf_3);
#endif
#ifndef _Tlibcp1_Tfmt_Tf_u32_base_Ff_2
void _Tlibcp1_Tfmt_Tf_u32_base_Ff_2(struct _Tlibcp1_Tfmt_Tf_u32_base *_Lf_0, struct _Tlibcp1_Tfmt *_Lfmt_1);
#endif
#ifndef _Tcp1_Tstmt_space_Fwrite_1
void _Tcp1_Tstmt_space_Fwrite_1(struct _Tcp1_Tstmt_space *_Lspace_0);
#endif
#ifndef _Tcp1_Fwrite_file_3
uint8_t _Tcp1_Fwrite_file_3(char *_Lpath_0, void *_Ldata_1, uint64_t _Lsize_2);
#endif
#ifndef _Tcp1_Fdeps_close_0
void _Tcp1_Fdeps_close_0();
#endif
#ifndef _Tcp1_Tmap_Fget_or_insert_4
int32_t _Tcp1_Tmap_Fget_or_insert_4(struct _Tcp1_Tmap *_Lm_0, char *_Lstr_1, uint8_t _Llen_2, int32_t _Lval_3);
#endif
#ifndef _Tcp1_Freq_parse_3
char* _Tcp1_Freq_parse_3(char *_Lin_path_cp1_0, uint8_t _Lin_path_cp1_len_1, uint8_t _Lrequire_2);
#endif
#ifndef _Tcp1_Fread_file_2
void* _Tcp1_Fread_file_2(char *_Lpath_0, uint64_t *_Lout_size_1);
#endif
#ifndef _Tcp1_Trdr_Fn1_1
uint8_t _Tcp1_Trdr_Fn1_1(union _Tcp1_Trdr *_Lr_0);
#endif
#ifndef _Tcp1_Tname_type_Frd_2
void _Tcp1_Tname_type_Frd_2(_Tcp1_Tname_type *_Li_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Tbasic_type_id_Frd_2
void _Tcp1_Tbasic_type_id_Frd_2(_Tcp1_Tbasic_type_id *_Le_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Fbasic_type_1
_Tcp1_Tat _Tcp1_Fbasic_type_1(_Tcp1_Tbasic_type_id _Lt_0);
#endif
#ifndef _Tcp1_Tat_Frd_2
void _Tcp1_Tat_Frd_2(_Tcp1_Tat *_Li_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Tid_Frd_2
void _Tcp1_Tid_Frd_2(_Tcp1_Tid *_Lid_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Tat_map_Fget_or_insert_5
int32_t _Tcp1_Tat_map_Fget_or_insert_5(struct _Tcp1_Tat_map *_Lm_0, _Tcp1_Tat _Lparent_1, _Tcp1_Tname_type _Ltype_2, _Tcp1_Tid _Lname_3, int32_t _Lval_4);
#endif
#ifndef _Tcp1_Tinclude_Frd_2
void _Tcp1_Tinclude_Frd_2(_Tcp1_Tinclude *_Li_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Tdecl_var_data_Frd_2
void _Tcp1_Tdecl_var_data_Frd_2(struct _Tcp1_Tdecl_var_data *_Lvd_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Tcvar_flags_Frd_2
void _Tcp1_Tcvar_flags_Frd_2(_Tcp1_Tcvar_flags *_Lf_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Texpr_i_Frd_2
void _Tcp1_Texpr_i_Frd_2(_Tcp1_Texpr_i *_Le_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Tcvar_Frd_2
void _Tcp1_Tcvar_Frd_2(_Tcp1_Tcvar *_Lc_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Tenum_flags_Frd_2
void _Tcp1_Tenum_flags_Frd_2(_Tcp1_Tenum_flags *_Le_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Tstruct_flags_Frd_2
void _Tcp1_Tstruct_flags_Frd_2(_Tcp1_Tstruct_flags *_Lf_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Tfarg_Frd_2
void _Tcp1_Tfarg_Frd_2(struct _Tcp1_Tfarg *_Lf_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Tfunc_flags_Frd_2
void _Tcp1_Tfunc_flags_Frd_2(_Tcp1_Tfunc_flags *_Le_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef qalloc
void* qalloc(int32_t _Lsize_0);
#endif
#ifndef _Tcp1_Tfunc_Frd_2
void _Tcp1_Tfunc_Frd_2(_Tcp1_Tfunc *_Lf_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Trdr_Fn4_1
uint32_t _Tcp1_Trdr_Fn4_1(union _Tcp1_Trdr *_Lr_0);
#endif
#ifndef _Tcp1_Trdr_Fb_1
uint8_t _Tcp1_Trdr_Fb_1(union _Tcp1_Trdr *_Lr_0);
#endif
#ifndef _Tcp1_Ftemplate_inst_1
void _Tcp1_Ftemplate_inst_1(struct _Tcp1_Ttemplate_inst_data *_Lti_0);
#endif
#ifndef _Tcp1_Fjscode_reserve_1
void _Tcp1_Fjscode_reserve_1(uint32_t _Llen_0);
#endif
char* _Tcp1_Tbasic_type_id_Fcp1_name_1(_Tcp1_Tbasic_type_id _Le_0) {
   cm1_push_u(_Le_0);
   cm1_run(103);
   return cm1_pop_ptr();
}
#ifndef _Tcp1_Tat_Fjscode_write_name_dot_1
void _Tcp1_Tat_Fjscode_write_name_dot_1(_Tcp1_Tat _Lat_idx_0);
#endif
#ifndef _Tcp1_Tdecl_var_data_Fprocess_5
uint8_t _Tcp1_Tdecl_var_data_Fprocess_5(struct _Tcp1_Tdecl_var_data *_Lvd_0, _Tcp1_Tfile _Lfile_1, uint32_t _Lrow_2, uint32_t _Lcol_3, _Tcp1_Tat _Lbase_at_4);
#endif
#ifndef _Tcp1_Fat_validate_5
_Tcp1_Tat _Tcp1_Fat_validate_5(_Tcp1_Tat _Lvd_type_0, _Tcp1_Tat _Lat_i_1, _Tcp1_Tfile _Lfile_2, uint32_t _Lrow_3, uint32_t _Lcol_4);
#endif
#ifndef _Tcp1_Tat_Ffinalize_4
uint8_t _Tcp1_Tat_Ffinalize_4(_Tcp1_Tat _Lat_i_0, struct _Tcp1_Ttype_info *_Lti_1, uint32_t _Lrow_2, uint32_t _Lcol_3);
#endif
#ifndef _Tcp1_Tdecl_func_Flvars_rd_2
void _Tcp1_Tdecl_func_Flvars_rd_2(struct _Tcp1_Tdecl_func *_Lf_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Tstmt_space_Frd_3
void _Tcp1_Tstmt_space_Frd_3(struct _Tcp1_Tstmt_space *_Lspace_0, union _Tcp1_Trdr *_Lr_1, struct _Tcp1_Tstmt_space *_Lparent_2);
#endif
#ifndef _Tcp1_Tstmt_Fprocess_1
uint8_t _Tcp1_Tstmt_Fprocess_1(struct _Tcp1_Tstmt *_Ls_0);
#endif
#ifndef _Tcp1_Tlvar_Fptr_1
struct _Tcp1_Tlvar_data* _Tcp1_Tlvar_Fptr_1(_Tcp1_Tlvar _Ll_0);
#endif
#ifndef _Tcp1_Tstruct_Foutput_1
void _Tcp1_Tstruct_Foutput_1(_Tcp1_Tstruct _Ls_i_0);
#endif
#ifndef _Tcp1_Tenum_Foutput_1
void _Tcp1_Tenum_Foutput_1(_Tcp1_Tenum _Le_i_0);
#endif
#ifndef _Tcp1_Texpr_i_Fprocess_1
uint8_t _Tcp1_Texpr_i_Fprocess_1(_Tcp1_Texpr_i _Le_0);
#endif
#ifndef _Tcp1_Tid_Fc_name_1
char* _Tcp1_Tid_Fc_name_1(_Tcp1_Tid _Lid_0);
#endif
#ifndef _Tcp1_Texpr_i_Fptr_1
struct _Tcp1_Texpr* _Tcp1_Texpr_i_Fptr_1(_Tcp1_Texpr_i _Le_0);
#endif
#ifndef _Tcp1_Texpr_i_Fwrite_assign_1
void _Tcp1_Texpr_i_Fwrite_assign_1(struct _Tcp1_Texpr *_Lexpr_0);
#endif
#ifndef _Tcp1_Texpr_i_Fwrite_compare_1
void _Tcp1_Texpr_i_Fwrite_compare_1(struct _Tcp1_Texpr *_Lexpr_0);
#endif
#ifndef _Tcp1_Texpr_i_Fwrite_bool_1
void _Tcp1_Texpr_i_Fwrite_bool_1(struct _Tcp1_Texpr *_Lexpr_0);
#endif
#ifndef _Tcp1_Texpr_i_Fwrite_char_1
void _Tcp1_Texpr_i_Fwrite_char_1(struct _Tcp1_Texpr *_Lexpr_0);
#endif
#ifndef _Tcp1_Texpr_i_Fwrite_math_1
void _Tcp1_Texpr_i_Fwrite_math_1(struct _Tcp1_Texpr *_Lexpr_0);
#endif
#ifndef _Tcp1_Texpr_i_Fwrite_unary_1
void _Tcp1_Texpr_i_Fwrite_unary_1(struct _Tcp1_Texpr *_Lexpr_0);
#endif
#ifndef _Tcp1_Texpr_i_Fwrite_ref_1
void _Tcp1_Texpr_i_Fwrite_ref_1(struct _Tcp1_Texpr *_Lexpr_0);
#endif
#ifndef _Tcp1_Texpr_i_Fwrite_lvar_1
void _Tcp1_Texpr_i_Fwrite_lvar_1(struct _Tcp1_Texpr *_Lexpr_0);
#endif
#ifndef _Tcp1_Texpr_i_Fwrite_fvar_1
void _Tcp1_Texpr_i_Fwrite_fvar_1(struct _Tcp1_Texpr *_Lexpr_0);
#endif
#ifndef _Tcp1_Texpr_i_Fwrite_soa_field_1
void _Tcp1_Texpr_i_Fwrite_soa_field_1(struct _Tcp1_Texpr *_Lexpr_0);
#endif
#ifndef _Tcp1_Texpr_i_Fwrite_gvar_1
void _Tcp1_Texpr_i_Fwrite_gvar_1(struct _Tcp1_Texpr *_Lexpr_0);
#endif
#ifndef _Tcp1_Texpr_i_Fwrite_cvar_1
void _Tcp1_Texpr_i_Fwrite_cvar_1(struct _Tcp1_Texpr *_Lexpr_0);
#endif
#ifndef _Tcp1_Texpr_i_Fwrite_bools_1
void _Tcp1_Texpr_i_Fwrite_bools_1(struct _Tcp1_Texpr *_Lexpr_0);
#endif
#ifndef _Tcp1_Texpr_i_Fwrite_method_1
void _Tcp1_Texpr_i_Fwrite_method_1(struct _Tcp1_Texpr *_Lexpr_0);
#endif
#ifndef _Tcp1_Texpr_i_Fwrite_func_1
void _Tcp1_Texpr_i_Fwrite_func_1(struct _Tcp1_Texpr *_Lexpr_0);
#endif
#ifndef _Tcp1_Texpr_i_Fwrite_metafunc_1
void _Tcp1_Texpr_i_Fwrite_metafunc_1(struct _Tcp1_Texpr *_Lexpr_0);
#endif
#ifndef _Tcp1_Texpr_i_Fwrite_str_1
void _Tcp1_Texpr_i_Fwrite_str_1(struct _Tcp1_Texpr *_Lexpr_0);
#endif
#ifndef _Tcp1_Texpr_i_Fwrite_int_1
void _Tcp1_Texpr_i_Fwrite_int_1(struct _Tcp1_Texpr *_Lexpr_0);
#endif
#ifndef _Tcp1_Texpr_i_Fwrite_size_of_type_1
void _Tcp1_Texpr_i_Fwrite_size_of_type_1(struct _Tcp1_Texpr *_Lexpr_0);
#endif
#ifndef _Tcp1_Texpr_i_Fwrite_null_1
void _Tcp1_Texpr_i_Fwrite_null_1(struct _Tcp1_Texpr *_Lexpr_0);
#endif
#ifndef _Tcp1_Texpr_i_Fwrite_index_1
void _Tcp1_Texpr_i_Fwrite_index_1(struct _Tcp1_Texpr *_Lexpr_0);
#endif
char* _Tcp1_Texpr_type_Fcp1_name_1(_Tcp1_Texpr_type _Le_0) {
   cm1_push_u(_Le_0);
   cm1_run(138);
   return cm1_pop_ptr();
}
#ifndef _Tcp1_Texpr_i_Fwrite_value_2
uint8_t _Tcp1_Texpr_i_Fwrite_value_2(_Tcp1_Texpr_i _Le_0, struct _Tcp1_Tvalue *_Lv_1);
#endif
#ifndef _Tcp1_Ttype_info_Fcount_1
void _Tcp1_Ttype_info_Fcount_1(struct _Tcp1_Ttype_info *_Lti_0);
#endif
#ifndef _Tcp1_Tat_Fwrite_type_1
uint8_t _Tcp1_Tat_Fwrite_type_1(_Tcp1_Tat _Ltd_0);
#endif
#ifndef _Tcp1_Tat_Fcount_stars0_2
int32_t _Tcp1_Tat_Fcount_stars0_2(_Tcp1_Tat _Ltd_0, struct _Tcp1_Ttype_info *_Lti_1);
#endif
#ifndef _Tlibcp1_Tfmt_Ff_reserve_cstr_5
void _Tlibcp1_Tfmt_Ff_reserve_cstr_5(struct _Tlibcp1_Tfmt *_Lfmt_0, char *_Lstr_1, int32_t _Llen_full_2, int32_t _Llen_3, struct _Tlibcp1_Tfmt_Tf_cstr *_Lf_4);
#endif
#ifndef _Tcp1_Tdecl_var_data_Fwrite_lvar_2
void _Tcp1_Tdecl_var_data_Fwrite_lvar_2(struct _Tcp1_Tdecl_var_data *_Lvd_0, _Tcp1_Tlvar _Llvar_1);
#endif
#ifndef _Tcp1_Tstmt_Fwrite_1
void _Tcp1_Tstmt_Fwrite_1(struct _Tcp1_Tstmt *_Ls_0);
#endif
#ifndef _Tposix_Tfd_Fopen_4
uint8_t _Tposix_Tfd_Fopen_4(_Tposix_Tfd *_Lfile_0, char *_Lpath_1, _Tposix_Topen_flags _Lflags_2, int32_t _Lmode_3);
#endif
#ifndef _Tcp1_Fread_file_5
void* _Tcp1_Fread_file_5(char *_Lpath_0, int32_t _Ladd_before_1, int32_t _Ladd_after_2, uint64_t _Lmax_size_3, uint64_t *_Lout_size_4);
#endif
#ifndef _Tcp1_Tat_map_Fget_or_insert_4
int32_t _Tcp1_Tat_map_Fget_or_insert_4(struct _Tcp1_Tat_map *_Lm_0, uint32_t _Lparent_and_type_1, _Tcp1_Tid _Lname_2, int32_t _Lval_3);
#endif
#ifndef _Tcp1_Tvar_flags_Frd_2
void _Tcp1_Tvar_flags_Frd_2(_Tcp1_Tvar_flags *_Lf_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Ttype_info_Frd_2
void _Tcp1_Ttype_info_Frd_2(struct _Tcp1_Ttype_info *_Lti_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Texpr_type_Frd_2
void _Tcp1_Texpr_type_Frd_2(_Tcp1_Texpr_type *_Le_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Texpr_i_Falloc_0
_Tcp1_Texpr_i _Tcp1_Texpr_i_Falloc_0();
#endif
#ifndef _Tcp1_Texpr_i_Frd_assign_2
void _Tcp1_Texpr_i_Frd_assign_2(_Tcp1_Texpr_i _Le_idx_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Texpr_i_Frd_compare_2
void _Tcp1_Texpr_i_Frd_compare_2(_Tcp1_Texpr_i _Le_idx_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Texpr_i_Frd_bool_2
void _Tcp1_Texpr_i_Frd_bool_2(_Tcp1_Texpr_i _Le_idx_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Texpr_i_Frd_char_2
void _Tcp1_Texpr_i_Frd_char_2(_Tcp1_Texpr_i _Le_idx_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Texpr_i_Frd_math_2
void _Tcp1_Texpr_i_Frd_math_2(_Tcp1_Texpr_i _Le_idx_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Texpr_i_Frd_unary_2
void _Tcp1_Texpr_i_Frd_unary_2(_Tcp1_Texpr_i _Le_idx_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Texpr_i_Frd_ref_2
void _Tcp1_Texpr_i_Frd_ref_2(_Tcp1_Texpr_i _Le_idx_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Texpr_i_Frd_cast_fast_2
void _Tcp1_Texpr_i_Frd_cast_fast_2(_Tcp1_Texpr_i _Le_idx_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Texpr_i_Frd_lvar_2
void _Tcp1_Texpr_i_Frd_lvar_2(_Tcp1_Texpr_i _Le_idx_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Texpr_i_Frd_fvar_2
void _Tcp1_Texpr_i_Frd_fvar_2(_Tcp1_Texpr_i _Le_idx_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Texpr_i_Frd_soa_field_2
void _Tcp1_Texpr_i_Frd_soa_field_2(_Tcp1_Texpr_i _Le_idx_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Texpr_i_Frd_gvar_2
void _Tcp1_Texpr_i_Frd_gvar_2(_Tcp1_Texpr_i _Le_idx_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Texpr_i_Frd_cvar_2
void _Tcp1_Texpr_i_Frd_cvar_2(_Tcp1_Texpr_i _Le_idx_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Texpr_i_Frd_bools_2
void _Tcp1_Texpr_i_Frd_bools_2(_Tcp1_Texpr_i _Le_idx_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Texpr_i_Frd_method_2
void _Tcp1_Texpr_i_Frd_method_2(_Tcp1_Texpr_i _Le_idx_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Texpr_i_Frd_func_2
void _Tcp1_Texpr_i_Frd_func_2(_Tcp1_Texpr_i _Le_idx_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Texpr_i_Frd_str_2
void _Tcp1_Texpr_i_Frd_str_2(_Tcp1_Texpr_i _Le_idx_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Texpr_i_Frd_int_2
void _Tcp1_Texpr_i_Frd_int_2(_Tcp1_Texpr_i _Le_idx_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Texpr_i_Frd_size_of_type_2
void _Tcp1_Texpr_i_Frd_size_of_type_2(_Tcp1_Texpr_i _Le_idx_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Texpr_i_Frd_null_2
void _Tcp1_Texpr_i_Frd_null_2(_Tcp1_Texpr_i _Le_idx_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Texpr_i_Frd_index_2
void _Tcp1_Texpr_i_Frd_index_2(_Tcp1_Texpr_i _Le_idx_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Texpr_i_Frd_metamethod_2
void _Tcp1_Texpr_i_Frd_metamethod_2(_Tcp1_Texpr_i _Le_idx_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Texpr_i_Frd_metafunc_2
void _Tcp1_Texpr_i_Frd_metafunc_2(_Tcp1_Texpr_i _Le_idx_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Texpr_i_Fvalue_4
uint8_t _Tcp1_Texpr_i_Fvalue_4(_Tcp1_Texpr_i _Le_0, int32_t _Lref_1, uint8_t _Lparen_2, struct _Tcp1_Tvalue *_Lv_3);
#endif
#ifndef _Tcp1_Tlvar_flags_Frd_2
void _Tcp1_Tlvar_flags_Frd_2(_Tcp1_Tlvar_flags *_Lf_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Tlvar_Frd_2
void _Tcp1_Tlvar_Frd_2(_Tcp1_Tlvar *_Ll_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Tstmt_type_Frd_2
void _Tcp1_Tstmt_type_Frd_2(_Tcp1_Tstmt_type *_Ls_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Tstmt_space_Frd_expr_2
void _Tcp1_Tstmt_space_Frd_expr_2(struct _Tcp1_Tstmt_space *_Lspace_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Tstmt_space_Frd_if_2
void _Tcp1_Tstmt_space_Frd_if_2(struct _Tcp1_Tstmt_space *_Lspace_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Tstmt_space_Frd_if_elif_2
void _Tcp1_Tstmt_space_Frd_if_elif_2(struct _Tcp1_Tstmt_space *_Lspace_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Tstmt_space_Frd_if_else_2
void _Tcp1_Tstmt_space_Frd_if_else_2(struct _Tcp1_Tstmt_space *_Lspace_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Tstmt_space_Frd_if_end_2
void _Tcp1_Tstmt_space_Frd_if_end_2(struct _Tcp1_Tstmt_space *_Lspace_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Tstmt_space_Frd_switch_2
void _Tcp1_Tstmt_space_Frd_switch_2(struct _Tcp1_Tstmt_space *_Lspace_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Tstmt_space_Frd_case_2
void _Tcp1_Tstmt_space_Frd_case_2(struct _Tcp1_Tstmt_space *_Lspace_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Tstmt_space_Frd_case_end_2
void _Tcp1_Tstmt_space_Frd_case_end_2(struct _Tcp1_Tstmt_space *_Lspace_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Tstmt_space_Frd_default_2
void _Tcp1_Tstmt_space_Frd_default_2(struct _Tcp1_Tstmt_space *_Lspace_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Tstmt_space_Frd_default_end_2
void _Tcp1_Tstmt_space_Frd_default_end_2(struct _Tcp1_Tstmt_space *_Lspace_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Tstmt_space_Frd_switch_end_2
void _Tcp1_Tstmt_space_Frd_switch_end_2(struct _Tcp1_Tstmt_space *_Lspace_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Tstmt_space_Frd_loop_2
void _Tcp1_Tstmt_space_Frd_loop_2(struct _Tcp1_Tstmt_space *_Lspace_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Tstmt_space_Frd_loop_end_2
void _Tcp1_Tstmt_space_Frd_loop_end_2(struct _Tcp1_Tstmt_space *_Lspace_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Tstmt_space_Frd_continue_2
void _Tcp1_Tstmt_space_Frd_continue_2(struct _Tcp1_Tstmt_space *_Lspace_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Tstmt_space_Frd_break_2
void _Tcp1_Tstmt_space_Frd_break_2(struct _Tcp1_Tstmt_space *_Lspace_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Tstmt_space_Frd_return_2
void _Tcp1_Tstmt_space_Frd_return_2(struct _Tcp1_Tstmt_space *_Lspace_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Tstmt_space_Frd_space_2
void _Tcp1_Tstmt_space_Frd_space_2(struct _Tcp1_Tstmt_space *_Lspace_0, union _Tcp1_Trdr *_Lr_1);
#endif
char* _Tcp1_Tstmt_type_Fcp1_name_1(_Tcp1_Tstmt_type _Le_0) {
   cm1_push_u(_Le_0);
   cm1_run(196);
   return cm1_pop_ptr();
}
#ifndef _Tcp1_Tstmt_Fprocess_expr_2
void _Tcp1_Tstmt_Fprocess_expr_2(struct _Tcp1_Tstmt *_Lstmt_0, uint8_t *_Lok_1);
#endif
#ifndef _Tcp1_Tstmt_Fprocess_if_2
void _Tcp1_Tstmt_Fprocess_if_2(struct _Tcp1_Tstmt *_Lstmt_0, uint8_t *_Lok_1);
#endif
#ifndef _Tcp1_Tstmt_Fprocess_if_elif_2
void _Tcp1_Tstmt_Fprocess_if_elif_2(struct _Tcp1_Tstmt *_Lstmt_0, uint8_t *_Lok_1);
#endif
#ifndef _Tcp1_Tstmt_Fprocess_if_else_2
void _Tcp1_Tstmt_Fprocess_if_else_2(struct _Tcp1_Tstmt *_Lstmt_0, uint8_t *_Lok_1);
#endif
#ifndef _Tcp1_Tstmt_Fprocess_if_end_2
void _Tcp1_Tstmt_Fprocess_if_end_2(struct _Tcp1_Tstmt *_Lstmt_0, uint8_t *_Lok_1);
#endif
#ifndef _Tcp1_Tstmt_Fprocess_switch_2
void _Tcp1_Tstmt_Fprocess_switch_2(struct _Tcp1_Tstmt *_Lstmt_0, uint8_t *_Lok_1);
#endif
#ifndef _Tcp1_Tstmt_Fprocess_case_2
void _Tcp1_Tstmt_Fprocess_case_2(struct _Tcp1_Tstmt *_Lstmt_0, uint8_t *_Lok_1);
#endif
#ifndef _Tcp1_Tstmt_Fprocess_case_end_2
void _Tcp1_Tstmt_Fprocess_case_end_2(struct _Tcp1_Tstmt *_Lstmt_0, uint8_t *_Lok_1);
#endif
#ifndef _Tcp1_Tstmt_Fprocess_default_2
void _Tcp1_Tstmt_Fprocess_default_2(struct _Tcp1_Tstmt *_Lstmt_0, uint8_t *_Lok_1);
#endif
#ifndef _Tcp1_Tstmt_Fprocess_default_end_2
void _Tcp1_Tstmt_Fprocess_default_end_2(struct _Tcp1_Tstmt *_Lstmt_0, uint8_t *_Lok_1);
#endif
#ifndef _Tcp1_Tstmt_Fprocess_switch_end_2
void _Tcp1_Tstmt_Fprocess_switch_end_2(struct _Tcp1_Tstmt *_Lstmt_0, uint8_t *_Lok_1);
#endif
#ifndef _Tcp1_Tstmt_Fprocess_loop_2
void _Tcp1_Tstmt_Fprocess_loop_2(struct _Tcp1_Tstmt *_Lstmt_0, uint8_t *_Lok_1);
#endif
#ifndef _Tcp1_Tstmt_Fprocess_loop_end_2
void _Tcp1_Tstmt_Fprocess_loop_end_2(struct _Tcp1_Tstmt *_Lstmt_0, uint8_t *_Lok_1);
#endif
#ifndef _Tcp1_Tstmt_Fprocess_continue_2
void _Tcp1_Tstmt_Fprocess_continue_2(struct _Tcp1_Tstmt *_Lstmt_0, uint8_t *_Lok_1);
#endif
#ifndef _Tcp1_Tstmt_Fprocess_break_2
void _Tcp1_Tstmt_Fprocess_break_2(struct _Tcp1_Tstmt *_Lstmt_0, uint8_t *_Lok_1);
#endif
#ifndef _Tcp1_Tstmt_Fprocess_return_2
void _Tcp1_Tstmt_Fprocess_return_2(struct _Tcp1_Tstmt *_Lstmt_0, uint8_t *_Lok_1);
#endif
#ifndef _Tcp1_Tstmt_Fprocess_space_2
void _Tcp1_Tstmt_Fprocess_space_2(struct _Tcp1_Tstmt *_Lstmt_0, uint8_t *_Lok_1);
#endif
#ifndef _Tcp1_Texpr_i_Fprocess_assign_2
void _Tcp1_Texpr_i_Fprocess_assign_2(struct _Tcp1_Texpr *_Lexpr_0, uint8_t *_Lok_1);
#endif
#ifndef _Tcp1_Texpr_i_Fprocess_compare_2
void _Tcp1_Texpr_i_Fprocess_compare_2(struct _Tcp1_Texpr *_Lexpr_0, uint8_t *_Lok_1);
#endif
#ifndef _Tcp1_Texpr_i_Fprocess_bool_2
void _Tcp1_Texpr_i_Fprocess_bool_2(struct _Tcp1_Texpr *_Lexpr_0, uint8_t *_Lok_1);
#endif
#ifndef _Tcp1_Texpr_i_Fprocess_char_2
void _Tcp1_Texpr_i_Fprocess_char_2(struct _Tcp1_Texpr *_Lexpr_0, uint8_t *_Lok_1);
#endif
#ifndef _Tcp1_Texpr_i_Fprocess_math_2
void _Tcp1_Texpr_i_Fprocess_math_2(struct _Tcp1_Texpr *_Lexpr_0, uint8_t *_Lok_1);
#endif
#ifndef _Tcp1_Texpr_i_Fprocess_unary_2
void _Tcp1_Texpr_i_Fprocess_unary_2(struct _Tcp1_Texpr *_Lexpr_0, uint8_t *_Lok_1);
#endif
#ifndef _Tcp1_Texpr_i_Fprocess_ref_2
void _Tcp1_Texpr_i_Fprocess_ref_2(struct _Tcp1_Texpr *_Lexpr_0, uint8_t *_Lok_1);
#endif
#ifndef _Tcp1_Texpr_i_Fprocess_cast_fast_2
void _Tcp1_Texpr_i_Fprocess_cast_fast_2(struct _Tcp1_Texpr *_Lexpr_0, uint8_t *_Lok_1);
#endif
#ifndef _Tcp1_Texpr_i_Fprocess_lvar_2
void _Tcp1_Texpr_i_Fprocess_lvar_2(struct _Tcp1_Texpr *_Lexpr_0, uint8_t *_Lok_1);
#endif
#ifndef _Tcp1_Texpr_i_Fprocess_fvar_2
void _Tcp1_Texpr_i_Fprocess_fvar_2(struct _Tcp1_Texpr *_Lexpr_0, uint8_t *_Lok_1);
#endif
#ifndef _Tcp1_Texpr_i_Fprocess_soa_field_2
void _Tcp1_Texpr_i_Fprocess_soa_field_2(struct _Tcp1_Texpr *_Lexpr_0, uint8_t *_Lok_1);
#endif
#ifndef _Tcp1_Texpr_i_Fprocess_gvar_2
void _Tcp1_Texpr_i_Fprocess_gvar_2(struct _Tcp1_Texpr *_Lexpr_0, uint8_t *_Lok_1);
#endif
#ifndef _Tcp1_Texpr_i_Fprocess_cvar_2
void _Tcp1_Texpr_i_Fprocess_cvar_2(struct _Tcp1_Texpr *_Lexpr_0, uint8_t *_Lok_1);
#endif
#ifndef _Tcp1_Texpr_i_Fprocess_bools_2
void _Tcp1_Texpr_i_Fprocess_bools_2(struct _Tcp1_Texpr *_Lexpr_0, uint8_t *_Lok_1);
#endif
#ifndef _Tcp1_Texpr_i_Fprocess_method_2
void _Tcp1_Texpr_i_Fprocess_method_2(struct _Tcp1_Texpr *_Lexpr_0, uint8_t *_Lok_1);
#endif
#ifndef _Tcp1_Texpr_i_Fprocess_func_2
void _Tcp1_Texpr_i_Fprocess_func_2(struct _Tcp1_Texpr *_Lexpr_0, uint8_t *_Lok_1);
#endif
#ifndef _Tcp1_Texpr_i_Fprocess_str_2
void _Tcp1_Texpr_i_Fprocess_str_2(struct _Tcp1_Texpr *_Lexpr_0, uint8_t *_Lok_1);
#endif
#ifndef _Tcp1_Texpr_i_Fprocess_int_2
void _Tcp1_Texpr_i_Fprocess_int_2(struct _Tcp1_Texpr *_Lexpr_0, uint8_t *_Lok_1);
#endif
#ifndef _Tcp1_Texpr_i_Fprocess_size_of_type_2
void _Tcp1_Texpr_i_Fprocess_size_of_type_2(struct _Tcp1_Texpr *_Lexpr_0, uint8_t *_Lok_1);
#endif
#ifndef _Tcp1_Texpr_i_Fprocess_null_2
void _Tcp1_Texpr_i_Fprocess_null_2(struct _Tcp1_Texpr *_Lexpr_0, uint8_t *_Lok_1);
#endif
#ifndef _Tcp1_Texpr_i_Fprocess_index_2
void _Tcp1_Texpr_i_Fprocess_index_2(struct _Tcp1_Texpr *_Lexpr_0, uint8_t *_Lok_1);
#endif
#ifndef _Tcp1_Texpr_i_Fprocess_metamethod_2
void _Tcp1_Texpr_i_Fprocess_metamethod_2(struct _Tcp1_Texpr *_Lexpr_0, uint8_t *_Lok_1);
#endif
#ifndef _Tcp1_Texpr_i_Fprocess_metafunc_2
void _Tcp1_Texpr_i_Fprocess_metafunc_2(struct _Tcp1_Texpr *_Lexpr_0, uint8_t *_Lok_1);
#endif
#ifndef _Tcp1_Fwrite_char_1
void _Tcp1_Fwrite_char_1(char _Lc_0);
#endif
#ifndef _Tcp1_Tdecl_var_data_Fwrite_fvar_1
void _Tcp1_Tdecl_var_data_Fwrite_fvar_1(struct _Tcp1_Tdecl_var_data *_Lvd_0);
#endif
#ifndef _Tcp1_Tgvar_Fwrite_1
void _Tcp1_Tgvar_Fwrite_1(_Tcp1_Tgvar _Lg_0);
#endif
#ifndef _Tcp1_Fwrite_str_node_2
void _Tcp1_Fwrite_str_node_2(int32_t _Llen_0, void *_Lptr_1);
#endif
#ifndef _Tlibcp1_Tfmt_Ff_reserve_Tf32_1_2
void _Tlibcp1_Tfmt_Ff_reserve_Tf32_1_2(float _Li_0, struct _Tlibcp1_Tfmt *_Lfmt_1, struct _Tlibcp1_Tfmt_Tf_f32 *_Lf_2);
#endif
#ifndef _Tlibcp1_Tfmt_Tf_f32_Ff_2
void _Tlibcp1_Tfmt_Tf_f32_Ff_2(struct _Tlibcp1_Tfmt_Tf_f32 *_Lf_0, struct _Tlibcp1_Tfmt *_Lfmt_1);
#endif
#ifndef _Tlibcp1_Tfmt_Ff_reserve_Tf64_1_2
void _Tlibcp1_Tfmt_Ff_reserve_Tf64_1_2(double _Li_0, struct _Tlibcp1_Tfmt *_Lfmt_1, struct _Tlibcp1_Tfmt_Tf_f64 *_Lf_2);
#endif
#ifndef _Tlibcp1_Tfmt_Tf_f64_Ff_2
void _Tlibcp1_Tfmt_Tf_f64_Ff_2(struct _Tlibcp1_Tfmt_Tf_f64 *_Lf_0, struct _Tlibcp1_Tfmt *_Lfmt_1);
#endif
#ifndef _Tlibcp1_Tfmt_Ff_reserve_Tu64_1_2
void _Tlibcp1_Tfmt_Ff_reserve_Tu64_1_2(uint64_t _Lu_0, struct _Tlibcp1_Tfmt *_Lfmt_1, struct _Tlibcp1_Tfmt_Tf_u64 *_Lf_2);
#endif
#ifndef _Tlibcp1_Tfmt_Tf_u64_Ff_2
void _Tlibcp1_Tfmt_Tf_u64_Ff_2(struct _Tlibcp1_Tfmt_Tf_u64 *_Lf_0, struct _Tlibcp1_Tfmt *_Lfmt_1);
#endif
#ifndef _Tcp1_Texpr_cast_fast_Fwrite_value_2
void _Tcp1_Texpr_cast_fast_Fwrite_value_2(struct _Tcp1_Texpr_cast_fast *_Le_0, struct _Tcp1_Tvalue *_Lv_1);
#endif
#ifndef _Tcp1_Tat_Fpointer_1
int32_t _Tcp1_Tat_Fpointer_1(_Tcp1_Tat _Ltd_0);
#endif
#ifndef _Tcp1_Tstmt_Fwrite_expr_1
void _Tcp1_Tstmt_Fwrite_expr_1(struct _Tcp1_Tstmt *_Lstmt_0);
#endif
#ifndef _Tcp1_Tstmt_Fwrite_if_1
void _Tcp1_Tstmt_Fwrite_if_1(struct _Tcp1_Tstmt *_Lstmt_0);
#endif
#ifndef _Tcp1_Tstmt_Fwrite_if_elif_1
void _Tcp1_Tstmt_Fwrite_if_elif_1(struct _Tcp1_Tstmt *_Lstmt_0);
#endif
#ifndef _Tcp1_Tstmt_Fwrite_if_else_1
void _Tcp1_Tstmt_Fwrite_if_else_1(struct _Tcp1_Tstmt *_Lstmt_0);
#endif
#ifndef _Tcp1_Tstmt_Fwrite_if_end_1
void _Tcp1_Tstmt_Fwrite_if_end_1(struct _Tcp1_Tstmt *_Lstmt_0);
#endif
#ifndef _Tcp1_Tstmt_Fwrite_switch_1
void _Tcp1_Tstmt_Fwrite_switch_1(struct _Tcp1_Tstmt *_Lstmt_0);
#endif
#ifndef _Tcp1_Tstmt_Fwrite_case_1
void _Tcp1_Tstmt_Fwrite_case_1(struct _Tcp1_Tstmt *_Lstmt_0);
#endif
#ifndef _Tcp1_Tstmt_Fwrite_case_end_1
void _Tcp1_Tstmt_Fwrite_case_end_1(struct _Tcp1_Tstmt *_Lstmt_0);
#endif
#ifndef _Tcp1_Tstmt_Fwrite_default_1
void _Tcp1_Tstmt_Fwrite_default_1(struct _Tcp1_Tstmt *_Lstmt_0);
#endif
#ifndef _Tcp1_Tstmt_Fwrite_default_end_1
void _Tcp1_Tstmt_Fwrite_default_end_1(struct _Tcp1_Tstmt *_Lstmt_0);
#endif
#ifndef _Tcp1_Tstmt_Fwrite_switch_end_1
void _Tcp1_Tstmt_Fwrite_switch_end_1(struct _Tcp1_Tstmt *_Lstmt_0);
#endif
#ifndef _Tcp1_Tstmt_Fwrite_loop_1
void _Tcp1_Tstmt_Fwrite_loop_1(struct _Tcp1_Tstmt *_Lstmt_0);
#endif
#ifndef _Tcp1_Tstmt_Fwrite_loop_end_1
void _Tcp1_Tstmt_Fwrite_loop_end_1(struct _Tcp1_Tstmt *_Lstmt_0);
#endif
#ifndef _Tcp1_Tstmt_Fwrite_continue_1
void _Tcp1_Tstmt_Fwrite_continue_1(struct _Tcp1_Tstmt *_Lstmt_0);
#endif
#ifndef _Tcp1_Tstmt_Fwrite_break_1
void _Tcp1_Tstmt_Fwrite_break_1(struct _Tcp1_Tstmt *_Lstmt_0);
#endif
#ifndef _Tcp1_Tstmt_Fwrite_return_1
void _Tcp1_Tstmt_Fwrite_return_1(struct _Tcp1_Tstmt *_Lstmt_0);
#endif
#ifndef _Tcp1_Tstmt_Fwrite_space_1
void _Tcp1_Tstmt_Fwrite_space_1(struct _Tcp1_Tstmt *_Lstmt_0);
#endif
#ifndef _Tposix_Tfd_Fopen_3
uint8_t _Tposix_Tfd_Fopen_3(_Tposix_Tfd *_Lfile_0, char *_Lpath_1, _Tposix_Topen_flags _Lflags_2);
#endif
#ifndef _Tcp1_Texpr_i_Fset_3
void _Tcp1_Texpr_i_Fset_3(_Tcp1_Texpr_i _Le_0, struct _Tcp1_Texpr *_Lexpr_1, _Tcp1_Texpr_type _Ltype_2);
#endif
#ifndef _Tcp1_Tassign_Frd_2
void _Tcp1_Tassign_Frd_2(_Tcp1_Tassign *_Ls_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Tcompare_Frd_2
void _Tcp1_Tcompare_Frd_2(_Tcp1_Tcompare *_Le_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Texpr_i_Fset_bool_2
void _Tcp1_Texpr_i_Fset_bool_2(_Tcp1_Texpr_i _Le_idx_0, uint8_t _Lval_1);
#endif
#ifndef _Tcp1_Tmath_Frd_2
void _Tcp1_Tmath_Frd_2(_Tcp1_Tmath *_Le_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Tunary_Frd_2
void _Tcp1_Tunary_Frd_2(_Tcp1_Tunary *_Lu_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Texpr_i_Fset_fvar_3
void _Tcp1_Texpr_i_Fset_fvar_3(_Tcp1_Texpr_i _Le_idx_0, _Tcp1_Texpr_i _Lexpr_1, _Tcp1_Tid _Lmember_2);
#endif
#ifndef _Tcp1_Texpr_i_Fset_gvar_3
void _Tcp1_Texpr_i_Fset_gvar_3(_Tcp1_Texpr_i _Le_idx_0, _Tcp1_Tat _Lat_idx_1, _Tcp1_Tid _Lname_2);
#endif
#ifndef _Tcp1_Texpr_i_Fset_cvar_3
void _Tcp1_Texpr_i_Fset_cvar_3(_Tcp1_Texpr_i _Le_idx_0, _Tcp1_Tat _Lat_1, _Tcp1_Tid _Lname_2);
#endif
#ifndef _Tcp1_Tbools_Frd_2
void _Tcp1_Tbools_Frd_2(_Tcp1_Tbools *_Le_0, union _Tcp1_Trdr *_Lr_1);
#endif
#ifndef _Tcp1_Texpr_i_Fset_method_8
void _Tcp1_Texpr_i_Fset_method_8(_Tcp1_Texpr_i _Le_idx_0, _Tcp1_Texpr_i _Lthis_expr_1, _Tcp1_Tid _Lfunc_name_2, uint8_t _Langle_3, uint8_t _Lgroup_c_4, uint8_t *_Lgroup_v_5, uint8_t _Lcarg_c_6, _Tcp1_Texpr_i *_Lcarg_v_7);
#endif
#ifndef _Tcp1_Texpr_i_Fset_func_8
void _Tcp1_Texpr_i_Fset_func_8(_Tcp1_Texpr_i _Le_idx_0, _Tcp1_Tat _Lat_idx_1, _Tcp1_Tid _Lfunc_name_2, uint8_t _Langle_3, uint8_t _Lgroup_c_4, uint8_t *_Lgroup_v_5, uint8_t _Lcarg_c_6, _Tcp1_Texpr_i *_Lcarg_v_7);
#endif
#ifndef _Tcp1_Trdr_Fcopy_3
void _Tcp1_Trdr_Fcopy_3(union _Tcp1_Trdr *_Lr_0, void *_Ldata_1, int32_t _Lsize_2);
#endif
#ifndef _Tcp1_Trdr_Ff4_1
float _Tcp1_Trdr_Ff4_1(union _Tcp1_Trdr *_Lr_0);
#endif
#ifndef _Tcp1_Trdr_Ff8_1
double _Tcp1_Trdr_Ff8_1(union _Tcp1_Trdr *_Lr_0);
#endif
#ifndef _Tcp1_Texpr_i_Fset_index_3
void _Tcp1_Texpr_i_Fset_index_3(_Tcp1_Texpr_i _Le_idx_0, _Tcp1_Texpr_i _Lleft_1, _Tcp1_Texpr_i _Lright_2);
#endif
#ifndef _Tcp1_Texpr_str_Flen_1
uint32_t _Tcp1_Texpr_str_Flen_1(struct _Tcp1_Texpr_str *_Ls_0);
#endif
#ifndef _Tcp1_Texpr_i_Fvalue_assign_5
void _Tcp1_Texpr_i_Fvalue_assign_5(_Tcp1_Texpr_i _Le_0, int8_t _Lref_1, uint8_t _Lparen_2, struct _Tcp1_Tvalue *_Lv_3, uint8_t *_Lok_4);
#endif
#ifndef _Tcp1_Texpr_i_Fvalue_compare_5
void _Tcp1_Texpr_i_Fvalue_compare_5(_Tcp1_Texpr_i _Le_0, int8_t _Lref_1, uint8_t _Lparen_2, struct _Tcp1_Tvalue *_Lv_3, uint8_t *_Lok_4);
#endif
#ifndef _Tcp1_Texpr_i_Fvalue_bool_5
void _Tcp1_Texpr_i_Fvalue_bool_5(_Tcp1_Texpr_i _Lle_0, int32_t _Lref_1, uint8_t _Lparen_2, struct _Tcp1_Tvalue *_Lv_3, uint8_t *_Lok_4);
#endif
#ifndef _Tcp1_Texpr_i_Fvalue_char_5
void _Tcp1_Texpr_i_Fvalue_char_5(_Tcp1_Texpr_i _Lle_0, int32_t _Lref_1, uint8_t _Lparen_2, struct _Tcp1_Tvalue *_Lv_3, uint8_t *_Lok_4);
#endif
#ifndef _Tcp1_Texpr_i_Fvalue_math_5
void _Tcp1_Texpr_i_Fvalue_math_5(_Tcp1_Texpr_i _Le_0, int8_t _Lref_1, uint8_t _Lparen_2, struct _Tcp1_Tvalue *_Lv_3, uint8_t *_Lok_4);
#endif
#ifndef _Tcp1_Texpr_i_Fvalue_unary_5
void _Tcp1_Texpr_i_Fvalue_unary_5(_Tcp1_Texpr_i _Le_0, int8_t _Lref_1, uint8_t _Lparen_2, struct _Tcp1_Tvalue *_Lv_3, uint8_t *_Lok_4);
#endif
#ifndef _Tcp1_Texpr_i_Fvalue_ref_5
void _Tcp1_Texpr_i_Fvalue_ref_5(_Tcp1_Texpr_i _Le_0, int8_t _Lref_1, uint8_t _Lparen_2, struct _Tcp1_Tvalue *_Lv_3, uint8_t *_Lok_4);
#endif
#ifndef _Tcp1_Texpr_i_Fvalue_cast_fast_5
void _Tcp1_Texpr_i_Fvalue_cast_fast_5(_Tcp1_Texpr_i _Le_0, int8_t _Lref_1, uint8_t _Lparen_2, struct _Tcp1_Tvalue *_Lv_3, uint8_t *_Lok_4);
#endif
#ifndef _Tcp1_Texpr_i_Fvalue_lvar_5
void _Tcp1_Texpr_i_Fvalue_lvar_5(_Tcp1_Texpr_i _Le_0, int8_t _Lref_1, uint8_t _Lparen_2, struct _Tcp1_Tvalue *_Lv_3, uint8_t *_Lok_4);
#endif
#ifndef _Tcp1_Texpr_i_Fvalue_fvar_5
void _Tcp1_Texpr_i_Fvalue_fvar_5(_Tcp1_Texpr_i _Lexpr_0, int8_t _Lref_1, uint8_t _Lparen_2, struct _Tcp1_Tvalue *_Lv_3, uint8_t *_Lok_4);
#endif
#ifndef _Tcp1_Texpr_i_Fvalue_soa_field_5
void _Tcp1_Texpr_i_Fvalue_soa_field_5(_Tcp1_Texpr_i _Lexpr_0, int8_t _Lref_1, uint8_t _Lparen_2, struct _Tcp1_Tvalue *_Lv_3, uint8_t *_Lok_4);
#endif
#ifndef _Tcp1_Texpr_i_Fvalue_gvar_5
void _Tcp1_Texpr_i_Fvalue_gvar_5(_Tcp1_Texpr_i _Lg_0, int32_t _Lref_1, uint8_t _Lparen_2, struct _Tcp1_Tvalue *_Lv_3, uint8_t *_Lok_4);
#endif
#ifndef _Tcp1_Texpr_i_Fvalue_cvar_5
void _Tcp1_Texpr_i_Fvalue_cvar_5(_Tcp1_Texpr_i _Le_0, int8_t _Lref_1, uint8_t _Lparen_2, struct _Tcp1_Tvalue *_Lv_3, uint8_t *_Lok_4);
#endif
#ifndef _Tcp1_Texpr_i_Fvalue_bools_5
void _Tcp1_Texpr_i_Fvalue_bools_5(_Tcp1_Texpr_i _Le_0, int32_t _Lref_1, uint8_t _Lparen_2, struct _Tcp1_Tvalue *_Lv_3, uint8_t *_Lok_4);
#endif
#ifndef _Tcp1_Texpr_i_Fvalue_func_5
void _Tcp1_Texpr_i_Fvalue_func_5(_Tcp1_Texpr_i _Le_0, int32_t _Lref_1, uint8_t _Lparen_2, struct _Tcp1_Tvalue *_Lv_3, uint8_t *_Lok_4);
#endif
#ifndef _Tcp1_Texpr_i_Fvalue_method_5
void _Tcp1_Texpr_i_Fvalue_method_5(_Tcp1_Texpr_i _Le_0, int32_t _Lref_1, uint8_t _Lparen_2, struct _Tcp1_Tvalue *_Lv_3, uint8_t *_Lok_4);
#endif
#ifndef _Tcp1_Texpr_i_Fvalue_str_5
void _Tcp1_Texpr_i_Fvalue_str_5(_Tcp1_Texpr_i _Ls_0, int32_t _Lref_1, uint8_t _Lparen_2, struct _Tcp1_Tvalue *_Lv_3, uint8_t *_Lok_4);
#endif
#ifndef _Tcp1_Texpr_i_Fvalue_int_5
void _Tcp1_Texpr_i_Fvalue_int_5(_Tcp1_Texpr_i _Lle_0, int32_t _Lref_1, uint8_t _Lparen_2, struct _Tcp1_Tvalue *_Lv_3, uint8_t *_Lok_4);
#endif
#ifndef _Tcp1_Texpr_i_Fvalue_size_of_type_5
void _Tcp1_Texpr_i_Fvalue_size_of_type_5(_Tcp1_Texpr_i _Lle_0, int32_t _Lref_1, uint8_t _Lparen_2, struct _Tcp1_Tvalue *_Lv_3, uint8_t *_Lok_4);
#endif
#ifndef _Tcp1_Texpr_i_Fvalue_null_5
void _Tcp1_Texpr_i_Fvalue_null_5(_Tcp1_Texpr_i _Lle_0, int32_t _Lref_1, uint8_t _Lparen_2, struct _Tcp1_Tvalue *_Lv_3, uint8_t *_Lok_4);
#endif
#ifndef _Tcp1_Texpr_i_Fvalue_index_5
void _Tcp1_Texpr_i_Fvalue_index_5(_Tcp1_Texpr_i _Le_0, int8_t _Lref_1, uint8_t _Lparen_2, struct _Tcp1_Tvalue *_Lv_3, uint8_t *_Lok_4);
#endif
#ifndef _Tcp1_Tstmt_space_Fstmt_push_7
void _Tcp1_Tstmt_space_Fstmt_push_7(struct _Tcp1_Tstmt_space *_Ls_0, struct _Tcp1_Tstmt *_Ls2_1, uint32_t _Lbegin_row_2, uint32_t _Lbegin_col_3, uint32_t _Lend_row_4, uint32_t _Lend_col_5, _Tcp1_Tstmt_type _Ltype_6);
#endif
#ifndef _Tcp1_Texpr_i_Ftype_1
_Tcp1_Tat _Tcp1_Texpr_i_Ftype_1(_Tcp1_Texpr_i _Le_0);
#endif
#ifndef _Tcp1_Texpr_i_Fprocess_case_func_2
uint8_t _Tcp1_Texpr_i_Fprocess_case_func_2(struct _Tcp1_Texpr *_Lexpr_0, _Tcp1_Tfunc _Lf_idx_1);
#endif
#ifndef _Tcp1_Tstmt_space_Fprocess_1
uint8_t _Tcp1_Tstmt_space_Fprocess_1(struct _Tcp1_Tstmt_space *_Lspace_0);
#endif
#ifndef _Tcp1_Texpr_i_Ftry_deduce_2
void _Tcp1_Texpr_i_Ftry_deduce_2(_Tcp1_Texpr_i _Le_idx_0, _Tcp1_Tat _Lat_1);
#endif
#ifndef _Tcp1_Ttype_info_Finit_1
void _Tcp1_Ttype_info_Finit_1(struct _Tcp1_Ttype_info *_Lti_0);
#endif
#ifndef _Tcp1_Ttype_info_Fcopy_from_2
void _Tcp1_Ttype_info_Fcopy_from_2(struct _Tcp1_Ttype_info *_Lti_0, struct _Tcp1_Ttype_info *_Lti2_1);
#endif
#ifndef _Tcp1_Fcompatible_4
uint8_t _Tcp1_Fcompatible_4(_Tcp1_Tat _Lsrc_0, uint8_t _Lsrc_c_1, _Tcp1_Tat _Ldes_2, uint8_t _Ldes_c_3);
#endif
#ifndef _Tlibcp1_Tfmt_Ff_reserve_Tu8_1_2
void _Tlibcp1_Tfmt_Ff_reserve_Tu8_1_2(uint8_t _Lu_0, struct _Tlibcp1_Tfmt *_Lfmt_1, struct _Tlibcp1_Tfmt_Tf_u32 *_Lf_2);
#endif
#ifndef _Tcp1_Tgvar_Fprocess_1
uint8_t _Tcp1_Tgvar_Fprocess_1(_Tcp1_Tgvar _Lg_0);
#endif
#ifndef _Tcp1_Fensure_bool_2
uint8_t _Tcp1_Fensure_bool_2(_Tcp1_Tat _Lat_0, _Tcp1_Tbools _Ltype_1);
#endif
#ifndef _Tcp1_Ffarg_process_7
uint8_t _Tcp1_Ffarg_process_7(_Tcp1_Texpr_i *_Le_in_out_0, int8_t _Lca_ref_1, struct _Tcp1_Tvalue *_Lca_value_2, struct _Tcp1_Tdecl_var_data *_Lfd_arg_3, _Tcp1_Tat _Lbase_at_4, int32_t _Larg_num_5, _Tcp1_Tid _Lf_name_6);
#endif
#ifndef _Tcp1_Tdecl_var_data_Fwrite_gvar_2
void _Tcp1_Tdecl_var_data_Fwrite_gvar_2(struct _Tcp1_Tdecl_var_data *_Lvd_0, _Tcp1_Tat _Lat_1);
#endif
#ifndef _Tcp1_Tvalue_Fset_5
void _Tcp1_Tvalue_Fset_5(struct _Tcp1_Tvalue *_Lv_0, int8_t _Lref_1, uint8_t _Lparen_2, _Tcp1_Tat _Ltype_3, struct _Tcp1_Ttype_info *_Linfo_4);
#endif
#ifndef _Tcp1_Texpr_i_Ftype_assign_2
void _Tcp1_Texpr_i_Ftype_assign_2(struct _Tcp1_Texpr *_Lexpr_0, _Tcp1_Tat *_Lat_1);
#endif
#ifndef _Tcp1_Texpr_i_Ftype_compare_2
void _Tcp1_Texpr_i_Ftype_compare_2(struct _Tcp1_Texpr *_Lexpr_0, _Tcp1_Tat *_Lat_1);
#endif
#ifndef _Tcp1_Texpr_i_Ftype_bool_2
void _Tcp1_Texpr_i_Ftype_bool_2(struct _Tcp1_Texpr *_Lexpr_0, _Tcp1_Tat *_Lat_1);
#endif
#ifndef _Tcp1_Texpr_i_Ftype_char_2
void _Tcp1_Texpr_i_Ftype_char_2(struct _Tcp1_Texpr *_Lexpr_0, _Tcp1_Tat *_Lat_1);
#endif
#ifndef _Tcp1_Texpr_i_Ftype_math_2
void _Tcp1_Texpr_i_Ftype_math_2(struct _Tcp1_Texpr *_Lexpr_0, _Tcp1_Tat *_Lat_1);
#endif
#ifndef _Tcp1_Texpr_i_Ftype_unary_2
void _Tcp1_Texpr_i_Ftype_unary_2(struct _Tcp1_Texpr *_Lexpr_0, _Tcp1_Tat *_Lat_1);
#endif
#ifndef _Tcp1_Texpr_i_Ftype_ref_2
void _Tcp1_Texpr_i_Ftype_ref_2(struct _Tcp1_Texpr *_Lexpr_0, _Tcp1_Tat *_Lat_1);
#endif
#ifndef _Tcp1_Texpr_i_Ftype_cast_fast_2
void _Tcp1_Texpr_i_Ftype_cast_fast_2(struct _Tcp1_Texpr *_Lexpr_0, _Tcp1_Tat *_Lat_1);
#endif
#ifndef _Tcp1_Texpr_i_Ftype_lvar_2
void _Tcp1_Texpr_i_Ftype_lvar_2(struct _Tcp1_Texpr *_Lexpr_0, _Tcp1_Tat *_Lat_1);
#endif
#ifndef _Tcp1_Texpr_i_Ftype_fvar_2
void _Tcp1_Texpr_i_Ftype_fvar_2(struct _Tcp1_Texpr *_Lexpr_0, _Tcp1_Tat *_Lat_1);
#endif
#ifndef _Tcp1_Texpr_i_Ftype_soa_field_2
void _Tcp1_Texpr_i_Ftype_soa_field_2(struct _Tcp1_Texpr *_Lexpr_0, _Tcp1_Tat *_Lat_1);
#endif
#ifndef _Tcp1_Texpr_i_Ftype_gvar_2
void _Tcp1_Texpr_i_Ftype_gvar_2(struct _Tcp1_Texpr *_Lexpr_0, _Tcp1_Tat *_Lat_1);
#endif
#ifndef _Tcp1_Texpr_i_Ftype_cvar_2
void _Tcp1_Texpr_i_Ftype_cvar_2(struct _Tcp1_Texpr *_Lexpr_0, _Tcp1_Tat *_Lat_1);
#endif
#ifndef _Tcp1_Texpr_i_Ftype_bools_2
void _Tcp1_Texpr_i_Ftype_bools_2(struct _Tcp1_Texpr *_Lexpr_0, _Tcp1_Tat *_Lat_1);
#endif
#ifndef _Tcp1_Texpr_i_Ftype_func_2
void _Tcp1_Texpr_i_Ftype_func_2(struct _Tcp1_Texpr *_Lexpr_0, _Tcp1_Tat *_Lat_1);
#endif
#ifndef _Tcp1_Texpr_i_Ftype_method_2
void _Tcp1_Texpr_i_Ftype_method_2(struct _Tcp1_Texpr *_Lexpr_0, _Tcp1_Tat *_Lat_1);
#endif
#ifndef _Tcp1_Texpr_i_Ftype_int_2
void _Tcp1_Texpr_i_Ftype_int_2(struct _Tcp1_Texpr *_Lexpr_0, _Tcp1_Tat *_Lat_1);
#endif
#ifndef _Tcp1_Texpr_i_Ftype_size_of_type_2
void _Tcp1_Texpr_i_Ftype_size_of_type_2(struct _Tcp1_Texpr *_Lexpr_0, _Tcp1_Tat *_Lat_1);
#endif
#ifndef _Tcp1_Texpr_i_Ftype_null_2
void _Tcp1_Texpr_i_Ftype_null_2(struct _Tcp1_Texpr *_Lexpr_0, _Tcp1_Tat *_Lat_1);
#endif
#ifndef _Tcp1_Texpr_i_Ftype_index_2
void _Tcp1_Texpr_i_Ftype_index_2(struct _Tcp1_Texpr *_Lexpr_0, _Tcp1_Tat *_Lat_1);
#endif
#ifndef _Tcp1_Texpr_i_Ftry_deduce_math_2
void _Tcp1_Texpr_i_Ftry_deduce_math_2(struct _Tcp1_Texpr *_Lexpr_0, _Tcp1_Tat _Lat_1);
#endif
#ifndef _Tcp1_Texpr_i_Ftry_deduce_cvar_2
void _Tcp1_Texpr_i_Ftry_deduce_cvar_2(struct _Tcp1_Texpr *_Lexpr_0, _Tcp1_Tat _Lat_1);
#endif
int32_t _Tcp1_Fmain_2(int32_t _Larg_c_0, char **_Larg_v_1) {
   cm1_push_i(_Larg_c_0);
   cm1_push_ptr(_Larg_v_1);
   cm1_run(5);
   return cm1_pop_i64();
}
void stdout_then_print_error(char *_Lbuf_0, uint32_t _Llen_1) {
write(((_Tposix_Tfd)(1)), _Lbuf_0, _Llen_1);
if(_Tcp1_Gprinted_error) {
return;
}
_Tcp1_Gprinted_error = 1;
int32_t _Li_2;
_Li_2 = ((int32_t)(1));
for(int i = (_Llen_1 - 6) - 1; i > 0; ) {
i --;
if(((_Lbuf_0[_Li_2] == '.') && (_Lbuf_0[(_Li_2 + 1)] == 'c') && (_Lbuf_0[(_Li_2 + 2)] == 'p') && (_Lbuf_0[(_Li_2 + 3)] == '1') && (_Lbuf_0[(_Li_2 + 4)] == ':') && ((_Lbuf_0[(_Li_2 + 5)] >= '0') && (_Lbuf_0[(_Li_2 + 5)] <= '9')))) {
uint32_t _Lline_3 = {0};
_Tposix_Tfd _Lfd_4;
ssize_t _Lsize_5;
char* _Ldata_6;
int32_t _Lcur_line_7;
int32_t _Lk_8;
sscanf(&_Lbuf_0[(_Li_2 + 5)], "%u", &_Lline_3);
_Lbuf_0[(_Li_2 + 4)] = 0;
_Lfd_4 = ((_Tposix_Tfd)(open(_Lbuf_0, 0x0000, 0)));
if(_Lfd_4 == (-1)) {
return;
}
_Lsize_5 = ((ssize_t)(lseek(_Lfd_4, 0, 2)));
lseek(_Lfd_4, 0, 0);
_Ldata_6 = ((char*)(malloc(_Lsize_5 + 1)));
read(_Lfd_4, _Ldata_6, _Lsize_5);
close(_Lfd_4);
_Ldata_6[_Lsize_5] = 0;
_Lcur_line_7 = ((int32_t)(1));
_Lk_8 = ((int32_t)(0));
while(1) {
int32_t _Lj_9;
if(_Ldata_6[_Lk_8] == 0) {
goto break_1;
}
_Lj_9 = ((int32_t)(_Lk_8));
while(1) {
char _Lc_10;
_Lc_10 = ((char)(_Ldata_6[_Lk_8++]));
if(((_Lc_10 == 0) || (_Lc_10 == '\n'))) {
goto break_2;
}
continue_2:;
}
break_2:;
if(_Lline_3 == _Lcur_line_7) {
_Llen_1 = ((_Lk_8 - 1) - _Lj_9);
_Ldata_6[_Llen_1++] = '\n';
write(((_Tposix_Tfd)(1)), &_Ldata_6[_Lj_9], _Llen_1);
free(_Ldata_6);
return;
}
_Lcur_line_7++;
continue_1:;
}
break_1:;
free(_Ldata_6);
return;
}
continue_0:;
_Li_2++;
}
break_0:;
}
void _Tcp1_Foutput_reserve_1(uint32_t _Llen_0) {
   cm1_push_u(_Llen_0);
   cm1_run(6);
   (void)cm1_pop_ptr();
}
void _Tlibcp1_Fstdout_1(struct _Tlibcp1_Tfmt *_Lfmt_0) {
   cm1_push_ptr(_Lfmt_0);
   cm1_run(7);
   (void)cm1_pop_ptr();
}
void _Tlibcp1_Tfmt_Ff_reserve_cstr_4(struct _Tlibcp1_Tfmt *_Lfmt_0, char *_Lstr_1, int32_t _Llen_2, struct _Tlibcp1_Tfmt_Tf_cstr *_Lf_3) {
   cm1_push_ptr(_Lfmt_0);
   cm1_push_ptr(_Lstr_1);
   cm1_push_i(_Llen_2);
   cm1_push_ptr(_Lf_3);
   cm1_run(8);
   (void)cm1_pop_ptr();
}
void _Tlibcp1_Tfmt_Ff_reserve_stdout_1(struct _Tlibcp1_Tfmt *_Lfmt_0) {
   cm1_push_ptr(_Lfmt_0);
   cm1_run(9);
   (void)cm1_pop_ptr();
}
void _Tlibcp1_Tfmt_Tf_cstr_Ff_2(struct _Tlibcp1_Tfmt_Tf_cstr *_Lf_0, struct _Tlibcp1_Tfmt *_Lfmt_1) {
   cm1_push_ptr(_Lf_0);
   cm1_push_ptr(_Lfmt_1);
   cm1_run(10);
   (void)cm1_pop_ptr();
}
void _Tlibcp1_Tfmt_Ff_stdout_1(struct _Tlibcp1_Tfmt *_Lfmt_0) {
   cm1_push_ptr(_Lfmt_0);
   cm1_run(11);
   (void)cm1_pop_ptr();
}
void _Tlibcp1_Tfmt_Ff_reserve_Tchar_1_2(char _Lc_0, struct _Tlibcp1_Tfmt *_Lfmt_1, struct _Tlibcp1_Tfmt_Tf_char *_Lf_2) {
   cm1_push_i(_Lc_0);
   cm1_push_ptr(_Lfmt_1);
   cm1_push_ptr(_Lf_2);
   cm1_run(12);
   (void)cm1_pop_ptr();
}
void _Tlibcp1_Tfmt_Tf_char_Ff_2(struct _Tlibcp1_Tfmt_Tf_char *_Lf_0, struct _Tlibcp1_Tfmt *_Lfmt_1) {
   cm1_push_ptr(_Lf_0);
   cm1_push_ptr(_Lfmt_1);
   cm1_run(13);
   (void)cm1_pop_ptr();
}
void _Tlibcp1_Tfmt_Ff_reserve_arr_Tchar_1_2(char *_Lc_0, struct _Tlibcp1_Tfmt *_Lfmt_1, struct _Tlibcp1_Tfmt_Tf_cstr *_Lf_2) {
   cm1_push_ptr(_Lc_0);
   cm1_push_ptr(_Lfmt_1);
   cm1_push_ptr(_Lf_2);
   cm1_run(14);
   (void)cm1_pop_ptr();
}
struct _Tlibcp1_Tsprintf* _Tlibcp1_Fsprintf_2(char *_Lbuf_0, struct _Tlibcp1_Tsprintf *_Lsf_1) {
   cm1_push_ptr(_Lbuf_0);
   cm1_push_ptr(_Lsf_1);
   cm1_run(15);
   return cm1_pop_ptr();
}
void _Tlibcp1_Tsprintf_Ff_2(struct _Tlibcp1_Tsprintf *_Lsf_0, struct _Tlibcp1_Tfmt *_Lfmt_1) {
   cm1_push_ptr(_Lsf_0);
   cm1_push_ptr(_Lfmt_1);
   cm1_run(16);
   (void)cm1_pop_ptr();
}
void _Tlibcp1_Tfmt_Ff_reserve_sprintf_f_1(struct _Tlibcp1_Tfmt *_Lfmt_0) {
   cm1_push_ptr(_Lfmt_0);
   cm1_run(17);
   (void)cm1_pop_ptr();
}
void _Tlibcp1_Tfmt_Ff_sprintf_f_1(struct _Tlibcp1_Tfmt *_Lfmt_0) {
   cm1_push_ptr(_Lfmt_0);
   cm1_run(18);
   (void)cm1_pop_ptr();
}
void qalloc_undo(int32_t _Lsize_0) {
   cm1_push_i(_Lsize_0);
   cm1_run(19);
   (void)cm1_pop_ptr();
}
void _Tcp1_Fquick_alloc_init_0() {
   cm1_run(20);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tat_data_Finit_4(struct _Tcp1_Tat_data *_Lat_0, _Tcp1_Tname_type _Ltype_1, _Tcp1_Tat _Lparent_2, _Tcp1_Tid _Lname_3) {
   cm1_push_ptr(_Lat_0);
   cm1_push_u(_Ltype_1);
   cm1_push_i(_Lparent_2);
   cm1_push_i(_Lname_3);
   cm1_run(21);
   (void)cm1_pop_ptr();
}
_Tcp1_Tinclude _Tcp1_Finclude_add_2(uint8_t _Linclude_len_0, char *_Linclude_str_1) {
   cm1_push_u(_Linclude_len_0);
   cm1_push_ptr(_Linclude_str_1);
   cm1_run(22);
   return cm1_pop_i64();
}
uint8_t _Tcp1_Tinclude_Fvalidate_2(_Tcp1_Tinclude _Lpath_0, _Tcp1_Tinclude_error *_Lerr_1) {
   cm1_push_i(_Lpath_0);
   cm1_push_ptr(_Lerr_1);
   cm1_run(23);
   return cm1_pop_u64();
}
void _Tlibcp1_Fstdbuf_1(struct _Tlibcp1_Tfmt *_Lfmt_0) {
   cm1_push_ptr(_Lfmt_0);
   cm1_run(24);
   (void)cm1_pop_ptr();
}
void _Tlibcp1_Tfmt_Ff_reserve_stdbuf_1(struct _Tlibcp1_Tfmt *_Lfmt_0) {
   cm1_push_ptr(_Lfmt_0);
   cm1_run(25);
   (void)cm1_pop_ptr();
}
void _Tlibcp1_Tfmt_Ff_stdbuf_1(struct _Tlibcp1_Tfmt *_Lfmt_0) {
   cm1_push_ptr(_Lfmt_0);
   cm1_run(26);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tinclude_error_Fprint_2(_Tcp1_Tinclude_error _Le_0, _Tcp1_Tinclude _Lpath_1) {
   cm1_push_u(_Le_0);
   cm1_push_i(_Lpath_1);
   cm1_run(27);
   (void)cm1_pop_ptr();
}
void _Tcp1_Fimport_3(_Tcp1_Tinclude _Lpath_0, uint8_t _Lrequire_1, _Tcp1_Tfile _Lfile_2) {
   cm1_push_i(_Lpath_0);
   cm1_push_u(_Lrequire_1);
   cm1_push_i(_Lfile_2);
   cm1_run(28);
   (void)cm1_pop_ptr();
}
void _Tcp1_Fread_4(char *_Lin_path_cp1_0, uint16_t _Lin_path_cp1_len_1, uint8_t _Lstrdup_2, uint8_t _Lrequire_3) {
   cm1_push_ptr(_Lin_path_cp1_0);
   cm1_push_u(_Lin_path_cp1_len_1);
   cm1_push_u(_Lstrdup_2);
   cm1_push_u(_Lrequire_3);
   cm1_run(29);
   (void)cm1_pop_ptr();
}
char* _Tcp1_Tinclude_Fstr_1(_Tcp1_Tinclude _Li_0) {
   cm1_push_i(_Li_0);
   cm1_run(30);
   return cm1_pop_ptr();
}
uint8_t _Tcp1_Tinclude_Flen_1(_Tcp1_Tinclude _Li_0) {
   cm1_push_i(_Li_0);
   cm1_run(31);
   return cm1_pop_u64();
}
char* _Tcp1_Tfile_Fpath_1(_Tcp1_Tfile _Lf_0) {
   cm1_push_i(_Lf_0);
   cm1_run(32);
   return cm1_pop_ptr();
}
uint16_t _Tcp1_Tfile_Fpath_len_1(_Tcp1_Tfile _Lf_0) {
   cm1_push_i(_Lf_0);
   cm1_run(33);
   return cm1_pop_u64();
}
char* _Tcp1_Tid_Fstr_1(_Tcp1_Tid _Lid_0) {
   cm1_push_i(_Lid_0);
   cm1_run(34);
   return cm1_pop_ptr();
}
uint8_t _Tcp1_Tid_Flen_1(_Tcp1_Tid _Lid_0) {
   cm1_push_i(_Lid_0);
   cm1_run(35);
   return cm1_pop_u64();
}
void _Tcp1_Fjscode_1(struct _Tlibcp1_Tfmt *_Lfmt_0) {
   cm1_push_ptr(_Lfmt_0);
   cm1_run(36);
   (void)cm1_pop_ptr();
}
void _Tlibcp1_Tfmt_Ff_reserve_arr_Tchar_1_3(char *_Lc_0, int32_t _Llen_1, struct _Tlibcp1_Tfmt *_Lfmt_2, struct _Tlibcp1_Tfmt_Tf_cstr *_Lf_3) {
   cm1_push_ptr(_Lc_0);
   cm1_push_i(_Llen_1);
   cm1_push_ptr(_Lfmt_2);
   cm1_push_ptr(_Lf_3);
   cm1_run(37);
   (void)cm1_pop_ptr();
}
void _Tlibcp1_Tfmt_Ff_reserve_jscode_1(struct _Tlibcp1_Tfmt *_Lfmt_0) {
   cm1_push_ptr(_Lfmt_0);
   cm1_run(38);
   (void)cm1_pop_ptr();
}
void _Tlibcp1_Tfmt_Ff_jscode_1(struct _Tlibcp1_Tfmt *_Lfmt_0) {
   cm1_push_ptr(_Lfmt_0);
   cm1_run(39);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tat_Fjscode_write_1(_Tcp1_Tat _Lat_idx_0) {
   cm1_push_i(_Lat_idx_0);
   cm1_run(40);
   (void)cm1_pop_ptr();
}
struct _Tcp1_Tat_data* _Tcp1_Tat_Fptr_1(_Tcp1_Tat _Li_0) {
   cm1_push_i(_Li_0);
   cm1_run(41);
   return cm1_pop_ptr();
}
void _Tcp1_Tat_Fjscode_write_name_1(_Tcp1_Tat _Lat_idx_0) {
   cm1_push_i(_Lat_idx_0);
   cm1_run(42);
   (void)cm1_pop_ptr();
}
void _Tlibcp1_Tfmt_Ff_reserve_Tu32_1_2(uint32_t _Lu_0, struct _Tlibcp1_Tfmt *_Lfmt_1, struct _Tlibcp1_Tfmt_Tf_u32 *_Lf_2) {
   cm1_push_u(_Lu_0);
   cm1_push_ptr(_Lfmt_1);
   cm1_push_ptr(_Lf_2);
   cm1_run(43);
   (void)cm1_pop_ptr();
}
void _Tlibcp1_Tfmt_Tf_u32_Ff_2(struct _Tlibcp1_Tfmt_Tf_u32 *_Lf_0, struct _Tlibcp1_Tfmt *_Lfmt_1) {
   cm1_push_ptr(_Lf_0);
   cm1_push_ptr(_Lfmt_1);
   cm1_run(44);
   (void)cm1_pop_ptr();
}
void _Tlibcp1_Tfmt_Ff_reserve_Tu16_1_2(uint16_t _Lu_0, struct _Tlibcp1_Tfmt *_Lfmt_1, struct _Tlibcp1_Tfmt_Tf_u32 *_Lf_2) {
   cm1_push_u(_Lu_0);
   cm1_push_ptr(_Lfmt_1);
   cm1_push_ptr(_Lf_2);
   cm1_run(45);
   (void)cm1_pop_ptr();
}
void _Tlibcp1_Tfmt_Ff_reserve_Tfile_1_2(_Tcp1_Tfile _Lid_0, struct _Tlibcp1_Tfmt *_Lfmt_1, struct _Tlibcp1_Tfmt_Tf_cstr *_Lf_2) {
   cm1_push_i(_Lid_0);
   cm1_push_ptr(_Lfmt_1);
   cm1_push_ptr(_Lf_2);
   cm1_run(46);
   (void)cm1_pop_ptr();
}
void _Tlibcp1_Tfmt_Ff_reserve_Tid_1_2(_Tcp1_Tid _Lid_0, struct _Tlibcp1_Tfmt *_Lfmt_1, struct _Tlibcp1_Tfmt_Tf_cstr *_Lf_2) {
   cm1_push_i(_Lid_0);
   cm1_push_ptr(_Lfmt_1);
   cm1_push_ptr(_Lf_2);
   cm1_run(47);
   (void)cm1_pop_ptr();
}
struct _Tcp1_Tdecl_func* _Tcp1_Tfunc_Fptr_1(_Tcp1_Tfunc _Lf_0) {
   cm1_push_i(_Lf_0);
   cm1_run(48);
   return cm1_pop_ptr();
}
struct _Tcp1_Tstruct_data* _Tcp1_Tstruct_Fptr_1(_Tcp1_Tstruct _Ls_0) {
   cm1_push_i(_Ls_0);
   cm1_run(49);
   return cm1_pop_ptr();
}
struct _Tcp1_Tenum_data* _Tcp1_Tenum_Fptr_1(_Tcp1_Tenum _Lf_0) {
   cm1_push_i(_Lf_0);
   cm1_run(50);
   return cm1_pop_ptr();
}
_Tcp1_Tid _Tcp1_Fid_add_2(uint8_t _Lid_len_0, char *_Lid_str_1) {
   cm1_push_u(_Lid_len_0);
   cm1_push_ptr(_Lid_str_1);
   cm1_run(51);
   return cm1_pop_i64();
}
uint8_t _Tcp1_Tfunc_Fprocess_later_1(_Tcp1_Tfunc _Lf_idx_0) {
   cm1_push_i(_Lf_idx_0);
   cm1_run(52);
   return cm1_pop_u64();
}
uint8_t _Tcp1_Tfunc_Fprocess_now_1(_Tcp1_Tfunc _Lf_idx_0) {
   cm1_push_i(_Lf_idx_0);
   cm1_run(53);
   return cm1_pop_u64();
}
uint8_t _Tcp1_Tlvar_Fprocess_1(_Tcp1_Tlvar _Ll_0) {
   cm1_push_i(_Ll_0);
   cm1_run(54);
   return cm1_pop_u64();
}
void _Tcp1_Foutput_1(struct _Tlibcp1_Tfmt *_Lfmt_0) {
   cm1_push_ptr(_Lfmt_0);
   cm1_run(55);
   (void)cm1_pop_ptr();
}
void _Tlibcp1_Tfmt_Ff_reserve_output_1(struct _Tlibcp1_Tfmt *_Lfmt_0) {
   cm1_push_ptr(_Lfmt_0);
   cm1_run(56);
   (void)cm1_pop_ptr();
}
void _Tlibcp1_Tfmt_Ff_output_1(struct _Tlibcp1_Tfmt *_Lfmt_0) {
   cm1_push_ptr(_Lfmt_0);
   cm1_run(57);
   (void)cm1_pop_ptr();
}
struct _Tcp1_Tcvar_data* _Tcp1_Tcvar_Fptr_1(_Tcp1_Tcvar _Lc_0) {
   cm1_push_i(_Lc_0);
   cm1_run(58);
   return cm1_pop_ptr();
}
void _Tcp1_Tinclude_Foutput_1(_Tcp1_Tinclude _Lthis_0) {
   cm1_push_i(_Lthis_0);
   cm1_run(59);
   (void)cm1_pop_ptr();
}
struct _Tcp1_Tdecl_gvar* _Tcp1_Tgvar_Fptr_1(_Tcp1_Tgvar _Lg_0) {
   cm1_push_i(_Lg_0);
   cm1_run(60);
   return cm1_pop_ptr();
}
void _Tcp1_Tat_Foutput_4(_Tcp1_Tat _Lat_i_0, _Tcp1_Tfile _Lfile_1, uint32_t _Lrow_2, uint32_t _Lcol_3) {
   cm1_push_i(_Lat_i_0);
   cm1_push_i(_Lfile_1);
   cm1_push_u(_Lrow_2);
   cm1_push_u(_Lcol_3);
   cm1_run(61);
   (void)cm1_pop_ptr();
}
uint8_t _Tcp1_Tcvar_Fprocess_1(_Tcp1_Tcvar _Lc_0) {
   cm1_push_i(_Lc_0);
   cm1_run(62);
   return cm1_pop_u64();
}
void _Tlibcp1_Tfmt_Ff_reserve_Tinclude_1_2(_Tcp1_Tinclude _Li_0, struct _Tlibcp1_Tfmt *_Lfmt_1, struct _Tlibcp1_Tfmt_Tf_cstr *_Lf_2) {
   cm1_push_i(_Li_0);
   cm1_push_ptr(_Lfmt_1);
   cm1_push_ptr(_Lf_2);
   cm1_run(63);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tcvar_Fwrite_1(_Tcp1_Tcvar _Lc_0) {
   cm1_push_i(_Lc_0);
   cm1_run(64);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fwrite_1(_Tcp1_Texpr_i _Le_0) {
   cm1_push_i(_Le_0);
   cm1_run(65);
   (void)cm1_pop_ptr();
}
void _Tlibcp1_Tfmt_Ff_reserve_Ti32_1_2(int32_t _Li_0, struct _Tlibcp1_Tfmt *_Lfmt_1, struct _Tlibcp1_Tfmt_Tf_i32 *_Lf_2) {
   cm1_push_i(_Li_0);
   cm1_push_ptr(_Lfmt_1);
   cm1_push_ptr(_Lf_2);
   cm1_run(66);
   (void)cm1_pop_ptr();
}
void _Tlibcp1_Tfmt_Tf_i32_Ff_2(struct _Tlibcp1_Tfmt_Tf_i32 *_Lf_0, struct _Tlibcp1_Tfmt *_Lfmt_1) {
   cm1_push_ptr(_Lf_0);
   cm1_push_ptr(_Lfmt_1);
   cm1_run(67);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tat_Fwrite_1(_Tcp1_Tat _Lat_idx_0) {
   cm1_push_i(_Lat_idx_0);
   cm1_run(68);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tat_Fwrite_space_1(_Tcp1_Tat _Lat_idx_0) {
   cm1_push_i(_Lat_idx_0);
   cm1_run(69);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tdecl_var_data_Fwrite_type_fvar_1(struct _Tcp1_Tdecl_var_data *_Lvd_0) {
   cm1_push_ptr(_Lvd_0);
   cm1_run(70);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tdecl_var_data_Fwrite_type_gvar_2(struct _Tcp1_Tdecl_var_data *_Lvd_0, _Tcp1_Tat _Lat_1) {
   cm1_push_ptr(_Lvd_0);
   cm1_push_i(_Lat_1);
   cm1_run(71);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tdecl_func_Fwrite_1(struct _Tcp1_Tdecl_func *_Lf_0) {
   cm1_push_ptr(_Lf_0);
   cm1_run(72);
   (void)cm1_pop_ptr();
}
uint8_t _Tcp1_Tat_Fwrite_type_info_3(_Tcp1_Tat _Ltd_0, struct _Tcp1_Ttype_info *_Lti_1, int32_t _Ladd_2) {
   cm1_push_i(_Ltd_0);
   cm1_push_ptr(_Lti_1);
   cm1_push_i(_Ladd_2);
   cm1_run(73);
   return cm1_pop_u64();
}
void _Tcp1_Tdecl_var_data_Fwrite_lvar_type_2(struct _Tcp1_Tdecl_var_data *_Lvd_0, _Tcp1_Tlvar _Llvar_1) {
   cm1_push_ptr(_Lvd_0);
   cm1_push_i(_Llvar_1);
   cm1_run(74);
   (void)cm1_pop_ptr();
}
struct _Tcp1_Tfile_data* _Tcp1_Tfile_Fptr_1(_Tcp1_Tfile _Lf_0) {
   cm1_push_i(_Lf_0);
   cm1_run(75);
   return cm1_pop_ptr();
}
void _Tlibcp1_Tfmt_Ff_reserve_Tu32_1_3(uint32_t _Lu_0, _Tlibcp1_Tfmt_Tu32_base _Lbase_1, struct _Tlibcp1_Tfmt *_Lfmt_2, struct _Tlibcp1_Tfmt_Tf_u32_base *_Lf_3) {
   cm1_push_u(_Lu_0);
   cm1_push_u(_Lbase_1);
   cm1_push_ptr(_Lfmt_2);
   cm1_push_ptr(_Lf_3);
   cm1_run(76);
   (void)cm1_pop_ptr();
}
void _Tlibcp1_Tfmt_Tf_u32_base_Ff_2(struct _Tlibcp1_Tfmt_Tf_u32_base *_Lf_0, struct _Tlibcp1_Tfmt *_Lfmt_1) {
   cm1_push_ptr(_Lf_0);
   cm1_push_ptr(_Lfmt_1);
   cm1_run(77);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_space_Fwrite_1(struct _Tcp1_Tstmt_space *_Lspace_0) {
   cm1_push_ptr(_Lspace_0);
   cm1_run(78);
   (void)cm1_pop_ptr();
}
uint8_t _Tcp1_Fwrite_file_3(char *_Lpath_0, void *_Ldata_1, uint64_t _Lsize_2) {
   cm1_push_ptr(_Lpath_0);
   cm1_push_ptr(_Ldata_1);
   cm1_push_u(_Lsize_2);
   cm1_run(79);
   return cm1_pop_u64();
}
void* _Tcp1_Fread_file_2(char *_Lpath_0, uint64_t *_Lout_size_1) {
   cm1_push_ptr(_Lpath_0);
   cm1_push_ptr(_Lout_size_1);
   cm1_run(80);
   return cm1_pop_ptr();
}
uint8_t _Tcp1_Trdr_Fn1_1(union _Tcp1_Trdr *_Lr_0) {
   cm1_push_ptr(_Lr_0);
   cm1_run(81);
   return cm1_pop_u64();
}
void _Tcp1_Tname_type_Frd_2(_Tcp1_Tname_type *_Li_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_ptr(_Li_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(82);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tbasic_type_id_Frd_2(_Tcp1_Tbasic_type_id *_Le_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_ptr(_Le_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(83);
   (void)cm1_pop_ptr();
}
_Tcp1_Tat _Tcp1_Fbasic_type_1(_Tcp1_Tbasic_type_id _Lt_0) {
   cm1_push_u(_Lt_0);
   cm1_run(84);
   return cm1_pop_i64();
}
void _Tcp1_Tat_Frd_2(_Tcp1_Tat *_Li_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_ptr(_Li_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(85);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tid_Frd_2(_Tcp1_Tid *_Lid_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_ptr(_Lid_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(86);
   (void)cm1_pop_ptr();
}
int32_t _Tcp1_Tat_map_Fget_or_insert_5(struct _Tcp1_Tat_map *_Lm_0, _Tcp1_Tat _Lparent_1, _Tcp1_Tname_type _Ltype_2, _Tcp1_Tid _Lname_3, int32_t _Lval_4) {
   cm1_push_ptr(_Lm_0);
   cm1_push_i(_Lparent_1);
   cm1_push_u(_Ltype_2);
   cm1_push_i(_Lname_3);
   cm1_push_i(_Lval_4);
   cm1_run(87);
   return cm1_pop_i64();
}
void _Tcp1_Tinclude_Frd_2(_Tcp1_Tinclude *_Li_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_ptr(_Li_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(88);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tdecl_var_data_Frd_2(struct _Tcp1_Tdecl_var_data *_Lvd_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_ptr(_Lvd_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(89);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tcvar_flags_Frd_2(_Tcp1_Tcvar_flags *_Lf_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_ptr(_Lf_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(90);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Frd_2(_Tcp1_Texpr_i *_Le_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_ptr(_Le_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(91);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tcvar_Frd_2(_Tcp1_Tcvar *_Lc_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_ptr(_Lc_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(92);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tenum_flags_Frd_2(_Tcp1_Tenum_flags *_Le_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_ptr(_Le_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(93);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstruct_flags_Frd_2(_Tcp1_Tstruct_flags *_Lf_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_ptr(_Lf_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(94);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tfarg_Frd_2(struct _Tcp1_Tfarg *_Lf_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_ptr(_Lf_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(95);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tfunc_flags_Frd_2(_Tcp1_Tfunc_flags *_Le_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_ptr(_Le_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(96);
   (void)cm1_pop_ptr();
}
void* qalloc(int32_t _Lsize_0) {
   cm1_push_i(_Lsize_0);
   cm1_run(97);
   return cm1_pop_ptr();
}
void _Tcp1_Tfunc_Frd_2(_Tcp1_Tfunc *_Lf_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_ptr(_Lf_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(98);
   (void)cm1_pop_ptr();
}
uint32_t _Tcp1_Trdr_Fn4_1(union _Tcp1_Trdr *_Lr_0) {
   cm1_push_ptr(_Lr_0);
   cm1_run(99);
   return cm1_pop_u64();
}
uint8_t _Tcp1_Trdr_Fb_1(union _Tcp1_Trdr *_Lr_0) {
   cm1_push_ptr(_Lr_0);
   cm1_run(100);
   return cm1_pop_u64();
}
void _Tcp1_Ftemplate_inst_1(struct _Tcp1_Ttemplate_inst_data *_Lti_0) {
   cm1_push_ptr(_Lti_0);
   cm1_run(101);
   (void)cm1_pop_ptr();
}
void _Tcp1_Fjscode_reserve_1(uint32_t _Llen_0) {
   cm1_push_u(_Llen_0);
   cm1_run(102);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tat_Fjscode_write_name_dot_1(_Tcp1_Tat _Lat_idx_0) {
   cm1_push_i(_Lat_idx_0);
   cm1_run(104);
   (void)cm1_pop_ptr();
}
uint8_t _Tcp1_Tdecl_var_data_Fprocess_5(struct _Tcp1_Tdecl_var_data *_Lvd_0, _Tcp1_Tfile _Lfile_1, uint32_t _Lrow_2, uint32_t _Lcol_3, _Tcp1_Tat _Lbase_at_4) {
   cm1_push_ptr(_Lvd_0);
   cm1_push_i(_Lfile_1);
   cm1_push_u(_Lrow_2);
   cm1_push_u(_Lcol_3);
   cm1_push_i(_Lbase_at_4);
   cm1_run(105);
   return cm1_pop_u64();
}
_Tcp1_Tat _Tcp1_Fat_validate_5(_Tcp1_Tat _Lvd_type_0, _Tcp1_Tat _Lat_i_1, _Tcp1_Tfile _Lfile_2, uint32_t _Lrow_3, uint32_t _Lcol_4) {
   cm1_push_i(_Lvd_type_0);
   cm1_push_i(_Lat_i_1);
   cm1_push_i(_Lfile_2);
   cm1_push_u(_Lrow_3);
   cm1_push_u(_Lcol_4);
   cm1_run(106);
   return cm1_pop_i64();
}
uint8_t _Tcp1_Tat_Ffinalize_4(_Tcp1_Tat _Lat_i_0, struct _Tcp1_Ttype_info *_Lti_1, uint32_t _Lrow_2, uint32_t _Lcol_3) {
   cm1_push_i(_Lat_i_0);
   cm1_push_ptr(_Lti_1);
   cm1_push_u(_Lrow_2);
   cm1_push_u(_Lcol_3);
   cm1_run(107);
   return cm1_pop_u64();
}
void _Tcp1_Tdecl_func_Flvars_rd_2(struct _Tcp1_Tdecl_func *_Lf_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_ptr(_Lf_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(108);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_space_Frd_3(struct _Tcp1_Tstmt_space *_Lspace_0, union _Tcp1_Trdr *_Lr_1, struct _Tcp1_Tstmt_space *_Lparent_2) {
   cm1_push_ptr(_Lspace_0);
   cm1_push_ptr(_Lr_1);
   cm1_push_ptr(_Lparent_2);
   cm1_run(109);
   (void)cm1_pop_ptr();
}
uint8_t _Tcp1_Tstmt_Fprocess_1(struct _Tcp1_Tstmt *_Ls_0) {
   cm1_push_ptr(_Ls_0);
   cm1_run(110);
   return cm1_pop_u64();
}
struct _Tcp1_Tlvar_data* _Tcp1_Tlvar_Fptr_1(_Tcp1_Tlvar _Ll_0) {
   cm1_push_i(_Ll_0);
   cm1_run(111);
   return cm1_pop_ptr();
}
void _Tcp1_Tstruct_Foutput_1(_Tcp1_Tstruct _Ls_i_0) {
   cm1_push_i(_Ls_i_0);
   cm1_run(112);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tenum_Foutput_1(_Tcp1_Tenum _Le_i_0) {
   cm1_push_i(_Le_i_0);
   cm1_run(113);
   (void)cm1_pop_ptr();
}
uint8_t _Tcp1_Texpr_i_Fprocess_1(_Tcp1_Texpr_i _Le_0) {
   cm1_push_i(_Le_0);
   cm1_run(114);
   return cm1_pop_u64();
}
char* _Tcp1_Tid_Fc_name_1(_Tcp1_Tid _Lid_0) {
   cm1_push_i(_Lid_0);
   cm1_run(115);
   return cm1_pop_ptr();
}
struct _Tcp1_Texpr* _Tcp1_Texpr_i_Fptr_1(_Tcp1_Texpr_i _Le_0) {
   cm1_push_i(_Le_0);
   cm1_run(116);
   return cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fwrite_assign_1(struct _Tcp1_Texpr *_Lexpr_0) {
   cm1_push_ptr(_Lexpr_0);
   cm1_run(117);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fwrite_compare_1(struct _Tcp1_Texpr *_Lexpr_0) {
   cm1_push_ptr(_Lexpr_0);
   cm1_run(118);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fwrite_bool_1(struct _Tcp1_Texpr *_Lexpr_0) {
   cm1_push_ptr(_Lexpr_0);
   cm1_run(119);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fwrite_char_1(struct _Tcp1_Texpr *_Lexpr_0) {
   cm1_push_ptr(_Lexpr_0);
   cm1_run(120);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fwrite_math_1(struct _Tcp1_Texpr *_Lexpr_0) {
   cm1_push_ptr(_Lexpr_0);
   cm1_run(121);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fwrite_unary_1(struct _Tcp1_Texpr *_Lexpr_0) {
   cm1_push_ptr(_Lexpr_0);
   cm1_run(122);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fwrite_ref_1(struct _Tcp1_Texpr *_Lexpr_0) {
   cm1_push_ptr(_Lexpr_0);
   cm1_run(123);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fwrite_lvar_1(struct _Tcp1_Texpr *_Lexpr_0) {
   cm1_push_ptr(_Lexpr_0);
   cm1_run(124);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fwrite_fvar_1(struct _Tcp1_Texpr *_Lexpr_0) {
   cm1_push_ptr(_Lexpr_0);
   cm1_run(125);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fwrite_soa_field_1(struct _Tcp1_Texpr *_Lexpr_0) {
   cm1_push_ptr(_Lexpr_0);
   cm1_run(126);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fwrite_gvar_1(struct _Tcp1_Texpr *_Lexpr_0) {
   cm1_push_ptr(_Lexpr_0);
   cm1_run(127);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fwrite_cvar_1(struct _Tcp1_Texpr *_Lexpr_0) {
   cm1_push_ptr(_Lexpr_0);
   cm1_run(128);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fwrite_bools_1(struct _Tcp1_Texpr *_Lexpr_0) {
   cm1_push_ptr(_Lexpr_0);
   cm1_run(129);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fwrite_method_1(struct _Tcp1_Texpr *_Lexpr_0) {
   cm1_push_ptr(_Lexpr_0);
   cm1_run(130);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fwrite_func_1(struct _Tcp1_Texpr *_Lexpr_0) {
   cm1_push_ptr(_Lexpr_0);
   cm1_run(131);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fwrite_metafunc_1(struct _Tcp1_Texpr *_Lexpr_0) {
   cm1_push_ptr(_Lexpr_0);
   cm1_run(132);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fwrite_str_1(struct _Tcp1_Texpr *_Lexpr_0) {
   cm1_push_ptr(_Lexpr_0);
   cm1_run(133);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fwrite_int_1(struct _Tcp1_Texpr *_Lexpr_0) {
   cm1_push_ptr(_Lexpr_0);
   cm1_run(134);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fwrite_size_of_type_1(struct _Tcp1_Texpr *_Lexpr_0) {
   cm1_push_ptr(_Lexpr_0);
   cm1_run(135);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fwrite_null_1(struct _Tcp1_Texpr *_Lexpr_0) {
   cm1_push_ptr(_Lexpr_0);
   cm1_run(136);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fwrite_index_1(struct _Tcp1_Texpr *_Lexpr_0) {
   cm1_push_ptr(_Lexpr_0);
   cm1_run(137);
   (void)cm1_pop_ptr();
}
uint8_t _Tcp1_Texpr_i_Fwrite_value_2(_Tcp1_Texpr_i _Le_0, struct _Tcp1_Tvalue *_Lv_1) {
   cm1_push_i(_Le_0);
   cm1_push_ptr(_Lv_1);
   cm1_run(139);
   return cm1_pop_u64();
}
void _Tcp1_Ttype_info_Fcount_1(struct _Tcp1_Ttype_info *_Lti_0) {
   cm1_push_ptr(_Lti_0);
   cm1_run(140);
   (void)cm1_pop_ptr();
}
uint8_t _Tcp1_Tat_Fwrite_type_1(_Tcp1_Tat _Ltd_0) {
   cm1_push_i(_Ltd_0);
   cm1_run(141);
   return cm1_pop_u64();
}
int32_t _Tcp1_Tat_Fcount_stars0_2(_Tcp1_Tat _Ltd_0, struct _Tcp1_Ttype_info *_Lti_1) {
   cm1_push_i(_Ltd_0);
   cm1_push_ptr(_Lti_1);
   cm1_run(142);
   return cm1_pop_i64();
}
void _Tlibcp1_Tfmt_Ff_reserve_cstr_5(struct _Tlibcp1_Tfmt *_Lfmt_0, char *_Lstr_1, int32_t _Llen_full_2, int32_t _Llen_3, struct _Tlibcp1_Tfmt_Tf_cstr *_Lf_4) {
   cm1_push_ptr(_Lfmt_0);
   cm1_push_ptr(_Lstr_1);
   cm1_push_i(_Llen_full_2);
   cm1_push_i(_Llen_3);
   cm1_push_ptr(_Lf_4);
   cm1_run(143);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tdecl_var_data_Fwrite_lvar_2(struct _Tcp1_Tdecl_var_data *_Lvd_0, _Tcp1_Tlvar _Llvar_1) {
   cm1_push_ptr(_Lvd_0);
   cm1_push_i(_Llvar_1);
   cm1_run(144);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_Fwrite_1(struct _Tcp1_Tstmt *_Ls_0) {
   cm1_push_ptr(_Ls_0);
   cm1_run(145);
   (void)cm1_pop_ptr();
}
uint8_t _Tposix_Tfd_Fopen_4(_Tposix_Tfd *_Lfile_0, char *_Lpath_1, _Tposix_Topen_flags _Lflags_2, int32_t _Lmode_3) {
   cm1_push_ptr(_Lfile_0);
   cm1_push_ptr(_Lpath_1);
   cm1_push_i(_Lflags_2);
   cm1_push_i(_Lmode_3);
   cm1_run(146);
   return cm1_pop_u64();
}
void* _Tcp1_Fread_file_5(char *_Lpath_0, int32_t _Ladd_before_1, int32_t _Ladd_after_2, uint64_t _Lmax_size_3, uint64_t *_Lout_size_4) {
   cm1_push_ptr(_Lpath_0);
   cm1_push_i(_Ladd_before_1);
   cm1_push_i(_Ladd_after_2);
   cm1_push_u(_Lmax_size_3);
   cm1_push_ptr(_Lout_size_4);
   cm1_run(147);
   return cm1_pop_ptr();
}
void _Tcp1_Tvar_flags_Frd_2(_Tcp1_Tvar_flags *_Lf_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_ptr(_Lf_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(148);
   (void)cm1_pop_ptr();
}
void _Tcp1_Ttype_info_Frd_2(struct _Tcp1_Ttype_info *_Lti_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_ptr(_Lti_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(149);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_type_Frd_2(_Tcp1_Texpr_type *_Le_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_ptr(_Le_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(150);
   (void)cm1_pop_ptr();
}
_Tcp1_Texpr_i _Tcp1_Texpr_i_Falloc_0() {
   cm1_run(151);
   return cm1_pop_i64();
}
void _Tcp1_Texpr_i_Frd_assign_2(_Tcp1_Texpr_i _Le_idx_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_i(_Le_idx_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(152);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Frd_compare_2(_Tcp1_Texpr_i _Le_idx_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_i(_Le_idx_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(153);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Frd_bool_2(_Tcp1_Texpr_i _Le_idx_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_i(_Le_idx_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(154);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Frd_char_2(_Tcp1_Texpr_i _Le_idx_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_i(_Le_idx_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(155);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Frd_math_2(_Tcp1_Texpr_i _Le_idx_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_i(_Le_idx_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(156);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Frd_unary_2(_Tcp1_Texpr_i _Le_idx_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_i(_Le_idx_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(157);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Frd_ref_2(_Tcp1_Texpr_i _Le_idx_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_i(_Le_idx_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(158);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Frd_cast_fast_2(_Tcp1_Texpr_i _Le_idx_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_i(_Le_idx_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(159);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Frd_lvar_2(_Tcp1_Texpr_i _Le_idx_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_i(_Le_idx_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(160);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Frd_fvar_2(_Tcp1_Texpr_i _Le_idx_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_i(_Le_idx_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(161);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Frd_soa_field_2(_Tcp1_Texpr_i _Le_idx_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_i(_Le_idx_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(162);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Frd_gvar_2(_Tcp1_Texpr_i _Le_idx_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_i(_Le_idx_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(163);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Frd_cvar_2(_Tcp1_Texpr_i _Le_idx_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_i(_Le_idx_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(164);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Frd_bools_2(_Tcp1_Texpr_i _Le_idx_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_i(_Le_idx_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(165);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Frd_method_2(_Tcp1_Texpr_i _Le_idx_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_i(_Le_idx_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(166);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Frd_func_2(_Tcp1_Texpr_i _Le_idx_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_i(_Le_idx_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(167);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Frd_str_2(_Tcp1_Texpr_i _Le_idx_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_i(_Le_idx_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(168);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Frd_int_2(_Tcp1_Texpr_i _Le_idx_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_i(_Le_idx_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(169);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Frd_size_of_type_2(_Tcp1_Texpr_i _Le_idx_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_i(_Le_idx_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(170);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Frd_null_2(_Tcp1_Texpr_i _Le_idx_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_i(_Le_idx_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(171);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Frd_index_2(_Tcp1_Texpr_i _Le_idx_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_i(_Le_idx_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(172);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Frd_metamethod_2(_Tcp1_Texpr_i _Le_idx_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_i(_Le_idx_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(173);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Frd_metafunc_2(_Tcp1_Texpr_i _Le_idx_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_i(_Le_idx_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(174);
   (void)cm1_pop_ptr();
}
uint8_t _Tcp1_Texpr_i_Fvalue_4(_Tcp1_Texpr_i _Le_0, int32_t _Lref_1, uint8_t _Lparen_2, struct _Tcp1_Tvalue *_Lv_3) {
   cm1_push_i(_Le_0);
   cm1_push_i(_Lref_1);
   cm1_push_u(_Lparen_2);
   cm1_push_ptr(_Lv_3);
   cm1_run(175);
   return cm1_pop_u64();
}
void _Tcp1_Tlvar_flags_Frd_2(_Tcp1_Tlvar_flags *_Lf_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_ptr(_Lf_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(176);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tlvar_Frd_2(_Tcp1_Tlvar *_Ll_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_ptr(_Ll_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(177);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_type_Frd_2(_Tcp1_Tstmt_type *_Ls_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_ptr(_Ls_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(178);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_space_Frd_expr_2(struct _Tcp1_Tstmt_space *_Lspace_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_ptr(_Lspace_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(179);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_space_Frd_if_2(struct _Tcp1_Tstmt_space *_Lspace_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_ptr(_Lspace_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(180);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_space_Frd_if_elif_2(struct _Tcp1_Tstmt_space *_Lspace_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_ptr(_Lspace_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(181);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_space_Frd_if_else_2(struct _Tcp1_Tstmt_space *_Lspace_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_ptr(_Lspace_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(182);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_space_Frd_if_end_2(struct _Tcp1_Tstmt_space *_Lspace_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_ptr(_Lspace_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(183);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_space_Frd_switch_2(struct _Tcp1_Tstmt_space *_Lspace_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_ptr(_Lspace_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(184);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_space_Frd_case_2(struct _Tcp1_Tstmt_space *_Lspace_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_ptr(_Lspace_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(185);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_space_Frd_case_end_2(struct _Tcp1_Tstmt_space *_Lspace_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_ptr(_Lspace_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(186);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_space_Frd_default_2(struct _Tcp1_Tstmt_space *_Lspace_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_ptr(_Lspace_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(187);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_space_Frd_default_end_2(struct _Tcp1_Tstmt_space *_Lspace_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_ptr(_Lspace_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(188);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_space_Frd_switch_end_2(struct _Tcp1_Tstmt_space *_Lspace_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_ptr(_Lspace_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(189);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_space_Frd_loop_2(struct _Tcp1_Tstmt_space *_Lspace_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_ptr(_Lspace_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(190);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_space_Frd_loop_end_2(struct _Tcp1_Tstmt_space *_Lspace_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_ptr(_Lspace_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(191);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_space_Frd_continue_2(struct _Tcp1_Tstmt_space *_Lspace_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_ptr(_Lspace_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(192);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_space_Frd_break_2(struct _Tcp1_Tstmt_space *_Lspace_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_ptr(_Lspace_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(193);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_space_Frd_return_2(struct _Tcp1_Tstmt_space *_Lspace_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_ptr(_Lspace_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(194);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_space_Frd_space_2(struct _Tcp1_Tstmt_space *_Lspace_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_ptr(_Lspace_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(195);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_Fprocess_expr_2(struct _Tcp1_Tstmt *_Lstmt_0, uint8_t *_Lok_1) {
   cm1_push_ptr(_Lstmt_0);
   cm1_push_ptr(_Lok_1);
   cm1_run(197);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_Fprocess_if_2(struct _Tcp1_Tstmt *_Lstmt_0, uint8_t *_Lok_1) {
   cm1_push_ptr(_Lstmt_0);
   cm1_push_ptr(_Lok_1);
   cm1_run(198);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_Fprocess_if_elif_2(struct _Tcp1_Tstmt *_Lstmt_0, uint8_t *_Lok_1) {
   cm1_push_ptr(_Lstmt_0);
   cm1_push_ptr(_Lok_1);
   cm1_run(199);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_Fprocess_if_else_2(struct _Tcp1_Tstmt *_Lstmt_0, uint8_t *_Lok_1) {
   cm1_push_ptr(_Lstmt_0);
   cm1_push_ptr(_Lok_1);
   cm1_run(200);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_Fprocess_if_end_2(struct _Tcp1_Tstmt *_Lstmt_0, uint8_t *_Lok_1) {
   cm1_push_ptr(_Lstmt_0);
   cm1_push_ptr(_Lok_1);
   cm1_run(201);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_Fprocess_switch_2(struct _Tcp1_Tstmt *_Lstmt_0, uint8_t *_Lok_1) {
   cm1_push_ptr(_Lstmt_0);
   cm1_push_ptr(_Lok_1);
   cm1_run(202);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_Fprocess_case_2(struct _Tcp1_Tstmt *_Lstmt_0, uint8_t *_Lok_1) {
   cm1_push_ptr(_Lstmt_0);
   cm1_push_ptr(_Lok_1);
   cm1_run(203);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_Fprocess_case_end_2(struct _Tcp1_Tstmt *_Lstmt_0, uint8_t *_Lok_1) {
   cm1_push_ptr(_Lstmt_0);
   cm1_push_ptr(_Lok_1);
   cm1_run(204);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_Fprocess_default_2(struct _Tcp1_Tstmt *_Lstmt_0, uint8_t *_Lok_1) {
   cm1_push_ptr(_Lstmt_0);
   cm1_push_ptr(_Lok_1);
   cm1_run(205);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_Fprocess_default_end_2(struct _Tcp1_Tstmt *_Lstmt_0, uint8_t *_Lok_1) {
   cm1_push_ptr(_Lstmt_0);
   cm1_push_ptr(_Lok_1);
   cm1_run(206);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_Fprocess_switch_end_2(struct _Tcp1_Tstmt *_Lstmt_0, uint8_t *_Lok_1) {
   cm1_push_ptr(_Lstmt_0);
   cm1_push_ptr(_Lok_1);
   cm1_run(207);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_Fprocess_loop_2(struct _Tcp1_Tstmt *_Lstmt_0, uint8_t *_Lok_1) {
   cm1_push_ptr(_Lstmt_0);
   cm1_push_ptr(_Lok_1);
   cm1_run(208);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_Fprocess_loop_end_2(struct _Tcp1_Tstmt *_Lstmt_0, uint8_t *_Lok_1) {
   cm1_push_ptr(_Lstmt_0);
   cm1_push_ptr(_Lok_1);
   cm1_run(209);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_Fprocess_continue_2(struct _Tcp1_Tstmt *_Lstmt_0, uint8_t *_Lok_1) {
   cm1_push_ptr(_Lstmt_0);
   cm1_push_ptr(_Lok_1);
   cm1_run(210);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_Fprocess_break_2(struct _Tcp1_Tstmt *_Lstmt_0, uint8_t *_Lok_1) {
   cm1_push_ptr(_Lstmt_0);
   cm1_push_ptr(_Lok_1);
   cm1_run(211);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_Fprocess_return_2(struct _Tcp1_Tstmt *_Lstmt_0, uint8_t *_Lok_1) {
   cm1_push_ptr(_Lstmt_0);
   cm1_push_ptr(_Lok_1);
   cm1_run(212);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_Fprocess_space_2(struct _Tcp1_Tstmt *_Lstmt_0, uint8_t *_Lok_1) {
   cm1_push_ptr(_Lstmt_0);
   cm1_push_ptr(_Lok_1);
   cm1_run(213);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fprocess_assign_2(struct _Tcp1_Texpr *_Lexpr_0, uint8_t *_Lok_1) {
   cm1_push_ptr(_Lexpr_0);
   cm1_push_ptr(_Lok_1);
   cm1_run(214);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fprocess_compare_2(struct _Tcp1_Texpr *_Lexpr_0, uint8_t *_Lok_1) {
   cm1_push_ptr(_Lexpr_0);
   cm1_push_ptr(_Lok_1);
   cm1_run(215);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fprocess_bool_2(struct _Tcp1_Texpr *_Lexpr_0, uint8_t *_Lok_1) {
   cm1_push_ptr(_Lexpr_0);
   cm1_push_ptr(_Lok_1);
   cm1_run(216);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fprocess_char_2(struct _Tcp1_Texpr *_Lexpr_0, uint8_t *_Lok_1) {
   cm1_push_ptr(_Lexpr_0);
   cm1_push_ptr(_Lok_1);
   cm1_run(217);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fprocess_math_2(struct _Tcp1_Texpr *_Lexpr_0, uint8_t *_Lok_1) {
   cm1_push_ptr(_Lexpr_0);
   cm1_push_ptr(_Lok_1);
   cm1_run(218);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fprocess_unary_2(struct _Tcp1_Texpr *_Lexpr_0, uint8_t *_Lok_1) {
   cm1_push_ptr(_Lexpr_0);
   cm1_push_ptr(_Lok_1);
   cm1_run(219);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fprocess_ref_2(struct _Tcp1_Texpr *_Lexpr_0, uint8_t *_Lok_1) {
   cm1_push_ptr(_Lexpr_0);
   cm1_push_ptr(_Lok_1);
   cm1_run(220);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fprocess_cast_fast_2(struct _Tcp1_Texpr *_Lexpr_0, uint8_t *_Lok_1) {
   cm1_push_ptr(_Lexpr_0);
   cm1_push_ptr(_Lok_1);
   cm1_run(221);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fprocess_lvar_2(struct _Tcp1_Texpr *_Lexpr_0, uint8_t *_Lok_1) {
   cm1_push_ptr(_Lexpr_0);
   cm1_push_ptr(_Lok_1);
   cm1_run(222);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fprocess_fvar_2(struct _Tcp1_Texpr *_Lexpr_0, uint8_t *_Lok_1) {
   cm1_push_ptr(_Lexpr_0);
   cm1_push_ptr(_Lok_1);
   cm1_run(223);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fprocess_soa_field_2(struct _Tcp1_Texpr *_Lexpr_0, uint8_t *_Lok_1) {
   cm1_push_ptr(_Lexpr_0);
   cm1_push_ptr(_Lok_1);
   cm1_run(224);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fprocess_gvar_2(struct _Tcp1_Texpr *_Lexpr_0, uint8_t *_Lok_1) {
   cm1_push_ptr(_Lexpr_0);
   cm1_push_ptr(_Lok_1);
   cm1_run(225);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fprocess_cvar_2(struct _Tcp1_Texpr *_Lexpr_0, uint8_t *_Lok_1) {
   cm1_push_ptr(_Lexpr_0);
   cm1_push_ptr(_Lok_1);
   cm1_run(226);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fprocess_bools_2(struct _Tcp1_Texpr *_Lexpr_0, uint8_t *_Lok_1) {
   cm1_push_ptr(_Lexpr_0);
   cm1_push_ptr(_Lok_1);
   cm1_run(227);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fprocess_method_2(struct _Tcp1_Texpr *_Lexpr_0, uint8_t *_Lok_1) {
   cm1_push_ptr(_Lexpr_0);
   cm1_push_ptr(_Lok_1);
   cm1_run(228);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fprocess_func_2(struct _Tcp1_Texpr *_Lexpr_0, uint8_t *_Lok_1) {
   cm1_push_ptr(_Lexpr_0);
   cm1_push_ptr(_Lok_1);
   cm1_run(229);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fprocess_str_2(struct _Tcp1_Texpr *_Lexpr_0, uint8_t *_Lok_1) {
   cm1_push_ptr(_Lexpr_0);
   cm1_push_ptr(_Lok_1);
   cm1_run(230);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fprocess_int_2(struct _Tcp1_Texpr *_Lexpr_0, uint8_t *_Lok_1) {
   cm1_push_ptr(_Lexpr_0);
   cm1_push_ptr(_Lok_1);
   cm1_run(231);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fprocess_size_of_type_2(struct _Tcp1_Texpr *_Lexpr_0, uint8_t *_Lok_1) {
   cm1_push_ptr(_Lexpr_0);
   cm1_push_ptr(_Lok_1);
   cm1_run(232);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fprocess_null_2(struct _Tcp1_Texpr *_Lexpr_0, uint8_t *_Lok_1) {
   cm1_push_ptr(_Lexpr_0);
   cm1_push_ptr(_Lok_1);
   cm1_run(233);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fprocess_index_2(struct _Tcp1_Texpr *_Lexpr_0, uint8_t *_Lok_1) {
   cm1_push_ptr(_Lexpr_0);
   cm1_push_ptr(_Lok_1);
   cm1_run(234);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fprocess_metamethod_2(struct _Tcp1_Texpr *_Lexpr_0, uint8_t *_Lok_1) {
   cm1_push_ptr(_Lexpr_0);
   cm1_push_ptr(_Lok_1);
   cm1_run(235);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fprocess_metafunc_2(struct _Tcp1_Texpr *_Lexpr_0, uint8_t *_Lok_1) {
   cm1_push_ptr(_Lexpr_0);
   cm1_push_ptr(_Lok_1);
   cm1_run(236);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tdecl_var_data_Fwrite_fvar_1(struct _Tcp1_Tdecl_var_data *_Lvd_0) {
   cm1_push_ptr(_Lvd_0);
   cm1_run(237);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tgvar_Fwrite_1(_Tcp1_Tgvar _Lg_0) {
   cm1_push_i(_Lg_0);
   cm1_run(238);
   (void)cm1_pop_ptr();
}
void _Tlibcp1_Tfmt_Ff_reserve_Tf32_1_2(float _Li_0, struct _Tlibcp1_Tfmt *_Lfmt_1, struct _Tlibcp1_Tfmt_Tf_f32 *_Lf_2) {
   cm1_push_f32(_Li_0);
   cm1_push_ptr(_Lfmt_1);
   cm1_push_ptr(_Lf_2);
   cm1_run(239);
   (void)cm1_pop_ptr();
}
void _Tlibcp1_Tfmt_Tf_f32_Ff_2(struct _Tlibcp1_Tfmt_Tf_f32 *_Lf_0, struct _Tlibcp1_Tfmt *_Lfmt_1) {
(*_Lfmt_1)._Mlen += sprintf(&(*_Lfmt_1)._Mptr[(*_Lfmt_1)._Mlen], "%.9f", (*_Lf_0)._Mf32);
}
void _Tlibcp1_Tfmt_Ff_reserve_Tf64_1_2(double _Li_0, struct _Tlibcp1_Tfmt *_Lfmt_1, struct _Tlibcp1_Tfmt_Tf_f64 *_Lf_2) {
   cm1_push_f64(_Li_0);
   cm1_push_ptr(_Lfmt_1);
   cm1_push_ptr(_Lf_2);
   cm1_run(240);
   (void)cm1_pop_ptr();
}
void _Tlibcp1_Tfmt_Tf_f64_Ff_2(struct _Tlibcp1_Tfmt_Tf_f64 *_Lf_0, struct _Tlibcp1_Tfmt *_Lfmt_1) {
(*_Lfmt_1)._Mlen += sprintf(&(*_Lfmt_1)._Mptr[(*_Lfmt_1)._Mlen], "%.17f", (*_Lf_0)._Mf64);
}
void _Tlibcp1_Tfmt_Ff_reserve_Tu64_1_2(uint64_t _Lu_0, struct _Tlibcp1_Tfmt *_Lfmt_1, struct _Tlibcp1_Tfmt_Tf_u64 *_Lf_2) {
   cm1_push_u(_Lu_0);
   cm1_push_ptr(_Lfmt_1);
   cm1_push_ptr(_Lf_2);
   cm1_run(241);
   (void)cm1_pop_ptr();
}
void _Tlibcp1_Tfmt_Tf_u64_Ff_2(struct _Tlibcp1_Tfmt_Tf_u64 *_Lf_0, struct _Tlibcp1_Tfmt *_Lfmt_1) {
   cm1_push_ptr(_Lf_0);
   cm1_push_ptr(_Lfmt_1);
   cm1_run(242);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_cast_fast_Fwrite_value_2(struct _Tcp1_Texpr_cast_fast *_Le_0, struct _Tcp1_Tvalue *_Lv_1) {
   cm1_push_ptr(_Le_0);
   cm1_push_ptr(_Lv_1);
   cm1_run(243);
   (void)cm1_pop_ptr();
}
int32_t _Tcp1_Tat_Fpointer_1(_Tcp1_Tat _Ltd_0) {
   cm1_push_i(_Ltd_0);
   cm1_run(244);
   return cm1_pop_i64();
}
void _Tcp1_Tstmt_Fwrite_expr_1(struct _Tcp1_Tstmt *_Lstmt_0) {
   cm1_push_ptr(_Lstmt_0);
   cm1_run(245);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_Fwrite_if_1(struct _Tcp1_Tstmt *_Lstmt_0) {
   cm1_push_ptr(_Lstmt_0);
   cm1_run(246);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_Fwrite_if_elif_1(struct _Tcp1_Tstmt *_Lstmt_0) {
   cm1_push_ptr(_Lstmt_0);
   cm1_run(247);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_Fwrite_if_else_1(struct _Tcp1_Tstmt *_Lstmt_0) {
   cm1_push_ptr(_Lstmt_0);
   cm1_run(248);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_Fwrite_if_end_1(struct _Tcp1_Tstmt *_Lstmt_0) {
   cm1_push_ptr(_Lstmt_0);
   cm1_run(249);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_Fwrite_switch_1(struct _Tcp1_Tstmt *_Lstmt_0) {
   cm1_push_ptr(_Lstmt_0);
   cm1_run(250);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_Fwrite_case_1(struct _Tcp1_Tstmt *_Lstmt_0) {
   cm1_push_ptr(_Lstmt_0);
   cm1_run(251);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_Fwrite_case_end_1(struct _Tcp1_Tstmt *_Lstmt_0) {
   cm1_push_ptr(_Lstmt_0);
   cm1_run(252);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_Fwrite_default_1(struct _Tcp1_Tstmt *_Lstmt_0) {
   cm1_push_ptr(_Lstmt_0);
   cm1_run(253);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_Fwrite_default_end_1(struct _Tcp1_Tstmt *_Lstmt_0) {
   cm1_push_ptr(_Lstmt_0);
   cm1_run(254);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_Fwrite_switch_end_1(struct _Tcp1_Tstmt *_Lstmt_0) {
   cm1_push_ptr(_Lstmt_0);
   cm1_run(255);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_Fwrite_loop_1(struct _Tcp1_Tstmt *_Lstmt_0) {
   cm1_push_ptr(_Lstmt_0);
   cm1_run(256);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_Fwrite_loop_end_1(struct _Tcp1_Tstmt *_Lstmt_0) {
   cm1_push_ptr(_Lstmt_0);
   cm1_run(257);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_Fwrite_continue_1(struct _Tcp1_Tstmt *_Lstmt_0) {
   cm1_push_ptr(_Lstmt_0);
   cm1_run(258);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_Fwrite_break_1(struct _Tcp1_Tstmt *_Lstmt_0) {
   cm1_push_ptr(_Lstmt_0);
   cm1_run(259);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_Fwrite_return_1(struct _Tcp1_Tstmt *_Lstmt_0) {
   cm1_push_ptr(_Lstmt_0);
   cm1_run(260);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_Fwrite_space_1(struct _Tcp1_Tstmt *_Lstmt_0) {
   cm1_push_ptr(_Lstmt_0);
   cm1_run(261);
   (void)cm1_pop_ptr();
}
uint8_t _Tposix_Tfd_Fopen_3(_Tposix_Tfd *_Lfile_0, char *_Lpath_1, _Tposix_Topen_flags _Lflags_2) {
   cm1_push_ptr(_Lfile_0);
   cm1_push_ptr(_Lpath_1);
   cm1_push_i(_Lflags_2);
   cm1_run(262);
   return cm1_pop_u64();
}
void _Tcp1_Texpr_i_Fset_3(_Tcp1_Texpr_i _Le_0, struct _Tcp1_Texpr *_Lexpr_1, _Tcp1_Texpr_type _Ltype_2) {
   cm1_push_i(_Le_0);
   cm1_push_ptr(_Lexpr_1);
   cm1_push_u(_Ltype_2);
   cm1_run(263);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tassign_Frd_2(_Tcp1_Tassign *_Ls_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_ptr(_Ls_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(264);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tcompare_Frd_2(_Tcp1_Tcompare *_Le_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_ptr(_Le_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(265);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fset_bool_2(_Tcp1_Texpr_i _Le_idx_0, uint8_t _Lval_1) {
   cm1_push_i(_Le_idx_0);
   cm1_push_u(_Lval_1);
   cm1_run(266);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tmath_Frd_2(_Tcp1_Tmath *_Le_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_ptr(_Le_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(267);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tunary_Frd_2(_Tcp1_Tunary *_Lu_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_ptr(_Lu_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(268);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fset_fvar_3(_Tcp1_Texpr_i _Le_idx_0, _Tcp1_Texpr_i _Lexpr_1, _Tcp1_Tid _Lmember_2) {
   cm1_push_i(_Le_idx_0);
   cm1_push_i(_Lexpr_1);
   cm1_push_i(_Lmember_2);
   cm1_run(269);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fset_gvar_3(_Tcp1_Texpr_i _Le_idx_0, _Tcp1_Tat _Lat_idx_1, _Tcp1_Tid _Lname_2) {
   cm1_push_i(_Le_idx_0);
   cm1_push_i(_Lat_idx_1);
   cm1_push_i(_Lname_2);
   cm1_run(270);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fset_cvar_3(_Tcp1_Texpr_i _Le_idx_0, _Tcp1_Tat _Lat_1, _Tcp1_Tid _Lname_2) {
   cm1_push_i(_Le_idx_0);
   cm1_push_i(_Lat_1);
   cm1_push_i(_Lname_2);
   cm1_run(271);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tbools_Frd_2(_Tcp1_Tbools *_Le_0, union _Tcp1_Trdr *_Lr_1) {
   cm1_push_ptr(_Le_0);
   cm1_push_ptr(_Lr_1);
   cm1_run(272);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fset_method_8(_Tcp1_Texpr_i _Le_idx_0, _Tcp1_Texpr_i _Lthis_expr_1, _Tcp1_Tid _Lfunc_name_2, uint8_t _Langle_3, uint8_t _Lgroup_c_4, uint8_t *_Lgroup_v_5, uint8_t _Lcarg_c_6, _Tcp1_Texpr_i *_Lcarg_v_7) {
   cm1_push_i(_Le_idx_0);
   cm1_push_i(_Lthis_expr_1);
   cm1_push_i(_Lfunc_name_2);
   cm1_push_u(_Langle_3);
   cm1_push_u(_Lgroup_c_4);
   cm1_push_ptr(_Lgroup_v_5);
   cm1_push_u(_Lcarg_c_6);
   cm1_push_ptr(_Lcarg_v_7);
   cm1_run(273);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fset_func_8(_Tcp1_Texpr_i _Le_idx_0, _Tcp1_Tat _Lat_idx_1, _Tcp1_Tid _Lfunc_name_2, uint8_t _Langle_3, uint8_t _Lgroup_c_4, uint8_t *_Lgroup_v_5, uint8_t _Lcarg_c_6, _Tcp1_Texpr_i *_Lcarg_v_7) {
   cm1_push_i(_Le_idx_0);
   cm1_push_i(_Lat_idx_1);
   cm1_push_i(_Lfunc_name_2);
   cm1_push_u(_Langle_3);
   cm1_push_u(_Lgroup_c_4);
   cm1_push_ptr(_Lgroup_v_5);
   cm1_push_u(_Lcarg_c_6);
   cm1_push_ptr(_Lcarg_v_7);
   cm1_run(274);
   (void)cm1_pop_ptr();
}
void _Tcp1_Trdr_Fcopy_3(union _Tcp1_Trdr *_Lr_0, void *_Ldata_1, int32_t _Lsize_2) {
   cm1_push_ptr(_Lr_0);
   cm1_push_ptr(_Ldata_1);
   cm1_push_i(_Lsize_2);
   cm1_run(275);
   (void)cm1_pop_ptr();
}
float _Tcp1_Trdr_Ff4_1(union _Tcp1_Trdr *_Lr_0) {
   cm1_push_ptr(_Lr_0);
   cm1_run(276);
   return cm1_pop_f32();
}
double _Tcp1_Trdr_Ff8_1(union _Tcp1_Trdr *_Lr_0) {
   cm1_push_ptr(_Lr_0);
   cm1_run(277);
   return cm1_pop_f64();
}
void _Tcp1_Texpr_i_Fset_index_3(_Tcp1_Texpr_i _Le_idx_0, _Tcp1_Texpr_i _Lleft_1, _Tcp1_Texpr_i _Lright_2) {
   cm1_push_i(_Le_idx_0);
   cm1_push_i(_Lleft_1);
   cm1_push_i(_Lright_2);
   cm1_run(278);
   (void)cm1_pop_ptr();
}
uint32_t _Tcp1_Texpr_str_Flen_1(struct _Tcp1_Texpr_str *_Ls_0) {
   cm1_push_ptr(_Ls_0);
   cm1_run(279);
   return cm1_pop_u64();
}
void _Tcp1_Texpr_i_Fvalue_assign_5(_Tcp1_Texpr_i _Le_0, int8_t _Lref_1, uint8_t _Lparen_2, struct _Tcp1_Tvalue *_Lv_3, uint8_t *_Lok_4) {
   cm1_push_i(_Le_0);
   cm1_push_i(_Lref_1);
   cm1_push_u(_Lparen_2);
   cm1_push_ptr(_Lv_3);
   cm1_push_ptr(_Lok_4);
   cm1_run(280);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fvalue_compare_5(_Tcp1_Texpr_i _Le_0, int8_t _Lref_1, uint8_t _Lparen_2, struct _Tcp1_Tvalue *_Lv_3, uint8_t *_Lok_4) {
   cm1_push_i(_Le_0);
   cm1_push_i(_Lref_1);
   cm1_push_u(_Lparen_2);
   cm1_push_ptr(_Lv_3);
   cm1_push_ptr(_Lok_4);
   cm1_run(281);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fvalue_bool_5(_Tcp1_Texpr_i _Lle_0, int32_t _Lref_1, uint8_t _Lparen_2, struct _Tcp1_Tvalue *_Lv_3, uint8_t *_Lok_4) {
   cm1_push_i(_Lle_0);
   cm1_push_i(_Lref_1);
   cm1_push_u(_Lparen_2);
   cm1_push_ptr(_Lv_3);
   cm1_push_ptr(_Lok_4);
   cm1_run(282);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fvalue_char_5(_Tcp1_Texpr_i _Lle_0, int32_t _Lref_1, uint8_t _Lparen_2, struct _Tcp1_Tvalue *_Lv_3, uint8_t *_Lok_4) {
   cm1_push_i(_Lle_0);
   cm1_push_i(_Lref_1);
   cm1_push_u(_Lparen_2);
   cm1_push_ptr(_Lv_3);
   cm1_push_ptr(_Lok_4);
   cm1_run(283);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fvalue_math_5(_Tcp1_Texpr_i _Le_0, int8_t _Lref_1, uint8_t _Lparen_2, struct _Tcp1_Tvalue *_Lv_3, uint8_t *_Lok_4) {
   cm1_push_i(_Le_0);
   cm1_push_i(_Lref_1);
   cm1_push_u(_Lparen_2);
   cm1_push_ptr(_Lv_3);
   cm1_push_ptr(_Lok_4);
   cm1_run(284);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fvalue_unary_5(_Tcp1_Texpr_i _Le_0, int8_t _Lref_1, uint8_t _Lparen_2, struct _Tcp1_Tvalue *_Lv_3, uint8_t *_Lok_4) {
   cm1_push_i(_Le_0);
   cm1_push_i(_Lref_1);
   cm1_push_u(_Lparen_2);
   cm1_push_ptr(_Lv_3);
   cm1_push_ptr(_Lok_4);
   cm1_run(285);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fvalue_ref_5(_Tcp1_Texpr_i _Le_0, int8_t _Lref_1, uint8_t _Lparen_2, struct _Tcp1_Tvalue *_Lv_3, uint8_t *_Lok_4) {
   cm1_push_i(_Le_0);
   cm1_push_i(_Lref_1);
   cm1_push_u(_Lparen_2);
   cm1_push_ptr(_Lv_3);
   cm1_push_ptr(_Lok_4);
   cm1_run(286);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fvalue_cast_fast_5(_Tcp1_Texpr_i _Le_0, int8_t _Lref_1, uint8_t _Lparen_2, struct _Tcp1_Tvalue *_Lv_3, uint8_t *_Lok_4) {
   cm1_push_i(_Le_0);
   cm1_push_i(_Lref_1);
   cm1_push_u(_Lparen_2);
   cm1_push_ptr(_Lv_3);
   cm1_push_ptr(_Lok_4);
   cm1_run(287);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fvalue_lvar_5(_Tcp1_Texpr_i _Le_0, int8_t _Lref_1, uint8_t _Lparen_2, struct _Tcp1_Tvalue *_Lv_3, uint8_t *_Lok_4) {
   cm1_push_i(_Le_0);
   cm1_push_i(_Lref_1);
   cm1_push_u(_Lparen_2);
   cm1_push_ptr(_Lv_3);
   cm1_push_ptr(_Lok_4);
   cm1_run(288);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fvalue_fvar_5(_Tcp1_Texpr_i _Lexpr_0, int8_t _Lref_1, uint8_t _Lparen_2, struct _Tcp1_Tvalue *_Lv_3, uint8_t *_Lok_4) {
   cm1_push_i(_Lexpr_0);
   cm1_push_i(_Lref_1);
   cm1_push_u(_Lparen_2);
   cm1_push_ptr(_Lv_3);
   cm1_push_ptr(_Lok_4);
   cm1_run(289);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fvalue_soa_field_5(_Tcp1_Texpr_i _Lexpr_0, int8_t _Lref_1, uint8_t _Lparen_2, struct _Tcp1_Tvalue *_Lv_3, uint8_t *_Lok_4) {
   cm1_push_i(_Lexpr_0);
   cm1_push_i(_Lref_1);
   cm1_push_u(_Lparen_2);
   cm1_push_ptr(_Lv_3);
   cm1_push_ptr(_Lok_4);
   cm1_run(290);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fvalue_gvar_5(_Tcp1_Texpr_i _Lg_0, int32_t _Lref_1, uint8_t _Lparen_2, struct _Tcp1_Tvalue *_Lv_3, uint8_t *_Lok_4) {
   cm1_push_i(_Lg_0);
   cm1_push_i(_Lref_1);
   cm1_push_u(_Lparen_2);
   cm1_push_ptr(_Lv_3);
   cm1_push_ptr(_Lok_4);
   cm1_run(291);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fvalue_cvar_5(_Tcp1_Texpr_i _Le_0, int8_t _Lref_1, uint8_t _Lparen_2, struct _Tcp1_Tvalue *_Lv_3, uint8_t *_Lok_4) {
   cm1_push_i(_Le_0);
   cm1_push_i(_Lref_1);
   cm1_push_u(_Lparen_2);
   cm1_push_ptr(_Lv_3);
   cm1_push_ptr(_Lok_4);
   cm1_run(292);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fvalue_bools_5(_Tcp1_Texpr_i _Le_0, int32_t _Lref_1, uint8_t _Lparen_2, struct _Tcp1_Tvalue *_Lv_3, uint8_t *_Lok_4) {
   cm1_push_i(_Le_0);
   cm1_push_i(_Lref_1);
   cm1_push_u(_Lparen_2);
   cm1_push_ptr(_Lv_3);
   cm1_push_ptr(_Lok_4);
   cm1_run(293);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fvalue_func_5(_Tcp1_Texpr_i _Le_0, int32_t _Lref_1, uint8_t _Lparen_2, struct _Tcp1_Tvalue *_Lv_3, uint8_t *_Lok_4) {
   cm1_push_i(_Le_0);
   cm1_push_i(_Lref_1);
   cm1_push_u(_Lparen_2);
   cm1_push_ptr(_Lv_3);
   cm1_push_ptr(_Lok_4);
   cm1_run(294);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fvalue_method_5(_Tcp1_Texpr_i _Le_0, int32_t _Lref_1, uint8_t _Lparen_2, struct _Tcp1_Tvalue *_Lv_3, uint8_t *_Lok_4) {
   cm1_push_i(_Le_0);
   cm1_push_i(_Lref_1);
   cm1_push_u(_Lparen_2);
   cm1_push_ptr(_Lv_3);
   cm1_push_ptr(_Lok_4);
   cm1_run(295);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fvalue_str_5(_Tcp1_Texpr_i _Ls_0, int32_t _Lref_1, uint8_t _Lparen_2, struct _Tcp1_Tvalue *_Lv_3, uint8_t *_Lok_4) {
   cm1_push_i(_Ls_0);
   cm1_push_i(_Lref_1);
   cm1_push_u(_Lparen_2);
   cm1_push_ptr(_Lv_3);
   cm1_push_ptr(_Lok_4);
   cm1_run(296);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fvalue_int_5(_Tcp1_Texpr_i _Lle_0, int32_t _Lref_1, uint8_t _Lparen_2, struct _Tcp1_Tvalue *_Lv_3, uint8_t *_Lok_4) {
   cm1_push_i(_Lle_0);
   cm1_push_i(_Lref_1);
   cm1_push_u(_Lparen_2);
   cm1_push_ptr(_Lv_3);
   cm1_push_ptr(_Lok_4);
   cm1_run(297);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fvalue_size_of_type_5(_Tcp1_Texpr_i _Lle_0, int32_t _Lref_1, uint8_t _Lparen_2, struct _Tcp1_Tvalue *_Lv_3, uint8_t *_Lok_4) {
   cm1_push_i(_Lle_0);
   cm1_push_i(_Lref_1);
   cm1_push_u(_Lparen_2);
   cm1_push_ptr(_Lv_3);
   cm1_push_ptr(_Lok_4);
   cm1_run(298);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fvalue_null_5(_Tcp1_Texpr_i _Lle_0, int32_t _Lref_1, uint8_t _Lparen_2, struct _Tcp1_Tvalue *_Lv_3, uint8_t *_Lok_4) {
   cm1_push_i(_Lle_0);
   cm1_push_i(_Lref_1);
   cm1_push_u(_Lparen_2);
   cm1_push_ptr(_Lv_3);
   cm1_push_ptr(_Lok_4);
   cm1_run(299);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Fvalue_index_5(_Tcp1_Texpr_i _Le_0, int8_t _Lref_1, uint8_t _Lparen_2, struct _Tcp1_Tvalue *_Lv_3, uint8_t *_Lok_4) {
   cm1_push_i(_Le_0);
   cm1_push_i(_Lref_1);
   cm1_push_u(_Lparen_2);
   cm1_push_ptr(_Lv_3);
   cm1_push_ptr(_Lok_4);
   cm1_run(300);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tstmt_space_Fstmt_push_7(struct _Tcp1_Tstmt_space *_Ls_0, struct _Tcp1_Tstmt *_Ls2_1, uint32_t _Lbegin_row_2, uint32_t _Lbegin_col_3, uint32_t _Lend_row_4, uint32_t _Lend_col_5, _Tcp1_Tstmt_type _Ltype_6) {
   cm1_push_ptr(_Ls_0);
   cm1_push_ptr(_Ls2_1);
   cm1_push_u(_Lbegin_row_2);
   cm1_push_u(_Lbegin_col_3);
   cm1_push_u(_Lend_row_4);
   cm1_push_u(_Lend_col_5);
   cm1_push_u(_Ltype_6);
   cm1_run(301);
   (void)cm1_pop_ptr();
}
_Tcp1_Tat _Tcp1_Texpr_i_Ftype_1(_Tcp1_Texpr_i _Le_0) {
   cm1_push_i(_Le_0);
   cm1_run(302);
   return cm1_pop_i64();
}
uint8_t _Tcp1_Texpr_i_Fprocess_case_func_2(struct _Tcp1_Texpr *_Lexpr_0, _Tcp1_Tfunc _Lf_idx_1) {
   cm1_push_ptr(_Lexpr_0);
   cm1_push_i(_Lf_idx_1);
   cm1_run(303);
   return cm1_pop_u64();
}
uint8_t _Tcp1_Tstmt_space_Fprocess_1(struct _Tcp1_Tstmt_space *_Lspace_0) {
   cm1_push_ptr(_Lspace_0);
   cm1_run(304);
   return cm1_pop_u64();
}
void _Tcp1_Texpr_i_Ftry_deduce_2(_Tcp1_Texpr_i _Le_idx_0, _Tcp1_Tat _Lat_1) {
   cm1_push_i(_Le_idx_0);
   cm1_push_i(_Lat_1);
   cm1_run(305);
   (void)cm1_pop_ptr();
}
void _Tcp1_Ttype_info_Finit_1(struct _Tcp1_Ttype_info *_Lti_0) {
   cm1_push_ptr(_Lti_0);
   cm1_run(306);
   (void)cm1_pop_ptr();
}
void _Tcp1_Ttype_info_Fcopy_from_2(struct _Tcp1_Ttype_info *_Lti_0, struct _Tcp1_Ttype_info *_Lti2_1) {
   cm1_push_ptr(_Lti_0);
   cm1_push_ptr(_Lti2_1);
   cm1_run(307);
   (void)cm1_pop_ptr();
}
uint8_t _Tcp1_Fcompatible_4(_Tcp1_Tat _Lsrc_0, uint8_t _Lsrc_c_1, _Tcp1_Tat _Ldes_2, uint8_t _Ldes_c_3) {
   cm1_push_i(_Lsrc_0);
   cm1_push_u(_Lsrc_c_1);
   cm1_push_i(_Ldes_2);
   cm1_push_u(_Ldes_c_3);
   cm1_run(308);
   return cm1_pop_u64();
}
void _Tlibcp1_Tfmt_Ff_reserve_Tu8_1_2(uint8_t _Lu_0, struct _Tlibcp1_Tfmt *_Lfmt_1, struct _Tlibcp1_Tfmt_Tf_u32 *_Lf_2) {
   cm1_push_u(_Lu_0);
   cm1_push_ptr(_Lfmt_1);
   cm1_push_ptr(_Lf_2);
   cm1_run(309);
   (void)cm1_pop_ptr();
}
uint8_t _Tcp1_Tgvar_Fprocess_1(_Tcp1_Tgvar _Lg_0) {
   cm1_push_i(_Lg_0);
   cm1_run(310);
   return cm1_pop_u64();
}
uint8_t _Tcp1_Fensure_bool_2(_Tcp1_Tat _Lat_0, _Tcp1_Tbools _Ltype_1) {
   cm1_push_i(_Lat_0);
   cm1_push_u(_Ltype_1);
   cm1_run(311);
   return cm1_pop_u64();
}
uint8_t _Tcp1_Ffarg_process_7(_Tcp1_Texpr_i *_Le_in_out_0, int8_t _Lca_ref_1, struct _Tcp1_Tvalue *_Lca_value_2, struct _Tcp1_Tdecl_var_data *_Lfd_arg_3, _Tcp1_Tat _Lbase_at_4, int32_t _Larg_num_5, _Tcp1_Tid _Lf_name_6) {
   cm1_push_ptr(_Le_in_out_0);
   cm1_push_i(_Lca_ref_1);
   cm1_push_ptr(_Lca_value_2);
   cm1_push_ptr(_Lfd_arg_3);
   cm1_push_i(_Lbase_at_4);
   cm1_push_i(_Larg_num_5);
   cm1_push_i(_Lf_name_6);
   cm1_run(312);
   return cm1_pop_u64();
}
void _Tcp1_Tdecl_var_data_Fwrite_gvar_2(struct _Tcp1_Tdecl_var_data *_Lvd_0, _Tcp1_Tat _Lat_1) {
   cm1_push_ptr(_Lvd_0);
   cm1_push_i(_Lat_1);
   cm1_run(313);
   (void)cm1_pop_ptr();
}
void _Tcp1_Tvalue_Fset_5(struct _Tcp1_Tvalue *_Lv_0, int8_t _Lref_1, uint8_t _Lparen_2, _Tcp1_Tat _Ltype_3, struct _Tcp1_Ttype_info *_Linfo_4) {
   cm1_push_ptr(_Lv_0);
   cm1_push_i(_Lref_1);
   cm1_push_u(_Lparen_2);
   cm1_push_i(_Ltype_3);
   cm1_push_ptr(_Linfo_4);
   cm1_run(314);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Ftype_assign_2(struct _Tcp1_Texpr *_Lexpr_0, _Tcp1_Tat *_Lat_1) {
   cm1_push_ptr(_Lexpr_0);
   cm1_push_ptr(_Lat_1);
   cm1_run(315);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Ftype_compare_2(struct _Tcp1_Texpr *_Lexpr_0, _Tcp1_Tat *_Lat_1) {
   cm1_push_ptr(_Lexpr_0);
   cm1_push_ptr(_Lat_1);
   cm1_run(316);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Ftype_bool_2(struct _Tcp1_Texpr *_Lexpr_0, _Tcp1_Tat *_Lat_1) {
   cm1_push_ptr(_Lexpr_0);
   cm1_push_ptr(_Lat_1);
   cm1_run(317);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Ftype_char_2(struct _Tcp1_Texpr *_Lexpr_0, _Tcp1_Tat *_Lat_1) {
   cm1_push_ptr(_Lexpr_0);
   cm1_push_ptr(_Lat_1);
   cm1_run(318);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Ftype_math_2(struct _Tcp1_Texpr *_Lexpr_0, _Tcp1_Tat *_Lat_1) {
   cm1_push_ptr(_Lexpr_0);
   cm1_push_ptr(_Lat_1);
   cm1_run(319);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Ftype_unary_2(struct _Tcp1_Texpr *_Lexpr_0, _Tcp1_Tat *_Lat_1) {
   cm1_push_ptr(_Lexpr_0);
   cm1_push_ptr(_Lat_1);
   cm1_run(320);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Ftype_ref_2(struct _Tcp1_Texpr *_Lexpr_0, _Tcp1_Tat *_Lat_1) {
   cm1_push_ptr(_Lexpr_0);
   cm1_push_ptr(_Lat_1);
   cm1_run(321);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Ftype_cast_fast_2(struct _Tcp1_Texpr *_Lexpr_0, _Tcp1_Tat *_Lat_1) {
   cm1_push_ptr(_Lexpr_0);
   cm1_push_ptr(_Lat_1);
   cm1_run(322);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Ftype_lvar_2(struct _Tcp1_Texpr *_Lexpr_0, _Tcp1_Tat *_Lat_1) {
   cm1_push_ptr(_Lexpr_0);
   cm1_push_ptr(_Lat_1);
   cm1_run(323);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Ftype_fvar_2(struct _Tcp1_Texpr *_Lexpr_0, _Tcp1_Tat *_Lat_1) {
   cm1_push_ptr(_Lexpr_0);
   cm1_push_ptr(_Lat_1);
   cm1_run(324);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Ftype_soa_field_2(struct _Tcp1_Texpr *_Lexpr_0, _Tcp1_Tat *_Lat_1) {
   cm1_push_ptr(_Lexpr_0);
   cm1_push_ptr(_Lat_1);
   cm1_run(325);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Ftype_gvar_2(struct _Tcp1_Texpr *_Lexpr_0, _Tcp1_Tat *_Lat_1) {
   cm1_push_ptr(_Lexpr_0);
   cm1_push_ptr(_Lat_1);
   cm1_run(326);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Ftype_cvar_2(struct _Tcp1_Texpr *_Lexpr_0, _Tcp1_Tat *_Lat_1) {
   cm1_push_ptr(_Lexpr_0);
   cm1_push_ptr(_Lat_1);
   cm1_run(327);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Ftype_bools_2(struct _Tcp1_Texpr *_Lexpr_0, _Tcp1_Tat *_Lat_1) {
   cm1_push_ptr(_Lexpr_0);
   cm1_push_ptr(_Lat_1);
   cm1_run(328);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Ftype_func_2(struct _Tcp1_Texpr *_Lexpr_0, _Tcp1_Tat *_Lat_1) {
   cm1_push_ptr(_Lexpr_0);
   cm1_push_ptr(_Lat_1);
   cm1_run(329);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Ftype_method_2(struct _Tcp1_Texpr *_Lexpr_0, _Tcp1_Tat *_Lat_1) {
   cm1_push_ptr(_Lexpr_0);
   cm1_push_ptr(_Lat_1);
   cm1_run(330);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Ftype_int_2(struct _Tcp1_Texpr *_Lexpr_0, _Tcp1_Tat *_Lat_1) {
   cm1_push_ptr(_Lexpr_0);
   cm1_push_ptr(_Lat_1);
   cm1_run(331);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Ftype_size_of_type_2(struct _Tcp1_Texpr *_Lexpr_0, _Tcp1_Tat *_Lat_1) {
   cm1_push_ptr(_Lexpr_0);
   cm1_push_ptr(_Lat_1);
   cm1_run(332);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Ftype_null_2(struct _Tcp1_Texpr *_Lexpr_0, _Tcp1_Tat *_Lat_1) {
   cm1_push_ptr(_Lexpr_0);
   cm1_push_ptr(_Lat_1);
   cm1_run(333);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Ftype_index_2(struct _Tcp1_Texpr *_Lexpr_0, _Tcp1_Tat *_Lat_1) {
   cm1_push_ptr(_Lexpr_0);
   cm1_push_ptr(_Lat_1);
   cm1_run(334);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Ftry_deduce_math_2(struct _Tcp1_Texpr *_Lexpr_0, _Tcp1_Tat _Lat_1) {
   cm1_push_ptr(_Lexpr_0);
   cm1_push_i(_Lat_1);
   cm1_run(335);
   (void)cm1_pop_ptr();
}
void _Tcp1_Texpr_i_Ftry_deduce_cvar_2(struct _Tcp1_Texpr *_Lexpr_0, _Tcp1_Tat _Lat_1) {
   cm1_push_ptr(_Lexpr_0);
   cm1_push_i(_Lat_1);
   cm1_run(336);
   (void)cm1_pop_ptr();
}
void* cm1_gvar(uint16_t var_idx) {
   switch (var_idx) {
      case 0: {
         return &stdout;
      }
      case 1: {
         return &_Tcp1_Ginclude_path_v;
      }
      case 2: {
         return &_Tcp1_Ginclude_path_len_v;
      }
      case 3: {
         return &_Tcp1_Gdefine_v;
      }
      case 4: {
         return &_Tcp1_Gdefine_len_v;
      }
      case 5: {
         return &_Tcp1_Gdebug_func_prefix;
      }
      case 6: {
         return &_Tcp1_Gdebug_func_prefix_len;
      }
      case 7: {
         return &_Tcp1_Ginclude_path_c;
      }
      case 8: {
         return &_Tcp1_Gdefine_c;
      }
      case 9: {
         return &_Tcp1_Ginclude_dir;
      }
      case 10: {
         return &_Tcp1_Ginclude_dir_len;
      }
      case 11: {
         return &_Tcp1_Gid_map;
      }
      case 12: {
         return &_Tcp1_Ginclude_map;
      }
      case 13: {
         return &_Tcp1_Gat_map;
      }
      case 14: {
         return &_Tcp1_Gfunc_main;
      }
      case 15: {
         return &_Tcp1_Gat_c;
      }
      case 16: {
         return &_Tcp1_Gat_cap;
      }
      case 17: {
         return &_Tcp1_Gat_v;
      }
      case 18: {
         return &_Tcp1_Gimport_cap;
      }
      case 19: {
         return &_Tcp1_Gimport_v;
      }
      case 20: {
         return &_Tcp1_Gimport_file_v;
      }
      case 21: {
         return &_Tcp1_Gimport_required_v;
      }
      case 22: {
         return &_Tcp1_Gtemplate_inst_cap;
      }
      case 23: {
         return &_Tcp1_Gtemplate_inst_v;
      }
      case 24: {
         return &_Tcp1_Gimport_new_c;
      }
      case 25: {
         return &_Tcp1_Gimport_c;
      }
      case 26: {
         return &_Tcp1_Gtemplate_inst_new_c;
      }
      case 27: {
         return &_Tcp1_Gjscode_buf_cap;
      }
      case 28: {
         return &_Tcp1_Gjscode_buf_data;
      }
      case 29: {
         return &_Tcp1_Gtemplate_inst_c;
      }
      case 30: {
         return &_Tcp1_Gtemplate_code_c;
      }
      case 31: {
         return &_Tcp1_Gtemplate_code_v;
      }
      case 32: {
         return &_Tcp1_Gjscode_buf_len;
      }
      case 33: {
         return &_Tcp1_Gfunc_c;
      }
      case 34: {
         return &_Tcp1_Gbasic_type;
      }
      case 35: {
         return &_Tcp1_Gid_add;
      }
      case 36: {
         return &_Tcp1_Gid_sub;
      }
      case 37: {
         return &_Tcp1_Gid_mul;
      }
      case 38: {
         return &_Tcp1_Gid_div;
      }
      case 39: {
         return &_Tcp1_Gid_eq;
      }
      case 40: {
         return &_Tcp1_Gid_ne;
      }
      case 41: {
         return &_Tcp1_Gid_gt;
      }
      case 42: {
         return &_Tcp1_Gid_ge;
      }
      case 43: {
         return &_Tcp1_Gid_lt;
      }
      case 44: {
         return &_Tcp1_Gid_le;
      }
      case 45: {
         return &_Tcp1_Gid_and;
      }
      case 46: {
         return &_Tcp1_Gid_or;
      }
      case 47: {
         return &_Tcp1_Gfunc_in_process;
      }
      case 48: {
         return &_Tcp1_Gfunc_head_outputted_v;
      }
      case 49: {
         return &_Tcp1_Gfunc_body_outputted_v;
      }
      case 50: {
         return &_Tcp1_Ginclude_c;
      }
      case 51: {
         return &_Tcp1_Ginclude_is_outputted;
      }
      case 52: {
         return &_Tcp1_Ginclude_outputted_v;
      }
      case 53: {
         return &_Tcp1_Gcvar_c;
      }
      case 54: {
         return &_Tcp1_Gcvar_is_outputted;
      }
      case 55: {
         return &_Tcp1_Gcvar_outputted_v;
      }
      case 56: {
         return &_Tcp1_Ggvar_c;
      }
      case 57: {
         return &_Tcp1_Ggvar_is_outputted;
      }
      case 58: {
         return &_Tcp1_Ggvar_outputted_v;
      }
      case 59: {
         return &_Tcp1_Genum_c;
      }
      case 60: {
         return &_Tcp1_Genum_is_outputted;
      }
      case 61: {
         return &_Tcp1_Genum_outputted_v;
      }
      case 62: {
         return &_Tcp1_Gstruct_c;
      }
      case 63: {
         return &_Tcp1_Gstruct_is_outputted;
      }
      case 64: {
         return &_Tcp1_Gstruct_outputted_v;
      }
      case 65: {
         return &_Tcp1_Gprocess_first;
      }
      case 66: {
         return &_Tcp1_Gprocess_last;
      }
      case 67: {
         return &_Tcp1_Gfunc_head_outputted_c;
      }
      case 68: {
         return &_Tcp1_Gctx_func;
      }
      case 69: {
         return &_Tcp1_Goutput_cap;
      }
      case 70: {
         return &output_data;
      }
      case 71: {
         return &_Tcp1_Gcvar_outputted_c;
      }
      case 72: {
         return &_Tcp1_Genum_outputted_c;
      }
      case 73: {
         return &_Tcp1_Gstruct_outputted_c;
      }
      case 74: {
         return &_Tcp1_Ggvar_outputted_c;
      }
      case 75: {
         return &_Tcp1_Ginclude_outputted_c;
      }
      case 76: {
         return &_Tcp1_Gfunc_body_outputted_c;
      }
      case 77: {
         return &_Tcp1_Gnest_id;
      }
      case 78: {
         return &output_len;
      }
      case 79: {
         return &_Tcp1_Gprinted_error;
      }
      case 80: {
         return &_Tlibcp1_Gstdout_buf_len;
      }
      case 81: {
         return &_Tlibcp1_Gstdout_buf_data;
      }
      case 82: {
         return &_Tcp1_Gquick_alloc_c;
      }
      case 83: {
         return &_Tcp1_Gquick_alloc_cap;
      }
      case 84: {
         return &_Tcp1_Gquick_alloc_v;
      }
      case 85: {
         return &_Tcp1_Ginclude_cap;
      }
      case 86: {
         return &_Tcp1_Ginclude_len_v;
      }
      case 87: {
         return &_Tcp1_Ginclude_str_v;
      }
      case 88: {
         return &_Tcp1_Gfile_c;
      }
      case 89: {
         return &_Tcp1_Gfile_cap;
      }
      case 90: {
         return &_Tcp1_Gfile_v;
      }
      case 91: {
         return &_Tcp1_Gid_table;
      }
      case 92: {
         return &_Tcp1_Ginclude_table_cap;
      }
      case 93: {
         return &_Tcp1_Ginclude_table;
      }
      case 94: {
         return &_Tcp1_Gat_table;
      }
      case 95: {
         return &_Tcp1_Gcvar_table;
      }
      case 96: {
         return &_Tcp1_Gcvar_cap;
      }
      case 97: {
         return &_Tcp1_Gcvar_v;
      }
      case 98: {
         return &_Tcp1_Ggvar_cap;
      }
      case 99: {
         return &_Tcp1_Ggvar_v;
      }
      case 100: {
         return &_Tcp1_Genum_cap;
      }
      case 101: {
         return &_Tcp1_Genum_v;
      }
      case 102: {
         return &_Tcp1_Gstruct_cap;
      }
      case 103: {
         return &_Tcp1_Gstruct_v;
      }
      case 104: {
         return &_Tcp1_Gfunc_cap;
      }
      case 105: {
         return &_Tcp1_Gfunc_v;
      }
      case 106: {
         return &_Tcp1_Gctx_func_id;
      }
      case 107: {
         return &_Tcp1_Gtemplate_code_cap;
      }
      case 108: {
         return &_Tcp1_Gid_str_v;
      }
      case 109: {
         return &_Tcp1_Gid_len_v;
      }
      case 110: {
         return &_Tcp1_Gid_c;
      }
      case 111: {
         return &_Tcp1_Gid_cap;
      }
      case 112: {
         return &_Tcp1_Gid_c_name_v;
      }
      case 113: {
         return &_Tcp1_Gctx_begin_row;
      }
      case 114: {
         return &_Tcp1_Gctx_begin_col;
      }
      case 115: {
         return &_Tcp1_Gctx_end_row;
      }
      case 116: {
         return &_Tcp1_Gctx_end_col;
      }
      case 117: {
         return &_Tcp1_Gid_blank;
      }
      case 118: {
         return &_Tcp1_Gexpr_is_processed;
      }
      case 119: {
         return &_Tcp1_Gexpr_v;
      }
      case 120: {
         return &_Tcp1_Gexpr_c;
      }
      case 121: {
         return &_Tcp1_Gexpr_cap;
      }
      case 122: {
         return &_Tcp1_Tstmt_space_Gif_stack_v;
      }
      case 123: {
         return &_Tcp1_Tstmt_space_Gif_stack_c;
      }
      case 124: {
         return &_Tcp1_Gnest_stack_id_v;
      }
      case 125: {
         return &_Tcp1_Gnest_stack_c;
      }
      case 126: {
         return &_Tcp1_Gnest_stack_ptr_v;
      }
      case 127: {
         return &_Tcp1_Gswitch_stack_v;
      }
      case 128: {
         return &_Tcp1_Gswitch_stack_c;
      }
      case 129: {
         return &_Tcp1_Gcase_stack_v;
      }
      case 130: {
         return &_Tcp1_Gcase_stack_c;
      }
   }
   return NULL;
}
void cm1_run_c(uint16_t func_idx) {
   switch (func_idx) {
      case 0: {
         int32_t arg2 = cm1_pop_i64();
         int32_t arg1 = cm1_pop_i64();
         void* arg0 = cm1_pop_ptr();
         int32_t ret = open(arg0, arg1, arg2);
         cm1_push_i(ret);
         break;
      }
      case 1: {
         uint64_t arg0 = cm1_pop_u64();
         void* ret = malloc(arg0);
         cm1_push_ptr(ret);
         break;
      }
      case 2: {
         uint64_t arg1 = cm1_pop_u64();
         void* arg0 = cm1_pop_ptr();
         void* ret = realloc(arg0, arg1);
         cm1_push_ptr(ret);
         break;
      }
      case 3: {
         void* arg0 = cm1_pop_ptr();
         free(arg0);
         cm1_push_ptr(0);
         break;
      }
      case 4: {
         int32_t arg0 = cm1_pop_i64();
         exit(arg0);
         cm1_push_ptr(0);
         break;
      }
      case 5: {
         void* arg0 = cm1_pop_ptr();
         void* ret = getenv(arg0);
         cm1_push_ptr(ret);
         break;
      }
      case 6: {
         void* arg1 = cm1_pop_ptr();
         void* arg0 = cm1_pop_ptr();
         void* ret = realpath(arg0, arg1);
         cm1_push_ptr(ret);
         break;
      }
      case 7: {
         int32_t arg0 = cm1_pop_i64();
         int32_t ret = close(arg0);
         cm1_push_i(ret);
         break;
      }
      case 8: {
         uint64_t arg1 = cm1_pop_u64();
         void* arg0 = cm1_pop_ptr();
         void* ret = getcwd(arg0, arg1);
         cm1_push_ptr(ret);
         break;
      }
      case 9: {
         int32_t arg2 = cm1_pop_i64();
         int64_t arg1 = cm1_pop_i64();
         int32_t arg0 = cm1_pop_i64();
         int64_t ret = lseek(arg0, arg1, arg2);
         cm1_push_i(ret);
         break;
      }
      case 10: {
         uint64_t arg2 = cm1_pop_u64();
         void* arg1 = cm1_pop_ptr();
         int32_t arg0 = cm1_pop_i64();
         int64_t ret = read(arg0, arg1, arg2);
         cm1_push_i(ret);
         break;
      }
      case 11: {
         uint64_t arg2 = cm1_pop_u64();
         void* arg1 = cm1_pop_ptr();
         int32_t arg0 = cm1_pop_i64();
         int64_t ret = write(arg0, arg1, arg2);
         cm1_push_i(ret);
         break;
      }
      case 12: {
         void* arg0 = cm1_pop_ptr();
         int32_t ret = fflush(arg0);
         cm1_push_i(ret);
         break;
      }
      case 13: {
         uint64_t arg2 = cm1_pop_u64();
         int32_t arg1 = cm1_pop_i64();
         void* arg0 = cm1_pop_ptr();
         void* ret = memchr(arg0, arg1, arg2);
         cm1_push_ptr(ret);
         break;
      }
      case 14: {
         uint64_t arg2 = cm1_pop_u64();
         void* arg1 = cm1_pop_ptr();
         void* arg0 = cm1_pop_ptr();
         int32_t ret = memcmp(arg0, arg1, arg2);
         cm1_push_i(ret);
         break;
      }
      case 15: {
         uint64_t arg2 = cm1_pop_u64();
         void* arg1 = cm1_pop_ptr();
         void* arg0 = cm1_pop_ptr();
         void* ret = memcpy(arg0, arg1, arg2);
         cm1_push_ptr(ret);
         break;
      }
      case 16: {
         uint64_t arg2 = cm1_pop_u64();
         int32_t arg1 = cm1_pop_i64();
         void* arg0 = cm1_pop_ptr();
         void* ret = memset(arg0, arg1, arg2);
         cm1_push_ptr(ret);
         break;
      }
      case 17: {
         void* arg1 = cm1_pop_ptr();
         void* arg0 = cm1_pop_ptr();
         void* ret = strcpy(arg0, arg1);
         cm1_push_ptr(ret);
         break;
      }
      case 18: {
         void* arg0 = cm1_pop_ptr();
         void* ret = strdup(arg0);
         cm1_push_ptr(ret);
         break;
      }
      case 19: {
         void* arg0 = cm1_pop_ptr();
         uint64_t ret = strlen(arg0);
         cm1_push_u(ret);
         break;
      }
      case 20: {
         int32_t arg1 = cm1_pop_i64();
         void* arg0 = cm1_pop_ptr();
         void* ret = strrchr(arg0, arg1);
         cm1_push_ptr(ret);
         break;
      }
      case 21: {
         void* arg1 = cm1_pop_ptr();
         void* arg0 = cm1_pop_ptr();
         void* ret = strtok(arg0, arg1);
         cm1_push_ptr(ret);
         break;
      }
      case 22: {
         void* arg0 = cm1_pop_ptr();
         Fskipnum(arg0);
         cm1_push_ptr(0);
         break;
      }
      case 23: {
         void* arg0 = cm1_pop_ptr();
         uint32_t ret = Fgetnum(arg0);
         cm1_push_u(ret);
         break;
      }
      case 24: {
         uint32_t arg1 = cm1_pop_u64();
         void* arg0 = cm1_pop_ptr();
         Fputnum(arg0, arg1);
         cm1_push_ptr(0);
         break;
      }
      case 25: {
         void* arg0 = cm1_pop_ptr();
         int32_t ret = Fgetint(arg0);
         cm1_push_i(ret);
         break;
      }
      case 26: {
         int32_t arg1 = cm1_pop_i64();
         void* arg0 = cm1_pop_ptr();
         Fputint(arg0, arg1);
         cm1_push_ptr(0);
         break;
      }
      case 27: {
         void* arg0 = cm1_pop_ptr();
         uint64_t ret = Fgetlnum(arg0);
         cm1_push_u(ret);
         break;
      }
      case 28: {
         uint64_t arg1 = cm1_pop_u64();
         void* arg0 = cm1_pop_ptr();
         Fputlnum(arg0, arg1);
         cm1_push_ptr(0);
         break;
      }
      case 29: {
         uint32_t arg0 = cm1_pop_u64();
         uint32_t ret = Fpow2gt(arg0);
         cm1_push_u(ret);
         break;
      }
      case 30: {
         uint32_t arg0 = cm1_pop_u64();
         uint32_t ret = Fpow2gteq(arg0);
         cm1_push_u(ret);
         break;
      }
      case 31: {
         uint32_t arg1 = cm1_pop_u64();
         void* arg0 = cm1_pop_ptr();
         stdout_then_print_error(arg0, arg1);
         cm1_push_ptr(0);
         break;
      }
      case 32: {
         void* arg0 = cm1_pop_ptr();
         _Tcp1_Fdeps_init_1(arg0);
         cm1_push_ptr(0);
         break;
      }
      case 33: {
         uint32_t arg2 = cm1_pop_u64();
         void* arg1 = cm1_pop_ptr();
         uint32_t arg0 = cm1_pop_u64();
         uint32_t ret = crc32c(arg0, arg1, arg2);
         cm1_push_u(ret);
         break;
      }
      case 34: {
         uint32_t arg0 = cm1_pop_u64();
         _Tcp1_Fc_init_1(arg0);
         cm1_push_ptr(0);
         break;
      }
      case 35: {
         void* arg0 = cm1_pop_ptr();
         _Tcp1_Fdeps_output_1(arg0);
         cm1_push_ptr(0);
         break;
      }
      case 36: {
         void* arg0 = cm1_pop_ptr();
         _Tcp1_Tmap_Finit_1(arg0);
         cm1_push_ptr(0);
         break;
      }
      case 37: {
         void* arg0 = cm1_pop_ptr();
         _Tcp1_Tat_map_Finit_1(arg0);
         cm1_push_ptr(0);
         break;
      }
      case 38: {
         uint8_t arg7 = cm1_pop_u64();
         uint8_t arg6 = cm1_pop_u64();
         uint32_t arg5 = cm1_pop_u64();
         uint32_t arg4 = cm1_pop_u64();
         uint8_t arg3 = cm1_pop_u64();
         void* arg2 = cm1_pop_ptr();
         uint8_t arg1 = cm1_pop_u64();
         void* arg0 = cm1_pop_ptr();
         uint8_t ret = _Tcp1_Fmeta_begin_8(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
         cm1_push_u(ret);
         break;
      }
      case 39: {
         uint32_t arg1 = cm1_pop_u64();
         void* arg0 = cm1_pop_ptr();
         uint32_t ret = _Tcp1_Fquickjs_hex_2(arg0, arg1);
         cm1_push_u(ret);
         break;
      }
      case 40: {
         uint8_t arg2 = cm1_pop_u64();
         uint32_t arg1 = cm1_pop_u64();
         void* arg0 = cm1_pop_ptr();
         _Tcp1_Fjs_end_3(arg0, arg1, arg2);
         cm1_push_ptr(0);
         break;
      }
      case 41: {
         uint8_t arg2 = cm1_pop_u64();
         uint32_t arg1 = cm1_pop_u64();
         void* arg0 = cm1_pop_ptr();
         _Tcp1_Fmeta_end_3(arg0, arg1, arg2);
         cm1_push_ptr(0);
         break;
      }
      case 42: {
         _Tcp1_Fdeps_close_0();
         cm1_push_ptr(0);
         break;
      }
      case 43: {
         int32_t arg3 = cm1_pop_i64();
         uint8_t arg2 = cm1_pop_u64();
         void* arg1 = cm1_pop_ptr();
         void* arg0 = cm1_pop_ptr();
         int32_t ret = _Tcp1_Tmap_Fget_or_insert_4(arg0, arg1, arg2, arg3);
         cm1_push_i(ret);
         break;
      }
      case 44: {
         uint8_t arg2 = cm1_pop_u64();
         uint8_t arg1 = cm1_pop_u64();
         void* arg0 = cm1_pop_ptr();
         void* ret = _Tcp1_Freq_parse_3(arg0, arg1, arg2);
         cm1_push_ptr(ret);
         break;
      }
      case 45: {
         int32_t arg3 = cm1_pop_i64();
         int32_t arg2 = cm1_pop_i64();
         uint32_t arg1 = cm1_pop_u64();
         void* arg0 = cm1_pop_ptr();
         int32_t ret = _Tcp1_Tat_map_Fget_or_insert_4(arg0, arg1, arg2, arg3);
         cm1_push_i(ret);
         break;
      }
      case 46: {
         char arg0 = cm1_pop_i64();
         _Tcp1_Fwrite_char_1(arg0);
         cm1_push_ptr(0);
         break;
      }
      case 47: {
         void* arg1 = cm1_pop_ptr();
         int32_t arg0 = cm1_pop_i64();
         _Tcp1_Fwrite_str_node_2(arg0, arg1);
         cm1_push_ptr(0);
         break;
      }
      case 48: {
         void* arg1 = cm1_pop_ptr();
         void* arg0 = cm1_pop_ptr();
         _Tlibcp1_Tfmt_Tf_f32_Ff_2(arg0, arg1);
         cm1_push_ptr(0);
         break;
      }
      case 49: {
         void* arg1 = cm1_pop_ptr();
         void* arg0 = cm1_pop_ptr();
         _Tlibcp1_Tfmt_Tf_f64_Ff_2(arg0, arg1);
         cm1_push_ptr(0);
         break;
      }
   }
}
#define CM1_OP_RETURN              0
#define CM1_OP_POP_RETURN          1
#define CM1_OP_CALL_CM1            2
#define CM1_OP_CALL_C              3
#define CM1_OP_POP                 4
#define CM1_OP_PUSH_ZERO           5
#define CM1_OP_PUSH_I32            6
#define CM1_OP_PUSH_U8             7
#define CM1_OP_PUSH_U16            8
#define CM1_OP_PUSH_U32            9
#define CM1_OP_PUSH_U64            10
#define CM1_OP_COPY_MEM            11
#define CM1_OP_ZERO_MEM            12
#define CM1_OP_GVAR_PUSH           13
#define CM1_OP_LVAR_PUSH           14
#define CM1_OP_LVAR_SET            15
#define CM1_OP_ADDR_ADD            16
#define CM1_OP_ADDR_SUB            17
#define CM1_OP_JUMP_IF_ZERO        18
#define CM1_OP_JUMP                19
#define CM1_OP_DUP_PAIR            20
#define CM1_OP_INEG                21
#define CM1_OP_BIT_NOT             22
#define CM1_OP_LOGICAL_NOT         23
#define CM1_OP_PUSH_MEM_PTR        24
#define CM1_OP_SET_MEM_PTR         25
#define CM1_OP_INT_CONVERT         26
#define CM1_OP_INT_BINARY          27
#define CM1_OP_PUSH_MEM_INT        28
#define CM1_OP_SET_MEM_INT         29
#define CM1_OP_LVAR_INC_DEC_INT    30
#define CM1_OP_MEM_INC_DEC_INT     31
#define CM1_OP_PUSH_F32            32
#define CM1_OP_PUSH_F64            33
#define CM1_OP_NUM_CONVERT         34
#define CM1_OP_FLOAT_BINARY        35
#define CM1_OP_PUSH_MEM_FLOAT      36
#define CM1_OP_SET_MEM_FLOAT       37
#define CM1_OP_FNEG                38
#define CM1_OP_FLOAT_TO_BOOL       39
#define CM1_OP_LVAR_INC_DEC_FLOAT  40
#define CM1_OP_MEM_INC_DEC_FLOAT   41
#define CM1_OP_PUSH_STRING         42
#define CM1_OP_LVAR_SPILL          43
#define CM1_OP_MEM_INC_DEC_PTR     44

#define CM1_TYPE_CHAR 1
#define CM1_TYPE_I8   2
#define CM1_TYPE_U8   3
#define CM1_TYPE_I16  4
#define CM1_TYPE_U16  5
#define CM1_TYPE_I32  6
#define CM1_TYPE_U32  7
#define CM1_TYPE_I64  8
#define CM1_TYPE_U64  9
#define CM1_TYPE_F32  10
#define CM1_TYPE_F64  11

static uint8_t* cm1_bytecode;
static uint32_t cm1_lvar_pos;

typedef uint16_t cm1_unaligned_u16 __attribute__((aligned(1), may_alias));
typedef uint32_t cm1_unaligned_u32 __attribute__((aligned(1), may_alias));
typedef uint64_t cm1_unaligned_u64 __attribute__((aligned(1), may_alias));
typedef float cm1_unaligned_f32 __attribute__((aligned(1), may_alias));
typedef double cm1_unaligned_f64 __attribute__((aligned(1), may_alias));

static bool cm1_int_is_valid(uint8_t kind) {
   return kind >= CM1_TYPE_CHAR && kind <= CM1_TYPE_U64;
}

static bool cm1_int_is_signed(uint8_t kind) {
   if (kind == CM1_TYPE_CHAR) return (char)-1 < 0;
   return (kind & 1) == 0;
}

static unsigned cm1_int_rank(uint8_t kind) {
   if (!cm1_int_is_valid(kind)) {
      printf("invalid integer type: %u\n", kind);
      exit(EXIT_FAILURE);
   }
   if (kind == CM1_TYPE_CHAR) return 0;
   return (kind - CM1_TYPE_I8) >> 1;
}

static size_t cm1_int_size(uint8_t kind) {
   return (size_t)1 << cm1_int_rank(kind);
}

static unsigned cm1_int_width(uint8_t kind) {
   // The compiler promotes 8- and 16-bit operands before arithmetic.
   return kind < CM1_TYPE_I64 ? 32 : 64;
}

static uint64_t cm1_int_convert(uint64_t value, uint8_t kind) {
   unsigned width = (unsigned)cm1_int_size(kind) * 8;
   if (width == 64) return value;
   uint64_t mask = (UINT64_C(1) << width) - 1;
   value &= mask;
   if (!cm1_int_is_signed(kind)) return value;
   uint64_t sign = UINT64_C(1) << (width - 1);
   return (value ^ sign) - sign;
}

static uint64_t cm1_load_int(const void* ptr, uint8_t kind) {
   uint64_t value;
   switch (cm1_int_rank(kind)) {
      case 0: value = *(const uint8_t*)ptr; break;
      case 1: value = *(const cm1_unaligned_u16*)ptr; break;
      case 2: value = *(const cm1_unaligned_u32*)ptr; break;
      case 3: value = *(const cm1_unaligned_u64*)ptr; break;
      default: abort();
   }
   return cm1_int_convert(value, kind);
}

static uint64_t cm1_store_int(void* ptr, uint64_t value, uint8_t kind) {
   value = cm1_int_convert(value, kind);
   switch (cm1_int_rank(kind)) {
      case 0: *(uint8_t*)ptr = value; break;
      case 1: *(cm1_unaligned_u16*)ptr = value; break;
      case 2: *(cm1_unaligned_u32*)ptr = value; break;
      case 3: *(cm1_unaligned_u64*)ptr = value; break;
      default: abort();
   }
   return value;
}

static bool cm1_float_is_valid(uint8_t kind) {
   return kind == CM1_TYPE_F32 || kind == CM1_TYPE_F64;
}

static bool cm1_number_is_valid(uint8_t kind) {
   return cm1_int_is_valid(kind) || cm1_float_is_valid(kind);
}

static float cm1_number_as_f32(union cm1_stack_item value, uint8_t kind) {
   if (kind == CM1_TYPE_F32) return value.f32;
   if (kind == CM1_TYPE_F64) return (float)value.f64;
   if (cm1_int_is_signed(kind)) return (float)value.i64;
   return (float)value.u64;
}

static double cm1_number_as_f64(union cm1_stack_item value, uint8_t kind) {
   if (kind == CM1_TYPE_F32) return (double)value.f32;
   if (kind == CM1_TYPE_F64) return value.f64;
   if (cm1_int_is_signed(kind)) return (double)value.i64;
   return (double)value.u64;
}

static union cm1_stack_item cm1_number_convert(
   union cm1_stack_item value, uint8_t src_kind, uint8_t des_kind
) {
   union cm1_stack_item result;
   result.u64 = 0;
   if (!cm1_number_is_valid(src_kind) || !cm1_number_is_valid(des_kind)) {
      printf("invalid numeric conversion: %u to %u\n", src_kind, des_kind);
      exit(EXIT_FAILURE);
   }
   if (des_kind == CM1_TYPE_F32) {
      result.f32 = cm1_number_as_f32(value, src_kind);
   } else if (des_kind == CM1_TYPE_F64) {
      result.f64 = cm1_number_as_f64(value, src_kind);
   } else if (cm1_float_is_valid(src_kind)) {
      if (cm1_int_is_signed(des_kind)) {
         int64_t integer = src_kind == CM1_TYPE_F32
            ? (int64_t)value.f32 : (int64_t)value.f64;
         result.u64 = cm1_int_convert((uint64_t)integer, des_kind);
      } else {
         uint64_t integer = src_kind == CM1_TYPE_F32
            ? (uint64_t)value.f32 : (uint64_t)value.f64;
         result.u64 = cm1_int_convert(integer, des_kind);
      }
   } else {
      result.u64 = cm1_int_convert(value.u64, des_kind);
   }
   return result;
}

void cm1_init(const char* cm1_path) {
   #ifdef _WIN32
   int fd = open(cm1_path, O_RDONLY | O_BINARY);
   #else
   int fd = open(cm1_path, O_RDONLY);
   #endif
   size_t size = lseek(fd, 0, SEEK_END) - 4; // Minus 4 for the crc32c
   // printf("loading cm1 bytecode: %s (%zu bytes)\n", cm1_path, size);
   lseek(fd, 4, SEEK_SET); // Skip the crc32c
   void* data = malloc(size);
   read(fd, data, size);
   close(fd);
   cm1_bytecode = (uint8_t*)data;
   #ifndef CM1_NO_STACK_RAND
   uint64_t splitmix64_state = 0;
   for (uint32_t i = 0; i < CM1_STACK_LIMIT; i++) {
      uint64_t z = (splitmix64_state += UINT64_C(0x9E3779B97F4A7C15));
      z = (z ^ (z >> 30)) * UINT64_C(0xBF58476D1CE4E5B9);
      z = (z ^ (z >> 27)) * UINT64_C(0x94D049BB133111EB);
      cm1_stack_v[i].i64 = z ^ (z >> 31);
   }
   #endif
}

void cm1_run(uint16_t func_idx) {
   uint32_t old_lvar_pos = cm1_lvar_pos;

   uint32_t* offset_v = (uint32_t*)cm1_bytecode;
   // printf("cm1_run function #%u, offset @ %u\n", func_idx, offset_v[func_idx]);
   uint8_t* bc = cm1_bytecode + offset_v[func_idx];
   uint8_t arg_c = *(bc++);
   cm1_lvar_pos = cm1_stack_pos - arg_c;
   uint32_t old_stack_pos = cm1_lvar_pos; // Replace arguments with the return value when the call finishes
   // printf("lvar_pos = %u, cm1_stack_pos = %u, arg_c = %u\n", cm1_lvar_pos, cm1_stack_pos, arg_c);
   uint16_t lvar_c = *((uint16_t*)bc); // Allocate stack for local variables
   bc += sizeof(uint16_t);
   cm1_stack_pos += lvar_c + 1; // +1 to leave a slot for POP_RETURN
   // Do necessary copying of arguments passed as aggregates
   // to avoid modifying the aggregate's memory that was passed by the caller
   for (;;) {
      uint8_t lvar_idx = *(bc++);
      if (lvar_idx == 0xff) break;
      uint64_t* old_ptr = (uint64_t*)cm1_stack_v[cm1_lvar_pos + lvar_idx].ptr;
      uint64_t* new_ptr = (uint64_t*)&cm1_stack_v[cm1_stack_pos];
      cm1_stack_v[cm1_lvar_pos + lvar_idx].ptr = new_ptr;
      uint16_t size = *((uint16_t*)bc);
      bc += sizeof(uint16_t);
      for (uint16_t i = 0; i < size; i++) {
         new_ptr[i] = old_ptr[i];
      }
      #ifdef CM1_DEBUG_STACK_ALLOC
      printf("Allocated %u bytes for local variable at index %u\n", size << 3, lvar_idx);
      #endif
      cm1_stack_pos += size;
   }
   // Allocate stack memory for aggregates and arrays
   for (;;) {
      uint16_t lvar_idx = *((uint16_t*)bc);
      bc += sizeof(uint16_t);
      if (lvar_idx == 0xffff) break;
      cm1_stack_v[cm1_lvar_pos + lvar_idx].ptr = &cm1_stack_v[cm1_stack_pos];
      uint16_t size = *((uint16_t*)bc);
      bc += sizeof(uint16_t);
      #ifdef CM1_DEBUG_STACK_ALLOC
      printf("Allocated %u bytes for local variable at index %u\n", size << 3, lvar_idx);
      #endif
      cm1_stack_pos += size;
   }
   for (;;) {
      uint8_t op = *(bc++);
      #ifdef CM1_DEBUG_STACK
      printf("op %u, stack:", op);
      for (uint32_t i = 0; i < cm1_stack_pos; i++) {
         printf(" %" PRIx64, cm1_stack_v[i].i64);
      }
      printf("\n");
      #endif
      switch (op) {
         case CM1_OP_RETURN: {
            cm1_lvar_pos = old_lvar_pos;
            cm1_stack_pos = old_stack_pos;
            cm1_push_ptr(NULL);
            return;
         }
         case CM1_OP_POP_RETURN: {
            union cm1_stack_item value = cm1_stack_v[--cm1_stack_pos];
            cm1_lvar_pos = old_lvar_pos;
            cm1_stack_pos = old_stack_pos;
            cm1_stack_v[cm1_stack_pos++] = value;
            return;
         }
         case CM1_OP_CALL_CM1: {
            uint16_t func_idx2 = *((uint16_t*)bc);
            bc += sizeof(uint16_t);
            cm1_run(func_idx2);
            break;
         }
         case CM1_OP_CALL_C: {
            uint16_t func_idx2 = *((uint16_t*)bc);
            bc += sizeof(uint16_t);
            // printf("running a C function, func-idx #%u\n", func_idx2);
            cm1_run_c(func_idx2);
            break;
         }
         case CM1_OP_PUSH_ZERO: {
            cm1_push_i(0);
            break;
         }
         case CM1_OP_PUSH_I32: {
            int32_t val = *((int32_t*)bc);
            bc += sizeof(int32_t);
            // printf("pushing i32 to stack: %d\n", val);
            cm1_push_i(val);
            break;
         }
         case CM1_OP_PUSH_U8: {
            uint8_t val = *((uint8_t*)bc);
            bc += sizeof(uint8_t);
            // printf("pushing i32 to stack: %d\n", val);
            cm1_push_u(val);
            break;
         }
         case CM1_OP_PUSH_U16: {
            uint16_t val = *((uint16_t*)bc);
            bc += sizeof(uint16_t);
            // printf("pushing i32 to stack: %d\n", val);
            cm1_push_u(val);
            break;
         }
         case CM1_OP_PUSH_U32: {
            uint32_t val = *((uint32_t*)bc);
            bc += sizeof(uint32_t);
            // printf("pushing i32 to stack: %d\n", val);
            cm1_push_u(val);
            break;
         }
         case CM1_OP_PUSH_U64: {
            uint64_t val = *((uint64_t*)bc);
            bc += sizeof(uint64_t);
            // printf("pushing i32 to stack: %d\n", val);
            cm1_push_u(val);
            break;
         }
         case CM1_OP_PUSH_STRING: {
            uint32_t offset = *(const cm1_unaligned_u32*)bc;
            bc += sizeof(uint32_t);
            cm1_push_ptr(cm1_bytecode + offset);
            break;
         }
         case CM1_OP_COPY_MEM: {
            size_t size = cm1_pop_usz();
            uint8_t* src = cm1_pop_ptr();
            uint8_t* des = cm1_pop_ptr();
            memcpy(des, src, size);
            cm1_push_ptr(des);
            break;
         }
         case CM1_OP_ZERO_MEM: {
            size_t size = cm1_pop_usz();
            uint8_t* des = cm1_pop_ptr();
            memset(des, 0, size);
            cm1_push_ptr(des);
            break;
         }
         case CM1_OP_GVAR_PUSH: {
            uint32_t var_idx = *((uint32_t*)bc);
            bc += sizeof(uint32_t);
            cm1_push_ptr(cm1_gvar(var_idx));
            break;
         }
         case CM1_OP_LVAR_PUSH: {
            uint16_t var_idx = *((uint16_t*)bc);
            bc += sizeof(uint16_t);
            cm1_stack_v[cm1_stack_pos++] =
               cm1_stack_v[cm1_lvar_pos + var_idx];
            break;
         }
         case CM1_OP_LVAR_SPILL: {
            uint16_t var_idx = *((uint16_t*)bc);
            bc += sizeof(uint16_t);
            uint8_t size_mode = *(bc++);
            size_t size = size_mode & 0x7f;
            union cm1_stack_item old_value =
               cm1_stack_v[cm1_lvar_pos + var_idx];
            uint8_t* storage = (uint8_t*)&cm1_stack_v[cm1_stack_pos++];
            memset(storage, 0, sizeof(union cm1_stack_item));
            if (size_mode & 0x80) memcpy(storage, &old_value, size);
            cm1_stack_v[cm1_lvar_pos + var_idx].ptr = storage;
            break;
         }
         case CM1_OP_LVAR_SET: {
            uint16_t var_idx = *((uint16_t*)bc);
            bc += sizeof(uint16_t);
            union cm1_stack_item value = cm1_stack_v[--cm1_stack_pos];
            cm1_stack_v[cm1_lvar_pos + var_idx] = value;
            cm1_stack_v[cm1_stack_pos++] = value;
            break;
         }
         case CM1_OP_PUSH_MEM_PTR: {
            ssize_t offset = cm1_pop_isz();
            uint8_t* addr = cm1_pop_ptr();
            cm1_push_ptr(*(void**)(addr + offset));
            break;
         }
         case CM1_OP_SET_MEM_PTR: {
            void* val = cm1_pop_ptr();
            ssize_t offset = cm1_pop_isz();
            uint8_t* addr = cm1_pop_ptr();
            *(void**)(addr + offset) = val;
            cm1_push_ptr(val);
            break;
         }
         case CM1_OP_INT_CONVERT: {
            uint8_t kind = *(bc++);
            cm1_stack_v[cm1_stack_pos - 1].u64 =
               cm1_int_convert(cm1_stack_v[cm1_stack_pos - 1].u64, kind);
            break;
         }
         case CM1_OP_INT_BINARY: {
            uint8_t op_kind = *(bc++);
            uint8_t int_op = op_kind >> 4;
            uint8_t kind = op_kind & 15;
            uint64_t op2 = cm1_int_convert(cm1_pop_u64(), kind);
            uint64_t op1 = cm1_int_convert(cm1_pop_u64(), kind);
            uint64_t result = 0;
            bool comparison = false;
            unsigned width = cm1_int_width(kind);
            bool is_signed = cm1_int_is_signed(kind);
            switch (int_op) {
               case 0: result = op1 + op2; break; // add
               case 1: result = op1 - op2; break; // sub
               case 2: result = op1 * op2; break; // mul
               case 3: { // div
                  if (op2 == 0) abort();
                  if (is_signed) {
                     int64_t lhs = (int64_t)op1;
                     int64_t rhs = (int64_t)op2;
                     if ((width == 32 && lhs == INT32_MIN && rhs == -1) ||
                         (width == 64 && lhs == INT64_MIN && rhs == -1)) {
                        abort();
                     }
                     result = (uint64_t)(lhs / rhs);
                  } else {
                     result = op1 / op2;
                  }
                  break;
               }
               case 4: { // mod
                  if (op2 == 0) abort();
                  if (is_signed) {
                     int64_t lhs = (int64_t)op1;
                     int64_t rhs = (int64_t)op2;
                     if ((width == 32 && lhs == INT32_MIN && rhs == -1) ||
                         (width == 64 && lhs == INT64_MIN && rhs == -1)) {
                        result = 0;
                     } else {
                        result = (uint64_t)(lhs % rhs);
                     }
                  } else {
                     result = op1 % op2;
                  }
                  break;
               }
               case 5: result = op1 << (op2 & (width - 1)); break; // shl
               case 6: // shr
                  if (is_signed) {
                     result = (uint64_t)((int64_t)op1 >> (op2 & (width - 1)));
                  } else {
                     result = op1 >> (op2 & (width - 1));
                  }
                  break;
               case 7: result = op1 & op2; break;
               case 8: result = op1 ^ op2; break;
               case 9: result = op1 | op2; break;
               case 10: // lt
                  result = is_signed ? (int64_t)op1 < (int64_t)op2 : op1 < op2;
                  comparison = true;
                  break;
               case 11: // le
                  result = is_signed ? (int64_t)op1 <= (int64_t)op2 : op1 <= op2;
                  comparison = true;
                  break;
               case 12: // gt
                  result = is_signed ? (int64_t)op1 > (int64_t)op2 : op1 > op2;
                  comparison = true;
                  break;
               case 13: // ge
                  result = is_signed ? (int64_t)op1 >= (int64_t)op2 : op1 >= op2;
                  comparison = true;
                  break;
               case 14: result = op1 == op2; comparison = true; break;
               case 15: result = op1 != op2; comparison = true; break;
               default:
                  printf("invalid integer binary op: %u\n", int_op);
                  exit(EXIT_FAILURE);
            }
            if (comparison) {
               cm1_push_i(result);
            } else {
               cm1_push_u(cm1_int_convert(result, kind));
            }
            break;
         }
         case CM1_OP_PUSH_MEM_INT: {
            uint8_t kind = *(bc++);
            ssize_t offset = cm1_pop_isz();
            uint8_t* addr = cm1_pop_ptr();
            cm1_push_u(cm1_load_int(addr + offset, kind));
            break;
         }
         case CM1_OP_SET_MEM_INT: {
            uint8_t kind = *(bc++);
            uint64_t value = cm1_pop_u64();
            ssize_t offset = cm1_pop_isz();
            uint8_t* addr = cm1_pop_ptr();
            cm1_push_u(cm1_store_int(addr + offset, value, kind));
            break;
         }
         case CM1_OP_LVAR_INC_DEC_INT: {
            uint16_t var_idx = *((uint16_t*)bc);
            bc += sizeof(uint16_t);
            uint8_t mode_kind = *(bc++);
            uint8_t mode = mode_kind >> 4;
            uint8_t kind = mode_kind & 15;
            uint64_t old_val = cm1_int_convert(
               cm1_stack_v[cm1_lvar_pos + var_idx].u64, kind);
            uint64_t new_val = cm1_int_convert(
               (mode & 1) ? old_val + 1 : old_val - 1, kind);
            cm1_stack_v[cm1_lvar_pos + var_idx].u64 = new_val;
            cm1_push_u((mode & 2) ? new_val : old_val);
            break;
         }
         case CM1_OP_MEM_INC_DEC_INT: {
            uint8_t mode_kind = *(bc++);
            uint8_t mode = mode_kind >> 4;
            uint8_t kind = mode_kind & 15;
            ssize_t offset = cm1_pop_isz();
            uint8_t* addr = cm1_pop_ptr();
            uint64_t old_val = cm1_load_int(addr + offset, kind);
            uint64_t new_val = cm1_int_convert(
               (mode & 1) ? old_val + 1 : old_val - 1, kind);
            cm1_store_int(addr + offset, new_val, kind);
            cm1_push_u((mode & 2) ? new_val : old_val);
            break;
         }
         case CM1_OP_MEM_INC_DEC_PTR: {
            uint8_t mode = *(bc++);
            size_t element_size = cm1_pop_usz();
            ssize_t offset = cm1_pop_isz();
            uint8_t* addr = cm1_pop_ptr();
            uint8_t* old_value = *(void**)(addr + offset);
            uint8_t* new_value = (mode & 1)
               ? old_value + element_size : old_value - element_size;
            *(void**)(addr + offset) = new_value;
            cm1_push_ptr((mode & 2) ? new_value : old_value);
            break;
         }
         case CM1_OP_ADDR_ADD: {
            ssize_t offset = cm1_pop_isz();
            uint8_t* addr = cm1_pop_ptr();
            cm1_push_ptr(addr + offset);
            break;
         }
         case CM1_OP_ADDR_SUB: {
            ssize_t offset = cm1_pop_isz();
            uint8_t* addr = cm1_pop_ptr();
            cm1_push_ptr(addr - offset);
            break;
         }
         case CM1_OP_POP: {
            cm1_stack_pos--;
            break;
         }
         case CM1_OP_JUMP_IF_ZERO: {
            int32_t offset = *((int32_t*)bc);
            bc += sizeof(int32_t);
            if (cm1_pop_i64() == 0) bc += offset;
            break;
         }
         case CM1_OP_JUMP: {
            int32_t offset = *((int32_t*)bc);
            bc += sizeof(int32_t) + offset;
            break;
         }
         case CM1_OP_DUP_PAIR: {
            cm1_stack_v[cm1_stack_pos] = cm1_stack_v[cm1_stack_pos - 2];
            cm1_stack_v[cm1_stack_pos + 1] = cm1_stack_v[cm1_stack_pos - 1];
            cm1_stack_pos += 2;
            break;
         }
         case CM1_OP_INEG: {
            uint64_t op1 = cm1_pop_u64();
            cm1_push_u(0 - op1);
            break;
         }
         case CM1_OP_BIT_NOT: {
            uint64_t op1 = cm1_pop_u64();
            cm1_push_u(~op1);
            break;
         }
         case CM1_OP_LOGICAL_NOT: {
            int64_t op1 = cm1_pop_i64();
            cm1_push_i(!op1);
            break;
         }
         case CM1_OP_PUSH_F32: {
            float value = *(const cm1_unaligned_f32*)bc;
            bc += sizeof(float);
            cm1_push_f32(value);
            break;
         }
         case CM1_OP_PUSH_F64: {
            double value = *(const cm1_unaligned_f64*)bc;
            bc += sizeof(double);
            cm1_push_f64(value);
            break;
         }
         case CM1_OP_NUM_CONVERT: {
            uint8_t kinds = *(bc++);
            uint8_t src_kind = kinds >> 4;
            uint8_t des_kind = kinds & 15;
            cm1_stack_v[cm1_stack_pos - 1] = cm1_number_convert(
               cm1_stack_v[cm1_stack_pos - 1], src_kind, des_kind);
            break;
         }
         case CM1_OP_FLOAT_BINARY: {
            uint8_t op_result = *(bc++);
            uint8_t operand_kinds = *(bc++);
            uint8_t float_op = op_result >> 4;
            uint8_t result_kind = op_result & 15;
            uint8_t op1_kind = operand_kinds >> 4;
            uint8_t op2_kind = operand_kinds & 15;
            union cm1_stack_item op2 = cm1_stack_v[--cm1_stack_pos];
            union cm1_stack_item op1 = cm1_stack_v[--cm1_stack_pos];
            bool comparison = float_op >= 10;
            bool comparison_result = false;
            if (result_kind == CM1_TYPE_F32) {
               float lhs = cm1_number_as_f32(op1, op1_kind);
               float rhs = cm1_number_as_f32(op2, op2_kind);
               float result = 0.0f;
               switch (float_op) {
                  case 0: result = lhs + rhs; break;
                  case 1: result = lhs - rhs; break;
                  case 2: result = lhs * rhs; break;
                  case 3: result = lhs / rhs; break;
                  case 10: comparison_result = lhs < rhs; break;
                  case 11: comparison_result = lhs <= rhs; break;
                  case 12: comparison_result = lhs > rhs; break;
                  case 13: comparison_result = lhs >= rhs; break;
                  case 14: comparison_result = lhs == rhs; break;
                  case 15: comparison_result = lhs != rhs; break;
                  default:
                     printf("invalid float binary op: %u\n", float_op);
                     exit(EXIT_FAILURE);
               }
               if (!comparison) cm1_push_f32(result);
            } else if (result_kind == CM1_TYPE_F64) {
               double lhs = cm1_number_as_f64(op1, op1_kind);
               double rhs = cm1_number_as_f64(op2, op2_kind);
               double result = 0.0;
               switch (float_op) {
                  case 0: result = lhs + rhs; break;
                  case 1: result = lhs - rhs; break;
                  case 2: result = lhs * rhs; break;
                  case 3: result = lhs / rhs; break;
                  case 10: comparison_result = lhs < rhs; break;
                  case 11: comparison_result = lhs <= rhs; break;
                  case 12: comparison_result = lhs > rhs; break;
                  case 13: comparison_result = lhs >= rhs; break;
                  case 14: comparison_result = lhs == rhs; break;
                  case 15: comparison_result = lhs != rhs; break;
                  default:
                     printf("invalid double binary op: %u\n", float_op);
                     exit(EXIT_FAILURE);
               }
               if (!comparison) cm1_push_f64(result);
            } else {
               printf("invalid floating result type: %u\n", result_kind);
               exit(EXIT_FAILURE);
            }
            if (comparison) cm1_push_i(comparison_result);
            break;
         }
         case CM1_OP_PUSH_MEM_FLOAT: {
            uint8_t kind = *(bc++);
            ssize_t offset = cm1_pop_isz();
            uint8_t* addr = cm1_pop_ptr();
            if (kind == CM1_TYPE_F32) {
               cm1_push_f32(*(const cm1_unaligned_f32*)(addr + offset));
            } else if (kind == CM1_TYPE_F64) {
               cm1_push_f64(*(const cm1_unaligned_f64*)(addr + offset));
            } else {
               printf("invalid floating memory type: %u\n", kind);
               exit(EXIT_FAILURE);
            }
            break;
         }
         case CM1_OP_SET_MEM_FLOAT: {
            uint8_t kind = *(bc++);
            union cm1_stack_item value = cm1_stack_v[--cm1_stack_pos];
            ssize_t offset = cm1_pop_isz();
            uint8_t* addr = cm1_pop_ptr();
            if (kind == CM1_TYPE_F32) {
               *(cm1_unaligned_f32*)(addr + offset) = value.f32;
            } else if (kind == CM1_TYPE_F64) {
               *(cm1_unaligned_f64*)(addr + offset) = value.f64;
            } else {
               printf("invalid floating memory type: %u\n", kind);
               exit(EXIT_FAILURE);
            }
            cm1_stack_v[cm1_stack_pos++] = value;
            break;
         }
         case CM1_OP_FNEG: {
            uint8_t kind = *(bc++);
            if (kind == CM1_TYPE_F32) {
               cm1_stack_v[cm1_stack_pos - 1].f32 =
                  -cm1_stack_v[cm1_stack_pos - 1].f32;
            } else if (kind == CM1_TYPE_F64) {
               cm1_stack_v[cm1_stack_pos - 1].f64 =
                  -cm1_stack_v[cm1_stack_pos - 1].f64;
            } else {
               printf("invalid floating negation type: %u\n", kind);
               exit(EXIT_FAILURE);
            }
            break;
         }
         case CM1_OP_FLOAT_TO_BOOL: {
            uint8_t kind = *(bc++);
            union cm1_stack_item value = cm1_stack_v[--cm1_stack_pos];
            if (kind == CM1_TYPE_F32) {
               cm1_push_i(value.f32 != 0.0f);
            } else if (kind == CM1_TYPE_F64) {
               cm1_push_i(value.f64 != 0.0);
            } else {
               printf("invalid floating condition type: %u\n", kind);
               exit(EXIT_FAILURE);
            }
            break;
         }
         case CM1_OP_LVAR_INC_DEC_FLOAT: {
            uint16_t var_idx = *((uint16_t*)bc);
            bc += sizeof(uint16_t);
            uint8_t mode_kind = *(bc++);
            uint8_t mode = mode_kind >> 4;
            uint8_t kind = mode_kind & 15;
            union cm1_stack_item old_value =
               cm1_stack_v[cm1_lvar_pos + var_idx];
            union cm1_stack_item new_value = old_value;
            if (kind == CM1_TYPE_F32) {
               new_value.f32 += (mode & 1) ? 1.0f : -1.0f;
            } else if (kind == CM1_TYPE_F64) {
               new_value.f64 += (mode & 1) ? 1.0 : -1.0;
            } else {
               printf("invalid floating increment type: %u\n", kind);
               exit(EXIT_FAILURE);
            }
            cm1_stack_v[cm1_lvar_pos + var_idx] = new_value;
            cm1_stack_v[cm1_stack_pos++] =
               (mode & 2) ? new_value : old_value;
            break;
         }
         case CM1_OP_MEM_INC_DEC_FLOAT: {
            uint8_t mode_kind = *(bc++);
            uint8_t mode = mode_kind >> 4;
            uint8_t kind = mode_kind & 15;
            ssize_t offset = cm1_pop_isz();
            uint8_t* addr = cm1_pop_ptr();
            union cm1_stack_item old_value;
            union cm1_stack_item new_value;
            old_value.u64 = 0;
            if (kind == CM1_TYPE_F32) {
               old_value.f32 = *(const cm1_unaligned_f32*)(addr + offset);
               new_value = old_value;
               new_value.f32 += (mode & 1) ? 1.0f : -1.0f;
               *(cm1_unaligned_f32*)(addr + offset) = new_value.f32;
            } else if (kind == CM1_TYPE_F64) {
               old_value.f64 = *(const cm1_unaligned_f64*)(addr + offset);
               new_value = old_value;
               new_value.f64 += (mode & 1) ? 1.0 : -1.0;
               *(cm1_unaligned_f64*)(addr + offset) = new_value.f64;
            } else {
               printf("invalid floating increment type: %u\n", kind);
               exit(EXIT_FAILURE);
            }
            cm1_stack_v[cm1_stack_pos++] =
               (mode & 2) ? new_value : old_value;
            break;
         }
         default:
            printf("invalid bytecode op: %u\n", op);
            exit(EXIT_FAILURE);
      }
   }
}
