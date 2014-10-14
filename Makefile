CC = g++
CFLAGS = -Wall -Wextra -g3 

all: digitalClockSync.out digitalClockSyncBounded1.out leaderElectionGeneral.out

digitalClockSync.out: digitalClockSync.cpp
	$(CC) $(CFLAGS) -o $@ $^

digitalClockSyncBounded1.out: digitalClockSyncBounded1.cpp
	$(CC) $(CFLAGS) -o $@ $^

leaderElectionGeneral.out: leaderElectionGeneral.cpp
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm digitalClockSync.out
