/*************************************************************************
> File Name: linkedlist.c
> Author: 
> Mail: 
> Created Time: 2018年07月19日 星期四 13时18分57秒
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node *next;

}Node, *LinkedList;

LinkedList insert(LinkedList head, Node *node, int index) {
    if (head == NULL) {
        if (index != 0) {
            return head;

        }
        head = node;
        return head;

    }
    if (index == 0) {
        node->next = head;
        head = node;
        return head;

    }
    Node *current_node = head;
    int count = 0;
    while (current_node->next != NULL && count < index - 1) { /*current_node 下一个只要不为空就继续循环遍历 并且计数  因为最开始是 0 ， 计数从1 开始记录
*/
        current_node = current_node->next;
        count++;
    }
    if (count == index - 1) {
        node->next = current_node->next;
        current_node->next = node;
    }
    return head;
}

void output(LinkedList head) {
    Node *current_node = head;
    while (current_node != NULL) {
        printf("%d ", current_node->data);
        current_node = current_node->next;
    }
    printf("\n");
}

LinkedList delete_node(LinkedList head, int index) {
    if (head == NULL) {
        return head;
    }
    if (index == 0) {
        head = head->next;
        return head;
    }

    Node *current_node = head;
    int count = 0;
    while (current_node->next != NULL && count < index - 1) {
        count++;
        current_node = current_node->next;
    }

    if (count == index - 1 && current_node->next != NULL) {
        Node *delete_node = current_node->next;
        current_node->next = delete_node->next;
        free(delete_node);
    }
    return head;
}

void clear(LinkedList head) {
    Node *current_node = head;
    while (current_node != NULL) {
        Node *delete_node = current_node;
        current_node = current_node->next;
        free(delete_node);
    }
}

int main() {
    LinkedList linkedlist = NULL;
    int sum;
    scanf("%d", &sum);
    for (int i = 0; i < sum; i++) {
        int num, value;
        scanf("%d%d", &num, &value);
        Node *node = (Node*)malloc(sizeof(Node));
        node->data = value;
        node->next = NULL;
        linkedlist = insert(linkedlist, node, num);
    }
    output(linkedlist);
    printf("plase cin the delete number!\n");
    int key;
    scanf("%d", &key);
    linkedlist = delete_node(linkedlist, key);
    output(linkedlist);
    clear(linkedlist);
    return 0;
}

