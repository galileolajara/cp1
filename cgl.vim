syntax match Number /[0-9]\+\(\.[0-9]\+\)\?/
syntax match Number /#\([a-zA-Z]\|_\+[a-zA-Z0-9]\|[0-9]\)[_a-zA-Z0-9]*\(-[_a-zA-Z0-9]\+\)*/
syntax match Default /\([a-zA-Z]\|_\+[a-zA-Z0-9]\)[_a-zA-Z0-9]*\(-[_a-zA-Z0-9]\+\)*/
syntax match Function /\([a-zA-Z]\|_\+[a-zA-Z0-9]\)[_a-zA-Z0-9]*\(-[_a-zA-Z0-9]\+\)*(\@=/
syntax match Operator "{\@<=\(at\|while\|if\|elif\|else\|switch\|case\|default\|do\|alias\|gvar\|cvar\)[a-zA-Z0-9-]\@!"
syntax match Structure /\(:\|'\)[_a-zA-Z0-9]\+\(-[_a-zA-Z0-9]\+\)*/
syntax match Operator /:\(ref\|bool\|char\|u8\|i8\|u32\|i32\|float\|usz\|u64\|this\|true\|false\|null\|return\)[a-zA-Z0-9-]\@!/
syntax match Operator /@\(inline\|main\|case\|process\|real-name\|glc-name\|no-decl\)/
syntax match String /"\(\\[^\n]\|[^\\\"\n]\)*"/
syntax match String /''[^\\]/
syntax match String /''\\[abfnrtv\\'"0]/
syntax match Comment /\/\/[ \t].*$/
"syntax match Operator /\(;\|(\|)\|+\|,\|{\|}\|\[\|\]\)/
