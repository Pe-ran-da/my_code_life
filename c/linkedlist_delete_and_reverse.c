/*************************************************************************
> File Name: linkedlist_delete_and_reverse.c
> Author: 
> Mail: 
> Created Time: 2018年07月19日 星期四 16时47分42秒
************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node *next;

}Node, *LinkedList;

LinkedList insert(LinkedList head, Node *node, int index) {
    if (head == NULL) {
        if (index != 0) {
            printf("failed\n");
            return head;

        }
        head = node;
        printf("success\n");
        return head;

    }
    if (index == 0) {
        node->next = head;
        head = node;
        printf("success\n");
        return head;

    }
    Node *current_node = head;
    int count = 0;
    while (current_node->next != NULL && count < index - 1) {
        current_node = current_node->next;
        count++;

    }
    if (count == index - 1) {
        node->next = current_node->next;
        current_node->next = node;
        printf("success\n");
        return head;

    }
    printf("failed\n");
    return head;

}

void output(LinkedList head) {
    if (head == NULL) {
        return;

    }
    Node *current_node = head;
    while (current_node != NULL) {
        printf("%d ", current_node->data);
        current_node = current_node->next;

    }
    printf("\n");

}

LinkedList delete_node(LinkedList head, int index) {
    if (head == NULL) {
        printf("failed\n");
        return head;

    }
    if (index == 0) {
        head = head->next;
        printf("success\n");
        return head;

    }
    Node *current_node = head;
    int count = 0;
    while (current_node->next != NULL && index - 1 > count) {
        current_node = current_node->next;
        count++;
    }
    if(index - 1 == count && current_node->next != NULL) {
        Node *delete_node = current_node->next;
        current_node->next = delete_node->next;
        free(delete_node);
        printf("success\n");
        return head;
    }
    printf("failed\n");
    return head;

}

LinkedList reverse(LinkedList head) {
    if (head == NULL) {
        return head;

    }
    Node *next_node, *current_node;
    current_node = head->next;
    head->next = NULL;
    while (current_node != NULL) {
        next_node = current_node->next;
        current_node->next = head;
        head = current_node;
        current_node = next_node;

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
    int num;
    scanf("%d", &num);
    for (int i = 0; i < num; i++) {
        int value;
        scanf("%d", &value);
        if (value == 1) {
            int sum, key;
            scanf("%d%d", &sum, &key);
            Node *node = (Node *)malloc(sizeof(Node));
            node->data = key;
            node->next = NULL;
            linkedlist = insert(linkedlist, node, sum);

        } else if (value == 2) {
            output(linkedlist);

        } else if (value == 3) {
            int sum;
            scanf("%d", &sum);
            linkedlist = delete_node(linkedlist, sum);

        } else if (value == 4) {
            linkedlist = reverse(linkedlist);
         //   output(linkedlist);

        }

    }
    clear(linkedlist);
    return 0;

}
