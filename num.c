#include <stdint.h>
#include <limits.h>

void Fskipnum(uint8_t** pbuf) {
  uint8_t* buf = *pbuf;
  uint8_t first = *(buf ++);
  uint8_t zeroes = __builtin_ctz(first);
  *pbuf = buf + zeroes;
}

uint32_t Fgetnum(uint8_t** pbuf) {
  uint8_t* buf = *pbuf;
  uint8_t first = *(buf ++);
  if(first == 0) return 0xffffffff;
  uint32_t var;
  uint8_t zeroes = __builtin_ctz(first);
  // fprintf(stdout, ":getnum, zeroes: %d\n", zeroes);
  switch(zeroes) {
    case 0:
      var = first >> 1;
      break;
    case 1:
      var = (first >> 2) | (*(buf ++) << 6);
      break;
    case 2:
      var = (first >> 3) | (*(buf ++) << 5);
      var |= *(buf ++) << (5 + 8);
      break;
    case 3:
      var = (first >> 4) | (*(buf ++) << 4);
      var |= *(buf ++) << (4 + 8);
      var |= *(buf ++) << (4 + 8 + 8);
      break;
    case 4:
      var = (first >> 5) | (*(buf ++) << 3);
      var |= *(buf ++) << (3 + 8);
      var |= *(buf ++) << (3 + 8 + 8);
      var |= *(buf ++) << (3 + 8 + 8 + 8);
      break;
    default:
      return  0xffffffff;
  }
  *pbuf = buf;
  return var;
}

void Fputnum(uint8_t **pbuf, uint32_t num) {
  uint8_t* buf = *pbuf;
  uint8_t zeroes = num == 0 ? 31 : __builtin_clz(num);
  uint8_t bits = 32 - zeroes;
  // fprintf(stdout, ":putnum(%u), zeroes: %u, bits: %u\n", num, zeroes, bits);
  switch(bits) {
    case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7:
      *(buf ++) = (num << 1) | 1;
      // fprintf(stdout, "encoding in 1 byte\n");
      break;
    case 8: case 9: case 10: case 11: case 12: case 13: case 14:
      *(buf ++) = (num << 2) | (1 << 1);
      *(buf ++) = num >> 6;
      // fprintf(stdout, "encoding in 2 byte\n");
      break;
    case 15: case 16: case 17: case 18: case 19: case 20: case 21:
      *(buf ++) = (num << 3) | (1 << 2);
      *(buf ++) = num >> 5;
      *(buf ++) = num >> (5 + 8);
      // fprintf(stdout, "encoding in 3 byte\n");
      break;
    case 22: case 23: case 24: case 25: case 26: case 27: case 28:
      *(buf ++) = (num << 4) | (1 << 3);
      *(buf ++) = num >> 4;
      *(buf ++) = num >> (4 + 8);
      *(buf ++) = num >> (4 + 8 + 8);
      // fprintf(stdout, "encoding in 4 byte\n");
      break;
    default:
      *(buf ++) = (num << 5) | (1 << 4);
      *(buf ++) = num >> 3;
      *(buf ++) = num >> (3 + 8);
      *(buf ++) = num >> (3 + 8 + 8);
      *(buf ++) = num >> (3 + 8 + 8 + 8);
      // fprintf(stdout, "encoding in 5 byte\n");
      break;
  }
  *pbuf = buf;
}

