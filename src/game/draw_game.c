/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** game_loop
*/

#include "wolf.h"

static void shot_gun_anim(system_t *sys, weapon_t *weapon)
{
    int current = sfClock_getElapsedTime(sys->clock).microseconds;
    double diff = (double)(current - weapon->shot) / SEC_IN_MICRO;

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

void draw_game(system_t *sys, void *structure)
{
    game_t *game = (game_t *)structure;

    game_events(sys, game);
    shot_gun_anim(sys, game->weapon);
    cast_all_rays(game);
    sfRenderWindow_clear(sys->window, sfWhite);
    if (sfMusic_getStatus(sys->music) == sfStopped)
        sfMusic_play(sys->music);
    draw_map(sys, game);
    sfRenderWindow_drawVertexArray(sys->window,
        game->map->rays, &game->map->wall_state);
    sfRenderWindow_drawSprite(
        sys->window, game->weapon->sprite->sprite, NULL);
    draw_toolbar(sys, game);
    draw_crossair(sys, game->player);
    sfRenderWindow_display(sys->window);
}
