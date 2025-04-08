/*
** EPITECH PROJECT, 2025
** main_maker.c
** File description:
** Main file for the A-Maze-d script maker.
*/

#include "../../include/header_viewer.h"

sprite_t *get_room_sprite(room_t *room) // possibly useless
{
    sprite_t *sprite = NULL;
    char *name = merge_str("room_", room->name);

    if (name == NULL)
        return OMNIFREE(name, 1);
    sprite = get_sprite(name);
    OMNIFREE(name, 1);
    return sprite;
}

void tmp_room_track(sfMouseMoveEvent mouse)
{
    sfVector2i mouse_gamepos =
        {CAM->center.x + (mouse.x - 400) / CAM->zoom + 25,
        CAM->center.y + (mouse.y - 300) / CAM->zoom + 25};
    sfVector2f snapped_pos =
        {(mouse_gamepos.x / 50 - (mouse_gamepos.x < 0)) * 50,
        (mouse_gamepos.y / 50 - (mouse_gamepos.y < 0)) * 50};

    get_sprite("room_tmp")->pos = snapped_pos;
}

static char *make_room_name(sprite_t *room)
{
    char *name = NULL;
    char *tmp1 = NULL;
    char *tmp2 = NULL;

    tmp2 = int_to_str((int)(room->pos.x / 50));
    if (tmp2 == NULL)
        return NULL;
    tmp1 = merge_str(tmp2, "_");
    OMNIFREE(tmp2, 1);
    if (tmp1 == NULL)
        return NULL;
    tmp2 = int_to_str((int)(room->pos.y / 50));
    if (tmp2 == NULL)
        return OMNIFREE(tmp1, 1);
    name = merge_str(tmp1, tmp2);
    OMNIFREE(tmp1, 1);
    OMNIFREE(tmp2, 1);
    return name;
}

void destroy_room(room_t *room)
{
    char *name = merge_str("room_", room->name);

    if (name == NULL)
        return;
    DESTROY(get_sprite(name), get_spritelist, free_sprite);
    OMNIFREE(name, 1);
    DESTROY(room, get_rooms, free_room);
}

void room_wobble(room_t *room)
{
    sprite_t *sprite = NULL;
    char *name = merge_str("room_", room->name);

    if (name == NULL)
        return;
    sprite = get_sprite(name);
    run_timer(name, 0.5);
    OMNIFREE(name, 1);
}

void interact_maker(void)
{
    sprite_t *room_tmp = get_sprite("room_tmp");
    char *name = NULL;

    if (MOUSEPRESS(sfMouseLeft) && get_timer("place_cdwn") == NULL) {
        run_timer("place_cdwn", 0.5);
        name = make_room_name(room_tmp);
        if (add_room(name, room_tmp->pos.x, room_tmp->pos.y, &MAZE) == ERROR) {
            destroy_room(get_room(name, MAZE));
            OMNIFREE(name, 1);
            return;
        }
        create_room_sprite(get_room(name, MAZE));
        room_wobble(get_room(name, MAZE));
        OMNIFREE(name, 1);
        play_sound("place", 60, diceroll(90, 110) / 100.0);
    }
}

void events_maker(void)
{
    sfEvent event;

    cam_move_keys();
    interact_maker();
    while (sfRenderWindow_pollEvent(WINDOW, &event)) {
        if (event.type == sfEvtMouseMoved) {
            tmp_room_track(event.mouseMove);
            cam_move_mouse(event.mouseMove);
        }
        if (event.type == sfEvtMouseWheelScrolled)
            cam_zoom_mouse(event.mouseWheelScroll);
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyEscape)
            sfRenderWindow_close(WINDOW);
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(WINDOW);
    }
}

void update_rooms(void)
{
    sprite_t *room = NULL;
    timers_t *timer = *get_timerlist();
    float time_left = 0;

    while (timer != NULL) {
        room = get_sprite(timer->name);
        if (room != NULL) {
            time_left = timer->tend - TIME;
            room->scale.x = 1 + cos(TIME * 28) * time_left / 6.0 + time_left / 3.0;
            room->scale.y = 1 + sin(TIME * 28) * time_left / 6.0 + time_left / 3.0;
        }
        timer = timer->next;
    }
}

int update_stuff_maker(void)
{
    update_tweens();
    update_timers();
    update_music();
    //if (update_robots() == ERROR)
    //    return ERROR;
    update_rooms();
    if (TIME > 4.5)
        update_compass();
    hue_shift();
    draw_allsprites(NONE);
    draw_allsprites(TUNNEL);
    draw_allsprites(ROOM);
    //draw_robots();
    draw_alltexts(NONE);
    update_cam();
    draw_allsprites(HUD);
    draw_alltexts(HUD);
    events_maker();
    return SUCCESS;
}

void run_maker(void)
{
    while (sfRenderWindow_isOpen(WINDOW)) {
        sfRenderWindow_clear(WINDOW, sfBlack);
        if (update_stuff_maker() == ERROR) {
            sfRenderWindow_close(WINDOW);
            return;
        }
        sfRenderWindow_display(WINDOW);
    }
}

int init_thingthing(void)
{
    if (make_sprite("room_tmp", "room_default", 0, 0) == NULL)
        return ERROR;
    get_sprite("room_tmp")->color = color_from_hue(0, 255, 0, 150);
    get_sprite("room_tmp")->type = ROOM;
    center_sprite_origin(get_sprite("room_tmp"), 0.5, 0.5);
    return SUCCESS;
}

int init_maker_sprites(void)
{
    int inits[4] = {init_thingthing(),
        init_blackscreen(), init_compass(), init_bg()};

    for (int i = 0; i < 4; i++) {
        if (inits[i] == ERROR)
            return ERROR;
    }
    return SUCCESS;
}

int init_maker_assets(void)
{
    create_window(800, 600, "A-MAZE-D VIEWER!");
    *get_clock() = sfClock_create();
    GAME->bounds = (sfIntRect){10, 10, 50, 50};
    if (init_cam() == NULL)
        return ERROR;
    setup_camera();
    if (init_maker_sprites() == ERROR)
        return ERROR;
    if (init_sounds() == ERROR)
        return ERROR;
    if (init_music() == ERROR)
        return ERROR;
    return SUCCESS;
}

int start_maker(void)
{
    int retval = SUCCESS;

    if (init_new_maze() == ERROR)
        return ERROR;
    if (init_gamestuff() != ERROR && init_maker_assets() != ERROR)
        run_maker();
    else
        retval = ERROR;
    destroy_assets();
    free_maze(&MAZE);
    return retval;
}
