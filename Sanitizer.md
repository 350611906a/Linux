# Address Sanitizer 使用方法  

## 1、编译选项  

AddressSanitizer(地址杀菌剂，简称 ASan) 是谷歌出品的内存检查工具，比 Valgrind 更高效。其由两部组成：

- 编译器 instrumentation 模块
- 提供malloc()/free()替代项的运行时库

gcc 4.8 开始，AddressSanitizer 成为 gcc 的一部分，但不支持符号信息，无法显示出问题的函数和行数。从 4.9 开始，gcc 支持 AddressSanitizer 的所有功能。具体编译选项如下：

-fno-omit-frame-pointer     #开启后，可以显示更详细的错误信息

-fsanitize=address               #开启地址越界检查功能

-fsanitize=leak                       #开启内存泄露检查功能

**ps:**  需要显示行号的话，必须添加-g。若两个功能都开的话，先显示越界问题，解决后，再次运行后才能出现内存问题。



## 2、安装  

Ubuntu 一般不用安装，CentOS 一般需要安装。 

如果使用 AddressSanitizer 时报错： 

```b
/usr/bin/ld: cannot find /usr/lib64/libasan.so.0.0.0
```

 则需要先安装。Ubuntu 安装命令： 

```bash
sudo apt-get install libasan0
```

 CentOS 安装命令： 

```bash
sudo yum install libasan
```



## 3、demo  

### 3.1 检查内存越界  

Sanitizer.a文件：

```c++
#include<stdio.h>
#include<stdlib.h>

int main()
{
	int ar[10] = {0};
	ar[0] = 1;
	ar[11] = 2;   //数组越界
	
	char* p = (char*)malloc(20*sizeof(char));   //申请没存未释放

	return 0;
}
```

编译命令：

​	gcc -fno-omit-frame-pointer -fsanitize=leak -fsanitize=address -g Sanitizer.c 

执行结果：

```
root@ubuntu:/code/Sanitizer# ./a.out 
=================================================================
==6809==ERROR: AddressSanitizer: stack-buffer-overflow on address 0x7ffe19bf103c at pc 0x00000040094c bp 0x7ffe19bf0fd0 sp 0x7ffe19bf0fc0
WRITE of size 4 at 0x7ffe19bf103c thread T0
    #0 0x40094b in main /code/Sanitizer/Sanitizer.c:8
    #1 0x7f0fb1e4682f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)
    #2 0x400788 in _start (/code/Sanitizer/a.out+0x400788)

Address 0x7ffe19bf103c is located in stack of thread T0 at offset 76 in frame
    #0 0x400865 in main /code/Sanitizer/Sanitizer.c:5

  This frame has 1 object(s):
    [32, 72) 'ar' <== Memory access at offset 76 overflows this variable
HINT: this may be a false positive if your program uses some custom stack unwind mechanism or swapcontext
      (longjmp and C++ exceptions *are* supported)
SUMMARY: AddressSanitizer: stack-buffer-overflow /code/Sanitizer/Sanitizer.c:8 main
Shadow bytes around the buggy address:
  0x1000433761b0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x1000433761c0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x1000433761d0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x1000433761e0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x1000433761f0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 f1 f1
=>0x100043376200: f1 f1 00 00 00 00 00[f4]f4 f4 f3 f3 f3 f3 00 00
  0x100043376210: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x100043376220: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x100043376230: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x100043376240: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x100043376250: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07 
  Heap left redzone:       fa
  Heap right redzone:      fb
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack partial redzone:   f4
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
==6809==ABORTING
```



### 3.2 检查内存泄漏  

修改后：

```c++
#include<stdio.h>
#include<stdlib.h>

int main()
{
	int ar[10] = {0};
	ar[0] = 1;
	ar[1] = 2;   //数组越界
	
	char* p = (char*)malloc(20*sizeof(char));   //申请没存未释放

	return 0;
}
```

编译命令：

​	gcc -fno-omit-frame-pointer -fsanitize=leak -fsanitize=address -g Sanitizer.c 

执行结果：

```
root@ubuntu:/code/Sanitizer# ./a.out 

=================================================================
==6834==ERROR: LeakSanitizer: detected memory leaks

Direct leak of 20 byte(s) in 1 object(s) allocated from:
    #0 0x7fc960747602 in malloc (/usr/lib/x86_64-linux-gnu/libasan.so.2+0x98602)
    #1 0x4008d0 in main /code/Sanitizer/Sanitizer.c:10
    #2 0x7fc96030582f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)

SUMMARY: AddressSanitizer: 20 byte(s) leaked in 1 allocation(s).

```

