/*
** EPITECH PROJECT, 2025
** init_rooms.c
** File description:
** Functions to initialize the program's rooms.
*/

#include "../include/header_viewer.h"

void setup_camera(void)
{
    sfIntRect bounds = GAME->bounds;
    float cam_zoom;
    float cam_y;

    bounds.width -= bounds.left;
    bounds.height -= bounds.top;
    cam_zoom = 2.0 / ((float)MAX(bounds.width, bounds.height) / 200.0);
    cam_y = bounds.top + bounds.height / 2.0;
    CAM->center.x = bounds.left + bounds.width / 2.0;
    CAM->center.y = cam_y + 800;
    CAM->zoom = cam_zoom * 1.3;
    make_tween("camzoom", &CAM->zoom, cam_zoom, 5.0)->method = EASEINOUT;
    make_tween("camvert", &CAM->center.y, cam_y, 7.0)->method = EASEOUT;
    GAME->bounds = (sfIntRect){bounds.left - 200, bounds.top - 200,
        bounds.width + 400, bounds.height + 400};
}

sfIntRect update_bounds(room_t *room)
{
    sfIntRect bounds = GAME->bounds;

    if (bounds.left == -1 || room->x < bounds.left)
        bounds.left = room->x;
    if (bounds.top == -1 || room->y < bounds.top)
        bounds.top = room->y;
    if (bounds.width == -1 || room->x > bounds.width)
        bounds.width = room->x;
    if (bounds.height == -1 || room->y > bounds.height)
        bounds.height = room->y;
    return bounds;
}

static char *get_room_texture(room_t *room)
{
    if (room == MAZE->start)
        return "room_start";
    if (room == MAZE->end)
        return "room_end";
    return "room_default";
}

static void setup_room(sprite_t *sprite)
{
    sprite->color = color_from_hue(0, 150, 0, 255);
    sprite->type = ROOM;
    center_sprite_origin(sprite, 0.5, 0.5);
}

int create_room_sprite(room_t *room)
{
    char *name = merge_str("room_", room->name);

    if (name == NULL)
        return ERROR;
    if (make_sprite(name, get_room_texture(room),
        room->x, room->y) == NULL) {
        OMNIFREE(name, 1);
        return ERROR;
    }
    setup_room(get_sprite(name));
    OMNIFREE(name, 1);
    return SUCCESS;
}

int init_rooms(void)
{
    room_t *room = MAZE->rooms;

    while (room != NULL) {
        room->x *= 50;
        room->y *= 50;
        GAME->bounds = update_bounds(room);
        if (create_room_sprite(room) == ERROR)
            return ERROR;
        room = room->next;
    }
    setup_camera();
    return SUCCESS;
}
