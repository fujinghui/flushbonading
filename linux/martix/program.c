
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define deal(x, y) (((1<<x)|((~(1<<y))<<8)))
#define show(x, y) ioctl(fd, 0, deal(7-x, y))

static int fd = -1;

unsigned char read_char[50] = {"1"};     //read char
unsigned char key[32];
void Sleep(int ms){
    struct timeval delay;
    delay.tv_sec = 0;
    delay.tv_usec = ms * 50;
    select(0, NULL, NULL, NULL, &delay);
}

void set(int data, int line){
    int i;
    for(i = 0; i < 8; i ++)
    {
        if(data&(1<<i))
        {
            show(i, line);
            Sleep(1);
        }
    }
}

void text(unsigned char data[], int position){
    int i;
    
    if(position >= 0)
    {   for(i = 0; i < 8; i ++)
        {
         set((data[i] >> position)|(data[i]<<(8-position)), i);
        }
    }
    else if(position<0)
    {
        position = -position;
        for(i = 0; i < 8; i --)
        {
            
            set((data[i] << position), i);
        }
    }

}
unsigned char mask[8] = {
    0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01
};
void readFont(unsigned char read_char[], unsigned char key[32]){
    int fd = open("16x16/hzk16k", O_RDONLY);
    int len = 0, i;
    if(fd == -1)
    {
        printf("open error!\n");
        return;
    }
    int offset = 
    (94 * (unsigned int)(read_char[0]-0xa0-1) + (read_char[1]-0xa0-1))*32;
    lseek(fd, offset, SEEK_SET);
    printf("offset:%d\n", offset);
    len = read(fd, key, 32);
    if(len != 32)
        printf("read error!\n");
    close(fd);                                  //close file
}
//convert encoding to gb2312
void toConvertGB2312(unsigned char read_char[]){
    //printf("parse:%d\n", read_char[0]&0x80);
    int flag = read_char[0]&0x80;
    if(flag == 0)                               //is ascii
    {
        unsigned char temp = read_char[0];
        read_char[0] = 0xA3;
        read_char[1] = temp|0x80;
    }
}
//will 16*16 point font to convert 8*8 point font
//arithmetic coordinate to divide 2
void Convert16To8(
    unsigned char input_str[],
    unsigned char output_str[]){
    int i, j;
    int position_16, position_8;
    for(i = 0; i < 16; i ++)
    {
        for(j = 0; j < 16; j ++)
        {
            int flag = input_str[i * 2 + j / 8]&mask[j%8];
            if(flag)
            {
                //will bit set 1
                int ty = ((i * 10)/2+5)/10;
                int tx = ((j * 10)/2+5)/10;
                ty = (ty>=8)?(7):ty;
                tx = (tx>=8)?(7):tx;
                output_str[(i*10/2+5)/10] |= mask[(j*10/2+5)/10];
            } 
        }
    }
}
void initDevice(){
    fd = open("/dev/matrixled", O_RDWR);
    if(fd < 0)
    {
        printf("Can't open\n");
    }
}

void inputParam(){
    int len;
    char *lenstr;
    char buffer[128];
    lenstr = getenv("CONTENT_LENGTH");
    if(lenstr == NULL)
    {
        printf("param error!");
    }
    else
    {
        len = atoi(lenstr);
        fgets(buffer, len + 1, stdin);
        if(sscanf(buffer, "text=%[^&]", read_char) != 1)
        {
            printf("param error\n");
            return;
        }
    }
    printf("Content-Type:text/plain;charset=us-ascii\r\n");
    
}
int main(void){
    unsigned char show_text[8];
	int position = 0;
    int i, j, k;
    //init
    memset(show_text, 0, sizeof(show_text));
    inputParam();
    //scanf("%s", read_char);
    printf("convert before encoding:");
    for(i = 0; i < 5; i ++)
        printf("%x ", read_char[i]);
    printf("\n");
    toConvertGB2312(read_char);             //read a number
    printf("GB2312 encoding:%x %x\n", read_char[0], read_char[1]);
    readFont(read_char, key);
    printf("data:");
    for(i = 0; i < 32; i ++)
    {
        printf("%x ", key[i]);
    }
    printf("\n");
    for(i = 0; i < 16; i ++)
    {
        for(k = 0; k < 2; k ++)
        for(j = 0; j < 8; j ++)
        {
            if(key[i * 2 + k]&mask[j])
                printf("*");
            else
                printf(" ");
        }
        printf("\n");
    }
    printf("Convert before(8*8):\n");
    Convert16To8(key, show_text);
    for(i = 0; i < 8; i ++)
    {
        for(j = 0; j < 8; j ++)
        {
            if(show_text[i] & mask[j])
                printf("*");
            else
                printf(" ");
        }
        printf("\n");
    }
    printf("\n");
    initDevice();       //init device
    i = 0;
    j = 0;
    while(j < 1)
    {
        text(show_text, position);
        if(i > 500)
        {
            i = 0;
            position ++;
            if(position >= 8)
             {
                 position = 0;
                 j ++;
             }
        }
        i ++;
    }
    close(fd);
	return 0;
}
