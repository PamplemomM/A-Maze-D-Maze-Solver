/*
** EPITECH PROJECT, 2025
** init_assets.c
** File description:
** Functions to initialize the program's assets.
*/

#include "../include/header_viewer.h"

static int init_robots(void)
{
    for (int i = 1; i <= MAZE->nb_robots; i++) {
        if (make_robot(i) == NULL)
            return ERROR;
    }
    return SUCCESS;
}

static int init_rooms(void)
{
    room_t *room = MAZE->rooms;
    char *name = NULL;

    while (room != NULL) {
        name = merge_str("room_", room->name);
        if (name == NULL)
            return ERROR;
        if (make_sprite(name, "jonkler", room->x * 50, room->y * 50) == NULL) {
            OMNIFREE(name, 1);
            return ERROR;
        }
        center_sprite_origin(get_sprite(name), 0.5, 0.5);
        OMNIFREE(name, 1);
        room = room->next;
    }
    return SUCCESS;
}

static int init_sprites(void)
{
    if (init_robots() == ERROR)
        return ERROR;
    if (init_rooms() == ERROR)
        return ERROR;
    if (make_sprite("bg", "bg", -100, -50) == NULL)
        return ERROR;
    get_sprite("bg")->color = color_from_hue(0, 255, 255, 255);
    return SUCCESS;
}

static int init_sounds(void)
{
    return SUCCESS;
}

static int init_music(void)
{
    if (play_music("Parade", "K.K. Parade", 50, 1.0) == NULL) // put the volume back up to 50
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
