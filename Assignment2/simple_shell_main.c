#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

void parseCmd(char* cmd, char** params);
int executeCmd(char** params);


#define MAX_COMMAND_LENGTH 100
#define MAX_NUMBER_OF_PARAMS 10
#define true  1
#define false 0

int main()
{
    char cmd[MAX_COMMAND_LENGTH ];
    char* params[MAX_NUMBER_OF_PARAMS];
    int cmdCount = 0;


    for( ; ; ) {

        char* u_name = getenv("USER"); 
        printf("%s@ >> ", u_name);
        if(fgets(cmd, sizeof(cmd), stdin) == NULL) break; 
       
	   // Remove trailing newline character, if any
        if(cmd[strlen(cmd)-1] == '\n') {
            cmd[strlen(cmd)-1] = '\0';
        }

        // Split cmd into array of parameters
		parseCmd(cmd, params);

        
        if(strcmp(params[0], "exit") == false) break; //if first argument equal to exit them exit from shell

   
        if(executeCmd(params) == false) break; //executig command
    }
	printf("\n");
    return 0;
}

// Split cmd into array of parameters
void parseCmd(char* cmd, char** params)
{       	
	int count = 0;
    for(int i = 0; i < MAX_NUMBER_OF_PARAMS; i++) {
        params[i] = strsep(&cmd, " "); 
	if(params[i] == NULL) break; //if no command do not execute		
}
}

int executeCmd(char** params)
{
    // Fork process
    pid_t pid = fork();

    // Error
    if (pid == -1) {
        char* error = strerror(errno);
        printf("fork: %s\n", error);
        return true;
    }

    // Child process
    else if (pid == 0) {
        // Execute command
        execvp(params[0], params);  

        // Error occurred
        char* error = strerror(errno);
        printf("shell: %s: %s\n", params[0], error);
        return false;
    }

    else {
      
        int childStatus;
        waitpid(pid, &childStatus, 0);
        return true;
    }
}