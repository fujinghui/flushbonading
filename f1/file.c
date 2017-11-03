#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
int main(void){
    int fp = open("open.txt", O_CREAT | O_RDWR | O_TRUNC, 666);//S_IRWXU | S_IXGRP | S_IROTH | S_IXOTH);
    if(fp != NULL)
    {
        write(fp, "hello", 5);
        printf("yes");
    }else
    {
        printf("error:%d\n", errno);
    }
    close(fp);
    return 0;
}
