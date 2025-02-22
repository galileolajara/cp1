// Generated by Cp1
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "file.cp1.h"
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#define _NLibC_NExit_Csuccess 0
#define _NLibC_NExit_Cfailure (_NLibC_NExit_Csuccess + 1)
#define _NWindows_NCreateFileShareMode_C0 0
#define _NWindows_NHandle_Cnull 0
typedef int _NLibC_NExit;
typedef uint32_t _NWindows_NCreateFileAccess;
typedef uint32_t _NWindows_NCreateFileShareMode;
typedef uint32_t _NWindows_NCreateFileCreationDisposition;
typedef uint32_t _NWindows_NCreateFileFlags;
typedef int _NPosix_NFd;
typedef int _NPosix_NOpenFlags;
typedef int _NPosix_NSeek;
struct _NLibCp1_NStdOut;
struct _NLibCp1_NStdOut {
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
char* _Ginput_path;
uint32_t _Gpreprocess_def_c;
uint32_t _Gpreprocess_def_cap;
char** _Gpreprocess_def_str_v;
uint8_t* _Gpreprocess_def_len_v;
char* _Gstdout_buf_data;
uint32_t _Gstdout_buf_len;
uint32_t _Gstdout_buf_cap;
int main(int _Larg_c_0, char** _Larg_v_1);
void _NLibCp1_Pstdout_1(struct _NLibCp1_NStdOut* _Lso_0);
void _NLibCp1_NStdOut_Pstdout_cstr_3(struct _NLibCp1_NStdOut* _Lso_0, char* _Lstr_1, uint32_t _Llen_2);
void _Tchar_Pstdout_arr_2(char* _Lstr_0, struct _NLibCp1_NStdOut* _Lso_1);
void _NLibCp1_NStdOut_Pstdout_end_1(struct _NLibCp1_NStdOut* _Lso_0);
void _Tchar_Pstdout_2(char _Lval_0, struct _NLibCp1_NStdOut* _Lso_1);
void _NCp1_Ppreprocess_def_2(char* _Lname_0, uint8_t _Llen_1);
void* _NCp1_Pread_file_2(char* _Lpath_0, size_t* _Lout_size_1);
void _NCp1_Ppreprocess_init_0();
void _NCp1_Ppreprocess_2(void** _Lin_out_data_0, size_t* _Lin_out_size_1);
bool _NCp1_Pwrite_file_3(char* _Lpath_0, void* _Ldata_1, size_t _Lsize_2);
void _NLibCp1_Pstdout_bytes_2(void* _Ldata_0, size_t _Lsize_1);
void _NLibCp1_Pstdout_cstr_1(char* _Lstr_0);
void _NLibCp1_Pstdout_flush_0();
void _NLibCp1_Pstdout_char_1(char _Lval_0);
void* _NCp1_Pread_file_4(char* _Lpath_0, int32_t _Ladd_before_1, int32_t _Ladd_after_2, size_t* _Lout_size_3);
void _Tu32_Pstdout_2(uint32_t _Lval_0, struct _NLibCp1_NStdOut* _Lso_1);
bool _NCp1_Ppreprocess_def_get_2(char* _Lname_0, uint8_t _Llen_1);
bool _NPosix_NFd_Popen_4(_NPosix_NFd* _Lfile_0, char* _Lpath_1, _NPosix_NOpenFlags _Lflags_2, int _Lmode_3);
void _NLibCp1_Pstdout_reserve_1(uint32_t _Llen_0);
#define _NLibC_Pmalloc_arr_2(var, c) var = malloc(sizeof(var[0]) * (c))
bool _NPosix_NFd_Popen_3(_NPosix_NFd* _Lfile_0, char* _Lpath_1, _NPosix_NOpenFlags _Lflags_2);
void _NLibCp1_Pstdout_u32_1(uint32_t _Lval_0);
#ifdef _WIN32
#define _NPosix_Popen_3(p, f, m) open(p, f | O_BINARY, m)
#else
#define _NPosix_Popen_3(p, f, m) open(p, f, m)
#endif
#define _NLibC_Prealloc_arr_2(var, c) var = realloc(var, sizeof(var[0]) * (c))
#ifdef _WIN32
#define _NPosix_Popen_2(p, f) open(p, f | O_BINARY)
#else
#define _NPosix_Popen_2(p, f) open(p, f)
#endif
int main(int _Larg_c_0, char** _Larg_v_1) {
int32_t _Li_3;
char* _Lin_data_13 = {0};
size_t _Lin_size_14;
if(_Larg_c_0 < 3) {
struct _NLibCp1_NStdOut _L_2;
usage:
_NLibCp1_Pstdout_1(&_L_2);
_NLibCp1_NStdOut_Pstdout_cstr_3(&_L_2, "Usage: ", 7u);
_Tchar_Pstdout_arr_2(_Larg_v_1[0], &_L_2);
_NLibCp1_NStdOut_Pstdout_cstr_3(&_L_2, " [options] [.cp1 input file] [.cp1 output file]\n"
"Options:\n"
" -Ddefinename     Define a name that will yield true on #if(...) preprocessor\n", 135u);
_NLibCp1_NStdOut_Pstdout_end_1(&_L_2);
exit(_NLibC_NExit_Cfailure);
}
_Li_3 = 1;
for(int i = _Larg_c_0 - 1; i > 0; ) {
i --;
if(_Larg_v_1[_Li_3][0] == '-') {
if(_Larg_v_1[_Li_3][1] == 'D') {
char* _Lname_4;
int32_t _Llen_5;
_Lname_4 = &_Larg_v_1[_Li_3][2];
_Llen_5 = 0;
while(1) {
if(_Lname_4[_Llen_5] == '\0') {
goto break_1;
}
if(((_Lname_4[_Llen_5] >= 'a') && (_Lname_4[_Llen_5] <= 'z'))) {
} else if(((_Lname_4[_Llen_5] >= 'A') && (_Lname_4[_Llen_5] <= 'Z'))) {
} else if(((_Lname_4[_Llen_5] >= '0') && (_Lname_4[_Llen_5] <= '9'))) {
if(_Llen_5 == 0) {
struct _NLibCp1_NStdOut _L_6;
_NLibCp1_Pstdout_1(&_L_6);
_NLibCp1_NStdOut_Pstdout_cstr_3(&_L_6, "Error, in option -Ddefinename, definename cannot begin with a number\n", 69u);
_NLibCp1_NStdOut_Pstdout_end_1(&_L_6);
goto usage;
}
} else if(_Lname_4[_Llen_5] == '_') {
} else if(_Lname_4[_Llen_5] == '-') {
if(_Llen_5 == 0) {
struct _NLibCp1_NStdOut _L_7;
_NLibCp1_Pstdout_1(&_L_7);
_NLibCp1_NStdOut_Pstdout_cstr_3(&_L_7, "Error, in option -Ddefinename (which is ", 40u);
_Tchar_Pstdout_arr_2(_Larg_v_1[_Li_3], &_L_7);
_NLibCp1_NStdOut_Pstdout_cstr_3(&_L_7, "), definename' cannot begin with a dash\n", 40u);
_NLibCp1_NStdOut_Pstdout_end_1(&_L_7);
goto usage;
} else if(_Lname_4[(_Llen_5 - 1)] == '-') {
struct _NLibCp1_NStdOut _L_8;
_NLibCp1_Pstdout_1(&_L_8);
_NLibCp1_NStdOut_Pstdout_cstr_3(&_L_8, "Error, in option -Ddefinename (which is ", 40u);
_Tchar_Pstdout_arr_2(_Larg_v_1[_Li_3], &_L_8);
_NLibCp1_NStdOut_Pstdout_cstr_3(&_L_8, "), definename' cannot contain consecutive a dashes\n", 51u);
_NLibCp1_NStdOut_Pstdout_end_1(&_L_8);
goto usage;
}
} else {
struct _NLibCp1_NStdOut _L_9;
_NLibCp1_Pstdout_1(&_L_9);
_NLibCp1_NStdOut_Pstdout_cstr_3(&_L_9, "Error, in option -Ddefinename (which is ", 40u);
_Tchar_Pstdout_arr_2(_Larg_v_1[_Li_3], &_L_9);
_NLibCp1_NStdOut_Pstdout_cstr_3(&_L_9, "), invalid character '", 22u);
_Tchar_Pstdout_2(_Lname_4[_Llen_5], &_L_9);
_NLibCp1_NStdOut_Pstdout_cstr_3(&_L_9, "' was detected in definename'\n", 30u);
_NLibCp1_NStdOut_Pstdout_end_1(&_L_9);
goto usage;
}
_Llen_5++;
continue_1:;
}
break_1:;
if(_Llen_5 == 0) {
struct _NLibCp1_NStdOut _L_10;
_NLibCp1_Pstdout_1(&_L_10);
_NLibCp1_NStdOut_Pstdout_cstr_3(&_L_10, "Error, in option -Ddefinename (which is ", 40u);
_Tchar_Pstdout_arr_2(_Larg_v_1[_Li_3], &_L_10);
_NLibCp1_NStdOut_Pstdout_cstr_3(&_L_10, "), Definename' cannot be blank\n", 31u);
_NLibCp1_NStdOut_Pstdout_end_1(&_L_10);
goto usage;
}
if(_Lname_4[(_Llen_5 - 1)] == '-') {
struct _NLibCp1_NStdOut _L_11;
_NLibCp1_Pstdout_1(&_L_11);
_NLibCp1_NStdOut_Pstdout_cstr_3(&_L_11, "Error, in option -Ddefinename (which is ", 40u);
_Tchar_Pstdout_arr_2(_Larg_v_1[_Li_3], &_L_11);
_NLibCp1_NStdOut_Pstdout_cstr_3(&_L_11, "), Definename' cannot end with a dash\n", 38u);
_NLibCp1_NStdOut_Pstdout_end_1(&_L_11);
goto usage;
}
_NCp1_Ppreprocess_def_2(_Lname_4, _Llen_5);
} else {
struct _NLibCp1_NStdOut _L_12;
_NLibCp1_Pstdout_1(&_L_12);
_NLibCp1_NStdOut_Pstdout_cstr_3(&_L_12, "Error, invalid option '", 23u);
_Tchar_Pstdout_2(_Larg_v_1[_Li_3][1], &_L_12);
_NLibCp1_NStdOut_Pstdout_cstr_3(&_L_12, "'\n", 2u);
_NLibCp1_NStdOut_Pstdout_end_1(&_L_12);
goto usage;
}
} else {
goto break_0;
}
_Li_3++;
continue_0:;
}
break_0:;
if((_Larg_c_0 - _Li_3) != 2) {
goto usage;
}
_Ginput_path = _Larg_v_1[_Li_3];
_Lin_data_13 = _NCp1_Pread_file_2(_Larg_v_1[_Li_3], &_Lin_size_14);
if(_Lin_data_13 == NULL) {
struct _NLibCp1_NStdOut _L_15;
_NLibCp1_Pstdout_1(&_L_15);
_NLibCp1_NStdOut_Pstdout_cstr_3(&_L_15, "Cannot open file for reading: ", 30u);
_Tchar_Pstdout_arr_2(_Larg_v_1[(_Li_3 + 1)], &_L_15);
_Tchar_Pstdout_2('\n', &_L_15);
_NLibCp1_NStdOut_Pstdout_end_1(&_L_15);
exit(_NLibC_NExit_Cfailure);
}
_NCp1_Ppreprocess_init_0();
_NCp1_Ppreprocess_2(&_Lin_data_13, &_Lin_size_14);
if(!_NCp1_Pwrite_file_3(_Larg_v_1[(_Li_3 + 1)], _Lin_data_13, _Lin_size_14)) {
struct _NLibCp1_NStdOut _L_16;
_NLibCp1_Pstdout_1(&_L_16);
_NLibCp1_NStdOut_Pstdout_cstr_3(&_L_16, "Cannot open file for writing: ", 30u);
_Tchar_Pstdout_arr_2(_Larg_v_1[(_Li_3 + 1)], &_L_16);
_Tchar_Pstdout_2('\n', &_L_16);
_NLibCp1_NStdOut_Pstdout_end_1(&_L_16);
exit(_NLibC_NExit_Cfailure);
}
return 0;
}
inline void _NLibCp1_Pstdout_1(struct _NLibCp1_NStdOut* _Lso_0) {
}
inline void _NLibCp1_NStdOut_Pstdout_cstr_3(struct _NLibCp1_NStdOut* _Lso_0, char* _Lstr_1, uint32_t _Llen_2) {
_NLibCp1_Pstdout_bytes_2(_Lstr_1, _Llen_2);
}
inline void _Tchar_Pstdout_arr_2(char* _Lstr_0, struct _NLibCp1_NStdOut* _Lso_1) {
_NLibCp1_Pstdout_cstr_1(_Lstr_0);
}
inline void _NLibCp1_NStdOut_Pstdout_end_1(struct _NLibCp1_NStdOut* _Lso_0) {
_NLibCp1_Pstdout_flush_0();
}
inline void _Tchar_Pstdout_2(char _Lval_0, struct _NLibCp1_NStdOut* _Lso_1) {
_NLibCp1_Pstdout_char_1(_Lval_0);
}
void _NCp1_Ppreprocess_def_2(char* _Lname_0, uint8_t _Llen_1) {
uint32_t _Li_2;
_Li_2 = _Gpreprocess_def_c++;
if(_Gpreprocess_def_cap < _Gpreprocess_def_c) {
_Gpreprocess_def_cap = ((_Gpreprocess_def_c << 1) + 8);
_Gpreprocess_def_str_v = realloc(_Gpreprocess_def_str_v, _Gpreprocess_def_cap * sizeof(size_t));
_Gpreprocess_def_len_v = realloc(_Gpreprocess_def_len_v, _Gpreprocess_def_cap * sizeof(size_t));
}
_Gpreprocess_def_str_v[_Li_2] = _Lname_0;
_Gpreprocess_def_len_v[_Li_2] = _Llen_1;
}
inline void* _NCp1_Pread_file_2(char* _Lpath_0, size_t* _Lout_size_1) {
return _NCp1_Pread_file_4(_Lpath_0, 0, 0, _Lout_size_1);
}
void _NCp1_Ppreprocess_init_0() {
#ifdef _WIN32
_NCp1_Ppreprocess_def_2("windows", 7);
#endif
#ifdef __APPLE__
_NCp1_Ppreprocess_def_2("apple", 5);
#endif
#ifdef __linux__
_NCp1_Ppreprocess_def_2("linux", 5);
#endif
#ifdef __unix__
_NCp1_Ppreprocess_def_2("unix", 4);
#endif
#if defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__NetBSD__) || defined(__DragonFly__)
_NCp1_Ppreprocess_def_2("bsd", 3);
#endif
#ifdef __FreeBSD__
_NCp1_Ppreprocess_def_2("freebsd", 7);
#endif
#ifdef __OpenBSD__
_NCp1_Ppreprocess_def_2("openbsd", 7);
#endif
#ifdef __NetBSD__
_NCp1_Ppreprocess_def_2("netbsd", 6);
#endif
#ifdef __DragonFly__
_NCp1_Ppreprocess_def_2("dragonfly", 9);
#endif
#if defined(_LP64) || defined(__LP64__)
_NCp1_Ppreprocess_def_2("cpu64", 5);
#endif
}
void _NCp1_Ppreprocess_2(void** _Lin_out_data_0, size_t* _Lin_out_size_1) {
bool _Lpreprocess_2;
char* _Lin_data_3;
size_t _Lin_size_4;
union _NCp1_NRdr _Lr_end_5 = {0};
union _NCp1_NRdr _Lr_6 = {0};
void* _Lnew_data_7;
union _NCp1_NWtr _Lw_8 = {0};
uint32_t _Lline_9;
union _NCp1_NWtr _Lw_begin_28 = {0};
_Lpreprocess_2 = false;
_Lin_data_3 = (*_Lin_out_data_0);
_Lin_size_4 = (*_Lin_out_size_1);
_Lr_end_5._Freff = _Lin_data_3;
_Lr_end_5._Fpos += _Lin_size_4;
_Lr_6._Freff = _Lin_data_3;
_Lnew_data_7 = malloc(_Lin_size_4 + 1);
_Lw_8._Freff = _Lnew_data_7;
_Lline_9 = (uint32_t)(0);
while(_Lr_6._Fpos < _Lr_end_5._Fpos) {
int32_t _Lline_len_10;
_Lline_9++;
_Lline_len_10 = 0;
while(1) {
if(_Lr_6._Fp1[_Lline_len_10] == '\n') {
goto break_1;
}
_Lline_len_10++;
continue_1:;
}
break_1:;
if(((_Lr_6._Fp1[0] == '#') && (_Lr_6._Fp1[1] == 'i') && (_Lr_6._Fp1[2] == 'f') && ((_Lr_6._Fp1[3] == '(') || ((_Lr_6._Fp1[3] == '!') && (_Lr_6._Fp1[4] == '('))))) {
uint32_t _Lif_line_11;
int32_t _Lstart_12;
bool _Linvert_13;
int32_t _Lrparen_14;
char* _Ldef_str_17;
int32_t _Ldef_len_18;
bool _Lok_19;
char* _Lindention_20;
int32_t _Lindention_len_21;
_Lif_line_11 = _Lline_9;
_Lw_8._Fp1[0] = '\n';
_Lw_8._Fpos++;
_Lstart_12 = 4;
_Linvert_13 = false;
if(_Lr_6._Fp1[3] == '!') {
_Lstart_12 = 5;
_Linvert_13 = true;
}
_Lrparen_14 = -1;
int32_t _Li_15;
_Li_15 = _Lstart_12;
for(int i = _Lline_len_10 - _Lstart_12; i > 0; ) {
i --;
if(_Lr_6._Fp1[_Li_15] == ')') {
_Lrparen_14 = _Li_15;
goto break_2;
}
continue_2:;
_Li_15++;
}
break_2:;
if(_Lrparen_14 == -1) {
struct _NLibCp1_NStdOut _L_16;
_NLibCp1_Pstdout_1(&_L_16);
_Tchar_Pstdout_arr_2(_Ginput_path, &_L_16);
_Tchar_Pstdout_2(':', &_L_16);
_Tu32_Pstdout_2(_Lline_9, &_L_16);
_NLibCp1_NStdOut_Pstdout_cstr_3(&_L_16, ": Error in preprocessing the code, #if(...) must have a closing parenthesis ')'\n", 80u);
_NLibCp1_NStdOut_Pstdout_end_1(&_L_16);
exit(_NLibC_NExit_Cfailure);
}
_Ldef_str_17 = &_Lr_6._Fcharr[_Lstart_12];
_Ldef_len_18 = (_Lrparen_14 - _Lstart_12);
_Lok_19 = _NCp1_Ppreprocess_def_get_2(_Ldef_str_17, _Ldef_len_18);
if(_Linvert_13) {
_Lok_19 = !_Lok_19;
}
_Lr_6._Fpos += (_Lline_len_10 + 1);
_Lindention_20 = NULL;
_Lindention_len_21 = -1;
if(_Lr_6._Fpos < _Lr_end_5._Fpos) {
int32_t _Lline_len_22;
int32_t _Lfirst_char_23;
_Lline_len_22 = 0;
while(1) {
if(_Lr_6._Fp1[_Lline_len_22] == '\n') {
goto break_3;
}
_Lline_len_22++;
continue_3:;
}
break_3:;
_Lfirst_char_23 = 0;
while(1) {
if(((_Lr_6._Fp1[_Lfirst_char_23] == ' ') || (_Lr_6._Fp1[_Lfirst_char_23] == '\t'))) {
} else {
goto break_4;
}
_Lfirst_char_23++;
continue_4:;
}
break_4:;
if(_Lok_19) {
memcpy(_Lw_8._Fp1, &_Lr_6._Fp1[_Lfirst_char_23], (_Lline_len_22 + 1) - _Lfirst_char_23);
_Lw_8._Fpos += ((_Lline_len_22 + 1) - _Lfirst_char_23);
if(((_Lr_6._Fp1[_Lfirst_char_23] == '#') && (_Lr_6._Fp1[(_Lfirst_char_23 + 1)] == 'i') && (_Lr_6._Fp1[(_Lfirst_char_23 + 2)] == 'f') && ((_Lr_6._Fp1[(_Lfirst_char_23 + 3)] == '(') || ((_Lr_6._Fp1[(_Lfirst_char_23 + 3)] == '!') && (_Lr_6._Fp1[(_Lfirst_char_23 + 4)] == '('))))) {
_Lpreprocess_2 = true;
}
} else {
_Lw_8._Fp1[0] = '\n';
_Lw_8._Fpos++;
}
_Lindention_20 = _Lr_6._Fcharr;
_Lindention_len_21 = _Lfirst_char_23;
_Lline_len_22++;
_Lr_6._Fpos += _Lline_len_22;
}
if(_Lindention_len_21 <= 0) {
struct _NLibCp1_NStdOut _L_24;
_NLibCp1_Pstdout_1(&_L_24);
_Tchar_Pstdout_arr_2(_Ginput_path, &_L_24);
_Tchar_Pstdout_2(':', &_L_24);
_Tu32_Pstdout_2(_Lline_9, &_L_24);
_NLibCp1_NStdOut_Pstdout_cstr_3(&_L_24, ": Error in preprocessing the code, #if(...). Its next line (line ", 65u);
_Tu32_Pstdout_2(_Lline_9 + 1, &_L_24);
_NLibCp1_NStdOut_Pstdout_cstr_3(&_L_24, ") must be indented more than line ", 34u);
_Tu32_Pstdout_2(_Lline_9, &_L_24);
_Tchar_Pstdout_2('\n', &_L_24);
_NLibCp1_NStdOut_Pstdout_end_1(&_L_24);
exit(_NLibC_NExit_Cfailure);
}
_Lline_9++;
while(_Lr_6._Fpos < _Lr_end_5._Fpos) {
int32_t _Lline_len_25;
int32_t _Lfirst_char_26;
_Lline_9++;
_Lline_len_25 = 0;
while(1) {
if(_Lr_6._Fp1[_Lline_len_25] == '\n') {
goto break_6;
}
_Lline_len_25++;
continue_6:;
}
break_6:;
_Lfirst_char_26 = 0;
while(1) {
if(((_Lr_6._Fp1[_Lfirst_char_26] == ' ') || (_Lr_6._Fp1[_Lfirst_char_26] == '\t'))) {
} else {
goto break_7;
}
_Lfirst_char_26++;
continue_7:;
}
break_7:;
if(((_Lline_len_25 >= _Lindention_len_21) && (memcmp(_Lr_6._Fp1, _Lindention_20, _Lindention_len_21) == 0))) {
if(_Lok_19) {
memcpy(_Lw_8._Fp1, &_Lr_6._Fp1[_Lindention_len_21], (_Lline_len_25 + 1) - _Lindention_len_21);
_Lw_8._Fpos += ((_Lline_len_25 + 1) - _Lindention_len_21);
if(((_Lr_6._Fp1[_Lindention_len_21] == '#') && (_Lr_6._Fp1[(_Lindention_len_21 + 1)] == 'i') && (_Lr_6._Fp1[(_Lindention_len_21 + 2)] == 'f') && ((_Lr_6._Fp1[(_Lindention_len_21 + 3)] == '(') || ((_Lr_6._Fp1[(_Lindention_len_21 + 3)] == '!') && (_Lr_6._Fp1[(_Lindention_len_21 + 4)] == '('))))) {
_Lpreprocess_2 = true;
}
} else {
_Lw_8._Fp1[0] = '\n';
_Lw_8._Fpos++;
}
} else {
if(((_Lr_6._Fp1[0] == '#') && (_Lr_6._Fp1[1] == 'e') && (_Lr_6._Fp1[2] == 'n') && (_Lr_6._Fp1[3] == 'd') && (_Lr_6._Fp1[4] == 'i') && (_Lr_6._Fp1[5] == 'f') && ((_Lr_6._Fp1[6] == ' ') || (_Lr_6._Fp1[6] == '\t') || (_Lr_6._Fp1[6] == '\n')))) {
_Lw_8._Fp1[0] = '\n';
_Lw_8._Fpos++;
_Lr_6._Fpos += (_Lline_len_25 + 1);
} else {
struct _NLibCp1_NStdOut _L_27;
_NLibCp1_Pstdout_1(&_L_27);
_Tchar_Pstdout_arr_2(_Ginput_path, &_L_27);
_Tchar_Pstdout_2(':', &_L_27);
_Tu32_Pstdout_2(_Lline_9, &_L_27);
_NLibCp1_NStdOut_Pstdout_cstr_3(&_L_27, ": Error, expecting '#endif' with the same indention as '#if' on line ", 69u);
_Tu32_Pstdout_2(_Lif_line_11, &_L_27);
_NLibCp1_NStdOut_Pstdout_cstr_3(&_L_27, ", because line ", 15u);
_Tu32_Pstdout_2(_Lline_9, &_L_27);
_NLibCp1_NStdOut_Pstdout_cstr_3(&_L_27, "'s indention is different from indention at line ", 49u);
_Tu32_Pstdout_2(_Lif_line_11 + 1, &_L_27);
_Tchar_Pstdout_2('\n', &_L_27);
_NLibCp1_NStdOut_Pstdout_end_1(&_L_27);
exit(_NLibC_NExit_Cfailure);
}
goto break_5;
}
_Lline_len_25++;
_Lr_6._Fpos += _Lline_len_25;
continue_5:;
}
break_5:;
goto continue_0;
} else {
_Lline_len_10++;
memcpy(_Lw_8._Fp1, _Lr_6._Fp1, _Lline_len_10);
_Lw_8._Fpos += _Lline_len_10;
}
_Lr_6._Fpos += _Lline_len_10;
continue_0:;
}
break_0:;
_Lw_8._Fp1[0] = '\0';
free(_Lin_data_3);
(*_Lin_out_data_0) = _Lnew_data_7;
_Lw_begin_28._Freff = _Lnew_data_7;
(*_Lin_out_size_1) = (_Lw_8._Fpos - _Lw_begin_28._Fpos);
if(_Lpreprocess_2) {
_NCp1_Ppreprocess_2(_Lin_out_data_0, _Lin_out_size_1);
}
}
bool _NCp1_Pwrite_file_3(char* _Lpath_0, void* _Ldata_1, size_t _Lsize_2) {
#ifdef _WIN32
if(true) {
HANDLE _Lh_3;
uint32_t _Lbytes_written_4 = {0};
_Lh_3 = CreateFileA(_Lpath_0, GENERIC_WRITE, _NWindows_NCreateFileShareMode_C0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, _NWindows_NHandle_Cnull);
if(_Lh_3 == INVALID_HANDLE_VALUE) {
return false;
}
if((!WriteFile(_Lh_3, _Ldata_1, _Lsize_2, &_Lbytes_written_4, NULL) || (_Lbytes_written_4 != _Lsize_2))) {
CloseHandle(_Lh_3);
return false;
}
CloseHandle(_Lh_3);
return true;
}
#else
if(true) {
_NPosix_NFd _Lfd_5 = {0};
if(!_NPosix_NFd_Popen_4(&_Lfd_5, _Lpath_0, O_CREAT | O_TRUNC | O_WRONLY, 0644)) {
return false;
}
if(write(_Lfd_5, _Ldata_1, _Lsize_2) != _Lsize_2) {
close(_Lfd_5);
return false;
}
close(_Lfd_5);
return true;
}
#endif
}
inline void _NLibCp1_Pstdout_bytes_2(void* _Ldata_0, size_t _Lsize_1) {
_NLibCp1_Pstdout_reserve_1(_Lsize_1);
memcpy(&_Gstdout_buf_data[_Gstdout_buf_len], _Ldata_0, _Lsize_1);
_Gstdout_buf_len += _Lsize_1;
}
inline void _NLibCp1_Pstdout_cstr_1(char* _Lstr_0) {
_NLibCp1_Pstdout_bytes_2(_Lstr_0, strlen(_Lstr_0));
}
inline void _NLibCp1_Pstdout_flush_0() {
write((_NPosix_NFd)(1), _Gstdout_buf_data, _Gstdout_buf_len);
_Gstdout_buf_len = 0;
}
inline void _NLibCp1_Pstdout_char_1(char _Lval_0) {
_NLibCp1_Pstdout_reserve_1(1);
_Gstdout_buf_data[_Gstdout_buf_len++] = _Lval_0;
}
inline void* _NCp1_Pread_file_4(char* _Lpath_0, int32_t _Ladd_before_1, int32_t _Ladd_after_2, size_t* _Lout_size_3) {
#ifdef _WIN32
if(true) {
HANDLE _Lh_4;
LARGE_INTEGER _Lf_size_5 = {0};
uint64_t _Lsize_6;
uint8_t* _Lbuf_7 = {0};
uint32_t _Lbytes_read_8 = {0};
_Lh_4 = CreateFileA(_Lpath_0, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, _NWindows_NHandle_Cnull);
if(_Lh_4 == INVALID_HANDLE_VALUE) {
return NULL;
}
if(!GetFileSizeEx(_Lh_4, &_Lf_size_5)) {
CloseHandle(_Lh_4);
return NULL;
}
_Lsize_6 = _Lf_size_5.QuadPart;
_NLibC_Pmalloc_arr_2(_Lbuf_7, _Ladd_before_1 + _Lsize_6 + _Ladd_after_2);
if((!ReadFile(_Lh_4, &_Lbuf_7[_Ladd_before_1], _Lsize_6, &_Lbytes_read_8, NULL) || (_Lbytes_read_8 != _Lsize_6))) {
free(_Lbuf_7);
CloseHandle(_Lh_4);
return NULL;
}
CloseHandle(_Lh_4);
(*_Lout_size_3) = _Lsize_6;
return _Lbuf_7;
}
#else
if(true) {
_NPosix_NFd _Lfd_9 = {0};
size_t _Lsize_10;
uint8_t* _Lbuf_11 = {0};
if(!_NPosix_NFd_Popen_3(&_Lfd_9, _Lpath_0, O_RDONLY)) {
return NULL;
}
_Lsize_10 = lseek(_Lfd_9, 0, SEEK_END);
if(_Lsize_10 == -1) {
close(_Lfd_9);
return NULL;
}
if(lseek(_Lfd_9, 0, SEEK_SET) == -1) {
close(_Lfd_9);
return NULL;
}
_NLibC_Pmalloc_arr_2(_Lbuf_11, _Ladd_before_1 + _Lsize_10 + _Ladd_after_2);
if(read(_Lfd_9, &_Lbuf_11[_Ladd_before_1], _Lsize_10) != _Lsize_10) {
free(_Lbuf_11);
close(_Lfd_9);
return NULL;
}
close(_Lfd_9);
(*_Lout_size_3) = _Lsize_10;
return _Lbuf_11;
}
#endif
}
inline void _Tu32_Pstdout_2(uint32_t _Lval_0, struct _NLibCp1_NStdOut* _Lso_1) {
_NLibCp1_Pstdout_u32_1(_Lval_0);
}
bool _NCp1_Ppreprocess_def_get_2(char* _Lname_0, uint8_t _Llen_1) {
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
inline bool _NPosix_NFd_Popen_4(_NPosix_NFd* _Lfile_0, char* _Lpath_1, _NPosix_NOpenFlags _Lflags_2, int _Lmode_3) {
_NPosix_NFd _Lfd_4;
_Lfd_4 = _NPosix_Popen_3(_Lpath_1, _Lflags_2, _Lmode_3);
if(_Lfd_4 != -1) {
(*_Lfile_0) = _Lfd_4;
return true;
} else {
return false;
}
}
void _NLibCp1_Pstdout_reserve_1(uint32_t _Llen_0) {
uint32_t _Lspace_1;
_Lspace_1 = (_Gstdout_buf_cap - _Gstdout_buf_len);
if(_Lspace_1 < _Llen_0) {
if(_Gstdout_buf_cap == 0) {
_Gstdout_buf_cap = 256;
} else {
_Gstdout_buf_cap += _Gstdout_buf_cap;
}
_Lspace_1 = (_Gstdout_buf_cap - _Gstdout_buf_len);
while(_Lspace_1 < _Llen_0) {
_Gstdout_buf_cap += _Gstdout_buf_cap;
_Lspace_1 = (_Gstdout_buf_cap - _Gstdout_buf_len);
continue_0:;
}
break_0:;
_NLibC_Prealloc_arr_2(_Gstdout_buf_data, _Gstdout_buf_cap);
}
}
inline bool _NPosix_NFd_Popen_3(_NPosix_NFd* _Lfile_0, char* _Lpath_1, _NPosix_NOpenFlags _Lflags_2) {
_NPosix_NFd _Lfd_3;
_Lfd_3 = _NPosix_Popen_2(_Lpath_1, _Lflags_2);
if(_Lfd_3 != -1) {
(*_Lfile_0) = _Lfd_3;
return true;
} else {
return false;
}
}
void _NLibCp1_Pstdout_u32_1(uint32_t _Lval_0) {
_NLibCp1_Pstdout_reserve_1(10);
if(_Lval_0 == 0) {
_Gstdout_buf_data[_Gstdout_buf_len++] = '0';
} else {
char* _Ldata_1 = {0};
int32_t _Ldigits_2;
int32_t _Lstart_3;
int32_t _Lend_4;
_Ldata_1 = &_Gstdout_buf_data[_Gstdout_buf_len];
_Ldigits_2 = 0;
while(1) {
_Ldata_1[_Ldigits_2++] = ((_Lval_0 % 10) + '0');
_Lval_0 /= 10;
if(_Lval_0 == 0) {
goto break_0;
}
continue_0:;
}
break_0:;
_Lstart_3 = 0;
_Lend_4 = (_Ldigits_2 - 1);
while(_Lstart_3 < _Lend_4) {
char _Ltmp_5;
_Ltmp_5 = _Ldata_1[_Lstart_3];
_Ldata_1[_Lstart_3] = _Ldata_1[_Lend_4];
_Ldata_1[_Lend_4] = _Ltmp_5;
_Lstart_3++;
_Lend_4--;
continue_1:;
}
break_1:;
_Gstdout_buf_len += _Ldigits_2;
}
}
