/*
** EPITECH PROJECT, 2025
** main_maker.c
** File description:
** Main file for the A-Maze-d script maker.
*/

#include "../../include/header_viewer.h"

void track_room_select(void) // COME HERE!!!!
{
    static sfVector2f prev_pos = {0, 0};
    sfVector2i mouse = sfMouse_getPositionRenderWindow(WINDOW);
    sfVector2i mouse_gamepos;
    sfVector2f snapped_pos;

    if (mouse.x < 0 || mouse.y < 0 || mouse.x > 800 || mouse.y > 600) {
        get_sprite("room_select")->draw = 0;
        return;
    }
    mouse_gamepos = (sfVector2i)
        {CAM->center.x + (mouse.x + CAM->offset.x - 400) / CAM->zoom + 25,
        CAM->center.y + (mouse.y + CAM->offset.y - 300) / CAM->zoom + 25};
    snapped_pos = (sfVector2f)
        {(mouse_gamepos.x / 50 - (mouse_gamepos.x < 0)) * 50,
        (mouse_gamepos.y / 50 - (mouse_gamepos.y < 0)) * 50};
    get_sprite("room_select")->pos = snapped_pos;
    get_sprite("room_select")->draw = 1;
    if (snapped_pos.x != prev_pos.x || snapped_pos.y != prev_pos.y)
        play_sound("click", MIN(10.0 * CAM->zoom, MIN(TIME * 5, 20.0)), 1.0);
    prev_pos = snapped_pos;
}

// you are autistic, don't forget it. you are AUTISTIC.
int interact_room(void)
{
    sprite_t *select = get_sprite("room_select");
    char *name = make_room_name(select->pos);

    if (GAME->state == MKR_ROOM && get_room(name, MAZE) == NULL) {
        if (place_room() == ERROR) {
            OMNIFREE(name, 1);
            return ERROR;
        }
    } else if (GAME->state == MKR_DESTROY && get_room(name, MAZE) != NULL) {
        destroy_room(get_room(name, MAZE));
        update_rooms_pos(select, 1);
    }
    OMNIFREE(name, 1);
    return SUCCESS;
}

void set_interaction(void)
{
    if ((GAME->state == MKR_NONE || GAME->state == MKR_ROOM)
        && MOUSEPRESS(sfMouseLeft)) {
        toggle_gamestate(MKR_ROOM);
        return;
    }
    if ((GAME->state == MKR_NONE || GAME->state == MKR_DESTROY)
        && KEYPRESS(sfKeyLControl)) {
        toggle_gamestate(MKR_DESTROY);
        return;
    }
    if ((GAME->state == MKR_NONE || GAME->state == MKR_TUNNEL)
        && KEYPRESS(sfKeyLAlt)) {
        toggle_gamestate(MKR_TUNNEL);
        return;
    }
    toggle_gamestate(MKR_NONE);
}

int interact_maker(void)
{
    set_interaction();
    if (interact_nb_robots() == ERROR)
        return ERROR;
    if (GAME->state == MKR_ROOM || GAME->state == MKR_DESTROY)
        return interact_room();
    interact_tunnel();
    if (GAME->state == MKR_NONE
        && KEYPRESS(sfKeyE) && get_sprite("room_select")->draw) {
        GAME->state = MKR_EXIT;
        if (place_room() == ERROR)
            return ERROR;
        GAME->state = MKR_NONE;
    }
    if (GAME->state == MKR_NONE
        && KEYPRESS(sfKeyS) && get_timer("save_cdwn") == NULL) {
        run_timer("save_cdwn", 1.0);
        save_maze();
        return SUCCESS;
    }
    return SUCCESS;
}

void events_maker(void)
{
    sfEvent event;

    cam_move_keys();
    track_room_select();
    interact_maker(); // this can return ERROR
    interact_sim_logs();
    while (sfRenderWindow_pollEvent(WINDOW, &event)) {
        if (event.type == sfEvtMouseMoved)
            cam_move_mouse(event.mouseMove);
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

void update_room_select(void)
{
    sprite_t *room = get_sprite("room_select");
    float fact = cos(TIME * 2.0);
    float scale = 1.1 + fact / 20;
    float tweened_scale = scale + (room->scale.x - scale) / 1.2;

    room->scale = (sfVector2f){tweened_scale, tweened_scale};
    room->color.a = (fact + 1) * 25 + 100;
}

int update_stuff_maker(void)
{
    update_tweens();
    update_timers();
    update_music();
    update_rooms();
    update_room_select();
    if (TIME > 4.5)
        update_compass();
    hue_shift();
    update_cam();
    draw_allsprites(NONE);
    draw_allsprites(TUNNEL);
    draw_allsprites(ROOM);
    //draw_robots();
    draw_alltexts(NONE);
    draw_allsprites(HUD);
    draw_alltexts(HUD);
    if (sfRenderWindow_hasFocus(WINDOW))
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
