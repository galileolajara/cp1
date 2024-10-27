#include "unordered_dense.h"

struct ShortString {
   char* str;
   uint8_t len;
};
struct string_hash {
   using is_transparent = void; // enable heterogeneous overloads
   using is_avalanching = void; // mark class as high quality avalanching hash

   [[nodiscard]] auto operator()(ShortString const& s) const noexcept -> uint64_t {
      return ankerl::unordered_dense::detail::wyhash::hash(s.str, s.len);
   }
};
struct string_compare {
   bool operator()(ShortString const& lhs, ShortString const& rhs) const {
      return lhs.len == rhs.len && memcmp(lhs.str, rhs.str, lhs.len) == 0;
   }
};
typedef ankerl::unordered_dense::map<ShortString, int, string_hash, string_compare> map_t;

#ifdef GLC_GET_SIZE
#include <stdio.h>
int main(int argc, char** argv) {
   FILE* fp = fopen(argv[1], "w");
   fprintf(fp, "{at(%%glc)\n{cvar #hash-table-size = %zu}\n}\n", sizeof(map_t));
   fclose(fp);
   return 0;
}
#else
extern "C" void _Mglc_Smap_Pinit_1(map_t &map) {
   new (&map) map_t();
}
extern "C" int _Mglc_Smap_Pget_or_insert_4(map_t &map, char* str, uint8_t len, int val) {
   ShortString s;
   s.str = str;
   s.len = len;
   auto result = map.insert({s, val});
   if (result.second) {
      return -1;
   } else {
      return result.first->second;
   }
}
#endif
