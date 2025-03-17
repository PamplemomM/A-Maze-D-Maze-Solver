/*
** EPITECH PROJECT, 2024
** robot_factory
** File description:
** my_strchr.c
*/
#include "../../include/header_amazed.h"

static int is_delimiter(char c, const char *delim)
{
    char *d = (char *)delim;

    for (d; *d != '\0'; d++) {
        if (c == *d) {
            return 1;
        }
        d = (char *)delim;
    }
    return SUCCESS;
}

static char *skip_delimiters(char *str, const char *delim)
{
    char *ptr = str;

    while (*ptr != '\0') {
        if (!is_delimiter(*ptr, delim)) {
            break;
        }
        ptr++;
    }
    return *ptr == '\0' ? NULL : ptr;
}

static char *find_token_end(char *str, const char *delim)
{
    char *ptr = str;

    while (*ptr != '\0') {
        if (is_delimiter(*ptr, delim)) {
            *ptr = '\0';
            return ptr + 1;
        }
        ptr++;
    }
    return NULL;
}

char *my_strtok(char *str, const char *delim)
{
    char *token_start;
    static char *saved_ptr = NULL;

    if (str != NULL)
        saved_ptr = str;
    if (saved_ptr == NULL)
        return NULL;
    token_start = skip_delimiters(saved_ptr, delim);
    if (token_start == NULL) {
        saved_ptr = NULL;
        return NULL;
    }
    saved_ptr = find_token_end(token_start, delim);
    return token_start;
}