int32_t Fgetint(uint8_t** pbuf) {
  uint8_t* buf = *pbuf;
  uint8_t first = *(buf ++);
  if(first == 0) return 0xffffffff;
  int32_t var;
  uint8_t zeroes = __builtin_ctz(first);
  // fprintf(stdout, ":getnum, zeroes: %d\n", zeroes);
  uint8_t negative;
  switch(zeroes) {
    case 0:
      negative = (first & 2) != 0;
      var = first >> 2;
      break;
    case 1:
      negative = (first & 4) != 0;
      var = (first >> 3) | (*(buf ++) << 5);
      break;
    case 2:
      negative = (first & 8) != 0;
      var = (first >> 4) | (*(buf ++) << 4);
      var |= *(buf ++) << (4 + 8);
      break;
    case 3:
      negative = (first & 16) != 0;
      var = (first >> 5) | (*(buf ++) << 3);
      var |= *(buf ++) << (3 + 8);
      var |= *(buf ++) << (3 + 8 + 8);
      break;
    case 4:
      negative = (first & 32) != 0;
      var = (first >> 6) | (*(buf ++) << 2);
      var |= *(buf ++) << (2 + 8);
      var |= *(buf ++) << (2 + 8 + 8);
      var |= *(buf ++) << (2 + 8 + 8 + 8);
      break;
    default:
      return INT_MAX;
  }
  *pbuf = buf;
  if (negative) return -var;
  return var;
}
void Fputint(uint8_t **pbuf, int32_t _int) {
   uint32_t num;
   uint8_t negative;
   if (_int < 0) {
      negative = 1;
      num = -_int;
   } else {
      negative = 0;
      num = _int;
   }
  uint8_t* buf = *pbuf;
  uint8_t zeroes = num == 0 ? 31 : __builtin_clz(num);
  uint8_t bits = 32 - zeroes + 1;
  // fprintf(stdout, ":putnum(%u), zeroes: %u, bits: %u\n", num, zeroes, bits);
  switch(bits) {
    case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7:
       if(negative) {
      *(buf ++) = (num << 2) | 1 | 2;
       } else {
      *(buf ++) = (num << 2) | 1;
       }
      // fprintf(stdout, "encoding in 1 byte\n");
      break;
    case 8: case 9: case 10: case 11: case 12: case 13: case 14:
      if(negative) {
      *(buf ++) = (num << 3) | (1 << 1) | 4;
      } else {
      *(buf ++) = (num << 3) | (1 << 1);
      }
      *(buf ++) = num >> 5;
      // fprintf(stdout, "encoding in 2 byte\n");
      break;
    case 15: case 16: case 17: case 18: case 19: case 20: case 21:
      if(negative) {
      *(buf ++) = (num << 4) | (1 << 2) | 8;
      } else {
      *(buf ++) = (num << 4) | (1 << 2);
      }
      *(buf ++) = num >> 4;
      *(buf ++) = num >> (4 + 8);
      // fprintf(stdout, "encoding in 3 byte\n");
      break;
    case 22: case 23: case 24: case 25: case 26: case 27: case 28:
      if(negative) {
      *(buf ++) = (num << 5) | (1 << 3) | 16;
      } else {
      *(buf ++) = (num << 5) | (1 << 3);
      }
      *(buf ++) = num >> 3;
      *(buf ++) = num >> (3 + 8);
      *(buf ++) = num >> (3 + 8 + 8);
      // fprintf(stdout, "encoding in 4 byte\n");
      break;
    default:
      if(negative) {
      *(buf ++) = (num << 6) | (1 << 4) | 32;
      } else {
      *(buf ++) = (num << 6) | (1 << 4);
      }
      *(buf ++) = num >> 2;
      *(buf ++) = num >> (2 + 8);
      *(buf ++) = num >> (2 + 8 + 8);
      *(buf ++) = num >> (2 + 8 + 8 + 8);
      // fprintf(stdout, "encoding in 5 byte\n");
      break;
  }
  *pbuf = buf;
}

void Fputnum1(uint8_t **pbuf, uint32_t num) {
	uint8_t* buf = *pbuf;
	*(buf ++) = (num << 1) | 1;
	*pbuf = buf;
}

void Fputnum2(uint8_t **pbuf, uint32_t num) {
	uint8_t* buf = *pbuf;
   *(buf ++) = (num << 2) | (1 << 1);
   *(buf ++) = num >> 6;
	*pbuf = buf;
}

void Fputnum3(uint8_t **pbuf, uint32_t num) {
	uint8_t* buf = *pbuf;
   *(buf ++) = (num << 3) | (1 << 2);
   *(buf ++) = num >> 5;
   *(buf ++) = num >> (5 + 8);
	*pbuf = buf;
}

void Fputnum4(uint8_t **pbuf, uint32_t num) {
	uint8_t* buf = *pbuf;
   *(buf ++) = (num << 4) | (1 << 3);
   *(buf ++) = num >> 4;
   *(buf ++) = num >> (4 + 8);
   *(buf ++) = num >> (4 + 8 + 8);
	*pbuf = buf;
}

void Fputnum5(uint8_t **pbuf, uint32_t num) {
	uint8_t* buf = *pbuf;
   *(buf ++) = (num << 5) | (1 << 4);
   *(buf ++) = num >> 3;
   *(buf ++) = num >> (3 + 8);
   *(buf ++) = num >> (3 + 8 + 8);
   *(buf ++) = num >> (3 + 8 + 8 + 8);
	*pbuf = buf;
}

