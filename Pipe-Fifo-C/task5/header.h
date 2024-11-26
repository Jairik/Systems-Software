/* Header file for task 5
 * JJ McCauley
 * Defines structs and definitions used in other portions of the program */

#define NOT_READY -1
#define FILLED 0
#define TAKEN 1
#define GO 2
#define STOP 3

// Struct to hold the pair of two numbers
struct curNums{
	int num1;
	int num2;
};

// Struct to hold shared memory contents
struct Memory {
	int status;
	int gostop;
	struct curNums data;
};
