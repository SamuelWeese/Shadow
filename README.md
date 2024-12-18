# SHADOW

Shadow is a tool developed to replay files by capturing the output and input to a process, and saving it.


## Planning

[WhiteBoard](https://miro.com/app/board/uXjVL2dvQCc=/)

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

Another option could be hooking the different IO functions of a system. This does have the downside of being "more work".

### Memory Map

TODO.

### Networking

TODO.

