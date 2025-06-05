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

static void next_pos(save_t *save, entity_t *entity, sfVector2f *player)
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
    entity->next_pos.x = entity->pos.x + value *
        (player->x - entity->pos.x) / entity->dist;
    entity->next_pos.y = entity->pos.y + value *
        (player->y - entity->pos.y) / entity->dist;
}

void add_projectile(game_t *game, sfVector2f *boss, int dist)
{
    entity_t *entity = malloc(sizeof(entity_t));

    entity->type = E_BOSS_PROJECTILE;
    entity->pos = *boss;
    entity->dist = dist;
    next_pos(game->player->save, entity, &game->player->pos);
    entity->offset = (sfVector2f){0, 0};
    entity->is_alive = sfTrue;
    entity->damage = SKIP;
    entity->change_pos = SKIP;
    entity->change_rect = 0;
    entity->health = ENEMY[E_BOSS_PROJECTILE].health;
    entity->prev_tile = (sfVector2i){0, 0};
    entity->see = sfFalse;
    push_to_head(game->player->save->entities, entity);
}

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

static sfBool is_kill(entity_t *projectile, game_t *game, float difficulty)
{
    int value = ENTITY[projectile->type].text_size.x / 2;

    if (projectile->pos.x > game->player->pos.x - value
        && projectile->pos.x < game->player->pos.x + value
        && projectile->pos.y > game->player->pos.y - value
        && projectile->pos.y < game->player->pos.y + value) {
            game->player->save->info->item_info[INFO_HEALTH] -=
                ENEMY[projectile->type].attack * difficulty;
            sfMusic_play(game->music[HURT]);
            game->time_info->shot = TIME_OVERLAY;
        return sfTrue;
    }
    return sfFalse;
}

static sfBool return_value(
    entity_t *projectile, game_t *game, float difficulty)
{
    if (projectile->see == sfTrue) {
        return sfTrue;
    }
    if (projectile->next_pos.x == SKIP || projectile->next_pos.y == SKIP
        || is_arrived(projectile) == sfTrue
        || is_kill(projectile, game, difficulty) == sfTrue) {
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

    if (return_value(projectile, game, difficulty) == sfTrue)
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

void handle_projectiles(save_t *save, game_t *game)
{
    node_t *next = NULL;
    entity_t *tmp = NULL;

    for (node_t *head = save->entities->head; head != NULL; head = next) {
        next = head->next;
        tmp = head->data;
        if (tmp->type < E_BOSS_PROJECTILE)
            continue;
        if (move_closer(tmp, game, save->info->difficulty) == sfFalse)
            do_explosion(tmp, save, game, head);
    }
}
