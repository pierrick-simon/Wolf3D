/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** move_y.c
*/

#include "game.h"

void move_y(player_t *player, double delta)
{
    if (player->jump_value != Y_MAX
        && sfKeyboard_isKeyPressed(sfKeyUp)) {
        player->jump_value += Y_SPEED * delta;
        if (player->jump_value >= Y_MAX)
            player->jump_value = Y_MAX;
    }
    if (player->jump_value != Y_MIN
        && sfKeyboard_isKeyPressed(sfKeyDown)) {
        player->jump_value -= Y_SPEED * delta;
        if (player->jump_value <= Y_MIN)
            player->jump_value = Y_MIN;
    }
}
