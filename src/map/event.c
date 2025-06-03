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
    int exit = SUCCESS;

    if (map->str != MAP_PLAY && map->str != MAP_CONTINUE
        && map->str != MAP_EDIT)
        return SUCCESS;
    tmp = malloc(sizeof(char) * (strlen(name) + LEN_SAVE + strlen(sys->dir)));
    if (tmp == NULL)
        return ERROR;
    if (map->str == MAP_PLAY || map->str == MAP_EDIT)
        sprintf(tmp, "%s/%s.legend", sys->dir, name);
    if (map->str == MAP_CONTINUE)
        sprintf(tmp, "save/%s.legend", name);
    exit = get_save(tmp, sys->save);
    free(tmp);
    return exit;
}

static void reset_str(select_map_t *map, state_info_t *state, str_map_t id)
{
    state->old_scene = state->scene;
    state->scene = map->draw[id].scene;
    map->draw[map->str].color = sfWhite;
    map->str = MAP_PLAY;
    map->save = sfFalse;
    map->check = sfFalse;
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
        sys->save->name = NULL;
        if (load_map(map, sys, tmp) == ERROR) {
            sys->save->name = tmp;
            return;
        }
        if (map->str == MAP_SCORE)
            sys->save->name = tmp;
        if (map->str != MAP_SCORE)
            free(tmp);
        reset_str(map, state, map->str);
    }
    if (is_input(event, sfKeyEscape, sfTrue, 7))
        reset_str(map, state, MAP_BACK);
}

static void check_continue(select_map_t *map, int prev)
{
    if (map->save == sfFalse) {
        if (map->str == MAP_CONTINUE && prev == MAP_CONTINUE - 1)
            map->str++;
        if (map->str == MAP_CONTINUE && prev == MAP_CONTINUE + 1)
            map->str--;
    }
    if (map->edit == sfFalse) {
        if (map->str == MAP_EDIT && prev == MAP_EDIT - 1)
            map->str++;
        if (map->str == MAP_EDIT && prev == MAP_EDIT + 1)
            map->str--;
    }
}

static void switch_str(sfEvent event, select_map_t *map)
{
    int prev = map->str;

    map->draw[map->str].color = sfWhite;
    if (is_input(event, sfKeyUp, sfFalse, 0)
        || sfJoystick_getAxisPosition(0, sfJoystickPovY) == - MAX_JOYSTICK)
        map->str--;
    if (is_input(event, sfKeyDown, sfFalse, 0)
        || sfJoystick_getAxisPosition(0, sfJoystickPovY) == MAX_JOYSTICK)
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
