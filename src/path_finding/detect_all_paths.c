/*
** EPITECH PROJECT, 2025
** detect_all_paths.c
** File description:
** The file that will detect all the paths to the end.
*/

#include "../../include/header_amazed.h"


pathlist_t *find_allpath(maze_t *maze)
{
    pathlist_t *paths = NULL;

    if (maze == NULL)
        return ERROR;
    for (int i = 1; i <= maze->nb_robots; i++) {
        find_robot_move(maze->start, maze, i, &good_path);
    }
    return paths;
}
