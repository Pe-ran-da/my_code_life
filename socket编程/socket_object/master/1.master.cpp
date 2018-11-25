/*************************************************************************
	> File Name: 1.master.cpp
	> Author: peranda
	> Mail:1365227825@qq.com  
	> Created Time: 2018年11月21日 星期三 17时15分55秒
 ************************************************************************/

#include <string.h>
#include "../common/common.h"
#define INF 5 

pthread_mutex_t arr[INF];
pthread_mutex_t insert_key;
void mutex_locks() {
    //pthread_mutex_t arr[INF];
    for (int i = 0; i < INF; i++)
        arr[i] = PTHREAD_MUTEX_INITIALIZER;
    insert_key = PTHREAD_MUTEX_INITIALIZER;
}

typedef struct Node {
    int client_fd; // 套接字
    struct sockaddr_in client_addr; // 套接字结构体
    struct Node *next; 
} Node;

typedef struct LinkedList {
    Node head;
    int length; // 长度标示量
} LinkedList;

// 线程数组
LinkedList linkedlist[INF + 1] = {0};

struct mythreads {
    LinkedList *l; //线程标记
    int number; // 线程的标记位
};

void *func(void *);

/******************hash*******************/
typedef struct NodeHash{
    char *str;  // 记录的字符串
    int key;  // 删除和存在的标记
    struct NodeHash *next;
} NodeHash;

typedef struct HashTable {
    NodeHash **data;
    int size; // 哈希的头节点大小
} HashTable;

NodeHash *init_node(char *str, NodeHash *head) {
    NodeHash *p = (NodeHash *)malloc(sizeof(NodeHash));
    p->str = strdup(str);
    p->next = head;
    p->key = 1; // 将点置为存在
    return p;
} 


HashTable *init_hashtable(int n) {
    HashTable *h = (HashTable *)malloc(sizeof(HashTable));
    h->size = n << 1;
    h->data = (NodeHash **)calloc(sizeof(NodeHash *), h->size);
    return h;
}

/*void hash_clear_node(NodeHash *node) {

}*/

/*void clear_hashtable(HashTable *h) {

}*/


int BKDRHash(char *str) {
    int seed = 31, hash = 0;
    for (int i = 0; str[i]; i++) {
        hash = hash * seed + str[i];
    }
    return hash & 0x7fffffff;
}
 
int hash_insert(HashTable *h, char *str) {
    int hash = BKDRHash(str);
    int ind = hash % h->size;
    NodeHash *p = h->data[ind]; 
    while (p && strcmp(p->str, str)) p = p->next;
    if (strcmp(p->str, str) == 0) { // 以前存在过
        p->key = 1;
    } else {  // 以前没有存在过
        h->data[ind] = init_node(str, h->data[ind]);
    }
    return 1;
}

int hash_search(HashTable *h, char *str) {
    int hash = BKDRHash(str);
    int ind = hash % h->size;
    NodeHash *p = h->data[ind];
    while (p && strcmp(p->str, str)) p = p->next;
    if (strcmp(p->str, str) == 0 && p->key == 1) {
        return 1;    //p->key = 1; 点为存在
    } else {
        return 0;
    }
}

void delete_hash(HashTable *h, char *str) {
    int hash = BKDRHash(str);
    int ind = hash % h->size;
    NodeHash *p = h->data[ind];
    while (p && strcmp(p->str, str)) p = p->next;
    if (strcmp(p->str, str) == 0) {
        p->key = 0; 
    }
    return ;
}

/*************hash*************/

/*************linkedlist****************/
  
