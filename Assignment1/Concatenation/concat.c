#include <stdio.h>
#include <errno.h>

int main(int argc, char* argv[]) {
        if(argc <= 1)
        {
                printf("You must type \n");
        }
        else
        {
                for(int i = 1; i<argc; i++){
                        printf("%s",argv[i] );
                }

        printf("\n");

        }

}