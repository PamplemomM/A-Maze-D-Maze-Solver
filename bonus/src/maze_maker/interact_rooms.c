/*
** EPITECH PROJECT, 2025
** interact_rooms.c
** File description:
** Functions to interact with the rooms.
*/

#include "../../include/header_viewer.h"

int interact_room(void)
{
    sprite_t *select = get_sprite("room_select");
    char *name = make_room_name(select->pos);

    if (GAME->state == MKR_ROOM && get_room(name, MAZE) == NULL) {
        if (place_room(select->pos) == ERROR) {
            OMNIFREE(name, 1);
            return ERROR;
        }
    } else if (GAME->state == MKR_DESTROY && get_room(name, MAZE) != NULL) {
        destroy_room(get_room(name, MAZE));
        update_rooms_pos(1);
    }
    OMNIFREE(name, 1);
    return SUCCESS;
}
