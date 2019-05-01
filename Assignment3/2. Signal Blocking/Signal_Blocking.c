#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>   
#include <string.h>   
#include <signal.h>
#include <fcntl.h>
#include <errno.h>

struct sigaction sa, old_sa;
static volatile int flag = -1;
const char *signal_name;


void grp_handle(int );

void grp_handle(int signo) {
    sigset_t pending;
    // Find out which signal we're handling
    switch (signo) {
        case SIGQUIT:
            signal_name = "SIGQUIT";
            break;
        case SIGTERM:
            signal_name = "SIGTERM"; 
            break;
        case SIGINT:
            signal_name = "SIGINT";
            break;
        default:
            exit(0);
    }
}
int main(int argc, char* argv[])
{
	int sFp,dFp,nbr; //sFp - source file open , dFp - destinition file open , nbr - n byte read
	char *buff[1024];

	printf("My pid is: %d\n", getpid()); // process id -- it will be useful to kill process for handling SIGTERM signal
	
	//Open source file
	sFp = open(argv[1],O_RDONLY);
	if(sFp == -1){
	printf("\nError opening file %s errno = %d\n",argv[1],errno);
	exit(EXIT_FAILURE);	
	}

	//Open  destination file 
	dFp = open(argv[2],O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if(dFp == -1) {
		printf("\nError opening file %s errno = %d\n",argv[2],errno);
		exit(EXIT_FAILURE);
	}
	//Signal handling Part
	sa.sa_handler = &grp_handle; //will execute the grp_hanle function whenever the signal is delivered

	if (sigaction(SIGINT, &sa, &old_sa) == -1) { // Should not happen
		perror("Error: cannot handle SIGINT");
	}

	if (sigaction(SIGQUIT, &sa, &old_sa) == -1) { // Should not happen
		perror("Error: cannot handle SIGQUIT"); 
	}

	if (sigaction(SIGTERM, &sa, &old_sa) == -1) { // Should not happen
		perror("Error: cannot handle SIGTERM"); 
	}
	
	printf("You can press signals\n");
	
	//Start data transfer from src file to dest file till it reaches EOF
	while((nbr = read(sFp,buff,1024)) > 0)
	{
		if(write(dFp,buff,nbr) != nbr)
		printf("\nError in writing data to %s\n",argv[2]);
		//printf("You can press signals\n");
        sleep(5); //--during  sec given signals can be handled after copying source file to destinition 
    }
	flag=1;//completes
	close(sFp);
	close(dFp);
	
	//handling signals SIGQUIT, SIGINT AND SIGTERM
	while(flag != 1);//wait for copy completes
	printf("Executing Signals\n");
	if(signal_name == "SIGQUIT"){
	printf("latest QUIT signal ^\\ \n");
	}
	else if(signal_name == "SIGINT") {
   printf("latest INT signal ^C \n");
	}
	else if(signal_name == "SIGTERM"){
   printf("latest TERM signal\n");
	}      
}
