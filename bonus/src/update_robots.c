/*
** EPITECH PROJECT, 2025
** update_robots.c
** File description:
** Functions to update the robots.
*/

#include "../include/header_viewer.h"

void hue_shift(void)
{
    vwr_robot_t *robot = *get_robotlist();

    GAME->hue += HUESHIFT;
    if (GAME->hue >= 360)
        GAME->hue -= 360;
    while (robot != NULL) {
        robot->sprite->color =
            color_from_hue(360 / (float)MAZE->nb_robots
            * robot->id + GAME->hue, 255, 240, 255);
        robot = robot->next;
    }
}

int update_robots(void)
{
    static int prev_id = 0;
    tween_t *tween_id = get_tween("id");
    float length_id = 0.0;
    float speed = 1.0;

    if (tween_id != NULL) {
        length_id = fabs(tween_id->dest - tween_id->start);
        speed = 1 + sin(fabs((*tween_id->value) - tween_id->start)
            / length_id * M_PI) * sqrt(length_id);
    }
    if (GAME->state == REWIND && GAME->move_id <= 0.2)
        DESTROY(tween_id, get_tweenlist, free_tween);
    if (tween_id == NULL && get_timer("moving") == NULL)
        toggle_gamestate(PAUSE);
    if ((int)GAME->move_id != prev_id) {
        prev_id = (int)GAME->move_id;
        update_progbar();
    }
    return move_robots(speed);
}

static void reorder_robots(void)
{
    vwr_robot_t **list = GAME->robots_order;
    vwr_robot_t *tmp = NULL;

    for (int i = 1; list[i] != NULL; i++) {
        if (list[i - 1]->sprite->pos.y > list[i]->sprite->pos.y) {
            tmp = list[i];
            list[i] = list[i - 1];
            list[i - 1] = tmp;
            reorder_robots();
        }
    }
}

void draw_robots(void)
{
    vwr_robot_t **list = GAME->robots_order;

    if (list == NULL)
        return;
    if (get_timer("moving") != NULL)
        reorder_robots();
    for (int i = 0; list[i] != NULL; i++)
        draw_sprite(list[i]->sprite);
}
