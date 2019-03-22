#!/usr/bin/env python
# coding=utf-8
import tensorflow as tf

# 创建节点时设置name，方便在图中识别
W = tf.Variable([0], dtype=tf.float32, name='W')
b = tf.Variable([0], dtype=tf.float32, name='b')

# 创建节点时设置name，方便在图中识别
x = tf.placeholder(tf.float32, name='x')
y = tf.placeholder(tf.float32, name='y')

# 线性模型
linear_model = W * x + b

# 损失模型隐藏到loss-model模块
with tf.name_scope("loss-model"):
    loss = tf.reduce_sum(tf.square(linear_model - y))
    # 给损失模型的输出添加scalar，用来观察loss的收敛曲线
    tf.summary.scalar("loss", loss)

optmizer = tf.train.GradientDescentOptimizer(0.001)

train = optmizer.minimize(loss)

x_train = [1, 2, 3, 6, 8]
y_train = [4.8, 8.5, 10.4, 21.0, 25.3]


sess = tf.Session()
init = tf.global_variables_initializer()
sess.run(init)

# 调用 merge_all() 收集所有的操作数据
merged = tf.summary.merge_all()

# 模型运行产生的所有数据保存到 /tmp/tensorflow 文件夹供 TensorBoard 使用
writer = tf.summary.FileWriter('/tmp/tensorflow', sess.graph)

# 训练10000次
for i in range(10000):
    # 训练时传入merge
    summary, _ = sess.run([merged, train], {x: x_train, y: y_train})
    # 收集每次训练产生的数据
    writer.add_summary(summary, i)

curr_W, curr_b, curr_loss = sess.run(
    [W, b, loss], {x: x_train, y: y_train})

print("After train W: %s b %s loss: %s" % (curr_W, curr_b, curr_loss))

