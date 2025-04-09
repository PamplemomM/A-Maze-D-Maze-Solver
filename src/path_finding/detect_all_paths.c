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
        if (find_all_moves(current->links[i], maze, path) == SUCCESS) {
            add_new_path(path, current->links[i]->name);
            return SUCCESS;
        }
    }
    return ERROR;
}

int add_new_pathlist(pathlist_t **original, path_t *new)
{
    pathlist_t *current = *original;
    pathlist_t *new_list = malloc(sizeof(pathlist_t) * 1);

    if (new_list == NULL || *original == NULL || new == NULL ||
        current == NULL)
        return ERROR;
    new_list->path = new;
    new_list->lenght = my_linked_size(&new);
    new_list->next = NULL;
    if (current == NULL) {
        *original = new_list;
        return SUCCESS;
    }
    while (current->next != NULL)
        current = current->next;
    current->next = new_list;
    return SUCCESS;
}

int create_new_pathlist(maze_t *maze, pathlist_t *paths)
{
    path_t *new_path = NULL;
    path_t *current = paths->path;
    int value = 0;

    new_path->next = NULL;
    value = find_all_moves(maze->start, maze, &new_path);
    add_new_pathlist(&paths, new_path);
    return value;
}

pathlist_t *find_allpath(maze_t *maze)
{
    pathlist_t *paths = NULL;
    int value = 0;

    if (maze == NULL)
        return NULL;
    while (value == SUCCESS) {
        value = create_new_path(maze, paths);
    }
    return paths;
}
