/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** event
*/

#include "wolf.h"

void switch_screen(sfEvent event, system_t *sys, setting_t *setting)
{
    sfRenderWindow *new = NULL;
    sfBool old = sys->fullscreen;

    if (setting->str == SETTING_FULL) {
        if (is_keyboard_input(event, sfKeyRight)
            && sys->fullscreen == sfFalse) {
            new = create_window(sfFullscreen, 1);
            sys->fullscreen = sfTrue;
        }
        if (is_keyboard_input(event, sfKeyLeft) && sys->fullscreen == sfTrue) {
            new = create_window(sfTitlebar | sfClose, 0.5);
            sys->fullscreen = sfFalse;
        }
        if (new != NULL) {
            sfRenderWindow_close(sys->window);
            sfRenderWindow_destroy(sys->window);
            sys->window = new;
        } else
            sys->fullscreen = old;
    }
}

void switch_scene(sfEvent event, system_t *sys, setting_t *setting)
{
    if (is_keyboard_input(event, sfKeyEnter) && setting->str == SETTING_BACK) {
        sys->scene = setting->draw[setting->str].scene;
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
        switch_scene(event, sys, setting);
        switch_screen(event, sys, setting);
    }
}
