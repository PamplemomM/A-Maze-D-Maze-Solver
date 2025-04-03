/*
** EPITECH PROJECT, 2025
** move_robots.c
** File description:
** Moving algorithm of the best path.
*/

#include "../../include/header_amazed.h"

static char **dup_pathlist(path_t **good_path, maze_t *maze)
{
    path_t *current = *good_path;
    int size = 0;
    int i = 0;
    char **path = NULL;

    while (current != NULL) {
        size++;
        current = current->next;
    }
    path = malloc(sizeof(char *) * (size + 1));
    if (path == NULL)
        return NULL;
    current = *good_path;
    while (current != NULL) {
        path[i] = my_strdup(current->name);
        i++;
        current = current->next;
    }
    path[i] = NULL;
    return path;
}

int display_robots_move(path_t **good_path, maze_t *maze)
{
    path_t *pathlist = *good_path;
    char **path = dup_pathlist(good_path, maze);

    if (path == NULL)
        return ERROR;
    for (int i = 0; path[i] != NULL; i++) {
        for (int j = 1; j < maze->nb_robots + 1; j++)
            mini_printf("P%d-%s\n", j, path[i]);
    }
    while (pathlist != NULL) {
        for (int i = 1; i < maze->nb_robots + 1; i++)
            mini_printf("P%d-%s\n", i, pathlist->name);
        pathlist = pathlist->next;
    }
    return SUCCESS;
}

