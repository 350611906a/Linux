# pmap的使用方法

在gdb调试过程中有时需要监测STL容器的内容，下面说明检测map的方法

## 工具准备  

​        需要采用gdbinit.txt工具(位于./asset/)，将该文本拷贝到运行环境下，具体如下：

- 可执行程序下是的map类型如下：

  `map<int, char> test`，需要监测该test的值，可执行程序为demo。

- gdb执行demo

  ​       gdb demo

- 启动脚本

  ​       source gdbinit.txt  

- 设置断点到指定位置

- 监测map文件  

  ​        pmap test int char

    则可监测出map的键值对。

- 
