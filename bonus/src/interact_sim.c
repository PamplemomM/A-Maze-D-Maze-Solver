/*
** EPITECH PROJECT, 2025
** interact_sim.c
** File description:
** Functions to interact with the game simulation.
*/

#include "../include/header_viewer.h"

void start_sim(float start)
{
    GAME->move_id = start;
    make_tween("id", &GAME->move_id, GAME->nb_moves + 0.2,
        sqrt(GAME->nb_moves - start))->method = EASEINOUT;
    update_robots_rooms((int)start);
}

static void interact_sim_state(void)
{
    if (KEYPRESS(sfKeyBackspace) && get_timer("rewind_cdwn") == NULL) {
        run_timer("rewind_cdwn", 0.5);
        toggle_gamestate(REWIND);
    }
    if (KEYPRESS(sfKeySpace) && get_timer("play_cdwn") == NULL) {
        run_timer("play_cdwn", 0.2);
        if (GAME->state == PAUSE)
            toggle_gamestate(PLAY);
        else
            toggle_gamestate(PAUSE);
    }
}

static void interact_sim_iterate(void)
{
    if ((KEYPRESS(sfKeyAdd) || KEYPRESS(sfKeyN))
        && get_timer("iterup_cdwn") == NULL) {
        run_timer("iterup_cdwn", 0.2);
        if ((int)GAME->move_id >= GAME->nb_moves && GAME->state == PAUSE)
            text_jumpscare("no more moves blud </3", 1);
        if ((int)GAME->move_id < GAME->nb_moves)
            GAME->move_id++;
        toggle_gamestate(PAUSE);
        DESTROY(get_tween("id"), get_tweenlist, free_tween);
    }
    if ((KEYPRESS(sfKeySubtract) || KEYPRESS(sfKeyB))
        && get_timer("iterdown_cdwn") == NULL) {
        run_timer("iterdown_cdwn", 0.2);
        if ((int)GAME->move_id <= 0 && GAME->state == PAUSE)
            text_jumpscare("wrong way dawg </3", 1);
        if ((int)GAME->move_id > 0)
            GAME->move_id--;
        toggle_gamestate(PAUSE);
        DESTROY(get_tween("id"), get_tweenlist, free_tween);
    }
}

static void interact_sim_logs_on(void)
{
    make_tween("camlog", &CAM->offset.x, -125, 1.0)->method = EASEOUT;
    make_tween("camzoom", &CAM->zoom,
        CAM->zoom * 0.7, 1.0)->method = EASEOUT;
    make_tween("logs", &get_sprite("logs")->pos.x,
        -125, 1.0)->method = EASEOUT;
    make_tween("logstitle", &get_text("logstitle")->pos.x,
        -45, 1.0)->method = EASEOUT;
    make_tween("logstxt", &get_text("logstxt")->pos.x,
        -118, 1.0)->method = EASEOUT;
    play_sound("logs_toggle", 75, diceroll(90, 110) / 100.0);
    GAME->logs = 1;
}

static void interact_sim_logs_off(void)
{
    make_tween("camlog", &CAM->offset.x, 0, 1.0)->method = EASEOUT;
    make_tween("camzoom", &CAM->zoom,
        CAM->zoom / 0.7, 1.0)->method = EASEOUT;
    make_tween("logs", &get_sprite("logs")->pos.x,
        -250, 1.0)->method = EASEOUT;
    make_tween("logstitle", &get_text("logstitle")->pos.x,
        -170, 1.0)->method = EASEOUT;
    make_tween("logstxt", &get_text("logstxt")->pos.x,
        -243, 1.0)->method = EASEOUT;
    play_sound("logs_toggle", 75, diceroll(80, 90) / 100.0);
    GAME->logs = 0;
}

void interact_sim_logs(void)
{
    if (KEYPRESS(sfKeyTab) && get_timer("logs_cdwn") == NULL) {
        run_timer("logs_cdwn", 0.5);
        if (GAME->logs)
            interact_sim_logs_off();
        else
            interact_sim_logs_on();
    }
}

void interact_sim(void)
{
    interact_sim_state();
    interact_sim_iterate();
    interact_sim_logs();
}
