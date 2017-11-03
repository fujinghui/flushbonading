#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
int main(void){
    printf("error%s", "fadfafasdfasdfads");
    printf("errorno=%d\n", errno);   
    printf("--------------\n");
    FILE *fp = fopen("xinxiang.txt", "rb");
    if(NULL == fp)
    {
        printf("errno=%d\n", errno);
        perror("fopen");
        return -1;
    }
    else
    {
        printf("errno=%d\n", errno);
    }
    fclose(fp);
    fp = NULL;
    return 0;
}
