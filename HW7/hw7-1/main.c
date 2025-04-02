#include <stdio.h>
#include "hw7-1.h"
int main() {
    int choose;
    while(1) {
        choose = GameStart(); 
        if( choose == -1 ) {
            printf("Please input 1 or 2 !\n");
        }
        else {
            printf("ok, you select the level %d\n", choose);
            break;
        }
    }
}