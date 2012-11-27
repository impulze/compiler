CC = clang++ -std=c++0x -ggdb3
CXX = clang++ -std=c++0x -ggdb3
ANTLR = antlr
WARNFLAGS = -Wall -Wextra
COMPFLAGS = $(WARNFLAGS) -I$(ANTLRCPP)
CFLAGS = $(COMPFLAGS)
CXXFLAGS = $(COMPFLAGS)

# sources
PARSER_OBJS = boofar_parser.o
# boofar_parser_debug.o
PARSER_GEN = boofar_parser.hpp boofar_parser.cpp boofar_parser.tokens
LEXER_OBJS = boofar_lexer.o
# boofar_lexer_debug.o
LEXER_GEN = boofar_lexer.hpp boofar_lexer.cpp boofar_lexer.tokens
COMMON_OBJS = boofar_nodes.o $(PARSER_OBJS) $(LEXER_OBJS)
COMPILER_OBJS = boofar_code_generator.o boofar_prettyprinter.o compiler.o $(COMMON_OBJS)
TESTS_OBJS = tests/suite.o tests/tokens.o $(COMMON_OBJS)

# collection variables
OBJS = $(COMPILER_OBJS) $(TESTS_OBJS)
DEPS = $(OBJS:%=deps/%)

# overwrite default rules
LINK.o = $(CXX) $(LDFLAGS) $(TARGET_ARCH)

all: compiler
# tests/suite

compiler: $(COMPILER_OBJS)
	$(CXX) $(LDFLAGS) $(TARGET_ARCH) -o $@ $^ $(LDLIBS)

tests/suite: $(TESTS_OBJS)
	$(CXX) $(LDFLAGS) $(TARGET_ARCH) -o $@ $^ $(LDLIBS)

tests/%.o: CXXFLAGS += -I.

depend: $(DEPS)

%.o: %.cc
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -MM -MT $@ $< > deps/$@
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -o $@ -c $<

boofar_parser.o boofar_lexer.o: WARNFLAGS = -w

boofar_lexer_debug.cc: boofar_lexer.h
boofar_parser_debug.cc: boofar_parser.h
compiler.cc: boofar_lexer.h boofar_parser.h

boofar_lexer.h: boofar_lexer.hpp
boofar_lexer.tokens boofar_lexer.hpp boofar_lexer.cpp: boofar_lexer.g
	$(ANTLR) $<

boofar_parser.g: boofar_lexer.tokens
boofar_parser.h: boofar_parser.hpp
boofar_parser.tokens boofar_parser.hpp boofar_parser.cpp: boofar_parser.g
	$(ANTLR) $<

clean:
	$(RM) compiler tests/suite
	$(RM) $(OBJS)
	$(RM) $(DEPS)
	$(RM) $(PARSER_GEN) $(LEXER_GEN)

-include $(DEPS)
-include config.mk
