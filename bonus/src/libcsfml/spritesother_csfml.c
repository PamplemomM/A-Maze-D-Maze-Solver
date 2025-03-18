/*
** EPITECH PROJECT, 2025
** spritesother_csfml
** File description:
** More sprite related functions.
*/

#include "../../include/header_csfml.h"

void draw_allsprites(void)
{
    sprite_t *sprite = *get_spritelist();

    while (sprite != NULL) {
        draw_sprite(sprite);
        sprite = sprite->next;
    }
}
