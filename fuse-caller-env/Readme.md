# Fuse-caller-environ

* The task is to implement **FUSE** filesystem to some **mount point**. The **root** of a filesystem **must contain** (folders) **environ variables** of **current process**. 
Each **folder** named as **environ variable** of process must **contains** variable **value**. For **example**:
  ```sh
  ~$ ls -lha (mount_point)
  total 4,0K
  drwxr-xr-x 2 ejeny ejeny    0 фев 28 19:27 .
  drwxrwxr-x 4 ejeny ejeny 4,0K фев 28 19:27 ..
  -r--r--r-- 1 ejeny ejeny 4,0K фев 28 19:27 _
  -r--r--r-- 1 ejeny ejeny 4,0K фев 28 19:27 COLORTERM
  -r--r--r-- 1 ejeny ejeny 4,0K фев 28 19:27 DBUS_SESSION_BUS_ADDRESS
  -r--r--r-- 1 ejeny ejeny 4,0K фев 28 19:27 DESKTOP_SESSION
  -r--r--r-- 1 ejeny ejeny 4,0K фев 28 19:27 DISPLAY
  -r--r--r-- 1 ejeny ejeny 4,0K фев 28 19:27 GDMSESSION
  -r--r--r-- 1 ejeny ejeny 4,0K фев 28 19:27 GJS_DEBUG_OUTPUT
  -r--r--r-- 1 ejeny ejeny 4,0K фев 28 19:27 GJS_DEBUG_TOPICS
  -r--r--r-- 1 ejeny ejeny 4,0K фев 28 19:27 GNOME_DESKTOP_SESSION_ID
  -r--r--r-- 1 ejeny ejeny 4,0K фев 28 19:27 GNOME_TERMINAL_SERVICE
  -r--r--r-- 1 ejeny ejeny 4,0K фев 28 19:27 GPG_AGENT_INFO
  -r--r--r-- 1 ejeny ejeny 4,0K фев 28 19:27 GTK_MODULES
  -r--r--r-- 1 ejeny ejeny 4,0K фев 28 19:27 HOME
  -r--r--r-- 1 ejeny ejeny 4,0K фев 28 19:27 IM_CONFIG_PHASE
  -r--r--r-- 1 ejeny ejeny 4,0K фев 28 19:27 INVOCATION_ID
  -r--r--r-- 1 ejeny ejeny 4,0K фев 28 19:27 JOURNAL_STREAM
  -r--r--r-- 1 ejeny ejeny 4,0K фев 28 19:27 LANG
  ...
  -r--r--r-- 1 ejeny ejeny 4,0K фев 28 19:27 PATH
  -r--r--r-- 1 ejeny ejeny 4,0K фев 28 19:27 PWD
  ...
  -r--r--r-- 1 ejeny ejeny 4,0K фев 28 19:27 USER
  ...
  
  ~$ cat (mount_point)/LANG 
  en_US.UTF-8
  
  ~$ cat (mount_point)/USER
  ejeny
  
  ~$ cat (mount_point)/PATH
  /usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
  
  ~$ cat (mount_point)/PWD
  /home/ejeny/EjenY_FS/fs_prac/fuse
  ```
  
  # Files
  
  * [main4.c](https://github.com/EjenY-Poltavchiny/Filesystems-prac/blob/main/fuse-stack/main4.c)
