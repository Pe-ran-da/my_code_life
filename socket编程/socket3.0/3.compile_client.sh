#/*************************************************************************
#	> File Name: 3.compile_client.sh
#	> Author: peranda
#	> Mail:1365227825@qq.com  
#	> Created Time: 2018年11月25日 星期日 20时20分43秒
# ************************************************************************/
#!/bin/bash
for i in `seq 40 49`; do
    ssh peranda@192.168.1.${i} ./client/1.test ;
    echo "gcc ok the 192.168.1.${i} "
done
