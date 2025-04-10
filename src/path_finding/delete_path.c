/*
** EPITECH PROJECT, 2025
** delete_path.c
** File description:
** The file that will delete the paths.
*/

#include "../../include/header_amazed.h"

static int free_pathlist(pathlist_t *node)
{
    if (node != NULL) {
        free_paths(&node->path);
        free(node);
    }
    return SUCCESS;
}

