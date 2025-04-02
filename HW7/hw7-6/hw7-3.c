#include <stdio.h>
#include <string.h>
#include "hw7-3.h"

void ParsingData(const char* command, char* string1, char* string2) {
    const char* space_pos = strchr(command, ' ');

    size_t pos = space_pos - command;
    strncpy(string1, command, pos);
    string1[pos] = '\0';
        
    strcpy(string2, space_pos + 3);
}