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

void pError(char *msg){
	printf("%s", msg);
	exit(1);
}

/*
// Returns a c-string of the home directory
char *getHomeDir(){
	int uid = getuid();  // Retreive the current user ID
	struct passwd *pwd = getpwuid(uid);  // Get struct that contains user information
	return pwd->pw_dir;  // Return user's home directory
}

// Given a path, returns a c-string of the full path with home directory
char *getFullPath(char *dir){
	char *homeDir = getHomeDir();  // Get home directory
	char *newPath;
	if((newPath = (char *)malloc((strlen(homeDir) + strlen(dir) + 1) * sizeof(char))) == NULL){
		pError("Error allocating memory");
	}

	// Getting sizes of different c-strings
	int dirSize = strlen(dir);
	int homeDirSize = strlen(homeDir);
	int newPathSize = strlen(newPath);
	
	// Adding the home dir to new path dir
	for(int i = 0; i < homeDirSize; i++){
		newPath[i] = homeDir[i];
	}
	for(int j = 0; j < dirSize; j++){
		newPath[j+homeDirSize] = dir[j];
	}

	// add \0 to end of newPath
	newPath[homeDirSize + dirSize] = '\0';

	// Return the new c-string
	return newPath;
} */


// Parameters: file name and path to directory
int main(int argc, char* argv[]){
	int isDir = 0;  // Used for determining if directory exists, 1->Exists, 0->Does not exist

	// Ensure valid number of parameters is provided
	if(argc != 3){pError("Invalid number of arguments");}

	char *file = argv[1], *path = argv[2];

	// Ensure that the file and path exists
	if((access(argv[1], R_OK)) == -1 || ()access(argv[2], R_OK)) == -1){pError("File does not exist");}
	
	// Check if the given path is a directory
	struct stat path_stat;
	if((stat(path, &path_stat)) == -1){pError("Stat error");}
	if(S_ISDIR(path_stat.st_mode)){
		isDir = 1;
	}

	//If given path is a directory, create new file to link to
	if(dir == 1){

	}

	// Moving file to new spot 
	if((link(file, path)) == -1){
		pError("Error linking file");
	}

	// 'Removing' old file spot
	if((unlink(file)) == -1){
		pError("Error unlinking file");
	}
	
	return 0;
}
