/*
** EPITECH PROJECT, 2025
** salade_de_free.c
** File description:
** Free anything.
*/

#include "../../include/header_viewer.h"
#include <stdarg.h>

void *salade_de_free(char const *format, ...)
{
    va_list arg;

    va_start(arg, format);
    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%')
            omnifree(va_arg(arg, void ***), format[i + 1] - '0');
    }
    va_end(arg);
    return NULL;
}
