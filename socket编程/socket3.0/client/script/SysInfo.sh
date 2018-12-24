#                           hello! world!                               
########################################################################
#--------> File Name:SysInfo.sh
#--------> Version: 1.0
#--------> Author: Peranda
#--------> Mail: 
#--------> Created Time:2018-08-26 09:57:21
########################################################################
#!/bin/bash

echo "------------"
echo "time    hostname    OS   root版本   runtime  平均负载　　磁盘总量　　磁盘所用百分比　内存大小　　内存已用百分比　cpu温度　　　磁盘警报级别　　内存警报级别　　cpu警报级别"

echo -n "`date +%Y%m%d_%H:%M:%S`  " #时间
echo -n "`hostname` " # 主机名字
echo -n "`uname -o` " # os版本
echo -n "`cat /proc/version | cut -d " " -f 3 `  " #内核版本
echo -n "`uptime -p | tr " " "_"` " #运行时间
echo -n " `cat /proc/loadavg | cut -d " " -f 1-3` " #平均负载

###########磁盘总量（所有的量）
ans=`grep MemTotal /proc/meminfo | xargs | cut -d " " -f 2` # MemTotal里面找了磁盘内存总量
echo -n "${ans}MB " #输出磁盘内存总量
ans1=`grep MemFree /proc/meminfo | xargs | cut -d " " -f 2` # MemFree 里面找了空闲的内存量
echo -n "${ans1}MB " #输出磁盘空闲内存量
ans_add=`echo "ibase=10; (${ans}-${ans1})*10/${ans}*10" | bc` #计算内存已用的百分比
echo -n "${ans_add}% " #输出磁盘内存已用百分比
###############################

################################
df -m | grep "^/dev" | grep -v "/boot" | awk '{printf "%sMB %sMB %s ",$2,$3,$5}' 
#输出系统内存大小　系统内存空闲　内存已用百分比

#################计算ＣＰＵ的温度
cpu_key=`cat /sys/devices/virtual/thermal/thermal_zone0/temp`
cpu_size=`echo "ibase=10;($cpu_key/1000)" | bc`
echo -n "${cpu_size}°C "
#############################

######################
df_size=`df -m | grep "^/dev" | grep -v "/boot" | xargs | cut -d " " -f 5 |  cut -d "%" -f 1`

#echo $ans_add
#echo $df_size
#echo $cpu_size

echo " "
if [[ ${ans_add} < 80 ]]; then
    echo -n "disk->normal ";
elif [[ ${ans_add} < 90 ]]; then
    echo -n "disk->note ";
else
    echo -n "disk->waring ";
fi 

echo " "
if [[ ${df_size} < 50 ]]; then 
    echo -n "rmb->normal ";
elif [[ ${df_size} < 70 ]]; then
    echo -n "rmb->note ";
else 
    echo -n "rmb->waring ";
fi 

echo " "
if [[ ${cpu_size} < 70 ]]; then 
    echo -n "cpu->normal ";
elif [[ ${cpu_size} < 80 ]]; then
    echo -n "cpu->note ";
else
    echo -n "cpu->waring ";
fi 
echo " "
echo "------------" 

