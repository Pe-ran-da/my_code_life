/*************************************************************************
> File Name: nuton.c
> Author: Peranda
> Mail: 
> Created Time: 2018年10月07日 星期日 20时35分31秒
************************************************************************/

#include <stdio.h>
#include <math.h>
#define EPS 1e-7

double nuton(double a) {
    double x = 1.0;
    while (fabs((x * x - a)) > EPS){
        x -= (x * x - a) / (x * x);
    }
    return x;
}

