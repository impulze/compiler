parser grammar boofar_parser;

options
{
	tokenVocab = boofar_lexer;
	language = C;
	output = AST;
}

@header
{
}

@includes
{
	#include "antlr3_cc.h"
	#include "boofar_nodes.h"

	#include <antlr3.h>
	#include <memory>

	namespace bn = boofar::nodes;
	using std::unique_ptr;

	void boofar_parser_debug(ANTLR3_STRING *string);
}

program : statement+ ;

statement :
		( declaration | expression ) SEMICOLON
	|	function_definition ;

expression :
		assignment
	|	binary_operation
	;

atomic_expression :
		literal
	|	IDENTIFIER
	|	LEFT_PARENTHESIS expression RIGHT_PARENTHESIS
	;

declaration returns [ unique_ptr<bn::declaration> node ] :
		type=IDENTIFIER name=IDENTIFIER {
			auto typestr = antlr3::common_token(type);
			auto namestr = antlr3::common_token(name);
			auto typeid_ = bn::identifier(typestr.to_string());
			auto nameid_ = bn::identifier(namestr.to_string());

			$node.reset(new bn::declaration(&typeid_, &nameid_));
		} ;

parameter_list : ( declaration ( COMMA declaration )* )? ;

function_definition : FUNCTION IDENTIFIER LEFT_PARENTHESIS parameter_list RIGHT_PARENTHESIS LEFT_BRACE statement+ RIGHT_BRACE ;

assignment : IDENTIFIER EQUALS expression ;

unary_operation : atomic_expression | UNARY_OPERATOR expression ;

binary_operation : unary_operation BINARY_OPERATOR expression ;

literal :
		(
			OCT_LITERAL {boofar_parser_debug($OCT_LITERAL.text);}
		|	DEC_LITERAL {boofar_parser_debug($DEC_LITERAL.text);}
		|	HEX_LITERAL {boofar_parser_debug($HEX_LITERAL.text);}
		|	FLOAT_LITERAL {boofar_parser_debug($FLOAT_LITERAL.text);}
		)+
	;
