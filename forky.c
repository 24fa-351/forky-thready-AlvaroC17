#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

void start_process(int i, int sleep_time) {
    printf("Process %d beginning\n", i);
    sleep(sleep_time);
    printf("Process %d exiting\n", i);
}

void pattern1(int n) {
    pid_t pid;
    int i;

    for (i = 1; i <= n; i++) {
        pid = fork();
        if (pid == 0) { // Child process
            int sleep_time = rand() % 8 + 1;
            start_process(i, sleep_time);
            exit(0);
        }
    }
    while (wait(NULL) > 0); // Parent waits for all child processes to complete
}

void pattern2(int n) {
    pid_t pid;
    int i = 1;

    printf("Main creating Process %d\n", i);
    while (i <= n) {
        pid = fork();
        if (pid == 0) { // Child process
            int sleep_time = rand() % 8 + 1;
            start_process(i, sleep_time);
            exit(0);
        }
        else {
            wait(NULL); // Parent waits for child to complete
            if (++i <= n) {
                printf("Main creating Process %d\n", i);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <number_of_processes> <pattern>\n", argv[0]);
        return 1;
    }

    int num_processes = atoi(argv[1]);
    int pattern = atoi(argv[2]);

    if (num_processes < 1 || num_processes > 256 || (pattern != 1 && pattern != 2)) {
        fprintf(stderr, "Invalid number of processes or pattern number.\n");
        return 1;
    }

    srand(time(NULL)); // Initialize random number generator

    if (pattern == 1) {
        pattern1(num_processes);
    } else if (pattern == 2) {
        pattern2(num_processes);
    }

    return 0;
}
