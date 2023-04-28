#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libgeometry/counter.h"
#include "libgeometry/macr.h"
#include "libgeometry/parser.h"

int main()
{
    system("clear");
    FILE* check;
    check = fopen("shapes.txt", "r");
    if (check == NULL) {
        printf("Error of opening file!\n");
        return 1;
    }
    char* string = (char*)malloc(N * sizeof(char));
    char** strings = (char**)malloc(sizeof(char*));
    int row = 1, count = 1, fail = 1;
    printf("\nFailed:");
    for (; fgets(string, N, check) != NULL; count++) {
        int k = is_circle(string);
        if (!k) {
            strings = (char**)realloc(strings, row * sizeof(char*));
            strings[row - 1] = (char*)malloc(strlen(string) * sizeof(char));
            strcpy(strings[row - 1], string);
            row++;
        } else {
            error_msg(string, k, fail++);
        }
    }
    intersections(strings, row - 1);
    for (int i = 0; i < row - 1; i++) {
        free(strings[i]);
    }
    free(strings);
    free(string);
    return 0;
}
