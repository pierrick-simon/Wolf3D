/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** update_save
*/

#include "game.h"
#include "save.h"
#include <math.h>

static void update_save_weapon(system_t *sys, weapon_t *weapon)
{
    weapon->horizontal_offset = 0;
    weapon->shot = -1;
    weapon->weapon = (int)log2(sys->save->info->start_weapon);
    sfSprite_setTexture(weapon->sprite,
        weapon->info[weapon->weapon].texture, sfTrue);
    sfSprite_setTextureRect(weapon->sprite,
        weapon->info[weapon->weapon].rectangle);
    sfSprite_setOrigin(weapon->sprite,
    (sfVector2f){weapon->info[weapon->weapon].size.x / 2,
    weapon->info[weapon->weapon].size.y});
}

void update_save(system_t *sys, game_t *game)
{
    if (sys->save->update == sfFalse) {
        game->player->pos = sys->save->info->start_pos;
        game->player->angle = sys->save->info->start_angle;
        game->player->save = sys->save;
        game->time_info->time = 0;
        game->tool->sprint = 0;
        game->tool->no_sprint = 0;
        game->tool->save = -1;
        game->tool->last_save = 0;
        game->light->last_min = sys->save->info->time
            / SEC_IN_MICRO / MIN_IN_SEC;
        update_save_weapon(sys, game->weapon);
        sys->save->update = sfTrue;
    }
    sys->save->info->start_pos = game->player->pos;
    sys->save->info->start_angle = game->player->angle;
}
