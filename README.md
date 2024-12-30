# SHADOW

Shadow is a tool developed to replay files by capturing the output and input to a process, and saving it.


## Planning

[WhiteBoard](https://miro.com/app/board/uXjVL2dvQCc=/?share_link_id=128326230375)

## Stage 1

### Goals

#### Reading

- Read all input output
- Read all from memory map
- Read all from networks

#### User Interface

- Show input output as stream with history
- Show memory map state with live updates
- Show networks in wireshark like way 


## Current State

### IO

Ideally, this is some form of shim, as we want to be able to virtualize our IO layer so that when we play back an application, we can have presaved value to be inserted into the application.

#### Tracers

This _may_ work, however I (Sam) am not thinking it will. Processes can detect tracers, and the question remains "How do we record data identically as bytes from a trace?". 

Investigated:

- strace
- ptrace
- execvp
- blktrace

#### Hooks

Another option could be hooking the different IO functions of a system. This does have the downside of being "more work". We could use [LD_PRELOAD](https://www.baeldung.com/linux/ld_preload-trick-what-is) to do this possibly.


Functions to Hook:
- [pipe](https://man7.org/linux/man-pages/man2/pipe.2.html)
- [read](https://man7.org/linux/man-pages/man2/read.2.html)
- [write](https://man7.org/linux/man-pages/man2/write.2.html)
- [signal](https://man7.org/linux/man-pages/man2/signal.2.html)
- [sigaction](https://man7.org/linux/man-pages/man2/sigaction.2.html)
- [msgget](https://man7.org/linux/man-pages/man2/msgget.2.html)
- [msgsend](https://man7.org/linux/man-pages/man2/msgsend.2.html)
- [msgrcv](https://man7.org/linux/man-pages/man2/msgrcv.2.html)
- [shmget](https://man7.org/linux/man-pages/man2/shmget.2.html)
- [shmat](https://man7.org/linux/man-pages/man2/shmat.2.html)
- [shmdt](https://man7.org/linux/man-pages/man2/shmdt.2.html)
- [semop](https://man7.org/linux/man-pages/man2/semop.2.html)
- [semget](https://man7.org/linux/man-pages/man2/semget.2.html)
- [semctl](https://man7.org/linux/man-pages/man2/semctl.2.html)
- [dbus_connection_send](https://man7.org/linux/man-pages/man2/dbus_connection_send.2.html)
- [dbus_connection_read](https://man7.org/linux/man-pages/man2/dbus_connection_read.2.html)
- [inotify_add_watch](https://man7.org/linux/man-pages/man2/inotify_add_watch.2.html)

This may or may not allow us to deal with things such as Procfs and Sysfs. I believe they are accessed through read, but I'm not certain. TODO test.

###### HOOK EVERYTHING!

Realistically, if we go down the hooking route, we should hook everything, and just do it dynamically. This also fixes the issues of the system using some form of unaccounted for library that I was too stupid to not forsee.


#### eBPF

TODO, not yet explored.

#### Kernel Module

TODO, probably overkill.

### Memory Map

TODO.

### Networking

TODO.

