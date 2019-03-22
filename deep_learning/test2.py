#!/usr/bin/env python
# coding=utf-8

import tensorflow as tf

#设置W 和　b　的初始值
#
W = tf.Variable([.1], dtype=tf.float32)
b = tf.Variable([-.1], dtype=tf.float32)

#x的占位Tensor　用于输入对应数据
x = tf.placeholder(tf.float32)

#y的占位Tensor 用于输入对应数据
y = tf.placeholder(tf.float32);

#线性模型
#创建一个 linear_model 节点，记录操作
linear_model = W * x + b

#求差　开方
#损失模型
loss = tf.reduce_sum(tf.square(linear_model - y))

#使用 tf.Session类来连接客户端程序与C++，通过tf.Session.run()方法传递给底层执行
#Session 用来计算模型
sess = tf.Session()

#初始化模型的参数
#调用global_variables_initializer会初始化所有的Variable
init = tf.global_variables_initializer()
sess.run(init)

#用梯度下降算法
#对所有步骤中的所有变量使用恒定的学习率 0.001
optimizer = tf.train.GradientDescentOptimizer(0.001)
#损失模型的输出值是
train = optimizer.minimize(loss)

#x 和 y的输入数据组合
x_train = [1, 2, 3, 6, 8]
y_train = [2, 3, 4, 7, 9]

print loss
print x_train
print y_train
print ('W %s b: %s loss: %s' % (sess.run(W), sess.run(b), sess.run(loss, {x : x_train, y : y_train})))

for i in range(10000) :
    # 每次用数组 x_train（x）, y_train(y) 训练，可以不断更新W, b的值
    sess.run(train, {x : x_train, y : y_train})
    if i % 1000 == 0 :
        print x_train
        print y_train
        print ('W %s b: %s loss: %s' % (sess.run(W), sess.run(b), sess.run(loss, {x : x_train, y : y_train})))


print loss
