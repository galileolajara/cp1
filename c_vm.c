#define vml_pop_mem vml_pop_i32
#define layer_limit 0x80
#define value_limit 0x800
#define local_limit 0x800
#define memory_limit 0x80000

union vm64 {
   int32_t i32;
   float f32;
};

struct vm_locals {
   uint16_t stack;
   uint16_t lvar;
   uint8_t* r;
   union vm64 value[value_limit];
   uint8_t memory[memory_limit];
};

void vml_push_i32(struct vm_locals* vml, int32_t i32) {
   vml->value[vml->stack++].i32 = i32;
}

int32_t vml_pop_i32(struct vm_locals* vml) {
   return vml->value[--vml->stack].i32;
}

void func_run(func_t f, struct vm_locals* vml) {
   vml->r = bytecode_v + func_bytecode_v[f];
   lvaridx_t func_arg_c = *(vml->r++);
   lvaridx_t func_lvar_c = *(vml->r++);
   vml->stack = func_arg_c + func_lvar_c;
   vml->lvar = 0;
   uint16_t layer_c = 0;
   uint16_t layer_stack_pos[layer_limit];
   uint16_t layer_lvar_pos[layer_limit];
   uint8_t* layer_code_pos[layer_limit];
   while (1) {
      uint8_t op = *(vml->r++);
      // printf("op: %u\n", op);
      switch (op) {
         case bc_return: {
            if (layer_c == 0) {
               return;
            } else {
               layer_c--;
               vml->stack = layer_stack_pos[layer_c];
               vml->lvar = layer_lvar_pos[layer_c];
               vml->r = layer_code_pos[layer_c];
            }
            break;
         }
         case bc_return_32: {
            int32_t i32 = vml_pop_i32(vml);
            if (layer_c == 0) {
               vml->value[0].i32 = i32;
               return;
            } else {
               layer_c--;
               vml->stack = layer_stack_pos[layer_c];
               vml->lvar = layer_lvar_pos[layer_c];
               vml->r = layer_code_pos[layer_c];
               vml_push_i32(vml, i32);
            }
            break;
         }
         case bc_push_32: {
            int32_t i32 = getint(&vml->r);
            // printf("push %d\n", i32);
            vml_push_i32(vml, i32);
            break;
         }
         case bc_push_call: {
            func_t f2 = getnum(&vml->r);
            int32_t bc_offset = func_bytecode_v[f2];
            if (bc_offset < 0) {
               bc_offset = -bc_offset - 1;
               // printf("call built-in function #%u\n", bc_offset);
               #include "runc-functions.c"
            } else {
               // printf("call function #%u @ %d\n", f2, bc_offset);
               uint8_t* r = vml->r;
               vml->r = bytecode_v + bc_offset;
               lvaridx_t call_arg_c = *(vml->r++);
               lvaridx_t call_lvar_c = *(vml->r++);
               layer_lvar_pos[layer_c] = vml->lvar;
               layer_stack_pos[layer_c] = vml->lvar = vml->stack - call_arg_c;
               vml->stack += call_lvar_c;
               layer_code_pos[layer_c] = r;
               layer_c++;
            }
            break;
         }
         case bc_push_lvar_32: {
            lvaridx_t idx = *(vml->r++);
            // printf("push lvar %u = %d\n", idx, vml->value[vml->lvar + idx].i32);
            vml_push_i32(vml, vml->value[vml->lvar + idx].i32);
            break;
         }
         case bc_add_i32: {
            int32_t b = vml_pop_i32(vml);
            int32_t a = vml_pop_i32(vml);
            // printf("%d + %d = %d\n", a, b, a + b);
            vml_push_i32(vml, a + b);
            break;
         }
         case bc_sub_i32: {
            int32_t b = vml_pop_i32(vml);
            int32_t a = vml_pop_i32(vml);
            // printf("%d - %d = %d\n", a, b, a - b);
            vml_push_i32(vml, a - b);
            break;
         }
         case bc_mul_i32: {
            int32_t b = vml_pop_i32(vml);
            int32_t a = vml_pop_i32(vml);
            // printf("%d * %d = %d\n", a, b, a * b);
            vml_push_i32(vml, a * b);
            break;
         }
         case bc_div_i32: {
            int32_t b = vml_pop_i32(vml);
            int32_t a = vml_pop_i32(vml);
            // printf("%d / %d = %d\n", a, b, a / b);
            vml_push_i32(vml, a / b);
            break;
         }
         case bc_lvar_set_32: {
            lvaridx_t idx = *(vml->r++);
            int32_t a = vml_pop_i32(vml);
            // printf("lvar_set_32: %d -> %u\n", a, idx);
            vml->value[vml->lvar + idx].i32 = a;
            break;
         }
         case bc_unaryop_lvar_32_postinc: {
            lvaridx_t idx = *(vml->r++);
            int32_t a = vml->value[vml->lvar + idx].i32;
            vml->value[vml->lvar + idx].i32 = a + 1;
            vml_push_i32(vml, a);
            break;
         }
         case bc_unaryop_lvar_32_preinc: {
            lvaridx_t idx = *(vml->r++);
            int32_t a = ++vml->value[vml->lvar + idx].i32;
            vml_push_i32(vml, a);
            break;
         }
         case bc_unaryop_lvar_32_postdec: {
            lvaridx_t idx = *(vml->r++);
            int32_t a = vml->value[vml->lvar + idx].i32;
            vml->value[vml->lvar + idx].i32 = a - 1;
            vml_push_i32(vml, a);
            break;
         }
         case bc_unaryop_lvar_32_predec: {
            lvaridx_t idx = *(vml->r++);
            int32_t a = --vml->value[vml->lvar + idx].i32;
            vml_push_i32(vml, a);
            break;
         }
         case bc_mem_set_8: {
            int32_t a = vml_pop_i32(vml);
            mem_t mem = getmem(&vml->r);
            vml->memory[mem] = a;
            break;
         }
         case bc_mem_push_8: {
            mem_t mem = getmem(&vml->r);
            vml_push_i32(vml, vml->memory[mem]);
            break;
         }
         case bc_push_addr: {
            vml_push_i32(vml, getmem(&vml->r));
            break;
         }
         case bc_if: {
            int32_t a = vml_pop_i32(vml);
            if (a != 0) {
               vml->r += 4;
            } else {
               vml->r += *(int32_t*)vml->r;
            }
            break;
         }
         case bc_jump: {
            vml->r += *(int32_t*)vml->r;
            break;
         }
         case bc_not: {
            int32_t a = vml_pop_i32(vml);
            vml_push_i32(vml, !a);
            break;
         }
         case bc_lt_i32: {
            int32_t b = vml_pop_i32(vml);
            int32_t a = vml_pop_i32(vml);
            // printf("%d < %d = %d\n", a, b, a < b);
            vml_push_i32(vml, a < b);
            break;
         }
         case bc_gt_i32: {
            int32_t b = vml_pop_i32(vml);
            int32_t a = vml_pop_i32(vml);
            // printf("%d > %d = %d\n", a, b, a > b);
            vml_push_i32(vml, a > b);
            break;
         }
         case bc_eq_i32: {
            int32_t b = vml_pop_i32(vml);
            int32_t a = vml_pop_i32(vml);
            // printf("%d == %d = %d\n", a, b, a == b);
            vml_push_i32(vml, a == b);
            break;
         }
         case bc_lteq_i32: {
            int32_t b = vml_pop_i32(vml);
            int32_t a = vml_pop_i32(vml);
            // printf("%d <= %d = %d\n", a, b, a <= b);
            vml_push_i32(vml, a <= b);
            break;
         }
         case bc_gteq_i32: {
            int32_t b = vml_pop_i32(vml);
            int32_t a = vml_pop_i32(vml);
            // printf("%d >= %d = %d\n", a, b, a >= b);
            vml_push_i32(vml, a >= b);
            break;
         }
         case bc_noteq_i32: {
            int32_t b = vml_pop_i32(vml);
            int32_t a = vml_pop_i32(vml);
            // printf("%d != %d = %d\n", a, b, a != b);
            vml_push_i32(vml, a != b);
            break;
         }
         case bc_mem_postinc_8: {
            mem_t mem = getmem(&vml->r);
            vml_push_i32(vml, vml->memory[mem]++);
            break;
         }
         case bc_mem_preinc_8: {
            mem_t mem = getmem(&vml->r);
            vml_push_i32(vml, ++vml->memory[mem]);
            break;
         }
         case bc_pop_32: {
            (void)vml_pop_i32(vml);
            break;
         }
         case bc_mem_postdec_8: {
            mem_t mem = getmem(&vml->r);
            vml_push_i32(vml, vml->memory[mem]--);
            break;
         }
         case bc_mem_predec_8: {
            mem_t mem = getmem(&vml->r);
            vml_push_i32(vml, --vml->memory[mem]);
            break;
         }
         case bc_and: {
            int32_t b = vml_pop_i32(vml);
            int32_t a = vml_pop_i32(vml);
            // printf("%d && %d = %d\n", a, b, a && b);
            vml_push_i32(vml, a && b);
            break;
         }
         case bc_or: {
            int32_t b = vml_pop_i32(vml);
            int32_t a = vml_pop_i32(vml);
            // printf("%d || %d = %d\n", a, b, a || b);
            vml_push_i32(vml, a || b);
            break;
         }
         default: {
            printf("unrecognized op: %u\n", op);
            exit(EXIT_FAILURE);
         }
      }
   }
}
