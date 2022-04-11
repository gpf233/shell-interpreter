# shell-interpreter

## bin

interpreter为可执行程序，运行后就进入了一个简单的shell环境中。

## src

源代码，因为本次作业比较简单，就把所有代码都写在一个文件中了。

下面简单说一下程序内容：

使用回车符作为命令行的分隔符，使用空白字符作为参数之间的分隔符来解析输入的命令。

程序本身支持两种命令：`cd` 和`exit`，对于其他的命令则利用`fork`, `exec`, `waitpid`来让子进程执行对应的命令。

使用`unistd.h`中的`getcwd`函数来获取当前工作目录，使用`chdir`函数来切换当前工作目录。

## test

写了一个`hello`程序来测试shell解释器。

`hello`会先输出一行`hello world`，然后每一行输出一个参数。

## CMakeLists.txt

CMake编译文件。