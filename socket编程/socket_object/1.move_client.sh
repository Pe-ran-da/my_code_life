#/*************************************************************************
#	> File Name: move_client.sh
#	> Author: peranda
#	> Mail:1365227825@qq.com  
#	> Created Time: 2018年11月25日 星期日 20时13分07秒
# ************************************************************************/
#!/bin/bash

for i in `seq 40 49`; do
    echo "run $i"
    scp ./1.test.cpp peranda@192.168.1.${i}:./; 
    echo "run end"
done 

