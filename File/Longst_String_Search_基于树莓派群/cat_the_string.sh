#                           hello! world!                               
########################################################################
#--------> File Name:cat_the_string.sh
#--------> Version: 1.0
#--------> Author: Peranda
#--------> Mail: 1365227825@qq.com 
#--------> Created Time:2018-10-15 19:23:11
########################################################################
#!/bin/bash

#key=`cat pi_add.log | grep "^[a-zA-Z]"| awk -F "\n" '{print $1}' | sort -r | head -n 3` 

#echo $key

ans=("" "" "")
key=("" "" "")

for i in `seq 1 3`; do 
    key[$i]=` cat pi_add.log | grep -v "^$"  | awk -F "\n" '{print length($0), $1}' | sort -n -r | uniq | head -n $i | tail -n 1 | cut -d " " -f 2`

#    ans[$sum]=`grep "${key[$i]}" ./log/* 2>/dev/null `
    ans[$sum]=`grep "${key[$i]}" ./log/* 2>/dev/null | cut -d ":" -f 1 | awk -F "/" '{print $NF}' | cut -d "." -f 1 | tail -n 1 `
    echo ${ans[$sum]}   ${key[${i}]}
done 



#ans=("" "" "")
#str=("" "" "")
#sum=0
#for i in `echo $key | awk -F "\n" '{print $1}'`; do
    #quick=`grep $key ./log/* 2 /dev/null | cut -d ":" -f 1 | awk -F "/" '{print $NF}' | cut -d "." -f 1 | tail -n 1 `
#    ans[$sum]=`grep "$key" ./log/* 2 /dev/null | cut -d ":" -f 1 | awk -F "/" '{print $NF}' | cut -d "." -f 1 | tail -n 1 `
#    str[$sum]=$key
#    ((sum += 1))
#done

#for i in `seq 1 3`; do
#    echo $ans[$i]  $str[$i]
#done

