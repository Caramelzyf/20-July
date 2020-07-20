/*************************************************************************
	> File Name: quick_sort_v7.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 11 Jul 2020 09:11:38 AM CST
 ************************************************************************/

#include<iostream>
#include<math.h>
using namespace std;

#define swap(a, b) { \
    __typeof(a) __temp = a; \
    a = b, b = __temp; \
}

void unguarded_insert_sort(int *arr, int l, int r) {
        int  ind = l;
    for(int i = l + 1; i <= r; i++) {
                if(arr[i] < arr[ind])
                    ind = i;
            
    }
        swap(arr[l], arr[ind]);
    for (int i = l + 2; i <= r; i++) {
                int j = i;
        while(arr[j] < arr[j-1]) {
                        swap(arr[j], arr[j-1]);
                        --j;
                    
        }
            
    }
        return;

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

int med_num(int *arr, int l, int r) {
        int a=arr[l], b=arr[r], c= arr[(l+r) /2];

        if (a > b) swap(a, b);
        if (b > c) swap(b, c);
        if (a > b) swap(a, b);
        return b;

}

void in_quick_sort_v7(int *arr, int l, int r,int h ,int n) {
    while (r - l >= 16 && h < 2 * log(n)) {
        int x = l, y = r, z = med_num(arr,l,r);
        int temp;
        do {
            while(arr[x] < z)
                x++;
            while(arr[y] > z)
                y--;
            if(x <= y) {
                //swap(arr[x],arr[y]);
                temp = arr[x], arr[x] = arr[y], arr[y] = temp;
                x++;
                y--;
                                                              
            }      
        } while (x <= y);
        h++;
        in_quick_sort_v7(arr, l, y, h, n);
        l = x ;
            
    }
        
    if(l < r) {
        unguarded_insert_sort (arr, l, r);
            
    }
    else if (h >= 2 * log(n)) {
        heap_sort(arr, l ,r);
    }
        return ;

}

void quick_sort_v7(int *arr, int l, int r) {
    int h = 0;
    int n = r+1;
    in_quick_sort_v7(arr, l, r, h, n);
}

