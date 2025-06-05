/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** event
*/

#include "save.h"
#include "linked_list.h"
#include <string.h>

static int get_map_name(levels_t *your_maps, system_t *sys)
{
    node_t *head = your_maps->info->current_file;

    if (your_maps->str == LEVELS_SUB)
        return ERROR;
    if (your_maps->str < LEVELS_SAVE1 || your_maps->str > LEVELS_SAVE3)
        return SUCCESS;
    if (your_maps->str == LEVELS_SAVE1)
        sys->save->name = strdup(((file_t *)head->data)->name);
    if (your_maps->str == LEVELS_SAVE2)
        sys->save->name = strdup(((file_t *)head->next->data)->name);
    if (your_maps->str == LEVELS_SAVE3)
        sys->save->name = strdup(((file_t *)head->next->next->data)->name);
    if (sys->save->name == NULL)
        return ERROR;
    return SUCCESS;
}

static void switch_scene(sfEvent event, levels_t *your_maps,
    system_t *sys, state_info_t *state)
{
    if (is_input(event, sfKeyEnter, sfTrue, 0)) {
        if (get_map_name(your_maps, sys) == ERROR)
            return;
        state->old_scene = state->scene;
        state->scene = your_maps->draw[your_maps->str].scene;
        free_linked_list(your_maps->info->list, &free_node_file);
        your_maps->info->list = NULL;
        your_maps->info->update = sfFalse;
        your_maps->draw[your_maps->str].color = sfWhite;
        your_maps->str = LEVELS_SUB;
    }
    if (is_input(event, sfKeyEscape, sfTrue, 7)) {
        state->old_scene = state->scene;
        state->scene = your_maps->draw[LEVELS_BACK].scene;
        free_linked_list(your_maps->info->list, &free_node_file);
        your_maps->info->list = NULL;
        your_maps->info->update = sfFalse;
        your_maps->draw[your_maps->str].color = sfWhite;
        your_maps->str = LEVELS_SUB;
    }
}

static void check_save_minus(levels_t *your_maps)
{
    node_t *head = your_maps->info->current_file;
    int tmp = LEVELS_SUB;

    if (tmp == LEVELS_SUB && head != NULL)
        tmp++;
    if (tmp == LEVELS_SAVE1 && head->next != NULL)
        tmp++;
    if (tmp == LEVELS_SAVE2 && head->next->next != NULL)
        tmp++;
    if (your_maps->str > tmp && your_maps->str < LEVELS_BACK)
        your_maps->str = tmp;
}

static void check_save_plus(levels_t *your_maps)
{
    node_t *head = your_maps->info->current_file;

    if (your_maps->str == LEVELS_SAVE1 && head == NULL)
        your_maps->str = LEVELS_BACK;
    if (your_maps->str == LEVELS_SAVE2 && head->next == NULL)
        your_maps->str = LEVELS_BACK;
    if (your_maps->str == LEVELS_SAVE3 && head->next->next == NULL)
        your_maps->str = LEVELS_BACK;
}

static void switch_str(sfEvent event, levels_t *your_maps)
{
    your_maps->draw[your_maps->str].color = sfWhite;
    if (is_input(event, sfKeyUp, sfFalse, 0) ||
        sfJoystick_getAxisPosition(0, sfJoystickPovY) == - MAX_JOYSTICK) {
        your_maps->str--;
        check_save_minus(your_maps);
    }
    if (is_input(event, sfKeyDown, sfFalse, 0) ||
        sfJoystick_getAxisPosition(0, sfJoystickPovY) == MAX_JOYSTICK) {
        your_maps->str++;
        check_save_plus(your_maps);
    }
    if (your_maps->str == NB_LEVELS)
        your_maps->str = LEVELS_SUB;
    if (your_maps->str == LEVELS_TITLE)
        your_maps->str = LEVELS_BACK;
    your_maps->draw[your_maps->str].color = sfRed;
}

static sfBool move_right(info_save_t *info)
{
    if (info->file / NB_SHOW_SAVE + 1 < info->nb_page)
        return true;
    return false;
}

static void move_map(sfEvent event, levels_t *your_maps)
{
    float x = sfJoystick_getAxisPosition(0, sfJoystickPovX);

    if ((is_input(event, sfKeyRight, sfTrue, 5) || x == MAX_JOYSTICK)
        && move_right(your_maps->info) == sfTrue) {
        your_maps->info->file += NB_SHOW_SAVE;
        your_maps->info->current_file =
            your_maps->info->current_file->next->next->next;
        your_maps->draw[your_maps->str].color = sfWhite;
        your_maps->str = LEVELS_SUB;
    }
    if ((is_input(event, sfKeyLeft, sfTrue, 6) || x == - MAX_JOYSTICK)
        && your_maps->info->file > 0) {
        your_maps->info->file -= NB_SHOW_SAVE;
        your_maps->info->current_file =
            your_maps->info->current_file->prev->prev->prev;
        your_maps->draw[your_maps->str].color = sfWhite;
        your_maps->str = LEVELS_SUB;
    }
}

static void change_map(sfEvent event, levels_t *your_maps)
{
    if (your_maps->str >= LEVELS_SUB && your_maps->str <= LEVELS_SAVE3) {
        move_map(event, your_maps);
        your_maps->draw[your_maps->str].color = sfRed;
    }
}

void your_maps_events(system_t *sys, levels_t *your_maps)
{
    sfEvent event = {0};

    while (sfRenderWindow_pollEvent(sys->window, &event)) {
        sys_events(event, sys);
        switch_str(event, your_maps);
        switch_scene(event, your_maps, sys, sys->state);
        change_map(event, your_maps);
    }
}
