#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 1000
#define MAX_LINE_LENGTH 256

int main() {
    char filename[100];
    char lines[MAX_LINES][MAX_LINE_LENGTH];
    int lineCount = 0;



    FILE *file = fopen("f1.txt", "r");
    if (file == NULL) {
        printf("Error: Unable to open the file\n");
        return 1;
    }

    while (fgets(lines[lineCount], sizeof(lines[lineCount]), file) != NULL) {
        lineCount++;
        if (lineCount >= MAX_LINES) {
            printf("Warning: Maximum number of lines exceeded\n");
            break;
        }
    }

    fclose(file);
    for(int j=0;j<lineCount;j++){
        printf("%s",lines[j]);
    }
    
}