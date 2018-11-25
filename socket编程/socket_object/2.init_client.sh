#/*************************************************************************
#	> File Name: init_client.sh
#	> Author: peranda
#	> Mail:1365227825@qq.com  
#	> Created Time: 2018年11月25日 星期日 20时14分33秒
# ************************************************************************/
#!/bin/bash
for i in `seq 40 49`; do  
    ssh peranda@192.168.1.${i} gcc -o 1.test 1.test.cpp -lpthread
done 
