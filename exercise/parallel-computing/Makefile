.PYONY: all, clean

EXECS = hello ping-pong ring
CC := /usr/bin/mpicc

all: ${EXECS}

hello: hello.c
	${CC} -o hello hello.c

ping-pong: ping-pong.c

ring: ring.c

clean:
	rm ${EXECS} -rf

run:
	@mpirun -np 3 -f hosts ./hello

test:
	@mpirun -n 3 -host localhost ./hello
	@mpirun -n 2 -host localhost ./ping-pong
	@mpirun -n 5 -host localhost ./ring
