/*
** EPITECH PROJECT, 2025
** main_maker.c
** File description:
** Main file for the A-Maze-d script maker.
*/

#include "../../include/header_viewer.h"

int events_maker(void)
{
    sfEvent event;

    cam_move_keys();
    track_room_select();
    interact_maker();
    interact_sim_logs();
    while (sfRenderWindow_pollEvent(WINDOW, &event)) {
        if (event.type == sfEvtMouseMoved)
            cam_move_mouse(event.mouseMove);
        if (event.type == sfEvtMouseWheelScrolled)
            cam_zoom_mouse(event.mouseWheelScroll);
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyEscape)
            sfRenderWindow_close(WINDOW);
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(WINDOW);
    }
}

int update_stuff_maker(void)
{
    update_tweens();
    update_timers();
    update_music();
    update_rooms();
    update_room_select();
    if (TIME > 4.5)
        update_compass();
    hue_shift();
    update_cam();
    draw_allsprites(NONE);
    draw_allsprites(TUNNEL);
    draw_allsprites(ROOM);
    draw_alltexts(NONE);
    draw_allsprites(HUD);
    draw_alltexts(HUD);
    if (sfRenderWindow_hasFocus(WINDOW))
        events_maker();
    return SUCCESS;
}

void run_maker(void)
{
    while (sfRenderWindow_isOpen(WINDOW)) {
        sfRenderWindow_clear(WINDOW, sfBlack);
        if (update_stuff_maker() == ERROR) {
            sfRenderWindow_close(WINDOW);
            return;
        }
        sfRenderWindow_display(WINDOW);
    }
}

int start_maker(void)
{
    int retval = SUCCESS;

    if (init_new_maze() == ERROR)
        return ERROR;
    if (init_gamestuff() != ERROR && init_maker_assets() != ERROR)
        run_maker();
    else
        retval = ERROR;
    destroy_assets();
    free_maze(&MAZE);
    return retval;
}
