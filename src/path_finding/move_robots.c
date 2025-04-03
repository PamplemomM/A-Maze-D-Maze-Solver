/*
** EPITECH PROJECT, 2025
** move_robots.c
** File description:
** Moving algorithm of the best path.
*/

#include "../../include/header_amazed.h"

int move_robots(path_t **good_path, maze_t *maze)
{
    path_t *path = good_path;

    while (path != NULL) {
        for (int i = 1; i < maze->nb_robots + 1; i++)
            mini_printf("P%d-%s\n", i, path->name);
        path = path->next;
    }
    return SUCCESS;
}
