/*
** EPITECH PROJECT, 2025
** main_amazed.c
** File description:
** Main file for the A-Maze-d project.
*/

#include "../include/header_amazed.h"

int main(int argc)
{
    maze_t *maze = parse_maze(0);

    if (maze == NULL)
        return ERROR;
    print_maze(maze);
    if (argc != 1)
        find_solved_maze_one_line(maze);
    else
        find_solved_maze(maze);
    free_maze(&maze);
    return SUCCESS;
}
