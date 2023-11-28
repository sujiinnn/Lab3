/*
 * 시스템 프로그래밍 Lab3 실습 8번
 * 파일 이름: iopipe.c
 * 20213004 안수진
 */

#include <stdio.h>

#define BUFSIZE 256

int main()
{
    FILE *pin, *pout;
    char buf[BUFSIZE];

    pin = popen("who", "r");
    pout = popen("wc -l", "w");

    while (fgets(buf, BUFSIZE, pin) != NULL)
        fputs(buf, pout);
        
    pclose(pin);
    pclose(pout);
}
