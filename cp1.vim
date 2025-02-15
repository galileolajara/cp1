syntax match Number /0u\?/
syntax match Number /[1-9][0-9]*u\?/
syntax match Number /[0-9]\+\.[0-9]\+f\?/
syntax match Number /0o[0-7]\+/
syntax match Number /0x[0-9a-fA-F]\+/
syntax match Number /#\([a-zA-Z]\|_\+[a-zA-Z0-9]\|[0-9]\)[_a-zA-Z0-9]*\(-[_a-zA-Z0-9]\+\)*/
syntax match Default /\([a-zA-Z]\|_\+[a-zA-Z0-9]\)[_a-zA-Z0-9]*\(-[_a-zA-Z0-9]\+\)*/
syntax match Structure /[A-Z][_a-zA-Z0-9]*\(-[_a-zA-Z0-9]\+\)*/
syntax match Function /<\@<=\([a-zA-Z]\|_\+[a-zA-Z0-9]\|[0-9]\)[_a-zA-Z0-9]*\(-[_a-zA-Z0-9]\+\)*/
syntax match Function /\([a-zA-Z]\|_\+[a-zA-Z0-9]\)[_a-zA-Z0-9]*\(-[_a-zA-Z0-9]\+\)*(\@=/
syntax match Operator /\(true\|false\|null\|return\|continue\|break\|using\|if\|elif\|else\|switch\|case\|default\|var\|loop\|ref\|bool\|char\|intc\|i8\|u8\|i16\|u16\|i32\|u32\|i64\|u64\|isz\|usz\|f32\|f64\|this\|enum\|struct\|union\|:base\)[a-zA-Z0-9-_]\@!/
syntax match Operator /@\(inline\|main\|case\|process\|real-name\|meta-method\|glc-name\|no-decl\|no-body\|decl\|extern\|var-args\|soa-field\|cp1-name\|fall-through\)/
syntax match String /[ \n]\+\$[ \n]\+/
syntax match String /#\?include "[^"]*"/
syntax match String /#\?include <[^>]*>/
syntax match String /"\(\\[^\n]\|[^\\\"\n]\)*"/
syntax match String /' [^\n]*/
syntax match String /'"[^"]*"/
syntax match String /'<[^>]*>/
syntax match String /'\[[^\]]*\]/
syntax match String /'{[^}]*}/
syntax match String /'([^)]*)/
syntax match String /''[^\\]/
syntax match String /''\\[abfnrtv\\'0]/
syntax match Comment /\/\/ .*$/
syntax match Comment /^[ ]*#if(.*$/
syntax match Comment /^[ ]*#if!(.*$/
syntax match Comment /^[ ]*#endif\( .*\|\)$/
"syntax match Operator /\(;\|(\|)\|+\|,\|{\|}\|\[\|\]\)/
