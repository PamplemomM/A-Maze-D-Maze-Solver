/*
** EPITECH PROJECT, 2025
** ultralen.c
** File description:
** Measure anything.
*/

#include "../../include/header_tools.h"

int ultralen(void **thing, void *end)
{
    int len = 0;

    if (thing == NULL)
        return 0;
    while (thing[len] != end)
        len++;
    return len;
}
