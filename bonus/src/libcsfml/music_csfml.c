/*
** EPITECH PROJECT, 2024
** music_csfml
** File description:
** Music related functions.
*/

#include "../../include/header_csfml.h"

music_t **get_music(void)
{
    static music_t *music = NULL;

    return &music;
}

music_t *play_music(char *name, char const *file, float volume, float pitch)
{
    music_t *music = *get_music();

    if (music == NULL) {
        music = malloc(sizeof(music_t));
        if (music == NULL)
            return NULL;
        *get_music() = music;
    } else
        sfMusic_destroy(music->music);
    music->name = strdup(name);
    if (music->name == NULL)
        return OMNIFREE(music, 1);
    music->music = sfMusic_createFromFile(file);
    music->time = 0.0;
    music->volume = volume;
    music->pitch = pitch;
    sfMusic_play(music->music);
    update_music();
    return music;
}

void update_music(void)
{
    music_t *music = *get_music();

    if (music == NULL)
        return;
    music->time = sfMusic_getPlayingOffset(music->music).microseconds
    / 1000000.0;
    sfMusic_setVolume(music->music, music->volume);
    sfMusic_setPitch(music->music, music->pitch);
}

void destroy_music(void)
{
    music_t *music = *get_music();

    if (music == NULL)
        return;
    sfMusic_destroy(music->music);
    OMNIFREE(music->name, 1);
    OMNIFREE(music, 1);
}
