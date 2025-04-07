/*
** EPITECH PROJECT, 2025
** init_maze_assets.c
** File description:
** Functions to initialize the program's rooms and tunnels.
*/

#include "../include/header_viewer.h"

int init_robots(void)
{
    vwr_robot_t **list = malloc(sizeof(vwr_robot_t *) * (MAZE->nb_robots + 1));

    if (list == NULL)
        return ERROR;
    for (int i = 1; i <= MAZE->nb_robots; i++) {
        if (make_robot(i) == NULL)
            return ERROR;
        list[MAZE->nb_robots - i] = get_robot(i);
    }
    list[MAZE->nb_robots] = NULL;
    GAME->robots_order = list;
    return SUCCESS;
}

static void setup_camera(void)
{
    sfIntRect bounds = GAME->bounds;
    float cam_zoom;

    bounds.width -= bounds.left;
    bounds.height -= bounds.top;
    cam_zoom = 2.0 / ((float)MAX(bounds.width, bounds.height) / 200.0);
    CAM->center.x = bounds.left + bounds.width / 2.0;
    CAM->center.y = bounds.top + bounds.height / 2.0;
    CAM->zoom = cam_zoom * 1.2;
    make_tween("camzoom", &CAM->zoom, cam_zoom, 1.7)->method = EASEOUT;
    GAME->bounds = (sfIntRect){bounds.left - 200, bounds.top - 200,
        bounds.width + 400, bounds.height + 400};
}

static void update_bounds(room_t *room)
{
    if (GAME->bounds.left == -1 || room->x < GAME->bounds.left)
        GAME->bounds.left = room->x;
    if (GAME->bounds.top == -1 || room->y < GAME->bounds.top)
        GAME->bounds.top = room->y;
    if (GAME->bounds.width == -1 || room->x > GAME->bounds.width)
        GAME->bounds.width = room->x;
    if (GAME->bounds.height == -1 || room->y > GAME->bounds.height)
        GAME->bounds.height = room->y;
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

static int create_room_sprite(room_t *room)
{
    char *name = merge_str("room_", room->name);

    if (name == NULL)
        return ERROR;
    room->x *= 50;
    room->y *= 50;
    update_bounds(room);
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
        if (create_room_sprite(room) == ERROR)
            return ERROR;
        room = room->next;
    }
    setup_camera();
    return SUCCESS;
}

static void setup_tunnel(sprite_t *sprite, room_t *start, room_t *dest)
{
    int diffx = dest->x - start->x;
    int diffy = dest->y - start->y;
    int diffd = sqrt(pow(diffx, 2) + pow(diffy, 2)) - 25;
    float traj = atan2f(diffx, -diffy) * 180.0 / M_PI;

    sprite->scale.y = diffd / (float)sprite->rect.height;
    sprite->scale.x = (10.0 + 5.0 / sprite->scale.y)
        / (float)sprite->rect.width;
    sprite->angle = traj;
    sprite->color = color_from_hue(0, 255, 0, 100);
    sprite->type = TUNNEL;
    center_sprite_origin(sprite, 0.5, 1.0);
}

static int create_tunnel_sprite(tunnel_t *tunnel)
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
