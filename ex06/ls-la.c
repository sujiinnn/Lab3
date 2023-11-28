/*
 * 시스템 프로그래밍 Lab3 실습 6번
 * 파일 이름: ls-la.c
 * 20213004 안수진
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    
    pid_t pid;
    pid = fork();
    
    if (pid == 0) {
        /* 자식 프로세스가 execl 호출 */
        execl("/bin/ls", argv[1], argv[2], (char * ) 0);
        perror("execl failed");
    } else if (pid > 0) {
        /* 자식이 끝날 때까지 수행을 일시 중단하기 위해 wait 호출 */
        wait((int * ) 0);
        printf("ls completed\n");
        exit(0);
    } else
        perror("fork failed");
}