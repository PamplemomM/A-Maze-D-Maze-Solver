/*
** EPITECH PROJECT, 2025
** display_robot_path.c
** File description:
** Moving algorithm of all the different paths.
*/

#include "../../include/header_amazed.h"

int get_shorters_path_temp(pathlist_t *paths, maze_t *maze)
{
    pathlist_t *current = *paths;
    pathlist_t *winner = NULL;
    int min = 0;

    if (current == NULL)
        return winner;
    min = current->length;
    while (current != NULL) {
        if (current->length < min) {
            min = current->length;
            winner = current;
        }
        current = current->next;
    }
    return winner->path;
}

int calculate_paths_proportion(pathlist_t *paths, maze_t *maze)
{
    int max_id = get_movelength(paths->length, maze->nb_robots);

    if (paths == NULL)
        return ERROR;
    return SUCCESS;
}
/*

Step 1:
Trier tous les paths dans l'ordre croissant.
Step 2:
Launch every robots in a path is nb_robots >= tpath (length path).
Step 3:
Repeat.

Imagine a maze :
  A-B
 /   \         coding style
S--C--E
|\   /|
D  H  G
 \   /
  E-F

Paths :
S-C-E -> 2
S-H-E -> 2
S-A-B-E -> 3
S-D-E-F-G-E -> 5

Si il y a 3 robots, tu envoie dans les nb_robots (trois) premiers
qui sont triees si tpath (longueur du path) est inferieure ou egale au
nombre de robots.
Donc un dans SCE, un dans SHE et un dans SABE.

Si il y a 7 robots, ca va donc en envoyer un dans chaque path au premier tour,
et au deuxieme tour il n'y aura plus que 3 robots, donc ca va envoyer que
dans ceux <= 4 donc SCE, SHE ou SABE. Donc au total, un seul partira dans
SDEFGE car c'est le plus optimise.

*/
