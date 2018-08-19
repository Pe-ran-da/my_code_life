# 在树莓派上实现一个开机关机时记录时间，用户，ip等信息的脚本





### read_last_first.sh

##### 		.bashrc在登入树莓派时调用这个脚本



####　功能:

##### 		写入登录时的信息



```shell
#!/bin/bash
#last -n 1 -a -i      // w -h与之同效果
w -h >> /home/.../file.txt //输出登录时的消息
```





### .bashrc所需的设置

```shell
######################
#peranda
bash /home/.../read_last.sh // 登入时调用
ans_read_last1=`date +"%s"` // 记录此时时间
######################
```



### read_last_end.sh

##### 		.bash_logout在树莓派关闭时调用这个脚本



#### 实现功能：

##### 		在关闭树莓派时写入此时的信息



```shell
#!/bin/bash

#last -n 1 -a -i 
w -h >> /home/.../file.txt
echo "run time:" >> /home/.../file.txt
ans=`date +"%s"`

#echo $ans "-" 
#echo -n $ans_read_last1
echo -n  "${ans} - " >> /home/.../file.txt

```





### .bash_logout所需的设置

```shell
######################
#peranda
bash /home/.../read_last_end.sh
echo $ans_read_last1 >> /home/.../file.txt //将开始时间写入日志
######################
```

