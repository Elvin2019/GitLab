#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
 
int main(int argc ,const char *argv[])
{
    FILE *fileptr;
    int x;
    char filechar[40];
 
   
    strcpy(filechar,strtol(argv[1],NULL,10));
	x = argv[2];
    
    fileptr = fopen(filechar, "a+");
    fseek(fileptr,x,SEEK_SET);
    fclose(fileptr);
    return 0;
}