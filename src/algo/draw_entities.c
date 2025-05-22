/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** draw_entities.c
*/

#include "game.h"
#include "entities.h"

static void set_center(game_t *game, draw_entity_t *info)
{
    if (info->start.y + game->player->jump_value <= WIN_HEIGHT / 2 &&
        info->end.y + game->player->jump_value >= WIN_HEIGHT / 2 &&
        info->start.x <= WIN_WIDTH / 2 && info->end.x >= WIN_WIDTH / 2 &&
        info->enemy->type >= NB_ITEM)
        game->map->entity_center = info->enemy->id;
}

static void disp_entitie(draw_entity_t *info, system_t *sys,
    game_t *game, ray_t rays[NB_RAYS])
{
    sfVertex tmp = {.color = sfWhite};

    set_center(game, info);
    for (int stripe = info->start.x; stripe < info->end.x; stripe++) {
        if (info->dist.y > 0 && stripe > 0 && stripe < WIN_WIDTH
            && info->dist.y < rays[stripe].len / (float)TILE_SIZE) {
            tmp.position = (sfVector2f){stripe, info->start.y
                + game->player->jump_value};
            tmp.texCoords = (sfVector2f)
                {((float)(stripe - info->start.x) / (float)(info->end.x -
                info->start.x)) * ENTITY[info->enemy->type].text_size.x, 0};
            sfVertexArray_append(game->map->line, tmp);
            tmp.position.y = info->end.y + game->player->jump_value;
            tmp.texCoords.y = ENTITY[info->enemy->type].text_size.y;
            sfVertexArray_append(game->map->line, tmp);
        }
    }
    sfRenderWindow_drawVertexArray(sys->window,
        game->map->line, &game->state_entities[info->enemy->type]);
    sfVertexArray_clear(game->map->line);
}

static void get_dist(entity_t *enemy, game_t *game, draw_entity_t *info)
{
    sfVector2f v = game->player->v;
    sfVector2f n = game->player->n;

    info->diff = (sfVector2f)
        {(enemy->pos.x - game->player->pos.x) / (float)TILE_SIZE,
        (enemy->pos.y - game->player->pos.y) / (float)TILE_SIZE};
    info->inv = (1.0 / ((n.x * v.y) - (v.x * n.y)));
    info->dist = (sfVector2f)
        {info->inv * ((v.x * info->diff.y) - (v.y * info->diff.x)),
        info->inv * ((n.x * info->diff.y) - (n.y * info->diff.x))};
}

static void draw_entitie(system_t *sys,
    entity_t *enemy, game_t *game, ray_t rays[NB_RAYS])
{
    draw_entity_t info = {0};
    float ratio = ENTITY[enemy->type].text_size.y /
        ENTITY[enemy->type].text_size.x;

    get_dist(enemy, game, &info);
    info.x = (int)((WIN_WIDTH / 2) * (1 + (info.dist.x / info.dist.y)));
    info.size = abs(((int)((WIN_HEIGHT / info.dist.y) *
        ENTITY[enemy->type].factor)));
    info.end = (sfVector2i){info.size / 2 + info.x,
        (info.size * ratio) / 2 + WIN_HEIGHT / 2};
    info.start = (sfVector2i){- info.size / 2 + info.x,
        (-(info.size * ratio) / 2 + WIN_HEIGHT / 2)};
    info.enemy = enemy;
    disp_entitie(&info, sys, game, rays);
}

void draw_entities(game_t *game, system_t *sys)
{
    node_t *node = game->player->save->entities->tail;

    game->map->entity_center = NO_ENTITIE;
    while (node != NULL) {
        draw_entitie(sys, node->data, game, game->map->rays);
        node = node->prev;
    }
}
