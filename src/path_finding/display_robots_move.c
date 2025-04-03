/*
** EPITECH PROJECT, 2025
** move_robots.c
** File description:
** Moving algorithm of the best path.
*/

#include "../../include/header_amazed.h"

static int my_linked_size(path_t **node)
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

int display_robots_move(path_t **good_path, maze_t *maze)
{
    char **path = dup_pathlist(good_path);
    int id_size = my_linked_size(good_path);
    int max_id = id_size + maze->nb_robots - 2;
    //int id = 0;

    if (path == NULL)
        return ERROR;
    for (int id = 0; id <= max_id; id++) {
        for (int rbt = 1; rbt < maze->nb_robots + 1; rbt++) {
            if (rbt <= id + 1 && abs(rbt - (id + 1)) < id_size)
                //mini_printf("Id=%d ; move=%d ; path_num=%d ; room %s\n",
                    //id, rbt, abs(rbt - (id + 1)),
                    //path[abs(rbt - (id + 1))]);
                mini_printf("P%d-%s ", rbt, path[abs(rbt - (id + 1))]);
        }
        mini_printf("\n");
    }
    
    
    
    
    
    
    /*for (int rbt = 1; rbt < maze->nb_robots + 1; rbt++) {
        if (id < rbt)
            continue;
        mini_printf("P%d-%s\n", rbt, path[rbt + id]);
        id++;
    }
    for (int i = 0; path[i] != NULL; i++) {
        for (int rbt = 1; rbt < maze->nb_robots + 1; rbt++)
            mini_printf("P%d-%s\n", rbt, path[i]);
    }*/
    OMNIFREE(path, 2);
    return SUCCESS;
}

