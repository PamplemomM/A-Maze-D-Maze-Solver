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

static int parse_move(char *line, int offset)
{
    static int move_id = 0;
    char *robot_name = get_name(line, &offset, " -\n");
    char *room_name = get_name(line, &offset, " -\n");
    int robot_id = my_getnbr(&robot_name[1]);
    room_t *room = get_room(room_name, MAZE);

    printf("P%d-%s ", my_getnbr(&robot_name[1]), room_name);
    OMNIFREE(robot_name, 1);
    OMNIFREE(room_name, 1);
    if (robot_id <= 0 || robot_id > MAZE->nb_robots || room == NULL)
        return ERROR;
    make_move(robot_id, room, move_id, MAZE);
    if (line[offset] == 'P')
        return parse_move(line, offset);
    printf("\n");
    move_id++;
    return SUCCESS;
}

static int read_moves(void)
{
    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, stdin) != -1) {
        if (parse_move(line, 0) == ERROR) {
            OMNIFREE(line, 1);
            return ERROR;
        }
    }
    OMNIFREE(line, 1);
    return SUCCESS;
}

int read_maze(void)
{
    MAZE = parse_maze();
    if (MAZE == NULL)
        return ERROR;
    if (read_moves() == ERROR) {
        free_maze(&MAZE);
        return ERROR;
    }
    return SUCCESS;
}
