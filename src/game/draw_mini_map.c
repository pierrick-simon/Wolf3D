/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** draw_mini_map
*/

#include "game.h"
#include "save.h"

#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

static void reveal_tile(save_t *save, int x, int y)
{
    if (save->map[y][x] == 0) {
        save->mini_map[y + MINI_MAP_OFFSET][x + MINI_MAP_OFFSET] =
            sfTransparent;
        return;
    }
    if (save->map[y][x] == 4) {
        save->mini_map[y + MINI_MAP_OFFSET][x + MINI_MAP_OFFSET] = sfGreen;
        return;
    }
    if (save->map[y][x] == 1)
        save->mini_map[y + MINI_MAP_OFFSET][x + MINI_MAP_OFFSET] = GREY;
    else
        save->mini_map[y + MINI_MAP_OFFSET][x + MINI_MAP_OFFSET] = LIGHT_GREY;
}

static void reveal_line(
    save_t *save, sfVector2i player_tile, sfVector2i new_tile)
{
    int x = abs(new_tile.x - player_tile.x);
    int y = abs(new_tile.y - player_tile.y) * -1;
    int next = x + y;
    int tmp = 0;

    while (true) {
        reveal_tile(save, player_tile.x, player_tile.y);
        if ((player_tile.x == new_tile.x && player_tile.y == new_tile.y)
            || save->map[player_tile.y][player_tile.x] != 0)
            break;
        tmp = next * 2;
        if (tmp >= y) {
            next += y;
            player_tile.x += player_tile.x < new_tile.x ? 1 : -1;
        }
        if (tmp <= x) {
            next += x;
            player_tile.y += player_tile.y < new_tile.y ? 1 : -1;
        }
    }
}

static void update_around(save_t *save, sfVector2i *player_tile, int i)
{
    sfVector2i new_tile = {0, 0};
    sfVector2i copy = {player_tile->x, player_tile->y};

    for (int j = MINI_MAP_SHOW * -1; j <= MINI_MAP_SHOW; j++) {
        if (sqrt(i * i + j * j) > MINI_MAP_SHOW)
            continue;
        new_tile.x = player_tile->x + j;
        new_tile.y = player_tile->y + i;
        reveal_line(save, copy, new_tile);
    }
}

static void draw_look(system_t *sys, sfRectangleShape *mini_map)
{
    float angle_center = DEG(sys->save->info->start_angle) - 90;
    sfVector2f center = {
        MINI_MAP_BORDER + MINI_MAP_SIZE / 2,
        MINI_MAP_BORDER + MINI_MAP_SIZE / 2};

    sfRectangleShape_setSize(mini_map,
        (sfVector2f){MINI_MAP_RAY, MINI_MAP_TILE});
    sfRectangleShape_setFillColor(mini_map, sfGreen);
    sfRectangleShape_setPosition(mini_map, (sfVector2f){center.x, center.y});
    sfRectangleShape_setOrigin(mini_map, (sfVector2f){MINI_MAP_RAY / 2, 0});
    for (int i = MINI_MAP_FOV * -1; i <= MINI_MAP_FOV; i += MINI_MAP_FOV) {
        sfRectangleShape_setRotation(mini_map, angle_center + i);
        sfRenderWindow_drawRectangleShape(sys->window, mini_map, NULL);
    }
    sfRectangleShape_setRotation(mini_map, 0);
    sfRectangleShape_setOrigin(mini_map, (sfVector2f){0, 0});
}

static void draw_center(system_t *sys, sfRectangleShape *mini_map)
{
    sfRectangleShape_setPosition(mini_map, (sfVector2f){(float)MINI_MAP_SIZE /
        2 + MINI_MAP_BORDER, (float)MINI_MAP_SIZE
        / 2 + MINI_MAP_BORDER});
    sfRectangleShape_setFillColor(mini_map, sfBlack);
    sfRectangleShape_setSize(mini_map,
        (sfVector2f){MINI_MAP_CURSOR, MINI_MAP_CURSOR});
    sfRectangleShape_setOrigin(mini_map,
        (sfVector2f){MINI_MAP_CURSOR / 2, MINI_MAP_CURSOR / 2});
    sfRenderWindow_drawRectangleShape(sys->window, mini_map, NULL);
    sfRectangleShape_setOrigin(mini_map, (sfVector2f){0, 0});
}

