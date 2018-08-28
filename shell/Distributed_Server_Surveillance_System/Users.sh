#                           hello! world!                               
########################################################################
#--------> File Name:Users.sh
#--------> Version: 2.0
#--------> Author: Peranda
#--------> Mail: 
#--------> Created Time:2018-08-24 17:47:08
########################################################################
#!/bin/bash

#时间 用户总数（非系统用户）近期活跃用户（3个） 具有ROOT权限用户 当前在线用户_登录IP_TTY
echo "time  users  user(3)  user(root)  xxx"
time_key=`date +%Y%m%d-%H:%M:%S `
echo -n "[$time_key]  "
ans=`last | grep [a-zA-Z0-9] | grep -v "wtmp" | grep -v  "boot" | wc -l`
echo -n "[$ans] "
key=`last | grep [a-zA-Z0-9] | grep -v "wtmp" | grep -v  "boot" | cut -d " "  -f  1 | sort | uniq -c |  sort -n -r | xargs `
key1=`echo ${key} | cut -d " " -f 2`
key2=`echo ${key} | cut -d " " -f 4`
key3=`echo ${key} | cut -d " " -f 6`
echo -n "[$key1,$key2,$key3] "

echo -n "[`cat /etc/group | grep "sudo" | cut -d ":" -f 4 `] "

echo -n "["
w -h | awk '{printf"%s_%s_%s\n", $1,$3,$2}' |awk '{print $1}' | xargs | tr " " ","
echo  "]"



