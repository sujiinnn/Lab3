/*
* 시스템 프로그래밍 Lab3 실습 3번
* 파일 이름: ls_R.c
* 20213004 안수진
*/

#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIR_MAX 20
#define FILE_MAX 100

void recursionDir(const char *name) {

    DIR *dir;
    struct dirent *dirc;

    char temp[DIR_MAX][FILE_MAX];
    char dir_path[DIR_MAX][FILE_MAX];

    int i = 0;
    int j = 0;

    for (int m = 0; m < DIR_MAX; m++) {
        memset(temp[m], 0, FILE_MAX);
        memset(dir_path[m], 0, FILE_MAX);
    }

    if (!(dir = opendir(name))) {
        return;
    }

    printf("%s: \n", name);

    while ((dirc = readdir(dir)) != NULL) {

        if (dirc->d_type == DT_DIR) {
            char path[1024];

            if (strcmp(dirc->d_name, ".") == 0 || strcmp(dirc->d_name, "..") == 0 || strcmp(dirc->d_name, ".git") == 0) {
                continue;
            }

            snprintf(path, sizeof(path), "%s/%s", name, dirc->d_name);

            strncpy(temp[i], path, sizeof(temp[i]) - 1);
            strncpy(dir_path[i], temp[i], sizeof(dir_path[i]) - 1);

            i++;

            printf("%s%5s", dir_path[i - 1], "");

        } else {
            printf("%s%5s", dirc->d_name, "");
        }
    }

    printf("\n\n");

    while (j < i) {
        recursionDir(dir_path[j]);
        j++;
    }
    closedir(dir);
}

int main(void) {
    recursionDir(".");
    return 0;
}
