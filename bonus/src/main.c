/*
** EPITECH PROJECT, 2025
** main.c
** File description:
** Main file for the A-Maze-d viewer.
*/

#include "../include/header_viewer.h"

int usage_print(void)
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

int do_move(vwr_robot_t *robot, room_t *room, float speed)
{
    char *tmp = merge_str(robot->sprite->name, "x");

    if (tmp == NULL)
        return ERROR;
    make_tween(tmp, &robot->sprite->pos.x, room->x * 50, 1.0 / speed)->method = EASEOUT;
    tmp[my_strlen(tmp) - 1] = 'y';
    make_tween(tmp, &robot->sprite->pos.y, room->y * 50, 1.0 / speed)->method = EASEOUT;
    OMNIFREE(tmp, 1);
    play_sound("move", 50.0 + 50.0 / speed, 0.8 * speed);
    make_tween("camtilt", &CAM->angle, diceroll(-10, 10) / 20.0 * speed, 2.0 / speed)->method = EASEOUT;
    robot->room = room;
    return SUCCESS;
}

void start_sim(void)
{
    static float id = 0.0;
    vwr_robot_t *robot = *get_robotlist();
    int tmp = 0;

    make_tween("id", &id, GAME->nb_moves + 0.1, GAME->nb_moves / 2.0)->method = EASEINOUT;
    while (robot != NULL) {
        do_move(robot, MAZE->start, 10);
        robot = robot->next;
    }
}

int move_robots(void) // called as long as 'get_tween("id") != NULL'
{
    static move_t *move = NULL;
    float curid = *(get_tween("id")->value);
    float speed = 1 + sin(curid / GAME->nb_moves * M_PI) * GAME->nb_moves / 7.0;

    if (move == NULL)
        move = MAZE->moves;
    if (get_timer("mvcooldown") == NULL && move->id <= curid) {
        if (do_move(get_robot(move->robot), move->dest, speed) == ERROR)
            return ERROR;
        move = move->next;
        run_timer("mvcooldown", diceroll(5, 15) / 10.0 / speed);
    }
    if (move == NULL)
        DESTROY(get_tween("id"), get_tweenlist, free_tween); // end the loop
    return SUCCESS;
}

void interact_time(void)
{
    if (KEYPRESS(sfKeyBackspace) && get_timer("startcooldown") == NULL) {
        run_timer("startcooldown", 1.0);
        start_sim();
    }
}

void events(void)
{
    sfEvent event;

    move_cam();
    interact_time();
    while (sfRenderWindow_pollEvent(WINDOW, &event)) {
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyEscape)
            sfRenderWindow_close(WINDOW);
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(WINDOW);
    }
}

void hue_shift(void)
{
    vwr_robot_t *robot = *get_robotlist();

    GAME->hue += HUESHIFT;
    if (GAME->hue >= 360)
        GAME->hue -= 360;
    while (robot != NULL) {
        robot->sprite->color = color_from_hue(360 / MAZE->nb_robots * robot->id + GAME->hue, 255, 225, 255); // REDO THIS
        robot = robot->next;
    }
}

void update_stuff(void)
{
    update_tweens();
    update_timers();
    hue_shift();
    draw_allsprites();
    update_cam();
    if (get_tween("id") != NULL)
        move_robots();
}

void run(void)
{
    while (sfRenderWindow_isOpen(WINDOW)) {
        sfRenderWindow_clear(WINDOW, color_from_hue(0, 75, 0, 255));
        update_stuff();
        events();
        sfRenderWindow_display(WINDOW);
    }
}

void start(void)
{
    if (init_gamestuff() != ERROR && init_assets() != ERROR)
        run();
    destroy_assets();
}

// the CSFML itself leaks 226,396 bytes of memory on its own
// music can add to the memory leaks as well
int main(int ac, char **av)
{
    if (ac != 1)
        return usage_print();
    if (read_maze() == ERROR)
        return ERROR;
    srand(time(NULL));
    //MAZE->nb_robots = diceroll(2, 7); // tmp
    start();
    free_maze(&MAZE);
    return SUCCESS;
}
