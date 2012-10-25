#include "boofar_parser.h"

#include <iostream>

void boofar_parser_debug(ANTLR3_STRING *string)
{
	char *chars = reinterpret_cast<char *>(string->chars);

	std::cout << chars << std::endl;
}
