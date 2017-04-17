.PYONY: all, clean

EXECS := mpi single-serial double-serial

LDLIBS = -lGL -lGLU -lglut -lm
MPICC := /usr/bin/mpicc
CC := /usr/bin/gcc

all: ${EXECS}

single-serial: single-serial-main.c
	${CC} -o $@ $^ ${LDLIBS}

double-serial: double-serial-main.c
	${CC} -o $@ $^ ${LDLIBS}

mpi: mpi-main.c
	${MPICC} -o $@ $^ ${LDLIBS}

mpi-gdb: mpi-main.c
	${MPICC} -o $@ $^ ${LDLIBS} -g

test-single:
	@${PWD}/single-serial

test-double:
	@${PWD}/double-serial

test-mpi:
	@mpirun -np 4 -host localhost ${PWD}/mpi

test-mpi-multimachine:
	@mpirun -np 2 -host localhost ${PWD}/mpi

test-mpi-gdb: mpi-gdb
	@mpirun -np 2 xterm -e gdb ${PWD}/mpi-gdb

clean:
	rm -rf ${EXECS} mpi-gdb
