/*
** EPITECH PROJECT, 2025
** display_robot_path.c
** File description:
** File for displaying the robots in a single path.
*/

#include "../../include/header_amazed.h"

int get_move_lenght(int path_size, int robot_count)
{
    return path_size + robot_count - 2;
}

int my_linked_size(path_t **node)
{
    int size = 0;
    path_t *current = *node;

    while (current != NULL) {
        size++;
        current = current->next;
    }
    return size;
}

static char **dup_pathlist(path_t **good_path)
{
    path_t *current = *good_path;
    int size = my_linked_size(good_path);
    int i = 0;
    char **path = malloc(sizeof(char *) * (size + 1));

    if (path == NULL)
        return NULL;
    current = *good_path;
    while (current != NULL) {
        path[i] = my_strdup(current->name);
        i++;
        current = current->next;
    }
    path[i] = NULL;
    return path;
}

static int print_move(int rbt, int id, char **path, int id_size)
{
    if (rbt <= id + 1 && abs(rbt - (id + 1)) < id_size)
        mini_printf("P%d-%s ", rbt, path[abs(rbt - (id + 1))]);
    return SUCCESS;
}

//mini_printf("Id=%d ; move=%d ; path_num=%d ; room %s\n",
    //id, rbt, abs(rbt - (id + 1)),
    //path[abs(rbt - (id + 1))]);
int display_robots_move_singlepath(path_t **good_path, maze_t *maze)
{
    char **path = dup_pathlist(good_path);
    int id_size = my_linked_size(good_path);
    int max_id = id_size + maze->nb_robots - 2;

    if (path == NULL)
        return ERROR;
    for (int id = 0; id <= max_id; id++) {
        for (int rbt = 1; rbt < maze->nb_robots + 1; rbt++) {
            print_move(rbt, id, path, id_size);
        }
        mini_printf("\n");
    }
    OMNIFREE(path, 2);
    return SUCCESS;
}
