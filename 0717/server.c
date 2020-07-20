/*************************************************************************
	> File Name: server.c
	> Author: 
	> Mail: 
	> Created Time: Fri 17 Jul 2020 11:08:56 AM CST
 ************************************************************************/

#include<stdio.h>
#include "head.h"

#define MAX 200
int main(int argc, char **argv) {
    if(argc != 2) {
        fprintf(stderr, "Usage : %s port\n", argv[0]);
        exit(1);
    }
    int server_listen, port, sockfd;
    int max_fd; //最大文件描述符
    port = atoi(argv[1]);

    if((server_listen = socket_create(port)) < 0) {
        perror("socked_create");
        exit(1);
    }
    //存储sockfd
    
    int clients[MAX] = {0};
    for(int i=0; i<MAX; i++) {
        clients[i] = -1;
    }
    fd_set rfds, wfds, efds;

    max_fd = server_listen;
    while(1) {
        FD_ZERO(&rfds);
        FD_ZERO(&wfds);
        FD_ZERO(&efds);

        FD_SET(server_listen, &rfds); //server_listen 加入可读
        
        for (int i=0; i<MAX; i++) {
            if(clients[i] == server_listen) {
                continue;
            }
            if(clients[i] > 0) { 
                //存在文件描述符
                if(clients[i] > max_fd) {
                    max_fd = clients[i];
                }
                FD_SET(clients[i], &rfds);  //加入可读
            }
        }
        int ret_val = 0;
        if((ret_val = select(max_fd + 1, &rfds, NULL, NULL, NULL)) < 0) {
            perror("select");
            exit(1);
        }
        if(FD_ISSET(server_listen, &rfds)) {
            //有连接
            struct sockaddr_in client;
            socklen_t len = sizeof(client);
            if((sockfd = accept(server_listen, (struct sockaddr *)&client, &len)) < 0) {
                perror("accept");
                exit(1);
            }

            printf("Login : %s <%d>\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
            if(sockfd > MAX) {
                fprintf(stderr, "Too many clients\n" );
                close(sockfd);
            }else {
                if(clients[sockfd] == -1){
                    clients[sockfd] = sockfd;
                }
            }
        }
        for(int i=0; i<=max_fd; i++) {
            if(clients[i] == server_listen || clients[i] < 0) {
                continue;
            }
            if(FD_ISSET(clients[i], &rfds)) {
                char buff[512] = {0};
                int ret = recv(clients[i], buff, sizeof(buff), 0);
                if(ret <= 0) {
                    close(clients[i]);
                    clients[i] = -1;
                }
                printf("Recv : %s\n", buff);
                send(clients[i], buff, strlen(buff), 0);

            }
        }

    }
    return 0;
}
