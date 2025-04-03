/*
** EPITECH PROJECT, 2025
** solve_maze.c
** File description:
** Solving algorithm of the maze structure.
*/

#include "../../include/header_amazed.h"

int solve_maze(maze_t *maze)
{
    return SUCCESS;
}

static int find_mult_robot_move(room_t *current, maze_t *maze, int robot)
{
    tunnel_t *tunnel = NULL;

    if (current == NULL || current->links == NULL)
        return SUCCESS;
    for (int i = 0; current->links[i] != NULL; i++) {
        tunnel = get_tunnel(current, current->links[i], maze);
        if (tunnel == NULL)
            continue;
        if (tunnel->val == 1) {
            mini_printf("P%d-%s ", robot, current->links[i]->name);
            find_mult_robot_move(current->links[i], maze, robot);
            break;
        }
    }
    return SUCCESS;
}

int add_new_path(path_t **node, char *room)
{
    path_t *new_path = malloc(sizeof(path_t) * 1);
    path_t *current = *node;

    if (new_path == NULL)
        return ERROR;
    new_path->name = my_strdup(room);
    if (new_path->name == NULL) {
        free(new_path);
        return ERROR;
    }
    new_path->room = NULL;
    new_path->next = NULL;
    if (current == NULL) {
        *node = new_path;
        return SUCCESS;
    }
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_path;
    return SUCCESS;
}

static int find_robot_move(room_t *current, maze_t *maze, int robot,
    path_t **path)
{
    tunnel_t *tunnel = NULL;

    if (current == NULL || current->links == NULL)
        return SUCCESS;
    for (int i = 0; current->links[i] != NULL; i++) {
        tunnel = get_tunnel(current, current->links[i], maze);
        if (tunnel == NULL)
            continue;
        if (tunnel->val == 1) {
            tunnel->val = 2;
            add_new_path(path, current->links[i]->name);
            find_robot_move(current->links[i], maze, robot, path);
            break;
        }
    }
    return SUCCESS;
}

int find_solved_maze(maze_t *maze)
{
    path_t *good_path = NULL;
    path_t *path = NULL;

    if (maze == NULL)
        return ERROR;
    for (int i = 1; i <= maze->nb_robots; i++) {
        find_robot_move(maze->start, maze, i, &good_path);
    }
    path = good_path;
    while (path != NULL) {
        mini_printf("P%d-%s\n", 1, path->name);
        path = path->next;
    }
    return SUCCESS;
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
