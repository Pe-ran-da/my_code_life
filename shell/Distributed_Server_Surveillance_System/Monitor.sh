#                           hello! world!                               
########################################################################
#--------> File Name:Monitor.sh
#--------> Version: 1.0
#--------> Author: Peranda
#--------> Mail: 
#--------> Created Time:2018-09-12 14:00:34
########################################################################
#!/bin/bash

key=`top -n 1 | head -8 | tail -1 | xargs | cut -d " " -f 1-13`
pid1=` echo ${key} | cut -d " " -f 1 ` #top输出有个空格,所以从2开始取
cpu1=` echo ${key} | cut -d " " -f 9`
men1=` echo ${key} | cut -d " " -f 10` 
echo ${key} 
echo ${pid1}
echo ${cpu1}
echo ${men1}
#cpu1=`echo ${key} | xargs | cut -d " " -f 9`
#men1=`echo ${key} | xargs | cut -d `

sleep 5s #沉睡5秒

key=`top -n 1 | head -8 | tail -1 | xargs | cut -d " " -f 1-13 `
pid2=` echo ${key} | cut -d " " -f 1`
cpu2=` echo ${key} | cut -d " " -f 9`
men2=` echo ${key} | cut -d " " -f 10`
name=` echo ${key} | cut -d " " -f 2`
user_=`echo ${key} | cut -d " " -f 12`
echo ${key}
echo ${pid2}
echo ${cpu2}
echo ${men2}
echo ${name}
echo ${user_}

ans=" `date +%Y%m%d__%H:%M:%S ` ${user_} ${pid2} ${name} ${cpu2} ${men2}"
#时间 进程名 PID 用户 CPU占用 内存(men)占用
if [[ pid1 == pid2 && ( $(echo "$cpu1 >= 50" | bc) = 1 || $(echo "$cpu2 >= 50" | bc) = 1 ) ]]; then
    #此处有个浮点数比较，颇为有用
    echo "恶意进程:"
    echo $ans
else 
    echo "没有恶意进程,此时最大的进程为:"
    echo $ans
fi

