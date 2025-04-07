/*
** EPITECH PROJECT, 2025
** init_assets.c
** File description:
** Functions to initialize the program's assets.
*/

#include "../include/header_viewer.h"

static int init_robots(void)
{
    vwr_robot_t **list = malloc(sizeof(vwr_robot_t *) * (MAZE->nb_robots + 1));

    if (list == NULL)
        return ERROR;
    for (int i = 1; i <= MAZE->nb_robots; i++) {
        if (make_robot(i) == NULL)
            return ERROR;
        list[MAZE->nb_robots - i] = get_robot(i);
    }
    list[MAZE->nb_robots] = NULL;
    GAME->robots_order = list;
    return SUCCESS;
}

static void setup_camera(sfIntRect bounds)
{
    float cam_zoom;

    bounds.width -= bounds.left;
    bounds.height -= bounds.top;
    cam_zoom = 2.0 / ((float)MAX(bounds.width, bounds.height) / 200.0);
    GAME->bounds = (sfIntRect){bounds.left - 200, bounds.top - 200, bounds.width + 400, bounds.height + 400};
    CAM->center.x = bounds.left + bounds.width / 2.0;
    CAM->center.y = bounds.top + bounds.height / 2.0;
    CAM->zoom = cam_zoom * 1.2;
    make_tween("camzoom", &CAM->zoom, cam_zoom, 1.7)->method = EASEOUT;
}

static void update_bounds(sfIntRect *bounds, room_t *room)
{
    if (bounds->left == -1 || room->x < bounds->left)
        bounds->left = room->x;
    if (bounds->top == -1 || room->y < bounds->top)
        bounds->top = room->y;
    if (bounds->width == -1 || room->x > bounds->width)
        bounds->width = room->x;
    if (bounds->height == -1 || room->y > bounds->height)
        bounds->height = room->y;
}

static char *get_room_texture(room_t *room)
{
    if (room == MAZE->start)
        return "room_start";
    if (room == MAZE->end)
        return "room_end";
    return "room_default";
}

static void setup_room(sprite_t *sprite)
{
    sprite->color = color_from_hue(0, 150, 0, 255);
    sprite->type = ROOM;
    center_sprite_origin(sprite, 0.5, 0.5);
}

static int init_rooms(void)
{
    room_t *room = MAZE->rooms;
    char *name = NULL;
    sfIntRect bounds = {-1, -1, -1, -1};

    while (room != NULL) {
        name = merge_str("room_", room->name);
        if (name == NULL)
            return ERROR;
        room->x *= 50;
        room->y *= 50;
        update_bounds(&bounds, room);
        if (make_sprite(name, get_room_texture(room), room->x, room->y) == NULL) {
            OMNIFREE(name, 1);
            return ERROR;
        }
        setup_room(get_sprite(name));
        OMNIFREE(name, 1);
        room = room->next;
    }
    setup_camera(bounds);
    return SUCCESS;
}

static void setup_tunnel(sprite_t *sprite, room_t *start, room_t *dest)
{
    int diffx = dest->x - start->x;
    int diffy = dest->y - start->y;
    int diffd = sqrt(pow(diffx, 2) + pow(diffy, 2)) - 25;
    float traj = atan2f(diffx, -diffy) * 180.0 / M_PI;

    sprite->scale.y = diffd / (float)sprite->rect.height;
    sprite->scale.x = (10.0 + 5.0 / sprite->scale.y) / (float)sprite->rect.width;
    sprite->angle = traj;
    sprite->color = color_from_hue(0, 255, 0, 100);
    sprite->type = TUNNEL;
    center_sprite_origin(sprite, 0.5, 1.0);
}

static int init_tunnels(void)
{
    tunnel_t *tunnel = MAZE->tunnels;
    char *path = NULL;
    char *name = NULL;

    while (tunnel != NULL) {
        path = merge_str(tunnel->r1->name, tunnel->r2->name);
        if (path == NULL)
            return ERROR;
        name = merge_str("tunnel_", path);
        OMNIFREE(path, 1);
        if (name == NULL)
            return ERROR;
        if (make_sprite(name, "tunnel", tunnel->r1->x, tunnel->r1->y) == NULL) {
            OMNIFREE(name, 1);
            return ERROR;
        }
        setup_tunnel(get_sprite(name), tunnel->r1, tunnel->r2);
        OMNIFREE(name, 1);
        tunnel = tunnel->next;
    }
    return SUCCESS;
}

static int init_compass(void)
{
    if (make_sprite("cmpa", "compass_arrow", 400, 300) == NULL ||
        make_sprite("cmpp", "compass_pivot", 400, 300) == NULL)
        return ERROR;
    get_sprite("cmpa")->rect.width = 45;
    get_sprite("cmpa")->color.a = 0;
    get_sprite("cmpp")->color.a = 0;
    get_sprite("cmpa")->type = HUD;
    get_sprite("cmpp")->type = HUD;
    center_sprite_origin(get_sprite("cmpa"), 0.5, 4.0);
    center_sprite_origin(get_sprite("cmpp"), 0.5, 0.5);
    return SUCCESS;
}

