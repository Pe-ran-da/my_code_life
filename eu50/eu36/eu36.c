/*************************************************************************
	> File Name: eu36.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月22日 星期日 14时10分37秒
 ************************************************************************/

#include<stdio.h>
#define ll long long 

ll BASE(ll x, ll base) {
    ll key = x;
    ll ans = 0;
    while (x) {
        ans = ans * base + x % base;
        x /= base;
    }
    return ans == key;
}


int main(){
    ll ans = 0;
    for (ll i = 1; i < 1000000; i++) {
        if (!BASE(i, 10)) continue;
        if (!BASE(i, 2)) continue;
        ans += i;
    } 
    printf("%lld\n", ans);
    return 0;
}
