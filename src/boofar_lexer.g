lexer grammar boofar_lexer;

options
{
	language = C;
}

INTEGER : '0'..'9'+
	;

COMMENT : '//' ~('\n'|'\r')* '\r'? '\n' {$channel=HIDDEN;}
	// |   '/*' ( options {greedy=false;} : . )* '*/' {$channel=HIDDEN;}
	;

WHITESPACE : (
	' '
	| '\t'
	| '\r'
	| '\n'
	) {$channel=HIDDEN;}
	;
