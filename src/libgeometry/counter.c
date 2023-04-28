#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _USE_MATH_DEFINES
#include <math.h>

#include "lexer.h"
#include "macr.h"
#include "parser.h"

void clear(char* string)
{
    for (int i = 0; i < (int)strlen(string); i++) {
        string[i] = ' ';
    }
}

double* arguments(char* string)
{
    double* args = (double*)malloc(COL * sizeof(double));
    int i = 0;
    int count = 0;
    char* temp = (char*)malloc(sizeof(char));
    for (i = 0; string[i] != '('; i++) {
    }
    i++;
    for (; string[i] != ' '; i++) {
        temp[count++] = string[i];
        temp = (char*)realloc(temp, (count + 1) * sizeof(char));
    }
    i++;
    count = 0;
    args[0] = atof(temp);
    clear(temp);
    temp = (char*)realloc(temp, sizeof(char));
    for (; string[i] != ','; i++) {
        temp[count++] = string[i];
        temp = (char*)realloc(temp, (count + 1) * sizeof(char));
    }
    i++;
    count = 0;
    args[1] = atof(temp);
    clear(temp);
    temp = (char*)realloc(temp, sizeof(char));
    for (; string[i] != ')'; i++) {
        temp[count++] = string[i];
        temp = (char*)realloc(temp, (count + 1) * sizeof(char));
    }
    args[2] = atof(temp);
    free(temp);
    return args;
}

double count_area(char* string)
{
    int i = 0;
    char* temp = (char*)malloc(sizeof(char));
    int count = 0;
    for (i = 0; string[i] != ','; i++) {
    }
    i++;
    for (; string[i] != ')'; i++) {
        temp[count++] = string[i];
        temp = (char*)realloc(temp, (count + 1) * sizeof(char));
    }
    double area = M_PI * atof(temp) * atof(temp);
    free(temp);
    return area;
}

double count_perimeter(char* string)
{
    int i = 0;
    char* temp = (char*)malloc(sizeof(char));
    int count = 0;
    for (i = 0; string[i] != ','; i++) {
    }
    i++;
    for (int p = i; string[p] != ')'; p++) {
        temp[count++] = string[p];
        temp = (char*)realloc(temp, (count + 1) * sizeof(char));
    }
    double perimeter = 2 * M_PI * atof(temp);
    free(temp);
    return perimeter;
}

void intersections(char** strings, int row)
{
    double** val = (double**)malloc(row * sizeof(double*));
    for (int i = 0; i < row; i++) {
        val[i] = (double*)malloc(COL * sizeof(double));
        val[i] = arguments(strings[i]);
    }
    printf("\nCorrect:");
    for (int i = 0; i < row; i++) {
        printf("\n%d. %s", i + 1, strings[i]);
        printf("\tarea = %f\n", count_area(strings[i]));
        printf("\tperimeter = %f\n", count_perimeter(strings[i]));
        for (int j = 0; j < row; j++) {
            if (i != j) {
                double d = (double)sqrt(
                        pow((val[i][0] - val[j][0]), 2)
                        + pow((val[i][1] - val[j][1]), 2));
                int minr = 0, maxr = 0;
                if (val[i][2] < val[j][2]) {
                    minr = val[i][2];
                    maxr = val[j][2];
                } else {
                    minr = val[j][2];
                    maxr = val[i][2];
                }
                if (((d < (minr + maxr)) && (maxr - minr < d))
                    || (d == maxr + minr) || (d == maxr - minr)) {
                    printf("\tintersects:\n\t\t%d. circle\n", j + 1);
                }
            }
        }
    }
    printf("\n");
    for (int i = 0; i < row; i++) {
        free(val[i]);
    }
    free(val);
}
