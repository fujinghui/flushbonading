#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#define deal(x, y) (((1<<x)|((~(1<<y))<<8)))
#define show(x, y) ioctl(fd, 0, deal(x, y))
static int fd = -1;
unsigned char stext[] = {0x00, 0x7E, 0x42, 0x42, 0x42, 0x42, 0x7E, 0x00};
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
    //Sleep(1);

}
void text(unsigned char data[], int position){
    int i;
    
    if(position >= 0)
    {   
        for(i = 0; i < 8; i ++)
        {
            set((data[i] >> position)|(data[i]<<(8-position)), i);
        }
    }
    // else if(position<0)
    // {
    //     position = -position;
    //     for(i = 0; i < 8; i --)
    //     {
            
    //         set((data[i] << position), i);
    //     }
    // }

}
int main()
{
	int i=0;
	fd=open("/dev/matrixled",O_RDWR);
	if(fd<0)
	{
		printf("Can't open\n");
		return -1;
	}
	else
	{
		printf("openfadaf OK%x\n", fd);
	}
    int c = 0;
    int position = 0;
    //printf("fadfadf");
    
    while(1)
	{
        text(stext, position);
        c ++;
	    if(c > 440)
        {
            position ++;
            c = 0;
        }
        if(position > 8)
        {
            position = 0;
        }
        
    }

   	close(fd);
  	return 0;
}


