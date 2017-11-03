#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <wait.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void sigchild(int signum){
    for(;;)
    {
        pid_t pid = waitpid(-1, 0, WNOHANG);
        if(pid == -1)
        {
            if(errno != ECHILD)
            {
                perror("wait");
                exit(-1);
            }
            printf("service:all child progress is exit...\n");
            break;
        }
        if(pid)
        {
            printf("service:find %u child exit...\n", getpid());
        }
        else
        {
            printf("service:not find have child progress\n");
            break;
        }
    }
}

int main(int argc, char **argv){
    std::cout<<"fadsf"<<std::endl;
    if(argc < 2)
    {
        std::cout<<"useage:"<<argv[0]<<" <port>"<<std::endl;
        return -1;
    }
    if(signal(SIGCHLD, sigchild) == SIG_ERR)
    {
        perror("signal");
        return -1;
    }
    std::cout<<"service:create network socket..."<<std::endl;
    //network tcp ip(is 0)
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1)
    {
        std::cout<<"socket";
        return -1;
    }
    std::cout<<"service:address bind"<<std::endl;
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[1]));
    addr.sin_addr.s_addr=INADDR_ANY;
    int res = bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
    if(res == -1)
    {
        perror("bind");
        return -1;
    }
    printf("service:listen socket!\n");
    //wait max is 1024
    if(listen(sockfd, 1024) == -1)
    {
        perror("listen");
        return -1;
    }
    for(;;)
    {
        printf("service:wait link connection!\n");
        struct sockaddr_in addrcli = {};
        socklen_t addrlen = sizeof(addrcli);
        int connfd = accept(sockfd, (struct sockaddr*)&addrcli, &addrlen); 
        if(-1 == connfd)
        {
            perror("accept");
            return -1;
        }
        printf("service rece from:%s:%u client\n", inet_ntoa(addrcli.sin_addr), ntohs(addrcli.sin_port));
        pid_t pid = fork();
        if(pid == -1)
        {
            perror("fork");
            return -1;
        }
        //this code need change
        else if(pid == 0)            //child progress
        {
            printf("%u child progress:is%s:%u client service...\n", getpid(),
                   inet_ntoa(addrcli.sin_addr),
                   ntohs(addrcli.sin_port));
            if(close(sockfd) == -1)
            {
                perror("sockfd");
                return -1;
            }
            for(;;)
            {
                char buf[1024];
                printf("%u child progress:recive request...\n", getpid());
                ssize_t rb = recv(connfd, buf, sizeof(buf), 0);
                if(rb == -1)
                {
                    perror("recv");
                    return -1;
                }
                if(rb == 0)
                {
                    printf("%u child progress:client close link!\n", getpid());
                    break;
                }
                printf("%u child progress:send responsed...\n", getpid());
                if(send(connfd, buf, rb, 0) == -1)
                {
                    perror("send");
                    return -1;
                }
            }
            printf("%u child progress:close socket...\n", getpid());
            return 0;
            
        }
        if(close(connfd) == -1)
        {
            perror("close");
            return -1;
        }
    }
    printf("service:close listen socket...\n");
    if(close(sockfd) == -1)
    {
        perror("close");
        return -1;
    }
    printf("completion\n");
    return 0;
}
