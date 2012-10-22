#include "boofar_lexer.h"
#include "boofar_parser.h"

int main(int, char *argv[])
{
	pANTLR3_UINT8 const filename = reinterpret_cast<pANTLR3_UINT8>(argv[1]);
	pANTLR3_INPUT_STREAM const input = antlr3FileStreamNew(filename, ANTLR3_ENC_UTF8);
	pboofar_lexer const lexer = boofar_lexerNew(input);
	pANTLR3_COMMON_TOKEN_STREAM tokens = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT, TOKENSOURCE(lexer));
	pboofar_parser const parser = boofar_parserNew(tokens);

	parser->parse(parser);

	parser->free(parser);
	tokens->free(tokens);
	lexer->free(lexer);
	input->close(input);

	return 0;
}
