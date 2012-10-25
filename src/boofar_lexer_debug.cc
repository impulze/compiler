#include "boofar_lexer.h"

void (*g_antlr3_report_error)(ANTLR3_BASE_RECOGNIZER *);

void boofar_lexer_report_error(ANTLR3_BASE_RECOGNIZER *recognizer)
{
	g_antlr3_report_error(recognizer);
}
