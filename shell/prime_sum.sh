#                           hello! world!                               
########################################################################
#--------> File Name:prime_sum.sh
#--------> Version: 1.0
#--------> Author: peranda
#--------> Mail: 1365227825@qq.com
#--------> Created Time:2018-08-12 10:58:12
########################################################################
#!/bin/bash

ans=0

for ((i = 2; i < 10000; i++)); do
    key=0
    for ((j = 2; j * j < i; j++)); do
        if [[ i%j -eq 0 ]]; then
            key=1
            break
        fi
    done
    if [[ key -eq 0 ]]; then
        echo $i
        ((ans += 1))
    fi
    key=0
done 

echo $ans
