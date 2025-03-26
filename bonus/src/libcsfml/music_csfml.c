/*
** EPITECH PROJECT, 2025
** music_csfml.c
** File description:
** Music related functions.
*/

#include "../../include/header_csfml.h"

music_t **get_music(void)
{
    static music_t *music = NULL;

    return &music;
}

static char *merge_music_path(char *name)
{
    char *path = NULL;
    char *tmp = NULL;

    tmp = merge_str(name, FORMAT_MUS);
    if (tmp == NULL)
        return NULL;
    path = merge_str(PATH_MUS, tmp);
    if (path == NULL)
        return OMNIFREE(tmp, 1);
    OMNIFREE(tmp, 1);
    return path;
}

static void setup_music(music_t *music)
{
    music->time = 0.0;
    sfMusic_play(music->music);
    update_music();
}

music_t *play_music(char *name, char *file, float volume, float pitch)
{
    music_t *music = malloc(sizeof(music_t));
    char *path = NULL;

    destroy_music();
    if (music == NULL)
        return NULL;
    path = merge_music_path(name);
    if (path == NULL)
        return OMNIFREE(music, 1);
    music->name = strdup(name);
    if (music->name == NULL) {
        OMNIFREE(path, 1);
        return OMNIFREE(music, 1);
    }
    music->music = sfMusic_createFromFile(path);
    music->volume = volume;
    music->pitch = pitch;
    OMNIFREE(path, 1);
    setup_music(music);
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
