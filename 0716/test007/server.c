/*************************************************************************
	> File Name: server.c
	> Author: 
	> Mail: 
	> Created Time: Tue 14 Jul 2020 11:49:01 AM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include <pthread.h>
#include "head.h"

void *work(void *arg) {
    printf("In work:\n");
    int sockfd = *((int *)arg);
    
    char buff[512] = {0};
    recv(sockfd, buff, sizeof(buff), 0);
    printf("Recv: %s\n", buff);
    send(sockfd, buff, strlen(buff), 0);
    printf("send over\n");
    close(sockfd);

}
int main(int argc, char **argv) {
    if(argc != 2) {
        fprintf(stderr, "Usage : %s port!\n", argv[0]);
        exit(1);
    }

    int server_listen, port;
    port = atoi(argv[1]);

    if((server_listen = socket_create(port)) < 0) {
        perror("socket_create()");
        exit(1);
    }

    pthread_t threads[10];
    int i=0;

    while(1){
        if(i >= 10) {
            printf("over error!\n");
        }
        int sockfd;
        if((sockfd = accept(server_listen, NULL, NULL)) < 0) {
            perror("accept");
            exit(1);
        }
    printf("sockfd:%d",sockfd);

        pthread_create(&threads[i], NULL, work, (void*)&sockfd);
        printf("Create success\n");
        pthread_join(threads[i], NULL);
    
        i++;

    }
    close(server_listen);
    return 0;
}

