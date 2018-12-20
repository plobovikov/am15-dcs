

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
	ssize_t bytes_read;
    struct mq_attr attr;
    char buffer[MAX_SIZE + 1];
    /* initialize the queue attributes */
 
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_SIZE;
    attr.mq_curmsgs = 0;
 
    /* create the message queue */
 
    mq = mq_open(QUEUE_NAME, O_CREAT | O_RDONLY | O_NONBLOCK, 0644, &attr);
 
    while(1) {
 
 
 
		memset(buffer, 0x00, sizeof(buffer));
 
        bytes_read = mq_receive(mq, buffer, MAX_SIZE, NULL);
 
        if(bytes_read >= 0) {
 
			printf("SERVER: Received message: %s\n", buffer);
 
		} else {
 
			printf("SERVER: None \n");
		}
 
		fflush(stdout);
 
		usleep(0.725 * 1e6);
    }
 
    /* cleanup */
 
    mq_close(mq);
    mq_unlink(QUEUE_NAME);
 
}

