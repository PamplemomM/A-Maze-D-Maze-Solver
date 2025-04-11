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

static int init_icons(void)
{
    if (make_sprite("icon", "maker_icons", 40, 40) == NULL)
        return ERROR;
    get_sprite("icon")->scale = (sfVector2f){2.0, 2.0};
    get_sprite("icon")->rect.width = 25;
    get_sprite("icon")->type = HUD;
    center_sprite_origin(get_sprite("icon"), 0.5, 0.5);
    return SUCCESS;
}

static int init_display_robot_counter(void)
{
    char *nb_robots = int_to_str(MAZE->nb_robots);

    if (nb_robots == NULL)
        return ERROR;
    if (make_text("nb_robots", nb_robots,
        765 - digitcount(MAZE->nb_robots) * 22, 20) == NULL) {
        OMNIFREE(nb_robots, 1);
        return ERROR;
    }
    OMNIFREE(nb_robots, 1);
    get_text("nb_robots")->color = color_from_hue(0, 255, 0, 150);
    get_text("nb_robots")->type = HUD;
    sfText_setCharacterSize(get_text("nb_robots")->text, 80);
    return SUCCESS;
}

static int init_display_robots(void)
{
    if (init_display_robot_counter() == ERROR)
        return ERROR;
    for (int i = 1; i <= MAZE->nb_robots; i++) {
        if (make_robot(i) == NULL)
            return ERROR;
        get_robot(i)->sprite->pos.x = 750 -
            ((i - 1) / ((float)MAZE->nb_robots)) * 100.0;
        get_robot(i)->sprite->pos.y = 90;
        get_robot(i)->sprite->type = HUD;
    }
    return SUCCESS;
}

static int init_maker_sprites(void)
{
    int inits[8] = {init_room_select(), init_start_room(), init_blackscreen(),
        init_icons(), init_display_robots(), init_compass(),
        init_logs(), init_bg()};

    for (int i = 0; i < 8; i++) {
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
        0, 5.0)->method = EASEINOUT;  // lalalallalala
    sfMusic_setLoop(MUSIC->music, sfTrue);
    return SUCCESS;
}

int init_maker_assets(void)
{
    create_window(800, 600, "A-MAZE-D VIEWER!");
    *get_clock() = sfClock_create();
    MAZE->nb_robots = 3;
    MAZE->viewer = 2;
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
