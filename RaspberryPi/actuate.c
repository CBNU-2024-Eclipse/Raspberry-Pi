#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

void run_command(const char *command, int times) {
    for (int i = 0; i < times; i++) {
        if (fork() == 0) {
            execl("/bin/sh", "sh", "-c", command, NULL);
            exit(0);  // Exit the child process
        }
        sleep(1);    // Wait for 1 second between each run
    }
}

int main(int argc, char *argv[]) {
    if (argc != 7) {
        fprintf(stderr, "Usage: %s <pumpon> <pumptime> <lighton> <lighttime> <fanon> <fantime>\n", argv[0]);
        return 1;
    }

    int pumpon = atoi(argv[1]);
    int pumptime = atoi(argv[2]);
    int lighton = atoi(argv[3]);
    int lighttime = atoi(argv[4]);
    int fanon = atoi(argv[5]);
    int fantime = atoi(argv[6]);

    if (pumpon == 1) {
        if (fork() == 0) {
            run_command("/home/pi/smartfarm/pumpon", pumptime);
            exit(0);
        }
    }

    if (lighton == 1) {
        if (fork() == 0) {
            run_command("/home/pi/smartfarm/rgbtest", lighttime);
            exit(0);
        }
    }

    if (fanon == 1) {
        if (fork() == 0) {
            run_command("/home/pi/smartfarm/fanon", fantime);
            exit(0);
        }
    }
    // Wait for all child processes to finish
    while (wait(NULL) > 0);

    return 0;
}

