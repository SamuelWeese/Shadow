#include <sys/ptrace.h>
#include <unistd.h>

int main() {
    ptrace(PTRACE_TRACEME, 0, NULL, NULL);
    execl("/bin/ls", "ls", NULL);
    return 0;
}