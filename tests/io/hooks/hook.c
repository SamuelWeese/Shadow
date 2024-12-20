#ifndef __hooks
#define __hooks
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <string.h>
#include <stdint.h>

// Function pointers for original libc functions
ssize_t (*original_read)(int fd, void *buf, size_t count);
ssize_t (*original_write)(int fd, const void *buf, size_t count);
int (*original_pipe)(int pipefd[2]);
//void (*original_signal)(int signum, void (*handler)(int));
int (*original_sigaction)(int signum, const struct sigaction *act, struct sigaction *oldact);
int (*original_msgget)(key_t key, int msgflg);
int (*original_msgsnd)(int msqid, const void *msgp, size_t msgsz, int msgflg);
ssize_t (*original_msgrcv)(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);
int (*original_shmget)(key_t key, size_t size, int shmflg);
void *(*original_shmat)(int shmid, const void *shmaddr, int shmflg);
int (*original_shmdt)(const void *shmaddr);
int (*original_semop)(int semid, struct sembuf *sops, size_t nsops);
int (*original_semget)(key_t key, int nsems, int semflg);
int (*original_semctl)(int semid, int semnum, int cmd, ...);
int (*original_inotify_add_watch)(int fd, const char *pathname, uint32_t mask);

// Custom hook implementations
ssize_t read(int fd, void *buf, size_t count) {
    if (!original_read) original_read = dlsym(RTLD_NEXT, "read");
    ssize_t result = original_read(fd, buf, count);
    if (result > 0) printf("[HOOK] read(fd=%d, count=%zu): %.*s\n", fd, count, (int)result, (char *)buf);
    return result;
}

ssize_t write(int fd, const void *buf, size_t count) {
    if (!original_write) original_write = dlsym(RTLD_NEXT, "write");
    printf("[HOOK] write(fd=%d, count=%zu): %.*s\n", fd, count, (int)count, (const char *)buf);
    return original_write(fd, buf, count);
}

int pipe(int pipefd[2]) {
    if (!original_pipe) original_pipe = dlsym(RTLD_NEXT, "pipe");
    printf("[HOOK] pipe()\n");
    return original_pipe(pipefd);
}
/*
void (*signal(int signum, void (*handler)(int)))(int) {
    if (!original_signal) original_signal = dlsym(RTLD_NEXT, "signal");
    printf("[HOOK] signal(signum=%d)\n", signum);
    return original_signal(signum, handler);
}*/

int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact) {
    if (!original_sigaction) original_sigaction = dlsym(RTLD_NEXT, "sigaction");
    printf("[HOOK] sigaction(signum=%d)\n", signum);
    return original_sigaction(signum, act, oldact);
}

int msgget(key_t key, int msgflg) {
    if (!original_msgget) original_msgget = dlsym(RTLD_NEXT, "msgget");
    printf("[HOOK] msgget(key=%d, msgflg=%d)\n", key, msgflg);
    return original_msgget(key, msgflg);
}

int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg) {
    if (!original_msgsnd) original_msgsnd = dlsym(RTLD_NEXT, "msgsnd");
    printf("[HOOK] msgsnd(msqid=%d, msgsz=%zu)\n", msqid, msgsz);
    return original_msgsnd(msqid, msgp, msgsz, msgflg);
}

ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg) {
    if (!original_msgrcv) original_msgrcv = dlsym(RTLD_NEXT, "msgrcv");
    ssize_t result = original_msgrcv(msqid, msgp, msgsz, msgtyp, msgflg);
    printf("[HOOK] msgrcv(msqid=%d, msgsz=%zu)\n", msqid, msgsz);
    return result;
}

int shmget(key_t key, size_t size, int shmflg) {
    if (!original_shmget) original_shmget = dlsym(RTLD_NEXT, "shmget");
    printf("[HOOK] shmget(key=%d, size=%zu, shmflg=%d)\n", key, size, shmflg);
    return original_shmget(key, size, shmflg);
}

void *shmat(int shmid, const void *shmaddr, int shmflg) {
    if (!original_shmat) original_shmat = dlsym(RTLD_NEXT, "shmat");
    void *result = original_shmat(shmid, shmaddr, shmflg);
    printf("[HOOK] shmat(shmid=%d)\n", shmid);
    return result;
}

int shmdt(const void *shmaddr) {
    if (!original_shmdt) original_shmdt = dlsym(RTLD_NEXT, "shmdt");
    printf("[HOOK] shmdt()\n");
    return original_shmdt(shmaddr);
}

int semop(int semid, struct sembuf *sops, size_t nsops) {
    if (!original_semop) original_semop = dlsym(RTLD_NEXT, "semop");
    printf("[HOOK] semop(semid=%d, nsops=%zu)\n", semid, nsops);
    return original_semop(semid, sops, nsops);
}

int semget(key_t key, int nsems, int semflg) {
    if (!original_semget) original_semget = dlsym(RTLD_NEXT, "semget");
    printf("[HOOK] semget(key=%d, nsems=%d, semflg=%d)\n", key, nsems, semflg);
    return original_semget(key, nsems, semflg);
}

int semctl(int semid, int semnum, int cmd, ...) {
    if (!original_semctl) original_semctl = dlsym(RTLD_NEXT, "semctl");
    printf("[HOOK] semctl(semid=%d, semnum=%d, cmd=%d)\n", semid, semnum, cmd);
    return original_semctl(semid, semnum, cmd);
}

int inotify_add_watch(int fd, const char *pathname, uint32_t mask) {
    if (!original_inotify_add_watch) original_inotify_add_watch = dlsym(RTLD_NEXT, "inotify_add_watch");
    printf("[HOOK] inotify_add_watch(fd=%d, pathname=%s, mask=%u)\n", fd, pathname, mask);
    return original_inotify_add_watch(fd, pathname, mask);
}

#endif