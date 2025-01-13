#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#define _Nstdc_Nfd_Cnil (-1)
#define _Nstdc_Nexit_Csuccess 0
#define _Nstdc_Nexit_Cfailure (_Nstdc_Nexit_Csuccess + 1)
#define _Ncmd_Cc 0
#define _Ncmd_Crun (_Ncmd_Cc + 1)
typedef int _Nstdc_Nfd;
typedef int _Nstdc_Nopen_flags;
typedef int _Nstdc_Nexit;
typedef uint8_t _Ncmd;
typedef int _Nstdc_Nseek;
char _Ginclude_dir[512];
uint16_t _Ginclude_dir_len;
int32_t _Gcp1_path_c;
char** _Gcp1_path_v;
char** _Gcp1_path_real_v;
int32_t _Gincluded_c;
uint32_t* _Gincluded_len_v;
char** _Gincluded_v;
int32_t _Gincluded_cap;
int32_t _Gcp1_path_cap;
uint32_t* _Gcp1_path_len_v;
uint32_t* _Gcp1_path_real_len_v;
int main(int _Larg_c_0, char** _Larg_v_1);
void _Pprint_commands_1(char* _Lbin_0);
void _Pprint_c_usage_1(char* _Lbin_0);
bool _Pvalidate_cp1_paths_5(int32_t _Lstart_0, int32_t _Larg_c_1, char** _Larg_v_2, char* _Lbin_3, _Ncmd _Lcmd_4);
void _Pprint_command_2(int32_t _Larg_c_0, char** _Larg_v_1);
struct FILE* _Nstdc_Nfd_Pfopen_2(_Nstdc_Nfd _Lfile_0, char* _Lmode_1);
void _Pprint_run_usage_1(char* _Lbin_0);
int _Nstdc_Nfd_Pclose_1(_Nstdc_Nfd _Lfile_0);
void _Pget_compiler_2(char* _Lbin_0, struct FILE* _Lninja_f_1);
void _Pprint_usage_2(char* _Lbin_0, _Ncmd _Lcmd_1);
bool _Pcp1_path_input_4(char* _Lcp1_path_0, int32_t _Lcp1_path_len_1, char* _Lbin_2, _Ncmd _Lcmd_3);
void _Pcp1_path_add_4(char* _Lcp1_path_real_0, int32_t _Lcp1_path_real_len_1, char* _Lcp1_path_2, int32_t _Lcp1_path_len_3);
bool _Nstdc_Nfd_Popen_3(_Nstdc_Nfd* _Lfile_0, char* _Lpath_1, _Nstdc_Nopen_flags _Lflags_2);
int main(int _Larg_c_0, char** _Larg_v_1) {
char* _Lbin_2;
char _Labs_path_3[512];
uint16_t _Labs_path_len_4;
char* _Lslash_10;
char* _Lcmd_11;
_Lbin_2 = _Larg_v_1[0];
_Labs_path_len_4 = 0;
if(_Lbin_2[0] == '/') {
_Labs_path_len_4 = strlen(_Lbin_2);
memcpy(_Labs_path_3, _Lbin_2, _Labs_path_len_4);
_Labs_path_3[_Labs_path_len_4] = '\0';
} else {
bool _Lhas_slash_5;
_Lhas_slash_5 = false;
int32_t _Li_6;
_Li_6 = 0;
while(1) {
if(_Lbin_2[_Li_6] == '\0') {
goto break_0;
}
if(_Lbin_2[_Li_6] == '/') {
_Lhas_slash_5 = true;
goto break_0;
}
continue_0:;
_Li_6++;
}
break_0:;
if(_Lhas_slash_5) {
realpath(_Lbin_2, _Labs_path_3);
} else {
char* _LPATH_7;
char* _Lfound_8;
_Nstdc_Nfd _Lfd_9;
_LPATH_7 = strdup(getenv("PATH"));
_Lfound_8 = strtok(_LPATH_7, ":");
_Lfd_9 = _Nstdc_Nfd_Cnil;
while(_Lfound_8 != NULL) {
sprintf(_Labs_path_3, "%s/%s", _Lfound_8, _Lbin_2);
_Lfd_9 = open(_Labs_path_3, O_RDONLY);
if(_Lfd_9 != _Nstdc_Nfd_Cnil) {
goto break_1;
}
_Lfound_8 = strtok(NULL, ":");
continue_1:;
}
break_1:;
if(_Lfd_9 == _Nstdc_Nfd_Cnil) {
printf("Cannot run %s because we can't detect its absolute path\n", _Lbin_2);
exit(_Nstdc_Nexit_Cfailure);
}
free(_LPATH_7);
}
}
_Lslash_10 = strrchr(_Labs_path_3, '/');
_Lslash_10[0] = '\0';
_Lslash_10 = strrchr(_Labs_path_3, '/');
_Lslash_10[0] = '\0';
sprintf(_Ginclude_dir, "%s/include", _Labs_path_3);
_Ginclude_dir_len = strlen(_Ginclude_dir);
if(_Larg_c_0 < 2) {
_Pprint_commands_1(_Lbin_2);
exit(_Nstdc_Nexit_Cfailure);
}
_Lcmd_11 = _Larg_v_1[1];
if(strcmp(_Lcmd_11, "c") == 0) {
char* _Lc_path_12;
size_t _Lc_path_len_13;
char _Lninja_path_14[24];
_Nstdc_Nfd _Lninja_fd_15;
struct FILE* _Lninja_f_16;
char _Lcommand_19[24 + 9];
int _Lret_20;
if(_Larg_c_0 < 4) {
_Pprint_c_usage_1(_Lbin_2);
exit(_Nstdc_Nexit_Cfailure);
}
_Lc_path_12 = _Larg_v_1[2];
_Lc_path_len_13 = strlen(_Lc_path_12);
if(!(((_Lc_path_len_13 > 2) && (_Lc_path_12[(_Lc_path_len_13 - 2)] == '.') && (_Lc_path_12[(_Lc_path_len_13 - 1)] == 'c')))) {
_Pprint_c_usage_1(_Lbin_2);
printf("Error, [output.c] (which is '%s') must be a filename that ends with '.c', for example: main.c\n", _Lc_path_12);
exit(_Nstdc_Nexit_Cfailure);
}
if(!(_Pvalidate_cp1_paths_5(3, _Larg_c_0, _Larg_v_1, _Lbin_2, _Ncmd_Cc))) {
_Pprint_command_2(_Larg_c_0, _Larg_v_1);
exit(_Nstdc_Nexit_Cfailure);
}
mkdir("cp1-tmp", 32749);
strcpy(_Lninja_path_14, "cp1-tmp/ninja-XXXXXXXXX");
_Lninja_fd_15 = mkstemp(_Lninja_path_14);
if(_Lninja_fd_15 == _Nstdc_Nfd_Cnil) {
_Pprint_c_usage_1(_Lbin_2);
printf("Error, cannot open file for reading: %s\n", _Lninja_path_14);
exit(_Nstdc_Nexit_Cfailure);
}
_Lninja_f_16 = _Nstdc_Nfd_Pfopen_2(_Lninja_fd_15, "w");
fprintf(_Lninja_f_16, "rule parser\n");
fprintf(_Lninja_f_16, " command = %s-parser $in $out\n", _Lbin_2);
fprintf(_Lninja_f_16, "rule compiler\n");
fprintf(_Lninja_f_16, " command = %s-compiler $in $out\n", _Lbin_2);
int32_t _Li_17;
_Li_17 = 0;
for(int i = _Gcp1_path_c; i > 0; ) {
i --;
fprintf(_Lninja_f_16, "build cp1-tmp/%s-b: parser %s\n", _Gcp1_path_v[_Li_17], _Gcp1_path_real_v[_Li_17]);
continue_2:;
_Li_17++;
}
break_2:;
fprintf(_Lninja_f_16, "build %s: compiler", _Lc_path_12);
int32_t _Li_18;
_Li_18 = 0;
for(int i = _Gcp1_path_c; i > 0; ) {
i --;
fprintf(_Lninja_f_16, " cp1-tmp/%s-b", _Gcp1_path_v[_Li_18]);
continue_3:;
_Li_18++;
}
break_3:;
fprintf(_Lninja_f_16, "\n");
fclose(_Lninja_f_16);
sprintf(_Lcommand_19, "ninja -f %s", _Lninja_path_14);
_Lret_20 = system(_Lcommand_19);
unlink(_Lninja_path_14);
if(_Lret_20 != 0) {
exit(_Nstdc_Nexit_Cfailure);
}
} else if(strcmp(_Lcmd_11, "run") == 0) {
char _Lc_path_21[22];
_Nstdc_Nfd _Lc_fd_22;
char _Lexe_path_23[24];
_Nstdc_Nfd _Lexe_fd_24;
char _Lninja_path_25[24];
_Nstdc_Nfd _Lninja_fd_26;
struct FILE* _Lninja_f_27;
char _Lcommand_30[24 + 9];
int _Lninja_ret_31;
int _Lexe_ret_32;
if(_Larg_c_0 < 3) {
_Pprint_run_usage_1(_Lbin_2);
exit(_Nstdc_Nexit_Cfailure);
}
if(!(_Pvalidate_cp1_paths_5(2, _Larg_c_0, _Larg_v_1, _Lbin_2, _Ncmd_Crun))) {
_Pprint_command_2(_Larg_c_0, _Larg_v_1);
exit(_Nstdc_Nexit_Cfailure);
}
mkdir("cp1-tmp", 32749);
strcpy(_Lc_path_21, "cp1-tmp/c-XXXXXXXXX");
_Lc_fd_22 = mkstemp(_Lc_path_21);
if(_Lc_fd_22 == _Nstdc_Nfd_Cnil) {
_Pprint_run_usage_1(_Lbin_2);
printf("Error, cannot open file for reading: %s\n", _Lc_path_21);
exit(_Nstdc_Nexit_Cfailure);
}
_Nstdc_Nfd_Pclose_1(_Lc_fd_22);
unlink(_Lc_path_21);
strcpy(_Lexe_path_23, "cp1-tmp/exe-XXXXXXXXX");
_Lexe_fd_24 = mkstemp(_Lexe_path_23);
if(_Lexe_fd_24 == _Nstdc_Nfd_Cnil) {
_Pprint_run_usage_1(_Lbin_2);
printf("Error, cannot open file for reading: %s\n", _Lexe_path_23);
exit(_Nstdc_Nexit_Cfailure);
}
_Nstdc_Nfd_Pclose_1(_Lexe_fd_24);
unlink(_Lexe_path_23);
_Lc_path_21[19] = '.';
_Lc_path_21[20] = 'c';
_Lc_path_21[21] = '\0';
strcpy(_Lninja_path_25, "cp1-tmp/ninja-XXXXXXXXX");
_Lninja_fd_26 = mkstemp(_Lninja_path_25);
if(_Lninja_fd_26 == _Nstdc_Nfd_Cnil) {
_Pprint_run_usage_1(_Lbin_2);
printf("Error, cannot open file for reading: %s\n", _Lninja_path_25);
exit(_Nstdc_Nexit_Cfailure);
}
_Lninja_f_27 = _Nstdc_Nfd_Pfopen_2(_Lninja_fd_26, "w");
fprintf(_Lninja_f_27, "rule parser\n");
fprintf(_Lninja_f_27, " command = %s-parser $in $out\n", _Lbin_2);
fprintf(_Lninja_f_27, "rule compiler\n");
fprintf(_Lninja_f_27, " command = %s-compiler $in $out\n", _Lbin_2);
_Pget_compiler_2(_Lbin_2, _Lninja_f_27);
int32_t _Li_28;
_Li_28 = 0;
for(int i = _Gcp1_path_c; i > 0; ) {
i --;
fprintf(_Lninja_f_27, "build cp1-tmp/%s-b: parser %s\n", _Gcp1_path_v[_Li_28], _Gcp1_path_real_v[_Li_28]);
continue_4:;
_Li_28++;
}
break_4:;
fprintf(_Lninja_f_27, "build %s: compiler", _Lc_path_21);
int32_t _Li_29;
_Li_29 = 0;
for(int i = _Gcp1_path_c; i > 0; ) {
i --;
fprintf(_Lninja_f_27, " cp1-tmp/%s-b", _Gcp1_path_v[_Li_29]);
continue_5:;
_Li_29++;
}
break_5:;
fprintf(_Lninja_f_27, "\n");
fprintf(_Lninja_f_27, "build %s: c %s\n", _Lexe_path_23, _Lc_path_21);
fclose(_Lninja_f_27);
sprintf(_Lcommand_30, "ninja -f %s", _Lninja_path_25);
_Lninja_ret_31 = system(_Lcommand_30);
unlink(_Lninja_path_25);
unlink(_Lc_path_21);
if(_Lninja_ret_31 != 0) {
exit(_Nstdc_Nexit_Cfailure);
}
_Lexe_ret_32 = system(_Lexe_path_23);
unlink(_Lexe_path_23);
if(_Lexe_ret_32 != 0) {
exit(_Nstdc_Nexit_Cfailure);
}
} else {
_Pprint_commands_1(_Lbin_2);
exit(_Nstdc_Nexit_Cfailure);
}
return 0;
}
void _Pprint_commands_1(char* _Lbin_0) {
printf("Usage: %s [command] [options]\n", _Lbin_0);
printf("Commands:\n");
printf("  c     Build a C file.\n");
printf("  run      Compile and run the cp1 codes.\n");
}
void _Pprint_c_usage_1(char* _Lbin_0) {
printf("Usage: %s c [output.c] [cp1 file/s...]\n", _Lbin_0);
}
bool _Pvalidate_cp1_paths_5(int32_t _Lstart_0, int32_t _Larg_c_1, char** _Larg_v_2, char* _Lbin_3, _Ncmd _Lcmd_4) {
int32_t _Li_5;
_Li_5 = _Lstart_0;
for(int i = _Larg_c_1 - _Lstart_0; i > 0; ) {
i --;
char* _Lcp1_path_6;
size_t _Lcp1_path_len_7;
_Lcp1_path_6 = _Larg_v_2[_Li_5];
if(_Lcp1_path_6[0] == '/') {
_Pprint_usage_2(_Lbin_3, _Lcmd_4);
printf("Error, [cp1 file] (which is '%s') must be a relative filepath (e.g. file.cp1), not an absolute path (/home/user/file.cp1)\n", _Lcp1_path_6);
exit(_Nstdc_Nexit_Cfailure);
}
_Lcp1_path_len_7 = strlen(_Lcp1_path_6);
if(((_Lcp1_path_6[0] == '.') && (_Lcp1_path_6[1] == '/'))) {
_Lcp1_path_6 = &_Lcp1_path_6[2];
_Lcp1_path_len_7 -= 2;
}
int32_t _Lj_8;
_Lj_8 = 0;
for(int i = _Lcp1_path_len_7; i > 0; ) {
i --;
if(_Lcp1_path_6[_Lj_8] == '\\') {
_Pprint_usage_2(_Lbin_3, _Lcmd_4);
printf("Error, [cp1 file] (which is '%s') must not contain backslashes '\\', please use forward slashes '/' instead\n", _Lcp1_path_6);
exit(_Nstdc_Nexit_Cfailure);
}
continue_1:;
_Lj_8++;
}
break_1:;
int32_t _Lj_9;
_Lj_9 = 0;
for(int i = _Lcp1_path_len_7 - 1; i > 0; ) {
i --;
if(((_Lcp1_path_6[_Lj_9] == '.') && (_Lcp1_path_6[(_Lj_9 + 1)] == '/'))) {
_Pprint_usage_2(_Lbin_3, _Lcmd_4);
printf("Error, [cp1 file] (which is '%s') must not contain './'\n", _Lcp1_path_6);
exit(_Nstdc_Nexit_Cfailure);
}
continue_2:;
_Lj_9++;
}
break_2:;
if(!(((_Lcp1_path_len_7 > 4) && (_Lcp1_path_6[(_Lcp1_path_len_7 - 4)] == '.') && (_Lcp1_path_6[(_Lcp1_path_len_7 - 3)] == 'c') && (_Lcp1_path_6[(_Lcp1_path_len_7 - 2)] == 'p') && (_Lcp1_path_6[(_Lcp1_path_len_7 - 1)] == '1')))) {
_Pprint_usage_2(_Lbin_3, _Lcmd_4);
printf("Error, [cp1 file] (which is '%s') must be a filename that ends with '.cp1', for example: main.cp1\n", _Lcp1_path_6);
exit(_Nstdc_Nexit_Cfailure);
}
if(!(_Pcp1_path_input_4(_Lcp1_path_6, _Lcp1_path_len_7, _Lbin_3, _Lcmd_4))) {
_Pprint_usage_2(_Lbin_3, _Lcmd_4);
return false;
}
continue_0:;
_Li_5++;
}
break_0:;
return true;
}
void _Pprint_command_2(int32_t _Larg_c_0, char** _Larg_v_1) {
printf("Command was:");
int32_t _Li_2;
_Li_2 = 0;
for(int i = _Larg_c_0; i > 0; ) {
i --;
printf(" %s", _Larg_v_1[_Li_2]);
continue_0:;
_Li_2++;
}
break_0:;
printf("\n");
}
inline struct FILE* _Nstdc_Nfd_Pfopen_2(_Nstdc_Nfd _Lfile_0, char* _Lmode_1) {
return fdopen(_Lfile_0, _Lmode_1);
}
void _Pprint_run_usage_1(char* _Lbin_0) {
printf("Usage: %s run [cp1 file/s...]\n", _Lbin_0);
}
inline int _Nstdc_Nfd_Pclose_1(_Nstdc_Nfd _Lfile_0) {
return close(_Lfile_0);
}
void _Pget_compiler_2(char* _Lbin_0, struct FILE* _Lninja_f_1) {
char* _LPATH_2;
char* _Lfound_3;
_LPATH_2 = strdup(getenv("PATH"));
_Lfound_3 = strtok(_LPATH_2, ":");
while(_Lfound_3 != NULL) {
_Nstdc_Nfd _Lfd_4;
char _Lcompiler_5[512];
sprintf(_Lcompiler_5, "%s/tcc", _Lfound_3);
_Lfd_4 = open(_Lcompiler_5, O_RDONLY);
if(_Lfd_4 != _Nstdc_Nfd_Cnil) {
fprintf(_Lninja_f_1, "rule c\n");
fprintf(_Lninja_f_1, " command = tcc $in -o $out\n");
_Nstdc_Nfd_Pclose_1(_Lfd_4);
free(_LPATH_2);
return;
}
sprintf(_Lcompiler_5, "%s/clang", _Lfound_3);
_Lfd_4 = open(_Lcompiler_5, O_RDONLY);
if(_Lfd_4 != _Nstdc_Nfd_Cnil) {
fprintf(_Lninja_f_1, "rule c\n");
fprintf(_Lninja_f_1, " command = clang $in -o $out\n");
_Nstdc_Nfd_Pclose_1(_Lfd_4);
free(_LPATH_2);
return;
}
sprintf(_Lcompiler_5, "%s/gcc", _Lfound_3);
_Lfd_4 = open(_Lcompiler_5, O_RDONLY);
if(_Lfd_4 != _Nstdc_Nfd_Cnil) {
fprintf(_Lninja_f_1, "rule c\n");
fprintf(_Lninja_f_1, " command = gcc $in -o $out\n");
_Nstdc_Nfd_Pclose_1(_Lfd_4);
free(_LPATH_2);
return;
}
_Lfound_3 = strtok(NULL, ":");
continue_0:;
}
break_0:;
printf("Cannot execute '%s run' because the required compiler was not found: tcc clang or gcc\n", _Lbin_0);
exit(_Nstdc_Nexit_Cfailure);
}
void _Pprint_usage_2(char* _Lbin_0, _Ncmd _Lcmd_1) {
switch(_Lcmd_1) {
case _Ncmd_Cc:;
_Pprint_c_usage_1(_Lbin_0);
break;
case _Ncmd_Crun:;
_Pprint_run_usage_1(_Lbin_0);
break;
}
}
bool _Pcp1_path_input_4(char* _Lcp1_path_0, int32_t _Lcp1_path_len_1, char* _Lbin_2, _Ncmd _Lcmd_3) {
_Nstdc_Nfd _Lfd_5;
size_t _Llen_6;
char* _Ldata_7;
int32_t _Lpos_8;
int32_t _Lline_9;
int32_t _Li_4;
_Li_4 = 0;
for(int i = _Gcp1_path_c; i > 0; ) {
i --;
if(memcmp(_Gcp1_path_v[_Li_4], _Lcp1_path_0, _Lcp1_path_len_1) == 0) {
return true;
}
continue_0:;
_Li_4++;
}
break_0:;
_Pcp1_path_add_4(_Lcp1_path_0, _Lcp1_path_len_1, _Lcp1_path_0, _Lcp1_path_len_1);
if(!(_Nstdc_Nfd_Popen_3(&_Lfd_5, _Lcp1_path_0, O_RDONLY))) {
printf("Error, [cp1 file] (which is '%s') cannot be opened for reading\n", _Lcp1_path_0);
return false;
}
_Llen_6 = lseek(_Lfd_5, 0, SEEK_END);
lseek(_Lfd_5, 0, SEEK_SET);
_Ldata_7 = malloc(_Llen_6 + 1);
read(_Lfd_5, _Ldata_7, _Llen_6);
_Nstdc_Nfd_Pclose_1(_Lfd_5);
_Ldata_7[_Llen_6] = '\0';
if(!(((_Llen_6 > 0) && (_Ldata_7[(_Llen_6 - 1)] == '\n')))) {
printf("Error, [cp1 file] (which is '%s') must end a new line\n", _Lcp1_path_0);
return false;
}
if(_Ldata_7[(_Llen_6 - 2)] == '\r') {
printf("Error, [cp1 file] (which is '%s') must have Unix line endings '\\n' instead of Windows line endings '\\r\\n'\n", _Lcp1_path_0);
return false;
}
_Lpos_8 = 0;
_Lline_9 = 0;
while(_Ldata_7[_Lpos_8] == '#') {
int32_t _Lstart_10;
_Lline_9++;
_Lstart_10 = _Lpos_8;
while(1) {
_Lpos_8++;
if(_Ldata_7[_Lpos_8] == '\n') {
if(memcmp("#import \"", &_Ldata_7[_Lstart_10], 9) == 0) {
int32_t _Lend_11;
char* _Limport_13;
int32_t _Limport_path_len_14;
char* _Limport_path_17;
_Lstart_10 += 9;
_Lend_11 = -1;
int32_t _Lj_12;
_Lj_12 = _Lstart_10;
for(int i = _Lpos_8 - _Lstart_10; i > 0; ) {
i --;
if(_Ldata_7[_Lj_12] == '\"') {
_Lend_11 = _Lj_12;
goto break_3;
}
continue_3:;
_Lj_12++;
}
break_3:;
if(_Lend_11 == -1) {
printf("%s:%u: #import \"...\" must end with '\"'\n", _Lcp1_path_0, _Lline_9);
return false;
}
_Limport_13 = &_Ldata_7[_Lstart_10];
_Limport_path_len_14 = (_Lend_11 - _Lstart_10);
if(((_Limport_path_len_14 >= 4) && (_Limport_13[(_Limport_path_len_14 - 4)] == '.') && (_Limport_13[(_Limport_path_len_14 - 3)] == 'c') && (_Limport_13[(_Limport_path_len_14 - 2)] == 'g') && (_Limport_13[(_Limport_path_len_14 - 1)] == 'l'))) {
printf("%s:%u: #import \"%.*s\" doesn't need a '.cp1' suffix\n", _Lcp1_path_0, _Lline_9, _Limport_path_len_14, _Limport_13);
return false;
}
if(_Limport_13[0] == '/') {
printf("%s:%u: #import \"%.*s\" must be a relative path, '/' was detected at the beginning of file path\n", _Lcp1_path_0, _Lline_9, _Limport_path_len_14, _Limport_13);
return false;
}
int32_t _Lj_15;
_Lj_15 = 0;
for(int i = _Limport_path_len_14; i > 0; ) {
i --;
if(_Limport_13[_Lj_15] == '\\') {
printf("%s:%u: #import \"%.*s\" must not contain backslashes '\\', please use forward slashes '/' instead\n", _Lcp1_path_0, _Lline_9, _Limport_path_len_14, _Limport_13);
return false;
}
continue_4:;
_Lj_15++;
}
break_4:;
int32_t _Lj_16;
_Lj_16 = 0;
for(int i = _Limport_path_len_14 - 1; i > 0; ) {
i --;
if(((_Limport_13[_Lj_16] == '.') && (_Limport_13[(_Lj_16 + 1)] == '/'))) {
printf("%s:%u: #import \"%.*s\" must not contain './'\n", _Lcp1_path_0, _Lline_9, _Limport_path_len_14, _Limport_13);
return false;
}
continue_5:;
_Lj_16++;
}
break_5:;
_Limport_path_17 = malloc(_Limport_path_len_14 + 5);
memcpy(_Limport_path_17, _Limport_13, _Limport_path_len_14);
_Limport_path_17[_Limport_path_len_14++] = '.';
_Limport_path_17[_Limport_path_len_14++] = 'c';
_Limport_path_17[_Limport_path_len_14++] = 'g';
_Limport_path_17[_Limport_path_len_14++] = 'l';
_Limport_path_17[_Limport_path_len_14] = '\0';
if(!(_Pcp1_path_input_4(_Limport_path_17, _Limport_path_len_14, _Lbin_2, _Lcmd_3))) {
printf("Error from #import \"%.*s\" at file '%s' line %u\n", _Limport_path_len_14 - 4, _Limport_13, _Lcp1_path_0, _Lline_9);
return false;
}
} else if(memcmp("#include <", &_Ldata_7[_Lstart_10], 10) == 0) {
int32_t _Lend_18;
char* _Linclude_path_20;
int32_t _Linclude_path_len_21;
bool _Lfound_22;
_Lstart_10 += 10;
_Lend_18 = -1;
int32_t _Lj_19;
_Lj_19 = _Lstart_10;
for(int i = _Lpos_8 - _Lstart_10; i > 0; ) {
i --;
if(_Ldata_7[_Lj_19] == '>') {
_Lend_18 = _Lj_19;
goto break_6;
}
continue_6:;
_Lj_19++;
}
break_6:;
if(_Lend_18 == -1) {
printf("%s:%u: #include <...> must end with '>'\n", _Lcp1_path_0, _Lline_9);
return false;
}
_Linclude_path_20 = &_Ldata_7[_Lstart_10];
_Linclude_path_len_21 = (_Lend_18 - _Lstart_10);
_Lfound_22 = false;
int32_t _Lj_23;
_Lj_23 = 0;
for(int i = _Gincluded_c; i > 0; ) {
i --;
if(((_Linclude_path_len_21 == _Gincluded_len_v[_Lj_23]) && (memcmp(_Gincluded_v[_Lj_23], _Linclude_path_20, _Linclude_path_len_21) == 0))) {
_Lfound_22 = true;
goto break_7;
}
continue_7:;
_Lj_23++;
}
break_7:;
if(!(_Lfound_22)) {
int32_t _Li_24;
char* _Lpath_25;
char _Lspec_path_26[128];
_Nstdc_Nfd _Lspec_fd_28;
size_t _Lspec_len_29;
char* _Lspec_data_30;
int32_t _Lspec_pos_31;
int32_t _Lspec_line_32;
_Li_24 = _Gincluded_c++;
if(_Gincluded_cap < _Gincluded_c) {
_Gincluded_cap = ((_Gincluded_c << 1) + 8);
_Gincluded_v = realloc(_Gincluded_v, _Gincluded_cap * sizeof(size_t));
_Gincluded_len_v = realloc(_Gincluded_len_v, _Gincluded_cap * sizeof(uint32_t));
}
_Lpath_25 = malloc(_Linclude_path_len_21 + 1);
memcpy(_Lpath_25, _Linclude_path_20, _Linclude_path_len_21);
_Lpath_25[_Linclude_path_len_21] = '\0';
_Gincluded_v[_Li_24] = _Lpath_25;
_Gincluded_len_v[_Li_24] = _Linclude_path_len_21;
sprintf(_Lspec_path_26, "%s/%s", _Ginclude_dir, _Lpath_25);
uint16_t _Li_27;
_Li_27 = (_Ginclude_dir_len + 1);
for(int i = strlen(_Lspec_path_26) - (_Ginclude_dir_len + 1); i > 0; ) {
i --;
if(_Lspec_path_26[_Li_27] == '/') {
_Lspec_path_26[_Li_27] = '-';
}
continue_8:;
_Li_27++;
}
break_8:;
if(!(_Nstdc_Nfd_Popen_3(&_Lspec_fd_28, _Lspec_path_26, O_RDONLY))) {
printf("%s:%u: #include <%s> failed because '%s' does not exists\n", _Lcp1_path_0, _Lline_9, _Lpath_25, _Lspec_path_26);
return false;
}
_Lspec_len_29 = lseek(_Lspec_fd_28, 0, SEEK_END);
lseek(_Lspec_fd_28, 0, SEEK_SET);
_Lspec_data_30 = malloc(_Lspec_len_29 + 1);
read(_Lspec_fd_28, _Lspec_data_30, _Lspec_len_29);
_Lspec_pos_31 = 0;
_Lspec_line_32 = 0;
while(_Lspec_pos_31 < _Lspec_len_29) {
int32_t _Lstart_33;
_Lspec_line_32++;
_Lstart_33 = _Lspec_pos_31;
while(1) {
if(_Lspec_data_30[_Lspec_pos_31] == '\n') {
if(_Lspec_data_30[_Lstart_33] == '<') {
int32_t _Lrangle_34;
_Lstart_33++;
_Lrangle_34 = -1;
int32_t _Lj_35;
_Lj_35 = _Lstart_33;
for(int i = _Lspec_pos_31 - _Lstart_33; i > 0; ) {
i --;
if(_Lspec_data_30[_Lj_35] == '>') {
_Lrangle_34 = _Lj_35;
goto break_11;
}
continue_11:;
_Lj_35++;
}
break_11:;
if(_Lrangle_34 != -1) {
char* _Lfile_path_36;
int32_t _Lfile_path_len_37;
char* _Lfile_path_dup_38;
char* _Lreal_path_39;
size_t _Lreal_path_len_40;
_Lfile_path_36 = &_Lspec_data_30[_Lstart_33];
_Lfile_path_len_37 = (_Lrangle_34 - _Lstart_33);
_Lfile_path_dup_38 = malloc(_Lfile_path_len_37 + 1);
memcpy(_Lfile_path_dup_38, _Lfile_path_36, _Lfile_path_len_37);
_Lfile_path_dup_38[_Lfile_path_len_37] = '\0';
_Lreal_path_39 = malloc(_Ginclude_dir_len + 1 + _Lfile_path_len_37 + 1);
sprintf(_Lreal_path_39, "%s/%.*s", _Ginclude_dir, _Lfile_path_len_37, _Lfile_path_36);
_Lreal_path_len_40 = strlen(_Lreal_path_39);
_Pcp1_path_add_4(_Lreal_path_39, _Lreal_path_len_40, _Lfile_path_dup_38, _Lfile_path_len_37);
}
}
_Lspec_pos_31++;
goto break_10;
}
_Lspec_pos_31++;
continue_10:;
}
break_10:;
continue_9:;
}
break_9:;
free(_Lspec_data_30);
}
}
_Lpos_8++;
goto break_2;
}
continue_2:;
}
break_2:;
continue_1:;
}
break_1:;
free(_Ldata_7);
return true;
}
void _Pcp1_path_add_4(char* _Lcp1_path_real_0, int32_t _Lcp1_path_real_len_1, char* _Lcp1_path_2, int32_t _Lcp1_path_len_3) {
int32_t _Li_4;
_Li_4 = _Gcp1_path_c++;
if(_Gcp1_path_cap < _Gcp1_path_c) {
_Gcp1_path_cap = ((_Gcp1_path_cap << 1) + 8);
_Gcp1_path_v = realloc(_Gcp1_path_v, _Gcp1_path_cap * sizeof(size_t));
_Gcp1_path_len_v = realloc(_Gcp1_path_len_v, _Gcp1_path_cap * sizeof(uint32_t));
_Gcp1_path_real_v = realloc(_Gcp1_path_real_v, _Gcp1_path_cap * sizeof(size_t));
_Gcp1_path_real_len_v = realloc(_Gcp1_path_real_len_v, _Gcp1_path_cap * sizeof(uint32_t));
}
_Gcp1_path_v[_Li_4] = _Lcp1_path_2;
_Gcp1_path_len_v[_Li_4] = _Lcp1_path_len_3;
_Gcp1_path_real_v[_Li_4] = _Lcp1_path_real_0;
_Gcp1_path_real_len_v[_Li_4] = _Lcp1_path_real_len_1;
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
