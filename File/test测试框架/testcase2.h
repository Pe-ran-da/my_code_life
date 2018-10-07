/*************************************************************************
> File Name: testcase2.h
> Author: Peranda
> Mail: 
> Created Time: 2018年10月07日 星期日 16时27分09秒
************************************************************************/

#ifndef _TESTCASE2_H
#define _TESTCASE2_H
#include "test.h"
#include "add.h"

TEST(test, add_func) {
    EXPECT_EQ(add(1, 2), 3);
    EXPECT_EQ(add(3, 4), 7);
    EXPECT_EQ(add(2, 2), 4);
}

#endif
