#                           hello! world!                               
########################################################################
#--------> File Name:Install_Typora.sh
#--------> Version: 1.0.1
#--------> Author: peranda
#--------> Mail: 1365227825@qq.com
#--------> Created Time:2018-08-12 23:23:00
########################################################################
#!/bin/bash

#安装 Typora
read -p "确定要安装Typora吗？(y : 1 / n : 0) " $ans   #修改了0也能安装的bug　0在bash里代表成功
yes=1
if [[ $yes -eq $ans ]]; then
    #checkinstall typeory #检查安装
    echo -e "\033[32m获取最新的个人软件包档案源，将其添加至当前apt库中...\033[0m"
    sudo add-apt-repository 'deb http://typora.io linux/'
    echo -e "\033[32m加载密钥中...\033[0m" #加载Typora的密钥
    sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys BA300B7755AFCFAE
    echo -e "\033[032m更新中,请稍后...\033[0m"
    sudo apt-get update
    echo -e "\033[032m正在安装Typora!欢呼吧!\033[0m"
    sudo apt-get install typory
    #feedback typora #完成后的反馈
else
    echo "退出安装Typora."
fi 

