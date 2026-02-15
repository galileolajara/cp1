/*!max:re2c */

int c_lexer_scan(struct c_lexer* l) {
   l->start = l->cursor;

   #define YYCTYPE  uint8_t
   #define YYCURSOR l->cursor
   #define YYMARKER l->marker
   #define YYCTXMARKER l->ctx_marker
   #define YYFILL(n)   

   /*!re2c
   re2c:indent:top      = 1;
   re2c:yyfill:enable   = 0;
    
   *                                            { string_mem[0] = l->start[0]; return C_TOKEN_END; }
   ("unsigned short"|"uint16_t")                { return C_TOKEN_U16; }
   "void"                                       { return C_TOKEN_VOID; }
   "bool"                                       { return C_TOKEN_BOOL; }
   "char"                                       { return C_TOKEN_CHAR; }
   [ \t\n]+                                     { return 0; }

   ";"                                          { return C_TOKEN_SEMICOLON; }
   "{"                                          { return C_TOKEN_OPEN_CURLY; }
   "}"                                          { return C_TOKEN_CLOSE_CURLY; }
   "("                                          { return C_TOKEN_OPEN_PAREN; }
   ")"                                          { return C_TOKEN_CLOSE_PAREN; }
   "="                                          { return C_TOKEN_EQUAL; }
   ","                                          { return C_TOKEN_COMMA; }
   "return"                                     { return C_TOKEN_RETURN; }
   "if"                                         { return C_TOKEN_IF; }
   "else"                                       { return C_TOKEN_ELSE; }
   "true"                                       { return C_TOKEN_TRUE; }
   "false"                                      { return C_TOKEN_FALSE; }
   "else" [ \n\t]+ "if"                         { return C_TOKEN_ELSE_IF; }
   "!" .                                        { return C_TOKEN_EXPOINT; }
   "0"                                          { return C_TOKEN_INT; }
   [1-9][0-9]*                                  { return C_TOKEN_INT; }
   "0u"                                         { return C_TOKEN_UINT; }
   [1-9][0-9]*"u"                               { return C_TOKEN_UINT; }

   "+"                                          { return C_TOKEN_PLUS; }
   "*"                                          { return C_TOKEN_STAR; }

   "#"[^\n\000]+                                { return C_TOKEN_PREPROCESS; }
   "\"" {
      goto lex_string;
   }

   [a-zA-Z_][a-zA-Z0-9_]*                       { return C_TOKEN_ID; }
   
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
            printf("%s:%u:%u: Error reading the string\n", input_path, row_now, col_now + 1);
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
         string_buf = string_mem;
         string_len = string_ptr - string_mem;
         /* _Tcp1_Gstring_buf = string_mem;
         _Tcp1_Gstring_len = string_ptr - string_mem; */
         return C_TOKEN_STRING;
      }
   }
}
