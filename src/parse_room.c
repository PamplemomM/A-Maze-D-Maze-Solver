/*
** EPITECH PROJECT, 2025
** parse_room.c
** File description:
** Parsing of Rooms.
*/

#include "../include/header_amazed.h"

room_t *get_room(char *name, maze_t *maze)
{
    room_t *room = maze->rooms;

    if (name == NULL)
        return NULL;
    while (room != NULL) {
        if (my_strcmp(room->name, name) == 0)
            return room;
        room = room->next;
    }
    return NULL;
}

static room_t *check_valid_room(char *name, int x, int y, maze_t *maze)
{
    room_t *room = maze->rooms;

    while (room != NULL) {
        if (room->x == x && room->y == y)
            return room;
        room = room->next;
    }
    return get_room(name, maze);
}

static int add_room(char *name, int x, int y, maze_t *maze)
{
    room_t *room = check_valid_room(name, x, y, maze);

    if (room != NULL)
        return ERROR;
    else {
        room = malloc(sizeof(room_t));
        if (room == NULL)
            return ERROR;
    }
    room->name = my_strdup(name);
    if (room->name == NULL) {
        OMNIFREE(room, 1);
        return ERROR;
    }
    room->x = x;
    room->y = y;
    room->links = NULL;
    room->next = maze->rooms;
    maze->rooms = room;
    return SUCCESS;
}

char *get_name(char *line, int *i, char const *separators)
{
    char *name = NULL;

    while (!char_in_str(line[*i], separators) && line[*i] != '\0')
        (*i)++;
    name = malloc(sizeof(char) * (*i + 1));
    if (name == NULL)
        return NULL;
    for (int j = 0; j < *i; j++)
        name[j] = line[j];
    name[*i] = '\0';
    while (char_in_str(line[*i], separators) && line[*i] != '\0')
        (*i)++;
    return name;
}

static int get_coords(char *line, int *i)
{
    int nbr = 0;
    int tmp = *i;

    while (line[*i] >= '0' && line[*i] <= '9') {
        nbr = nbr * 10 + line[*i] - '0';
        (*i)++;
    }
    if (tmp == *i)
        return -1;
    while (line[*i] == ' ')
        (*i)++;
    return nbr;
}

static void handle_room(maze_t *maze, char *name, int *start_or_end)
{
    if (*start_or_end == 1)
        maze->start = get_room(name, maze);
    else if (*start_or_end == 2)
        maze->end = get_room(name, maze);
    *start_or_end = 0;
}

int parse_room(maze_t *maze, char *line, int *special)
{
    char *name = NULL;
    int x = 0;
    int y = 0;
    int i = 0;

    name = get_name(line, &i, " ");
    if (name == NULL)
        return ERROR;
    x = get_coords(line, &i);
    y = get_coords(line, &i);
    if (x == -1 || y == -1 || add_room(name, x, y, maze) == ERROR) {
        OMNIFREE(name, 1);
        return -1;
    }
    handle_room(maze, name, special);
    OMNIFREE(name, 1);
    return SUCCESS;
}
