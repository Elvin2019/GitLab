/*
 * C Program to Find the Number of Lines in a Text File
 */
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int main(int argc, const char *argv[])
{	
	time_t current_time;
    char* c_time_string;
	char data[1000],data1[1000];

    current_time = time(NULL);

    if (current_time == ((time_t)-1))
    {
        (void) fprintf(stderr, "Failure to obtain the current time.\n");
        exit(EXIT_FAILURE);
    }

    /* Convert to local time format. */
    c_time_string = ctime(&current_time);

    if (c_time_string == NULL)
    {
        (void) fprintf(stderr, "Failure to convert the current time.\n");
        exit(EXIT_FAILURE);
    }

    
    FILE *fileptr;
    int count_lines = 0, count_words=0,max_length=0,min_length=0,errnum,result;
    char filechar[40], chr;
 
    printf("Enter file name:");
    scanf("%s", filechar);
    fileptr = fopen(filechar, "r");
	if (fileptr == NULL) {
   
      errnum = errno;
      fprintf(stderr, "Value of errno: %d\n", errno);
      perror("Error printed by perror");
	  result = -1;
 } 
    else {
   
     
   
   //extract character from file and store in chr
    chr = getc(fileptr);
    while (chr != EOF)
    {   count_words++;
        //Count whenever new line is encountered
        if (chr == '\n')
        {
			
            count_lines = count_lines + 1;
			if( max_length < count_words)
			{ max_length = count_words;}
			if(min_length > count_words)
			{
			min_length = count_words;}
			count_words = 0;
        }
        //take next character from file.
        chr = getc(fileptr);
    }
    fclose(fileptr); //close file.
    printf("There are %d lines %d is maximum length %d is minimum length \n", count_lines, max_length, min_length);
	}
	fileptr = fopen("counter.log","a+");
	if(result == -1)
	{(void) sprintf(data," %s %d", c_time_string,result);
	  fputs(data,fileptr);
	  }
	else{
		(void) sprintf( data1," %s %d %d %d" , c_time_string, count_lines,max_length,min_length);
		fputs(data1,fileptr);
    return 0;
}}