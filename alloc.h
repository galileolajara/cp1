#include "num.c"
#define _Mglc_Pquick_alloc_one_1(r) r = qalloc(sizeof(r[0]))
#define _Mglc_Pquick_alloc_arr_2(r, c) r = qalloc(sizeof(r[0]) * (c))
#define _Mglc_Pquick_alloc_plus_2(r, plus) r = qalloc(sizeof(r[0]) + plus)
#define _Mglc_Pmalloc_1(r) r = malloc(sizeof(r[0])); memset(r, 0, sizeof(r[0]))
#define _Mglc_Pmalloc_arr_2(r, c) r = malloc(sizeof(r[0]) * (c)); memset(r, 0, sizeof(r[0]) * (c))
#define _Mglc_Prealloc_3(r, c, oldc) r = realloc(r, sizeof(r[0]) * (c)); memset(r + (oldc), 0, sizeof(r[0]) * ((c) - (oldc)))
#define _Mglc_Pgrow_2(cap, c) cap = Fpow2gteq(c + 8)
