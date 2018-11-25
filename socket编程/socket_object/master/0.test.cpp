/*************************************************************************
	> File Name: 0.test.cpp
	> Author: peranda
	> Mail:1365227825@qq.com  
	> Created Time: 2018年11月21日 星期三 16时15分52秒
 ************************************************************************/
#include "common.h"
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



struct mypara {
    LinkedList * l;
    int num;//线程号
};

void *func(void *);



/***********初始化链表（链表用来存放，所有的client端结点的信息）******************/

LinkedList *init_linkedlist() {
    LinkedList *l = (LinkedList *)malloc(sizeof(LinkedList));
    l->head.next = NULL;
    l->length = 0;
    return l;
}


/***********初始化结点（结点用来存放client端信息**********/

Node *init_node() {
    Node *node = (Node *)malloc(sizeof(Node));
    node->next = NULL;
    return node;
}

/****************将主动连接过来的client端的结点信息，插入到链表中***********/

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


/********************从配置文件中读取信息********************/
int get_conf(char *pathname, char *key_name, char *value) {
    FILE *fp = NULL;
    if ((fp = fopen (pathname, "r")) == NULL) {
        printf ("pathname NULL!\n");
        exit(0);
    }
    size_t len = 0;
    char *line = NULL;
    ssize_t  read;
    int key_len = strlen(key_name);
    while (( read = getline(&line, &len, fp)) != -1) {
        if (strstr(line, key_name) != NULL) {
            if (line[key_len] == '=') {
                strncpy(value, &line[key_len + 1], read - key_len - 1);
                key_len = strlen(value);
                value[key_len - 1] = '\0';
                fclose(fp);
                return 1;
            }
        }
    } 
    fclose(fp);
    return 0;
}

/*****************输出*********************/
void output(LinkedList *l) {
    Node *p = l->head.next;
    while (p) {
        printf ("%s:%d\n", inet_ntoa(p->client_addr.sin_addr), ntohs(p->client_addr.sin_port));
        p = p->next;
    }
    printf ("\n");
}


/***************每次找到最短的链表进行插入**************/

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



/************************建立监听，等待client端主动连接********/

int socketfd_listen(int port1) {
    int serverfd;
    struct sockaddr_in addr_server;
    if ((serverfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket failed!\n");
        exit(0);
    }
    char port[10];
    get_conf("/home/gaoyu/code/socket_1/Phealthy.conf", "port", port);
    addr_server.sin_family = AF_INET;
    addr_server.sin_port = htons(atoi(port));
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


/*******主动建立与client的连接，连接失败就从链表中删除该结点************/

int socket_create(Node *p) {
    int sockfd;
    struct sockaddr_in dest_addr;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket Failed!\n");
        exit(0);
    }
    char port2[10] = {0};
    get_conf("./Phealthy.conf", "port1", port2);
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


/*********************判断是否重复，不重复就插入链表****************/

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


/***************删除结点***************/

void delete_node (LinkedList *l) {
        Node *p = &(l->head);
        Node *q = p->next;
        while (q) {
            if (socket_create(q) == 0) {
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
}

/*
void delete_node (LinkedList *l, int index) {
    Node *p = &(l->head); 
    while (index--) {
        p = p->next;
        if (p == NULL) return ;
    }
    if (p->next == NULL) return;
    Node *q = p->next;
    p->next = p->next->next;
    free (q);
    l->length--;
    return;
}
*/

int main () {
    pthread_t t[INS + 1];
    char ip[20] = {0}, start1[10] = {0}, finish1[10] = {0}, port[10] = {0};
    get_conf("/home/gaoyu/code/socket_1/Phealthy.conf", "prename", ip); 
    get_conf("/home/gaoyu/code/socket_1/Phealthy.conf", "start", start1);
    get_conf("/home/gaoyu/code/socket_1/Phealthy.conf", "finish", finish1);
    get_conf("/home/gaoyu/code/socket_1/Phealthy.conf", "port", port);
    int sub;
    int start = atoi(start1);
    int finish = atoi(finish1);
    for (int i = start; i <= finish; i++) {
        char buffer[100];
        sprintf(buffer,"%s.%d", ip, i);
        Node *p = init_node();
        p->client_addr.sin_addr.s_addr = inet_addr(buffer);
        p->client_addr.sin_port = htons(atoi(port));
        sub = find_min(linkedlist, INS);
        insert (&linkedlist[sub], p, linkedlist[sub].length); 
    }
    for (int i = 0; i < INS; ++i) {
        printf ("------>%d.log<-----------%d\n", i, linkedlist[i].length);
        output(&linkedlist[i]);
    }
    //创建线程
    struct mypara para[INS + 1];
    for (int i = 0; i < INS; i++) {
        para[i].l = &linkedlist[i];
        para[i].num = i;
        if (pthread_create(&t[i], NULL, func, (void *)&para[i]) == -1) {
            perror("pthread create ERROR !");
            exit(1);
        }
        //      printf ("current pthread id = %ld\n", t[i]);
    }
    struct sockaddr_in addr_client;
    int serverfd;
    serverfd = socketfd_listen(atoi(port));//监听

    //等待client端连接
    while (1) {
        Node *p = init_node();
        socklen_t len= sizeof(addr_client);
        if (p->client_fd = accept (serverfd, (struct sockaddr *)&p->client_addr, &len) < 0) {
            perror("accept ERROR");
            exit(1);
        }
        if (unrepeat(linkedlist, p, INS) == 0) {
            printf ("repeat!\n");
            continue;
        }
        sub = find_min(linkedlist, INS);
        insert (&linkedlist[sub], p, linkedlist[sub].length);
        for (int i = 0; i < INS; ++i) {
            printf ("----->%d.log<------------%d\n", i, linkedlist[i].length);
            output(&linkedlist[i]);
        }
    } 
    pthread_join(t[0], NULL);
    pthread_join(t[1], NULL);
    pthread_join(t[2], NULL);
    pthread_join(t[3], NULL);
    pthread_join(t[4], NULL);
    
    close(serverfd);
    return 0;
}


void *func(void *argv) {
    struct mypara *para;
    para = (struct mypara *)argv;
    LinkedList *list = para->l;
    while (1) {
        if (list != NULL)
            delete_node(list); 
        printf ("------>%d.log<--------%d\n", para->num, para->l->length);
        output(list);
        sleep(1);
    } 
    pthread_exit(NULL);
    return NULL;
}

