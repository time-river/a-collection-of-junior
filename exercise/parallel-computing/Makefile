.PYONY: all, clean

EXECS = hello ping-pong
CC := /usr/bin/mpicc

all: ${EXECS}

hello: hello.c
	${CC} -o hello hello.c

ping-pong: ping-pong.c

clean:
	rm ${EXECS}

run:
	@mpirun -np 3 -f hosts ./hello

test:
	@mpirun -n 3 -host localhost ./hello
	@mpirun -n 2 -host localhost ./ping-pong
