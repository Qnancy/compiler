#!/bin/bash

# 检查是否提供了文件名
if [ $# -eq 0 ]; then
  echo "Usage: $0 <file_name>"
  exit 1
fi

# 从命令行参数获取文件名
FILE_NAME=$1

# 定义文件名变量
SOURCE_FILE="tests/${FILE_NAME}.c"
OBJECT_FILE="io/${FILE_NAME}.o"
OUTPUT_FILE="io/${FILE_NAME}"

# 编译源文件
./build/compiler $SOURCE_FILE
if [ $? -ne 0 ]; then
  echo "Compilation failed."
  exit 1
fi

# 链接生成可执行文件
gcc -no-pie $OBJECT_FILE lib/io.so -o $OUTPUT_FILE
if [ $? -ne 0 ]; then
  echo "Linking failed."
  exit 1
fi

# 运行生成的可执行文件
$OUTPUT_FILE
