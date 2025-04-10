/*
** EPITECH PROJECT, 2025
** find_moves.c
** File description:
** Find the best path of the maze.
*/

#include "../../include/header_amazed.h"

int display_paths_order(pathlist_t **paths)
{
    pathlist_t *current = *paths;

    while (current != NULL) {
        mini_printf(" -- %d --\n", current->length);
        current = current->next;
    }
    return SUCCESS;
}

static path_t *add_path_node(path_t **head, room_t *room)
{
    path_t *headcpy = *head;
    path_t *path = malloc(sizeof(path_t));

    if (path == NULL)
        return NULL;
    path->room = room;
    path->next = NULL;
    if (headcpy == NULL) {
        *head = path;
        return path;
    }
    while (headcpy->next != NULL)
        headcpy = headcpy->next;
    headcpy->next = path;
    return path;
}

static void free_path_list(path_t *path_list)
{
    path_t *tmp;

    while (path_list != NULL) {
        tmp = path_list;
        path_list = path_list->next;
        free(tmp);
    }
}

static int is_room_available(room_t *room, move_t *current, int current_id)
{
    move_t *move = current;

    while (move != NULL) {
        if (move->id == current_id && move->dest == room) {
            return FALSE;
        }
        move = move->next;
    }
    return TRUE;
}

static path_t *find_possible_paths(room_t *current, move_t *current_moves,
    int current_id)
{
    path_t *paths = NULL;
    room_t *potential_room = NULL;

    for (int i = 0; current->links[i] != NULL; i++) {
        potential_room = current->links[i];
        if (is_room_available(potential_room, current_moves,
            current_id) == TRUE) {
            add_path_node(&paths, potential_room);
        }
    }
    return paths;
}

static room_t *select_best_path(room_t *current, room_t *dest_room,
    move_t *current_moves, int current_id)
{
    path_t *paths = find_possible_paths(current, current_moves, current_id);
    room_t *best_path = NULL;
    int dist_min = 1000000;
    path_t *path = paths;
    int dist = 0;

    while (path != NULL) {
        dist = abs(path->room->x - dest_room->x) +
            abs(path->room->y - dest_room->y);
        if (dist < dist_min) {
            dist_min = dist;
            best_path = path->room;
        }
        path = path->next;
    }
    free_path_list(paths);
    return best_path;
}

move_t *find_moves(maze_t *maze, int current_id)
{
    move_t *move_list = NULL;
    room_t *next = NULL;
    room_t *current = maze->start;

    for (int i = 0; i < maze->nb_robots; i++) {
        if (current == maze->end) {
            continue;
        }
        next = select_best_path(current, maze->end, move_list, current_id);
        if (next != NULL) {
            make_move(i, next, current_id, maze);
        }
        current = current->next;
    }
    return move_list;
}
