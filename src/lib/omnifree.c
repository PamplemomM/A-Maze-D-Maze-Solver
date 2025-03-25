/*
** EPITECH PROJECT, 2025
** omnifree
** File description:
** Free anything.
*/

#include "../../include/header_amazed.h"

void *omnifree(void ***thing, int dimension)
{
    if (*thing == NULL)
        return NULL;
    if (dimension > 1) {
        for (int i = 0; (*thing)[i] != NULL; i++)
            omnifree((void ***)&(*thing)[i], dimension - 1);
    }
    free(*thing);
    *thing = NULL;
    return NULL;
}
