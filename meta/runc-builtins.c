id_t id_str = c_lexer_id("str", 3);
id_t id_len = c_lexer_id("len", 3);
id_t id_str2 = c_lexer_id("str2", 4);
id_t id_len2 = c_lexer_id("len2", 4);
func_arg(type_char, id_str, 0, 0);
func_arg(type_u32, id_len, 0, 0);
func_sig(type_void, c_lexer_id("_FO_2", 5), 0, 0);
func_bytecode_v[func_now] = -1;

func_sig(type_void, c_lexer_id("_FL_0", 5), 0, 0);
func_bytecode_v[func_now] = -2;

func_arg(type_char, id_str, 0, 0);
func_arg(type_u32, id_len, 0, 0);
func_sig(type_void, c_lexer_id("_FR_2", 5), 0, 0);
func_bytecode_v[func_now] = -3;

func_arg(type_char, id_str, 0, 0);
func_arg(type_u32, id_len, 0, 0);
func_arg(type_char, id_str2, 0, 0);
func_arg(type_u32, id_len2, 0, 0);
func_sig(type_void, c_lexer_id("_FR_4", 5), 0, 0);
func_bytecode_v[func_now] = -4;
