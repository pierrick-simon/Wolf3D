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

static void get_angle(player_t *tmp, game_t *game, entity_t *enemy)
{
    float dist = fabs(game->player->pos.x - enemy->pos.x) / enemy->dist;
    float diff_x = game->player->pos.x - enemy->pos.x;
    float diff_y = game->player->pos.y - enemy->pos.y;

    if (dist > 1)
        dist = 1;
    if (dist < -1)
        dist = -1;
    tmp->angle = asin(dist);
    if (diff_y > 0) {
        if (diff_x > 0)
            tmp->angle = M_PI / 2 - tmp->angle;
        else
            tmp->angle += M_PI / 2;
    } else {
        if (diff_x > 0)
            tmp->angle = (M_PI / 2 - tmp->angle) * -1;
        else
            tmp->angle = (M_PI / 2 + tmp->angle) * -1;
    }
}

static sfBool is_wall(game_t *game, entity_t *enemy)
{
    player_t tmp = {0};
    intersection_t type = {0};
    sfVector2f intersection_point = {0};
    float value = 0;

    type.type = NONE;
    tmp.save = game->player->save;
    tmp.pos = enemy->pos;
    if (enemy->dist < 1)
        return sfFalse;
    get_angle(&tmp, game, enemy);
    value = cast_single_ray(&tmp, 0, &type, &intersection_point);
    if (value < enemy->dist)
        return sfTrue;
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

    if (is_wall(game, enemy) == sfTrue)
        return;
    enemy->change_pos = SKIP;
    enemy->pos.x += mov.x * coef;
    enemy->pos.y += mov.y * coef;
    change_movement_rect(enemy, game, ENEMY[enemy->type].speed * difficulty);
}

static void change_attack_rect(entity_t *enemy, game_t *game)
{
    if (enemy->change_pos == SKIP)
        enemy->change_pos = TIME_OVERLAY;
    if (enemy->change_pos > 0)
        enemy->change_pos -= game->time_info->delta;
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
    if (enemy->cooldown <= 0 && is_wall(game, enemy) == sfFalse) {
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
            delete_node(save->entities, node, &free);
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
        if (tmp->dist > RENDER_DISTANCE || tmp->type < NB_ITEM)
            continue;
        if (tmp->is_alive == sfFalse) {
            change_death_rect(tmp, save, game, head);
            continue;
        }
        if (tmp->dist < ENEMY[tmp->type].attack_range * save->info->difficulty
            || tmp->change_pos > 0)
            attack_player(tmp, save, game);
        else
            get_new_position(tmp, game, save->info->difficulty);
    }
}
