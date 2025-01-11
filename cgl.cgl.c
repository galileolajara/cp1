#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#define _Nstdc_Nexit_Csuccess 0
#define _Nstdc_Nexit_Cfailure (_Nstdc_Nexit_Csuccess + 1)
#define _Nstdc_Nfd_Cnil (-1)
typedef int32_t _Nstdc_Nexit;
typedef int32_t _Nstdc_Nfd;
typedef int32_t _Nstdc_Nopen_flags;
int32_t main(int32_t _Larg_c_0, char** _Larg_v_1);
void _Pprint_commands_1(char* _Lbin_0);
void _Pprint_to_c_usage_1(char* _Lbin_0);
FILE* _Nstdc_Nfd_Pfopen_2(_Nstdc_Nfd _Lfile_0, char* _Lmode_1);
int32_t _Nstdc_Nfile_Pclose_1(FILE* _Lf_0);
void _Pprint_run_usage_1(char* _Lbin_0);
int32_t _Nstdc_Nfd_Pclose_1(_Nstdc_Nfd _Lfile_0);
void _Pget_compiler_2(char* _Lbin_0, FILE* _Lninja_f_1);
int32_t main(int32_t _Larg_c_0, char** _Larg_v_1) {
char* _Lbin_2;
char* _Lcmd_3;
_Lbin_2 = _Larg_v_1[0];
if(_Larg_c_0 < 2) {
_Pprint_commands_1(_Lbin_2);
exit(_Nstdc_Nexit_Cfailure);
}
_Lcmd_3 = _Larg_v_1[1];
if(strcmp(_Lcmd_3, "to-c") == 0) {
char* _Lc_path_4;
size_t _Lc_path_len_5;
char _Lninja_path_9[24];
_Nstdc_Nfd _Lninja_fd_10;
FILE* _Lninja_f_11;
char _Lcommand_16[24 + 9];
int32_t _Lret_17;
if(_Larg_c_0 < 4) {
_Pprint_to_c_usage_1(_Lbin_2);
exit(_Nstdc_Nexit_Cfailure);
}
_Lc_path_4 = _Larg_v_1[2];
_Lc_path_len_5 = strlen(_Lc_path_4);
if(!(((_Lc_path_len_5 > 2) && (_Lc_path_4[(_Lc_path_len_5 - 2)] == '.') && (_Lc_path_4[(_Lc_path_len_5 - 1)] == 'c')))) {
_Pprint_to_c_usage_1(_Lbin_2);
fprintf(stdout, "Error, [output.c] (which is '%s') must be a filename that ends with '.c', for example: main.c\n", _Lc_path_4);
exit(_Nstdc_Nexit_Cfailure);
}
int32_t _Li_6;
_Li_6 = 3;
for(int i = _Larg_c_0 - 3; i > 0; ) {
i --;
char* _Lcgl_path_7;
size_t _Lcgl_path_len_8;
_Lcgl_path_7 = _Larg_v_1[_Li_6];
_Lcgl_path_len_8 = strlen(_Lcgl_path_7);
if(!(((_Lcgl_path_len_8 > 4) && (_Lcgl_path_7[(_Lcgl_path_len_8 - 4)] == '.') && (_Lcgl_path_7[(_Lcgl_path_len_8 - 3)] == 'c') && (_Lcgl_path_7[(_Lcgl_path_len_8 - 2)] == 'g') && (_Lcgl_path_7[(_Lcgl_path_len_8 - 1)] == 'l')))) {
_Pprint_to_c_usage_1(_Lbin_2);
fprintf(stdout, "Error, [cgl file] (which is '%s') must be a filename that ends with '.cgl', for example: main.cgl\n", _Lcgl_path_7);
exit(_Nstdc_Nexit_Cfailure);
}
continue_0:;
_Li_6++;
}
break_0:;
mkdir("cgl-tmp", 32749);
strcpy(_Lninja_path_9, "cgl-tmp/ninja-XXXXXXXXX");
_Lninja_fd_10 = mkstemp(_Lninja_path_9);
if(_Lninja_fd_10 == _Nstdc_Nfd_Cnil) {
_Pprint_to_c_usage_1(_Lbin_2);
fprintf(stdout, "Error, cannot open file for reading: %s\n", _Lninja_path_9);
exit(_Nstdc_Nexit_Cfailure);
}
_Lninja_f_11 = _Nstdc_Nfd_Pfopen_2(_Lninja_fd_10, "w");
fprintf(_Lninja_f_11, "rule parser\n");
fprintf(_Lninja_f_11, " command = %s-parser $in\n", _Lbin_2);
fprintf(_Lninja_f_11, "rule compiler\n");
fprintf(_Lninja_f_11, " command = %s-compiler $in $out\n", _Lbin_2);
int32_t _Li_12;
_Li_12 = 3;
for(int i = _Larg_c_0 - 3; i > 0; ) {
i --;
char* _Lcgl_path_13;
_Lcgl_path_13 = _Larg_v_1[_Li_12];
fprintf(_Lninja_f_11, "build cgl-tmp/%s-b: parser %s\n", _Lcgl_path_13, _Lcgl_path_13);
continue_1:;
_Li_12++;
}
break_1:;
fprintf(_Lninja_f_11, "build %s: compiler", _Lc_path_4);
int32_t _Li_14;
_Li_14 = 3;
for(int i = _Larg_c_0 - 3; i > 0; ) {
i --;
char* _Lcgl_path_15;
_Lcgl_path_15 = _Larg_v_1[_Li_14];
fprintf(_Lninja_f_11, " cgl-tmp/%s-b", _Lcgl_path_15);
continue_2:;
_Li_14++;
}
break_2:;
fprintf(_Lninja_f_11, "\n");
_Nstdc_Nfile_Pclose_1(_Lninja_f_11);
sprintf(_Lcommand_16, "ninja -f %s", _Lninja_path_9);
_Lret_17 = system(_Lcommand_16);
unlink(_Lninja_path_9);
if(_Lret_17 != 0) {
exit(_Nstdc_Nexit_Cfailure);
}
} else if(strcmp(_Lcmd_3, "run") == 0) {
char _Lc_path_21[22];
_Nstdc_Nfd _Lc_fd_22;
char _Lexe_path_23[24];
_Nstdc_Nfd _Lexe_fd_24;
char _Lninja_path_25[24];
_Nstdc_Nfd _Lninja_fd_26;
FILE* _Lninja_f_27;
char _Lcommand_32[24 + 9];
int32_t _Lninja_ret_33;
int32_t _Lexe_ret_34;
if(_Larg_c_0 < 3) {
_Pprint_run_usage_1(_Lbin_2);
exit(_Nstdc_Nexit_Cfailure);
}
int32_t _Li_18;
_Li_18 = 2;
for(int i = _Larg_c_0 - 2; i > 0; ) {
i --;
char* _Lcgl_path_19;
size_t _Lcgl_path_len_20;
_Lcgl_path_19 = _Larg_v_1[_Li_18];
_Lcgl_path_len_20 = strlen(_Lcgl_path_19);
if(!(((_Lcgl_path_len_20 > 4) && (_Lcgl_path_19[(_Lcgl_path_len_20 - 4)] == '.') && (_Lcgl_path_19[(_Lcgl_path_len_20 - 3)] == 'c') && (_Lcgl_path_19[(_Lcgl_path_len_20 - 2)] == 'g') && (_Lcgl_path_19[(_Lcgl_path_len_20 - 1)] == 'l')))) {
_Pprint_run_usage_1(_Lbin_2);
fprintf(stdout, "Error, [cgl file] (which is '%s') must be a filename that ends with '.cgl', for example: main.cgl\n", _Lcgl_path_19);
exit(_Nstdc_Nexit_Cfailure);
}
continue_3:;
_Li_18++;
}
break_3:;
mkdir("cgl-tmp", 32749);
strcpy(_Lc_path_21, "cgl-tmp/c-XXXXXXXXX");
_Lc_fd_22 = mkstemp(_Lc_path_21);
if(_Lc_fd_22 == _Nstdc_Nfd_Cnil) {
_Pprint_run_usage_1(_Lbin_2);
fprintf(stdout, "Error, cannot open file for reading: %s\n", _Lc_path_21);
exit(_Nstdc_Nexit_Cfailure);
}
_Nstdc_Nfd_Pclose_1(_Lc_fd_22);
unlink(_Lc_path_21);
strcpy(_Lexe_path_23, "cgl-tmp/exe-XXXXXXXXX");
_Lexe_fd_24 = mkstemp(_Lexe_path_23);
if(_Lexe_fd_24 == _Nstdc_Nfd_Cnil) {
_Pprint_run_usage_1(_Lbin_2);
fprintf(stdout, "Error, cannot open file for reading: %s\n", _Lexe_path_23);
exit(_Nstdc_Nexit_Cfailure);
}
_Nstdc_Nfd_Pclose_1(_Lexe_fd_24);
unlink(_Lexe_path_23);
_Lc_path_21[19] = '.';
_Lc_path_21[20] = 'c';
_Lc_path_21[21] = '\0';
strcpy(_Lninja_path_25, "cgl-tmp/ninja-XXXXXXXXX");
_Lninja_fd_26 = mkstemp(_Lninja_path_25);
if(_Lninja_fd_26 == _Nstdc_Nfd_Cnil) {
_Pprint_run_usage_1(_Lbin_2);
fprintf(stdout, "Error, cannot open file for reading: %s\n", _Lninja_path_25);
exit(_Nstdc_Nexit_Cfailure);
}
_Lninja_f_27 = _Nstdc_Nfd_Pfopen_2(_Lninja_fd_26, "w");
fprintf(_Lninja_f_27, "rule parser\n");
fprintf(_Lninja_f_27, " command = %s-parser $in\n", _Lbin_2);
fprintf(_Lninja_f_27, "rule compiler\n");
fprintf(_Lninja_f_27, " command = %s-compiler $in $out\n", _Lbin_2);
_Pget_compiler_2(_Lbin_2, _Lninja_f_27);
int32_t _Li_28;
_Li_28 = 2;
for(int i = _Larg_c_0 - 2; i > 0; ) {
i --;
char* _Lcgl_path_29;
_Lcgl_path_29 = _Larg_v_1[_Li_28];
fprintf(_Lninja_f_27, "build cgl-tmp/%s-b: parser %s\n", _Lcgl_path_29, _Lcgl_path_29);
continue_4:;
_Li_28++;
}
break_4:;
fprintf(_Lninja_f_27, "build %s: compiler", _Lc_path_21);
int32_t _Li_30;
_Li_30 = 2;
for(int i = _Larg_c_0 - 2; i > 0; ) {
i --;
char* _Lcgl_path_31;
_Lcgl_path_31 = _Larg_v_1[_Li_30];
fprintf(_Lninja_f_27, " cgl-tmp/%s-b", _Lcgl_path_31);
continue_5:;
_Li_30++;
}
break_5:;
fprintf(_Lninja_f_27, "\n");
fprintf(_Lninja_f_27, "build %s: c %s\n", _Lexe_path_23, _Lc_path_21);
_Nstdc_Nfile_Pclose_1(_Lninja_f_27);
sprintf(_Lcommand_32, "ninja -f %s", _Lninja_path_25);
_Lninja_ret_33 = system(_Lcommand_32);
unlink(_Lninja_path_25);
unlink(_Lc_path_21);
if(_Lninja_ret_33 != 0) {
exit(_Nstdc_Nexit_Cfailure);
}
_Lexe_ret_34 = system(_Lexe_path_23);
unlink(_Lexe_path_23);
if(_Lexe_ret_34 != 0) {
exit(_Nstdc_Nexit_Cfailure);
}
} else {
_Pprint_commands_1(_Lbin_2);
exit(_Nstdc_Nexit_Cfailure);
}
return 0;
}
void _Pprint_commands_1(char* _Lbin_0) {
fprintf(stdout, "Usage: %s [command] [options]\n", _Lbin_0);
fprintf(stdout, "Commands:\n");
fprintf(stdout, "  to-c     Build a C file.\n");
fprintf(stdout, "  run      Compile and run the cgl codes.\n");
}
void _Pprint_to_c_usage_1(char* _Lbin_0) {
fprintf(stdout, "Usage: %s to-c [output.c] [cgl file/s...]\n", _Lbin_0);
}
inline FILE* _Nstdc_Nfd_Pfopen_2(_Nstdc_Nfd _Lfile_0, char* _Lmode_1) {
return fdopen(_Lfile_0, _Lmode_1);
}
inline int32_t _Nstdc_Nfile_Pclose_1(FILE* _Lf_0) {
return fclose(_Lf_0);
}
void _Pprint_run_usage_1(char* _Lbin_0) {
fprintf(stdout, "Usage: %s run [cgl file/s...]\n", _Lbin_0);
}
inline int32_t _Nstdc_Nfd_Pclose_1(_Nstdc_Nfd _Lfile_0) {
return close(_Lfile_0);
}
void _Pget_compiler_2(char* _Lbin_0, FILE* _Lninja_f_1) {
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
return;
}
sprintf(_Lcompiler_5, "%s/clang", _Lfound_3);
_Lfd_4 = open(_Lcompiler_5, O_RDONLY);
if(_Lfd_4 != _Nstdc_Nfd_Cnil) {
fprintf(_Lninja_f_1, "rule c\n");
fprintf(_Lninja_f_1, " command = clang $in -o $out\n");
_Nstdc_Nfd_Pclose_1(_Lfd_4);
return;
}
sprintf(_Lcompiler_5, "%s/gcc", _Lfound_3);
_Lfd_4 = open(_Lcompiler_5, O_RDONLY);
if(_Lfd_4 != _Nstdc_Nfd_Cnil) {
fprintf(_Lninja_f_1, "rule c\n");
fprintf(_Lninja_f_1, " command = gcc $in -o $out\n");
_Nstdc_Nfd_Pclose_1(_Lfd_4);
return;
}
_Lfound_3 = strtok(NULL, ":");
continue_0:;
}
break_0:;
printf("Cannot execute '%s run' because the required compiler was not found: tcc clang or gcc\n", _Lbin_0);
exit(_Nstdc_Nexit_Cfailure);
}
