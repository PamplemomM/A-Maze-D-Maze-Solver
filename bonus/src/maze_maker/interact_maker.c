/*
** EPITECH PROJECT, 2025
** interact_maker.c
** File description:
** Functions to interact with the maker.
*/

#include "../../include/header_viewer.h"

void update_room_select(void)
{
    sprite_t *room = get_sprite("room_select");
    float fact = cos(TIME * 2.0);
    float scale = 1.1 + fact / 20;
    float tweened_scale = scale + (room->scale.x - scale) / 1.2;

    room->scale = (sfVector2f){tweened_scale, tweened_scale};
    room->color.a = (fact + 1) * 25 + 100;
}

static void snap_room_select(sfVector2f prev_pos)
{
    sfVector2i mouse = sfMouse_getPositionRenderWindow(WINDOW);
    sfVector2i mouse_gamepos =
        {CAM->center.x + (mouse.x + CAM->offset.x - 400) / CAM->zoom + 25,
        CAM->center.y + (mouse.y + CAM->offset.y - 300) / CAM->zoom + 25};
    sfVector2f snapped_pos =
        {(mouse_gamepos.x / 50 - (mouse_gamepos.x < 0)) * 50,
        (mouse_gamepos.y / 50 - (mouse_gamepos.y < 0)) * 50};

    get_sprite("room_select")->pos = snapped_pos;
    if (snapped_pos.x != prev_pos.x || snapped_pos.y != prev_pos.y)
        play_sound("click", MIN(10.0 * CAM->zoom, MIN(TIME * 5, 20.0)), 1.0);
}

void track_room_select(void)
{
    static sfVector2f prev_pos = {0, 0};
    sfVector2i mouse = sfMouse_getPositionRenderWindow(WINDOW);

    if (mouse.x < 0 || mouse.y < 0 || mouse.x > 800 || mouse.y > 600) {
        get_sprite("room_select")->draw = 0;
        return;
    }
    get_sprite("room_select")->draw = 1;
    snap_room_select(prev_pos);
    prev_pos = get_sprite("room_select")->pos;
}

static void set_interaction(void)
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
        if (place_room(get_sprite("room_select")->pos) == ERROR)
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
