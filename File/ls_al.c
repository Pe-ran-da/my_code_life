/*************************************************************************
> File Name: ls_al.c
> Author: Peranda
> Mail: 
> Created Time: 2018年09月18日 星期二 13时50分27秒
************************************************************************/

#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <math.h>

void do_ls (char []);
void dostat(char *);
void show_file_info(char *, struct stat *);
void mode_to_letters(int , char []);
char *uid_to_name(uid_t);
char *gid_to_name(gid_t);

void do_ls1(char []);
void dostat1(char *);
void show_file_info1(struct stat *);
long int value;
float ans;

void main(int ac, char *av[]) {
    int ac1 = ac;
    if (ac1 == 1) {
        do_ls1(".");
    } else {
        while(--ac1) {
            do_ls1(*av);
        }
    }
    printf("总量为 %ld\n",value);    
    if (ac == 1) {
        do_ls(".");
    } else {
        while(--ac) {
            do_ls(*av);
        }
    }
    
}

void do_ls1(char dirname1[]) {    
    DIR *dir_list1; //目录操作指针
    struct dirent *dirfile1;//各个目录

    if (( dir_list1 = opendir(dirname1)) == NULL) {
        fprintf(stderr, "no open the %s lists!\n", dirname1);
    } else {    
        while(( dirfile1 = readdir(dir_list1)) != NULL) {
            dostat1(dirfile1->d_name);
        }
        closedir(dir_list1);
    }
}

void do_ls(char dirname[]) {
    DIR *dir_list; //目录操作指针
    struct dirent *dirfile;//各个目录

    if (( dir_list = opendir(dirname)) == NULL) {
        fprintf(stderr, "no open the %s lists!\n", dirname);
    } else {    
        while(( dirfile = readdir(dir_list)) != NULL) {
            dostat(dirfile->d_name);
        }
        closedir(dir_list);
    }
}


void dostat1(char *filename) {
    struct stat info;
    if (stat(filename, &info) == -1)//打开错误
    perror(filename);
    else {                           //打开
          show_file_info1(&info);

    }
}

void show_file_info1(struct stat *info_open) {
    ans = ceil ((info_open->st_size) * 1.0 / 4096);
    value += (int)ans * 4;
}

void dostat(char *filename) {
    struct stat info;
    if (stat(filename, &info) == -1)//打开错误
    perror(filename);
    else {                           //打开
          show_file_info(filename, &info);

    }
}

void show_file_info(char *filename, struct stat *info_open) {
    char *uid_to_name(), *ctime(), *gid_to_name(), *filemode();
    void mode_to_letters();
    char modestr[11]; // 前10位做类型显示
    mode_to_letters(info_open->st_mode, modestr);//计算文件类型和许可权限

    
    printf("%s ", modestr);
    printf("%ld ", info_open->st_nlink);
    printf("%-8s", uid_to_name(info_open->st_uid));
    printf("%-8s", gid_to_name(info_open->st_gid));
    printf("%8ld\t", info_open->st_size);
    printf("%-8.12s ", 4 + ctime(&info_open->st_mtime));

    if (modestr[0] == 'd') {
        printf("\033[1m\033[34m %-16s\n\033[0m", filename);
    } else { 
        printf("%-16s\n",filename);
    }

}

void  mode_to_letters(int mode, char str[]) {
    strcpy(str, "----------"); //填入字符
    //ch = 'w'; // 默认白色 显示文件颜色控制符
    if (S_ISDIR(mode)) str[0] = 'd'; 
    if (S_ISCHR(mode)) str[0] = 'c';
    if (S_ISBLK(mode)) str[0] = 'b';

    if (mode & S_IRUSR) str[1] = 'r';
    if (mode & S_IWUSR) str[2] = 'w';
    if (mode & S_IXUSR) str[3] = 'x';

    if (mode & S_IRGRP) str[4] = 'r';
    if (mode & S_IWGRP) str[5] = 'w';
    if (mode & S_IXGRP) str[6] = 'x';

    if (mode & S_IROTH) str[7] = 'r';
    if (mode & S_IWOTH) str[8] = 'w';
    if (mode & S_IXOTH) str[9] = 'x';
}

#include <pwd.h>

char *uid_to_name(uid_t uid) {
    struct passwd *getpwuid(), *pw_ptr;
    static char numstr[10];

    if ((pw_ptr = getpwuid(uid)) == NULL) {
        sprintf(numstr, "%d", uid);
        return numstr;
    } else {
        return pw_ptr->pw_name;
    }
}

#include <grp.h>

char *gid_to_name(gid_t gid) {
    struct group *getgrgid(), *grp_ptr;
    static char numstr[10];

    if ((grp_ptr = getgrgid(gid)) == NULL) {
        sprintf(numstr, "%d", gid);
        return numstr;
    } else {
        return grp_ptr->gr_name;
    }
}

