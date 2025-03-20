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
    room_t *temp;

    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp->name);
        if (temp->links != NULL)
            free(temp->links);
        free(temp);
    }
    free(maze);
}

room_t *init_room(char *name, int x, int y)
{
    room_t *room = malloc(sizeof(room_t));

    if (room == NULL)
        return NULL;
    room->name = my_strdup(name);
    if (room->name == NULL) {
        free(room);
        return NULL;
    }
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

static void get_name(char *line, char *name, int *i)
{
    int j = 0;

    while (line[*i] != ' ' && line[*i] != '\0') {
        name[j] = line[(*i)];
        j++;
        (*i)++;
    }
    name[j] = '\0';
    while (line[*i] == ' ')
        (*i)++;
}

static int get_coords(char *line, int *i)
{
    char coord[100];
    int j = 0;

    while (line[*i] != ' ' && line[*i] != '\0' && line[*i] != '\n') {
        coord[j] = line[(*i)];
        j++;
        (*i)++;
    }
    coord[j] = '\0';
    while (line[*i] == ' ')
        (*i)++;
    return my_getnbr(coord);
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
    char *name = malloc(sizeof(char) * (my_strlen(line) + 1));
    int x = 0;
    int y = 0;
    int i = 0;

    get_name(line, name, &i);
    x = get_coords(line, &i);
    y = get_coords(line, &i);
    if (name[0] == '\0' || (x == 0 && y == 0))
        return 0;
    add_room(&maze->rooms, name, x, y);
    handle_room(maze, name, special);
    return 1;
}


