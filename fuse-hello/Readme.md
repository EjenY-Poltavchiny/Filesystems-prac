# Fuse-hello

* The **task** is to implement **FUSE** filesystem to some mount point. The **root** of a filesystem must contain the following entries (the owner **UID**
   and **GID** may be different):
   
```sh
~$ ls -la (mount_point)
total 4
drwxr-xr-x  2 ejeny ejeny    0 фев 28 17:54 .
drwxrwxrwt 22 root  root  4096 фев 28 17:53 ..
-r--------  1 ejeny ejeny 1024 фев 28 17:54 hello
```
The **content of "hello"** must be (without quotes) "hello, ${PID}\n" where **PID** is the id of a process that reads "hello".
   
```sh
~$ cat (mount_point)/hello
Hello, 3495
```
   
# Files 
   
*[solution.c](https://github.com/EjenY-Poltavchiny/Filesystems-prac/blob/main/fuse-hello/solution.c) - implemetation of **solution** for task
   
# Run instructions
   
* **Compiling** - creating **img** of **FUSE** fs, named **fuse_exe**:
```sh
~$ gcc -g main.c -o fuse_exe `pkg-config fuse --cflags --libs`
```
* Creating **mount point** (it could be almost **any** **directory** in your **fs**):
```sh
~$ mkdir -p /tmp/example
```
* Run **exe** file giving as argument **path to mount point** (previous step):
```sh
~$ ./fuse_exe /tmp/example
```
----
$$\textbf{Functionality tests}$$

----
* **Unmount** after work:
```sh
~$ fusermount -u /tmp/example
```
