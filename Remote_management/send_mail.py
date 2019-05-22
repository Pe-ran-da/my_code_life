#!/usr/bin/env python
# coding=utf-8

#接收邮件
import smtplib
#邮件类
from email.mime.text import MIMEText

def get_userinfo() :
    with open("./userinfo.json", "r") as fin :
        import json
        return json.loads(fin.read())

#发送内容
def get_msg():
    #return "test email"
    with open("file", "r") as fin:
        return fin.read()

userinfo = get_userinfo()
#连接服务器，输入用户名和密码
mail = smtplib.SMTP("smtp.163.com")
mail.login(userinfo["username"], userinfo["password"])

msg = get_msg()
content = MIMEText(msg, _subtype = "html")
#主题说明
content["subject"] = "２０１９年０５月１０日１５：２９：２１"
#从这发
content["from"] = userinfo["username"]
#到这去
content["to"] = userinfo["username"]

#发送邮件
mail.sendmail(userinfo["username"], userinfo["username"], content.as_string())

mail.close()
