/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** event
*/

#include "game_menu.h"
#include "save.h"

static void switch_scene(sfEvent event,
    choose_t *choose, state_info_t *state)
{
    if (is_input(event, sfKeyEnter, sfTrue, 0)
        || is_input(event, sfKeyEscape, sfTrue, 7)) {
        if (is_input(event, sfKeyEscape, sfTrue, 7))
            choose->str = CHOOSE_BACK;
        state->old_scene = state->scene;
        state->scene = choose->draw[choose->str].scene;
        choose->draw[choose->str].color = sfWhite;
        choose->str = CHOOSE_LEVELS;
    }
}

static void switch_str(sfEvent event, choose_t *choose)
{
    choose->draw[choose->str].color = sfWhite;
    if (is_input(event, sfKeyUp, sfFalse, 0)
        || sfJoystick_getAxisPosition(0, sfJoystickPovY) == - MAX_JOYSTICK)
        choose->str--;
    if (is_input(event, sfKeyDown, sfFalse, 0)
        || sfJoystick_getAxisPosition(0, sfJoystickPovY) == MAX_JOYSTICK)
        choose->str++;
    if (choose->str == NB_CHOOSE)
        choose->str = CHOOSE_LEVELS;
    if (choose->str == CHOOSE_TITLE)
        choose->str = CHOOSE_BACK;
    choose->draw[choose->str].color = sfRed;
}

void choose_events(system_t *sys, choose_t *choose)
{
    sfEvent event = {0};

    while (sfRenderWindow_pollEvent(sys->window, &event)) {
        sys_events(event, sys);
        switch_str(event, choose);
        switch_scene(event, choose, sys->state);
    }
}
