#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>


void processLine(char *currLine, char newPath[24]) {
	// Get filepath from curr path & year
	char filename[34];
	char *title = strtok(currLine, ",");
	sprintf(filename, "%s/%s.txt", newPath, strtok(NULL, ","));

	// Create file & append title, then close & set perms
	FILE *file = fopen(filename, "a");
	fprintf(file, "%s\n", title);
	fclose(file);
	chmod(filename, 0640);
}


void processFile(char *filename) {
	// Calc dir name & create dir
	char newPath[24];
	srandom((unsigned int) time(NULL));
	sprintf(newPath, "./streedan.movies.%i", (int) random() % 100000);
	mkdir(newPath, 0750);
	
	// Open file & notify user
	char *currLine = NULL;
	size_t len = 0;
	FILE *movieFile = fopen(filename, "r");
	printf("Now processing the chosen file named %s\n", filename);
	
	// Loop over lines of file, calling processLine() on each
	getline(&currLine, &len, movieFile);
	while (getline(&currLine, &len, movieFile) != -1)
		processLine(currLine, newPath);

	// Close file & inform user
	fclose(movieFile);
	printf("Created directory with name %s\n\n", newPath);
}

void getEstFile(int mode, char* filename) {
	// Open dir and set init size based on the mode
	DIR* currDir = opendir(".");
	struct dirent *aDir;
	off_t size = --mode ? LLONG_MAX : 0;
	struct stat dirStat;
	
	// Loop over each entry in dir
	while ((aDir = readdir(currDir)) != NULL) {
		// If entry name starts with `movies_` and ends with `.csv`
		if (!strncmp(aDir->d_name,"movies_", 7) && !strcmp(aDir->d_name + strlen(aDir->d_name) - 4, ".csv")) {
			// Gather entry info
			stat(aDir->d_name, &dirStat);
			
			// If smallest/largest (based on mode), set file name to entry
			if ((!mode && dirStat.st_size > size) || (mode && dirStat.st_size < size)) {
				size = dirStat.st_size;
				memset(filename, '\0', 256 * sizeof(char));
				strcpy(filename, aDir->d_name);
			}
		}
	}
	closedir(currDir);
}



int getFilename(int mode) {
	// Get mode 3, get filename from user, otherwise, call getEstFile()
	char filename[256];
	if (mode == 3) {
		printf("Enter the complete file name: ");
		scanf("%s", filename);
		
		// If file not found, notify user and return 0
		if (access(filename, 0)) {
			printf("The file %s was not found. Try again\n", filename);
			return 1;
		}
	} else
		getEstFile(mode, filename);
	
	processFile(filename);
	return 0;
}


void fileToProcess(void) {
	int input;
	int fileNotFound = 1;
	
	// Present use with menu until valid file is found
	while (fileNotFound) {
		printf("\nWhich file you want to process?\nEnter 1 to pick the largest file\nEnter 2 to pick the smallest file\nEnter 3 to specify the name of a file\n\nEnter a choice from 1 to 3: ");
		scanf("%i", &input);
		// Checks for valid user input & file. If valid, sets fileNotFound to false
		fileNotFound = input > 0 && input < 4 ? getFilename(input) : printf("You entered an incorrect choice. Try again.\n");
	}
}

/**
 * @brief Main function that implements the menu for the user to select which file to process or exit the program
 *
 * @param argc The number of arguments passed to the program
 * @param argv The list of arguments passed to the program
 *
 * @return 0 upon successful execution
 */
int main(int argc, const char * argv[]) {
	int input = 0;
	// Loop until user exits
	while (input != 2) {
		printf("1. Select file to process\n2. Exit the program\n\nEnter a choice 1 or 2: ");
		scanf("%i", &input);
		
		// Validate user input and call fileToProcess()
		if (input == 1)
			fileToProcess();
		else if (input != 2)
			printf("You entered an incorrect choice. Try again.\n\n");
	}
	return 0;
}