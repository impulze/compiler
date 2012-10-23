parser grammar boofar_parser;

options
{
	tokenVocab = boofar_lexer;
	language = C;
}

parse : (DECIMAL | IDENTIFIER) + EOF;
