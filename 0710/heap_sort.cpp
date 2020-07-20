/*************************************************************************
	> File Name: heap_sort.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 11 Jul 2020 08:57:29 AM CST
 ************************************************************************/

#include<iostream>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <stack>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <vector>
using namespace std;
#define swap(a, b) { \
                       __typeof(a) __temp = a; \
                       a = b, b = __temp; \
                   }

void up_maintain(int *arr, int ind) {
    while (ind > 1 && arr[ind] > arr[ind >> 1]) {
                swap(arr[ind], arr[ind >> 1]);
                ind >>= 1;
            
    }
        return ;

}

void down_maintain(int *arr, int ind, int n) {
        int temp;
    while (ind * 2 <= n) {
                temp = ind;
                if (arr[ind << 1] > arr[temp]) temp = ind << 1;
                if ((ind << 1 | 1) <= n && arr[ind << 1 | 1] > arr[temp]) temp = (ind << 1 | 1);
                if (temp == ind) break;
                swap(arr[ind], arr[temp]);
                ind = temp;
            
    }
        return ;

}

void heap_sort(int *arr, int l, int r) {
        int *brr = arr + l - 1, n = r - l + 1;
    for (int i = 2; i <= n; i++) {
                up_maintain(brr, i);
            
    }
    for (int i = n; i > 1; i--) {
                swap(brr[1], brr[i]);
                down_maintain(brr, 1, i - 1);
            
    }
        return ;

}

#undef swap



