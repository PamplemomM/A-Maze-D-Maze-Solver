/*
** EPITECH PROJECT, 2025
** main.c
** File description:
** Main file for the A-Maze-d viewer.
*/

#include "../include/header_viewer.h"

static int usage_print(void)
{
    FILE *file = fopen("assets/usage.txt", "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t read = 0;

    if (file == NULL)
        return ERROR;
    while (read != -1) {
        if (read != 0)
            write(1, line, read);
        read = getline(&line, &len, file);
    }
    free(line);
    fclose(file);
    return SUCCESS;
}

void events(void)
{
    sfEvent event;

    cam_move_keys();
    interact_sim();
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

int update_stuff(void)
{
    update_tweens();
    update_timers();
    update_music();
    if (update_robots() == ERROR)
        return ERROR;
    if (TIME > 4.5)
        update_compass();
    hue_shift();
    draw_allsprites(NONE);
    draw_allsprites(TUNNEL);
    draw_allsprites(ROOM);
    draw_robots();
    draw_alltexts(NONE);
    update_cam();
    draw_allsprites(HUD);
    draw_alltexts(HUD);
    if (sfRenderWindow_hasFocus(WINDOW))
        events();
    return SUCCESS;
}

void run(void)
{
    while (sfRenderWindow_isOpen(WINDOW)) {
        sfRenderWindow_clear(WINDOW, sfBlack);
        if (update_stuff() == ERROR) {
            sfRenderWindow_close(WINDOW);
            return;
        }
        sfRenderWindow_display(WINDOW);
    }
}

int start_simulator(void)
{
    int retval = SUCCESS;

    if (read_maze() == ERROR)
        return ERROR;
    if (init_gamestuff() != ERROR && init_assets() != ERROR)
        run();
    else
        retval = ERROR;
    destroy_assets();
    free_maze(&MAZE);
    return retval;
}

// the CSFML itself leaks 226,396 bytes of memory on its own
// music and sounds can add to the memory leaks as well
int main(int ac, char **av)
{
    srand(time(NULL));
    if (ac == 2 && strcmp(av[1], "-m") == 0)
        return start_maker();
    else if (ac != 1)
        return usage_print();
    return start_simulator();
}
