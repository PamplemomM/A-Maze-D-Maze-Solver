/*
** EPITECH PROJECT, 2024
** my_str_to_word_array.c
** File description:
** The file for the function my_str_to_word_array.c.
*/
#include "../../include/header_amazed.h"

static int replace_me_those_spaces(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\\' && str[i + 1] == 't') {
            str[i] = ' ';
            str[i + 1] = ' ';
        }
        if (str[i] == '\t' || str[i] == ',')
            str[i] = ' ';
    }
    return SUCCESS;
}

static int found_line_len(char *str, int i)
{
    int result = 0;

    if (i > my_strlen(str))
        return 0;
    while (str[i] != ' ' && str[i] != '\0') {
        result++;
        i++;
    }
    return result;
}

static int looping(char *str, int *i)
{
    while (str[*i] == ' ') {
        (*i)++;
    }
    return 1;
}

static int count_words(char *str)
{
    int count = 1;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ') {
            count += looping(str, &i);
        }
    }
    return count;
}

static int condition(char *str, int i)
{
    while (str[i] == ' ') {
            i++;
    }
    return i;
}

static int init_inside(char **res, char *str, int *i, int *j)
{
    int word_len = found_line_len(str, *i);
    int k = 0;

    res[*j] = malloc(sizeof(char) * (word_len + 1));
    if (res[*j] == NULL) {
        for (int x = 0; x < *j; x++) {
            free(res[x]);
        }
        free(res);
        return ERROR;
    }
    while (str[*i] != '\0' && str[*i] != ' ') {
        res[*j][k] = str[*i];
        (*i)++;
        k++;
    }
    res[*j][k] = '\0';
    (*j)++;
    return SUCCESS;
}

char **my_str_to_word_array(char *str)
{
    int j = 0;
    int failed = 0;
    int size = count_words(str);
    char **res = malloc(sizeof(char *) * (size + 1));

    if (res == NULL)
        return NULL;
    replace_me_those_spaces(str);
    for (int i = 0; str[i] != '\0'; i = condition(str, i)) {
        if (str[i] != ' ')
            failed = init_inside(res, str, &i, &j);
        if (failed == ERROR || j >= size)
            return NULL;
    }
    res[j] = NULL;
    return res;
}

void free_word_array(char **wa)
{
    if (wa == NULL) {
        return;
    }
    for (int i = 0; wa[i] != NULL; i++) {
        free(wa[i]);
    }
    free(wa);
}

int my_print_wa(char **wa)
{
    for (int i = 0; wa[i] != NULL; i++) {
        for (int j = 0; wa[i][j] != '\0'; j++) {
            write(1, &wa[i][j], 1);
        }
        write(1, "\n", 1);
    }
    return SUCCESS;
}
