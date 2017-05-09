.PYONY: all clean

LDFLAGS := $(LDFLAGS) -g -DDEBUG_LEX -DDEBUG_XML -DDEBUG_YACC -DYYDEBUG=0
LDLIBS := $(LDLIBS) -ly -lmxml -lm
CC := gcc

all: common.c condition.c xml.c parse.tab.c
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)

parse.tab.c: lex.yy.c parse.y
	bison parse.y -v

lex.yy.c: lex.l
	flex $<

common.o: common.c

clean:
	rm -rf *.tab.c *.yy.c *.o all
