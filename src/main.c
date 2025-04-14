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
    shotgun_t shotgun = {NULL};
    
    init_game(&game);
    init_shotgun(&shotgun);
    game_loop(&game, &shotgun);
    return EXIT_S;
}
