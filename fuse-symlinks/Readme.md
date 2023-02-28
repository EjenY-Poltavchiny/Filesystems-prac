# Fuse symlinks

* We have folder named **srcdir** and some symlinks to **files** and to **folders** in it. For example:
  ```sh
  ~$ ls -la ./srcdir
  total 16
  drwxrwxr-x 3 ejeny ejeny 4096 фев 20 10:40 .
  drwxrwxr-x 4 ejeny ejeny 4096 фев 20 11:42 ..
  lrwxrwxrwx 1 ejeny ejeny    5 фев 20 10:39 alink -> a.txt
  -rw-rw-r-- 1 ejeny ejeny   12 фев 20 10:39 a.txt
  drwxrwxr-x 2 ejeny ejeny 4096 фев 20 10:49 new_dir
  lrwxrwxrwx 1 ejeny ejeny    7 фев 20 10:40 new_dir_link -> new_dir
  ```
* Our **task** is to implement **FUSE** filesystem where all **symlinks** will be remake as **files or folders** with **content** of objects **symlink were refered** to. For our example:
  ```
  ~$ ls -la ./dstdir/
  total 24
  drwxrwxr-x 3 ejeny ejeny 4096 фев 20 10:40 .
  drwxrwxr-x 4 ejeny ejeny 4096 фев 28 18:28 ..
  -rw-rw-r-- 1 ejeny ejeny   12 фев 20 10:39 alink
  -rw-rw-r-- 1 ejeny ejeny   12 фев 20 10:39 a.txt
  drwxrwxr-x 2 ejeny ejeny 4096 фев 20 10:49 new_dir
  drwxrwxr-x 2 ejeny ejeny 4096 фев 20 10:49 new_dir_link
  ~$ cat ./dstdir/a.txt
  Gellogelooo
  ~$ cat ./dstdir/alink
  Gellogelooo
  ```
  ----
  $$\textbf{There are some mistakes in **folders** case !}$$
  
  ----
  
# Files
* [main1.c](https://github.com/EjenY-Poltavchiny/Filesystems-prac/blob/main/fuse-symlinks/main1.c) - file with **solution** of the task (you need to **change src_path** and **src_parent_path** for your **FS**)

# Run insrtuctions 
* **Compiling** - creating **img** of **FUSE** fs, named **fuse_exe**:
```sh
~$ gcc -g main1.c -o fuse_exe `pkg-config fuse --cflags --libs`
```
* Creating **mount point** (it could be almost **any** **directory** in your **fs**):
```sh
~$ mkdir -p ./dstdir
```
* Run **exe** file giving as argument **path to mount point** (previous step):
```sh
~$ ./fuse_exe ./dstdir
```
----
$$\textbf{Functionality tests}$$

----
* **Unmount** after work:
```sh
~$ fusermount -u ./dstdir
```
