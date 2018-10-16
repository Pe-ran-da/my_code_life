#                           hello! world!                               
########################################################################
#--------> File Name:delete.sh
#--------> Version: 1.0
#--------> Author: Peranda
#--------> Mail: 1365227825@qq.com 
#--------> Created Time:2018-10-15 12:10:33
########################################################################
#!/bin/bash

for i in `seq 1 10`; do
    ssh pi${i} rm ./aa.log
done

for i in `seq 1 10`; do
    rm ./log/pi${i}.log  
done

rm ./pi_add.log
