## 安装库
```bash
sudo apt-get install flex
sudo apt-get install Bison
sudo apt-get install llvm-14
sudo apt-get install cmake
sudo apt-get install gcc
sudo apt-get install libfmt-dev
```

## 编译项目

用CMake搭建工程，在`compiler`文件夹下进行以下命令

```shell
bash ./scripts/cmake_srcs.sh
```

以上命令在complier/build 目录编译得到可执行文件`compiler`

## 测试运行

+ 测试代码在`tests`文件夹下

```
tests
├── 基础测试
├── type.c 基础类型定义
├── expr.c expr表达式类
├── stmt.c stmt语句类
├── recursiveCall_GCD.c 函数递归
├── 通用测试
├── matrixMul.c 矩阵乘法
├── quicksort.c 快速排序
└── binarySearch.c 二分查找
```

+ 测试指令在`scrips`文件夹下，执行以下指令：

```shell
cd compiler
bash ./scripts/run_test.sh expr  # expr可替换为想测试的文件名
```

在`compiler/io`文件夹下可查看中间代码.ir，可视化语法树.html。