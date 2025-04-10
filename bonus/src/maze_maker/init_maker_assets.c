/*
** EPITECH PROJECT, 2025
** init_maker_assets.c
** File description:
** Functions to initialize the program's assets.
*/

#include "../../include/header_viewer.h"

static int init_room_select(void)
{
    if (make_sprite("room_select", "room_select", 0, 0) == NULL)
        return ERROR;
    get_sprite("room_select")->color = color_from_hue(0, 255, 0, 150);
    get_sprite("room_select")->type = ROOM;
    center_sprite_origin(get_sprite("room_select"), 0.5, 0.5);
    return SUCCESS;
}

static int init_start_room(void)
{
    if (add_room("0_0", 0, 0, &MAZE) == ERROR)
        return ERROR;
    MAZE->start = get_room("0_0", MAZE);
    if (create_room_sprite(MAZE->start) == ERROR)
        return ERROR;
    get_sprite("room_0_0")->color = color_from_hue(0, 240, 0, 255);
    return SUCCESS;
}

static int init_maker_sprites(void)
{
    int inits[6] = {init_room_select(), init_start_room(),
        init_blackscreen(), init_compass(), init_logs(), init_bg()};

    for (int i = 0; i < 6; i++) {
        if (inits[i] == ERROR)
            return ERROR;
    }
    get_sprite("light")->color = color_from_hue(0, 100, 0, 255);
    return SUCCESS;
}

static int init_maker_music(void)
{
    if (play_music("Floor One", "Dorkus64 - Floor One", 0, 1.0) == NULL)
        return ERROR;
    make_tween("music_fadein", &MUSIC->volume,
        0, 5.0)->method = EASEINOUT; // go fuck youruseellf
    sfMusic_setLoop(MUSIC->music, sfTrue);
    return SUCCESS;
}

int init_maker_assets(void)
{
    create_window(800, 600, "A-MAZE-D VIEWER!");
    *get_clock() = sfClock_create();
    MAZE->nb_robots = 1;
    GAME->state = MKR_NONE;
    GAME->bounds = (sfIntRect){0, 0, 1, 1};
    if (init_cam() == NULL)
        return ERROR;
    setup_camera();
    get_tween("camzoom")->start = 1.0;
    get_tween("camzoom")->dest = 0.5;
    if (init_maker_sprites() == ERROR)
        return ERROR;
    if (init_sounds() == ERROR)
        return ERROR;
    if (init_maker_music() == ERROR)
        return ERROR;
    return SUCCESS;
}
