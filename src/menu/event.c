/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** event
*/

#include "wolf.h"

static void switch_scene(sfEvent event, system_t *sys, menu_t *menu)
{
    if (is_keyboard_input(event, sfKeyEnter)) {
        if (str_menu[menu->str].scene == QUIT) {
            sfRenderWindow_close(sys->window);
            sfMusic_setVolume(sys->music, VOL_MIN);
        }
        sys->scene = str_menu[menu->str].scene;
    }
}

static void switch_str(sfEvent event, menu_t *menu)
{
    if (is_keyboard_input(event, sfKeyUp))
        menu->str--;
    if (is_keyboard_input(event, sfKeyDown))
        menu->str++;
    if (menu->str == NB_MENU)
        menu->str = MENU_PLAY;
    if (menu->str == MENU_TITLE)
        menu->str = MENU_QUIT;
}

void menu_events(system_t *sys, menu_t *menu)
{
    sfEvent event = {0};

    while (sfRenderWindow_pollEvent(sys->window, &event)) {
        sys_events(event, sys);
        switch_str(event, menu);
        switch_scene(event, sys, menu);
    }
}
