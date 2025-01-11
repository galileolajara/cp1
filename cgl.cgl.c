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
system(_Lcommand_16);
unlink(_Lninja_path_9);
} else if(strcmp(_Lcmd_3, "run") == 0) {
char _Lc_path_20[22];
_Nstdc_Nfd _Lc_fd_21;
char _Lexe_path_22[24];
_Nstdc_Nfd _Lexe_fd_23;
char _Lninja_path_24[24];
_Nstdc_Nfd _Lninja_fd_25;
FILE* _Lninja_f_26;
char _Lcommand_31[24 + 9];
int32_t _Lninja_ret_32;
int32_t _Lexe_ret_33;
if(_Larg_c_0 < 3) {
_Pprint_run_usage_1(_Lbin_2);
exit(_Nstdc_Nexit_Cfailure);
}
int32_t _Li_17;
_Li_17 = 2;
for(int i = _Larg_c_0 - 2; i > 0; ) {
i --;
char* _Lcgl_path_18;
size_t _Lcgl_path_len_19;
_Lcgl_path_18 = _Larg_v_1[_Li_17];
_Lcgl_path_len_19 = strlen(_Lcgl_path_18);
if(!(((_Lcgl_path_len_19 > 4) && (_Lcgl_path_18[(_Lcgl_path_len_19 - 4)] == '.') && (_Lcgl_path_18[(_Lcgl_path_len_19 - 3)] == 'c') && (_Lcgl_path_18[(_Lcgl_path_len_19 - 2)] == 'g') && (_Lcgl_path_18[(_Lcgl_path_len_19 - 1)] == 'l')))) {
_Pprint_run_usage_1(_Lbin_2);
fprintf(stdout, "Error, [cgl file] (which is '%s') must be a filename that ends with '.cgl', for example: main.cgl\n", _Lcgl_path_18);
exit(_Nstdc_Nexit_Cfailure);
}
continue_3:;
_Li_17++;
}
break_3:;
mkdir("cgl-tmp", 32749);
strcpy(_Lc_path_20, "cgl-tmp/c-XXXXXXXXX");
_Lc_fd_21 = mkstemp(_Lc_path_20);
if(_Lc_fd_21 == _Nstdc_Nfd_Cnil) {
_Pprint_run_usage_1(_Lbin_2);
fprintf(stdout, "Error, cannot open file for reading: %s\n", _Lc_path_20);
exit(_Nstdc_Nexit_Cfailure);
}
_Nstdc_Nfd_Pclose_1(_Lc_fd_21);
unlink(_Lc_path_20);
strcpy(_Lexe_path_22, "cgl-tmp/exe-XXXXXXXXX");
_Lexe_fd_23 = mkstemp(_Lexe_path_22);
if(_Lexe_fd_23 == _Nstdc_Nfd_Cnil) {
_Pprint_run_usage_1(_Lbin_2);
fprintf(stdout, "Error, cannot open file for reading: %s\n", _Lexe_path_22);
exit(_Nstdc_Nexit_Cfailure);
}
_Nstdc_Nfd_Pclose_1(_Lexe_fd_23);
unlink(_Lexe_path_22);
_Lc_path_20[19] = '.';
_Lc_path_20[20] = 'c';
_Lc_path_20[21] = '\0';
strcpy(_Lninja_path_24, "cgl-tmp/ninja-XXXXXXXXX");
_Lninja_fd_25 = mkstemp(_Lninja_path_24);
if(_Lninja_fd_25 == _Nstdc_Nfd_Cnil) {
_Pprint_run_usage_1(_Lbin_2);
fprintf(stdout, "Error, cannot open file for reading: %s\n", _Lninja_path_24);
exit(_Nstdc_Nexit_Cfailure);
}
_Lninja_f_26 = _Nstdc_Nfd_Pfopen_2(_Lninja_fd_25, "w");
fprintf(_Lninja_f_26, "rule parser\n");
fprintf(_Lninja_f_26, " command = %s-parser $in\n", _Lbin_2);
fprintf(_Lninja_f_26, "rule compiler\n");
fprintf(_Lninja_f_26, " command = %s-compiler $in $out\n", _Lbin_2);
_Pget_compiler_2(_Lbin_2, _Lninja_f_26);
int32_t _Li_27;
_Li_27 = 2;
for(int i = _Larg_c_0 - 2; i > 0; ) {
i --;
char* _Lcgl_path_28;
_Lcgl_path_28 = _Larg_v_1[_Li_27];
fprintf(_Lninja_f_26, "build cgl-tmp/%s-b: parser %s\n", _Lcgl_path_28, _Lcgl_path_28);
continue_4:;
_Li_27++;
}
break_4:;
fprintf(_Lninja_f_26, "build %s: compiler", _Lc_path_20);
int32_t _Li_29;
_Li_29 = 2;
for(int i = _Larg_c_0 - 2; i > 0; ) {
i --;
char* _Lcgl_path_30;
_Lcgl_path_30 = _Larg_v_1[_Li_29];
fprintf(_Lninja_f_26, " cgl-tmp/%s-b", _Lcgl_path_30);
continue_5:;
_Li_29++;
}
break_5:;
fprintf(_Lninja_f_26, "\n");
fprintf(_Lninja_f_26, "build %s: c %s\n", _Lexe_path_22, _Lc_path_20);
_Nstdc_Nfile_Pclose_1(_Lninja_f_26);
sprintf(_Lcommand_31, "ninja -f %s", _Lninja_path_24);
_Lninja_ret_32 = system(_Lcommand_31);
unlink(_Lninja_path_24);
unlink(_Lc_path_20);
if(_Lninja_ret_32 != 0) {
unlink(_Lexe_path_22);
return _Lninja_ret_32;
}
_Lexe_ret_33 = system(_Lexe_path_22);
unlink(_Lexe_path_22);
return _Lexe_ret_33;
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
FILE* _Nstdc_Nfd_Pfopen_2(_Nstdc_Nfd _Lfile_0, char* _Lmode_1) {
return fdopen(_Lfile_0, _Lmode_1);
}
int32_t _Nstdc_Nfile_Pclose_1(FILE* _Lf_0) {
return fclose(_Lf_0);
}
void _Pprint_run_usage_1(char* _Lbin_0) {
fprintf(stdout, "Usage: %s run [cgl file/s...]\n", _Lbin_0);
}
int32_t _Nstdc_Nfd_Pclose_1(_Nstdc_Nfd _Lfile_0) {
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
