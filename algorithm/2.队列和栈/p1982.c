/*************************************************************************
	> File Name: 4.c
	> Author: Peranda
	> Mail: 1365227825@qq.com 
	> Created Time: 2018年10月23日 星期二 02时30分20秒
 ************************************************************************/

#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <math.h>
#define INF 0x3f3f3f3f
#define MOD_SUM 100000007

typedef long long ll;

ll pow_sum(ll a, ll b) {
    ll sum = 1;
    for (int i = 0; i < b; i++) {
        sum = sum % MOD_SUM * a % MOD_SUM;
        sum %= MOD_SUM;
    }
}


ll calc(const char *str, int l, int r, int a_value) {
    int pos = -1, temp_prior = 0, prior = INF - 1;
    for (int i = l; i <= r; i++) {
        int cur_prior = INF;
        switch(str[i]){
            case '(': temp_prior += 100; break;
                   case ')': temp_prior -= 100; break;
            case '+': cur_prior = temp_prior + 1; break;
            case '-': cur_prior = temp_prior + 1; break;
            case '*': cur_prior = temp_prior + 2; break;
            case '/': cur_prior = temp_prior + 2; break;
            case '^': cur_prior = temp_prior + 3; break;
        }
        if (cur_prior <= prior) {
            prior = cur_prior;
            pos = i;
        }
    }
    if (pos == -1) {
        // 单独的是数的时候
        ll num = 0;
        for (int i = l; i <= r; i++) {
            if (str[i] == 'a') return a_value;
            if (str[i] < '0' || str[i] > '9') continue;
            num = num *10 + str[i] -'0';
            num %= MOD_SUM;
        }
        return num;
    } else {
        ll a = calc(str, l, pos - 1, a_value);
        ll b = calc(str, pos + 1, r, a_value);
        switch (str[pos]) {
            case '+': return (a + b) % MOD_SUM;
            case '-': return (a - b) % MOD_SUM;
            case '*': return (a * b) % MOD_SUM;
            case '/': return (a / b) % MOD_SUM;
            case '^': return pow_sum(a, b);

        }
    }
    return 0;
}



int brackets(const char* str) {
    int len = strlen(str);
    int sum = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] == '(') sum++;
        if (str[i] == ')') sum--;
        if (sum < 0) return 0;
    }
    if (sum == 0) return 1;
    else return 0;
}


int main() {
    char str[60];
    char ans[60];
    scanf("%[^\r]", str);
    getchar();
    //if (brackets(str) == 1) printf("%d\n" , calc(str, 0, strlen(str), 1));
    int n;
    scanf("%d", &n);getchar();
    for (int i = 0; i < n; i++) {
        int kk = 0;
        scanf("%[^\r]", ans);
        //printf("%s\n", ans);
        getchar();
        if (brackets(ans) == 0) continue;
        //printf("%s\n", ans);
        for (int j = -8; j < 8; j++) {
            if(calc(ans, 0, strlen(ans), j) != calc(str, 0, strlen(str), j)) {
                kk = 1;
            } 
            if (!kk) {
                //printf("%d", i);
                printf("%c", (char)(i + 65));
                break;
            }
        }
        memset(ans, 0, sizeof(ans));
        //continue;
    }
    return 0;
}


