/*
** EPITECH PROJECT, 2025
** main_amazed.c
** File description:
** Main file for the A-Maze-d project.
*/

#include "../include/header_amazed.h"

static void print_tunnels_rev(tunnel_t *tunnel)
{
    if (tunnel == NULL)
        return;
    print_tunnels_rev(tunnel->next);
    PRINT("%s-%s\n", tunnel->r1->name, tunnel->r2->name);
}

static void print_rooms_rev(room_t *room, maze_t *maze)
{
    if (room == NULL)
        return;
    print_rooms_rev(room->next, maze);
    if (room == maze->start)
        mini_printf("##start\n");
    if (room == maze->end)
        mini_printf("##end\n");
    PRINT("%s %d %d\n", room->name, room->x, room->y);
}

void print_maze(maze_t *maze)
{
    if (maze == NULL)
        return;
    mini_printf("#number_of_robots\n");
    PRINT("%d\n", maze->nb_robots);
    mini_printf("#rooms\n");
    print_rooms_rev(maze->rooms, maze);
    mini_printf("#tunnels\n");
    print_tunnels_rev(maze->tunnels);
    mini_printf("#moves\n");
}

int main(void)
{
    maze_t *maze = parse_maze(MAIN);

    print_maze(maze);
    find_solved_maze(maze);
    free_maze(&maze);
    return SUCCESS;
}
