/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** event
*/

#include "wolf.h"

static void change_scene(sfEvent event, system_t *sys)
{
    if (is_input(event, sfKeyTab, sfTrue, 3)) {
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
    float volume = sfMusic_getVolume(sys->music);

    if (is_input(event, sfKeyF1, sfFalse, 0)) {
        if (volume < 1)
            volume = VOL_MAX;
        else
            volume = VOL_MIN;
    }
    if (is_input(event, sfKeyF2, sfFalse, 0)) {
        if (volume > VOL_MIN + VOL_GAP)
            volume -= VOL_GAP;
        else
            volume = 0.0;
    }
    if (is_input(event, sfKeyF3, sfFalse, 0)
        && volume < VOL_MAX - VOL_GAP)
        volume += VOL_GAP;
    sfMusic_setVolume(sys->music, volume);
}

static void close_window(sfEvent event, system_t *sys)
{
    if (is_input(event, sfKeyEscape, sfTrue, 8) || event.type == sfEvtClosed) {
        sfRenderWindow_close(sys->window);
        sfMusic_setVolume(sys->music, VOL_MIN);
    }
}

static void resize_window(sfEvent event, system_t *sys)
{
    sfRenderWindow *new = NULL;
    sfBool old = sys->fullscreen;

    if (is_input(event, sfKeyF11, sfFalse, 0)) {
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
