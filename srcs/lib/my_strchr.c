/*
** EPITECH PROJECT, 2024
** robot_factory
** File description:
** my_strchr.c
*/
#include "../../include/header_amazed.h"

char *my_strchr(char const *str, int c)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == c)
            return (char *)&str[i];
    }
    return NULL;
}

char *my_strrchr(const char *str, int c)
{
    char *last_occurrence = NULL;
    unsigned char target = (unsigned char)c;

    if (str == NULL)
        return NULL;
    while (*str != '\0') {
        if ((unsigned char)*str == target) {
            last_occurrence = (char *)str;
        }
        str++;
    }
    if (target == '\0')
        return (char *)str;
    return last_occurrence;
}