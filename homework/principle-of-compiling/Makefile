.PYONY: all clean

EXECS := test-scanner

test-scanner: test-find.lex
	flex -o $@.c $<
	gcc -o $@ $@.c -D DEBUG

clean:
	rm -rf test-scanner*
