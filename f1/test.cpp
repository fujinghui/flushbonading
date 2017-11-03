#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
int main(void){
    write(1, "hello world!\n", 13);    
    char *s = strerror(0);
    return 0;
}
