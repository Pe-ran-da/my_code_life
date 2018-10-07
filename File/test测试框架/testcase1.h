/*************************************************************************
> File Name: testcase1.h
> Author: Peranda
> Mail: 
> Created Time: 2018年10月07日 星期日 16时19分32秒
************************************************************************/

#ifndef _TESTCASE1_H
#define _TESTCASE1_H

#include "test.h"
#include "is_prime.h"

TEST(test, is_prime_func) {
    EXPECT_EQ(is_prime(5), 1);
    EXPECT_EQ(is_prime(-2), 0);
    EXPECT_EQ(is_prime(15), 0);
    EXPECT_EQ(is_prime(9973), 1);
}

#endif
