/*!max:re2c */

char* string_mem;
extern char* _Gstring_buf;
extern int _Gstring_len;
char* _Gstring_buf;
int _Gstring_len;
void _NCp1_Pparse_str_init_1(int maxsize) {
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

   *                                { return CP1_TOKEN_END; }
   
   "{"                              { return CP1_TOKEN_OPEN_CURLY_BRACE; }
   "{" spaces                       { return CP1_TOKEN_OPEN_CURLY_BRACE_SPACE; }
   "}"                              { return CP1_TOKEN_CLOSE_CURLY_BRACE; }
   spaces "}"                       { return CP1_TOKEN_SPACE_CLOSE_CURLY_BRACE; }
   "("                              { return CP1_TOKEN_OPEN_PARENTHESIS; }
   "(" spaces                       { return CP1_TOKEN_OPEN_PARENTHESIS_SPACE; }
   ")"                              { return CP1_TOKEN_CLOSE_PARENTHESIS; }
   spaces ")"                       { return CP1_TOKEN_SPACE_CLOSE_PARENTHESIS; }
   spaces? "," spaces ")"           { return CP1_TOKEN_COMMA_SPACE_CLOSE_PARENTHESIS; }
   spaces? "," spaces               { return CP1_TOKEN_COMMA_SPACE; }
   spaces? "," spaces "]"           { return CP1_TOKEN_COMMA_SPACE_CLOSE_BRACKET; }
   spaces                           { return CP1_TOKEN_SPACE; }
   spaces? ";"                      { return CP1_TOKEN_SEMICOLON; }
   "+"                              { return CP1_TOKEN_PLUS; }
   "-"                              { return CP1_TOKEN_MINUS; }
   "!"                              { return CP1_TOKEN_EXCLAMATION; }
   "`"                              { return CP1_TOKEN_GRAVE; }
   "&"                              { return CP1_TOKEN_AMPERSAND; }
   "#"                              { return CP1_TOKEN_HASH; }
   "["                              { return CP1_TOKEN_OPEN_BRACKET; }
   "[" spaces                       { return CP1_TOKEN_OPEN_BRACKET_SPACE; }
   "]"                              { return CP1_TOKEN_CLOSE_BRACKET; }
   spaces "]"                       { return CP1_TOKEN_SPACE_CLOSE_BRACKET; }
   // "<"                              { return CP1_TOKEN_OPEN_ANGULAR_BRACKET; }
   // "<" spaces                       { return CP1_TOKEN_OPEN_ANGULAR_BRACKET_SPACE; }
   ">"                              { return CP1_TOKEN_CLOSE_ANGULAR_BRACKET; }
   spaces ">"                       { return CP1_TOKEN_SPACE_CLOSE_ANGULAR_BRACKET; }
	"0"                              { return CP1_TOKEN_NUM_ZERO; }
	[1-9] [0-9]*                     { return CP1_TOKEN_NUM_I32; }
	[1-9] [0-9]* "u"                 { return CP1_TOKEN_NUM_U32; }
	[0-9]+ "u64"                     { return CP1_TOKEN_NUM_U64; }
   "0o" [0-7]+                      { return CP1_TOKEN_NUM_OCT; }
	"0x" [0-9a-fA-F]+                { return CP1_TOKEN_NUM_HEX; }
	("0"|[1-9][0-9]*) "." [0-9]+ "f" { return CP1_TOKEN_NUM_F32; }
   "\"" {
      goto lex_string;
   }
   "'- " [^\n]* "\n"                  {
      _Gstring_len = (l->cursor - 1) - (l->start + 3);
      _Gstring_buf = l->start + 3;
      return CP1_TOKEN_STRING;
   }
   "'= " [^\n]* "\n"                  {
      _Gstring_len = l->cursor - (l->start + 3);
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

   spaces "@inline"                 { return CP1_TOKEN_SPACE_AT_INLINE; }
   spaces "@main"                   { return CP1_TOKEN_SPACE_AT_MAIN; }
   spaces "@process"                { return CP1_TOKEN_SPACE_AT_PROCESS; }
   spaces "@real-name(" [^)]* ")"   { return CP1_TOKEN_SPACE_AT_REAL_NAME_STR; }
   spaces "@real-name"              { return CP1_TOKEN_SPACE_AT_REAL_NAME; }
   spaces "@meta-method(" [^ ]+ " " [^)]+ ")"   { return CP1_TOKEN_SPACE_AT_META_METHOD_STR; }
   spaces "@decl"                   { return CP1_TOKEN_SPACE_AT_DECL; }
   spaces "@cp1-name"               { return CP1_TOKEN_SPACE_AT_CP1_NAME; }
   spaces "@case"                   { return CP1_TOKEN_SPACE_AT_CASE; }
   // spaces "@union"                  { return CP1_TOKEN_SPACE_AT_UNION; }
   spaces "@extern"                 { return CP1_TOKEN_SPACE_AT_EXTERN; }
   spaces "@fall-through"           { return CP1_TOKEN_SPACE_AT_FALL_THROUGH; }
   spaces "@var-args"               { return CP1_TOKEN_SPACE_AT_VAR_ARGS; }
   spaces "@no-decl(" [^)]* ")"     { return CP1_TOKEN_SPACE_AT_NO_DECL_STR; }
   spaces "@no-decl"                { return CP1_TOKEN_SPACE_AT_NO_DECL; }
   spaces "@no-body"                { return CP1_TOKEN_SPACE_AT_NO_BODY; }
   spaces "@soa-field"              { return CP1_TOKEN_SPACE_AT_SOA_FIELD; }
   spaces "=" spaces                { return CP1_TOKEN_SPACE_EQUAL_SPACE; }
   spaces "+=" spaces               { return CP1_TOKEN_SPACE_PLUS_EQUAL_SPACE; }
   spaces "-=" spaces               { return CP1_TOKEN_SPACE_MINUS_EQUAL_SPACE; }
   spaces "*=" spaces               { return CP1_TOKEN_SPACE_MUL_EQUAL_SPACE; }
   spaces "/=" spaces               { return CP1_TOKEN_SPACE_DIV_EQUAL_SPACE; }
   spaces "<<=" spaces              { return CP1_TOKEN_SPACE_LSHIFT_EQUAL_SPACE; }
   spaces ">>=" spaces              { return CP1_TOKEN_SPACE_RSHIFT_EQUAL_SPACE; }
   spaces "&=" spaces               { return CP1_TOKEN_SPACE_AND_EQUAL_SPACE; }
   spaces "|=" spaces               { return CP1_TOKEN_SPACE_OR_EQUAL_SPACE; }
   spaces "^=" spaces               { return CP1_TOKEN_SPACE_XOR_EQUAL_SPACE; }
   spaces "+" spaces                { return CP1_TOKEN_SPACE_PLUS_SPACE; }
   spaces "-" spaces                { return CP1_TOKEN_SPACE_MINUS_SPACE; }
   spaces "*" spaces                { return CP1_TOKEN_SPACE_MUL_SPACE; }
   spaces "/" spaces                { return CP1_TOKEN_SPACE_DIV_SPACE; }
   spaces "%" spaces                { return CP1_TOKEN_SPACE_MOD_SPACE; }
   spaces "<<" spaces               { return CP1_TOKEN_SPACE_LANGLE_LANGLE_SPACE; }
   spaces ">>" spaces               { return CP1_TOKEN_SPACE_RANGLE_RANGLE_SPACE; }
   spaces "&" spaces                { return CP1_TOKEN_SPACE_AMP_SPACE; }
   spaces "|" spaces                { return CP1_TOKEN_SPACE_PIPE_SPACE; }
   spaces "^" spaces                { return CP1_TOKEN_SPACE_XOR_SPACE; }
   spaces "$" spaces                { return CP1_TOKEN_SPACE_DOLLAR_SPACE; }
   "(&&," spaces                    { return CP1_TOKEN_OPEN_PARENTHESIS_AMP_AMP_COMMA_SPACE; }
   "(||," spaces                    { return CP1_TOKEN_OPEN_PARENTHESIS_PIPE_PIPE_COMMA_SPACE; }

   "ref"                            { return CP1_TOKEN_REF; }
   "bool"                           { return CP1_TOKEN_BOOL; }
   "char"                           { return CP1_TOKEN_CHAR; }
   "intc"                           { return CP1_TOKEN_INTC; }
   "i8"                             { return CP1_TOKEN_I8; }
   "u8"                             { return CP1_TOKEN_U8; }
   "i16"                            { return CP1_TOKEN_I16; }
   "u16"                            { return CP1_TOKEN_U16; }
   "i32"                            { return CP1_TOKEN_I32; }
   "u32"                            { return CP1_TOKEN_U32; }
   "i64"                            { return CP1_TOKEN_I64; }
   "u64"                            { return CP1_TOKEN_U64; }
   "isz"                            { return CP1_TOKEN_ISZ; }
   "usz"                            { return CP1_TOKEN_USZ; }
   "f32"                            { return CP1_TOKEN_F32; }
   "f64"                            { return CP1_TOKEN_F64; }

   "this"                           { return CP1_TOKEN_THIS; }
   "true"                           { return CP1_TOKEN_TRUE; }
   "false"                          { return CP1_TOKEN_FALSE; }
   "null"                           { return CP1_TOKEN_NULL; }

   spaces "==" spaces               { return CP1_TOKEN_SPACE_EQUAL_EQUAL_SPACE; }
   spaces "!=" spaces               { return CP1_TOKEN_SPACE_EXCLAMATION_EQUAL_SPACE; }
   spaces "<" spaces                { return CP1_TOKEN_SPACE_LANGLE_SPACE; }
   spaces "<=" spaces               { return CP1_TOKEN_SPACE_LANGLE_EQUAL_SPACE; }
   spaces ">" spaces                { return CP1_TOKEN_SPACE_RANGLE_SPACE; }
   spaces ">=" spaces               { return CP1_TOKEN_SPACE_RANGLE_EQUAL_SPACE; }

   spaces "&&" spaces               { return CP1_TOKEN_SPACE_AMP_AMP_SPACE; }
   spaces "||" spaces               { return CP1_TOKEN_SPACE_PIPE_PIPE_SPACE; }

   "using"                          { return CP1_TOKEN_USING; }
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
   ":"                              { return CP1_TOKEN_COLON; }
   ":base"                          { return CP1_TOKEN_COLON_BASE; }

   "<" id                           { return CP1_TOKEN_ANGULAR_BRACKET_ID; }
   "#" id                           { return CP1_TOKEN_HASH_ID; }
   [a-z] id_one* ("-" id)*          { return CP1_TOKEN_ID; }
   [A-Z] id_one* ("-" id)*          { return CP1_TOKEN_ID_UPPER; }
   "." [A-Z] id_one* ("-" id)*      { return CP1_TOKEN_DOT_ID_UPPER; }
   "[" id? "]" id                           { return CP1_TOKEN_SOA_FIELD; }
 
   */
lex_string: {
      #define pushchar(c) *(string_ptr++) = c
      _Gstring_buf = string_mem;
      char* string_ptr = string_mem;
      unsigned char *begin;
      goto string_continue;
      for(;;) {
         /*!re2c
         re2c:yyfill:enable = 0;

         * {
            fprintf(stdout, "%u:%u: Error reading the string\n", _Grow, _Gcol + 1);
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
         _Gstring_len = string_ptr - string_mem;
         return CP1_TOKEN_STRING;
      }
   }
}
