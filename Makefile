CC=g++
CFLAGS=-I
CFLAGS+=-Wall
FILES=pipe.cpp

pipe: $(FILES)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f *.o pipe

all: pipe
