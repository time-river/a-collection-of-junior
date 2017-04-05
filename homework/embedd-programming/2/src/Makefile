.PYONY: all, static, shared, test, clean

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(shell pwd)

all: static shared test clean

static: call.o libfun.o
	$(CC) -o $@ $^ 

shared: libfun.o
	$(CC) -fPIC -shared -o libfun.so $^
	$(CC) -o $@ call.c -L. -lfun

test:
	@echo "----------------------------test--------------------------------"
	$(shell pwd)/static
	$(shell pwd)/shared

clean:
	rm -rf *.o static shared libfun.so
