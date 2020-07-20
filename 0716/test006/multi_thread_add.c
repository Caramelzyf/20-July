/*************************************************************************
	> File Name: multi_thread_add.c
	> Author: 
	> Mail: 
	> Created Time: Thu 16 Jul 2020 07:12:55 PM CST
 ************************************************************************/

#include<stdio.h>
#include <pthread.h>
#include <stdlib.h>


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
long long int sum = 0;
int a = 0;


void *add(void *arg) {
    if(a >= 1000) {
        exit(1);
    }
    if(pthread_mutex_lock(&mutex) != 0) {
        perror("pthread_mutex_lock");
        exit(1);
    }
    a++;
    long unsigned int id = *((long unsigned int *)arg);
    
    printf("thread id:%lu\n",id);
    printf("sum:%lld,+a:%d\n", sum,a);
    
    sum += a;

    printf("after sum:%lld\n\n\n",sum);
    if(pthread_mutex_unlock(&mutex) != 0) {
        perror("pthread_mutex_unlock");
        exit(1);
    }

    pthread_exit(NULL);
}


int main() {
    pthread_t threads[5];
    long unsigned int thread_id[5];
    
    //int a = 1;

    pthread_mutex_init(&mutex, NULL);
    while(a < 1000) {
    for(int i = 0; i < 5; i++) {
        if(a >= 1000) {
            break;
        }
        thread_id[i] = i;
        pthread_create(&threads[i], NULL, add, (void*)&thread_id[i]);
        //printf("%d:%lu\n", i,thread_id[i]);
        
    }

        for(int i = 0; i < 5; i++) {
            if(a >= 1000) {
                break;
            }
            pthread_join(threads[i], NULL);
       }

        if(a >= 1000) {
            break;
        }
    }

    pthread_mutex_destroy(&mutex);
    return 0;
}
