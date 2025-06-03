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

static void check_press_button(
    system_t *sys, buttons_t *buttons, edit_map_t *edit, edit_t i)
{
    sfBool change = sfFalse;
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(sys->window);

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
        event.mouseButton.button == sfMouseLeft){
        for (edit_t i = 0; i < NB_EDIT; i++) {
            check_press_button(sys, buttons, edit, i);
        }
    }
}

static void dispatch_info(save_t *save, int i, int j, edit_map_t *edit)
{
    char tmp[2048];

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
    for (int i = 0; i < save->size.y; i++) {
        for (int j = 0; j < save->size.x; j++) {
            dispatch_info(save, i, j, edit);
        }
    }
    save_map(save, "your_maps");
    empty_linked_list(save->entities, &free);
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
        state->old_scene = state->scene;
        state->scene = edit_map->draw[edit_map->str].scene;
        edit_map->draw[edit_map->str].color = sfBlack;
        edit_map->str = EDIT_MAP_SAVE;
        edit_map->update = sfFalse;
        free_map(sys->save->size.y, edit_map->draw_map->map);
        empty_linked_list(edit_map->history, &free_node_history);
        edit_map->draw_map->map = NULL;
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
    if (edit_map->str == EDIT_MAP_ITEM)
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
}
