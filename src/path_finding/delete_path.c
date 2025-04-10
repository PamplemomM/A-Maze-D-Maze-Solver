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

static int destroy_firstpath(pathlist_t *paths)
{
    pathlist_t *next = NULL;

    if (paths == NULL)
        return;
    next = paths->next;
    free_singlepath(paths);
    paths = next;
    return SUCCESS;
}

static int destroy_lastpath(pathlist_t *paths)
{
    pathlist_t *current = paths;

    if (current->next == NULL) {
        free_singlepath(current);
        paths = NULL;
        return;
    }
    while (current->next->next != NULL)
        current = current->next;
    free_singlepath(current->next);
    current->next = NULL;
    return SUCCESS;
}

static int destroy_middlepath(pathlist_t *paths)
{
    pathlist_t *temp = NULL;

    temp = paths->next;
    paths->next = temp->next;
    free_singlepath(temp);
    return SUCCESS;
}

void delete_path_fromlist(pathlist_t *element, pathlist_t *paths)
{
    pathlist_t *current = paths;

    if (element == NULL)
        return;
    if (current == element) {
        destroy_firstpath(paths);
        return;
    }
    while (current->next != NULL) {
        if (current->next == element)
            break;
        current = current->next;
    }
    if (current->next == NULL) {
        destroy_lastpath(paths);
        return;
    }
    destroy_middlepath(paths);
}
