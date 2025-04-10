/*
** EPITECH PROJECT, 2025
** toggle_gamestates.c
** File description:
** Functions to toggle gamestates.
*/

#include "../include/header_viewer.h"

static void toggle_gamestate_playpause(gamestate_t state)
{
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
}

static void toggle_gamestate_rewind(gamestate_t state)
{
    if (state == REWIND) {
        if (GAME->move_id <= 1.0) {
            text_jumpscare("too early bro </3", 1);
            return;
        }
        GAME->state = state;
        text_jumpscare("REWIND!", 1);
        play_sound("rewind", 75, diceroll(90, 110) / 100.0);
        make_tween("id", &GAME->move_id, 0.0,
            sqrt(GAME->move_id))->method = EASEOUT;
    }
}

static void toggle_gamestate_maker_effect(int def)
{
    play_sound("switch", diceroll(30, 50), (diceroll(100, 110) - def * 20)
        / 100.0);
    get_sprite("icon")->angle += 5;
    make_tween("icon_tilt", &get_sprite("icon")->angle,
        0.0, 0.5)->method = EASEOUT;
}

static void toggle_gamestate_maker(gamestate_t state)
{
    if (state == MKR_ROOM || state == MKR_NONE) {
        if (GAME->state != MKR_ROOM && GAME->state != MKR_NONE)
            toggle_gamestate_maker_effect(1);
        GAME->state = state;
        get_sprite("icon")->rect.left = 0;
    }
    if (state == MKR_TUNNEL) {
        GAME->state = state;
        get_sprite("icon")->rect.left = 25;
        toggle_gamestate_maker_effect(0);
    }
    if (state == MKR_DESTROY) {
        GAME->state = state;
        get_sprite("icon")->rect.left = 50;
        toggle_gamestate_maker_effect(0);
    }
}

void toggle_gamestate(gamestate_t state)
{
    if (GAME->state == state)
        return;
    toggle_gamestate_playpause(state);
    toggle_gamestate_rewind(state);
    toggle_gamestate_maker(state);
}
