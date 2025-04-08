/*
** EPITECH PROJECT, 2025
** move_robots.c
** File description:
** Functions to make the robots move.
*/

#include "../include/header_viewer.h"

static int do_move_tweens(sprite_t *sprite, room_t *room, float speed)
{
    char *tmp = merge_str(sprite->name, "0");
    float fact = 0.8 / speed;

    if (tmp == NULL)
        return ERROR;
    tmp[my_strlen(tmp) - 1] = 'x';
    make_tween(tmp, &sprite->pos.x, room->x, fact / 1.5)->method = EASEOUT;
    tmp[my_strlen(tmp) - 1] = 'r';
    make_tween(tmp, &sprite->angle, 0, fact / 1.7)->method = EASEINOUT;
    tmp[my_strlen(tmp) - 1] = 'y';
    make_tween(tmp, &sprite->pos.y, room->y, fact / 1.5)->method = EASEOUT;
    tmp[my_strlen(tmp) - 1] = 'w';
    make_tween(tmp, &sprite->scale.x, 0.2, fact / 1.45)->method = EASEINOUT;
    tmp[my_strlen(tmp) - 1] = 'h';
    make_tween(tmp, &sprite->scale.y, 0.2, fact / 1.45)->method = EASEINOUT;
    OMNIFREE(tmp, 1);
    return SUCCESS;
}

static int do_move_math(vwr_robot_t *robot, room_t *room)
{
    sprite_t *sprite = robot->sprite;
    int diffx = room->x - sprite->pos.x;
    int diffy = room->y - sprite->pos.y;
    int diffd = sqrt(pow(diffx, 2) + pow(diffy, 2));
    float traj = atan2f(diffx, fabs(diffy - 80.0)) * 180.0 / M_PI;
    float angle = MAX(MIN(sqrt(abs(diffx)) * ((float)(diffx + 1)
        / (float)(abs(diffx) + 1)) * 1.5, 80), -80);
    float diffa = fabs(traj - angle);
    float squish_factor = MAX(((diffa + 25.0) / 50.0 - 1.0)
        * (diffd / 1000.0) + 1.0, 0.4);

    sprite->angle = angle;
    sprite->scale.x *= squish_factor;
    sprite->scale.y /= squish_factor;
    if (diffy > 0)
        sprite->pos.y += ((sprite->scale.y - 0.2) * 500.0)
            / (fabs(angle) / 20.0 + 1.0);
}

static int do_move(vwr_robot_t *robot, room_t *room, float speed)
{
    do_move_math(robot, room);
    if (do_move_tweens(robot->sprite, room, speed) == ERROR)
        return ERROR;
    play_sound("move", MIN(40.0 / speed * CAM->zoom, 70.0),
        diceroll(80, 90) / 100.0 + speed / 50.0);
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

static int count_remaining_moves(void)
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

static int move_next_robot(vwr_robot_t **robot, int moves_cnt, float speed)
{
    while (*robot != NULL && (*robot)->move_to == NULL)
        *robot = (*robot)->next;
    if (*robot == NULL)
        return SUCCESS;
    if (add_logs_move(*robot, (*robot)->move_to) == ERROR)
        return ERROR;
    do_move(*robot, (*robot)->move_to, speed);
    run_timer("move_cdwn", (diceroll(5, 10) / 40.0 / speed)
        / (1 + moves_cnt / 5.0));
    *robot = (*robot)->next;
    return SUCCESS;
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
        update_robots_rooms(curr_id);
        update_progbuff(curr_id);
        moves_cnt = count_remaining_moves();
    }
    if (get_timer("move_cdwn") == NULL && robot != NULL)
        return move_next_robot(&robot, moves_cnt, speed);
    return SUCCESS;
}
