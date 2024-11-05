/* Lab 7 - Task 4
 * JJ McCauley
 * Task: Using signal and kill system calls for intraprocess communication */

#include <signal.h>
#include <stdio.h>

void err(char *msg){
	printf("%s\n", msg);
	exit(1);
}


int main(){
	int pid1, pid2;
	
	// Creating first child process
	pid1 = fork()

	if(pid1 == -1){err("Error forking first process");}
	// Child case
	else if(pid1 == 0){
		signal(SIGUSR)
	}
	// Parent case
	else{
		pid2 = fork();
		//Second child case
		if(pid2 == 0){

		}
	}
}
