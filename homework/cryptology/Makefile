.PYONY: all, clean
LDLIBS := -D DEBUG

EXECS := caesar single-table affine

all: ${EXECS}

caesar: caesar.c

single-table: single-table.c

affine: affine.c

clean:
	rm -rf ${EXECS}
