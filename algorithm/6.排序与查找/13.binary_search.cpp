/*************************************************************************
	> File Name: 13.binary_search.cpp
	> Author: peranda
	> Mail:1365227825@qq.com  
	> Created Time: 2018年11月06日 星期二 19时27分16秒
 ************************************************************************/

#include <stdio.h>


int binary_search(int *num, int n, int x) {
    int head = 0, tail = n - 1, mid;
    while (head <= tail) {
        mid = (head + tail) >> 1;
        if (num[mid] == x) return mid;
        if (num[mid] > x) tail = mid - 1;
        else head = mid + 1;
    }
    return -1;
}

//111100000
int binary_search2(int *num, int n) {
    int head = -1, tail = n - 1, mid;
    while (head < tail) {
        mid = (head + tail + 1) >> 1;
        if (num[mid] == 1) head = mid;
        else tail = mid - 1;
    }
    return head;
}

// 00001111
int binary_search3(int *num, int n) {
    int head = 0, tail = n, mid;
    while (head < tail) {
        mid = (head + tail) >> 1;
        if (num[mid] == 1) tail = mid;
        else head = mid + 1;
    }
    return head == n ? -1 : head;
}

int main() {
    
    //    printf(" %d\n", binary_search(num, n, 1));
    printf(" %d\n", binary_search2(num, n));
//    printf(" %d\n", binary_search3(num, n));
    return 0;
}
