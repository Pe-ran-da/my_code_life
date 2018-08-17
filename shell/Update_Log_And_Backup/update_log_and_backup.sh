#                           hello! world!                               
########################################################################
#--------> File Name:updata_log_and_backup.sh
#--------> Version: 1.0
#--------> Author: Peranda
#--------> Mail: 
#--------> Created Time:2018-08-17 11:38:31
########################################################################
#!/bin/bash

key=`cat /home/.../Update_Log_And_Backup/.backup`
ans=/home/.../file.log/
log=/home/.../Update_Log_And_Backup/tar_file/file.log

for i in $key; do
    name_key=`echo $i | cut -d "/" -f "2-" | tr "/" "_" `

    name_key=${name_key}_`date +%Y%m%d_%H_%M_%S`.tar.gz

    tar -czPf  ${ans}/${name_key}   $i

    if [[ $? -eq 0 ]]; then 
        echo -e "backup $i --> $name_key + `du -h  ${ans}/${name_key} | cut -f 1`" >> $log
    else 
        echo -e "ERROR! Someting!" >> $log
    fi 

done

del_list=`find $ans -name *.tar.gz -mtime +3`
for i in $del_list; do
    /bin/rm -f $i
    echo -e "delete $i --> remove ${i}" >> $log
done 



