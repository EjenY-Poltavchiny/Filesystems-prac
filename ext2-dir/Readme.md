# Ext2-dir

* The **task** is to implement solution wich sholud be able to **output** **content** of the **folder**.
* We have **this** folder
  ```sh
  ~$(mount point) ls -li
  total 4
  13 drwxr-xr-x 2 root root 4096 мар  1 00:53 another_dir
  14 -rw-r--r-- 1 root root    0 мар  1 00:53 somfile.txt
  ```
* **Output** example:
  ```sh
  ~$ ./a.out img 12
  12 d .
  2 d ..
  13 d another_dir
  14 f somfile.txt
  ```

# Files

* [mysol.c](https://github.com/EjenY-Poltavchiny/Filesystems-prac/blob/main/ext2-dir/mysol.c) - task **solution**

# Run and tests instructions

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
* **Run** exe **file** (**a.out** by default) with **image** and **inode number** as arguments. For **exmaple**:
  ```sh
  ./a.out img 12
  ...
  ```
* **Unmount** after work:
  ```sh
  ~$ sudo umount ext2_sys
  ```
