/*
** EPITECH PROJECT, 2025
** solve_maze.c
** File description:
** Solving algorithm of the maze structure.
*/

#include "../../include/header_amazed.h"

int free_paths(path_t **paths)
{
    path_t *current = *paths;
    path_t *next = NULL;

    while (current != NULL) {
        next = current->next;
        OMNIFREE(current->name, 1);
        OMNIFREE(current, 1);
        current = next;
    }
    *paths = NULL;
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

int push_path_front(path_t **node, path_t *new_path)
{
    new_path->next = *node;
    *node = new_path;
    return SUCCESS;
}

int push_path_back(path_t **node, path_t *new_path)
{
    path_t *current = *node;

    new_path->next = NULL;
    if (current == NULL) {
        *node = new_path;
        return SUCCESS;
    }
    while (current->next != NULL)
        current = current->next;
    current->next = new_path;
    return SUCCESS;
}

int add_new_path(path_t **node, char *room)
{
    path_t *new_path = malloc(sizeof(path_t) * 1);

    if (new_path == NULL)
        return ERROR;
    new_path->name = my_strdup(room);
    if (new_path->name == NULL) {
        free(new_path);
        return ERROR;
    }
    new_path->room = NULL;
    new_path->next = *node;
    *node = new_path;
    return SUCCESS;
}

static int find_robot_move(room_t *current, maze_t *maze,
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
            find_robot_move(current->links[i], maze, path);
            break;
        }
    }
    return SUCCESS;
}

int find_solved_maze_one_line(maze_t *maze)
{
    path_t *good_path = NULL;

    if (maze == NULL)
        return ERROR;
    find_robot_move(maze->start, maze, &good_path);
    display_robots_move_singlepath(&good_path, maze);
    free_paths(&good_path);
    return SUCCESS;
}

int find_solved_maze(maze_t *maze)
{
    path_t *good_path = NULL;

    if (maze == NULL)
        return ERROR;
    free_pathlist(find_allpath(maze));
    return SUCCESS;
}

int detect_moves(maze_t *maze)
{
    move_t *moves = NULL;
    int id = 0;

    if (maze == NULL)
        return ERROR;
    moves = find_moves(maze, id);
    free_moves(moves);
    return SUCCESS;
}
