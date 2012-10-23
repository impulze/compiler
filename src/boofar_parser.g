parser grammar boofar_parser;

options
{
	tokenVocab = boofar_lexer;
	language = C;
}

@header
{
#include "boofar_parser_debug.h"
}

parse : (
		DECIMAL {boofar_parser_debug($DECIMAL.text);}
		| IDENTIFIER {boofar_parser_debug($DECIMAL.text);}
	) + EOF;
