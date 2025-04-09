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

static int offset_room(room_t *room, sfVector2i offset)
{
    sprite_t *sprite = get_room_sprite(room);
    timers_t *timer = get_timer(sprite->name);
    char *name = NULL;

    sprite->pos.x += offset.x;
    sprite->pos.y += offset.y;
    room->x += offset.x;
    room->y += offset.y;
    OMNIFREE(room->name, 1);
    room->name = make_room_name(sprite);
    if (room->name == NULL)
        return ERROR;
    name = merge_str("room_", room->name);
    if (name == NULL)
        return ERROR;
    if (timer != NULL) {
        OMNIFREE(timer->name, 1);
        timer->name = strdup(name);
        if (timer->name == NULL) {
            OMNIFREE(sprite->name, 1);
            return ERROR;
        }
    }
    OMNIFREE(sprite->name, 1);
    sprite->name = name;
    return SUCCESS;
}

int update_rooms_pos(sprite_t *select)
{
    room_t *room = MAZE->rooms;
    sfVector2i offset;

    if (GAME->state == BUILD) {
        offset = (sfVector2i){abs(MIN(select->pos.x, 0)),
            abs(MIN(select->pos.y, 0))};
    } else if (GAME->state == BREAK) {
        update_maker_bounds();
        offset = (sfVector2i)
            {-200 - GAME->bounds.left, -200 - GAME->bounds.top};
    }
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
    add_logs_offset(offset);
    update_maker_bounds();
    return SUCCESS;
}
