.PYONY: all, clean

LDLIBS = -lGL -lGLU -lglut -lm
CC := /usr/bin/mpicc

mpi: mpi_main.c
	${CC} -o mpi mpi_main.c ${LDLIBS} -g

test:
	@mpirun -np 2 -host localhost ${PWD}/mpi

test-gdb:
	@mpirun -np 2 xterm -e gdb ${PWD}/mpi

clean:
	rm -rf mpi
