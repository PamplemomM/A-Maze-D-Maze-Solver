/*
** EPITECH PROJECT, 2025
** init_assets
** File description:
** Functions to initialize the program's assets.
*/

#include "../include/header.h"

static void gender_reveal(sprite_t *guy, int i)
{
    if (diceroll(0, 100) <= 8) {
        guy->rect.left = 175;
        guy->rect.width = 185;
    } else
        guy->rect.width = 175;
    guy->color = color_from_hue(360 / DATA->robotcnt * i + GAME->hue, 255, 225);
}

static void *init_sprites(void)
{
    char *name;
    char *tmp;

    for (int i = 0; i < DATA->robotcnt; i++) {
        name = malloc(sizeof(char) * (digitcount(i) + 2));
        if (name == NULL)
            return NULL;
        strcpy(name, "P");
        tmp = int_to_str(i);
        if (tmp == NULL)
            return OMNIFREE(name, 1);
        strcpy(name, tmp);
        OMNIFREE(tmp, 1);
        make_sprite(name, "assets/guy.png", 100 + i * (400 / DATA->robotcnt), 100);
        if (get_sprite(name) == NULL)
            return OMNIFREE(name, 1);
        gender_reveal(get_sprite(name), i);
        OMNIFREE(name, 1);
    }
}

static void *init_sounds(void)
{
}

static void *init_music(void)
{
}

void *init_assets(void)
{
    create_window(800, 600, "A-MAZING!");
    *get_clock() = sfClock_create();
    if (init_sprites() == NULL)
        return NULL;
    if (init_sounds() == NULL)
        return NULL;
    if (init_music() == NULL)
        return NULL;
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
    free(DATA);
}
