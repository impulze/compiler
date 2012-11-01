#include "antlr3_cc.h"
#include "boofar_lexer.h"
#include "boofar_parser.h"

namespace boofar
{
	class lexer
		: public antlr3::lexer_factory<boofar_lexer>
	{
	public:
		explicit lexer(antlr3::input_stream &);

	private:
		static ANTLR3_TOKEN_SOURCE *get_token_source(boofar_lexer *lexer);
	};

	class parser
		: public antlr3::parser_factory<boofar_parser>
	{
	public:
		explicit parser(antlr3::token_stream &);

		antlr3::generic_parse_return program();
		antlr3::generic_parse_return statement();
		antlr3::generic_parse_return expression();
		antlr3::generic_parse_return atomic_expression();
		antlr3::generic_parse_return declaration();
		antlr3::generic_parse_return assignment();
		antlr3::generic_parse_return unary_operation();
		antlr3::generic_parse_return binary_operation();
		antlr3::generic_parse_return literal();
	};

	namespace types
	{
		enum type
		{
			oct_literal = OCT_LITERAL,
			hex_literal = HEX_LITERAL,
			dec_literal = DEC_LITERAL,
			float_literal = FLOAT_LITERAL,
			//string_literal = STRING_LITERAL,
			identifier = IDENTIFIER,
			comment = COMMENT,
			newline = NEWLINE
		};
	}

	typedef types::type type;
}
