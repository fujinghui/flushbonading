#include <stdio.h>
int main(void){
    //char a = '\72';
    //printf("%c", a);
    int a = 0;
    int b = (a=-1)?2:3;
    int c = (a=0)?2:3;
    printf("%d %d\n", b, c);
    return 0;
}
