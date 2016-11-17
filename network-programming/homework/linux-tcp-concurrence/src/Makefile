all: main client

main: event.o io.o

.PYONY: clean

clean:
	-rm -f *.o
	-rm -f main client

CC += -g
