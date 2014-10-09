#include<stdio.h>
#include<stdlib.h>

#define n 10

typedef struct {
    int clock;
    int numberOfNeighbors;
    int *inputs; // This is the recieve channel
    int **outputs; // This is the output channels
}process;

process processes[n];

void initAndRoute();
void printState();


int main()
{
    initAndRoute();

    while(true){
	getchar(); // Used in order step through the algorithms
	printState();
    }
    return 0;
}


void printState(){
    printf("       %d                                        \n       +                                         \n       |     %d                                  \n       |     +                                   \n       |     |    %d                             \n    +--+--+  |    +      %d                      \n    |  10 |  |    |      +                       \n    +--+--+  |    |      |                       \n       |     |    |   +--+--+                    \n       |     |    |   |  2  +-----------+        \n       |     |    |   +--+--+           |        \n    +--+--+  |    |      |           +--+--+     \n    |  9  +--+    +---+  |      +----+  3  +-+ %d\n    +--+--+           |  |      |    +--+--+     \n       |              +--+--+   |       |        \n       +--------------+  1  +---+       |        \n                      +--+--+           |        \n                      |  |              |        \n       +--------------+  |           +--+--+     \n       |                 |           |  4  +-+ %d\n    +--+--+              |           +--+--+     \n+---+  6  +----+         |              |        \n|   +--+--+    |      +--+--+           |        \n|      |       +------+  5  +-----------+        \n|      |              +--+--+                    \n|   +--+--+              |                       \n|   |  7  +--+           +---+ %d                \n|   +--+--+  |                                   \n|      |     +---+ %d                            \n|      |                                         \n|   +--+--+                                      \n|   |  8  +---+ %d                               \n|   +-----+                                      \n|                                                \n+---+ %d                                         \n",
	   1,2,3,4,5,6,7,8,9,10);
}

void initAndRoute(){
    // Assign the number of neighbors
    processes[0].numberOfNeighbors = 5;
    processes[1].numberOfNeighbors = 2;
    processes[2].numberOfNeighbors = 3;
    processes[3].numberOfNeighbors = 2;
    processes[4].numberOfNeighbors = 4;
    processes[5].numberOfNeighbors = 3;
    processes[6].numberOfNeighbors = 2;
    processes[7].numberOfNeighbors = 1;
    processes[8].numberOfNeighbors = 2;
    processes[9].numberOfNeighbors = 1;

    // Initialize the channels
    for(int i = 0; i < n; i++){
	processes[i].inputs = (int *)malloc(sizeof(int)*processes[i].numberOfNeighbors);
	processes[i].outputs = (int **)malloc(sizeof(int*)*processes[i].numberOfNeighbors); // One pointer/input
    }

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
    *(processes[3].outputs) = (processes[4].inputs+1);

    // Processor 5
    *(processes[4].outputs) = (processes[3].inputs+1);
    *(processes[4].outputs+1) = (processes[0].inputs+2);
    *(processes[4].outputs+2) = (processes[5].inputs+1);

    // Processor 6
    *(processes[5].outputs) = (processes[0].inputs+3);
    *(processes[5].outputs) = (processes[4].inputs+2);
    *(processes[5].outputs) = (processes[6].inputs);

    // Processor 7
    *(processes[6].outputs) = (processes[5].inputs+2);
    *(processes[6].outputs) = (processes[7].inputs);
    
    // Processor 8
    *(processes[7].outputs) = (processes[6].inputs+1);
    
    // Processor 9
    *(processes[8].outputs) = (processes[0].inputs+4);
    *(processes[8].outputs) = (processes[9].inputs);

    // Processor 10
    *(processes[9].outputs) = (processes[8].inputs+1);
}
