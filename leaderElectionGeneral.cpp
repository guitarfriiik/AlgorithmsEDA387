#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <time.h>  

#include <string.h>

#include <vector>
#include <algorithm>

#define n 10
#define NONBLOCKING 0


const int kServerPort = 5789;

const size_t kTransferBufferSize = 64;

const int kServerBacklog = 8;

typedef struct {
    int leader, distance;
    int numberOfNeighbors;
    int clock, min;
    int neighbors[10]; // May contain at most 10 neighbors
    int *inputs; // This is the recieve channel
    int **outputs; // This is the output channels
}process;

process processes[n];

void initAndRoute();
void printState();
int awaitRequest(int fd);

static int setup_server_socket( short port );
void sendState(int fd);

void randomize(void);
void fault(void);

int main()
{
    int serverPort = kServerPort;
    int listenfd = setup_server_socket( serverPort );

    initAndRoute();

    sockaddr_in clientAddr;
    socklen_t addrSize = sizeof(clientAddr);

    int clientfd = accept( listenfd, (sockaddr*)&clientAddr, &addrSize );

    if( -1 == clientfd )
	{
	    perror( "accept() failed" );
	    return 1;
	}
    
    sendState(clientfd);
    // Create a dummy recieve - use instead of getChar and fix the ending

    while(true){
	

	/******************************* This is the psuedo code for the algorithm *******************/

	for(int i = 0; i < n; i++){
	    
	    /*
	     * 
	     * Do for ever for all processors
	     *
	     */
     	    int candidate = i;
	    int distance = 0;

	    for(int j = 0; j < processes[i].numberOfNeighbors; j++){
		int tempLeader = processes[j].leader;
		int tempDistance = processes[j].distance;
		
		if(((tempDistance < n-1) && (tempLeader < candidate)) || ((tempLeader == candidate) && (tempDistance < distance))){
		    candidate = tempLeader;
		    distance = tempDistance+1;
		}

	    }

	    processes[i].leader = candidate;
	    processes[i].distance = distance;

	}
	/********************************************************************************************/

	/** Send the new state */
	int ret = awaitRequest(clientfd);
	if(ret == 0 || ret == -1)
	    break;
	sendState(clientfd);
	
    }
    close(listenfd);
    close(clientfd);
    return 0;
}

int awaitRequest(int fd){
    char recvBuff[1024];
    memset(recvBuff, 0 ,sizeof(recvBuff));
    ssize_t num = recv(fd, recvBuff, sizeof(recvBuff)-1, 0); // For now, just block untill the gui request the next results.. (Dont care about the result..)
    if(strncmp(recvBuff, "fault", 1024-1) == 0){
	fault();
    }
    else if(strncmp(recvBuff, "randomize", 1024-1) == 0){
	randomize();
    }
    return (int)num;
}


void randomize(void){
    /*
     * Randomize clocks..
     *
     */
    srand (time(NULL));
    for (int i = 0; i < n; i++) {
	processes[i].leader = rand() % 100;
	srand (time(NULL));
	processes[i].distance = rand() % 100;
    }
}
void fault(void){
    // Randomly inject a fault in one of the processors
    srand (time(NULL));
    int i = rand() % 10 - 1;
    int temp = rand() % 100;
    while(processes[i].clock == temp)
	temp = rand() % 100;
    processes[i].clock = temp;
}


void sendState(int fd){
    char tempChar[10];
    char stringToSend[100];
    memset(stringToSend, 0 ,sizeof(stringToSend));
    for(int i = 0; i<n; i++){
	memset(tempChar, 0 ,sizeof(tempChar));
	
	sprintf(tempChar, "%d;%d,", processes[i].leader, processes[i].distance);
	strcat(stringToSend, tempChar);
    }

    write(fd, stringToSend, strlen(stringToSend));
    
}

void printState(){
    printf("       %d                                        \n       +                                         \n       |     %d                                  \n       |     +                                   \n       |     |    %d                             \n    +--+--+  |    +      %d                      \n    |  10 |  |    |      +                       \n    +--+--+  |    |      |                       \n       |     |    |   +--+--+                    \n       |     |    |   |  2  +-----------+        \n       |     |    |   +--+--+           |        \n    +--+--+  |    |      |           +--+--+     \n    |  9  +--+    +---+  |      +----+  3  +-+ %d\n    +--+--+           |  |      |    +--+--+     \n       |              +--+--+   |       |        \n       +--------------+  1  +---+       |        \n                      +--+--+           |        \n                      |  |              |        \n       +--------------+  |           +--+--+     \n       |                 |           |  4  +-+ %d\n    +--+--+              |           +--+--+     \n+---+  6  +----+         |              |        \n|   +--+--+    |      +--+--+           |        \n|      |       +------+  5  +-----------+        \n|      |              +--+--+                    \n|   +--+--+              |                       \n|   |  7  +--+           +---+ %d                \n|   +--+--+  |                                   \n|      |     +---+ %d                            \n|      |                                         \n|   +--+--+                                      \n|   |  8  +---+ %d                               \n|   +-----+                                      \n|                                                \n+---+ %d                                         \n",
	   processes[9].clock, processes[8].clock, processes[0].clock, processes[1].clock, processes[2].clock, processes[3].clock, processes[4].clock, processes[6].clock, processes[7].clock, processes[5].clock);//10,9,1,2,3,4,5,7,8,6); // This is the order
}

