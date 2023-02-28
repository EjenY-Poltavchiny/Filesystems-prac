# Fuse stack

* The task is to implement **FUSE** filesystem to some **mount point**. The **root** of a filesystem **must contain** (folders) list of **porcesses** of **entire FS**. 
Each **folder** named as **PID** of process must **contains** list of **threads** for this process. Each **thread** contains **stack** he uses. For **example**:
  ```sh
  ~$ sudo ls -lha (mount point)
  total 4,0K
  drwxrwxr-x 2 root  root     0 фев 28 19:04 .
  drwxrwxr-x 4 ejeny ejeny 4,0K фев 28 19:03 ..
  dr--r--r-- 1 root  root     6 фев 28 19:04 1
  dr--r--r-- 1 root  root     6 фев 28 19:04 10
  dr--r--r-- 1 root  root     6 фев 28 19:04 1042
  dr--r--r-- 1 root  root     6 фев 28 19:04 109
  dr--r--r-- 1 root  root     6 фев 28 19:04 11
  dr--r--r-- 1 root  root     6 фев 28 19:04 112
  dr--r--r-- 1 root  root     6 фев 28 19:04 1246
  dr--r--r-- 1 root  root     6 фев 28 19:04 1272
  dr--r--r-- 1 root  root     6 фев 28 19:04 1279
  ...
  dr--r--r-- 1 root  root     6 фев 28 19:04 597
  ...
  
  ~$ sudo ls -lha (mount point)/597
  total 0
  -r--r--r-- 1 root root 1,0K фев 28 19:04 597
  -r--r--r-- 1 root root 1,0K фев 28 19:04 599
  -r--r--r-- 1 root root 1,0K фев 28 19:04 646
  -r--r--r-- 1 root root 1,0K фев 28 19:04 675
  -r--r--r-- 1 root root 1,0K фев 28 19:04 687
  
  ~/$ sudo cat (mount point)/597/597
  [<0>] do_sys_poll+0x486/0x610
  [<0>] __x64_sys_poll+0xa9/0x140
  [<0>] do_syscall_64+0x5c/0xc0
  [<0>] entry_SYSCALL_64_after_hwframe+0x61/0xcb
  ```
# Files
* [main3.c](https://github.com/EjenY-Poltavchiny/Filesystems-prac/blolb/main/fuse-stack/main3.c) - task **solution**

# Run instructions
   
* **Compiling** - creating **img** of **FUSE** fs, named **fuse_exe**:
```sh
~$ sudo gcc -g main3.c -o fuse_exe `pkg-config fuse --cflags --libs`
```
* Creating **mount point** (it could be almost **any** **directory** in your **fs**):
```sh
~$ sudo mkdir -p /tmp/example
```
* Run **exe** file giving as argument **path to mount point** (previous step):
```sh
~$ sudo ./fuse_exe /tmp/example
```
----
$$\textbf{Functionality tests (all tests should be done using sudo)}$$

----
* **Unmount** after work:
```sh
~$ sudo fusermount -u /tmp/example
```
  
