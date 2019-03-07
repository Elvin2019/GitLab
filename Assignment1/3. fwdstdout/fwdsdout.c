#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    FILE *fileptr;
   
    char filechar[40], chr,data[100];
 
    
    fileptr = fopen("myfile.txt", "a+");
   //extract character from file and store in chr
    chr = getc(fileptr);
    while (chr != EOF)
    {
        //Count whenever new line is encountered
        //take next character from file.
        strcat(data, &chr);
        chr = getc(fileptr);
    }
    fclose(fileptr); //close file.
	printf("Enter file name : ");
	scanf("%s", filechar);
	fileptr = fopen(filechar,"w");
	fputs(data,fileptr);
    return 0;
}