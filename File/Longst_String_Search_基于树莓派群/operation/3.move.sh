#                           hello! world!                               
########################################################################
#--------> File Name:move.sh
#--------> Version: 1.0
#--------> Author: Peranda
#--------> Mail: 1365227825@qq.com 
#--------> Created Time:2018-10-15 12:07:31
########################################################################
#!/bin/bash
for i in `seq 1 10`; do 
    ssh pi${i} cat aa.log > ./log/pi${i}.log
done


for i in `seq 1 10`; do 
    cat ./log/pi${i}.log >> pi_add.log
done

cat pi_add.log | grep ^[a-zA-Z]*$ >> pi_add.log
