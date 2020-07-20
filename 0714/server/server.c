/*************************************************************************
	> File Name: server.c
	> Author: 
	> Mail: 
	> Created Time: Tue 14 Jul 2020 11:49:01 AM CST
 ************************************************************************/

#include<stdio.h>
#include "head.h"


int main(int argc, char **argv) {
    if(argc != 2) {
        fprintf(stderr, "Usage : %s port!\n", argv[0]);
        exit(1);
    }

    int server_listen, port, sockfd;
    port = atoi(argv[1]);

    if((server_listen = socket_create(port)) < 0) {
        perror("socket_create()");
        exit(1);
    }

    if((sockfd = accept(server_listen, NULL, NULL)) < 0) {
        perror("accept()");
        exit(1);
    }

    
    char buff[512] = {0};
    recv(sockfd, buff, sizeof(buff), 0);
    printf("Recv: %s\n",buff);
    send(sockfd, buff, strlen(buff), 0);
    //printf("send over\n");
    close(sockfd);
    close(server_listen);
    return 0;
}

