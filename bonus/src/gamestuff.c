/*
** EPITECH PROJECT, 2025
** gamestuff.c
** File description:
** Functions to manipulate the 'game_t' struct.
*/

#include "../include/header_viewer.h"

game_t **get_gamestuff(void)
{
    static game_t *game = NULL;

    return &game;
}

int init_gamestuff(void)
{
    move_t *move = MAZE->moves;

    GAME = malloc(sizeof(game_t));
    if (GAME == NULL)
        return ERROR;
    GAME->state = PAUSE;
    GAME->logs = 0;
    GAME->bounds = (sfIntRect){0, 0, 800, 600};
    GAME->hue = diceroll(0, 360);
    GAME->robots_order = NULL;
    GAME->move_id = 0;
    GAME->nb_moves = 0;
    if (move == NULL)
        return ERROR;
    while (move->next != NULL)
        move = move->next;
    GAME->nb_moves = move->id + 1;
    return SUCCESS;
}

void destroy_gamestuff(void)
{
    if (GAME == NULL)
        return;
    OMNIFREE(GAME->robots_order, 1);
    OMNIFREE(GAME, 1);
}
