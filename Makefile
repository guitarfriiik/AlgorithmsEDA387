CC = g++
CFLAGS = -Wall -Wextra -g3 

all: digitalClockSync.out

digitalClockSync.out: digitalClockSync.cpp
	$(CC) $(CFLAGS) -o $@ $^
clean:
	rm digitalClockSync.out
