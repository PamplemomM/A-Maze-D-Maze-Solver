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
    #define HUESHIFT 0.25


// --------- VIEWER STRUCTURES ---------

typedef enum game_states_s {
    PLAY,
    PAUSE,
    REWIND
} gamestate_t;

typedef struct vwr_robot_s {
    struct vwr_robot_s *next;
    int id;
    sprite_t *sprite;
    room_t *room;
    room_t *move_to;
} vwr_robot_t; // robot structure for the viewer

typedef struct game {
    gamestate_t state;
    int logs;
    sfIntRect bounds;
    float hue;
    vwr_robot_t **robots_order;
    float move_id;
    int nb_moves;
} game_t; // miscellaneous data that needs to be globalized


// --------- VIEWER FUNCTIONS ----------

// --- move_robots.c ---
int move_allrobots_to(room_t *room);
void update_robots_rooms(int id);
int move_robots(float speed);

// --- interact_sim.c ---
void toggle_gamestate(gamestate_t state);
void start_sim(float start);
void interact_sim(void);

// --- interact_cam.c ---
void cam_move_mouse(sfMouseMoveEvent mouse);
void cam_zoom_mouse(sfMouseWheelScrollEvent mouse);
void cam_move_keys(void);

// --- logs.c ---
int add_to_logs(char *entry);
int add_logs_move(vwr_robot_t *robot, room_t *dest);

// --- update_robots.c ---
void hue_shift(void);
int update_robots(void);
void draw_robots(void);

// --- update_hud.c ---
void update_progbar(void);
void update_progbuff(int id);
void update_compass(void);

// --- gamestuff.c ---
game_t **get_gamestuff(void);
int init_gamestuff(void);
void destroy_gamestuff(void);

// --- amazed_data.c ---
maze_t **get_maze(void);
room_t **get_rooms(void);
tunnel_t **get_tunnels(void);
void free_room(room_t *room);
void free_tunnel(tunnel_t *tunnel);

// --- init_maze.c ---
int init_new_maze(void);
int read_maze(void);

// --- init_assets.c ---
int init_sounds(void);
int init_music(void);
int init_assets(void);
void destroy_assets(void);

// --- init_rooms.c ---
void setup_camera(void);
sfIntRect update_bounds(room_t *room);
int create_room_sprite(room_t *room);
int init_rooms(void);

// --- init_tunnels.c ---
int create_tunnel_sprite(tunnel_t *tunnel);
int init_tunnels(void);

// --- init_misc_assets.c ---
int init_blackscreen(void);
int init_compass(void);
int init_logs(void);
int init_progbar(void);
int init_bg(void);

// --- robots_list.c ---
vwr_robot_t **get_robotlist(void);
vwr_robot_t *get_robot(int id);
vwr_robot_t *make_robot(int id);
int init_robots(void);
void free_robot(vwr_robot_t *robot);

// --- main_maker.c ---
int start_maker(void);

#endif /* AMAZEDVIS_H */
