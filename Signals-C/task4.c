/* Lab 7 - Task 4
 * JJ McCauley
 * Task: Using signal and kill system calls for intraprocess communication */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sigGoodChild(int sig){
	if(sig == SIGUSR1){printf("Hi Honey! Anything wrong?\n");}
}

void sigBadChild(int sig){
	if(sig == SIGUSR2){printf("Do you make trouble again?\n");}
}

void err(char *msg){
	printf("%s\n", msg);
	exit(1);
}


int main(){
	int pid1, pid2;
	signal(SIGUSR1, sigGoodChild);
	signal(SIGUSR2, sigBadChild);

	// Creating first child process
	pid1 = fork();

	if(pid1 == -1){err("Error forking first process");}
	// Child case
	else if(pid1 == 0){
		kill(getppid(), SIGUSR1);
	}
	// Parent case
	else{
		pid2 = fork();
		//Second child case
		if(pid2 == 0){
			kill(getppid(), SIGUSR2);	
		}
		//Parent case
		else{
			pause();
		}
	}
}
