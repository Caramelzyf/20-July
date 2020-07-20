/*************************************************************************
	> File Name: file_server.c
	> Author: 
	> Mail: 
	> Created Time: Wed 15 Jul 2020 11:06:17 AM CST
 ************************************************************************/

#include<stdio.h>
#include "head.h"

int main(int argc, char **argv) {

    if(argc != 2) {
        fprintf(stderr, "Usage : %s port!\n", argv[0]);
        exit(1);
    }

    int server_listen, sockfd, port;
    port = atoi(argv[1]);
    if((server_listen = socket_create(port)) < 0) {
        perror("socket_create()");
        exit(1);
    }

    //while(1) {

    
        if((sockfd = accept(server_listen, NULL, NULL)) < 0) {
            perror("accept()");
            exit(1);
        }

        FILE *fp = NULL;
        if((fp = fopen("./tmp_test.txt", "w")) == NULL) {
            perror("fopen()");
            exit(1);
        }
        long long int fsize;
        recv(sockfd, (char*)&fsize, sizeof(fsize), 0);
        printf("%lld\n",fsize);

        while(1) {
            
            char buff[18888] = {0};
            long long int retval = recv(sockfd, buff, fsize, 0);
            printf("%s", buff);

            if(retval <= 0) {
                
               close(sockfd);
               break;
            }
            int nwrite = fwrite(buff, 1, fsize, fp);
            if(retval == fsize) {
                close(sockfd);
                break;
            }

        }
        fclose(fp);

    //}
    return 0;
}
