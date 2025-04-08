/*
** EPITECH PROJECT, 2025
** parse_tunnel.c
** File description:
** Parsing of Tunnels.
*/

#include "../../include/header_amazed.h"

int add_tunnel(room_t *r1, room_t *r2, maze_t **maze)
{
    tunnel_t *headcpy = (*maze)->tunnels;
    tunnel_t *tunnel = malloc(sizeof(tunnel_t));

    if (tunnel == NULL)
        return ERROR;
    tunnel->r1 = r1;
    tunnel->r2 = r2;
    tunnel->val = -1;
    tunnel->next = NULL;
    if (headcpy == NULL) {
        (*maze)->tunnels = tunnel;
        return SUCCESS;
    }
    while (headcpy->next != NULL)
        headcpy = headcpy->next;
    headcpy->next = tunnel;
    return SUCCESS;
}

int connect_rooms(room_t *r1, room_t *r2)
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

int parse_tunnel(maze_t **maze, char *line)
{
    int i = 0;
    char *name1 = get_name(line, &i, " -\n");
    char *name2 = get_name(line, &i, " -\n");
    room_t *r1 = get_room(name1, *maze);
    room_t *r2 = get_room(name2, *maze);

    if (name1 == NULL || name2 == NULL) {
        OMNIFREE(name1, 1);
        OMNIFREE(name1, 1);
        return ERROR;
    }
    OMNIFREE(name1, 1);
    OMNIFREE(name2, 1);
    if (r1 == NULL || r2 == NULL)
        return give_up("Tunnel between non-existent rooms.", maze);
    if (connect_rooms(r1, r2) == ERROR
        || add_tunnel(r1, r2, maze) == ERROR)
        return ERROR;
    return SUCCESS;
}
