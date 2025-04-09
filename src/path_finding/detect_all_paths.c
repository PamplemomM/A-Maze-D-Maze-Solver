/*
** EPITECH PROJECT, 2025
** detect_all_paths.c
** File description:
** The file that will detect all the paths to the end.
*/

#include "../../include/header_amazed.h"

int free_pathlist(pathlist_t *paths)
{
    pathlist_t *current = paths;
    pathlist_t *next = NULL;

    while (current != NULL) {
        next = current->next;
        free_paths(&current->path);
        current = next;
    }
    paths = NULL;
    return SUCCESS;
}

pathlist_t *find_allpath(maze_t *maze)
{
    pathlist_t *paths = NULL;

    if (maze == NULL)
        return NULL;
    for (int i = 1; i <= maze->nb_robots; i++) {
        continue;
    }
    return paths;
}
