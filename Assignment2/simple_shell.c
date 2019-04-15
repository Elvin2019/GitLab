
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100

int main(int argc, char *argv[])
{
    char cmd[MAX_LEN] = "";
	printf("Welcome to Simple shell: \n");
    system("/bin/sh"); //for simple shell

	if (argc < 2) /*no command specified*/
    {
		if(strcmp(argv[1], "exit") == 0){ 
        printf("Bye\n");
        exit(0);
		}
		
		fprintf(stderr, "Error: wrong command");
        printf("\n");
        exit(1);
   }
    else
    {
        strcat(cmd, argv[1]); //enetering first command like source
        for (char **i = &argv[2]; *i; i++) //while second command, point to dest
        {
            strcat(cmd, " "); //char *strcat(char *dest, const char *src)
            strcat(cmd, *i); //I have used strcat appending string pointed by src to end of string pointed by des
        }
        system(cmd);
    }

    return 0;
}