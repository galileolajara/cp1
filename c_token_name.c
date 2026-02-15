#include <stdio.h>
int main(int argc, char** argv) {
   FILE* fin = fopen(argv[1], "r");
   FILE* fout = fopen(argv[2], "w");
   fprintf(fout, "const char* token_name(int t) {\n   switch(t) {\n");
   char line[256];
   while (fgets(line, sizeof(line), fin)) {
      char name[64];
      sscanf(line + 8 + 8, "%s", name);
      fprintf(fout, "      case C_TOKEN_%s: return \"%s\";\n", name, name);
   }
   fprintf(fout, "   }\n   return \"\";\n}\n");
   fclose(fin);
   fclose(fout);
   return 0;
}
