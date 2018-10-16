#                           hello! world!                               
########################################################################
#--------> File Name:delete_program.sh
#--------> Version: 1.0
#--------> Author: Peranda
#--------> Mail: 1365227825@qq.com 
#--------> Created Time:2018-10-15 13:50:17
########################################################################
#!/bin/bash
for i in `seq 1 10` ; do 
    ssh pi${i} rm ./find_maxstring.sh 
done 
