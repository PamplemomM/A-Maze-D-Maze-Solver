/*
** EPITECH PROJECT, 2025
** update_bounds.c
** File description:
** Functions to update the maze boundaries.
*/

#include "../../include/header_viewer.h"

void update_maker_bounds(void)
{
    room_t *room = MAZE->rooms;
    sfIntRect bounds;

    if (room == NULL)
        return;
    bounds = (sfIntRect){room->x - 200, room->y - 200,
        room->x + 400, room->y + 400};
    while (room != NULL) {
        if (room->x < bounds.left + 200)
            bounds.left = room->x - 200;
        if (room->y < bounds.top + 200)
            bounds.top = room->y - 200;
        if (room->x > bounds.width - 400)
            bounds.width = room->x + 400;
        if (room->y > bounds.height - 400)
            bounds.height = room->y + 400;
        room = room->next;
    }
    GAME->bounds = bounds;
    setup_bg(0);
}

static int add_logs_offset(sfVector2i offset)
{
    char *entry = malloc(sizeof(char) * (strlen("map boundaries modified\n")
        + strlen("all rooms were offset by , \n")
        + digitcount(offset.x) + digitcount(offset.y) + 1));

    if (entry == NULL)
        return ERROR;
    sprintf(entry,
        "map boundaries modified\nall rooms were offset by %d, %d\n",
        offset.x, offset.y);
    if (add_to_logs(entry) == ERROR) {
        OMNIFREE(entry, 1);
        return ERROR;
    }
    OMNIFREE(entry, 1);
    return SUCCESS;
}

static void offset_cam(sfVector2i offset)
{
    tween_t *camx = get_tween("camlat");
    tween_t *camy = get_tween("camvert");

    if (camx != NULL) {
        camx->start += offset.x;
        camx->dest += offset.x;
    }
    if (camy != NULL) {
        camy->start += offset.y;
        camy->dest += offset.y;
    }
    CAM->center.x += offset.x;
    CAM->center.y += offset.y;
}

static int offset_room_name(room_t *room, sfVector2i offset)
{
    sprite_t *sprite = get_room_sprite(room);
    timers_t *timer = get_timer(sprite->name);

    OMNIFREE(room->name, 1);
    room->name = make_room_name(sprite->pos);
    if (room->name == NULL)
        return ERROR;
    OMNIFREE(sprite->name, 1);
    sprite->name = merge_str("room_", room->name);
    if (sprite->name == NULL)
        return ERROR;
    if (timer != NULL) {
        OMNIFREE(timer->name, 1);
        timer->name = strdup(sprite->name);
        if (timer->name == NULL) {
            OMNIFREE(sprite->name, 1);
            return ERROR;
        }
    }
    return SUCCESS;
}

static int offset_room(room_t *room, sfVector2i offset)
{
    sprite_t *sprite = get_room_sprite(room);

    sprite->pos.x += offset.x;
    sprite->pos.y += offset.y;
    room->x += offset.x;
    room->y += offset.y;
    if (offset_room_name(room, offset) == ERROR)
        return ERROR;
    return SUCCESS;
}

static char *get_tunnel_path_preoffset(tunnel_t *tunnel, sfVector2i offset)
{
    char *path = NULL;
    char *nr1 = NULL;
    char *nr2 = NULL;
    sfVector2f pos;

    pos = (sfVector2f){tunnel->r1->x - offset.x, tunnel->r1->y - offset.y};
    nr1 = make_room_name(pos);
    pos = (sfVector2f){tunnel->r2->x - offset.x, tunnel->r2->y - offset.y};
    nr2 = make_room_name(pos);
    path = merge_str(nr1, nr2);
    OMNIFREE(nr1, 1);
    OMNIFREE(nr2, 1);
    return path;
}

static sprite_t *get_tunnel_sprite_preoffset(tunnel_t *tunnel,
    sfVector2i offset)
{
    sprite_t *sprite = NULL;
    char *path = get_tunnel_path_preoffset(tunnel, offset);
    char *name = NULL;

    if (path == NULL)
        return NULL;
    name = merge_str("tunnel_", path);
    OMNIFREE(path, 1);
    if (name == NULL)
        return NULL;
    sprite = get_sprite(name);
    OMNIFREE(name, 1);
    return sprite;
}

static void update_tunnels_pos(sfVector2i offset)
{
    sprite_t *sprite = NULL;
    tunnel_t *tunnel = MAZE->tunnels;

    while (tunnel != NULL) {
        sprite = get_tunnel_sprite_preoffset(tunnel, offset);
        sprite->pos.x = (tunnel->r1->x + tunnel->r2->x) / 2.0;
        sprite->pos.y = (tunnel->r1->y + tunnel->r2->y) / 2.0;
        OMNIFREE(sprite->name, 1);
        sprite->name = make_tunnel_name(tunnel);
        tunnel = tunnel->next;
    }
}

static int apply_offset(sfVector2i offset)
{
    sprite_t *select = get_sprite("room_select");
    room_t *room = MAZE->rooms;

    if (offset.x == 0 && offset.y == 0)
        return SUCCESS;
    select->pos.x += offset.x;
    select->pos.y += offset.y;
    offset_cam(offset);
    while (room != NULL) {
        if (offset_room(room, offset) == ERROR)
            return ERROR;
        room = room->next;
    }
    update_tunnels_pos(offset);
    add_logs_offset(offset);
    update_maker_bounds();
    return SUCCESS;
}

int update_rooms_pos(int add_or_del)
{
    sprite_t *select = get_sprite("room_select");
    sfVector2i offset;

    if (add_or_del == 0) {
        offset = (sfVector2i){abs(MIN(select->pos.x, 0)),
            abs(MIN(select->pos.y, 0))};
    } else if (add_or_del == 1) {
        update_maker_bounds();
        offset = (sfVector2i)
            {-200 - GAME->bounds.left, -200 - GAME->bounds.top};
    }
    return apply_offset(offset);
}
