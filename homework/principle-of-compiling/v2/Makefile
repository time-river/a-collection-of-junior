.PYONY: clean

LDFLAGS := $(LDFLAGS) -g -DDEBUG_LEX -DDEBUG_XML -DDEBUG_YACC -DYYDEBUG=1
LDLIBS := $(LDLIBS) -ly -lmxml -lm
CC := gcc

interpreter: common.c condition.c xml.c parse.tab.c
	$(CC) -o $@ $^ $(LDLIBS)

interpreter-gdb: common.c condition.c xml.c parse.tab.c
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)

interpreter-lex: common.c condition.c xml.c parse.tab.c
	$(CC) -o $@ $^ $(LDLIBS)  -DDEBUG_LEX

interpreter-yyac: common.c condition.c xml.c parse.tab.c
	$(CC) -o $@ $^ $(LDLIBS)  -DDEBUG_YACC

parse.tab.c: lex.yy.c parse.y
	bison parse.y -v

lex.yy.c: lex.l
	flex $<

common.o: common.c

clean:
	rm -rf *.tab.c *.yy.c *.o interpreter interpreter-gdb interpreter-lex interpreter-yyac
