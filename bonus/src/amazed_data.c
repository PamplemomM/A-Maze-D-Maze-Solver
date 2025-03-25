/*
** EPITECH PROJECT, 2025
** amazed_data
** File description:
** Functions to manipulate and store the A-Maze-d data.
*/

#include "../include/header_viewer.h"

maze_t **get_maze(void)
{
    static maze_t *maze = NULL;

    return &maze;
}

static int parse_moves(void)
{
    return SUCCESS;
}

int read_maze(void)
{
    MAZE = parse_maze(VIEWER);
    if (MAZE == NULL)
        return ERROR;
    return parse_moves();
}
