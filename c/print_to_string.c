/*************************************************************************
	> File Name: print_to_string.c
	> Author: 
	> Mail: 
	> Created Time: 2018年08月08日 星期三 21时33分25秒
 ************************************************************************/

#include <stdio.h>
#include <cstring>
int main() {
        char information[100];
        char *name = "Li, Lei";
        char *gender = "male";
        int age = 14;
        float height = 187.5f;
         sprintf(information, "%s is a %s. He is %d-year-old and %fcm tall.\n", name, gender, age, height); // 不输出结果
        printf("%s", information);    // 输出information的结果
        int len_sum = strlen(information);
        printf("%d\n", len_sum);      // 测试长度
    
}

