/*
** EPITECH PROJECT, 2025
** parse_maze.c
** File description:
** te file for parsing the maze.
*/
#include "../include/struct.h"
#include "../include/header_amazed.h"

void free_maze(maze_t *maze)
{
    room_t *current = maze->rooms;
    tunnel_t *tunnel = maze->tunnels;
    void *tmp = NULL;
    int i = 0;

    while (current != NULL) {
        tmp = current->next;
        OMNIFREE(current->name, 1);
        if (current->links != NULL)
            OMNIFREE(current->links, 1);
        OMNIFREE(current, 1);
        current = tmp;
    }
    while (tunnel != NULL) {
        tmp = tunnel->next;
        OMNIFREE(tunnel, 1);
        tunnel = tmp;
    }
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

static void nullify_maze(maze_t *maze)
{
    maze->rooms = NULL;
    maze->start = NULL;
    maze->end = NULL;
    maze->tunnels = NULL;
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
    maze->nb_robots = my_getnbr(line);
    nullify_maze(maze);
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
