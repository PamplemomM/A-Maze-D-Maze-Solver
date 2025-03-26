/*
** EPITECH PROJECT, 2025
** sounds_csfml.c
** File description:
** Sound related functions.
*/

#include "../../include/header_csfml.h"

sound_t **get_soundbank(void)
{
    static sound_t *soundbank = NULL;

    return &soundbank;
}

sound_t *get_sound(char const *name)
{
    sound_t *sound = *get_soundbank();

    while (sound != NULL) {
        if (strcmp(sound->name, name) == 0)
            return sound;
        sound = sound->next;
    }
    return NULL;
}

sound_t *play_sound(char *name, float volume, float pitch)
{
    sound_t *sound = get_sound(name);

    if (sound == NULL) {
        sound = load_sound(name);
        if (sound == NULL)
            return NULL;
    }
    sound->time = 0.0;
    sound->volume = volume;
    sound->pitch = pitch;
    sfSound_play(sound->sound);
    update_sounds();
    return sound;
}

void update_sounds(void)
{
    sound_t *sound = *get_soundbank();

    while (sound != NULL) {
        sound->time = sfSound_getPlayingOffset(sound->sound).microseconds
        / 1000000.0;
        sfSound_setVolume(sound->sound, sound->volume);
        sfSound_setPitch(sound->sound, sound->pitch);
        sound->status = sfSound_getStatus(sound->sound);
        sound = sound->next;
    }
}

void free_sound(sound_t *sound)
{
    sfSound_destroy(sound->sound);
    sfSoundBuffer_destroy(sound->buffer);
    OMNIFREE(sound->name, 1);
    OMNIFREE(sound, 1);
}
