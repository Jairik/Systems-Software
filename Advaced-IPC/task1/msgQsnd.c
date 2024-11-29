/* Lab 10 - Task 1
 * JJ McCauley
 * Task: Acts as the queue message sender, asking for two integer values from the standard input until EOF */

#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>

struct msgBuf{
	long msgType;  // Required
	int num1, num2;
};

int main(){
	struct msgBuf mBuf;
	int msqid;
	key_t key;

	// Create a key for the message queue
	if((key = ftok("msgQsnd.c", 'X')) == -1){perror("Error generating key"); exit(1);}

	// Creating the message queue
	if((msqid = msgget(key, 0644 | IPC_CREAT)) == -1){perror("Error generating message queue"); exit(1);}

	// Retreiving lines of ints to be sent to message queue
	printf("Enter two integers\n");
	while(1){
		if(scanf("%d%d", &mBuf.num1, &mBuf.num2) != 2){  // If NOT two valid numbers
			if(feof(stdin)){  // If EOF, break loop and close message queue
				printf("Done Sending Input\n");
				break;
			}
			else{  // Else, must be invalid input
				printf("Invalid Input. Please Try Again\n");
				while(getchar() != '\n');  // Clearing buffer, thank you Stack Overflow
				continue;
			}
		}

		// Try to send the message
		mBuf.msgType = 1;  // Irrelevant but required
		if(msgsnd(msqid, (struct msgBuf *) &mBuf, sizeof(mBuf), 0) == -1){perror("Send Error\n"); exit(1);}
			
		printf("Enter two integers or CTRL-D to stop\n");
	}

	// Now, remove message queue once sending is complete
	if(msgctl(msqid, IPC_RMID, NULL) == -1){perror("Error Deleting Message Queue"); exit(1);}

	exit(0);

}
