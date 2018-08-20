/*************************************************************************
	> File Name: P1255数楼梯（大数相加，递推）.c
	> Author: Peranda
	> Mail: 
	> Created Time: 2018年08月20日 星期一 11时08分04秒
 ************************************************************************/

#include <stdio.h>

int ans[3][1100] ={0};

int main() {
    ans[0][0] = ans[1][0] = ans[2][0] = 1;
    int sum;
    scanf("%d", &sum);
    if (sum == 1 || sum == 2) {
        printf("1\n");
        return 0;
    } else if (sum == 0) {
        printf("0\n");
        return 0;
    }
    int key = 0;
    ans[0][1] = 3; ans[1][1] = 5; //从３开始计算
    while (key < sum - 2) {
        for (int i = 1; i <= ans[(key + 2) % 3][0]; i++) {
            ans[(key + 2) % 3][i] = ans[(key + 1) % 3][i] + ans[(key) % 3][i];
        }
        for (int i = 1; i <= ans[(key + 2) % 3][0]; i++) {//进位计算
            if (ans[(key + 2) % 3][i] < 10) continue;
            ans[(key + 2) % 3][i + 1] += ans[(key + 2) % 3][i] / 10;
            ans[(key + 2) % 3][i] %= 10;
            ans[(key + 2) % 3][0] += (i == ans[(key + 2) % 3][0]);
        }
//        printf("%d\n", ans[(key + 2) % 3][0]);
        ans[(key + 3) % 3][0] = ans[(key + 2) % 3][0];
        key += 1;
    }
//    printf("%d\n",ans[(key - 1) % 3][0]);
    while (ans[(key - 1) % 3][ans[(key - 1) % 3][0]] == 0) {//去除签到零
        ans[(key - 1) % 3][0] -= 1;
    }
    for (int i = ans[(key - 1) % 3][0]; i > 0; i--) {
        printf("%d", ans[(key - 1) % 3][i]);
    }
    return 0;
}
