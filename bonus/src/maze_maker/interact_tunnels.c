/*
** EPITECH PROJECT, 2025
** interact_tunnels.c
** File description:
** Functions to interact with the tunnels.
*/

#include "../../include/header_viewer.h"

static int try_place_tunnel(tunnel_t **tunnel, room_t **room_tmp)
{
    char *name = make_room_name(get_sprite("room_select")->pos);
    room_t *r2 = get_room(name, MAZE);

    free_room((*tunnel)->r2);
    *room_tmp = NULL;
    OMNIFREE(name, 1);
    if (r2 != NULL && r2 != (*tunnel)->r1) {
        (*tunnel)->r2 = r2;
        return place_tunnel((*tunnel)->r1, (*tunnel)->r2);
    }
    return ERROR;
}

static int interact_tunnel_update(tunnel_t **tunnel, room_t **room_tmp)
{
    sprite_t *select = get_sprite("room_select");
    sprite_t *sprite = get_sprite("tunnel_tmp");

    if (GAME->state == MKR_TUNNEL) {
        (*room_tmp)->x = select->pos.x;
        (*room_tmp)->y = select->pos.y;
        sprite->color.a = (cos(TIME * 2.0) + 1) * 25 + 175;
        setup_tunnel(sprite, (*tunnel)->r1, (*tunnel)->r2);
    } else {
        DESTROY(sprite, get_spritelist, free_sprite);
        if (try_place_tunnel(tunnel, room_tmp) == ERROR) {
            OMNIFREE(*tunnel, 1);
            return ERROR;
        }
        OMNIFREE(*tunnel, 1);
    }
    return SUCCESS;
}

static sprite_t *make_tmp_tunnel(void)
{
    sprite_t *sprite = make_sprite("tunnel_tmp", "tunnel", 0, 0);

    if (sprite == NULL)
        return NULL;
    sprite->color = color_from_hue(0, 255, 0, 200);
    sprite->type = TUNNEL;
    center_sprite_origin(sprite, 0.5, 0.5);
    return sprite;
}

static room_t *make_tunnel_tmp_room(void)
{
    sprite_t *select = get_sprite("room_select");
    room_t *room_tmp = malloc(sizeof(room_t));

    if (room_tmp == NULL)
        return NULL;
    room_tmp->name = strdup("room_tmp");
    if (room_tmp->name == NULL)
        return OMNIFREE(room_tmp, 1);
    room_tmp->x = select->pos.x;
    room_tmp->y = select->pos.y;
    room_tmp->links = NULL;
    room_tmp->next = NULL;
    return room_tmp;
}

static int interact_tunnel_initiate(tunnel_t **tunnel,
    room_t **room_tmp, room_t *r1)
{
    *tunnel = malloc(sizeof(tunnel_t));
    if (*tunnel == NULL)
        return ERROR;
    *room_tmp = make_tunnel_tmp_room();
    if (*room_tmp == NULL) {
        OMNIFREE(*tunnel, 1);
        return ERROR;
    }
    (*tunnel)->r1 = r1;
    (*tunnel)->r2 = *room_tmp;
    (*tunnel)->next = NULL;
    return SUCCESS;
}

static int interact_tunnel_first_room(tunnel_t **tunnel, room_t **room_tmp)
{
    sprite_t *select = get_sprite("room_select");
    sprite_t *sprite = NULL;
    room_t *r1 = NULL;
    char *name = make_room_name(select->pos);

    r1 = get_room(name, MAZE);
    OMNIFREE(name, 1);
    if (r1 == NULL)
        return SUCCESS;
    sprite = make_tmp_tunnel();
    if (sprite == NULL) {
        OMNIFREE(*tunnel, 1);
        return ERROR;
    }
    if (interact_tunnel_initiate(tunnel, room_tmp, r1) == ERROR) {
        DESTROY(sprite, get_spritelist, free_sprite);
        return ERROR;
    }
    setup_tunnel(sprite, (*tunnel)->r1, (*tunnel)->r2);
    return SUCCESS;
}

int interact_tunnel(void)
{
    static tunnel_t *tunnel = NULL;
    static room_t *room_tmp = NULL;

    if (tunnel != NULL) {
        if (interact_tunnel_update(&tunnel, &room_tmp) == ERROR)
            return ERROR;
        return SUCCESS;
    }
    if (GAME->state == MKR_TUNNEL && tunnel == NULL) {
        if (interact_tunnel_first_room(&tunnel, &room_tmp) == ERROR)
            return ERROR;
    }
    return SUCCESS;
}
