/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** event
*/

#include "game_menu.h"

static void change_fps(
    sfEvent event, state_info_t *state, setting_t *setting)
{
    if (setting->str == SETTING_FPS) {
        if ((is_input(event, sfKeyRight, sfFalse, 0) ||
            sfJoystick_getAxisPosition(0, sfJoystickPovX) == - MAX_JOYSTICK)
            && state->fps < FPS_MAX)
            state->fps += FPS_GAP;
        if ((is_input(event, sfKeyLeft, sfFalse, 0) ||
            sfJoystick_getAxisPosition(0, sfJoystickPovX) == MAX_JOYSTICK)
            && state->fps > FPS_MIN)
            state->fps -= FPS_GAP;
    }
}

static void change_volume(
    sfEvent event, state_info_t *state, setting_t *setting)
{
    if (setting->str == SETTING_SOUND) {
        if ((is_input(event, sfKeyRight, sfFalse, 0) ||
            sfJoystick_getAxisPosition(0, sfJoystickPovX) == - MAX_JOYSTICK)
            && state->volume < VOL_MAX)
            state->volume += VOL_GAP;
        if ((is_input(event, sfKeyLeft, sfFalse, 0) ||
            sfJoystick_getAxisPosition(0, sfJoystickPovX) == MAX_JOYSTICK)
            && state->volume > VOL_MIN)
            state->volume -= VOL_GAP;
    }
}

static void change_window(
    system_t *sys, sfRenderWindow *new, sfBool old, state_info_t *state)
{
    if (new != NULL) {
        sfRenderWindow_close(sys->window);
        sfRenderWindow_destroy(sys->window);
        sys->window = new;
    } else
        state->fullscreen = old;
}

static void switch_screen(
    sfEvent event, system_t *sys, setting_t *settings, state_info_t *state)
{
    sfRenderWindow *new = NULL;
    sfBool old = state->fullscreen;

    if (settings->str == SETTING_FULL) {
        if (is_input(event, sfKeyLeft, sfFalse, 0)
            && state->fullscreen == sfFalse) {
            new = create_window(sfFullscreen, 1);
            state->fullscreen = sfTrue;
        }
        if (is_input(event, sfKeyRight, sfFalse, 0)
            && state->fullscreen == sfTrue) {
            new = create_window(sfTitlebar | sfClose, 0.5);
            state->fullscreen = sfFalse;
        }
        change_window(sys, new, old, state);
    }
}

static void switch_scene(
    sfEvent event, state_info_t *state, setting_t *setting)
{
    int old = state->old_scene;

    if ((is_input(event, sfKeyEnter, sfTrue, 0)
        && setting->str == SETTING_BACK)
        || is_input(event, sfKeyEscape, sfFalse, 0)) {
        state->old_scene = state->scene;
        state->scene = old;
        setting->draw[setting->str].color = sfWhite;
        setting->str = SETTING_FULL;
    }
}

static void switch_str(sfEvent event, setting_t *setting)
{
    setting->draw[setting->str].color = sfWhite;
    if (is_input(event, sfKeyUp, sfFalse, 0) ||
        sfJoystick_getAxisPosition(0, sfJoystickPovY) == - MAX_JOYSTICK)
        setting->str--;
    if (is_input(event, sfKeyDown, sfFalse, 0) ||
        sfJoystick_getAxisPosition(0, sfJoystickPovY) == MAX_JOYSTICK)
        setting->str++;
    if (setting->str == NB_SETTINGS)
        setting->str = SETTING_FPS;
    if (setting->str == SETTING_TITLE)
        setting->str = SETTING_BACK;
    setting->draw[setting->str].color = sfRed;
}

void setting_events(system_t *sys, setting_t *settings)
{
    sfEvent event = {0};

    while (sfRenderWindow_pollEvent(sys->window, &event)) {
        sys_events(event, sys);
        switch_str(event, settings);
        switch_scene(event, sys->state, settings);
        switch_screen(event, sys, settings, sys->state);
        change_volume(event, sys->state, settings);
        change_fps(event, sys->state, settings);
    }
}
