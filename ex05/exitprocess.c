/*
 * 시스템 프로그래밍 Lab3 실습 5번
 * 파일 이름: exitprocess.c
 * 20213004 안수진
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
    int exit_status;
    printf("enter exit status: ");
    scanf("%d", & exit_status);
    exit(exit_status);
}