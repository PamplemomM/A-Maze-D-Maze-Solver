/*
** EPITECH PROJECT, 2025
** text_csfml.c
** File description:
** Text related functions.
*/

#include "../../include/header_csfml.h"

text_t **get_textlist(void)
{
    static text_t *textlist = NULL;

    return &textlist;
}

text_t *get_text(char const *name)
{
    text_t *text = *get_textlist();

    while (text != NULL) {
        if (strcmp(text->name, name) == 0)
            return text;
        text = text->next;
    }
    return NULL;
}

static void setup_text(text_t *text)
{
    if (*get_textlist() == NULL)
        text->font = sfFont_createFromFile(DEF_FONT);
    else
        text->font = (*get_textlist())->font;
    text->text = sfText_create();
    sfText_setCharacterSize(text->text, 60);
    sfText_setFont(text->text, text->font);
    sfText_setString(text->text, text->str);
    text->scale = (sfVector2f){1, 1};
    text->angle = 0;
    text->alpha = 1;
    text->color = sfBlack;
    text->draw = 1;
    text->next = *get_textlist();
    *get_textlist() = text;
}

text_t *make_text(char *name, char *str, int x, int y)
{
    text_t *text = malloc(sizeof(text_t));

    if (text == NULL)
        return NULL;
    text->name = strdup(name);
    if (text->name == NULL)
        return OMNIFREE(text, 1);
    text->pos = (sfVector2f){x, y};
    text->str = strdup(str);
    if (text->str == NULL) {
        OMNIFREE(text->name, 1);
        return OMNIFREE(text, 1);
    }
    setup_text(text);
    return text;
}

void draw_alltexts(void)
{
    text_t *text = *get_textlist();

    while (text != NULL) {
        if (text->draw) {
            sfText_setPosition(text->text, text->pos);
            sfText_setScale(text->text, text->scale);
            sfText_setRotation(text->text, text->angle);
            text->color.a = text->alpha * 255;
            sfText_setFillColor(text->text, text->color);
            sfRenderWindow_drawText(WINDOW, text->text, NULL);
        }
        text = text->next;
    }
}

void free_text(text_t *text)
{
    sfText_destroy(text->text);
    OMNIFREE(text->name, 1);
    OMNIFREE(text->str, 1);
    OMNIFREE(text, 1);
}
