/*************************************************************************
	> File Name: 1.test.pth.c
	> Author: 
	> Mail: 
	> Created Time: Thu 16 Jul 2020 11:47:07 AM CST
 ************************************************************************/

#include<stdio.h>
#include <pthread.h>
#include <string.h>

void *work(void *arg) {
    printf("In thread!\n");
    printf("name is %s\n", (char*)arg);

}
int main() {
    pthread_t tid;
    char name[20] = {0};
    strcpy(name, "zyf");

    pthread_create(&tid, NULL, work, (void*)name);

    pthread_join(tid, NULL);
    return 0;

}
