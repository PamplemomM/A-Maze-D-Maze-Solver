/*
** EPITECH PROJECT, 2025
** gamestuff
** File description:
** Functions to manipulate the 'game_t' struct.
*/

#include "../include/header.h"

game_t **get_gamestuff(void)
{
    static game_t *game = NULL;

    return &game;
}

int init_gamestuff(void)
{
    GAME = malloc(sizeof(game_t));
    if (GAME == NULL)
        return ERROR;
    GAME->hue = diceroll(0, 360);
    return SUCCESS;
}

void destroy_gamestuff(void)
{
    if (GAME == NULL)
        return;
    free(GAME);
}
