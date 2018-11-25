/*************************************************************************
	> File Name: 0.master.cpp
	> Author: peranda
	> Mail:1365227825@qq.com  
	> Created Time: 2018年11月18日 星期日 11时28分15秒
 ************************************************************************/
#include <arpa/inet.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/file.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdarg.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define max_size 10
#define BACKLOG 10
//#include "common.h"
#define INS 5

typedef struct Node {
    int client_fd;
    struct sockaddr_in client_addr;
    struct Node *next;
} Node;

typedef struct LinkedList {
    Node head;
    int length;
} LinkedList;

LinkedList linkedlist[INS + 1] = {0};
void *func(void *);

/////////////////////////////////////////
////hash 
typedef struct NodeHash {
    char *str;
    struct NodeHash *next;
} NodeHash;

typedef struct HashTable {
    NodeHash **data;
    int size;
} HashTable;

NodeHash *init_node(char *str, NodeHash *head) {
    NodeHash *p = (NodeHash *)malloc(sizeof(NodeHash));
    p->str = strdup(str);
    p->next = head;
    return p;
}

HashTable *init_hashtable(int n) {
    HashTable *h = (HashTable *)malloc(sizeof(HashTable));
    h->size = n * 2;
    h->data = (NodeHash **)calloc(sizeof(NodeHash *),  h->size);
    return h;
}

void hash_clear_node(NodeHash *node) {
    if (node == NULL) return ;
    NodeHash *p = node, *q;
    while (p) {
        q = p->next;
        free(p->str);
        free(p);
        p = q;
    }
    return ;
}

int BKDRHash(char *str) {
    int seed = 31, hash = 0;
    for (int i = 0; str[i]; i++) {
        hash = hash * seed + str[i];
    }
    return hash & 0x7fffffff;
}


int hash_insert (HashTable *h, char *str) {
    printf("insert\n");
    int hash = BKDRHash(str);
    int ind = hash % h->size;
    h->data[ind] = init_node(str, h->data[ind]);
    //拉链法
    return 1;
}

int hash_search(HashTable *h, char *str) {
    printf("search\n");
    int hash = BKDRHash(str);
    int ind = hash % h->size;
    NodeHash *p = h->data[ind];
    while (p && strcmp(p->str, str)) p = p->next;
    return p != NULL;
}


void clear_hashtable(HashTable *h) {
    if (h == NULL) return ;
    for (int i = 0; i < h->size; i++) hash_clear_node(h->data[i]);
    free(h);
    return ;
}
/////////////////////////////////////////////////

LinkedList *init_linkedlist() {
    LinkedList *l = (LinkedList *)malloc(sizeof(LinkedList));
    l->head.next = NULL;
    l->length = 0;
    return l;
}

Node *init_node() {
    Node *node = (Node *)malloc(sizeof(Node));
    node->next = NULL;
    return node;
}

void insert (LinkedList *l, Node *node, int index) {
    Node *p = &(l->head);
    while (index--) {
        p = p->next;
        if (p == NULL) return;
    }
    node->next = p->next;
    p->next = node;
    l->length++;
    return ;
}

void output(LinkedList *l) {
    Node *p = l->head.next;
    while (p) {
        printf (" %s", inet_ntoa(p->client_addr.sin_addr));
        p = p->next;
    }
    printf ("\n");

    return ;
}

int find_min(LinkedList *l, int n) {
    int min = 0x3ffffff, num = 0;
    for (int i = 0; i < n; i++) {
        if (l[i].length < min) {
            min = l[i].length;
            num = i;
        }
    }
    return num;
}

int socketfd_create(int port) {
    int serverfd;
    struct sockaddr_in addr_server;
    if ((serverfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket failed!\n");
        exit(0);
    }
    addr_server.sin_family = AF_INET;
    addr_server.sin_port = htons(port);
    addr_server.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(serverfd, (struct sockaddr* )&addr_server, sizeof(struct sockaddr)) < 0) {
        perror("bind");
        exit(0);
    }

    if (listen(serverfd, 20) < 0) {
        perror("listen!");
        exit(0);
    }
    return serverfd;
}

