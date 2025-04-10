/*
** EPITECH PROJECT, 2025
** sort_path.c
** File description:
** The file that will sort all the paths.
*/

#include "../../include/header_amazed.h"

static int sort_path(pathlist_t **paths)
{
    pathlist_t *list = NULL;
    pathlist_t *current = *paths;
    pathlist_t *next;

    while (current != NULL) {
        next = current->next;
        current->next = NULL;
        insert_list(&list, current);
        current = next;
    }
    *paths = list;
    return SUCCESS;
}

