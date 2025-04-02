#include <stdio.h>
#include <string.h>
#include "hw7-5.h"

int main() {
    char testcase[51] = {};
    scanf("%s", testcase);
    char answer[51] = {};
    strcpy(answer, getAnswer2(testcase));
    printf("%s\n", answer);

    return 0;
}