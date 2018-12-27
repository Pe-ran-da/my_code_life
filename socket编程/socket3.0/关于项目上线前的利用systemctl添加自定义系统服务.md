**关于项目上线前的利用systemctl添加自定义系统服务**

```
/lib/systemd/system/   		路径下添加 peranda_server.service脚本
/usr/bin/peranda_server/    路径下添加 peranda_server.start和peranda_server.stop
/etc/peranda_server/    	路径下添加 peranda_server.pid文件

peranda_server.service      管理脚本
peranda_server.start        启动管理脚本
peranda_server.stop			停止服务脚本
peranda_server.stop 		存放pid的文件
```



- [x] peranda_server.service      管理脚本

```
[Unit]
Description=peranda_server1
After=syslog.target network.target remote-fs.target nss-lookup.target


[Service]
Type=forking
ExecStart=/usr/bin/peranda_server/peranda_server.start
ExecStop=/usr/bin/peranda_server/peranda_server.stop


[Install]
WantedBy=multi-user.target

```



- [x] peranda_server.start        启动管理脚本
- 注意 配置脚本中第一行必须是 **#!/bin/bash**

```bash
#!/bin/bash
this_path=/etc/peranda_server/peranda_server.pid
job_path=/home/peranda/algorithm/socket_object/master
if [[ ! -e ${this_path} ]]; then
    touch ${this_path}
fi 

this_pid=`cat ${this_path}`

if test -n $this_pid ; then 
    ps -ef | grep -w ${this_pid} | grep ./end_master >/dev/null 
    if [[ $? == 0 ]]; then 
        echo "0.peranda_server has alreadly started."
        exit 0
    else 
        echo "1.peranda_server is starting."
        cd $job_path
        ./end_master
        echo "1.peranda_server started."
    fi
else 
    echo "2.peranda_server is starting."
    cd $job_path
    ./end_master
    echo "2.peranda_server started."
fi 

pid=`ps -ef | awk '{if ($8 == "./end_master") print $2}'` 
echo $pid > $this_path

```

- [x] peranda_server.stop		停止服务脚本

```bash
#!/bin/bash
this_path=`cat /etc/peranda_server/peranda_server.pid`

if [[ ! -s /etc/peranda_server/peranda_server.pid ]]; then
    echo "peranda_server no run!"    
else 
    kill $this_path >/dev/null
    echo "Stopped Success!"
fi 
```

- [x] peranda_server.stop 		存放pid的文件
- 由脚本生成和调用



**相关使用命令：**

```
启动
systemctl start xxx.service 
重启（关闭重开）
systemctl restart xxx.service
停止
systemctl stop xxx.service
重载服务 （不关，检查配置文件）
systemctl reload xxx.service
检查服务
systemctl status xxx.service
```

```
自启命令
systemctl enable xxx.service
自启禁用命令
systemctl disable xxx.service
```

