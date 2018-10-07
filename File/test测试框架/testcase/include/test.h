/*************************************************************************
	> File Name: test3.h
	> Author: Peranda
	> Mail: 
	> Created Time: 2018年10月07日 星期日 11时58分57秒
 ************************************************************************/

#ifndef _TEST3_H
#define _TEST3_H
#include <stdlib.h>


struct TestFuncData {
    int total, expand;
};

typedef void (*test_func_t)();
typedef struct FuncData {
    const char *a_str, *b_str;
    test_func_t func;
    struct FuncData *next;
} FuncData;


FuncData *addFuncData(
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

#define EXPECT(a, b) ({ \
        int temp; \
        printf("%s == %s %s\n", #a, #b, (temp = (a == b)) ? "True" : "False"); \
        __data->total += 1; \
        __data->expand += temp; \
})

#endif
