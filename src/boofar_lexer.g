lexer grammar boofar_lexer;

options
{
	language = C;
}

@header
{
	#include <antlr3.h>

	extern void boofar_lexer_report_error(ANTLR3_BASE_RECOGNIZER *recognizer);
	extern void (*g_antlr3_report_error)(ANTLR3_BASE_RECOGNIZER *recognizer);
}

@apifuncs
{
	// save previous functions and replace with custom
	g_antlr3_report_error = RECOGNIZER->reportError;
	RECOGNIZER->reportError = boofar_lexer_report_error;
}

OCT_LITERAL : '0' ('o'|'O') OCT_DIGIT+;
HEX_LITERAL : '0' ('x'|'X') HEX_DIGIT+;
DEC_LITERAL : DEC_DIGIT+;
FLOAT_LITERAL : DEC_LITERAL '.' DEC_DIGIT* EXPONENT?
	| '.' DEC_DIGIT+ EXPONENT?
	| DEC_LITERAL EXPONENT
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
fragment ASCII_LETTER : 'a'..'z'|'A'..'Z';
fragment ESCAPE : '\\' ('\r'|'\n'|'\t'|'\b'|'\f'|'\"'|'\\'|'\'');

NEWLINE : ('\r'|'\n') {$channel=HIDDEN;};
WHITESPACE : (NEWLINE|'\t'|' ') {$channel=HIDDEN;};
