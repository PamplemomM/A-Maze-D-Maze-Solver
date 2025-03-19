/*
** EPITECH PROJECT, 2025
** amazed_data
** File description:
** Functions to manipulate and store the A-Maze-d data.
*/

#include "../include/header.h"

data_t **get_data(void)
{
    static data_t *data = NULL;

    return &data;
}

int read_data(void)
{
    DATA = malloc(sizeof(data_t));
    if (DATA == NULL)
        return -1;
    DATA->robotcnt = 3;
    DATA->rooms = NULL;
    DATA->moves = NULL;
    return 0;
}

void destroy_data(void)
{
    if (DATA == NULL)
        return;
    // to do
    free(DATA);
}
