/*************************************************************************
> File Name: P1614爱与愁的心痛（滑动窗口法）.c
> Author: Peranda
> Mail: 
> Created Time: 2018年08月20日 星期一 16时25分01秒
************************************************************************/

#include <stdio.h>
#define MAX_N 3000

int arr[MAX_N + 10] = {0};

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    if (n == 0) {
        printf("0\n");
        return 0;
    }
    int ans = 0;
    int min_val = 0x7fffffff;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &arr[i]);
        ans += arr[i];
        if (i == m) min_val = ans;
        if (i > m && i <= n) {
            ans -= arr[i - m];
            if (min_val > ans) min_val = ans;
        }
    }
    printf("%d", min_val);
    return 0;
}