LinkedList *init_linkedlist () {
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

void insert(LinkedList *l, Node *node, int index) {
    Node *p = &(l->head);
    while (index--) {
        p = p->next;
        if (p == NULL) return ;
    }
    node->next = p->next;
    p->next = node;
    l->length += 1; // 长度
    return ;
}

void output(LinkedList *l) {
    printf("output the link\n");
    Node *p = l->head.next;
    while (p) {
        printf("%s:%d\n", inet_ntoa(p->client_addr.sin_addr), ntohs(p->client_addr.sin_port));
        p = p->next;
    }
    printf("\n");
    return ;
}

int find_min(LinkedList *l, int n) {
    int min = 0x7fffffff, num = 0;
    for (int i = 0; i < n; i++) {
        if (l[i].length < min) {
            min = l[i].length;
            num = i;
        }
    }
    return num;
}

int read_file(char *filename, char *path, char *arr) {
    FILE *fp ;
    if ((fp = fopen(filename, "r")) == NULL) {
        perror("read_file open file error!");
        exit(0);
    }
    
    size_t len = 0;
    char *line = NULL;
    ssize_t read;
    int path_len = strlen(path);
    while ((read = getline(&line, &len, fp)) != -1) {
        if (strstr(line, path) != NULL) {
            if (line[path_len] != '=') continue;
            strncpy(arr, &line[path_len + 1], read - path_len - 1);
            int addlen = strlen(arr);
            arr[addlen - 1] = '\0';
            break;
        }
    }
    fclose(fp);
    return 0;
}

int socketfd_listen(int listen_port) {
    int serverfd;
    struct sockaddr_in server_addr;
    
    if ((serverfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("listen Socket error!");
        exit(0);
    }
    
    char port[20];
    bzero(port, 20); // *
    read_file("../configuration_file/file", "port", port);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(port));
    server_addr.sin_addr.s_addr = (INADDR_ANY);
    if (bind(serverfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in)) < 0) { // * sizeof 的套接字换成sockaddr
        perror("listen Socket bind error!");
        exit(0);
    }
    if (listen(serverfd, 20) < 0) {
        perror("listen Socket listen error!");
        exit(0);
    }
    return serverfd;
}

int sockcreate(Node *p) {
    /*int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0))) {
        perror("ping client Socket is error!");
        exit(0);
    }
    char port[20];
    bzero(port, 20);
    */
    int sockfd;
    struct sockaddr_in dest_addr;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket Failed!\n");
        exit(0);
    }
    char port2[10] = {0};
    read_file("../configuration_file/file", "port", port2);
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(atoi(port2));
    dest_addr.sin_addr.s_addr = p->client_addr.sin_addr.s_addr;
    if (connect(sockfd, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) < 0) {
        printf ("delete %s\n", inet_ntoa(p->client_addr.sin_addr));
        close(sockfd);
        return 0;
    }
    close(sockfd);
    return 1;
}

int find_node(HashTable *hash, char *str) {
    if (hash_search(hash, str) == 0) {
        return 0; // 0 yes
    }
    return 1; // 1 no
}

int unrepeat(LinkedList *l,Node *node, int n) {
    for (int i = 0; i < n; i++) {
        Node *p = l[i].head.next;
        while (p) {
            if (p->client_addr.sin_addr.s_addr == node->client_addr.sin_addr.s_addr) {
                return 0;
            }
            p = p->next;
        }
    }
    return 1;
}


void delete_node(LinkedList *l) {
    Node *p = &(l->head);
    Node *q = p->next;
    while (q) {
        if (sockcreate(q) == 0) {
            Node *x = q;
            p->next = q->next;
            free(x);
            l->length--;
            q = p->next;
        }
        else {
            p = p->next;
            q = q->next;
        }
    }
    output(linkedlist);
    return ;
}

