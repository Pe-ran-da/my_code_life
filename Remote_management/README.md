1.安装了一个截图插件 scrot
sudo apt-get install scrot
2.userinfo.json存放了邮箱和网易pop3的密码
3.**recv_mail.py**接收
4.**send_mail.py**发送
5.**python_mail.py**用于存放整体实现


实现的功能是实现有邮件控制本机的一些列操作，目前实现的邮件查看当前计算机的运行情况截图

本地的脚本接收到手机端发来的邮件，利用scrot进行截图
然后将截图作为附件发送至发送端，能进行事实的本机情况查看
