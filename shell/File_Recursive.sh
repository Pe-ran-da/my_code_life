#                           hello! world!                               
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
