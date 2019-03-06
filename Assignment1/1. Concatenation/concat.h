#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void concat(int argc,const char *argv[])
{
int i;
char a[100],b[100];

for(i=1; i< argc; i++)
{ strcpy( b , argv[i]);
    
  if(((isdigit(b[i]))  || (isalpha(b[i]))) != 0)
  {
      strcat(a,b);
  }
  else{}

}
for(i =0; i< strlen(a); i++ )


{
   if(((isdigit(a[i]))  || (isalpha(a[i]))) != 0)
  {
      printf("%c",a[i]);
  }
  else{}



}
