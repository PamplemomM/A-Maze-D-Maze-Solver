/*
** EPITECH PROJECT, 2024
** amazed
** File description:
** struct.h
*/

#ifndef STRUCT_H
    #define STRUCT_H

    #include "header_amazed.h"

typedef struct room_s {
    char *name;
    int x;
    int y;
    struct room **links;
    struct room *next;
} room_t;

typedef struct maze_s {
    int nb_robots;
    room_t *rooms;
    room_t *start;
    room_t *end;
} maze_t;

// --- parse functions ---
int parse_room(maze_t *maze, char *line, int *special);
room_t *init_room(char *name, int x, int y);
room_t *find_room_name(room_t *room, char *name);
void add_room(char *name, int x, int y, room_t **room);
int link_counter(room_t *room);
int add_link(room_t *link, room_t *to);

#endif /* STRUCT_H */
