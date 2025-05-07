/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** event
*/

#include "save.h"
#include "linked_list.h"
#include <string.h>

static int get_map_name(maps_t *maps, system_t *sys)
{
    node_t *head = maps->info->current_file;

    if (maps->str < MAPS_SAVE1 || maps->str > MAPS_SAVE3)
        return SUCCESS;
    if (maps->str == MAPS_SAVE1)
        sys->save->name = strdup(((file_t *)head->data)->name);
    if (maps->str == MAPS_SAVE2)
        sys->save->name = strdup(((file_t *)head->next->data)->name);
    if (maps->str == MAPS_SAVE3)
        sys->save->name = strdup(((file_t *)head->next->next->data)->name);
    if (sys->save->name == NULL)
        return ERROR;
    return SUCCESS;
}

static void switch_scene(sfEvent event, maps_t *maps,
    system_t *sys, state_info_t *state)
{
    if (is_input(event, sfKeyEnter, sfTrue, 0)) {
        if (get_map_name(maps, sys) == ERROR)
            return;
        state->old_scene = state->scene;
        state->scene = maps->draw[maps->str].scene;
        free_linked_list(maps->info->list, &free_node_file);
        maps->info->list = NULL;
        maps->info->update = sfFalse;
        maps->draw[maps->str].color = sfWhite;
        maps->str = MAPS_SUB;
    }
    if (is_input(event, sfKeyEscape, sfFalse, 0)) {
        state->old_scene = state->scene;
        state->scene = maps->draw[MAPS_BACK].scene;
        free_linked_list(maps->info->list, &free_node_file);
        maps->info->list = NULL;
        maps->info->update = sfFalse;
        maps->draw[maps->str].color = sfWhite;
        maps->str = MAPS_SUB;
    }
}

static void check_save_minus(maps_t *maps)
{
    node_t *head = maps->info->current_file;
    int tmp = MAPS_SUB;

    if (tmp == MAPS_SUB && head != NULL)
        tmp++;
    if (tmp == MAPS_SAVE1 && head->next != NULL)
        tmp++;
    if (tmp == MAPS_SAVE2 && head->next->next != NULL)
        tmp++;
    if (maps->str > tmp && maps->str < MAPS_BACK)
        maps->str = tmp;
}

static void check_save_plus(maps_t *maps)
{
    node_t *head = maps->info->current_file;

    if (maps->str == MAPS_SAVE1 && head == NULL)
        maps->str = MAPS_BACK;
    if (maps->str == MAPS_SAVE2 && head->next == NULL)
        maps->str = MAPS_BACK;
    if (maps->str == MAPS_SAVE3 && head->next->next == NULL)
        maps->str = MAPS_BACK;
}

static void switch_str(sfEvent event, maps_t *maps)
{
    maps->draw[maps->str].color = sfWhite;
    if (is_input(event, sfKeyUp, sfFalse, 0) ||
        sfJoystick_getAxisPosition(0, sfJoystickPovY) == - MAX_JOYSTICK) {
        maps->str--;
        check_save_minus(maps);
    }
    if (is_input(event, sfKeyDown, sfFalse, 0) ||
        sfJoystick_getAxisPosition(0, sfJoystickPovY) == MAX_JOYSTICK) {
        maps->str++;
        check_save_plus(maps);
    }
    if (maps->str == NB_MAPS)
        maps->str = MAPS_SUB;
    if (maps->str == MAPS_TITLE)
        maps->str = MAPS_BACK;
    maps->draw[maps->str].color = sfRed;
}

static sfBool move_right(info_save_t *info)
{
    if (info->file / NB_SHOW_SAVE + 1 < info->nb_page)
        return true;
    return false;
}

static void change_map(sfEvent event, maps_t *maps)
{
    if (maps->str == MAPS_SUB) {
        if (is_input(event, sfKeyRight, sfFalse, 0)
            && move_right(maps->info) == sfTrue) {
            maps->info->file += NB_SHOW_SAVE;
            maps->info->current_file =
                maps->info->current_file->next->next->next;
        }
        if (is_input(event, sfKeyLeft, sfFalse, 0)
            && maps->info->file > 0) {
            maps->info->file -= NB_SHOW_SAVE;
            maps->info->current_file =
                maps->info->current_file->prev->prev->prev;
        }
    }
}

void maps_events(system_t *sys, maps_t *maps)
{
    sfEvent event = {0};

    while (sfRenderWindow_pollEvent(sys->window, &event)) {
        sys_events(event, sys);
        switch_str(event, maps);
        switch_scene(event, maps, sys, sys->state);
        change_map(event, maps);
    }
}
