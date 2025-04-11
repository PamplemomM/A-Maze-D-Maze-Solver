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

static int add_logs_destroy_tunnel(tunnel_t *tunnel)
{
    char *entry = malloc(sizeof(char)
        * (strlen("tunnel between  and  destroyed\n")
        + strlen(tunnel->r1->name) + strlen(tunnel->r2->name) + 1));

    if (entry == NULL)
        return ERROR;
    sprintf(entry, "tunnel between %s and %s destroyed\n",
        tunnel->r1->name, tunnel->r2->name);
    if (add_to_logs(entry) == ERROR) {
        OMNIFREE(entry, 1);
        return ERROR;
    }
    OMNIFREE(entry, 1);
    return SUCCESS;
}

void destroy_tunnel(tunnel_t *tunnel)
{
    char *name = NULL;

    if (tunnel == NULL)
        return;
    name = make_tunnel_name(tunnel);
    if (name == NULL)
        return;
    add_logs_destroy_tunnel(tunnel);
    DESTROY(get_sprite(name), get_spritelist, free_sprite);
    OMNIFREE(name, 1);
    DESTROY(tunnel, get_tunnels, free_tunnel);
}

static int add_logs_new_tunnel(tunnel_t *tunnel)
{
    char *entry = malloc(sizeof(char) * (strlen("tunnel added between  and \n")
        + strlen(tunnel->r1->name) + strlen(tunnel->r2->name) + 1));

    if (entry == NULL)
        return ERROR;
    sprintf(entry, "tunnel added between %s and %s\n",
        tunnel->r1->name, tunnel->r2->name);
    if (add_to_logs(entry) == ERROR) {
        OMNIFREE(entry, 1);
        return ERROR;
    }
    OMNIFREE(entry, 1);
    return SUCCESS;
}

int place_tunnel(room_t *r1, room_t *r2)
{
    if (get_tunnel(r1, r2, MAZE) != NULL)
        return SUCCESS;
    if (add_tunnel(r1, r2, &MAZE) == ERROR)
        return ERROR;
    add_logs_new_tunnel(get_tunnel(r1, r2, MAZE));
    create_tunnel_sprite(get_tunnel(r1, r2, MAZE));
    play_sound("place", MIN(40.0 * CAM->zoom + 30.0, 90.0),
        diceroll(90, 110) / 100.0); // pick a new one blud
    return SUCCESS;
}