int main () {
    struct sockaddr_in add_client;
    pthread_t pth[INS + 1];
    int port = 12345;

    // ip数
    int doubleClientNum = 200;
    int serverfd = socketfd_create(port);
    
    for (int i = 0; i < INS; i++) {
        if (pthread_create(&pth[i], NULL, func, (void *)&linkedlist[i]) == -1) {
            perror("pthread_create error!");
            exit(1);
        }
        printf ("the current id is = %ld\n", pth[i]);
    }
    
    int sub;
    HashTable *hash = init_hashtable(doubleClientNum);
    
    while (1) {
        Node *p = init_node();
        socklen_t len = sizeof(add_client);
        /*for (int i = 0; i < INS; ++i) {
            printf (" wwwwwww----- %d pthreads! ------- \n ", linkedlist[i].length);
            output(&linkedlist[i]);
        }*/
       
        //int new_client_fd; 
        if ((p->client_fd  = accept (serverfd, (struct sockaddr *)&p->client_addr, &len)) < 0) {
            perror("accept ERROR");
            exit(1);
        }

        printf (" %s", inet_ntoa((p->client_addr).sin_addr));
        printf ("\n");
        sub = find_min(linkedlist, INS);
        
        
        // 查找索引
        if (hash_search(hash, inet_ntoa(p->client_addr.sin_addr)) == 0) {
            
            insert(&linkedlist[sub], p, linkedlist[sub].length);
            hash_insert(hash, inet_ntoa(p->client_addr.sin_addr));
        } else {
            close(p->client_fd);
        }
        
        /*else {
            int listen_client = socket(AF_INET, SOCK_STREAM, 0);
            //sockaddr_in listen_client_fd;
            if (connect(listen_client, (struct sockaddr *)&p->client_addr, sizeof(add_client)) < 0) \
            {
                perror("master connect error!");
                exit(-1);
            }
            // something
            
            
            
        }*/
        
        //insert (&linkedlist[sub], p, linkedlist[sub].length);
        for (int i = 0; i < INS; ++i) {
            printf ("------- %d pthreads! ------- \n ", linkedlist[i].length);
            output(&linkedlist[i]);
        }
    } 
    pthread_join(pth[0], NULL);
    pthread_join(pth[1], NULL);
    pthread_join(pth[2], NULL);
    pthread_join(pth[3], NULL);
    pthread_join(pth[4], NULL);

    return 0;
}

void *func(void *argv) {
    LinkedList *arr = (LinkedList *)argv;
    Node *temp = arr->head.next;
    
   // struct sockaddr_in temp_sock;
   // int temp_df = socket(AF_INET, SOCK_STREAM, 0);
    

    /* temp_sock.sin_family = AF_INET;
    temp_sock.sin_port = temp->client_addr.sin_port;
    temp_sock.sin_addr.s_addr = temp->client_addr.sin_addr.s_addr;*/
    
    //printf (" %s", inet_ntoa(p->client_addr.sin_addr));

    while (1) {
        /*struct sockaddr_in temp_sock;
        int temp_df = socket(AF_INET, SOCK_STREAM, 0);
        socklen_t len = sizeof(temp_sock);
        */
        if (temp != NULL) {
            struct sockaddr_in temp_sock;
            int temp_df = socket(AF_INET, SOCK_STREAM, 0);
            socklen_t len = sizeof(temp_sock);


            //Node *ker = temp;
            //temp = temp->next;

            temp_sock.sin_family = AF_INET;
            temp_sock.sin_port = temp->client_addr.sin_port;
            temp_sock.sin_addr.s_addr = temp->client_addr.sin_addr.s_addr;
            
           if (connect(temp_df, (struct sockaddr *)&arr->head.client_addr, sizeof(temp_sock)) < 0) {
               perror("connect error1");
               //Node *delete_node = temp->next;
                //ker->next = temp->next;
                
                //temp = temp->next;
                //free(delete_node);
            } 
            
            #define MAX_V 1024
            FILE *fd = fopen("./file.log", "w+");
            char buffer[MAX_V];
            
            bzero(buffer, MAX_V);
            //int new_client_fd = accept(temp_df, (struct sockaddr *)&arr->head.client_addr, &len);
            int length = 0;
            while ((length = recv(temp_df  /*new_client_fdi*/, buffer, MAX_V, 0)) > 0) {
                if (fwrite(buffer, sizeof(char), length, fd) < length) {
                    break;
                }
                bzero(buffer, MAX_V);
            }
            fclose(fd);

            temp = temp->next;
        } 
        if (temp == NULL) { // 在走到末尾的时候走到链首
            temp = arr->head.next;
        } 
    }
    pthread_exit(NULL);
}

