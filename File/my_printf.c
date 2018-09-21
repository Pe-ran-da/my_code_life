/*************************************************************************
> File Name: my_printf.c
> Author: Peranda
> Mail: 
> Created Time: 2018年09月20日 星期四 20时45分32秒
************************************************************************/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <inttypes.h>
#include <string.h>

int my_printf(const char *frm, ...) {
    int cnt = 0;
    va_list arg;
    va_start(arg, frm);
    for (int i = 0; frm[i]; i++) {
        switch (frm[i]) {
            case '%' : {
                i++;
                switch(frm[i]) {
                    case 'd' : {
                        int temp = va_arg(arg, int); // 先计取出传入的参数
                        if (temp > 0) {// 传入参数大于0
                            int sum = (int)log10(temp) + 1 ;//计算长度
                            int key = sum;
                            int arr[sum];
                            while(key) {
                                key--;
                                arr[key] =  temp % 10; //按位存入数组
                                temp /= 10;
                            }
                            cnt = 0;
                            int j = 0;
                            while(sum--) {
                                cnt = cnt * 10 + arr[j];//反正cnt就这么存着吧
                                char aa = arr[j] + '0';//按位转化为字符
                                putchar(aa);//输出
                                j++;
                            }
                        }  else if (temp < 0) {//传入参数小于0
                            int sum = 0;
                            int aa = temp;
                            while(aa){         // 计算负数长度当然不能用log10
                                aa /= 10;
                                sum++;
                            }
                            int arr[sum];      // 存数
                            int key = sum;
                            while(temp) {      // 放入数组
                                key--;
                                arr[key] = temp % 10; // 存入的数个个都是负数
                                temp /= 10;
                            }
                            cnt = 0;
                            int j = 0;
                            char ch = '-';
                            putchar(ch);//先输出负号
                            while (sum--) {
                                cnt = cnt * 10 + arr[j];
                                char bb = (-1 * arr[j]) + '0';//把负数转化成整数
                                putchar(bb);
                                j++;
                            }
                        } else {//传入参数为0
                            char ch = '0';
                            putchar(ch);
                        }
                    } break;
                    default : 
                        fprintf(stderr, "error : unknow %%%c\n", frm[i]); 
                        exit(1);
                    }
                } break;
            default:
                putchar(frm[i]);
            }
        }
    return cnt;
}

int main() {
    int n = 123;
    my_printf("hello world\n");
    my_printf("n = %d\n", n);
    my_printf("n = %d\n", 12000);
    my_printf("n = %d\n", -567);
    my_printf("n = %d\n", INT32_MIN);
    my_printf("n = %d\n", INT32_MAX);
    return 0;
}
