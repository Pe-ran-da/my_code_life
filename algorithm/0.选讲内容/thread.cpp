/*************************************************************************
	> File Name: thread.cpp
	> Author: peranda
	> Mail:1365227825@qq.com  
	> Created Time: 2018年11月04日 星期日 11时22分51秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define NORMAL 0
#define THREAD 1

typedef struct Node {
    int key, ltag, rtag;
    struct Node *lchild, *rchild;
} Node;

Node *init(int key) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = key;
    p->lchild = p->rchild = NULL;
    p->ltag = p->rtag = NORMAL;
    return p;
}


Node *insert(Node *root, int key) {
    if (root == NULL) return init(key);
    if (root->key == key) return root;
    if (key < root->key) root->lchild = insert(root->lchild, key);
    else root->rchild = insert(root->rchild, key);
    return root;
}

void build(Node *root){
    if (root == NULL) return ;
    static Node *pre = NULL;//qian yige 
    build(root->lchild);
    if (root->lchild == NULL) { // 前一个节点的线索
        root->lchild = pre;
        root->ltag = THREAD;
    }
    if (pre != NULL && pre->rchild == NULL) {// 前一个节点的后继jieidan 
        pre->rchild = root;
        pre->rtag = THREAD;
    }
    pre = root;
    build(root->rchild);
    return ;
}

void output(Node *root) {
    int status = 1;
    Node *p = root;
    while (p) {
        switch (status) {
        // 状态机思想
            case 1: { 
                while (p->ltag == NORMAL && p->lchild) p = p->lchild;
                status = 2;
            } break;
            case 2: {
                printf("%d ", p->key);
                status = 3;
            } break;
            case 3: {
                if (p->rtag == NORMAL) {
                    //p = p->rchild;
                    status = 1;
                } else {
                    //p = p->rchild;
                    status = 2;
                }
                p = p->rchild;
            } break;
        }
    }
    return ;
}


int clear(Node *root) {
    if (root == NULL) return 0;
    root->ltag == NORMAL && clear(root->lchild);
    root->rtag == NORMAL && clear(root->rchild);
    free(root);
    return 0;
}

int output_th(Node *root) {
    if(root == NULL) return 0;
    printf("key : %d", root->key);
    if (root->lchild) {
        printf("(ltag : %d, lchild : %d)", root->ltag, root->lchild->key);
    } 
    if (root->rchild) {
        printf("(rtag : %d, rchild : %d)", root->rtag, root->rchild->key);
        
    }
    printf("\n");
    root->ltag == NORMAL && output_th(root->lchild);
    root->rtag == NORMAL && output_th(root->rchild);
    return 0;
}


int main() {
    int n;
    Node *root = NULL;
    while (scanf("%d", &n) != EOF) {
        root = insert(root, n);
    }
    build(root);
    output_th(root);
    output(root);
    clear(root);
    return 0;
}
