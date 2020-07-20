/*************************************************************************
	> File Name: multi_process.c
	> Author: 
	> Mail: 
	> Created Time: Thu 16 Jul 2020 05:28:17 PM CST
 ************************************************************************/

#include<stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char **argv)  //命令行解析
{
    int opt;
    int flag = 0;
    char msg[512] = {0};
    
    while((opt = getopt(argc, argv, "m:")) != -1) {
    switch (opt) {
        case 'm':
        strcpy(msg, optarg);
        flag = 1;
        break;
        default:
        fprintf(stderr, "Uasge : %s [-m msg]\n",argv[0]);
        return 0;
        }
            
    }

    if(flag == 0) {
        int pid = fork();
        if(pid != 0) { 
            //父进程
            int status;
            int result = wait(&status);
            if(result == -1 || status != 0) {
                printf("fork error!\n");
                return 0;
            }else {
                system("cat msg.txt");
            }
        } else {
            //子进程
            system("vim msg.txt");
            
        }
    } else {
        printf("msg = %s\n", msg);
    }
    return 0;

}
