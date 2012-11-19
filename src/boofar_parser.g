parser grammar boofar_parser;

options
{
	tokenVocab = boofar_lexer;
	language = Cpp;
}

@namespace
{
	generated
}

@includes
{
	#include "boofar_lexer.h"
	#include "boofar_traits.h"
	#include "boofar_nodes.h"

	#include <memory>

	namespace bn = boofar::nodes;
	using std::unique_ptr;
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

declaration returns [ boofar::nodes::declaration *node ]
	:
		type=identifier name=identifier
		{ node = new boofar::nodes::declaration(type, name); }
	;
/*
declaration returns [ boofar::nodes::declaration *node ] :
		type=IDENTIFIER name=IDENTIFIER {
			auto type_id = new boofar::nodes::identifier($type.text);
			auto name_id = new boofar::nodes::identifier($name.text);
			$node = new boofar::nodes::declaration(type_id, name_id);
		} ;
*/

parameter_list : ( declaration ( COMMA declaration )* )? ;

function_definition : FUNCTION IDENTIFIER LEFT_PARENTHESIS parameter_list RIGHT_PARENTHESIS LEFT_BRACE statement+ RIGHT_BRACE ;

assignment : IDENTIFIER EQUALS expression ;

unary_operation : atomic_expression | UNARY_OPERATOR expression ;

binary_operation : unary_operation BINARY_OPERATOR expression ;

literal :
		(
			OCT_LITERAL {/*boofar_parser_debug($OCT_LITERAL.text);*/}
		|	DEC_LITERAL {/*boofar_parser_debug($DEC_LITERAL.text);*/}
		|	HEX_LITERAL {/*boofar_parser_debug($HEX_LITERAL.text);*/}
		|	FLOAT_LITERAL {/*boofar_parser_debug($FLOAT_LITERAL.text);*/}
		)+
	;

identifier returns [ boofar::nodes::identifier *node ]
	:
		IDENTIFIER
		{ node = new boofar::nodes::identifier($IDENTIFIER.text); }
	;
