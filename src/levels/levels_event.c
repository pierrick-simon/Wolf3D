/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** event
*/

#include "save.h"
#include "linked_list.h"

static int load_map(normal_map_t *normal_map, system_t *sys)
{
    int return_value = SUCCESS;
    node_t *head = normal_map->info->current_file;

    if (normal_map->str == NOR_MAP_SAVE1)
        return_value = get_save(((file_t *)head->data)->path, sys->save);
    if (normal_map->str == NOR_MAP_SAVE2)
        return_value = get_save(((file_t *)head->next->data)->path, sys->save);
    if (normal_map->str == NOR_MAP_SAVE3)
        return_value = get_save(
            ((file_t *)head->next->next->data)->path, sys->save);
    return return_value;
}

static void switch_scene(sfEvent event, normal_map_t *normal_map,
    system_t *sys, state_info_t *state)
{
    if (is_input(event, sfKeyEnter, sfTrue, 0)) {
        if (load_map(normal_map, sys) == ERROR)
            return;
        state->old_scene = state->scene;
        state->scene = normal_map->draw[normal_map->str].scene;
        free_linked_list(normal_map->info->list, &free_node_file);
        normal_map->info->list = NULL;
        normal_map->info->update = sfFalse;
    }
}

static void check_save_minus(normal_map_t *normal_map)
{
    node_t *head = normal_map->info->current_file;
    int tmp = NOR_MAP_SUB;

    if (tmp == NOR_MAP_SUB && head != NULL)
        tmp++;
    if (tmp == NOR_MAP_SAVE1 && head->next != NULL)
        tmp++;
    if (tmp == NOR_MAP_SAVE2 && head->next->next != NULL)
        tmp++;
    if (normal_map->str > tmp && normal_map->str < NOR_MAP_BACK)
        normal_map->str = tmp;
}

static void check_save_plus(normal_map_t *normal_map)
{
    node_t *head = normal_map->info->current_file;

    if (normal_map->str == NOR_MAP_SAVE1 && head == NULL)
        normal_map->str = NOR_MAP_BACK;
    if (normal_map->str == NOR_MAP_SAVE2 && head->next == NULL)
        normal_map->str = NOR_MAP_BACK;
    if (normal_map->str == NOR_MAP_SAVE3 && head->next->next == NULL)
        normal_map->str = NOR_MAP_BACK;
}

static void switch_str(sfEvent event, normal_map_t *normal_map)
{
    normal_map->draw[normal_map->str].color = sfWhite;
    if (is_input(event, sfKeyUp, sfFalse, 0) ||
        sfJoystick_getAxisPosition(0, sfJoystickPovY) == -100) {
        normal_map->str--;
        check_save_minus(normal_map);
    }
    if (is_input(event, sfKeyDown, sfFalse, 0) ||
        sfJoystick_getAxisPosition(0, sfJoystickPovY) == 100) {
        normal_map->str++;
        check_save_plus(normal_map);
    }
    if (normal_map->str == NB_NOR_MAP)
        normal_map->str = NOR_MAP_SUB;
    if (normal_map->str == NOR_MAP_TITLE)
        normal_map->str = NOR_MAP_BACK;
    normal_map->draw[normal_map->str].color = sfRed;
}

static sfBool move_right(info_save_t *info)
{
    if (info->file / NB_SHOW_SAVE + 1 < info->nb_page)
        return true;
    return false;
}

static void change_map(sfEvent event, normal_map_t *normal_map)
{
    if (normal_map->str == NOR_MAP_SUB) {
        if (is_input(event, sfKeyRight, sfFalse, 0)
            && move_right(normal_map->info) == sfTrue) {
            normal_map->info->file += NB_SHOW_SAVE;
            normal_map->info->current_file =
                normal_map->info->current_file->next->next->next;
        }
        if (is_input(event, sfKeyLeft, sfFalse, 0)
            && normal_map->info->file > 0) {
            normal_map->info->file -= NB_SHOW_SAVE;
            normal_map->info->current_file =
                normal_map->info->current_file->prev->prev->prev;
        }
    }
}

void levels_events(system_t *sys, normal_map_t *normal_map)
{
    sfEvent event = {0};

    while (sfRenderWindow_pollEvent(sys->window, &event)) {
        sys_events(event, sys);
        switch_str(event, normal_map);
        switch_scene(event, normal_map, sys, sys->state);
        change_map(event, normal_map);
    }
}
