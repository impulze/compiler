lexer grammar boofar_lexer;

options
{
	language = C;
}

OCT_LITERAL : '0' OCT_DIGIT+;
HEX_LITERAL : '0' ('x'|'X') HEX_DIGIT+;
DEC_LITERAL : '0' | ('1'..'9' DEC_DIGIT*);
FLOAT_LITERAL : DEC_DIGIT+ '.' DEC_DIGIT* EXPONENT?
	| '.' DEC_DIGIT+ EXPONENT?
	| DEC_DIGIT+ EXPONENT
	;
STRING_LITERAL : '"' (ESCAPE|~('\\'|'"'))* '"';
IDENTIFIER : ASCII_LETTER (ASCII_LETTER|'_'|DEC_DIGIT)*;
COMMENT : '//' ~('\n'|'\r')* '\r'? '\n' {$channel=HIDDEN;}
	| '/*' ( options {greedy=false;} : . )* '*/' {$channel=HIDDEN;}
	;

fragment OCT_DIGIT : '0'..'7';
fragment HEX_DIGIT : '0'..'9'|'A'..'F'|'a'..'f';
fragment DEC_DIGIT : '0'..'9';
fragment EXPONENT : ('e'|'E') ('+'|'-')? ('0'..'9')+;
fragment ASCII_LETTER : 'a'..'z' | 'A'..'Z';
fragment ESCAPE : '\\' ('\r'|'\n'|'\t'|'\b'|'\f'|'\"'|'\\'|'\'');

NEWLINE : ('\r'|'\n') {$channel=HIDDEN;};
WHITESPACE : (NEWLINE|'\t'|' ') {$channel=HIDDEN;};
