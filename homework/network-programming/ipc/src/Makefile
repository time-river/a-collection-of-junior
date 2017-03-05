all: main

main: semaphore.o shm.o
main-gdb: semaphore.o shm.o

.PYONY: clean

clean:
	rm -rf *.o
	rm -rf main main-gdb
