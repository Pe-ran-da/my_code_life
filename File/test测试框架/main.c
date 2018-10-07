/*************************************************************************
	> File Name: main.c
	> Author: Peranda
	> Mail: 
	> Created Time: 2018年10月07日 星期日 11时30分03秒
 ************************************************************************/

#include <stdio.h>
#include "is_prime.h"
#include "add.h"
#include "nuton.h"
#include "test.h"

#ifdef FUNC_TEST

#include "testcase1.h"
#include "testcase2.h"
#include "testcase3.h"

#endif


int main() {
    //is_prime(10);
    //add(3, 4);
    printf("hello world\n");
    return RUN_ALL_TEST();
}
