/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** game_loop
*/

#include "wolf.h"

static void shot_gun_anim(game_t *game, weapon_t *weapon)
{
    int current = sfClock_getElapsedTime(game->clock).microseconds;
    double diff = (double)(current - weapon->shot) / SEC_IN_MICRO;

    for (int i = 0; i < WEAPON_NB_TILE; i++) {
        if (diff > WEAPON_FRAME * i
            && diff < WEAPON_FRAME * (i + 1)
            && weapon->sprite.tile == i) {
            move_rect(&weapon->sprite, WEAPON_SPRITE_X, WEAPON_NB_TILE);
            weapon->sprite.tile++;
            break;
        }
    }
    if (weapon->sprite.tile == WEAPON_NB_TILE)
        weapon->sprite.tile = 0;
}

void draw_map(game_t *game)
{
    sfVector2f pos = {0, 0};

    sfRectangleShape_setPosition(game->map->ceiling_floor, pos);
    sfRectangleShape_setFillColor(game->map->ceiling_floor, CEILING_COLOR);
    sfRenderWindow_drawRectangleShape(game->window,
        game->map->ceiling_floor, NULL);
    pos = (sfVector2f){0, WIN_HEIGHT / 2};
    sfRectangleShape_setPosition(game->map->ceiling_floor, pos);
    sfRectangleShape_setFillColor(game->map->ceiling_floor, FLOOR_COLOR);
    sfRenderWindow_drawRectangleShape(game->window,
        game->map->ceiling_floor, NULL);
}

void game_loop(game_t *game, weapon_t *weapon)
{
    while (sfRenderWindow_isOpen(game->window) == sfTrue) {
        events(game, weapon);
        shot_gun_anim(game, weapon);
        cast_all_rays(game);
        sfRenderWindow_clear(game->window, sfWhite);
        if (sfMusic_getStatus(game->music) == sfStopped)
            sfMusic_play(game->music);
        draw_map(game);
        sfRenderWindow_drawVertexArray(game->window, game->rays, NULL);
        sfRenderWindow_drawSprite(game->window, weapon->sprite.sprite, NULL);
        sfRenderWindow_display(game->window);
    }
}
