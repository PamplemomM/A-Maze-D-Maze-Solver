/*
** EPITECH PROJECT, 2025
** free_maze.c
** File description:
** Freeing the maze.
*/

#include "../include/header_amazed.h"

static void free_rooms(room_t *room)
{
    void *tmp = NULL;

    while (room != NULL) {
        tmp = room->next;
        OMNIFREE(room->name, 1);
        if (room->links != NULL)
            OMNIFREE(room->links, 1);
        OMNIFREE(room, 1);
        room = tmp;
    }
}

static void free_tunnels(tunnel_t *tunnel)
{
    void *tmp = NULL;

    while (tunnel != NULL) {
        tmp = tunnel->next;
        OMNIFREE(tunnel, 1);
        tunnel = tmp;
    }
}

static void free_moves(move_t *move)
{
    void *tmp = NULL;

    while (move != NULL) {
        tmp = move->next;
        OMNIFREE(move->robot, 1);
        OMNIFREE(move, 1);
        move = tmp;
    }
}

void free_maze(maze_t **maze)
{
    if (*maze == NULL)
        return;
    free_rooms((*maze)->rooms);
    free_tunnels((*maze)->tunnels);
    free_moves((*maze)->moves);
    OMNIFREE(*maze, 1);
}
