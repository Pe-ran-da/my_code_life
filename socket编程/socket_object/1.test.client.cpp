/*************************************************************************
> File Name: 1.test.cpp
> Author: peranda
> Mail:1365227825@qq.com  
> Created Time: 2018年11月25日 星期日 15时05分59秒
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
#define port 12345
#define port1 12345//监听端口
#define host "192.168.1.154"


void socket_connect(char *host1, int Port) {
    int sockfd;
    struct sockaddr_in dest_addr;
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(Port);//本地转换为网络字节序
    dest_addr.sin_addr.s_addr = inet_addr(host1);
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket Failed!\n");
        exit(1);
    }

    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(port);
    dest_addr.sin_addr.s_addr = inet_addr(host);
    if (connect(sockfd, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) < 0) {
        printf ("connect Failed!\n");
        close (sockfd);
        exit(1);
    }
    printf ("Connect success!\n");
    close (sockfd);
    return ;
}
int socketfd_listen(int Port) {
    int serverfd;
    struct sockaddr_in addr_server;
    if ((serverfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        close (serverfd);
        perror("Socket failed!\n");
        exit(0);
    }
    addr_server.sin_family = AF_INET;
    addr_server.sin_port = htons(Port);
    addr_server.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(serverfd, (struct sockaddr* )&addr_server, sizeof(struct sockaddr)) < 0) {
        perror("bind");
        close (serverfd);
        exit(0);
    }

    if (listen(serverfd, 20) < 0) {
        perror("listen!");
        close (serverfd);
        exit(0);
    }
    return serverfd;
}
int main () { 

    socket_connect(host, port); // 连接
    int client_fd;
    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);

    int sock_fd = socketfd_listen(port1);  //监听
    int sum = 0;
    while (1) {
        printf("a = %d\n", sum);
        if (client_fd = accept(sock_fd, (struct sockaddr *)&client_addr, &len) < 0) {
            perror("accept failed!");
            continue;
        }

        if (sum > 10) {
            close(client_fd);
            break;
        }
        sum += 1;
    }
    close (sock_fd);
    return 0;
}