uint64_t Fgetlnum(uint8_t** pbuf) {
	uint8_t* buf = *pbuf;
	uint8_t first = *(buf ++);
	uint64_t var;
	uint8_t zeroes = first == 0 ? 8 : __builtin_ctzll(first);
	// fprintf(stdout, ":getnum, zeroes: %d\n", zeroes);
	switch(zeroes) {
		case 0:
		var = first >> 1;
		break;
		case 1:
		var = (first >> 2) | (*(buf ++) << 6);
		break;
		case 2:
		var = (first >> 3) | (*(buf ++) << 5);
		var |= *(buf ++) << (5 + 8);
		break;
		case 3:
		var = (first >> 4) | (*(buf ++) << 4);
		var |= *(buf ++) << (4 + 8);
		var |= *(buf ++) << (4 + 8 + 8);
		break;
		case 4:
		var = (first >> 5) | (*(buf ++) << 3);
		var |= *(buf ++) << (3 + 8);
		var |= *(buf ++) << (3 + 8 + 8);
		var |= (uint64_t)*(buf ++) << (3 + 8 + 8 + 8);
		break;
		case 5:
		var = (first >> 6) | (*(buf ++) << 2);
		var |= *(buf ++) << (2 + 8);
		var |= *(buf ++) << (2 + 8 + 8);
		var |= (uint64_t)*(buf ++) << (2 + 8 + 8 + 8);
		var |= (uint64_t)*(buf ++) << (2 + 8 + 8 + 8 + 8);
		break;
		case 6:
		var = (first >> 7) | (*(buf ++) << 1);
		var |= *(buf ++) << (1 + 8);
		var |= *(buf ++) << (1 + 8 + 8);
		var |= (uint64_t)*(buf ++) << (1 + 8 + 8 + 8);
		var |= (uint64_t)*(buf ++) << (1 + 8 + 8 + 8 + 8);
		var |= (uint64_t)*(buf ++) << (1 + 8 + 8 + 8 + 8 + 8);
		break;
		case 7:
		var = *(buf ++);
		var |= *(buf ++) << (8);
		var |= *(buf ++) << (8 + 8);
		var |= (uint64_t)*(buf ++) << (8 + 8 + 8);
		var |= (uint64_t)*(buf ++) << (8 + 8 + 8 + 8);
		var |= (uint64_t)*(buf ++) << (8 + 8 + 8 + 8 + 8);
		var |= (uint64_t)*(buf ++) << (8 + 8 + 8 + 8 + 8 + 8);
		break;
		default:
		var = /* (first >> 8) | */ *(buf ++);
		var |= *(buf ++) << (8);
		var |= *(buf ++) << (8 + 8);
		var |= (uint64_t)*(buf ++) << (8 + 8 + 8);
		var |= (uint64_t)*(buf ++) << (8 + 8 + 8 + 8);
		var |= (uint64_t)*(buf ++) << (8 + 8 + 8 + 8 + 8);
		var |= (uint64_t)*(buf ++) << (8 + 8 + 8 + 8 + 8 + 8);
		var |= (uint64_t)*(buf ++) << (8 + 8 + 8 + 8 + 8 + 8 + 8);
		break;
	}
	*pbuf = buf;
	return var;
}

