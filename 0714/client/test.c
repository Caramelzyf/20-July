/*************************************************************************
	> File Name: client.c
	> Author: 
	> Mail: 
	> Created Time: Tue 14 Jul 2020 11:56:20 AM CST
 ************************************************************************/

#include<stdio.h>
#include "head.h"

struct UserInfo {
    char name[50];
    char id[50];
};


int main(int argc, char *argv[]) {
    if(argc != 3) {
        fprintf(stderr, "Usage: %s ip port!\n", argv[0]);
        exit(1);
    }

    char ip[20] = {0};
    int port;
    strcpy(ip, argv[1]);
    port = atoi(argv[2]);
    int sockfd;
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket()");
        exit(1);
    }

    struct sockaddr_in server;

    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(ip);


    if(connect(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("connect()");
        exit(1);
    }

    char buff[512] = {0};

    sprintf(buff, "Hello!");
    send(sockfd, buff, strlen(buff), 0);
    bzero(buff, sizeof(buff));

    recv(sockfd, buff, sizeof(buff), 0);
    printf("Server Echo : %s\n",buff);
   
    return 0;
}
