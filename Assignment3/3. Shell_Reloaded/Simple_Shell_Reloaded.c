#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>
#include <fcntl.h>

#ifndef BUFFSIZE
#define BUFFSIZE 4096
#endif

#ifndef MAX_CMD
#define MAX_COMMAND_LENGTH 100
#endif

#ifndef MAX_CMD
#define MAX_NUMBER_OF_PARAMS 10
#endif

#define true  1
#define false 0

struct sigaction sa;

void parse_Command(char* command, char** params);
int exec_Command(char** params);

int line = false;
//I have created background process that opening file with fopen function 

void handler(int signo)
{
  //sleep(2);
  pid_t pid;
  int status;
  pid = wait(&status);
  printf("Command with Child-Pid %d Completes with status %d\n", pid,status);
  char mypid[12];   // ex. 34567
    sprintf(mypid, "%d", pid);
    int len=strlen(mypid);
   
	mypid[len++]='.';
    mypid[len++]='t';
    mypid[len++]='x';
    mypid[len++]='t';
    mypid[len]='\0';
    FILE* fp=fopen(mypid,"r");
    if (fp == NULL) 
    { 
        //printf("Cannot open file \n"); 
        exit(0); 
    } 
    // Read contents from file 
    char c = fgetc(fp); 
    while (c != EOF) 
    { 
        printf ("%c", c); 
        c = fgetc(fp); 
    } 
    fclose(fp);
    //printf("\n");
    remove(mypid);
    //printf("Pid %d exited.\n", pid);
}

int main()
{
    char command[MAX_COMMAND_LENGTH ];
    char* params[MAX_NUMBER_OF_PARAMS];
	printf("Welcome to Simple shell: \n");
    char get[BUFFSIZE];
	
    sa.sa_handler = &handler;
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) { // Should not happen
    perror("Error: cannot handle SIGINT");
      }	
	
	getcwd(get, BUFFSIZE); //getting path 
	for ( ; ; ) {    
	   
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
	
		parse_Command(command, params); //splitting given command into parameters
     
		if(strcmp(params[0], "exit") == false){
			break;  //if first argument equal to exit them exit from shell
		}
		if(strcmp(params[0], "") == false){
			continue; //if just press enter it continues untill exit
		}
        if(exec_Command(params) == false){ 
			break;
		}		//executig command
			
  
  }
	printf("\n");
    return 0;
}

// Split cmd into array of parameters
void parse_Command(char* command, char** params)
{       	
    int len=0;	
    for(int i = 0; i < MAX_NUMBER_OF_PARAMS; i++) {
        params[i] = strsep(&command, " "); 
	if(params[i] == NULL){
		break; //if no command do not execute		
		}
        //printf("%d th param %s with len %d\n",i,params[i],strlen(params[i]));
	}
}


int exec_Command(char** params)
{
    // Fork process
	pid_t pid = fork();
	
    // Error
    if (pid == -1) {
        char* error = strerror(errno);
        printf("fork: %s\n", error);
        return true;
    }

    // Child proces when there exist error
    else if (pid == 0) {
        pid_t cpid=getpid(); //returns the process ID
        char* error=NULL;
        char mypid[12];  
        sprintf(mypid, "%d", cpid); //mpid char = cpid - process number  example: 1522
        int len=strlen(mypid); //length = process id character size 
        mypid[len++]='.'; 
        mypid[len++]='t';
        mypid[len++]='x';
        mypid[len++]='t';
        mypid[len]='\0';
		// addindg end of process id + .txt,  
        int fd=open(mypid, O_WRONLY|O_CREAT, 0666);
        close(1);
        dup2(fd,1);
        execvp(params[0], params); //execvp used to execute given parameter  
         error = strerror(errno);
        //printf(">> %s: %s\n", params[0], error);
        close(fd);
        printf("Child pid is as str %s\n", mypid);
        if(error == NULL)
        exit(0);
        else 
        exit(errno);
        //return false;
    }

    // Parent process
    else {
        // Wait for child process to finish
		char *str;
		int childStatus;
        //waitpid(pid, &childStatus, 0);
                //printf("return From Parent with child -id -%d\n",pid);
		return true;
	}
}
