#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <inttypes.h>
#include <sys/times.h>
#include <sys/resource.h>


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

void parse_Command(char* command, char** params);
void operate_and(int command, char** params);
int exec_Command(char** params);


struct tms start_tms;
struct tms end_tms;
struct rusage res_mem;
struct rlimit limit;
struct rlimit lim_mem;
clock_t  start, end;

int *buff;
int line = false;
int store = 0;
int count = 0;



int main()
{
    char command[MAX_COMMAND_LENGTH ];
    char* params[MAX_NUMBER_OF_PARAMS];
    int c = 0;
	printf("Welcome to Simple shell: \n");
    char get[BUFFSIZE];
	
	
	
	getcwd(get, BUFFSIZE); //getting path 
	for ( ; ; ) {
	   //printf("%s@ >> ", getenv("USER")); //print user name + >> shell mark
		//if (fgetc(stdin) == sizeof(command)) continue;       
	   
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
		/*if(strcmp(params[0],"-r") == false){
		//strcat(Cpu_time, )
		}*/
		c++;
		parse_Command(command, params); //splitting given command into parameters
     //operate_and(c, params); //need to complete
     //	if(strcmp(params[c], "&&") == true && strcmp(params[c+1], "&&") == false) continue;	
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
	
    for(int i = 0; i < MAX_NUMBER_OF_PARAMS; i++) {
        params[i] = strsep(&command, " "); 
	if(params[i] == NULL){
		break; //if no command do not execute		
		}
	}
}




void operate_and(int command, char** params)
{       	
	buff = malloc(sizeof(int) * BUFFSIZE);

    for(int i = 0; i < command; ++i) {
		if(strcmp(params[i], "&&") == false){
			store = 1;
			buff[count] = i;
			count++;
		}
	}
	if(store == true){
		if(strcmp(params[command -1], "&&") ==false){
		}else {
			buff[count] = command;
			count++;
			}
		}
	
}
int exec_Command(char** params)
{
    // Fork process
    

	pid_t pid = fork();
	start = times(&start_tms);
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
		char *str;
		int childStatus;
        waitpid(pid, &childStatus, 0);
		end = times(&end_tms);
		times(&end_tms);
		getrusage(RUSAGE_SELF, &res_mem); //get memory 
		
		getrlimit(RLIMIT_CPU, &limit);
		getrlimit (RLIMIT_AS, &lim_mem); 
		//printf("\nDefault CPU_time is : %lld\n\n", (long long int)limit.rlim_cur);
		//printf("\n Default value is : %lld\n", (long long int)rl.rlim_cur); 

		printf("Set CPU time limit: ");
		scanf("%ld",&limit.rlim_cur);
		
		printf("Set Virtual memory limit: ");
		scanf("%ld",&lim_mem.rlim_cur);

		setrlimit(RLIMIT_CPU, &limit);
		setrlimit (RLIMIT_AS, &lim_mem); 
		printf("\nRestricted CPU time now is : %lld\n", (long long int)limit.rlim_cur); 
		printf("Restricted Virtual memory now is : %lld\n\n", (long long int)lim_mem.rlim_cur); 

		/*
        printf("Test end_tms.tms_utime = %jd\n\n",end_tms.tms_utime);
        printf("Test end_tms.tms_stime = %jd\n\n",end_tms.tms_stime);
		*/
       
        clock_t real = (end - start)/100; //real time 
        clock_t utime = end_tms.tms_utime - start_tms.tms_utime;
        clock_t stime = end_tms.tms_stime - start_tms.tms_stime;
        
		
      	printf("Real time %jd\n\n", (intmax_t)real); //extra - real time 
        printf("User CPU time %jd\n\n", (intmax_t)utime); //User CPU time
        printf("System CPU %jd\n\n", (intmax_t)stime); // system CPU time
		printf("Residential memory: %ld\n\n",res_mem.ru_maxrss); //mempry used on process
	
	
		return true;
    
	
	}
}