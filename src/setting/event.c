/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** event
*/

#include "wolf.h"

static void change_volume(
    sfEvent event, state_info_t *state, setting_t *setting)
{
    if (setting->str == SETTING_SOUND) {
        if (is_keyboard_input(event, sfKeyRight) && state->volume < VOL_MAX)
            state->volume += VOL_GAP;
        if (is_keyboard_input(event, sfKeyLeft) && state->volume > VOL_MIN)
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
    sfEvent event, system_t *sys, setting_t *setting, state_info_t *state)
{
    sfRenderWindow *new = NULL;
    sfBool old = state->fullscreen;

    if (setting->str == SETTING_FULL) {
        if (is_keyboard_input(event, sfKeyLeft)
            && state->fullscreen == sfFalse) {
            new = create_window(sfFullscreen, 1);
            state->fullscreen = sfTrue;
        }
        if (is_keyboard_input(event, sfKeyRight)
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

    if (is_keyboard_input(event, sfKeyEnter) && setting->str == SETTING_BACK) {
        state->old_scene = state->scene;
        state->scene = old;
    }
}

static void switch_str(sfEvent event, setting_t *setting)
{
    setting->draw[setting->str].color = sfWhite;
    if (is_keyboard_input(event, sfKeyUp))
        setting->str--;
    if (is_keyboard_input(event, sfKeyDown))
        setting->str++;
    if (setting->str == NB_SETTING)
        setting->str = SETTING_FULL;
    if (setting->str == SETTING_TITLE)
        setting->str = SETTING_BACK;
    setting->draw[setting->str].color = sfRed;
}

void setting_events(system_t *sys, setting_t *setting)
{
    sfEvent event = {0};

    while (sfRenderWindow_pollEvent(sys->window, &event)) {
        sys_events(event, sys);
        switch_str(event, setting);
        switch_scene(event, sys->state, setting);
        switch_screen(event, sys, setting, sys->state);
        change_volume(event, sys->state, setting);
    }
}
