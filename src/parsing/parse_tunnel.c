/*
** EPITECH PROJECT, 2025
** parse_tunnel.c
** File description:
** Parsing of Tunnels.
*/

#include "../../include/header_amazed.h"

static int add_tunnel(room_t *r1, room_t *r2, tunnel_t **tunnels)
{
    tunnel_t *newtunnel = malloc(sizeof(tunnel_t));

    if (newtunnel == NULL)
        return ERROR;
    newtunnel->r1 = r1;
    newtunnel->r2 = r2;
    newtunnel->val = -1;
    newtunnel->next = *tunnels;
    *tunnels = newtunnel;
    return SUCCESS;
}

static int connect_rooms(room_t *r1, room_t *r2)
{
    room_t **newlist = NULL;
    int len = 0;

    if (r1 == NULL || r2 == NULL)
        return ERROR;
    if (r1->links != NULL) {
        while (r1->links[len] != NULL)
            len++;
    }
    newlist = malloc(sizeof(room_t *) * (len + 2));
    if (newlist == NULL)
        return ERROR;
    for (int i = 0; i < len; i++)
        newlist[i] = r1->links[i];
    newlist[len] = r2;
    newlist[len + 1] = NULL;
    if (r1->links != NULL)
        OMNIFREE(r1->links, 1);
    r1->links = newlist;
    return SUCCESS;
}

int parse_tunnel(maze_t *maze, char *line)
{
    int i = 0;
    int j = 0;
    char *name1 = get_name(line, &i, " -\n");
    char *name2 = get_name(&line[i], &j, " -\n");
    room_t *r1 = get_room(name1, maze);
    room_t *r2 = get_room(name2, maze);

    OMNIFREE(name1, 1);
    OMNIFREE(name2, 1);
    if (connect_rooms(r1, r2) == ERROR
        || add_tunnel(r1, r2, &maze->tunnels) == ERROR)
        return ERROR;
    return SUCCESS;
}
