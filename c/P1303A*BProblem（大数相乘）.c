/*************************************************************************
	> File Name: P1255数楼梯（递推，斐波那契数列）.c
	> Author: Peranda
	> Mail: 
	> Created Time: 2018年08月19日 星期日 21时48分38秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#define MAX_N 4000000

int arr1[2000] = {0};
int arr2[MAX_N] = {0};
int ans[MAX_N] = {0};
int main() {
    char s1[2000], s2[2000];
    scanf("%s %s", s1, s2);
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    //printf("%d %d\n", len1, len2);
    arr1[0] = len1;
    arr2[0] = len2;
    for (int i = len1; i > 0; i--) {
        arr1[i] = (s1[len1 - i] - '0');
        //printf("s1 : arr1[] = %d s1[] =%d \n", arr1[i], (s1[len1 - i] - '0'));
    }
/*    for (int i = 1; i <= len1; i++) {
        printf("%d ", arr1[i]);
    }
    printf("\n");*/
    for (int i = len2; i > 0; i--) {
        arr2[i] = (s2[len2 - i] - '0');
    }
//    printf ("%d %d\n", arr1[0], arr2[0]);
    for (int i = 1; i <= arr1[0]; i++) {
        for (int j = 1; j <= arr2[0]; j++) {
            //arr2[j + i - 1] += arr1[i] * arr2[j];
            ans[j + i - 1] += arr1[i] * arr2[j];
        } 
       /* for (int j = 1; i <= arr2[0]; j++) {
            if (arr2[j] < 10) continue;
            arr2[j + 1] += arr2[j] / 10;
            arr2[j] %= 10;
            arr2[0] += (j == arr2[0]);
        }**/
    }
    ans[0] = len1 + len2 - 1;
    for (int i = 1; i < len1 + len2; i++) {
        if (ans[i] < 10) continue;
        ans[i + 1] += ans[i] / 10;
        ans[i] %= 10;
        ans[0] += (i == ans[0]);
    }
    while (ans[ans[0]] == 0) {
        ans[0]--;
        if (ans[0] == 1) break;
    }
    //printf("arr2[0] %d \n", arr2[0]);
    for (int i = ans[0]; i >= 1; i--) {
        printf("%d", ans[i]);
    }
    printf("\n");
    return 0;
}

