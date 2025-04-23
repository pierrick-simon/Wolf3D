/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** event
*/

#include "wolf.h"

static void switch_scene(
    sfEvent event, normal_map_t *normal_map, state_info_t *state)
{
    if (is_keyboard_input(event, sfKeyEnter)) {
        state->old_scene = state->scene;
        state->scene = normal_map->draw[normal_map->str].scene;
    }
}

static void switch_str(sfEvent event, normal_map_t *normal_map)
{
    normal_map->draw[normal_map->str].color = sfWhite;
    if (is_keyboard_input(event, sfKeyUp))
        normal_map->str--;
    if (is_keyboard_input(event, sfKeyDown))
        normal_map->str++;
    if (normal_map->str == NB_NOR_MAP)
        normal_map->str = NOR_MAP_MAP1;
    if (normal_map->str == NOR_MAP_TITLE)
        normal_map->str = NOR_MAP_BACK;
    normal_map->draw[normal_map->str].color = sfRed;
}

void normal_map_events(system_t *sys, normal_map_t *normal_map)
{
    sfEvent event = {0};

    while (sfRenderWindow_pollEvent(sys->window, &event)) {
        sys_events(event, sys);
        switch_str(event, normal_map);
        switch_scene(event, normal_map, sys->state);
    }
}
