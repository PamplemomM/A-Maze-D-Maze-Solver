/*
** EPITECH PROJECT, 2025
** robots_list
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

static void gender_reveal(sprite_t *robot)
{
    if (diceroll(0, 100) <= 8) {
        robot->rect.left = 175;
        robot->rect.width = 185;
    } else
        robot->rect.width = 175;
}

static void robot_tweaks(sprite_t *robot)
{
    //robot->scale = (sfVector2f){0.3, 0.3};
    sfSprite_setOrigin(robot->sprite,
        (sfVector2f){robot->rect.width / 2.0, robot->rect.height / 2.0});
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

vwr_robot_t *make_robot(int id)
{
    vwr_robot_t *robot = NULL;
    sprite_t *sprite = NULL;
    char *name = make_robot_name(id);

    if (name == NULL)
        return NULL;
    sprite = make_sprite(name, "guy", 150 + (id - 1) * (500 / (MAZE->nb_robots - 1)), 285); // tmp position // fails if only 1 robot
    printf("lala\n");
    if (sprite == NULL)
        return OMNIFREE(name, 1);
    OMNIFREE(name, 1);
    robot = malloc(sizeof(vwr_robot_t));
    if (robot == NULL) {
        DESTROY(sprite, get_spritelist, free_sprite);
        return NULL;
    }
    robot->id = id;
    robot->room = MAZE->start;
    gender_reveal(sprite);
    robot->next = *get_robotlist();
    *get_robotlist() = robot;
    return robot;
}

void free_robot(vwr_robot_t *robot)
{
    OMNIFREE(robot, 1);
}
