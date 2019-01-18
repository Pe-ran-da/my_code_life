/*************************************************************************
	> File Name: 15.Shift-And.cpp
	> Author: peranda
	> Mail:1365227825@qq.com  
	> Created Time: 2019年01月01日 星期二 10时25分01秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OB_SHIFT 15
#define OB_BASH  (1 << OB_SHIFT)
#define OB_MASK  (OB_BASH - 1)

#define TEST(func, a, b) { \
    printf("%s (\"%s\", \"%s\") = %d\n", #func, a, b, func(a, b)); \
}

struct object {
    int len;
    int ob_digit[2000];
};

//初始化
object *init() { // 初始化
   	object *v = (object *)malloc(sizeof(object)); 
    v->len = 0;
    return v;
}

object *init_val(object *v,int n) { // 初始化
   	//object *v = (object *)malloc(sizeof(object));
    //v->len = 0;
    memset(v->ob_digit, 0, sizeof(int) * 20);
    while (n > 0) {
        v->ob_digit[v->len] =  n & OB_MASK;
        n = n >> OB_SHIFT;
        v->len += 1;
        printf("init_val\n\n");
    }
    return v;
}


//优化长度
object *long_normalize(object *v) {
	int i = v->len - 1;
	//int j = i;
	while (i >= 0 && v->ob_digit[i] == 0)
		--i;
	/*if (i != j) // 出现负的长度的时候用
		v->len = (v->len < 0) ? -(i) : i;*/
	return v;
}

object *and_two (object *v, object *u) { // &
    int len;
    v = long_normalize(v);
    u = long_normalize(u);
    
    printf("and_two : v %d , u %d\n", v->len, u->len);
    v->len > u->len ? (len = u->len) : (len = v->len);
    
   // object *cnt = init();
   //cnt->len = len;
    
    len -= 1; // len - 1, 0
    while (len >= 0) {
        v->ob_digit[len] = v->ob_digit[len] & u->ob_digit[len];
        len --;
    }
    return long_normalize(v);
}


object *a_in(object *v, int cnt) { // << 
    int size_v = v->len;
    int carry = 0;
    int i = 0;
    for (; i < size_v; i++) {
        carry += v->ob_digit[i] << cnt;
        v->ob_digit[i] = carry & OB_MASK; //掩码得到低15位
        carry >>= OB_SHIFT; // 截取低15位以上
    }
    v->ob_digit[i] = carry;

    return long_normalize(v);
}

object *or_one(object *v, int key) { // |
    int size_v = v->len;
    if (v->len >= 0) { 
        v->ob_digit[0] |= key;
        printf("or_one success! %d \n", v->ob_digit[0]);
    }
    return v;
}

int a_to_b(object *v, object *u, int *key) {
    int len;
    v->len > u->len ? (len = u->len) : (len = v->len);

    int ans = 0;
    len -= 1;
    while (len >= 0) {
        if (v->ob_digit[len] & u->ob_digit[len]) {
            key[0] *= OB_BASH; 
            key[1] *= OB_BASH; 
            printf("v  %d   u  %d\n", v->ob_digit[len], u->ob_digit[len]);
            key[0] += v->ob_digit[len]; 
            key[1] += u->ob_digit[len]; 
            ans += 1;
        }
        len -= 1;
    }
    //printf("ans ------ %d -- \n", ans);
    return *key;
}

void output(object *p) {
    int len = p->len - 1;
    while (len >= 0) {
        printf("-------out  %d   -------\n", p->ob_digit[len]);
        len -= 1;
    }
}

int Shift_And(char *str, char *pattern) {
    #define BASE 128
    int code[BASE] = {0}, len = 0;
    printf("0\n");
    for (len = 0; pattern[len]; len++) {
        code[pattern[len]] |= (1 << len);
    }
    for (int i  = 0; i < 128; i++) {
        printf("%d ", code[i]);
    }
    printf("read!\n");
    //int p = 0;
    object *p = init();
    p = init_val(p, 0);
    printf("p init success!\n");

    object *_code = init();
    object *_len = init();
    _len = init_val(_len, 1 << (len - 1)); 
    object *_cnt = init();
    //cnt->len = len;
    //int key[2] = {0, 0};
    for (int i = 0; str[i]; i++) {
        printf("i ----:---- %d\n", i);
        int key[2] = {0, 0};
        //printf("code[str[%d]] = %d\n", i, code[str[i]]);
        _code = init_val(_code, code[str[i]]);
        //printf("_code init_val value:\n");
        //output(_code);
        //printf("code init_val success!\n");
        
        
        
        
        _cnt = init_val(_cnt, 0);
        p = a_in(p, 1); // ob << 1
       // output(p);
        p = or_one(p, 1); // ob | 1 
       // output(p);
        p = and_two(p, _code); // ob & ob
        printf("基础操作！\n");
        output(p);
        //printf("_code\n");
        //output(_code);
        //p = and_two(or_one( add_two(p, 1), 1), _code);
        
        //printf("2,5\n");
        
        //_len = init_val(_len, 1 << (len - 1)); 
        output(p);
        printf("1 << (len(%d) - 1) = %d\n", len, 1 << (len - 1));

        //printf("3\n");

        a_to_b(p, _len, key);
        printf("key %d,  %d\n", key[0], key[1]);
        printf("i  %d  len  %d, i - len + 1  = %d \n", i, len, i - len + 1);
        if (key[0] & key[1]) { // ob & ob
            printf("zhaodale!\n");
            free(_code);
            free(_len);
            free(p);
            free(_cnt);
            return i - len + 1;
        }
        //p = (p << 1 | 1) & code[str[i]];
        //if (p & (1 << (len - 1))) return i - len + 1;
        
    }
    free(_cnt);
    free(_code);
    free(_len);
    free(p);
    return -1;
    #undef BASE
}


int main() {
  /*  
    printf("%d \n", OB_SHIFT);
    printf("%d \n", OB_BASH);
    printf("%d \n", OB_MASK);

    object *p = init();
    p = init_val(p, 1);
    output(p);
    

    object *q = init();
    q = init_val(q, 87654321);
    output(q);
  
    q = long_normalize(q);
    output(q);


    object *a = init();

    a = and_two(p, q);
    output(a);

    a = a_in(a, 1);
    output(a);

    a = or_one(a, 1);
    output(a);
    

    int key = a_to_b(p, q);
    printf("key %d \n", key);
    free(a);
    free(p);
    free(q);
*/    
    char str[100], pattern[30];
    while (scanf("%s%s", str, pattern) != EOF) {
        TEST(Shift_And, str, pattern);
    }
    return 0;
}
