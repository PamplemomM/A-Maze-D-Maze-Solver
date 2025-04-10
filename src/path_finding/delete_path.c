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

int delete_path_fromlist(pathlist_t *paths, pathlist_t *node)
{
    pathlist_t *temp = paths;
    pathlist_t *prev = temp;

    if (temp == node) {
        paths = temp->next;
        free_pathlist(temp);
        return SUCCESS;
    }
    temp = temp->next;
    while (temp != NULL) {
        if (temp == node) {
            prev->next = temp->next;
            free_pathlist(temp);
            return SUCCESS;
        }
        prev = temp;
        temp = temp->next;
    }
    return SUCCESS;
}

