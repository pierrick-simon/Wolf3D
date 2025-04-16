/*
** EPITECH PROJECT, 2025
** wolfengine
** File description:
** music.c
*/

#include "wolfengine.h"

static void music_setvolume(sfEvent event, game_t *game)
{
    float volume = sfMusic_getVolume(game->music);

    if (is_keyboard_input(event, sfKeyF1)) {
        if (volume < 1)
            volume = MUSIC_MAX;
        else
            volume = MUSIC_MIN;
    }
    if (is_keyboard_input(event, sfKeyF2)) {
        if (volume > MUSIC_MIN + MUSIC_GAP)
            volume -= MUSIC_GAP;
        else
            volume = 0.0;
    }
    if (is_keyboard_input(event, sfKeyF3) && volume < MUSIC_MAX - MUSIC_GAP)
        volume += MUSIC_GAP;
    sfMusic_setVolume(game->music, volume);
}
