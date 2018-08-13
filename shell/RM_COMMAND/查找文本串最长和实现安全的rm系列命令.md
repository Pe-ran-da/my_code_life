





# 第一个作业：实现遍历目录并且查找其最长字符串，长度以及所在文件



```shell

########################################################################
#--------> File Name:File_Recursive.sh
#--------> Version: 1.0
#--------> Author: peranda
#--------> Mail: 1365227825@qq.com
#--------> Created Time:2018-08-12 15:32:02
########################################################################
#!/bin/bash

max_val=0 #计算长度  
max_ans="" #保留串内容
max_key="" #地址
link=""    #推导地址的变量

maxsize=$((1024))

function read_file() { #处理文件
    filelist1=`cat $1` #传递的参数接受要用$1 shell里没有全局变量这种说法
    for i in $filelist1 
    do
        #        echo "sum_key:"
        #sum_key=`echo $i|awk '{print $5}'` #错误的实现方式
                                         #记得sum_key=`ls -l $i|awk'{print $5}'`　不要这么搞
        sum_key=${#i} #计算长度
        if [[ $sum_key -gt $maxsize ]]; then
                max_val=$sum_key
                max_ans=$i
                max_key=`pwd`
        fi 
    done
}

function file_run() { #递归目录
    for i in  `ls $1`
    do
    #    echo "link :"
        link=$1/$i #将当前目录做成串
        echo $link
        if [[ -d $link ]]; then
            file_run $link
        fi
        if [[ -f $link ]]; then
            read_file $link
        fi 
    done
}

read_home="/home/peranda/algorithm/" #开始循环初始目录
 
for num in $read_home; do
    if [[ -d $num ]]; then #是目录就去递归　
        link=$read_home
        echo $link
        file_run $link
    fi
    if [[ -f $num ]]; then #文件就查找
        read_file $num
    fi 
done

echo "输出整个串：" $max_ans
echo "他的地址是：" $max_key
echo "他的长度是：" $max_val

```





## 实现的难点：

> 1. 首先是递归入口的确立，最开始对目录的递归的实现没有任何思路，后面抽出来作为主函数块实现了
>
> 2. 对shell的语法不熟悉，导致了相关的操作失误
>
> 3.  sum_key= ｀echo $i|awk '{print $5}'｀是错误的实现方式
>
> ​        sum_key= ｀ls -l $i|awk'{print $5}'｀　这么搞是把字符串再展开，是不对的







## 对本次实现的思考：

>1. 本次的代码是第一次对文件操作的脚本实现，首先是心理障碍，怕去写和怕去学，这算是迈出了第一步
>2. 这次的实现是需要理解的，要先大致规划一下代码的运行流程，然后去思考一下实现的大致方向，最后加以实现







## 执行结果：

![zuoye1](/home/peranda/Pictures/zuoye1.png)











#　第二个作业：实现一个回收站



## 在/.bashrc里面的部分

```shell
# 创造新的rm命令的别名
THEN_RECOVER=/home/.../.My_Pail #我的回收站的地址
alias rm='source /home/.../RM_COMMAND/move_file.sh'    #删除（移动命令）的别名设置
alias rl='source /home/.../RM_COMMAND/read_file.sh'    #浏览命令别名的设置
alias rf='source /home/.../RM_COMMAND/found_file.sh'   #找回回收站的文件的设置
alias rmd='source /home/.../RM_COMMAND/delete_file.sh' #清空回收站内的文件
#保险起见　路径替换成了/...

```



## move_file.sh 部分

