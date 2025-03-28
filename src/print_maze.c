/*
** EPITECH PROJECT, 2025
** print_maze.c
** File description:
** Printing the maze.
*/

#include "../include/header_amazed.h"

static void print_tunnels(tunnel_t *tunnel)
{
    if (tunnel == NULL)
        return;
    while (tunnel != NULL) {
        PRINT("%s-%s\n", tunnel->r1->name, tunnel->r2->name);
        tunnel = tunnel->next;
    }
}

static void print_rooms(room_t *room, maze_t *maze)
{
    if (room == NULL)
        return;
    while (room != NULL) {
        if (room == maze->start)
            mini_printf("##start\n");
        if (room == maze->end)
            mini_printf("##end\n");
        PRINT("%s %d %d\n", room->name, room->x, room->y);
        room = room->next;
    }
}

void print_maze(maze_t *maze)
{
    if (maze == NULL)
        return;
    mini_printf("#number_of_robots\n");
    PRINT("%d\n", maze->nb_robots);
    mini_printf("#rooms\n");
    print_rooms(maze->rooms, maze);
    mini_printf("#tunnels\n");
    print_tunnels(maze->tunnels);
    mini_printf("#moves\n");
}
