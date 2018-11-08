/*************************************************************************
> File Name: 9.heap_sort.cpp
> Author: Peranda
> Mail: 1365227825@qq.com 
> Created Time: 2018年10月30日 星期二 20时27分44秒
************************************************************************/

#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

#define swap(a, b) { \
    __typeof(a) __temp = a; a = b; b = __temp;\
}


void heap_sort(int *arr, int n) {
    int *p = arr - 1;
    for (int i = n >> 1; i >= 1; i--) {
        int ind = i;
        while ((ind <= 1) <= n) {
            int temp = ind;
            if (p[temp] < p[ind << 1]) temp = ind << 1;
            if ((ind << 1 | 1) <= n && p[temp] < p[ind << 1 | 1])
                temp = ind << 1 | 1;
            if (temp == ind ) break;
            swap(p[temp], p[ind]);
            ind = temp;
        }
    }
    for (int i = n; i > 1; i--) {
        swap(p[i], p[1]);
        int ind = 1;
        while ((ind << 1) <= i - 1) {
            int temp = ind;
            if (p[temp] < p[ind << 1]) temp = ind << 1;
            if ((ind << 1 | 1) <= i - 1 && p[temp] < p[ind << 1 | 1])
                temp = ind << 1 | 1;
            if (temp == ind ) break;
            swap(p[temp], p[ind]);
            ind = temp;
        }
    }
    return ;
}

void output(int *num, int n) {
    printf("heap_sort : [");
    for (int i = 0; i < n; i++) {
        printf(" %d", num[i]);
    }
    printf("]\n");
}

int main() {
    srand(time(0));
    #define MAX_N 20 
    int arr[MAX_N];
    for (int i = 0; i < MAX_N; i++) {
        arr[i] = rand() % 100;
    }
    output(arr, MAX_N);
    heap_sort(arr, MAX_N);
    output(arr, MAX_N);
    return 0;
}
