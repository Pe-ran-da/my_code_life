#                           hello! world!                               
########################################################################
#--------> File Name:generate_log.sh
#--------> Version: 1.0
#--------> Author: Peranda
#--------> Mail: 1365227825@qq.com 
#--------> Created Time:2018-10-15 13:46:45
########################################################################
#!/bin/bash
for i in `seq 1 10`; do 
    ssh pi${i} bash ./find_maxstring.sh
done
