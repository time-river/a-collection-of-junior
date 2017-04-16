.PYONY: all, clean

EXECS = hello
CC := /usr/bin/mpicc

all: ${EXECS}

hello: hello.c
	${CC} -o hello hello.c

clean:
	rm ${EXECS}

run:
	@mpirun -np 3 -f hosts ./hello

test:
	@mpirun -n 3 -host localhost ./hello
