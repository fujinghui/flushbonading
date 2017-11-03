#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

static int fd = -1;
void Sleep(int ms){
    struct timeval delay;
    delay.tv_sec = 0;
    delay.tv_usec = ms * 1000;
    select(0, NULL, NULL, NULL, &delay);
}
int main()
{
	int i=0;
    int angle = 0;
    int mode = 0;
    fd=open("/dev/stepper",O_RDWR);
	if(fd<0)
	{
		printf("Can't open\n");
		return -1;
	}
	else
	{
		printf("open OK %x\n", fd);
	}
    i = 0;
    printf("please input angle and mode(1:forward 2:back):");
    scanf("%d %d", &angle, &mode);

    int t = 0;
	//ioctl(fd, 0, 0xf);
    for(; angle > 0;)
    {
        if(mode == 1)
        {
            for(i = 3; i >= 0 && angle > 0; i --, angle --)
            {
                ioctl(fd, 0, i);
                Sleep(10);
            }
        }
        else
        {
            for(i = 0; i <= 3 && angle > 0; i ++, angle --)
            {
                ioctl(fd, 0, i);
                Sleep(10);
            }
        }
    }
    close(fd);
    return 0;
    /*
	while(1)
	{
        for(t = 0; t < 25; t ++)
        {
            for(i=3;i>=0;i--)
            {
             ioctl(fd, 0, i);
             Sleep(10);
            }
        }
        for(t = 0; t < 25; t ++)
        {
	    	for(i=0;i<4;i++)
	    	{
	    		ioctl(fd, 0, i);
	    		Sleep(10);
	    	}
        }   
	}
	

   	close(fd);
  	return 0;
    */
}


