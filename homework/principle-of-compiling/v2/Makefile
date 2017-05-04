.PYONY: all clean

LDLIBS := $(LDLIBS) -ly

all: common.c parse.tab.c
	$(CC) -o $@ $^

parse.tab.c: lex.yy.c parse.y
	bison parse.y

lex.yy.c: lex.l
	flex $<

common.o: common.c

clean:
	rm -rf *.tab.c *.yy.c *.o all
