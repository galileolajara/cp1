struct pp_buf_t {
   uint8_t* v;
   uint32_t len;
   uint32_t cap;
};

#define pp_macro_limit 1024
#define pp_macro_param_limit 32
#define pp_expand_depth_limit 64
#define pp_cond_limit 128

struct pp_arg_t {
   uint8_t* buf;
   uint32_t len;
};

struct pp_macro_t {
   uint8_t* name;
   uint32_t name_len;
   bool function_like;
   uint8_t* param_v[pp_macro_param_limit];
   uint32_t param_len_v[pp_macro_param_limit];
   uint32_t param_c;
   uint8_t* body;
   uint32_t body_len;
};

struct pp_cond_t {
   bool parent_active;
   bool active;
   bool branch_taken;
   bool has_else;
};

bool pp_is_ident_start(uint8_t c) {
   return ((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')) || (c == '_');
}

bool pp_is_ident_char(uint8_t c) {
   return pp_is_ident_start(c) || ((c >= '0') && (c <= '9'));
}

void pp_buf_reserve(struct pp_buf_t* out, uint32_t add_len) {
   uint32_t need = out->len + add_len;
   if (need <= out->cap) {
      return;
   }
   uint32_t cap = out->cap == 0 ? 256 : out->cap;
   while (cap < need) {
      cap *= 2;
   }
   uint8_t* v = realloc(out->v, cap);
   if (v == NULL) {
      printf("Out of memory while preprocessing input\n");
      exit(EXIT_FAILURE);
   }
   out->v = v;
   out->cap = cap;
}

void pp_buf_push(struct pp_buf_t* out, uint8_t c) {
   pp_buf_reserve(out, 1);
   out->v[out->len++] = c;
}

void pp_buf_append(struct pp_buf_t* out, uint8_t* src, uint32_t len) {
   if (len == 0) {
      return;
   }
   pp_buf_reserve(out, len);
   memcpy(out->v + out->len, src, len);
   out->len += len;
}

uint8_t* pp_copy(uint8_t* src, uint32_t len) {
   uint8_t* dst = malloc(len + 1);
   if (dst == NULL) {
      printf("Out of memory while preprocessing input\n");
      exit(EXIT_FAILURE);
   }
   if (len != 0) {
      memcpy(dst, src, len);
   }
   dst[len] = 0;
   return dst;
}

void pp_trim_bounds(uint8_t* src, uint32_t len, uint32_t* begin, uint32_t* end) {
   uint32_t b = 0;
   uint32_t e = len;
   while ((b < e) && ((src[b] == ' ') || (src[b] == '\t'))) {
      b++;
   }
   while ((e > b) && ((src[e - 1] == ' ') || (src[e - 1] == '\t'))) {
      e--;
   }
   *begin = b;
   *end = e;
}

int32_t pp_macro_find(struct pp_macro_t* macro_v, uint32_t macro_c, uint8_t* name, uint32_t name_len) {
   for (int32_t i = (int32_t)macro_c - 1; i >= 0; i--) {
      if ((macro_v[i].name_len == name_len) && (memcmp(macro_v[i].name, name, name_len) == 0)) {
         return i;
      }
   }
   return -1;
}

int32_t pp_param_find(struct pp_macro_t* macro, uint8_t* name, uint32_t name_len) {
   for (uint32_t i = 0; i < macro->param_c; i++) {
      if ((macro->param_len_v[i] == name_len) && (memcmp(macro->param_v[i], name, name_len) == 0)) {
         return i;
      }
   }
   return -1;
}

uint32_t pp_skip_quote(uint8_t* src, uint32_t len, uint32_t i, uint8_t quote) {
   i++;
   while (i < len) {
      if ((src[i] == '\\') && ((i + 1) < len)) {
         i += 2;
         continue;
      }
      if (src[i] == quote) {
         i++;
         break;
      }
      i++;
   }
   return i;
}

uint32_t pp_skip_block_comment(uint8_t* src, uint32_t len, uint32_t i) {
   i += 2;
   while (i + 1 < len) {
      if ((src[i] == '*') && (src[i + 1] == '/')) {
         i += 2;
         return i;
      }
      i++;
   }
   return len;
}

void pp_args_free(struct pp_arg_t* arg_v, uint32_t arg_c) {
   for (uint32_t i = 0; i < arg_c; i++) {
      free(arg_v[i].buf);
   }
}

bool pp_parse_call_args(uint8_t* src, uint32_t len, uint32_t open_paren_i, struct pp_arg_t* arg_v, uint32_t* arg_c, uint32_t* end_i) {
   if ((open_paren_i >= len) || (src[open_paren_i] != '(')) {
      return false;
   }
   uint32_t depth = 1;
   uint32_t start = open_paren_i + 1;
   uint32_t c = 0;
   uint32_t i = start;
   while (i < len) {
      uint8_t ch = src[i];
      if ((ch == '"') || (ch == '\'')) {
         i = pp_skip_quote(src, len, i, ch);
         continue;
      }
      if ((ch == '/') && ((i + 1) < len)) {
         if (src[i + 1] == '/') {
            i = len;
            break;
         }
         if (src[i + 1] == '*') {
            i = pp_skip_block_comment(src, len, i);
            continue;
         }
      }
      if (ch == '(') {
         depth++;
         i++;
         continue;
      }
      if (ch == ')') {
         if (depth == 1) {
            uint32_t b = 0;
            uint32_t e = 0;
            pp_trim_bounds(src + start, i - start, &b, &e);
            if ((c != 0) || (e != b)) {
               if (c >= pp_macro_param_limit) {
                  pp_args_free(arg_v, c);
                  return false;
               }
               arg_v[c].buf = pp_copy(src + start + b, e - b);
               arg_v[c].len = e - b;
               c++;
            }
            *arg_c = c;
            *end_i = i + 1;
            return true;
         }
         depth--;
         i++;
         continue;
      }
      if ((ch == ',') && (depth == 1)) {
         if (c >= pp_macro_param_limit) {
            pp_args_free(arg_v, c);
            return false;
         }
         uint32_t b = 0;
         uint32_t e = 0;
         pp_trim_bounds(src + start, i - start, &b, &e);
         arg_v[c].buf = pp_copy(src + start + b, e - b);
         arg_v[c].len = e - b;
         c++;
         start = i + 1;
         i++;
         continue;
      }
      i++;
   }
   pp_args_free(arg_v, c);
   return false;
}

bool pp_parse_define_line(uint8_t* line, uint32_t len, struct pp_macro_t* macro_v, uint32_t* macro_c, uint32_t row) {
   uint32_t i = 0;
   while ((i < len) && ((line[i] == ' ') || (line[i] == '\t'))) {
      i++;
   }
   if ((i >= len) || (line[i] != '#')) {
      return false;
   }
   i++;
   while ((i < len) && ((line[i] == ' ') || (line[i] == '\t'))) {
      i++;
   }
   static const uint8_t define_str[] = "define";
   if (((len - i) < 6) || (memcmp(line + i, define_str, 6) != 0)) {
      return false;
   }
   i += 6;
   if ((i < len) && pp_is_ident_char(line[i])) {
      return false;
   }
   while ((i < len) && ((line[i] == ' ') || (line[i] == '\t'))) {
      i++;
   }
   if ((i >= len) || !pp_is_ident_start(line[i])) {
      printf("%s:%u:1: invalid #define, expected macro name\n", input_path, row);
      exit(EXIT_FAILURE);
   }
   uint32_t name_begin = i;
   i++;
   while ((i < len) && pp_is_ident_char(line[i])) {
      i++;
   }
   uint32_t name_len = i - name_begin;
   bool function_like = false;
   uint8_t* param_v[pp_macro_param_limit];
   uint32_t param_len_v[pp_macro_param_limit];
   uint32_t param_c = 0;
   if ((i < len) && (line[i] == '(')) {
      function_like = true;
      i++;
      while ((i < len) && ((line[i] == ' ') || (line[i] == '\t'))) {
         i++;
      }
      if ((i < len) && (line[i] == ')')) {
         i++;
      } else {
         while (1) {
            if ((i >= len) || !pp_is_ident_start(line[i])) {
               printf("%s:%u:1: invalid #define parameter list\n", input_path, row);
               exit(EXIT_FAILURE);
            }
            if (param_c >= pp_macro_param_limit) {
               printf("%s:%u:1: too many macro parameters (limit %u)\n", input_path, row, pp_macro_param_limit);
               exit(EXIT_FAILURE);
            }
            uint32_t p_begin = i;
            i++;
            while ((i < len) && pp_is_ident_char(line[i])) {
               i++;
            }
            param_v[param_c] = pp_copy(line + p_begin, i - p_begin);
            param_len_v[param_c] = i - p_begin;
            param_c++;
            while ((i < len) && ((line[i] == ' ') || (line[i] == '\t'))) {
               i++;
            }
            if ((i < len) && (line[i] == ',')) {
               i++;
               while ((i < len) && ((line[i] == ' ') || (line[i] == '\t'))) {
                  i++;
               }
               continue;
            }
            if ((i < len) && (line[i] == ')')) {
               i++;
               break;
            }
            printf("%s:%u:1: invalid #define parameter list\n", input_path, row);
            exit(EXIT_FAILURE);
         }
      }
   }
   while ((i < len) && ((line[i] == ' ') || (line[i] == '\t'))) {
      i++;
   }
   uint8_t* body = pp_copy(line + i, len - i);
   uint32_t body_len = len - i;
   int32_t idx = pp_macro_find(macro_v, *macro_c, line + name_begin, name_len);
   if (idx < 0) {
      if (*macro_c >= pp_macro_limit) {
         printf("%s:%u:1: too many macros (limit %u)\n", input_path, row, pp_macro_limit);
         exit(EXIT_FAILURE);
      }
      idx = (*macro_c)++;
   }
   struct pp_macro_t* macro = &macro_v[idx];
   macro->name = pp_copy(line + name_begin, name_len);
   macro->name_len = name_len;
   macro->function_like = function_like;
   macro->param_c = param_c;
   for (uint32_t p = 0; p < param_c; p++) {
      macro->param_v[p] = param_v[p];
      macro->param_len_v[p] = param_len_v[p];
   }
   macro->body = body;
   macro->body_len = body_len;
   return true;
}

bool pp_macro_disabled(const struct pp_macro_t* macro, const struct pp_macro_t** stack_v, uint32_t stack_c) {
   for (uint32_t i = 0; i < stack_c; i++) {
      if (stack_v[i] == macro) {
         return true;
      }
   }
   return false;
}

void pp_substitute_body(struct pp_macro_t* macro, struct pp_arg_t* arg_v, uint32_t arg_c, struct pp_buf_t* out) {
   uint32_t i = 0;
   uint8_t* src = macro->body;
   uint32_t len = macro->body_len;
   while (i < len) {
      uint8_t ch = src[i];
      if ((ch == '"') || (ch == '\'')) {
         uint32_t j = pp_skip_quote(src, len, i, ch);
         pp_buf_append(out, src + i, j - i);
         i = j;
         continue;
      }
      if ((ch == '/') && ((i + 1) < len)) {
         if (src[i + 1] == '/') {
            pp_buf_append(out, src + i, len - i);
            return;
         }
         if (src[i + 1] == '*') {
            uint32_t j = pp_skip_block_comment(src, len, i);
            pp_buf_append(out, src + i, j - i);
            i = j;
            continue;
         }
      }
      if (pp_is_ident_start(ch)) {
         uint32_t j = i + 1;
         while ((j < len) && pp_is_ident_char(src[j])) {
            j++;
         }
         int32_t p = pp_param_find(macro, src + i, j - i);
         if (p >= 0) {
            if ((uint32_t)p >= arg_c) {
               printf("Internal preprocessor error while substituting macro arguments\n");
               exit(EXIT_FAILURE);
            }
            pp_buf_append(out, arg_v[p].buf, arg_v[p].len);
         } else {
            pp_buf_append(out, src + i, j - i);
         }
         i = j;
         continue;
      }
      pp_buf_push(out, ch);
      i++;
   }
}

void pp_expand_text(struct pp_macro_t* macro_v, uint32_t macro_c, uint8_t* src, uint32_t len, struct pp_buf_t* out, const struct pp_macro_t** stack_v, uint32_t stack_c, uint32_t row) {
   if (stack_c >= pp_expand_depth_limit) {
      printf("%s:%u:1: macro expansion depth exceeded limit (%u)\n", input_path, row, pp_expand_depth_limit);
      exit(EXIT_FAILURE);
   }
   uint32_t i = 0;
   while (i < len) {
      uint8_t ch = src[i];
      if ((ch == '"') || (ch == '\'')) {
         uint32_t j = pp_skip_quote(src, len, i, ch);
         pp_buf_append(out, src + i, j - i);
         i = j;
         continue;
      }
      if ((ch == '/') && ((i + 1) < len)) {
         if (src[i + 1] == '/') {
            pp_buf_append(out, src + i, len - i);
            return;
         }
         if (src[i + 1] == '*') {
            uint32_t j = pp_skip_block_comment(src, len, i);
            pp_buf_append(out, src + i, j - i);
            i = j;
            continue;
         }
      }
      if (pp_is_ident_start(ch)) {
         uint32_t j = i + 1;
         while ((j < len) && pp_is_ident_char(src[j])) {
            j++;
         }
         int32_t m = pp_macro_find(macro_v, macro_c, src + i, j - i);
         if (m >= 0) {
            struct pp_macro_t* macro = &macro_v[m];
            if (!pp_macro_disabled(macro, stack_v, stack_c)) {
               const struct pp_macro_t* stack2[pp_expand_depth_limit];
               memcpy(stack2, stack_v, stack_c * sizeof(stack_v[0]));
               stack2[stack_c] = macro;
               if (!macro->function_like) {
                  pp_expand_text(macro_v, macro_c, macro->body, macro->body_len, out, stack2, stack_c + 1, row);
                  i = j;
                  continue;
               }
               uint32_t k = j;
               while ((k < len) && ((src[k] == ' ') || (src[k] == '\t'))) {
                  k++;
               }
               if ((k < len) && (src[k] == '(')) {
                  struct pp_arg_t raw_arg_v[pp_macro_param_limit];
                  uint32_t raw_arg_c = 0;
                  uint32_t call_end = 0;
                  if (!pp_parse_call_args(src, len, k, raw_arg_v, &raw_arg_c, &call_end)) {
                     printf("%s:%u:%u: invalid macro call for '%.*s'\n", input_path, row, i + 1, macro->name_len, macro->name);
                     exit(EXIT_FAILURE);
                  }
                  if (raw_arg_c != macro->param_c) {
                     printf("%s:%u:%u: macro '%.*s' expects %u arguments but got %u\n", input_path, row, i + 1, macro->name_len, macro->name, macro->param_c, raw_arg_c);
                     exit(EXIT_FAILURE);
                  }
                  struct pp_arg_t exp_arg_v[pp_macro_param_limit];
                  for (uint32_t a = 0; a < raw_arg_c; a++) {
                     struct pp_buf_t arg_out = {0};
                     pp_expand_text(macro_v, macro_c, raw_arg_v[a].buf, raw_arg_v[a].len, &arg_out, stack_v, stack_c, row);
                     pp_buf_push(&arg_out, 0);
                     exp_arg_v[a].buf = arg_out.v;
                     exp_arg_v[a].len = arg_out.len - 1;
                  }
                  struct pp_buf_t body_out = {0};
                  pp_substitute_body(macro, exp_arg_v, raw_arg_c, &body_out);
                  pp_expand_text(macro_v, macro_c, body_out.v, body_out.len, out, stack2, stack_c + 1, row);
                  pp_args_free(raw_arg_v, raw_arg_c);
                  pp_args_free(exp_arg_v, raw_arg_c);
                  free(body_out.v);
                  i = call_end;
                  continue;
               }
            }
         }
         pp_buf_append(out, src + i, j - i);
         i = j;
         continue;
      }
      pp_buf_push(out, ch);
      i++;
   }
}

bool pp_is_space_tab(uint8_t c) {
   return (c == ' ') || (c == '\t');
}

bool pp_is_digit(uint8_t c) {
   return (c >= '0') && (c <= '9');
}

bool pp_is_hex_digit(uint8_t c) {
   return pp_is_digit(c) || ((c >= 'a') && (c <= 'f')) || ((c >= 'A') && (c <= 'F'));
}

bool pp_name_eq(uint8_t* name, uint32_t name_len, const char* lit) {
   uint32_t lit_len = strlen(lit);
   return (name_len == lit_len) && (memcmp(name, lit, lit_len) == 0);
}

bool pp_parse_directive(uint8_t* line, uint32_t len, uint32_t* name_begin, uint32_t* name_len, uint32_t* arg_begin) {
   uint32_t i = 0;
   while ((i < len) && pp_is_space_tab(line[i])) {
      i++;
   }
   if ((i >= len) || (line[i] != '#')) {
      return false;
   }
   i++;
   while ((i < len) && pp_is_space_tab(line[i])) {
      i++;
   }
   *name_begin = i;
   if ((i >= len) || !pp_is_ident_start(line[i])) {
      *name_len = 0;
      *arg_begin = i;
      return true;
   }
   i++;
   while ((i < len) && pp_is_ident_char(line[i])) {
      i++;
   }
   *name_len = i - *name_begin;
   *arg_begin = i;
   return true;
}

bool pp_parse_directive_ident_arg(uint8_t* line, uint32_t len, uint32_t arg_begin, uint32_t* ident_begin, uint32_t* ident_len) {
   uint32_t i = arg_begin;
   while ((i < len) && pp_is_space_tab(line[i])) {
      i++;
   }
   if ((i >= len) || !pp_is_ident_start(line[i])) {
      return false;
   }
   uint32_t begin = i;
   i++;
   while ((i < len) && pp_is_ident_char(line[i])) {
      i++;
   }
   uint32_t id_len = i - begin;
   while ((i < len) && pp_is_space_tab(line[i])) {
      i++;
   }
   if (i < len) {
      if ((line[i] != '/') || ((i + 1) >= len) || ((line[i + 1] != '/') && (line[i + 1] != '*'))) {
         return false;
      }
   }
   *ident_begin = begin;
   *ident_len = id_len;
   return true;
}

bool pp_directive_tail_is_empty_or_comment(uint8_t* line, uint32_t len, uint32_t arg_begin) {
   uint32_t i = arg_begin;
   while ((i < len) && pp_is_space_tab(line[i])) {
      i++;
   }
   if (i >= len) {
      return true;
   }
   return (line[i] == '/') && ((i + 1) < len) && ((line[i + 1] == '/') || (line[i + 1] == '*'));
}

bool pp_cond_is_active(struct pp_cond_t* cond_v, uint32_t cond_c) {
   return (cond_c == 0) || cond_v[cond_c - 1].active;
}

void pp_if_expr_error(uint32_t row, const char* msg) {
   printf("%s:%u:1: invalid #if expression: %s\n", input_path, row, msg);
   exit(EXIT_FAILURE);
}

void pp_expand_if_text(struct pp_macro_t* macro_v, uint32_t macro_c, uint8_t* src, uint32_t len, struct pp_buf_t* out, const struct pp_macro_t** stack_v, uint32_t stack_c, uint32_t row) {
   if (stack_c >= pp_expand_depth_limit) {
      printf("%s:%u:1: macro expansion depth exceeded limit (%u)\n", input_path, row, pp_expand_depth_limit);
      exit(EXIT_FAILURE);
   }
   uint32_t i = 0;
   while (i < len) {
      uint8_t ch = src[i];
      if ((ch == '"') || (ch == '\'')) {
         uint32_t j = pp_skip_quote(src, len, i, ch);
         pp_buf_append(out, src + i, j - i);
         i = j;
         continue;
      }
      if ((ch == '/') && ((i + 1) < len)) {
         if (src[i + 1] == '/') {
            return;
         }
         if (src[i + 1] == '*') {
            i = pp_skip_block_comment(src, len, i);
            pp_buf_push(out, ' ');
            continue;
         }
      }
      if (pp_is_ident_start(ch)) {
         uint32_t j = i + 1;
         while ((j < len) && pp_is_ident_char(src[j])) {
            j++;
         }
         if (((j - i) == 7) && (memcmp(src + i, "defined", 7) == 0)) {
            uint32_t k = j;
            while ((k < len) && pp_is_space_tab(src[k])) {
               k++;
            }
            bool with_paren = false;
            if ((k < len) && (src[k] == '(')) {
               with_paren = true;
               k++;
               while ((k < len) && pp_is_space_tab(src[k])) {
                  k++;
               }
            }
            if ((k >= len) || !pp_is_ident_start(src[k])) {
               pp_if_expr_error(row, "expected identifier after defined");
            }
            uint32_t name_begin = k;
            k++;
            while ((k < len) && pp_is_ident_char(src[k])) {
               k++;
            }
            uint32_t name_len = k - name_begin;
            while ((k < len) && pp_is_space_tab(src[k])) {
               k++;
            }
            if (with_paren) {
               if ((k >= len) || (src[k] != ')')) {
                  pp_if_expr_error(row, "expected ')' after defined(identifier)");
               }
               k++;
            }
            bool is_defined = pp_macro_find(macro_v, macro_c, src + name_begin, name_len) >= 0;
            pp_buf_push(out, is_defined ? '1' : '0');
            i = k;
            continue;
         }
         int32_t m = pp_macro_find(macro_v, macro_c, src + i, j - i);
         if (m >= 0) {
            struct pp_macro_t* macro = &macro_v[m];
            if (!pp_macro_disabled(macro, stack_v, stack_c)) {
               const struct pp_macro_t* stack2[pp_expand_depth_limit];
               memcpy(stack2, stack_v, stack_c * sizeof(stack_v[0]));
               stack2[stack_c] = macro;
               if (!macro->function_like) {
                  pp_expand_if_text(macro_v, macro_c, macro->body, macro->body_len, out, stack2, stack_c + 1, row);
                  i = j;
                  continue;
               }
               uint32_t k = j;
               while ((k < len) && pp_is_space_tab(src[k])) {
                  k++;
               }
               if ((k < len) && (src[k] == '(')) {
                  struct pp_arg_t raw_arg_v[pp_macro_param_limit];
                  uint32_t raw_arg_c = 0;
                  uint32_t call_end = 0;
                  if (!pp_parse_call_args(src, len, k, raw_arg_v, &raw_arg_c, &call_end)) {
                     printf("%s:%u:%u: invalid macro call for '%.*s'\n", input_path, row, i + 1, macro->name_len, macro->name);
                     exit(EXIT_FAILURE);
                  }
                  if (raw_arg_c != macro->param_c) {
                     printf("%s:%u:%u: macro '%.*s' expects %u arguments but got %u\n", input_path, row, i + 1, macro->name_len, macro->name, macro->param_c, raw_arg_c);
                     exit(EXIT_FAILURE);
                  }
                  struct pp_arg_t exp_arg_v[pp_macro_param_limit];
                  for (uint32_t a = 0; a < raw_arg_c; a++) {
                     struct pp_buf_t arg_out = {0};
                     pp_expand_if_text(macro_v, macro_c, raw_arg_v[a].buf, raw_arg_v[a].len, &arg_out, stack_v, stack_c, row);
                     pp_buf_push(&arg_out, 0);
                     exp_arg_v[a].buf = arg_out.v;
                     exp_arg_v[a].len = arg_out.len - 1;
                  }
                  struct pp_buf_t body_out = {0};
                  pp_substitute_body(macro, exp_arg_v, raw_arg_c, &body_out);
                  pp_expand_if_text(macro_v, macro_c, body_out.v, body_out.len, out, stack2, stack_c + 1, row);
                  pp_args_free(raw_arg_v, raw_arg_c);
                  pp_args_free(exp_arg_v, raw_arg_c);
                  free(body_out.v);
                  i = call_end;
                  continue;
               }
            }
         }
         pp_buf_append(out, src + i, j - i);
         i = j;
         continue;
      }
      pp_buf_push(out, ch);
      i++;
   }
}

struct pp_expr_parser_t {
   uint8_t* src;
   uint32_t len;
   uint32_t i;
   uint32_t row;
};

void pp_expr_skip_ws(struct pp_expr_parser_t* p) {
   while ((p->i < p->len) && pp_is_space_tab(p->src[p->i])) {
      p->i++;
   }
}

bool pp_expr_take(struct pp_expr_parser_t* p, const char* op) {
   uint32_t op_len = strlen(op);
   if ((p->i + op_len) > p->len) {
      return false;
   }
   if (memcmp(p->src + p->i, op, op_len) != 0) {
      return false;
   }
   p->i += op_len;
   return true;
}

int64_t pp_expr_parse_conditional(struct pp_expr_parser_t* p);

int64_t pp_expr_parse_number(struct pp_expr_parser_t* p) {
   uint32_t start = p->i;
   if ((p->src[p->i] == '0') && ((p->i + 1) < p->len) && ((p->src[p->i + 1] == 'x') || (p->src[p->i + 1] == 'X'))) {
      p->i += 2;
      uint32_t hex_start = p->i;
      while ((p->i < p->len) && pp_is_hex_digit(p->src[p->i])) {
         p->i++;
      }
      if (p->i == hex_start) {
         pp_if_expr_error(p->row, "hex literal requires at least one hex digit");
      }
   } else {
      while ((p->i < p->len) && pp_is_digit(p->src[p->i])) {
         p->i++;
      }
      if (p->i == start) {
         pp_if_expr_error(p->row, "expected integer literal");
      }
   }
   uint32_t num_end = p->i;
   while ((p->i < p->len) && ((p->src[p->i] == 'u') || (p->src[p->i] == 'U') || (p->src[p->i] == 'l') || (p->src[p->i] == 'L'))) {
      p->i++;
   }
   uint8_t* num = pp_copy(p->src + start, num_end - start);
   char* end = NULL;
   long long v = strtoll((char*)num, &end, 0);
   if ((uint32_t)(end - (char*)num) != (num_end - start)) {
      free(num);
      pp_if_expr_error(p->row, "invalid integer literal");
   }
   free(num);
   return v;
}

int64_t pp_expr_parse_char_escape(struct pp_expr_parser_t* p) {
   if (p->i >= p->len) {
      pp_if_expr_error(p->row, "incomplete escape sequence");
   }
   uint8_t c = p->src[p->i++];
   switch (c) {
      case 'n': return '\n';
      case 't': return '\t';
      case 'r': return '\r';
      case '\\': return '\\';
      case '\'': return '\'';
      case '"': return '"';
      case '0': return 0;
      case 'x': {
         if ((p->i >= p->len) || !pp_is_hex_digit(p->src[p->i])) {
            pp_if_expr_error(p->row, "expected hex digits after \\x");
         }
         int64_t v = 0;
         while ((p->i < p->len) && pp_is_hex_digit(p->src[p->i])) {
            uint8_t h = p->src[p->i++];
            v <<= 4;
            if ((h >= '0') && (h <= '9')) {
               v += h - '0';
            } else if ((h >= 'a') && (h <= 'f')) {
               v += 10 + (h - 'a');
            } else {
               v += 10 + (h - 'A');
            }
         }
         return v;
      }
      default: {
         if ((c >= '0') && (c <= '7')) {
            int64_t v = c - '0';
            uint32_t count = 1;
            while ((count < 3) && (p->i < p->len) && (p->src[p->i] >= '0') && (p->src[p->i] <= '7')) {
               v = (v << 3) + (p->src[p->i++] - '0');
               count++;
            }
            return v;
         }
         return c;
      }
   }
}

int64_t pp_expr_parse_char_literal(struct pp_expr_parser_t* p) {
   p->i++;
   if (p->i >= p->len) {
      pp_if_expr_error(p->row, "unterminated character literal");
   }
   int64_t v = 0;
   if (p->src[p->i] == '\\') {
      p->i++;
      v = pp_expr_parse_char_escape(p);
   } else {
      v = p->src[p->i++];
   }
   if ((p->i >= p->len) || (p->src[p->i] != '\'')) {
      pp_if_expr_error(p->row, "unterminated character literal");
   }
   p->i++;
   return v;
}

int64_t pp_expr_parse_primary(struct pp_expr_parser_t* p) {
   pp_expr_skip_ws(p);
   if (p->i >= p->len) {
      pp_if_expr_error(p->row, "unexpected end of expression");
   }
   if (p->src[p->i] == '(') {
      p->i++;
      int64_t v = pp_expr_parse_conditional(p);
      pp_expr_skip_ws(p);
      if (!pp_expr_take(p, ")")) {
         pp_if_expr_error(p->row, "expected ')'");
      }
      return v;
   }
   if (p->src[p->i] == '\'') {
      return pp_expr_parse_char_literal(p);
   }
   if (pp_is_digit(p->src[p->i])) {
      return pp_expr_parse_number(p);
   }
   if (pp_is_ident_start(p->src[p->i])) {
      p->i++;
      while ((p->i < p->len) && pp_is_ident_char(p->src[p->i])) {
         p->i++;
      }
      return 0;
   }
   pp_if_expr_error(p->row, "unexpected token");
   return 0;
}

int64_t pp_expr_parse_unary(struct pp_expr_parser_t* p) {
   pp_expr_skip_ws(p);
   if (pp_expr_take(p, "+")) {
      return +pp_expr_parse_unary(p);
   }
   if (pp_expr_take(p, "-")) {
      return -pp_expr_parse_unary(p);
   }
   if (pp_expr_take(p, "!")) {
      return !pp_expr_parse_unary(p);
   }
   if (pp_expr_take(p, "~")) {
      return ~pp_expr_parse_unary(p);
   }
   return pp_expr_parse_primary(p);
}

int64_t pp_expr_parse_mul(struct pp_expr_parser_t* p) {
   int64_t v = pp_expr_parse_unary(p);
   for (;;) {
      pp_expr_skip_ws(p);
      if (pp_expr_take(p, "*")) {
         v *= pp_expr_parse_unary(p);
         continue;
      }
      if (pp_expr_take(p, "/")) {
         int64_t rhs = pp_expr_parse_unary(p);
         v = (rhs == 0) ? 0 : (v / rhs);
         continue;
      }
      if (pp_expr_take(p, "%")) {
         int64_t rhs = pp_expr_parse_unary(p);
         v = (rhs == 0) ? 0 : (v % rhs);
         continue;
      }
      break;
   }
   return v;
}

int64_t pp_expr_parse_add(struct pp_expr_parser_t* p) {
   int64_t v = pp_expr_parse_mul(p);
   for (;;) {
      pp_expr_skip_ws(p);
      if (pp_expr_take(p, "+")) {
         v += pp_expr_parse_mul(p);
         continue;
      }
      if (pp_expr_take(p, "-")) {
         v -= pp_expr_parse_mul(p);
         continue;
      }
      break;
   }
   return v;
}

int64_t pp_expr_parse_shift(struct pp_expr_parser_t* p) {
   int64_t v = pp_expr_parse_add(p);
   for (;;) {
      pp_expr_skip_ws(p);
      if (pp_expr_take(p, "<<")) {
         v <<= pp_expr_parse_add(p);
         continue;
      }
      if (pp_expr_take(p, ">>")) {
         v >>= pp_expr_parse_add(p);
         continue;
      }
      break;
   }
   return v;
}

int64_t pp_expr_parse_rel(struct pp_expr_parser_t* p) {
   int64_t v = pp_expr_parse_shift(p);
   for (;;) {
      pp_expr_skip_ws(p);
      if (pp_expr_take(p, "<=")) {
         v = v <= pp_expr_parse_shift(p);
         continue;
      }
      if (pp_expr_take(p, ">=")) {
         v = v >= pp_expr_parse_shift(p);
         continue;
      }
      if (pp_expr_take(p, "<")) {
         v = v < pp_expr_parse_shift(p);
         continue;
      }
      if (pp_expr_take(p, ">")) {
         v = v > pp_expr_parse_shift(p);
         continue;
      }
      break;
   }
   return v;
}

int64_t pp_expr_parse_eq(struct pp_expr_parser_t* p) {
   int64_t v = pp_expr_parse_rel(p);
   for (;;) {
      pp_expr_skip_ws(p);
      if (pp_expr_take(p, "==")) {
         v = v == pp_expr_parse_rel(p);
         continue;
      }
      if (pp_expr_take(p, "!=")) {
         v = v != pp_expr_parse_rel(p);
         continue;
      }
      break;
   }
   return v;
}

int64_t pp_expr_parse_bitand(struct pp_expr_parser_t* p) {
   int64_t v = pp_expr_parse_eq(p);
   for (;;) {
      pp_expr_skip_ws(p);
      if ((p->i + 1 < p->len) && (p->src[p->i] == '&') && (p->src[p->i + 1] == '&')) {
         break;
      }
      if (!pp_expr_take(p, "&")) {
         break;
      }
      v &= pp_expr_parse_eq(p);
   }
   return v;
}

int64_t pp_expr_parse_bitxor(struct pp_expr_parser_t* p) {
   int64_t v = pp_expr_parse_bitand(p);
   for (;;) {
      pp_expr_skip_ws(p);
      if (!pp_expr_take(p, "^")) {
         break;
      }
      v ^= pp_expr_parse_bitand(p);
   }
   return v;
}

int64_t pp_expr_parse_bitor(struct pp_expr_parser_t* p) {
   int64_t v = pp_expr_parse_bitxor(p);
   for (;;) {
      pp_expr_skip_ws(p);
      if ((p->i + 1 < p->len) && (p->src[p->i] == '|') && (p->src[p->i + 1] == '|')) {
         break;
      }
      if (!pp_expr_take(p, "|")) {
         break;
      }
      v |= pp_expr_parse_bitxor(p);
   }
   return v;
}

int64_t pp_expr_parse_land(struct pp_expr_parser_t* p) {
   int64_t v = pp_expr_parse_bitor(p);
   for (;;) {
      pp_expr_skip_ws(p);
      if (!pp_expr_take(p, "&&")) {
         break;
      }
      v = (v && pp_expr_parse_bitor(p)) ? 1 : 0;
   }
   return v;
}

int64_t pp_expr_parse_lor(struct pp_expr_parser_t* p) {
   int64_t v = pp_expr_parse_land(p);
   for (;;) {
      pp_expr_skip_ws(p);
      if (!pp_expr_take(p, "||")) {
         break;
      }
      v = (v || pp_expr_parse_land(p)) ? 1 : 0;
   }
   return v;
}

int64_t pp_expr_parse_conditional(struct pp_expr_parser_t* p) {
   int64_t v = pp_expr_parse_lor(p);
   pp_expr_skip_ws(p);
   if (pp_expr_take(p, "?")) {
      int64_t a = pp_expr_parse_conditional(p);
      pp_expr_skip_ws(p);
      if (!pp_expr_take(p, ":")) {
         pp_if_expr_error(p->row, "expected ':' in conditional expression");
      }
      int64_t b = pp_expr_parse_conditional(p);
      return v ? a : b;
   }
   return v;
}

int64_t pp_eval_if_expr_expanded(uint8_t* expr, uint32_t len, uint32_t row) {
   struct pp_expr_parser_t parser = {
      .src = expr,
      .len = len,
      .i = 0,
      .row = row,
   };
   int64_t v = pp_expr_parse_conditional(&parser);
   pp_expr_skip_ws(&parser);
   if (parser.i != parser.len) {
      pp_if_expr_error(row, "unexpected trailing tokens");
   }
   return v;
}

bool pp_eval_if_expr(struct pp_macro_t* macro_v, uint32_t macro_c, uint8_t* expr, uint32_t expr_len, uint32_t row) {
   struct pp_buf_t expanded = {0};
   const struct pp_macro_t* stack_v[pp_expand_depth_limit];
   pp_expand_if_text(macro_v, macro_c, expr, expr_len, &expanded, stack_v, 0, row);
   pp_buf_push(&expanded, 0);
   int64_t v = pp_eval_if_expr_expanded(expanded.v, expanded.len - 1, row);
   free(expanded.v);
   return v != 0;
}

uint8_t* preprocess(uint8_t* data, uint32_t size) {
   struct pp_macro_t macro_v[pp_macro_limit];
   uint32_t macro_c = 0;
   struct pp_cond_t cond_v[pp_cond_limit];
   uint32_t cond_c = 0;
   struct pp_buf_t out = {0};
   uint32_t i = 0;
   uint32_t row = 1;
   while (i < size) {
      uint32_t line_begin = i;
      while ((i < size) && (data[i] != '\n')) {
         i++;
      }
      uint32_t line_end = i;
      bool has_newline = (i < size) && (data[i] == '\n');
      uint8_t* line = data + line_begin;
      uint32_t line_len = line_end - line_begin;

      uint32_t trim_b = 0;
      while ((trim_b < line_len) && pp_is_space_tab(line[trim_b])) {
         trim_b++;
      }
      bool is_pp_line = (trim_b < line_len) && (line[trim_b] == '#');
      bool line_active = pp_cond_is_active(cond_v, cond_c);
      if (is_pp_line) {
         uint32_t name_begin = 0;
         uint32_t name_len = 0;
         uint32_t arg_begin = 0;
         pp_parse_directive(line, line_len, &name_begin, &name_len, &arg_begin);
         uint8_t* name = line + name_begin;

         if (pp_name_eq(name, name_len, "if")) {
            if (cond_c >= pp_cond_limit) {
               printf("%s:%u:1: preprocessor conditional nesting exceeded limit (%u)\n", input_path, row, pp_cond_limit);
               exit(EXIT_FAILURE);
            }
            bool cond = false;
            if (line_active) {
               cond = pp_eval_if_expr(macro_v, macro_c, line + arg_begin, line_len - arg_begin, row);
            }
            cond_v[cond_c].parent_active = line_active;
            cond_v[cond_c].active = line_active && cond;
            cond_v[cond_c].branch_taken = cond;
            cond_v[cond_c].has_else = false;
            cond_c++;
         } else if (pp_name_eq(name, name_len, "ifdef") || pp_name_eq(name, name_len, "ifndef")) {
            if (cond_c >= pp_cond_limit) {
               printf("%s:%u:1: preprocessor conditional nesting exceeded limit (%u)\n", input_path, row, pp_cond_limit);
               exit(EXIT_FAILURE);
            }
            uint32_t ident_begin = 0;
            uint32_t ident_len = 0;
            if (!pp_parse_directive_ident_arg(line, line_len, arg_begin, &ident_begin, &ident_len)) {
               printf("%s:%u:1: expected identifier after #%.*s\n", input_path, row, name_len, name);
               exit(EXIT_FAILURE);
            }
            bool cond = pp_macro_find(macro_v, macro_c, line + ident_begin, ident_len) >= 0;
            if (pp_name_eq(name, name_len, "ifndef")) {
               cond = !cond;
            }
            cond_v[cond_c].parent_active = line_active;
            cond_v[cond_c].active = line_active && cond;
            cond_v[cond_c].branch_taken = cond;
            cond_v[cond_c].has_else = false;
            cond_c++;
         } else if (pp_name_eq(name, name_len, "elif")) {
            if (cond_c == 0) {
               printf("%s:%u:1: #elif without matching #if\n", input_path, row);
               exit(EXIT_FAILURE);
            }
            struct pp_cond_t* cond = &cond_v[cond_c - 1];
            if (cond->has_else) {
               printf("%s:%u:1: #elif after #else is not allowed\n", input_path, row);
               exit(EXIT_FAILURE);
            }
            bool branch = false;
            if (cond->parent_active && !cond->branch_taken) {
               branch = pp_eval_if_expr(macro_v, macro_c, line + arg_begin, line_len - arg_begin, row);
            }
            cond->active = cond->parent_active && !cond->branch_taken && branch;
            cond->branch_taken = cond->branch_taken || branch;
         } else if (pp_name_eq(name, name_len, "else")) {
            if (cond_c == 0) {
               printf("%s:%u:1: #else without matching #if\n", input_path, row);
               exit(EXIT_FAILURE);
            }
            if (!pp_directive_tail_is_empty_or_comment(line, line_len, arg_begin)) {
               printf("%s:%u:1: unexpected tokens after #else\n", input_path, row);
               exit(EXIT_FAILURE);
            }
            struct pp_cond_t* cond = &cond_v[cond_c - 1];
            if (cond->has_else) {
               printf("%s:%u:1: duplicate #else in the same #if block\n", input_path, row);
               exit(EXIT_FAILURE);
            }
            cond->active = cond->parent_active && !cond->branch_taken;
            cond->branch_taken = true;
            cond->has_else = true;
         } else if (pp_name_eq(name, name_len, "endif")) {
            if (cond_c == 0) {
               printf("%s:%u:1: #endif without matching #if\n", input_path, row);
               exit(EXIT_FAILURE);
            }
            if (!pp_directive_tail_is_empty_or_comment(line, line_len, arg_begin)) {
               printf("%s:%u:1: unexpected tokens after #endif\n", input_path, row);
               exit(EXIT_FAILURE);
            }
            cond_c--;
         } else if (line_active) {
            if (!pp_parse_define_line(line, line_len, macro_v, &macro_c, row)) {
               pp_buf_append(&out, line, line_len);
            }
         }
      } else if (line_active) {
         const struct pp_macro_t* stack_v[pp_expand_depth_limit];
         pp_expand_text(macro_v, macro_c, line, line_len, &out, stack_v, 0, row);
      }

      if (has_newline) {
         pp_buf_push(&out, '\n');
         i++;
         row++;
      }
   }
   if (cond_c != 0) {
      printf("%s:%u:1: unterminated preprocessor conditional block\n", input_path, row);
      exit(EXIT_FAILURE);
   }
   pp_buf_push(&out, 0);
   return out.v;
}
