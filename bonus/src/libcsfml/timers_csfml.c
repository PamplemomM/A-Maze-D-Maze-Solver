/*
** EPITECH PROJECT, 2025
** timers_csfml.c
** File description:
** Timer related functions.
*/

#include "../../include/header_csfml.h"

timers_t **get_timerlist(void)
{
    static timers_t *timerlist = NULL;

    return &timerlist;
}

timers_t *get_timer(char const *name)
{
    timers_t *timer = *get_timerlist();

    while (timer != NULL) {
        if (strcmp(timer->name, name) == 0)
            return timer;
        timer = timer->next;
    }
    return NULL;
}

timers_t *run_timer(char *name, float dur)
{
    timers_t *timer = get_timer(name);

    if (timer == NULL) {
        timer = malloc(sizeof(timer_t));
        if (timer == NULL)
            return NULL;
        timer->name = strdup(name);
        if (timer->name == NULL)
            return OMNIFREE(timer, 1);
        timer->next = *get_timerlist();
        *get_timerlist() = timer;
    }
    timer->tstart = TIME;
    timer->tend = TIME + dur;
    return timer;
}

void update_timers(void)
{
    timers_t *timer = *get_timerlist();
    timers_t *tmp;

    while (timer != NULL) {
        tmp = timer->next;
        if (TIME >= timer->tend)
            DESTROY(timer->name, get_timerlist, free_timer);
        timer = tmp;
    }
}

void free_timer(timers_t *timer)
{
    OMNIFREE(timer->name, 1);
    OMNIFREE(timer, 1);
}
