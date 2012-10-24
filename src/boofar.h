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

		void parse();
	};
}

