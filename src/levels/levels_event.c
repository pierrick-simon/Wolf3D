/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** event
*/

#include "save.h"
#include "linked_list.h"
#include <string.h>

static int get_map_name(levels_t *levels, system_t *sys)
{
    node_t *head = levels->info->current_file;

    if (levels->str < LEVELS_SAVE1 || levels->str > LEVELS_SAVE3)
        return SUCCESS;
    if (levels->str == LEVELS_SAVE1)
        sys->save->name = strdup(((file_t *)head->data)->name);
    if (levels->str == LEVELS_SAVE2)
        sys->save->name = strdup(((file_t *)head->next->data)->name);
    if (levels->str == LEVELS_SAVE3)
        sys->save->name = strdup(((file_t *)head->next->next->data)->name);
    if (sys->save->name == NULL)
        return ERROR;
    return SUCCESS;
}

static void switch_scene(sfEvent event, levels_t *levels,
    system_t *sys, state_info_t *state)
{
    if (is_input(event, sfKeyEnter, sfTrue, 0)) {
        if (get_map_name(levels, sys) == ERROR)
            return;
        state->old_scene = state->scene;
        state->scene = levels->draw[levels->str].scene;
        free_linked_list(levels->info->list, &free_node_file);
        levels->info->list = NULL;
        levels->info->update = sfFalse;
        levels->draw[levels->str].color = sfWhite;
        levels->str = LEVELS_SUB;
    }
    if (is_input(event, sfKeyEscape, sfTrue, 7)) {
        state->old_scene = state->scene;
        state->scene = levels->draw[LEVELS_BACK].scene;
        free_linked_list(levels->info->list, &free_node_file);
        levels->info->list = NULL;
        levels->info->update = sfFalse;
        levels->draw[levels->str].color = sfWhite;
        levels->str = LEVELS_SUB;
    }
}

static void check_save_minus(levels_t *levels)
{
    node_t *head = levels->info->current_file;
    int tmp = LEVELS_SUB;

    if (tmp == LEVELS_SUB && head != NULL)
        tmp++;
    if (tmp == LEVELS_SAVE1 && head->next != NULL)
        tmp++;
    if (tmp == LEVELS_SAVE2 && head->next->next != NULL)
        tmp++;
    if (levels->str > tmp && levels->str < LEVELS_BACK)
        levels->str = tmp;
}

static void check_save_plus(levels_t *levels)
{
    node_t *head = levels->info->current_file;

    if (levels->str == LEVELS_SAVE1 && head == NULL)
        levels->str = LEVELS_BACK;
    if (levels->str == LEVELS_SAVE2 && head->next == NULL)
        levels->str = LEVELS_BACK;
    if (levels->str == LEVELS_SAVE3 && head->next->next == NULL)
        levels->str = LEVELS_BACK;
}

static void switch_str(sfEvent event, levels_t *levels)
{
    levels->draw[levels->str].color = sfWhite;
    if (is_input(event, sfKeyUp, sfFalse, 0) ||
        sfJoystick_getAxisPosition(0, sfJoystickPovY) == - MAX_JOYSTICK) {
        levels->str--;
        check_save_minus(levels);
    }
    if (is_input(event, sfKeyDown, sfFalse, 0) ||
        sfJoystick_getAxisPosition(0, sfJoystickPovY) == MAX_JOYSTICK) {
        levels->str++;
        check_save_plus(levels);
    }
    if (levels->str == NB_LEVELS)
        levels->str = LEVELS_SUB;
    if (levels->str == LEVELS_TITLE)
        levels->str = LEVELS_BACK;
    levels->draw[levels->str].color = sfRed;
}

static sfBool move_right(info_save_t *info)
{
    if (info->file / NB_SHOW_SAVE + 1 < info->nb_page)
        return true;
    return false;
}

static void move_map(sfEvent event, levels_t *levels)
{
    float x = sfJoystick_getAxisPosition(0, sfJoystickPovX);

    if ((is_input(event, sfKeyRight, sfTrue, 5) || x == MAX_JOYSTICK)
        && move_right(levels->info) == sfTrue) {
        levels->info->file += NB_SHOW_SAVE;
        levels->info->current_file =
            levels->info->current_file->next->next->next;
        levels->draw[levels->str].color = sfWhite;
        levels->str = LEVELS_SUB;
    }
    if ((is_input(event, sfKeyLeft, sfTrue, 6) || x == - MAX_JOYSTICK)
        && levels->info->file > 0) {
        levels->info->file -= NB_SHOW_SAVE;
        levels->info->current_file =
            levels->info->current_file->prev->prev->prev;
        levels->draw[levels->str].color = sfWhite;
        levels->str = LEVELS_SUB;
    }
}

static void change_map(sfEvent event, levels_t *levels)
{
    if (levels->str >= LEVELS_SUB && levels->str <= LEVELS_SAVE3) {
        move_map(event, levels);
        levels->draw[levels->str].color = sfRed;
    }
}

void levels_events(system_t *sys, levels_t *levels)
{
    sfEvent event = {0};

    while (sfRenderWindow_pollEvent(sys->window, &event)) {
        sys_events(event, sys);
        switch_str(event, levels);
        switch_scene(event, levels, sys, sys->state);
        change_map(event, levels);
    }
}
