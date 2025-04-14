/*
** EPITECH PROJECT, 2025
** bonus
** File description:
** event
*/

#include "wolf.h"

static sfBool is_keyboard_input(sfEvent event, sfKeyCode key)
{
    if (event.type == sfEvtKeyPressed && event.key.code == key)
        return sfTrue;
    return sfFalse;
}

static void music_setvolume(sfEvent event, game_t *game)
{
    float volume = sfMusic_getVolume(game->music);

    if (is_keyboard_input(event, sfKeyF1)) {
        if (volume < 1)
            volume = VOL_MAX;
        else
            volume = VOL_MIN;
    }
    if (is_keyboard_input(event, sfKeyF2)) {
        if (volume > VOL_MIN + VOL_GAP)
            volume -= VOL_GAP;
        else
            volume = 0.0;
    }
    if (is_keyboard_input(event, sfKeyF3) && volume < VOL_MAX - VOL_GAP)
        volume += VOL_GAP;
    sfMusic_setVolume(game->music, volume);
}

static void close_window(sfEvent event, game_t *game)
{
    if (is_keyboard_input(event, sfKeyEscape) || event.type == sfEvtClosed) {
        sfRenderWindow_close(game->window);
        sfMusic_setVolume(game->music, VOL_MIN);
    }
}

static void click(sfEvent event, game_t *game, shotgun_t *shotgun)
{
    if (event.type == sfEvtMouseButtonPressed
        && event.mouseButton.button == sfMouseLeft) {
        shotgun->shot = sfClock_getElapsedTime(game->clock).microseconds;
        sfMusic_play(shotgun->sound);
    }
}

void events(game_t *game, shotgun_t *shotgun)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(game->window, &event)) {
        close_window(event, game);
        music_setvolume(event, game);
        click(event, game, shotgun);
    }
}
