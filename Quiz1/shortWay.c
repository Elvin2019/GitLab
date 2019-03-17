*#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main (int argc, const char *argv [] ) {

char data[100];
sprintf( data , "sudo find %s -print | grep -i %s ",argv[1] , argv [2] );
system(data);
}