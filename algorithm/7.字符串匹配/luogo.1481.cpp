/*************************************************************************
	> File Name: 16.trie.cpp
	> Author: peranda
	> Mail:1365227825@qq.com  
	> Created Time: 2018年12月30日 星期日 20时38分39秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BASE_CNT 26
#define BASE 'a' 

typedef struct Node {
    int flag;
    struct Node *next[26];
} Node ;

Node *getNewNode (){
    Node *p = (Node *)malloc(sizeof(Node));
    for (int i = 0; i < BASE_CNT; i++) {
        p->next[i] = NULL;
    }
    p->flag = 0;
    return p;
}

int insert(Node *node, const char *str) {
    Node *p = node;
    int cnt = 1;
    for (int i = 0; str[i]; i++) {
        if (p->next[str[i] - BASE] == NULL) p->next[str[i] - BASE] = getNewNode();
        p = p->next[str[i] - BASE];
        cnt += p->flag;
    }
    p->flag = 1;
    return cnt;
}


int main () {
    Node *root = getNewNode();
    char str[100];
    int a;
    int key = 0; 
    scanf("%d", &a);
    while (a--) {
        scanf("%s", str);
        int temp = insert(root, str);
        if (temp > key) key = temp;
    }
    printf("%d\n", key);
    return 0;
}
