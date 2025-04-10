/*
** EPITECH PROJECT, 2025
** sort_path.c
** File description:
** The file that will sort all the paths.
*/

#include "../../include/header_amazed.h"

static int insert_list(pathlist_t **paths, pathlist_t *new_node)
{
    pathlist_t *current = *paths;

    if (*paths == NULL || (*paths)->length > new_node->length) {
        new_node->next = *paths;
        *list = new_node;
        return SUCCESS;
    }
    while (current->next != NULL &&
        current->next->length > new_node->length)) {
        current = current->next;
    }
    new_node->next = current->next;
    current->next = new_node;
    return SUCCESS;
}

int sort_path(pathlist_t **paths)
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

