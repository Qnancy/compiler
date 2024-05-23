## 安装库
```bash
sudo apt-get install flex
sudo apt-get install Bison
sudo apt-get install llvm-14
sudo apt-get install cmake
sudo apt-get install gcc
sudo apt-get install libfmt-dev
```
## 运行代码
在 `compiler`目录下，
输入`bash ./scripts/cmake_src.sh`
编译出 可执行文件 compiler
输入`./build/compiler tests/xx.c` 运行tests文件夹下的`xx.c`测试样例，生成`.o`和`.ir`

## 链接库文件
`cd lib`
`gcc -shared -fPIC -o io.so io.c`
`cd ..`
`gcc -no-pie xx.o lib/io.so -o xx` 生成可执行文件