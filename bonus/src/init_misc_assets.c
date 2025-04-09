/*
** EPITECH PROJECT, 2025
** init_misc_assets.c
** File description:
** Functions to initialize the program's miscellaneous assets.
*/

#include "../include/header_viewer.h"

int init_blackscreen(void)
{
    if (make_sprite("black", "AWESOME_PIXEL", -150, 0) == NULL)
        return ERROR;
    get_sprite("black")->scale = (sfVector2f){950, 600};
    get_sprite("black")->color = sfBlack;
    get_sprite("black")->type = HUD;
    make_tween("screen_fadein",
        (float *)&get_sprite("black")->color.a, 0, 4.0);
    return SUCCESS;
}

void setup_bg(int do_color)
{
    sfIntRect bounds = GAME->bounds;
    float scalex = (float)bounds.width / (float)get_sprite("bg")->rect.width;
    float scaley = (float)bounds.height / (float)get_sprite("bg")->rect.height;
    float diag = sqrt(pow(bounds.width, 2) + pow(bounds.height, 2));

    get_sprite("bg")->pos = (sfVector2f){bounds.left, bounds.top};
    get_sprite("bg")->scale = (sfVector2f){scalex, scaley};
    get_sprite("bg")->color = color_from_hue(0, 255, 255, 255);
    get_sprite("shadow")->pos = (sfVector2f){bounds.left,
        bounds.top + bounds.height};
    get_sprite("shadow")->scale = (sfVector2f){diag - 0.2, 10000};
    get_sprite("shadow")->angle = -atan2f(bounds.height,
        bounds.width) * 180.0 / M_PI;
    get_sprite("shadow")->color = color_from_hue(0, 0, 0, 75);
    get_sprite("light")->pos = (sfVector2f){(bounds.left + bounds.width) / 2.0,
        (bounds.top + bounds.height) / 2.0};
    get_sprite("light")->scale = (sfVector2f){15, 20};
    if (do_color)
        get_sprite("light")->color = color_from_hue(GAME->hue, 255, 255, 255);
    center_sprite_origin(get_sprite("light"), 0.5, 0.5);
}

int init_bg(void)
{
    if (make_sprite("bg", "bg", GAME->bounds.left, GAME->bounds.top) == NULL)
        return ERROR;
    if (make_sprite("shadow", "AWESOME_PIXEL", GAME->bounds.left,
        GAME->bounds.top + GAME->bounds.height) == NULL)
        return ERROR;
    if (make_sprite("light", "gradient",
        (GAME->bounds.left + GAME->bounds.width) / 2.0,
        (GAME->bounds.top + GAME->bounds.height) / 2.0) == NULL)
        return ERROR;
    setup_bg(1);
    return SUCCESS;
}
