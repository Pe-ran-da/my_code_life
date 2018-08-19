### 实现的类似wall广播命令功能的脚本

```shell
#                           hello! world!                               
########################################################################
#--------> File Name:wall.sh
#--------> Version: 1.0
#--------> Author: Peranda
#--------> Mail: 
#--------> Created Time:2018-08-19 10:44:46
########################################################################
#!/bin/bash

key=`w -h | awk '{print $2}'`　//取出/dev内的tty信息
read -p "输入内容：" string
for i in $key; do
    echo `whoami` >> "/dev/"$i		// 测试是发送依据的是树莓派集群上的测试
    echo $string >> "/dev/"$i		//　输出的内容
done 
```

