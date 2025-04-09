/*
** EPITECH PROJECT, 2025
** push_topath.c
** File description:
** The function for pushing to the path.
*/

#include "../../include/header_amazed.h"

int push_path_front(path_t **node, path_t *new_path)
{
    new_path->next = *node;
    *node = new_path;
    return SUCCESS;
}

int push_path_back(path_t **node, path_t *new_path)
{
    path_t *current = *node;

    new_path->next = NULL;
    if (current == NULL) {
        *node = new_path;
        return SUCCESS;
    }
    while (current->next != NULL)
        current = current->next;
    current->next = new_path;
    return SUCCESS;
}
