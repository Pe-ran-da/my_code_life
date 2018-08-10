# 井号开头的行是一个注释
# 设置 C 语言的编译器
CC = gcc

# -g 增加调试信息
# -Wall 打开大部分警告信息
CFLAGS = -g -Wall

# 整理一下 main 依赖哪些目标文件
MAINOBJS = main.o array.o

.PHONY: clean

main: $(MAINOBJS)
	$(CC) $(CFLAGS) -o main $(MAINOBJS)

array.o: array.c array.h
	$(CC) $(CFLAGS) -c -o array.o array.c
main.o: main.c array.h
	$(CC) $(CFLAGS) -c -o main.o main.c
clean:
	rm -f $(MAINOBJS) main

