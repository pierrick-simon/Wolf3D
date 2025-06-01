/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** event
*/

#include "editor.h"
#include "save.h"
#include <string.h>

static void set_orientation(sfEvent event, edit_map_t *edit)
{
    if (is_input(event, sfKeyLeft, sfFalse, 0)) {
        edit->rotate -= RAD(1);
    }
    if (is_input(event, sfKeyRight, sfFalse, 0)) {
        edit->rotate += RAD(1);
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
        edit->zoom += zoom;
        if (edit->zoom > MAX_ZOOM)
            edit->zoom = MAX_ZOOM;
        if (edit->zoom < MIN_ZOOM)
            edit->zoom = MIN_ZOOM;
    }
}

static void move_map(sfEvent event, edit_map_t *edit)
{
    if (is_input(event, sfKeyZ, sfFalse, 0)) {
        edit->pos.y -= MOVE;
        if (edit->pos.y < -1 * (WIN_HEIGHT / 2))
            edit->pos.y = -1 * (WIN_HEIGHT / 2);
    }
    if (is_input(event, sfKeyS, sfFalse, 0)) {
        edit->pos.y += MOVE;
        if (edit->pos.y > WIN_HEIGHT / 2)
            edit->pos.y = WIN_HEIGHT / 2;
    }
    if (is_input(event, sfKeyQ, sfFalse, 0)) {
        edit->pos.x -= MOVE;
        if (edit->pos.x < -1 * (WIN_WIDTH / 2))
            edit->pos.x = -1 * (WIN_WIDTH / 2);
    }
    if (is_input(event, sfKeyD, sfFalse, 0)) {
        edit->pos.x += MOVE;
        if (edit->pos.x > WIN_WIDTH / 2)
            edit->pos.x = WIN_WIDTH / 2;
    }
}

static void reset_pos(sfEvent event, edit_map_t *edit)
{
    if (is_input(event, sfKeyA, sfFalse, 0)) {
        edit->pos = (sfVector2f){0, 0};
        edit->rotate = 0;
        edit->zoom = 1;
    }
}

static void switch_scene(sfEvent event, system_t *sys,
    edit_map_t *edit_map, state_info_t *state)
{
    if (is_input(event, sfKeyEnter, sfTrue, 0)
        || is_input(event, sfKeyEscape, sfTrue, 7)) {
        if (is_input(event, sfKeyEscape, sfTrue, 7))
            edit_map->str = EDIT_MAP_BACK;
        if (edit_map->str == EDIT_MAP_SAVE)
            save_map(sys->save, "your_maps");
        state->old_scene = state->scene;
        state->scene = edit_map->draw[edit_map->str].scene;
        edit_map->draw[edit_map->str].color = sfBlack;
        edit_map->str = EDIT_MAP_SAVE;
        edit_map->update = sfFalse;
        sfRenderWindow_setMouseCursorVisible(sys->window, sfFalse);
    }
}

static void switch_str(sfEvent event, edit_map_t *edit_map)
{
    edit_map->draw[edit_map->str].color = sfBlack;
    if (is_input(event, sfKeyUp, sfFalse, 0)
        || sfJoystick_getAxisPosition(0, sfJoystickPovY) == - MAX_JOYSTICK)
        edit_map->str--;
    if (is_input(event, sfKeyDown, sfFalse, 0)
        || sfJoystick_getAxisPosition(0, sfJoystickPovY) == MAX_JOYSTICK)
        edit_map->str++;
    if (edit_map->str == NB_EDIT_MAP)
        edit_map->str = EDIT_MAP_SAVE;
    if (edit_map->str == EDIT_MAP_TITLE)
        edit_map->str = EDIT_MAP_BACK;
    edit_map->draw[edit_map->str].color = sfRed;
}

void edit_map_events(system_t *sys, edit_map_t *edit_map)
{
    sfEvent event = {0};

    while (sfRenderWindow_pollEvent(sys->window, &event)) {
        sys_events(event, sys);
        switch_str(event, edit_map);
        switch_scene(event, sys, edit_map, sys->state);
        move_map(event, edit_map);
        set_zoom(event, edit_map);
        set_orientation(event, edit_map);
        reset_pos(event, edit_map);
    }
}
