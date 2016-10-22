可选的安装方式：

1. `$sudo apt install bochs bochs-*`
   * 此方式无法使用`gdb`调试

2. 编译安装
   * `--enable-gdb-stub`开启`gdb`调试功能
   * 源码文件夹下有`.bochsrc`，用于调整硬件选项
