/*
** EPITECH PROJECT, 2025
** cam_csfml
** File description:
** Camera related functions.
*/

#include "../../include/header_csfml.h"

cam_t **get_cam(void)
{
    static cam_t *cam = NULL;

    return &cam;
}

cam_t *init_cam(void)
{
    sfVector2u windowsize = sfRenderWindow_getSize(WINDOW);

    CAM = malloc(sizeof(cam_t));
    if (CAM == NULL)
        return NULL;
    CAM->view = sfView_createFromRect((sfFloatRect){0, 0,
        windowsize.x, windowsize.y});
    CAM->center = (sfVector2f){windowsize.x / 2.0, windowsize.y / 2.0};
    CAM->size = (sfVector2f){windowsize.x, windowsize.y};
    CAM->zoom = 1.0;
    CAM->angle = 0;
    return CAM;
}

void update_cam(void)
{
    if (CAM == NULL)
        return;
    sfView_setCenter(CAM->view, CAM->center);
    sfView_setSize(CAM->view, (sfVector2f){CAM->size.x / CAM->zoom,
        CAM->size.y / CAM->zoom});
    sfView_setRotation(CAM->view, CAM->angle);
    sfRenderWindow_setView(WINDOW, CAM->view);
}

void destroy_cam(void)
{
    if (CAM == NULL)
        return;
    sfView_destroy(CAM->view);
    OMNIFREE(CAM, 1);
}
