/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** main
*/

#include "wolf.h"

int main(void)
{
    game_t game = {NULL};
    system_t sys = {NULL};

    if (init_game(&game) == EXIT_F || init_system(&sys) == EXIT_F) {
        destroy_game(&game);
        destroy_sys(&sys);
        return EXIT_F;
    }
    game_loop(&sys, &game);
    destroy_game(&game);
    destroy_sys(&sys);
    return EXIT_S;
}
