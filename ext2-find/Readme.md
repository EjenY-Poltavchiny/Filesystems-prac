# Ext2-find

* The **task** is to implement **find** utility to **object** in **ext2** fs by **inode**
* For **example**:
  ```sh
  ~$(mount_point) find .
  .
  ./somefile.txt
  ./lost+found
  find: ‘./lost+found’: Permission denied
  ./a.txt
  ./anotherfile.txt
  ./new_dir
  ./new_dir/new_new_dir
  ./new_dir/new_new_dir/file2.txt
  ./new_dir/new_new_dir/file.txt
  ./new_dir/a.txt
  ./new_dir/b.txt
  ./new_dir/c.txt
  ```
  * in our task we will ignore **lost+found . ..**
* **Output** example (**root** of **ext2** FS have inode = **2**)
  ```sh
  ~/$ ./a.out img 2
  16 f ./new_dir/a.txt
  17 f ./new_dir/b.txt
  18 f ./new_dir/c.txt
  20 f ./new_dir/new_new_dir/file.txt
  21 f ./new_dir/new_new_dir/file2.txt
  13 f ./somefile.txt
  14 f ./anotherfile.txt
  15 f ./a.txt
  ```
  
# Files
  
* [main.c](https://github.com/EjenY-Poltavchiny/Filesystems-prac/blob/main/ext2-find/main.c) - **main** file of the solution
* [solution.c](https://github.com/EjenY-Poltavchiny/Filesystems-prac/blob/main/ext2-find/solution.c) - task **solution**
* [solution.h](https://github.com/EjenY-Poltavchiny/Filesystems-prac/blob/main/ext2-find/solution.h) - **declaration** of functions

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
  ./a.out img 2
  ...
  ```
* **Unmount** after work:
  ```sh
  ~$ sudo umount ext2_sys
  ```

