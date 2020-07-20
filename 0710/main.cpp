/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 11 Jul 2020 09:01:10 AM CST
 ************************************************************************/

#include<iostream>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <stack>
#include <algorithm>
#include <cstring>
#include <map>
#include <set>
#include <vector>
#include "quick_sort.h"

using namespace std;

#define TEST(func, arr, l, r) { \
    int *temp = (int *)malloc(sizeof(int) * (r - l + 1)); \
    memcpy(temp, arr, sizeof(int) * (r - l + 1)); \
    int b = clock(); \
    func(temp, l, r); \
    int e = clock(); \
    double t = 1.0 * (e - b) / CLOCKS_PER_SEC; \
    if (!check(temp, l, r)) { \
        printf("%s(%.3lf s) is \033[1;35mFAILED\033[0m\n", #func, t); \
    } else { \
        printf("%s(%.3lf s) is \033[1;32mOK\033[0m\n", #func, t); \
    } \
    free(temp); \
}

int *gen_data(int n) {
    int *arr = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % n;
            
    }
    return arr;

}

int check(int *arr, int l, int r) {
    for (int i = l + 1; i <= r; i++) {
        if (arr[i] < arr[i - 1]) return 0;
            
    }
        return 1;

}

void test1() {
    #define MAX_N 10000000
        printf("\ntest 1, random data, size: %d\n", MAX_N);
        int *arr = gen_data(MAX_N);
        
        TEST(quick_sort_v7, arr, 0, MAX_N - 1);
        free(arr);
        return ;
    #undef MAX_N

}

void test2() {
    #define MAX_N 100000
        printf("\ntest2, ordered data, size: %d\n", MAX_N);
        int *arr = gen_data(MAX_N);
        for (int i = 0; i < MAX_N; i++) arr[i] = i;
        TEST(quick_sort_v7, arr, 0, MAX_N - 1);
        
    free(arr);
    #undef MAX_N  

}

int main() {
        srand(time(0));
        test1();
        test2();
        return 0;

}
