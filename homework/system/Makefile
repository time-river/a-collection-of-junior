all: 1 2 3 4 5 6

1: 1~create-process

2:
	gcc -o 2~thread-share-data 2~thread-share-data.c -pthread

3: 3~signal

4: 4~anonymous-pipe

5: 5~semaphore

6: 6~share-memory-reader 6~share-memory-writer

7: 7~named-pipe-reader 7~named-pipe-writer

.PYONY: clean

clean:
	rm -rf 1~create-process \
		2~thread-share-data \
		3~signal \
		4~anonymous-pipe \
		5~semaphore \
		6~share-memory-reader 6~share-memory-writer \
		7~named-pipe-reader 7~named-pipe-writer
