/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** update
*/

#include "game.h"
#include "save.h"
#include "entities.h"
#include <stdio.h>
#include <math.h>

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

void update_toolbar_percent(draw_textbox_t *draw, int nb)
{
    sprintf(draw->str, "%03d", nb);
    draw->color = sfGreen;
    if (nb < MAX_HEALTH / 3 * 2)
        draw->color = ORANGE;
    if (nb < MAX_HEALTH / 3)
        draw->color = sfRed;
}

static void update_flashlight(system_t *sys, game_t *game)
{
    if (game->light->flash_on == sfTrue) {
        sys->save->info->item_info[INFO_FLASHLIGHT] -=
            game->time_info->delta * 2;
        if (sys->save->info->item_info[INFO_FLASHLIGHT] <= 0.0) {
            sys->save->info->item_info[INFO_FLASHLIGHT] = 0;
            game->light->flash_on = sfFalse;
            move_rect(game->tool->flashlight->sprite,
                &game->tool->flashlight->rectangle,
                FLASHLIGHT_SPRITE_X, FLASHLIGHT_SPRITE_STATUS);
        }
    }
    update_toolbar_percent(&game->tool->draw[TOOL_FLASH_NB],
        sys->save->info->item_info[INFO_FLASHLIGHT]);
}

static void update_toolbar(system_t *sys, game_t *game)
{
    int gap = MAX_HEALTH / HEAD_SPRITE_STATUS;
    int count = 0;

    for (int i = MAX_HEALTH - gap; i >= 0; i -= gap) {
        if (sys->save->info->item_info[INFO_HEALTH] > i) {
            game->tool->head->rectangle.top = HEAD_SPRITE_Y * count;
            break;
        }
        count++;
    }
    update_flashlight(sys, game);
    update_ammo(sys, game);
    update_toolbar_percent(&game->tool->draw[TOOL_HEALTH_NB],
        sys->save->info->item_info[INFO_HEALTH]);
    update_toolbar_percent(&game->tool->draw[TOOL_STAM_NB],
        sys->save->info->item_info[INFO_STAMINA]);
    sprintf(game->tool->draw[TOOL_FPS].str, "%3.0f",
        1.0 / game->time_info->delta);
    sprintf(game->tool->draw[TOOL_SCORE_NB].str, "%09d",
        sys->save->info->score);
}

static void update_saving(system_t *sys, toolbar_t *tool, float delta)
{
    float sec = 0;

    tool->last_save += delta;
    if (tool->last_save > AUTO_SAVE)
        tool->save = sys->save->info->time;
    sec = (float)(sys->save->info->time - tool->save) / SEC_IN_MICRO;
    if (tool->save == -1 || sec > 1) {
        tool->saving = sfFalse;
        return;
    }
    if (sec > 0.1)
        save_map(sys->save);
    tool->last_save = 0;
    tool->saving = sfTrue;
    sprintf(tool->draw[TOOL_SAVE].str, "saving...");
    if (sec < SAVE_TIME * 2)
        sprintf(tool->draw[TOOL_SAVE].str, "saving..");
    if (sec < SAVE_TIME)
        sprintf(tool->draw[TOOL_SAVE].str, "saving.");
}

static void update_sprint(game_t *game, save_t *save)
{
    if (save->info->item_info[INFO_STAMINA] != MAX_HEALTH
        && game->player->is_sprinting == sfFalse
        && game->tool->no_sprint > SEC_IN_MICRO) {
        save->info->item_info[INFO_STAMINA]++;
        game->tool->no_sprint = 0;
    }
    if (save->info->item_info[INFO_STAMINA] == 0)
        game->player->is_sprinting = sfFalse;
    if (game->tool->sprint > SEC_IN_MICRO / 10 && game->tool->sprint != 0) {
        save->info->item_info[INFO_STAMINA]--;
        game->tool->sprint = 0;
    }
    if (game->player->is_sprinting == sfFalse)
        game->tool->no_sprint += game->time_info->delta * SEC_IN_MICRO;
    else
        game->tool->sprint += game->time_info->delta * SEC_IN_MICRO;
}

static void update_interact(toolbar_t *tool, player_t *player, int **map)
{
    sfVector2i casted_pos = cast_pos(&player->center_ray.pos,
        player->center_ray.type);

    if (casted_pos.x < 0 || casted_pos.y < 0) {
        tool->interact = sfFalse;
        return;
    }
    if ((player->center_ray.distance < OPEN_DISTANCE &&
        map[casted_pos.y][casted_pos.x] == wall_textures[DOOR].value)
        || (player->center_ray.distance < FINISH_DISTANCE &&
        map[casted_pos.y][casted_pos.x] == wall_textures[FINAL].value)) {
            tool->interact = sfTrue;
            return;
    }
    tool->interact = sfFalse;
}

static void update_music_volume(
    system_t *sys, weapon_t *weapon, sfMusic **music)
{
    double volume = sys->state->volume;

    sfMusic_setVolume(sys->save->music, volume);
    for (int i = 0; i < NB_MUSIC; i++)
        sfMusic_setVolume(music[i], volume);
    for (int i = 0; i < NB_WEAPON; i++)
        sfMusic_setVolume(weapon->info[i].sound, volume);
}

void update_all(system_t *sys, game_t *game)
{
    update_save(sys, game);
    update_saving(sys, game->tool, game->time_info->delta);
    update_time(sys->save, sys->save->info->time, game->time_info, game);
    update_sprint(game, sys->save);
    update_toolbar(sys, game);
    update_interact(game->tool, game->player, sys->save->map);
    update_music_volume(sys, game->weapon, game->music);
    shot_gun_anim(game->weapon, game->time_info,
        game->tool, sys->save->info->weapons);
    cast_all_rays(game, sys->save);
    handle_items(sys->save, game);
    if (sys->save->info->item_info[INFO_HEALTH] <= 0)
        sys->state->scene = LOSE;
}
