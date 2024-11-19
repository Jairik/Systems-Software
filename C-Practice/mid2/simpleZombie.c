/* Super Simple Zombie Process */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
	// Create child & parent process
	pid_t pid = fork();  
	
	// On Fork Fail
	if(pid < 0){perror("Fork Error"); exit(1);}

	if(pid == 0){ // Child case - must exit before parent can process it
		sleep(1);
		exit(0);
	}
	else{  // Parent case - must not exit before child & should not process child
	       sleep(100);  // Sleep, not processing child exit
	}

}
