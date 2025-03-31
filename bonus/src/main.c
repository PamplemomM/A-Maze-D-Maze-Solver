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
    make_tween(tmp, &robot->sprite->pos.x, room->x * 50, 1.0 / speed / 2.0)->method = EASEOUT;

    tmp[my_strlen(tmp) - 1] = 'y';
    make_tween(tmp, &robot->sprite->pos.y, room->y * 50, 1.0 / speed / 2.0)->method = EASEOUT;

    tmp[my_strlen(tmp) - 1] = 'r';
    robot->sprite->angle += (room->x * 50 - robot->sprite->pos.x) / 10.0 * (robot->sprite->pos.y - room->y * 50 + 50) / 100.0;
    make_tween(tmp, &robot->sprite->angle, 0, 1.0 / speed / 2.2)->method = EASEINOUT;

    tmp[my_strlen(tmp) - 1] = 's';
    robot->sprite->scale.y += abs(room->y * 50 - robot->sprite->pos.y) / 3000.0;
    make_tween(tmp, &robot->sprite->scale.y, 0.2, 1.0 / speed / 2.0)->method = EASEINOUT;

    OMNIFREE(tmp, 1);
    play_sound("move", 70.0 / speed, diceroll(80, 90) / 100.0 + speed / 50.0);
    robot->room = room;
    robot->move_to = NULL;
    return SUCCESS;
}

int move_allrobots_to(room_t *room)
{
    vwr_robot_t *robot = *get_robotlist();

    while (robot != NULL) {
        do_move(robot, room, 3);
        robot = robot->next;
    }
    return SUCCESS;
}

void update_robots_rooms(int id)
{
    vwr_robot_t *robot = *get_robotlist();
    move_t *move = MAZE->moves;

    printf("updating to... %d\n", id);
    while (robot != NULL) {
        robot->move_to = MAZE->start;
        robot = robot->next;
    }
    while (move != NULL && move->id < id) {
        get_robot(move->robot)->move_to = move->dest;
        move = move->next;
    }
    robot = *get_robotlist();
    while (robot != NULL) {
        if (robot->room == robot->move_to)
            robot->move_to = NULL;
        robot = robot->next;
    }
}

void start_sim(float start)
{
    GAME->move_id = start;
    make_tween("id", &GAME->move_id, GAME->nb_moves + 0.2,
        sqrt(GAME->nb_moves - start))->method = EASEINOUT;
    update_robots_rooms((int)start);
}

void move_robots(float speed)
{
    static vwr_robot_t *robot = NULL;
    static int curr_id = 0;
    int diff_id = (int)GAME->move_id - curr_id;

    speed *= 1 + abs(diff_id) / 2.0;
    if (robot == NULL && diff_id == 0)
        return;
    if (robot == NULL && diff_id != 0) {
        robot = *get_robotlist();
        curr_id += diff_id / abs(diff_id);
        printf("move set %d is now in action!\n", curr_id);
        update_robots_rooms(curr_id);
    }
    if (get_timer("mvcooldown") == NULL && robot != NULL) {
        if (robot->move_to) {
            printf("move P%d-%s\n", robot->id, robot->move_to->name);
            do_move(robot, robot->move_to, speed);
            run_timer("mvcooldown", diceroll(5, 10) / 70.0 / speed);
        }
        robot = robot->next;
    }
}

void toggle_gamestate(gamestate_t state)
{
    if (GAME->state == state)
        return;
    GAME->state = state;
    if (state == PLAY) {
        text_jumpscare("UNPAUSED!", 1);
        play_sound("play", 75, diceroll(90, 110) / 100.0);
        start_sim(GAME->move_id);
    }
    if (state == PAUSE) {
        text_jumpscare("PAUSED!", 1);
        play_sound("pause", 75, diceroll(80, 90) / 100.0);
        DESTROY(get_tween("id"), get_tweenlist, free_tween);
    }
    if (state == REWIND) {
        text_jumpscare("REWIND!", 1);
        play_sound("rewind", 75, diceroll(90, 110) / 100.0);
        make_tween("id", &GAME->move_id, 0.0, sqrt(GAME->move_id))->method = EASEOUT;
    }
}

void interact_time(void)
{
    if (GAME->state == REWIND && GAME->move_id <= 0.2)
        DESTROY(get_tween("id"), get_tweenlist, free_tween);
    if (get_tween("id") == NULL)
        toggle_gamestate(PAUSE);
    if (KEYPRESS(sfKeyBackspace) && get_timer("actcooldown") == NULL) {
        run_timer("actcooldown", 0.5);
        if (GAME->move_id <= 1.0) {
            text_jumpscare("too early bro </3", 1);
            return;
        }
        toggle_gamestate(REWIND);
    }
    if (KEYPRESS(sfKeySpace) && get_timer("actcooldown") == NULL) {
        run_timer("actcooldown", 0.2);
        if (GAME->move_id >= GAME->nb_moves) {
            text_jumpscare("its already over bro </3", 1);
            return;
        }
        if (get_tween("id") == NULL)
            toggle_gamestate(PLAY);
        else
            toggle_gamestate(PAUSE);
    }
    if (KEYPRESS(sfKeyAdd) && get_timer("actcooldown") == NULL) {
        run_timer("actcooldown", 0.2);
        if ((int)GAME->move_id < GAME->nb_moves)
            GAME->move_id++;
        DESTROY(get_tween("id"), get_tweenlist, free_tween);
        printf("%d\n", (int)GAME->move_id);
    }
    if (KEYPRESS(sfKeySubtract) && get_timer("actcooldown") == NULL) {
        run_timer("actcooldown", 0.2);
        if ((int)GAME->move_id > 0)
            GAME->move_id--;
        DESTROY(get_tween("id"), get_tweenlist, free_tween);
        printf("%d\n", (int)GAME->move_id);
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

void update_robots(void)
{
    static int prev_id = 0;
    tween_t *tween_id = get_tween("id");
    float length_id = 0.0;
    float speed = 1.0;

    if (tween_id != NULL) {
        length_id = fabs(tween_id->dest - tween_id->start);
        speed = 1 + sin(fabs((*tween_id->value) - tween_id->start) / length_id * M_PI) * sqrt(length_id);
    }
    if ((int)GAME->move_id != prev_id)
        prev_id = (int)GAME->move_id;
    move_robots(speed);
    return;
}

void update_stuff(void)
{
    update_tweens();
    update_timers();
    hue_shift();
    draw_allsprites();
    draw_alltexts();
    update_cam();
    update_robots();
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
