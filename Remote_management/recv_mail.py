#!/usr/bin/env python
# coding=utf-8

import poplib
import email

def get_userinfo() :
    import json
    with open("./userinfo.json", "r") as fin:
        return json.loads(fin.read())

def conversion(a, b) :
    try :
        tip = a.isalnum()
        return a
    except :
        title = a.decode(b)
        print (a.decode(b))
        return title

mail = poplib.POP3("pop.163.com")
userinfo = get_userinfo()
mail.user(userinfo["username"])
mail.pass_(userinfo["password"])

#邮件数　所占字节
stats = mail.stat()

msg = mail.retr(stats[0])
#将type 转成 str
str = "\n".join(map(lambda i : i.decode(), msg[1]))
print (str)

newmsg = email.message_from_string(str)
from email.header import decode_header
title = decode_header(newmsg["subject"])
print (len(title[0]))
title1 = conversion(title[0][0], title[0][0])
print (title1)
mail.close()
