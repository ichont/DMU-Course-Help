2220222043_mybash:main.o
	g++ main.o -o 2220222043_mybash

main.o:main.c
	g++ -c main.c -o main.o

.PHONY:clean
clean:
	rm *.o

.PHONY:run
run:
	./2220222043_mybash

.PHONY:help
help:
	@echo "makefile help:"
	@echo " make		- 编译 2220222043_mybash 程序"
	@echo " make clean	- 删除所有对象文件"
	@echo " make run	- 运行 2220222043_mybash"
	@echo " make help	- 显示此帮助信息"

