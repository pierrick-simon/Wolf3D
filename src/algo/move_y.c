/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** move_y.c
*/

#include "game.h"

void move_y(player_t *player, double delta)
{
    if (player->cam_angle != Y_MAX
        && sfKeyboard_isKeyPressed(sfKeyUp)) {
        player->cam_angle += Y_SPEED * delta;
        if (player->cam_angle >= Y_MAX)
            player->cam_angle = Y_MAX;
    }
    if (player->cam_angle != Y_MIN
        && sfKeyboard_isKeyPressed(sfKeyDown)) {
        player->cam_angle -= Y_SPEED * delta;
        if (player->cam_angle <= Y_MIN)
            player->cam_angle = Y_MIN;
    }
}
