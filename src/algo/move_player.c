/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** move_player.c
*/

#include "wolf.h"

static sfBool is_wall(float y, float x)
{
    if (map[(int)y / TILE_SIZE][(int)x / TILE_SIZE] != 0)
        return sfTrue;
    return sfFalse;
}

static void sprint(player_t *player, sfVector2f casted_pos)
{
    int coef = 1;

    if (sfKeyboard_isKeyPressed(sfKeyLShift)) {
        coef = 2;
        player->fov = SPRINTING_FOV;
        player->is_sprinting = sfTrue;
    }
    if (is_wall(casted_pos.y,
        casted_pos.x + (player->v.x * coef * DISTANCE_COLISION)) == sfFalse)
        player->pos.x += player->v.x * coef * FORWARD_COEF;
    if (is_wall(casted_pos.y + (player->v.y * coef * DISTANCE_COLISION),
        casted_pos.x) == sfFalse)
        player->pos.y += player->v.y * coef * FORWARD_COEF;
}

static void move_verticaly(player_t *player, sfVector2f casted_pos)
{
    if ((sfKeyboard_isKeyPressed(sfKeyUp))
        || sfKeyboard_isKeyPressed(sfKeyZ)) {
        sprint(player, casted_pos);
    }
    if ((sfKeyboard_isKeyPressed(sfKeyDown))
        || sfKeyboard_isKeyPressed(sfKeyS)) {
        if (is_wall(casted_pos.y,
            casted_pos.x - (player->v.x * DISTANCE_COLISION)) == sfFalse)
            player->pos.x -= player->v.x;
        if (is_wall(casted_pos.y - (player->v.y * DISTANCE_COLISION),
            casted_pos.x) == sfFalse)
            player->pos.y -= player->v.y;
    }
}

static void move_horizontaly(player_t *player, sfVector2f casted_pos)
{
    if (sfKeyboard_isKeyPressed(sfKeyQ)) {
        if (is_wall(casted_pos.y,
            casted_pos.x + (player->v.y * DISTANCE_COLISION)) == sfFalse)
            player->pos.x += player->v.y;
        if (is_wall(casted_pos.y - (player->v.x * DISTANCE_COLISION),
            casted_pos.x) == sfFalse)
            player->pos.y -= player->v.x;
    }
    if (sfKeyboard_isKeyPressed(sfKeyD)) {
        if (is_wall(casted_pos.y,
            casted_pos.x - (player->v.y * DISTANCE_COLISION)) == sfFalse)
            player->pos.x -= player->v.y;
        if (is_wall(casted_pos.y + (player->v.x * DISTANCE_COLISION),
            casted_pos.x) == sfFalse)
            player->pos.y += player->v.x;
    }
}

static void rotate_player(player_t *player)
{
    if (sfKeyboard_isKeyPressed(sfKeyLeft)) {
        player->angle -= ROTATION_SPPED;
        if (player->angle < 0)
            player->angle += (M_PI * 2);
    }
    if (sfKeyboard_isKeyPressed(sfKeyRight)) {
        player->angle += ROTATION_SPPED;
        if (player->angle > (M_PI * 2))
            player->angle -= (M_PI * 2);
    }
}

void move_player(player_t *player)
{
    sfVector2f casted_pos = {player->pos.x, player->pos.y};

    move_verticaly(player, casted_pos);
    move_horizontaly(player, casted_pos);
    rotate_player(player);
}
