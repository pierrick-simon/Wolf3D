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

sfBool is_arrived(entity_t *enemy)
{
    if (enemy->pos.x > enemy->next_pos.x - 5
        && enemy->pos.x < enemy->next_pos.x + 5
        && enemy->pos.y > enemy->next_pos.y - 5
        && enemy->pos.y < enemy->next_pos.y + 5)
        return sfTrue;
    return sfFalse;
}

static sfBool return_value(entity_t *enemy, game_t *game, sfBool *return_value)
{
    if (is_wall_between(game, enemy) == sfFalse) {
        enemy->see = sfTrue;
        *return_value = sfFalse;
        return sfTrue;
    }
    if (enemy->see == sfFalse) {
        *return_value = sfTrue;
        return sfTrue;
    }
    if (enemy->next_pos.x == SKIP || enemy->next_pos.y == SKIP
        || is_arrived(enemy) == sfTrue) {
        if (get_next_pos(enemy, game) == sfFalse) {
            *return_value = sfTrue;
            return sfTrue;
        }
    }
    return sfFalse;
}

static sfBool move_closer(entity_t *enemy, game_t *game, float difficulty)
{
    float dist = 0;
    float coef = 0;
    sfVector2f mov = {0};
    sfBool tmp = sfFalse;

    if (return_value(enemy, game, &tmp) == sfTrue)
        return tmp;
    dist = sqrt(pow(enemy->pos.x - enemy->next_pos.x, 2) +
        pow(enemy->pos.y - enemy->next_pos.y, 2));
    coef = ENEMY[enemy->type].speed * difficulty
        * game->time_info->delta / dist;
    mov = (sfVector2f){enemy->next_pos.x - enemy->pos.x,
        enemy->next_pos.y - enemy->pos.y};
    enemy->pos.x += mov.x * coef;
    enemy->pos.y += mov.y * coef;
    change_movement_rect(enemy, game, ENEMY[enemy->type].speed * difficulty);
    return sfTrue;
}

static void get_new_position(entity_t *enemy, game_t *game, float difficulty)
{
    float coef = ENEMY[enemy->type].speed * difficulty
        * game->time_info->delta / enemy->dist;
    sfVector2f mov = {game->player->pos.x - enemy->pos.x,
        game->player->pos.y - enemy->pos.y};

    enemy->next_pos = (sfVector2f){SKIP, SKIP};
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
    if (enemy->shot >= 0 && enemy->change_rect != SKIP) {
        if (enemy->change_rect <= 0) {
            enemy->offset.x += ENTITY[enemy->type].text_size.x;
            enemy->change_rect = TIME_OVERLAY
                / (ENTITY[enemy->type].max_second - 1);
        } else
            enemy->change_rect -= game->time_info->delta;
        enemy->shot -= game->time_info->delta;
    } else
        enemy->offset.x = 0;
}

static void attack_player(entity_t *enemy, save_t *save, game_t *game)
{
    if (enemy->cooldown <= 0) {
        if (enemy->type == E_BOSS) {
            add_projectile(game, &enemy->pos, enemy->dist);
        } else {
            save->info->item_info[INFO_HEALTH] -= ENEMY[enemy->type].attack
                * save->info->difficulty;
            sfMusic_play(game->music[HURT]);
            game->time_info->shot = TIME_OVERLAY;
        }
        enemy->shot = TIME_OVERLAY;
        enemy->cooldown = ENEMY[enemy->type].cooldown *
            (2 - save->info->difficulty);
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

static void enemy_action(entity_t *enemy, game_t *game, save_t *save)
{
    if (enemy->dist < ENEMY[enemy->type].attack_range * save->info->difficulty
        || enemy->change_pos > 0)
        attack_player(enemy, save, game);
    else
        get_new_position(enemy, game, save->info->difficulty);
}

void enemies_movement(game_t *game, linked_list_t *enemies, save_t *save)
{
    entity_t *tmp = NULL;
    node_t *next = NULL;

    for (node_t *head = enemies->head; head != NULL; head = next) {
        next = head->next;
        tmp = head->data;
        if (tmp->dist > DISTANCE_ENEMY || tmp->type < NB_ITEM
            || tmp->type >= E_BOSS_PROJECTILE)
            continue;
        if (tmp->type == E_BOSS && tmp->see == sfTrue)
            add_node_boss(save->boss, tmp->health);
        if (tmp->is_alive == sfFalse) {
            change_death_rect(tmp, save, game, head);
            continue;
        }
        if (move_closer(tmp, game, save->info->difficulty) == sfTrue)
            continue;
        enemy_action(tmp, game, save);
    }
}
