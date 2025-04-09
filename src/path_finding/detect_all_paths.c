/*
** EPITECH PROJECT, 2025
** detect_all_paths.c
** File description:
** The file that will detect all the paths to the end.
*/

#include "../../include/header_amazed.h"

int free_pathlist(pathlist_t *paths)
{
    pathlist_t *current = paths;
    pathlist_t *next = NULL;

    while (current != NULL) {
        next = current->next;
        free_paths(&current->path);
        current = next;
    }
    paths = NULL;
    return SUCCESS;
}

static int find_all_moves(room_t *current, maze_t *maze,
    path_t **path)
{
    tunnel_t *tunnel = NULL;

    if (current == NULL || current->links == NULL)
        return SUCCESS;
    for (int i = 0; current->links[i] != NULL; i++) {
        tunnel = get_tunnel(current, current->links[i], maze);
        if (tunnel == NULL || tunnel->val == 1)
            continue;
        tunnel->val = 1;
        if (find_robot_move(current->links[i], maze) == SUCCESS) {
            add_new_path(path, current->links[i]->name);
            return SUCCESS;
        }
    }
    return ERROR;
}

pathlist_t *find_allpath(maze_t *maze)
{
    pathlist_t *paths = NULL;

    if (maze == NULL)
        return NULL;
    for (int i = 1; i <= maze->nb_robots; i++) {
        continue;
    }
    return paths;
}
