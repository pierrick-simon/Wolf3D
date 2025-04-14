/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** main
*/

#include "wolf.h"

int main(int ac, char **av)
{
    game_t game = {NULL};
    weapon_t weapon = {NULL};
    
    init_game(&game);
    init_weapon(&weapon);
    game_loop(&game, &weapon);
    return EXIT_S;
}
