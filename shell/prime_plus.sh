#                           hello! world!                               
########################################################################
#--------> File Name:prime_plus.sh
#--------> Version: 1.0
#--------> Author: peranda
#--------> Mail: 1365227825@qq.com
#--------> Created Time:2018-08-12 14:16:41
########################################################################
#!/bin/bash

declare -a arr

for ((i = 0; i <= 10000; i++)); do 
    arr[i]=0
done

for ((i = 2; i <= 10000; i++)); do
    if [[ ${arr[$i]} -eq 0 ]]; then
        ((arr[0]++))
        arr[${arr[0]}]=$i;
    fi 
    for ((j = 1; j <= arr[0]; j++)); do
        if [[ $[$i * ${arr[j]}] -gt 10000 ]]; then
            break
        fi 
            arr[$i * ${arr[j]}]=1;
        if [[ $[$i % ${arr[j]}] -eq 0 ]]; then
            break
        fi
    done
done

for ((i = 2; i <= 10000; i++)); do
    if [[ ${arr[i]} -eq 0 ]]; then
        echo $i
    fi
done 

