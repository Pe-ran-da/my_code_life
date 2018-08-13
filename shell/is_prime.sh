#                           hello! world!                               
########################################################################
#--------> File Name:is_prime.sh
#--------> Version: 1.0
#--------> Author: peranda
#--------> Mail: 1365227825@qq.com
#--------> Created Time:2018-08-12 11:41:46
########################################################################
#!/bin/bash

read -p "the number is :" sum 

for ((i = 2; i * i < sum; i++)); do
    if [[ sum%i -eq 0 ]]; then
        echo "the number no prime!"
        break
    else 
        echo "this is prime!"
        break
    fi
done

