#include <stdio.h>
#include <string.h>
#include "hw7-2.h"

#define MAX 21

char* getUserInput() {
    static char input[MAX];
    fgets(input, MAX, stdin);
    
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }
    else {
        while (getchar() != '\n');
    }

    return input;
}

void printAllInput(char command[51][21], int command_cnt) {
    for (int i = 0; i < command_cnt; i++) {
        printf("%s\n", command[i]);
    }
}