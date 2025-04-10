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

/*
  If pushing equals to 0, this means it's a push back,
  else, it's a push front.
*/
int add_new_path(path_t **node, char *room, int pushing)
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
    if (pushing == 0)
        push_path_back(node, new_path);
    else
        push_path_front(node, new_path);
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
            add_new_path(path, current->links[i]->name, FALSE);
            find_robot_move(current->links[i], maze, path);
            break;
        }
    }
    return SUCCESS;
}

int find_solved_maze_one_line(maze_t *maze)
{
    path_t *good_path = NULL;
    pathlist_t *paths = NULL;

    if (maze == NULL)
        return ERROR;
    find_robot_move(maze->start, maze, &good_path);
    free_paths(&good_path);
    paths = find_allpath(maze);
    good_path = get_shortest_path_temp(paths);
    display_robots_move_singlepath(good_path, maze);
    free_pathlist(paths);
    return SUCCESS;
}

int find_solved_maze(maze_t *maze)
{
    path_t *good_path = NULL;
    pathlist_t *paths = NULL;

    if (maze == NULL)
        return ERROR;
    find_robot_move(maze->start, maze, &good_path);
    free_paths(&good_path);
    paths = find_allpath(maze);
    calculate_paths_proportion(paths, maze);
    mini_printf("%d paths founds!", get_pathcount(paths));
    good_path = get_shortest_path_temp(paths);
    display_robots_move_singlepath(good_path, maze);
    free_pathlist(paths);
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
