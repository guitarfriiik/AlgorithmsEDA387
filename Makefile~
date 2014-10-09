CC = g++
CFLAGS = -Wall -Wextra -g3 

all: client-multi.out client-simple.out server-concurrent.out

client-multi.out: client-multi.cpp
	$(CC) $(CFLAGS) -o $@ $^

client-simple.out: client-simple.cpp
	$(CC) $(CFLAGS) -o $@ $^

server-concurrent.out: server-iterative.cpp
	$(CC) $(CFLAGS) -o $@ $^
clean:
	rm client-multi.out client-simple.out server-concurrent.out
