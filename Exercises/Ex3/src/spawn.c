#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>


#define USAGE "Usage: spawn N \"program_name [program_name params]\""
#define DEBUG 0

int main(int argc, char** argv){
	if(argc != 3){
		char*  what_is_N = "N: Number of children to spawn";
		char* what_is_prog = "program_name: Name of program children will execute";
		char* what_is_prog2 = "(program name and its requisite parameters go in \"quotes\")";
		printf("%s\n\t %s\n\t %s\n\t %s\n",USAGE,what_is_N,what_is_prog,what_is_prog2);
		printf("\n\tEg.,\n\tspawn 25 \"mv file1.txt file2.txt\"\n");
		return 1;
	}

	int num_children = atoi(argv[1]);
	char* tokens = strtok(argv[2]," ");	//Tokenized program & arguments

	char* params[10];		//Will hold subsequent tokens. 10 should be enough, right?
	params[0] = tokens;	//First param is program name

	/* Fill params[] with a null-terminated array of strings. Used for execv. */
	int i = 1;
	while(tokens != NULL) {
		tokens = strtok(NULL, " ");
		params[i++] = tokens;
	}

	// if(DEBUG) printf("\nSpawning %d children\n",num_children);
	// if(DEBUG) printf("\nExecuting:\n\t%s\n",program_to_execute);

	pid_t parent = getpid();
	pid_t pid;

	// if(DEBUG) printf("Parent process: %d\n",parent);

	for(int i = 0; i < num_children; i++){
		if(getpid() != parent) break;		//If not the parent process, don't fork
		pid = fork();		//Parents are allowed to fork all they want
	}

	//There was a forking error. Abort.
	if(pid < 0){
		printf("We've got a big forking problem here\n");
		return 1;
	}

	//Children processes:
	else if(pid == 0){
		if(DEBUG){
			printf("I am process #%d\n",getpid());
			printf("\tExecuting program named \"%s\"", params[0]);
			printf(" with parameters\n\t\t");
			int i = 0;
			while(params[i] != NULL) printf("\"%s\"\n\t\t",params[i++]);
			printf("\n");
		}
		//Execute the program specified with the parameters specified
		execv(params[0],params);
	}

	//Parent process:
	else {
		if(DEBUG) printf("This is parent process %d waiting for its children to wrap up...\n",getpid());
		wait(NULL);
		if(DEBUG) printf("All children done. Exiting...\n");
		printf("Done!\n");
	}

	return 0;
}
