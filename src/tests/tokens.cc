#include <boofar.h>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(tokens)

BOOST_AUTO_TEST_CASE(valid_identifiers)
{
	antlr3::input_stream input_stream("./tests/test_identifiers_001.bf");
	boofar::lexer lexer(input_stream);
	antlr3::token_stream token_stream(lexer);
	std::vector<antlr3::common_token> tokens = token_stream.get_tokens();
	std::uint32_t const expected_types[] = {
		boofar::types::identifier,
		boofar::types::newline,
		boofar::types::identifier,
		boofar::types::newline,
		boofar::types::identifier,
		boofar::types::newline,
		boofar::types::identifier,
		boofar::types::newline,
		boofar::types::identifier,
		boofar::types::newline,
		boofar::types::identifier,
		boofar::types::newline
	};
	std::size_t const expected_amount = sizeof expected_types / sizeof *expected_types;

	BOOST_CHECK_EQUAL(tokens.size(), expected_amount);
	for (std::size_t i = 0; i < expected_amount && i < tokens.size(); i++)
	{
		BOOST_CHECK_EQUAL(tokens[i].get_type(), expected_types[i]);
	}
}

BOOST_AUTO_TEST_CASE(valid_literals)
{
	antlr3::input_stream input_stream("./tests/test_literals_001.bf");
	boofar::lexer lexer(input_stream);
	antlr3::token_stream token_stream(lexer);
	std::vector<antlr3::common_token> tokens = token_stream.get_tokens();
	std::uint32_t const expected_types[] = {
		boofar::types::oct_literal,
		boofar::types::newline,
		boofar::types::oct_literal,
		boofar::types::newline,
		boofar::types::dec_literal,
		boofar::types::newline,
		boofar::types::dec_literal,
		boofar::types::newline,
		boofar::types::hex_literal,
		boofar::types::newline,
		boofar::types::hex_literal,
		boofar::types::newline,
		boofar::types::hex_literal,
		boofar::types::newline,
		boofar::types::hex_literal,
		boofar::types::newline,
		boofar::types::float_literal,
		boofar::types::newline,
		boofar::types::float_literal,
		boofar::types::newline,
		boofar::types::float_literal,
		boofar::types::newline,
		boofar::types::float_literal,
		boofar::types::newline,
		boofar::types::float_literal,
		boofar::types::newline,
		boofar::types::float_literal,
		boofar::types::newline,
		boofar::types::float_literal,
		boofar::types::newline,
		boofar::types::float_literal,
		boofar::types::newline,
		boofar::types::float_literal,
		boofar::types::newline,
		boofar::types::float_literal,
		boofar::types::newline,
		boofar::types::float_literal,
		boofar::types::newline,
		boofar::types::float_literal,
		boofar::types::newline,
		boofar::types::float_literal,
		boofar::types::newline,
		boofar::types::float_literal,
		boofar::types::newline,
		boofar::types::float_literal,
		boofar::types::newline,
		boofar::types::float_literal,
		boofar::types::newline,
		boofar::types::float_literal,
		boofar::types::newline,
		boofar::types::float_literal,
		boofar::types::newline,
		boofar::types::float_literal,
		boofar::types::newline,
		boofar::types::float_literal,
		boofar::types::newline,
		boofar::types::float_literal,
		boofar::types::newline,
		boofar::types::float_literal,
		boofar::types::newline,
		boofar::types::float_literal,
		boofar::types::newline,
		boofar::types::float_literal,
		boofar::types::newline,
		boofar::types::float_literal,
		boofar::types::newline,
		boofar::types::float_literal,
		boofar::types::newline,
		boofar::types::float_literal,
		boofar::types::newline,
		boofar::types::float_literal,
		boofar::types::newline,
		boofar::types::float_literal,
		boofar::types::newline,
		boofar::types::float_literal,
		boofar::types::newline,
		boofar::types::float_literal,
		boofar::types::newline,
		boofar::types::float_literal,
		boofar::types::newline,
		boofar::types::float_literal,
		boofar::types::newline
	};
	std::size_t const expected_amount = sizeof expected_types / sizeof *expected_types;

	BOOST_CHECK_EQUAL(tokens.size(), expected_amount);
	for (std::size_t i = 0; i < expected_amount && i < tokens.size(); i++)
	{
		BOOST_CHECK_EQUAL(tokens[i].get_type(), expected_types[i]);
	}
}

BOOST_AUTO_TEST_SUITE_END()
