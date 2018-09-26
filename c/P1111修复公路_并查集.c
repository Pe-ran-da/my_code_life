/*************************************************************************
	> File Name: P1111修复公路_并查集.c
	> Author: Peranda
	> Mail: 
	> Created Time: 2018年09月26日 星期三 16时02分03秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
        //algorithm
#define MAX_SIZE 100010


/*int arr[MAX_SIZE];
int father[MAX_SIZE];
int size[MAX_SIZE];
**/
int arr[MAX_SIZE];//并查集的树
int father[MAX_SIZE];//并查集的父亲查询
int size[MAX_SIZE];//存点数

struct Node {
    int child;  //存儿子值
    int father; //存父亲节点的值
    int time;   //时间用于排序
    //int size;   //存点数
}ans[MAX_SIZE];

int cmp(Node q, Node w) {
    return q.time < w.time;
}

void init(int x) {
    for (int i = 1; i <= x; i++) {
        father[i] = i;
        size[i] = 1;
    }
}

int get_sum(int x) {
    if (father[x] == x) return x;
    return father[x] = get_sum(father[x]);
}

void merge(int x, int y) {
    x = get_sum(x);
    y = get_sum(y);
    //printf("cccc\n");
    if (father[x] != father[y]) {//看他们是不是同一个
        father[x] = y;
        size[y] += size[x];
        //printf("aaaaaaaaaaaaaa  %d\n", size[y]);
    }
}

int find(int x, int y, int value) {
    x = get_sum(x);
    y = get_sum(y);
    if (father[x] == father[y]) {
        //printf("aaaaaa\n");
        if (size[y] == value || size[x] == value) {//村子够了
            //printf("BBBBBBB\n");
            return 1;
        }
    }
    return 0;
}

int main() {
    int x, y;
    
    scanf("%d %d", &x, &y);
    init(x);

    for (int i = 1; i <= y; i++) {
        scanf("%d %d %d", &ans[i].father, &ans[i].child, &ans[i].time);
    }
    std::sort(ans + 1, ans + y + 1, cmp);
    int key = 0;
    for (int i = 1; i <= y; i++) {
        merge(ans[i].father, ans[i].child);
        if (find(ans[i].father, ans[i].child, x) == 1) {
            printf("%d\n", ans[i].time);
            key = 1;
            break;
        }
        //printf("%d\n", ans[i].time);
    }
    if (key == 0) {
        printf("-1\n");
    }
    return 0;
}
