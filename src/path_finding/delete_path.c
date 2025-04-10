/*
** EPITECH PROJECT, 2025
** delete_path.c
** File description:
** The file that will delete the paths.
*/

#include "../../include/header_amazed.h"

static int free_singlepath(pathlist_t *node)
{
    if (node != NULL) {
        free_paths(&node->path);
        free(node);
    }
    return SUCCESS;
}

static int destroy_first(pathlist_t *list)
{
    pathlist_t *next = NULL;

    if (list == NULL)
        return;
    next = list->next;
    free_singlepath(list);
    list = next;
    return SUCCESS;
}

