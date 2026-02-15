char* output_buf;
uint32_t output_len;

struct D_t {
   struct D_t* next;
   uint8_t keylen;
   char keybuf[32];
   uint8_t vallen;
   char valbuf[256];
};

struct D_t* D_first;
struct D_t* D_last;
