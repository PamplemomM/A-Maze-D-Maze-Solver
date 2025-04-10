/*
** EPITECH PROJECT, 2025
** create_move_sequence.c
** File description:
** The file that will help creating the move sequence.
*/

#include "../../include/header_amazed.h"

int initialise_moving_sequence(pathlist_t **paths, maze_t *maze)
{
    pathlist_t *current = *paths;
    path_t *shortest_path = get_shortest_path_temp(paths);
    int shortest = my_linked_size(&shortest_path);
    int path_size = get_pathcount(paths);
    int start_id = 1;

    for (int i = 1; i < maze->nb_robots + 1; i++) {
        start_id = CEILING(maze->nb_robots / path_size);
        if (MAX(maze->nb_robots - start_id + 1, shortest + 1) >
            current->length + current->lower)
            move_robot_untilend(&current, start_id, i, maze);
        current = current->next;
        if (current == NULL)
            current = *paths;
    }
    return SUCCESS;
}

int move_robot_untilend(pathlist_t **path, int start_id, int robot_id,
    maze_t *maze)
{
    pathlist_t *currentlist = *path;
    path_t *current = currentlist->path;
    int id = start_id;

    while (current != NULL) {
        mini_printf("Making the move for robot %d during %d in %s\n", robot_id, id, current->name);
        //mini_printf("P%d-%s\n", robot_id, current->name);
        make_move(robot_id, current->room, id, maze);
        id++;
        current = current->next;
    }
    return SUCCESS;
}