void initAndRoute(){
    // Assign the number of neighbors
    processes[0].numberOfNeighbors = 5;
    processes[1].numberOfNeighbors = 2;
    processes[2].numberOfNeighbors = 3;
    processes[3].numberOfNeighbors = 2;
    processes[4].numberOfNeighbors = 3;
    processes[5].numberOfNeighbors = 3;
    processes[6].numberOfNeighbors = 2;
    processes[7].numberOfNeighbors = 1;
    processes[8].numberOfNeighbors = 2;
    processes[9].numberOfNeighbors = 1;
    /********** Double check this part **********************************/
    
    processes[0].neighbors[0] = 1;
    processes[0].neighbors[1] = 2;
    processes[0].neighbors[2] = 4;
    processes[0].neighbors[3] = 5;
    processes[0].neighbors[4] = 8;

    processes[1].neighbors[0] = 0;
    processes[1].neighbors[1] = 2;

    processes[2].neighbors[0] = 0;
    processes[2].neighbors[1] = 1;
    processes[2].neighbors[2] = 3;

    processes[3].neighbors[0] = 2;
    processes[3].neighbors[1] = 4;

    processes[4].neighbors[0] = 0;
    processes[4].neighbors[1] = 3;
    processes[4].neighbors[2] = 5;
    
    processes[5].neighbors[0] = 0;
    processes[5].neighbors[1] = 4;
    processes[5].neighbors[2] = 6;
    
    processes[6].neighbors[0] = 5;
    processes[6].neighbors[1] = 7;
    
    processes[7].neighbors[0] = 6;
    
    processes[8].neighbors[0] = 0;
    processes[8].neighbors[1] = 9;

    processes[9].neighbors[0] = 8;

    /********************************************/

    // Initialize the channels
    for(int i = 0; i < n; i++){
	processes[i].clock = 0;
	processes[i].inputs = (int *)malloc(sizeof(int)*processes[i].numberOfNeighbors);
	processes[i].outputs = (int **)malloc(sizeof(int*)*processes[i].numberOfNeighbors); // One pointer/input
    }

    randomize();
    
    // Perform the routing -- starting from the topmost process and go clock-wise

    // Processor 1
    *(processes[0].outputs) = (processes[1].inputs+1);
    *(processes[0].outputs+1) = (processes[2].inputs+1);
    *(processes[0].outputs+2) = (processes[4].inputs);
    *(processes[0].outputs+3) = (processes[5].inputs);
    *(processes[0].outputs+4) = (processes[8].inputs);
    
    // Processor 2
    *(processes[1].outputs+1) = (processes[0].inputs);
    *(processes[1].outputs) = (processes[2].inputs);

    // Processor 3
    *(processes[2].outputs) = (processes[1].inputs);
    *(processes[2].outputs+1) = (processes[0].inputs+1);
    *(processes[2].outputs+2) = (processes[3].inputs);
  
    // Processor 4
    *(processes[3].outputs) = (processes[2].inputs+2);
    *(processes[3].outputs+1) = (processes[4].inputs+1);

    // Processor 5
    *(processes[4].outputs) = (processes[3].inputs+1);
    *(processes[4].outputs+1) = (processes[0].inputs+2);
    *(processes[4].outputs+2) = (processes[5].inputs+1);

    // Processor 6
    *(processes[5].outputs) = (processes[0].inputs+3);
    *(processes[5].outputs+1) = (processes[4].inputs+2);
    *(processes[5].outputs+2) = (processes[6].inputs);

    // Processor 7
    *(processes[6].outputs) = (processes[5].inputs+2);
    *(processes[6].outputs+1) = (processes[7].inputs);
    
    // Processor 8
    *(processes[7].outputs) = (processes[6].inputs+1);
    
    // Processor 9
    *(processes[8].outputs) = (processes[0].inputs+4);
    *(processes[8].outputs+1) = (processes[9].inputs);

    // Processor 10
    *(processes[9].outputs) = (processes[8].inputs+1);
}


static int setup_server_socket( short port )
{
	// create new socket file descriptor
	int fd = socket( AF_INET, SOCK_STREAM, 0 );
	if( -1 == fd )
	{
		perror( "socket() failed" );
		return -1;
	}

	// bind socket to local address
	sockaddr_in servAddr; 
	memset( &servAddr, 0, sizeof(servAddr) );

	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(port);

	if( -1 == bind( fd, (const sockaddr*)&servAddr, sizeof(servAddr) ) )
	{
		perror( "bind() failed" );
		close( fd );
		return -1;
	}

	// get local address (i.e. the address we ended up being bound to)
	sockaddr_in actualAddr;
 	socklen_t actualAddrLen = sizeof(actualAddr);
	memset( &actualAddr, 0, sizeof(actualAddr) );

	if( -1 == getsockname( fd, (sockaddr*)&actualAddr, &actualAddrLen ) )
	{
		perror( "getsockname() failed" );
		close( fd );
		return -1;
	}

	// and start listening for incoming connections
	if( -1 == listen( fd, kServerBacklog ) )
	{
		perror( "listen() failed" );
		close( fd );
		return -1;
	}

	// allow immediate reuse of the address (ip+port)
	int one = 1;
	if( -1 == setsockopt( fd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int) ) )
	{
		perror( "setsockopt() failed" );
		close( fd );
		return -1;
	}

	return fd;
}
