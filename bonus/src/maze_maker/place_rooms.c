/*
** EPITECH PROJECT, 2025
** place_rooms.c
** File description:
** Functions to place and destroy rooms.
*/

#include "../../include/header_viewer.h"

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

char *make_room_name(sprite_t *room)
{
    char *name = NULL;
    char *tmp[2] = {NULL, NULL};

    tmp[1] = int_to_str((int)(room->pos.x / 50));
    if (tmp[1] == NULL)
        return NULL;
    tmp[0] = merge_str(tmp[1], "_");
    OMNIFREE(tmp[1], 1);
    if (tmp[0] == NULL)
        return NULL;
    tmp[1] = int_to_str((int)(room->pos.y / 50));
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

void destroy_room(room_t *room)
{
    sprite_t *select = get_sprite("room_select");
    char *name = NULL;

    if (room == NULL)
        return;
    name = merge_str("room_", room->name);
    if (name == NULL)
        return;
    if (room == MAZE->end)
        MAZE->end = NULL;
    add_logs_destroy_room(room);
    DESTROY(get_sprite(name), get_spritelist, free_sprite);
    OMNIFREE(name, 1);
    DESTROY(room, get_rooms, free_room);
    select->scale = (sfVector2f){0.95, 0.95};
    update_maker_bounds();
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

int place_room(void)
{
    sprite_t *select = get_sprite("room_select");
    char *name = make_room_name(select);

    if (name == NULL)
        return ERROR;
    if (get_room(name, MAZE) != NULL) {
        if (!(GAME->tool == T_EXIT && get_room(name, MAZE) != MAZE->end
            && get_room(name, MAZE) != MAZE->start)) {
            OMNIFREE(name, 1);
            return SUCCESS;
        }
        destroy_room(get_room(name, MAZE));
    }
    if (add_room(name, select->pos.x, select->pos.y, &MAZE) == ERROR) {
        OMNIFREE(name, 1);
        return ERROR;
    }
    if (GAME->tool == T_EXIT) {
        destroy_room(MAZE->end);
        MAZE->end = get_room(name, MAZE);
    }
    add_logs_new_room(get_room(name, MAZE));
    create_room_sprite(get_room(name, MAZE));
    room_modifs(get_room(name, MAZE));
    OMNIFREE(name, 1);
    update_maker_bounds();
    update_rooms_pos(select);
    play_sound("place", MIN(40.0 * CAM->zoom + 30.0, 90.0),
        diceroll(90, 110) / 100.0);
    return SUCCESS;
}
