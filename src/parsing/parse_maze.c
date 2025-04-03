/*
** EPITECH PROJECT, 2025
** parse_maze.c
** File description:
** Input parsing and creation of the maze structure.
*/

#include "../../include/header_amazed.h"

int give_up(char const *message, maze_t **maze)
{
    if (*maze == NULL)
        return ERROR;
    if (!(*maze)->viewer)
        print_maze(*maze);
    PRINT("PARSING ERROR: %s\n", message);
    free_maze(maze);
    return ERROR;
}

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

static int check_valid_maze(maze_t **maze)
{
    if (*maze == NULL)
        return ERROR;
    if ((*maze)->nb_robots <= 0)
        return give_up("Invalid number of robots.", maze);
    if ((*maze)->rooms == NULL)
        return give_up("No rooms.", maze);
    if ((*maze)->start == NULL)
        return give_up("No start room.", maze);
    if ((*maze)->end == NULL)
        return give_up("No end room.", maze);
    if ((*maze)->tunnels == NULL)
        return give_up("No tunnels.", maze);
    if (check_possible_path((*maze)->start, (*maze)->end, *maze) == ERROR)
        return give_up("End room cannot be reached.", maze);
    return SUCCESS;
}

static int read_room(char *line, maze_t **maze)
{
    static int end_or_start = 0;

    if (line == NULL)
        return ERROR;
    if (line[0] == '#' && my_strncmp(line, "##start", 7) == 0) {
        if ((*maze != NULL && (*maze)->start != NULL) || end_or_start != 0)
            return give_up("Multiple start rooms.", maze);
        end_or_start = 1;
    }
    if (line[0] == '#' && my_strncmp(line, "##end", 5) == 0) {
        if ((*maze != NULL && (*maze)->end != NULL) || end_or_start != 0)
            return give_up("Multiple end rooms.", maze);
        end_or_start = 2;
    }
    if (line[0] == '#')
        return SUCCESS;
    return parse_room(maze, line, &end_or_start);
}

static int read_tunnel(char *line, maze_t **maze)
{
    if (*maze == NULL || line == NULL)
        return ERROR;
    if ((*maze)->viewer && my_strncmp(line, "#moves", 6) == 0)
        return ERROR;
    if (line[0] == '#')
        return SUCCESS;
    return parse_tunnel(maze, line);
}

static int setup_maze(maze_t **maze, char *line, size_t len, int viewer)
{
    (*maze)->nb_robots = 0;
    (*maze)->rooms = NULL;
    (*maze)->start = NULL;
    (*maze)->end = NULL;
    (*maze)->tunnels = NULL;
    (*maze)->moves = NULL;
    (*maze)->viewer = viewer;
    if (getline(&line, &len, stdin) == -1) {
        OMNIFREE(line, 1);
        return give_up("Empty file.", maze);
    }
    while (line[0] == '#') {
        if (getline(&line, &len, stdin) == -1) {
            OMNIFREE(line, 1);
            return give_up("No robots.", maze);
        }
    }
    (*maze)->nb_robots = my_getnbr(line);
    OMNIFREE(line, 1);
    return SUCCESS;
}

int end_of_file(int return_value, char **line)
{
    if (return_value == -1) {
        OMNIFREE(*line, 1);
        return 1;
    }
    return 0;
}

maze_t *parse_maze(int viewer)
{
    char *line = NULL;
    size_t len = 0;
    maze_t *maze = malloc(sizeof(maze_t));

    if (maze == NULL || setup_maze(&maze, line, len, viewer) == ERROR)
        return OMNIFREE(maze, 1);
    while (!end_of_file(getline(&line, &len, stdin), &line)) {
        if (read_room(line, &maze) != SUCCESS)
            break;
    }
    do {
        if (read_tunnel(line, &maze) != SUCCESS)
            break;
    } while (getline(&line, &len, stdin) != -1);
    OMNIFREE(line, 1);
    if (check_valid_maze(&maze) == ERROR)
        return NULL;
    return maze;
}
