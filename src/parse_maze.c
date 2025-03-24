/*
** EPITECH PROJECT, 2025
** parse_maze.c
** File description:
** te file for parsing the maze.
*/
#include "../include/struct.h"
#include "../include/header_amazed.h"

maze_t *parse_maze(void)
{
    char *line = NULL;
    size_t len = 0;
    int end_or_start = 0;
    maze_t *maze = malloc(sizeof(maze_t));
    
    if (maze == NULL)
        return NULL;
    if (getline(&line, &len, stdin) == -1)
        return OMNIFREE(maze, 1);
    maze->nb_robots = my_getnbr(line);
    maze->rooms = NULL;
    maze->start = NULL;
    maze->end = NULL;
    while (getline(&line, &len, stdin) != -1) {     
        if (line[0] == '#' && my_strncmp(line, "##start", 7) == 0)
            end_or_start = 1;
        if (line[0] == '#' && my_strncmp(line, "##end", 5) == 0)
            end_or_start = 2;
        if (line[0] == '#')
            continue;
        if (parse_room(maze, line, &end_or_start) == 0)
            break;
    }
    OMNIFREE(line, 1);
    return maze;
}
// Il reste juste à implémenter le parsing des tunnels entre les rooms
