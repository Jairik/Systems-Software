/* Lab 9 - Task 4
 * JJ McCauley
 * Task: Modify task1 to Fifo instead of pipe 
 * Note: When opening the write end of FIFO, it blocks until there is somebody on the read end. Therefore, a child and parent
 * process must be made so prevent indefinite blocking. */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/wait.h>

int main() {
	int data_processed, status;
	pid_t pid;  // Used for fork method to use Fifo
	const char *fifo_path = "/tmp/task4_fifo";  // Constant c-string to hold fifo path 
	const char some_data[] = "123";
	char *buffer = (char *) malloc((strlen(some_data) + 1) * sizeof(char));  // Dynamically allocate space for buffer
	
	memset(buffer, '\0', strlen(some_data) + 1);  // Fills all values of buffer with '\0'
	
	// Create a parent + child process to run the FIFO
	pid = fork();

	// Fork Fail Case
	if(pid == -1){perror("Fork Error"); exit(1);}

	// Child Case (Write to Fifo)
	else if(pid == 0){
		// Open write end of Fifo
		int fdWrite = open(fifo_path, O_WRONLY);
		if(fdWrite == -1){perror("Failed to open write fifo"); exit(1);}	
		
		// Write data to the fifo
		data_processed = write(fdWrite, some_data, strlen(some_data));
		printf("Wrote %d bytes: %s\n", data_processed, some_data);
		close(fdWrite);  // Close the write end of Fifo
	} 

	// Parent Case (Read from FIFO)
	else{
		// Open the fifo file for reading
		int fdRead = open(fifo_path, O_RDONLY);
		if(fdRead < 0){perror("Failed to open read fifo"); exit(1);}

		// Wait for Child process to complete
		wait(&status);

		// Read data from the fifo
		data_processed = read(fdRead, buffer, sizeof(buffer));
		printf("Read %d bytes: %s\n", data_processed, buffer);
		close(fdRead);  // Close the read end
	}
	exit(EXIT_SUCCESS);
}
