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

* [main.cpp]()
