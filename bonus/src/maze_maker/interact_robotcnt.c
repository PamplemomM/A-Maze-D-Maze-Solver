/*
** EPITECH PROJECT, 2025
** interact_robotcnt.c
** File description:
** Functions to interact with the number of robots.
*/

#include "../../include/header_viewer.h"

int update_robot_display(void)
{
    vwr_robot_t *list = *get_robotlist();
    float pos = 0;

    while (list != NULL) {
        if (GAME->logs)
            pos = 750;
        else
            pos = 750 - ((list->id - 1) / ((float)MAZE->nb_robots)) * 100.0;
        make_tween(list->sprite->name, &list->sprite->pos.x,
            pos, 0.5)->method = EASEOUT;
        list = list->next;
    }
    return SUCCESS;
}

int update_robot_counter(int hold)
{
    text_t *counter = get_text("nb_robots");
    char *nb_robots = int_to_str(MAZE->nb_robots);

    if (nb_robots == NULL)
        return ERROR;
    OMNIFREE(counter->str, 1);
    counter->str = nb_robots;
    sfText_setString(counter->text, counter->str);
    counter->pos.x = 765 - digitcount(MAZE->nb_robots) * 22;
    counter->scale = (sfVector2f){0.9, 0.9};
    make_tween("cntr_scalex", &counter->scale.x, 1.0, 0.5)->method = EASEOUT;
    make_tween("cntr_scaley", &counter->scale.y, 1.0, 0.5)->method = EASEOUT;
    play_sound("counter_iterate", 60 / ((abs(hold) + 1) / 100.0),
        MAX(MIN(1.0 + (hold / 100.0), 8.0), 0.5));
    return SUCCESS;
}

static int interact_nb_robots_limit(void)
{
    play_sound("counter_limit", 70, 1.0);
    return SUCCESS;
}

static int make_display_robot(void)
{
    vwr_robot_t *robot = make_robot(MAZE->nb_robots);

    if (robot == NULL)
        return ERROR;
    robot->sprite->type = HUD;
    robot->sprite->pos = robot->next->sprite->pos;
    robot->sprite->rect = (sfIntRect){0, 0, 175, 356};
    return SUCCESS;
}

static int destroy_display_robot(void)
{
    vwr_robot_t *robot = *get_robotlist();

    robot->next->sprite->pos = robot->sprite->pos;
    DESTROY(get_tween(robot->sprite->name), get_tweenlist, free_tween);
    DESTROY(robot, get_robotlist, free_robot);
    return SUCCESS;
}

static int interact_nb_robots_up(int *hold)
{
    run_timer("robup_cdwn", 0.1 / MAX(*hold / 10.0, 1.0));
    if (MAZE->nb_robots >= 999) {
        *hold = 0;
        return interact_nb_robots_limit();
    }
    MAZE->nb_robots++;
    (*hold)++;
    if (make_display_robot() == ERROR)
        return ERROR;
    update_robot_counter(*hold);
    return update_robot_display();
}

static int interact_nb_robots_down(int *hold)
{
    run_timer("robdown_cdwn", 0.1 / MAX(*hold / 10.0, 1.0));
    if (MAZE->nb_robots <= 1) {
        *hold = 0;
        return interact_nb_robots_limit();
    }
    MAZE->nb_robots--;
    (*hold)++;
    destroy_display_robot();
    update_robot_counter(-(*hold));
    return update_robot_display();
}

int interact_nb_robots(void)
{
    static int hold = 0;

    if (GAME->logs)
        return SUCCESS;
    if ((KEYPRESS(sfKeyAdd) || KEYPRESS(sfKeyN))
        && get_timer("robup_cdwn") == NULL) {
        return interact_nb_robots_up(&hold);
    } else if ((KEYPRESS(sfKeySubtract) || KEYPRESS(sfKeyB))
        && get_timer("robdown_cdwn") == NULL) {
        return interact_nb_robots_down(&hold);
    }
    if (get_timer("robup_cdwn") == NULL && get_timer("robdown_cdwn") == NULL)
        hold = 0;
    return SUCCESS;
}
