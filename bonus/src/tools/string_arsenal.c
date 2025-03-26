/*
** EPITECH PROJECT, 2025
** string_arsenal.c
** File description:
** An arsenal of functions that concern strings.
*/

#include "../../include/header_tools.h"
#include <string.h>
#include <stddef.h>
#include <stdlib.h>

char *merge_str(char *s1, char *s2)
{
    char *str[2] = {s1, s2};
    char *result = NULL;
    int len = 0;

    if (s1 == NULL || s2 == NULL)
        return NULL;
    len = strlen(s1) + strlen(s2);
    result = malloc(sizeof(char) * (len + 1));
    if (result == NULL)
        return NULL;
    for (int i = 0; i < strlen(s1); i++)
        result[i] = s1[i];
    for (int j = 0; j < strlen(s2); j++)
        result[j + strlen(s1)] = s2[j];
    result[len] = '\0';
    return result;
}

char *int_to_str(int nbr)
{
    char *str;
    int len = digitcount(nbr);

    str = malloc(sizeof(char) * (len + 1));
    if (str == NULL)
        return NULL;
    for (int i = 0; i < len; i++) {
        str[len - i - 1] = nbr % 10 + '0';
        nbr /= 10;
    }
    str[len] = '\0';
    return str;
}
