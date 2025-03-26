/*
** EPITECH PROJECT, 2025
** header_csfml.h
** File description:
** Header for my CSFML lib.
*/

#ifndef CSFML_H
    #define CSFML_H

    #include "../../include/header_amazed.h"
    #include "header_tools.h"
    #include <SFML/Graphics.h>
    #include <SFML/Audio.h>
    #include <SFML/System.h>
    #include <stdlib.h>
    #include <string.h>
    #include <math.h>

    // assets paths:
    #define PATH_IMG "assets/images/"
    #define PATH_SFX "assets/sounds/"
    #define PATH_MUS "assets/music/"

    // assets formats:
    #define FORMAT_IMG ".png"
    #define FORMAT_SFX ".wav"
    #define FORMAT_MUS ".ogg"

    // default font:
    #define DEF_FONT "assets/fonts/VT323-Regular.ttf"

    // functions:
    #define WINDOW *get_window()
    #define TIME get_time()
    #define CAM (*get_cam())
    #define KEYPRESS(key) sfKeyboard_isKeyPressed(key)
    #define MOUSEPRESS(button) sfMouse_isButtonPressed(button)
    #define DESTROY(thing, list_func, free_func) destroy_thing((void *)thing, \
        (void **(*)(void))(list_func), (void (*)(void *))(free_func))

    // tools:
    #define MIN(a, b) ((a) < (b) ? (a) : (b))
    #define MAX(a, b) ((a) > (b) ? (a) : (b))

// ------- CSFML LIB STRUCTURES --------

typedef enum tween_methods {
    LINEAR,
    EASEIN,
    EASEOUT,
    EASEINOUT
} method_t; // tweening methods for the tween_t structure

typedef struct camera_s {
    sfView *view;
    sfVector2f center;
    sfVector2f size;
    float zoom;
    float angle;
} cam_t; // structure for a game camera

typedef struct linked_list_s {
    struct linked_list_s *next;
} linked_list_t; // generic linked list for destroy functions

typedef struct sprite_s {
    struct sprite_s *next;
    char *name;
    sfSprite *sprite;
    sfTexture *texture;
    sfVector2f pos;
    sfVector2f scale;
    float angle;
    sfColor color;
    sfIntRect rect;
    int draw;
} sprite_t; // linked list for sprites

typedef struct text_s {
    struct text_s *next;
    char *name;
    sfText *text;
    sfFont *font;
    char *str;
    sfVector2f pos;
    sfVector2f scale;
    float angle;
    float alpha;
    sfColor color;
    int draw;
} text_t; // linked list for texts

typedef struct tween_s {
    struct tween_s *next;
    char *name;
    float *value;
    float start;
    float dest;
    float tstart;
    float tend;
    method_t method;
} tween_t; // linked list for tweens
           // a tween is used to ease a value into a destination

typedef struct timer_s {
    struct timer_s *next;
    char *name;
    float tstart;
    float tend;
} timers_t; // linked list for timers

typedef struct sound_s {
    struct sound_s *next;
    char *name;
    sfSound *sound;
    sfSoundBuffer *buffer;
    float time;
    float volume;
    float pitch;
    sfSoundStatus status;
} sound_t; // linked list for sounds

typedef struct music_s {
    char *name;
    sfMusic *music;
    float time;
    float volume;
    float pitch;
} music_t; // structure for music

// -------- CSFML LIB FUNCTIONS --------

// --- window_csfml.c ---
sfRenderWindow **get_window(void);
void create_window(unsigned int width, unsigned int height, char const *name);
void destroy_window(void);

// --- destroy_csfml.c ---
void destroy_thing(void *element, void **(*list_func)(void),
    void (*free_func)(void *));

// --- cam_csfml.c ---
cam_t **get_cam(void);
cam_t *init_cam(void);
void update_cam(void);
void destroy_cam(void);

// --- sprites_csfml.c ---
sprite_t **get_spritelist(void);
sprite_t *get_sprite(char const *name);
sprite_t *make_sprite(char *name, char *file, int x, int y);
void draw_sprite(sprite_t *sprite);
void free_sprite(sprite_t *sprite);

// --- text_csfml.c ---
text_t **get_textlist(void);
text_t *get_text(char const *name);
text_t *make_text(char *name, char *str, int x, int y);
void draw_alltexts(void);
void free_text(text_t *text);

// --- tweens_csfml.c ---
tween_t **get_tweenlist(void);
tween_t *get_tween(char const *name);
void update_tweens(void);
tween_t *make_tween(char *name, float *val, float dest, float dur);
void free_tween(tween_t *tween);

// --- timers_csfml.c ---
timers_t **get_timerlist(void);
timers_t *get_timer(char const *name);
timers_t *run_timer(char *name, float dur);
void update_timers(void);
void free_timer(timers_t *timer);

// --- sounds_csfml.c ---
sound_t **get_soundbank(void);
sound_t *get_sound(char const *name);
sound_t *play_sound(char *name, float volume, float pitch);
void update_sounds(void);
void free_sound(sound_t *sound);

// --- music_csfml.c ---
music_t **get_music(void);
music_t *play_music(char *name, char *file, float volume, float pitch);
void update_music(void);
void destroy_music(void);

// --- time_csfml.c ---
sfClock **get_clock(void);
float get_time(void);
void destroy_clock(void);

// ----- CSFML LIB TOOL FUNCTIONS ------

// --- spritetools_csfml.c ---
void draw_allsprites(void);
void center_sprite_origin(sprite_t *sprite, float xfact, float yfact);

// --- soundloading_csfml.c ---
sound_t *load_sound(char *name);
int precache_sounds(void);

// --- arsenal_csfml.c ---
sfColor color_from_hue(float hue, float brightness,
    float saturation, float opacity);
int play_random_sound(char *name, int range, float volume, float pitch);
void animate(sprite_t *sprite, int first, int last, int fps);
void text_jumpscare(char *str, float dur);

#endif /* CSFML_H */
