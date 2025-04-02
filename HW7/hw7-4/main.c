#include <stdio.h>
#include <string.h>
#include "hw7-4.h"
int main() {
    char testcase[51] = {};
    scanf("%s", testcase);
    char answer[51] = {};
    strcpy(answer, getAnswer1(testcase));
    printf("%s\n", answer);

    return 0;
}