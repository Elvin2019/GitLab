#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>   
#include <string.h>   
#include <signal.h>

static struct sigaction sa;
static int sig_chk = 0;//alarm done
static int ss_tm = 0;//alarm done

void handler(int );
void my_sleep(int );
void alarm_handler(int );

void alarm_handler(int signal)
{
    sig_chk = 1;
    sigset_t pending;
    if (sigismember(&pending, SIGQUIT)) {
       //printf("Caught Second Time, So exit\n"); 
        ss_tm = 1;
    }
}

void handler(int sgn)
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
	sigset_t mask;
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = &alarm_handler; // Intercept and ignore SIGALRM
	//sa.sa_flags = SA_RESETHAND; // Remove the handler after first signal
	sigfillset(&sa.sa_mask);
	sigaction(SIGALRM, &sa, NULL);
	// Get the current signal mask
	sigprocmask(0, NULL, &mask);


// Wait with this mask
	alarm(sec);
//sigsuspend(&mask);
}
int main() 
{  
	char str[100];
	int len;
	sa.sa_handler = &handler;
	sa.sa_flags = SA_RESTART;
	sigfillset(&sa.sa_mask);
	if (sigaction(SIGQUIT, &sa, NULL) == -1){
        perror("Error: cannot handle SIGQUIT"); // Should not happen
	}
   while(1){
      write(1,"Enter Text :\n",14);
      len=read(0,str,100);
	  write(1,"Given Text :\n",14);
      write(1,str,len);
      memset(str,EOF,100);
   } 

}
