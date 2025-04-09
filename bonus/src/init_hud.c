/*
** EPITECH PROJECT, 2025
** init_hud.c
** File description:
** Functions to initialize the program's HUD elements.
*/

#include "../include/header_viewer.h"

int init_compass(void)
{
    if (make_sprite("cmpa", "compass_arrow", 400, 300) == NULL)
        return ERROR;
    if (make_sprite("cmpp", "compass_pivot", 400, 300) == NULL)
        return ERROR;
    get_sprite("cmpa")->rect.width = 45;
    get_sprite("cmpa")->color.a = 0;
    get_sprite("cmpp")->color = color_from_hue(GAME->hue + 180,
        255, 255, 0);
    get_sprite("cmpa")->type = HUD;
    get_sprite("cmpp")->type = HUD;
    center_sprite_origin(get_sprite("cmpa"), 0.5, 4.0);
    center_sprite_origin(get_sprite("cmpp"), 0.5, 0.5);
    return SUCCESS;
}

int init_logs(void)
{
    if (make_sprite("logs", "AWESOME_PIXEL", -250, 0) == NULL)
        return ERROR;
    if (make_text("logstitle", "LOGS", -170, 1) == NULL)
        return ERROR;
    if (make_text("logstxt", "program launched", -243, 55) == NULL)
        return ERROR;
    get_sprite("logs")->scale = (sfVector2f){250, 600};
    get_sprite("logs")->color = color_from_hue(0, 0, 0, 150);
    get_sprite("logs")->type = HUD;
    get_text("logstitle")->scale = (sfVector2f){0.8, 0.7};
    get_text("logstitle")->color = color_from_hue(0, 255, 0, 255);
    get_text("logstitle")->type = HUD;
    get_text("logstxt")->scale = (sfVector2f){0.25, 0.25};
    get_text("logstxt")->color = color_from_hue(0, 255, 0, 255);
    get_text("logstxt")->type = HUD;
    return SUCCESS;
}

int init_progbar(void)
{
    if (make_sprite("barprog", "AWESOME_PIXEL", 150, 552) == NULL)
        return ERROR;
    if (make_sprite("barbuff", "AWESOME_PIXEL", 150, 540) == NULL)
        return ERROR;
    if (make_sprite("barbg", "AWESOME_PIXEL", 148, 538) == NULL)
        return ERROR;
    get_sprite("barbg")->scale = (sfVector2f){504, 28.5};
    get_sprite("barbg")->color = color_from_hue(0, 255, 0, 180);
    get_sprite("barbg")->type = HUD;
    get_sprite("barbuff")->scale = (sfVector2f){0, 24.5};
    get_sprite("barbuff")->color = color_from_hue(GAME->hue + 180,
        200, 255, 255);
    get_sprite("barbuff")->type = HUD;
    get_sprite("barprog")->scale = (sfVector2f){3, 36};
    get_sprite("barprog")->color = color_from_hue(0, 255, 0, 255);
    get_sprite("barprog")->type = HUD;
    center_sprite_origin(get_sprite("barprog"), 0.5, 0.5);
    return SUCCESS;
}
