#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libgeometry/lexer.h"
#include "macr.h"

int check_brace_1(char* string, int* len)
{
    *len += 1;
    return (string[*len - 1] != '(') ? 2 : 0;
}

int check_arg_x(char* string, int* lenght)
{
    char* temp = (char*)malloc(N * sizeof(char));
    int j = 0, len = 0, p = *lenght;
    for (int i = p; ((string[i] >= '0') && (string[i] <= '9'))
         || (string[i] == '.') || (string[i] == '-');
         i++) {
        temp[j++] = string[i];
        *lenght += 1;
        len = i + 1;
    }
    if (((len == 0) || (string[len] != ' '))
        || ((string[p] != '0') && (atof(temp) == 0))) {
        free(temp);
        return 3;
    }
    *lenght += 1;
    free(temp);
    return 0;
}

int check_arg_y(char* string, int* lenght)
{
    char* temp = (char*)malloc(N * sizeof(char));
    int j = 0, len = 0, p = *lenght;
    for (int i = p; ((string[i] >= '0') && (string[i] <= '9'))
         || (string[i] == '.') || (string[i] == '-');
         i++) {
        temp[j++] = string[i];
        *lenght += 1;
        len = i + 1;
    }
    if ((len == 0) || (string[len] != ',')) {
        free(temp);
        return 4;
    }
    if (string[p] != '0' && atof(temp) == 0) {
        free(temp);
        return 4;
    }
    *lenght += 1;
    free(temp);
    return 0;
}

int check_radius(char* string, int* lenght)
{
    int len = 0, p = *lenght + 1;
    for (int i = p;
         ((string[i] >= '0') && (string[i] <= '9')) || (string[i] == '.');
         i++) {
        *lenght += 1;
        len = i + 1;
    }
    if (len == 0) {
        return 5;
    }
    *lenght += 1;
    return 0;
}

int check_brace_2(char* string, int* lenght)
{
    if (string[*lenght] != ')') {
        return 6;
    } else if (*lenght + 2 < (int)strlen(string)) {
        return 7;
    }
    return 0;
}

int is_circle(char* string)
{
    int len = 0;
    if (check_name(string, &len) == 1) {
        return 1;
    }
    if (check_brace_1(string, &len) == 2) {
        return 2;
    }
    if (check_arg_x(string, &len) == 3) {
        return 3;
    }
    if (check_arg_y(string, &len) == 4) {
        return 4;
    }
    if (check_radius(string, &len) == 5) {
        return 5;
    }
    if (check_brace_2(string, &len) == 6) {
        return 6;
    } else if (check_brace_2(string, &len) == 7) {
        return 7;
    }
    return 0;
}

void error_msg(char* string, int k, int fail)
{
    printf("\n%d. %s", fail, string);
    switch (k) {
    case 1:
        printf("Error: expected 'circle'\n");
        break;
    case 2:
        printf("Error: expected '('\n");
        break;
    case 3:
        printf("Error at x coordinate: expected double\n");
        break;
    case 4:
        printf("Error at y coordinate: expected double\n");
        break;
    case 5:
        printf("Error at radius: expected double\n");
        break;
    case 6:
        printf("Error: expected ')'\n");
        break;
    case 7:
        printf("Error: unexpected token\n");
        break;
    }
}
