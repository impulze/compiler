lexer grammar boofar_lexer;

options
{
	language = C;
}

DECIMAL : DIGIT+;
IDENTIFIER : ASCII_LETTER+;

COMMENT : '//' ~('\n'|'\r')* '\r'? '\n' {$channel=HIDDEN;}
	| '/*' ( options {greedy=false;} : . )* '*/' {$channel=HIDDEN;}
	;

fragment DIGIT : '0'..'9';
fragment ASCII_LETTER : 'a'..'z' | 'A'..'Z';

NEWLINE : ('\r'|'\n') {$channel=HIDDEN;};
WHITESPACE : (NEWLINE|'\t'|' ') {$channel=HIDDEN;};
