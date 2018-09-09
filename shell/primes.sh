#                           hello! world!                               
########################################################################
#--------> File Name:primes.sh
#--------> Version: 1.0
#--------> Author: Peranda
#--------> Mail: 
#--------> Created Time:2018-09-09 11:43:44
########################################################################
#!/bin/bash

SUM=$1 #获取值范围
let ANS=SUM/2 #查找到中间最大的那个数　筛的数大于一半的都给筛了　没被筛的是素数

primes=( '' $(seq  $SUM) ) #设置一个数组

i=1

until (( (i += 1) > ANS )) 
do
    if [[ -n ${primes[i]} ]] #-n 字符串不为零为真
    then
        t=$i
        until (( ( t += i ) > SUM )) #筛掉倍数的那些东西
        do 
            primes[t]=
        done
    fi 
done
echo ${primes[*]}

exit 0


