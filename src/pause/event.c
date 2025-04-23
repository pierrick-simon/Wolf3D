/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** event
*/

#include "wolf.h"

static void switch_scene(sfEvent event, state_info_t *state, pause_t *pause)
{
    if (is_input(event, sfKeyEnter, sfTrue, 0)) {
        state->old_scene = state->scene;
        state->scene = pause->draw[pause->str].scene;
    }
    if (is_input(event, sfKeyTab, sfTrue, 3)) {
        state->old_scene = state->scene;
        state->scene = GAME;
    }
}

static void switch_str(sfEvent event, pause_t *pause)
{
    pause->draw[pause->str].color = sfWhite;
    if (is_input(event, sfKeyUp, sfFalse, 0)
        || sfJoystick_getAxisPosition(0, sfJoystickPovY) == -100)
        pause->str--;
    if (is_input(event, sfKeyDown, sfFalse, 0)
        || sfJoystick_getAxisPosition(0, sfJoystickPovY) == 100)
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
        switch_scene(event, sys->state, pause);
    }
}
