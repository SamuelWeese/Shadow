#include <stdio.h>
#include <sys/ptrace.h>
#include <unistd.h>

int main() {
    if (ptrace(PTRACE_TRACEME, 0, NULL, NULL) == -1) {
        perror("ptrace");
        return 1;
    }

    printf("This process is now being traced!\n");

    for (int i = 0; i < 5; i++) {
        printf("Running iteration %d\n", i);
        sleep(1);
    }

    return 0;
}