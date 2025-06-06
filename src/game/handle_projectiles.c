/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** handle_projectiles
*/

#include "game.h"
#include "entities.h"
#include "stdlib.h"
#include "linked_list.h"
#include <math.h>

static void change_movement_rect_p(
    entity_t *projectile, game_t *game, float speed)
{
    projectile->offset.y = 0;
    if (projectile->change_rect <= 0) {
        projectile->offset.x += ENTITY[projectile->type].text_size.x;
        if (projectile->offset.x >= ENTITY[projectile->type].max_first *
            ENTITY[projectile->type].text_size.x)
            projectile->offset.x = 0;
        projectile->change_rect = 20 / speed;
    } else
        projectile->change_rect -= game->time_info->delta;
}

static void handle_kill(
    entity_t *projectile, game_t *game, float *health, sfVector2f *pos)
{
    int tmp = projectile->health;

    if (*health > tmp) {
        projectile->see = sfTrue;
        projectile->is_alive = sfFalse;
        projectile->health = 0;
        *health -= tmp;
    } else {
        projectile->health -= *health;
        *health = 0;
    }
    if (game->player->pos.x == pos->x
        && game->player->pos.y == pos->y) {
        sfMusic_play(game->music[HURT]);
        game->time_info->shot = TIME_OVERLAY;
    }
}

static sfBool is_kill(
    entity_t *projectile, game_t *game, float *health, sfVector2f *pos)
{
    int value = ENTITY[projectile->type].text_size.x / 2;

    if (projectile->pos.x > pos->x - value
        && projectile->pos.x < pos->x + value
        && projectile->pos.y > pos->y - value
        && projectile->pos.y < pos->y + value) {
        handle_kill(projectile, game, health, pos);
        return sfTrue;
    }
    return sfFalse;
}

static sfBool return_value(entity_t *projectile, game_t *game)
{
    if (projectile->see == sfTrue) {
        return sfTrue;
    }
    if (projectile->next_pos.x == SKIP || projectile->next_pos.y == SKIP
        || is_arrived(projectile) == sfTrue
        || is_kill(projectile, game,
            &game->player->save->info->item_info[INFO_HEALTH],
            &game->player->pos) == sfTrue) {
        projectile->see = sfTrue;
        projectile->is_alive = sfFalse;
        projectile->health = 0;
        sfMusic_play(game->music[PLASMA_EXPLOSION]);
        return sfTrue;
    }
    return sfFalse;
}

static sfBool move_closer(entity_t *projectile, game_t *game, float difficulty)
{
    float dist = 0;
    float coef = 0;
    sfVector2f mov = {0};

    if (return_value(projectile, game) == sfTrue)
        return sfFalse;
    dist = sqrt(pow(projectile->pos.x - projectile->next_pos.x, 2) +
        pow(projectile->pos.y - projectile->next_pos.y, 2));
    coef = ENEMY[projectile->type].speed * difficulty
        * game->time_info->delta / dist;
    mov = (sfVector2f){projectile->next_pos.x - projectile->pos.x,
        projectile->next_pos.y - projectile->pos.y};
    projectile->pos.x += mov.x * coef;
    projectile->pos.y += mov.y * coef;
    change_movement_rect_p(projectile, game,
        ENEMY[projectile->type].speed * difficulty);
    return sfTrue;
}

static void do_explosion(
    entity_t *projectile, save_t *save, game_t *game, node_t *node)
{
    if (projectile->is_alive == sfFalse) {
        projectile->cooldown = DEATH_RECT;
        projectile->is_alive = sfTrue;
        expolde_wall(game, projectile, save);
    }
    if (ENTITY[projectile->type].max_second == 0) {
        delete_node(save->entities, node, &free);
        return;
    }
    projectile->offset.y = ENTITY[projectile->type].text_size.y;
    if (projectile->cooldown <= 0) {
        projectile->offset.x += ENTITY[projectile->type].text_size.x;
        projectile->cooldown = DEATH_RECT;
        if (projectile->offset.x >= ENTITY[projectile->type].max_second *
            ENTITY[projectile->type].text_size.x)
            delete_node(save->entities, node, &free);
    } else
        projectile->cooldown -= game->time_info->delta;
}

static void handle_colision(
    entity_t *projectile, linked_list_t *list, game_t *game)
{
    node_t *next = NULL;
    entity_t *tmp = NULL;
    float healt = 0;
    sfBool shot = sfFalse;

    for (node_t *head = list->head; head != NULL; head = next) {
        next = head->next;
        tmp = head->data;
        if (tmp == projectile || tmp->type < NB_ITEM
            || tmp->is_alive == sfFalse)
            continue;
        healt = tmp->health;
        if (is_kill(projectile, game, &healt, &tmp->pos) == sfTrue) {
            tmp->health = healt;
            shot = sfTrue;
            break;
        }
    }
    if (tmp->type < E_BOSS_PROJECTILE && shot == sfTrue)
        tmp->damage = TIME_OVERLAY;
}

void handle_projectiles(save_t *save, game_t *game)
{
    node_t *next = NULL;
    entity_t *tmp = NULL;

    for (node_t *head = save->entities->head; head != NULL; head = next) {
        next = head->next;
        tmp = head->data;
        if (tmp->type < E_BOSS_PROJECTILE)
            continue;
        if (tmp->see == sfFalse)
            handle_colision(tmp, save->entities, game);
        if (move_closer(tmp, game, save->info->difficulty) == sfFalse)
            do_explosion(tmp, save, game, head);
    }
}
