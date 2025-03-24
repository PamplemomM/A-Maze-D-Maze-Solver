/*
** EPITECH PROJECT, 2025
** parse_maze.c
** File description:
** Input parsing and creation of the maze structure.
*/

#include "../include/header_amazed.h"

static void free_rooms(room_t *room)
{
    void *tmp = NULL;

    while (room != NULL) {
        tmp = room->next;
        OMNIFREE(room->name, 1);
        if (room->links != NULL)
            OMNIFREE(room->links, 1);
        OMNIFREE(room, 1);
        room = tmp;
    }
}

static void free_tunnels(tunnel_t *tunnel)
{
    void *tmp = NULL;

    while (tunnel != NULL) {
        tmp = tunnel->next;
        OMNIFREE(tunnel, 1);
        tunnel = tmp;
    }
}

static void free_moves(move_t *move)
{
    void *tmp = NULL;

    while (move != NULL) {
        tmp = move->next;
        OMNIFREE(move->robot, 1);
        OMNIFREE(move, 1);
        move = tmp;
    }
}

void free_maze(maze_t *maze)
{
    free_rooms(maze->rooms);
    free_tunnels(maze->tunnels);
    free_moves(maze->moves);
    OMNIFREE(maze, 1);
}

static int read_room(char *line, maze_t *maze)
{
    static int end_or_start = 0;

    if (line[0] == '#' && my_strncmp(line, "##start", 7) == 0)
        end_or_start = 1;
    if (line[0] == '#' && my_strncmp(line, "##end", 5) == 0)
        end_or_start = 2;
    if (line[0] == '#')
        return SUCCESS;
    return parse_room(maze, line, &end_or_start);
}

static int read_tunnel(char *line, maze_t *maze)
{
    if (line[0] == '#')
        return SUCCESS;
    return parse_tunnel(maze, line);
}

static int setup_maze(maze_t *maze, char *line, size_t len)
{
    while (line[0] < '0' && line[0] > '9') {
        if (getline(&line, &len, stdin) == -1)
            return ERROR;
    }
    maze->nb_robots = my_getnbr(line);
    maze->rooms = NULL;
    maze->start = NULL;
    maze->end = NULL;
    maze->tunnels = NULL;
    maze->moves = NULL;
    return SUCCESS;
}

maze_t *parse_maze(void)
{
    char *line = NULL;
    size_t len = 0;
    maze_t *maze = malloc(sizeof(maze_t));

    if (maze == NULL)
        return NULL;
    if (getline(&line, &len, stdin) == -1)
        return OMNIFREE(maze, 1);
    if (setup_maze(maze, line, len) == ERROR)
        return OMNIFREE(maze, 1);
    while (getline(&line, &len, stdin) != -1) {
        if (read_room(line, maze) != SUCCESS)
            break;
    }
    do {
        if (read_tunnel(line, maze) != SUCCESS)
            break;
    } while (getline(&line, &len, stdin) != -1);
    OMNIFREE(line, 1);
    return maze;
}
