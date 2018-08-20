/*************************************************************************
	> File Name: P1190接水问题（数论）.c
	> Author: Peranda
	> Mail: 
	> Created Time: 2018年08月20日 星期一 13时56分11秒
 ************************************************************************/

#include <stdio.h>
#include <algorithm>
#define MAX_N 10000
#define MAX_MIN 100

int arr[MAX_N + 10] = {0}; 
int ans[MAX_MIN + 10] = {0};

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &arr[i]);
        if (i <= m) ans[i] = arr[i];
        if (i > m) {
            std::sort(ans+1, ans+m+1); //往最小的桶装东西
            ans[1] += arr[i];//最小的桶
        }
    }
    std::sort(ans+1, ans+m+1);
    printf("%d\n", ans[m]);
    return 0;
}