static void draw_border(
    system_t *sys, sfRectangleShape *mini_map, sfTexture *texture)
{
    sfRectangleShape_setFillColor(mini_map, sfWhite);
    sfRectangleShape_setTexture(mini_map, texture, false);
    sfRectangleShape_setPosition(mini_map, (sfVector2f){0, 0});
    sfRectangleShape_setSize(mini_map, (sfVector2f){MINI_MAP_SIZE
        + MINI_MAP_BORDER * 2, MINI_MAP_BORDER});
    sfRenderWindow_drawRectangleShape(sys->window, mini_map, NULL);
    sfRectangleShape_setPosition(mini_map, (sfVector2f){0, MINI_MAP_SIZE
        + MINI_MAP_BORDER});
    sfRenderWindow_drawRectangleShape(sys->window, mini_map, NULL);
    sfRectangleShape_setPosition(mini_map, (sfVector2f){0, 0});
    sfRectangleShape_setSize(mini_map, (sfVector2f){MINI_MAP_BORDER,
        MINI_MAP_SIZE + MINI_MAP_BORDER * 2});
    sfRenderWindow_drawRectangleShape(sys->window, mini_map, NULL);
    sfRectangleShape_setPosition(mini_map, (sfVector2f){MINI_MAP_SIZE
        + MINI_MAP_BORDER, 0});
    sfRenderWindow_drawRectangleShape(sys->window, mini_map, NULL);
}

static void draw_square(
    system_t *sys, sfRectangleShape *mini_map, sfVector2i *player_tile)
{
    sfVector2f pos = {0, 0};
    sfVector2f size = {MINI_MAP_TILE, MINI_MAP_TILE};
    float offset_x = MINIOFF((int)sys->save->info->start_pos.x);
    float offset_y = MINIOFF((int)sys->save->info->start_pos.y);

    for (int i = -MINI_MAP_OFFSET; i <= MINI_MAP_OFFSET; i++) {
        for (int j = -MINI_MAP_OFFSET; j <= MINI_MAP_OFFSET; j++) {
            pos.x = MINI_MAP_BORDER + (j + MINI_MAP_OFFSET)
                * MINI_MAP_TILE - offset_x;
            pos.y = MINI_MAP_BORDER + (i + MINI_MAP_OFFSET)
                * MINI_MAP_TILE - offset_y;
            sfRectangleShape_setFillColor(mini_map, sys->save->mini_map
                [player_tile->y + i + MINI_MAP_OFFSET]
                [player_tile->x + j + MINI_MAP_OFFSET]);
            sfRectangleShape_setSize(mini_map, size);
            sfRectangleShape_setPosition(mini_map, pos);
            sfRenderWindow_drawRectangleShape(sys->window, mini_map, NULL);
        }
    }
}

void draw_minimap(
    system_t *sys, sfRectangleShape *mini_map, sfTexture *texture)
{
    sfVector2i player_tile = {floor(sys->save->info->start_pos.x / TILE_SIZE),
        floor(sys->save->info->start_pos.y / TILE_SIZE)};

    sfRectangleShape_setTexture(mini_map, NULL, false);
    sfRectangleShape_setSize(mini_map, (sfVector2f){MINI_MAP_SIZE +
        MINI_MAP_BORDER * 2, MINI_MAP_SIZE + MINI_MAP_BORDER * 2});
    sfRectangleShape_setFillColor(mini_map, sfWhite);
    sfRectangleShape_setPosition(mini_map, (sfVector2f){0, 0});
    sfRenderWindow_drawRectangleShape(sys->window, mini_map, NULL);
    draw_look(sys, mini_map);
    for (int i = MINI_MAP_SHOW * -1; i <= MINI_MAP_SHOW; i++)
        update_around(sys->save, &player_tile, i);
    draw_square(sys, mini_map, &player_tile);
    draw_center(sys, mini_map);
    draw_border(sys, mini_map, texture);
}
