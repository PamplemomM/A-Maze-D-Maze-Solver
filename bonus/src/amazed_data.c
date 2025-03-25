/*
** EPITECH PROJECT, 2025
** amazed_data
** File description:
** Functions to manipulate and store the received maze data.
*/

#include "../include/header_viewer.h"

maze_t **get_maze(void)
{
    static maze_t *maze = NULL;

    return &maze;
}

static int parse_move(char *line)
{
    int i = 0;
    int j = 0;
    char *robot_name = get_name(line, &i, " -\n");
    char *room_name = get_name(&line[i], &j, " -\n");
    vwr_robot_t *robot = get_robot(atoi(&robot_name[1]));
    room_t *room = get_room(room_name, MAZE);

    OMNIFREE(robot_name, 1);
    OMNIFREE(room_name, 1);
    if (robot == NULL || room == NULL)
        return ERROR;
    return SUCCESS;
}

static int read_moves(void)
{
    char *line = NULL;
    size_t len = 0;

    while (strncmp(line, "#moves", 6) != 0) {
        if (getline(&line, &len, stdin) == -1) {
            OMNIFREE(line, 1);
            return ERROR;
        }
    }
    while (getline(&line, &len, stdin) != -1) {
        if (parse_move(line) == ERROR)
            return ERROR;
    }
    OMNIFREE(line, 1);
    return SUCCESS;
}

int read_maze(void)
{
    MAZE = parse_maze(VIEWER);
    if (MAZE == NULL)
        return ERROR;
    //if (read_moves() == ERROR) {
    //    free_maze(&MAZE);
    //    return ERROR;
    //}
    return SUCCESS;
}
