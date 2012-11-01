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

program : statement+ ;

statement : ( declaration | expression ) SEMICOLON ;

expression :
		assignment
	|	binary_operation
	;

atomic_expression :
		literal
	|	IDENTIFIER
	|	LEFT_PARENTHESIS expression RIGHT_PARENTHESIS
	;

declaration : IDENTIFIER IDENTIFIER ;

assignment : IDENTIFIER EQUALS expression ;

unary_operation : atomic_expression | UNARY_OPERATOR expression ;

binary_operation : unary_operation ( BINARY_OPERATOR expression )* ;

literal :
		(
			OCT_LITERAL {boofar_parser_debug($OCT_LITERAL.text);}
		|	DEC_LITERAL {boofar_parser_debug($DEC_LITERAL.text);}
		|	HEX_LITERAL {boofar_parser_debug($HEX_LITERAL.text);}
		|	FLOAT_LITERAL {boofar_parser_debug($FLOAT_LITERAL.text);}
		)+
	;
