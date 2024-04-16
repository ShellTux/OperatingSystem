#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define N_FORKS 10

int main(void)
{
	srand(time(NULL));

	for (int i = 0; i < N_FORKS; ++i) {
		int sleepTime = 1 + rand() % 10;
		int pid = fork();

		if (pid == -1) {
			perror("Fork Error: ");
			exit(EXIT_FAILURE);
		} else if (pid == 0) {
			// NOTE: CHILD CODE
			sleep(sleepTime);
			printf("Child ID: %d, Child PID: %d, Child PPID: %d\n", pid, getpid(), getppid());
			exit(EXIT_SUCCESS);
		} else {
			// NOTE: MAIN CODE
			printf("New Process generated with PID: %d, with sleep time of %d\n", pid, sleepTime);
		}
	}

	pid_t status;
	while ((status = wait(NULL)) != -1) {
		printf("Finished execution of PID: %d\n", status);
	}

	return 0;
}
