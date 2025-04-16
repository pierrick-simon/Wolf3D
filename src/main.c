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
    weapon_t weapon = {NULL};
    map_t map = {NULL};

    init_map(&map);
    if (init_game(&game) == EXIT_F || init_weapon(&weapon) == EXIT_F) {
        destroy_game(&game);
        destroy_weapon(&weapon);
        return EXIT_F;
    }
    game_loop(&game, &weapon);
    destroy_game(&game);
    destroy_weapon(&weapon);
    return EXIT_S;
}
