/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** enemies_movement
*/

#include "element.h"
#include "game.h"
#include "save.h"
#include <math.h>
#include <stdlib.h>

static sfBool is_wall(
    int **map, sfVector2i *player_tile, sfVector2f *enemy_tile)
{
    int dx = ceil(fabs(enemy_tile->x - player_tile->x));
    int dy = ceil(fabs(enemy_tile->y - player_tile->y));
    int next = dx - dy;
    int tmp = 0;

    while (player_tile->x != enemy_tile->x
        || player_tile->y != enemy_tile->y) {
        if (map[player_tile->y][player_tile->x] != 0)
            return sfTrue;
        tmp = 2 * next;
        if (tmp > dy * -1) {
            next -= dy;
            player_tile->x += player_tile->x < enemy_tile->x ? 1 : -1;
        }
        if (tmp < dx) {
            next += dx;
            player_tile->y += player_tile->y < enemy_tile->y ? 1 : -1;
        }
    }
    return sfFalse;
}

static void get_new_position(enemy_t *enemy, game_t *game, float difficulty)
{
    float coef = ENEMY[enemy->type].speed * difficulty
        * game->time_info->delta / enemy->dist;
    sfVector2f mov = {game->player->pos.x - enemy->pos.x,
        game->player->pos.y - enemy->pos.y};
    sfVector2i player_tile = {floor(game->player->pos.x / TILE_SIZE),
        floor(game->player->pos.y / TILE_SIZE)};
    sfVector2f enemy_tile = {floor(enemy->pos.x / TILE_SIZE),
        floor(enemy->pos.y / TILE_SIZE)};

    if (is_wall(game->player->save->map, &player_tile, &enemy_tile) == sfTrue)
        return;
    enemy->pos.x += mov.x * coef;
    enemy->pos.y += mov.y * coef;
}

void enemies_movement(game_t *game, linked_list_t *enemies, float difficulty)
{
    enemy_t *tmp = NULL;

    for (node_t *head = enemies->head; head != NULL; head = head->next) {
        tmp = head->data;
        if (tmp->dist > ENEMY[tmp->type].detect_range * difficulty
            || tmp->dist < ENEMY[tmp->type].attack_range * difficulty)
            continue;
        get_new_position(tmp, game, difficulty);
    }
}
