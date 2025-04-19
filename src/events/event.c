/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** event
*/

#include "wolf.h"

static void change_scene(sfEvent event, system_t *sys)
{
    if (is_keyboard_input(event, sfKeyTab)) {
        if (sys->scene == MENU) {
            sys->scene = GAME;
            return;
        }
        if (sys->scene == GAME) {
            sys->scene = MENU;
            return;
        }
    }
}

static void music_setvolume(sfEvent event, system_t *sys)
{
    if (is_keyboard_input(event, sfKeyF1)) {
        if (sys->volume < 1)
            sys->volume = VOL_MAX;
        else
            sys->volume = VOL_MIN;
    }
    if (is_keyboard_input(event, sfKeyF2)) {
        if (sys->volume > VOL_MIN + VOL_GAP)
            sys->volume -= VOL_GAP;
        else
            sys->volume = 0.0;
    }
    if (is_keyboard_input(event, sfKeyF3) && sys->volume < VOL_MAX - VOL_GAP)
        sys->volume += VOL_GAP;
    sfMusic_setVolume(sys->music, sys->volume);
}

static void close_window(sfEvent event, system_t *sys)
{
    if (is_keyboard_input(event, sfKeyEscape) || event.type == sfEvtClosed) {
        sfRenderWindow_close(sys->window);
        sfMusic_setVolume(sys->music, VOL_MIN);
    }
}

static void resize_window(sfEvent event, system_t *sys)
{
    sfRenderWindow *new = NULL;
    sfBool old = sys->fullscreen;

    if (is_keyboard_input(event, sfKeyF11)) {
        if (sys->fullscreen == sfFalse) {
            new = create_window(sfFullscreen, 1);
            sys->fullscreen = sfTrue;
        } else {
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

void sys_events(sfEvent event, system_t *sys)
{
    close_window(event, sys);
    resize_window(event, sys);
    music_setvolume(event, sys);
    change_scene(event, sys);
}
