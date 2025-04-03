/*
** EPITECH PROJECT, 2025
** move_robots.c
** File description:
** Moving algorithm of the best path.
*/

#include "../../include/header_amazed.h"

static int dup_pathlist(path_t **good_path, maze_t *maze)
{
    path_t *pathlist = *good_path;
    int size = 0;
    char **path = NULL;

    while (pathlist != NULL) {
        size++;
        pathlist = pathlist->next;
    }
    path = malloc(sizeof(char *) * (size + 1));
    if (path == NULL)
        return ERROR;
    
    return SUCCESS;
}

int move_robots(path_t **good_path, maze_t *maze)
{
    path_t *pathlist = *good_path;

    while (pathlist != NULL) {
        for (int i = 1; i < maze->nb_robots + 1; i++)
            mini_printf("P%d-%s\n", i, pathlist->name);
        pathlist = pathlist->next;
    }
    return SUCCESS;
}

