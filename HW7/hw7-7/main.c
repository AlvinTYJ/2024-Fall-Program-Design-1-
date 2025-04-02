#include <stdio.h>
#include "hw7-7.h"

char all_testcase[59049][11]; // 59049 = 3^10

int main() {
    int target_len;
    scanf("%d", &target_len);
    GeneratingTest(target_len, all_testcase);
    
    int total = 1;
    for(int i=0;i<target_len;i++) total *= 3;
    for(int i=0;i<total;i++) {
        for(int j=0;j<target_len;j++) printf("%c", all_testcase[i][j]);
        printf("\n");
    }

    return 0;
}