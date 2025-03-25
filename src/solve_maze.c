/*
** EPITECH PROJECT, 2025
** solve_maze.c
** File description:
** Solving algorithm of the maze structure.
*/

#include "../include/header_amazed.h"

int solve_maze(maze_t *maze)
{
    return SUCCESS;
}

int find_robot_move(room_t *current, maze_t *maze)
{
    tunnel_t *tunnel = NULL;

    if (current == NULL)
        return SUCCESS;
    for (int i = 0; current->links[i] != NULL; i++) {
        tunnel = get_tunnel(current, current->links[i], maze);
        if (tunnel == NULL)
            continue;
        if (tunnel->val == 1) {
            tunnel->val = 1;
            mini_printf("P%d-%s\n", 1, current->links[i]->name);
            find_robot_move(current->next, maze);
        }
    }
    return SUCCESS;
}

int find_solved_maze(maze_t *maze)
{
    find_robot_move(maze->start, maze);
    return SUCCESS;
}