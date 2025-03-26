/*
** EPITECH PROJECT, 2025
** number_arsenal.c
** File description:
** An arsenal of functions that concern numbers.
*/

#include "../../include/header_tools.h"
#include <stdlib.h>

int digitcount(int nbr)
{
    int len = 0;

    if (nbr == 0)
        return 0;
    while (nbr != nbr / 10) {
        nbr /= 10;
        len++;
    }
    return len;
}

int diceroll(int low, int high)
{
    if (high < low)
        return high;
    return low + rand() % (high - low + 1);
}
