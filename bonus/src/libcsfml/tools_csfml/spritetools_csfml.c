/*
** EPITECH PROJECT, 2025
** spritetools_csfml.c
** File description:
** Sprite tool functions.
*/

#include "../../../include/header_csfml.h"

void draw_allsprites(element_type_t type)
{
    sprite_t *sprite = *get_spritelist();

    while (sprite != NULL) {
        if (type == ANY || sprite->type == type)
            draw_sprite(sprite);
        sprite = sprite->next;
    }
}

void center_sprite_origin(sprite_t *sprite, float xfact, float yfact)
{
    float x = sprite->rect.width * xfact;
    float y = sprite->rect.height * yfact;

    sfSprite_setOrigin(sprite->sprite, (sfVector2f){x, y});
}
