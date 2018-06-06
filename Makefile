
all: argv.o

build: argv.o

argv.o: argv.c argv.h
	$(CC) $(CFLAGS) -std=c99 -D_POSIX_C_SOURCE=200809L -c -o $@ argv.c

.PHONY: test
test:
	make -C test/ test

clean:
	-rm -f *.o
	-make -C test/ clean
