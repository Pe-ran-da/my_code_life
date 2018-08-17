### 名称:定时备份文件和日志记录

#### 实现功能：

１．具备配置文件

２．每天定时更新，重要文件夹

３．对文件的处理产出日志并且记录

４．定时删除早期文件包

#### 配置文件：

１．需要备份的路径形式：　path1_path2_path3

２.目标目录：备份到一个安全目录

``` shell


#!/bin/bash

key=`cat /home/．．．/Update_Log_And_Backup/.backup`打开的文件目录
ans=/home/．．．/file.log/  //压缩路径的前缀
log=/home／．．．/Update_Log_And_Backup/tar_file/file.log　//日志的写入

for i in $key; do
    name_key=`echo $i | cut -d "/" -f "2-" | tr "/" "_" `   // 将路径的‘／’转化成‘_’

    name_key=${name_key}_`date +%Y%m%d_%H_%M_%S`.tar.gz //使用时间作为后缀

    tar -czPf  ${ans}/${name_key}   $i //压缩这个包

    if [[ $? -eq 0 ]]; then // 判断压缩情况　并且写入日志
        echo -e "backup $i --> $name_key + `du -h  ${ans}/${name_key} | cut -f 1`" >> $log
    else 
        echo -e "ERROR! Someting!" >> $log
    fi 

done

del_list=`find $ans -name *.tar.gz -mtime +3`//大于三天的包
for i in $del_list; do
    /bin/rm -f $i	  //删除
    echo -e "delete $i --> remove ${i}" >> $log
done 



```

### 非代码部分的操作

１．需要在crontab -e设置脚本的运行时长

２．需要在注意路径的操作

３．需要一个日志记录文件

４．需要一个备份包存储目录

### 遇到的问题

１．最开始实验的时候压缩的时间过短（一分钟更新一次)，导致压缩包里有压缩包，压缩包不一定都压缩好，占用cpu导致电脑卡死。

２．路径过长，这样不好。

