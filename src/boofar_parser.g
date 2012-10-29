parser grammar boofar_parser;

options
{
	tokenVocab = boofar_lexer;
	language = C;
	output = AST;
}

@header
{
	#include <antlr3.h>
	void boofar_parser_debug(ANTLR3_STRING *string);
}

parse : (
		OCT_LITERAL {boofar_parser_debug($OCT_LITERAL.text);}
		| DEC_LITERAL {boofar_parser_debug($DEC_LITERAL.text);}
		| HEX_LITERAL {boofar_parser_debug($HEX_LITERAL.text);}
		| FLOAT_LITERAL {boofar_parser_debug($FLOAT_LITERAL.text);}
		| IDENTIFIER {boofar_parser_debug($IDENTIFIER.text);}
	) + EOF;
