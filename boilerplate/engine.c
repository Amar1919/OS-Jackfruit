#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#define MAX 20

typedef struct {
    char id[50];
    pid_t pid;
    int running;
} Container;

Container c[MAX];
int count = 0;

// find container
int find(char *id) {
    for(int i = 0; i < count; i++) {
        if(strcmp(c[i].id, id) == 0)
            return i;
    }
    return -1;
}

// supervisor
void run_supervisor() {
    printf("Supervisor started...\n");
    while(1) {
        sleep(5);
    }
}

// start container
void start_container(char *id, char *rootfs, char *cmd) {
    pid_t pid = fork();

    if(pid == 0) {
        chroot(rootfs);
        chdir("/");
        execl(cmd, cmd, "-c", "while true; do sleep 5; done", NULL);
        perror("exec failed");
        exit(1);
    } else {
        strcpy(c[count].id, id);
        c[count].pid = pid;
        c[count].running = 1;
        count++;

        printf("Container %s started with PID %d\n", id, pid);
    }
}

// list containers
void list_containers() {
    printf("Running container processes:\n");
    system("ps -ef | grep sh | grep -v grep");
}

// stop container
void stop_container(char *id) {
    int idx = find(id);

    if(idx == -1) {
        printf("Container not found\n");
        return;
    }

    kill(c[idx].pid, SIGTERM);
    c[idx].running = 0;

    printf("Container %s stopped\n", id);
}

int main(int argc, char *argv[]) {

    if(argc < 2) {
        printf("Usage:\n");
        printf("./engine supervisor\n");
        printf("./engine start <id> <rootfs> <cmd>\n");
        printf("./engine ps\n");
        printf("./engine stop <id>\n");
        return 1;
    }

    if(strcmp(argv[1], "supervisor") == 0) {
        run_supervisor();
    }

    else if(strcmp(argv[1], "start") == 0) {
        if(argc < 5) {
            printf("Usage: start <id> <rootfs> <cmd>\n");
            return 1;
        }
        start_container(argv[2], argv[3], argv[4]);
    }

    else if(strcmp(argv[1], "ps") == 0) {
        list_containers();
    }

    else if(strcmp(argv[1], "stop") == 0) {
        if(argc < 3) {
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
