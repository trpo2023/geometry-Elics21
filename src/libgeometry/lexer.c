#include <string.h>

#include "macr.h"

int check_name(char* string, int* len)
{
    char temp[N];
    for (int i = 0; (string[i] >= 'a') && (string[i] <= 'z'); i++) {
        temp[i] = string[i];
        *len += 1;
    }
    if (strcmp(temp, "circle") != 0) {
        return 1;
    }
    return 0;
}
