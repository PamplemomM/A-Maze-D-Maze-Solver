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

void cam_move_mouse(sfMouseMoveEvent mouse)
{
    static sfMouseMoveEvent mouseold = {sfEvtMouseMoved, 0, 0};

    if (MOUSEPRESS(sfMouseLeft) && (mouseold.x != 0 && mouseold.y != 0)) {
        DESTROY(get_tween("camvert"), get_tweenlist, free_tween);
        DESTROY(get_tween("camlat"), get_tweenlist, free_tween);
        CAM->center.x += (mouseold.x - mouse.x) / CAM->zoom;
        CAM->center.y += (mouseold.y - mouse.y) / CAM->zoom;
    }
    mouseold = mouse;
}

void cam_zoom_mouse(sfMouseWheelScrollEvent mouse)
{
    tween_t *tween = get_tween("camzoom");
    float tmp = CAM->zoom;

    if (tween != NULL)
        tmp = tween->dest;
    tween = make_tween("camzoom", &CAM->zoom, tmp, 0.5);
    tween->method = EASEOUT;
    tmp += mouse.delta * tmp / 10;
    if (tmp > 100)
        tmp = 100;
    else if (tmp < 0.1)
        tmp = 0.1;
    tween->dest = tmp;
}

void cam_move_keys(void)
{
    float fact = 1.0;

    if (KEYPRESS(sfKeyLShift))
        fact = 1.5;
    if (KEYPRESS(sfKeyUp))
        make_tween("camvert", &CAM->center.y, CAM->center.y - 50
            / CAM->zoom * pow(fact, 2), 0.8)->method = EASEOUT;
    else if (KEYPRESS(sfKeyDown))
        make_tween("camvert", &CAM->center.y, CAM->center.y + 50
            / CAM->zoom * pow(fact, 2), 0.8)->method = EASEOUT;
    if (KEYPRESS(sfKeyLeft))
        make_tween("camlat", &CAM->center.x, CAM->center.x - 50
            / CAM->zoom * pow(fact, 2), 0.8)->method = EASEOUT;
    else if (KEYPRESS(sfKeyRight))
        make_tween("camlat", &CAM->center.x, CAM->center.x + 50
            / CAM->zoom * pow(fact, 2), 0.8)->method = EASEOUT;
    if (KEYPRESS(sfKeyC))
        make_tween("camzoom", &CAM->zoom, MIN(CAM->zoom
            * (1.2 + (fact - 1) / 2.0), 100), 1)->method = EASEOUT;
    else if (KEYPRESS(sfKeyX))
        make_tween("camzoom", &CAM->zoom, MAX(CAM->zoom
            / (1.2 + (fact - 1) / 2.0), 0.1), 1)->method = EASEOUT;
}

sprite_t *get_room_sprite(room_t *room) // possibly useless
{
    sprite_t *sprite = NULL;
    char *name = merge_str("room_", room->name);

    if (name == NULL)
        return OMNIFREE(name, 1);
    sprite = get_sprite(name);
    OMNIFREE(name, 1);
    return sprite;
}

int do_move_tweens(sprite_t *sprite, room_t *room, float speed)
{
    char *tmp = merge_str(sprite->name, "0");

    if (tmp == NULL)
        return ERROR;
    tmp[my_strlen(tmp) - 1] = 'x'; // x axis
    make_tween(tmp, &sprite->pos.x, room->x, 0.8 / speed / 1.5)->method = EASEOUT;
    tmp[my_strlen(tmp) - 1] = 'r'; // rotation
    make_tween(tmp, &sprite->angle, 0, 0.8 / speed / 1.7)->method = EASEINOUT;
    tmp[my_strlen(tmp) - 1] = 'y'; // y axis
    make_tween(tmp, &sprite->pos.y, room->y, 0.8 / speed / 1.5)->method = EASEOUT;
    tmp[my_strlen(tmp) - 1] = 'w'; // width
    make_tween(tmp, &sprite->scale.x, 0.2, 0.8 / speed / 1.45)->method = EASEINOUT;
    tmp[my_strlen(tmp) - 1] = 'h'; // height
    make_tween(tmp, &sprite->scale.y, 0.2, 0.8 / speed / 1.45)->method = EASEINOUT;
    OMNIFREE(tmp, 1);
    return SUCCESS;
}

