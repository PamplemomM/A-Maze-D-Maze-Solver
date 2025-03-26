/*
** EPITECH PROJECT, 2025
** parse_maze.c
** File description:
** Input parsing and creation of the maze structure.
*/

#include "../../include/header_amazed.h"

tunnel_t *get_tunnel(room_t *r1, room_t *r2, maze_t *maze)
{
    tunnel_t *tunnel = maze->tunnels;

    if (r1 == NULL || r2 == NULL)
        return NULL;
    while (tunnel != NULL) {
        if (tunnel->r1 == r1 && tunnel->r2 == r2)
            return tunnel;
        tunnel = tunnel->next;
    }
    return NULL;
}

static int check_possible_path(room_t *r1, room_t *r2, maze_t *maze)
{
    tunnel_t *tunnel = NULL;

    if (r1 == NULL || r2 == NULL)
        return ERROR;
    if (r1 == r2)
        return SUCCESS;
    if (r1->links == NULL)
        return ERROR;
    for (int i = 0; r1->links[i] != NULL; i++) {
        tunnel = get_tunnel(r1, r1->links[i], maze);
        if (tunnel == NULL || tunnel->val == 0)
            continue;
        tunnel->val = 0;
        if (check_possible_path(r1->links[i], r2, maze) == SUCCESS) {
            tunnel->val = 1;
            return SUCCESS;
        }
    }
    return ERROR;
}

static int check_valid_maze(maze_t *maze)
{
    if (maze == NULL || maze->nb_robots <= 0 || maze->tunnels == NULL)
        return ERROR;
    if (check_possible_path(maze->start, maze->end, maze) == ERROR)
        return ERROR;
    return SUCCESS;
}

static int read_room(char *line, maze_t **maze)
{
    static int end_or_start = 0;

    if (line[0] == '#' && my_strncmp(line, "##start", 7) == 0) {
        if ((*maze != NULL && (*maze)->start != NULL) || end_or_start != 0)
            return ERROR;
        end_or_start = 1;
    }
    if (line[0] == '#' && my_strncmp(line, "##end", 5) == 0) {
        if ((*maze != NULL && (*maze)->end != NULL) || end_or_start != 0)
            return ERROR;
        end_or_start = 2;
    }
    if (line[0] == '#')
        return SUCCESS;
    return parse_room(*maze, line, &end_or_start);
}

static int read_tunnel(char *line, maze_t **maze, case_t cs)
{
    if (*maze == NULL)
        return ERROR;
    if (line[0] == '#')
        return SUCCESS;
    if (parse_tunnel(*maze, line) == ERROR) {
        if (cs == MAIN)
            return ERROR;
    }
    return SUCCESS;
}

static int setup_maze(maze_t *maze, char *line, size_t len)
{
    while (line[0] < '0' || line[0] > '9') {
        if (getline(&line, &len, stdin) == -1) {
            OMNIFREE(line, 1);
            return ERROR;
        }
    }
    maze->nb_robots = my_getnbr(line);
    maze->rooms = NULL;
    maze->start = NULL;
    maze->end = NULL;
    maze->tunnels = NULL;
    maze->moves = NULL;
    return SUCCESS;
}

maze_t *parse_maze(case_t cs)
{
    char *line = NULL;
    size_t len = 0;
    maze_t *maze = malloc(sizeof(maze_t));

    if (maze == NULL || getline(&line, &len, stdin) == -1
        || setup_maze(maze, line, len) == ERROR)
        return OMNIFREE(maze, 1);
    while (getline(&line, &len, stdin) != -1) {
        if (read_room(line, &maze) != SUCCESS)
            break;
    }
    do {
        if (read_tunnel(line, &maze, cs) != SUCCESS)
            break;
    } while (getline(&line, &len, stdin) != -1);
    OMNIFREE(line, 1);
    if (check_valid_maze(maze) == ERROR)
        return maze;
    return maze;
}
