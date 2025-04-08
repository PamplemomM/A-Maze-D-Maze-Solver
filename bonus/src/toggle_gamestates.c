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

static void toggle_gamestate_maker(gamestate_t state)
{
    if (state == BUILD) {
        GAME->state = state;
        text_jumpscare("BUILD MODE", 1);
        play_sound("mode_build", 75, diceroll(90, 110) / 100.0);
    }
    if (state == BREAK) {
        GAME->state = state;
        text_jumpscare("BREAK MODE", 1);
        play_sound("mode_break", 75, diceroll(90, 110) / 100.0);
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
