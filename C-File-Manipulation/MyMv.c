/* Lab 4 - Task 4
 * JJ McCauley
 * Task: mv function from scratch using system calls link and unlink*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pwd.h>  // To get user's home directory
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
// Debugging libraries
//#include <errno.h> 
//#include <string.h>

void pError(char *msg){
	printf("%s\n", msg);
	exit(1);
}

/*
// Returns a c-string of the home directory
char *getHomeDir(){
	int uid = getuid();  // Retreive the current user ID
	struct passwd *pwd = getpwuid(uid);  // Get struct that contains user information
	return pwd->pw_dir;  // Return user's home directory
}
*/

// Given a path and file name, returns c-string of new path with file name
char *getFullPath(char *dir, char *file){
	char *newPath;
	if((newPath = (char *)malloc((strlen(dir) + strlen(file) + 3) * sizeof(char))) == NULL){
		pError("Error allocating memory");
	}

	// Getting sizes of different c-strings
	int dirSize = strlen(dir);
	int fileSize = strlen(file);  // Poor name hindsight
	int newPathSize = strlen(newPath);
	
	// Adding the home dir to new path dir
	for(int i = 0; i < dirSize; i++){
		newPath[i] = dir[i];
	}
	newPath[dirSize] = '/';
	for(int j = 0; j < fileSize; j++){
		newPath[j+dirSize+1] = file[j];
	}

	// add \0 to end of newPath
	newPath[dirSize + fileSize + 1] = '\0';

	// Return the new c-string
	return newPath;
}


// Parameters: file name and path to directory
int main(int argc, char* argv[]){
	int isDir = 0;  // Used for determining if directory exists, 1->Exists, 0->Does not exist

	// Ensure valid number of parameters is provided
	if(argc != 3){pError("Invalid number of arguments");}

	char *file = argv[1], *path = argv[2], *fName = path;

	// Check if the given path is a directory
	struct stat path_stat;
	if((stat(path, &path_stat)) == -1){
		// File does not exists - will be made with file name in link
		isDir = 0;
	}  
	else if(S_ISDIR(path_stat.st_mode)){
		isDir = 1;
		path = getFullPath(path, file);
		//printf("New Path: %s\n", path);
	
	}
	else { 
		pError("Error - cannot overwrite file");  // Can be taken out if not desired
	}

	// Moving file to new spot 
	if((link(file, path)) == -1){
		//printf("Error: %s\n", strerror(errno));
		pError("Error linking file");
	}

	// 'Removing' old file spot
	if((unlink(file)) == -1){
		pError("Error unlinking file");
	}
	
	return 0;
}
