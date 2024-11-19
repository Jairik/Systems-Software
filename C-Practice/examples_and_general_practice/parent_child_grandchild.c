// Exercise for JJ

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	int pid1, pid2;
	pid1 = fork(); // Create child
	
	if(pid == 1){perror("fork error");}\
	// Child process
	else if(pid == 0){
		pid2 = fork();
		pid2 = getpid();
		if(pid2 == -1){error("fork error");}
		// Grandchild process
		else if(pid2 == 0){
			while(1){
				printf("I am grandchild\n");
				// If parent is terminated, also terminate
				if(getppid() == 1){exit(0);}
				sleep(1);
			}
		}
		// Child process
		else{
			for(int i = 0; i < 100; i++){
				printf("I am child\n");
				sleep(1);
			}
			exit(0);
		}
	}
	// Parent process
	else{
		while(1){
			printf("I am parent\n");
			if(waitpid(pid1, NULL, WNOHANG) != 0){ //WNOHANG makes it return immediately
				printf("Finished");
				break;
			}
		}
	}

	exit(0);
}
