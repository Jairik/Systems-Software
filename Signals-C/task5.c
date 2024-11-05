/* Lab 7 - Task 5
 * JJ McCauley
 * Task: Block and unblock signals */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(){
	sigset_t new_set, newer_set, old_set;  // Signal sets
	
	sigemptyset(&new_set);  // Clear signal sets
	sigaddset(&new_set, SIGINT);
	sigaddset(&new_set, SIGQUIT);
	
	sigprocmask(SIG_BLOCK, &new_set, &old_set); // Block the two signals
	
	// Iterate through loops
	for(int i = 1; i < 6; i++){
		printf("%d\n", i);
		sleep(1);
	}

	// Block only SIGINT (can also be achieved through sigdelset() function)
	sigemptyset(&newer_set);
	sigaddset(&newer_set, SIGINT);
	sigprocmask(SIG_SETMASK, &newer_set, NULL);

	printf("--- Second Loop ---\n");

	// Iterate through loops
	for(int j = 0; j < 6; j++){
		printf("%d\n", j);
		sleep(1);
	}


	// Restore block to defaults
	sigprocmask(SIG_SETMASK, &old_set, NULL); 

	exit(0);
}
