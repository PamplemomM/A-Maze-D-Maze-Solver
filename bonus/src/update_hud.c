/*
** EPITECH PROJECT, 2025
** update_hud.c
** File description:
** Functions to update the HUD elements.
*/

#include "../include/header_viewer.h"

void update_progbar(void)
{
    sprite_t *prog = get_sprite("barprog");

    make_tween("barprog", &prog->pos.x, (int)GAME->move_id /
        (float)GAME->nb_moves * 500.0 + 150, 0.2)->method = EASEOUT;
    prog->scale.x = MIN(prog->scale.x + 3, 15);
    prog->scale.y = MAX(prog->scale.y - 3, 30);
    make_tween("barprogw", &prog->scale.x, 3, 0.2)->method = EASEINOUT;
    make_tween("barprogh", &prog->scale.y, 36, 0.2)->method = EASEINOUT;
    play_sound("progbar", prog->scale.x * 2, 0.7 + prog->scale.x / 50.0);
}

void update_progbuff(int id)
{
    sprite_t *buff = get_sprite("barbuff");

    make_tween("barbuff", &buff->scale.x, id /
        (float)GAME->nb_moves * 500.0, 1.5)->method = EASEOUT;
}

static void update_compass_arrow(void)
{
    sprite_t *arrow = get_sprite("cmpa");
    sfVector2i center = {(GAME->bounds.left + GAME->bounds.width)
        / 2.0, (GAME->bounds.top + GAME->bounds.height) / 2.0};
    int diffx = center.x - CAM->center.x;
    int diffy = center.y - CAM->center.y;
    int diffd = sqrt(pow(diffx, 2) + pow(diffy, 2)) - 25;
    float traj = atan2f(diffx, -diffy) * 180.0 / M_PI;

    arrow->angle = traj;
    arrow->rect.left = (arrow->rect.left + 45) % 180;
}

void update_compass(void)
{
    sprite_t *arrow = get_sprite("cmpa");
    sprite_t *pivot = get_sprite("cmpp");
    float fact = 0.5 + cos(TIME * 2.0) * 0.2;
    sfIntRect bounds = GAME->bounds;

    arrow->scale = (sfVector2f){CAM->zoom, CAM->zoom};
    pivot->scale = (sfVector2f){fact * CAM->zoom, fact * CAM->zoom};
    if (CAM->center.x > bounds.left - 100 && CAM->center.y > bounds.top - 100
        && CAM->center.x < bounds.left + bounds.width + 100
        && CAM->center.y < bounds.top + bounds.height + 100) {
        arrow->color.a /= 1.2;
        pivot->color.a /= 1.2;
    } else {
        arrow->color.a = 255 + (arrow->color.a - 255) / 1.05;
        pivot->color.a = fact * 255;
    }
    if (get_timer("cmpcooldown") == NULL) {
        update_compass_arrow();
        run_timer("cmpcooldown", 0.1);
    }
}
