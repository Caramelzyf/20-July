/*************************************************************************
	> File Name: file_client.c
	> Author: 
	> Mail: 
	> Created Time: Wed 15 Jul 2020 11:22:47 AM CST
 ************************************************************************/

#include<stdio.h>
#include "head.h"

int main(int argc, char **argv) {
    if (argc != 4) {
        fprintf(stderr, "Usage : %s ip port file!\n", argv[0]);
        exit(1);
            
    }
    char ip[20] = {0};
    int port, sockfd;
    FILE *fp;
    char fname[50] = {0};

    strcpy(ip, argv[1]);
    port = atoi(argv[2]);
    strcpy(fname, argv[3]);

    if ((sockfd = socket_connect(ip, port)) < 0) {
        perror("socket_connect()");
        exit(1);
            
    }
    
    if((fp = fopen(fname ,"r")) == NULL) {
        perror("fopen()");
        exit(1);
    }

    size_t size;
    char buff[18888] = {0};

    while((size = fread(buff, 1, 18888, fp))) {
        send(sockfd, buff, size, 0);
        printf("send successed!\n%s ", buff);
        bzero(buff, sizeof(buff));
        
    }

    close(sockfd);
    fclose(fp);
    
    return 0;
}

