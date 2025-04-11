/*
** EPITECH PROJECT, 2025
** create_move_sequence.c
** File description:
** The file that will help creating the move sequence.
*/

#include "../../include/header_amazed.h"

int display_every_move_humanread(maze_t *maze)
{
    move_t *current = maze->moves;

    while (current != NULL) {
        mini_printf("Moving %d in ", current->robot);
        mini_printf("%s during ", current->room_name);
        mini_printf("%d\n", current->id);
        current = current->next;
    }
    return SUCCESS;
}

int get_move_length(maze_t *maze)
{
    move_t *current = maze->moves;
    int max = 0;

    while (current != NULL) {
        if (current->id > max)
            max = current->id;
        current = current->next;
    }
    return max;
}

int display_every_move(maze_t *maze)
{
    move_t *headcpy = maze->moves;
    move_t *current = maze->moves;
    int actual_id = 1;
    int length = get_move_length(maze);
    int printed = 0;

    while (actual_id <= length) {
        if (current->id == actual_id) {
            printed = 1;
            mini_printf("P%d-%s ", current->robot, current->room_name);
        }
        current = current->next;
        if (current == NULL) {
            current = headcpy;
            actual_id++;
            mini_printf("%s", (printed == 1) ? "\n" : "");
        }
    }
    return SUCCESS;
}

int initialise_moving_sequence(pathlist_t **paths, maze_t *maze,
    int path_size)
{
    pathlist_t *current = *paths;
    path_t *shortest_path = get_shortest_path_temp(paths);
    int shortest = my_linked_size(&shortest_path);
    int start_id = 1;

    for (int i = 1; i < maze->nb_robots + 1; i++) {
        start_id = CEILING((i) / path_size) + 1;
        while (!(MAX(maze->nb_robots - start_id + 1, shortest + 1) >
            current->length + current->lower)) {
            current = (current->next == NULL) ? *paths : current->next;
        }
        if (MAX(maze->nb_robots - start_id + 1, shortest + 1) >
            current->length + current->lower)
            move_robot_untilend(&current, start_id, i, maze);
        current = current->next;
        if (current == NULL)
            current = *paths;
    }
    return SUCCESS;
}

int move_robot_untilend(pathlist_t **path, int start_id, int robot_id,
    maze_t *maze)
{
    pathlist_t *currentlist = *path;
    path_t *current = currentlist->path;
    int id = start_id;

    while (current != NULL) {
        make_move_wthname(robot_id, current->name, id, maze);
        id++;
        current = current->next;
    }
    return SUCCESS;
}
/*
DEBUG PRINTS:

in move_robo_untilend loop :
mini_printf("Making the move for robot %d during %d in %s\n",
    robot_id, id, current->name);


in initialise_moving_sequence for loop after start_id :
mini_printf("Moving robot %d\n", i);
mini_printf("MAX(%d, %d) > %d\n", maze->nb_robots - start_id + 1,
    shortest + 1, current->length + current->lower);
mini_printf("StartID = %d and path_num = %d actual path size : %d\n",
    start_id, path_size, current->length);

In initialise_moving_sequence while loop :
mini_printf("BAD : MAX(%d, %d) > %d\n", maze->nb_robots - start_id + 1,
    shortest + 1, current->length + current->lower);
*/