int do_move(vwr_robot_t *robot, room_t *room, float speed)
{
    sprite_t *sprite = robot->sprite;
    int diffx = room->x - sprite->pos.x;
    int diffy = room->y - sprite->pos.y;
    int diffd = sqrt(pow(diffx, 2) + pow(diffy, 2));
    float traj = atan2f(diffx, fabs(diffy - 80.0)) * 180.0 / M_PI;
    float angle = MAX(MIN(sqrt(abs(diffx)) * ((float)(diffx + 1) / (float)(abs(diffx) + 1)) * 1.5, 80), -80);
    float diffa = fabs(traj - angle);
    float squish_factor = ((diffa + 25.0) / 50.0 - 1.0) * (diffd / 1000.0) + 1.0;

    sprite->angle = angle;
    sprite->pos.y += pow(MAX(diffy / 60.0, 0), 2) * squish_factor;
    sprite->scale.x *= squish_factor;
    sprite->scale.y /= squish_factor;
    if (do_move_tweens(robot->sprite, room, speed) == ERROR)
        return ERROR;
    play_sound("move", 70.0 / speed, diceroll(80, 90) / 100.0 + speed / 50.0);
    run_timer("moving", 0.8 / speed / 1.5);
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

// IF YOU SEE THIS, YOU'RE AMNESIC
void update_robots_rooms(int id)
{
    vwr_robot_t *robot = *get_robotlist();
    move_t *move = MAZE->moves;

    //printf("updating to... %d\n", id);
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

void update_progbar(void)
{
    sprite_t *prog = get_sprite("barprog");

    make_tween("barprog", &prog->pos.x, (int)GAME->move_id / (float)GAME->nb_moves * 500.0 + 150, 0.2)->method = EASEOUT;
    prog->scale.x = MIN(prog->scale.x + 3, 15);
    prog->scale.y = MAX(prog->scale.y - 3, 30);
    make_tween("barprogw", &prog->scale.x, 3, 0.2)->method = EASEINOUT;
    make_tween("barprogh", &prog->scale.y, 36, 0.2)->method = EASEINOUT;
    play_sound("progbar", prog->scale.x * 2, 0.7 + prog->scale.x / 50.0);
}

void update_progbuff(int id)
{
    sprite_t *buff = get_sprite("barbuff");

    make_tween("barbuff", &buff->scale.x, id / (float)GAME->nb_moves * 500.0, 2.0)->method = EASEOUT;
}

int count_remaining_moves(void)
{
    vwr_robot_t *robot = *get_robotlist();
    int cnt = 0;

    while (robot != NULL) {
        if (robot->move_to)
            cnt++;
        robot = robot->next;
    }
    return cnt;
}

int move_robots(float speed)
{
    static vwr_robot_t *robot = NULL;
    static int moves_cnt = 0;
    static int curr_id = 0;
    int diff_id = (int)GAME->move_id - curr_id;

    speed *= 1 + abs(diff_id) / 2.0;
    if (robot == NULL && diff_id == 0)
        return SUCCESS;
    if (robot == NULL && diff_id != 0) {
        robot = *get_robotlist();
        curr_id += diff_id / abs(diff_id);
        if (add_to_logs("\n") == ERROR)
            return ERROR;
        //printf("move set %d is now in action!\n", curr_id);
        update_robots_rooms(curr_id);
        update_progbuff(curr_id);
        moves_cnt = count_remaining_moves();
    }
    if (get_timer("mvcooldown") == NULL && robot != NULL) {
        while (robot != NULL && robot->move_to == NULL)
            robot = robot->next;
        if (robot == NULL)
            return SUCCESS;
        if (add_logs_move(robot, robot->move_to) == ERROR)
            return ERROR;
        //printf("move P%d-%s\n", robot->id, robot->move_to->name);
        do_move(robot, robot->move_to, speed);
        run_timer("mvcooldown", (diceroll(5, 10) / 40.0 / speed) / (1 + moves_cnt / 5.0));
        robot = robot->next;
    }
    return SUCCESS;
}

void toggle_gamestate(gamestate_t state)
{
    if (GAME->state == state)
        return;
    if (state == PLAY) {
        if (GAME->move_id >= GAME->nb_moves) {
            text_jumpscare("its already over bro </3", 1);
            return;
        }
        GAME->state = state;
        text_jumpscare("UNPAUSED!", 1);
        play_sound("play", 75, diceroll(90, 110) / 100.0);
        start_sim(GAME->move_id);
    }
    if (state == PAUSE) {
        GAME->state = state;
        text_jumpscare("PAUSED!", 1);
        play_sound("pause", 75, diceroll(80, 90) / 100.0);
        DESTROY(get_tween("id"), get_tweenlist, free_tween);
    }
    if (state == REWIND) {
        if (GAME->move_id <= 1.0) {
            text_jumpscare("too early bro </3", 1);
            return;
        }
        GAME->state = state;
        text_jumpscare("REWIND!", 1);
        play_sound("rewind", 75, diceroll(90, 110) / 100.0);
        make_tween("id", &GAME->move_id, 0.0, sqrt(GAME->move_id))->method = EASEOUT;
    }
    return;
}

void interact_sim(void)
{
    if (GAME->state == REWIND && GAME->move_id <= 0.2)
        DESTROY(get_tween("id"), get_tweenlist, free_tween);
    if (get_tween("id") == NULL && get_timer("moving") == NULL)
        toggle_gamestate(PAUSE);
    if (KEYPRESS(sfKeyBackspace) && get_timer("actcooldown") == NULL) {
        run_timer("actcooldown", 0.5);
        toggle_gamestate(REWIND);
    }
    if (KEYPRESS(sfKeySpace) && get_timer("actcooldown") == NULL) {
        run_timer("actcooldown", 0.2);
        if (GAME->state == PAUSE)
            toggle_gamestate(PLAY);
        else
            toggle_gamestate(PAUSE);
    }
    if ((KEYPRESS(sfKeyAdd) || KEYPRESS(sfKeyN)) && get_timer("actcooldown") == NULL) {
        run_timer("actcooldown", 0.2);
        if ((int)GAME->move_id < GAME->nb_moves)
            GAME->move_id++;
        else if (GAME->state == PAUSE)
            text_jumpscare("no more moves blud </3", 1);
        toggle_gamestate(PAUSE);
        DESTROY(get_tween("id"), get_tweenlist, free_tween);
    } else if ((KEYPRESS(sfKeySubtract) || KEYPRESS(sfKeyB)) && get_timer("actcooldown") == NULL) {
        run_timer("actcooldown", 0.2);
        if ((int)GAME->move_id > 0)
            GAME->move_id--;
        else if (GAME->state == PAUSE)
            text_jumpscare("wrong way dawg </3", 1);
        toggle_gamestate(PAUSE);
        DESTROY(get_tween("id"), get_tweenlist, free_tween);
    }
    if (KEYPRESS(sfKeyTab) && get_timer("logs_cdwn") == NULL) {
        run_timer("logs_cdwn", 0.5);
        if (GAME->logs) {
            make_tween("camlog", &CAM->offset.x, 0, 1.0)->method = EASEOUT;
            make_tween("camzoom", &CAM->zoom, CAM->zoom / 0.7, 1.0)->method = EASEOUT;
            make_tween("logs", &get_sprite("logs")->pos.x, -250, 1.0)->method = EASEOUT;
            make_tween("logstitle", &get_text("logstitle")->pos.x, -170, 1.0)->method = EASEOUT;
            make_tween("logstxt", &get_text("logstxt")->pos.x, -243, 1.0)->method = EASEOUT;
            play_sound("logs_toggle", 75, diceroll(80, 90) / 100.0);
            GAME->logs = 0;
        } else {
            make_tween("camlog", &CAM->offset.x, -125, 1.0)->method = EASEOUT;
            make_tween("camzoom", &CAM->zoom, CAM->zoom * 0.7, 1.0)->method = EASEOUT;
            make_tween("logs", &get_sprite("logs")->pos.x, -125, 1.0)->method = EASEOUT;
            make_tween("logstitle", &get_text("logstitle")->pos.x, -45, 1.0)->method = EASEOUT;
            make_tween("logstxt", &get_text("logstxt")->pos.x, -118, 1.0)->method = EASEOUT;
            play_sound("logs_toggle", 75, diceroll(90, 110) / 100.0);
            GAME->logs = 1;
        }
    }
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

void hue_shift(void)
{
    vwr_robot_t *robot = *get_robotlist();

    GAME->hue += HUESHIFT;
    if (GAME->hue >= 360)
        GAME->hue -= 360;
    while (robot != NULL) {
        robot->sprite->color =
            color_from_hue(360 / MAZE->nb_robots * robot->id + GAME->hue,
            255, 240, 255);
        robot = robot->next;
    }
}

int update_robots(void)
{
    static int prev_id = 0;
    tween_t *tween_id = get_tween("id");
    float length_id = 0.0;
    float speed = 1.0;

    if (tween_id != NULL) {
        length_id = fabs(tween_id->dest - tween_id->start);
        speed = 1 + sin(fabs((*tween_id->value) - tween_id->start) / length_id * M_PI) * sqrt(length_id);
    }
    if ((int)GAME->move_id != prev_id) {
        prev_id = (int)GAME->move_id;
        update_progbar();
    }
    return move_robots(speed);
}

void reorder_robots(void)
{
    vwr_robot_t **list = GAME->robots_order;
    vwr_robot_t *tmp = NULL;

    for (int i = 1; list[i] != NULL; i++) {
        if (list[i - 1]->sprite->pos.y > list[i]->sprite->pos.y) {
            tmp = list[i];
            list[i] = list[i - 1];
            list[i - 1] = tmp;
            reorder_robots();
        }
    }
}

void draw_robots(void)
{
    vwr_robot_t **list = GAME->robots_order;

    if (list == NULL)
        return;
    if (get_timer("moving") != NULL)
        reorder_robots();
    for (int i = 0; list[i] != NULL; i++)
        draw_sprite(list[i]->sprite);
}

void update_compass_arrow(void)
{
    sprite_t *arrow = get_sprite("cmpa");
    sfVector2i center = {(GAME->bounds.left + GAME->bounds.width)
        / 2.0, (GAME->bounds.top + GAME->bounds.height) / 2.0};
    int diffx = center.x - CAM->center.x;
    int diffy = center.y - CAM->center.y;
    int diffd = sqrt(pow(diffx, 2) + pow(diffy, 2)) - 25;
    float traj = atan2f(diffx, -diffy) * 180.0 / M_PI;

    arrow->angle = traj;
    arrow->rect.left = (arrow->rect.left + 45) % 180;
}

void update_compass(void)
{
    sprite_t *arrow = get_sprite("cmpa");
    sprite_t *pivot = get_sprite("cmpp");
    float fact = 0.5 + cos(TIME * 2.0) * 0.2;
    sfIntRect bounds = GAME->bounds;

    arrow->scale = (sfVector2f){CAM->zoom, CAM->zoom};
    pivot->scale = (sfVector2f){fact * CAM->zoom, fact * CAM->zoom};
    if (CAM->center.x > bounds.left - 100 && CAM->center.y > bounds.top - 100
        && CAM->center.x < bounds.left + bounds.width + 100
        && CAM->center.y < bounds.top + bounds.height + 100) {
        arrow->color.a /= 1.2;
        pivot->color.a /= 1.2;
    } else {
        arrow->color.a = 255 + (arrow->color.a - 255) / 1.05;
        pivot->color.a = fact * 200;
    }
    if (get_timer("cmpcooldown") == NULL) {
        update_compass_arrow();
        run_timer("cmpcooldown", 0.1);
    }
}

int update_stuff(void)
{
    update_tweens();
    update_timers();
    if (update_robots() == ERROR)
        return ERROR;
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
    if (ac == 2 && strcmp(av[1], "-c") == 0)
        return start_maker();
    else if (ac != 1)
        return usage_print();
    return start_simulator();
}
