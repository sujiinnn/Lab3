/*
 * 시스템 프로그래밍 Lab3 실습 9번
 * 파일 이름: sendmq.c
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

int main() {
    mqd_t mq_descriptor;
    struct mq_attr mq_attributes;
    char message_buffer[MESSAGE_SIZE];
    int status;
    pid_t child_pid;

    mq_attributes.mq_maxmsg = 10;       /* maximum number of messages in the queue */
    mq_attributes.mq_msgsize = MESSAGE_SIZE; /* maximum message size */

    while (1) {
        if ((child_pid = fork()) == 0) {
            memset(message_buffer, 0, MESSAGE_SIZE);
            printf("Input > ");
            scanf("%[^\n]", message_buffer);

            if ((mq_descriptor = mq_open(QUEUE_NAME, O_CREAT | O_RDWR, 0600, &mq_attributes)) == -1) {
                perror("mq_open failed");
                exit(EXIT_FAILURE);
            }

            if (mq_send(mq_descriptor, message_buffer, strlen(message_buffer), MESSAGE_PRIORITY) == -1) {
                perror("mq_send failed");
                exit(EXIT_FAILURE);
            }

            if (mq_close(mq_descriptor) == -1) {
                perror("mq_close failed");
                exit(EXIT_FAILURE);
            }

            exit(EXIT_SUCCESS);
        } else if (child_pid > 0) {
            child_pid = wait(&status);
            sleep(1); // Sleep to avoid race conditions
        } else {
            perror("fork failed");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
