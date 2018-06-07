
LDFLAGS+=$$(pkg-config --libs check)
CFLAGS+=$$(pkg-config --cflags check)

all: argv

test: argv
	./argv

argv: argv.c ../argv.c
	$(CC) $(CFLAGS) $+ -o $@ $(LDFLAGS)

clean:
	-rm -f argv
