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
            struct D_t* r = D_first;
            while (r != 0) {
               if (memcmp(r->keybuf, buf + i, r->keylen) == 0) {
                  break;
               }
               r = r->next;
            }
            if (r == 0) {
               output_buf[output_len++] = '$';
               output_buf[output_len++] = '{';
            } else {
               uint16_t vallen = r->vallen;
               memcpy(output_buf + output_len, r->valbuf, vallen);
               output_len += vallen;
               i += r->keylen + 1;
            }
         } else {
            output_buf[output_len++] = buf[i++];
         }
      }
      break;
   }
   case 3: {
      uint32_t vallen = vml_pop_i32(vml);
      mem_t valmem = vml_pop_mem(vml);
      char* valbuf = vml->memory + valmem;
      uint32_t keylen = vml_pop_i32(vml);
      mem_t keymem = vml_pop_mem(vml);
      char* keybuf = vml->memory + keymem;
      
      // check if keymem/keylen already exists
      struct D_t* r = D_first;
      bool allocate = true;
      while (r != 0) {
         if ((r->keylen == keylen) && (memcmp(r->keybuf, keybuf, keylen) == 0)) {
            allocate = false;
            break;
         }
         r = r->next;
      }

      if (allocate) {
         r = malloc(sizeof(struct D_t));
         memcpy(r->keybuf, keybuf, keylen);
         r->keylen = keylen;
      }
      memcpy(r->valbuf, valbuf, vallen);
      r->vallen = vallen;
      
      if (allocate) {
         if (D_last == 0) {
            D_last = D_first = r;
         } else {
            D_last->next = r;
            D_last = r;
         }
         r->next = 0;
      }
      break;
   }
   case 4: {
      uint32_t vallen = vml_pop_i32(vml);
      mem_t valmem = vml_pop_mem(vml);
      char* valbuf = vml->memory + valmem;
      uint32_t keylen = vml_pop_i32(vml);
      mem_t keymem = vml_pop_mem(vml);
      char* keybuf = vml->memory + keymem;
      
      struct D_t* r = D_first;
      bool found = false;
      while (r != 0) {
         if ((r->keylen == keylen) && (memcmp(r->keybuf, keybuf, keylen) == 0)) {
            found = true;
            break;
         }
         r = r->next;
      }

      vml_push_i32(vml, found && (vallen == r->vallen) && (memcmp(r->valbuf, valbuf, vallen) == 0) ? 1 : 0);
      break;
   }
   default:
      printf("built in function #%u (case %u) not yet implemented\n", bc_offset + 1, bc_offset);
      exit(EXIT_FAILURE);
}
