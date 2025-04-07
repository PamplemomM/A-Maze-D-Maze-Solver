/*
** EPITECH PROJECT, 2025
** main_maker.c
** File description:
** Main file for the A-Maze-d script maker.
*/

#include "../include/header_viewer.h"

void events_maker(void)
{
    sfEvent event;

    //cam_move_keys();
    //interact_sim();
    while (sfRenderWindow_pollEvent(WINDOW, &event)) {
        //if (event.type == sfEvtMouseMoved)
        //    cam_move_mouse(event.mouseMove);
        //if (event.type == sfEvtMouseWheelScrolled)
        //    cam_zoom_mouse(event.mouseWheelScroll);
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyEscape)
            sfRenderWindow_close(WINDOW);
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(WINDOW);
    }
}

void update_stuff_maker(void)
{
    update_tweens();
    update_timers();
    //update_robots();
    //hue_shift();
    draw_allsprites(NONE);
    draw_allsprites(ROOM);
    //draw_robots();
    draw_alltexts(NONE);
    update_cam();
    events_maker();
}

void run_maker(void)
{
    while (sfRenderWindow_isOpen(WINDOW)) {
        sfRenderWindow_clear(WINDOW, color_from_hue(0, 75, 0, 255));
        update_stuff_maker();
        sfRenderWindow_display(WINDOW);
    }
}

int init_new_maze(void)
{
    maze_t *maze = malloc(sizeof(maze_t));

    if (maze == NULL)
        return ERROR;
    //blablablabla
    OMNIFREE(maze, 1);
    return ERROR;
}

int start_maker(void)
{
    int retval = SUCCESS;

    if (init_new_maze() == ERROR)
        return ERROR;
    if (init_gamestuff() != ERROR && init_assets() != ERROR)
        run_maker();
    else
        retval = ERROR;
    destroy_assets();
    free_maze(&MAZE);
    return retval;
}
