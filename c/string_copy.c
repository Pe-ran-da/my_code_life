/*************************************************************************
	> File Name: string_copy.c
	> Author: 
	> Mail: 
	> Created Time: 2018年08月08日 星期三 21时39分27秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>

int main() {
    char string[100];
    char copy[100] = "";
    
    scanf("%s", string);
    strcpy(copy, string); // copy的初步学习
    //strcpy只是复制字符串　不限制复制数量　容易造成缓冲溢出
    
    printf("%s\n", copy);

    char ans[10] = "";
    strncpy(ans, string, strlen(string));
    //strncpy 在复制时可能出现乱码，　原因如下:
    //如果copy长度超出ans数组的长度，　首先肯定是破坏ans长度以后空间的内存
    //来存储string的内容，并且它超出长度后并不会负责添加"\0"到ans的结尾
    //所以有可能输出乱码，　是因为它在ans输出完成后，多输出了不是ans内的内
    //容，　并且再向后找到"\0"才会停止输出
    //输出该字符串ans，会在输出字符后面一直找到"\0"才结束，因此会出现乱码。
    
    //当然，如果stelen(string) < ans的声明长度，那么strncpy它copy来的内容
    //里面，　没有被填充的ans的区域内　都会被填充成NULL 也就是"\0"，自然
    //不会出现任何问题
    printf("%s\n", ans);
    return 0;
}
