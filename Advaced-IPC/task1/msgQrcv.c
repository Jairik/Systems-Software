/* Lab 10 - Task 1
 * JJ McCauley
 * Task: Act as receiving end of message queue for msgQsnd.c, printing the sum of the two ints */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msgBuf {
	long msgType;
	int num1, num2;
};

int main(){
	struct msgBuf mBuf;
	int msqid;
	key_t key;

	// Get the message queue key
	if((key = ftok("msgQsnd.c", 'X')) == -1){perror("Error generating key"); exit(1);}

	// Open existing message queue 
	if((msqid = msgget(key, 0644)) == -1){perror("Error opening message queue"); exit(1);}

	// Receiving each message from the message queue and add the nums
	for(;;){
		if(msgrcv(msqid, (struct msgBuf *) &mBuf, sizeof(mBuf), 0, 0) == -1){perror("Error receiving message"); exit(1);}

		// Print sum of two numbers
		printf("Sum: %d\n", (mBuf.num1 + mBuf.num2));
	}
}
