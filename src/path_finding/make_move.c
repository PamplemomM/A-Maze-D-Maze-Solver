/*
** EPITECH PROJECT, 2025
** make_move.c
** File description:
** Adding a node to the move list.
*/

#include "../../include/header_amazed.h"

move_t *make_move_wthname(int robot_id, char *name, int move_id,
    maze_t *maze)
{
    move_t *headcpy = maze->moves;
    move_t *move = malloc(sizeof(move_t));

    if (move == NULL)
        return NULL;
    move->id = move_id;
    move->robot = robot_id;
    move->room_name = name;
    move->next = NULL;
    if (headcpy == NULL) {
        maze->moves = move;
        return move;
    }
    while (headcpy->next != NULL)
        headcpy = headcpy->next;
    headcpy->next = move;
    return move;
}

move_t *make_move(int robot_id, room_t *dest, int move_id, maze_t *maze)
{
    move_t *headcpy = maze->moves;
    move_t *move = malloc(sizeof(move_t));

    if (move == NULL)
        return NULL;
    move->id = move_id;
    move->robot = robot_id;
    move->dest = dest;
    move->next = NULL;
    if (headcpy == NULL) {
        maze->moves = move;
        return move;
    }
    while (headcpy->next != NULL)
        headcpy = headcpy->next;
    headcpy->next = move;
    return move;
}
