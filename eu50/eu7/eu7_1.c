/*************************************************************************
	> File Name: eu7_1.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月24日 星期二 09时34分25秒
 ************************************************************************/

#define MAX_S 10000

int arr[MAX_S + 10] = {};

int main() {
    for (int i = 2; i <= MAX_S; i++) {
        if(arr[i]) continue;
        for (int j = i; j <= MAX_S; j += i) {
            arr[j] = i;  // 计算数ｉ最大素因子
        }
    }    
    for (int i = 2; i <= MAX_S; i++) {
        if (!arr[i]) arr[i] = i;
    }
    for (int i = 2; i <= MAX_S; i++) {
        printf("%d %d \n", i, arr[i]);
    }
    printf("\n");
    return 0;
}
