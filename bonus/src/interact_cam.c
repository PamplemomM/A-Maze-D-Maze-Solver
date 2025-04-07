/*
** EPITECH PROJECT, 2025
** interact_cam.c
** File description:
** Functions to interact with the game camera.
*/

#include "../include/header_viewer.h"

void cam_move_mouse(sfMouseMoveEvent mouse)
{
    static sfMouseMoveEvent mouseold = {sfEvtMouseMoved, 0, 0};

    if (MOUSEPRESS(sfMouseLeft) && (mouseold.x != 0 && mouseold.y != 0)) {
        DESTROY(get_tween("camvert"), get_tweenlist, free_tween);
        DESTROY(get_tween("camlat"), get_tweenlist, free_tween);
        CAM->center.x += (mouseold.x - mouse.x) / CAM->zoom;
        CAM->center.y += (mouseold.y - mouse.y) / CAM->zoom;
    }
    mouseold = mouse;
}

void cam_zoom_mouse(sfMouseWheelScrollEvent mouse)
{
    tween_t *tween = get_tween("camzoom");
    float tmp = CAM->zoom;

    if (tween != NULL)
        tmp = tween->dest;
    tween = make_tween("camzoom", &CAM->zoom, tmp, 0.5);
    tween->method = EASEOUT;
    tmp += mouse.delta * tmp / 10;
    if (tmp > 100)
        tmp = 100;
    else if (tmp < 0.1)
        tmp = 0.1;
    tween->dest = tmp;
}

static void cam_zoom_keys(float fact)
{
    if (KEYPRESS(sfKeyC))
        make_tween("camzoom", &CAM->zoom, MIN(CAM->zoom
            * (1.1 + (fact - 1) / 2.0), 100), 0.8)->method = EASEOUT;
    else if (KEYPRESS(sfKeyX))
        make_tween("camzoom", &CAM->zoom, MAX(CAM->zoom
            / (1.1 + (fact - 1) / 2.0), 0.1), 0.8)->method = EASEOUT;
}

void cam_move_keys(void)
{
    float fact = 1.0;

    if (KEYPRESS(sfKeyLShift))
        fact = 1.5;
    if (KEYPRESS(sfKeyUp))
        make_tween("camvert", &CAM->center.y, CAM->center.y - 25
            / CAM->zoom * pow(fact, 2), 0.4)->method = EASEOUT;
    else if (KEYPRESS(sfKeyDown))
        make_tween("camvert", &CAM->center.y, CAM->center.y + 25
            / CAM->zoom * pow(fact, 2), 0.4)->method = EASEOUT;
    if (KEYPRESS(sfKeyLeft))
        make_tween("camlat", &CAM->center.x, CAM->center.x - 25
            / CAM->zoom * pow(fact, 2), 0.4)->method = EASEOUT;
    else if (KEYPRESS(sfKeyRight))
        make_tween("camlat", &CAM->center.x, CAM->center.x + 25
            / CAM->zoom * pow(fact, 2), 0.4)->method = EASEOUT;
    cam_zoom_keys(fact);
}
