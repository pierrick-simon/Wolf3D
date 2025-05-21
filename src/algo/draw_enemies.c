/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** draw_enemies.c
*/

#include "game.h"
#include "element.h"

static void disp_enemy(draw_enemy_t *info, system_t *sys,
    game_t *game, ray_t rays[NB_RAYS])
{
    sfVertex tmp = {.color = sfWhite};

    for (int stripe = info->start.x; stripe < info->end.x; stripe++) {
        if (info->dist.y > 0 && stripe > 0 && stripe < NB_RAYS &&
            (info->dist.y < rays[stripe].len / (float)TILE_SIZE ||
            rays[stripe].len == 0.0)) {
            tmp.position = (sfVector2f){stripe, info->start.y};
            tmp.texCoords = (sfVector2f)
                {((float)(stripe - info->start.x) / (float)(info->end.x -
                info->start.x)) * ENEMY[info->type].text_size.x, 0};
            sfVertexArray_append(game->map->line, tmp);
            tmp.position.y = info->end.y;
            tmp.texCoords.y = ENEMY[info->type].text_size.y;
            sfVertexArray_append(game->map->line, tmp);
        }
    }
    sfRenderWindow_drawVertexArray(sys->window,
        game->map->line, &game->state_enemies[info->type]);
    sfVertexArray_clear(game->map->line);
}

static void draw_enemy(system_t *sys,
    enemy_t *enemy, game_t *game, ray_t rays[NB_RAYS])
{
    draw_enemy_t info = {0};
    sfVector2f v = game->player->center_ray.v;
    sfVector2f n = (sfVector2f){(v.y * (DEG(FOV) / 100.0)),
        (-v.x * (DEG(FOV) / 100.0))};

    info.diff = (sfVector2f)
        {(enemy->pos.x - game->player->pos.x) / (float)TILE_SIZE,
        (enemy->pos.y - game->player->pos.y) / (float)TILE_SIZE};
    info.inv = (1.0 / ((n.x * v.y) - (v.x * n.y)));
    info.dist = (sfVector2f)
        {info.inv * ((v.x * info.diff.y) - (v.y * info.diff.x)),
        info.inv * ((n.x * info.diff.y) - (n.y * info.diff.x))};
    info.x = (int)((NB_RAYS / 2) * (1 + (info.dist.x / info.dist.y)));
    info.size = abs((int)(WIN_HEIGHT / (info.dist.y)));
    info.start = (sfVector2i){- info.size / 2 + info.x,
        -info.size / 2 + WIN_HEIGHT / 2};
    info.end = (sfVector2i){info.size / 2 + info.x,
        info.size / 2 + WIN_HEIGHT / 2};
    info.type = enemy->type;
    disp_enemy(&info, sys, game, rays);
}

void draw_enemies(game_t *game, system_t *sys)
{
    node_t *node = game->player->save->enemies->tail;

    while (node != NULL) {
        draw_enemy(sys, node->data, game, game->map->rays);
        node = node->prev;
    }
}
