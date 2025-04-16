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

static void move_verticaly(sfEvent event,
    player_t *player, sfVector2f casted_pos)
{
    if ((is_keyboard_input(event, sfKeyUp)
        || is_keyboard_input(event, sfKeyZ))) {
        if (is_wall(casted_pos.y,
            casted_pos.x + (player->v.x * DISTANCE_COLISION)) == sfFalse)
            player->pos.x += player->v.x * FORWARD_COEF;
        if (is_wall(casted_pos.y + (player->v.y * DISTANCE_COLISION),
            casted_pos.x) == sfFalse)
            player->pos.y += player->v.y * FORWARD_COEF;
    }
    if ((is_keyboard_input(event, sfKeyDown)
        || is_keyboard_input(event, sfKeyS))) {
        if (is_wall(casted_pos.y,
            casted_pos.x - (player->v.x * DISTANCE_COLISION)) == sfFalse)
            player->pos.x -= player->v.x;
        if (is_wall(casted_pos.y - (player->v.y * DISTANCE_COLISION),
            casted_pos.x) == sfFalse)
            player->pos.y -= player->v.y;
    }
}

static void move_horizontaly(sfEvent event,
    player_t *player, sfVector2f casted_pos)
{
    if (is_keyboard_input(event, sfKeyQ)) {
        if (is_wall(casted_pos.y,
            casted_pos.x + (player->v.y * DISTANCE_COLISION)) == sfFalse)
            player->pos.x += player->v.y;
        if (is_wall(casted_pos.y - (player->v.x * DISTANCE_COLISION),
            casted_pos.x) == sfFalse)
            player->pos.y -= player->v.x;
    }
    if (is_keyboard_input(event, sfKeyD)) {
        if (is_wall(casted_pos.y,
            casted_pos.x - (player->v.y * DISTANCE_COLISION)) == sfFalse)
            player->pos.x -= player->v.y;
        if (is_wall(casted_pos.y + (player->v.x * DISTANCE_COLISION),
            casted_pos.x) == sfFalse)
            player->pos.y += player->v.x;
    }
}

static void rotate_player(sfEvent event, player_t *player)
{
    if (is_keyboard_input(event, sfKeyLeft)) {
        player->angle -= ROTATION_SPPED;
        if (player->angle < 0)
            player->angle += (M_PI * 2);
    }
    if (is_keyboard_input(event, sfKeyRight)) {
        player->angle += ROTATION_SPPED;
        if (player->angle > (M_PI * 2))
            player->angle -= (M_PI * 2);
    }
}

void move_player(sfEvent event, player_t *player)
{
    sfVector2f casted_pos = {player->pos.x, player->pos.y};

    move_verticaly(event, player, casted_pos);
    move_horizontaly(event, player, casted_pos);
    rotate_player(event, player);
}
