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
