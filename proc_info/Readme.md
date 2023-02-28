# Proc_info

* The **task** is to implement **solution** wich will output **eviroment**, **comand lines** and **path to exec file** for **all** system **processes**.
* **Output** example:
```
pid 3416:
  exe = '/usr/bin/gedit'
  argv = ['/usr/bin/gedit', '--gapplication-service', ]
  envp = ['XDG_RUNTIME_DIR=/run/user/1000', 'SESSION_MANAGER=local/ejeny-VirtualBox:@/tmp/.ICE-unix/1523,unix/ejeny-VirtualBox:/tmp/.ICE-unix/1523', 'XMODIFIERS=@im=ibus', 'XDG_SESSION_TYPE=x11', 'DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/1000/bus,guid=6cae56a4383da1d517cf046c63fd6d76', 'USER=ejeny', 'XAUTHORITY=/run/user/1000/gdm/Xauthority', 'QT_IM_MODULE=ibus', 'LC_ADDRESS=ru_RU.UTF-8', 'DBUS_STARTER_BUS_TYPE=session', 'SHLVL=0', 'XDG_MENU_PREFIX=gnome-', 'XDG_SESSION_DESKTOP=ubuntu', 'SHELL=/bin/bash', 'QT_ACCESSIBILITY=1', 'LC_NAME=ru_RU.UTF-8', 'LC_MEASUREMENT=ru_RU.UTF-8', 'LC_TIME=ru_RU.UTF-8', 'LC_MONETARY=ru_RU.UTF-8', 'WINDOWPATH=2', 'USERNAME=ejeny', 'XDG_DATA_DIRS=/usr/share/ubuntu:/usr/local/share/:/usr/share/:/var/lib/snapd/desktop', 'IM_CONFIG_PHASE=1', 'GNOME_SHELL_SESSION_MODE=ubuntu', 'LC_TELEPHONE=ru_RU.UTF-8', 'PWD=/home/ejeny', 'HOME=/home/ejeny', '_=/usr/bin/dbus-update-activation-environment', 'DBUS_STARTER_ADDRESS=unix:path=/run/user/1000/bus,guid=6cae56a4383da1d517cf046c63fd6d76', 'DISPLAY=:0', 'LC_PAPER=ru_RU.UTF-8', 'SSH_AUTH_SOCK=/run/user/1000/keyring/ssh', 'LC_NUMERIC=ru_RU.UTF-8', 'PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin', 'GTK_MODULES=gail:atk-bridge', 'GDMSESSION=ubuntu', 'GNOME_DESKTOP_SESSION_ID=this-is-deprecated', 'JOURNAL_STREAM=8:33754', 'GPG_AGENT_INFO=/run/user/1000/gnupg/S.gpg-agent:0:1', 'INVOCATION_ID=b5929c4bbdf5499e8c4941a3189dae15', 'XDG_SESSION_CLASS=user', 'LANG=en_US.UTF-8', 'LOGNAME=ejeny', 'XDG_CURRENT_DESKTOP=ubuntu:GNOME', 'DESKTOP_SESSION=ubuntu', 'LC_IDENTIFICATION=ru_RU.UTF-8', 'SSH_AGENT_PID=1484', 'MANAGERPID=1277', 'XDG_CONFIG_DIRS=/etc/xdg/xdg-ubuntu:/etc/xdg', ]

```

## Files

* [main.c](https://github.com/EjenY-Poltavchiny/Filesystems-prac/edit/main/proc_info/main.cpp) - main file
* [solution.c](https://github.com/EjenY-Poltavchiny/Filesystems-prac/edit/main/proc_info/solution.cpp) - task **solution code**
* [solution.h](https://github.com/EjenY-Poltavchiny/Filesystems-prac/edit/main/proc_info/solution.h) - declaration of function and task **formulating**
* [calbacks.c](https://github.com/EjenY-Poltavchiny/Filesystems-prac/edit/main/proc_info/callbacks.cpp) - implementation **functions** for **output**

## Run instructions

* Compiling
```sh
~$ gcc main.c solution.c callbacks.c
```
* Run executable file (**a.out** by default)
```sh
~$ ./a.out
```
