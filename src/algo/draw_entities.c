/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** draw_entities.c
*/

#include "game.h"
#include "entities.h"

static void set_center(game_t *game, draw_entity_t *info, ray_t center)
{
    sfVector2f ratio = {0};
    entity_id_t type = -1;

    if (info->entity->type < NB_ITEM || !info->entity->is_alive ||
        info->dist.y >= center.len / (float)TILE_SIZE)
        return;
    type = info->entity->type;
    ratio = (sfVector2f){(info->end.x - ((float)WIN_WIDTH / 2.0)) /
        (info->end.x - info->start.x), 1 - (((info->end.y) -
        ((float)WIN_HEIGHT / 2.0)) / ((info->end.y) - (info->start.y)))};
    if (ratio.x > 0 && ratio.x < 1 && ratio.y > 0 && ratio.y < 1) {
        game->map->entity_center = info->entity->id;
        if (ratio.x > ENTITY[type].weakness.left &&
            ratio.x < ENTITY[type].weakness.left + ENTITY[type].weakness.width
            && ratio.y > ENTITY[type].weakness.top &&
            ratio.y < ENTITY[type].weakness.top + ENTITY[type].weakness.height)
            game->map->is_weakness = sfTrue;
        else
            game->map->is_weakness = sfFalse;
    }
}

static void change_color_sprite(sfVertex *color,
    entity_t *entity, game_t *game)
{
    if (entity->damage >= 0) {
        *color = (sfVertex){.color = sfRed};
        entity->damage -= game->time_info->delta;
    } else
        *color = (sfVertex){.color = sfWhite};
}

static void disp_entitie(draw_entity_t *info,
    game_t *game, ray_t rays[NB_RAYS])
{
    sfVertex tmp = {0};

    change_color_sprite(&tmp, info->entity, game);
    set_center(game, info, rays[(int)((float)NB_RAYS / 2.0)]);
    for (int stripe = info->start.x; stripe < info->end.x; stripe++) {
        if (stripe > 0 && stripe < WIN_WIDTH
            && info->dist.y < rays[stripe].len / (float)TILE_SIZE) {
            tmp.position = (sfVector2f){stripe, info->start.y};
            tmp.texCoords = (sfVector2f)
                {((float)((stripe - info->start.x) / (float)(info->end.x -
                info->start.x)) * ENTITY[info->entity->type].text_size.x) +
                info->entity->offset.x, info->entity->offset.y};
            sfVertexArray_append(game->map->line, tmp);
            tmp.position.y = info->end.y;
            tmp.texCoords.y = ENTITY[info->entity->type].text_size.y +
                info->entity->offset.y;
            sfVertexArray_append(game->map->line, tmp);
        }
    }
}

static void get_dist(entity_t *entity, game_t *game, draw_entity_t *info)
{
    sfVector2f v = game->player->v;
    sfVector2f n = game->player->n;

    info->diff = (sfVector2f)
        {(entity->pos.x - game->player->pos.x) / (float)TILE_SIZE,
        (entity->pos.y - game->player->pos.y) / (float)TILE_SIZE};
    info->inv = (1.0 / ((n.x * v.y) - (v.x * n.y)));
    info->dist = (sfVector2f)
        {info->inv * ((v.x * info->diff.y) - (v.y * info->diff.x)),
        info->inv * ((n.x * info->diff.y) - (n.y * info->diff.x))};
}

static void draw_entitie(system_t *sys,
    entity_t *entity, game_t *game, ray_t rays[NB_RAYS])
{
    draw_entity_t info = {0};
    float ratio = ENTITY[entity->type].text_size.y /
        ENTITY[entity->type].text_size.x;
    float offset = (ENTITY[entity->type].y * DIST_OFFSET) / entity->dist;

    get_dist(entity, game, &info);
    if (info.dist.y <= 0)
        return;
    info.x = (int)((WIN_WIDTH / 2) * (1 + (info.dist.x / info.dist.y)));
    info.size = abs(((int)((WIN_HEIGHT / info.dist.y) *
        ENTITY[entity->type].factor)));
    info.end = (sfVector2i){info.size / 2 + info.x, ((info.size * ratio) / 2 +
        WIN_HEIGHT / 2) + offset + game->player->cam_angle};
    info.start = (sfVector2i){- info.size / 2 + info.x, (-(info.size * ratio)
        / 2 + WIN_HEIGHT / 2) + offset + game->player->cam_angle};
    info.entity = entity;
    disp_entitie(&info, game, rays);
    sfRenderWindow_drawVertexArray(sys->window,
        game->map->line, &game->state_entities[info.entity->type]);
    sfVertexArray_clear(game->map->line);
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
