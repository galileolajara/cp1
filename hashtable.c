#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "crc32c.h"

#define HASH_KEY_COUNT 256
#define BUCKET_SIZE 128

struct key_t {
	struct key_t* prev;
   uint32_t sums[BUCKET_SIZE];
   uint8_t lens[BUCKET_SIZE];
   uint8_t* strs[BUCKET_SIZE];
   uint32_t vals[BUCKET_SIZE];
   uint8_t valc;
};

struct map_t {
	struct key_t* keys[HASH_KEY_COUNT]; // last
};

struct at_key_t {
	struct at_key_t* prev;
   uint32_t names[BUCKET_SIZE];
   uint32_t parent_and_types[BUCKET_SIZE];
   uint32_t vals[BUCKET_SIZE];
   uint8_t valc;
};

struct at_map_t {
	struct at_key_t* keys[HASH_KEY_COUNT]; // last
};

#ifdef CP1_GET_SIZE
#include <stdio.h>
int main(int argc, char** argv) {
   FILE* fp = fopen(argv[1], "w");
   fprintf(fp, "using `cp1 {\n#hash-table-size`usz = %zu;\n}\n", sizeof(struct map_t));
   fclose(fp);
   return 0;
}
#else
void _Tcp1_Tmap_Finit_1(struct map_t* map) {
   for (int i = 0; i < HASH_KEY_COUNT; i++) {
      map->keys[i] = NULL;
   }
}
void* qalloc(int32_t size);
int32_t _Tcp1_Tmap_Fget_or_insert_4(struct map_t* map, uint8_t* str, uint8_t len, uint32_t val) {
   uint32_t sum = crc32c(0, str, len);
   uint8_t hk = sum & 0xff;
   struct key_t* last_key = map->keys[hk];
   struct key_t* key = last_key;
   while (key != NULL) {
      uint8_t valc = key->valc;
      for (int i = 0; i < valc; i++) {
         if (key->sums[i] == sum && key->lens[i] == len && memcmp(str, key->strs[i], len) == 0) {
            return key->vals[i];
         }
      }
      key = key->prev;
   }
   uint8_t* s = qalloc(len);
   memcpy(s, str, len);
   if (last_key != NULL && last_key->valc < BUCKET_SIZE) {
      uint8_t i = last_key->valc++;
      last_key->sums[i] = sum;
      last_key->vals[i] = val;
      last_key->strs[i] = s;
      last_key->lens[i] = len;
      return -1;
   }
   key = qalloc(sizeof(struct key_t));
   key->prev = last_key;
   map->keys[hk] = key;
   key->sums[0] = sum;
   key->vals[0] = val;
   key->strs[0] = s;
   key->lens[0] = len;
   key->valc = 1;
   return -1;
}
void _Tcp1_Tat_map_Finit_1(struct at_map_t* map) {
   for (int i = 0; i < HASH_KEY_COUNT; i++) {
      map->keys[i] = NULL;
   }
}
int32_t _Tcp1_Tat_map_Fget_or_insert_4(struct at_map_t* map, uint32_t parent_and_type, uint32_t name, uint32_t val) {
   uint32_t v[2];
   v[0] = name;
   v[1] = parent_and_type;
   uint32_t sum = crc32c(0, (uint8_t*)v, sizeof(v));
   uint8_t hk = sum & 0xff;
   struct at_key_t* last_key = map->keys[hk];
   struct at_key_t* key = last_key;
   while (key != NULL) {
      uint8_t valc = key->valc;
      for (int i = 0; i < valc; i++) {
         if (key->names[i] == name && key->parent_and_types[i] == parent_and_type) {
            return key->vals[i];
         }
      }
      key = key->prev;
   }
   if (last_key != NULL && last_key->valc < BUCKET_SIZE) {
      uint8_t i = last_key->valc++;
      last_key->names[i] = name;
      last_key->parent_and_types[i] = parent_and_type;
      last_key->vals[i] = val;
      return -1;
   }
   key = qalloc(sizeof(struct at_key_t));
   key->prev = last_key;
   map->keys[hk] = key;
   key->names[0] = name;
   key->parent_and_types[0] = parent_and_type;
   key->vals[0] = val;
   key->valc = 1;
   return -1;
}
#endif
