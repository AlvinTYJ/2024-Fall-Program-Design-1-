#include <stdio.h>
#include <string.h>
#include "hw7-2.h"

char command[51][21];
int main() {
    printf("Please input all the commands\n");
    int command_cnt = 0;
    while(1) {
        strcpy(command[command_cnt],getUserInput());
        if( strcmp(command[command_cnt++], "exit") == 0 ) {
            command_cnt--;
            printAllInput(command, command_cnt);
            break;
        }
    }

    return 0;
}