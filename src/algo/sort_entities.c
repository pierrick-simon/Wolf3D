/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** sort_entities.c
*/

#include "game.h"
#include "save.h"
#include "entities.h"
#include <math.h>

static bool cmp(void *first, void *second)
{
    entity_t *data_first = first;
    entity_t *data_second = second;

    if (data_first->dist < data_second->dist)
        return true;
    return false;
}

static void init_distances(game_t *game, player_t *player)
{
    node_t *node = game->player->save->entities->head;
    entity_t *data = NULL;
    sfVector2f v = {0};

    while (node != NULL) {
        data = node->data;
        v.x = data->pos.x - player->pos.x;
        v.y = data->pos.y - player->pos.y;
        data->dist = sqrt(v.x * v.x + v.y * v.y);
        node = node->next;
    }
}

void sort_entities(game_t *game)
{
    init_distances(game, game->player);
    sort_linked_list(game->player->save->entities, cmp);
}
