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
COMPILER_OBJS = compiler.o $(COMMON_OBJS)
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

boofar_%.o: WARNFLAGS = -w

boofar_parser.g: boofar_lexer.tokens
compiler.o \
boofar.o \
boofar_nodes.o \
boofar_lexer_debug.o \
tests/tokens.o: boofar_lexer.h boofar_parser.h
boofar_lexer_debug.o: boofar_lexer.h
boofar_parser_debug.o: boofar_parser.h
boofar_%.tokens boofar_%.h boofar_%.cpp: boofar_%.g
	$(ANTLR) $<

clean:
	$(RM) compiler tests/suite
	$(RM) $(OBJS)
	$(RM) $(DEPS)
	$(RM) $(PARSER_GEN) $(LEXER_GEN)

-include $(DEPS)
-include config.mk
