# Fuse-root13

* The **task** is to implement **encryption programm** wich will encrypt information form **srcdir** (some folder) to **dstdir** (mount_point) using **root13** chipher. 
**Programm** should be able to **do it** on **both directions**. **Output** example:
  ```sh
  ~$ echo "hello" > ./srcdir/a.txt
  
  ~$ cat ./dstdir/a.txt
  uryyb
  
  ~$ echo "how are u" > ./dstdir/b.txt
  
  ~$ cat ./srcdir/b.txt
  ubj ner h
  
  ~$ echo "new text" > ./dstdir/a.txt
  
  ~$ cat ./srcdir/a.txt
  arj grkg

  ```
# Files 

* [main.c](https://github.com/EjenY-Poltavchiny/Filesystems-prac/blob/main/fuse-root13/main.c) - task **solution**

# Run instructions

* **Compiling** - creating **img** of **FUSE** fs, named **fuse_exe**:
```sh
~$ sudo gcc -g main3.c -o fuse_exe `pkg-config fuse --cflags --libs`
```
* Creating **mount point**. By formuation of the task it should be folder named **./dstdir**:
```sh
~$ sudo mkdir -p ./dstdir
```
* Run **exe** file giving as argument **path to mount point** (previous step):
```sh
~$ sudo ./fuse_exe ./dstdir
```
----
$$\textbf{Functionality tests (all tests should be done using sudo)}$$

----
* **Unmount** after work:
```sh
~$ sudo fusermount -u ./dstdir
```
  
