#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>   
#include <string.h>   
#include <signal.h>
static struct sigaction sa;
static struct sigaction old_sa;
void handler(int );
void my_sleep(int );
void alarm_handler(int );
void alarm_handler(int signal) {
    if (signal != SIGALRM) {
        fprintf(stderr, "Caught wrong signal: %d\n", signal);
    }

    printf("Got sigalrm, do_sleep() will end\n");
}
void handler(int sgn)
{
const char *signal_name;
sigset_t pending;
printf("SIGQUIT recorded\n");
printf("Now Wait For 5 Seconds to get other signal\n");
my_sleep(5);
sigpending(&pending);
if (sigismember(&pending, SIGQUIT)) {
       printf("Caught Second Time, So exit\n"); 
       exit(0);
         }
else
{
printf("Not Get Second Signal within 5 Seconds\n");
printf("SO continue\n");
//sa.sa_flags = SA_RESTART;
return ;
}
}
void my_sleep(int sec)
{
struct sigaction sa;
sigset_t mask;
sa.sa_handler = &alarm_handler; // Intercept and ignore SIGALRM
//sa.sa_flags = SA_RESETHAND; // Remove the handler after first signal
sigfillset(&sa.sa_mask);
sigaction(SIGALRM, &sa, NULL);
// Get the current signal mask
sigprocmask(0, NULL, &mask);

// Unblock SIGALRM
sigdelset(&mask, SIGALRM);

// Wait with this mask
alarm(sec);
sigsuspend(&mask);
}
int main() 
{  
char str[100];
int len;
//struct sigaction sa;
sa.sa_handler = &handler;
sigfillset(&sa.sa_mask);
if (sigaction(SIGQUIT, &sa, NULL) == -1) {
        perror("Error: cannot handle SIGQUIT"); // Should not happen
}
   while(1)
   {
      write(1,"Enter Text :\n",14);
      len=read(0,str,100);
      write(1,"Given Text :\n",14);
      write(1,str,len);
      memset(str,EOF,100);
   } 

}

