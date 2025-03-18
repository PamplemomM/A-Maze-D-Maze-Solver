/*
** EPITECH PROJECT, 2025
** header
** File description:
** Header for the A-Maze-d visualizer.
*/

#ifndef AMAZEDVIS_H
    #define AMAZEDVIS_H

    #define OMNIFREE(thing, dimension) omnifree((void **)thing, dimension)
    #define GAME (*get_gamestuff())
    #define DATA (*get_data())

    #include "header_csfml.h"
    #include <unistd.h>
    #include <stdio.h>
    #include <time.h>

typedef struct game {
    float hue;
} game_t;

typedef struct room {
    char *name;
    struct room **links;
    struct room *next;
} room_t;

typedef struct move {
    int movecnt;
    struct room *next;
} move_t;

typedef struct data {
    int robotcnt;
    room_t *rooms;
    move_t *moves;
} data_t;

void *init_assets(void);
void destroy_assets(void);

game_t **get_gamestuff(void);
game_t *init_gamestuff(void);

data_t **get_data(void);

sfColor color_from_hue(float hue, float brightness, float saturation);
int diceroll(int low, int high);
int digitcount(int nbr);
char *int_to_str(int nbr);

void *omnifree(void **thing, int dimension);

#endif /* AMAZEDVIS_H */
