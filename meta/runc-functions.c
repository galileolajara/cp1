switch (bc_offset) {
   case 0: {
      uint32_t len = vml_pop_i32(vml);
      mem_t mem = vml_pop_mem(vml);
      memcpy(output_buf + output_len, vml->memory + mem, len);
      output_len += len;
      break;
   }
   case 1: {
      output_buf[output_len++] = '\n';
      break;
   }
   case 2: {
      uint32_t len = vml_pop_i32(vml);
      mem_t mem = vml_pop_mem(vml);
      char* buf = vml->memory + mem;
      for (uint32_t i = 0; i < len; ) {
         if ((buf[i] == '$') && (buf[i + 1] == '{')) {
            i += 2;
            struct replacer_t* r = replacer_first;
            while (r != 0) {
               if (memcmp(r->srcbuf, buf + i, r->srclen) == 0) {
                  break;
               }
               r = r->next;
            }
            if (r == 0) {
               output_buf[output_len++] = '$';
               output_buf[output_len++] = '{';
            } else {
               uint16_t deslen = r->deslen;
               memcpy(output_buf + output_len, r->desbuf, deslen);
               output_len += deslen;
               i += r->srclen + 1;
            }
         } else {
            output_buf[output_len++] = buf[i++];
         }
      }
      break;
   }
   case 3: {
      uint32_t deslen = vml_pop_i32(vml);
      mem_t desmem = vml_pop_mem(vml);
      char* desbuf = vml->memory + desmem;
      uint32_t srclen = vml_pop_i32(vml);
      mem_t srcmem = vml_pop_mem(vml);
      char* srcbuf = vml->memory + srcmem;
      
      // check if srcmem/srclen already exists
      struct replacer_t* r = replacer_first;
      bool allocate = true;
      while (r != 0) {
         if ((r->srclen == srclen) && (memcmp(r->srcbuf, srcbuf, srclen) == 0)) {
            allocate = false;
            break;
         }
         r = r->next;
      }

      if (allocate) {
         r = malloc(sizeof(struct replacer_t));
         memcpy(r->srcbuf, srcbuf, srclen);
         r->srclen = srclen;
      }
      memcpy(r->desbuf, desbuf, deslen);
      r->deslen = deslen;
      
      if (allocate) {
         if (replacer_last == 0) {
            replacer_last = replacer_first = r;
         } else {
            replacer_last->next = r;
            replacer_last = r;
         }
         r->next = 0;
      }
      break;
   }
   default:
      printf("built in function #%u (case %u) not yet implemented\n", bc_offset + 1, bc_offset);
      exit(EXIT_FAILURE);
}
