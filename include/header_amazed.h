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
    #include <stdbool.h>

    // defines:
    #define SUCCESS 0
    #define ERROR 84
    #define TRUE 1
    #define FALSE 0
    #define ABS(nb) (nb < 0) ? -nb : nb
    #define OMNIFREE(thing, dimension) omnifree((void ***)&thing, dimension)
    #define PRINT(format, ...) mini_printf(format, __VA_ARGS__)

// -------- A-MAZE-D STRUCTURES --------

typedef struct room_s {
    struct room_s *next;
    char *name;
    int x;
    int y;
    struct room_s **links;
} room_t;

typedef struct path_s {
    struct path_s *next;
    char *name;
    room_t *room;
} path_t;

typedef struct pathlist_s {
    path_t *path;
    int length;
    struct pathlist_s *next;
} pathlist_t;

typedef struct tunnel_s {
    struct tunnel_s *next;
    room_t *r1;
    room_t *r2;
    int val;
} tunnel_t;

typedef struct move_s {
    struct move_s *next;
    int id;
    int robot;
    room_t *dest;
} move_t;

typedef struct maze_s {
    int nb_robots;
    room_t *rooms;
    room_t *start;
    room_t *end;
    tunnel_t *tunnels;
    move_t *moves;
    int viewer;
} maze_t;


// --------- A-MAZE-D FUNCTIONS --------

// --- print_maze.c ---
void print_maze(maze_t *maze);

// --- free_maze.c ---
void free_rooms(room_t *room);
void free_tunnels(tunnel_t *tunnel);
void free_moves(move_t *move);
void free_maze(maze_t **maze);


// ----------- PARSING FOLDER -----------

// --- parse_maze.c ---
int give_up(char const *message, maze_t **maze);
tunnel_t *get_tunnel(room_t *r1, room_t *r2, maze_t *maze);
int end_of_file(int return_value, char **line);
maze_t *parse_maze(int viewer);

// --- parse_room.c ---
room_t *get_room(char *name, maze_t *maze);
int add_room(char *name, int x, int y, maze_t **maze);
char *get_name(char *line, int *i, char const *separators);
int parse_room(maze_t **maze, char *line, int *special);

// --- parse_tunnel.c ---
int add_tunnel(room_t *r1, room_t *r2, maze_t **maze);
int connect_rooms(room_t *r1, room_t *r2);
int parse_tunnel(maze_t **maze, char *line);


// --------- PATH_FINDING FOLDER ---------

// --- detect_all_paths.c ---
int get_pathlist_size(pathlist_t *paths);
int free_pathlist(pathlist_t *paths);
int add_new_pathlist(pathlist_t **original, path_t *new);
int create_new_pathlist(maze_t *maze, pathlist_t **paths);
pathlist_t *find_allpath(maze_t *maze);

// --- display_robots_move.c ---
int get_movelength(int path_size, int robot_count);
int my_linked_size(path_t **node);
int display_robots_move_singlepath(path_t *good_path, maze_t *maze);

// --- display_robot_path.c ---
path_t *get_shortest_path_temp(pathlist_t *paths);
int calculate_paths_proportion(pathlist_t *paths, maze_t *maze);

// --- make_move.c ---
move_t *make_move(int robot_id, room_t *dest, int move_id, maze_t *maze);

// --- push_topath.c ---
int push_path_front(path_t **node, path_t *new_path);
int push_path_back(path_t **node, path_t *new_path);

// --- find_moves.c ---
move_t *find_moves(maze_t *maze, int current_id);

// --- solve_maze.c ---
int free_paths(path_t **paths);
int add_new_path(path_t **node, char *room, int pushing);
int find_solved_maze(maze_t *maze);


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

// --- omnifree.c ---
void *omnifree(void ***thing, int dimension);

#endif /* AMAZED_H */
