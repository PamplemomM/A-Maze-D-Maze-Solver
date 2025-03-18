/*
** EPITECH PROJECT, 2025
** main
** File description:
** Main file for the A-Maze-d visualizer.
*/

#include "../include/header.h"

void usage_print(void)
{
    FILE *file = fopen("usage.txt", "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t read = 0;

    if (file == NULL)
        return;
    while (read != -1) {
        if (read != 0)
            write(1, line, read);
        read = getline(&line, &len, file);
    }
    free(line);
    fclose(file);
}

void events(void)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(WINDOW, &event)) {
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyEscape)
            sfRenderWindow_close(WINDOW);
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(WINDOW);
    }
}

void update_stuff(void)
{
    draw_allsprites();
}

void run(void)
{
    if (init_gamestuff() == NULL)
        sfRenderWindow_close(WINDOW);
    if (init_assets() == NULL)
        sfRenderWindow_close(WINDOW);
    while (sfRenderWindow_isOpen(WINDOW)) {
        sfRenderWindow_clear(WINDOW, color_from_hue(0, 75, 0));
        update_stuff();
        events();
        sfRenderWindow_display(WINDOW);
    }
    destroy_assets();
}

int read_data(void)
{
    DATA = malloc(sizeof(data_t));
    if (DATA == NULL)
        return -1;
    DATA->robotcnt = 3;
    DATA->rooms = NULL;
    DATA->moves = NULL;
    return 0;
}

int main(int ac, char **av)
{
    if (ac > 1 && strcmp(av[1], "-h") == 0) {
        usage_print();
        return 0;
    }
    if (read_data() == -1)
        return 84;
    srand(time(NULL));
    DATA->robotcnt = diceroll(2, 10);
    run();
    return 0;
}
