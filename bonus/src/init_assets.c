/*
** EPITECH PROJECT, 2025
** init_assets.c
** File description:
** Functions to initialize the program's assets.
*/

#include "../include/header_viewer.h"

static int init_sprites(void)
{
    int inits[7] = {init_rooms(), init_tunnels(), init_robots(),
        init_compass(), init_logs(), init_progbar(), init_bg()};

    for (int i = 0; i < 7; i++) {
        if (inits[i] == ERROR)
            return ERROR;
    }
    return SUCCESS;
}

static int init_sounds(void)
{
    return precache_sounds();
}

static int init_music(void)
{
    if (play_music("Parade", "K.K. Parade", 0, 1.0) == NULL) // don't forget.
        return ERROR;
    sfMusic_setLoop((*get_music())->music, sfTrue);
    return SUCCESS;
}

int init_assets(void)
{
    create_window(800, 600, "A-MAZE-D VIEWER!");
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

// DESTROY THEM ALL !! (Like in the casino of my grandmother)
void destroy_assets(void)
{
    while (*get_robotlist())
        DESTROY(*get_robotlist(), get_robotlist, free_robot);
    while (*get_spritelist())
        DESTROY(*get_spritelist(), get_spritelist, free_sprite);
    if (*get_textlist())
        sfFont_destroy((*get_textlist())->font);
    while (*get_textlist())
        DESTROY(*get_textlist(), get_textlist, free_text);
    while (*get_tweenlist())
        DESTROY(*get_tweenlist(), get_tweenlist, free_tween);
    while (*get_timerlist())
        DESTROY(*get_timerlist(), get_timerlist, free_timer);
    while (*get_soundbank())
        DESTROY(*get_soundbank(), get_soundbank, free_sound);
    destroy_music();
    destroy_clock();
    destroy_window();
    destroy_cam();
    destroy_gamestuff();
}
