/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** event
*/

#include "quit.h"
#include "save.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static int load_restart(lose_t *lose, system_t *sys, char *name)
{
    char *tmp = NULL;
    int exit = SUCCESS;

    if (lose->str != LOSE_RESTART)
        return SUCCESS;
    tmp = malloc(sizeof(char) * (strlen(name) + LEN_SAVE));
    if (tmp == NULL)
        return ERROR;
    sprintf(tmp, "maps/%s.legend", name);
    exit = get_save(tmp, sys->save);
    free(tmp);
    return exit;
}

static void switch_scene(
    sfEvent event, system_t *sys, lose_t *lose, state_info_t *state)
{
    if (is_input(event, sfKeyEnter, sfTrue, 0)
        || is_input(event, sfKeyEscape, sfTrue, 7)) {
        if (is_input(event, sfKeyEscape, sfTrue, 7))
            lose->str = LOSE_MENU;
        state->old_scene = state->scene;
        if (load_restart(lose, sys, sys->save->name) == ERROR)
            state->scene = MAPS;
        else
            state->scene = lose->draw[lose->str].scene;
        state->scene = lose->draw[lose->str].scene;
        lose->draw[lose->str].color = sfWhite;
        lose->str = LOSE_RESTART;
        lose->draw[lose->str].color = sfRed;
        lose->update = sfFalse;
    }
}

static void switch_str(sfEvent event, lose_t *lose)
{
    lose->draw[lose->str].color = sfWhite;
    if (is_input(event, sfKeyUp, sfFalse, 0)
        || sfJoystick_getAxisPosition(0, sfJoystickPovY) == - MAX_JOYSTICK)
        lose->str--;
    if (is_input(event, sfKeyDown, sfFalse, 0)
        || sfJoystick_getAxisPosition(0, sfJoystickPovY) == MAX_JOYSTICK)
        lose->str++;
    if (lose->str == NB_LOSE)
        lose->str = LOSE_RESTART;
    if (lose->str == LOSE_SCORE)
        lose->str = LOSE_MENU;
    lose->draw[lose->str].color = sfRed;
}

void lose_events(system_t *sys, lose_t *lose)
{
    sfEvent event = {0};

    while (sfRenderWindow_pollEvent(sys->window, &event)) {
        sys_events(event, sys);
        switch_str(event, lose);
        switch_scene(event, sys, lose, sys->state);
    }
}