int main() {
    mutex_locks();

    char ip[20], head_sum[20], tail_sum[20], port[20] ;
    bzero(ip, 20);
    bzero(head_sum, 20);
    bzero(tail_sum, 20);
    bzero(port, 20);
    
    read_file("../configuration_file/file", "ip", ip);
    read_file("../configuration_file/file", "head", head_sum);
    read_file("../configuration_file/file", "tail", tail_sum);
    read_file("../configuration_file/file", "port", port);
    
    // 初始化任务队列
    int value;
    int head = atoi(head_sum);
    int tail = atoi(tail_sum);
    // HashTable *hash = init_hashtable(10000); 
    for (int i = head; i <= tail; i++) {
        char buffer[20];
        sprintf(buffer,"%s.%d", ip, i);
        printf("%s.%d\n", ip, i);
        Node *node = init_node();
        node->client_addr.sin_addr.s_addr = inet_addr(buffer);
        node->client_addr.sin_port = htons(atoi(port));
        value = find_min(linkedlist, INF);
        insert(&linkedlist[value], node, linkedlist[value].length);
       // hash_insert(hash, buffer);
    }
    for (int i = 0; i < INF; i++) {
        printf("--------%dths phreads is %d length-----------\n", i, linkedlist[i].length);
        output(&linkedlist[i]);
    }
    

    // 创建调用线程
    pthread_t pth_t[INF + 1];
    //带长度的结构体数组
    struct mythreads my_pth[INF + 1];
    for (int i = 0; i < INF; i++) {
        my_pth[i].l = &linkedlist[i];
        my_pth[i].number = i;
        if (pthread_create(&pth_t[i], NULL, func, &my_pth[i]) == -1) {
            perror("pthread_create error~!");
            exit(0);
        }
    }
    

    //监听client的连接情况
    struct sockaddr_in client_addr;
    int client_fd;
    client_fd = socketfd_listen(atoi(port));
    
    //HashTable *hash = init_hashtable(10000); // 开 6倍最小值的空间　５个线程
    while (1) {
        Node *p = init_node();
        socklen_t len = sizeof(client_addr);
        if (p->client_fd = accept(client_fd, (struct sockaddr *)&p->client_addr, &len) < 0) {
            perror("main func accept error!");
            exit(0);
        }
        
        if (unrepeat(linkedlist, p, INF) == 0) {
            printf ("the node presence!\n");
            continue;
        }
        value = find_min(linkedlist, INF);
        pthread_mutex_lock(&insert_key);
        insert (&linkedlist[value], p, linkedlist[value].length);
        pthread_mutex_unlock(&insert_key);

        /*if (hash_search(hash, inet_ntoa(p->client_addr.sin_addr)) == 0) {
            insert(&linkedlist[value], p, linkedlist[value].length);
            //hash_insert(hash, inet_ntoa(p->client_addr.sin_addr));
        } else {
            printf(".............\n");
            continue;
        }*/
        for (int i = 0; i < INF; i++) {
            printf("listen!--------%dths phreads is %d length-----------\n", i, linkedlist[i].length);
            output(&linkedlist[i]);
        }
        
    }
    
    pthread_join(pth_t[0], NULL);
    pthread_join(pth_t[1], NULL);
    pthread_join(pth_t[2], NULL);
    pthread_join(pth_t[3], NULL);
    pthread_join(pth_t[4], NULL);
    
    close(client_fd);
    
    return 0;
}

void *func(void *argv) {
    struct mythreads *para;
    para = (struct mythreads *)argv;
    LinkedList *list = para->l;
    while (1) {
        if (list != NULL) {
            pthread_mutex_lock(&arr[para->number]);
            delete_node(list); 
            pthread_mutex_unlock(&arr[para->number]);

            //printf ("%d %d\n", para->number, para->l->length);
           // output(list);
            //sleep(1);
        } /*else {
            printf ("the pthread %d length is %d\n", para->number, para->l->length);
        }*/
        printf ("------------the pthread %d length is %d------------\n", para->number, para->l->length);
        for (int i = 0; i < INF; i++) {
            printf("while!--------%dths phreads is %d length-----------\n", i, linkedlist[i].length);
            output(&linkedlist[i]);
        }
        sleep(3);
    } 
    pthread_exit(NULL);
    return NULL;
}

