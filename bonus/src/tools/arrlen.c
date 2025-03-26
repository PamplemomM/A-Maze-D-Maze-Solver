/*
** EPITECH PROJECT, 2025
** arrlen.c
** File description:
** Measure any NULL-terminated array.
*/

#include "../../include/header_tools.h"

long unsigned int arrlen(void **array)
{
    long unsigned int len = 0;

    if (array == NULL)
        return 0;
    while (array[len] != NULL)
        len++;
    return len;
}
