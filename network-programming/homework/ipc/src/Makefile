all: main

main: semaphore.o shm.o
main-gdb: semaphore.o shm.o

.PYONY: clean

clean:
	-rm -f *.o
	-rm -f main main-gdb

CC += -g
