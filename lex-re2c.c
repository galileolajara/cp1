/*!max:re2c */

uint8_t meta_is_js;
extern char* string_mem;
extern const char* _Tcp1_Gstring_buf;
extern int _Tcp1_Gstring_len;
const char* _Tcp1_Gstring_buf;
int _Tcp1_Gstring_len;
extern const char* _Tcp1_Gtemplate_name_buf;
extern uint8_t _Tcp1_Gtemplate_name_len;
extern uint32_t _Tcp1_Gtemplate_code_indention;
extern uint32_t _Tcp1_Gtemplate_code_line_c;
const char* _Tcp1_Gtemplate_name_buf;
uint8_t _Tcp1_Gtemplate_name_len;
uint32_t _Tcp1_Gtemplate_code_indention;
uint32_t _Tcp1_Gtemplate_code_line_c;
const char* meta_start;
int meta_col;
const char* lex_part_1;
void _Tcp1_Fparse_str_init_1(int maxsize) {
   string_mem = malloc(maxsize);
}

int cp1_lexer_scan(struct cp1_lexer* l) {
   const char *yyt1;
   const char *yyt2;
   const char *id_start;
   const char *id_space;

   const char *marker;
   const char *cursor = l->cursor;
   l->start = cursor;
   #define YYCTYPE  uint8_t
   #define YYCURSOR cursor
   #define YYMARKER marker
   #define YYFILL(n)   

   /*!re2c
   re2c:tags            = 1;
   re2c:indent:top      = 1;
   re2c:yyfill:enable   = 0;

   spaces = [ \n]+;
   id_one = [_0-9a-zA-Z];
   id_first = [_0-9a-zA-Z];
   id = id_first+ ([-] id_one+)*;

   *                                { string_mem[0] = l->start[0]; l->cursor = cursor; return CP1_TOKEN_END; }
   "{"                              {
      if (_Tcp1_Glast_token == CP1_TOKEN_HASH_ID) {
         goto lex_template_inst;
      } else if (meta_start != 0) {
         goto lex_template_code;
      } else {
         l->cursor = cursor; return CP1_TOKEN_OPEN_CURLY_BRACE;
      }
   }
   "}"                               { l->cursor = cursor; return CP1_TOKEN_CLOSE_CURLY_BRACE; }
   spaces "}"                        { l->cursor = cursor; return CP1_TOKEN_SPACE_CLOSE_CURLY_BRACE; }
   "("                               { l->cursor = cursor; return CP1_TOKEN_OPEN_PARENTHESIS; }
   "<"                               { l->cursor = cursor; return CP1_TOKEN_OPEN_ANGLE; }
   ")"                               { l->cursor = cursor; return CP1_TOKEN_CLOSE_PARENTHESIS; }
   ">"                               { l->cursor = cursor; return CP1_TOKEN_CLOSE_ANGLE; }
   spaces ")"                        { l->cursor = cursor; return CP1_TOKEN_SPACE_CLOSE_PARENTHESIS; }
   spaces ">"                        { l->cursor = cursor; return CP1_TOKEN_SPACE_CLOSE_ANGLE; }
   spaces? "," spaces ")"            { l->cursor = cursor; return CP1_TOKEN_COMMA_SPACE_CLOSE_PARENTHESIS; }
   spaces? "," spaces ">"            { l->cursor = cursor; return CP1_TOKEN_COMMA_SPACE_CLOSE_ANGLE; }
   spaces? "," spaces                { l->cursor = cursor; return CP1_TOKEN_COMMA_SPACE; }
   spaces? "," spaces "]"            { l->cursor = cursor; return CP1_TOKEN_COMMA_SPACE_CLOSE_BRACKET; }
   spaces                            { l->cursor = cursor; return CP1_TOKEN_SPACE; }
   spaces? ";"                       { l->cursor = cursor; return CP1_TOKEN_SEMICOLON; }
   "+"                               { l->cursor = cursor; return CP1_TOKEN_PLUS; }
   "-"                               { l->cursor = cursor; return CP1_TOKEN_MINUS; }
   "!"                               { l->cursor = cursor; return CP1_TOKEN_EXCLAMATION; }
   "?"                               { l->cursor = cursor; return CP1_TOKEN_QUESTION; }
   "'"                               { l->cursor = cursor; return CP1_TOKEN_QUOTE; }
   "&"                               { l->cursor = cursor; return CP1_TOKEN_AMPERSAND; }
   "#"                               { l->cursor = cursor; return CP1_TOKEN_HASH; }
   "["                               { l->cursor = cursor; return CP1_TOKEN_OPEN_BRACKET; }
   "]"                               { l->cursor = cursor; return CP1_TOKEN_CLOSE_BRACKET; }
   spaces "]"                        { l->cursor = cursor; return CP1_TOKEN_SPACE_CLOSE_BRACKET; }
	"0"                               { l->cursor = cursor; return CP1_TOKEN_NUM_ZERO; }
	[1-9] [0-9]*                      { l->cursor = cursor; return CP1_TOKEN_NUM_I32; }
	[1-9] [0-9]* "u"                  { l->cursor = cursor; return CP1_TOKEN_NUM_U32; }
	[0-9]+ "u64"                      { l->cursor = cursor; return CP1_TOKEN_NUM_U64; }
   "0o" [0-7]+                       { l->cursor = cursor; return CP1_TOKEN_NUM_OCT; }
	"0x" [0-9a-fA-F]+                 { l->cursor = cursor; return CP1_TOKEN_NUM_HEX; }
	("0"|[1-9][0-9]*) "." [0-9]+ "f"? { l->cursor = cursor; return CP1_TOKEN_NUM_F32; }
	("0"|[1-9][0-9]*) "." [0-9]+ "F"  { l->cursor = cursor; return CP1_TOKEN_NUM_F64; }
   "\"\""[a-zA-Z_][_a-zA-Z0-9]*      {
      _Tcp1_Gstring_len = cursor - (l->start + 2);
      _Tcp1_Gstring_buf = l->start + 2;
      l->cursor = cursor; return CP1_TOKEN_STRING_MACRO;
   }
   // "meta" spaces "#" id spaces "{" {
      // goto lex_template_code;
   // }
   "\"" {
      goto lex_string;
   }
   "'- " [^\n\000]* "\n"                  {
      cursor--;
      _Tcp1_Gstring_len = cursor - (l->start + 3);
      _Tcp1_Gstring_buf = l->start + 3;
      l->cursor = cursor; return CP1_TOKEN_STRING;
   }
   "'= " [^\n\000]* "\n"                  {
      cursor--;
      _Tcp1_Gstring_len = (cursor + 1) - (l->start + 3);
      _Tcp1_Gstring_buf = l->start + 3;
      l->cursor = cursor; return CP1_TOKEN_STRING;
   }
   "'\"" [^\n\000"]* "\""                   {
      _Tcp1_Gstring_len = (cursor - 1) - (l->start + 2);
      _Tcp1_Gstring_buf = l->start + 2;
      l->cursor = cursor; return CP1_TOKEN_STRING;
   }
   "'<" [^\n\000>]* ">"                   {
      _Tcp1_Gstring_len = (cursor - 1) - (l->start + 2);
      _Tcp1_Gstring_buf = l->start + 2;
      l->cursor = cursor; return CP1_TOKEN_STRING;
   }
   "'[" [^\n\000\]]* "]"                   {
      _Tcp1_Gstring_len = (cursor - 1) - (l->start + 2);
      _Tcp1_Gstring_buf = l->start + 2;
      l->cursor = cursor; return CP1_TOKEN_STRING;
   }
   "'{" [^\n\000}]* "}"                   {
      _Tcp1_Gstring_len = (cursor - 1) - (l->start + 2);
      _Tcp1_Gstring_buf = l->start + 2;
      l->cursor = cursor; return CP1_TOKEN_STRING;
   }
   "'(" [^\n\000)]* ")"                   {
      _Tcp1_Gstring_len = (cursor - 1) - (l->start + 2);
      _Tcp1_Gstring_buf = l->start + 2;
      l->cursor = cursor; return CP1_TOKEN_STRING;
   }

   "include " '"' [^"\n\000]* '"'       { l->cursor = cursor; return CP1_TOKEN_INCLUDE; }
   "include " '<' [^>\n\000]* '>'       { l->cursor = cursor; return CP1_TOKEN_INCLUDE; }
   "include [" [^\000\]]* ']'           { l->cursor = cursor; return CP1_TOKEN_INCLUDE; }

   spaces "@inline"                 { l->cursor = cursor; return CP1_TOKEN_SPACE_AT_INLINE; }
   spaces "@main"                   { l->cursor = cursor; return CP1_TOKEN_SPACE_AT_MAIN; }
   spaces "@process"                { l->cursor = cursor; return CP1_TOKEN_SPACE_AT_PROCESS; }
   spaces "@real-name(" [^)\000]* ")"   { l->cursor = cursor; return CP1_TOKEN_SPACE_AT_REAL_NAME_STR; }
   spaces "@real-name"              { l->cursor = cursor; return CP1_TOKEN_SPACE_AT_REAL_NAME; }
   spaces "@aligned"                { l->cursor = cursor; return CP1_TOKEN_SPACE_AT_ALIGNED; }
   spaces "@meta"                   { l->cursor = cursor; return CP1_TOKEN_SPACE_AT_META; }
   spaces "@decl"                   { l->cursor = cursor; return CP1_TOKEN_SPACE_AT_DECL; }
   spaces "@cp1-name"               { l->cursor = cursor; return CP1_TOKEN_SPACE_AT_CP1_NAME; }
   spaces "@case"                   { l->cursor = cursor; return CP1_TOKEN_SPACE_AT_CASE; }
   spaces "@extern"                 { l->cursor = cursor; return CP1_TOKEN_SPACE_AT_EXTERN; }
   spaces "@fall-through"           { l->cursor = cursor; return CP1_TOKEN_SPACE_AT_FALL_THROUGH; }
   spaces "@var-args"               { l->cursor = cursor; return CP1_TOKEN_SPACE_AT_VAR_ARGS; }
   spaces "@no-decl(" [^)\000]* ")"     { l->cursor = cursor; return CP1_TOKEN_SPACE_AT_NO_DECL_STR; }
   spaces "@no-decl"                { l->cursor = cursor; return CP1_TOKEN_SPACE_AT_NO_DECL; }
   spaces "@no-name"                { l->cursor = cursor; return CP1_TOKEN_SPACE_AT_NO_NAME; }
   spaces "@dont-count"             { l->cursor = cursor; return CP1_TOKEN_SPACE_AT_DONT_COUNT; }
   spaces "@no-body"                { l->cursor = cursor; return CP1_TOKEN_SPACE_AT_NO_BODY; }
   spaces "@overload-get"           { l->cursor = cursor; return CP1_TOKEN_SPACE_AT_OVERLOAD_Tcp1_GET; }
   spaces "@overload-set"           { l->cursor = cursor; return CP1_TOKEN_SPACE_AT_OVERLOAD_SET; }
   spaces "@overload-math"          { l->cursor = cursor; return CP1_TOKEN_SPACE_AT_OVERLOAD_MATH; }
   spaces "@overload-bools"         { l->cursor = cursor; return CP1_TOKEN_SPACE_AT_OVERLOAD_BOOLS; }
   spaces "@overload-compare"       { l->cursor = cursor; return CP1_TOKEN_SPACE_AT_OVERLOAD_COMPARE; }
   spaces "@overload-if-begin"      { l->cursor = cursor; return CP1_TOKEN_SPACE_AT_OVERLOAD_IF_BEGIN; }
   spaces "@overload-if-else"       { l->cursor = cursor; return CP1_TOKEN_SPACE_AT_OVERLOAD_IF_ELSE; }
   spaces "@overload-if-end"        { l->cursor = cursor; return CP1_TOKEN_SPACE_AT_OVERLOAD_IF_END; }
   spaces "@overload-statement"     { l->cursor = cursor; return CP1_TOKEN_SPACE_AT_OVERLOAD_STATEMENT; }
   spaces "@no-cache"               { l->cursor = cursor; return CP1_TOKEN_SPACE_AT_NO_CACHE; }
   spaces "@js"                     { l->cursor = cursor; return CP1_TOKEN_SPACE_AT_JS; }
   spaces "@reflection"             { l->cursor = cursor; return CP1_TOKEN_SPACE_AT_REFLECTION; }
   spaces "@soa-field"              { l->cursor = cursor; return CP1_TOKEN_SPACE_AT_SOA_FIELD; }
   spaces "@const"                  { l->cursor = cursor; return CP1_TOKEN_SPACE_AT_CONST; }
   spaces "="                       { l->cursor = cursor; return CP1_TOKEN_SPACE_EQUAL; }
   spaces ":="                      { l->cursor = cursor; return CP1_TOKEN_SPACE_COLON_EQUAL; }
   spaces "+="                      { l->cursor = cursor; return CP1_TOKEN_SPACE_PLUS_EQUAL; }
   spaces "-="                      { l->cursor = cursor; return CP1_TOKEN_SPACE_MINUS_EQUAL; }
   spaces "*="                      { l->cursor = cursor; return CP1_TOKEN_SPACE_MUL_EQUAL; }
   spaces "/="                      { l->cursor = cursor; return CP1_TOKEN_SPACE_DIV_EQUAL; }
   spaces "<<="                     { l->cursor = cursor; return CP1_TOKEN_SPACE_LSHIFT_EQUAL; }
   spaces ">>="                     { l->cursor = cursor; return CP1_TOKEN_SPACE_RSHIFT_EQUAL; }
   spaces "&="                      { l->cursor = cursor; return CP1_TOKEN_SPACE_AND_EQUAL; }
   spaces "|="                      { l->cursor = cursor; return CP1_TOKEN_SPACE_OR_EQUAL; }
   spaces "^="                      { l->cursor = cursor; return CP1_TOKEN_SPACE_XOR_EQUAL; }
   spaces "+"                       { l->cursor = cursor; return CP1_TOKEN_SPACE_OP_PLUS; }
   spaces "-" spaces                { l->cursor = cursor; return CP1_TOKEN_SPACE_OP_MINUS_SPACE; }
   spaces "*"                       { l->cursor = cursor; return CP1_TOKEN_SPACE_OP_MUL; }
   spaces "/"                       { l->cursor = cursor; return CP1_TOKEN_SPACE_OP_DIV; }
   spaces "%"                       { l->cursor = cursor; return CP1_TOKEN_SPACE_OP_MOD; }
   spaces "<<"                      { l->cursor = cursor; return CP1_TOKEN_SPACE_OP_LSHIFT; }
   spaces ">>"                      { l->cursor = cursor; return CP1_TOKEN_SPACE_OP_RSHIFT; }
   spaces "&" spaces                { l->cursor = cursor; return CP1_TOKEN_SPACE_OP_AND_SPACE; }
   spaces "|" spaces                { l->cursor = cursor; return CP1_TOKEN_SPACE_OP_OR_SPACE; }
   spaces "^"                       { l->cursor = cursor; return CP1_TOKEN_SPACE_OP_XOR; }
   "(&&,"                           { l->cursor = cursor; return CP1_TOKEN_OPEN_PARENTHESIS_AMP_AMP_COMMA; }
   "(||,"                           { l->cursor = cursor; return CP1_TOKEN_OPEN_PARENTHESIS_PIPE_PIPE_COMMA; }

   "'ref"                            { l->cursor = cursor; return CP1_TOKEN_REF; }
   "'bool"                           { l->cursor = cursor; return CP1_TOKEN_BOOL; }
   "'char"                           { l->cursor = cursor; return CP1_TOKEN_CHAR; }
   "'cint"                           { l->cursor = cursor; return CP1_TOKEN_INTC; }
   "'i8"                             { l->cursor = cursor; return CP1_TOKEN_I8; }
   "'u8"                             { l->cursor = cursor; return CP1_TOKEN_U8; }
   "'i16"                            { l->cursor = cursor; return CP1_TOKEN_I16; }
   "'u16"                            { l->cursor = cursor; return CP1_TOKEN_U16; }
   "'i32"                            { l->cursor = cursor; return CP1_TOKEN_I32; }
   "'u32"                            { l->cursor = cursor; return CP1_TOKEN_U32; }
   "'i64"                            { l->cursor = cursor; return CP1_TOKEN_I64; }
   "'u64"                            { l->cursor = cursor; return CP1_TOKEN_U64; }
   "'isz"                            { l->cursor = cursor; return CP1_TOKEN_ISZ; }
   "'usz"                            { l->cursor = cursor; return CP1_TOKEN_USZ; }
   "'f32"                            { l->cursor = cursor; return CP1_TOKEN_F32; }
   "'f64"                            { l->cursor = cursor; return CP1_TOKEN_F64; }

   "'this"                           { l->cursor = cursor; return CP1_TOKEN_THIS; }
   "true"                           { l->cursor = cursor; return CP1_TOKEN_TRUE; }
   "false"                          { l->cursor = cursor; return CP1_TOKEN_FALSE; }
   "null"                           { l->cursor = cursor; return CP1_TOKEN_NULL; }

   spaces "=="                      { l->cursor = cursor; return CP1_TOKEN_SPACE_CMP_EQUAL_EQUAL; }
   spaces "!="                      { l->cursor = cursor; return CP1_TOKEN_SPACE_CMP_NOT_EQUAL; }
   spaces "<"                       { l->cursor = cursor; return CP1_TOKEN_SPACE_CMP_LESS_THAN; }
   spaces "<="                      { l->cursor = cursor; return CP1_TOKEN_SPACE_CMP_LESS_EQUAL; }
   spaces ">" spaces                { l->cursor = cursor; return CP1_TOKEN_SPACE_CMP_MORE_THAN_SPACE; }
   spaces ">="                      { l->cursor = cursor; return CP1_TOKEN_SPACE_CMP_MORE_EQUAL; }

   spaces "&&"                      { l->cursor = cursor; return CP1_TOKEN_SPACE_BOOL_AND_AND; }
   spaces "and" spaces              { l->cursor = cursor; return CP1_TOKEN_SPACE_BOOL_AND_AND_SPACE; }
   spaces "||"                      { l->cursor = cursor; return CP1_TOKEN_SPACE_BOOL_OR_OR; }
   spaces "or" spaces               { l->cursor = cursor; return CP1_TOKEN_SPACE_BOOL_OR_OR_SPACE; }

   "using"                          { l->cursor = cursor; return CP1_TOKEN_USING; }
   "meta"                           { meta_start = l->start; meta_col = _Tcp1_Gcol; l->cursor = cursor; return CP1_TOKEN_META; }
   "enum"                           { l->cursor = cursor; return CP1_TOKEN_ENUM; }
   "struct"                         { l->cursor = cursor; return CP1_TOKEN_STRUCT; }
   "union"                          { l->cursor = cursor; return CP1_TOKEN_UNION; }
   "return"                         { l->cursor = cursor; return CP1_TOKEN_RETURN; }
   "loop"                           { l->cursor = cursor; return CP1_TOKEN_LOOP; }
   "continue"                       { l->cursor = cursor; return CP1_TOKEN_CONTINUE; }
   "break"                          { l->cursor = cursor; return CP1_TOKEN_BREAK; }
   "default"                        { l->cursor = cursor; return CP1_TOKEN_DEFAULT; }
   "case"                           { l->cursor = cursor; return CP1_TOKEN_CASE; }
   "switch"                         { l->cursor = cursor; return CP1_TOKEN_SWITCH; }
   "if"                             { l->cursor = cursor; return CP1_TOKEN_IF; }
   spaces "elif"                    { l->cursor = cursor; return CP1_TOKEN_SPACE_ELIF; }
   spaces "else"                    { l->cursor = cursor; return CP1_TOKEN_SPACE_ELSE; }

   "''" [^\\\n]                     { l->cursor = cursor; return CP1_TOKEN_CHAR1; }
   "''\\" [^\n]                     { l->cursor = cursor; return CP1_TOKEN_CHAR2; }

   "."                              { l->cursor = cursor; return CP1_TOKEN_DOT; }
   "'base"                          { l->cursor = cursor; return CP1_TOKEN_BASE; }

   "#" id                           { l->cursor = cursor; return CP1_TOKEN_HASH_ID; }
   "#|" [^ \n\000] [^\n\000|]* "|"             { l->cursor = cursor; return CP1_TOKEN_HASH_ID; }
   "|" [^ \n\000|] [^\n\000|]* "|"              { l->cursor = cursor; return CP1_TOKEN_ID; }
   id_first+ ([-] id_one+)*         { l->cursor = cursor; return CP1_TOKEN_ID; }
   "'" id                           { l->cursor = cursor; return CP1_TOKEN_ID_TYPE; }
   "'|" [^ \n\000] [^\n\000|]* "|"             { l->cursor = cursor; return CP1_TOKEN_ID_TYPE; }
   "[" id? @lex_part_1 "]" id                   { l->cursor = cursor; return CP1_TOKEN_SOA_FIELD; }
   "import" [ ]+ "\"" @lex_part_1 [^"\n\000]* "\""  { l->cursor = cursor; return CP1_TOKEN_IMPORT; }
   "require" [ ]+ "\"" @lex_part_1 [^"\n\000]* "\"" { l->cursor = cursor; return CP1_TOKEN_REQUIRE; }
 
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
            fprintf(stdout, "%s:%u:%u: Error reading the string\n", input_path, _Tcp1_Grow, _Tcp1_Gcol + 1);
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
         _Tcp1_Gstring_buf = string_mem;
         _Tcp1_Gstring_len = string_ptr - string_mem;
         l->cursor = cursor; return CP1_TOKEN_STRING;
      }
   }
lex_template_code: {
      const char* start = meta_start;
      meta_start = 0;
      const char* name = start + 4;
      int col = _Tcp1_Gcol + 4;
      for(;;) {
         if (name[0] == '\n') {
            fprintf(stdout, "%s:%u:%u: Error, the syntax 'meta #NAME {' must not have a new line in between\n", input_path, _Tcp1_Grow, col);
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
            fprintf(stdout, "%s:%u:%u: Error, the syntax 'meta #NAME {' must not have a new line in between\n", input_path, _Tcp1_Grow, col);
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
         fprintf(stdout, "%s:%u:%u: Error, template name is too long\n", input_path, _Tcp1_Grow, _Tcp1_Gcol);
         exit(EXIT_FAILURE);
      }
      _Tcp1_Gtemplate_name_buf = name;
      _Tcp1_Gtemplate_name_len = name_len; */
      const char* curly_brace = name_end;
      for(;;) {
         if (curly_brace[0] == '\n') {
            fprintf(stdout, "%s:%u:%u: Error, the syntax 'meta #NAME {' must not have a new line in between\n", input_path, _Tcp1_Grow, col);
            exit(EXIT_FAILURE);
         }
         if (curly_brace[0] == '{') {
            break;
         }
         col++;
         curly_brace++;
      }
      if (curly_brace[1] != '\n') {
         fprintf(stdout, "%s:%u:%u: Error, the syntax 'meta #NAME {' must be followed by a new line\n", input_path, _Tcp1_Grow, col + 1);
         exit(EXIT_FAILURE);
      }
      col = meta_col;
      int32_t indention = 0;
      while (col > 1) {
         if (start[-1] != ' ') {
            fprintf(stdout, "%s:%u:%u: Error, the line that contains 'meta #NAME {' must not have other character in it. Found a character '%c'.\n", input_path, _Tcp1_Grow, col - 1, start[-1]);
            exit(EXIT_FAILURE);
         }
         col--;
         start--;
         indention++;
      }
      const char* code = curly_brace + 2;
      int32_t i = 0;
      int row = _Tcp1_Grow;
      char* string_ptr = string_mem;
      int32_t first_indent = -1;
      for(;;) {
         if (code[i] == '\0') {
            fprintf(stdout, "%s:%u:%u: Error, cannot find the matching '}' of the meta.\n", input_path, _Tcp1_Grow, _Tcp1_Gcol);
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
               _Tcp1_Gtemplate_code_line_c = row - _Tcp1_Grow - 1;
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
            } else if ((line[first_char] == '^') && (line[first_char + 1] == ' ')) {
               // indention is still ok
               int16_t copy_len = (line_len - 1) - indention;
               *((uint8_t*)pcode_len) = copy_len;
               *((uint8_t*)pcode_len + 1) = (copy_len >> 8) | 0xc0;
               string_ptr += 2;
               memcpy(string_ptr, line + indention + 2, copy_len);
               string_ptr += copy_len;
            } else if ((line[first_char] == '$') && (line[first_char + 1] == ' ')) {
               // indention is still ok
               int16_t copy_len = (line_len - 1) - indention;
               *((uint8_t*)pcode_len) = copy_len;
               *((uint8_t*)pcode_len + 1) = (copy_len >> 8) | 0x40;
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
                     if (meta_is_js && c == '`') {
                        *(string_ptr++) = '\\';
                        *(string_ptr++) = '`';
                     } else {
                        *(string_ptr++) = c;
                     }
                     /* if ((c == '$') && line[i] == '{') {
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
                     } */
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
      _Tcp1_Gstring_buf = string_mem;
      _Tcp1_Gstring_len = string_ptr - string_mem;
      l->cursor = cursor; return CP1_TOKEN_TEMPLATE_CODE;
   }
lex_template_inst: {
      // _Tcp1_Gtemplate_name_buf = l->start + 1;
      // _Tcp1_Gtemplate_name_len = (YYCURSOR - 1) - (l->start + 1);
      // printf("meta [%.*s]\n", _Tcp1_Gtemplate_name_len, _Tcp1_Gtemplate_name_buf);
      const char* json = YYCURSOR;
      int32_t i = 0;
      uint8_t indent = 1;
      for(;;) {
         uint8_t c = json[i++];
         if (c == '\0') {
            fprintf(stdout, "%s:%u:%u: Error, cannot find the closing '}' for the '#NAME{...}' syntax\n", input_path, _Tcp1_Grow, _Tcp1_Gcol);
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
      _Tcp1_Gstring_buf = (char*)&json[0];
      _Tcp1_Gstring_len = i - 1;
      YYCURSOR = (const char*)&json[i];
      l->cursor = cursor; return CP1_TOKEN_TEMPLATE_JSON;
   }
}
