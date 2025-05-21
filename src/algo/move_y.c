/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** move_y.c
*/

#include "game.h"

void move_y(player_t *player, double delta)
{
    if (player->jump_value != JUMP_MAX
        && sfKeyboard_isKeyPressed(sfKeyUp)) {
        player->jump_value += JUMP_SPEED * delta;
        if (player->jump_value >= JUMP_MAX)
            player->jump_value = JUMP_MAX;
    }
    if (player->jump_value != JUMP_MIN
        && sfKeyboard_isKeyPressed(sfKeyDown)) {
        player->jump_value -= JUMP_SPEED * delta;
        if (player->jump_value <= JUMP_MIN)
            player->jump_value = JUMP_MIN;
    }
}
