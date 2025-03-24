/*
** EPITECH PROJECT, 2025
** parse_room.c
** File description:
** Room parsing.
*/

#include "../include/header_amazed.h"

static room_t *init_room(char *name, int x, int y)
{
    room_t *room = malloc(sizeof(room_t));

    if (room == NULL)
        return NULL;
    room->name = my_strdup(name);
    if (room->name == NULL)
        return OMNIFREE(room, 1);
    room->x = x;
    room->y = y;
    room->links = NULL;
    room->next = NULL;
    return room;
}

room_t *find_room_name(room_t *room, char *name)
{
    room_t *target_room = room;

    if (name == NULL)
        return NULL;
    while (target_room != NULL) {
        if (my_strcmp(target_room->name, name) == 0)
            return target_room;
        target_room = target_room->next;
    }
    return NULL;
}

static int add_room(char *name, int x, int y, room_t **rooms)
{
    room_t *new_room = init_room(name, x, y);

    if (new_room == NULL)
        return ERROR;
    new_room->next = *rooms;
    *rooms = new_room;
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
        maze->start = find_room_name(maze->rooms, name);
    else if (*start_or_end == 2)
        maze->end = find_room_name(maze->rooms, name);
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
    if (x == -1 || y == -1 || add_room(name, x, y, &maze->rooms) == ERROR) {
        OMNIFREE(name, 1);
        return -1;
    }
    handle_room(maze, name, special);
    OMNIFREE(name, 1);
    return SUCCESS;
}
