/*************************************************************************
	> File Name: c
    ommon.c
	> Author: 
	> Mail: 
	> Created Time: Tue 14 Jul 2020 11:38:53 AM CST
 ************************************************************************/

#include<stdio.h>
#include "head.h"


int socket_create(int port) {
    int sockfd;
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        return -1;
    }
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        return -1;
    }

    if(listen(sockfd, 10) < 0) {
        return -1;
    }

    return sockfd;
}


int socket_connect(char *ip, int port) {
    int sockfd;
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        return -1;
    }
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ip);
    server.sin_port = htons(port);

    if (connect(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        //perror("connect()");
        return -1;
            
    }

    return sockfd;
}
