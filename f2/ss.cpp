#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#define IPSTR "118.190.25.51"
#define PORT 80
#define BUFSIZE 1024
int main(void){
	char buf[8096];			//receive service response
	int offset = 0;
	int rc, sockfd;
	char str1[4096], str2[4096], buf1[BUFSIZE], *str;
	fd_set t_set1;
	socklen_t len;
	struct timeval tv;
	struct sockaddr_in addr;
	struct tm * t_tm;
	float tem = 20.0;
	char strtime[30];
	time_t timer;
	while(1)
	{
		sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if(-1 == sockfd)
		{
			perror("socket");
			return -1;
		}
		bzero(&addr, sizeof(addr));
		addr.sin_family = AF_INET;
		addr.sin_port = htons(PORT);
		if(inet_pton(AF_INET, IPSTR, &addr.sin_addr) == -1)
		{
			perror("inet_pton");
			return -1;
		}
		if(connect(sockfd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
		{
			perror("connect");
			return -1;
		}
		printf("create link at server!\n");
		
        memset(strtime, 0, 30);
        time(&timer);
        t_tm = localtime(&timer);
        sprintf(strtime, "%4d-%-2d-%-2dT%-2d:%02d:%02d", 
                t_tm->tm_year+1900, t_tm->tm_mon+1, t_tm->tm_mday,
                t_tm->tm_hour, t_tm->tm_min, t_tm->tm_sec
                );

        memset(str2, 0, 4096);
        strcat(str2, "{\r\n");
        strcat(str2, "\"timestamp\":");
        strcat(str2, "\"");
        strcat(str2, strtime);
        strcat(str2, "\"");
        strcat(str2, ",\"value\":");
        memset(strtime, 0, 30);
        tem += 5.2;
        sprintf(strtime, "%f", tem);
        strcat(str2, strtime);
        strcat(str2, "\r\n}\r\n");
        str = (char*)malloc(128);
        len = strlen(str2);
        sprintf(str, "%d", len);
        
        memset(str1, 0, 4096);
        strcat(str1, "POST /v1.0/device/356389/sensor/403791/datapoints\n");
        strcat(str1, "Host :api.yeelink.net\r\n");
        strcat(str1, "Content-Type: application/x-www-form-urlencoded\r\n");
        strcat(str1, "U-ApiKey:2084160151f9d6dd55df03158de575d7\r\n");
        strcat(str1, "Content-Length:");
        strcat(str1, str);
        strcat(str1, "\r\n");
        strcat(str1, "Connection:alive\r\n");
        strcat(str1, "\r\n");
        strcat(str1, str2);
        strcat(str1, "\r\n\r\n");
        printf("%s\n", str1);
        int ret = write(sockfd, str1, strlen(str1));
        if(ret == -1)
        {
            perror("write");
            return -1;
        }
        else
        {
            printf("message send success! send byte count:%d\n", ret);
        }
        FD_ZERO(&t_set1);					//select model
		FD_SET(sockfd, &t_set1);
		memset(buf1, 0, 1024 * 8);
        offset = 0;
        while(rc = read(sockfd, buf1 + offset, 1024) != -1)
        {
            offset += rc;
        }
        printf("-------------message%d!-----------------\n\n", offset);
        printf("%s\n", buf1);


        if(close(sockfd) == -1)
		{
			perror("close");
			return -1;
		}
        sleep(20);
	}

	return 0;
}
