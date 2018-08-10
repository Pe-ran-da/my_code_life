/*************************************************************************
	> File Name: eu6.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年07月20日 星期五 17时23分23秒
 ************************************************************************/

#include<stdio.h>
#define ll long long 
int main() {
/*    int ans = 0;
    int sum1 = 0, sum2 = 0;

    for (int i = 1; i <= 100; i++) {
        sum1 += i * i;
    }
    sum2 = (101 * 100 / 2);
    sum2 *= sum2;
    printf("%d\n", sum2 - sum1);
*/
    ll sum1 = 5050 * 5050;
    ll sum2 = 100 * 100 * 100 * 100 / 4 + (6 * 100 * 101 * 201) / 24 - ((101 * 100) / 8) + 100 / 4;  
    printf("%lld\n", sum2);
    return 0;
}
