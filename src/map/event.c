/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** event
*/

#include "save.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static int load_map(select_map_t *map, system_t *sys, char *name)
{
    char *tmp = NULL;

    if (map->str != MAP_PLAY && map->str != MAP_CONTINUE)
        return SUCCESS;
    tmp = malloc(sizeof(char) * (strlen(name) + LEN_SAVE));
    if (tmp == NULL)
        return ERROR;
    if (map->str == MAP_PLAY)
        sprintf(tmp, "maps/%s.legend", name);
    if (map->str == MAP_CONTINUE)
        sprintf(tmp, "save/%s.legend", name);
    return get_save(tmp, sys->save);
}

static void switch_scene(
    sfEvent event, system_t *sys, select_map_t *map, state_info_t *state)
{
    char *tmp = NULL;

    if (is_input(event, sfKeyEnter, sfTrue, 0)) {
        tmp = strdup(sys->save->name);
        if (tmp == NULL)
            return;
        free(sys->save->name);
        if (load_map(map, sys, tmp) == ERROR) {
            sys->save->name = tmp;
            return;
        }
        state->old_scene = state->scene;
        state->scene = map->draw[map->str].scene;
        map->str = MENU_PLAY;
        map->save = sfFalse;
        map->check = sfFalse;
        free(tmp);
    }
}

static void check_continue(select_map_t *map, int prev)
{
    if (map->save == sfFalse) {
        map->draw[MAP_CONTINUE].color = GREY;
        if (map->str == MAP_CONTINUE && prev == MAP_CONTINUE - 1)
            map->str++;
        if (map->str == MAP_CONTINUE && prev == MAP_CONTINUE + 1)
            map->str--;
    }
}

static void switch_str(sfEvent event, select_map_t *map)
{
    int prev = map->str;

    map->draw[map->str].color = sfWhite;
    if (is_input(event, sfKeyUp, sfFalse, 0)
        || sfJoystick_getAxisPosition(0, sfJoystickPovY) == -100)
        map->str--;
    if (is_input(event, sfKeyDown, sfFalse, 0)
        || sfJoystick_getAxisPosition(0, sfJoystickPovY) == 100)
        map->str++;
    check_continue(map, prev);
    if (map->str == NB_MAP)
        map->str = MAP_PLAY;
    if (map->str == MAP_TITLE)
        map->str = MAP_BACK;
    map->draw[map->str].color = sfRed;
}

void map_events(system_t *sys, select_map_t *map)
{
    sfEvent event = {0};

    while (sfRenderWindow_pollEvent(sys->window, &event)) {
        sys_events(event, sys);
        switch_str(event, map);
        switch_scene(event, sys, map, sys->state);
    }
}
