/*
** EPITECH PROJECT, 2025
** destroy_csfml
** File description:
** Element destruction related functions.
*/

#include "../../include/header_csfml.h"

static void destroy_first(void **(*list_func)(void), void (*free_func)(void *))
{
    linked_list_t *list = (linked_list_t *)(*list_func());
    linked_list_t *next = NULL;

    if (list == NULL)
        return;
    next = list->next;
    free_func(list);
    *list_func() = next;
}

static void destroy_last(void **(*list_func)(void), void (*free_func)(void *))
{
    linked_list_t *list = (linked_list_t *)(*list_func());

    if (list->next == NULL) {
        free_func(list);
        *list_func() = NULL;
        return;
    }
    while (list->next->next != NULL)
        list = list->next;
    free_func(list->next);
    list->next = NULL;
}

static void destroy_middle(linked_list_t *list, void **(*list_func)(void),
    void (*free_func)(void *))
{
    linked_list_t *tmp = NULL;

    tmp = list->next;
    list->next = tmp->next;
    free_func(tmp);
}

void destroy_thing(void *element, void **(*list_func)(void),
    void (*free_func)(void *))
{
    linked_list_t *list = (linked_list_t *)(*list_func());

    if (element == NULL)
        return;
    if (list == element) {
        destroy_first(list_func, free_func);
        return;
    }
    while (list->next != NULL) {
        if (list->next == element)
            break;
        list = list->next;
    }
    if (list->next == NULL) {
        destroy_last(list_func, free_func);
        return;
    }
    destroy_middle(list, list_func, free_func);
}
