/* Lab 4 - Task 3.1
 * JJ McCauley
 * Makes a directory heirchy using symbolic links */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#define PATH_MAX_SIZE 512  // Arbitrary number

void pError(char *msg){
	printf("%s", msg);
	exit(1);  // Exit w/ error message
}


int main(){
	const char *home = getenv("HOME");  // Needed to work on other machines
	// Creating c-string variables to hold filepaths
	char homedir[PATH_MAX_SIZE], dir1[PATH_MAX_SIZE], dir2[PATH_MAX_SIZE], pathHelloLocal[PATH_MAX_SIZE];
	char dir21[PATH_MAX_SIZE], pathHello[PATH_MAX_SIZE], pathToHello[PATH_MAX_SIZE], toDir21[PATH_MAX_SIZE];
	// Assigning paths to c-string variables. snprintf must be used to concatanate home to string (since I am working on different machine)
	// SOURCE: https://www.linuxquestions.org/questions/programming-9/create-file-in-user-home-in-c-761774/
	snprintf(homedir, PATH_MAX_SIZE, "%s/Systems-Software/C-File-Manipulation/homedir", home);
        snprintf(dir1, PATH_MAX_SIZE, "%s/Systems-Software/C-File-Manipulation/homedir/dir1", home);
 	snprintf(dir2, PATH_MAX_SIZE, "%s/Systems-Software/C-File-Manipulation/homedir/dir2", home);
        snprintf(dir21, PATH_MAX_SIZE, "%s/Systems-Software/C-File-Manipulation/homedir/dir2/dir21", home);
 	snprintf(pathHello, PATH_MAX_SIZE, "%s/Systems-Software/C-File-Manipulation/homedir/dir2/dir21/hello", home);			 snprintf(pathToHello, PATH_MAX_SIZE, "%s/Systems-Software/C-File-Manipulation/homedir/dir1/toHello", home);
	snprintf(pathHelloLocal, PATH_MAX_SIZE, "%s/Systems-Software/C-File-Manipulation/hello", home);
	snprintf(toDir21, PATH_MAX_SIZE, "%s/Systems-Software/C-File-Manipulation/homedir/dir1/toDir21", home);

	// --- Create directory structure ---
	// Home Directory (Made inside current folder to not clutter home directory)
	if(mkdir(homedir, 0777) == -1){pError("Error creating home directory");}
	// Dir1
	if(mkdir(dir1, 0777) == -1){pError("Error creating Dir1");}
	// Dir 2
	if(mkdir(dir2, 0777) == -1){pError("Error creating Dir2");}
	//Dir 21
	if(mkdir(dir21, 0777) == -1){pError("Error creating Dir21");}
	// Copy hello file under Dir21
	if(link(pathHelloLocal, pathHello) == -1){pError("Error copying file");}
	// Create symbolic link 'toDir21' to Dir21 in Dir1
	if(symlink(dir21, toDir21) == -1){pError("Error creating symbolic link toDir21");}
	// Create symbolic link 'toHello' to Hello executable in Dir1/hello
	if(symlink(pathHello, pathToHello) == -1){pError("Error creating symbolic link toHello");}

	exit(0);
}
