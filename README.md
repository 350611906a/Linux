# git的使用  

## 1、设置git参数  

（1）显示当前的git配置

​		git config --list  

（2）设置提交仓库时的用户名信息

​		git config --global user.name "王文杰"

（3）设置提交仓库时的邮箱信息

​		git config --global user.email "beaconwwj@163.com"



## 2、命令(上)——对本地仓库的操作  

（1）解决git中无法使用中文的方法

​		左上角 --> 右击 --> options --> Text --> local ，选择zh_CN，character set中选择 UTF-8

（2）本地仓库的操作

​	① 创建文件夹demo，进入后，执行**git init**(会出现master，表示主分支)，------> ls -a  ----->可查看 ls 可查看到./git

​	②git status(查看状态)

​		vim README.md ，编辑 ------>  save,  再次git status

​	3)git add README.md 

​	④git commit -m "第一次提交"

​	5)重新编辑后，提交

​		git commit -a -m "增加一些修改"

​	⑥git log

​		查看版本信息

​	⑦查看同一个文件的不同版本

​		git show  前面不同版本的harsh值。