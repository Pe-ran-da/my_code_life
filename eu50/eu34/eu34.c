/*************************************************************************
	> File Name: eu34.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月22日 星期日 11时38分24秒
 ************************************************************************/

#include<stdio.h>
#define MAX_S 362880*7
int arr[10] = {1, 1};

void arr_sum() {
    for (int i = 2; i < 10; i++) {
        arr[i] = i * arr[i - 1]; 
    }
}

int factorial(int x) {
    arr_sum();
    int key = x;
    int ans = 0;
    while(x) {
        ans += arr[x % 10];
        x /= 10;
    }
    return key == ans;
}

int main(){
    //arr_sum();
    int add = 0;
    for (int i = 3; i < MAX_S; i++) {
        if(factorial(i)) add += i;
    }
    printf("%d\n", add);
    return 0;
}


