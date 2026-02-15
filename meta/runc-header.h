char* output_buf;
uint32_t output_len;

struct replacer_t {
   struct replacer_t* next;
   uint8_t srclen;
   char srcbuf[32];
   uint16_t deslen;
   char desbuf[1024];
};

struct replacer_t* replacer_first;
struct replacer_t* replacer_last;
