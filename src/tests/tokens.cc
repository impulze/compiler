#include <boofar.h>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(tokens)

BOOST_AUTO_TEST_CASE(valid_identifiers)
{
	antlr3::input_stream input_stream("./tests/test_identifiers_001.bf");
	boofar::lexer lexer(input_stream);
	antlr3::token_stream token_stream(lexer);
	std::vector<antlr3::common_token> tokens = token_stream.get_tokens();

	for (antlr3::common_token &token: tokens)
	{
		std::cout << "token: " << token.to_string() << std::endl;
	}
}

BOOST_AUTO_TEST_CASE(valid_literals)
{
	antlr3::input_stream input_stream("./tests/test_literals_001.bf");
	boofar::lexer lexer(input_stream);
	antlr3::token_stream token_stream(lexer);
	std::vector<antlr3::common_token> tokens = token_stream.get_tokens();

	for (antlr3::common_token &token: tokens)
	{
		std::cout << "token: " << token.to_string() << std::endl;
	}
}

BOOST_AUTO_TEST_SUITE_END()
