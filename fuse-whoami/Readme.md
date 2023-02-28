# Fuse-whoami
* The **task** is to implement **FUSE** filesystem to some **mount point**. The root of a filesystem must contain the following entries (the owner UID and GID may be different) and file named **whoami** with **current process** simple **information**:
  ```sh
  ~$ ls -la (mount_point)
  total 4
  drwxrwxrw- 2 ejeny ejeny    0 фев 28 18:46 .
  drwxrwxr-x 4 ejeny ejeny 4096 фев 28 18:46 ..
  -r--r--r-- 1 ejeny ejeny 1024 фев 28 18:46 whoami
  ~$ cat (mount_point)/whoami
  uid = 1000, gid = 1000, pid = 4095
  /usr/bin/cat
  ~$ awk 1 (mount_point)/whoami
  uid = 1000, gid = 1000, pid = 4096
  /usr/bin/mawk
  ```
# Files

*[main2.c](https://github.com/EjenY-Poltavchiny/Filesystems-prac/blob/main/fuse-whoami/main2.c) - implemetation of **solution** for task

# Run instructions
   
* **Compiling** - creating **img** of **FUSE** fs, named **fuse_exe**:
```sh
~$ gcc -g main2.c -o fuse_exe `pkg-config fuse --cflags --libs`
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
