/*
** EPITECH PROJECT, 2025
** display_robot_path.c
** File description:
** Moving algorithm of all the different paths.
*/

#include "../../include/header_amazed.h"

int calculate_paths_proportion(pathlist_t *paths, maze_t *maze)
{
    int max_id = get_movelength(paths->length, maze->nb_robots);

    if (paths == NULL)
        return ERROR;
    for (int id = 0; id <= max_id; id++) {
        for (int rbt = 1; rbt < maze->nb_robots + 1; rbt++) {
            print_move(rbt, id, path, id_size);
        }
        mini_printf("\n");
    }
    return SUCCESS;
}
