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

static int find_robot_move(room_t *current, maze_t *maze, int robot)
{
    tunnel_t *tunnel = NULL;

    if (current == NULL)
        return SUCCESS;
    for (int i = 0; current->links[i] != NULL; i++) {
        tunnel = get_tunnel(current, current->links[i], maze);
        if (tunnel == NULL)
            continue;
        if (tunnel->val == 1) {
            mini_printf("P%d-%s\n", robot, current->links[i]->name);
            find_robot_move(current->next, maze, robot);
        }
    }
    return SUCCESS;
}

int find_solved_maze(maze_t *maze)
{
    if (maze == NULL)
        return ERROR;
    for (int i = 1; i <= maze->nb_robots; i++) {
        find_robot_move(maze->start, maze, i);
    }
    return SUCCESS;
}

move_t *add_new_move(move_t **list, int id, int robot, room_t *dest)
{
    move_t *new_move = NULL;

    if (list == NULL || dest == NULL)
        return NULL;
    new_move = malloc(sizeof(move_t));
    if (new_move == NULL)
        return NULL;
    new_move->id = id;
    new_move->robot = robot;
    new_move->dest = dest;
    new_move->next = *list;
    *list = new_move;
    return new_move;
}

int detect_moves(maze_t *maze)
{
    move_t *moves = NULL;
    int id = 0;

    if (maze == NULL)
        return ERROR;
    moves = find_moves(maze, id);
    return SUCCESS;
}

void free_move_list(move_t *move_list)
{
    move_t *temp = NULL;

    while (move_list != NULL) {
        temp = move_list;
        move_list = move_list->next;
        free(temp);
    }
}
