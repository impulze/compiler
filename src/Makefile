CC = clang -m32
CXX = clang++ -std=c++11 -m32
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
LEXER_OBJS = boofar_lexer.o
LEXER_GEN = boofar_lexer.h boofar_lexer.c boofar_lexer.tokens
COMPILER_OBJS = antlr3_cc.o compiler.o $(PARSER_OBJS) $(LEXER_OBJS)

# collection variables
OBJS = $(COMPILER_OBJS)
DEPS = $(OBJS:%=deps/%)

# overwrite default rules
LINK.o = $(CXX) $(LDFLAGS) $(TARGET_ARCH)

all: compiler

compiler: $(COMPILER_OBJS)
	$(CXX) $(LDFLAGS) $(TARGET_ARCH) -o $@ $^ $(LDLIBS)

depend: $(DEPS)

%.o: %.cc
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -MM -MT $@ $< > deps/$@
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -o $@ -c $<

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -MM -MT $@ $< > deps/$@
	$(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -o $@ -c $<

boofar_%.o: WARNFLAGS = -w

compiler.cc: boofar_lexer.h boofar_parser.h

boofar_%.h boofar_%.c: boofar_%.g
	$(ANTLR) $<

clean:
	$(RM) compiler
	$(RM) $(OBJS)
	$(RM) $(DEPS)
	$(RM) $(PARSER_GEN) $(LEXER_GEN)

-include $(DEPS)
