#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>   
#include <string.h>   
#include <signal.h>

static struct sigaction sa;
static int sig_chk = 0;//alarm done

void handler(int );
void my_sleep(int );
void alarm_handler(int );

void alarm_handler(int signo)
{
    sig_chk = 1;
} 

void handler(int signo)
{
	static int cnt=0;
	cnt++;
	if((cnt == 2) && (sig_chk != 1)){ //means before 5 sec another signal come 
		printf(" Double quit signal before 5 Sec\n");
		cnt=0;
		exit(0);
	}
	else if((cnt == 2) && (sig_chk == 1)){ //means second signal comes after 5 sec means reinit
		cnt=1;
		sig_chk = 0;
	}
	my_sleep(5);
}

void my_sleep(int sec)
{
	struct sigaction sa;
	sa.sa_flags = SA_RESTART; //when signal called restart and wait  
	sa.sa_handler = &alarm_handler; // whenever first quit signal is delivered the function will be called 
	sigaction(SIGALRM, &sa, NULL);
	alarm(sec); //wait 5 second 
}
int main() 
{  
	char str[100];
	int len;
	sa.sa_handler = &handler;
	sa.sa_flags = SA_RESTART; //when signal called restart and wait  
	if (sigaction(SIGQUIT, &sa, NULL) == -1){
        perror("Error: cannot handle SIGQUIT"); // Should not happen
	}
   while(1){
      write(1,"Enter Text :\n",14); 
      len=read(0,str,100); //reading standart input 
	  write(1,"Given Text :\n",14);
      write(1,str,len);	 //printing standart output
   } 

}
