parser grammar boofar_parser;

options
{
	tokenVocab = boofar_lexer;
	language = C;
}

@header
{
	#include <antlr3.h>
	void boofar_parser_debug(ANTLR3_STRING *string);
}

parse : (
		DECIMAL {boofar_parser_debug($DECIMAL.text);}
		| IDENTIFIER {boofar_parser_debug($IDENTIFIER.text);}
	) + EOF;
