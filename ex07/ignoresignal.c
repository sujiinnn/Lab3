/*
 * 시스템 프로그래밍 Lab3 실습 7번
 * 파일 이름: ignoresignal.c
 * 20213004 안수진
 */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
int main()
{
    struct sigaction act;
    int i = 0;
    act.sa_handler = SIG_IGN;
    sigfillset(&(act.sa_mask));
    sigaction(SIGINT, &act, NULL);
    printf("SIGINT off\n");
    while (1)
    {
        sleep(1);
        printf("sleep for %d sec(s).\n", ++i);
    }
}