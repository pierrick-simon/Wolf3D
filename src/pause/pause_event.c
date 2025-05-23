/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** event
*/

#include "save.h"
#include "game_menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int load_restart(pause_t *pause, system_t *sys,
    char *name, float difficulty)
{
    char *tmp = NULL;
    int exit = SUCCESS;

    if (pause->str != PAUSE_RESTART)
        return SUCCESS;
    tmp = malloc(sizeof(char) * (strlen(name) + LEN_SAVE));
    if (tmp == NULL)
        return ERROR;
    sprintf(tmp, "maps/%s.legend", name);
    exit = get_save(tmp, sys->save);
    sys->save->info->difficulty = difficulty;
    free(tmp);
    return exit;
}

static void switch_scene(
    sfEvent event, state_info_t *state, pause_t *pause, system_t *sys)
{
    if (is_input(event, sfKeyEnter, sfTrue, 0)) {
        state->old_scene = state->scene;
        if (load_restart(pause, sys, sys->save->name,
            sys->save->info->difficulty) == ERROR)
            state->scene = MAPS;
        else
            state->scene = pause->draw[pause->str].scene;
        pause->draw[pause->str].color = sfWhite;
        pause->str = PAUSE_RESUME;
    }
    if (is_input(event, sfKeyEscape, sfTrue, 7)) {
        state->old_scene = state->scene;
        state->scene = GAME;
        pause->draw[pause->str].color = sfWhite;
        pause->str = PAUSE_RESUME;
    }
}

static void switch_str(sfEvent event, pause_t *pause)
{
    pause->draw[pause->str].color = sfWhite;
    if (is_input(event, sfKeyUp, sfFalse, 0)
        || sfJoystick_getAxisPosition(0, sfJoystickPovY) == - MAX_JOYSTICK)
        pause->str--;
    if (is_input(event, sfKeyDown, sfFalse, 0)
        || sfJoystick_getAxisPosition(0, sfJoystickPovY) == MAX_JOYSTICK)
        pause->str++;
    if (pause->str == NB_PAUSE)
        pause->str = PAUSE_RESUME;
    if (pause->str == PAUSE_TITLE)
        pause->str = PAUSE_BACK;
    pause->draw[pause->str].color = sfRed;
}

void pause_events(system_t *sys, pause_t *pause)
{
    sfEvent event = {0};

    while (sfRenderWindow_pollEvent(sys->window, &event)) {
        sys_events(event, sys);
        switch_str(event, pause);
        switch_scene(event, sys->state, pause, sys);
    }
}
