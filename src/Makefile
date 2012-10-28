CC = clang -m32 -ggdb3
CXX = clang++ -std=c++11 -m32 -ggdb3
ANTLR = antlr
ANTLRC_INSTALL = /usr/local
WARNFLAGS = -Wall -Wextra
COMPFLAGS = $(WARNFLAGS) -I$(ANTLRC_INSTALL)/include
CFLAGS = $(COMPFLAGS)
CXXFLAGS = $(COMPFLAGS)
LDLIBS = -lantlr3c
LDFLAGS = -L$(ANTLRC_INSTALL)/lib

# sources
PARSER_OBJS = boofar_parser.o boofar_parser_debug.o
PARSER_GEN = boofar_parser.h boofar_parser.c boofar_parser.tokens
LEXER_OBJS = boofar_lexer.o boofar_lexer_debug.o
LEXER_GEN = boofar_lexer.h boofar_lexer.c boofar_lexer.tokens
COMMON_OBJS = antlr3_cc.o boofar.o $(PARSER_OBJS) $(LEXER_OBJS)
COMPILER_OBJS = compiler.o $(COMMON_OBJS)
TESTS_OBJS = tests/suite.o tests/tokens.o $(COMMON_OBJS)

# collection variables
OBJS = $(COMPILER_OBJS) $(TESTS_OBJS)
DEPS = $(OBJS:%=deps/%)

# overwrite default rules
LINK.o = $(CXX) $(LDFLAGS) $(TARGET_ARCH)

all: compiler tests/suite

compiler: $(COMPILER_OBJS)
	$(CXX) $(LDFLAGS) $(TARGET_ARCH) -o $@ $^ $(LDLIBS)

tests/suite: $(TESTS_OBJS)
	$(CXX) $(LDFLAGS) $(TARGET_ARCH) -o $@ $^ $(LDLIBS)

tests/%.o: CXXFLAGS += -I.

depend: $(DEPS)

%.o: %.cc
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -MM -MT $@ $< > deps/$@
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -o $@ -c $<

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -MM -MT $@ $< > deps/$@
	$(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -o $@ -c $<

boofar_%.o: WARNFLAGS = -w

boofar_parser.g: boofar_lexer.tokens
compiler.o \
boofar.o \
boofar_lexer_debug.o \
tests/tokens.o: boofar_lexer.h boofar_parser.h
boofar_lexer_debug.o: boofar_lexer.h
boofar_parser_debug.o: boofar_parser.h
boofar_%.tokens boofar_%.h boofar_%.c: boofar_%.g
	$(ANTLR) $<

clean:
	$(RM) compiler tests/suite
	$(RM) $(OBJS)
	$(RM) $(DEPS)
	$(RM) $(PARSER_GEN) $(LEXER_GEN)

-include $(DEPS)
