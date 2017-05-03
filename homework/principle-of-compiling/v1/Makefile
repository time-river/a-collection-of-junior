.PYONY: test clean

LDFLAGS := $(LDFLAGS) -g

cc: find.lex parse.y common.c
	flex find.lex
	bison parse.y
	$(CC) -o $@ parse.tab.c common.c -ly -DDEBUG

test: test.c common.c

clean:
	rm -rf test cc *.yy.* *.tab.*
