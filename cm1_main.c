#ifdef CP1_NEW
#include "out/compile2.cm1.c"
#else
#include "compile.cm1.c"
#endif

int main(int argc, char** argv) {
   #ifdef CP1_NEW
   cm1_init("out/compile2.cm1");
   #else
   cm1_init("out/compile.cm1");
   #endif
   return _Tcp1_Fmain_2(argc, argv);
}
