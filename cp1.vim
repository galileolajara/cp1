syntax match Number /[0-9]\+\(\.[0-9]\+\)\?/
syntax match Number /0o[0-7]\+/
syntax match Number /#\([a-zA-Z]\|_\+[a-zA-Z0-9]\|[0-9]\)[_a-zA-Z0-9]*\(-[_a-zA-Z0-9]\+\)*/
syntax match Default /\([a-zA-Z]\|_\+[a-zA-Z0-9]\)[_a-zA-Z0-9]*\(-[_a-zA-Z0-9]\+\)*/
syntax match Function /\([a-zA-Z]\|_\+[a-zA-Z0-9]\)[_a-zA-Z0-9]*\(-[_a-zA-Z0-9]\+\)*(\@=/
"syntax match Operator "{\@<=\(at\|while\|if\|elif\|else\|switch\|case\|default\|do\|gvar\|cvar\)[a-zA-Z0-9-]\@!"
syntax match Structure /\(:\|'\)[_a-zA-Z0-9]\+\(-[_a-zA-Z0-9]\+\)*/
syntax match Operator /:\(ref\|bool\|char\|intc\|i8\|u8\|i16\|u16\|i32\|u32\|i64\|u64\|isz\|usz\|f32\|f64\|this\)[a-zA-Z0-9-]\@!/
syntax match Operator /\(true\|false\|null\|return\|continue\|break\|using\|if\|elif\|else\|while\|switch\|case\|default\)[a-zA-Z0-9-]\@!/
syntax match Operator /@\(inline\|main\|case\|process\|real-name\|glc-name\|no-decl\|no-body\|decl\)/
syntax match String /"\(\\[^\n]\|[^\\\"\n]\)*"/
syntax match String /'"[^"]*"/
syntax match String /'|[^|]*|/
syntax match String /';[^;]*;/
syntax match String /'_[^_]*_/
syntax match String /'+[^+]*+/
syntax match String /'<[^>]*>/
syntax match String /'\[[^\]]*\]/
syntax match String /'{[^}]*}/
syntax match String /'([^)]*)/
syntax match String /''[^\\]/
syntax match String /''\\[abfnrtv\\'"0]/
syntax match Comment /\/\/[ \t].*$/
syntax match Comment /^[ \t]*#if(.*$/
syntax match Comment /^[ \t]*#if!(.*$/
syntax match Comment /^[ \t]*#endif\([ \t].*\|\)$/
"syntax match Operator /\(;\|(\|)\|+\|,\|{\|}\|\[\|\]\)/
