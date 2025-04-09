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
