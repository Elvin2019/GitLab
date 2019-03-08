#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
 
int main(int argc ,const char *argv[])
{
    FILE *fileptr;
    int x ;
    char filechar[40];

    strcpy(filechar,argv[1]);
	x = strtol(argv[2],NULL,10);
    
    fileptr = fopen(filechar, "a+");
	
    //fseek(fileptr,x,SEEK_SET);
    ftruncate(fileno(fileptr),1024 * x);
	fclose(fileptr);
    return 0;
}