/*
** EPITECH PROJECT, 2025
** header_amazed.h
** File description:
** The header for the RobotFactory project.
*/

#ifndef AMAZED_H
    #define AMAZED_H

    #include <stddef.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <stdio.h>

    //defines :
    #define SUCCESS 0
    #define ERROR 84


// ----------- LIB FUNCTIONS -----------

// --- lib_c_functions.c ---
int my_getnbr(char const *str);
int mini_printf(const char *format, ...);

// --- my_stringlib.c ---
int my_strlen(char const *str);
char *my_strdup(char const *src);
char *my_strcpy(char *dest, char const *src);
int my_strcmp(char const *s1, char const *s2);
int my_strncmp(char const *s1, char const *s2, int n);

// --- my_str_to_word_array.c ---
char **my_str_to_word_array(char *str);
void free_word_array(char **wa);
int my_print_wa(char **wa);

// --- my_strchr.c ---
char *my_strchr(char const *str, int c);
char *my_strrchr(const char *str, int c);

// --- my_strtok.c ---
char *my_strtok(char *str, char const *delim);

#endif /* AMAZED_H */
