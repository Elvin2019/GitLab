int fdinfo(int fd){


	int flag = fcntl(fd, F_GETFD);
    if((flag & FD_CLOEXEC)== 0 ){
    printf("fd: %u\n", fd);
    int flags = fcntl(fd, F_GETFL);
	
    if ((flags & O_ACCMODE) == O_RDONLY) {
        printf("read access\n");
    }
    if ((flags & O_ACCMODE) == O_WRONLY) {
        printf("write access\n");
    }
    if ((flags & O_ACCMODE) == O_RDWR) {
        printf("Read and write access\n");
    }
        printf("\n");
    if (flags & O_DIRECTORY) {
		 printf("directory flag");
    }
    if (flags & O_CREAT) {
        printf("create flag\n");
    }
    if (flags & O_EXCL) {
        printf("O_EXCL\n");
    }
	
    printf("F_GETFL: %u\n", flags);
}
	else{
	printf("\n file doesnt exist \n");
	}
    return 1;

}