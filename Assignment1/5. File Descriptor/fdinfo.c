#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "fdinf.h"

void main(int argc, const char *argv[]){

 fdinfo(strtol(argv[1],NULL,10));
 
 }