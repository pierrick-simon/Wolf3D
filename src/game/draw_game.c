/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** game_loop
*/

#include "save.h"

static void shot_gun_anim(weapon_t *weapon, sfInt64 time)
{
    double diff = (double)(time - weapon->shot) / SEC_IN_MICRO;

    for (int i = 0; i < WEAPON_NB_TILE; i++) {
        if (diff > WEAPON_FRAME * i
            && diff < WEAPON_FRAME * (i + 1)
            && weapon->sprite->tile == i) {
            move_rect(weapon->sprite, WEAPON_SPRITE_X, WEAPON_NB_TILE);
            weapon->sprite->tile++;
            break;
        }
    }
    if (weapon->sprite->tile == WEAPON_NB_TILE)
        weapon->sprite->tile = 0;
}

static void draw_map(system_t *sys, game_t *game)
{
    sfVector2f pos = {0, 0};

    sfRectangleShape_setPosition(game->map->ceiling_floor, pos);
    sfRectangleShape_setFillColor(game->map->ceiling_floor, CEILING_COLOR);
    sfRenderWindow_drawRectangleShape(sys->window,
        game->map->ceiling_floor, NULL);
    pos = (sfVector2f){0, WIN_HEIGHT / 2};
    sfRectangleShape_setPosition(game->map->ceiling_floor, pos);
    sfRectangleShape_setFillColor(game->map->ceiling_floor, FLOOR_COLOR);
    sfRenderWindow_drawRectangleShape(sys->window,
        game->map->ceiling_floor, NULL);
}

static void draw_toolbar(system_t *sys, game_t *game)
{
    sfVector2f pos = (sfVector2f){0, TOOLBAR_POS};

    sfRectangleShape_setPosition(game->map->ceiling_floor, pos);
    sfRectangleShape_setFillColor(game->map->ceiling_floor, TOOLBAR_COLOR);
    sfRenderWindow_drawRectangleShape(sys->window,
        game->map->ceiling_floor, NULL);
}

static void draw_crossair(system_t *sys, player_t *player)
{
    sfRenderWindow_drawCircleShape(sys->window,
        player->crossair->circle, &player->crossair->state);
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
        player->pos = sys->save->start_pos;
        player->angle = sys->save->start_angle;
        player->save = sys->save;
        sys->save->update = sfTrue;
    }
}

void draw_game(system_t *sys, void *structure)
{
    game_t *game = (game_t *)structure;

    update_save(sys, game->player);
    update_time(game->time_info);
    game_events(sys, game);
    shot_gun_anim(game->weapon, game->time_info->time);
    cast_all_rays(game);
    sfRenderWindow_clear(sys->window, sfWhite);
    if (sfMusic_getStatus(sys->music) == sfStopped)
        sfMusic_play(sys->music);
    draw_map(sys, game);
    sfRenderWindow_drawVertexArray(sys->window,
        game->map->quads, &game->map->wall_state);
    sfRenderWindow_drawSprite(
        sys->window, game->weapon->sprite->sprite, NULL);
    draw_toolbar(sys, game);
    draw_crossair(sys, game->player);
    sfRenderWindow_display(sys->window);
}
