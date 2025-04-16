/*
** EPITECH PROJECT, 2025
** wolfengine
** File description:
** mov_player.c
*/

#include "wolfengine.h"
#include "hmap.h"
#include <math.h>

static void set_line(player_t *player, sfVertex vertex)
{
    vertex.position.x = player->pos.x;
    vertex.position.y = player->pos.y;
    vertex.color = sfGreen;
    sfVertexArray_append(player->line, vertex);
    vertex.position.x = player->pos.x + player->delta.x * 2;
    vertex.position.y = player->pos.y + player->delta.y * 2;
    vertex.color = sfGreen;
    sfVertexArray_append(player->line, vertex);
    sfVertexArray_setPrimitiveType(player->line, sfLines);
}

static void left_right(sfEvent event, player_t *player)
{
    if (is_keyboard_input(event, sfKeyQ)) {
        player->angle -= 0.1;
        if (player->angle < 0) {
            player->angle += 2 * PI;
        }
        player->delta.x = cos(player->angle) * player->speed;
        player->delta.y = sin(player->angle) * player->speed;
    }
    if (is_keyboard_input(event, sfKeyD)) {
        player->angle += 0.1;
        if (player->angle > 2 * PI) {
            player->angle -= 2 * PI;
        }
        player->delta.x = cos(player->angle) * player->speed;
        player->delta.y = sin(player->angle) * player->speed;
    }
}

static void up_down(sfEvent event, player_t *player)
{
    if (is_keyboard_input(event, sfKeyZ)) {
        player->pos.x += player->delta.x;
        player->pos.y += player->delta.y;
        sfCircleShape_setPosition(player->player, player->pos);
    }
    if (is_keyboard_input(event, sfKeyS)) {
        player->pos.x -= player->delta.x;
        player->pos.y -= player->delta.y;
        sfCircleShape_setPosition(player->player, player->pos);
    }
}


void mov_player(sfEvent event, player_t *player, game_t *game)
{
    sfVertex vertex = {0};

    if (game == NULL)
        return;
    vertex = (sfVertex){0};
    up_down(event, player);
    left_right(event, player);
    set_line(player, vertex);
}
