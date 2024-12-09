#include <stdio.h>
#include <stdlib.h>

int main(){
	int pipe1[2], pipe2[2];
	char buf[BUFSIZ];
	pipe(pipe1); pipe(pipe2);

	pid_t pid = fork();

	if(pid == 0) {  // Child process
		close(pipe1[1]); close(pipe2[0]); 
		char *m = "I love you too\n";
	}
	else{	// Parent process
		// Close appropriate pipe ends
		char *m = "I love you\n";
		read(fd1[0], buf, BUFSIZ);

	}
}
