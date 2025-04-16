/*
** EPITECH PROJECT, 2025
** wolfengine
** File description:
** game_loop.c
*/

#include <math.h>
#include "wolfengine.h"
#include "hmap.h"


static void hit_wall(player_t *player, game_t *game)
{
    int mp_index_x = (int)(player->rays->mp) % MAP_X;
    int mp_index_y = (int)(player->rays->mp) / MAP_Y;

    if (player->rays->mp < MAP_S && map[mp_index_y][mp_index_x] == 1) {
        player->rays->dof = 8;
    } else {
        player->rays->rxy.x += player->rays->xyoffset.x;
        player->rays->rxy.y += player->rays->xyoffset.y;
        player->rays->dof += 1;
    }
    sfRenderWindow_drawVertexArray(game->window, player->line, sfFalse);
}

static void looking_straight(player_t *player, game_t *game)
{
    if (player->rays->ra == 0 || player->rays->ra == PI) {
        player->rays->rxy.x = player->pos.x;
        player->rays->rxy.y = player->pos.y;
        player->rays->dof = MAP_X;
    }
    while (player->rays->dof < 8) {
        player->rays->mxy.x = (int)player->rays->rxy.x >> 6;
        player->rays->mxy.y = (int)player->rays->rxy.y >> 6;
        player->rays->mp = player->rays->mxy.y * MAP_X + player->rays->mxy.x;
        hit_wall(player, game);
    }
}

static void looking_down(player_t *player, double aTan, game_t *game)
{
    if (player->rays->ra > PI) {
        player->rays->rxy.y = (((int)(player->pos.y) >> 6) << 6) - 0.0001;
        player->rays->rxy.x = (player->pos.y - player->rays->rxy.y) * aTan + player->pos.x;
        player->rays->xyoffset.y = -MAP_S;
        player->rays->xyoffset.x = -player->rays->xyoffset.y * aTan;
    }
    if (player->rays->ra < PI) {
        player->rays->rxy.y = (((int)(player->pos.y) >> 6) << 6) - MAP_S;
        player->rays->rxy.x = (player->pos.y - player->rays->rxy.y) * aTan + player->pos.x;
        player->rays->xyoffset.y = MAP_S;
        player->rays->xyoffset.x = -player->rays->xyoffset.y * aTan;
    }
    looking_straight(player, game);
}

static void check_horizon_line(player_t *player, double aTan, game_t *game)
{
    player->rays->dof = 0;
    aTan = -1 / tan(player->rays->ra);

    looking_down(player, aTan, game);
}

static void draw_rays(player_t *player, game_t *game)
{
    double aTan = 0.0;

    player->rays->ra = player->angle;
    for (int r = 0; r < 1; r++) {
        check_horizon_line(player, aTan, game);
    }
}

int game_loop(game_t *game, player_t *player)
{
    player->delta.x = cos(player->angle) * 5;
    player->delta.y = sin(player->angle) * 5;
    while (sfRenderWindow_isOpen(game->window) == sfTrue) {
        events(game, player);
        sfRenderWindow_clear(game->window, game->bg);
        draw_rays(player, game);
        draw_minimap(game);
        // if (sfMusic_getStatus(game->music) == sfStopped)
            // sfMusic_play(game->music);
        sfRenderWindow_drawVertexArray(game->window, player->line, sfFalse);
        sfRenderWindow_drawCircleShape(game->window, player->player, sfFalse);
        sfVertexArray_clear(player->line);
        sfRenderWindow_display(game->window);
    }
    return EXIT_S;
}
