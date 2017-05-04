.PYONY: all clean

LDFLAGS := $(LDFLAGS) -g
LDLIBS := $(LDLIBS) -ly -lmxml

all: common.c xml.c parse.tab.c
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)

parse.tab.c: lex.yy.c parse.y
	bison parse.y

lex.yy.c: lex.l
	flex $<

common.o: common.c

clean:
	rm -rf *.tab.c *.yy.c *.o all
