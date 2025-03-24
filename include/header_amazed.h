/*
** EPITECH PROJECT, 2025
** header_amazed.h
** File description:
** The header for the A-Maze-d project.
*/

#ifndef AMAZED_H
    #define AMAZED_H

    #include <stddef.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <stdio.h>

    // defines:
    #define SUCCESS 0
    #define ERROR 84
    #define OMNIFREE(thing, dimension) omnifree((void **)thing, dimension)

// -------- A-MAZE-D STRUCTURES --------

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

typedef struct move_s {
    int id;
    char *robot;
    room_t *dest;
    struct move_s *next;
} move_t;

typedef struct maze_s {
    int nb_robots;
    room_t *rooms;
    room_t *start;
    room_t *end;
    tunnel_t *tunnels;
    move_t *moves;
} maze_t;

// --------- A-MAZE-D FUNCTIONS --------

// --- parse_maze.c ---
void free_maze(maze_t *maze);
maze_t *parse_maze(void);

// --- parse_room.c ---
room_t *find_room_name(room_t *room, char *name);
char *get_name(char *line, int *i, char const *separators);
int parse_room(maze_t *maze, char *line, int *special);

// --- parse_tunnel.c ---
int parse_tunnel(maze_t *maze, char *line);

// ----------- LIB FUNCTIONS -----------

// --- lib_c_functions.c ---
int char_in_str(char ch, char const *str);
int my_getnbr(char const *str);
int mini_printf(const char *format, ...);

// --- my_stringlib.c ---
int my_strlen(char const *str);
char *my_strdup(char const *src);
char *my_strcpy(char *dest, char const *src);
int my_strcmp(char const *s1, char const *s2);
int my_strncmp(char const *s1, char const *s2, int n);

// --- my_str_to_word_array.c ---
char **my_str_to_word_array(char *str);
void free_word_array(char **wa);
int my_print_wa(char **wa);

// --- my_strchr.c ---
char *my_strchr(char const *str, int c);
char *my_strrchr(const char *str, int c);

// --- my_strtok.c ---
char *my_strtok(char *str, char const *delim);

// --- omnifree.c ---
void *omnifree(void **thing, int dimension);

#endif /* AMAZED_H */
