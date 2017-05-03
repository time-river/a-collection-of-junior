.PYONY: all clean

LDLIBS := $(LDLIBS) -ly

sql: lex.l parse.y common.c
	flex lex.l
	bison parse.y
	$(CC) -o $@ parse.tab.c common.c $(LDLIBS)

clean:
	rm -rf *.tab.c *.yy.c sql
