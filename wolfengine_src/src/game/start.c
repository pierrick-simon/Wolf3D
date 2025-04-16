/*
** EPITECH PROJECT, 2025
** wolfengine
** File description:
** start.c
*/

#include <stddef.h>
#include "wolfengine.h"

int start(void)
{
    game_t game = {NULL};
    player_t player = {0};
    frame_t frame = {0};

    init_game(&game);
    init_player(&player);
    init_frame(&frame);
    if (game_loop(&game, &player) == EXIT_F)
        return EXIT_F;
    destroy_all(&game);
    return EXIT_S;
}
