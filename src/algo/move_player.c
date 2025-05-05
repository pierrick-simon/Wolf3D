/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** move_player.c
*/

#include "save.h"
#include "game.h"
#include <math.h>

static sfBool is_wall(float y, float x, save_t *save)
{
    if (save->map[(int)y / TILE_SIZE][(int)x / TILE_SIZE] != 0)
        return sfTrue;
    return sfFalse;
}

static void sprint(player_t *player, save_t *save)
{
    int coef = 1;

    if (sfKeyboard_isKeyPressed(sfKeyLShift) ||
        sfJoystick_getAxisPosition(0, sfJoystickZ) > 0) {
        player->is_sprinting = sfTrue;
        if (save->info->stamina != 0) {
            coef = 2;
            player->fov = SPRINTING_FOV;
        }
    }
    if (is_wall(player->pos.y,
        player->pos.x + (player->center_ray.v.x * coef * DISTANCE_COLISION),
        save) == sfFalse)
        player->pos.x += player->center_ray.v.x * coef * FORWARD_COEF;
    if (is_wall(player->pos.y +
        (player->center_ray.v.y * coef * DISTANCE_COLISION),
        player->pos.x, save) == sfFalse)
        player->pos.y += player->center_ray.v.y * coef * FORWARD_COEF;
}

static void move_verticaly(player_t *player, save_t *save)
{
    if ((sfKeyboard_isKeyPressed(sfKeyUp))
        || sfKeyboard_isKeyPressed(sfKeyZ)
        || sfJoystick_getAxisPosition(0, sfJoystickPovY) == -100) {
        sprint(player, save);
    }
    if ((sfKeyboard_isKeyPressed(sfKeyDown))
        || sfKeyboard_isKeyPressed(sfKeyS)
        || sfJoystick_getAxisPosition(0, sfJoystickPovY) == 100) {
        if (is_wall(player->pos.y,
            player->pos.x - (player->center_ray.v.x * DISTANCE_COLISION),
            save) == sfFalse)
            player->pos.x -= player->center_ray.v.x;
        if (is_wall(player->pos.y -
            (player->center_ray.v.y * DISTANCE_COLISION),
            player->pos.x, save) == sfFalse)
            player->pos.y -= player->center_ray.v.y;
    }
}

static void move_left(player_t *player, save_t *save, int *head)
{
    if (sfKeyboard_isKeyPressed(sfKeyQ)
        || sfJoystick_getAxisPosition(0, sfJoystickPovX) == -100) {
        *head -= HEAD_SPRITE_X;
        if (is_wall(player->pos.y,
            player->pos.x + (player->center_ray.v.y * DISTANCE_COLISION),
            save) == sfFalse)
            player->pos.x += player->center_ray.v.y;
        if (is_wall(player->pos.y -
            (player->center_ray.v.x * DISTANCE_COLISION),
            player->pos.x, save) == sfFalse)
            player->pos.y -= player->center_ray.v.x;
    }
}

static void move_right(player_t *player, save_t *save, int *head)
{
    if (sfKeyboard_isKeyPressed(sfKeyD)
        || sfJoystick_getAxisPosition(0, sfJoystickPovX) == 100) {
        *head += HEAD_SPRITE_X;
        if (is_wall(player->pos.y,
            player->pos.x - (player->center_ray.v.y * DISTANCE_COLISION),
            save) == sfFalse)
            player->pos.x -= player->center_ray.v.y;
        if (is_wall(player->pos.y +
            (player->center_ray.v.x * DISTANCE_COLISION),
            player->pos.x, save) == sfFalse)
            player->pos.y += player->center_ray.v.x;
    }
}

static void rotate_player(player_t *player, double delta, int *head)
{
    float x_controler = sfJoystick_getAxisPosition(0, sfJoystickU);

    if (fabs(x_controler) > 30)
        player->angle += ROTATION_SPEED * delta * (x_controler / 75);
    if (sfKeyboard_isKeyPressed(sfKeyLeft)) {
        *head -= HEAD_SPRITE_X;
        player->angle -= ROTATION_SPEED * delta;
        if (player->angle < 0)
            player->angle += (M_PI * 2);
    }
    if (sfKeyboard_isKeyPressed(sfKeyRight)) {
        player->angle += ROTATION_SPEED * delta;
        *head += HEAD_SPRITE_X;
        if (player->angle > (M_PI * 2))
            player->angle -= (M_PI * 2);
    }
}

void move_player(player_t *player, double delta, int *head)
{
    *head = HEAD_SPRITE_X;
    player->fov = FOV;
    player->is_sprinting = sfFalse;
    player->center_ray.v.x *= delta;
    player->center_ray.v.y *= delta;
    move_verticaly(player, player->save);
    move_left(player, player->save, head);
    move_right(player, player->save, head);
    rotate_player(player, delta, head);
    if (*head < 0)
        *head = 0;
    if (*head > HEAD_SPRITE_X * 2)
        *head = HEAD_SPRITE_X * 2;
}
