/*
** EPITECH PROJECT, 2025
** robots_list.c
** File description:
** Functions to manipulate the robots list.
*/

#include "../include/header_viewer.h"

vwr_robot_t **get_robotlist(void)
{
    static vwr_robot_t *robotlist = NULL;

    return &robotlist;
}

vwr_robot_t *get_robot(int id)
{
    vwr_robot_t *robot = *get_robotlist();

    while (robot != NULL) {
        if (robot->id == id)
            return robot;
        robot = robot->next;
    }
    return NULL;
}

static char *make_robot_name(int id)
{
    char *name = NULL;
    char *tmp = int_to_str(id);

    if (tmp == NULL)
        return NULL;
    name = merge_str("P", tmp);
    if (name == NULL)
        return OMNIFREE(tmp, 1);
    OMNIFREE(tmp, 1);
    return name;
}

static void gender_reveal(sprite_t *robot)
{
    if (diceroll(0, 100) <= 8) {
        robot->rect.left = 175;
        robot->rect.width = 185;
    } else
        robot->rect.width = 175;
}

static void setup_robot(vwr_robot_t *robot)
{
    sprite_t *sprite = robot->sprite;

    gender_reveal(sprite);
    sprite->scale = (sfVector2f){0.2, 0.2};
    center_sprite_origin(sprite, 0.5, 0.95);
    robot->next = *get_robotlist();
    *get_robotlist() = robot;
}

vwr_robot_t *make_robot(int id)
{
    vwr_robot_t *robot = NULL;
    sprite_t *sprite = NULL;
    char *name = make_robot_name(id);

    if (name == NULL)
        return NULL;
    sprite = make_sprite(name, "guy", MAZE->start->x * 50, MAZE->start->y * 50); // tmp position // fails if only 1 robot
    if (sprite == NULL)
        return OMNIFREE(name, 1);
    OMNIFREE(name, 1);
    robot = malloc(sizeof(vwr_robot_t));
    if (robot == NULL) {
        DESTROY(sprite, get_spritelist, free_sprite);
        return NULL;
    }
    robot->sprite = sprite;
    robot->id = id;
    robot->room = MAZE->start;
    setup_robot(robot);
    return robot;
}

void free_robot(vwr_robot_t *robot)
{
    DESTROY(robot->sprite, get_spritelist, free_sprite);
    OMNIFREE(robot, 1);
}
