/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** event
*/

#include "quit.h"
#include "save.h"

static void switch_scene(
    sfEvent event, system_t *sys, leave_t *leave, state_info_t *state)
{
    int tmp = state->old_scene;

    if (is_input(event, sfKeyEnter, sfTrue, 0)
        || is_input(event, sfKeyEscape, sfTrue, 7)) {
        if (is_input(event, sfKeyEscape, sfTrue, 7))
            leave->str = LEAVE_SAVE;
        if (leave->str == LEAVE_CANCEL) {
            state->old_scene = state->scene;
            state->scene = tmp;
            leave->draw[leave->str].color = sfWhite;
            leave->str = LEAVE_SAVE;
            return;
        }
        if (leave->str == LEAVE_SAVE)
            save_map(sys->save, "save");
        state->old_scene = state->scene;
        state->scene = leave->draw[leave->str].scene;
        leave->draw[leave->str].color = sfWhite;
        leave->str = LEAVE_SAVE;
    }
}

static void switch_str(sfEvent event, leave_t *leave)
{
    leave->draw[leave->str].color = sfWhite;
    if (is_input(event, sfKeyUp, sfFalse, 0)
        || sfJoystick_getAxisPosition(0, sfJoystickPovY) == - MAX_JOYSTICK)
        leave->str--;
    if (is_input(event, sfKeyDown, sfFalse, 0)
        || sfJoystick_getAxisPosition(0, sfJoystickPovY) == MAX_JOYSTICK)
        leave->str++;
    if (leave->str == NB_LEAVE)
        leave->str = LEAVE_SAVE;
    if (leave->str == LEAVE_TITLE)
        leave->str = LEAVE_CANCEL;
    leave->draw[leave->str].color = sfRed;
}

void leave_events(system_t *sys, leave_t *leave)
{
    sfEvent event = {0};

    while (sfRenderWindow_pollEvent(sys->window, &event)) {
        sys_events(event, sys);
        switch_str(event, leave);
        switch_scene(event, sys, leave, sys->state);
    }
}
