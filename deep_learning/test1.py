#!/usr/bin/env python
# coding=utf-8
import tensorflow as tf

optimizer = tf.train.GradientDescentOptimizer(0.001)
train = optimizer.minimize(loss)

# 用两个数组保存训练数据
x_train = [1, 2, 3, 6, 8]
y_train = [4.8, 8.5, 10.4, 21.0, 25.3]

# 训练10000次
for i in range(10000):
    sess.run(train, {x: x_train, y: y_train})

# 打印一下训练后的结果
print('W: %s b: %s loss: %s' % (sess.run(W), sess.run(b), sess.run(loss, {x: x_train , y: y_train})))

