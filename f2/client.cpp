#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


using namespace std;

int main(int argc, char **argv){
    if(argc == 3)
    {
        int sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if(sockfd == -1)
        {
            cout<<"socket";
            return -1;
        }
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(atoi(argv[2]));
        addr.sin_addr.s_addr = inet_addr(argv[1]);
        if(connect(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0)
        {
            cout<<"connect";
            return -1;
        }
        char buffer[1024] = "fujinghui\0";
        int len = 0;
        len = send(sockfd, buffer, strlen(buffer), 0);
        len = recv(sockfd, buffer, 1024, 0);
        cout<<"rece message:"<<buffer<<endl;
        //close(sockfd);
    }
    else
    {
        cout<<"useage:"<<argv[0]<<" <ip address> <port>"<<endl;
    }
    return 0;
}
