/*
** EPITECH PROJECT, 2024
** amazed
** File description:
** parse.c
*/

#include "../include/struct.h"

void free_maze(maze_t *maze)
{
    room_t *current = maze->rooms;
    room_t *tmp = NULL;
    int i = 0;

    while (current != NULL) {
        tmp = current->next;
        OMNIFREE(current->name, 1);
        if (current->links != NULL)
            OMNIFREE(current->links, 1);
        OMNIFREE(current, 1);
        current = tmp;
    }
    OMNIFREE(maze, 1);
}

room_t *init_room(char *name, int x, int y)
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

    while (target_room != NULL) {
        if (my_strcmp(target_room->name, name) == 0)
            return target_room;
        target_room = target_room->next;
    }
    return NULL;
}

void add_room(char *name, int x, int y, room_t **room)
{
    room_t *new_room = init_room(name, x, y);

    if (new_room == NULL)
        return;
    new_room->next = *room;
    *room = new_room;
}

static char *get_name(char *line, int *i)
{
    char *name = NULL;

    while (line[*i] != ' ' && line[*i] != '\0')
        (*i)++;
    name = malloc(sizeof(char) * (*i + 1));
    if (name == NULL)
        return NULL;
    for (int j = 0; j < *i; j++)
        name[j] = line[j];
    name[*i] = '\0';
    while (line[*i] == ' ')
        (*i)++;
    return name;
}

static int get_coords(char *line, int *i)
{
    int nbr = 0;
    int tmp = *i;

    while (line[*i] >= '0' && line[*i] <= '9') { // line[*i] != ' ' && line[*i] != '\0' && line[*i] != '\n') {
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

    name = get_name(line, &i);
    x = get_coords(line, &i);
    y = get_coords(line, &i);
    if (name == NULL || x == -1 || y == -1) {
        OMNIFREE(name, 1);
        return 0;
    }
    add_room(name, x, y, &maze->rooms);
    handle_room(maze, name, special);
    OMNIFREE(name, 1);
    return 1;
}
