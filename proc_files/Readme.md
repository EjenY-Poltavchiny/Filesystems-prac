# Proc_files

* The **task** is to implement **solution** wich will output **paths** for **files opened by all processes** at filesystem.
* **Output** example:
```
/home/ejeny/.local/share/gvfs-metadata/home
/home/ejeny/.local/share/gvfs-metadata/home-e00c4367.log
pipe:[64885]
pipe:[64885]
anon_inode:[eventfd]
socket:[64887]
anon_inode:[eventfd]
/home/ejeny/.cache/event-sound-cache.tdb.279876bc11824a40aff6130845aabe9b.x86_64-pc-linux-gnu
/dev/null

```
## Files

* [main.c](https://github.com/EjenY-Poltavchiny/Filesystems-prac/blob/main/proc_files/main.c) - main file
* [solution.c](https://github.com/EjenY-Poltavchiny/Filesystems-prac/blob/main/proc_files/solution.c) - task **solution code**
* [solution.h](https://github.com/EjenY-Poltavchiny/Filesystems-prac/blob/main/proc_files/solution.h) - declaration of function and task **formulating**
* [calbacks.c](https://github.com/EjenY-Poltavchiny/Filesystems-prac/blob/main/proc_files/callbacks.c) - implementation **functions** for **output**

## Run instructions

* Compiling
```sh
~$ gcc main.c solution.c callbacks.c
```
* Run executable file (**a.out** by default)
```sh
~$ ./a.out
```
