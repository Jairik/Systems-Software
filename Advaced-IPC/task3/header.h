/* Lab 10 - Task 3
 * JJ McCauley
 * Header.h - Holds structs for shared memory */

// Flags for sender/receiver
#define NOT_READY -1
#define FILLED 0
#define TAKEN 1
#define GO 2
#define STOP 0

// Semephore Flags
#define MUTEX 0
#define FULL 1
#define EMPTY 2

// Define Array Size as Constant
#define ARRSIZE 5

struct nums {
	int arr[ARRSIZE];  // Array of 5 integers
	int arrIndex;  // Index to hold current position
};


struct Memory{
	int gostop;  // GO or STOP
	struct nums data;  // Struct to hold the 5 integers
};

