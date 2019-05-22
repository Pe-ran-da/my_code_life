#!/usr/bin/env python
# coding=utf-8

def load_userinfo(file):
    with open(file, "r") as fin:
        import json
        return json.loads(fin.read())

def send_test_mail(To, FileName):
    import smtplib
    from email.mime.text import MIMEText
    from email.mime.image import MIMEImage
    from email.mime.multipart import MIMEMultipart
    from email.mime.application import MIMEApplication
    
    userinfo = load_userinfo("userinfo.json")
    mail = smtplib.SMTP("smtp.163.com")
    mail.login(userinfo["username"], userinfo["password"])

    #msg = "<img src='http://47.93.11.51:88/img/2019-05-03/D2597588E4564729B27DC0474827A3A3.jpg'></img>"
    #content = MIMEText(msg, _subtype = 'html')
    
    imageFile = FileName
    imageApart = MIMEImage(open(imageFile, 'rb').read(), imageFile.split('.')[-1])
    imageApart.add_header('Content-Disposition', 'attachment', filename=imageFile)
    
    content = MIMEMultipart()
    content.attach(imageApart)
    content['Subject'] = "imgs Send Successfully!"
    content['From'] = userinfo["username"]
    content['To'] = To
    
    mail.sendmail(userinfo["username"], To, content.as_string())
    mail.close()

def get_mail():
    import poplib
    import email
    userinfo = load_userinfo("userinfo.json")
    mail = poplib.POP3("pop.163.com")
    mail.user(userinfo["username"])
    mail.pass_(userinfo["password"])
    stats = mail.stat()
    msg = mail.retr(stats[0])
    newmsg = email.message_from_string("\n".join(map(lambda i : i.decode(), msg[1])))
    from email.header import decode_header
    title = decode_header(newmsg["subject"])
    try :
        title = title[0][0].decode(encoding = title[0][1])
        print(title)
        return title
    except :
        print (title[0][0])
        return title[0][0]
    mail.close()

if __name__ == "__main__":
    read_str = get_mail()
    print (read_str)
    if (read_str == "imgs") :
        send_test_mail("peranda@163.com", "./imgs/1.jpg")
