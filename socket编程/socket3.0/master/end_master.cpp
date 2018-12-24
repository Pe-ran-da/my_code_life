/*************************************************************************
> File Name: 1.master.cpp
> Author: peranda
> Mail:1365227825@qq.com  
> Created Time: 2018年11月21日 星期三 17时15分55秒
************************************************************************/

#include <string.h>
#include "../common/common.h"
#define INF 5 
#include <sys/stat.h> 

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
    read_file("../configuration_file/file", "master_port", port);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(port));
    server_addr.sin_addr.s_addr = (INADDR_ANY);
    if (bind(serverfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in)) < 0) { 
        // * sizeof 的套接字换成sockaddr
        perror("listen Socket bind error!");
        exit(0);
    }
    if (listen(serverfd, 20) < 0) {
        perror("listen Socket listen error!");
        exit(0);
    }
    return serverfd;
}

int sock_create(int num_fd, char *str) {

    //接收文件　    
    char client_PORT[20] = "";
    read_file("../configuration_file/file", "master_short_port", client_PORT);
    int client_port = atoi(client_PORT);

    int client_temp;
    struct sockaddr_in temp_addr;
    temp_addr.sin_family = AF_INET;
    temp_addr.sin_port = htons(client_port);
    temp_addr.sin_addr.s_addr = inet_addr(str);
    printf("test 1\n");
    sleep(1);
    if ((client_temp = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        close(client_temp);
        perror("get socket error!");
    }

    printf("test 2\n");
    sleep(1);
    if(connect(client_temp, (struct sockaddr *)&temp_addr, sizeof(temp_addr)) == 0) {
        printf("test 3\n");
        sleep(1);
        #define MAX_SUM 1024
        FILE *fp;
        char buffer[MAX_SUM + 2], IP[100];
        bzero(IP, 100);
        printf("%s\n", IP);
        bzero(buffer, MAX_SUM + 2);
        strcat(IP, "./master_log/");
        strcat(IP, str);
        strcat(IP, "/");
        strcat(IP, str);
        strcat(IP, ".log");
        fp = fopen(IP, "a+");
        if (fp == NULL) {
            fclose(fp);
            printf("--------------no %d file !", IP);
            //pthread_mutex_unlock(&arr[para->number]);
            // fclose(fp);
            // continue;
        }
        printf("%s hahah \n", str);
        bzero(buffer, MAX_SUM + 2);
        while (recv(client_temp, buffer, MAX_SUM, 0) > 0) {
            fwrite(buffer, strlen(buffer), 1, fp);
            fflush(stdout);
            bzero(buffer, MAX_SUM + 2);
            printf("yuan a %s\n", str);
        }
        close(client_temp);
        fclose(fp);
        printf("end recv !\n");

    } else {
        printf("test 4\n");
        sleep(1);
        close(client_temp);
        printf(" emmmm %s %s\n", client_PORT, str);
        perror("4 get socket connect error!");
    }
    return 0;
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

/*void delete_node(LinkedList *l) {
    Node *p = &(l->head);
    Node *q = p->next;;fdkdslf;ffjldsf
    while (q) {
        if (sockcreate(q) == 0) {
            Node *x = q;
            p->next = q->next;
            free(x);
            l->length--;
            q = p->next;
            printf("asdasdadssadasdasdasd\n");
            break;
        }
        else {
            p = p->next;
            q = q->next;
        }
        printf("tiaooooooooooooooooooooooooooo\n");
    }
    printf("111111111111111delete end!\n");
    //output(linkedlist);
    return ;
}*/


void delete_node(mythreads *para, LinkedList *l, Node *node) {
    pthread_mutex_lock(&arr[para->number]);
    Node *p = &(l->head); 
    while (p->next != NULL && p->next != node) {
        p = p->next;
    }
    if (p->next == node) {
        Node *current_node = p->next;
        p->next = current_node->next;
        free(current_node);
        l->length -= 1;
    }
    pthread_mutex_unlock(&arr[para->number]);
    return ;
}



void connect_node(mythreads *para) {
    Node *node = &para->l->head;
    char client_port_c[20];
    read_file("../configuration_file/file", "client_port", client_port_c);
    int client_port = atoi(client_port_c);
    while (node->next) {
        int server_socket;
        if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            perror("connect_node Socket error!\n");
            exit(0);
        }
        node = node->next;
        node->client_addr.sin_port = htons(client_port);
        if (connect(server_socket, (struct sockaddr *)&node->client_addr, sizeof(node->client_addr)) < 0){
            printf("delete the %s node!\n", inet_ntoa(node->client_addr.sin_addr));
            delete_node(para, para->l, node);
            //output(para->l);
            close(server_socket);
            continue;
        }
        char ip[60], path[60] = "./master_log/";
        strcpy(ip, inet_ntoa(node->client_addr.sin_addr));
        printf("link the %s node success!\n", ip);
        strcat(path, ip);
        mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        sock_create(server_socket, ip);
        close(server_socket);
    }
    return ;
}

void main_fork(){
    pid_t pid;
    int i;
    pid = fork();
    if(pid == -1) {
        exit(-1);
    }
    else if(pid != 0){
        exit(EXIT_SUCCESS);
    } 
}

int main() {
    main_fork();
    mutex_locks();

    char ip[20], head_sum[20], tail_sum[20], port[20] ;
    bzero(ip, 20);
    bzero(head_sum, 20);
    bzero(tail_sum, 20);
    bzero(port, 20);

    read_file("../configuration_file/file", "ip", ip);
    read_file("../configuration_file/file", "head", head_sum);
    read_file("../configuration_file/file", "tail", tail_sum);
    read_file("../configuration_file/file", "master_port", port);

    // 初始化任务队列
    /*int value;
    int head = atoi(head_sum);
    int tail = atoi(tail_sum);
    for (int i = head; i <= tail; i++) {
        char buffer[20];
        sprintf(buffer,"%s.%d", ip, i);
        printf("%s.%d\n", ip, i);
        Node *node = init_node();
        node->client_addr.sin_addr.s_addr = inet_addr(buffer);
        node->client_addr.sin_port = htons(atoi(port));
        //printf("first %s , %d\n", node->client_addr.sin_addr.s_addr, node->client_addr.sin_port);
        printf("first %d , %d\n", inet_addr(buffer), htons(atoi(port)));
        printf("first %s , %s\n\n", buffer, port);
        value = find_min(linkedlist, INF);
        insert(&linkedlist[value], node, linkedlist[value].length);
    }
    for (int i = 0; i < INF; i++) {
        printf("--------%dths phreads is %d length-----------\n", i, linkedlist[i].length);
        output(&linkedlist[i]);
    }*/


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

    int client_fd, interim_fd;
    struct sockaddr_in client_addr;
    interim_fd = socketfd_listen(atoi(port));

    int value;
    while (1) {

        client_fd = interim_fd;
        Node *p = init_node();
        socklen_t len = sizeof(client_addr);
        printf("%d\n", client_fd);
        if ((p->client_fd = accept(client_fd, (struct sockaddr *)&p->client_addr, &len)) < 0) {
            perror("main func accept error!");
            close(client_fd);
            exit(0);
        }

        if (unrepeat(linkedlist, p, INF) == 0) {
            printf ("the node presence!\n");
            close(p->client_fd);
            continue;
        }
        value = find_min(linkedlist, INF);
        pthread_mutex_lock(&insert_key);
        insert (&linkedlist[value], p, linkedlist[value].length);
        pthread_mutex_unlock(&insert_key);

        close(p->client_fd);

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
    return 0;
}

void *func(void *argv) {
    struct mythreads *para;
    para = (struct mythreads *)argv;
    LinkedList *list = para->l;

    while (1) {
        connect_node(para);
       /* printf ("+=============the pthread %d length is %d==============+\n", para->number, para->l->length);
        for (int i = 0; i < INF; i++) {
            printf("while!--------%dths phreads is %d length-----------\n", i, linkedlist[i].length);
            output(&linkedlist[i]);
        }*/
        sleep(1);
    } 
    pthread_exit(NULL);
    return NULL;
}

