/*!max:re2c */

char* string_mem;
extern char* _Gstring_buf;
extern int _Gstring_len;
char* _Gstring_buf;
int _Gstring_len;
void _Nglc_Pparse_str_init_1(int maxsize) {
   string_mem = malloc(maxsize);
}

int glc_lexer_scan(struct glc_lexer* l) {
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

   *                                { return GLC_TOKEN_END; }
   
   "{"                              { return GLC_TOKEN_LCBRACE; }
   "}"                              { return GLC_TOKEN_RCBRACE; }
   spaces "}"                       { return GLC_TOKEN_SPACE_RCBRACE; }
   "("                              { return GLC_TOKEN_LPAREN; }
   "(" spaces                       { return GLC_TOKEN_LPAREN_SPACE; }
   ")"                              { return GLC_TOKEN_RPAREN; }
   spaces ")"                       { return GLC_TOKEN_SPACE_RPAREN; }
   spaces? "," spaces ")"           { return GLC_TOKEN_COMMA_SPACE_RPAREN; }
   spaces? "," spaces               { return GLC_TOKEN_COMMA_SPACE; }
   spaces? "," spaces "}"           { return GLC_TOKEN_COMMA_SPACE_RCBRACE; }
   spaces? "," spaces "]"           { return GLC_TOKEN_COMMA_SPACE_RBRACKET; }
   spaces? ";" spaces "}"           { return GLC_TOKEN_SCOLON_SPACE_RCBRACE; }
   spaces? ";" spaces               { return GLC_TOKEN_SCOLON_SPACE; }
   spaces                           { return GLC_TOKEN_SPACE; }
   "{+" spaces?                     { return GLC_TOKEN_LCBRACE_PLUS_OR_SPACE; }
   "{gvar" spaces                   { return GLC_TOKEN_LCBRACE_GVAR_SPACE; }
   "{cvar" spaces                   { return GLC_TOKEN_LCBRACE_CVAR_SPACE; }
   "{at("                           { return GLC_TOKEN_LCBRACE_AT_LPAREN; }
   "{using" spaces                  { return GLC_TOKEN_LCBRACE_USING_SPACE; }
   "+"                              { return GLC_TOKEN_PLUS; }
   "-"                              { return GLC_TOKEN_MINUS; }
   "!"                              { return GLC_TOKEN_EXPOINT; }
   "`"                              { return GLC_TOKEN_GRAVE; }
   "'"                              { return GLC_TOKEN_QUOTE; }
   "&"                              { return GLC_TOKEN_AMPERSAND; }
   "#"                              { return GLC_TOKEN_HASH; }
   "["                              { return GLC_TOKEN_LBRACKET; }
   "[" spaces                       { return GLC_TOKEN_LBRACKET_SPACE; }
   "]"                              { return GLC_TOKEN_RBRACKET; }
   spaces "]"                       { return GLC_TOKEN_SPACE_RBRACKET; }
	"0"                              { return GLC_TOKEN_NUM_DEC; }
	[1-9] [0-9]*                     { return GLC_TOKEN_NUM_DEC; }
   "0o" [0-7]+                       { return GLC_TOKEN_NUM_OCT; }
	"0x" [0-9a-fA-F]+                { return GLC_TOKEN_NUM_HEX; }
   "\"" {
      goto lex_string;
   }
   "'=" [ \t] [^\n]*                     {
      _Gstring_len = (l->cursor + 1) - (l->start + 3);
      _Gstring_buf = l->start + 3;
      return GLC_TOKEN_STRING;
   }
   "'-" [ \t] [^\n]*                     {
      _Gstring_len = l->cursor - (l->start + 3);
      _Gstring_buf = l->start + 3;
      return GLC_TOKEN_STRING;
   }
   "'\"" [^\n"]* "\""                   {
      _Gstring_len = (l->cursor - 1) - (l->start + 2);
      _Gstring_buf = l->start + 2;
      return GLC_TOKEN_STRING;
   }
   "'|" [^\n|]* "|"                   {
      _Gstring_len = (l->cursor - 1) - (l->start + 2);
      _Gstring_buf = l->start + 2;
      return GLC_TOKEN_STRING;
   }
   "';" [^\n;]* ";"                   {
      _Gstring_len = (l->cursor - 1) - (l->start + 2);
      _Gstring_buf = l->start + 2;
      return GLC_TOKEN_STRING;
   }
   "'_" [^\n_]* "_"                   {
      _Gstring_len = (l->cursor - 1) - (l->start + 2);
      _Gstring_buf = l->start + 2;
      return GLC_TOKEN_STRING;
   }
   "'+" [^\n+]* "+"                   {
      _Gstring_len = (l->cursor - 1) - (l->start + 2);
      _Gstring_buf = l->start + 2;
      return GLC_TOKEN_STRING;
   }
   "'<" [^\n>]* ">"                   {
      _Gstring_len = (l->cursor - 1) - (l->start + 2);
      _Gstring_buf = l->start + 2;
      return GLC_TOKEN_STRING;
   }
   "'[" [^\n\]]* "]"                   {
      _Gstring_len = (l->cursor - 1) - (l->start + 2);
      _Gstring_buf = l->start + 2;
      return GLC_TOKEN_STRING;
   }
   "'{" [^\n}]* "}"                   {
      _Gstring_len = (l->cursor - 1) - (l->start + 2);
      _Gstring_buf = l->start + 2;
      return GLC_TOKEN_STRING;
   }
   "'(" [^\n)]* ")"                   {
      _Gstring_len = (l->cursor - 1) - (l->start + 2);
      _Gstring_buf = l->start + 2;
      return GLC_TOKEN_STRING;
   }

   "{include(" '"' [^"\n]* '")'     { return GLC_TOKEN_INCLUDE; }
   "{include(" '<' [^>\n]* '>)'     { return GLC_TOKEN_INCLUDE; }

   spaces "@inline"                 { return GLC_TOKEN_SPACE_AT_INLINE; }
   spaces "@main"                   { return GLC_TOKEN_SPACE_AT_MAIN; }
   spaces "@process"                { return GLC_TOKEN_SPACE_AT_PROCESS; }
   spaces "@real-name(" [^)]* ")"   { return GLC_TOKEN_SPACE_AT_REAL_NAME_STR; }
   spaces "@real-name"              { return GLC_TOKEN_SPACE_AT_REAL_NAME; }
   spaces "@decl"                   { return GLC_TOKEN_SPACE_AT_DECL; }
   spaces "@cgl-name"               { return GLC_TOKEN_SPACE_AT_CGL_NAME; }
   spaces "@case"                   { return GLC_TOKEN_SPACE_AT_CASE; }
   spaces "@union"                  { return GLC_TOKEN_SPACE_AT_UNION; }
   spaces "@extern"                 { return GLC_TOKEN_SPACE_AT_EXTERN; }
   spaces "@fall-through"           { return GLC_TOKEN_SPACE_AT_FALL_THROUGH; }
   spaces "@var-args"               { return GLC_TOKEN_SPACE_AT_VAR_ARGS; }
   spaces "@no-decl"                { return GLC_TOKEN_SPACE_AT_NO_DECL; }
   spaces "@no-body"                { return GLC_TOKEN_SPACE_AT_NO_BODY; }
   spaces "=" spaces                { return GLC_TOKEN_SPACE_EQUAL_SPACE; }
   spaces "+=" spaces               { return GLC_TOKEN_SPACE_PLUS_EQUAL_SPACE; }
   spaces "-=" spaces               { return GLC_TOKEN_SPACE_MINUS_EQUAL_SPACE; }
   spaces "*=" spaces               { return GLC_TOKEN_SPACE_MUL_EQUAL_SPACE; }
   spaces "/=" spaces               { return GLC_TOKEN_SPACE_DIV_EQUAL_SPACE; }
   spaces "<<=" spaces              { return GLC_TOKEN_SPACE_LSHIFT_EQUAL_SPACE; }
   spaces ">>=" spaces              { return GLC_TOKEN_SPACE_RSHIFT_EQUAL_SPACE; }
   spaces "&=" spaces               { return GLC_TOKEN_SPACE_AND_EQUAL_SPACE; }
   spaces "|=" spaces               { return GLC_TOKEN_SPACE_OR_EQUAL_SPACE; }
   spaces "^=" spaces               { return GLC_TOKEN_SPACE_XOR_EQUAL_SPACE; }
   spaces "+" spaces                { return GLC_TOKEN_SPACE_PLUS_SPACE; }
   spaces "-" spaces                { return GLC_TOKEN_SPACE_MINUS_SPACE; }
   spaces "*" spaces                { return GLC_TOKEN_SPACE_MUL_SPACE; }
   spaces "/" spaces                { return GLC_TOKEN_SPACE_DIV_SPACE; }
   spaces "<<" spaces               { return GLC_TOKEN_SPACE_LANGLE_LANGLE_SPACE; }
   spaces ">>" spaces               { return GLC_TOKEN_SPACE_RANGLE_RANGLE_SPACE; }
   spaces "&" spaces                { return GLC_TOKEN_SPACE_AMP_SPACE; }
   spaces "|" spaces                { return GLC_TOKEN_SPACE_PIPE_SPACE; }
   spaces "^" spaces                { return GLC_TOKEN_SPACE_XOR_SPACE; }
   "(&&," spaces                    { return GLC_TOKEN_LPAREN_AMP_AMP_COMMA_SPACE; }
   "(||," spaces                    { return GLC_TOKEN_LPAREN_PIPE_PIPE_COMMA_SPACE; }

   ":ref"                           { return GLC_TOKEN_GRAVE_REF; }
   ":bool"                          { return GLC_TOKEN_GRAVE_BOOL; }
   ":char"                          { return GLC_TOKEN_GRAVE_CHAR; }
   ":u8"                            { return GLC_TOKEN_GRAVE_TNUM; }
   ":i8"                            { return GLC_TOKEN_GRAVE_TINT; }
   ":i32"                           { return GLC_TOKEN_GRAVE_INT; }
   ":u32"                           { return GLC_TOKEN_GRAVE_NUM; }
   ":float"                         { return GLC_TOKEN_GRAVE_FLOAT; }
   ":usz"                           { return GLC_TOKEN_GRAVE_SIZE; }
   ":u64"                           { return GLC_TOKEN_GRAVE_LNUM; }

   ":this"                          { return GLC_TOKEN_GRAVE_THIS; }
   "true"                          { return GLC_TOKEN_TRUE; }
   "false"                         { return GLC_TOKEN_FALSE; }
   "null"                          { return GLC_TOKEN_NULL; }

   spaces "==" spaces               { return GLC_TOKEN_SPACE_EQUAL_EQUAL_SPACE; }
   spaces "!=" spaces               { return GLC_TOKEN_SPACE_EXPOINT_EQUAL_SPACE; }
   spaces "<" spaces                { return GLC_TOKEN_SPACE_LANGLE_SPACE; }
   spaces "<=" spaces               { return GLC_TOKEN_SPACE_LANGLE_EQUAL_SPACE; }
   spaces ">" spaces                { return GLC_TOKEN_SPACE_RANGLE_SPACE; }
   spaces ">=" spaces               { return GLC_TOKEN_SPACE_RANGLE_EQUAL_SPACE; }

   "return"                        { return GLC_TOKEN_RETURN; }
   "continue"                      { return GLC_TOKEN_CONTINUE; }
   "break"                         { return GLC_TOKEN_BREAK; }
   "{if"                            { return GLC_TOKEN_LCBRACE_IF; }
   "{switch"                        { return GLC_TOKEN_LCBRACE_SWITCH; }
   "{case"                          { return GLC_TOKEN_LCBRACE_CASE; }
   "{default"                       { return GLC_TOKEN_LCBRACE_DEFAULT; }
   "{do"                            { return GLC_TOKEN_LCBRACE_DO; }
   "{while"                         { return GLC_TOKEN_LCBRACE_WHILE; }
   spaces? "{elif"                  { return GLC_TOKEN_LCBRACE_ELIF; }
   spaces? "{else"                  { return GLC_TOKEN_LCBRACE_ELSE; }

   "''" [^\\\n]                     { return GLC_TOKEN_CHAR1; }
   "''\\" [^\n]                     { return GLC_TOKEN_CHAR2; }

   "."                              { return GLC_TOKEN_DOT; }

   ":" id                           { return GLC_TOKEN_ID_COLON; }
   // "/" id                           { return GLC_TOKEN_ID_FSLASH; }
   "\\" id                          { return GLC_TOKEN_ID_BSLASH; }
   // "%" id                           { return GLC_TOKEN_ID_MODULO; }
   "'" id                           { return GLC_TOKEN_ID_QUOTE; }
   "#" id                           { return GLC_TOKEN_ID_HASH; }
   // "." id                           { return GLC_TOKEN_ID_DOT; }
   [a-zA-Z\u00c0-\U0010ffff][0-9a-zA-Z\u00c0-\U0010ffff]*("-" id)*    { return GLC_TOKEN_ID; }
 
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
         return GLC_TOKEN_STRING;
      }
   }
}
