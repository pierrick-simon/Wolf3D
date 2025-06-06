/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** add_projectile
*/

#include "entities.h"
#include "game.h"
#include "save.h"
#include <math.h>

static void cal_pos(entity_t *entity, sfVector2f *player, float value)
{
    entity->next_pos.x = entity->pos.x + value *
        (player->x - entity->pos.x) / entity->dist;
    entity->next_pos.y = entity->pos.y + value *
        (player->y - entity->pos.y) / entity->dist;
    entity->pos.x = entity->pos.x +
        (ENTITY[E_BOSS_PROJECTILE].text_size.x / 2 + 10) *
        (player->x - entity->pos.x) / entity->dist;
    entity->pos.y = entity->pos.y +
        (ENTITY[E_BOSS_PROJECTILE].text_size.x / 2 + 10) *
        (player->y - entity->pos.y) / entity->dist;
}

static void next_pos_boss(save_t *save, entity_t *entity, sfVector2f *player)
{
    player_t tmp = {0};
    intersection_t type = {0};
    sfVector2f intersection_point = {0};
    float value = 0;

    type.type = NONE;
    tmp.save = save;
    tmp.pos = entity->pos;
    if (entity->dist < 1)
        return;
    get_angle(&tmp.angle, player, &entity->pos, entity->dist);
    value = cast_single_ray_enemy(&tmp, 0, &type, &intersection_point);
    cal_pos(entity, player, value);
}

void add_projectile_boss(game_t *game, sfVector2f *boss, int dist)
{
    entity_t *entity = malloc(sizeof(entity_t));

    entity->type = E_BOSS_PROJECTILE;
    entity->pos = *boss;
    entity->dist = dist;
    next_pos_boss(game->player->save, entity, &game->player->pos);
    entity->offset = (sfVector2f){0, 0};
    entity->is_alive = sfTrue;
    entity->damage = SKIP;
    entity->change_pos = SKIP;
    entity->change_rect = 0;
    entity->health = ENEMY[E_BOSS_PROJECTILE].attack;
    entity->prev_tile = (sfVector2i){0, 0};
    entity->see = sfFalse;
    push_to_head(game->player->save->entities, entity);
}

static void next_pos_player(player_t *player, entity_t *entity)
{
    intersection_t type = {0};
    sfVector2f intersection_point = {0};
    float value = cast_single_ray_enemy(player, 0, &type, &intersection_point);

    entity->dist = value;
    entity->next_pos.x = player->pos.x + value * cos(player->angle);
    entity->next_pos.y = player->pos.y + value * sin(player->angle);
    entity->pos.x = entity->pos.x +
        (ENTITY[E_PLAYER_PROJECTILE].text_size.x / 2 + 10) *
        (entity->next_pos.x - entity->pos.x) / entity->dist;
    entity->pos.y = entity->pos.y +
        (ENTITY[E_PLAYER_PROJECTILE].text_size.x / 2 + 10) *
        (entity->next_pos.y - entity->pos.y) / entity->dist;
}

void add_projectile_player(player_t *player)
{
    entity_t *entity = malloc(sizeof(entity_t));

    entity->type = E_PLAYER_PROJECTILE;
    entity->pos = player->pos;
    next_pos_player(player, entity);
    entity->offset = (sfVector2f){0, 0};
    entity->is_alive = sfTrue;
    entity->damage = SKIP;
    entity->change_pos = SKIP;
    entity->change_rect = 0;
    entity->health = ENEMY[E_PLAYER_PROJECTILE].attack;
    entity->prev_tile = (sfVector2i){0, 0};
    entity->see = sfFalse;
    push_to_head(player->save->entities, entity);
}
