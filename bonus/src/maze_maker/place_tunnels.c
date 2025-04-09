/*
** EPITECH PROJECT, 2025
** place_tunnels.c
** File description:
** Functions to place and destroy tunnels.
*/

#include "../../include/header_viewer.h"

sprite_t *get_tunnel_sprite(tunnel_t *tunnel)
{
    sprite_t *sprite = NULL;
    char *path = merge_str(tunnel->r1->name, tunnel->r2->name);
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

char *make_tunnel_name(tunnel_t *tunnel)
{
    char *path = merge_str(tunnel->r1->name, tunnel->r2->name);
    char *name = NULL;

    if (path == NULL)
        return NULL;
    name = merge_str("tunnel_", path);
    OMNIFREE(path, 1);
    return name;
}

void destroy_tunnel(tunnel_t *tunnel)
{
    char *name = NULL;

    if (tunnel == NULL)
        return;
    name = make_tunnel_name(tunnel);
    if (name == NULL)
        return;
    //add_logs_destroy_tunnel(tunnel);
    DESTROY(get_sprite(name), get_spritelist, free_sprite);
    OMNIFREE(name, 1);
    DESTROY(tunnel, get_tunnels, free_tunnel);
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

int place_tunnel(room_t *r1, room_t *r2)
{
    if (get_tunnel(r1, r2, MAZE) != NULL)
        return SUCCESS;
    if (add_tunnel(r1, r2, &MAZE) == ERROR)
        return ERROR;
    create_tunnel_sprite(get_tunnel(r1, r2, MAZE));
    play_sound("place", MIN(40.0 * CAM->zoom + 30.0, 90.0),
        diceroll(90, 110) / 100.0); // pick a new one blud
    return SUCCESS;
}

static int try_place_tunnel(tunnel_t *tunnel)
{
    char *name = make_room_name(get_sprite("room_select")->pos);

    if (get_room(name, MAZE) != NULL && get_room(name, MAZE) != tunnel->r1) {
        DESTROY(tunnel->r2, get_rooms, free_room);
        tunnel->r2 = get_room(name, MAZE);
        OMNIFREE(name, 1);
        return place_tunnel(tunnel->r1, tunnel->r2);
    }
    OMNIFREE(name, 1);
    return ERROR;
}

int interact_tunnel(void)
{
    sprite_t *select = get_sprite("room_select");
    static tunnel_t *tunnel = NULL;
    static sprite_t *sprite = NULL;
    char *name = NULL;

    if (tunnel != NULL) {
        if (GAME->tool == T_TUNNEL) {
            get_room("room_tmp", MAZE)->x = select->pos.x;
            get_room("room_tmp", MAZE)->y = select->pos.y;
            setup_tunnel(sprite, tunnel->r1, tunnel->r2);
        } else {
            DESTROY(sprite, get_spritelist, free_sprite);
            if (try_place_tunnel(tunnel) == ERROR) {
                DESTROY(tunnel->r2, get_rooms, free_room);
                OMNIFREE(tunnel, 1);
                return ERROR;
            }
            OMNIFREE(tunnel, 1);
        }
    }
    if (GAME->tool != T_TUNNEL)
        return ERROR;
    if (MOUSEPRESS(sfMouseLeft) && tunnel == NULL) {
        tunnel = malloc(sizeof(tunnel_t));
        if (tunnel == NULL)
            return ERROR;
        sprite = make_tmp_tunnel();
        name = make_room_name(select->pos);
        if (get_room(name, MAZE) == NULL) {
            DESTROY(sprite, get_spritelist, free_sprite);
            OMNIFREE(tunnel, 1);
            OMNIFREE(name, 1);
            return SUCCESS;
        }
        if (add_room("room_tmp", -1, -1, &MAZE) == ERROR) {
            DESTROY(sprite, get_spritelist, free_sprite);
            OMNIFREE(tunnel, 1);
            OMNIFREE(name, 1);
            return ERROR;
        }
        tunnel->r1 = get_room(name, MAZE);
        tunnel->r2 = get_room("room_tmp", MAZE);
        tunnel->next = NULL;
    }
    if (MOUSEPRESS(sfMouseLeft) && tunnel != NULL && tunnel->r1 != NULL) {
        if (try_place_tunnel(tunnel) == SUCCESS) {
            DESTROY(sprite, get_spritelist, free_sprite);
        }
    }
    OMNIFREE(name, 1);
    return SUCCESS;
}
