/*
** EPITECH PROJECT, 2025
** init_assets
** File description:
** Functions to initialize the program's assets.
*/

#include "../include/header_viewer.h"

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

static void *init_robots(void)
{
    char *name;
    char *tmp;

    for (int i = 1; i <= MAZE->nb_robots; i++) {
        name = malloc(sizeof(char) * (digitcount(i) + 2));
        if (name == NULL)
            return NULL;
        strcpy(name, "P");
        tmp = int_to_str(i);
        if (tmp == NULL)
            return OMNIFREE(name, 1);
        strcpy(&name[1], tmp);
        OMNIFREE(tmp, 1);
        make_sprite(name, "assets/guy.png", 150 + (i - 1) * (500 / (MAZE->nb_robots - 1)), 285); // fails if only 1 robot
        if (get_sprite(name) == NULL)
            return OMNIFREE(name, 1);
        gender_reveal(get_sprite(name));
        robot_tweaks(get_sprite(name));
        OMNIFREE(name, 1);
    }
}

static int init_sprites(void)
{
    if (init_robots() == NULL)
        return ERROR;
    make_sprite("bg", "assets/bg.png", -100, -50);
    get_sprite("bg")->color = color_from_hue(0, 255, 255, 255);
    return SUCCESS;
}

static int init_sounds(void)
{
    return SUCCESS;
}

static int init_music(void)
{
    return SUCCESS;
}

int init_assets(void)
{
    create_window(800, 600, "A-MAZING!");
    *get_clock() = sfClock_create();
    if (init_cam() == NULL)
        return ERROR;
    if (init_sprites() == ERROR)
        return ERROR;
    if (init_sounds() == ERROR)
        return ERROR;
    if (init_music() == ERROR)
        return ERROR;
    return SUCCESS;
}

void destroy_assets(void)
{
    while (*get_spritelist())
        destroy_sprite(*get_spritelist());
    if (*get_textlist() != NULL)
        sfFont_destroy((*get_textlist())->font);
    while (*get_textlist())
        destroy_text(*get_textlist());
    while (*get_tweenlist())
        destroy_tween((*get_tweenlist())->name);
    while (*get_timerlist())
        destroy_timer((*get_timerlist())->name);
    while (*get_soundbank())
        destroy_sound(*get_soundbank());
    destroy_music();
    destroy_clock();
    destroy_window();
    destroy_cam();
    destroy_gamestuff();
}
