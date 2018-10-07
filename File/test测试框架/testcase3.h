/*************************************************************************
	> File Name: testcase3.h
	> Author: Peranda
	> Mail: 
	> Created Time: 2018年10月07日 星期日 22时11分01秒
 ************************************************************************/

#ifndef _TESTCASE3_H
#define _TESTCASE3_H

#include "test.h"
#include "nuton.h"
//#define MIN_SIZE 1e-6
TEST(test, nuton_func) {
    EXPECT_SUB(nuton(9), 3);
    EXPECT_SUB(nuton(16), 2);
}

#endif
