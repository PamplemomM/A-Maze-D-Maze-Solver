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

// ---Structure room initialisation---
room_t *init_room(char *name, int x, int y);
// ---Function to find the room's name---
room_t *find_room_name(room_t *room, char *name);
// ---Add a room in the structure
void add_room(char *name, int x, int y, room_t **room);

#endif /* STRUCT_H */
