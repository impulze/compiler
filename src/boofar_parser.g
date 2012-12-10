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
program returns [ const nodes::block *node ] :
		prog=block { node = prog; }
	;

block returns [ const nodes::block *node ]
		scope
		{ std::vector<const nodes::generic *> statements; } :
	
		( stat=statement { $block::statements.push_back(stat); } )+
		{ node = new nodes::block(std::move($block::statements)); }
	;

statement returns [ const nodes::generic *node ] :
		( gen=declaration | gen=expression ) SEMICOLON
		{ node = gen; }
	|	cond=condition { node = cond; }
//	|	function_definition
	;

declaration returns [ const nodes::declaration *node ] :
		type=identifier name=identifier
		{ node = new nodes::declaration(type, name); }
	;

expression returns [ const nodes::generic *node ] :
		ass=assignment { node = ass; }
	|	op=operation { node = op; }
	;

condition returns [ const nodes::condition *node ]
	scope
	{
		const nodes::generic *else_node;
	} :
		{ $condition::else_node = &nodes::null::instance(); }
		IF LEFT_PARENTHESIS exp=expression RIGHT_PARENTHESIS bl=braced_block
		(
			ELSE
			(	econd=condition { $condition::else_node = econd; }
			|	eblock=braced_block { $condition::else_node = eblock; }
			)
		)?
		{ node = new nodes::condition(exp, bl, $condition::else_node); }
	;

braced_block returns [ const nodes::block *node ] :
		LEFT_BRACE bbl=block RIGHT_BRACE
		{ node = bbl; }
	;

assignment returns [ const nodes::assignment *node ] :
		id=identifier EQUALS exp=expression
		{ node = new nodes::assignment(id, exp); }
	;

operation returns [ const nodes::generic *node ]
	scope
	{
		const nodes::generic *left;
		const nodes::generic *right;
	} :
		{ $operation::left = $operation::right = &nodes::null::instance(); }
		(	unop=unary_operation { $operation::left = unop; }
		|	aexp=atomic_expression { $operation::left = aexp;}
		)
		(	( binop=BINARY_OPERATOR | binop = MINUS )  exp=expression
			{ $operation::right = exp; }
		)?
		{
			if ($operation::right == &nodes::null::instance())
			{ node = $operation::left; }
			else
			{
				node = new nodes::binary_operation($binop.text,
					$operation::left, $operation::right);
			}
		}
		;

unary_operation returns [ const nodes::unary_operation *node ] :
		( unop=UNARY_OPERATOR | unop=MINUS ) aexp=atomic_expression
		{ node = new nodes::unary_operation($unop.text, aexp); }
	;

atomic_expression returns [ const nodes::generic *node ] :
		lit=literal { node = lit; }
	|	id=identifier { node = id; }
	|	LEFT_PARENTHESIS exp=expression RIGHT_PARENTHESIS { node = exp; }
	;

// parameter_list : ( declaration ( COMMA declaration )* )? ;

// function_definition : FUNCTION IDENTIFIER LEFT_PARENTHESIS parameter_list RIGHT_PARENTHESIS LEFT_BRACE statement+ RIGHT_BRACE ;

literal returns [ const nodes::literal *node ]
	:
			OCT_LITERAL
			{
				node = new nodes::octal_literal($OCT_LITERAL.text);
				// boofar_parser_debug($OCT_LITERAL.text);
			}
		|	DEC_LITERAL
			{
				node = new nodes::decimal_literal($DEC_LITERAL.text);
				// boofar_parser_debug($DEC_LITERAL.text);
			}
		|	HEX_LITERAL
			{
				node = new nodes::hexadecimal_literal($HEX_LITERAL.text);
				// boofar_parser_debug($HEX_LITERAL.text);
			}
		|	FLOAT_LITERAL
			{
				node = new nodes::float_literal($FLOAT_LITERAL.text);
				// boofar_parser_debug($FLOAT_LITERAL.text);
			}
	;

identifier returns [ const nodes::identifier *node ]
	:
		IDENTIFIER
		{ node = new nodes::identifier($IDENTIFIER.text); }
	;
