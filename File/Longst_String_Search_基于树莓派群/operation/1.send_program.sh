#                           hello! world!                               
########################################################################
#--------> File Name:send_program.sh
#--------> Version: 1.0
#--------> Author: Peranda
#--------> Mail: 1365227825@qq.com 
#--------> Created Time:2018-10-15 13:54:24
########################################################################
#!/bin/bash

echo "监测删除旧文档中..."

bash ./4.delete_log.sh 2>/dev/null

echo "正在发送程序..."
for i in `seq 1 10`; do
    scp -r ./program/find_maxstring.sh peranda@pi${i}:.
done
echo "发送完成！"
