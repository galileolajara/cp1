/*!max:re2c */

char* string_mem;
extern const char* _Gstring_buf;
extern int _Gstring_len;
const char* _Gstring_buf;
int _Gstring_len;
extern const char* _Gtemplate_name_buf;
extern uint8_t _Gtemplate_name_len;
extern uint32_t _Gtemplate_code_indention;
extern uint32_t _Gtemplate_code_line_c;
const char* _Gtemplate_name_buf;
uint8_t _Gtemplate_name_len;
uint32_t _Gtemplate_code_indention;
uint32_t _Gtemplate_code_line_c;
const char* meta_start;
int meta_col;
void _Tcp1_Fparse_str_init_1(int maxsize) {
   string_mem = malloc(maxsize);
}

int cp1_lexer_scan(struct cp1_lexer* l) {
   l->start = l->cursor;

   #define YYCTYPE  uint8_t
   #define YYCURSOR l->cursor
   #define YYMARKER l->marker
   #define YYCTXMARKER l->ctx_marker
   #define YYFILL(n)   

   /*!re2c
   re2c:indent:top      = 1;
   re2c:yyfill:enable   = 0;

   spaces = [ \n]+;
   id_one = [_0-9a-zA-Z\u00c0-\U0010ffff];
   id = id_one+("-" id_one+)*;

   *                                { string_mem[0] = l->start[0]; return CP1_TOKEN_END; }
   "{"                              {
      if (_Glast_token == CP1_TOKEN_HASH_ID) {
         goto lex_template_inst;
      } else if (meta_start != 0) {
         goto lex_template_code;
      } else {
         return CP1_TOKEN_OPEN_CURLY_BRACE;
      }
   }
   "}"                               { return CP1_TOKEN_CLOSE_CURLY_BRACE; }
   spaces "}"                        { return CP1_TOKEN_SPACE_CLOSE_CURLY_BRACE; }
   "("                               { return CP1_TOKEN_OPEN_PARENTHESIS; }
   "<"                               { return CP1_TOKEN_OPEN_ANGLE; }
   ")"                               { return CP1_TOKEN_CLOSE_PARENTHESIS; }
   ">"                               { return CP1_TOKEN_CLOSE_ANGLE; }
   spaces ")"                        { return CP1_TOKEN_SPACE_CLOSE_PARENTHESIS; }
   spaces ">"                        { return CP1_TOKEN_SPACE_CLOSE_ANGLE; }
   spaces? "," spaces ")"            { return CP1_TOKEN_COMMA_SPACE_CLOSE_PARENTHESIS; }
   spaces? "," spaces ">"            { return CP1_TOKEN_COMMA_SPACE_CLOSE_ANGLE; }
   spaces? "," spaces                { return CP1_TOKEN_COMMA_SPACE; }
   spaces? "," spaces "]"            { return CP1_TOKEN_COMMA_SPACE_CLOSE_BRACKET; }
   spaces                            { return CP1_TOKEN_SPACE; }
   spaces? ";"                       { return CP1_TOKEN_SEMICOLON; }
   "+"                               { return CP1_TOKEN_PLUS; }
   "-"                               { return CP1_TOKEN_MINUS; }
   "!"                               { return CP1_TOKEN_EXCLAMATION; }
   "?"                               { return CP1_TOKEN_QUESTION; }
   "&"                               { return CP1_TOKEN_AMPERSAND; }
   "#"                               { return CP1_TOKEN_HASH; }
   "["                               { return CP1_TOKEN_OPEN_BRACKET; }
   "]"                               { return CP1_TOKEN_CLOSE_BRACKET; }
   spaces "]"                        { return CP1_TOKEN_SPACE_CLOSE_BRACKET; }
	"0"                               { return CP1_TOKEN_NUM_ZERO; }
	[1-9] [0-9]*                      { return CP1_TOKEN_NUM_I32; }
	[1-9] [0-9]* "u"                  { return CP1_TOKEN_NUM_U32; }
	[0-9]+ "u64"                      { return CP1_TOKEN_NUM_U64; }
   "0o" [0-7]+                       { return CP1_TOKEN_NUM_OCT; }
	"0x" [0-9a-fA-F]+                 { return CP1_TOKEN_NUM_HEX; }
	("0"|[1-9][0-9]*) "." [0-9]+ "f"? { return CP1_TOKEN_NUM_F32; }
	("0"|[1-9][0-9]*) "." [0-9]+ "F"  { return CP1_TOKEN_NUM_F64; }
   "\"\""[a-zA-Z_][_a-zA-Z0-9]*      {
      _Gstring_len = l->cursor - (l->start + 2);
      _Gstring_buf = l->start + 2;
      return CP1_TOKEN_STRING_MACRO;
   }
   // "meta" spaces "#" id spaces "{" {
      // goto lex_template_code;
   // }
   "\"" {
      goto lex_string;
   }
   "'- " [^\n]* "\n"                  {
      l->cursor--;
      _Gstring_len = l->cursor - (l->start + 3);
      _Gstring_buf = l->start + 3;
      return CP1_TOKEN_STRING;
   }
   "'= " [^\n]* "\n"                  {
      l->cursor--;
      _Gstring_len = (l->cursor + 1) - (l->start + 3);
      _Gstring_buf = l->start + 3;
      return CP1_TOKEN_STRING;
   }
   "'\"" [^\n"]* "\""                   {
      _Gstring_len = (l->cursor - 1) - (l->start + 2);
      _Gstring_buf = l->start + 2;
      return CP1_TOKEN_STRING;
   }
   "'<" [^\n>]* ">"                   {
      _Gstring_len = (l->cursor - 1) - (l->start + 2);
      _Gstring_buf = l->start + 2;
      return CP1_TOKEN_STRING;
   }
   "'[" [^\n\]]* "]"                   {
      _Gstring_len = (l->cursor - 1) - (l->start + 2);
      _Gstring_buf = l->start + 2;
      return CP1_TOKEN_STRING;
   }
   "'{" [^\n}]* "}"                   {
      _Gstring_len = (l->cursor - 1) - (l->start + 2);
      _Gstring_buf = l->start + 2;
      return CP1_TOKEN_STRING;
   }
   "'(" [^\n)]* ")"                   {
      _Gstring_len = (l->cursor - 1) - (l->start + 2);
      _Gstring_buf = l->start + 2;
      return CP1_TOKEN_STRING;
   }

   "include " '"' [^"\n]* '"'       { return CP1_TOKEN_INCLUDE; }
   "include " '<' [^>\n]* '>'       { return CP1_TOKEN_INCLUDE; }
   "include [" [^\]]* ']'           { return CP1_TOKEN_INCLUDE; }

   spaces "@inline"                 { return CP1_TOKEN_SPACE_AT_INLINE; }
   spaces "@main"                   { return CP1_TOKEN_SPACE_AT_MAIN; }
   spaces "@process"                { return CP1_TOKEN_SPACE_AT_PROCESS; }
   spaces "@real-name(" [^)]* ")"   { return CP1_TOKEN_SPACE_AT_REAL_NAME_STR; }
   spaces "@real-name"              { return CP1_TOKEN_SPACE_AT_REAL_NAME; }
   spaces "@aligned"                { return CP1_TOKEN_SPACE_AT_ALIGNED; }
   spaces "@meta"                   { return CP1_TOKEN_SPACE_AT_META; }
   spaces "@decl"                   { return CP1_TOKEN_SPACE_AT_DECL; }
   spaces "@cp1-name"               { return CP1_TOKEN_SPACE_AT_CP1_NAME; }
   spaces "@case"                   { return CP1_TOKEN_SPACE_AT_CASE; }
   spaces "@extern"                 { return CP1_TOKEN_SPACE_AT_EXTERN; }
   spaces "@fall-through"           { return CP1_TOKEN_SPACE_AT_FALL_THROUGH; }
   spaces "@var-args"               { return CP1_TOKEN_SPACE_AT_VAR_ARGS; }
   spaces "@no-decl(" [^)]* ")"     { return CP1_TOKEN_SPACE_AT_NO_DECL_STR; }
   spaces "@no-decl"                { return CP1_TOKEN_SPACE_AT_NO_DECL; }
   spaces "@no-name"                { return CP1_TOKEN_SPACE_AT_NO_NAME; }
   spaces "@dont-count"             { return CP1_TOKEN_SPACE_AT_DONT_COUNT; }
   spaces "@no-body"                { return CP1_TOKEN_SPACE_AT_NO_BODY; }
   spaces "@overload-get"           { return CP1_TOKEN_SPACE_AT_OVERLOAD_GET; }
   spaces "@overload-set"           { return CP1_TOKEN_SPACE_AT_OVERLOAD_SET; }
   spaces "@overload-math"          { return CP1_TOKEN_SPACE_AT_OVERLOAD_MATH; }
   spaces "@overload-bools"         { return CP1_TOKEN_SPACE_AT_OVERLOAD_BOOLS; }
   spaces "@overload-compare"       { return CP1_TOKEN_SPACE_AT_OVERLOAD_COMPARE; }
   spaces "@overload-if-begin"      { return CP1_TOKEN_SPACE_AT_OVERLOAD_IF_BEGIN; }
   spaces "@overload-if-else"       { return CP1_TOKEN_SPACE_AT_OVERLOAD_IF_ELSE; }
   spaces "@overload-if-end"        { return CP1_TOKEN_SPACE_AT_OVERLOAD_IF_END; }
   spaces "@overload-statement"     { return CP1_TOKEN_SPACE_AT_OVERLOAD_STATEMENT; }
   spaces "@reflection"             { return CP1_TOKEN_SPACE_AT_REFLECTION; }
   spaces "@no-cache"               { return CP1_TOKEN_SPACE_AT_NO_CACHE; }
   spaces "@soa-field"              { return CP1_TOKEN_SPACE_AT_SOA_FIELD; }
   spaces "@const"                  { return CP1_TOKEN_SPACE_AT_CONST; }
   spaces "="                       { return CP1_TOKEN_SPACE_EQUAL; }
   spaces ":="                      { return CP1_TOKEN_SPACE_COLON_EQUAL; }
   spaces "+="                      { return CP1_TOKEN_SPACE_PLUS_EQUAL; }
   spaces "-="                      { return CP1_TOKEN_SPACE_MINUS_EQUAL; }
   spaces "*="                      { return CP1_TOKEN_SPACE_MUL_EQUAL; }
   spaces "/="                      { return CP1_TOKEN_SPACE_DIV_EQUAL; }
   spaces "<<="                     { return CP1_TOKEN_SPACE_LSHIFT_EQUAL; }
   spaces ">>="                     { return CP1_TOKEN_SPACE_RSHIFT_EQUAL; }
   spaces "&="                      { return CP1_TOKEN_SPACE_AND_EQUAL; }
   spaces "|="                      { return CP1_TOKEN_SPACE_OR_EQUAL; }
   spaces "^="                      { return CP1_TOKEN_SPACE_XOR_EQUAL; }
   spaces "+"                       { return CP1_TOKEN_SPACE_OP_PLUS; }
   spaces "-" spaces                { return CP1_TOKEN_SPACE_OP_MINUS_SPACE; }
   spaces "*"                       { return CP1_TOKEN_SPACE_OP_MUL; }
   spaces "/"                       { return CP1_TOKEN_SPACE_OP_DIV; }
   spaces "%"                       { return CP1_TOKEN_SPACE_OP_MOD; }
   spaces "<<"                      { return CP1_TOKEN_SPACE_OP_LSHIFT; }
   spaces ">>"                      { return CP1_TOKEN_SPACE_OP_RSHIFT; }
   spaces "&" spaces                { return CP1_TOKEN_SPACE_OP_AND_SPACE; }
   spaces "|"                       { return CP1_TOKEN_SPACE_OP_OR; }
   spaces "^"                       { return CP1_TOKEN_SPACE_OP_XOR; }
   "(&&,"                           { return CP1_TOKEN_OPEN_PARENTHESIS_AMP_AMP_COMMA; }
   "(||,"                           { return CP1_TOKEN_OPEN_PARENTHESIS_PIPE_PIPE_COMMA; }

   "'ref"                            { return CP1_TOKEN_REF; }
   "'bool"                           { return CP1_TOKEN_BOOL; }
   "'char"                           { return CP1_TOKEN_CHAR; }
   "'intc"                           { return CP1_TOKEN_INTC; }
   "'i8"                             { return CP1_TOKEN_I8; }
   "'u8"                             { return CP1_TOKEN_U8; }
   "'i16"                            { return CP1_TOKEN_I16; }
   "'u16"                            { return CP1_TOKEN_U16; }
   "'i32"                            { return CP1_TOKEN_I32; }
   "'u32"                            { return CP1_TOKEN_U32; }
   "'i64"                            { return CP1_TOKEN_I64; }
   "'u64"                            { return CP1_TOKEN_U64; }
   "'isz"                            { return CP1_TOKEN_ISZ; }
   "'usz"                            { return CP1_TOKEN_USZ; }
   "'f32"                            { return CP1_TOKEN_F32; }
   "'f64"                            { return CP1_TOKEN_F64; }

   "'this"                           { return CP1_TOKEN_THIS; }
   "true"                           { return CP1_TOKEN_TRUE; }
   "false"                          { return CP1_TOKEN_FALSE; }
   "null"                           { return CP1_TOKEN_NULL; }

   spaces "=="                      { return CP1_TOKEN_SPACE_CMP_EQUAL_EQUAL; }
   spaces "!="                      { return CP1_TOKEN_SPACE_CMP_NOT_EQUAL; }
   spaces "<"                       { return CP1_TOKEN_SPACE_CMP_LESS_THAN; }
   spaces "<="                      { return CP1_TOKEN_SPACE_CMP_LESS_EQUAL; }
   spaces ">" spaces                { return CP1_TOKEN_SPACE_CMP_MORE_THAN_SPACE; }
   spaces ">="                      { return CP1_TOKEN_SPACE_CMP_MORE_EQUAL; }

   spaces "&&"                      { return CP1_TOKEN_SPACE_BOOL_AND_AND; }
   spaces "and" spaces              { return CP1_TOKEN_SPACE_BOOL_AND_AND_SPACE; }
   spaces "||"                      { return CP1_TOKEN_SPACE_BOOL_OR_OR; }
   spaces "or" spaces               { return CP1_TOKEN_SPACE_BOOL_OR_OR_SPACE; }

   "using"                          { return CP1_TOKEN_USING; }
   "meta"                           { meta_start = l->start; meta_col = _Gcol; return CP1_TOKEN_META; }
   "enum"                           { return CP1_TOKEN_ENUM; }
   "struct"                         { return CP1_TOKEN_STRUCT; }
   "union"                          { return CP1_TOKEN_UNION; }
   "return"                         { return CP1_TOKEN_RETURN; }
   "loop"                           { return CP1_TOKEN_LOOP; }
   "var"                            { return CP1_TOKEN_VAR; }
   "continue"                       { return CP1_TOKEN_CONTINUE; }
   "break"                          { return CP1_TOKEN_BREAK; }
   "default"                        { return CP1_TOKEN_DEFAULT; }
   "case"                           { return CP1_TOKEN_CASE; }
   "switch"                         { return CP1_TOKEN_SWITCH; }
   "if"                             { return CP1_TOKEN_IF; }
   spaces "elif"                    { return CP1_TOKEN_SPACE_ELIF; }
   spaces "else"                    { return CP1_TOKEN_SPACE_ELSE; }

   "''" [^\\\n]                     { return CP1_TOKEN_CHAR1; }
   "''\\" [^\n]                     { return CP1_TOKEN_CHAR2; }

   "."                              { return CP1_TOKEN_DOT; }
   "'base"                          { return CP1_TOKEN_BASE; }

   "#" id                           { return CP1_TOKEN_HASH_ID; }
   id_one+ ("-" id_one+)*           { return CP1_TOKEN_ID; }
   [0-9]+ id_one* ("-" id_one+)+    { return CP1_TOKEN_ID; }
   "'" id_one+ ("-" id_one+)*       { return CP1_TOKEN_ID_TYPE; }
   "[" id? "]" id                   { return CP1_TOKEN_SOA_FIELD; }
   "import" spaces "\"" [^"]* "\""  { return CP1_TOKEN_IMPORT; }
   "require" spaces "\"" [^"]* "\"" { return CP1_TOKEN_REQUIRE; }
 
   */
lex_string: {
      #define pushchar(c) *(string_ptr++) = c
      char* string_ptr = string_mem;
      const char *begin;
      goto string_continue;
      for(;;) {
         /*!re2c
         re2c:yyfill:enable = 0;

         * {
            fprintf(stdout, "%s:%u:%u: Error reading the string\n", input_path, _Grow, _Gcol + 1);
            exit(EXIT_FAILURE);
         }
         "\"" {
            goto string_end;
         }
         [^\n\\"] {
            string_accept_char:
            pushchar(*begin);
            goto string_continue;
         }
         "\\0" { pushchar('\0'); goto string_continue; }
         "\\\\" { pushchar('\\'); goto string_continue; }
         "\\\"" { pushchar('"'); goto string_continue; }
         "\\'" { pushchar('\''); goto string_continue; }
         "\\a" { pushchar('\a'); goto string_continue; }
         "\\b" { pushchar('\b'); goto string_continue; }
         "\\f" { pushchar('\f'); goto string_continue; }
         "\\n" { pushchar('\n'); goto string_continue; }
         "\\r" { pushchar('\r'); goto string_continue; }
         "\\t" { pushchar('\t'); goto string_continue; }
         "\\v" { pushchar('\v'); goto string_continue; }
         */
         string_continue: {
            begin = YYCURSOR;
         }
      }
      string_end: {
         _Gstring_buf = string_mem;
         _Gstring_len = string_ptr - string_mem;
         return CP1_TOKEN_STRING;
      }
   }
lex_template_code: {
      const char* start = meta_start;
      meta_start = 0;
      const char* name = start + 4;
      int col = _Gcol + 4;
      for(;;) {
         if (name[0] == '\n') {
            fprintf(stdout, "%s:%u:%u: Error, the syntax 'meta #NAME {' must not have a new line in between\n", input_path, _Grow, col);
            exit(EXIT_FAILURE);
         }
         if (name[0] != ' ') {
            break;
         }
         col++;
         name++;
      }
      name++;
      const char* name_end = name + 1;
      col++;
      for(;;) {
         if (name_end[0] == '\n') {
            fprintf(stdout, "%s:%u:%u: Error, the syntax 'meta #NAME {' must not have a new line in between\n", input_path, _Grow, col);
            exit(EXIT_FAILURE);
         }
         if (name_end[0] == ' ') {
            break;
         }
         col++;
         name_end++;
      }
      // printf("name [%.*s]\n", (int)(name_end - name), name);
      /* int name_len = name_end - name;
      if (name_len > 255) {
         fprintf(stdout, "%s:%u:%u: Error, template name is too long\n", input_path, _Grow, _Gcol);
         exit(EXIT_FAILURE);
      }
      _Gtemplate_name_buf = name;
      _Gtemplate_name_len = name_len; */
      const char* curly_brace = name_end;
      for(;;) {
         if (curly_brace[0] == '\n') {
            fprintf(stdout, "%s:%u:%u: Error, the syntax 'meta #NAME {' must not have a new line in between\n", input_path, _Grow, col);
            exit(EXIT_FAILURE);
         }
         if (curly_brace[0] == '{') {
            break;
         }
         col++;
         curly_brace++;
      }
      if (curly_brace[1] != '\n') {
         fprintf(stdout, "%s:%u:%u: Error, the syntax 'meta #NAME {' must be followed by a new line\n", input_path, _Grow, col + 1);
         exit(EXIT_FAILURE);
      }
      col = meta_col;
      int32_t indention = 0;
      while (col > 1) {
         if (start[-1] != ' ') {
            fprintf(stdout, "%s:%u:%u: Error, the line that contains 'meta #NAME {' must not have other character in it. Found a character '%c'.\n", input_path, _Grow, col - 1, start[-1]);
            exit(EXIT_FAILURE);
         }
         col--;
         start--;
         indention++;
      }
      const char* code = curly_brace + 2;
      int32_t i = 0;
      int row = _Grow;
      char* string_ptr = string_mem;
      int32_t first_indent = -1;
      for(;;) {
         if (code[i] == '\0') {
            fprintf(stdout, "%s:%u:%u: Error, cannot find the matching '}' of the meta.\n", input_path, _Grow, _Gcol);
            exit(EXIT_FAILURE);
         }
         row++;
         int32_t start = i;
         for(;;) {
            if (code[i] == '\n') {
               break;
            }
            i++;
         }
         const char* line = &code[start];
         int32_t line_len = i - start;
         #define TEMPLATE_MAX_LINE_LEN (32 * 1024)
         if (line_len >= TEMPLATE_MAX_LINE_LEN) {
            fprintf(stdout, "%s:%u: Error, the line is too long. Consists of %u bytes. Please write lines that are less than %u bytes\n", input_path, row, line_len, TEMPLATE_MAX_LINE_LEN);
            exit(EXIT_FAILURE);
         }

         int32_t first_char = 0;
         for(;;) {
            if (line[first_char] != ' ') {
               break;
            }
            first_char++;
         }
         int16_t *pcode_len = (int16_t*)string_ptr;
         if (line[first_char] == '\n') {
            // ignore indention
            *pcode_len = 0;
            string_ptr += 2;
         } else if (first_char == indention) {
            if (line[first_char] == '}') {
               _Gtemplate_code_line_c = row - _Grow - 1;
               YYCURSOR = (const char*)(line + first_char + 1);
               break;
            } else if ((line[first_char] == '#') && (line[first_char + 1] == ' ')) {
               // indention is still ok
               int16_t copy_len = (line_len - 1) - indention;
               *((uint8_t*)pcode_len) = copy_len;
               *((uint8_t*)pcode_len + 1) = (copy_len >> 8) | 0x80;
               string_ptr += 2;
               memcpy(string_ptr, line + indention + 2, copy_len);
               string_ptr += copy_len;
            } else {
               goto indent_more;
            }
         } else if (first_char < indention) {
            indent_more:
            fprintf(stdout, "%s:%u:%u: Error, this line must be indented further\n", input_path, row, first_char + 1);
            exit(EXIT_FAILURE);
         } else {
            if (first_indent == -1) {
               first_indent = first_char;
            } else if (first_char < first_indent) {
               goto indent_more;
            }
            string_ptr += 2;
            for(int32_t i = first_indent; i < first_char; i++) {
               *(string_ptr++) = ' ';
            }
            // 0 - inside `...`
            // 1 - inside ${...}
            // 2 - inside "..."
            // 3 - inside '...'
            uint8_t code_type = 0;
            int32_t code_start;
            int32_t string_start;
            uint32_t i = first_char;
            while (i < line_len) {
               uint8_t c = line[i++];
               switch (code_type) {
                  case 0: {
                     if ((c == '$') && line[i] == '{') {
                        code_start = indention + i;
                        i++;
                        code_type = 1;
                        *(string_ptr++) = '$';
                        *(string_ptr++) = '{';
                     } else if (c == '`') {
                        *(string_ptr++) = '\\';
                        *(string_ptr++) = '`';
                     } else if (c == '\\') {
                        if (line[i] == '$') {
                           *(string_ptr++) = '\\';
                           *(string_ptr++) = '$';
                           i++;
                        } else {
                           *(string_ptr++) = '\\';
                           *(string_ptr++) = '\\';
                           *(string_ptr++) = line[i++];
                        }
                     } else {
                        *(string_ptr++) = c;
                     }
                     break;
                  }
                  case 1: {
                     if (c == '}') {
                        code_type = 0;
                     } else if (c == '"') {
                        string_start = indention + i;
                        code_type = 2;
                     } else if (c == '\'') {
                        string_start = indention + i;
                        code_type = 3;
                     }
                     *(string_ptr++) = c;
                     break;
                  }
                  case 2: {
                     if (c == '"') {
                        code_type = 0;
                        *(string_ptr++) = c;
                     } else if (c == '\\') {
                        *(string_ptr++) = '\\';
                        *(string_ptr++) = line[i++];
                     } else {
                        *(string_ptr++) = c;
                     }
                     break;
                  }
                  case 3: {
                     if (c == '\'') {
                        code_type = 0;
                        *(string_ptr++) = c;
                     } else if (c == '\\') {
                        *(string_ptr++) = '\\';
                        *(string_ptr++) = line[i++];
                     } else {
                        *(string_ptr++) = c;
                     }
                     break;
                  }
               }
            }
            switch (code_type) {
               case 1: {
                  fprintf(stdout, "%s:%u:%u: Error, cannot find the closing '}' for the '${...}' syntax\n", input_path, row, code_start);
                  exit(EXIT_FAILURE);
               }
               case 2: {
                  fprintf(stdout, "%s:%u:%u: Error, cannot find the closing '\"' for the '\"...\"' string syntax\n", input_path, row, string_start);
                  exit(EXIT_FAILURE);
               }
               case 3: {
                  fprintf(stdout, "%s:%u:%u: Error, cannot find the closing \"'\" for the \"'...'\" string syntax\n", input_path, row, string_start);
                  exit(EXIT_FAILURE);
               }
            }
            uint16_t code_len = string_ptr - (char*)&pcode_len[1];
            *((uint8_t*)pcode_len) = code_len;
            *((uint8_t*)pcode_len + 1) = code_len >> 8;
         }
         i++;
      }
      _Gstring_buf = string_mem;
      _Gstring_len = string_ptr - string_mem;
      return CP1_TOKEN_TEMPLATE_CODE;
   }
lex_template_inst: {
      // _Gtemplate_name_buf = l->start + 1;
      // _Gtemplate_name_len = (YYCURSOR - 1) - (l->start + 1);
      // printf("meta [%.*s]\n", _Gtemplate_name_len, _Gtemplate_name_buf);
      const char* json = YYCURSOR;
      int32_t i = 0;
      uint8_t indent = 1;
      for(;;) {
         uint8_t c = json[i++];
         if (c == '\0') {
            fprintf(stdout, "%s:%u:%u: Error, cannot find the closing '}' for the '#NAME{...}' syntax\n", input_path, _Grow, _Gcol);
            exit(EXIT_FAILURE);
         }
         if (c == '"') {
            for(;;) {
               c = json[i++];
               if (c == '\\') {
                  i++;
               } else if (c == '"') {
                  break;
               }
            }
         } else if (c == '\'') {
            for(;;) {
               c = json[i++];
               if (c == '\\') {
                  i++;
               } else if (c == '\'') {
                  break;
               }
            }
         } else if (c == '`') {
            for(;;) {
               c = json[i++];
               if (c == '\\') {
                  i++;
               } else if (c == '`') {
                  break;
               }
            }
         } else if (c == '{') {
            indent++;
         } else if (c == '}') {
            indent--;
            if (indent == 0) {
               break;
            }
         }
      }
      _Gstring_buf = (char*)&json[0];
      _Gstring_len = i - 1;
      YYCURSOR = (const char*)&json[i];
      return CP1_TOKEN_TEMPLATE_JSON;
   }
}
