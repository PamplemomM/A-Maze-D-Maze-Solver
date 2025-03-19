/*
** EPITECH PROJECT, 2025
** main
** File description:
** Main file for the A-Maze-d visualizer.
*/

#include "../include/header.h"

int usage_print(void)
{
    FILE *file = fopen("usage.txt", "r");
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

void move_cam(void)
{
    float fact = 1.0;

    if (KEYPRESS(sfKeyLShift))
        fact = 1.5;
    if (KEYPRESS(sfKeyLeft)) {
        make_tween("camlat", &CAM->center.x, CAM->center.x - 50 / CAM->zoom * fact, 1)->method = EASEOUT;
        CAM->angle -= 0.5 * fact;
        make_tween("camrot", &CAM->angle, 0, 1)->method = EASEOUT;
    }
    if (KEYPRESS(sfKeyRight)) {
        make_tween("camlat", &CAM->center.x, CAM->center.x + 50 / CAM->zoom * fact, 1)->method = EASEOUT;
        CAM->angle += 0.5 * fact;
        make_tween("camrot", &CAM->angle, 0, 1)->method = EASEOUT;
    }
    if (KEYPRESS(sfKeyUp)) {
        if (get_tween("camvert") == NULL || TIME - get_tween("camvert")->tstart > 0.1) {
            CAM->angle += diceroll(-10, 10) / 10.0 * fact;
            make_tween("camrot", &CAM->angle, 0, 1)->method = EASEOUT;
        }
        make_tween("camvert", &CAM->center.y, CAM->center.y - 50 / CAM->zoom * fact, 1)->method = EASEOUT;
    }
    if (KEYPRESS(sfKeyDown)) {
        if (get_tween("camvert") == NULL || TIME - get_tween("camvert")->tstart > 0.1) {
            CAM->angle += diceroll(-10, 10) / 10.0 * fact;
            make_tween("camrot", &CAM->angle, 0, 1)->method = EASEOUT;
        }
        make_tween("camvert", &CAM->center.y, CAM->center.y + 50 / CAM->zoom * fact, 1)->method = EASEOUT;
    }
    if (KEYPRESS(sfKeyP)) {
        make_tween("camzoom", &CAM->zoom, MIN(CAM->zoom * (1.2 + (fact - 1) / 2.0), 100), 1)->method = EASEOUT;
    }
    if (KEYPRESS(sfKeyM)) {
        make_tween("camzoom", &CAM->zoom, MAX(CAM->zoom / (1.2 + (fact - 1) / 2.0), 0.1), 1)->method = EASEOUT;
    }
}

void events(void)
{
    sfEvent event;

    move_cam();
    while (sfRenderWindow_pollEvent(WINDOW, &event)) {
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyEscape)
            sfRenderWindow_close(WINDOW);
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(WINDOW);
    }
}

void hue_shift(void)
{
    sprite_t *sprite = *get_spritelist();
    int tmp = 0;
    int i = 0;

    GAME->hue += HUESHIFT;
    if (GAME->hue >= 360)
        GAME->hue -= 360;
    while (sprite != NULL && i < DATA->robotcnt) {
        tmp = strcmp(sprite->name, "P0");
        if (tmp > 0 && tmp < 10) {
            sprite->color = color_from_hue(360 / DATA->robotcnt * i + GAME->hue, 255, 225, 255);
            i++;
        }
        sprite = sprite->next;
    }
}

void update_stuff(void)
{
    update_tweens();
    hue_shift();
    draw_allsprites();
    update_cam();
}

void run(void)
{
    if (init_gamestuff() == ERROR)
        sfRenderWindow_close(WINDOW);
    if (init_assets() == ERROR)
        sfRenderWindow_close(WINDOW);
    while (sfRenderWindow_isOpen(WINDOW)) {
        sfRenderWindow_clear(WINDOW, color_from_hue(0, 75, 0, 255));
        update_stuff();
        events();
        sfRenderWindow_display(WINDOW);
    }
    destroy_assets();
}

int main(int ac, char **av)
{
    if (ac > 1 && strcmp(av[1], "-h") == 0)
        return usage_print();
    if (read_data() == -1)
        return 84;
    srand(time(NULL));
    DATA->robotcnt = diceroll(2, 10);
    run();
    return 0;
}
