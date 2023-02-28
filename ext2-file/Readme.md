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

* [main.c]()
