/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** shot.c
*/

#include "game.h"
#include "entities.h"

static void destroy_wall(int **map, player_t *player, game_t *game)
{
    sfVector2i casted_pos = cast_pos(&player->center_ray.pos,
        player->center_ray.type);

    if (casted_pos.x < 0 || casted_pos.y < 0)
        return;
    for (weapon_id_t i = 0; i < NB_WEAPON; ++i) {
        if (game->weapon->weapon == i && map[casted_pos.y][casted_pos.x] == 3
            && game->weapon->info[i].range > player->center_ray.distance) {
            map[casted_pos.y][casted_pos.x] = 0;
            player->save->info->score += 10;
            sfMusic_play(game->music[DESTROY_WALL]);
        }
    }
}

static void damage_enemy(game_t *game, node_t *node, entity_t *data)
{
    if (game->weapon->info[game->weapon->weapon].range < data->dist)
        return;
    data->health -= game->weapon->info[game->weapon->weapon].damage;
    if (data->health <= 0)
        delete_node(game->player->save->entities, node, free);
}

static void delete_center(game_t *game)
{
    node_t *node = game->player->save->entities->tail;
    entity_t *data = NULL;

    if (game->map->entity_center == NO_ENTITIE)
        return;
    while (node != NULL) {
        data = node->data;
        if (data->id == game->map->entity_center)
            return damage_enemy(game, node, data);
        node = node->prev;
    }
}

void shot(system_t *sys, weapon_t *weapon, game_t *game)
{
    double diff = (double)(game->time_info->time - weapon->shot)
        / SEC_IN_MICRO;
    int ind = weapon->weapon;

    if (diff < weapon->info[ind].speed * weapon->info[ind].nb_tile)
        return;
    if (sfKeyboard_isKeyPressed(sfKeySpace) ||
        sfJoystick_getAxisPosition(0, sfJoystickR) > 0) {
        if (weapon->weapon != PUNCH
            && sys->save->info->item_info[ind] == 0) {
            sfMusic_play(weapon->empty);
            return;
        }
        if (weapon->weapon != PUNCH)
            sys->save->info->item_info[ind]--;
        weapon->shot = game->time_info->time;
        delete_center(game);
        sfMusic_play(weapon->info[weapon->weapon].sound);
        destroy_wall(sys->save->map, game->player, game);
    }
}
