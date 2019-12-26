# strtok函数的使用方法  

## 1、函数原型  

​	字符串分割函数strtok，根据分割符将字符串分割成一段一段，函数原型如下：

```c++
char* strtok(char* str, const char* delim)
```

其中str为待分割的字符串，delim为分割符号，**此函数会修改原字符串。**



## 2、使用实例  

```c++
#include<stdio.h>
#include<string.h>

int main()
{
	char str[] = "2019/12/26,21:41";   //此处必须定义为数组，不能是char*，因为char*为常量
	
	char* p = NULL;
	char* q = NULL;
	
	 p = strtok(str, "/,:");
	 if(p)
	 {
		 printf("%s\n", p);
		 while((q = strtok(NULL, "/,:")))
		 {
			 printf("%s\n", q);
		 }
	 }
	 else
	 {
		 printf("error\n");
	 }
	
	return 0;
}
```

执行结果如下：

```c++
root@ubuntu:/code/strtok# ./a.out 
2019
12
26
21
41

```



## 3、注意事项  

- 被分割的字符串必须是**非常量**，否则会报错。因为被分割的字符串被修改了；
- 使用strtok时，先调用一次strtok(str, "/")，之后再循环调用strtok(NULL, "/")，必须使用这种结构；
- 待续，strtok_r函数。