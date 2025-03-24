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
    struct room_s **links;
    struct room_s *next;
} room_t;

typedef struct tunnel_s {
    room_t *r1;
    room_t *r2;
    int val;
    struct tunnel_s *next;
} tunnel_t;

typedef struct maze_s {
    int nb_robots;
    room_t *rooms;
    room_t *start;
    room_t *end;
    tunnel_t *tunnels;
} maze_t;

// --- parse functions ---
void free_maze(maze_t *maze);
maze_t *parse_maze(void);
int parse_room(maze_t *maze, char *line, int *special);
int parse_tunnel(maze_t *maze, char *line);

// ---Function to find the room's name---
room_t *find_room_name(room_t *room, char *name);

// ---Get a room's name from a line---
char *get_name(char *line, int *i, char const *separators);

#endif /* STRUCT_H */
