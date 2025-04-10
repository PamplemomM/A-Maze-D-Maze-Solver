/*
** EPITECH PROJECT, 2025
** init_tunnels.c
** File description:
** Functions to initialize the program's tunnels.
*/

#include "../include/header_viewer.h"

void setup_tunnel(sprite_t *sprite, room_t *start, room_t *dest)
{
    int diffx = dest->x - start->x;
    int diffy = dest->y - start->y;
    int diffd = MAX(sqrt(pow(diffx, 2) + pow(diffy, 2)) - 40, 15);
    float traj = atan2f(diffx, -diffy) * 180.0 / M_PI;

    if (diffx == 0 && diffy == 0)
        sprite->draw = 0;
    else
        sprite->draw = 1;
    sprite->pos.x = (dest->x + start->x) / 2.0;
    sprite->pos.y = (dest->y + start->y) / 2.0;
    sprite->scale.y = diffd / (float)sprite->rect.height;
    sprite->scale.x = (10.0 + 10.0 / sprite->scale.y)
        / (float)sprite->rect.width;
    sprite->angle = traj;
}

int create_tunnel_sprite(tunnel_t *tunnel)
{
    char *path = merge_str(tunnel->r1->name, tunnel->r2->name);
    char *name = NULL;

    if (path == NULL)
        return ERROR;
    name = merge_str("tunnel_", path);
    OMNIFREE(path, 1);
    if (name == NULL)
        return ERROR;
    if (make_sprite(name, "tunnel", tunnel->r1->x, tunnel->r1->y) == NULL) {
        OMNIFREE(name, 1);
        return ERROR;
    }
    setup_tunnel(get_sprite(name), tunnel->r1, tunnel->r2);
    get_sprite(name)->color = color_from_hue(0, 255, 0, 100);
    get_sprite(name)->type = TUNNEL;
    center_sprite_origin(get_sprite(name), 0.5, 0.5);
    OMNIFREE(name, 1);
    return SUCCESS;
}

int init_tunnels(void)
{
    tunnel_t *tunnel = MAZE->tunnels;

    while (tunnel != NULL) {
        if (create_tunnel_sprite(tunnel) == ERROR)
            return ERROR;
        tunnel = tunnel->next;
    }
    return SUCCESS;
}
