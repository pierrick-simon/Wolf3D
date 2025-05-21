/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** event
*/

#include "game_menu.h"

static void switch_scene(
    sfEvent event, system_t *sys, menu_t *menu, state_info_t *state)
{
    if (is_input(event, sfKeyEnter, sfTrue, 0)) {
        if (menu->draw[menu->str].scene == QUIT) {
            sfRenderWindow_close(sys->window);
            sfMusic_setVolume(sys->music, VOL_MIN);
        }
        state->old_scene = state->scene;
        state->scene = menu->draw[menu->str].scene;
        menu->draw[menu->str].color = sfWhite;
        menu->str = MENU_PLAY;
    }
}

static void switch_str(sfEvent event, menu_t *menu)
{
    menu->draw[menu->str].color = sfWhite;
    if (is_input(event, sfKeyUp, sfFalse, 0)
        || sfJoystick_getAxisPosition(0, sfJoystickPovY) == - MAX_JOYSTICK)
        menu->str--;
    if (is_input(event, sfKeyDown, sfFalse, 0)
        || sfJoystick_getAxisPosition(0, sfJoystickPovY) == MAX_JOYSTICK)
        menu->str++;
    if (menu->str == NB_MENU)
        menu->str = MENU_PLAY;
    if (menu->str == MENU_TITLE)
        menu->str = MENU_QUIT;
    menu->draw[menu->str].color = sfRed;
}

void menu_events(system_t *sys, menu_t *menu)
{
    sfEvent event = {0};

    while (sfRenderWindow_pollEvent(sys->window, &event)) {
        sys_events(event, sys);
        switch_str(event, menu);
        switch_scene(event, sys, menu, sys->state);
    }
}
