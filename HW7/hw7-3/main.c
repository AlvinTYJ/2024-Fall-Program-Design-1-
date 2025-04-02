#include <stdio.h>
#include <string.h>
#include "hw7-3.h"
#include "hw7-2.h"

char string1[51][21], string2[51][21];
char command[51][21];
int main() {
    printf("Please input all the commands\n");
    int command_cnt = 0;
    while(1) {
        strcpy(command[command_cnt],getUserInput());
        if( strcmp(command[command_cnt++], "exit") == 0 ) {
            command_cnt--;
            break;
        }
    }

    for(int i=0;i<command_cnt;i++) {
        ParsingData(command[i], string1[i], string2[i]);
        printf("command %d: string1 = %s\n", i + 1,string1[i]);
        printf("command %d: string2 = %s\n", i + 1,string2[i]);
    }

    return 0;
}