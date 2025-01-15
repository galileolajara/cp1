#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#define _NStdc_NExit_Csuccess 0
#define _NStdc_NExit_Cfailure (_NStdc_NExit_Csuccess + 1)
typedef int _NStdc_NExit;
typedef int _NStdc_NFd;
typedef int _NStdc_NOpenFlags;
typedef int _NStdc_NSeek;
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
int main(int _Larg_c_0, char** _Larg_v_1);
void _NCp1_Ppreprocess_def_2(char* _Lname_0, uint8_t _Llen_1);
bool _NStdc_NFd_Popen_3(_NStdc_NFd* _Lfile_0, char* _Lpath_1, _NStdc_NOpenFlags _Lflags_2);
int _NStdc_NFd_Pclose_1(_NStdc_NFd _Lfile_0);
void _NCp1_Ppreprocess_init_0();
void _NCp1_Ppreprocess_2(void** _Lin_out_data_0, size_t* _Lin_out_size_1);
bool _NStdc_NFd_Popen_4(_NStdc_NFd* _Lfile_0, char* _Lpath_1, _NStdc_NOpenFlags _Lflags_2, int _Lmode_3);
bool _NCp1_Ppreprocess_def_get_2(char* _Lname_0, uint8_t _Llen_1);
int main(int _Larg_c_0, char** _Larg_v_1) {
int32_t _Li_2;
_NStdc_NFd _Lin_fd_5;
size_t _Lin_size_6;
char* _Lin_data_7;
_NStdc_NFd _Lout_fd_8;
if(_Larg_c_0 < 3) {
usage:
printf("Usage: %s [options] [.cp1 input file] [.cp1 output file]\n", _Larg_v_1[0]);
printf("Options:\n");
printf(" -Ddefinename     Define a name that will yield true on #if(...) preprocessor\n");
exit(_NStdc_NExit_Cfailure);
}
_Li_2 = 1;
for(int i = _Larg_c_0; i > 0; ) {
i --;
if(_Larg_v_1[_Li_2][0] == '-') {
if(_Larg_v_1[_Li_2][1] == 'D') {
char* _Lname_3;
int32_t _Llen_4;
_Lname_3 = &_Larg_v_1[_Li_2][2];
_Llen_4 = 0;
while(1) {
if(_Lname_3[_Llen_4] == '\0') {
goto break_1;
}
if(((_Lname_3[_Llen_4] >= 'a') && (_Lname_3[_Llen_4] <= 'z'))) {
} else if(((_Lname_3[_Llen_4] >= 'A') && (_Lname_3[_Llen_4] <= 'Z'))) {
} else if(((_Lname_3[_Llen_4] >= '0') && (_Lname_3[_Llen_4] <= '9'))) {
if(_Llen_4 == 0) {
printf("Error, in option -Ddefinename, Definename' cannot begin with a number\n");
goto usage;
}
} else if(_Lname_3[_Llen_4] == '_') {
} else if(_Lname_3[_Llen_4] == '-') {
if(_Llen_4 == 0) {
printf("Error, in option -Ddefinename (which is %s), Definename' cannot begin with a dash\n", _Larg_v_1[_Li_2]);
goto usage;
} else if(_Lname_3[(_Llen_4 - 1)] == '-') {
printf("Error, in option -Ddefinename (which is %s), Definename' cannot contain consecutive a dashes\n", _Larg_v_1[_Li_2]);
goto usage;
}
} else {
printf("Error, in option -Ddefinename (which is %s), invalid character '%c' was detected in Definename'\n", _Larg_v_1[_Li_2], _Lname_3[_Llen_4]);
goto usage;
}
_Llen_4++;
continue_1:;
}
break_1:;
if(_Llen_4 == 0) {
printf("Error, in option -Ddefinename (which is %s), Definename' cannot be blank\n", _Larg_v_1[_Li_2]);
goto usage;
}
if(_Lname_3[(_Llen_4 - 1)] == '-') {
printf("Error, in option -Ddefinename (which is %s), Definename' cannot end with a dash\n", _Larg_v_1[_Li_2]);
goto usage;
}
_NCp1_Ppreprocess_def_2(_Lname_3, _Llen_4);
} else {
printf("Error, invalid option '-%c'\n", _Larg_v_1[_Li_2][1]);
goto usage;
}
} else {
goto break_0;
}
_Li_2++;
continue_0:;
}
break_0:;
if((_Larg_c_0 - _Li_2) != 2) {
goto usage;
}
_Ginput_path = _Larg_v_1[_Li_2];
if(!(_NStdc_NFd_Popen_3(&_Lin_fd_5, _Larg_v_1[_Li_2], O_RDONLY))) {
printf("Cannot open file for reading: %s\n", _Larg_v_1[_Li_2]);
exit(_NStdc_NExit_Cfailure);
}
_Lin_size_6 = lseek(_Lin_fd_5, 0, SEEK_END);
lseek(_Lin_fd_5, 0, SEEK_SET);
_Lin_data_7 = malloc(_Lin_size_6);
read(_Lin_fd_5, _Lin_data_7, _Lin_size_6);
_NStdc_NFd_Pclose_1(_Lin_fd_5);
_NCp1_Ppreprocess_init_0();
_NCp1_Ppreprocess_2(&_Lin_data_7, &_Lin_size_6);
if(!(_NStdc_NFd_Popen_4(&_Lout_fd_8, _Larg_v_1[(_Li_2 + 1)], O_CREAT | O_TRUNC | O_WRONLY, 32676))) {
printf("Cannot open file for writing: %s\n", _Larg_v_1[(_Li_2 + 1)]);
exit(_NStdc_NExit_Cfailure);
}
write(_Lout_fd_8, _Lin_data_7, _Lin_size_6);
_NStdc_NFd_Pclose_1(_Lout_fd_8);
return 0;
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
union _NCp1_NRdr _Lr_end_5;
union _NCp1_NRdr _Lr_6;
void* _Lnew_data_7;
union _NCp1_NWtr _Lw_8;
int32_t _Lline_9;
union _NCp1_NWtr _Lw_begin_25;
_Lpreprocess_2 = false;
_Lin_data_3 = (*_Lin_out_data_0);
_Lin_size_4 = (*_Lin_out_size_1);
_Lr_end_5._Freff = _Lin_data_3;
_Lr_end_5._Fpos += _Lin_size_4;
_Lr_6._Freff = _Lin_data_3;
_Lnew_data_7 = malloc(_Lin_size_4 + 1);
_Lw_8._Freff = _Lnew_data_7;
_Lline_9 = 0;
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
int32_t _Lif_line_11;
int32_t _Lstart_12;
bool _Linvert_13;
int32_t _Lrparen_14;
char* _Ldef_str_16;
int32_t _Ldef_len_17;
bool _Lok_18;
char* _Lindention_19;
int32_t _Lindention_len_20;
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
printf("%s:%u: Error in preprocessing the code, #if(...) must have a closing parenthesis ')'\n", _Ginput_path, _Lline_9);
exit(_NStdc_NExit_Cfailure);
}
_Ldef_str_16 = &_Lr_6._Fcharr[_Lstart_12];
_Ldef_len_17 = (_Lrparen_14 - _Lstart_12);
_Lok_18 = _NCp1_Ppreprocess_def_get_2(_Ldef_str_16, _Ldef_len_17);
if(_Linvert_13) {
_Lok_18 = !_Lok_18;
}
_Lr_6._Fpos += (_Lline_len_10 + 1);
_Lindention_19 = NULL;
_Lindention_len_20 = -1;
if(_Lr_6._Fpos < _Lr_end_5._Fpos) {
int32_t _Lline_len_21;
int32_t _Lfirst_char_22;
_Lline_len_21 = 0;
while(1) {
if(_Lr_6._Fp1[_Lline_len_21] == '\n') {
goto break_3;
}
_Lline_len_21++;
continue_3:;
}
break_3:;
_Lfirst_char_22 = 0;
while(1) {
if(((_Lr_6._Fp1[_Lfirst_char_22] == ' ') || (_Lr_6._Fp1[_Lfirst_char_22] == '\t'))) {
} else {
goto break_4;
}
_Lfirst_char_22++;
continue_4:;
}
break_4:;
if(_Lok_18) {
memcpy(_Lw_8._Fp1, &_Lr_6._Fp1[_Lfirst_char_22], (_Lline_len_21 + 1) - _Lfirst_char_22);
_Lw_8._Fpos += ((_Lline_len_21 + 1) - _Lfirst_char_22);
if(((_Lr_6._Fp1[_Lfirst_char_22] == '#') && (_Lr_6._Fp1[(_Lfirst_char_22 + 1)] == 'i') && (_Lr_6._Fp1[(_Lfirst_char_22 + 2)] == 'f') && ((_Lr_6._Fp1[(_Lfirst_char_22 + 3)] == '(') || ((_Lr_6._Fp1[(_Lfirst_char_22 + 3)] == '!') && (_Lr_6._Fp1[(_Lfirst_char_22 + 4)] == '('))))) {
_Lpreprocess_2 = true;
}
} else {
_Lw_8._Fp1[0] = '\n';
_Lw_8._Fpos++;
}
_Lindention_19 = _Lr_6._Fcharr;
_Lindention_len_20 = _Lfirst_char_22;
_Lline_len_21++;
_Lr_6._Fpos += _Lline_len_21;
}
if(_Lindention_len_20 <= 0) {
printf("%s:%u: Error in preprocessing the code, #if(...). Its next line (line %u) must be indented more than line %u\n", _Ginput_path, _Lline_9, _Lline_9 + 1, _Lline_9);
exit(_NStdc_NExit_Cfailure);
}
_Lline_9++;
while(_Lr_6._Fpos < _Lr_end_5._Fpos) {
int32_t _Lline_len_23;
int32_t _Lfirst_char_24;
_Lline_9++;
_Lline_len_23 = 0;
while(1) {
if(_Lr_6._Fp1[_Lline_len_23] == '\n') {
goto break_6;
}
_Lline_len_23++;
continue_6:;
}
break_6:;
_Lfirst_char_24 = 0;
while(1) {
if(((_Lr_6._Fp1[_Lfirst_char_24] == ' ') || (_Lr_6._Fp1[_Lfirst_char_24] == '\t'))) {
} else {
goto break_7;
}
_Lfirst_char_24++;
continue_7:;
}
break_7:;
if(((_Lline_len_23 >= _Lindention_len_20) && (memcmp(_Lr_6._Fp1, _Lindention_19, _Lindention_len_20) == 0))) {
if(_Lok_18) {
memcpy(_Lw_8._Fp1, &_Lr_6._Fp1[_Lindention_len_20], (_Lline_len_23 + 1) - _Lindention_len_20);
_Lw_8._Fpos += ((_Lline_len_23 + 1) - _Lindention_len_20);
if(((_Lr_6._Fp1[_Lindention_len_20] == '#') && (_Lr_6._Fp1[(_Lindention_len_20 + 1)] == 'i') && (_Lr_6._Fp1[(_Lindention_len_20 + 2)] == 'f') && ((_Lr_6._Fp1[(_Lindention_len_20 + 3)] == '(') || ((_Lr_6._Fp1[(_Lindention_len_20 + 3)] == '!') && (_Lr_6._Fp1[(_Lindention_len_20 + 4)] == '('))))) {
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
_Lr_6._Fpos += (_Lline_len_23 + 1);
} else {
printf("%s:%u: Error, expecting '#endif' with the same indention as '#if' on line %u, because line %u:S indention is different from indention at line %u\n", _Ginput_path, _Lline_9, _Lif_line_11, _Lline_9, _Lif_line_11 + 1);
exit(_NStdc_NExit_Cfailure);
}
goto break_5;
}
_Lline_len_23++;
_Lr_6._Fpos += _Lline_len_23;
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
_Lw_begin_25._Freff = _Lnew_data_7;
(*_Lin_out_size_1) = (_Lw_8._Fpos - _Lw_begin_25._Fpos);
if(_Lpreprocess_2) {
_NCp1_Ppreprocess_2(_Lin_out_data_0, _Lin_out_size_1);
} else {
}
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
