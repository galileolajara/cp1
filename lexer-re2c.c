/*!max:re2c */

char* string_mem;
extern char* _Gstring_buf;
extern int _Gstring_len;
char* _Gstring_buf;
int _Gstring_len;
void _Ncp1_Pparse_str_init_1(int maxsize) {
   string_mem = malloc(maxsize);
}

int cp1_lexer_scan(struct cp1_lexer* l) {
   l->start = l->cursor;

   #define YYCTYPE  uint8_t
   #define YYCURSOR l->cursor
   // #define YYLIMIT  l->limit
   #define YYMARKER l->marker
   #define YYCTXMARKER l->ctx_marker
   #define YYFILL(n)   

   /*!re2c
   re2c:indent:top      = 1;
   re2c:yyfill:enable   = 0;

   spaces = [ \t\n]+;
   id_one = [0-9a-zA-Z\u00c0-\U0010ffff];
   id = id_one+("-" id_one+)*;
   // id = [0-9a-zA-Z]+("-" [0-9a-zA-Z]+)*;

   *                                { return CP1_TOKEN_END; }
   
   "{"                              { return CP1_TOKEN_LCBRACE; }
   "{" spaces                       { return CP1_TOKEN_LCBRACE_SPACE; }
   "}"                              { return CP1_TOKEN_RCBRACE; }
   spaces "}"                       { return CP1_TOKEN_SPACE_RCBRACE; }
   "("                              { return CP1_TOKEN_LPAREN; }
   "(" spaces                       { return CP1_TOKEN_LPAREN_SPACE; }
   ")"                              { return CP1_TOKEN_RPAREN; }
   spaces ")"                       { return CP1_TOKEN_SPACE_RPAREN; }
   spaces? "," spaces ")"           { return CP1_TOKEN_COMMA_SPACE_RPAREN; }
   spaces? "," spaces               { return CP1_TOKEN_COMMA_SPACE; }
   spaces? "," spaces "}"           { return CP1_TOKEN_COMMA_SPACE_RCBRACE; }
   spaces? "," spaces "]"           { return CP1_TOKEN_COMMA_SPACE_RBRACKET; }
   // spaces? ";" spaces "}"           { return CP1_TOKEN_SCOLON_SPACE_RCBRACE; }
   // spaces? ";" spaces               { return CP1_TOKEN_SCOLON_SPACE; }
   spaces                           { return CP1_TOKEN_SPACE; }
   spaces? ";"                      { return CP1_TOKEN_SCOLON; }
   // "{+" spaces?                     { return CP1_TOKEN_LCBRACE_PLUS_OR_SPACE; }
   "{gvar" spaces                   { return CP1_TOKEN_LCBRACE_GVAR_SPACE; }
   "{cvar" spaces                   { return CP1_TOKEN_LCBRACE_CVAR_SPACE; }
   "{at("                           { return CP1_TOKEN_LCBRACE_AT_LPAREN; }
   // "{using" spaces                  { return CP1_TOKEN_LCBRACE_USING_SPACE; }
   "+"                              { return CP1_TOKEN_PLUS; }
   "-"                              { return CP1_TOKEN_MINUS; }
   "!"                              { return CP1_TOKEN_EXPOINT; }
   "`"                              { return CP1_TOKEN_GRAVE; }
   "'"                              { return CP1_TOKEN_QUOTE; }
   "&"                              { return CP1_TOKEN_AMPERSAND; }
   "#"                              { return CP1_TOKEN_HASH; }
   "["                              { return CP1_TOKEN_LBRACKET; }
   "[" spaces                       { return CP1_TOKEN_LBRACKET_SPACE; }
   "]"                              { return CP1_TOKEN_RBRACKET; }
   spaces "]"                       { return CP1_TOKEN_SPACE_RBRACKET; }
	"0"                              { return CP1_TOKEN_NUM_DEC; }
	[1-9] [0-9]*                     { return CP1_TOKEN_NUM_DEC; }
   "0o" [0-7]+                       { return CP1_TOKEN_NUM_OCT; }
	"0x" [0-9a-fA-F]+                { return CP1_TOKEN_NUM_HEX; }
   "\"" {
      goto lex_string;
   }
   "'=" [ \t] [^\n]*                     {
      _Gstring_len = (l->cursor + 1) - (l->start + 3);
      _Gstring_buf = l->start + 3;
      return CP1_TOKEN_STRING;
   }
   "'-" [ \t] [^\n]*                     {
      _Gstring_len = l->cursor - (l->start + 3);
      _Gstring_buf = l->start + 3;
      return CP1_TOKEN_STRING;
   }
   "'\"" [^\n"]* "\""                   {
      _Gstring_len = (l->cursor - 1) - (l->start + 2);
      _Gstring_buf = l->start + 2;
      return CP1_TOKEN_STRING;
   }
   "'|" [^\n|]* "|"                   {
      _Gstring_len = (l->cursor - 1) - (l->start + 2);
      _Gstring_buf = l->start + 2;
      return CP1_TOKEN_STRING;
   }
   "';" [^\n;]* ";"                   {
      _Gstring_len = (l->cursor - 1) - (l->start + 2);
      _Gstring_buf = l->start + 2;
      return CP1_TOKEN_STRING;
   }
   "'_" [^\n_]* "_"                   {
      _Gstring_len = (l->cursor - 1) - (l->start + 2);
      _Gstring_buf = l->start + 2;
      return CP1_TOKEN_STRING;
   }
   "'+" [^\n+]* "+"                   {
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

   "{include(" '"' [^"\n]* '")'     { return CP1_TOKEN_INCLUDE; }
   "{include(" '<' [^>\n]* '>)'     { return CP1_TOKEN_INCLUDE; }

   spaces "@inline"                 { return CP1_TOKEN_SPACE_AT_INLINE; }
   spaces "@main"                   { return CP1_TOKEN_SPACE_AT_MAIN; }
   spaces "@process"                { return CP1_TOKEN_SPACE_AT_PROCESS; }
   spaces "@real-name(" [^)]* ")"   { return CP1_TOKEN_SPACE_AT_REAL_NAME_STR; }
   spaces "@real-name"              { return CP1_TOKEN_SPACE_AT_REAL_NAME; }
   spaces "@decl"                   { return CP1_TOKEN_SPACE_AT_DECL; }
   spaces "@cp1-name"               { return CP1_TOKEN_SPACE_AT_CP1_NAME; }
   spaces "@case"                   { return CP1_TOKEN_SPACE_AT_CASE; }
   spaces "@union"                  { return CP1_TOKEN_SPACE_AT_UNION; }
   spaces "@extern"                 { return CP1_TOKEN_SPACE_AT_EXTERN; }
   spaces "@fall-through"           { return CP1_TOKEN_SPACE_AT_FALL_THROUGH; }
   spaces "@var-args"               { return CP1_TOKEN_SPACE_AT_VAR_ARGS; }
   spaces "@no-decl"                { return CP1_TOKEN_SPACE_AT_NO_DECL; }
   spaces "@no-body"                { return CP1_TOKEN_SPACE_AT_NO_BODY; }
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
   spaces "<<" spaces               { return CP1_TOKEN_SPACE_LANGLE_LANGLE_SPACE; }
   spaces ">>" spaces               { return CP1_TOKEN_SPACE_RANGLE_RANGLE_SPACE; }
   spaces "&" spaces                { return CP1_TOKEN_SPACE_AMP_SPACE; }
   spaces "|" spaces                { return CP1_TOKEN_SPACE_PIPE_SPACE; }
   spaces "^" spaces                { return CP1_TOKEN_SPACE_XOR_SPACE; }
   "(&&," spaces                    { return CP1_TOKEN_LPAREN_AMP_AMP_COMMA_SPACE; }
   "(||," spaces                    { return CP1_TOKEN_LPAREN_PIPE_PIPE_COMMA_SPACE; }

   ":ref"                           { return CP1_TOKEN_COLON_REF; }
   ":bool"                          { return CP1_TOKEN_COLON_BOOL; }
   ":char"                          { return CP1_TOKEN_COLON_CHAR; }
   ":intc"                          { return CP1_TOKEN_COLON_INTC; }
   ":i8"                            { return CP1_TOKEN_COLON_I8; }
   ":u8"                            { return CP1_TOKEN_COLON_U8; }
   ":i16"                           { return CP1_TOKEN_COLON_I16; }
   ":u16"                           { return CP1_TOKEN_COLON_U16; }
   ":i32"                           { return CP1_TOKEN_COLON_I32; }
   ":u32"                           { return CP1_TOKEN_COLON_U32; }
   ":i64"                           { return CP1_TOKEN_COLON_I64; }
   ":u64"                           { return CP1_TOKEN_COLON_U64; }
   ":isz"                           { return CP1_TOKEN_COLON_ISZ; }
   ":usz"                           { return CP1_TOKEN_COLON_USZ; }
   ":f32"                           { return CP1_TOKEN_COLON_F32; }
   ":f64"                           { return CP1_TOKEN_COLON_F64; }

   ":this"                          { return CP1_TOKEN_COLON_THIS; }
   "true"                           { return CP1_TOKEN_TRUE; }
   "false"                          { return CP1_TOKEN_FALSE; }
   "null"                           { return CP1_TOKEN_NULL; }

   spaces "==" spaces               { return CP1_TOKEN_SPACE_EQUAL_EQUAL_SPACE; }
   spaces "!=" spaces               { return CP1_TOKEN_SPACE_EXPOINT_EQUAL_SPACE; }
   spaces "<" spaces                { return CP1_TOKEN_SPACE_LANGLE_SPACE; }
   spaces "<=" spaces               { return CP1_TOKEN_SPACE_LANGLE_EQUAL_SPACE; }
   spaces ">" spaces                { return CP1_TOKEN_SPACE_RANGLE_SPACE; }
   spaces ">=" spaces               { return CP1_TOKEN_SPACE_RANGLE_EQUAL_SPACE; }

   "using"                          { return CP1_TOKEN_USING; }
   "return"                         { return CP1_TOKEN_RETURN; }
   "loop"                           { return CP1_TOKEN_LOOP; }
   "var"                            { return CP1_TOKEN_VAR; }
   "continue"                       { return CP1_TOKEN_CONTINUE; }
   "break"                          { return CP1_TOKEN_BREAK; }
   "default"                        { return CP1_TOKEN_DEFAULT; }
   "case"                           { return CP1_TOKEN_CASE; }
   "switch"                         { return CP1_TOKEN_SWITCH; }
   "while"                          { return CP1_TOKEN_WHILE; }
   "if"                             { return CP1_TOKEN_IF; }
   spaces "elif"                    { return CP1_TOKEN_SPACE_ELIF; }
   spaces "else"                    { return CP1_TOKEN_SPACE_ELSE; }
   // "{if"                            { return CP1_TOKEN_LCBRACE_IF; }
   // "{switch"                        { return CP1_TOKEN_LCBRACE_SWITCH; }
   // "{case"                          { return CP1_TOKEN_LCBRACE_CASE; }
   // "{default"                       { return CP1_TOKEN_LCBRACE_DEFAULT; }
   // "{do"                            { return CP1_TOKEN_LCBRACE_DO; }
   // "{while"                         { return CP1_TOKEN_LCBRACE_WHILE; }
   // spaces? "{elif"                  { return CP1_TOKEN_LCBRACE_ELIF; }
   // spaces? "{else"                  { return CP1_TOKEN_LCBRACE_ELSE; }

   "''" [^\\\n]                     { return CP1_TOKEN_CHAR1; }
   "''\\" [^\n]                     { return CP1_TOKEN_CHAR2; }

   "."                              { return CP1_TOKEN_DOT; }

   ":" id                           { return CP1_TOKEN_ID_COLON; }
   // "/" id                           { return CP1_TOKEN_ID_FSLASH; }
   "\\" id                          { return CP1_TOKEN_ID_BSLASH; }
   // "%" id                           { return CP1_TOKEN_ID_MODULO; }
   "'" id                           { return CP1_TOKEN_ID_QUOTE; }
   "#" id                           { return CP1_TOKEN_ID_HASH; }
   // "." id                           { return CP1_TOKEN_ID_DOT; }
   [a-zA-Z\u00c0-\U0010ffff][0-9a-zA-Z\u00c0-\U0010ffff]*("-" id)*    { return CP1_TOKEN_ID; }
 
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
