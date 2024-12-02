/* Lab 10 - Task 2
 * JJ McCauley
 * Header.h - Holds structs for shared memory */

// Flags for sender/receiver
#define NOT_READY -1
#define FILLED 0
#define TAKEN 1
#define GO 2
#define STOP 0


struct nums {
	int arr[5];  // Array of 5 integers
	int arrIndex;  // Index to hold current position
};


struct Memory{
	int status;  // Either FILLED or TAKEN
	int gostop;  // GO or STOP
	int blocked;  // Either 1 (blocked) or 0 (not blocked)
	struct nums data;  // Struct to hold the 5 integers
};
