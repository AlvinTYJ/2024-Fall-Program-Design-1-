#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char input1[100],input2[100];
    FILE *file;

    while (1) {
        printf("Please enter the name of the file to read from.\n");
        fgets(input1, sizeof(input1), stdin);
        input1[strcspn(input1, "\n")] = 0;
        
        if (strcmp(input1, "exit") == 0) {
            break;
        }
        
        file = fopen(input1, "r");
        if (file == NULL) {
            printf("The file name does not exist.\n");
            continue;
        }
        int num1, den1, num2, den2, a ,b;
        fscanf(file, "%d %d %d %d", &num1, &den1, &num2, &den2);
        fclose(file);
        
        printf("Please enter the name of the file to write the output to.\n");
        fgets(input2, sizeof(input2), stdin);
        input2[strcspn(input2, "\n")] = 0;
        file = fopen(input2,"w");

        a = (num1*den2) + (num2*den1);
        b = den1*den2;
        printf("Calculation complete!\n");
        fprintf(file,"%d/%d\n", a, b);
        fclose(file);
    }

    return 0;
}