/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** event
*/

#include "editor.h"
#include "save.h"
#include "linked_list.h"
#include <string.h>
#include <stdio.h>

static sfBool one_use(
    system_t *sys, edit_map_t *edit, edit_t i)
{
    if (BUTTON[i].state == STAY)
        return sfFalse;
    BUTTON[i].f(sys, edit);
    return sfTrue;
}

static sfVector2i get_pos(system_t *sys)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(sys->window);

    if (sys->state->fullscreen == false) {
        mouse_pos.x *= 2;
        mouse_pos.y *= 2;
    }
    return mouse_pos;
}

static void check_press_button(
    system_t *sys, buttons_t *buttons, edit_map_t *edit, edit_t i)
{
    sfBool change = sfFalse;
    sfVector2i mouse_pos = get_pos(sys);

    if (sfFloatRect_contains(&edit->buttons->bounds[i],
        mouse_pos.x, mouse_pos.y) == sfFalse
        || one_use(sys, edit, i))
        return;
    if (buttons->press == sfTrue && edit->edit != i) {
        edit->edit = i;
        change = sfTrue;
    }
    if (buttons->press == sfTrue && edit->edit == i
        && change == sfFalse) {
        buttons->press = sfFalse;
        change = sfTrue;
    }
    if (buttons->press == sfFalse && change == sfFalse) {
        buttons->press = sfTrue;
        edit->edit = i;
    }
}

static void is_on_button(
    sfEvent event, system_t *sys, buttons_t *buttons, edit_map_t *edit)
{
    if (event.type == sfEvtMouseButtonPressed &&
        event.mouseButton.button == sfMouseLeft) {
        for (edit_t i = 0; i < NB_EDIT; i++) {
            check_press_button(sys, buttons, edit, i);
        }
    }
}

static void dispatch_info(save_t *save, int i, int j, edit_map_t *edit)
{
    char tmp[2048] = {0};

    if (edit->draw_map->map[i][j] == EDIT_START) {
        save->info->start_pos = (sfVector2f){j * TILE_SIZE + TILE_SIZE / 2,
            i * TILE_SIZE + TILE_SIZE / 2};
        save->map[i][j] = 0;
        return;
    }
    if (edit->draw_map->map[i][j] > EDIT_START) {
        sprintf(tmp, "%d:%d:%d:0", edit->draw_map->map[i][j] - (EDIT_START + 1)
            , j * TILE_SIZE + TILE_SIZE / 2, i * TILE_SIZE + TILE_SIZE / 2);
        add_node_entity(save->entities, tmp);
        save->map[i][j] = 0;
        return;
    }
    save->map[i][j] = edit->draw_map->map[i][j];
}

static void get_info_save(save_t *save, edit_map_t *edit)
{
    empty_linked_list(save->entities, &free);
    for (int i = 0; i < save->size.y; i++) {
        for (int j = 0; j < save->size.x; j++) {
            dispatch_info(save, i, j, edit);
        }
    }
    save_map(save, "your_maps");
    edit->saving = sfTrue;
    sfClock_restart(edit->clock);
}

static void reset_edit(
    system_t *sys, edit_map_t *edit_map, state_info_t *state)
{
    state->old_scene = EDIT_MAP;
    edit_map->draw[edit_map->str].color = sfBlack;
    edit_map->str = EDIT_MAP_SAVE;
    edit_map->update = sfFalse;
    free_map(sys->save->size.y, edit_map->draw_map->map);
    empty_linked_list(edit_map->history, &free_node_history);
    empty_linked_list(sys->save->entities, &free);
    edit_map->draw_map->map = NULL;
    sfRenderWindow_setMouseCursorVisible(sys->window, sfFalse);
    edit_map->saving = sfFalse;
}

static void switch_scene(sfEvent event, system_t *sys,
    edit_map_t *edit_map, state_info_t *state)
{
    if (is_input(event, sfKeyEnter, sfTrue, 0)
        || is_input(event, sfKeyEscape, sfTrue, 7)) {
        if (is_input(event, sfKeyEscape, sfTrue, 7))
            edit_map->str = EDIT_MAP_BACK;
        if (edit_map->str == EDIT_MAP_SAVE)
            return get_info_save(sys->save, edit_map);
        if (edit_map->str == EDIT_MAP_BACK && state->old_scene == MAP)
            state->scene = state->old_scene;
        else
            state->scene = edit_map->draw[edit_map->str].scene;
        reset_edit(sys, edit_map, state);
    }
}

static void switch_str(sfEvent event, edit_map_t *edit_map)
{
    edit_map->draw[edit_map->str].color = sfBlack;
    if (is_input(event, sfKeyLeft, sfFalse, 0)
        || sfJoystick_getAxisPosition(0, sfJoystickPovY) == - MAX_JOYSTICK)
        edit_map->str = EDIT_MAP_SAVE;
    if (is_input(event, sfKeyRight, sfFalse, 0)
        || sfJoystick_getAxisPosition(0, sfJoystickPovY) == MAX_JOYSTICK)
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
        map_event(event, edit_map);
        is_on_button(event, sys, edit_map->buttons, edit_map);
    }
    mouse_click(sys, edit_map, edit_map->draw_map->coor);
    if (sys->state->fullscreen == sfFalse)
        sfConvexShape_setOutlineThickness(edit_map->draw_map->shape, 2);
    else
        sfConvexShape_setOutlineThickness(edit_map->draw_map->shape, 2);
}
