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

static void update_time(
    save_t *save, sfUint64 time, time_info_t *time_info, game_t *game)
{
    int tmp = 0;
    int min = 0;
    int sec = 0;

    if (time_info->time == 0)
        time_info->time = time;
    time_info->start_time =
        sfClock_getElapsedTime(time_info->clock).microseconds;
    tmp = time_info->time / SEC_IN_MICRO;
    min = tmp / MIN_IN_SEC;
    sec = tmp % MIN_IN_SEC;
    sprintf(game->tool->draw[TOOL_TIME_NB].str, "%02d:%02d", min, sec);
    save->info->time = time_info->time;
}

void update_time_end(time_info_t *time_info)
{
    time_info->end_time =
        sfClock_getElapsedTime(time_info->clock).microseconds;
    time_info->time += time_info->end_time - time_info->start_time;
    time_info->delta = (time_info->end_time - time_info->start_time) /
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
    sys->save->info->start_pos = player->pos;
    sys->save->info->start_angle = player->angle;
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

static void update_toolbar(system_t *sys, toolbar_t *tool, double delta)
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
    sprintf(tool->draw[TOOL_FPS].str, "%3.0f", 1.0 / delta);
    sprintf(tool->draw[TOOL_SCORE_NB].str, "%09d", sys->save->info->score);
}

static void update_saving(system_t *sys, toolbar_t *tool)
{
    float sec = (float)(sys->save->info->time - tool->save) / SEC_IN_MICRO;

    if (tool->save == -1 || sec > 1) {
        tool->saving = sfFalse;
        return;
    }
    tool->saving = sfTrue;
    sprintf(tool->draw[TOOL_SAVE].str, "saving...");
    if (sec < SAVE_TIME * 2)
        sprintf(tool->draw[TOOL_SAVE].str, "saving..");
    if (sec < SAVE_TIME)
        sprintf(tool->draw[TOOL_SAVE].str, "saving.");
}

void update_all(system_t *sys, game_t *game)
{
    update_save(sys, game->player);
    update_saving(sys, game->tool);
    update_time(sys->save, sys->save->info->time, game->time_info, game);
    update_toolbar(sys, game->tool, game->time_info->delta);
    shot_gun_anim(game->weapon, game->time_info->time);
    cast_all_rays(game);
}
