/*************************************************************************
	> File Name: 1.client.cpp
	> Author: peranda
	> Mail:1365227825@qq.com  
	> Created Time: 2018年11月23日 星期五 15时07分15秒
 ************************************************************************/

#include "../common/common.h"


int read_file(char *filename, char *path, char *arr) {
    FILE *fp;
    if ((fp = fopen(filename, "r")) == NULL) {
        perror("client fopen error!");
        exit(0);
    }
    size_t len = 0;
    char *line = NULL;
    ssize_t read;
    int path_len = strlen(path);
    while ((read = getline(&line, &len, fp)) != -1) {
        if (strstr(line, path) == NULL) continue;
        if (line[path_len] != '=') continue;
        
        strncpy(arr, &line[path_len + 1], read - path_len - 1);
        int addlen = strlen(arr);
        arr[addlen - 1] = '\0';
        break;
    }
    fclose(fp);
    return 0;

}


int insert_master() {
    char host[20];
    char port[20];
    read_file("../configuration_file/file", "master_ip", host);
    read_file("../configuration_file/file", "port", port);
    
    struct sockaddr_in client_addr;
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = inet_addr(host);
    client_addr.sin_port = htons(atoi(port));

    int client_fd;
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("client insert Socket error!");
        exit(0);
    }

    if (connect(client_fd, (struct sockaddr *)&client_addr, sizeof(struct sockaddr_in)) < 0) {
        perror("client insert connect error!");
        exit(0);
    }
   
    close(client_fd);
    return 1;
} 

int listen_master() {
    char host[20];
    char port[20];
    read_file("../configuration_file/file", "master_ip", host);
    read_file("../configuration_file/file", "port", port);
    
    struct sockaddr_in client_addr;
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = inet_addr(host);
    client_addr.sin_port = htons(atoi(port));

    int client_fd;
    printf("%d", client_fd);
    printf("ann!");
    
    if (bind(client_fd, (struct sockaddr *)&client_addr, sizeof(struct sockaddr_in)) < 0) {
        perror("client Listen bind error!"); 
        exit(0);
    }

    if (listen(client_fd, 20) < 0) {
        perror("client Listen listen error");
        exit(0);
    }
    
    //int new_master_fd;
    //struct sockaddr_in new_master_addr;
    
   // while (1) {
        int new_master_fd;
        struct sockaddr_in new_master_addr;
        printf("haha!");
        if ((new_master_fd = accept(new_master_fd, (struct sockaddr *)&new_master_addr, sizeof(struct sockaddr_in))) < 0) {
            perror("client Listen accept error!");
            exit(0);
        }
        printf("while 1 !\n");
        close(new_master_fd);
   // }
    close(client_fd);
    return 0;
}


int main() {
    insert_master();
    sleep(3);
    listen_master();
    
    return 0;
}