void Fputlnum(uint8_t **pbuf, uint64_t num) {
  uint8_t* buf = *pbuf;
  uint8_t zeroes = num == 0 ? 63 : __builtin_clzll(num);
  uint8_t bits = 64 - zeroes;
  // fprintf(stdout, ":putnum(%u), zeroes: %u, bits: %u\n", num, zeroes, bits);
  switch(bits) {
    case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7:
      *(buf ++) = (num << 1) | 1;
      // fprintf(stdout, "encoding in 1 byte\n");
      break;
    case 8: case 9: case 10: case 11: case 12: case 13: case 14:
      *(buf ++) = (num << 2) | (1 << 1);
      *(buf ++) = num >> 6;
      // fprintf(stdout, "encoding in 2 byte\n");
      break;
    case 15: case 16: case 17: case 18: case 19: case 20: case 21:
      *(buf ++) = (num << 3) | (1 << 2);
      *(buf ++) = num >> 5;
      *(buf ++) = num >> (5 + 8);
      // fprintf(stdout, "encoding in 3 byte\n");
      break;
    case 22: case 23: case 24: case 25: case 26: case 27: case 28:
      *(buf ++) = (num << 4) | (1 << 3);
      *(buf ++) = num >> 4;
      *(buf ++) = num >> (4 + 8);
      *(buf ++) = num >> (4 + 8 + 8);
      // fprintf(stdout, "encoding in 4 byte\n");
      break;
    case 29: case 30: case 31: case 32: case 33: case 34: case 35:
      *(buf ++) = (num << 5) | (1 << 4);
      *(buf ++) = num >> 3;
      *(buf ++) = num >> (3 + 8);
      *(buf ++) = num >> (3 + 8 + 8);
      *(buf ++) = num >> (3 + 8 + 8 + 8);
      // fprintf(stdout, "encoding in 5 byte\n");
      break;
    case 36: case 37: case 38: case 39: case 40: case 41: case 42:
      *(buf ++) = (num << 6) | (1 << 5);
      *(buf ++) = num >> 2;
      *(buf ++) = num >> (2 + 8);
      *(buf ++) = num >> (2 + 8 + 8);
      *(buf ++) = num >> (2 + 8 + 8 + 8);
      *(buf ++) = num >> (2 + 8 + 8 + 8 + 8);
      // fprintf(stdout, "encoding in 5 byte\n");
      break;
    case 43: case 44: case 45: case 46: case 47: case 48: case 49:
      *(buf ++) = (num << 7) | (1 << 6);
      *(buf ++) = num >> 1;
      *(buf ++) = num >> (1 + 8);
      *(buf ++) = num >> (1 + 8 + 8);
      *(buf ++) = num >> (1 + 8 + 8 + 8);
      *(buf ++) = num >> (1 + 8 + 8 + 8 + 8);
      *(buf ++) = num >> (1 + 8 + 8 + 8 + 8 + 8);
      // fprintf(stdout, "encoding in 5 byte\n");
      break;
    case 50: case 51: case 52: case 53: case 54: case 55: case 56:
      *(buf ++) = (1 << 7);
      *(buf ++) = num;
      *(buf ++) = num >> (8);
      *(buf ++) = num >> (8 + 8);
      *(buf ++) = num >> (8 + 8 + 8);
      *(buf ++) = num >> (8 + 8 + 8 + 8);
      *(buf ++) = num >> (8 + 8 + 8 + 8 + 8);
      *(buf ++) = num >> (8 + 8 + 8 + 8 + 8 + 8);
      break;
    default:
      *(buf ++) = 0;
      *(buf ++) = num;
      *(buf ++) = num >> (8);
      *(buf ++) = num >> (8 + 8);
      *(buf ++) = num >> (8 + 8 + 8);
      *(buf ++) = num >> (8 + 8 + 8 + 8);
      *(buf ++) = num >> (8 + 8 + 8 + 8 + 8);
      *(buf ++) = num >> (8 + 8 + 8 + 8 + 8 + 8);
      *(buf ++) = num >> (8 + 8 + 8 + 8 + 8 + 8 + 8);
      // fprintf(stdout, "encoding in 5 byte\n");
      break;
   /*
    default:
      *(buf ++) = 0;
      *(buf ++) = num;
      *(buf ++) = num >> (8);
      *(buf ++) = num >> (8 + 8);
      *(buf ++) = num >> (8 + 8 + 8);
      *(buf ++) = num >> (8 + 8 + 8 + 8);
      *(buf ++) = num >> (8 + 8 + 8 + 8 + 8);
      *(buf ++) = num >> (8 + 8 + 8 + 8 + 8 + 8);
      *(buf ++) = num >> (8 + 8 + 8 + 8 + 8 + 8 + 8);
      break;
   */
  }
  *pbuf = buf;
}

/*
uint32_t Fpow2(uint32_t n) {
  uint8_t bits = 32 - __builtin_clz(n);
  return 1 << bits;
}
*/

uint32_t Fpow2gt(uint32_t n) {
	if(n == 0) return 1;
  uint8_t bits = 32 - __builtin_clz(n);
  return 1 << bits;
}

uint32_t Fpow2gteq(uint32_t n) {
	if(n <= 1) return 1;
  uint8_t bits = 32 - __builtin_clz(n - 1);
  return 1 << bits;
}
