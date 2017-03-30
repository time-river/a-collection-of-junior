EXECS = hello
CC := /usr/bin/mpicc

all: ${EXECS}

hello: hello.c
	${CC} -o hello hello.c

clean:
	rm ${EXECS}
