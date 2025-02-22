// Generated by Cp1
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#define _NLibC_NExit_Csuccess 0
#define _NLibC_NExit_Cfailure (_NLibC_NExit_Csuccess + 1)
#define _NPosix_NFd_Cnil (-1)
typedef int _NLibC_NExit;
typedef int _NPosix_NFd;
struct _NLibCp1_NStdOut;
struct _NLibCp1_NStdOut {
};
char* _Gstdout_buf_data;
uint32_t _Gstdout_buf_len;
uint32_t _Gstdout_buf_cap;
int main(int _Larg_c_0, char** _Larg_v_1);
void _Pprint_commands_1(char* _Lbin_0);
void _Pvalidate_cp1_path_2(char* _Lbin_0, char* _Lcp1_path_1);
void _NLibCp1_Pstdout_1(struct _NLibCp1_NStdOut* _Lso_0);
void _NLibCp1_NStdOut_Pstdout_cstr_3(struct _NLibCp1_NStdOut* _Lso_0, char* _Lstr_1, uint32_t _Llen_2);
void _Tchar_Pstdout_arr_2(char* _Lstr_0, struct _NLibCp1_NStdOut* _Lso_1);
void _Tchar_Pstdout_2(char _Lval_0, struct _NLibCp1_NStdOut* _Lso_1);
void _NLibCp1_NStdOut_Pstdout_end_1(struct _NLibCp1_NStdOut* _Lso_0);
int _NPosix_NFd_Pclose_1(_NPosix_NFd _Lfile_0);
void _NLibCp1_Pstdout_bytes_2(void* _Ldata_0, size_t _Lsize_1);
void _NLibCp1_Pstdout_cstr_1(char* _Lstr_0);
void _NLibCp1_Pstdout_char_1(char _Lval_0);
void _NLibCp1_Pstdout_flush_0();
void _NLibCp1_Pstdout_reserve_1(uint32_t _Llen_0);
#define _NLibC_Prealloc_arr_2(var, c) var = realloc(var, sizeof(var[0]) * (c))
int main(int _Larg_c_0, char** _Larg_v_1) {
char* _Lbin_7;
char _Lc_path_8[21] = {0};
_NPosix_NFd _Lc_fd_9;
char _Lexe_path_11[21] = {0};
_NPosix_NFd _Lexe_fd_12;
char _Lcommand_14[1024] = {0};
int _Lc_ret_15;
int _Lcompile_ret_16;
int _Lexe_ret_18;
#ifdef _WIN32
if(true) {
char* _Larg_2;
size_t _Llen_3;
_Larg_2 = _Larg_v_1[0];
_Llen_3 = strlen(_Larg_2);
if(((_Larg_2[(_Llen_3 - 4)] == '.') && (_Larg_2[(_Llen_3 - 3)] == 'e') && (_Larg_2[(_Llen_3 - 2)] == 'x') && (_Larg_2[(_Llen_3 - 1)] == 'e'))) {
_Larg_2[(_Llen_3 - 4)] = '\0';
}
}
int32_t _Li_4;
_Li_4 = 0;
for(int i = _Larg_c_0; i > 0; ) {
i --;
char* _Larg_5;
_Larg_5 = _Larg_v_1[_Li_4];
int32_t _Lj_6;
_Lj_6 = 0;
while(1) {
if(_Larg_5[_Lj_6] == '\0') {
goto break_1;
} else if(_Larg_5[_Lj_6] == '\\') {
_Larg_5[_Lj_6] = '/';
}
continue_1:;
_Lj_6++;
}
break_1:;
continue_0:;
_Li_4++;
}
break_0:;
#endif
_Lbin_7 = _Larg_v_1[0];
if(_Larg_c_0 != 2) {
_Pprint_commands_1(_Lbin_7);
exit(_NLibC_NExit_Cfailure);
}
_Pvalidate_cp1_path_2(_Lbin_7, _Larg_v_1[1]);
#ifdef _WIN32
mkdir("cp1-tmp-0");
#else
mkdir("cp1-tmp-0", 0755);
#endif
strcpy(_Lc_path_8, "cp1-tmp-0/c-XXXXXX");
_Lc_fd_9 = mkstemp(_Lc_path_8);
if(_Lc_fd_9 == _NPosix_NFd_Cnil) {
struct _NLibCp1_NStdOut _L_10;
_Pprint_commands_1(_Lbin_7);
_NLibCp1_Pstdout_1(&_L_10);
_NLibCp1_NStdOut_Pstdout_cstr_3(&_L_10, "Error, cannot open file for reading: ", 37u);
_Tchar_Pstdout_arr_2(_Lc_path_8, &_L_10);
_Tchar_Pstdout_2('\n', &_L_10);
_NLibCp1_NStdOut_Pstdout_end_1(&_L_10);
exit(_NLibC_NExit_Cfailure);
}
_NPosix_NFd_Pclose_1(_Lc_fd_9);
unlink(_Lc_path_8);
strcpy(_Lexe_path_11, "cp1-tmp-0/exe-XXXXXX");
_Lexe_fd_12 = mkstemp(_Lexe_path_11);
if(_Lexe_fd_12 == _NPosix_NFd_Cnil) {
struct _NLibCp1_NStdOut _L_13;
_Pprint_commands_1(_Lbin_7);
_NLibCp1_Pstdout_1(&_L_13);
_NLibCp1_NStdOut_Pstdout_cstr_3(&_L_13, "Error, cannot open file for reading: ", 37u);
_Tchar_Pstdout_arr_2(_Lexe_path_11, &_L_13);
_Tchar_Pstdout_2('\n', &_L_13);
_NLibCp1_NStdOut_Pstdout_end_1(&_L_13);
exit(_NLibC_NExit_Cfailure);
}
_NPosix_NFd_Pclose_1(_Lexe_fd_12);
unlink(_Lexe_path_11);
_Lc_path_8[18] = '.';
_Lc_path_8[19] = 'c';
_Lc_path_8[20] = '\0';
sprintf(_Lcommand_14, "%.*s-compile -c %s %s", (int)(strlen(_Lbin_7) - 4), _Lbin_7, _Lc_path_8, _Larg_v_1[1]);
_Lc_ret_15 = system(_Lcommand_14);
if(_Lc_ret_15 != 0) {
unlink(_Lc_path_8);
exit(_NLibC_NExit_Cfailure);
}
sprintf(_Lcommand_14, "tcc -o \"%s\" \"%s\" || clang -o \"%s\" \"%s\" || gcc -o \"%s\" \"%s\"", _Lexe_path_11, _Lc_path_8, _Lexe_path_11, _Lc_path_8, _Lexe_path_11, _Lc_path_8);
_Lcompile_ret_16 = system(_Lcommand_14);
unlink(_Lc_path_8);
if(_Lcompile_ret_16 != 0) {
exit(_NLibC_NExit_Cfailure);
}
#ifdef _WIN32
int32_t _Li_17;
_Li_17 = 0;
while(1) {
if(_Lexe_path_11[_Li_17] == '\0') {
goto break_2;
} else if(_Lexe_path_11[_Li_17] == '/') {
_Lexe_path_11[_Li_17] = '\\';
}
continue_2:;
_Li_17++;
}
break_2:;
#endif
_Lexe_ret_18 = system(_Lexe_path_11);
unlink(_Lexe_path_11);
if(_Lexe_ret_18 != 0) {
exit(_NLibC_NExit_Cfailure);
}
return 0;
}
void _Pprint_commands_1(char* _Lbin_0) {
struct _NLibCp1_NStdOut _L_1;
_NLibCp1_Pstdout_1(&_L_1);
_NLibCp1_NStdOut_Pstdout_cstr_3(&_L_1, "Usage: ", 7u);
_Tchar_Pstdout_arr_2(_Lbin_0, &_L_1);
_NLibCp1_NStdOut_Pstdout_cstr_3(&_L_1, " [file.cp1]\n", 12u);
_NLibCp1_NStdOut_Pstdout_end_1(&_L_1);
}
void _Pvalidate_cp1_path_2(char* _Lbin_0, char* _Lcp1_path_1) {
size_t _Lcp1_path_len_3;
if(_Lcp1_path_1[0] == '/') {
struct _NLibCp1_NStdOut _L_2;
_Pprint_commands_1(_Lbin_0);
_NLibCp1_Pstdout_1(&_L_2);
_NLibCp1_NStdOut_Pstdout_cstr_3(&_L_2, "Error, [cp1 file] (which is '", 29u);
_Tchar_Pstdout_arr_2(_Lcp1_path_1, &_L_2);
_NLibCp1_NStdOut_Pstdout_cstr_3(&_L_2, "') must be a relative filepath (e.g. file.cp1), not an absolute path (/home/user/file.cp1)\n", 91u);
_NLibCp1_NStdOut_Pstdout_end_1(&_L_2);
exit(_NLibC_NExit_Cfailure);
}
_Lcp1_path_len_3 = strlen(_Lcp1_path_1);
if(((_Lcp1_path_1[0] == '.') && (_Lcp1_path_1[1] == '/'))) {
_Lcp1_path_1 = &_Lcp1_path_1[2];
_Lcp1_path_len_3 -= 2;
}
int32_t _Lj_4;
_Lj_4 = 0;
for(int i = _Lcp1_path_len_3; i > 0; ) {
i --;
if(_Lcp1_path_1[_Lj_4] == '\\') {
struct _NLibCp1_NStdOut _L_5;
_Pprint_commands_1(_Lbin_0);
_NLibCp1_Pstdout_1(&_L_5);
_NLibCp1_NStdOut_Pstdout_cstr_3(&_L_5, "Error, [cp1 file] (which is '", 29u);
_Tchar_Pstdout_arr_2(_Lcp1_path_1, &_L_5);
_NLibCp1_NStdOut_Pstdout_cstr_3(&_L_5, "') must not contain backslashes '\\', please use forward slashes '/' instead\n", 76u);
_NLibCp1_NStdOut_Pstdout_end_1(&_L_5);
exit(_NLibC_NExit_Cfailure);
}
continue_0:;
_Lj_4++;
}
break_0:;
int32_t _Lj_6;
_Lj_6 = 0;
for(int i = _Lcp1_path_len_3 - 1; i > 0; ) {
i --;
if(((_Lcp1_path_1[_Lj_6] == '.') && (_Lcp1_path_1[(_Lj_6 + 1)] == '/'))) {
struct _NLibCp1_NStdOut _L_7;
_Pprint_commands_1(_Lbin_0);
_NLibCp1_Pstdout_1(&_L_7);
_NLibCp1_NStdOut_Pstdout_cstr_3(&_L_7, "Error, [cp1 file] (which is '", 29u);
_Tchar_Pstdout_arr_2(_Lcp1_path_1, &_L_7);
_NLibCp1_NStdOut_Pstdout_cstr_3(&_L_7, "') must not contain './'\n", 25u);
_NLibCp1_NStdOut_Pstdout_end_1(&_L_7);
exit(_NLibC_NExit_Cfailure);
}
continue_1:;
_Lj_6++;
}
break_1:;
if(!((_Lcp1_path_len_3 > 4) && (_Lcp1_path_1[(_Lcp1_path_len_3 - 4)] == '.') && (_Lcp1_path_1[(_Lcp1_path_len_3 - 3)] == 'c') && (_Lcp1_path_1[(_Lcp1_path_len_3 - 2)] == 'p') && (_Lcp1_path_1[(_Lcp1_path_len_3 - 1)] == '1'))) {
struct _NLibCp1_NStdOut _L_8;
_Pprint_commands_1(_Lbin_0);
_NLibCp1_Pstdout_1(&_L_8);
_NLibCp1_NStdOut_Pstdout_cstr_3(&_L_8, "Error, [cp1 file] (which is '", 29u);
_Tchar_Pstdout_arr_2(_Lcp1_path_1, &_L_8);
_NLibCp1_NStdOut_Pstdout_cstr_3(&_L_8, "') must be a filename that ends with '.cp1', for example: main.cp1\n", 67u);
_NLibCp1_NStdOut_Pstdout_end_1(&_L_8);
exit(_NLibC_NExit_Cfailure);
}
}
inline void _NLibCp1_Pstdout_1(struct _NLibCp1_NStdOut* _Lso_0) {
}
inline void _NLibCp1_NStdOut_Pstdout_cstr_3(struct _NLibCp1_NStdOut* _Lso_0, char* _Lstr_1, uint32_t _Llen_2) {
_NLibCp1_Pstdout_bytes_2(_Lstr_1, _Llen_2);
}
inline void _Tchar_Pstdout_arr_2(char* _Lstr_0, struct _NLibCp1_NStdOut* _Lso_1) {
_NLibCp1_Pstdout_cstr_1(_Lstr_0);
}
inline void _Tchar_Pstdout_2(char _Lval_0, struct _NLibCp1_NStdOut* _Lso_1) {
_NLibCp1_Pstdout_char_1(_Lval_0);
}
inline void _NLibCp1_NStdOut_Pstdout_end_1(struct _NLibCp1_NStdOut* _Lso_0) {
_NLibCp1_Pstdout_flush_0();
}
inline int _NPosix_NFd_Pclose_1(_NPosix_NFd _Lfile_0) {
return close(_Lfile_0);
}
inline void _NLibCp1_Pstdout_bytes_2(void* _Ldata_0, size_t _Lsize_1) {
_NLibCp1_Pstdout_reserve_1(_Lsize_1);
memcpy(&_Gstdout_buf_data[_Gstdout_buf_len], _Ldata_0, _Lsize_1);
_Gstdout_buf_len += _Lsize_1;
}
inline void _NLibCp1_Pstdout_cstr_1(char* _Lstr_0) {
_NLibCp1_Pstdout_bytes_2(_Lstr_0, strlen(_Lstr_0));
}
inline void _NLibCp1_Pstdout_char_1(char _Lval_0) {
_NLibCp1_Pstdout_reserve_1(1);
_Gstdout_buf_data[_Gstdout_buf_len++] = _Lval_0;
}
inline void _NLibCp1_Pstdout_flush_0() {
write((_NPosix_NFd)(1), _Gstdout_buf_data, _Gstdout_buf_len);
_Gstdout_buf_len = 0;
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
