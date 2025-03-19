/*
** EPITECH PROJECT, 2025
** tools
** File description:
** Tool functions with awesome names.
*/

#include "../include/header.h"

sfColor color_from_hue(float hue, float brightness,
    float saturation, float opacity)
{
    sfColor color;

    color.r = (cos(hue * M_PI / 180.0) + 1) * 127;
    color.g = (cos((hue + 120) * M_PI / 180.0) + 1) * 127;
    color.b = (cos((hue + 240) * M_PI / 180.0) + 1) * 127;
    color.r = brightness + (color.r - brightness) * saturation / 255.0;
    color.g = brightness + (color.g - brightness) * saturation / 255.0;
    color.b = brightness + (color.b - brightness) * saturation / 255.0;
    color.r *= brightness / 255.0;
    color.g *= brightness / 255.0;
    color.b *= brightness / 255.0;
    color.a = opacity;
    return color;
}

int diceroll(int low, int high)
{
    if (high < low)
        return high;
    return low + rand() % (high - low + 1);
}

void play_random_sound(char *name, int range, float volume, float pitch)
{
    char *newname = malloc(sizeof(char) * (strlen(name) + 2));
    int pick = diceroll(0, range);

    if (newname == NULL)
        return;
    strcpy(newname, name);
    strcat(newname, "0");
    newname[strlen(name)] += pick;
    play_sound(newname, volume, pitch);
    free(newname);
}

void animate(sprite_t *sprite, int first, int last, int fps)
{
    sfIntRect *rect = &sprite->rect;
    sfVector2u size = sfTexture_getSize(sprite->texture);
    unsigned long frame = TIME / (1.0 / fps);
    int frx = size.x / rect->width;
    int fry = size.y / rect->height;

    frame = frame % (last - first + 1) + first;
    rect->left = (frame % frx) * rect->width;
    rect->top = (frame / frx % fry) * rect->height;
}

int digitcount(int nbr)
{
    int len = 0;

    if (nbr == 0)
        return 0;
    while (nbr != nbr / 10) {
        nbr /= 10;
        len++;
    }
    return len;
}

char *int_to_str(int nbr)
{
    char *str;
    int len = digitcount(nbr);

    str = malloc(sizeof(char) * (len + 1));
    if (str == NULL)
        return NULL;
    for (int i = 0; i < len; i++) {
        str[len - i - 1] = nbr % 10 + '0';
        nbr /= 10;
    }
    str[len] = '\0';
    return str;
}

void text_jumpscare(char *str, float dur)
{
    char *jumpscare[3] = {"jumpscare1", "jumpscare2", "jumpscare3"};
    static int i = 0;
    text_t *txt = get_text(jumpscare[i]);

    if (txt == NULL) {
        txt = make_text(jumpscare[i], str, 400 + diceroll(-30, 30),
        300 + diceroll(-20, 20));
    } else {
        free(txt->str);
        txt->str = strdup(str);
        sfText_setString(txt->text, txt->str);
    }
    sfText_setOrigin(txt->text, (sfVector2f){strlen(str) * 10, 30});
    txt->scale = (sfVector2f){1, 1};
    txt->angle = diceroll(-75, 75) / 10.0;
    txt->alpha = 1;
    txt->color = sfWhite;
    make_tween(jumpscare[i], &txt->alpha, 0, dur)->method = EASEIN;
    i = (i + 1) % 3;
}
