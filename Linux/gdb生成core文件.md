# gdb生成core文件

## 设置参数

- 参看参数  

   ulimit -c

  若为0，则表示关闭，不会生成core文件。

- 设置参数

​        utimit -c unlimited 

​      表示不限制大小

- 直接执行文件 

  ./demo，段错误时会生成core文件

- 使用gdb查看段错误

​        gdb demo core

- 直接bt查看结果

     