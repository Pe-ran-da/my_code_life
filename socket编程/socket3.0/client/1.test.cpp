/*************************************************************************
> File Name: 1.test.cpp
> Author: peranda
> Mail:1365227825@qq.com  
> Created Time: 2018年11月25日 星期日 15时05分59秒
************************************************************************/

#include "../common/common.h"
pthread_mutex_t add_old_key; // 定时日志获取锁
pthread_mutex_t main_key; // 主线程锁


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

//心跳
void heart_func() {
    int sockfd;
    char master_port_char[20];
    char master_port_ip[20];

    read_file("./configuration_file/file", "master_port", master_port_char);
    read_file("./configuration_file/file", "master_ip", master_port_ip);

    int heart_port = atoi(master_port_char);

    struct sockaddr_in dest_addr;
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(heart_port);
    dest_addr.sin_addr.s_addr = inet_addr(master_port_ip);

    printf("master ip : %s, port : %d\n", master_port_ip, heart_port);

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket Failed!\n");
        exit(1);
    }

    if (connect(sockfd, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) < 0) {
        printf ("connect Failed!\n");
        close (sockfd);
        //exit(1);
    }
    printf ("Connect success!\n");
    close (sockfd); 
}

// 心跳控制函数
void *socket_connect(void *argv) {
    while(1) {
        heart_func();
        sleep(30);
    }
}

int socketfd_listen(int Port) {
    int serverfd;
    struct sockaddr_in addr_server;
    if ((serverfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        close (serverfd);
        perror("Socket failed!\n");
        exit(0);
    }
    
    //char master_ip[30];
    //read_file("./configuration_file/file", "master_ip", master_ip);
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
    printf("listen over!\n");
    return serverfd;
}

//定时写入日志
void *add_old(void *argv) { 
    while(1) {
        //设置锁
        pthread_mutex_lock(&add_old_key);
        system("bash ./script/SysInfo.sh >> ./script/SysInfo.log");
        //解除锁
        pthread_mutex_unlock(&add_old_key);
        sleep(5);
    }
}


void send_file(int client_long_fd, int master_short_fd) {
    struct sockaddr_in master_short_in;
    socklen_t len = sizeof(master_short_in);
    printf("haha !\n");
    int client_short_fd;
    if ((client_short_fd = accept(master_short_fd, (struct sockaddr *)&master_short_in, &len)) <  0) {
        close(client_short_fd);
        perror("accept failed!");
    } else { 
        printf("zheli!\n");
        // 加锁
        pthread_mutex_lock(&main_key);
        #define MAX_SUM 1024
        FILE *fp;
        char buffer[MAX_SUM];
        bzero(buffer, MAX_SUM); 
        fp = popen("cat ./script/SysInfo.log", "r");
        if (fp == NULL) {
            perror("FILE Not Found\n");
        }
        int length = 0;
        printf("while hot!");
        while ((length = fread(buffer, sizeof(char), MAX_SUM, fp)) > 0) {
            if (send(client_short_fd, buffer, length, 0) < 0) {
                break;
            }
            printf("send over!");
            bzero(buffer, MAX_SUM);
        }
        fclose(fp);
        close(client_short_fd);
        system("rm ./script/SysInfo.log");
        pthread_mutex_unlock(&main_key);
    }
    printf("erererere!\n");
}

void main_fork() {
    pid_t pid;
    int i;
    pid = fork();
    if(pid == -1)
    {
        exit(-1);
    }
    else if(pid != 0){
        exit(EXIT_SUCCESS);
    }
}

int main() {
    //main_fork();
    pthread_t add_old_t;
    if (pthread_create(&add_old_t, NULL, add_old, NULL) == -1) {
        perror("pthread_create error!");
        exit(0);
    }
    
    pthread_t heart_t;
    if (pthread_create(&heart_t, NULL, socket_connect, NULL) == -1) {
        perror("pthread socket_connect error!");
        exit(0);
    }

    char CLIENT_PORT[30], MASTER_SHORT_PORT[30];
    read_file("./configuration_file/file", "client_port", CLIENT_PORT);
    int client_listen = socketfd_listen(atoi(CLIENT_PORT));

    read_file("./configuration_file/file", "master_short_port", MASTER_SHORT_PORT);
    printf("%s %s\n", CLIENT_PORT, MASTER_SHORT_PORT);
    int master_short_fd = socketfd_listen(atoi(MASTER_SHORT_PORT));
    int client_fd;
    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);
    
    while (1) {

        if ((client_fd = accept(client_listen, (struct sockaddr *)&client_addr, &len)) < 0) {
            close(client_fd);
        } else {
            printf("accept success!\n");
            send_file(client_fd, master_short_fd);
            close(client_fd);
        }
    }
    pthread_join(add_old_t, NULL);
    pthread_join(heart_t, NULL);
    close(master_short_fd);
    close (client_listen);
    return 0;
}
