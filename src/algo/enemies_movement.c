/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** enemies_movement
*/

#include "entities.h"
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

static void change_movement_rect(entity_t *enemy, game_t *game, float speed)
{
    enemy->offset.y = 0;
    if (enemy->change_rect <= 0) {
        enemy->offset.x += ENTITY[enemy->type].text_size.x;
        if (enemy->offset.x >= ENTITY[enemy->type].max_first *
            ENTITY[enemy->type].text_size.x)
            enemy->offset.x = 0;
        enemy->change_rect = 10 / speed;
    } else
        enemy->change_rect -= game->time_info->delta;
}

static void get_new_position(entity_t *enemy, game_t *game, float difficulty)
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
    change_movement_rect(enemy, game, ENEMY[enemy->type].speed * difficulty);
}

static void change_attack_rect(entity_t *enemy, game_t *game)
{
    if (ENTITY[enemy->type].max_second == 0)
        return;
    enemy->offset.y = ENTITY[enemy->type].text_size.y;
    if (game->time_info->shot >= 0 && enemy->change_rect != SKIP) {
        if (enemy->change_rect <= 0) {
            enemy->offset.x += ENTITY[enemy->type].text_size.x;
            enemy->change_rect = TIME_OVERLAY
                / (ENTITY[enemy->type].max_second - 1);
        } else
            enemy->change_rect -= game->time_info->delta;
    } else
        enemy->offset.x = 0;
}

static void attack_player(entity_t *enemy, save_t *save, game_t *game)
{
    if (enemy->cooldown <= 0) {
        save->info->item_info[INFO_HEALTH] -= ENEMY[enemy->type].attack;
        enemy->cooldown = ENEMY[enemy->type].cooldown *
            (2 - save->info->difficulty);
        game->time_info->shot = TIME_OVERLAY;
        sfMusic_play(game->music[HURT]);
        enemy->offset.x = 0;
        if (ENTITY[enemy->type].max_second - 1 != 0)
            enemy->change_rect = 0;
        else
            enemy->change_rect = SKIP;
    } else
        enemy->cooldown -= game->time_info->delta;
    change_attack_rect(enemy, game);
}

void change_death_rect(
    entity_t *enemy, save_t *save, game_t *game, node_t *node)
{
    if (ENTITY[enemy->type].max_third == 0) {
        delete_node(save->entities, node, &free);
        return;
    }
    enemy->offset.y = ENTITY[enemy->type].text_size.y * 2;
    if (enemy->cooldown <= 0) {
        enemy->offset.x += ENTITY[enemy->type].text_size.x;
        enemy->cooldown = DEATH_RECT;
        if (enemy->offset.x >= ENTITY[enemy->type].max_third *
            ENTITY[enemy->type].text_size.x)
            enemy->offset.x -= ENTITY[enemy->type].text_size.x;
    } else
        enemy->cooldown -= game->time_info->delta;
}

void enemies_movement(game_t *game, linked_list_t *enemies, save_t *save)
{
    entity_t *tmp = NULL;
    node_t *next = NULL;

    for (node_t *head = enemies->head; head != NULL; head = next) {
        next = head->next;
        tmp = head->data;
        if (tmp->is_alive == sfFalse) {
            change_death_rect(tmp, save, game, head);
            continue;
        }
        if (tmp->dist > RENDER_DISTANCE * save->info->difficulty
            || tmp->type < NB_ITEM)
            continue;
        if (tmp->dist < ENEMY[tmp->type].attack_range * save->info->difficulty)
            attack_player(tmp, save, game);
        else
            get_new_position(tmp, game, save->info->difficulty);
    }
}
