

#include <fcntl.h>
#include <mqueue.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define QUEUE_NAME  "/test_queue"
#define MAX_SIZE    1024
#define MSG_STOP    "exit"
 
int main(int argc, char** argv) {
	mqd_t mq;
 
    char buffer[MAX_SIZE];
 
    /* open the mail queue */
 
    mq = mq_open(QUEUE_NAME, O_WRONLY);

	int count = 0;
 
    while(1) {
 
        snprintf(buffer, sizeof(buffer), "MESSAGE %d", count++);
		printf("CLIENT: Send message... \n");
        mq_send(mq, buffer, MAX_SIZE, 0);
		fflush(stdout);
		usleep(7.33 * 1e6);
    }
    mq_close(mq);
	return 0;
 
}

