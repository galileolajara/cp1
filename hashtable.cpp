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
struct ParentTypeName {
   int parent_and_type; // type is at 30th - 32nd bit
   int name;
};
struct ParentTypeName_hash {
   using is_transparent = void; // enable heterogeneous overloads
   using is_avalanching = void; // mark class as high quality avalanching hash

   [[nodiscard]] auto operator()(ParentTypeName const& s) const noexcept -> uint64_t {
      return ankerl::unordered_dense::detail::wyhash::hash(&s, sizeof(s));
   }
};
struct ParentTypeName_compare {
   bool operator()(ParentTypeName const& lhs, ParentTypeName const& rhs) const {
      return lhs.parent_and_type == rhs.parent_and_type && lhs.name == rhs.name;
   }
};
typedef ankerl::unordered_dense::map<ParentTypeName, int, ParentTypeName_hash, ParentTypeName_compare> at_map_t;

#ifdef CP1_GET_SIZE
#include <stdio.h>
int main(int argc, char** argv) {
   FILE* fp = fopen(argv[1], "w");
   fprintf(fp, "{at(:cp1)\n#hash-table-size = %zu;\n}\n", sizeof(map_t));
   fclose(fp);
   return 0;
}
#else
extern "C" void _Ncp1_Nmap_Pinit_1(map_t &map) {
   new (&map) map_t();
}
extern "C" int _Ncp1_Nmap_Pget_or_insert_4(map_t &map, char* str, uint8_t len, int val) {
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
extern "C" void _Ncp1_Nat_map_Pinit_1(at_map_t &map) {
   new (&map) at_map_t();
}
extern "C" int _Ncp1_Nat_map_Pget_or_insert_5(at_map_t &map, int parent, uint8_t type, int name, int val) {
   ParentTypeName s;
   s.parent_and_type = parent | (type << 30);
   s.name = name;
   auto result = map.insert({s, val});
   if (result.second) {
      return -1;
   } else {
      return result.first->second;
   }
}
#endif
