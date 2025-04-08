/*
** EPITECH PROJECT, 2025
** amazed_data.c
** File description:
** Functions to manipulate and store the received maze data.
*/

#include "../include/header_viewer.h"

maze_t **get_maze(void)
{
    static maze_t *maze = NULL;

    return &maze;
}

static int parse_move(char *line, int offset)
{
    static int move_id = 0;
    char *robot_name = get_name(line, &offset, " -\n");
    char *room_name = get_name(line, &offset, " -\n");
    room_t *room = get_room(room_name, MAZE);
    int robot_id;

    if (robot_name == NULL || room_name == NULL)
        return give_up("Move with invalid robot or room.", &MAZE);
    robot_id = my_getnbr(&robot_name[1]);
    OMNIFREE(robot_name, 1);
    OMNIFREE(room_name, 1);
    if (robot_id <= 0 || robot_id > MAZE->nb_robots)
        return give_up("Move with non-existent robot.", &MAZE);
    if (room == NULL)
        return give_up("Move to non-existent room.", &MAZE);
    make_move(robot_id, room, move_id, MAZE);
    if (line[offset] == 'P')
        return parse_move(line, offset);
    move_id++;
    return SUCCESS;
}

static int read_moves(void)
{
    char *line = NULL;
    size_t len = 0;
    int cnt = 0;

    while (!end_of_file(getline(&line, &len, stdin), &line)) {
        if (parse_move(line, 0) == ERROR) {
            OMNIFREE(line, 1);
            return ERROR;
        }
        cnt++;
    }
    if (cnt == 0 && line == NULL)
        return give_up("No moves.", &MAZE);
    OMNIFREE(line, 1);
    return SUCCESS;
}

int init_new_maze(void)
{
    maze_t *maze = malloc(sizeof(maze_t));

    if (maze == NULL)
        return ERROR;
    maze->nb_robots = 0;
    maze->rooms = NULL;
    maze->start = NULL;
    maze->end = NULL;
    maze->tunnels = NULL;
    maze->moves = NULL;
    maze->viewer = 2;
    MAZE = maze;
    return SUCCESS;
}

int read_maze(void)
{
    MAZE = parse_maze(1);
    if (MAZE == NULL)
        return ERROR;
    if (read_moves() == ERROR)
        return ERROR;
    return SUCCESS;
}
