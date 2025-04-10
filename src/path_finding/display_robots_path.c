/*
** EPITECH PROJECT, 2025
** display_robot_path.c
** File description:
** Moving algorithm of all the different paths.
*/

#include "../../include/header_amazed.h"

int sort_paths(pathlist_t **paths)
{
    pathlist_t *current = *paths;
    pathlist_t *temp = NULL;

    if (paths == NULL || *paths == NULL || (*paths)->next == NULL)
        return SUCCESS;
    while (current->next != NULL) {
        if (current->length > current->next->length) {
            temp = current->next;
            current->next = temp->next;
            temp->next = current;
            if (current == *paths)
                *paths = temp;
            sort_paths(paths);
            return SUCCESS;
        }
        current = current->next;
    }
    return SUCCESS;
}

int get_pathcount(pathlist_t **paths)
{
    int cpt = 0;
    pathlist_t *current = *paths;

    while (current != NULL) {
        cpt++;
        current = current->next;
    }
    return cpt;
}

pathlist_t *get_shortest_pathlist(pathlist_t **paths)
{
    pathlist_t *shortest = NULL;
    pathlist_t *current = *paths;
    int min = MAX_INT;

    while (current != NULL) {
        if (current->length < min) {
            min = current->length;
            shortest = current;
        }
        current = current->next;
    }
    return shortest;
}

int get_lowerpath_count(pathlist_t **paths, pathlist_t *current)
{
    int cpt = 0;
    pathlist_t *curr = *paths;

    while (curr != NULL) {
        if ((curr != current) && (curr->length < current->length))
            cpt++;
        curr = curr->next;
    }
    return cpt;
}

int find_path_lower(pathlist_t **paths)
{
    pathlist_t *current = *paths;

    while (current != NULL) {
        current->lower = get_lowerpath_count(paths, current);
        current = current->next;
    }
    return SUCCESS;
}

int calculate_paths_proportion(pathlist_t **paths, maze_t *maze)
{
    pathlist_t *current = *paths;
    path_t *shortest_path = get_shortest_path_temp(paths);
    int shortest = my_linked_size(&shortest_path);
    pathlist_t *tmp = NULL;

    if (*paths == NULL)
        return SUCCESS;
    while (current != NULL) {
        tmp = current->next;
        if (MAX(maze->nb_robots, shortest + 1) <= current->length +
            current->lower) {
            delete_path_fromlist(current, paths);
        }
        current = tmp;
    }
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
