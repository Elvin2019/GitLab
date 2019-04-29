#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>   
#include <string.h>   
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
static volatile int flag=-1;
struct sigaction sa,old_sa;
const char *signal_name;
//static int signal;
void grp_handle(int );

void grp_handle(int sign) {
    //const char *signal_name;
    sigset_t pending;
    //signal=sign;
    // Find out which signal we're handling
    switch (sign) {
        case SIGQUIT:
            signal_name = "SIGQUIT";
            //sa.sa_flags = SA_RESTART;
            //printf("You have pressed QUIT signal\n");
            break;
        case SIGTERM:
            signal_name = "SIGTERM";
            //sa.sa_flags = SA_RESTART;
            //printf("You have pressed TERM signal\n");
            break;
        case SIGINT:
            signal_name = "SIGINT";
            //sa.sa_flags = SA_RESTART;
            //printf("You have pressed INT signal\n");
            break;
        default:
            exit(0);
    }
}
int main(int argc, char* argv[])
{
int sFp,dFp,nbr,nbw;
char *buff[1024];

printf("My pid is: %d\n", getpid());
if(argc != 3 || argv[1] == "--help")
{
printf("\nUsage: executable source_file destination_file\n");
exit(EXIT_FAILURE);
}
 
/*Open source file*/
sFp = open(argv[1],O_RDONLY);
if(sFp == -1)
{
printf("\nError opening file %s errno = %d\n",argv[1],errno);
exit(EXIT_FAILURE);	
}

/*Open/Create destination file*/
dFp = open(argv[2],O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
if(dFp == -1)
	{
		printf("\nError opening file %s errno = %d\n",argv[2],errno);
		exit(EXIT_FAILURE);
	}
/*Signal handling Part*/
//struct sigaction sa;
sa.sa_handler = &grp_handle;
sa.sa_flags = SA_RESTART;
sigfillset(&sa.sa_mask);

if (sigaction(SIGINT, &sa, &old_sa) == -1) {
    perror("Error: cannot handle SIGINT");
  }

if (sigaction(SIGQUIT, &sa, &old_sa) == -1) {
    perror("Error: cannot handle SIGQUIT"); 
  }

if (sigaction(SIGTERM, &sa, &old_sa) == -1) {
    perror("Error: cannot handle SIGTERM"); 
  }
flag=0;
printf("Flag--%d\n",flag);
/*Start data transfer from src file to dest file till it reaches EOF*/
	while((nbr = read(sFp,buff,1024)) > 0)
	{
		if(write(dFp,buff,nbr) != nbr)
			printf("\nError in writing data to %s\n",argv[2]);
	printf("You can press signals\n");
        sleep(5);
        }
flag=1;//completes
printf("Flag--%d\n",flag);
close(sFp);
close(dFp);
while(flag != 1);//wait for copy completes
  //return ;
printf("Executing Signals\n");
 if(signal_name == "SIGQUIT")
  {
   printf("latest QUIT signal\n");
   //(*old_sa.sa_handler)(signal);
    sigaction(SIGQUIT,&old_sa,NULL);
    raise(SIGQUIT);
  }
 else if(signal_name == "SIGINT")
  {
   printf("latest INT signal\n");
   //(*old_sa.sa_handler)(signal);
   sigaction(SIGINT,&old_sa,NULL);
    raise(SIGINT);
  }
 else if(signal_name == "SIGTERM")
  {
   printf("latest TERM signal\n");
   //(*old_sa.sa_handler)(signal);
sigaction(SIGTERM,&old_sa,NULL);
    raise(SIGTERM);
  }      

//exit(0);
}
