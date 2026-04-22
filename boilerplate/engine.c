#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#define MAX 50

typedef struct {
    char id[50];
    pid_t pid;
    int running;
} Container;

Container c[MAX];
int count = 0;

// start container
void start_container(char *id, char *rootfs, char *cmd) {
    pid_t pid = fork();

    if (pid == 0) {
        // child process (container)
        chroot(rootfs);
        chdir("/");

        // logging inside container
        FILE *f = fopen("/log.txt", "w");
        if (f) {
            dup2(fileno(f), STDOUT_FILENO);
            dup2(fileno(f), STDERR_FILENO);
        }

        // infinite loop to keep container alive
        execl(cmd, cmd, "-c", "while true; do echo running; sleep 2; done", NULL);

        perror("exec failed");
        exit(1);
    } else {
        // parent process
        strcpy(c[count].id, id);
        c[count].pid = pid;
        c[count].running = 1;
        count++;

        printf("Container %s started with PID %d\n", id, pid);
    }
}

// list containers (using system process table)
void list_containers() {
    printf("Container Processes:\n");
    system("ps -ef | grep 'while true' | grep -v grep");
}

// stop container
void stop_container(char *id) {
    for (int i = 0; i < count; i++) {
        if (strcmp(c[i].id, id) == 0 && c[i].running) {
            kill(c[i].pid, SIGTERM);
            c[i].running = 0;
            printf("Container %s stopped\n", id);
            return;
        }
    }
    printf("Container not found\n");
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Usage:\n");
        printf("./engine start <id> <rootfs> <cmd>\n");
        printf("./engine ps\n");
        printf("./engine stop <id>\n");
        return 1;
    }

    if (strcmp(argv[1], "start") == 0) {
        if (argc < 5) {
            printf("Usage: start <id> <rootfs> <cmd>\n");
            return 1;
        }
        start_container(argv[2], argv[3], argv[4]);
    }

    else if (strcmp(argv[1], "ps") == 0) {
        list_containers();
    }

    else if (strcmp(argv[1], "stop") == 0) {
        if (argc < 3) {
            printf("Usage: stop <id>\n");
            return 1;
        }
        stop_container(argv[2]);
    }

    else {
        printf("Unknown command\n");
    }

    return 0;
}
