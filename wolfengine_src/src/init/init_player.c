/*
** EPITECH PROJECT, 2025
** wolfengine
** File description:
** init_player.c
*/

#include "wolfengine.h"
#include <stdlib.h>

static void init_mov(player_t *player)
{
    player->delta.x = 0;
    player->delta.y = 0;
    player->angle = 0;
    player->line = sfVertexArray_create();
}

static void init_rays(player_t *player)
{
    player->rays = malloc(sizeof(rays_t));
    if (player->rays == NULL)
        return;
    player->rays->mxy = (sfVector2f){0, 0};
    player->rays->mp = 0;
    player->rays->dof = 0;
    player->rays->rxy = (sfVector2f){0, 0};
    player->rays->ra = 0;
    player->rays->xyoffset = (sfVector2f){0, 0};
}

player_t *init_player(player_t *player)
{
    
    player->player = sfCircleShape_create();
    player->speed = PLAYER_SPEED;
    player->radius = PLAYER_RADIUS;
    sfCircleShape_setRadius(player->player, player->radius);
    player->color = PLAYER_COLOR;
    sfCircleShape_setFillColor(player->player, player->color);
    player->pos = (sfVector2f)PLAYER_POS;
    sfCircleShape_setPosition(player->player, player->pos);
    sfCircleShape_setOrigin(player->player,
        (sfVector2f){(player->radius / 2), (player->radius / 2)});
    init_mov(player);
    init_rays(player);
    return player;
}
