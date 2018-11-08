/*************************************************************************
	> File Name: test1.cpp
	> Author: Peranda
	> Mail: 1365227825@qq.com 
	> Created Time: 2018年11月01日 星期四 19时49分05秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int pi, di;
} Node;

typedef struct Heap {
    Node *data;
    int size, length_input;
} Heap;

void init(Heap *h, int length_input) {
    h->data = (Node *)malloc(sizeof(Node *) * length_input);
    h->size = 0;
    h->length_input = length_input;
    return ;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void push(Heap *h, int value, int d) {
    h->data[h->size].di = d;
    h->data[h->size].pi = value;
    int current = h->size;
    int father = (current - 1) / 2;
    while (h->data[current].pi > h->data[father].pi) {
        swap(&h->data[current].pi, &h->data[father].pi);
        current = father;
        father = (current - 1) / 2;
    }
    h->size++;
}

void output(Heap *h) {
    for (int i = 0; i < h->size; i++) {
        printf("%d ",  h->data[i].pi);
    }
    printf("\n");
}

int top(Heap *h) {
    return h->data[0].pi;
}

void update(Heap *h, int pos, int n) {
    int lchild = 2 * pos + 1, rchild = 2 * pos + 2;
    int max_value = pos;
    if (lchild < n && h->data[lchild].pi  > h->data[max_value].pi) {
        max_value = lchild;
    }
    if (rchild < n && h->data[rchild].pi > h->data[max_value].pi) {
        max_value = rchild;
    }
    if (max_value != pos) {
        swap(&h->data[pos].pi, &h->data[max_value].pi);
        update(h, max_value, n);
    }
}

void pop(Heap *h) {
    swap(&h->data[0].pi, &h->data[h->size - 1].pi);
    h->size--;
    update(h, 0, h->size);
}


void heap_sort(Heap *h) {
    for (int i = h->size - 1; i >= 1; i--) {
        swap(&h->data[i].pi, &h->data[0].pi);
        update(h, 0, i);
    }
}

void clear(Heap *h) {
    free(h->data);
    free(h);
}

void output(Heap *h) {
    for (int i = 0; i < h->size; i++) {
        printf(" %d %d", h->data[i].pi, h->data[i].di);
        i == h->size - 1 || printf(",");
    }
    printf("\n");
}

int main() {
    Heap *heap = (Heap *)malloc(sizeof(Heap));
    init(heap, 200010);
    int n, m;
    int pi, di;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &m);
        for (int j = 0; j < m; j++) {
            scanf("%d %d", &pi, &di);
            push(heap, pi, di);
        }
        output(heap);
    }
    
    return 0;
}
