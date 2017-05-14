.PYONY: all clean

LDLIBS := -ly

all: calculate-1 calculate-2

calculate-1: calculate-1.y
	bison -o $@.c $<
	gcc -o $@ $@.c ${LDLIBS}

calculate-2: calculate-2.y
	bison -o $@.c $<
	gcc -o $@ $@.c ${LDLIBS}

clean:
	rm -rf calculate-1.c calculate-1 \
		calculate-2.c calculate-2
