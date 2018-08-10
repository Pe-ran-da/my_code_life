/*************************************************************************
> File Name: eu9.c
> Author: 
> Mail: 
> Created Time: 2018年07月29日 星期日 19时02分02秒
************************************************************************/

#include<stdio.h>
#include <stdio.h>

#include <stdlib.h>

#include <math.h>



 int main() {

     bool flag = true;

     int32_t a, b, c, e;

     for (int32_t i = 1; i < 32 && flag; ++i) {

         for (int32_t j = i + 1; j <= 32 && flag; ++j) {

             a = j * j - i * i;

             b = 2 * i * j;

             
             c = i * i + j * j;

             if (1000 % (a + b + c) == 0) {
                printf("a %d b %d c %d\n", a, b, c);
                 e = (int32_t)pow(1000 / (a + b + c), 3);

                 
                 printf("%d\n", e * a * b * c);

                 flag = false;


             }


         }


     }

     return 0;


 }
