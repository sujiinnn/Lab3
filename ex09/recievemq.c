/*
 * 시스템 프로그래밍 Lab3 실습 9번
 * 파일 이름: recievemq.c
 * 20213004 안수진
 */

#include <sys/types.h>
#include <sys/wait.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MESSAGE_SIZE 32
#define QUEUE_NAME "/my_queue"
#define MESSAGE_PRIORITY 1

char received_data[MESSAGE_SIZE];

int main() {
    mqd_t mq_descriptor;
    pid_t child_pid;
    int status;
    struct mq_attr mq_attributes, old_mq_attributes;
    int priority;

    char buffer[MESSAGE_SIZE];

    mq_attributes.mq_maxmsg = 10;       /* maximum number of messages in the queue */
    mq_attributes.mq_msgsize = MESSAGE_SIZE; /* maximum message size */

    while (1) {
        if ((child_pid = fork()) == 0) {
            if ((mq_descriptor = mq_open(QUEUE_NAME, O_RDWR | O_NONBLOCK, 0600, NULL)) == -1) {
                perror("mq_open failed");
                exit(EXIT_FAILURE);
            }

            mq_attributes.mq_flags = 0; /* release O_NONBLOCK */

            if (mq_setattr(mq_descriptor, &mq_attributes, &old_mq_attributes) == -1) {
                perror("mq_setattr failed");
                exit(EXIT_FAILURE);
            }

            if (!(old_mq_attributes.mq_flags & O_NONBLOCK)) {
            }

            if (mq_receive(mq_descriptor, received_data, MESSAGE_SIZE, &priority) == -1) {
                perror("mq_receive failed");
                exit(EXIT_FAILURE);
            }

            printf("User Said: %s\n", received_data);

            if (mq_close(mq_descriptor) == -1) {
                perror("mq_close failed");
                exit(EXIT_FAILURE);
            }

            if (mq_unlink(QUEUE_NAME) == -1) {
                perror("mq_unlink failed");
                exit(EXIT_FAILURE);
            }

            exit(EXIT_SUCCESS);
        } else if (child_pid > 0) {
            child_pid = wait(&status);
            sleep(3);
        } else {
            perror("fork failed");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
