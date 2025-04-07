/*
** EPITECH PROJECT, 2025
** texttools_csfml.c
** File description:
** Text tool functions.
*/

#include "../../../include/header_csfml.h"

void draw_alltexts(element_type_t type)
{
    text_t *text = *get_textlist();

    while (text != NULL) {
        if (type == ANY || text->type == type)
            draw_text(text);
        text = text->next;
    }
}
