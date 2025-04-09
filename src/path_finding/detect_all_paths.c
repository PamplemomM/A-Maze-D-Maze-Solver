/*
** EPITECH PROJECT, 2025
** detect_all_paths.c
** File description:
** The file that will detect all the paths to the end.
*/

#include "../../include/header_amazed.h"

int get_pathlist_size(pathlist_t *paths)
{
    int cpt = 0;
    pathlist_t *current = paths;

    while (current != NULL) {
        cpt++;
        current = current->next;
    }
    return cpt;
}

int free_pathlist(pathlist_t *paths)
{
    pathlist_t *current = paths;
    pathlist_t *next = NULL;

    while (current != NULL) {
        next = current->next;
        free_paths(&current->path);
        free(current);
        current = next;
    }
    paths = NULL;
    return SUCCESS;
}

static int find_all_moves(room_t *current, maze_t *maze,
    path_t **path)
{
    tunnel_t *tunnel = NULL;
    tunnel_t *rev_tunnel = NULL;

    if (current == NULL || current->links == NULL)
        return SUCCESS;
    for (int i = 0; current->links[i] != NULL; i++) {
        tunnel = get_tunnel(current, current->links[i], maze);
        if (tunnel == NULL || tunnel->val == 1)
            continue;
        rev_tunnel = get_tunnel(current->links[i], current, maze);
        if (rev_tunnel != NULL)
            rev_tunnel->val = 1;
        tunnel->val = 1;
        if (find_all_moves(current->links[i], maze, path) == SUCCESS) {
            add_new_path(path, current->links[i]->name, TRUE);
            return SUCCESS;
        }
    }
    return ERROR;
}

int add_new_pathlist(pathlist_t **original, path_t *new)
{
    pathlist_t *current = *original;
    pathlist_t *new_list = NULL;

    if (new == NULL)
        return ERROR;
    new_list = malloc(sizeof(pathlist_t) * 1);
    if (new_list == NULL)
        return ERROR;
    new_list->path = new;
    new_list->length = my_linked_size(&new);
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

int create_new_pathlist(maze_t *maze, pathlist_t **paths)
{
    path_t *new_path = NULL;
    int value = 0;

    value = find_all_moves(maze->start, maze, &new_path);
    add_new_pathlist(paths, new_path);
    return value;
}

static int display_paths(int i, pathlist_t *paths)
{
    path_t *current = NULL;
    pathlist_t *cur_list = paths;

    if (cur_list == NULL)
        return ERROR;
    for (int j = 1; j < i && cur_list->next != NULL; j++) {
        cur_list = cur_list->next;
    }
    current = cur_list->path;
    while (current != NULL) {
        mini_printf("P%d-%s\n", i, current->name);
        current = current->next;
    }
    return SUCCESS;
}

pathlist_t *find_allpath(maze_t *maze)
{
    pathlist_t *paths = NULL;
    int value = 0;

    if (maze == NULL)
        return NULL;
    value = create_new_pathlist(maze, &paths);
    while (value == SUCCESS) {
        value = create_new_pathlist(maze, &paths);
    }
    return paths;
}
//for (int i = 1; i < maze->nb_robots + 1; i++)
//    display_paths(i, paths);
