/*
** EPITECH PROJECT, 2025
** tweens_csfml
** File description:
** Tween related functions.
*/

#include "../../include/header_csfml.h"

tween_t **get_tweenlist(void)
{
    static tween_t *tweenlist = NULL;

    return &tweenlist;
}

tween_t *get_tween(char const *name)
{
    tween_t *tween = *get_tweenlist();

    while (tween != NULL) {
        if (strcmp(tween->name, name) == 0)
            return tween;
        tween = tween->next;
    }
    return NULL;
}

tween_t *make_tween(char *name, float *val, float dest, float dur)
{
    tween_t *tween = get_tween(name);

    if (tween == NULL) {
        tween = malloc(sizeof(tween_t));
        if (tween == NULL)
            return NULL;
        tween->name = strdup(name);
        if (tween->name == NULL)
            return OMNIFREE(tween, 1);
        tween->next = *get_tweenlist();
        *get_tweenlist() = tween;
    }
    tween->value = val;
    tween->start = *val;
    tween->dest = dest;
    tween->tstart = TIME;
    tween->tend = TIME + dur;
    tween->method = LINEAR;
    return tween;
}

static void do_tween(tween_t *tween, method_t method)
{
    float *val = tween->value;
    double prog = (TIME - tween->tstart) / (tween->tend - tween->tstart);
    double fact;

    if (method == LINEAR) {
        *val = tween->start + ((tween->dest - tween->start) /
        (tween->tend - tween->tstart)) * (TIME - tween->tstart);
        return;
    }
    if (method == EASEIN)
        fact = pow(prog, 5);
    if (method == EASEOUT)
        fact = 1 - pow(1 - prog, 5);
    if (method == EASEINOUT) {
        if (prog < 0.5)
            fact = 2 * pow(prog, 2);
        else
            fact = (1 - pow(-2 * prog + 2, 2) / 2);
    }
    *val = tween->start + (tween->dest - tween->start) * fact;
}

void update_tweens(void)
{
    tween_t *tween = *get_tweenlist();
    tween_t *tmp = NULL;

    while (tween != NULL) {
        tmp = tween->next;
        do_tween(tween, tween->method);
        if (TIME >= tween->tend) {
            *tween->value = tween->dest;
            DESTROY(tween, get_tweenlist, free_tween);
        }
        tween = tmp;
    }
}

void free_tween(tween_t *tween)
{
    OMNIFREE(tween->name, 1);
    OMNIFREE(tween, 1);
}
