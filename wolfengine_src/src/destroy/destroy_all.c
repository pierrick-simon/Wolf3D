/*
** EPITECH PROJECT, 2025
** wolfengine
** File description:
** destro_all.c
*/

#include "wolfengine.h"

void destroy_all(game_t *game)
{
    sfRenderWindow_destroy(game->window);
}
