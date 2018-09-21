/*************************************************************************
	> File Name: scanf_quick.cpp
	> Author: Peranda
	> Mail: 
	> Created Time: 2018年09月18日 星期二 20时35分52秒
 ************************************************************************/

#include <stdio.h>

using namespace std;

char ss[1 << 17], *A = ss, *B = ss;

inline char gc() {
    return A == B && (B = (A = ss) + fread(ss, 1, 1 << 17, stdin), A == B) ? -1 : *A++;
}

template<typename T> inline void sdf(T &x) {
    char c;
    T y = 1;
    while (c = gc(), (c < 48 || c > 57) && c != -1) {
        if (c == '-') y = -1;
    }
    x = c ^ 48;
    while (c = gc(), (c <= 57 && c >= 48)) {
        x = (x << 1) + (x << 3) + (c ^ 48);
    }
    x *= y;
} 

int main() {
    int n, a;
    sdf(n);
    for (int i = 0; i < n; i++) {
        sdf(a);
        printf("%d\n", a);
    }
    return 0;
}
/*需要文件输入数据 以二进制程序运行*/
