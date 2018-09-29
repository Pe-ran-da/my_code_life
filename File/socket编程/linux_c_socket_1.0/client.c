/*************************************************************************
> File Name: client.c
> Author: Peranda
> Mail: 
> Created Time: 2018年09月28日 星期五 11时20分16秒
************************************************************************/
/*
#include <stdio.h>
#include<netinet/in.h>  // sockaddr_in 
#include<sys/types.h>  // socket 
#include<sys/socket.h>  // socket 
#include<stdio.h>    // printf 
#include<stdlib.h>    // exit 
#include<string.h>    // bzero 
*//*
*/

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

//buffer数组长度
#define BUFFER_SIZE 1024 

int main(int ag, char **av) {

    char *host = av[1];//ip
    int port = atoi(av[2]);//端口

    // 声明并初始化一个客户端的socket地址结构 
    struct sockaddr_in client_addr; 
    bzero(&client_addr, sizeof(client_addr)); 
    client_addr.sin_family = AF_INET; 
    client_addr.sin_addr.s_addr = inet_addr(host);//ip 
    client_addr.sin_port = htons(port); //端口

    // 创建socket，若成功，返回socket描述符 
    int client_socket_fd = socket(AF_INET, SOCK_STREAM, 0); 
    if(client_socket_fd < 0) { 
        perror("Create Socket Failed:"); 
        exit(1); 
    } 
    
    if(connect(client_socket_fd, (struct sockaddr*)&client_addr, sizeof(client_addr)) < 0) { 
        perror("Can Not Connect To Server IP:"); 
        exit(0); 
    } 
    
    // 打开文件，读入
    FILE *fd = fopen("./cccp", "r");
    FILE *fd1 = fopen("./cn",  "r");
    char buffer[BUFFER_SIZE]; 
    
    // 从服务器接收数据到buffer中 
    // 每接收一段数据，便将其写入文件中，循环直到文件接收完并写完为止 
    bzero(buffer, BUFFER_SIZE); 
    int length = 0;
    // 打开fd1内的数据
    while((length = fread(buffer, sizeof(char), BUFFER_SIZE, fd1)) > 0) {
        // 向服务器发送buffer中的数据 
        if(send(client_socket_fd, buffer, length, 0) < 0) { 
            break; 
        } 
        bzero(buffer, BUFFER_SIZE); 
    } 
    
    bzero(buffer, BUFFER_SIZE);
    while((length = fread(buffer, sizeof(char), BUFFER_SIZE, fd)) > 0) {
        if (send(client_socket_fd, buffer, length, 0) < 0) {
            break;
        }
        bzero(buffer, BUFFER_SIZE);
    }

    // 接收成功后，关闭文件，关闭socket 
    fclose(fd); 
    close(client_socket_fd); 
    return 0; 
} 
