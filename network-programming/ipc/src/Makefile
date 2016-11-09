all: main

main: semaphore.o shm.o
main-gdb: main

.PYONY: clean

clean:
	-rm *.o
	-rm main

CC += -g
