/*
** EPITECH PROJECT, 2025
** amazed_data.c
** File description:
** Functions to manipulate and store the received maze data.
*/

#include "../include/header_viewer.h"

maze_t **get_maze(void)
{
    static maze_t *maze = NULL;

    return &maze;
}

room_t **get_rooms(void)
{
    return &(MAZE->rooms);
}

tunnel_t **get_tunnels(void)
{
    return &(MAZE->tunnels);
}

void free_room(room_t *room)
{
    if (room == NULL)
        return;
    OMNIFREE(room->name, 1);
    OMNIFREE(room->links, 1);
    OMNIFREE(room, 1);
}

void free_tunnel(tunnel_t *tunnel)
{
    OMNIFREE(tunnel, 1);
}
