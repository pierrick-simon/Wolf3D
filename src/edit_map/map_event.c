/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** map_event
*/

#include "editor.h"

static void set_orientation(sfEvent event, edit_map_t *edit)
{
    if (is_input(event, sfKeyLeft, sfFalse, 0)) {
        edit->draw_map->rotate -= RAD(1);
    }
    if (is_input(event, sfKeyRight, sfFalse, 0)) {
        edit->draw_map->rotate += RAD(1);
    }
}

static void set_zoom(sfEvent event, edit_map_t *edit)
{
    float zoom = 0;

    if (event.type == sfEvtMouseWheelScrolled) {
        zoom = event.mouseWheelScroll.delta;
        if (zoom > 0)
            zoom = ZOOM * -1;
        else
            zoom = ZOOM;
        edit->draw_map->zoom += zoom;
        if (edit->draw_map->zoom > MAX_ZOOM)
            edit->draw_map->zoom = MAX_ZOOM;
        if (edit->draw_map->zoom < MIN_ZOOM)
            edit->draw_map->zoom = MIN_ZOOM;
    }
}

static void move_map(sfEvent event, edit_map_t *edit)
{
    if (is_input(event, sfKeyZ, sfFalse, 0)) {
        edit->draw_map->pos.y -= MOVE;
        if (edit->draw_map->pos.y < -1 * (WIN_HEIGHT / 2))
            edit->draw_map->pos.y = -1 * (WIN_HEIGHT / 2);
    }
    if (is_input(event, sfKeyS, sfFalse, 0)) {
        edit->draw_map->pos.y += MOVE;
        if (edit->draw_map->pos.y > WIN_HEIGHT / 2)
            edit->draw_map->pos.y = WIN_HEIGHT / 2;
    }
    if (is_input(event, sfKeyQ, sfFalse, 0)) {
        edit->draw_map->pos.x -= MOVE;
        if (edit->draw_map->pos.x < -1 * (WIN_WIDTH / 2))
            edit->draw_map->pos.x = -1 * (WIN_WIDTH / 2);
    }
    if (is_input(event, sfKeyD, sfFalse, 0)) {
        edit->draw_map->pos.x += MOVE;
        if (edit->draw_map->pos.x > WIN_WIDTH / 2)
            edit->draw_map->pos.x = WIN_WIDTH / 2;
    }
}

static void reset_pos(sfEvent event, edit_map_t *edit)
{
    if (is_input(event, sfKeyA, sfFalse, 0)) {
        edit->draw_map->pos = (sfVector2f){0, 0};
        edit->draw_map->rotate = 0;
        edit->draw_map->zoom = 1;
    }
}

void map_event(sfEvent event, edit_map_t *edit_map)
{
    move_map(event, edit_map);
    set_zoom(event, edit_map);
    set_orientation(event, edit_map);
    reset_pos(event, edit_map);
}
