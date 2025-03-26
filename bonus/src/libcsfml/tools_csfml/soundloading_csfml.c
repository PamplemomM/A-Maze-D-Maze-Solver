/*
** EPITECH PROJECT, 2025
** soundloading_csfml.c
** File description:
** Sound loading functions.
*/

#include "../../../include/header_csfml.h"
#include "../../../include/header_tools.h"
#include <stddef.h>
#include <stdlib.h>
#include <dirent.h>

static char *merge_sound_path(char *name)
{
    char *path = NULL;
    char *tmp = NULL;

    tmp = merge_str(name, FORMAT_SFX);
    if (tmp == NULL)
        return NULL;
    path = merge_str(PATH_SFX, tmp);
    if (path == NULL)
        return OMNIFREE(tmp, 1);
    return path;
}

static void setup_sound(sound_t *sound)
{
    sound->sound = sfSound_create();
    sfSound_setBuffer(sound->sound, sound->buffer);
    sound->volume = 0.0;
    sound->pitch = 1.0;
    sound->status = 0;
    sound->next = *get_soundbank();
    *get_soundbank() = sound;
}

sound_t *load_sound(char *name)
{
    sound_t *sound = malloc(sizeof(sound_t));
    char *path = NULL;

    if (sound == NULL)
        return NULL;
    path = merge_sound_path(name);
    if (path == NULL)
        return OMNIFREE(sound, 1);
    sound->name = strdup(name);
    if (sound->name == NULL) {
        OMNIFREE(path, 1);
        return OMNIFREE(sound, 1);
    }
    sound->buffer = sfSoundBuffer_createFromFile(path);
    OMNIFREE(path, 1);
    setup_sound(sound);
    return sound;
}

int precache_sounds(void)
{
    DIR *dr = opendir(PATH_SFX);
    struct dirent *buff = NULL;
    char *name = NULL;

    buff = readdir(dr);
    while (buff != NULL) {
        name = buff->d_name;
        if (strcmp(&(name)[strlen(name) - strlen(FORMAT_SFX)], FORMAT_SFX) != 0) {
            buff = readdir(dr);
            continue;
        }
        name[strlen(name) - strlen(FORMAT_SFX)] = '\0';
        if (load_sound(name) == NULL) {
            OMNIFREE(name, 1);
            closedir(dr);
            return ERROR;
        }
        buff = readdir(dr);
    }
    OMNIFREE(name, 1);
    closedir(dr);
}
