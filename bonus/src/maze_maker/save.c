/*
** EPITECH PROJECT, 2025
** save.c
** File description:
** Functions to save your maze.
*/

#include "../../include/header_viewer.h"

static int save_nb_robots(int fd)
{
    char *nb_robots = int_to_str(MAZE->nb_robots);

    if (nb_robots == NULL)
        return ERROR;
    write(fd, "#number_of_robots\n", strlen("#number_of_robots\n"));
    write(fd, nb_robots, strlen(nb_robots));
    write(fd, "\n", 1);
    OMNIFREE(nb_robots, 1);
    return SUCCESS;
}

static int save_rooms(int fd)
{
    room_t *room = MAZE->rooms;
    char *tmp = NULL;

    if (room == NULL)
        return SUCCESS;
    write(fd, "#rooms\n", strlen("#rooms\n"));
    while (room != NULL) {
        if (room == MAZE->start)
            write(fd, "##start\n", strlen("##start\n"));
        if (room == MAZE->end)
            write(fd, "##end\n", strlen("##end\n"));
        write(fd, room->name, strlen(room->name));
        write(fd, " ", 1);
        tmp = int_to_str(room->x / 50);
        if (tmp == NULL)
            return ERROR;
        write(fd, tmp, strlen(tmp));
        OMNIFREE(tmp, 1);
        write(fd, " ", 1);
        tmp = int_to_str(room->y / 50);
        if (tmp == NULL)
            return ERROR;
        write(fd, tmp, strlen(tmp));
        OMNIFREE(tmp, 1);
        write(fd, "\n", 1);
        room = room->next;
    }
    return SUCCESS;
}

static int save_tunnels(int fd)
{
    tunnel_t *tunnel = MAZE->tunnels;

    if (tunnel == NULL)
        return SUCCESS;
    write(fd, "#tunnels\n", strlen("#tunnels\n"));
    while (tunnel != NULL) {
        write(fd, tunnel->r1->name, strlen(tunnel->r1->name));
        write(fd, "-", 1);
        write(fd, tunnel->r2->name, strlen(tunnel->r2->name));
        write(fd, "\n", 1);
        tunnel = tunnel->next;
    }
    return SUCCESS;
}

void save_maze(void)
{
    int fd = open("new_custom_maze.txt", O_WRONLY | O_TRUNC | O_CREAT,
        S_IRUSR | S_IWUSR);

    if (fd == -1) {
        text_jumpscare("File couldn't open!!! :'(", 2);
        return;
    }
    if (save_nb_robots(fd) == ERROR || save_rooms(fd) == ERROR
        || save_tunnels(fd) == ERROR) {
        text_jumpscare("Error while saving :(", 2);
        close(fd);
        return;
    }
    text_jumpscare("Saved! :DDD", 2);
    play_sound("save", 50, 1.0);
    close(fd);
}
