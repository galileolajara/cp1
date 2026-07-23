#include "out/compile2.cm1.c"

int main(int argc, char** argv) {
   cm1_init("out/compile2.cm1");
   int r = _Tcp1_Fmain_2(argc, argv);
   printf("main ran without crashing\n");
   return r;
}
