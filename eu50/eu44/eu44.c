/*************************************************************************
	> File Name: eu44.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月27日 星期五 15时54分44秒
 ************************************************************************/

#include<stdio.h>

int pentagonal(int x) {
    return n * (n * 3 - 1) / 2;
}

int is_pentagonal(int x){
    int head = 1; tail = 10000, mid;
    while(head <= tail) {
        mid = (head + tail) >> 1;
        if (pentagonal(mid) == x) return 1;
        if (pentagonal(mid) > x) tail = mid - 1;
        else head = mid + 1;
    }
    return 0;
}

int main() {
    
    return 0;
}
