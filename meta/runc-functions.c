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
   default:
      printf("built in function #%u not yet implemented\n", bc_offset);
      exit(EXIT_FAILURE);
}
