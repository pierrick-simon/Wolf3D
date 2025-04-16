/*
** EPITECH PROJECT, 2025
** wolfengine
** File description:
** init_game.c
*/

#include "wolfengine.h"

int init_game(game_t *game)
{
    game->window = set_window();
    game->clock = sfClock_create();
    game->music = sfMusic_createFromFile(MUSIC_PATH);
    game->bg = sfColor_fromRGB(0, 0, 0);
    return EXIT_S;
}
