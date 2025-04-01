/*
** EPITECH PROJECT, 2025
** sprites_csfml.c
** File description:
** Sprite related functions.
*/

#include "../../include/header_csfml.h"

sprite_t **get_spritelist(void)
{
    static sprite_t *spritelist = NULL;

    return &spritelist;
}

sprite_t *get_sprite(char const *name)
{
    sprite_t *sprite = *get_spritelist();

    while (sprite != NULL) {
        if (strcmp(sprite->name, name) == 0)
            return sprite;
        sprite = sprite->next;
    }
    return NULL;
}

static char *merge_sprite_path(char *name)
{
    char *path = NULL;
    char *tmp = NULL;

    tmp = merge_str(name, FORMAT_IMG);
    if (tmp == NULL)
        return NULL;
    path = merge_str(PATH_IMG, tmp);
    if (path == NULL)
        return OMNIFREE(tmp, 1);
    OMNIFREE(tmp, 1);
    return path;
}

static void setup_sprite(sprite_t *sprite)
{
    sfSprite_setTexture(sprite->sprite, sprite->texture, sfTrue);
    sprite->scale = (sfVector2f){1, 1};
    sprite->angle = 0;
    sprite->color = sfWhite;
    sprite->rect = (sfIntRect){0, 0, sfTexture_getSize(sprite->texture).x,
    sfTexture_getSize(sprite->texture).y};
    sprite->type = NONE;
    sprite->draw = 1;
    sprite->next = *get_spritelist();
    *get_spritelist() = sprite;
}

sprite_t *make_sprite(char *name, char *file, int x, int y)
{
    sprite_t *sprite = malloc(sizeof(sprite_t));
    char *path = NULL;

    if (sprite == NULL)
        return NULL;
    path = merge_sprite_path(file);
    if (path == NULL)
        return OMNIFREE(sprite, 1);
    sprite->name = strdup(name);
    if (sprite->name == NULL) {
        OMNIFREE(path, 1);
        return OMNIFREE(sprite, 1);
    }
    sprite->sprite = sfSprite_create();
    sprite->texture = sfTexture_createFromFile(path, NULL);
    sprite->pos = (sfVector2f){x, y};
    OMNIFREE(path, 1);
    setup_sprite(sprite);
    return sprite;
}

void draw_sprite(sprite_t *sprite)
{
    if (sprite->draw) {
        sfSprite_setPosition(sprite->sprite, sprite->pos);
        sfSprite_setTextureRect(sprite->sprite, sprite->rect);
        sfSprite_setScale(sprite->sprite, sprite->scale);
        sfSprite_setRotation(sprite->sprite, sprite->angle);
        sfSprite_setColor(sprite->sprite, sprite->color);
        sfRenderWindow_drawSprite(WINDOW, sprite->sprite, NULL);
    }
}

// oopsy, I left a fart here...
void free_sprite(sprite_t *sprite)
{
    sfSprite_destroy(sprite->sprite);
    sfTexture_destroy(sprite->texture);
    OMNIFREE(sprite->name, 1);
    OMNIFREE(sprite, 1);
}
