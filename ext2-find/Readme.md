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
  
  * [main.c]()
  * [solution.c]()
  * [solution.h]()
