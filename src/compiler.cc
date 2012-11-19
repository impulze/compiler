#include "boofar_lexer.h"
#include "boofar_parser.h"
#include "boofar_prettyprinter.h"
#include "boofar_traits.h"

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using std::cerr;
using std::cout;
using std::runtime_error;
using std::string;
using std::vector;

struct argument
{
	string help;
	string param;
	bool passed;
};

namespace
{
	inline bool passed(vector<argument> const &args, string const &param);
	inline void usage(vector<argument> const &args);
}

int main(int argc, char *argv[])
{
	vector<argument> args = {
		{ "tokenize only", "tokenize", false },
		{ "print the AST", "prettyprint", false },
	};

	if (argc < 2 || argc > 3)
	{
		usage(args);
	}

	if (argc == 3)
	{
		bool found = false;

		for (auto &arg: args)
		{
			if (string(argv[1]) == ("--" + arg.param))
			{
				found = true;
				arg.passed = true;
			}
		}

		if (!found)
		{
			usage(args);
		}
	}

	char const *filename;

	if (argc == 3)
	{
		filename = argv[2];
	}
	else
	{
		filename = argv[1];
	}

	ANTLR_UINT8 const *antlr_filename = reinterpret_cast<ANTLR_UINT8 const *>(filename);
	boofar::traits::InputStreamType input(antlr_filename, ANTLR_ENC_8BIT);
	boofar::lexer lexer(&input);
	boofar::traits::TokenStreamType token_stream(ANTLR_SIZE_HINT, lexer.get_tokSource());

	if (argc == 3)
	{
		if (passed(args, "tokenize"))
		{
			token_stream.fillBuffer();
			auto tokens = token_stream.get_tokens();

			cout << "tokenizing:\n";

			for (boofar::traits::TokenStreamType::TokenType &token: tokens)
			{
				cout << "token: " << token.getText() << '\n';
			}
		}
		else if (passed(args, "prettyprint"))
		{
			cout << "pretty printing:\n";

			boofar::visitors::prettyprinter prettyprinter(cout);
		}
	}
	else
	{
		cout << "declaration:\n";

		boofar::parser parser(&token_stream);

		auto result = parser.declaration();
		cout << result << '\n';
	}

	return 0;
}

namespace
{
	bool passed(vector<argument> const &args, string const &param)
	{
		for (auto &arg: args)
		{
			if (arg.param == param)
			{
				return arg.passed;
			}
		}

		return false;
	}

	void usage(vector<argument> const &args)
	{
		cerr << "parsing: ./compiler <filename>\n";

		for (auto const &arg: args)
		{
			cerr << arg.help << ": ./compiler --" << arg.param << " <filename>\n";
		}

		throw runtime_error("illegal arguments");
	}
}
