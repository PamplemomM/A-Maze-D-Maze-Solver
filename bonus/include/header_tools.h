/*
** EPITECH PROJECT, 2025
** header_tools.h
** File description:
** Header for my tool functions.
*/

#ifndef TOOLS_H
    #define TOOLS_H

    #include "../../include/header_amazed.h"

    // functions:
    #define SDFREE(format, ...) salade_de_free(format, __VA_ARGS__)
    #define ULTRALEN(thing, end) ultralen((void **)thing, (void *)end)

// ------- C LIB TOOL FUNCTIONS --------

// --- salade_de_free.c ---
void *salade_de_free(char const *format, ...);

// --- string_arsenal.c ---
char *merge_str(char *s1, char *s2);
char *int_to_str(int nbr);

// --- number_arsenal.c ---
int digitcount(int nbr);
int diceroll(int low, int high);

// --- ultralen.c ---
int ultralen(void **thing, void *end);

#endif /* TOOLS_H */
