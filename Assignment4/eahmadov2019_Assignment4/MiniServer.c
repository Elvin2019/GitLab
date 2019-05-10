#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/sendfile.h>


#define PORT 9000 //port number is given 

//static web page html content 
char web_content[] = "HTTP/1.1 200 OK\nContent-Type: text/html; charset=UTF-8\r\n\r\n"
"<!DOCTYPE html>\r\n"
"<html> <head> <title>A very simple webpage</title> <basefont size=4> </head>\r\n"
"<body bgcolor=FFFFFF>\r\n" 
"<h1>A very simple webpage. This is an  level header.</h1>\r\n"
"<h2>This is a level h2 header.</h2>\r\n"
"<h6>This is a level h6 header.  Pretty small!</h6>\r\n"
"<p>This is a standard paragraph.</p>\r\n"
"<p align=center>Now I've aligned it in the center of the screen.</p>\r\n"
"<p align=right>Now aligned to the right</p>\r\n"
"<p><b>Bold text</b></p>\r\n"
"<p><strong>Strongly emphasized text</strong>  Can you tell the difference vs. bold?</p>\r\n"
"<p><i>Italics</i></p>\r\n"
"<p><em>Emphasized text</em>  Just like Italics!</p>\r\n"
"<p>Here is a pretty picture: <img align=top src= prettypicture.jpg> </p> </body> </html>\r\n";



int main(int argc, char const *argv[])
{	
	char buf[4096];
    int fd_s, fd_cl, new_socket, fd_img ,bind_server;
	int on = 1;
	//long valread;
    struct sockaddr_in s_addr, cl_addr;
    socklen_t s_len = sizeof(s_addr);
	
	//int addrlen = sizeof(address);
    // Only this line has been changed. Everything is same.
    //char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
    // Creating socket file descriptor
   fd_s = socket(AF_INET, SOCK_STREAM, 0);
   if (fd_s < 0)
    {
        perror("In socket");
        exit(1);
    }
	//last_fd = fd_s;
    setsockopt(fd_s, SOL_SOCKET,SO_REUSEADDR, &on, sizeof(int));

    s_addr.sin_family = AF_INET; //host byte order
    s_addr.sin_addr.s_addr = INADDR_ANY; //auto-fill with my IP/
    s_addr.sin_port = htons( PORT ); //short, network byte order 
    
  //  memset(address.sin_zero, '\0', sizeof address.sin_zero);
    
	bind_server = bind(fd_s, (struct sockaddr *)&s_addr, sizeof(s_addr));
    if (bind_server == -1)
    {
        perror("In bind");
		close(fd_s);
        exit(1);
    }
    if (listen(fd_s, 10) == -1)
    {
        perror("In listen");
        close(fd_s);
		exit(1);
    }


	 //fcntl(fd_s, F_SETFL, O_NONBLOCK); /* Change the socket into non-blocking state	*/
    // fcntl(fd_cl, F_SETFL, O_NONBLOCK); /* Change the socket into non-blocking state	*/

    while(1)
    {
        printf("\n Mini server is created need to be requested via http://localhost:9000/  \n\n");
		fd_cl = accept(fd_s, (struct sockaddr *)&cl_addr, &s_len);
		if (fd_cl == -1){
            perror("failed to connect ....");
            continue;
			//exit(EXIT_FAILURE);
			}
		printf("connected to client ....");
		
        if(!fork()){
			//clidh process
			close(fd_s);
			memset(buf,0,4096);
			read(fd_cl,buf,4095);
	
			printf("%s\n", buf);
			//openning image on browser 
			if(!strncmp(buf, "GET /prettypicture.jpg", 22)){ //checking 
				fd_img = open("prettypicture.jpg", O_RDONLY); // open 
				sendfile(fd_cl, fd_img, NULL, 20000); //size is 14700 in sample image  //send file 
				close(fd_img);
			}
			else 
			write(fd_cl, web_content, sizeof(web_content)-1);
		
		close(fd_cl);
		printf("client server is closing ..\n");
		exit(0);
		}
		//parent process
		close(fd_cl);
	
        /*char buffer[30000] = {0};
    //    valread = read( new_socket , buffer, 30000);
        printf("%s\n",buffer );
        write(new_socket , hello , strlen(hello));
        printf("------------------Hello message sent-------------------");
        close(new_socket);
    */
	}
    return 0;
}


 