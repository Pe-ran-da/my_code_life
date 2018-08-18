/*************************************************************************
	> File Name: P4702取石子（博弈论）.c
	> Author: peranda
	> Mail: 1365227825@qq.com
	> Created Time: 2018年08月11日 星期六 20时33分14秒
 ************************************************************************/

#include<stdio.h>
#define MAX_S 100

int ans[MAX_S + 5] = {0};

int main() {
    int n;
    int sum = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &ans[i]);
        sum += ans[i];
    }
    if (sum & 1) { // 本题为就判断题 因为题目中规定每次取１粒　那么
                    //先取出最后一粒的人胜利　也就是说　石子儿的单数
                  //存在时　先手胜　反之则相反
        printf("Alice\n");
    } else {
        printf("Bob\n");
    }
    return 0;
}
