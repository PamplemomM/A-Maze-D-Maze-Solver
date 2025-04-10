/*
** EPITECH PROJECT, 2025
** sort_pathlist.c
** File description:
** The file that will sort all the pathlist.
*/

#include "../../include/header_amazed.h"

int sort_paths(pathlist_t **paths)
{
    pathlist_t *current = *paths;
    pathlist_t *temp = NULL;

    if (paths == NULL || *paths == NULL || (*paths)->next == NULL)
        return SUCCESS;
    while (current->next != NULL) {
        if (current->length > current->next->length) {
            temp = current->next;
            current->next = temp->next;
            temp->next = current;
            *paths = (current == *paths) ? temp : *paths;
            sort_paths(paths);
            return SUCCESS;
        }
        current = current->next;
    }
    return SUCCESS;
}

int insert_list(pathlist_t **paths, pathlist_t *new_node)
{
    pathlist_t *current = *paths;

    if (*paths == NULL || (*paths)->length < new_node->length) {
        new_node->next = *paths;
        *paths = new_node;
        return SUCCESS;
    }
    while (current->next != NULL &&
        current->next->length > new_node->length) {
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

