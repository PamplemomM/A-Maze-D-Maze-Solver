/*
** EPITECH PROJECT, 2024
** main_amazed.c
** File description:
** the main file for the amazed project.
*/
#include "../include/struct.h"
#include "../include/header_amazed.h"

void print_rooms_rev(room_t *room, maze_t *maze)
{
    if (room == NULL)
        return;
    print_rooms_rev(room->next, maze);
    if (room == maze->start)
        mini_printf("##start\n");
    if (room == maze->end)
        mini_printf("##end\n");
    mini_printf("%s %d %d\n", room->name, room->x, room->y);
}

void print_maze(maze_t *maze)
{
    mini_printf("#number_of_robots\n");
    mini_printf("%d\n", maze->nb_robots);
    mini_printf("#rooms\n");
    print_rooms_rev(maze->rooms, maze);
    mini_printf("#tunnels\n");
    mini_printf("#moves\n");
}

int main(int ac, char **av)
{
    maze_t *maze = parse_maze();

    print_maze(maze);
    free_maze(maze);
    return SUCCESS;
}
