/*
** EPITECH PROJECT, 2025
** create_move_sequence.c
** File description:
** The file that will help creating the move sequence.
*/

#include "../../include/header_amazed.h"

int move_robot_untilend(pathlist_t **path, int start_id, int robot_id,
    maze_t *maze)
{
    pathlist_t *currentlist = *path;
    path_t *current = currentlist->path;
    int id = start_id;

    while (current != NULL) {
        mini_printf("Making the move for robot %d during %d in %s", robot_id, id, current->name);
        make_move(robot_id, current->room, id, maze);
        id++;
        current = current->next;
    }
    return SUCCESS;
}
