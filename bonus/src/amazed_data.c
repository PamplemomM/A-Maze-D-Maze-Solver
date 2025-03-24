/*
** EPITECH PROJECT, 2025
** amazed_data
** File description:
** Functions to manipulate and store the A-Maze-d data.
*/

#include "../include/header.h"

maze_t **get_maze(void)
{
    static maze_t *maze = NULL;

    return &maze;
}

int read_maze(void)
{
    MAZE = parse_maze();
    if (MAZE == NULL)
        return ERROR;
    return SUCCESS;
}
