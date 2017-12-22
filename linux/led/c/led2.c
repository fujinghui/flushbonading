#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>


static int fd = -1;
void Sleep(int ms){
	struct timeval delay;
	delay.tv_sec = 0;
	delay.tv_usec = ms * 1000;
	select(0, NULL, NULL, NULL, &delay);
}

int main(void){
	char *param = NULL;
	int i;
	param = getenv("QUERY_STRING");
	printf("Content-Type:text/html;charset=utf-8\n\n");
	//header_print();
	if(param == NULL)
	{
		printf("{'status':'0', 'msg':'param error!'}");
		return -1;
	}
	printf("param:%s\n<br />", param);
}