static int init_logs(void)
{
    if (make_sprite("logs", "AWESOME_PIXEL", -250, 0) == NULL)
        return ERROR;
    if (make_text("logstitle", "LOGS", -170, 1) == NULL)
        return ERROR;
    if (make_text("logstxt", "program launched", -243, 55) == NULL)
        return ERROR;
    get_sprite("logs")->scale = (sfVector2f){250, 600};
    get_sprite("logs")->color = color_from_hue(0, 0, 0, 150);
    get_sprite("logs")->type = HUD;
    get_text("logstitle")->scale = (sfVector2f){0.8, 0.7};
    get_text("logstitle")->color = color_from_hue(0, 255, 0, 255);
    get_text("logstitle")->type = HUD;
    get_text("logstxt")->scale = (sfVector2f){0.25, 0.25};
    get_text("logstxt")->color = color_from_hue(0, 255, 0, 255);
    get_text("logstxt")->type = HUD;
    return SUCCESS;
}

static int init_progbar(void)
{
    if (make_sprite("barprog", "AWESOME_PIXEL", 150, 552) == NULL)
        return ERROR;
    if (make_sprite("barbuff", "AWESOME_PIXEL", 150, 540) == NULL)
        return ERROR;
    if (make_sprite("barbg", "AWESOME_PIXEL", 148, 538) == NULL)
        return ERROR;
    get_sprite("barbg")->scale = (sfVector2f){504, 28.5};
    get_sprite("barbg")->color = color_from_hue(0, 255, 0, 180);
    get_sprite("barbg")->type = HUD;
    get_sprite("barbuff")->scale = (sfVector2f){0, 24.5};
    get_sprite("barbuff")->color = color_from_hue(GAME->hue + 120, 200, 255, 255);
    get_sprite("barbuff")->type = HUD;
    get_sprite("barprog")->scale = (sfVector2f){3, 36};
    get_sprite("barprog")->color = color_from_hue(0, 255, 0, 255);
    get_sprite("barprog")->type = HUD;
    center_sprite_origin(get_sprite("barprog"), 0.5, 0.5);
    return SUCCESS;
}

static int init_bg(void)
{
    float scalex;
    float scaley;
    float diag;

    if (make_sprite("bg", "bg", GAME->bounds.left, GAME->bounds.top) == NULL)
        return ERROR;
    if (make_sprite("shadow", "AWESOME_PIXEL", GAME->bounds.left, GAME->bounds.top + GAME->bounds.height) == NULL)
        return ERROR;
    if (make_sprite("light", "gradient", CAM->center.x, CAM->center.y) == NULL)
        return ERROR;
    scalex = (float)GAME->bounds.width / (float)get_sprite("bg")->rect.width;
    scaley = (float)GAME->bounds.height / (float)get_sprite("bg")->rect.height;
    get_sprite("bg")->scale = (sfVector2f){scalex, scaley};
    get_sprite("bg")->type = NONE;
    get_sprite("bg")->color = color_from_hue(0, 255, 255, 255);
    diag = sqrt(pow(GAME->bounds.width, 2) + pow(GAME->bounds.height, 2));
    get_sprite("shadow")->scale = (sfVector2f){diag - 0.2, 10000};
    get_sprite("shadow")->angle = -atan2f(GAME->bounds.height,
        GAME->bounds.width) * 180.0 / M_PI;
    get_sprite("shadow")->color = color_from_hue(0, 0, 0, 75);
    get_sprite("light")->scale = (sfVector2f){15, 20};
    get_sprite("light")->color = color_from_hue(GAME->hue, 255, 255, 255);
    center_sprite_origin(get_sprite("light"), 0.5, 0.5);
    return SUCCESS;
}

static int init_sprites(void)
{
    int inits[7] = {init_rooms(), init_tunnels(), init_robots(),
        init_compass(), init_logs(), init_progbar(), init_bg()};

    for (int i = 0; i < 7; i++) {
        if (inits[i] == ERROR)
            return ERROR;
    }
    return SUCCESS;
}

static int init_sounds(void)
{
    return precache_sounds();
}

static int init_music(void)
{
    if (play_music("Parade", "K.K. Parade", 50, 1.0) == NULL) // put the volume back up to 50
        return ERROR;
    sfMusic_setLoop((*get_music())->music, sfTrue);
    return SUCCESS;
}

int init_assets(void)
{
    create_window(800, 600, "A-MAZE-D VIEWER!");
    *get_clock() = sfClock_create();
    if (init_cam() == NULL)
        return ERROR;
    if (init_sprites() == ERROR)
        return ERROR;
    if (init_sounds() == ERROR)
        return ERROR;
    if (init_music() == ERROR)
        return ERROR;
    return SUCCESS;
}

// DESTROY THEM ALL !! (Like in the casino of my grandmother)
void destroy_assets(void)
{
    while (*get_robotlist())
        DESTROY(*get_robotlist(), get_robotlist, free_robot);
    while (*get_spritelist())
        DESTROY(*get_spritelist(), get_spritelist, free_sprite);
    if (*get_textlist())
        sfFont_destroy((*get_textlist())->font);
    while (*get_textlist())
        DESTROY(*get_textlist(), get_textlist, free_text);
    while (*get_tweenlist())
        DESTROY(*get_tweenlist(), get_tweenlist, free_tween);
    while (*get_timerlist())
        DESTROY(*get_timerlist(), get_timerlist, free_timer);
    while (*get_soundbank())
        DESTROY(*get_soundbank(), get_soundbank, free_sound);
    destroy_music();
    destroy_clock();
    destroy_window();
    destroy_cam();
    destroy_gamestuff();
}
