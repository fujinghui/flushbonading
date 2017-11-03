#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
int main(int argc, char **argv){
    if(argc != 3)
    {
        printf("usage:%s <pathname1> <pathname2>", argv[0]);
        return -1;
    }
    int src = open(argv[1], O_RDONLY);
    if(src == -1)
    {
        perror("open");
        return -1;
    }
    struct stat st;
    if(fstat(src, &st) == -1)
    {
        perror("fstat");
        return -1;
    }
    int dst = open(argv[2], O_WRONLY | O_CREAT | O_EXCL, st.st_mode);
    if(dst == -1)
    {
        if(errno != EEXIST)
        {
            perror("open");
            return -1;
        }
        printf("file %s exists!is over?(y/n)", argv[2]);
        int ch = getchar();
        if(ch != 'y' && ch != 'Y')
        {
            return -1;
        }
    }
        dst = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, st.st_mode);
        if(dst == -1)
        {
            perror("opne");
            return -1;
        }
        ssize_t bytes;
        char buf[1024] = {0};
        while((bytes=read(src, buf, sizeof(buf)))>0)
        {
           if(write(dst, buf, bytes) == -1)
           {
               perror("read");
               return -1;
           }
        }
        if(bytes == -1)
        {
            perror("read");
            return -1;
        }
        close(src);
        close(dst);
    return 0;
}





