/*************************************************************************
	> File Name: test.h
	> Author: Tanxiaoze
	> Mail: 2406577693@qq.com
	> Created Time: 2018年10月07日 星期日 09时28分13秒
 ************************************************************************/

#ifndef _TEST_H
#define _TEST_H
#include <stdlib.h>

#define PASS "\033[32mPASS\033[0m"
#define FAIL "\033[31mFAIL\033[0m"

struct TestFuncData {
    int total, expand;
};

typedef void (*test_func_t)();
typedef struct FuncData {
    const char *a_str, *b_str;
    test_func_t func;
    struct FuncData *next;
} FuncData;


void addFuncData(
    const char *a,
    const char *b,
    test_func_t func
);

#define TEST(a, b) \
    void a##_haizeix_##b(); \
    __attribute__((constructor)) \
    void ADDFUNC_##a##_haizeix_##b() { \
        addFuncData(#a, #b, a##_haizeix_##b); \
    } \
    void a##_haizeix_##b(struct TestFuncData *__data)

#define EXPECT_EQ(a, b) ({ \
        int temp; \
        printf("%s == %s %s\n", #a, #b, (temp = (a == b)) ? "True" : "False"); \
        __data->total += 1; \
        __data->expand += temp; \
})

#define EXPECT_NE(a, b) ({ \
        int temp; \
        printf("%s != %s %s\n", #a, #b, (temp = (a != b)) ? "True" : "False"); \
        __data->total += 1; \
        __data->expand += temp; \
})

#define EXPECT_GT(a, b) ({ \
        int temp; \
        printf("%s > %s %s\n", #a, #b, (temp = (a > b)) ? "True" : "False"); \
        __data->total += 1; \
        __data->expand += temp; \
})

#define EXPECT_LT(a, b) ({ \
        int temp; \
        printf("%s < %s %s\n", #a, #b, (temp = (a < b)) ? "True" : "False"); \
        __data->total += 1; \
        __data->expand += temp; \
})

#define EXPECT_GE(a, b) ({ \
        int temp; \
        printf("%s >= %s %s\n", #a, #b, (temp = (a >= b)) ? "True" : "False"); \
        __data->total += 1; \
        __data->expand += temp; \
})

#define EXPECT_LE(a, b) ({ \
        int temp; \
        printf("%s <= %s %s\n", #a, #b, (temp = (a <= b)) ? "True" : "False"); \
        __data->total += 1; \
        __data->expand += temp; \
})

#define EXPECT_SUB(a, b) ({ \
        double exp = 1e-6; \
        int temp; \
        printf("%s <= %s %s\n", #a, #b, (temp = ((a - b) <= exp) ) ? "True" : "False"); \
        __data->total += 1; \
        __data->expand += temp; \
})


int RUN_ALL_TEST();

#endif
