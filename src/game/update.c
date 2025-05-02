/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** update
*/

#include "game.h"
#include "save.h"
#include <stdio.h>

static void update_guns(weapon_t *weapon)
{
    int ind = weapon->weapon;

    if (weapon->info[ind].current_tile == weapon->info[ind].nb_tile)
        weapon->info[ind].current_tile = 0;
    if (ind == PUNCH) {
        if (weapon->info[ind].current_tile == 0)
            weapon->info[ind].posf.x = HAND_POS;
        else
            weapon->info[ind].posf.x = PUNCH_POS;
    }
    sfSprite_setPosition(weapon->sprite, weapon->info[ind].posf);
}

static void shot_gun_anim(weapon_t *weapon, sfInt64 time)
{
    double diff = (double)(time - weapon->shot) / SEC_IN_MICRO;
    int ind = weapon->weapon;

    for (int i = 0; i < weapon->info[ind].nb_tile; i++) {
        if (diff > weapon->info[ind].speed * i
            && diff < weapon->info[ind].speed * (i + 1)
            && weapon->info[ind].current_tile == i) {
            move_rect(weapon->sprite, &weapon->info[ind].rectangle,
                weapon->info[ind].size.x, weapon->info[ind].nb_tile);
            weapon->info[ind].current_tile++;
            break;
        }
    }
    update_guns(weapon);
}

static void update_time(time_info_t *time_info)
{
    time_info->prev_time = time_info->time;
    time_info->time = sfClock_getElapsedTime(time_info->clock).microseconds;
    time_info->delta = (time_info->time - time_info->prev_time) /
        (float)SEC_IN_MICRO;
}

static void update_save(system_t *sys, player_t *player)
{
    if (sys->save->update == sfFalse) {
        player->pos = sys->save->info->start_pos;
        player->angle = sys->save->info->start_angle;
        player->save = sys->save;
        sys->save->update = sfTrue;
    }
}

static void update_toolbar_percent(draw_textbox_t *draw, int nb)
{
    sprintf(draw->str, "%03d", nb);
    draw->color = sfGreen;
    if (nb < MAX_HEALTH / 3 * 2)
        draw->color = ORANGE;
    if (nb < MAX_HEALTH / 3)
        draw->color = sfRed;
}

static void update_toolbar(system_t *sys, toolbar_t *tool)
{
    int gap = MAX_HEALTH / HEAD_SPRITE_STATUS;
    int count = 0;

    for (int i = MAX_HEALTH - gap; i >= 0; i -= gap) {
        if (sys->save->info->health > i) {
            tool->head->rectangle.top = HEAD_SPRITE_Y * count;
            break;
        }
        count++;
    }
    update_toolbar_percent(&tool->draw[TOOL_AMMO_NB], sys->save->info->ammo);
    update_toolbar_percent(
        &tool->draw[TOOL_HEALTH_NB], sys->save->info->health);
    update_toolbar_percent(&tool->draw[TOOL_ARMOR_NB], sys->save->info->armor);
}

void update_all(system_t *sys, game_t *game)
{
    update_save(sys, game->player);
    update_time(game->time_info);
    update_toolbar(sys, game->tool);
    shot_gun_anim(game->weapon, game->time_info->time);
    cast_all_rays(game);
}
