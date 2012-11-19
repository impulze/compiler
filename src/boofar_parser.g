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

	namespace nodes = boofar::nodes;
	using std::unique_ptr;
}

program : statement+ ;

statement :
		( declaration | expression ) SEMICOLON
	|	function_definition
	;

expression returns [ nodes::generic *node ] :
		assignment { node = assignment(); }
	|	binary_operation { node = binary_operation(); }
	;

atomic_expression returns [ nodes::generic *node ] :
		literal { node = literal(); }
	|	identifier { node = identifier(); }
	|	LEFT_PARENTHESIS expression RIGHT_PARENTHESIS { node = expression(); }
	;

declaration returns [ nodes::declaration *node ] :
		type=identifier name=identifier { node = new nodes::declaration(type, name); }
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

assignment returns [ nodes::assignment *node ] :
		identifier EQUALS expression
		{ node = new nodes::assignment(identifier(), expression()); }
	;

unary_operation : atomic_expression | UNARY_OPERATOR expression ;

binary_operation returns [ nodes::binary_operation *node ] :
		unary_operation BINARY_OPERATOR expression 
	;

literal returns [ nodes::literal *node ]
	:
			OCT_LITERAL
			{
				node = new nodes::octal_literal($OCT_LITERAL.text);
				/* boofar_parser_debug($OCT_LITERAL.text); */
			}
		|	DEC_LITERAL
			{
				node = new nodes::decimal_literal($DEC_LITERAL.text);
				/* boofar_parser_debug($DEC_LITERAL.text); */
			}
		|	HEX_LITERAL
			{
				node = new nodes::hexadecimal_literal($HEX_LITERAL.text);
				/* boofar_parser_debug($HEX_LITERAL.text); */
			}
		|	FLOAT_LITERAL
			{
				node = new nodes::float_literal($FLOAT_LITERAL.text);
				/* boofar_parser_debug($FLOAT_LITERAL.text); */
			}
	;

identifier returns [ nodes::identifier *node ]
	:
		IDENTIFIER
		{ node = new nodes::identifier($IDENTIFIER.text); }
	;