``` shell

#移动文件的操作
    if [[ "$1" == "-f"  ]]; then #rm -r name
        echo -e "\033[1;34m执行了rm -f操作！\033[0m"
        if [[ -d $2   ]]; then
            mv $2 ~/.My_Pail/$2 
            #不增加时间在结尾是因为如果是目录最好不要添加东西
        else 
            mv $2 ~/.My_Pail/${2}.`date +%Y%m%d-%H:%M:%S`
            #文件则在末尾日期，因为删除文件比较频繁，以免出现重名
        fi 
        echo -e "\033[1;34m已经将"$@"放入回收站\033[0m" 
        　
    elif [[ "$1" == "-r" && "$2" == "-f"   ]]; then 
        　 
        echo -e "\033[1;34m执行了rm -r -f操作！\033[0m"
        mv $3 ~/.My_Pail/$3 

        #只需要移动这个目录或者文件　因为在其他地方文件末尾是有日期的
        #不怕重名


    else  
        echo -e "\033[1;34m正在进行将"$@"放入回收站的操作！\033[0m"
        #rm name 实现删除（移动）功能
        mv $@ ~/.My_Pail/$@.`date +%Y%m%d-%H:%M:%S`

        if [[ $? -eq 0   ]]; then
            echo -e "\033[1;34m已经将"$@"放入回收站！\033[0m"
        else 
            echo -e "\033[1;31m您的回收操作失败了！\033[0m"
        fi
        #设置时间是为了预防多次移动的文件出现重名
        #并且能直观的分辨文件的移动时间
    fi


```



## read_file.sh　部分

``` shell
#浏览回收站的东西
 
    # rl 直接查看文件内容
    echo -e "\033[1;34m您的回收站内有这些文件：\033[0m"
    ls -al ~/.My_Pail


```



## found_file.sh 部分

```shell
#找回文件的操作

	# rf mame* 因为找回的文件名字自带时间
    mv -i ~/.My_Pail/$@ ./ 
    if [[ $? -eq 0 ]]; then
        echo -e "\033[1;34m您已经将文件"$@"找回至\033[0m"; pwd
    else 
        echo -e "\033[1;31m您的文件找回操作失败！\033[0m" 
    fi 


```





## delete_file.sh　部分

```shell
#删除文件的操作

    echo -e "\033[1;31m警告！您正在的进行回收站清空操作！！\033[0m"
    echo -e "\033[1;31m您确定要执行此操作吗？[y/n]\033[0m"
    read key
    if [ $key == 'y' -o $key == 'Y' ]; then 
        /bin/rm -rf ~/.My_Pail/*
        echo -e "\033[1;34m您的清空操作执行成功！\033[0m"
    else 
        echo -e "\033[1;31m您的清空操作失败！请检查是否出现问题！\033[0m" 
    fi


```

## clear_file.sh 部分

``` shell

find ~/.My_Pail/* -mtime +7 -name "*" -exec /bin/rm -rf {} \; 
# 删除存在超过７天的文件
# 然后在终端执行　crontab -e
#0 0 * * * /.../clear_file.sh >/dev/null 2>&1
#/dev/null２>&1 意思就是把错误输出2重定向到标准输出1，也就是屏幕，标准输出进了“/null”，也就是标准输出进了黑洞，错误输出打印到屏幕 
#设置是每天凌晨0点0分执行clear_file.sh文件进行数据清理任务了。
```







## 实现的难点：

> 1. 对于.bashrc的工作情况不理解，最开始导致了无法实现脚本的构架
> 2. 对于source的工作职能不理解，所以我后来在.bashrc里面无法实现封装各个部分的函数，并且传入.bashrc
> 3. 对于定时删除文件的相应语法完全不熟悉
> 4. 在自定义安全的"rm -f"以及"rm -r -f"会自动输出一句　": 未找到命令"，那应该是系统自己的"rm"里面未执行输出的
>
> 







## 对于本题思考：

>1. 首先是对.bashrc文件意义的不理解，最开始把整个脚本写到了.bashrc里面，这是不对也是不好的习惯，需要对自己的习惯进行约束
>2. 探索的心很重要，多试试不同的写法是最快的学习方法









## 执行结果：

![zuoye](/home/peranda/Pictures/zuoye.png)



