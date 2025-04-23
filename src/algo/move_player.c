/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** move_player.c
*/

#include "wolf.h"
#include <math.h>

static sfBool is_wall(float y, float x)
{
    if (map[(int)y / TILE_SIZE][(int)x / TILE_SIZE] != 0)
        return sfTrue;
    return sfFalse;
}

static void sprint(player_t *player)
{
    int coef = 1;

    if (sfKeyboard_isKeyPressed(sfKeyLShift) ||
        sfJoystick_getAxisPosition(0, sfJoystickZ) > 0) {
        coef = 2;
        player->fov = SPRINTING_FOV;
        player->is_sprinting = sfTrue;
    }
    if (is_wall(player->pos.y,
        player->pos.x + (player->v.x * coef * DISTANCE_COLISION)) == sfFalse)
        player->pos.x += player->v.x * coef * FORWARD_COEF;
    if (is_wall(player->pos.y + (player->v.y * coef * DISTANCE_COLISION),
        player->pos.x) == sfFalse)
        player->pos.y += player->v.y * coef * FORWARD_COEF;
}

static void move_verticaly(player_t *player)
{
    if ((sfKeyboard_isKeyPressed(sfKeyUp))
        || sfKeyboard_isKeyPressed(sfKeyZ)
        || sfJoystick_getAxisPosition(0, sfJoystickPovY) == -100) {
        sprint(player);
    }
    if ((sfKeyboard_isKeyPressed(sfKeyDown))
        || sfKeyboard_isKeyPressed(sfKeyS)
        || sfJoystick_getAxisPosition(0, sfJoystickPovY) == 100) {
        if (is_wall(player->pos.y,
            player->pos.x - (player->v.x * DISTANCE_COLISION)) == sfFalse)
            player->pos.x -= player->v.x;
        if (is_wall(player->pos.y - (player->v.y * DISTANCE_COLISION),
            player->pos.x) == sfFalse)
            player->pos.y -= player->v.y;
    }
}

static void move_horizontaly(player_t *player)
{
    if (sfKeyboard_isKeyPressed(sfKeyQ)
        || sfJoystick_getAxisPosition(0, sfJoystickPovX) == -100) {
        if (is_wall(player->pos.y,
            player->pos.x + (player->v.y * DISTANCE_COLISION)) == sfFalse)
            player->pos.x += player->v.y;
        if (is_wall(player->pos.y - (player->v.x * DISTANCE_COLISION),
            player->pos.x) == sfFalse)
            player->pos.y -= player->v.x;
    }
    if (sfKeyboard_isKeyPressed(sfKeyD)
        || sfJoystick_getAxisPosition(0, sfJoystickPovX) == 100) {
        if (is_wall(player->pos.y,
            player->pos.x - (player->v.y * DISTANCE_COLISION)) == sfFalse)
            player->pos.x -= player->v.y;
        if (is_wall(player->pos.y + (player->v.x * DISTANCE_COLISION),
            player->pos.x) == sfFalse)
            player->pos.y += player->v.x;
    }
}

static void rotate_player(player_t *player, double delta)
{
    float x_controler = sfJoystick_getAxisPosition(0, sfJoystickU);

    if (fabs(x_controler) > 30)
        player->angle += ROTATION_SPEED * delta * (x_controler / 75);
    if (sfKeyboard_isKeyPressed(sfKeyLeft)) {
        player->angle -= ROTATION_SPEED * delta;
        if (player->angle < 0)
            player->angle += (M_PI * 2);
    }
    if (sfKeyboard_isKeyPressed(sfKeyRight)) {
        player->angle += ROTATION_SPEED * delta;
        if (player->angle > (M_PI * 2))
            player->angle -= (M_PI * 2);
    }
}

void move_player(player_t *player, double delta)
{
    player->fov = FOV;
    player->is_sprinting = sfFalse;
    player->v.x *= delta;
    player->v.y *= delta;
    move_verticaly(player);
    move_horizontaly(player);
    rotate_player(player, delta);
}
