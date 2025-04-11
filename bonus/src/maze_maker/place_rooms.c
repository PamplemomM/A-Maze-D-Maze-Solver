/*
** EPITECH PROJECT, 2025
** place_rooms.c
** File description:
** Functions to place and destroy rooms.
*/

#include "../../include/header_viewer.h"

void update_rooms(void)
{
    sprite_t *room = NULL;
    timers_t *timer = *get_timerlist();
    float time_left = 0;
    float wobble_fact = 0;

    while (timer != NULL) {
        room = get_sprite(timer->name);
        if (room != NULL) {
            time_left = timer->tend - TIME;
            wobble_fact = cos(TIME * 28) * time_left / 6.0;
            room->scale.x = 1 + wobble_fact + time_left / 3.0;
            room->scale.y = 1 - wobble_fact + time_left / 3.0;
        }
        timer = timer->next;
    }
}

sprite_t *get_room_sprite(room_t *room)
{
    sprite_t *sprite = NULL;
    char *name = merge_str("room_", room->name);

    if (name == NULL)
        return OMNIFREE(name, 1);
    sprite = get_sprite(name);
    OMNIFREE(name, 1);
    return sprite;
}

char *make_room_name(sfVector2f pos)
{
    char *name = NULL;
    char *tmp[2] = {NULL, NULL};

    tmp[1] = int_to_str((int)(pos.x / 50));
    if (tmp[1] == NULL)
        return NULL;
    tmp[0] = merge_str(tmp[1], "_");
    OMNIFREE(tmp[1], 1);
    if (tmp[0] == NULL)
        return NULL;
    tmp[1] = int_to_str((int)(pos.y / 50));
    if (tmp[1] == NULL)
        return OMNIFREE(tmp[0], 1);
    name = merge_str(tmp[0], tmp[1]);
    SDFREE("%1 %1", &tmp[0], &tmp[1]);
    return name;
}

static int add_logs_destroy_room(room_t *room)
{
    char *entry = malloc(sizeof(char) * (strlen("room  destroyed\n")
        + strlen(room->name) + 1));

    if (entry == NULL)
        return ERROR;
    sprintf(entry, "room %s destroyed\n", room->name);
    if (add_to_logs(entry) == ERROR) {
        OMNIFREE(entry, 1);
        return ERROR;
    }
    OMNIFREE(entry, 1);
    return SUCCESS;
}

static void destroy_room_tunnels(room_t *room)
{
    tunnel_t *tunnel = MAZE->tunnels;
    tunnel_t *tmp = NULL;

    while (tunnel != NULL) {
        tmp = tunnel->next;
        if (tunnel->r1 == room || tunnel->r2 == room)
            destroy_tunnel(tunnel);
        tunnel = tmp;
    }
}

void destroy_room(room_t *room)
{
    sprite_t *select = get_sprite("room_select");
    char *name = NULL;

    if (room == NULL || room == MAZE->start)
        return;
    name = merge_str("room_", room->name);
    if (name == NULL)
        return;
    if (room == MAZE->end)
        MAZE->end = NULL;
    add_logs_destroy_room(room);
    destroy_room_tunnels(room);
    DESTROY(get_sprite(name), get_spritelist, free_sprite);
    OMNIFREE(name, 1);
    DESTROY(room, get_rooms, free_room);
    select->scale = (sfVector2f){0.95, 0.95};
    update_maker_bounds();
    play_sound("destroy", MIN(60.0 * CAM->zoom + 20.0, 100.0),
        diceroll(90, 110) / 100.0);
}

static int add_logs_new_room(room_t *room)
{
    char *entry = malloc(sizeof(char) * (strlen("room  added at , \n")
        + strlen(room->name) + digitcount(room->x) + digitcount(room->y) + 1));

    if (entry == NULL)
        return ERROR;
    sprintf(entry, "room %s added at %d, %d\n", room->name, room->x, room->y);
    if (add_to_logs(entry) == ERROR) {
        OMNIFREE(entry, 1);
        return ERROR;
    }
    OMNIFREE(entry, 1);
    return SUCCESS;
}

static void room_modifs(room_t *room)
{
    sprite_t *sprite = NULL;
    char *name = merge_str("room_", room->name);

    if (name == NULL)
        return;
    sprite = get_sprite(name);
    sprite->color = color_from_hue(0, 240, 0, 255);
    run_timer(name, 0.5);
    OMNIFREE(name, 1);
}

static void place_room_effects(room_t *room)
{
    if (GAME->state == MKR_EXIT) {
        destroy_room(MAZE->end);
        MAZE->end = room;
    }
    add_logs_new_room(room);
    create_room_sprite(room);
    room_modifs(room);
    update_maker_bounds();
    update_rooms_pos(0);
    play_sound("place", MIN(60.0 * CAM->zoom + 30.0, 100.0),
        diceroll(90, 110) / 100.0);
    if (GAME->state == MKR_EXIT)
        update_rooms_pos(1);
}

int place_room(sfVector2f pos)
{
    char *name = make_room_name(pos);

    if (name == NULL)
        return ERROR;
    if (get_room(name, MAZE) != NULL) {
        if (get_room(name, MAZE) == MAZE->end
            || get_room(name, MAZE) == MAZE->start) {
            OMNIFREE(name, 1);
            return SUCCESS;
        }
        if (GAME->state == MKR_EXIT)
            destroy_room(get_room(name, MAZE));
    }
    if (add_room(name, pos.x, pos.y, &MAZE) == ERROR) {
        OMNIFREE(name, 1);
        return ERROR;
    }
    place_room_effects(get_room(name, MAZE));
    OMNIFREE(name, 1);
    return SUCCESS;
}
