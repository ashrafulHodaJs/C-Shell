#include <stdio.h>
#include "colors.h"

void print_green(const char *text)
{
    printf("\033[0;32m%s\033[0m", text);
}

void print_red(const char *text)
{
    printf("\033[0;31m%s\033[0m", text);
}

void print_yellow(const char *text)
{
    printf("\033[0;33m%s\033[0m", text);
}
