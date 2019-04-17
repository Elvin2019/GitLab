#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <inttypes.h>
#include <sys/times.h>

#ifndef BUFFSIZE
#define BUFFSIZE 4096
#endif

#ifndef MAX_CMD
#define MAX_COMMAND_LENGTH 100
#endif

#ifndef MAX_CMD
#define MAX_NUMBER_OF_PARAMS 10
#endif



void parseCmd(char* command, char** params);
int executeCmd(char** params);

struct tms start_tms;
struct tms end_tms;


#define true  1
#define false 0



char *str_buff;
int line = false;



int main()
{
    char command[MAX_COMMAND_LENGTH ];
    char* params[MAX_NUMBER_OF_PARAMS];
    int cmdCount = 0;
	printf("Welcome to Simple shell: \n");
    char get[BUFFSIZE];
	
    str_buff = malloc(sizeof(char) * BUFFSIZE);
	int c = 0;
	
	getcwd(get, BUFFSIZE); //getting path 
	for ( ; ; ) {
	   //printf("%s@ >> ", getenv("USER")); //print user name + >> shell mark
		//if (fgetc(stdin) == sizeof(command)) continue;       
	   c++;
	   if(line){
		   printf(">");
        	}else if((getenv("HOME")!= NULL) && (strcmp(getenv("HOME"), get) == false)){
			printf(">home>");
        	}else{
			printf(">%s>>", get);
		}
	    if(fgets(command, sizeof(command), stdin) == NULL){
			break; //reading command form stdin, exit whent ctrl + D
		}
	  
        if(command[strlen(command)-1] == '\n') {
            command[strlen(command)-1] = '\0';
        }
		
		parseCmd(command, params); //splitting given command into parameters
        
     //	if(strcmp(params[c], "&&") == true && strcmp(params[c+1], "&&") == false) continue;	
		if(strcmp(params[0], "exit") == false){
			break;  //if first argument equal to exit them exit from shell
		}
		if(strcmp(params[0], "") == false){
			continue; //if just press enter it continues untill exit
		}
        if(executeCmd(params) == false){ 
			break;
		}		//executig command
			
  
  }
	//printf("\n");
    return 0;
}

// Split cmd into array of parameters
void parseCmd(char* command, char** params)
{       	
	int count = 0;
    for(int i = 0; i < MAX_NUMBER_OF_PARAMS; i++) {
        params[i] = strsep(&command, " "); 
	if(params[i] == NULL){
		break; //if no command do not execute		
		}
	}
}



int executeCmd(char** params)
{
    // Fork process
    

	pid_t pid = fork();
	times(&start_tms);
	/*
    printf("Test start_tms.tms_utime = %jd\n\n",  (intmax_t)start_tms.tms_utime);
    printf("Test start_tms.tms_stime = %jd\n\n",  (intmax_t)start_tms.tms_stime);
	*/
    // Error
    if (pid == -1) {
        char* error = strerror(errno);
        printf("fork: %s\n", error);
        return true;
    }

    // Child proces when there exist error
    else if (pid == 0) {
        execvp(params[0], params); //execvp used to execute given parameter  
		char* error = strerror(errno);
        printf(">> %s: %s\n", params[0], error); 
        return false;
    }

    // Parent process
    else {
        // Wait for child process to finish
        int childStatus;
        waitpid(pid, &childStatus, 0);
    
		times(&end_tms);
		
		/*
        printf("Test end_tms.tms_utime = %jd\n\n",end_tms.tms_utime);
        printf("Test end_tms.tms_stime = %jd\n\n",end_tms.tms_stime);
		*/
       
        
        clock_t utime = end_tms.tms_utime - start_tms.tms_utime;
        clock_t stime = end_tms.tms_stime - start_tms.tms_stime;
        clock_t real;

      	printf("Real time %jd\n\n", (intmax_t)real);
        printf("User CPU time %jd\n\n", (intmax_t)utime);
        printf("System CPU %jd\n\n", (intmax_t)stime);
		
	
		return true;
    
	
	}
}