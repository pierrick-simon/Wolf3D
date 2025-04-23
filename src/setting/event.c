/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** event
*/

#include "wolf.h"

void switch_scene(sfEvent event, system_t *sys, setting_t *setting)
{
    if (is_input(event, sfKeyEnter, sfTrue, 0) &&
        setting->str == SETTING_BACK) {
        sys->scene = str_setting[setting->str].scene;
    }
}

static void switch_str(sfEvent event, setting_t *setting)
{
    if (is_input(event, sfKeyUp, sfFalse, 0) ||
        sfJoystick_getAxisPosition(0, sfJoystickPovY) == -100)
        setting->str--;
    if (is_input(event, sfKeyDown, sfFalse, 0) ||
        sfJoystick_getAxisPosition(0, sfJoystickPovY) == 100)
        setting->str++;
    if (setting->str == NB_MENU)
        setting->str = SETTING_FULL;
    if (setting->str == SETTING_TITLE)
        setting->str = SETTING_BACK;
}

void setting_events(system_t *sys, setting_t *setting)
{
    sfEvent event = {0};

    while (sfRenderWindow_pollEvent(sys->window, &event)) {
        sys_events(event, sys);
        switch_str(event, setting);
        switch_scene(event, sys, setting);
    }
}
