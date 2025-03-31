/*
** EPITECH PROJECT, 2025
** header_viewer.h
** File description:
** Header for the A-Maze-d viewer.
*/

#ifndef AMAZEDVIS_H
    #define AMAZEDVIS_H

    #include "../../include/header_amazed.h"
    #include "header_tools.h"
    #include "header_csfml.h"
    #include <time.h>

    // functions:
    #define GAME (*get_gamestuff())
    #define MAZE (*get_maze())

    // values:
    #define HUESHIFT 0.5


// --------- VIEWER STRUCTURES ---------

typedef struct vwr_robot_s {
    struct vwr_robot_s *next;
    int id;
    sprite_t *sprite;
    room_t *room;
    room_t *move_to;
} vwr_robot_t; // robot structure for the viewer

typedef struct game {
    float hue;
    float move_id;
    int nb_moves;
} game_t; // miscellaneous data that needs to be globalized


// --------- VIEWER FUNCTIONS ----------

// --- amazed_data.c ---
maze_t **get_maze(void);
int read_maze(void);

// --- gamestuff.c ---
game_t **get_gamestuff(void);
int init_gamestuff(void);
void destroy_gamestuff(void);

// --- init_assets.c ---
int init_assets(void);
void destroy_assets(void);

// --- robots_list.c ---
vwr_robot_t **get_robotlist(void);
vwr_robot_t *get_robot(int id);
vwr_robot_t *make_robot(int id);
void free_robot(vwr_robot_t *robot);

#endif /* AMAZEDVIS_H */
