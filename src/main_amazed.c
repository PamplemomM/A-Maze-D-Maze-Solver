/*
** EPITECH PROJECT, 2025
** main_amazed.c
** File description:
** Main file for the A-Maze-d project.
*/

#include "../include/header_amazed.h"

int main(void)
{
    maze_t *maze = parse_maze(0);

    if (maze == NULL)
        return ERROR;
    print_maze(maze);
    find_solved_maze(maze);
    free_maze(&maze);
    return SUCCESS;
}
