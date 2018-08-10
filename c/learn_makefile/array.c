/*************************************************************************
	> File Name: array.c
	> Author: 
	> Mail: 
	> Created Time: 2018年08月09日 星期四 19时59分27秒
 ************************************************************************/

#include<stdio.h>
#include "array.h"  
int array_sum(int arr[], int arr_length) {  
    int i;
    int sum = 0;
    for(i = 0; i < arr_length; i++) {
        sum += arr[i];
    }
    return sum;     
}
    double array_avg(int arr[], int arr_length) {return array_sum(arr, arr_length) / (double) arr_length;}          
  
