/* Simple example of orphan process */

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


int main(){
	pid_t pid = fork();  // Create parent + child process
	
	if(pid < 0){perror("Fork error"); exit(1);}  // Handling fork error	
	
	else if(pid == 0){  // Child case - must stay alive after parent
		for(int i = 0; i < 10; i++){
			printf("I am child process!\n");
			sleep(1);
		}
		exit(0);
	}

	else{  // Parent case - must die before child
		printf("I am parent!\n");
		sleep(1);
		printf("Parent die now\n");
		exit(0);
	}
}
