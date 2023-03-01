#include "main_header.h"

#define TEE_SIZE 255

ssize_t tee () {
    char * buffer = calloc(TEE_SIZE,sizeof(char));
    ssize_t NumRead = read(0,buffer,TEE_SIZE);
    if(NumRead==-1){
        perror("read");
        return 1;
    }
    ssize_t NumWrite = write(1,buffer,(size_t)NumRead);
    if(NumRead==-1){
        perror("write");
        return 1;
    }
}

int cp (const char* pathname1, const char* pathname2){
    int fd1,fd2;
    char * buffer = calloc(TEE_SIZE,sizeof(char));
    ssize_t NumRead = 1;
    fd1 = open(pathname1,O_RDWR);
    if(fd1==-1){
        perror("open1");
        return 1;
    }
    fd2 = open(pathname2,O_RDWR|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR);
    if(fd2==-1){
        perror("open2");
        return 1;
    }
    while (NumRead != 0){
        NumRead = read(fd1,buffer,TEE_SIZE);
        if(NumRead ==-1){
            perror("read");
            return 1;
        }
        if(write(fd2,buffer,(size_t)NumRead) == -1){
            perror("write");
            return 1;
        }
    }
    close(fd1);
    close(fd2);
}

ssize_t rev (const char* pathname){
    int fd;
    char * buffer;
    off_t NowPosition;
    fd = open(pathname,O_RDWR);
    if(fd==-1){
        perror("open1");
        return 1;
    }
    NowPosition=lseek(fd,-1,SEEK_END);
    while (NowPosition > 0){
        if(read(fd,buffer,1) == -1){
            perror("read");
            return 1;
        }
        if(write(1,buffer,1) == -1){
            perror("write");
            return 1;
        }
        NowPosition=lseek(fd,-2,SEEK_CUR);
    }
    close(fd);
}