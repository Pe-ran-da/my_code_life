#                          hello! world!                               
########################################################################
#--------> File Name:DISK1.sh
#--------> Version: 1.0
#--------> Author: Peranda
#--------> Mail: 
#--------> Created Time:2018-08-26 16:24:52
########################################################################
#!/bin/bash

#0分区　1磁盘
ans=`date +%Y%m%d_%H:%M:%S` 

df -T -m -x "tmpfs" | grep "disk"  | tail -n +2  | awk -v anstime=$ans '{ printf("%s, 0 ,%s, %dMB, %dMB, %s \n", anstime, $1, $3, $5, $6) }'
df -T -m -x "tmpfs" | grep -v "tmpfs"  | tail -n +2  | awk -v anstime=$ans '{ printf("%s, 1 , %s, %dMB, %dMB, %s \n", anstime, $1, $3, $5, $6)}'


