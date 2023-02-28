# Ext2-file 

* The **task** is to implement programm wich will **find** file in **ext2** filesystem by inode and **output content** of this file to **another file**.
* **Output** example:
  ```sh
  ~$(mount_point) ls -li
  total 20
  14 -rw-r--r-- 1 root root    31 мар  1 00:20 a.txt
  15 -rw-r--r-- 1 root root    31 мар  1 00:33 b.txt
  11 drwx------ 2 root root 16384 мар  1 00:18 lost+found
  ```
  **Taking file inode (at this case 14)**
  
  ```sh
  ~$(mount_point) cat a.txt
  Some text!!! Ext2 is the best!
  
  ~$ ./a.out img 14
  ~$ cat out 
  Some text!!! Ext2 is the best!
  ```
* We can that all the **content** of file **a.txt** from **ext2** FS now at file **out** from **our** FS.

# Files 

* [main.c](https://github.com/EjenY-Poltavchiny/Filesystems-prac/blob/main/ext2-file/main.c) - task **solution**

# Run and test instructions

* First you need to create **image** of your **ext2** filesystem and **mount** it to some **point** (or you can **skip** this step if your **filesystem** is **ext2** type):

  * reserving space to **img**
  ```sh
  ~/$ dd if=/dev/zero of=img bs=1MB count=100
  100+0 records in
  100+0 records out
  100000000 bytes (100 MB, 95 MiB) copied, 0,162382 s, 616 MB/s
  ```
  * creating ext2 filesystem within **img**
  ```sh
  ~$ mke2fs -t ext2 ./img
  mke2fs 1.45.5 (07-Jan-2020)
  Discarding device blocks: done                            
  Creating filesystem with 24414 4k blocks and 24416 inodes

  Allocating group tables: done                            
  Writing inode tables: done                            
  Writing superblocks and filesystem accounting information: done
  ```
  * **making** mount point and **mount** **ext2** FS to it (**fill** using **sudo** this folder with **files** and **folders** to test programm and **ls -li** to **take** file **inode**)
  ```sh
  ~$ mkdir -p ext2_sys
  ~$ sudo mount ./img ext2_sys
  [sudo] password for ejeny: 
  ...
  (Watch **output** example)
  ```
* **Complinig** code 
  ```sh
  ~$ gcc main.c 
  ```
* **Run** exe **file** (**a.out** by default) with **image** and **inode number** as arguments
  ```sh
  ./a.out img 14
  ```
  $$\textbf{Functionality tests (all tests should be done using sudo)}$$

----
* **Unmount** after work:
```sh
~$ sudo umount ext2_sys
```
  
