#                           hello! world!                               
########################################################################
#--------> File Name:find_MaxLength_string.sh
#--------> Version: 1.0
#--------> Author: Peranda
#--------> Mail: 1365227825@qq.com 
#--------> Created Time:2018-10-14 18:42:15
########################################################################
#!/bin/bash

#max_val=0  #计算长度 初始长度  
#max_ans="" #保留串内容
#max_key="" #地址

link=""    #推导地址的变量

max_val=(0 0 0)
max_ans=("" "" "")
max_key=("" "" "")

filter() { #跳过带有这种后缀的文件
    a=(rmvb pdf png img ipg out gif jpeg md avi zip tar gz 7z mp3 mp4)
    suffix=`echo $1 | awk -F. '{print $NF}'`
    echo ${a[*]} | grep "$suffix" >/dev/null 
    if [[ $? -eq 0 ]]; then
        return 1
    fi 
    return 0
}


function read_file() { #处理文件
    filelist1=`cat $1` #传递的参数接受要用$1 shell里没有全局变量这种说法
    for i in $filelist1 
    do
        #        echo "sum_key:"
        #sum_key=`echo $i|awk '{print $5}'` #错误的实现方式
        #记得sum_key=`ls -l $i|awk'{print $5}'`　不要这么搞
        echo $i | grep "^[a-zA-Z]*$"
        if [[ $? -eq 0 ]]; then
            sum_key=${#i} #计算长度
            if [[ $sum_key -gt ${max_val[0]} ]]; then
                max_val[2]=${max_val[1]}
                max_ans[2]=${max_ans[1]}
                max_key[2]=${max_key[1]}

                max_val[1]=${max_val[0]}
                max_ans[1]=${max_ans[0]}
                max_key[1]=${max_key[0]}

                max_val[0]=$sum_key
                max_ans[0]=$i
                max_key[0]=$link
                continue
            fi
            if [[ $sum_key -gt ${max_val[1]} ]]; then
                max_val[2]=${max_val[1]}
                max_ans[2]=${max_ans[1]}
                max_key[2]=${max_key[1]}

                max_val[1]=$sum_key
                max_ans[1]=$i
                max_key[1]=$link
                continue 
            fi
            if [[ $sum_key -gt ${max_val[2]} ]]; then
                max_val[2]=$sum_key
                max_ans[2]=$i
                max_key[2]=$link
                continue
            fi
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
            file $i | grep "exec" >/dev/null 
            if [[ $? -eq 1 ]]; then 
                filter $i
                if [[ $? -eq 0 ]]; then
                    read_file $link
                fi
            fi
        fi 
    done
}

read_home="/home/peranda" #开始循环初始目录
for num in $read_home; do
    link=$read_home
    if [[ -d $num ]]; then #是目录就去递归　
        #echo $link
        file_run $link
    fi
    if [[ -f $num ]]; then
        file $num | grep "exec" >/dev/null 
        if [[ $? -eq 1 ]]; then 
            filter $num
            if [[ $? -eq 0 ]]; then
                read_file $link
            fi
        fi
    fi 
done

echo  ${max_ans[0]} > aa.log
echo >> aa.log
echo "他的地址是：" ${max_key[0]}
echo "他的长度是：" ${max_val[0]}

echo  ${max_ans[1]} >> aa.log
echo >> aa.log
echo "他的地址是：" ${max_key[1]}
echo "他的长度是：" ${max_val[1]}

echo  ${max_ans[2]} >> aa.log
echo >> aa.log
echo "他的地址是：" ${max_key[2]}
echo "他的长度是：" ${max_val[2]}
