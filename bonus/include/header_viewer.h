/*
** EPITECH PROJECT, 2025
** header_viewer
** File description:
** Header for the A-Maze-d visualizer.
*/

#ifndef AMAZEDVIS_H
    #define AMAZEDVIS_H

    #include "../include/header_amazed.h"
    #include "header_csfml.h"
    #include <time.h>

    // defines:
    #define SDFREE(format, ...) salade_de_free(format, __VA_ARGS__)
    #define GAME (*get_gamestuff())
    #define MAZE (*get_maze())

    #define HUESHIFT 0.5

typedef struct game {
    float hue;
    int nb_moves;
} game_t;

int init_assets(void);
void destroy_assets(void);

game_t **get_gamestuff(void);
int init_gamestuff(void);
void destroy_gamestuff(void);

maze_t **get_maze(void);
int read_maze(void);

sfColor color_from_hue(float hue, float brightness,
    float saturation, float opacity);
int diceroll(int low, int high);
int digitcount(int nbr);
char *int_to_str(int nbr);

void *salade_de_free(char const *format, ...);

#endif /* AMAZEDVIS_H */
