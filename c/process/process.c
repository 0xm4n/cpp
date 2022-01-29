#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv) 
{
    pid_t pid = fork();
    if (pid != 0) {
        waitpid(pid, NULL, 0);
        printf("Hello from parent\n");
    } else {
        printf("Hello from child\n");
    }
    return 0;
}