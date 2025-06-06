/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** explode_wall
*/

#include "editor.h"
#include "game.h"
#include <math.h>

static void check_expolde_wall(
    game_t *game, save_t *save, sfVector2i tile)
{
    if (save->map[tile.y][tile.x] == 3) {
        save->map[tile.y][tile.x] = 0;
        sfMusic_play(game->music[DESTROY_WALL]);
        game->player->save->info->score += WALL_SCORE;
    }
}

static void expolde_wall_next(game_t *game, entity_t *projectile, save_t *save)
{
    check_expolde_wall(game, save, (sfVector2i)
        {floor(projectile->pos.x / TILE_SIZE),
        floor((projectile->pos.y + 5) / TILE_SIZE)});
    check_expolde_wall(game, save, (sfVector2i)
        {floor((projectile->pos.x + 5) / TILE_SIZE),
        floor((projectile->pos.y + 5) / TILE_SIZE)});
    check_expolde_wall(game, save, (sfVector2i)
        {floor((projectile->pos.x - 5) / TILE_SIZE),
        floor((projectile->pos.y + 5) / TILE_SIZE)});
    check_expolde_wall(game, save, (sfVector2i)
        {floor((projectile->pos.x + 5) / TILE_SIZE),
        floor((projectile->pos.y - 5) / TILE_SIZE)});
}

void expolde_wall(game_t *game, entity_t *projectile, save_t *save)
{
    check_expolde_wall(game, save, (sfVector2i)
        {floor((projectile->pos.x - 5) / TILE_SIZE),
        floor(projectile->pos.y / TILE_SIZE)});
    check_expolde_wall(game, save, (sfVector2i)
        {floor(projectile->pos.x / TILE_SIZE),
        floor((projectile->pos.y - 5) / TILE_SIZE)});
    check_expolde_wall(game, save, (sfVector2i)
        {floor((projectile->pos.x - 5) / TILE_SIZE),
        floor((projectile->pos.y - 5) / TILE_SIZE)});
    check_expolde_wall(game, save, (sfVector2i)
        {floor((projectile->pos.x + 5) / TILE_SIZE),
        floor(projectile->pos.y / TILE_SIZE)});
    expolde_wall_next(game, projectile, save);
}
